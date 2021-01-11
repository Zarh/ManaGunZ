#ifndef _EXFAT_H_
#define _EXFAT_H_

#include <ppu-types.h>

#include "ff.h"
#include "fflib.h"

#define YES 1
#define NO  0

#define MEMORY_STICK			0x103000000000010ULL
#define SD_CARD					0x103000100000010ULL
#define COMPACT_FLASH			0x103000200000010ULL

#define USB_MASS_STORAGE_1(n)	(0x10300000000000AULL+(n)) // For 0-5 
#define USB_MASS_STORAGE_2(n)	(0x10300000000001FULL+((n)-6)) // For 6-127
#define USB_MASS_STORAGE(n)		(((n) < 6) ? USB_MASS_STORAGE_1(n) : USB_MASS_STORAGE_2(n))

#define DEVICE_USB_MASS_STORAGE(x) 			x
#define DEVICE_MEMORY_STICK					128
#define DEVICE_COMPACT_FLASH				129
#define DEVICE_SD_CARD						130

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ff.h"
#include "fflib.h"
#include "exFAT.h"

FATFS** fso; // -> FATFS* FatFs[FF_VOLUMES]; from ff.c

#define FREE(x) if(x!=NULL) {free(x);x=NULL;}

void exFAT_init();
void exFAT_deinit();
u8 exFAT_is_mounted(u32 idx);
u32 exFAT_mount(u32 idx);
u32 exFAT_unmount(u32 idx);
void exFAT_unmount_all();
void exFAT_mount_all();
u8 is_exFAT(char *path);
int exFAT_get_idx(char *path);
u64 exFAT_get_device_id(char *path);
void exFAT_get_size(char *path, u64 *freesize, u64 *totalsize);
void exFAT_get_label(char *path, char *label);
void exFAT_set_label(char *path, char *label);


#endif
