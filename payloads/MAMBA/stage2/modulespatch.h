#ifndef __MODULESPATCH_H__
#define __MODULESPATCH_H__

#include <lv2/process.h>
#include <lv2/thread.h>

extern u8 condition_ps2softemu;
extern u8 condition_psp_iso;
extern u8 condition_psp_dec;
extern u8 condition_psp_keys;
//extern u8 condition_psp_change_emu;
extern u8 condition_psp_prometheus;
extern u8 condition_apphome; //needed libfs patch (JB FORMAT GAME)

typedef struct
{
	u32 offset;
	u32 data;
	u8 *condition;
} SprxPatch;

extern process_t vsh_process;
process_t get_vsh_process(void); //NzV
extern int vsh_type;

void load_boot_plugins(void);
void load_boot_plugins_kernel(void);

/* Functions for kernel */
void modules_patch_init(void);
int prx_load_vsh_plugin(unsigned int slot, char *path, void *arg, u32 arg_size);
int prx_unload_vsh_plugin(unsigned int slot);

/* Syscalls */
int sys_prx_load_vsh_plugin(unsigned int slot, char *path, void *arg, u32 arg_size);
int sys_prx_unload_vsh_plugin(unsigned int slot);
int sys_thread_create_ex(sys_ppu_thread_t *thread, void *entry, u64 arg, int prio, u64 stacksize, u64 flags, const char *threadname);

#ifdef FAN_CONTROL
void unhook_all_fan_patches(void);
#endif

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
int um_if_get_token(u8 *token,u32 token_size,u8 *seed,u32 seed_size);
int read_eeprom_by_offset(u32 offset, u8 *value, u64 auth_id);

int sys_fs_open(const char *path, int flags, int *fd, u64 mode, const void *arg, u64 size);
int sys_fs_read(int fd, void *buf, u64 nbytes, u64 *nread);
int sys_fs_close(int fd);

void debug_install(void);
void debug_uninstall(void);

void do_patch(u64 addr, u64 patch);
void do_patch32(u64 addr, u32 patch);

#endif /* __MODULESPATCH_H__ */

