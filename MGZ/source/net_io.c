// ps3netsrv client used as a file destination ("/net0:/..."). See net_io.h.
// Protocol: webMAN MOD _Projects_/ps3netsrv/include/netiso.h. All values are
// big-endian; they are packed byte by byte so this file also builds and runs
// on a PC (NET_IO_HOST) for testing against a real server.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>

#ifdef NET_IO_HOST
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
static pthread_mutex_t net_mutex = PTHREAD_MUTEX_INITIALIZER;
#define NET_LOCK()   pthread_mutex_lock(&net_mutex)
#define NET_UNLOCK() pthread_mutex_unlock(&net_mutex)
#else
#include <net/net.h>
#include <net/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/mutex.h>
#include <sysmodule/sysmodule.h>
static sys_mutex_t net_mutex;
static int net_mutex_ready = 0;
static void net_lock()
{
	if(!net_mutex_ready) {
		sys_mutex_attr_t attr;
		memset(&attr, 0, sizeof(attr));
		attr.attr_protocol  = SYS_MUTEX_PROTOCOL_FIFO;
		attr.attr_recursive = SYS_MUTEX_ATTR_RECURSIVE;
		attr.attr_pshared   = SYS_MUTEX_ATTR_PSHARED;
		attr.attr_adaptive  = SYS_MUTEX_ATTR_NOT_ADAPTIVE;
		strcpy(attr.name, "net_io");
		if(sysMutexCreate(&net_mutex, &attr) == 0) net_mutex_ready = 1;
	}
	if(net_mutex_ready) sysMutexLock(net_mutex, 0);
}
static void net_unlock()
{
	if(net_mutex_ready) sysMutexUnlock(net_mutex);
}
#define NET_LOCK()   net_lock()
#define NET_UNLOCK() net_unlock()
#endif

#include "net_io.h"

#define NETISO_CMD_OPEN_FILE        0x1224
#define NETISO_CMD_READ_FILE        0x1227
#define NETISO_CMD_CREATE_FILE      0x1228
#define NETISO_CMD_WRITE_FILE       0x1229
#define NETISO_CMD_OPEN_DIR         0x122A
#define NETISO_CMD_DELETE_FILE      0x122C
#define NETISO_CMD_MKDIR            0x122D
#define NETISO_CMD_RMDIR            0x122E
#define NETISO_CMD_STAT_FILE        0x1230
#define NETISO_CMD_READ_DIR         0x1232

// The server refuses requests larger than its 4 MB buffer.
#define NET_IO_CHUNK   (1024*1024)
#define NET_IO_TIMEOUT 30 // seconds
#define NET_IO_MAX_DIR_ENTRIES 4096

static char net_host[64] = {0};
static uint16_t net_port = 38008;
static char net_server_str[80] = {0};
static uint8_t net_enabled = 0;
static uint8_t net_lib_ready = 0;

// shared connection state
static int net_sock = -1;
static net_file_t *ro_owner = NULL; // handle whose file is the server's read file
static net_file_t *wo_owner = NULL; // handle that owns the server's write file

//*******************************************************************************************

static void put16(uint8_t *p, uint16_t v) { p[0] = v >> 8; p[1] = v; }
static void put32(uint8_t *p, uint32_t v) { p[0] = v >> 24; p[1] = v >> 16; p[2] = v >> 8; p[3] = v; }
static void put64(uint8_t *p, uint64_t v) { put32(p, (uint32_t) (v >> 32)); put32(p + 4, (uint32_t) v); }
static uint32_t get32(const uint8_t *p) { return ((uint32_t) p[0] << 24) | ((uint32_t) p[1] << 16) | ((uint32_t) p[2] << 8) | p[3]; }
static uint64_t get64(const uint8_t *p) { return ((uint64_t) get32(p) << 32) | get32(p + 4); }

uint8_t net_io_enabled()
{
	return net_enabled;
}

const char *net_io_server()
{
	return net_server_str;
}

static void net_disconnect();

int net_io_set_server(const char *host, unsigned int port)
{
	if(host == NULL || host[0] == 0 || sizeof(net_host) <= strlen(host)) return 0;
	if(port == 0 || 0xFFFF < port) port = 38008;
	NET_LOCK();
	net_disconnect(); // the next call connects to the new server
	NET_UNLOCK();
	strcpy(net_host, host);
	net_port = (uint16_t) port;
	snprintf(net_server_str, sizeof(net_server_str), "%s:%u", net_host, net_port);
	net_enabled = 1;
	return 1;
}

void net_io_disable()
{
	NET_LOCK();
	net_disconnect();
	NET_UNLOCK();
	net_enabled = 0;
	net_host[0] = 0;
	net_server_str[0] = 0;
}

// "192.168.1.100" or "192.168.1.100:38008"; empty = disable
int net_io_parse_server(const char *str)
{
	char host[64] = {0};
	unsigned int port = 38008;
	while(str && (*str == ' ' || *str == '\t')) str++;
	if(str == NULL || str[0] == 0) {
		net_io_disable();
		return 1;
	}
	if(sscanf(str, "%63[^:\r\n ]:%u", host, &port) < 1 || host[0] == 0) return 0;
	return net_io_set_server(host, port);
}

int net_io_save(const char *config_path)
{
	if(!net_enabled) return remove(config_path) == 0 ? 1 : 0;
	FILE *fp = fopen(config_path, "w");
	if(fp == NULL) return 0;
	fprintf(fp, "# ManaGunZ network destination (ps3netsrv): net0=<ip>[:<port>]\nnet0=%s\n", net_server_str);
	fclose(fp);
	return 1;
}

int net_io_init(const char *config_path)
{
	net_enabled = 0;

	FILE *fp = fopen(config_path, "r"); // newlib stdio: this file does not use the mgz_io macros
	if(fp == NULL) return 0;

	char line[256];
	while(fgets(line, sizeof(line), fp)) {
		char *p = line;
		while(*p == ' ' || *p == '\t') p++;
		if(*p == '#' || *p == ';') continue;
		if(strncmp(p, "net0=", 5) != 0) continue;
		p += 5;

		char host[64] = {0};
		unsigned int port = 38008;
		int n = sscanf(p, "%63[^:\r\n ]:%u", host, &port);
		if(n < 1 || host[0] == 0) continue;

		net_io_set_server(host, port);
		break;
	}
	fclose(fp);

	return net_enabled;
}

uint8_t is_net(const char *path)
{
	if(path == NULL) return 0;
	if(path[0] == '/') path++;
	if(strncmp(path, "net0:", 5) == 0) return 1;
	return 0;
}

// "/net0:/PS3ISO/x.iso" -> "/PS3ISO/x.iso" ("/net0:" -> "/")
static const char *remote_path(const char *path)
{
	if(path[0] == '/') path++;
	path += 5;
	if(path[0] == 0) return "/";
	return path;
}

//*******************************************************************************************
// connection

static void net_lib_init()
{
#ifndef NET_IO_HOST
	if(net_lib_ready) return;
	if(sysModuleIsLoaded(SYSMODULE_NET) != 0) sysModuleLoad(SYSMODULE_NET);
	netInitialize(); // returns an error when it was already initialized elsewhere: fine
#endif
	net_lib_ready = 1;
}

static void net_disconnect()
{
	if(0 <= net_sock) close(net_sock);
	net_sock = -1;
	ro_owner = NULL; // re-opened on the next read
	if(wo_owner) wo_owner->broken = 1; // CREATE would truncate it: the write file is lost
	wo_owner = NULL;
}

static int net_connect_once()
{
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0) return -1;

	struct timeval tv;
	tv.tv_sec = NET_IO_TIMEOUT;
	tv.tv_usec = 0;
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

	int bufsize = 256*1024;
	setsockopt(s, SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof(bufsize));
	setsockopt(s, SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof(bufsize));

	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(net_port);
	sa.sin_addr.s_addr = inet_addr(net_host);

	if(connect(s, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
		close(s);
		return -1;
	}

	return s;
}

// connect when needed (caller holds the lock)
static int net_ensure()
{
	if(!net_enabled) return -1;
	if(0 <= net_sock) return 0;

	net_lib_init();
	int s = net_connect_once();
	if(s < 0) {
		// the http code in main.c (download, upload...) calls netDeinitialize()
		// when it is done: initialize again and retry once
		net_lib_ready = 0;
		net_lib_init();
		s = net_connect_once();
	}
	if(s < 0) return -1;

	net_sock = s;
	ro_owner = NULL;
	wo_owner = NULL;
	return 0;
}

static int send_all(const void *buf, uint32_t size)
{
	const uint8_t *p = (const uint8_t *) buf;
	while(size) {
		int r = send(net_sock, p, size, 0);
		if(r <= 0) return -1;
		p += r;
		size -= r;
	}
	return 0;
}

static int recv_all(void *buf, uint32_t size)
{
	uint8_t *p = (uint8_t *) buf;
	while(size) {
		int r = recv(net_sock, p, size, 0);
		if(r <= 0) return -1;
		p += r;
		size -= r;
	}
	return 0;
}

// 16-byte command: opcode, 16-bit len, then 32-bit num + 64-bit offset
static int send_cmd(uint16_t opcode, uint16_t len16, uint32_t num, uint64_t offset)
{
	uint8_t cmd[16];
	memset(cmd, 0, sizeof(cmd));
	put16(cmd, opcode);
	if(len16) {
		put16(cmd + 2, len16);
	} else {
		put32(cmd + 4, num);
		put64(cmd + 8, offset);
	}
	return send_all(cmd, sizeof(cmd));
}

static int send_path_cmd(uint16_t opcode, const char *rpath)
{
	uint32_t len = strlen(rpath);
	if(len == 0 || 0xFFFF < len) return -1;
	if(send_cmd(opcode, (uint16_t) len, 0, 0) < 0) return -1;
	return send_all(rpath, len);
}

// path command with a 32-bit result; -2 = connection error
static int path_cmd_s32(uint16_t opcode, const char *rpath, int32_t *res)
{
	uint8_t r[4];
	if(send_path_cmd(opcode, rpath) < 0 || recv_all(r, 4) < 0) {
		net_disconnect();
		return -2;
	}
	*res = (int32_t) get32(r);
	return 0;
}

// make f the server's read file (caller holds the lock); -2 = connection error
static int select_ro(net_file_t *f)
{
	if(ro_owner == f) return 0;

	uint8_t r[16];
	if(send_path_cmd(NETISO_CMD_OPEN_FILE, f->path) < 0 || recv_all(r, 16) < 0) {
		net_disconnect();
		return -2;
	}
	int64_t size = (int64_t) get64(r);
	if(size < 0) {
		ro_owner = NULL;
		return -1;
	}
	f->size = size;
	ro_owner = f;
	return 0;
}

//*******************************************************************************************

net_file_t *net_fopen(const char *path, const char *mode)
{
	if(!is_net(path) || mode == NULL) return NULL;

	uint8_t write;
	if(mode[0] == 'r') write = 0; else
	if(mode[0] == 'w') write = 1; else
	return NULL; // 'a': not supported by ps3netsrv
	if(strchr(mode, '+')) return NULL; // read+write: not supported

	const char *rpath = remote_path(path);
	if(sizeof(((net_file_t *)0)->path) <= strlen(rpath)) return NULL;

	net_file_t *f = (net_file_t *) malloc(sizeof(net_file_t));
	if(f == NULL) return NULL;
	memset(f, 0, sizeof(net_file_t));
	strcpy(f->path, rpath);
	f->write = write;

	NET_LOCK();
	int ok = 0;
	int try;
	for(try = 0; try < 2 && !ok; try++) {
		if(net_ensure() < 0) break;

		if(write) {
			if(wo_owner != NULL) break; // one write file at a time
			int32_t res = -1;
			int r = path_cmd_s32(NETISO_CMD_CREATE_FILE, f->path, &res);
			if(r == -2) continue; // connection lost: retry once
			if(res != 0) {
				// the server drops the connection when CREATE fails
				net_disconnect();
				break;
			}
			wo_owner = f;
			ok = 1;
		} else {
			// ps3netsrv drops the connection (and with it a file being written)
			// when OPEN fails, so check that the file exists first
			uint8_t st[33];
			if(send_path_cmd(NETISO_CMD_STAT_FILE, f->path) < 0 || recv_all(st, sizeof(st)) < 0) {
				net_disconnect();
				continue;
			}
			if((int64_t) get64(st) < 0 || st[32]) break; // missing, or a directory
			
			int r = select_ro(f);
			if(r == -2) continue;
			if(r < 0) break;
			ok = 1;
		}
	}
	NET_UNLOCK();

	if(!ok) {
		free(f);
		return NULL;
	}
	return f;
}

int net_fclose(net_file_t *f)
{
	if(f == NULL) return -1;

	NET_LOCK();
	if(ro_owner == f) {
		// close the server's read file
		uint8_t r[16];
		if(0 <= net_sock) {
			if(send_path_cmd(NETISO_CMD_OPEN_FILE, "/CLOSEFILE") < 0 || recv_all(r, 16) < 0) net_disconnect();
		}
		ro_owner = NULL;
	}
	// The server closes its write file on the next CREATE or when the
	// connection ends; every write is already on its disk.
	if(wo_owner == f) wo_owner = NULL;
	NET_UNLOCK();

	int ret = (f->write && f->broken) ? -1 : 0;
	free(f);
	return ret;
}

int64_t net_fread(net_file_t *f, void *buf, uint64_t size)
{
	if(f == NULL || f->write) return 0;

	uint8_t *p = (uint8_t *) buf;
	uint64_t done = 0;
	int retried = 0;

	NET_LOCK();
	while(done < size) {
		uint32_t chunk = (size - done < NET_IO_CHUNK) ? (uint32_t) (size - done) : NET_IO_CHUNK;

		if(net_ensure() < 0) break;
		int r = select_ro(f);
		if(r == -2 && !retried) { retried = 1; continue; }
		if(r < 0) break;

		uint8_t res[4];
		if(send_cmd(NETISO_CMD_READ_FILE, 0, chunk, f->pos) < 0 || recv_all(res, 4) < 0) {
			net_disconnect();
			if(!retried) { retried = 1; continue; }
			break;
		}
		int32_t n = (int32_t) get32(res);
		if(n < 0) break;
		if(n == 0) break; // end of file
		if((uint32_t) n > chunk || recv_all(p + done, n) < 0) {
			net_disconnect();
			break;
		}

		done += n;
		f->pos += n;
		if((uint32_t) n < chunk) break;
	}
	NET_UNLOCK();

	// like stdio fread(): bytes read, 0 on error or end of file
	// (ManaGunZ uses the result as an unsigned byte count, so never -1)
	return (int64_t) done;
}

int64_t net_fwrite(net_file_t *f, const void *buf, uint64_t size)
{
	if(f == NULL || !f->write) return 0;

	const uint8_t *p = (const uint8_t *) buf;
	uint64_t done = 0;

	NET_LOCK();
	while(done < size) {
		if(f->broken || wo_owner != f || net_sock < 0) break;

		uint32_t chunk = (size - done < NET_IO_CHUNK) ? (uint32_t) (size - done) : NET_IO_CHUNK;

		uint8_t res[4];
		if(send_cmd(NETISO_CMD_WRITE_FILE, 0, chunk, 0) < 0
		|| send_all(p + done, chunk) < 0
		|| recv_all(res, 4) < 0) {
			net_disconnect();
			break;
		}
		int32_t n = (int32_t) get32(res);
		if(n > 0) {
			done += n;
			f->pos += n;
		}
		if(n != (int32_t) chunk) break;
	}
	NET_UNLOCK();

	// like stdio fwrite(): bytes written, less than size on error (never -1)
	return (int64_t) done;
}

int64_t net_fseek(net_file_t *f, int64_t offset, int whence)
{
	if(f == NULL) return -1;

	int64_t target;
	if(whence == SEEK_SET) target = offset; else
	if(whence == SEEK_CUR) target = (int64_t) f->pos + offset; else
	if(whence == SEEK_END) target = (f->write ? (int64_t) f->pos : f->size) + offset; else
	return -1;

	if(target < 0) return -1;

	// ps3netsrv writes are sequential
	if(f->write && (uint64_t) target != f->pos) return -1;

	f->pos = (uint64_t) target;
	return target;
}

uint64_t net_ftell(net_file_t *f)
{
	if(f == NULL) return 0;
	return f->pos;
}

//*******************************************************************************************

int net_stat(const char *path, struct stat *st)
{
	if(!is_net(path)) return -1;

	int ret = -1;
	int try;
	NET_LOCK();
	for(try = 0; try < 2; try++) {
		if(net_ensure() < 0) break;

		// file_size(8) mtime(8) ctime(8) atime(8) is_directory(1)
		uint8_t r[33];
		if(send_path_cmd(NETISO_CMD_STAT_FILE, remote_path(path)) < 0 || recv_all(r, sizeof(r)) < 0) {
			net_disconnect();
			continue;
		}
		int64_t size = (int64_t) get64(r);
		if(0 <= size) {
			memset(st, 0, sizeof(struct stat));
			st->st_size  = size;
			st->st_mtime = (time_t) get64(r + 8);
			st->st_ctime = (time_t) get64(r + 16);
			st->st_atime = (time_t) get64(r + 24);
			st->st_mode  = r[32] ? (S_IFDIR | 0777) : (S_IFREG | 0666);
			ret = 0;
		}
		break;
	}
	NET_UNLOCK();
	return ret;
}

static int simple_path_cmd(uint16_t opcode, const char *path)
{
	int32_t res = -1;
	int try;
	NET_LOCK();
	for(try = 0; try < 2; try++) {
		if(net_ensure() < 0) break;
		if(path_cmd_s32(opcode, remote_path(path), &res) == -2) { res = -1; continue; }
		break;
	}
	NET_UNLOCK();
	return res == 0 ? 0 : -1;
}

int net_mkdir(const char *path)
{
	if(!is_net(path)) return -1;
	return simple_path_cmd(NETISO_CMD_MKDIR, path);
}

int net_unlink(const char *path)
{
	if(!is_net(path)) return -1;

	struct stat st;
	if(net_stat(path, &st) != 0) return -1;

	if(S_ISDIR(st.st_mode)) return simple_path_cmd(NETISO_CMD_RMDIR, path);

	return simple_path_cmd(NETISO_CMD_DELETE_FILE, path);
}

//*******************************************************************************************

// The whole listing is read when the directory is opened (OPEN_DIR + READ_DIR),
// so several directories can be open at once (e.g. a recursive delete).
net_dir_t *net_opendir(const char *path)
{
	if(!is_net(path)) return NULL;

	net_dir_t *d = (net_dir_t *) malloc(sizeof(net_dir_t));
	if(d == NULL) return NULL;
	memset(d, 0, sizeof(net_dir_t));

	int ok = 0;
	int try;
	NET_LOCK();
	for(try = 0; try < 2 && !ok; try++) {
		if(net_ensure() < 0) break;

		int32_t res = -1;
		int r = path_cmd_s32(NETISO_CMD_OPEN_DIR, remote_path(path), &res);
		if(r == -2) continue;
		if(res != 0) break;

		uint8_t hdr[8];
		if(send_cmd(NETISO_CMD_READ_DIR, 0, 0, 0) < 0 || recv_all(hdr, 8) < 0) {
			net_disconnect();
			continue;
		}
		int64_t count = (int64_t) get64(hdr);
		if(count < 0) break;

		// file_size(8) mtime(8) is_directory(1) name(512)
		const uint32_t esize = 8 + 8 + 1 + 512;
		uint8_t *e = (uint8_t *) malloc(esize);
		if(e == NULL) { net_disconnect(); break; }

		int keep = count < NET_IO_MAX_DIR_ENTRIES ? (int) count : NET_IO_MAX_DIR_ENTRIES;
		d->entries = keep ? (net_dirent_t *) malloc(sizeof(net_dirent_t) * keep) : NULL;
		if(keep && d->entries == NULL) { free(e); net_disconnect(); break; }

		int64_t i;
		int fail = 0;
		d->count = 0;
		for(i = 0; i < count; i++) {
			if(recv_all(e, esize) < 0) { fail = 1; break; }
			if(d->count >= keep) continue;
			e[esize - 1] = 0;
			const char *name = (const char *) (e + 17);
			if(!strcmp(name, ".") || !strcmp(name, "..") || name[0] == 0) continue;
			net_dirent_t *de = &d->entries[d->count++];
			strncpy(de->name, name, sizeof(de->name) - 1);
			de->name[sizeof(de->name) - 1] = 0;
			de->size = get64(e);
			de->is_dir = e[16] ? 1 : 0;
		}
		free(e);
		if(fail) {
			net_disconnect();
			free(d->entries);
			d->entries = NULL;
			d->count = 0;
			continue;
		}
		ok = 1;
	}
	NET_UNLOCK();

	if(!ok) {
		free(d->entries);
		free(d);
		return NULL;
	}
	return d;
}

int net_readdir(net_dir_t *d, char *name, int name_size, uint8_t *is_dir, uint64_t *size)
{
	if(d == NULL || d->count <= d->next) return -1;

	net_dirent_t *de = &d->entries[d->next++];
	if(name && name_size > 0) {
		strncpy(name, de->name, name_size - 1);
		name[name_size - 1] = 0;
	}
	if(is_dir) *is_dir = de->is_dir;
	if(size) *size = de->size;
	return 0;
}

int net_closedir(net_dir_t *d)
{
	if(d == NULL) return -1;
	free(d->entries);
	free(d);
	return 0;
}
