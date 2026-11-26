#ifndef _NET_IO_H_
#define _NET_IO_H_

// Network destination for ManaGunZ: files on a ps3netsrv server (the same
// server webMAN MOD uses for /net0), so dumps can be written straight to a PC.
//
// Paths look like "/net0:/PS3ISO/BLUS12345.iso" (the leading '/' is optional);
// everything after "net0:" is the path on the server, relative to its root.
//
// The server is configured in <ManaGunZ>/USRDIR/setting/net.txt, one line per
// server: "net0=192.168.1.100:38008" (only net0 is used for now). Without that
// file the network device does not exist.
//
// ps3netsrv accepts only ONE connection per client IP (a new connection from
// the same IP closes the previous one), and each connection has one read-only
// file, one write-only file and one directory. So net_io uses a single shared
// connection:
//  - any number of files can be open for reading: reads carry their offset, and
//    the server's read file is switched (re-opened) when another handle reads;
//  - one file at a time can be open for writing (writes are sequential, no seek);
//  - directories are listed completely when opened (OPEN_DIR + READ_DIR).
// webMAN's own /net0 connection from the PS3 is closed by the server while
// ManaGunZ uses net0 (and the other way around).
// Not supported: "r+"/"a" modes, seeking a file opened for writing, rename,
// truncate, free space (reported as unknown/large).

#include <stdint.h>
#include <sys/stat.h>

typedef struct {
	char     path[1024];     // path on the server
	uint8_t  write;          // 1 = write-only (CREATE), 0 = read-only (OPEN)
	uint8_t  broken;         // write file lost (connection dropped)
	uint64_t pos;            // current position
	int64_t  size;           // file size when opened for reading
} net_file_t;

typedef struct {
	char     name[512];
	uint8_t  is_dir;
	uint64_t size;
} net_dirent_t;

typedef struct {
	net_dirent_t *entries;
	int      count;
	int      next;
} net_dir_t;

int  net_io_init(const char *config_path);   // returns number of configured devices
int  net_io_set_server(const char *host, unsigned int port); // used by net_io_init (and tests)
uint8_t net_io_enabled();
uint8_t is_net(const char *path);
const char *net_io_server(); // "ip:port" of net0, for display

net_file_t *net_fopen(const char *path, const char *mode);
int     net_fclose(net_file_t *f);
int64_t net_fread(net_file_t *f, void *buf, uint64_t size);
int64_t net_fwrite(net_file_t *f, const void *buf, uint64_t size);
int64_t net_fseek(net_file_t *f, int64_t offset, int whence);
uint64_t net_ftell(net_file_t *f);

int    net_stat(const char *path, struct stat *st);
int    net_mkdir(const char *path);
int    net_unlink(const char *path);  // file, or empty directory

net_dir_t *net_opendir(const char *path);
int    net_readdir(net_dir_t *d, char *name, int name_size, uint8_t *is_dir, uint64_t *size); // 0 = entry, -1 = end
int    net_closedir(net_dir_t *d);

#endif
