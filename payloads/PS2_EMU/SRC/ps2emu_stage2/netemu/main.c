#include <ps2emu/ps2emu.h>
#include <ps2emu/libc.h>
#include <ps2emu/io.h>
#include <ps2emu/cdvd.h>
#include <ps2emu/memory.h>
#include <ps2emu/vuart.h>
#include <ps2emu/patch.h>
#include <ps2emu/symbols.h>

#define CONFIG_FILE	"/tmp/cfg.bin"

typedef struct _payload_vars
{
	int setup_done;
	char iso_file[0x700];
	char mnt[0x100];
	uint8_t is_cd;
	uint8_t num_tracks;
	int limg_read;
	uint64_t iso_size;
	uint64_t debug_offset;
	int config_size;
	char cfg_suffix[0x20];
	char cfg_file[0x720];
} payload_vars;

payload_vars *vars = (payload_vars *)EXTENDED_DATA;

#ifdef DEBUG
#include "printf.c"
#define DPRINTF	printf

static INLINE void dump_stack_trace2(unsigned int n)
{
	int i = 1;
	
	if (n == 0)
		return;
	
	DPRINTF("--------STACK TRACE--------\n");
	
	void *p = get_patched_func_call_address();
	DPRINTF("%p\n", p);
	
	while (p && i < n)
	{
		p = get_call_address(i++);
		DPRINTF("%p\n", p);
	}
	
	DPRINTF("---------------------------\n");
}
	
#else
#define DPRINTF(...)
#define dump_stack_trace2(n)
#endif

/*static INLINE uint64_t get_file_size_dirty(int fd)
{
	uint64_t *structure = (uint64_t *) ((0x1270*fd) + *(uint64_t *)(TOC-0x4448) + 8);
	return structure[0x178/8];
}*/

/*PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_2(int, ufs_open_patched, (int unk, char *path))
{
	void *addr = get_patched_func_call_address();
	if(strstr(path, "log_file.bin"))
		goto done;
	
	if ((uint64_t)addr < 0x200000)	
		DPRINTF("ufs_open %s called from %p\n", path, addr);
	
	
	done:
	return DO_POSTCALL;
}

PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_2(int, ufs_fstat_patched, (int fd, ufs_stat *stat))
{
	//uint64_t file_size = get_file_size_dirty(fd);
	
	if (1)
	{
		DPRINTF("ufs_stat called from %p\n", get_patched_func_call_address());
	}
	
	return DO_POSTCALL;
}

PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_4(int, ufs_read_patched, (int fd, uint64_t offset, void *buf, uint64_t size))
{
	//uint64_t file_size = get_file_size_dirty(fd);
	
	if (1)
	{	
		DPRINTF("ufs_read %lx %lx called from %p\n", offset, size, get_patched_func_call_address());		
	}
	
	return DO_POSTCALL;
}*/

/*uint64_t dump_ram(uint64_t addr)
{
 return *(uint64_t *)addr;
}*/

PS2EMU_PATCHED_FUNCTION(int, open_iso, (int unk, char *path))
{
/*uint64_t val;
for(uint64_t i=0;i<0x50;i+=8)
{
val = dump_ram(0x3174478ULL+i);
int dump = ufs_open(0, "/tmp/dump");
ufs_write(dump, 1, (void *)val, 8);
}*/
	if (!vars->setup_done)
	{
//		if (strstr(path, "--COBRA--"))
	//	{

		int fd = ufs_open(0, CONFIG_FILE);
		if (fd >= 0)
		{
			uint8_t b;
			
			ufs_read(fd, 0, &b, 1);
			vars->is_cd = (b&1);
			
			ufs_read(fd, 1, vars->iso_file, 0x6FF);
			ufs_read(fd, 0x702, vars->mnt, 0xf0);
			if((strstr(vars->mnt, "mount")) || (strstr(path, "--COBRA--")))
			{
				uint8_t disable=0x00;
				ufs_write(fd, 0x702, &disable, 1);
				if (vars->is_cd)
				{
					// Read number of tracks
					uint8_t b;
					
					ufs_read(fd, 0x800, &b, 1);						
					vars->num_tracks = b;
				}		
			}
			
			else
			{
				vars->iso_file[0]=0;
			}
                        ufs_close(fd);
//		}
		}
		
		vars->setup_done = 1;
	}
	
	if (vars->iso_file[0])
		return ufs_open(unk, vars->iso_file+10);		
	
	return ufs_open(unk, path);
}

PS2EMU_PATCHED_FUNCTION(int, fstat_iso_patched, (int fd, ufs_stat *stat))
{
	int ret = ufs_fstat(fd, stat);
	
	if (vars->iso_file[0])
		vars->iso_size = stat->st_size;
	
	return ret;
}

PS2EMU_PATCHED_FUNCTION(int, read_iso_size, (int fd, uint64_t offset, uint64_t *iso_size, uint64_t size))
{
	if (vars->iso_file[0])
	{
		*iso_size = vars->iso_size;	
		return size;
	}
	
	return ufs_read(fd, offset, iso_size, size);
}

PS2EMU_PATCHED_FUNCTION(int, open_config, (int unk, char *path))
{
		if(vars->iso_file[0])
		{
			strcpy(vars->cfg_suffix, ".CONFIG");
			strcpy(vars->cfg_file, vars->iso_file+10);
			strcpy(vars->cfg_file+strlen(vars->iso_file)-10, vars->cfg_suffix);
			int fd=ufs_open(0, vars->cfg_file);
			if(fd>=0)
			{
				ufs_stat stat;
				ufs_fstat(fd, &stat);
				vars->config_size=stat.st_size;
			}
			return fd;
		}
	return ufs_open(unk, path);
}

PS2EMU_PATCHED_FUNCTION(int, read_config_size, (int fd, uint64_t offset, uint64_t *config_size, uint64_t size))
{
	if(vars->iso_file[0])
	{
		
		*config_size=vars->config_size;
		return size;
	}
	return ufs_read(fd, offset, config_size, size);
}

PS2EMU_PATCHED_FUNCTION(int, decrypt_config, (int fd, uint64_t offset, void *buf, uint64_t size))
{
	if(vars->iso_file[0])
	{
		return ufs_read(fd, offset, buf, size);
	}
	return decrypt(fd, offset, buf, size);
}

PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_4(int, cdvd_read_patched, (int fd, uint64_t lba, uint8_t *buf, uint64_t size))
{
	//DPRINTF("cdvd_read called from (%p): %lx %lx\n", get_patched_func_call_address(), lba, size);
	
	if (!vars->iso_file[0])
		return DO_POSTCALL;
	
	if (!vars->limg_read)
	{
		// limg is the first thing read
		vars->limg_read = 1;
		
		memset(buf, 0, size);
		*(uint32_t *)&buf[0] = 0x4C494D47;
		
		*(uint32_t *)&buf[8] = vars->iso_size / 0x800;
		*(uint32_t *)&buf[12] = 0x800;		
		
		if (!vars->is_cd)
		{
			*(uint32_t *)&buf[4] = 1;	
		}
		else
		{
			*(uint32_t *)&buf[4] = 2;
			
			if (vars->num_tracks != 0)
			{
				*(uint32_t *)&buf[8] = vars->iso_size / 0x930;
				*(uint32_t *)&buf[12] = 0x930;
			}
		}
		
		return size;
	}
	
	// Special case for 2048 CD iso
	if (vars->is_cd && vars->num_tracks == 0)
	{
		lba = lba - 0x18;
	}
	
	ufs_read(fd, lba, buf, size);			
	return size;
}
