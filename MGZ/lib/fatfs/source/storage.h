/**
 * SACD Ripper - http://code.google.com/p/sacd-ripper/
 *
 * Copyright (c) 2010-2011 by respective authors.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef __SYS_STORAGE_H__
#define __SYS_STORAGE_H__

#include <stdint.h>
#include <string.h>
#include <ppu-lv2.h>
#include <sys/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    char   Label[0x28];
	u64    sector_count;
    u32    sector_size;
    u32    unknown;
    u8     writable;
    u8     unknowns[7];
} __attribute__((packed)) device_info_t;

static inline s32 sys_storage_open(u64 device_ID, int* fd)
{
	lv2syscall4( 600, device_ID, 0, (u64)fd, 0 );
	return_to_user_prog(s32);
}

static inline s32 sys_storage_close(int fd)
{
	lv2syscall1( 601, fd );
	return_to_user_prog(s32);
}

static inline s32 sys_storage_read(int fd, u64 start_sector, u64 nb_sector, const void* buffer, u32 *sectors_read, u64 flags )
{
	lv2syscall7( 602, fd, 0, start_sector, nb_sector, (u64)buffer, (u64)sectors_read, flags );
	return_to_user_prog(s32);
}

static inline s32 sys_storage_write(int fd, u64 start_sector, u64 nb_sector, const void* buffer, u32 *sectors_wrote, u64 flags )
{
	lv2syscall7( 603, fd, 0, start_sector, nb_sector, (u64)buffer, (u64)sectors_wrote, flags );
	return_to_user_prog(s32);
}

static inline s32 sys_storage_get_device_info(u64 device_id, device_info_t *device_info)
{
	lv2syscall2( 609, device_id, (u64)device_info );
	return_to_user_prog(s32);
}

#ifdef __cplusplus
};
#endif
#endif /* _SYS_STORAGE_H__ */