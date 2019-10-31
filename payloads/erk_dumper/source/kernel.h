#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "common.h"
#include "symbols.h"
#include "error.h"

#define KERNEL_ADDRESS(address) (JOIN(KERNEL_BASE, ULL) | ((uint32_t)address))
#define KERNEL_EXPORT LONGCALL

#define KERNEL_FUNCTION_PRESERVE_CONTEXT(ret, name, args) \
	__asm__ ( \
		".section \".text\"\n" \
		".align 2\n" \
		".p2align 3,,7\n" \
		".globl "#name"\n" \
		".section \".opd\",\"aw\"\n" \
		".align 3\n" \
		#name": \n" \
		"	.quad .L."#name",.TOC.@tocbase\n" \
		"	.previous\n" \
		"	.type "#name", @function\n" \
		".L."#name":\n" \
		"	mflr %r0\n" \
		"	std %r0, 32(%r1)\n" \
		"	std %r2, 40(%r1)\n" \
		"	bl +4\n" \
		"	li %r0, 0\n" \
		"	li %r2, 0\n" \
		"	oris %r2, %r2, __toc@h\n" \
		"	ori %r2, %r2, __toc@l\n" \
		"	oris %r0, %r0, .L."#name"@h\n" \
		"	ori %r0, %r0, .L."#name"@l\n" \
		"	subf %r0, %r0, %r2\n" \
		"	mflr %r2\n" \
		"	addi %r2, %r2, -16\n" \
		"	add %r2, %r2, 0\n" \
		"	bl ._"#name"\n" \
		"	ld %r2, 40(%r1)\n" \
		"	ld %r0, 32(%r1)\n" \
		"	mtlr %r0\n" \
		"	blr\n" \
		"	.size "#name",.-.L."#name"\n" \
	); \
	ret name args; \
	ret _##name args

#define SYS_PROCESS_OBJECT             0x01UL
#define SYS_MEM_OBJECT                 0x08UL
#define SYS_INTR_TAG_OBJECT            0x0AUL
#define SYS_INTR_SERVICE_HANDLE_OBJECT 0x0BUL
#define SYS_EVENT_PORT_OBJECT          0x0EUL
#define SYS_TIMER_OBJECT               0x11UL
#define SYS_TRACE_OBJECT               0x21UL
#define SYS_SPUIMAGE_OBJECT            0x22UL
#define SYS_PRX_OBJECT                 0x23UL
#define SYS_SPUPORT_OBJECT             0x24UL
#define SYS_IO_BUFFER_OBJECT           0x44UL
#define SYS_STORAGE_HANDLE_OBJECT      0x45UL
#define SYS_FS_FD_OBJECT               0x73UL
#define SYS_MUTEX_OBJECT               0x85UL
#define SYS_COND_OBJECT                0x86UL
#define SYS_RWLOCK_OBJECT              0x88UL
#define SYS_EVENT_QUEUE_OBJECT         0x8DUL
#define SYS_LWMUTEX_OBJECT             0x95UL
#define SYS_SEMAPHORE_OBJECT           0x96UL
#define SYS_LWCOND_OBJECT              0x97UL
#define SYS_EVENT_FLAG_OBJECT          0x98UL

#define	PPU_THREAD_CREATE_JOINABLE  0x0000000000000001
#define	PPU_THREAD_CREATE_INTERRUPT 0x0000000000000002

#define	PPU_THREAD_DEFAULT_PRIORITY (-1)
#define	PPU_THREAD_DEFAULT_STACK_SIZE 0x2000

#define PPU_THREAD_ID_INVALID 0xffffffffu

typedef uint32_t process_id_t;
typedef void* process_t;
typedef void* object_handle_t;
typedef void* thread_t;
typedef int32_t prx_id_t;
typedef uint32_t memory_container_t;
typedef uint32_t addr_t;

typedef void (*thread_entry_t)(uint64_t arg);

typedef int64_t time_t;

#define MAX_PATH 1056
#define MAX_IMAGE_FILE_NAME_LENGTH 512

struct __attribute__ ((packed)) process_info_t {
	process_id_t pid;
	uint32_t status;
	uint32_t ppu_thread_count;
	uint32_t spu_thread_count;
	uint32_t raw_spu_count;
	process_id_t parent_pid;
	char* image_file_name;
	uint32_t memory_size;
	uint8_t osabi_type;
	uint8_t pad[3];
	uint64_t param_0x28;
	uint32_t param_0x30;
} process_info_t;

struct __attribute__ ((packed)) prx_segment_info_t {
	uint64_t base;
	uint64_t file_size;
	uint64_t memory_size;
	uint64_t index;
	uint64_t type;
} prx_segment_info_t;

struct __attribute__ ((packed)) prx_module_info_t {
	uint64_t size;
	char name[30];
	char version[2];
	uint32_t attributes;
	uint32_t start_entry;
	uint32_t stop_entry;
	uint32_t all_segment_count;
	uint32_t file_name;
	uint32_t file_name_size;
	uint32_t segments;
	uint32_t segment_count;
} prx_module_info_t;

enum ppu_thread_status {
	PPU_THREAD_STATUS_IDLE,
	PPU_THREAD_STATUS_RUNNABLE,
	PPU_THREAD_STATUS_ONPROC,
	PPU_THREAD_STATUS_SLEEP,
	PPU_THREAD_STATUS_STOP,
	PPU_THREAD_STATUS_ZOMBIE,
	PPU_THREAD_STATUS_DELETED,
	PPU_THREAD_STATUS_UNKNOWN
};

struct __attribute__ ((packed)) fs_stat_t {
	int32_t st_mode;
	int32_t st_uid;
	int32_t st_gid;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	uint64_t st_size;
	uint64_t st_blksize;
} fs_stat_t;

struct fs_dirent_t {
	uint8_t d_type;
	uint8_t d_namlen;
	char d_name[MAX_PATH + 1];
} fs_dirent_t;

struct fs_utime_t {
	time_t actime;
	time_t modtime;
} fs_utime_t;

struct __attribute__ ((packed)) object_desc_t {
	uint32_t uid;
	uint32_t unk;
	void* object;
} object_desc_t;

#define S_IFMT   0170000
#define S_IFSOCK 0140000
#define S_IFLNK  0120000
#define S_IFREG  0100000
#define S_IFBLK  0060000
#define S_IFDIR  0040000
#define S_IFCHR  0020000
#define S_IFIFO  0010000
#define S_ISUID  0004000
#define S_ISGID  0002000
#define S_ISVTX  0001000
#define S_IRWXU  00700
#define S_IRUSR  00400
#define S_IWUSR  00200
#define S_IXUSR  00100
#define S_IRWXG  00070
#define S_IRGRP  00040
#define S_IWGRP  00020
#define S_IXGRP  00010
#define S_IRWXO  00007
#define S_IROTH  00004
#define S_IWOTH  00002
#define S_IXOTH  00001

#define O_RDONLY  000000
#define O_WRONLY  000001
#define O_RDWR    000002
#define O_ACCMODE 000003
#define O_CREAT   000100
#define O_EXCL    000200
#define O_TRUNC   001000
#define O_APPEND  002000
#define O_MSELF   010000

#define DABR_CTRL_READ  0x0000000000000005ULL
#define DABR_CTRL_WRITE 0x0000000000000006ULL
#define DABR_CTRL_CLEAR 0x0000000000000000ULL

#define KB(x) (1024 * (x))
#define MB(x) (1048576 * (x))
#define GB(x) (1073741824 * (x))

#define MEMORY_PAGE_SIZE_4K  0x100
#define MEMORY_PAGE_SIZE_64K 0x200
#define MEMORY_PAGE_SIZE_1M  0x400

KERNEL_EXPORT int lv2_extend_kstack(int flag);

void* malloc(uint64_t size);
void free(void* ptr);

KERNEL_EXPORT void* lv2_allocate(uint64_t size, uint64_t flags);
KERNEL_EXPORT void lv2_deallocate(void* ptr, uint64_t flags);

KERNEL_EXPORT int lv2_page_allocate(process_t process, uint64_t size, uint64_t flags, uint64_t page_size, void** page_address);
KERNEL_EXPORT int lv2_page_deallocate(process_t process, void* page_address, uint64_t flags);
KERNEL_EXPORT int lv2_page_export_to_process(process_t process, void* page_address, uint64_t flags, void** process_page_address);
KERNEL_EXPORT int lv2_page_unexport_from_process(process_t process, void *process_page_address);

KERNEL_EXPORT void* lv2_create_memory_container(void* object, uint64_t size, uint64_t r5, uint64_t r6, uint32_t* result);
KERNEL_EXPORT int lv2_destroy_memory_container(void* container);

KERNEL_EXPORT int lv2_allocate_mapped_memory(uint64_t* address, uint64_t size, uint64_t flags, uint64_t r6, uint64_t r7);

KERNEL_EXPORT void* lv2_memset(void* s, int c, uint64_t n);
KERNEL_EXPORT void* lv2_memcpy(void* dest, const void* src, uint64_t n);
KERNEL_EXPORT void* lv2_memchr(const void *s, int c, uint64_t n);
KERNEL_EXPORT int lv2_memcmp(const void* s1, const void* s2, uint64_t n);

KERNEL_EXPORT uint64_t lv2_strlen(const char* s);
KERNEL_EXPORT char* lv2_strcpy(char* s1, const char *s2);
KERNEL_EXPORT char* lv2_strncpy(char* s1, const char *s2, uint64_t n);
KERNEL_EXPORT char* lv2_strcat(char* s1, const char *s2);
KERNEL_EXPORT char* lv2_strchr(const char* s, int c);
KERNEL_EXPORT char* lv2_strrchr(const char* s, int c);
KERNEL_EXPORT int lv2_strcmp(const char* s1, const char *s2);
KERNEL_EXPORT int lv2_strncmp(const char* s1, const char *s2, uint64_t n);

KERNEL_EXPORT int lv2_printf(const char* format, ...) __attribute__ ((format(printf, 1, 2)));
KERNEL_EXPORT int lv2_sprintf(char* s, const char* format, ...) __attribute__ ((format(printf, 2, 3)));
KERNEL_EXPORT int lv2_snprintf(char* s, uint64_t size, const char* format, ...) __attribute__ ((format(printf, 3, 4)));
KERNEL_EXPORT int lv2_vsnprintf(char* str, uint64_t size, const char* format, va_list args);

KERNEL_EXPORT int lv2_fs_open_1(const char* path, uint32_t flags, int64_t* fd, uint32_t mode, void* args, uint64_t args_size);
KERNEL_EXPORT int lv2_fs_open_2(const char* path, uint32_t flags, int64_t* fd, uint32_t mode, void* args, uint64_t args_size);
KERNEL_EXPORT int lv2_fs_read(int64_t fd, void* data, uint32_t size, uint64_t* num_read);
KERNEL_EXPORT int lv2_fs_write(int64_t fd, const void* data, uint32_t size, uint64_t* num_written);
KERNEL_EXPORT int lv2_fs_lseek(int64_t fd, int64_t offset, int whence, uint64_t* position);
KERNEL_EXPORT int lv2_fs_stat(const char* path, struct fs_stat_t* stat);
KERNEL_EXPORT int lv2_fs_close(int64_t fd);

KERNEL_EXPORT int lv2_syscall_sys_process_getpid(void);
KERNEL_EXPORT int lv2_syscall_sys_process_exit(int code);

KERNEL_EXPORT int lv2_ppu_thread_create(thread_t* id, thread_entry_t entry, uint64_t arg, int priority, uint64_t stack_size, uint64_t flags, const char* name);
KERNEL_EXPORT int lv2_ppu_thread_join(thread_t id, uint64_t* vptr);
KERNEL_EXPORT int lv2_ppu_thread_delay(thread_t id, uint64_t usecs, int unk1, int unk2);
KERNEL_EXPORT int lv2_ppu_thread_exit(uint64_t code);

KERNEL_EXPORT thread_t lv2_create_user_thread1(void* unk, void* entry, uint64_t arg, uint64_t unk2, uint32_t stack, uint64_t stack_size, process_t process, uint64_t flags, void* unk3, const char* name);
KERNEL_EXPORT thread_t lv2_create_user_thread2(void* unk, void* entry, uint64_t arg, uint64_t unk2, uint32_t stack, uint64_t stack_size, process_t process, uint64_t flags, const char* name);
KERNEL_EXPORT int lv2_register_thread(process_t process, thread_t thread, uint64_t unk);
KERNEL_EXPORT int lv2_start_thread(thread_t thread, int priority, uint64_t unk);
KERNEL_EXPORT int lv2_run_thread(thread_t thread);

KERNEL_EXPORT uint32_t lv2_allocate_user_stack(process_t process, uint64_t* stack_size);
KERNEL_EXPORT void lv2_deallocate_user_stack(process_t process, uint32_t stack, uint64_t stack_size);

KERNEL_EXPORT int lv2_copy_from_user(const void* uptr, void* kptr, uint64_t size);
KERNEL_EXPORT int lv2_copy_to_user(const void* kptr, void* uptr, uint64_t size);
KERNEL_EXPORT int lv2_copy_to_process(process_t process, void* kptr, void* uptr, uint64_t size);
KERNEL_EXPORT int lv2_copy_from_process(process_t process, void* uptr, void* kptr, uint64_t size);

KERNEL_EXPORT int lv2_id_table_reserve_id(uint64_t uid, void** private_kernel_object, object_handle_t* object);
KERNEL_EXPORT int lv2_id_table_unreserve_id(void* object_table, object_handle_t handle);

KERNEL_EXPORT uint64_t lv2_get_object_count(void* object_table, uint32_t type);
KERNEL_EXPORT int lv2_get_objects(void* object_table, uint32_t type, struct object_desc_t* objects, uint64_t count);

KERNEL_EXPORT int lv2_process_sub_8000000000003B38(process_id_t pid);
KERNEL_EXPORT int lv2_process_read_memory(process_t process, uint64_t ea_address, void* data, uint64_t size);
KERNEL_EXPORT int lv2_process_write_memory_ex(process_t process, uint64_t ea_address, const void* data, uint64_t size, int flag);
KERNEL_EXPORT int lv2_process_allocate_mapped_memory_ex(void* memory_object, uint64_t r4, uint64_t size, uint64_t r6, void* context, uint64_t* address);

static INLINE int lv2_process_write_memory(process_t process, uint64_t ea_address, const void* data, uint64_t size) {
	return lv2_process_write_memory_ex(process, ea_address, data, size, 1);
}

static INLINE int lv2_process_allocate_mapped_memory(process_t process, uint64_t size, uint64_t flags, uint64_t* address) {
	uint64_t r4;
	uint64_t page_size;
	if (flags == MEMORY_PAGE_SIZE_64K) {
		page_size = 0x10000;
		r4 = 3;
	} else if (flags == MEMORY_PAGE_SIZE_1M || flags == 0) {
		page_size = 0x100000;
		r4 = 4;
	} else {
		return EINVAL;
	}
	if ((size / page_size) * page_size != size)
		return EINVAL;
	void* memory_object = (void*)*(uint64_t*)((uint8_t*)process + 0x30);
	void* context = (void*)*(uint64_t*)((uint8_t*)memory_object + 0x2D0);
	uint64_t r6 = 0x100500;
	return lv2_process_allocate_mapped_memory_ex(memory_object, r4, size, r6, context, address);
}

KERNEL_EXPORT int lv2_process_get_internal_ppu_thread_count(process_t process);
KERNEL_EXPORT int lv2_process_get_parent_pid(process_t process, process_id_t* pid);

KERNEL_EXPORT int lv2_prx_load_module(process_t process, memory_container_t mem_container, uint64_t flags, const char* path);
KERNEL_EXPORT int lv2_prx_start_module(prx_id_t id, process_t process, uint64_t flags, void* info);
KERNEL_EXPORT int lv2_prx_stop_module(prx_id_t id, process_t process, uint64_t flags, void* info);
KERNEL_EXPORT int lv2_prx_unload_module(prx_id_t id, process_t process);

KERNEL_EXPORT int lv2_prx_get_module_info(process_t process, prx_id_t id, struct prx_module_info_t* info, const char* file_name, struct prx_segment_info_t* segments);
KERNEL_EXPORT prx_id_t lv2_prx_get_module_id_by_address(process_t process, uint64_t address);
KERNEL_EXPORT prx_id_t lv2_prx_get_module_id_by_name(process_t process, const char* name);
KERNEL_EXPORT int lv2_prx_get_module_list(process_t process, prx_id_t* list, uint32_t* unk_list, uint32_t max_count, uint32_t* count, uint32_t* num2);

KERNEL_EXPORT int lv2_kernel_ea_to_lpar_addr(uint64_t ea_address, uint64_t* lpar_addr);
KERNEL_EXPORT int lv2_process_ea_to_lpar_addr_ex(uint64_t address_space, uint64_t ea_address, uint64_t* lpar_address);

KERNEL_EXPORT int lv2_map_contiguous_memory(uint64_t address_space, uint64_t lpar_region_address, uint64_t lpar_region_size, uint64_t page_tag, uint64_t ea_address, uint64_t* ea_address_r8);
KERNEL_EXPORT int lv2_unmap_contiguous_memory(uint64_t address_space, uint64_t ea_address, uint64_t lpar_region_size);

KERNEL_EXPORT uint64_t lv2_spin_lock_irqsave_ex(void* ta);
KERNEL_EXPORT void lv2_spin_unlock_irqrestore_ex(void* ta, uint64_t restore, int zero);

KERNEL_EXPORT int lv2_panic(uint64_t unk);

int page_allocate_auto(process_t process, uint64_t size, uint64_t flags, void** page_address);

int prx_start_module_with_thread(prx_id_t id, process_t process, uint64_t flags, uint64_t arg);
int prx_stop_module_with_thread(prx_id_t id, process_t process, uint64_t flags, uint64_t arg);

void suspend_interrupts(void);
void resume_interrupts(void);

thread_t get_current_thread(void);
process_t get_current_process(void);
process_t get_current_process_critical(void);
void* get_current_process_object_table(void);

process_id_t process_get_pid(process_t process);
int32_t process_get_thread_count(process_t process);
uint32_t process_get_status(process_t process);
uint64_t process_get_ppu_thread_count(process_t process);
uint64_t process_get_spu_thread_count(process_t process);
uint64_t process_get_raw_spu_count(process_t process);
uint32_t process_get_parent_pid(process_t process);
uint64_t process_get_address_space(process_t process);
uint64_t process_get_memory_size(process_t process);
uint8_t process_get_osabi_type(process_t process);
uint64_t process_get_0x248(process_t process);
uint32_t process_get_0x278(process_t process);
const char* process_get_image_file_name(process_t process);
const char* process_get_name(process_t process);
uint32_t process_get_sdk_version(process_t process);
uint32_t process_get_ppu_guid(process_t process);
uint8_t* process_get_param_sfo(process_t process);
const char* ppu_thread_status_to_string(uint32_t status);

int process_get_info(process_t process, struct process_info_t* info);

int process_ea_to_lpar_addr(process_t process, uint64_t ea_address, uint64_t* lpar_address);

int ppu_user_thread_create(process_t process, thread_t* thread, void* entry, uint64_t arg, int priority, uint64_t stack_size, uint64_t flags, const char* name);

uint64_t lv1_peek64(uint64_t address);
void lv1_poke64(uint64_t address, uint64_t value);

uint64_t lv2_peek64(uint64_t address);
void lv2_poke64(uint64_t address, uint64_t value);
void lv2_poke64_no_sync(uint64_t address, uint64_t value);

void clear_icache(uint64_t address, uint64_t size);

uint64_t get_call_address(int level);

int set_dabr(uint64_t address, uint64_t control_flag);

uint64_t spin_lock_irqsave(void);
void spin_unlock_irqrestore(uint64_t restore);

void print_backtrace(int n);

static INLINE int timer_usleep(uint64_t usecs) {
	return lv2_ppu_thread_delay(get_current_thread(), usecs, 0, 1);
}

static INLINE void lv2_poke32(uint64_t address, uint32_t value) {
	uint64_t old_value = lv2_peek64(address);
	lv2_poke64(address, ((uint64_t)value << 32) | (old_value & 0xFFFFFFFFULL));
}

static INLINE void lv2_poke16(uint64_t address, uint16_t value) {
	uint64_t old_value = lv2_peek64(address);
	lv2_poke64(address, ((uint64_t)value << 48) | (old_value & 0xFFFFFFFFFFFFULL));
}

static INLINE void lv2_poke8(uint64_t address, uint8_t value) {
	uint64_t old_value = lv2_peek64(address);
	lv2_poke64(address, ((uint64_t)value << 56) | (old_value & 0xFFFFFFFFFFFFFFULL));
}

#endif