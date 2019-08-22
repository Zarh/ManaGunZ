#include <ps2emu/ps2emu.h>
#include <ps2emu/libc.h>
#include <ps2emu/io.h>
#include <ps2emu/cdvd.h>
#include <ps2emu/memory.h>
#include <ps2emu/patch.h>
#include <ps2emu/symbols.h>

#include "common.h"

typedef struct
{
	uint32_t address;
	uint32_t data;
	uint8_t *condition;
} Patch;

static uint8_t condition_true = 1;
static uint8_t condition_iso = 0;
static uint8_t condition_optical = 0;
static uint8_t condition_ps2_cdda = 0;

static Patch patches[] =
{
	{ ps2_disc_auth_caller_symbol,   LI(3, 0), &condition_true },
	{ ps2_disc_auth_caller_symbol+4, BLR, &condition_true },
	{ DISC_TYPE_OFFSET,	LI(25, 0x13), &condition_ps2_cdda }, /* hack for ps2 cdda, SCECdPS2CD -> SCECdPS2CDDA */
};

#define N_PATCHES	(sizeof(patches) / sizeof(Patch))

static INLINE void *get_data_buffer(void)
{
	uint64_t *p = (uint64_t *) *(uint64_t *)(TOC+DATA_TOC_OFFSET);
	return  (void *) p[DATA_SUBTOC_OFFSET/8];	
}

static INLINE uint8_t *get_buffer_from_lpar(uint64_t lpar)
{
	uint64_t *p = (uint64_t *) *(uint64_t *)(TOC+DATA_TOC_OFFSET);
	uint64_t lpar1 = p[LPAR_SUBTOC_OFFSET/8];
	uint64_t lpar2 = lpar1+0x1000;
	uint64_t lpar3 = lpar1+0x400;
	uint64_t lpar4 = lpar1+0x10000;
	
	uint8_t *out1 = get_data_buffer();
	uint8_t *out2 = out1+0x1000;
	uint8_t *out3 = out1+0x400;
	uint8_t *out4 = out1+0x10000;
	
	if (lpar == lpar1)
	{
		return out1;
	}
	else if (lpar == lpar2)
	{
		return out2;
	}
	else if (lpar == lpar3)
	{
		return out3;
	}
	else if (lpar == lpar4)
	{
		return out4;
	}
	else if (lpar == 0)
	{
		return NULL; // Buffer not needed
	}
	
	DPRINTF("Warning: cannot find buffer for lpar: 0x%lx, using default logic (lpar1=0x%lx)!!!\n", lpar, lpar1);
	dump_stack_trace2(16);
	return (lpar-lpar1)+out1;
}

static INLINE uint64_t get_file_size(int fd)
{
	uint64_t *structure = (uint64_t *) ((0x1270*fd) + *(uint64_t *)(TOC+FILESZ_TOC_OFFSET));
	return structure[0x178/8];
}

#include "common.c"

PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_8(int, emu_cdvd_send_atapi_command, (uint8_t *cmd, uint64_t unk, uint64_t outlpar, uint32_t outlen, uint32_t outnum, uint32_t unk2, uint32_t unk3, uint64_t nretries))
{
	int ret = DO_POSTCALL;
	uint8_t *out = get_buffer_from_lpar(outlpar);
	
	/*if (!out)
		return ret;*/
	
	int tri = process_scsi_cmd_iso(cmd, out, outlen);
	
	if (tri < 0)
	{
		ret = tri;
	}
	else if (tri > 0)
	{
		ret = 0;
	}
	
	return ret;	
}

static f_desc_t orig_send_atapi_command;

PS2EMU_HOOKED_FUNCTION(int, optical_cdvd_send_atapi_command, (uint8_t *cmd, uint64_t unk, uint64_t outlpar, uint32_t outlen, uint32_t outnum, uint32_t unk2, uint32_t unk3, uint64_t nretries))
{
	ScsiRead2064 read2064;
	uint8_t *out = get_buffer_from_lpar(outlpar);
	int is_2064 = (cmd[0] == SCSI_CMD_READ_2064);
	
	/*if (!out)
		return 0;*/
	//DPRINTF("%s\n", get_scsi_cmd_name(cmd[0]));
	
	if (is_2064 && device_type == DEVICE_TYPE_DVD)
	{
		ScsiRead10 *read10 = (ScsiRead10 *)cmd;
		
		memcpy(&read2064, cmd, sizeof(ScsiRead2064));		
		memset(read10, 0, sizeof(ScsiRead10));
		
		read10->opcode = SCSI_CMD_READ_10;
		read10->lba = read2064.lba;
		read10->length = read2064.length;
		read10->control = read2064.control;
	}
	
	void (* func)() = (void *)&orig_send_atapi_command;	
	func(cmd, unk, outlpar, outlen, outnum, unk2, unk3, nretries);
	
	if (is_2064 && device_type == DEVICE_TYPE_DVD)
	{
		memcpy(cmd, &read2064, sizeof(ScsiRead2064));
	}
	
	return post_process_scsi_cmd_optical(cmd, out, outlen);	
}

static INLINE void apply_patches(void)
{
	if (condition_iso)
	{
		hook_function_with_cond_postcall(cdvd_send_atapi_command_symbol, emu_cdvd_send_atapi_command, 8);
		uint32_t *inst = (uint32_t *)DISC_SIZE_OFFSET;
		
		inst[0] = LI(10, 0);
		inst[1] = ORIS(10, 10, iso_size_sectors>>16);
		inst[2] = ORI(10, 10, iso_size_sectors&0xFFFF);
		clear_icache(inst, 12);	
		
		if (device_type == DEVICE_TYPE_PS2_CD && num_tracks > 1)
		{
			for (int i = 1; i < num_tracks; i++)
			{
				if (tracks[i].adr_control == 0x10)
				{
					condition_ps2_cdda = 1;
					break;
				}
			}
		}
	}
	else if (condition_optical)
	{
		hook_function(cdvd_send_atapi_command_symbol, optical_cdvd_send_atapi_command, &orig_send_atapi_command);
	}
	
	for (int i = 0; i < N_PATCHES; i++)
	{
		if (*patches[i].condition)
		{		
			uint32_t *addr= (uint32_t *)(uint64_t)patches[i].address;
			*addr = patches[i].data;
			clear_icache(addr, 4);			
		}		
	}	
}

// 0x02200000

int main(void)
{
#ifdef DEBUG
	debug_init();
	debug_install();
	DPRINTF("Hello from ps2hwemu_stage2.\n");	
#endif
	int ret = setup_iso();
	if (ret == -2)
	{
		condition_optical = 1;
	}
	else if (ret == 0)
	{
		condition_iso = 1;
	}
	
	apply_patches();	
	
#ifdef DEBUG
	//apply_debug_patches();
#endif	
	
	return 0;
}
