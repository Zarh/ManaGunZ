#ifndef __STORAGE_H__
#define __STORAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <ppu-lv2.h>
#include <lv2/syscalls.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "scsi.h"
#include "storage.h"
#include "syscall8.h"

#define MAX_PATH		0x420

#define ATA_HDD			0x101000000000007ULL
#define BDVD_DRIVE		0x101000000000006ULL
#define PATA0_HDD_DRIVE		0x101000000000008ULL
#define PATA0_BDVD_DRIVE	BDVD_DRIVE
#define PATA1_HDD_DRIVE		ATA_HDD
#define PATA1_BDVD_DRIVE	0x101000000000009ULL
#define BUILTIN_FLASH		0x100000000000001ULL
#define MEMORY_STICK		0x103000000000010ULL
#define SD_CARD			0x103000100000010ULL
#define COMPACT_FLASH		0x103000200000010ULL

#define USB_MASS_STORAGE_1(n)	(0x10300000000000AULL+n) /* For 0-5 */
#define USB_MASS_STORAGE_2(n)	(0x10300000000001FULL+(n-6)) /* For 6-127 */

#define	HDD_PARTITION(n)	(ATA_HDD | ((uint64_t)n<<32))
#define FLASH_PARTITION(n)	(BUILTIN_FLASH | ((uint64_t)n<<32))

#define DEVICE_TYPE_PS3_DVD	0xFF70
#define DEVICE_TYPE_PS3_BD	0xFF71
#define DEVICE_TYPE_PS2_CD	0xFF60
#define DEVICE_TYPE_PS2_DVD	0xFF61
#define DEVICE_TYPE_PSX_CD	0xFF50
#define DEVICE_TYPE_BDROM	0x40
#define DEVICE_TYPE_BDMR_SR	0x41 /* Sequential record */
#define DEVICE_TYPE_BDMR_RR 	0x42 /* Random record */
#define DEVICE_TYPE_BDMRE	0x43
#define DEVICE_TYPE_DVD		0x10 /* DVD-ROM, DVD+-R, DVD+-RW etc, they are differenced by booktype field in some scsi command */
#define DEVICE_TYPE_CD		0x08 /* CD-ROM, CD-DA, CD-R, CD-RW, etc, they are differenced somehow with scsi commands */

#define STORAGE_COMMAND_NATIVE		0x01
#define STORAGE_COMMAND_GET_DEVICE_SIZE	0x10
#define STORAGE_COMMAND_GET_DEVICE_TYPE	0x11

typedef uint32_t sys_device_handle_t;

typedef struct
{
	char label[32]; 
	uint32_t unk_08; 
	uint32_t unk_0C; 
	uint64_t sector_count; 
	uint32_t sector_size; 
	uint32_t unk_30; 
	uint8_t unk_40[8]; 
	
} __attribute__((packed)) sys_device_info_t;

typedef struct
{
	uint32_t inlen;
	uint32_t unk1; 
	uint32_t outlen;
	uint32_t unk2;
	uint32_t unk3;
} __attribute__((packed)) StorageCmdScsiData;

int sys_storage_get_device_info(uint64_t device_id, sys_device_info_t *device_info);


LV2_SYSCALL sys_storage_open(uint64_t device_id, uint64_t unk, sys_device_handle_t *device_handle, uint64_t unk2)
{
	lv2syscall4(SYSCALL_STORAGE_OPEN, device_id, unk, (uint64_t)device_handle, unk2);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_close(sys_device_handle_t device_handle)
{
	lv2syscall1(SYSCALL_STORAGE_CLOSE, device_handle);
	return_to_user_prog(s32);
}

int sys_storage_read(sys_device_handle_t device_handle, uint64_t unk, uint64_t start_sector, uint32_t sector_count, void *buf, uint32_t *nread, uint64_t unk2);

LV2_SYSCALL sys_storage_send_device_command(sys_device_handle_t device_handle, unsigned int command, void *indata, uint64_t inlen, void *outdata, uint64_t outlen)
{
	lv2syscall6(SYSCALL_STORAGE_SEND_DEVICE_COMMAND, device_handle, command, (uint64_t)indata, inlen, (uint64_t)outdata, outlen);
	return_to_user_prog(s32);
}

int sys_storage_execute_device_command(sys_device_handle_t device_handle, unsigned int command, void *indata, uint64_t inlen, void *outdata, uint64_t outlen, uint64_t *ret);

/* Payloaed storage extensions */

typedef struct
{
	int size;
	int disc_emulation;
	char firstfile_path[MAX_PATH];	
} __attribute__((packed)) sys_emu_state_t;

LV2_SYSCALL sys_storage_ext_get_disc_type(unsigned int *real_disctype, unsigned int *effective_disctype, unsigned int *fake_disctype)
{
	lv2syscall4(8, SYSCALL8_OPCODE_GET_DISC_TYPE, (uint64_t)real_disctype, (uint64_t)effective_disctype, (uint64_t)fake_disctype);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_read_ps3_disc(void *buf, uint64_t start_sector, uint32_t count)
{
	lv2syscall4(8, SYSCALL8_OPCODE_READ_PS3_DISC, (uint64_t)buf, start_sector, count);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_fake_storage_event(uint64_t event, uint64_t param, uint64_t device)
{
	lv2syscall4(8, SYSCALL8_OPCODE_FAKE_STORAGE_EVENT, event, param, device);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_get_emu_state(sys_emu_state_t *state)
{
	lv2syscall2(8, SYSCALL8_OPCODE_GET_EMU_STATE, (uint64_t)state);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_mount_ps3_discfile(unsigned int filescount, uint32_t *files)
{
	lv2syscall3(8, SYSCALL8_OPCODE_MOUNT_PS3_DISCFILE, filescount, (uint64_t)files);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_mount_dvd_discfile(unsigned int filescount, uint32_t *files)
{
	lv2syscall3(8, SYSCALL8_OPCODE_MOUNT_DVD_DISCFILE, filescount, (uint64_t)files);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_mount_bd_discfile(unsigned int filescount, uint32_t *files)
{
	lv2syscall3(8, SYSCALL8_OPCODE_MOUNT_BD_DISCFILE, filescount, (uint64_t)files);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_mount_psx_discfile(char *file, unsigned int trackscount, ScsiTrackDescriptor *tracks)
{
	lv2syscall4(8, SYSCALL8_OPCODE_MOUNT_PSX_DISCFILE, (uint64_t)file, trackscount, (uint64_t)tracks);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_mount_ps2_discfile(unsigned int filescount, uint32_t *files, unsigned int trackscount, ScsiTrackDescriptor *tracks)
{
	lv2syscall5(8, SYSCALL8_OPCODE_MOUNT_PS2_DISCFILE, filescount, (uint64_t)files, trackscount, (uint64_t)tracks);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_umount_discfile(void)
{
	lv2syscall1(8, SYSCALL8_OPCODE_UMOUNT_DISCFILE);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_storage_ext_mount_encrypted_image(char *image, char *mount_point, char *filesystem, uint64_t nonce)
{
	lv2syscall5(8, SYSCALL8_OPCODE_MOUNT_ENCRYPTED_IMAGE, (uint64_t)image, (uint64_t)mount_point, (uint64_t)filesystem, nonce);
	return_to_user_prog(s32);
}

// Not really storage funcs, but...
LV2_SYSCALL sys_ss_disc_auth(uint64_t func, uint64_t param)
{
	lv2syscall2(864, func, param);
	return_to_user_prog(s32);
}

typedef struct
{
	char mount_point[32];
	char filesystem[32];
	char block_dev[32];
	uint8_t unk[52];
} __attribute__((packed)) CellFsMountInfo;

int cellFsUtilMount(const char *block_dev, const char *filesystem, const char *mount_point, int unk, int read_only, int unk2, char *argv[], int argc);
int cellFsUtilUmount(const char *mount_point, uint64_t unk, int force);

LV2_SYSCALL cellFsUtilGetMountInfo(CellFsMountInfo *info, uint64_t size, uint64_t *rsize)
{
	lv2syscall3(842, (uint64_t)info, size, (uint64_t)rsize);
	return_to_user_prog(s32);
}

LV2_SYSCALL cellFsUtilGetMountInfoSize(uint64_t *size)
{
	lv2syscall1(841, (uint64_t)size);
	return_to_user_prog(s32);
}

int cellFsUtilGetSpaceInfo(const char *mount_point, uint64_t *total_size, uint64_t *free_size);

static inline uint64_t get_device(char *name) __attribute__((unused));

static inline uint64_t get_device(char *name)
{
	if (strcmp(name, "CELL_FS_IOS:ATA_HDD") == 0)
		return ATA_HDD;
	
	if (strcmp(name, "CELL_FS_IOS:BDVD_DRIVE") == 0)
		return BDVD_DRIVE;
	
	if (strcmp(name, "CELL_FS_IOS:PATA0_HDD_DRIVE") == 0)
		return PATA0_HDD_DRIVE;
	
	if (strcmp(name, "CELL_FS_IOS:PATA0_BDVD_DRIVE") == 0)
		return PATA0_BDVD_DRIVE;
	
	if (strcmp(name, "CELL_FS_IOS:PATA1_HDD_DRIVE") == 0)
		return PATA1_HDD_DRIVE;
	
	if (strcmp(name, "CELL_FS_IOS:PATA1_BDVD_DRIVE") == 0)
		return PATA1_BDVD_DRIVE;
	
	if (strcmp(name, "CELL_FS_IOS:BUILTIN_FLASH") == 0)
		return BUILTIN_FLASH;
	
	if (strcmp(name, "CELL_FS_IOS:COMPACT_FLASH") == 0)
		return COMPACT_FLASH;
	
	if (strcmp(name, "CELL_FS_IOS:MEMORY_STICK") == 0)
		return MEMORY_STICK;
	
	if (strcmp(name, "CELL_FS_IOS:SD_CARD") == 0)
		return SD_CARD;
	
	if (strncmp(name, "CELL_FS_IOS:USB_MASS_STORAGE", 28) == 0)
	{
		if (!isdigit(name[28]) || !isdigit(name[29]) || !isdigit(name[30]) || name[31] != 0)
			return 0;
		
		unsigned int num = ((name[28]-'0')*100) + ((name[29]-'0')*10) + (name[30]-'0');
		
		if (num > 127)
			return 0;
		
		if (num < 6)
			return USB_MASS_STORAGE_1(num);
		
		return USB_MASS_STORAGE_2(num);
	}
	
	if (strcmp(name, "CELL_FS_IOS:BUILTIN_FLSH1") == 0)
		return FLASH_PARTITION(2);
	
	if (strcmp(name, "CELL_FS_IOS:BUILTIN_FLSH2") == 0)
		return FLASH_PARTITION(3);
	
	if (strcmp(name, "CELL_FS_IOS:BUILTIN_FLSH3") == 0)
		return FLASH_PARTITION(4);
	
	if (strcmp(name, "CELL_FS_IOS:BUILTIN_FLSH4") == 0)
		return FLASH_PARTITION(5);
	
	if (strcmp(name, "CELL_FS_UTILITY:HDD0") == 0)
		return HDD_PARTITION(1);
	
	if (strcmp(name, "CELL_FS_UTILITY:HDD1") == 0)
		return HDD_PARTITION(2);
	
	if (strcmp(name, "CELL_FS_UTILITY:HDD2") == 0)
		return HDD_PARTITION(3);
	
	if (strcmp(name, "CELL_FS_UTILITY:HDD") == 0)
		return ATA_HDD;	
	
	return 0;
}

LV2_SYSCALL sys_map_path(char *oldpath, char *newpath)
{
	lv2syscall2(35, (uint64_t)oldpath, (uint64_t)newpath);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_map_paths(char *paths[], char *new_paths[], unsigned int num)
{
	lv2syscall4(8, SYSCALL8_OPCODE_MAP_PATHS, (uint64_t)paths, (uint64_t)new_paths, num);
	return_to_user_prog(s32);
}


#ifdef __cplusplus
}
#endif

#endif /* __STORAGE_H__ */

