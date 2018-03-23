#include "ps3mapi.h"

#define SC_COBRA_SYSCALL8						8
#define SYSCALL8_OPCODE_PS3MAPI			 		0x7777

//-----------------------------------------------
//CORE
//-----------------------------------------------

#define PS3MAPI_CORE_VERSION			 		0x0122
#define PS3MAPI_CORE_MINVERSION			 		0x0111

#define PS3MAPI_OPCODE_GET_CORE_VERSION			0x0011
#define PS3MAPI_OPCODE_GET_CORE_MINVERSION		0x0012
#define PS3MAPI_OPCODE_GET_FW_TYPE				0x0013
#define PS3MAPI_OPCODE_GET_FW_VERSION			0x0014

int ps3mapi_get_core_version()
{
	lv2syscall2(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_CORE_VERSION);
	return_to_user_prog(int);
}

int ps3mapi_get_core_minversion()
{
	lv2syscall2(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_CORE_MINVERSION);
	return_to_user_prog(int);
}

int ps3mapi_get_fw_type(char *fw)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_FW_TYPE, (u64) fw);
	return_to_user_prog(int);
}

int ps3mapi_get_fw_version()
{
	lv2syscall2(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_FW_VERSION);
	return_to_user_prog(int);
}

//-----------------------------------------------
//PEEK POKE
//-----------------------------------------------

#define PS3MAPI_OPCODE_SUPPORT_SC8_PEEK_POKE	0x1000
#define PS3MAPI_OPCODE_LV2_PEEK					0x1006
#define PS3MAPI_OPCODE_LV2_POKE					0x1007
#define PS3MAPI_OPCODE_LV1_PEEK					0x1008
#define PS3MAPI_OPCODE_LV1_POKE					0x1009

#define PS3MAPI_OPCODE_SUPPORT_SC8_PEEK_POKE_OK	0x6789

int ps3mapi_support_sc8_peek_poke()
{
	lv2syscall2(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SUPPORT_SC8_PEEK_POKE);
	return_to_user_prog(int);
}

u64 ps3mapi_lv2_peek(u64 value)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LV2_PEEK, (u64) value);
	return_to_user_prog(u64);
}

int ps3mapi_lv2_poke(u64 addr, u64 value)
{
	lv2syscall4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LV2_POKE, (u64) addr, (u64) value);
	return_to_user_prog(int);
}

u64 ps3mapi_lv1_peek(u64 value)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LV1_PEEK, (u64) value);
	return_to_user_prog(u64);
}

int ps3mapi_lv1_poke(u64 addr, u64 value)
{
	lv2syscall4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LV1_POKE, (u64) addr, (u64) value);
	return_to_user_prog(int);
}

//-----------------------------------------------
//SECURITY
//-----------------------------------------------

#define PS3MAPI_OPCODE_SET_ACCESS_KEY			0x2000
#define PS3MAPI_OPCODE_REQUEST_ACCESS			0x2001

int ps3mapi_set_access_key(int ps3mapi_key)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_ACCESS_KEY, (u64) ps3mapi_key);
	return_to_user_prog(int);
}

int ps3mapi_request_access(int ps3mapi_key)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_REQUEST_ACCESS, (u64) ps3mapi_key);
	return_to_user_prog(int);
}

//-----------------------------------------------
//PROCESSES
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_ALL_PROC_PID			0x0021
#define PS3MAPI_OPCODE_GET_PROC_NAME_BY_PID		0x0022
#define PS3MAPI_OPCODE_GET_PROC_BY_PID			0x0023
#define PS3MAPI_OPCODE_GET_CURRENT_PROC			0x0024
#define PS3MAPI_OPCODE_GET_CURRENT_PROC_CRIT	0x0025

int ps3mapi_get_all_processes_pid(process_id_t *pid_list)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_ALL_PROC_PID, (u64) pid_list);
	return_to_user_prog(int);
}

int ps3mapi_get_process_name_by_pid(process_id_t pid, char *name)
{
	lv2syscall4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_NAME_BY_PID, (u64) pid, (u64) name);
	return_to_user_prog(int);
}

int ps3mapi_get_process_by_pid(process_id_t pid, process_t process)
{
	lv2syscall4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_BY_PID, (u64) pid, (u64) process);
	return_to_user_prog(int);
}

int ps3mapi_get_current_process(process_t process)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_CURRENT_PROC, (u64) process);
	return_to_user_prog(int);
}

int ps3mapi_get_current_process_critical(process_t process)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_CURRENT_PROC_CRIT, (u64) process);
	return_to_user_prog(int);
}

//-----------------------------------------------
//MEMORY
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_PROC_MEM				0x0031
#define PS3MAPI_OPCODE_SET_PROC_MEM				0x0032

int ps3mapi_set_process_mem(process_id_t pid, uint64_t addr, char *buf, int size)
{
	lv2syscall5(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_MEM, (u64) pid, (u64) addr, (u64) size);
	return_to_user_prog(int);
}

int ps3mapi_get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size)
{
	lv2syscall6(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_PROC_MEM, (u64) pid, (u64) addr, (u64) buf, (u64) size);
	return_to_user_prog(int);
}

//-----------------------------------------------
//MODULES
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_ALL_PROC_MODULE_PID		0x0041
#define PS3MAPI_OPCODE_GET_PROC_MODULE_NAME			0x0042
#define PS3MAPI_OPCODE_GET_PROC_MODULE_FILENAME		0x0043
#define PS3MAPI_OPCODE_LOAD_PROC_MODULE				0x0044
#define PS3MAPI_OPCODE_UNLOAD_PROC_MODULE			0x0045
#define PS3MAPI_OPCODE_UNLOAD_VSH_PLUGIN			0x0046
#define PS3MAPI_OPCODE_GET_VSH_PLUGIN_INFO			0x0047

int ps3mapi_get_all_process_modules_prx_id(process_id_t pid, sys_prx_id_t *prx_id_list)
{
	lv2syscall4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_ALL_PROC_MODULE_PID, (u64) pid, (u64) prx_id_list);
	return_to_user_prog(int);
}

int ps3mapi_get_process_module_name_by_prx_id(process_id_t pid, sys_prx_id_t prx_id, char *name)
{
	lv2syscall5(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_MODULE_NAME, (u64) pid, (u64) prx_id, (u64) name);
	return_to_user_prog(int);
}

int ps3mapi_get_process_module_filename_by_prx_id(process_id_t pid, sys_prx_id_t prx_id, char *name)
{
	lv2syscall5(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_MODULE_FILENAME, (u64) pid, (u64) prx_id, (u64) name);
	return_to_user_prog(int);
}

int ps3mapi_load_process_modules(process_id_t pid, char *path, void *arg, uint32_t arg_size)
{
	lv2syscall6(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LOAD_PROC_MODULE, (u64) pid, (u64) path, (u64) arg, (u64) arg_size);
	return_to_user_prog(int);
}

int ps3mapi_unload_process_modules(process_id_t pid, sys_prx_id_t prx_id)
{
	lv2syscall4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_UNLOAD_PROC_MODULE, (u64) pid, (u64) prx_id);
	return_to_user_prog(int);
}

int ps3mapi_unload_vsh_plugin(char* name)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_UNLOAD_VSH_PLUGIN, (u64) name);
	return_to_user_prog(int);
}


int ps3mapi_get_vsh_plugin_info(unsigned int slot, char *name, char *filename)
{
	lv2syscall5(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_VSH_PLUGIN_INFO, (u64) slot, (u64) name, (u64) filename);
	return_to_user_prog(int);
}

//-----------------------------------------------
//SYSCALL
//-----------------------------------------------

#define PS3MAPI_OPCODE_CHECK_SYSCALL			0x0091
#define PS3MAPI_OPCODE_DISABLE_SYSCALL			0x0092
#define PS3MAPI_OPCODE_PDISABLE_SYSCALL8 		0x0093
#define PS3MAPI_OPCODE_PCHECK_SYSCALL8 			0x0094

int ps3mapi_check_syscall(int num)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_CHECK_SYSCALL, (u64) num);
	return_to_user_prog(int);
}

int ps3mapi_disable_syscall(int num)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_DISABLE_SYSCALL, (u64) num);
	return_to_user_prog(int);
}

int ps3mapi_pdisable_syscall8(int pdisable_sc8)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_PDISABLE_SYSCALL8, (u64) pdisable_sc8);
	return_to_user_prog(int);
}

int ps3mapi_pcheck_syscall8()
{
	lv2syscall2(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_PCHECK_SYSCALL8);
	return_to_user_prog(int);
}

//-----------------------------------------------
//REMOVE COBRA/MAMBA HOOK
//-----------------------------------------------

#define PS3MAPI_OPCODE_REMOVE_HOOK			0x0101

int ps3mapi_remove_hook()
{
	lv2syscall2(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_REMOVE_HOOK);
	return_to_user_prog(int);
}

//-----------------------------------------------
//PSID/IDPS
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_IDPS 		0x0081
#define PS3MAPI_OPCODE_SET_IDPS 		0x0082
#define PS3MAPI_OPCODE_GET_PSID 		0x0083
#define PS3MAPI_OPCODE_SET_PSID			0x0084

int ps3mapi_get_idps(uint64_t *idps)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_IDPS, (u64) idps);
	return_to_user_prog(int);
}

int ps3mapi_set_idps(uint64_t part1, uint64_t part2)
{
	lv2syscall4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_IDPS, (u64) part1, (u64) part2);
	return_to_user_prog(int);
}

int ps3mapi_get_psid(uint64_t *psid)
{
	lv2syscall3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PSID, (u64) psid);
	return_to_user_prog(int);
}

int ps3mapi_set_psid(uint64_t part1, uint64_t part2)
{
	lv2syscall4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_PSID, (u64) part1, (u64) part2);
	return_to_user_prog(int);
}
