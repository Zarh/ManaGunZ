#ifndef __MODULESPATCH_H__
#define __MODULESPATCH_H__

#include <lv2/process.h>
#include <lv2/thread.h>

extern uint8_t condition_ps2softemu;
extern uint8_t condition_psp_iso;
extern uint8_t condition_psp_dec;
extern uint8_t condition_psp_keys;
//extern uint8_t condition_psp_change_emu;
extern uint8_t condition_psp_prometheus;
extern uint8_t condition_apphome; //needed libfs patch (JB FORMAT GAME)

typedef struct
{
	uint32_t offset;
	uint32_t data;
	uint8_t *condition;
} SprxPatch;

extern process_t vsh_process;
process_t get_vsh_process(void); //NzV
extern int vsh_type;

void load_boot_plugins(void);
void load_boot_plugins_kernel(void);

/* Functions for kernel */
void modules_patch_init(void);
int prx_load_vsh_plugin(unsigned int slot, char *path, void *arg, uint32_t arg_size);
int prx_unload_vsh_plugin(unsigned int slot);

/* Syscalls */
int sys_prx_load_vsh_plugin(unsigned int slot, char *path, void *arg, uint32_t arg_size);
int sys_prx_unload_vsh_plugin(unsigned int slot);
int sys_thread_create_ex(sys_ppu_thread_t *thread, void *entry, uint64_t arg, int prio, uint64_t stacksize, uint64_t flags, const char *threadname);

#ifdef PS3M_API
void ps3mapi_unhook_all(void);
void unhook_all_modules(void);
int ps3mapi_unload_vsh_plugin(char* name);
int ps3mapi_get_vsh_plugin_info(unsigned int slot, char *name, char *filename);
#endif

#ifdef ps2tonet_patch
int bc_to_net(int param);
#endif

// post_lv1_call_99_wrapper
int um_if_get_token(uint8_t *token,uint32_t token_size,uint8_t *seed,uint32_t seed_size);
int read_eeprom_by_offset(uint32_t offset, uint8_t *value, uint64_t auth_id);

int sys_fs_open(const char *path, int flags, int *fd, uint64_t mode, const void *arg, uint64_t size);
int sys_fs_read(int fd, void *buf, uint64_t nbytes, uint64_t *nread);
int sys_fs_close(int fd);

void debug_install(void);
void debug_uninstall(void);

void do_patch(uint64_t addr, uint64_t patch);
void do_patch32(uint64_t addr, uint32_t patch);

#endif /* __MODULESPATCH_H__ */

