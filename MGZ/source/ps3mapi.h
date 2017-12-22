#ifndef _PS3MAPI_H
#define _PS3MAPI_H

#include <ppu-lv2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t process_id_t;

typedef int32_t sys_prx_id_t;

typedef struct
{
	void *unk_00; // 0
	char name[24]; // 8
	// ...
} __attribute__((packed)) UnkProcessStruct;

typedef struct _process_t
{
	void *syscall_table; // 0
	uint64_t unk_8[4]; // 8
	uint32_t pid; // 0x28
	int status; // 0x2C
	void *mem_object; // 0x30
	UnkProcessStruct *unk_38; // 0x38
	uint64_t unk_40; // 0x40
	void *first_thread; // 0x48 
	uint64_t unk_50; // 0x50
	uint64_t unk_58; // 0x58
	void *unk_60; // 0x60
	void *unk_68; // 0x68 vshprocess -> mios2_SPU_Service.elf
	void *unk_70; // 0x70 vshprocess -> mios2_SPU_Service.elf
	uint64_t unk_78; // 0x78
	uint64_t unk_80; // 0x80
	uint64_t unk_88[4]; // 0x88
	uint64_t unk_A8; // 0xA8  user address?
	struct _process_t *parent; // 0xB0
	struct _process_t *first_child; // 0xB8  
	struct _process_t *next_sibling; // 0xC0
	uint64_t num_children; // 0xC8
	void *unk_D0; // 0xD0
	uint64_t unk_D8; // 0xD8
	uint64_t unk_E0; // 0xE0
	uint64_t unk_E8; // 0xE8
	uint64_t unk_F0[2]; // 0xF0
	uint64_t unk_100; // 0x100
	uint64_t unk_108; // 0x108
	void *unk_110; // 0x110
	void *unk_118; // 0x118  vshprocess -> pointer to unk_D0
	uint64_t unk_120; // 0x120
	void *unk_128; // 0x128  only on vshprocess -> same as first_thread
	void *unk_130; // 0x130 only on vsh process -> same as first thread
	uint64_t unk_138; // 0x138
	uint64_t unk_140[4]; // 0x140
	char *process_image; // 0x160
	void *unk_168; // 0x168
	uint64_t unk_170; // 0x170
	uint64_t unk_178; // 0x178
	uint64_t unk_180; // 0x180
	uint64_t unk_188[4]; // 0x188
	uint64_t unk_1A8; // 0x1A8
	uint64_t unk_1B0; // 0x1B0
	uint64_t unk_1B8; // 0x1B8
	uint64_t unk_1C0; // 0x1C0
	uint64_t unk_1C8; // 0x1C8
	uint64_t unk_1D0; // 0x1D0
	uint64_t unk_1D8; // 0x1D8
	uint64_t unk_1E0; // 0x1E0
	uint64_t unk_1E8[4]; // 0x1E8
	void *object_table; // 0x208 waiting for a better name...
	// ...?
	// 0x26C -> sdk version 32bits
} __attribute__((packed)) *process_t;

//-----------------------------------------------
//CORE
//-----------------------------------------------

int ps3mapi_get_core_version();
int ps3mapi_get_core_minversion();
int ps3mapi_get_fw_type(char *fw);
int ps3mapi_get_fw_version();

//-----------------------------------------------
//PEEK POKE
//-----------------------------------------------

int ps3mapi_support_sc8_peek_poke();
u64 ps3mapi_lv2_peek(u64 value);
int ps3mapi_lv2_poke(u64 addr, u64 value);
u64 ps3mapi_lv1_peek(u64 value);
int ps3mapi_lv1_poke(u64 addr, u64 value);

//-----------------------------------------------
//SECURITY
//-----------------------------------------------

int ps3mapi_set_access_key(int ps3mapi_key);
int ps3mapi_request_access(int ps3mapi_key);

//-----------------------------------------------
//PROCESSES
//-----------------------------------------------

int ps3mapi_get_all_processes_pid(process_id_t *pid_list);
int ps3mapi_get_process_name_by_pid(process_id_t pid, char *name);
int ps3mapi_get_process_by_pid(process_id_t pid, process_t process);
int ps3mapi_get_current_process(process_t process);
int ps3mapi_get_current_process_critical(process_t process);

//-----------------------------------------------
//MEMORY
//-----------------------------------------------

int ps3mapi_set_process_mem(process_id_t pid, uint64_t addr, char *buf, int size);
int ps3mapi_get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size);

//-----------------------------------------------
//MODULES
//-----------------------------------------------

int ps3mapi_get_all_process_modules_prx_id(process_id_t pid, sys_prx_id_t *prx_id_list);
int ps3mapi_get_process_module_name_by_prx_id(process_id_t pid, sys_prx_id_t prx_id, char *name);
int ps3mapi_get_process_module_filename_by_prx_id(process_id_t pid, sys_prx_id_t prx_id, char *name);
int ps3mapi_load_process_modules(process_id_t pid, char *path, void *arg, uint32_t arg_size);
int ps3mapi_unload_process_modules(process_id_t pid, sys_prx_id_t prx_id);
int ps3mapi_unload_vsh_plugin(char* name);
int ps3mapi_get_vsh_plugin_info(unsigned int slot, char *name, char *filename);

//-----------------------------------------------
//SYSCALL
//-----------------------------------------------

int ps3mapi_check_syscall(int num);
int ps3mapi_disable_syscall(int num);
int ps3mapi_pdisable_syscall(int pdisable_sc8);
int ps3mapi_pdisable_syscall();

//-----------------------------------------------
//REMOVE COBRA/MAMBA HOOK
//-----------------------------------------------

int ps3mapi_remove_hook();

//-----------------------------------------------
//PSID/IDPS
//-----------------------------------------------

int ps3mapi_get_idps(uint64_t *idps);
int ps3mapi_set_idps(uint64_t part1, uint64_t part2);
int ps3mapi_get_psid(uint64_t *psid);
int ps3mapi_set_psid(uint64_t part1, uint64_t part2);

#ifdef __cplusplus
}
#endif

#endif /* _PS3MAPI_H */