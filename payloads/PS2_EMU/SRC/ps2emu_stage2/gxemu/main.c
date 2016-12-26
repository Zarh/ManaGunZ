#include <ps2emu/ps2emu.h>
#include <ps2emu/libc.h>
#include <ps2emu/io.h>
#include <ps2emu/cdvd.h>
#include <ps2emu/memory.h>
#include <ps2emu/vuart.h>
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

static Patch patches[] =
{
	{ ps2_disc_auth_caller_symbol,   LI(3, 0), &condition_true },
	{ ps2_disc_auth_caller_symbol+4, BLR, &condition_true },
};

#define N_PATCHES	(sizeof(patches) / sizeof(Patch))

static INLINE void *get_data_buffer(void)
{
	return (void *) *(uint64_t *)(*(uint64_t *)((TOC+DATA_TOC_OFFSET)));
}

static INLINE uint8_t *get_buffer_from_lpar(uint64_t lpar)
{
	uint64_t lpar1 = *(uint64_t *)(*(uint64_t *)((TOC+LPAR_TOC_OFFSET)));
	uint64_t lpar2 = lpar1+0x1000;
	uint64_t lpar3 = lpar1+0x400;
	
	uint8_t *out1 = get_data_buffer();
	uint8_t *out2 = out1+0x1000;
	uint8_t *out3 = out1+0x400;
	
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
	
	DPRINTF("Warning: cannot find buffer for lpar: 0x%lx, using default logic!!!\n", lpar);
	dump_stack_trace2(16);
	return (lpar-lpar1)+out1;
}

static INLINE uint64_t get_file_size(int fd)
{
	uint64_t *structure = (uint64_t *) ((0x1270*fd) + *(uint64_t *)(TOC+FILESZ_TOC_OFFSET));
	return structure[0x178/8];
}

#include "common.c"

PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_3(int, emu_cdvd_send_atapi_command, (uint8_t *cmd, uint64_t outlpar, uint64_t outlen))
{
	int ret = DO_POSTCALL;
	uint8_t *out = get_buffer_from_lpar(outlpar);
	
	if (!out)
		return ret;
	
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

PS2EMU_HOOKED_FUNCTION_COND_POSTCALL_1(int, emu_cdvd_send_device_command, (uint64_t cmd))
{
	if (cmd != STORAGE_COMMAND_GET_DEVICE_SIZE)
	{
		DPRINTF("Unexpected command: %lx\n", cmd);
		dump_stack_trace2(16);
		return DO_POSTCALL;
	}
	
	uint32_t *psize = get_data_buffer();	
	*psize = iso_size_sectors-1;
	return 0;
}

static f_desc_t orig_send_atapi_command;

PS2EMU_HOOKED_FUNCTION(int, optical_cdvd_send_atapi_command, (uint8_t *cmd, uint64_t outlpar, uint64_t outlen))
{
	ScsiRead2064 read2064;
	uint8_t *out = get_buffer_from_lpar(outlpar);
	int is_2064 = (cmd[0] == SCSI_CMD_READ_2064);
	
	if (!out)
		return 0;
	
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
	func(cmd, outlpar, outlen);
	
	if (is_2064 && device_type == DEVICE_TYPE_DVD)
	{
		memcpy(cmd, &read2064, sizeof(ScsiRead2064));
	}
	
	return post_process_scsi_cmd_optical(cmd, out, outlen);	
}

#ifdef DEBUG

PS2EMU_HOOKED_FUNCTION_POSTCALL_4(void, ps2_disc_auth_hook, (uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6))
{
	DPRINTF("\n---------- ps2_disc_auth %lx %lx %lx %lx\n", r3, r4, r5, r6);
}

static INLINE void apply_debug_patches(void)
{			
	hook_function_with_postcall(ps2_disc_auth_symbol, ps2_disc_auth_hook, 4);
	//hook_function_with_precall(cdvd_send_atapi_command_symbol, hook_cdvd_send_atapi_command, 3);	
}

#endif

static INLINE void apply_patches(void)
{
	if (condition_iso)
	{
		hook_function_with_cond_postcall(cdvd_send_atapi_command_symbol, emu_cdvd_send_atapi_command, 3);
		hook_function_with_cond_postcall(cdvd_send_device_command_symbol, emu_cdvd_send_device_command, 1);			
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

int main(void)
{
#ifdef DEBUG
	debug_init();
	DPRINTF("Hello from ps2gxemu_stage2..\n");	
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
	apply_debug_patches();
#endif	

	return 0;
}
