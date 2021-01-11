#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ff.h"
#include "fflib.h"
#include "exFAT.h"

#define FREE(x) if(x!=NULL) {free(x);x=NULL;}

void exFAT_init()
{
	fflib_init();
	
	int i;
	fso = (FATFS **) malloc(MAXFDS * sizeof(FATFS*));
	for(i=0; i < MAXFDS; i++) fso[i] = (FATFS *) malloc(sizeof(FATFS));
	
	for(i=0; i < 128; i++) {
		fflib_attach(DEVICE_USB_MASS_STORAGE(i), USB_MASS_STORAGE(i), NO);
	}
	fflib_attach(DEVICE_MEMORY_STICK, MEMORY_STICK, NO);
	fflib_attach(DEVICE_COMPACT_FLASH, COMPACT_FLASH, NO);
	fflib_attach(DEVICE_SD_CARD, SD_CARD, NO);
	
}

void exFAT_deinit()
{
	int i;
	for(i=0; i < MAXFDS; i++) fflib_detach(i);
	for(i=0; i < MAXFDS; i++) FREE(fso[i]);
	FREE(fso);
}

u8 exFAT_is_mounted(u32 idx)
{
	if(0 < fflib_fd_get(idx)) return YES;
	
	return NO;
}

u32 exFAT_mount(u32 idx)
{
	char drv[7];
	snprintf (drv, 7, "%d:/", idx);
	return f_mount(fso[idx], drv, 1);
}

u32 exFAT_unmount(u32 idx)
{
	fflib_fd_set(idx, -1);
	fflib_ss_set(idx, -1);
	
	char drv[7];
	snprintf (drv, 7, "%d:/", idx);
	return f_unmount(drv);
}

void exFAT_unmount_all()
{
	int i;
	for(i=0; i < MAXFDS; i++) exFAT_unmount(i);
}

void exFAT_mount_all()
{
	int i;

	//check
	if(fso==NULL) exFAT_init();
	
	for(i=0; i < MAXFDS; i++) {
		if( exFAT_mount(i) == FR_OK ) {
			//ignore FAT32/FAT16
			if(fso[i]->fs_type != FS_EXFAT)	exFAT_unmount(i);
		} else {
			// unplugged ?
			if(exFAT_is_mounted(i))	exFAT_unmount(i);
		}
	}
}

u8 is_exFAT(char *path)
{
	u8 n=0;
	if( path[0] == '/') n=1;
	if( strncmp(&path[n], "exFAT", 5) == 0 ) return YES;

	return NO;
}

int exFAT_get_idx(char *path)
{
	if( is_exFAT(path) == NO) return -1;
	
	int o;
	sscanf(path, "%*[^0123456789]%d", &o);  
    return o;
}

u64 exFAT_get_device_id(char *path)
{
	int idx = exFAT_get_idx(path);
	
	return fflib_id_get(idx);
}

void exFAT_get_size(char *path, u64 *freesize, u64 *totalsize)
{
	*freesize = 0;
	*totalsize = 0;
	
	int idx = exFAT_get_idx(path);
	
	if( exFAT_is_mounted(idx) == NO ) return;
	
    u32 fre_clust, fre_sect, tot_sect;
	
    /* Get volume information and free clusters of drive 1 */
    int res = f_getfree(path, &fre_clust, &fso[idx]);
    if (res) return;

    /* Get total sectors and free sectors */
    tot_sect = (fso[idx]->n_fatent - 2) * fso[idx]->csize;
    fre_sect = fre_clust * fso[idx]->csize;
	
	int ss = fflib_ss_get(idx);
	
	*freesize = tot_sect * ss;
	*totalsize = fre_sect * ss;
}

void exFAT_get_label(char *path, char *label)
{
	f_getlabel(path, label, 0);
}

void exFAT_set_label(char *path, char *label)
{
	int idx = exFAT_get_idx(path);
	char drv[255];   
	sprintf(drv, "%d:%s", idx, label);
	
	f_setlabel(drv);
}
