#ifndef __PS2EMU_IO_H__
#define __PS2EMU_IO_H__

#include <ps2emu/ps2emu.h>

#ifdef PS2NETEMU

typedef struct
{
	uint64_t st_atime;
	uint64_t st_mtime;
	uint64_t st_unktime; // Real less fakeable modtime?
	uint64_t st_ctime;
	uint32_t unk;
	uint32_t unk2;
	uint64_t st_size;
} __attribute__((packed)) ufs_stat;

#else

typedef struct
{
	uint64_t st_atime;
	uint64_t st_mtime;
	uint64_t st_unktime; // Real less fakeable modtime?
	uint64_t st_ctime;
	uint32_t unk;
} __attribute__((packed)) ufs_stat;

#endif

PS2EMU_EXPORT int ufs_open(int unk, char *path);
PS2EMU_EXPORT int ufs_close(int fd);
PS2EMU_EXPORT int ufs_read(int fd, uint64_t offset, void *buf, uint64_t size);
PS2EMU_EXPORT int ufs_write(int fd, uint64_t offset, void *buf, uint64_t size);
PS2EMU_EXPORT int ufs_fstat(int fd, ufs_stat *stat);

#endif /* __PS2EMU_IO_H */

