#ifndef	__LV2_SYSCALL_H__
#define __LV2_SYSCALL_H__

#include <lv2/lv2.h>
#include <lv2/patch.h>

#define SYS_PROCESS_GETPID											  1 // sys_pid_t sys_process_getpid(void);
#define SYS_PROCESS_WAIT_FOR_CHILD									  2 // 3 params: sys_pid_t, uint32_t *status, unk=0
#define SYS_PROCESS_EXIT											  3 // int sys_process_exit(int)
#define SYS_PROCESS_GET_STATUS										  4 // int sys_process_get_status(sys_pid_t pid)
#define SYS_PROCESS_DETACH_CHILD									  5 // 1 param
//#define SYS_PROCESS_CREATE_PROGRAM_SEGMENT						  6
//#define SYS_PROCESS_DESTROY_PROGRAM_SEGMENT						  7
//#define SYS_PROCESS_AUTHENTICATE_PROGRAM_SEGMENT					  8
//#define SYS_PROCESS_LOAD_PROGRAM_SEGMENT							  9
//#define SYS_PROCESS_UNLOAD_PROGRAM_SEGMENT						 10
//#define SYS_PROCESS_FIND_PROGRAM_SEGMENT							 11
#define SYS_PROCESS_GET_NUMBER_OF_OBJECT							 12 // int sys_process_get_number_of_object(uint32_t object_type, uint32_t* count)
#define SYS_PROCESS_GET_ID											 13 // int sys_process_get_id(uint32_t object, uint32_t * buff, size_t size, size_t * set_size);
#define SYS_PROCESS_IS_SPU_LOCK_LINE_RESERVATION_ADDRESS			 14 // int sys_process_is_spu_lock_line_reservation_address(sys_addr_t addr, uint64_t flags);
//#define SYS_PROCESS_CREATE										 15
//#define SYS_PROCESS_CREATE_PRIMARY_PPU_THREAD						 17
#define SYS_PROCESS_GETPPID											 18 // sys_pid_t sys_process_getppid(void);
#define SYS_PROCESS_KILL											 19 // int sys_process_kill(sys_pid_t pid);
//#define sys_process_create_primary_ppu_thread_tls					 20
#define SYS_PROCESS_SPAWN											 21 // int sys_process_spawn(int *pid, int prio, uint64_t flags, void *stack, int stack_size, int unk1, int unk2)
#define SYS_PROCESS_EXIT2											 22 // void sys_process_exit2(int error_code,0,0)
#define SYS_PROCESS_WAIT_FOR_CHILD2									 23
//#define _sys_process_spawn2										 24 /* another create process too, used for games, ps1 emu, etc */
#define SYS_PROCESS_GET_SDK_VERSION									 25 // 2 params :sys_pid_t pid, uint8_t outbuf[4]
//#define _sys_process_exit											 26 /* calls sys_process_exit 4 params (calls sys_process_exit) */
//#define _sys_process_spawn3										 27 /* another create process too, used for games, ps1 emu, etc */
//#define _sys_process_get_number_of_object							 28 /* int sys_process_get_number_of_object(uint32_t object) */
//#define _sys_process_get_id										 29 /* same as syscall13 just with root flag check, same input etc. */
#define SYS_PROCESS_GET_PARAMSFO									 30	// int _sys_process_get_paramsfo(uint8_t buffer[0x40]);
#define SYS_PROCESS_GET_PPU_GUID									 31 // sys_addr_t sys_process_get_ppu_guid(void);
#define SYS_PPU_THREAD_EXIT											 41 // int sys_ppu_thread_exit(int errorcode)
//#define SYS_PPU_THREAD_GET_ID										 42
#define SYS_PPU_THREAD_YIELD										 43 // void sys_ppu_thread_yield(void);
#define SYS_PPU_THREAD_JOIN											 44 // int sys_ppu_thread_join(sys_ppu_thread_t thread_id, uint64_t * vptr);
#define SYS_PPU_THREAD_DETACH										 45 // int sys_ppu_thread_detach(sys_ppu_thread_t thread_id);
#define SYS_PPU_THREAD_GET_JOIN_STATE								 46 // void sys_ppu_thread_get_join_state(int *isjoinable);
#define SYS_PPU_THREAD_SET_PRIORITY									 47 // int sys_ppu_thread_set_priority(sys_ppu_thread_t thread_id, int prio); Flags are checked when 3071 > prio < 3199
#define SYS_PPU_THREAD_GET_PRIORITY									 48 // int sys_ppu_thread_get_priority(sys_ppu_thread_t thread_id, int *prio);
#define SYS_PPU_THREAD_GET_STACK_INFORMATION						 49 // int sys_ppu_thread_get_stack_information(sys_ppu_thread_stack_t * info);
#define SYS_PPU_THREAD_STOP											 50 // int sys_ppu_thread_stop(sys_ppu_thread_t thread_id);
#define SYS_PPU_THREAD_RESTART										 51 // int sys_ppu_thread_restart(void);
#define SYS_PPU_THREAD_CREATE										 52 // int sys_ppu_thread_create(sys_ppu_thread_t *thread_id, & void (*entry)(uint64_t), uint64_t arg, 0, int prio, size_t stacksize, uint64_t flags, const char *threadname);
#define SYS_PPU_THREAD_START										 53 // int sys_ppu_thread_start(sys_ppu_thread_t thread_id);
//#define _get_allocation_information								 54 // syscall(0x036, 0x109/0x111, out: uint8[4]), pu_thread get (kernel) allocation information
//#define _set_allocation_information								 55 // syscall(0x037, 0x111, 0> int <0x100), pu_thread set (kernel) allocation? information
#define SYS_PPU_THREAD_RENAME										 56 // int sys_ppu_thread_rename(sys_ppu_thread_t thread_id, const char *name);
#define SYS_PPU_THREAD_RECOVER_PAGE_FAULT							 57 // int sys_ppu_thread_recover_page_fault(sys_ppu_thread_t thread_id);
#define SYS_PPU_THREAD_GET_PAGE_FAULT_CONTEXT						 58 // int sys_ppu_thread_get_page_fault_context(sys_ppu_thread_t thread_id, sys_ppu_thread_icontext_t * ctxp);
#define SYS_TRACE_CREATE											 60
#define SYS_TRACE_START												 61
#define SYS_TRACE_STOP												 62
#define SYS_TRACE_UPDATE_TOP_INDEX									 63
#define SYS_TRACE_DESTROY											 64
#define SYS_TRACE_DRAIN												 65
#define SYS_TRACE_ATTACH_PROCESS									 66
#define SYS_TRACE_ALLOCATE_BUFFER									 67
#define SYS_TRACE_FREE_BUFFER										 68
#define SYS_TRACE_CREATE2											 69
#define SYS_TIMER_CREATE											 70 // int sys_timer_create(sys_timer_t * timer_id);
#define SYS_TIMER_DESTROY											 71 // int sys_timer_destroy(sys_timer_t timer_id);
#define SYS_TIMER_GET_INFORMATION									 72 // int sys_timer_get_information(sys_timer_t timer_id, sys_timer_information_t * info);
#define SYS_TIMER_START												 73 // int sys_timer_start(sys_timer_t timer_id, system_time_t base_time, usecond_t period);
#define SYS_TIMER_STOP												 74 // int sys_timer_stop(sys_timer_t timer_id);
#define SYS_TIMER_CONNECT_EVENT_QUEUE								 75 // int sys_timer_connect_event_queue(sys_timer_t timer_id, sys_event_queue_t queue_id, uint64_t name, uint64_t data1, uint64_t data2);
#define SYS_TIMER_DISCONNECT_EVENT_QUEUE							 76 // int sys_timer_disconnect_event_queue(sys_timer_t timer_id);
#define SYS_TRACE_CREATE2_IN_CBEPM									 77
#define SYS_TRACE_													 78
#define SYS_INTERRUPT_TAG_CREATE									 80 // int sys_interrupt_tag_create(sys_interrupt_tag_t * intrtag, sys_irqoutlet_id_t irq, sys_hw_thread_t hwthread);
#define SYS_INTERRUPT_TAG_DESTROY									 81 // int sys_interrupt_tag_destroy(sys_interrupt_tag_t intrtag);
#define SYS_EVENT_FLAG_CREATE										 82 // int sys_event_flag_create(sys_event_flag_t * id, sys_event_flag_attribute_t * attr, uint64_t init);
#define SYS_EVENT_FLAG_DESTROY										 83 // int sys_event_flag_destroy(sys_event_flag_t id);
#define _SYS_INTERRUPT_THREAD_ESTABLISH								 84 // int sys_interrupt_thread_establish(sys_interrupt_thread_handle_t * ih, sys_interrupt_tag_t intrtag, uint64_t intrthread, uint64_t arg1, uint64_t arg2);
#define SYS_EVENT_FLAG_WAIT											 85 // int sys_event_flag_wait(sys_event_flag_t id, uint64_t bitptn, uint32_t mode, uint64_t * result, usecond_t timeout);
#define SYS_EVENT_FLAG_TRYWAIT										 86 // int sys_event_flag_trywait(sys_event_flag_t id, uint64_t bitptn, uint32_t mode, uint64_t * result);
#define SYS_EVENT_FLAG_SET											 87 // int sys_event_flag_set(sys_event_flag_t id, uint64_t bitptn);
#define SYS_INTERRUPT_THREAD_EOI									 88 // void sys_interrupt_thread_eoi(void);
#define _SYS_INTERRUPT_THREAD_DISESTABLISH							 89 // int sys_interrupt_thread_disestablish(sys_interrupt_thread_handle_t ih);
#define SYS_SEMAPHORE_CREATE										 90
#define SYS_SEMAPHORE_DESTROY										 91
#define SYS_SEMAPHORE_WAIT											 92
#define SYS_SEMAPHORE_TRYWAIT										 93
#define SYS_SEMAPHORE_POST											 94
#define SYS_LWMUTEX_CREATE											 95
#define SYS_LWMUTEX_DESTROY											 96
#define SYS_LWMUTEX_LOCK											 97
#define SYS_LWMUTEX_UNLOCK											 98
#define SYS_LWMUTEX_TRYLOCK											 99
#define SYS_MUTEX_CREATE											100
#define SYS_MUTEX_DESTROY											101
#define SYS_MUTEX_LOCK												102
#define SYS_MUTEX_TRYLOCK											103
#define SYS_MUTEX_UNLOCK											104
#define SYS_COND_CREATE												105
#define SYS_COND_DESTROY											106
#define SYS_COND_WAIT												107
#define SYS_COND_SIGNAL												108
#define SYS_COND_SIGNAL_ALL											109
#define SYS_COND_SIGNAL_TO											110
#define SYS_LWCOND_CREATE											111
#define SYS_LWCOND_DESTROY											112
#define SYS_LWCOND_QUEUE_WAIT										113
#define SYS_SEMAPHORE_GET_VALUE										114
#define sys_lwcond_signal											115
#define sys_lwcond_signal_all										116
#define sys_lwmutex_unlock2											117
#define SYS_EVENT_FLAG_CLEAR										118
#define SYS_TIME_GET_RTC											119
#define SYS_RWLOCK_CREATE											120
#define SYS_RWLOCK_DESTROY											121
#define SYS_RWLOCK_RLOCK											122
#define SYS_RWLOCK_TRYRLOCK											123
#define SYS_RWLOCK_RUNLOCK											124
#define SYS_RWLOCK_WLOCK											125
#define SYS_RWLOCK_TRYWLOCK											126
#define SYS_RWLOCK_WUNLOCK											127
#define SYS_EVENT_QUEUE_CREATE										128
#define SYS_EVENT_QUEUE_DESTROY										129
#define SYS_EVENT_QUEUE_RECEIVE										130
#define SYS_EVENT_QUEUE_TRYRECEIVE									131
#define SYS_EVENT_FLAG_CANCEL										132
#define SYS_EVENT_QUEUE_DRAIN										133
#define SYS_EVENT_PORT_CREATE										134
#define SYS_EVENT_PORT_DESTROY										135
#define SYS_EVENT_PORT_CONNECT_LOCAL								136
#define SYS_EVENT_PORT_DISCONNECT									137
#define SYS_EVENT_PORT_SEND											138
#define SYS_EVENT_FLAG_GET											139
#define SYS_EVENT_PORT_CONNECT_IPC									140
#define SYS_TIMER_USLEEP											141
#define SYS_TIMER_SLEEP												142
#define SYS_TIME_SET_TIMEZONE										143
#define SYS_TIME_GET_TIMEZONE										144
#define SYS_TIME_GET_CURRENT_TIME									145
#define SYS_TIME_GET_TIMEBASE_FREQUENCY								147
#define _SYS_RWLOCK_TRYWLOCK										148
#define SYS_RAW_SPU_CREATE_INTERRUPT_TAG							150
#define SYS_RAW_SPU_SET_INT_MASK									151
#define SYS_RAW_SPU_GET_INT_MASK									152
#define SYS_RAW_SPU_SET_INT_STAT									153
#define SYS_RAW_SPU_GET_INT_STAT									154
#define SYS_SPU_IMAGE_GET_INFORMATION								155
#define SYS_SPU_IMAGE_OPEN											156
#define sys_spu_image_import										157
#define sys_spu_image_close											158
#define sys_raw_spu_load											159
#define SYS_RAW_SPU_CREATE											160
#define SYS_RAW_SPU_DESTROY											161
#define SYS_RAW_SPU_READ_PUINT_MB									163
#define SYS_SPU_THREAD_GET_EXIT_STATUS								165
#define SYS_SPU_THREAD_SET_ARGUMENT									166
#define SYS_SPU_THREAD_GROUP_START_ON_EXIT							167
#define SYS_SPU_INITIALIZE											169
#define SYS_SPU_THREAD_GROUP_CREATE									170
#define SYS_SPU_THREAD_GROUP_DESTROY								171
#define SYS_SPU_THREAD_INITIALIZE									172
#define SYS_SPU_THREAD_GROUP_START									173
#define SYS_SPU_THREAD_GROUP_SUSPEND								174
#define SYS_SPU_THREAD_GROUP_RESUME									175
#define SYS_SPU_THREAD_GROUP_YIELD									176
#define SYS_SPU_THREAD_GROUP_TERMINATE								177
#define SYS_SPU_THREAD_GROUP_JOIN									178
#define SYS_SPU_THREAD_GROUP_SET_PRIORITY							179
#define SYS_SPU_THREAD_GROUP_GET_PRIORITY							180
#define SYS_SPU_THREAD_WRITE_LS										181
#define SYS_SPU_THREAD_READ_LS										182
//#define SYS_SPU_THREAD_ENQUEUE_DMA								183
#define SYS_SPU_THREAD_WRITE_SNR									184
#define SYS_SPU_THREAD_GROUP_CONNECT_EVENT							185
#define SYS_SPU_THREAD_GROUP_DISCONNECT_EVENT						186
#define SYS_SPU_THREAD_SET_SPU_CFG									187
#define SYS_SPU_THREAD_GET_SPU_CFG									188
//#define SYS_SPU_THREAD_READ_PU_MB									189
#define SYS_SPU_THREAD_WRITE_SPU_MB									190
#define SYS_SPU_THREAD_CONNECT_EVENT								191
#define SYS_SPU_THREAD_DISCONNECT_EVENT								192
#define SYS_SPU_THREAD_BIND_QUEUE									193
#define SYS_SPU_THREAD_UNBIND_QUEUE									194
#define SYS_RAW_SPU_SET_SPU_CFG										196
#define SYS_RAW_SPU_GET_SPU_CFG										197
#define SYS_SPU_THREAD_RECOVER_PAGE_FAULT							198
#define SYS_RAW_SPU_RECOVER_PAGE_FAULT								199
//#define (console_putc)											200
//#define (console_getc)											201
//#define (event_create_port)										202
//#define (event_send_locally)										203
//#define (sys_pseudo_fs_read)										209
//#define (sys_pseudo_fs_write)										210
//#define (sys_pseudo_fs_append)									211
//#define (start_debug)												212
//#define (console_write)											213
//#define (sys_pseudo_fs_get_file_size)								214
#define sys_dbg_mat_set_condition									215	// (logical_console_open) int sys_dbg_mat_set_condition(sys_addr_t,int)
#define sys_dbg_mat_get_condition									216	// (logical_console_close) int sys_dbg_mat_get_condition(sys_addr_t,int*)
//#define (logical_console_getc)									217
//#define (logical_console_putc)									218
//#define (logical_console_flush)									219
//#define (get_logical_partition_id)								226
#define SYS_ISOLATED_SPU_CREATE										230	// int sys_isolated_spu_create(sys_raw_spu_t *id, uint8_t *source_spe, in?: args?,0,0,0)
#define SYS_ISOLATED_SPU_DESTROY									231	// int sys_isolated_spu_destroy(sys_raw_spu_t id)
#define SYS_ISOLATED_SPU_START										232	// int sys_isolated_spu_start(sys_raw_spu_t id)
#define SYS_ISOLATED_SPU_CREATE_INTERRUPT_TAG						233	// int sys_isolated_spu_create_interrupt_tag(sys_raw_spu_t id, uint32_t class_id, uint32_t hwthread, sys_interrupt_tag_t *intrtag)
#define SYS_ISOLATED_SPU_SET_INT_MASK								234	// int sys_isolated_spu_set_int_mask(sys_raw_spu_t id, uint32_t class_id, uint64_t mask)
#define SYS_ISOLATED_SPU_GET_INT_MASK								235	// int sys_isolated_spu_get_int_mask(sys_raw_spu_t id, uint32_t class_id, uint64_t *mask)
#define SYS_ISOLATED_SPU_SET_INT_STAT								236	// int sys_isolated_spu_set_int_stat(sys_raw_spu_t id, uint32_t class_id, uint64_t stat)
#define SYS_ISOLATED_SPU_GET_INT_STAT								237	// int sys_isolated_spu_get_int_stat(sys_raw_spu_t id, uint32_t class_id, uint64_t * stat)
#define SYS_ISOLATED_SPU_SET_SPU_CFG								238	// int sys_isolated_spu_set_spu_cfg(sys_spu_thread_t id, uint64_t value)
#define SYS_ISOLATED_SPU_GET_SPU_CFG								239	// int sys_isolated_spu_get_spu_cfg(sys_spu_thread_t id, uint64_t * value)
#define SYS_ISOLATED_SPU_READ_PUINT_MB								240	// 	int sys_isolated_spu_read_puint_mb(sys_raw_spu_t id, uint32_t * value)
#define SYS_SPU_THREAD_GROUP_SYSTEM_SET_NEXT_GROUP					244	// 	int sys_spu_thread_group_system_set_next_group(void)
#define SYS_SPU_THREAD_GROUP_SYSTEM_UNSET_NEXT_GROUP				245	// int sys_spu_thread_group_system_unset_next_group(void)
#define SYS_SPU_THREAD_GROUP_SYSTEM_SET_SWITCH_GROUP				246	// int sys_spu_thread_group_system_set_switch_group(void)
#define SYS_SPU_THREAD_GROUP_SYSTEM_UNSET_SWITCH_GROUP				247	// 	int sys_spu_thread_group_system_unset_switch_group(void)
//#define sys_spu_thread_group....									248	// 5 Params: sys_spu_thread_group_t group,.....
//#define sys_spu_thread_group....									249
#define SYS_SPU_THREAD_GROUP_SET_COOPERATIVE_VICTIMS				250
#define SYS_SPU_THREAD_GROUP_CONNECT_EVENT_ALL_THREADS				251
#define SYS_SPU_THREAD_GROUP_DISCONNECT_EVENT_ALL_THREADS			252
#define SYS_SPU_THREAD_GROUP										253
#define SYS_SPU_THREAD_GROUP_LOG									254
#define SYS_SPU_IMAGE_OPEN_BY_FD									260
//#define SYS_PSEUDO_FS_TRUNCATE									295
//#define SYS_PSEUDO_FS_GET_DENTS									296
#define SYS_VM_MEMORY_MAP											300 // int sys_vm_memory_map(size_t vsize, size_t psize, sys_memory_container_t container, uint64_t flag, uint64_t policy, sys_addr_t * addr);
#define SYS_VM_UNMAP												301 // int sys_vm_unmap(sys_addr_t addr);
#define SYS_VM_APPEND_MEMORY										302 // int sys_vm_append_memory(sys_addr_t addr, size_t size);
#define SYS_VM_RETURN_MEMORY										303 // int sys_vm_return_memory(sys_addr_t addr, size_t size);
#define SYS_VM_LOCK													304 // int sys_vm_lock(sys_addr_t addr, size_t size);
#define SYS_VM_UNLOCK												305 // int sys_vm_unlock(sys_addr_t addr, size_t size);
#define SYS_VM_TOUCH												306 // int sys_vm_touch(sys_addr_t addr, size_t size);
#define SYS_VM_FLUSH												307 // int sys_vm_flush(sys_addr_t addr, size_t size);
#define SYS_VM_INVALIDATE											308 // int sys_vm_invalidate(sys_addr_t addr, size_t size);
#define SYS_VM_STORE												309 // int sys_vm_store(sys_addr_t addr, size_t size);
#define SYS_VM_SYNC													310 // int sys_vm_sync(sys_addr_t addr, size_t size);
#define SYS_VM_TEST													311 // int sys_vm_test(sys_addr_t addr, size_t size, uint64_t * result);
#define SYS_VM_GET_STATISTICS										312 // int sys_vm_get_statistics(sys_addr_t addr, sys_vm_statistics_t * stat);
#define DIFF SYS_VM_MEMORY_MAP										313 // same Params (size_t vsize, size_t psize, sys_memory_container_t container, uint64_t flag, uint64_t policy, sys_addr_t * addr); apperently maps different vm memory area
//#define															314 // 2 Params
//#define															315 // 1 Params
#define SYS_MEMORY_CONTAINER_CREATE									324 // int sys_memory_container_create(sys_memory_container_t * cid, size_t yield_size);
#define SYS_MEMORY_CONTAINER_DESTROY								325 // int sys_memory_container_destroy(sys_memory_container_t cid);
#define SYS_MMAPPER_ALLOCATE_FIXED_ADDRESS							326 // int sys_mmapper_allocate_fixed_address(void);
#define SYS_MMAPPER_ENABLE_PAGE_FAULT_NOTIFICATION					327 // int sys_mmapper_enable_page_fault_notification(sys_addr_t start_addr, sys_event_queue_t queue_id);
#define SYS_MMAPPER_ALLOCATE_SHARED_MEMORY_EXT						328 // int sys_mmapper_allocate_shared_memory_ext(u64 shmem_key, u32 size, u64 pageSizeFlags, u32 memory_container_id, void *entries, u32 entry_count, u32 *mem_id)
#define SYS_MMAPPER_FREE_SHARED_MEMORY								329 // int sys_mmapper_free_shared_memory(sys_addr_t start_addr);
#define SYS_MMAPPER_ALLOCATE_ADDRESS								330 // int sys_mmapper_allocate_address(size_t size, uint64_t flags, size_t alignment, sys_addr_t * alloc_addr);
#define SYS_MMAPPER_FREE_ADDRESS									331 // int sys_mmapper_free_address(sys_addr_t start_addr);
#define SYS_MMAPPER_ALLOCATE_SHARED_MEMORY							332 // 4 Params: (uint32_t id? ('UMEM'), size_t size, size_t alignment, sys_memory_t * mem_id)
#define SYS_MMAPPER_SET_SHARED_MEMORY_FLAG							333 // int sys_mmapper_set_shared_memory_flag(sys_addr_t, flags) ?;
#define SYS_MMAPPER_MAP_SHARED_MEMORY								334 // 3 Params: (sys_addr_t start_addr, sys_memory_t mem_id, uint64_t flags) ?
#define SYS_MMAPPER_UNMAP_SHARED_MEMORY								335 // 2 Params: (sys_addr_t start_addr,sys_memory_t *mem_id ) ?
#define SYS_MMAPPER_CHANGE_ADDRESS_ACCESS_RIGHT						336 // int sys_mmapper_change_address_access_right(sys_addr_t start_addr, uint64_t flags);
#define SYS_MMAPPER_CHANGE_ADDRESS_ACCESS_RIGHT						336 // int sys_mmapper_change_address_access_right(sys_addr_t start_addr, uint64_t flags);
#define SYS_MMAPPER_SEARCH_AND_MAP									337 // int sys_mmapper_search_and_map(sys_addr_t start_addr, sys_memory_t mem_id, uint64_t flags, sys_addr_t * alloc_addr);
#define SYS_MMAPPER_GET_SHARED_MEMORY_ATTRIBUTE						338 // 2 Params
//#define															339 // 5 Params
//#define															340 // 2 Params
#define _SYS_MEMORY_CONTAINER_CREATE								341 // int _sys_memory_container_create(sys_memory_container_t * cid, size_t yield_size);
#define _SYS_MEMORY_CONTAINER_DESTROY								342 // int _sys_memory_container_destroy(sys_memory_container_t cid);
#define SYS_MEMORY_CONTAINER_GET_SIZE								343 // int sys_memory_container_get_size(sys_memory_info_t * mem_info, sys_memory_container_t cid);
#define SYS_MEMORY_BUDGET_SET										344
//#define															345 // 3 Params, a variation of sys_memory_container_destroy (sys_memory_container_t cid, int, &out)
//#define															346
//#define (sys_mmapper_map_mmio_area)								347
#define SYS_MEMORY_ALLOCATE											348 // int sys_memory_allocate(size_t size, uint64_t flags, sys_addr_t * alloc_addr);
#define SYS_MEMORY_FREE												349 // int sys_memory_free(sys_addr_t start_addr);
#define SYS_MEMORY_ALLOCATE_FROM_CONTAINER							350 // int sys_memory_allocate_from_container(size_t size, sys_memory_container_t container, uint64_t flags, sys_addr_t * alloc_addr);
#define SYS_MEMORY_GET_PAGE_ATTRIBUTE								351 // int sys_memory_get_page_attribute(sys_addr_t addr, sys_page_attr_t * attr);
#define SYS_MEMORY_GET_USER_MEMORY_SIZE								352 // int sys_memory_get_user_memory_size(sys_memory_info_t * mem_info);
#define SYS_MEMORY_GET_USER_MEMORY_STAT								353	// int sys_memory_get_user_memory_stat(out:uint8[0x1C])
//#define															354	// 3 Params
//#define															355	// 2 Param: uint32_t *, uint32_t * (set 0, reset memory stats?)
#define SYS_MEMORY_ALLOCATE_COLORED									356	// 4 Params
//#define															357	// 2 Params
//#define															358	// 5 Params
//#define (sys_mmapper_unmap_mmio_area)								359	// 2 Params
//#define															360	// 7 Params
#define SYS_MEMORY_ALLOCATE_FROM_CONTAINER_COLORED					361	// 5 Params
#define SYS_MMAPPER_ALLOCATE_MEMORY_FROM_CONTAINER					362	// sys_mmapper_allocate_memory_from_container(size_t size, sys_memory_container_t container, uint64_t flags, sys_memory_t *mem_id)
//#define 															363	// 6 Params
//#define 															364
#define SYS_UART_INITIALIZE											367	// syscall(367, void)
#define SYS_UART_RECEIVE											368	// sys_uart_receive(out: uint8_t buffer[SizeToReceive], int SizeToReceive (0x400/0x800), 0/1)
#define SYS_UART_SEND												369	// sys_uart_send(const void *buf, uint64_t size, uint64_t flags)
#define SYS_UART_GET_PARAMS											370	// int sys_uart_get_params(out:buffer[0x10])
#define SYS_GAME_WATCHDOG_START										372	// 1 param: int time(r)
#define SYS_GAME_WATCHDOG_STOP										373	// int sys_game_watchdog_stop(void)
#define SYS_GAME_WATCHDOG_CLEAR										374	// int sys_game_watchdog_clear(void)
#define SYS_GAME_SET_SYSTEM_SW_VERSION								375	// int sys_game_set_system_sw_version(uint64_t version)
#define SYS_GAME_GET_SYSTEM_SW_VERSION								376	// int sys_game_get_system_sw_version(void)
#define SYS_SM_SET_SHOP_MODE										377	// int sys_sm_set_shop_mode(int mode (0/1)) ( HV System Manager access -
#define SYS_SM_GET_EXT_EVENT2										378	// 4 Param, sc378(uint64_t * v1,uint64_t * v2, uint64_t * v3, 0=receive buffer/1=get queuing events), v1==7 -> yesHOT
#define SYS_SM_SHUTDOWN												379	// int sys_sm_shutdown(uint16_t op, const void * lpar_parameter, uint64_t parameter_size ) 0x1100/0x100 = turn off, 0x1200 = Lv2 Hard Reboot,  0x200 = Lv2 Soft Reboot, 0x8201 = load lpar id, 1 0x8202 = load lpar id 2, 0x8204 = load lpar id 3 (PS2_NETEMU)
#define SYS_SM_GET_PARAMS											380	// alias sys_get_system_parameter, 4 Params: uint64_t * unknown1, uint64_t * unknown2, uint64_t * unknown3, uint64_t * bootparam? (more info: #Boot_Parameter)
#define SYS_SM_GET_INTER_LPAR_PARAMETER								381 // 2 Params: syscall(381,uint8_t lpar_parameter[param_size], int param_size (0x600));
#define SYS_SM_INITIALIZE											382 // int syscall(382, void); - prevents ps3 lpar shutdown ?
#define SYS_GAME_GET_TEMPERATURE									383 // int sys_game_get_temperature(0=CELL/1=RSX,uint32_t *temperature) ( HV System Manager access - ServiceID 13 (TEMPERATURE)) 2nd Byte conversion: r.shift (second_byte * 0x64 ) by 8 Example: 195 = 0xC3 -> 0xC3 * 0x64 -> 0x4C2C ->> shift -> 0x4C -> XX.76°C
#define SYS_SM_GET_TZPB												384 // 1 Param: syscall(384,uint64_t *tzpb); (uint8_t [0x20]) Get TimeZone Presence
#define SYS_SM_REQUEST_LED											385 // int sys_sm_request_led( int led_id(1=power,2=status or 3=disk), out:uint8_t led_action[1] ) HV System Manager access - ServiceID 17
#define SYS_SM_CONTROL_LED											386 // int sys_sm_control_led(uint8_t led_id, uint8_t led_action)	led_id = 0,1 (STATUS),2 (POWER)(red, green, red+green combined: looks like yellow);	led_action = 0,1,2,3 (off,on,blink fast, blink slow)
#define SYS_SM_GET_SYSTEM_INFO										387 // syscall(387, uint8_t platform_info[0x18]) / OS Version, Revision, System Software Version?
#define SYS_SM_RING_BUZZER_TOO										388 // 2 Params,HV System Manager access - ServiceID 21 (RING_BUZZER)
#define SYS_SM_SET_FAN_POLICY										389 // int sys_sm_set_fan_policy (in:uint8, in:uint8, in:uint8)
#define SYS_SM_REQUEST_ERROR_LOG									390 // 4 Params, uint8_t offset (0-0x20), uint8_t *, uint32_t *, uint32_t *
#define SYS_SM_REQUEST_BE_COUNT										391 // 4 Params: uint8_t *, uint32_t* total_time_in_seconds, uint32_t* power_on_counter, uint32_t* power_off_counter
#define SYS_SM_RING_BUZZER											392 // 3 Params: PacketID=0x1004, field2, field4
#define SYS_GET_HW_CONFIG											393	// gets hardware configuration: syscall(393,uint8_t * res, uint64_t * hw_config)
#define SYS_SM_REQUEST_SCVERSION									394 // uint8_t SoftID[8],old_PatchID[8],new_PatchID[8]; lv2syscall3(394, (uint64_t)SoftID, (uint64_t)old_PatchID, (uint64_t)new_PatchID);
#define SYS_SM_REQUEST_SYSTEM_EVENT_LOG								395 // 	int sys_sm_request_system_event_log(int offset(0 - 5),uint64_t *out,uint64_t *out,uint64_t *out,uint8_t buf[0x20], int flag ), 6 Params, HV System Manager access - ServiceID 32 (REQUEST_SYSTEM_EVENT_LOG)
#define SYS_SM_SET_RTC_ALARM										396 // int sys_sm_set_rtc_alarm(CellRtcTick *pTick), HV System Manager access - ServiceID 34+38 (RTC_ALARM)
#define SYS_SM_GET_RTC_ALARM										397 // 1 Param, HV System Manager access - ServiceID 36
#define SYS_CONSOLE_WRITE											398 // int sys_console_write(const char *s, unsigned int len)(lv2,lv1::console::write_async
//#define 															399 // (sys_kernel_test)
//#define 															400 // int sys_request_system_event_log(int offset(0 - 5),uint64_t *out, int flag ) , HV System Manager access - ServiceID 32 (REQUEST_SYSTEM_EVENT_LOG)
//#define 															401 // 2 Params: uint64_t param,uint8_t * st (status?/state?)
#define SYS_TTY_READ												402 // int sys_tty_read(unsigned int ch, void *buf, unsigned int len, unsigned int *preadlen);
#define SYS_TTY_WRITE												403 // int sys_tty_write(unsigned int ch, const void *buf, unsigned int len, unsigned int *pwritelen);
//#define															404 // 2 Params: uint64_t * param, uint8_t * st
//#define															405 // 2 Params: uint16_t * comp?, uint8_t * st (status?/state?)
//#define															406 // 2 Params: uint32_t comp? ,uint8_t * st	comp? = 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x100
//#define															407 // 1 Param: uint8_t * st
#define sys_sm_get_tzpb too											408 // 1 Param: out:uint8_t [0x20] same as 384 just requires PM
#define sys_sm_get_fan_policy										409 // int sys_sm_get_fan_policy(uint8_t id, uint8_t *st (status? state?), uint8_t *policy (mode), uint8_t * mode (speed), uint8_t *duty)
#define sys_game_board_storage_read									410 // 2 Params,out:uint8_t[0x10], uint8_t[1], HV System Manager access - ServiceID 54
#define sys_game_board_storage_write								411 // 2 Params,in:uint8_t[0x10],uint8_t[1], HV System Manager access - ServiceID 52
#define sys_game_get_rtc_status										412 //
//#define															413 // 3 Params, HV System Manager access - ServiceID 56: out:uint8_t[1],out:uint8_t[1],out:uint8_t[1]
//#define															414 // 3 Params,in:packetid ,in:uint8_t[0x20],out:uint8_t[1], HV System Manager access - ServiceID 58
//#define															415 // 3 Params,in:packetid,out:uint8_t[0x20],out:uint8_t[1], HV System Manager access - ServiceID 60
#define SYS_OVERLAY_LOAD_MODULE										450 // int sys_overlay_load_module(sys_overlay_t * ovlmid, const char *path, uint64_t flags, sys_addr_t * entry)
#define SYS_OVERLAY_UNLOAD_MODULE									451
#define SYS_OVERLAY_GET_MODULE_LIST									452
#define SYS_OVERLAY_GET_MODULE_INFO									453
#define SYS_OVERLAY_LOAD_MODULE_BY_FD								454
#define SYS_OVERLAY_GET_MODULE_INFO2								455
#define SYS_OVERLAY_GET_SDK_VERSION									456
#define _SYS_PRX_GET_MODULE_ID_BY_ADDRESS							461
#define _SYS_PRX_LOAD_MODULE_BY_FD									463
#define _SYS_PRX_LOAD_MODULE_ON_MEMCONTAINER_BY_FD					464
#define _SYS_PRX_LOAD_MODULE_LIST									465
#define _SYS_PRX_LOAD_MODULE_LIST_ON_MEMCONTAINER					466
#define SYS_PRX_GET_PPU_GUID										467
#define _SYS_PRX_LOAD_MODULE										480
#define _SYS_PRX_START_MODULE										481
#define _SYS_PRX_STOP_MODULE										482
#define _SYS_PRX_UNLOAD_MODULE										483
#define _SYS_PRX_REGISTER_MODULE									484
#define _SYS_PRX_QUERY_MODULE										485
#define _SYS_PRX_REGISTER_LIBRARY									486
#define _SYS_PRX_UNREGISTER_LIBRARY									487 // int sys_prx_unregister_library(void* library) // only returns 0
#define _SYS_PRX_LINK_LIBRARY										488 // int sys_prx_link_library(void) // only returns 0
#define _SYS_PRX_UNLINK_LIBRARY										489 // int sys_prx_unlink_library(void) // only returns 0
#define _SYS_PRX_QUERY_LIBRARY										490 // int sys_prx_query_library(void) // only returns 0
#define SYS_PRX_DBG_GET_MODULE_LIST									492 // 4 Params:
#define SYS_PRX_DBG_GET_MODULE_INFO									493 // int sys_prx_dbg_get_module_info(sys_pid_t pid, sys_prx_id_t id, sys_prx_dbg_module_info* info)
#define _SYS_PRX_GET_MODULE_LIST									494 // int sys_prx_get_module_list(sys_prx_flags_t flags, sys_prx_get_module_list_t *pInfo);
#define _SYS_PRX_GET_MODULE_INFO									495 // int sys_prx_get_module_info(sys_prx_id_t id, sys_prx_flags_t flags, sys_prx_module_info_t *pInfo)
#define _SYS_PRX_GET_MODULE_ID_BY_NAME								496 // sys_prx_id_t sys_prx_get_module_id_by_name(const char* name, sys_prx_flags_t flags, sys_prx_get_module_id_by_name_option_t *pOpt)
#define _SYS_PRX_LOAD_MODULE_ON_MEMCONTAINER						497 // sys_prx_id_t sys_prx_load_module_on_memcontainer(const char* path, sys_memory_container_t mem_container, sys_prx_flags_t flags, sys_prx_load_module_option_t pOpt)
#define _SYS_PRX_START												498 // int sys_prx_start (void) // only returns 0
#define _SYS_PRX_STOP												499 // int sys_prx_stop(void)
#define SYS_HID_MANAGER_OPEN										500 // 2 Params
#define SYS_HID_MANAGER_CLOSE										501 // 1 Param: uint32_t port_no
#define SYS_HID_MANAGER_READ										502 // 4 Params: uint32_t port_no,uint32_t packet_id, uint8_t[size], uint32_t size
#define SYS_HID_MANAGER_IOCTL										503 // 4 Params: uint32_t port_no,uint32_t packet_id, uint8_t[size], uint32_t size
#define SYS_HID_MANAGER_MAP_LOGICAL_ID_TO_PORT_ID					504 // param 1: device_type, 1 = pad, 2 = kb, 3 = mouseint sc(int device_type, int device_no, int port_no)
#define SYS_HID_MANAGER_UNMAP_LOGICAL_ID_TO_PORT_ID					505 // int sc(int device_type, int device_no, int port_no)
#define SYS_HID_MANAGER_ADD_HOT_KEY_OBSERVER						506 // 2 Params
#define SYS_HID_MANAGER_REMOVE_HOT_KEY_OBSERVER						507 // 2 Params
#define SYS_HID_MANAGER_GRAB_FOCUS									508 // 1 Param: sys_pid_t pid (for example current pid)
#define SYS_HID_MANAGER_RELEASE_FOCUS								509 // 1 Param
#define SYS_HID_MANAGER_CHECK_FOCUS									510 // int syscall(510, void);
#define SYS_HID_MANAGER_SET_MASTER_PROCESS							511 // 1 Param
//#define															512 // 1 Param : int syscall(512,sys_pid_t pid), simple root-flag check?;
//#define SYS_HID_MANAGER_...										513 // 4 Params
//#define SYS_HID_MANAGER_...										514 // 3 Params
#define SYS_CONFIG_OPEN												516 // 2 Params : (sys_event_queue_t * equeue_id, uint64_t *conf_id (out))
#define SYS_CONFIG_CLOSE											517 // sys_config_close(sys_event_queue_t * equeue_id);
#define SYS_CONFIG_GET_SERVICE_EVENT								518 // 4 Params:
#define SYS_CONFIG_ADD_SERVICE_LISTENER								519 // 6 Params (u32 conf_id, ?, ?, ?, ?, ?)
#define SYS_CONFIG_REMOVE_SERVICE_LISTENER							520 // 2 Params
#define SYS_CONFIG_REGISTER_SERVICE									521 // 7 Params
#define SYS_CONFIG_UNREGISTER_SERVICE								522 // 2 Params
#define SYS_CONFIG_IO_EVENT											523 //
#define SYS_CONFIG_REGISTER_IO_ERROR_LISTENER						524 //
#define SYS_CONFIG_UNREGISTER_IO_ERROR_LISTENER						525 //
#define SYS_USBD_INITIALIZE											530 // 1 Param, out: *uint32_t
#define SYS_USBD_FINALIZE											531 // 1 Param, in: handle/id
#define SYS_USBD_GET_DEVICE_LIST									532 // 3 Params
#define SYS_USBD_GET_DESCRIPTOR_SIZE								533 // 2 Params
#define SYS_USBD_GET_DESCRIPTOR										534 // 4 Params
#define SYS_USBD_REGISTER_LDD										535 // 3 Params
#define SYS_USBD_UNREGISTER_LDD										536 // 3 Params
#define SYS_USBD_OPEN_PIPE											537 // 7 Params
#define SYS_USBD_OPEN_DEFAULT_PIPE									538 // 2 Params
#define SYS_USBD_CLOSE_PIPE											539 // 2 Params
#define SYS_USBD_RECEIVE_EVENT										540 // 4 Params
#define SYS_USBD_DETECT_EVENT										541 // void
#define SYS_USBD_ATTACH												542 // 4 Params
#define SYS_USBD_TRANSFER_DATA										543 // 6 Params
#define SYS_USBD_ISOCHRONOUS_TRANSFER_DATA							544 // 3 Params
#define SYS_USBD_GET_TRANSFER_STATUS								545 // 5 Params
#define SYS_USBD_GET_ISOCHRONOUS_TRANSFER_STATUS					546 // 5 Params
#define SYS_USBD_GET_DEVICE_LOCATION								547 // 3 Params
#define SYS_USBD_SEND_EVENT											548 // 2 Params
#define SYS_USBD_EVENT_PORT_SEND									549 // int sys_usbd_event_port_send(uint64_t usb_id?, uint64_t data1, uint64_t data2, uint64_t data3);
#define SYS_USBD_ALLOCATE_MEMORY									550 // 3 Params
#define SYS_USBD_FREE_MEMORY										551 // 2 Params
#define SYS_USBD_ENABLE_WAKE_ON										552 // 1 Param
//#define															553 // void
//#define															554 // void
//#define															555 // void
#define SYS_USBD_GET_DEVICE_SPEED									556 // 3 Params, , , out:uint8_t[1]
//#define															557 // 5 Params
//#define															558 // 3 Params
#define SYS_USBD_REGISTER_EXTRA_LDD									559 // 6 Params
#define SYS_USBMASS_IOCTL											560 //
//#define															561 // 1 Param: out:uint8_t [4] (cf/sd/mmc/sm/ms flag availability from hw config)
//#define															562 // gets MultiCardReader Firmware Version: syscall(0x232, out:uint8_t [2])
//#define															563 //
//#define															564 //
//#define															565 //
//#define															566 //
//#define															567 //
//#define															568 //
//#define															569 //
#define _YS_PAD_LDD_REGISTER_CONTROLLER								570 //
#define YS_PAD_LDD_UNREGISTER_CONTROLLER							571 // int sys_pad_ldd_unregister_controller ( int32_t handle)
#define YS_PAD_LDD_DATA_INSERT										572 // int sys_pad_ldd_data_insert (int32_t handle, cellpaddata* data /* uint8_t[0x84] */)
#define YS_PAD_DBG_LDD_SET_DATA_INSERT_MODE							573 // int sys_pad_dbg_ldd_set_data_insert_mode ( int32_t handle, 0x100, uint32_t* mode , 4)
#define YS_PAD_LDD_REGISTER_CONTROLLER								574 // int sys_pad_ldd_register_controller/sys_pad_dbg_ldd_register_controller ( uint8_t[0x114] /* struct */, int32_t* out, 5, uint32_t device_capability<<1)
#define YS_PAD_LDD_GET_PORT_NO										575 // int sys_pad_ldd_get_port_no (int32_t handle)
#define YS_PAD_MANAGER												577 // int sys_pad_manager_.... (int8_t device_number?)
//#define															578 //
#define YS_BLUETOOTH_AUD_SERIAL_UNK1								579 // (0x243,0,unk1*,aud_serial*,unk2*,unk3*,unk4*)	0xD0044D40 00 00 00 00 / 0xD0044D44 00 82 8E 18 --> 00 7D 39 A0 --> 0x007D39A0 5F 61 75 64 5F 53 45 52 49 41 4C 00 00 00 00 00 _aud_SERIAL..... / 0xD0044D48 00 00 00 00 / 0xD0044D4C 00 00 00 00
//#define															580 //
//#define															581 //
//#define															582 //
#define YS_BT_READ_FIRMWARE_VERSION									583 // gets Bluetooth Firmware Version: syscall(0x247, out:uint8_t [2])
#define YS_BT_COMPLETE_WAKE_ON_HOST									584 //
#define YS_BT_DISABLE_BLUETOOTH										585 //
#define YS_BT_ENABLE_BLUETOOTH										586 // return 0x80010003
#define YS_BT_BCCMD													587 //
#define YS_BT_READ_HQ												588 // return 0x80010003
#define YS_BT_HID_GET_REMOTE_STATUS									589 // return 0x80010003
#define YS_BT_REGISTER_CONTROLLER									590 // bt_set_device_info()
#define YS_BT_CLEAR_REGISTERED_CONTOLLER							591 // return 0
#define YS_BT_CONNECT_ACCEPT_CONTROLLER								592 // return 0
#define YS_BT_GET_LOCAL_BDADDRESS									593 // getting bluetooth address
#define YS_BT_HID_GET_DATA											594 // return 0x80010003
#define YS_BT_HID_SET_REPORT										595 // return 0x80010003
#define YS_BT_SCHED_LOG												596 // return 0x80010003
#define YS_BT_CANCEL_CONNECT_ACCEPT_CONTROLLER						597 // bt_cancel_connect_accept_controller(),deprecated
//#define															598 // 0 Param
//#define															599 // 2 Params: out:uint8_t[2], out:uint8_t[2]
#define SYS_STORAGE_OPEN											600
#define SYS_STORAGE_CLOSE											601
#define SYS_STORAGE_READ											602
#define SYS_STORAGE_WRITE											603
#define SYS_STORAGE_SEND_DEVICE_COMMAND								604
#define SYS_STORAGE_ASYNC_CONFIGURE									605
#define SYS_STORAGE_ASYNC_READ										606
#define SYS_STORAGE_ASYNC_WRITE										607
#define SYS_STORAGE_ASYNC_CANCEL									608
#define SYS_STORAGE_GET_DEVICE_INFO									609
#define SYS_STORAGE_GET_DEVICE_CONFIG								610
#define SYS_STORAGE_REPORT_DEVICES									611
#define SYS_STORAGE_CONFIGURE_MEDIUM_EVENT							612
#define SYS_STORAGE_SET_MEDIUM_POLLING_INTERVAL						613
#define SYS_STORAGE_CREATE_REGION									614
#define SYS_STORAGE_DELETE_REGION									615
#define SYS_STORAGE_EXECUTE_DEVICE_COMMAND							616
#define SYS_STORAGE_GET_REGION_ACL									617
#define SYS_STORAGE_SET_REGION_ACL									618
#define SYS_STORAGE_ASYNC_SEND_DEVICE_COMMAND						619
#define SYS_IO_BUFFER_CREATE										624
#define SYS_IO_BUFFER_DESTROY										625
#define SYS_IO_BUFFER_ALLOCATE										626
#define SYS_IO_BUFFER_FREE											627
#define SYS_GPIO_SET												630
#define SYS_GPIO_GET												631
#define SYS_FSW_CONNECT_EVENT										633
#define SYS_FSW_DISCONNECT_EVENT									634
//#define															635 // sys_btsetting_if?	2 Params: uint64_t packet_id (0=init,1=finalize,....27) , uint8_t buffer
//#define															636 // (BT Database Lookup)
//#define															637 // BT dev list related, syscall(0x27d, out:uint8_t[0x100])
//#define															638 // BT related, 3 Params: packet_id (<7), input, output?
//#define															639 // "deprecated!" (seems Sony doesnt want/like USB Bluetooth Audio transmitter/receiver)
#define SYS_USBBTAUDIO_INITIALIZE									640 // "deprecated!"
#define SYS_USBBTAUDIO_FINALIZE										641 // "deprecated!"
#define SYS_USBBTAUDIO_DISCOVERY									642 // "deprecated!"
#define SYS_USBBTAUDIO_CANCEL_DISCOVERY								643 // "deprecated!"
#define SYS_USBBTAUDIO_PAIRING										644 // "deprecated!"
#define SYS_USBBTAUDIO_SET_PASSKEY									645 // "deprecated!"
#define SYS_USBBTAUDIO_CONNECT										646 // "deprecated!"
#define SYS_USBBTAUDIO_DISCONNECT									647 // "deprecated!"
//#define															648 // "deprecated!"
//#define															649 // "deprecated!"
#define SYS_RSXAUDIO_INITIALIZE										650 // int sys_rsxaudio_initialize(out:uint8[4])
#define SYS_RSXAUDIO_FINALIZE										651 // 1 Params
#define SYS_RSXAUDIO_IMPORT_SHARED_MEMORY							652 // 2 Params
#define SYS_RSXAUDIO_UNIMPORT_SHARED_MEMORY							653 // 2 Params
#define SYS_RSXAUDIO_CREATE_CONNECTION								654 // 1 Params
#define SYS_RSXAUDIO_CLOSE_CONNECTION								655 // 1 Params
#define SYS_RSXAUDIO_PREPARE_PROCESS								656 // 1 Params
#define SYS_RSXAUDIO_START_PROCESS									657 // 1 Params
#define SYS_RSXAUDIO_STOP_PROCESS									658 // 1 Params
#define SYS_RSXAUDIO_												659 // 3 Params
#define SYS_RSX_DEVICE_OPEN											666
#define SYS_RSX_DEVICE_CLOSE										667
#define SYS_RSX_MEMORY_ALLOCATE										668
#define SYS_RSX_MEMORY_FREE											669
#define SYS_RSX_CONTEXT_ALLOCATE									670
#define SYS_RSX_CONTEXT_FREE										671
#define SYS_RSX_CONTEXT_IOMAP										672
#define SYS_RSX_CONTEXT_IOUNMAP										673
#define SYS_RSX_CONTEXT_ATTRIBUTE									674
#define SYS_RSX_DEVICE_MAP											675
#define SYS_RSX_DEVICE_UNMAP										676
#define SYS_RSX_ATTRIBUTE											677
#define SYS_BDEMU_SEND_COMMAND										699
#define SYS_NET_ACCEPT												700	/* Added */
#define SYS_NET_BIND												701	/* Added */
#define SYS_NET_CONNECT												702	/* Added */
#define SYS_NET_LISTEN												706	/* Added */
#define SYS_NET_RECVFROM											707	/* Added */
#define SYS_NET_SENDTO												710	/* Added */
#define SYS_NET_SHUTDOWN											712	/* Added */
#define SYS_NET_SOCKET												713	/* Added */
#define SYS_NET_CLOSE												714	/* Added */
#define SYS_NET_BNET_POLL											715
#define SYS_NET_BNET_SELECT											716
#define SYS_NET_OPEN_DUMP											717	// int sys_net_open_dump ( int len, int flags )
#define SYS_NET_READ_DUMP											718	// int sys_net_read_dump ( int id, void *buf, int len, int *pflags )
#define SYS_NET_CLOSE_DUMP											719	// int sys_net_close_dump ( int id, int *pflags )
#define SYS_NET_WRITE_DUMP											720	// int sys_net_write_dump ( char *buf )
#define SYS_NET_ABORT												721	// int sys_net_abort (packet id <5: 0=abort socket,1=abort resolver ), sys_net_thread_id_t tid/int socket_descriptor, int flags )
#define SYS_NET_INFOCTL												722
#define SYS_NET_CONTROL												723
#define SYS_NET_BNET_IOCTL											724
#define SYS_NET_BNET_SYSCTL											725
#define SYS_NET_EURUS_POST_COMMAND									726	// int sys_net_eurus_post_command(uint16_t cmd, uint8_t *cmdbuf, uint64_t cmdbuf_size) Hypervisor_Reverse_Engineering#Commands_2 Commands
#define SYS_FS_TEST													800 /* int sys_fs_test(packetid < 7 (6 tests) ,0,*deviceid,4,uint8* out[0x420],0x420) */
#define SYS_CELLFSOPEN												801	/* CellFsErrno sys_fs_open(const char *path, int flags, int *fd, uint64_t mode, const void *arg, uint64_t size); */
#define SYS_CELLFSREAD												802	/* CellFsErrno sys_fs_read(int fd, void *buf, uint64_t nbytes, uint64_t *nread); */
#define SYS_CELLFSWRITE												803	/* CellFsErrno sys_fs_write(int fd, const void *buf, uint64_t nbytes, uint64_t *nwrite); */
#define SYS_CELLFSCLOSE												804	/* CellFsErrno sys_fs_close(int fd); */
#define SYS_CELLFSOPENDIR											805	/* CellFsErrno sys_fs_opendir(const char *path, int *fd); */
#define SYS_FS_READDIR												806 /* CellFsErrno sys_fs_readdir(int fd, CellFsDirent *dir, uint64_t *nread); */
#define SYS_FS_CLOSEDIR												807 /* CellFsErrno sys_fs_closedir(int fd); */
#define SYS_CELLFSSTAT												808	/* Added */
#define SYS_CELLFSFSTAT												809	/* CellFsErrno sys_fs_fstat(int fd, CellFsStat *sb); */
#define SYS_FS_LINK													810 /* int sys_fs_link(char const*, char const*) */
#define SYS_CELLFSMKDIR												811	/* CellFsErrno sys_fs_mkdir(const char *path, CellFsMode mode); */
#define SYS_CELLFSRENAME											812 /* CellFsErrno sys_fs_rename(const char *from, const char *to); */
#define SYS_FS_RMDIR												813 /* CellFsErrno sys_fs_rmdir(const char *path); */
#define SYS_CELLFSUNLINK											814	/* CellFsErrno sys_fs_unlink(const char *path); */
#define SYS_CELLFSUTIME												815	/* CellFsErrno sys_fs_utime(const char *path, const CellFsUtimbuf *timep); */
#define SYS_FS_ACCESS												816 /* int sys_fs_access(char cont*, int) */
#define SYS_FS_FCNTL												817 /* int sys_fs_fcntl(int, int, void *, unsigned long) */
#define SYS_CELLFSLSEEK												818	/* CellFsErrno sys_fs_lseek(int fd, int64_t offset, int whence, uint64_t *pos); */
#define SYS_FS_FDATASYNC											819 /* int sys_fs_datasync(int) */
#define SYS_FS_FSYNC												820	// CellFsErrno sys_fs_fsync(int fd);
#define SYS_FS_FGET_BLOCK_SIZE										821	// int sys_fs_fget_block_size(int, unsigned long *, unsigned long *, unsigned long *, int *)
#define SYS_FS_GET_BLOCK_SIZE										822	// int sys_fs_get_block_size(char const*, unsigned long *, unsigned long *, unsigned long *)
#define SYS_FS_ACL_READ												823	// int sys_fs_acl_read(char const*, CellFsAcl *)
#define SYS_FS_ACL_WRITE											824	// int sys_fs_acl_read(char const*, CellFsAcl *)
#define SYS_FS_LSN_GET_CDA_SIZE										825	// int sys_fs_lsn_get_cda_size(int, unsigned long *)
#define SYS_FS_LSN_GET_CDA											826	// int sys_fs_lsn_get_cda(int, CellFsCda *, unsigned long, unsigned long *)
#define SYS_FS_LSN_LOCK												827	// int sys_fs_lsn_lock(int)
#define SYS_FS_LSN_UNLOCK											828	// int sys_fs_lsn_unlock(int)
#define SYS_FS_LSN_READ												829	// int sys_fs_lsn_read(int, CellFsCda const*, unsigned long)
#define SYS_FS_LSN_WRITE											830	// int sys_fs_lsn_write(int, CellFsCda const*, unsigned long)
#define SYS_FS_TRUNCATE												831	// CellFsErrno sys_fs_truncate(const char *path, uint64_t size);
#define SYS_FS_FTRUNCATE											832	// CellFsErrno sys_fs_ftruncate(int fd, uint64_t size);
#define SYS_FS_SYMBOLIC_LINK										833	// int sys_fs_symbolic_link(char const*, char const*)
#define SYS_FS_CHMOD												834	// CellFsErrno sys_fs_chmod(const char *path, CellFsMode mode);
#define SYS_FS_CHOWN												835	// int sys_fs_chown(char const*, int, int)
#define SYS_CELLFSNEWFS												836	// int sys_fs_newfs(char const* deviceName, char const*, int, char const**)
#define SYS_CELLFSMOUNT												837	// int sys_fs_mount(char const* deviceName, char const*, char const*, int, int, int, char const**)
#define SYS_CELLFSUMOUNT											838	// int sys_fs_unmount(char const*, int, int) Parameters: Device Path (e.g. /dev_flash)
#define SYS_FS_SYNC													839	// int sys_fs_sync(const char *dir) Parameter: Device Path (e.g. /dev_hdd0)
#define SYS_FS_DISK_FREE											840	// int sys_fs_disk_free(char const*, unsigned long *, unsigned long *)
#define SYS_FS_GET_MOUNT_INFO_SIZE									841	// int sys_fs_get_mount_info_size(unsigned long *)
#define SYS_FS_GET_MOUNT_INFO										842	// int sys_fs_get_mount_info(CellFsMountInformation *, unsigned long, unsigned long *)
#define SYS_FS_GET_FS_INFO_SIZE										843	// int sys_fs_get_fs_info_size(unsigned long *)
#define SYS_FS_GET_FS_INFO											844	// int sys_fs_get_fs_info(ulong, ulong*, CellFsInfo *)
#define SYS_FS_MAPPED_ALLOCATE										845	// int sys_fs_mapped_allocate(int, unsigned long, void **)
#define SYS_FS_MAPPED_FREE											846	// int sys_fs_mapped_free(int, void *)
#define SYS_FS_TRUNCATE2											847	// int sys_fs_ftruncate2(int fd, uint64_t size);
#define SYSCALL_SYS_SS_GET_CACHE_OF_ANALOG_SUNSET_FLAG				860	// int syscall_sys_ss_get_cache_of_analog_sunset_flag(out:uint8_t[1])
#define SYS_SS_PROTECTED_FILE_DB									861	// gamesave_storage_manager_if(uint32_t packetid (0-0x13), uint8_t buf[0xB8], const char* path, int32_t len, int32_t unk2, int32_t unk3, 0, 0);
#define SYS_SS_VIRTUAL_TRM_MANAGER									862	// vtrm_manager_if (Interface)
#define SYS_SS_UPDATE_MANAGER										863	// update_manager_if (Interface)
#define SYS_SS_SEC_HW_FRAMEWORK										864	// storage_manager_if (Interface) auth psx disc: 0x5004, 1. auth ps3 disc: 0x5007, in/out	buffer of 0x18 bytes
																		// return to normal	: 0x5004, 0x29
#define SYS_SS_RANDOM_NUMBER_GENERATOR								865	// int sys_ss_random_number_generator(id,buffer,size), alias sys_get_random_number
#define SYS_SS_SECURE_RTC											866	// secure_rtc_manager_if (Interface)
#define SYS_SS_APPLIANCE_INFO_MANAGER								867	// aim_manager_if (Interface)
#define SYS_SS_INDIVIDUAL_INFO_MANAGER								868	// indi_info_manager_if (Interface)
#define SYS_SS_FACTORY_DATA_MANAGER									869	// factory_data_manager_if (Interface)
#define SYS_SS_GET_CONSOLE_ID										870	// int sys_ss_get_console_id(uint8_t *buf) //returns IDPS in buf
#define SYS_SS_ACCESS_CONTROL_ENGINE								871	// 3 params 
#define SYS_SS_GET_OPEN_PSID										872 // int sys_ss_get_open_psid(CellSsOpenPSID *ptr) ; typedef struct CellSsOpenPSID { uint64_t high; uint64_t low;}
#define SYS_SS_GET_CACHE_OF_PRODUCT_MODE							873	/* Added */
#define SYS_SS_GET_CACHE_OF_FLASH_EXT_FLAG							874	/* Added */
#define SYS_SS_GET_BOOT_DEVICE										875	/* Added */
#define SYS_SS_DISC_ACCESS_CONTROL									876	// 2 Params: 0x20000(=get_disc_access_control),uint32_t * disc_access / 0x20001(=set_disc_access_control),1
#define SYS_SS_UTOKEN_IF											877 // syscall(877,0x25003=Decrypt or 0x25004 or 0x25005=Encrypt or 0x25006=(copy syscall table to user), uint8_t *token, 0xC50 (size)), user_token_manager_if
#define SYS_SS_AD_SIGN												878	// syscall(878, 0x26001, in_buffer[0x14], out_buffer[0x80])
#define SYS_SS_MEDIA_ID												879	// syscall(879, 0x10001, out_buffer[0x10])
#define SYS_DECI3_OPEN												880
#define SYS_DECI3_CREATE_EVENT_PATH									881
#define SYS_DECI3_CLOSE												882
#define SYS_DECI3_SEND												883
#define SYS_DECI3_RECEIVE											884
#define SYS_DECI3_OPEN2												885
//#define sys_														889
#define SYS_DECI3_INITIALIZE										890
#define SYS_DECI3_TERMINATE											891
#define SYS_DECI3_DEBUG_MODE										892
#define SYS_DECI3_SHOW_STATUS										893
#define SYS_DECI3_ECHO_TEST											894
#define SYS_DECI3_SEND_DCMP_PACKET									895
#define SYS_DECI3_DUMP_CP_REGISTER									896
#define SYS_DECI3_DUMP_CP_BUFFER									897
#define SYS_DECI3_TEST												899
#define SYS_DBG_STOP_PROCESSES										900	// 2 params: sys_pid_t pid, 1
#define SYS_DBG_CONTINUE_PROCESSES									901	//
#define SYS_DBG_STOP_THREADS										902	// 2 params: in/out, len
#define SYS_DBG_CONTINUE_THREADS									903	// 2 params: uint64_t *inbuff, int length(0 or ... or 8)
#define SYS_DBG_READ_PROCESS_MEMORY									904	// int sys_dbg_read_process_memory(sys_pid_t pid, uint64_t process_ea, uint32_t size, void* data)
#define SYS_DBG_WRITE_PROCESS_MEMORY								905	// int sys_dbg_write_process_memory(sys_pid_t pid, uint64_t process_ea, uint32_t size, const void* data)
#define SYS_DBG_READ_THREAD_REGISTER								906	// 3 Params: uint8_t [0x10], uint64_t *, uint8_t[0x10]
#define SYS_DBG_WRITE_THREAD_REGISTER								907	//
#define SYS_DBG_GET_PROCESS_LIST									908	// int sys_dbg_get_process_list(sys_pid_t* pids, uint64_t* max, uint64_t* count)
#define SYS_DBG_GET_THREAD_LIST										909	// int sys_dbg_get_thread_list( sys_pid_t pid, sys_ppu_thread_t* ids, uint64_t* ids_num, uint64_t* all_ids_num)
#define SYS_DBG_GET_THREAD_INFO										910	// 2 Params: uint8_t * [0x10] {type,thread id?}, uint8_t [0x80]
#define SYS_DBG_SPU_THREAD_READ_FROM_LS								911	// 4 Params: spu thread id,, size, uint8_t[size]
#define SYS_DBG_SPU_THREAD_WRITE_TO_LS								912	//
#define SYS_DBG_KILL_PROCESS										913	// int sys_dbg_kill_process(sys_pid_t pid)
#define SYS_DBG_GET_PROCESS_INFO									914	// int sys_dbg_get_process_info(sys_pid_t pid, sys_process_info_t* info)
#define SYS_DBG_SET_RUN_CONTROL_BIT_TO_SPU							915	//
#define SYS_DBG_SPU_THREAD_GET_EXCEPTION_CAUSE						916	//
#define SYS_DBG_CREATE_KERNEL_EVENT_QUEUE							917	//
#define SYS_DBG_READ_KERNEL_EVENT_QUEUE								918	//
#define SYS_DBG_DESTROY_KERNEL_EVENT_QUEUE							919	//
#define SYS_DBG_GET_PROCESS_EVENT_CTRL_FLAG							920	//
#define SYS_DBG_SET_PROCESS_EVENT_CNTL_FLAG							921	//
#define SYS_DBG_GET_SPU_THREAD_GROUP_EVENT_CNTL_FLAG				922	//
#define SYS_DBG_SET_SPU_THREAD_GROUP_EVENT_CNTL_FLAG				923	//
#define SYS_DBG_GET_MODULE_LIST										924	//
#define SYS_DBG_GET_RAW_SPU_LIST									925	//
#define SYS_DBG_INITIALIZE_SCRATCH_EXECUTABLE_AREA					926	//
#define SYS_DBG_TERMINATE_SCRATCH_EXECUTABLE_AREA					927	//
#define SYS_DBG_INITIALIZE_SCRATCH_DATA_AREA						928	//
#define SYS_DBG_TERMINATE_SCRATCH_DATA_AREA							929	//
#define SYS_DBG_GET_USER_MEMORY_STAT								930	//
#define SYS_DBG_GET_SHARED_MEMORY_ATTRIBUTE_LIST					931	//
#define SYS_DBG_GET_MUTEX_LIST										932	//
#define SYS_DBG_GET_MUTEX_INFORMATION								933	// int sys_dbg_get_mutex_information(sys_pid_t id, sys_mutex_t id, sys_dbg_mutex_information_t* info )
#define SYS_DBG_GET_COND_LIST										934	//
#define SYS_DBG_GET_COND_INFORMATION								935	// int sys_dbg_get_cond_information ( sys_pid_t id, sys_cond_t id, sys_dbg_cond_information_t* info )
#define SYS_DBG_GET_RWLOCK_LIST										936	//
#define SYS_DBG_GET_RWLOCK_INFORMATION								937	// int sys_dbg_get_rwlock_information ( sys_pid_t id, sys_rwlock_t id, sys_dbg_rwlock_information_t* info )
#define SYS_DBG_GET_LWMUTEX_LIST									938	//
#define SYS_DBG_GET_ADDRESS_FROM_DABR								939	// int sys_dbg_get_address_from_dabr ( sys_pid_t id, uint64_t* addr, uint64_t* ctrl_flag )
#define SYS_DBG_SET_ADDRESS_TO_DABR									940	// int sys_dbg_set_address_to_dabr ( sys_pid_t id, uint64_t addr, uint64_t ctrl_flag )
#define SYS_DBG_GET_LWMUTEX_INFORMATION								941	// int sys_dbg_get_lwmutex_information ( sys_pid_t id, sys_lwmutex_pseudo_id_t id, sys_dbg_lwmutex_information_t* info )
#define SYS_DBG_GET_EVENT_QUEUE_LIST								942	//
#define SYS_DBG_GET_EVENT_QUEUE_INFORMATION							943	// int sys_dbg_get_event_queue_information ( sys_pid_t id, sys_event_queue_t id, sys_dbg_event_queue_information_t* info )
#define SYS_DBG_INITIALIZE_PPU_EXCEPTION_HANDLER					944	// int sys_dbg_initialize_ppu_exception_handler( sys_event_queue_t * equeue_id)
#define SYS_DBG_FINALIZE_PPU_EXCEPTION_HANDLER						945	// int sys_dbg_finalize_ppu_exception_handler ( sys_event_queue_t equeue_id )
#define SYS_DBG_GET_SEMAPHORE_LIST									946	//
#define SYS_DBG_GET_SEMAPHORE_INFORMATION							947	// int sys_dbg_get_semaphore_information (sys_pid_t id, sys_semaphore_t id, sys_dbg_semaphore_information_t* info )
#define SYS_DBG_GET_KERNEL_THREAD_LIST								948	//
#define SYS_DBG_GET_KERNEL_THREAD_INFO								949	//
#define SYS_DBG_GET_LWCOND_LIST										950	//
#define SYS_DBG_GET_LWCOND_INFORMATION								951	// int sys_dbg_get_lwcond_information (sys_pid_t id, sys_lwcond_pseudo_id_t id, sys_dbg_lwcond_information_t* info )
#define SYS_DBG_CREATE_SCRATCH_DATA_AREA_EXT						952	//
#define SYS_DBG_VM_GET_PAGE_INFORMATION								953	// int sys_dbg_vm_get_page_information (sys_pid_t id, sys_addr_t addr, unsigned int num, sys_vm_page_information_t *pageinfo )
#define SYS_DBG_VM_GET_INFO											954	//
#define SYS_DBG_ENABLE_FLOATING_POINT_ENABLED_EXCEPTION				955	// int sys_dbg_enable_floating_point_enabled_exception ( sys_ppu_thread_t id )
#define SYS_DBG_DISABLE_FLOATING_POINT_ENABLED_EXCEPTION			956	// int sys_dbg_disable_floating_point_enabled_exception ( sys_ppu_thread_t id )
#define SYS_DBG_GET_PROCESS_MEMORY_CONTAINER_INFORMATION			957	// (u32 proc_id, dbg_mc_info *mc_info[count], u32 *count)
//#define sys_dbg_(send event flags?)								959	// 4 Params: id, uint64_t,uint64_t,uint64_t
#define SYS_CONTROL_PERFORMANCE_MONITOR								960	// int sys_control_performance_monitor? (int id, 0 / *out ) - Controls Performance Monitor on the Cell Broadband Engine syscall
#define SYS_PERFORMANCE_MONITOR_HIDDEN								961	//
#define SYS_PERFORMANCE_MONITOR_BOOKMARK							962	//
#define SYS_LV1_PC_TRACE_CREATE										963	//
#define SYS_LV1_PC_TRACE_START										964	//
#define SYS_LV1_PC_TRACE_STOP										965	//
#define SYS_LV1_PC_TRACE_GET_STATUS									966	//
#define SYS_LV1_PC_TRACE_DESTROY									967	//
#define SYS_RSX_TRACE_IOCTL											968	//
//#define 															969	//
#define SYS_DBG_GET_EVENT_FLAG_LIST									970	//
#define SYS_DBG_GET_EVENT_FLAG_INFORMATION							971	// int sys_dbg_get_event_flag_information ( sys_pid_t id, sys_event_flag_t id, sys_dbg_event_flag_information_t* info )
//#define sys_dbg_(send event flags?)								972	// 1 Param: uint8_t [0x48]
//#define															973	//
//#define															974	// sc(0x3CE, in:(ppu)thread_id, out:uint8_t[0x440])
#define SYS_DBG_READ_SPU_THREAD_CONTEXT2							975	// int sys_dbg_read_spu_thread_context2( sys_spu_thread_t id, sys_dbg_spu_thread_context2_t* spu_context )
#define SYS_CRYPTO_ENGINE_CREATE									976	// int sys_crypto_engine_create(sys_pid_t* id);
#define SYS_CRYPTO_ENGINE_DESTROY									977	// int sys_crypto_engine_destroy(sys_pid_t id);
#define SYS_CRYPTO_ENGINE_HASHER_PREPARE							978	// int sys_crypto_engine_hasher_prepare(sys_pid_t id, int32_t hash_key_index); /* uses HMAC-SHA1 with key size of 0x14 bytes, keys are generated by VTRM (master) */
#define SYS_CRYPTO_ENGINE_HASHER_RUN								979	// int sys_crypto_engine_hasher_run(sys_pid_t id, const void* data, uint32_t data size); /* splits data by chunks of 0x400 bytes max */
#define SYS_CRYPTO_ENGINE_HASHER_GET_HASH							980	// int sys_crypto_engine_hasher_get_hash(sys_pid_t id, void* buffer, uint32_t max_buffer_size /* >= 0x14 */);
#define SYS_CRYPTO_ENGINE_CIPHER_PREPARE							981	// int sys_crypto_engine_cipher_prepare(sys_pid_t id, int32_t hash_key_index, int32_t mode /* 1:encrypt, 2:decrypt */, int32_t cipher_key_index, const void* iv, uint32_t iv_size); /* uses AES-CBC-128, keys are generated by VTRM (master) */
#define SYS_CRYPTO_ENGINE_CIPHER_RUN								982	// int sys_crypto_engine_cipher_run(sys_pid_t id, const void* input, void* output, uint32_t data_size); /* splits data by chunks of 0x400 bytes max */
#define SYS_CRYPTO_ENGINE_CIPHER_GET_HASH							983	// int sys_crypto_engine_cipher_get_hash(sys_pid_t id, void* buffer, uint32_t max_buffer_size /* >= 0x14 */);
#define SYS_CRYPTO_ENGINE_RANDOM_GENERATE							984	// int sys_crypto_engine_random_generate(void* buffer, uint32_t max_buffer_size /* >= 0x10 */);
#define SYS_DBG_GET_CONSOLE_TYPE									985	// returns Console Type, syscall(985,uint64_t * type)
//#define																986	// seems to return Game Application Title ID , syscall(986,out:uint8[0x40])
//#define																987	// syscall(987,0 or 1, uint64_t data), example: 0, 0x8000100000020000 (no root flags required)
//#define sys_dbg_(something)_ppu_exception_handler					988	// 2 Params: syscall(988,int i,0) , i <0x10 (1 or 2 or 4 or 8 or 0x10)
//#define																989	// 2 Params: syscall(989, (spu) thread_id ,out:uint8[0x20])

#define MAX_NUM_OF_SYSTEM_CALLS									   1024

#define LV2_SYSCALL	LV2_CONTEXT

#define LV2_SYSCALL2(ret, name, args) asm("" \
"	.section \".text\"\n" \
"	.align 2\n" \
"	.p2align 3,,7\n" \
"	.globl "#name"\n" \
"	.section \".opd\",\"aw\"\n" \
"	.align 3\n" \
#name": \n" \
"	.quad .L."#name",.TOC.@tocbase\n" \
"	.previous\n" \
"	.type   "#name", @function\n" \
".L."#name":\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	mflr 0\n" \
"	std 0, 32(1)\n" \
"	std 2, 40(1)\n" \
"	bl +4\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -32\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args

/* Extends the kernel stack of the syscall in 4096 bytes. Can only be called once in a syscall */
LV2_EXPORT int extend_kstack(int unk);

static INLINE uint64_t get_syscall_address(int n)
{
	uint64_t **table = (uint64_t **)MKA(syscall_table_symbol);
	uint64_t *syscall = table[n];
	return syscall[0];
}

static INLINE void create_syscall(int n, void *func)
{
	uint64_t ***table = (uint64_t ***)MKA(syscall_table_symbol);
	uint64_t **syscall = table[n];
	f_desc_t *f = (f_desc_t *)func;
	syscall[0] = f->addr;
}

static INLINE void create_syscall2(int n, void *func)
{
	uint64_t **table = (uint64_t **)MKA(syscall_table_symbol);
	f_desc_t *f = (f_desc_t *)func;
	uint64_t *opd = f->addr;

	opd[0] = ((uint64_t)opd) + 16;
	opd[1] = MKA(TOC);
	table[n] = opd;
}

#define patch_syscall	create_syscall

static INLINE void set_syscall_handler(void *syscall_handler)
{
	patch_call(syscall_call_offset, syscall_handler);
}

static INLINE uint64_t syscall_8(int n, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5, uint64_t param6, uint64_t param7, uint64_t param8)
{
	uint64_t **table = (uint64_t **)MKA(syscall_table_symbol);
	f_desc_t *f = (f_desc_t *)table[n];
	uint64_t *sc = (uint64_t *)f->addr;

	f_desc_t fn;
	fn.addr = (void*)sc;
	fn.toc = (void*)MKA(TOC);
	uint64_t (*func)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t) = (void *)&fn;

	return (uint64_t)func(param1, param2, param3, param4, param5, param6, param7, param8);
}

static INLINE void syscall7(int n, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5, uint64_t param6, uint64_t param7) {syscall_8(n, param1, param2, param3, param4, param5, param6, param7, 0);}
static INLINE void syscall6(int n, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5, uint64_t param6) {syscall_8(n, param1, param2, param3, param4, param5, param6, 0, 0);}
static INLINE void syscall5(int n, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5) {syscall_8(n, param1, param2, param3, param4, param5, 0, 0, 0);}
static INLINE void syscall4(int n, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4) {syscall_8(n, param1, param2, param3, param4, 0, 0, 0, 0);}
static INLINE void syscall3(int n, uint64_t param1, uint64_t param2, uint64_t param3) {syscall_8(n, param1, param2, param3, 0, 0, 0, 0, 0);}
static INLINE void syscall2(int n, uint64_t param1, uint64_t param2) {syscall_8(n, param1, param2, 0, 0, 0, 0, 0, 0);}
static INLINE void syscall1(int n, uint64_t param1) {syscall_8(n, param1, 0, 0, 0, 0, 0, 0, 0);}
static INLINE void syscall0(int n) {syscall_8(n, 0, 0, 0, 0, 0, 0, 0, 0);}

#endif /* __LV2_SYSCALL_H__ */
