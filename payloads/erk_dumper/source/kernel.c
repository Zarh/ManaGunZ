#include "kernel.h"
#include "hypervisor.h"
#include "util.h"

void* malloc(uint64_t size) {
	return lv2_allocate(size, 0x27);
}

void free(void* ptr) {
	lv2_deallocate(ptr, 0x27);
}

int page_allocate_auto(process_t process, uint64_t size, uint64_t flags, void** page_address) {
	uint64_t page_size;
	
	if (size >= 0x100000) {
		size = (size + 0xFFFFF) & ~0xFFFFF;
		page_size = MEMORY_PAGE_SIZE_1M;
	} else if (size >= 0x10000) {
		size = (size + 0xFFFF) & ~0xFFFF; 
		page_size = MEMORY_PAGE_SIZE_64K;
	} else {
		if (size > 0x1000)
			size = (size + 0xFFF) & ~0xFFF;			
		else
			size = 0x1000;
		page_size = MEMORY_PAGE_SIZE_4K;
	}
	return lv2_page_allocate(process, size, flags, page_size, page_address);
}

process_t get_current_process_critical(void) {
	process_t proc;
	suspend_interrupts();
	proc = get_current_process();
	resume_interrupts();
	return proc;
}

void* get_current_process_object_table(void) {
	process_t process;
	void* object_table;
	suspend_interrupts();
	process = get_current_process();
	object_table = (void*)*(uint64_t*)((uint8_t*)process + 0x208);
	resume_interrupts();	
	return object_table;
}

process_id_t process_get_pid(process_t process) {
	return *(process_id_t*)((uint8_t*)process + 0x28);
}

uint32_t process_get_status(process_t process) {
	return *(process_id_t*)((uint8_t*)process + 0x2C);
}

uint64_t process_get_ppu_thread_count(process_t process) {
	uint64_t n1 = *(uint64_t*)((uint8_t*)process + 0x50);
	uint64_t n2 = *(uint64_t*)((uint8_t*)process + 0x58);
	uint64_t n3 = lv2_process_get_internal_ppu_thread_count(process);
	return n1 + n2 + n3;
}

uint64_t process_get_spu_thread_count(process_t process) {
	return *(uint64_t*)((uint8_t*)process + 0x80);
}

uint64_t process_get_raw_spu_count(process_t process) {
	return *(uint64_t*)((uint8_t*)process + 0x90);
}

uint32_t process_get_parent_pid(process_t process) {
	return *(uint32_t*)((uint8_t*)process + 0x90);
}

uint64_t process_get_address_space(process_t process) {
	return *(uint64_t*)((uint8_t*)process + 0x30);
}

uint64_t process_get_memory_size(process_t process) {
	return *(uint64_t*)((uint8_t*)process + 0xA8);
}

uint8_t process_get_osabi_type(process_t process) {
	return *(uint8_t*)((uint8_t*)process + 0x268);
}

uint64_t process_get_0x248(process_t process) {
	return *(uint64_t*)((uint8_t*)process + 0x248) & 0xFFFFFFFFFFFFFFF;
}

uint32_t process_get_0x278(process_t process) {
	return *(uint32_t*)((uint8_t*)process + 0x278);
}

const char* process_get_image_file_name(process_t process) {
	return (const char*)*(uint64_t*)((uint8_t*)process + 0x160);
}

const char* process_get_name(process_t process) {
	return (const char*)(*(uint64_t*)((uint8_t*)process + 0x38) + 0x8) + 0x8;
}

uint32_t process_get_sdk_version(process_t process) {
	return *(uint32_t*)((uint8_t*)process + 0x26C);
}

uint32_t process_get_ppu_guid(process_t process) {
	return *(uint32_t*)((uint8_t*)process + 0x308);
}

uint8_t* process_get_param_sfo(process_t process) {
	uint8_t* content = (uint8_t*)process + 0x280;
	if (*content == '\xFF')
		return NULL;
	return content;
}

int process_ea_to_lpar_addr(process_t process, uint64_t ea_address, uint64_t* lpar_address) {
	return lv2_process_ea_to_lpar_addr_ex(process_get_address_space(process), ea_address, lpar_address);
}

int process_get_info(process_t process, struct process_info_t* info) {
	info->pid = process_get_pid(process);
	info->status = process_get_status(process);
	info->ppu_thread_count = (uint32_t)process_get_ppu_thread_count(process);
	info->spu_thread_count = (uint32_t)process_get_spu_thread_count(process);
	info->raw_spu_count = (uint32_t)process_get_raw_spu_count(process);
	lv2_process_get_parent_pid(process, &info->parent_pid);
	info->memory_size = (uint32_t)process_get_memory_size(process);
	lv2_memset(info->image_file_name, 0, MAX_IMAGE_FILE_NAME_LENGTH);
	lv2_strncpy(info->image_file_name, process_get_image_file_name(process), MAX_IMAGE_FILE_NAME_LENGTH);
	info->osabi_type = process_get_osabi_type(process);
	info->param_0x28 = process_get_0x248(process);
	info->param_0x30 = process_get_0x278(process);

	return 0;
}

const char* ppu_thread_status_to_string(uint32_t status) {
	switch (status) {
		case PPU_THREAD_STATUS_IDLE: return "idle";
		case PPU_THREAD_STATUS_RUNNABLE: return "runnable";
		case PPU_THREAD_STATUS_ONPROC: return "onproc";
		case PPU_THREAD_STATUS_SLEEP: return "sleep";
		case PPU_THREAD_STATUS_STOP: return "stop";
		case PPU_THREAD_STATUS_ZOMBIE: return "zombie";
		case PPU_THREAD_STATUS_DELETED: return "deleted";
		case PPU_THREAD_STATUS_UNKNOWN: return "unknown";
	}
	return NULL;
}

int set_dabr(uint64_t address, uint64_t control_flag) {
	enum {
		DABR_USER = 1,
		DABR_KERNEL = 2
	};
	if (control_flag != DABR_CTRL_CLEAR && (control_flag & (DABR_CTRL_READ | DABR_CTRL_WRITE)) == 0)
		return -1;
	return lv1_set_dabr((address & ~3ULL) | control_flag, DABR_USER | DABR_KERNEL);
}

uint64_t spin_lock_irqsave(void) {
	uint8_t* ta = (uint8_t*)get_current_thread();
	return lv2_spin_lock_irqsave_ex(ta + 0x28);
}

void spin_unlock_irqrestore(uint64_t restore) {
	uint8_t* ta = (uint8_t*)get_current_thread();
	lv2_spin_unlock_irqrestore_ex(ta + 0x28, restore, 0);
}

int ppu_user_thread_create(process_t process, thread_t* thread, void* entry, uint64_t arg, int priority, uint64_t stack_size, uint64_t flags, const char* name) {
	uint64_t spr0;
	uint32_t user_stack;	
	uint64_t translated_flags;
	thread_t new_thread;
	uint64_t context;

	user_stack = lv2_allocate_user_stack(process, &stack_size);
	if (user_stack == 0)
		return ENOMEM;

	if ((flags & PPU_THREAD_CREATE_JOINABLE) == PPU_THREAD_CREATE_JOINABLE)
		translated_flags = 0x10003;
	else
		translated_flags = 0x10001;
	
	if ((flags & PPU_THREAD_CREATE_INTERRUPT) == PPU_THREAD_CREATE_INTERRUPT)
		translated_flags |= 0x4000;
	
	spr0 = mfsprg0();
	context = *(uint64_t*)((uint8_t*)spr0 + 0x48);

	new_thread = lv2_create_user_thread2((void*)context, entry, arg, 200, user_stack, stack_size, process, translated_flags, name);
	if (thread)
		*thread = new_thread;
	
	if (!new_thread) {
		lv2_deallocate_user_stack(process, user_stack, stack_size);
		return EAGAIN;
	}
	
	lv2_start_thread(new_thread, priority + 0x300, 0);
	lv2_register_thread(process, new_thread, 0);
	
	if ((flags & PPU_THREAD_CREATE_INTERRUPT) != PPU_THREAD_CREATE_INTERRUPT)
		lv2_run_thread(new_thread);		
	
	return 0;
}

int prx_get_module_name_by_address(process_t process, uint64_t address, char* name) {
	int result;

	struct prx_module_info_t info;
	prx_id_t id;

	result = lv2_prx_get_module_id_by_address(process, address);
	if (result < 0)
		return result;

	id = (prx_id_t)result;

	lv2_memset(&info, 0, sizeof(struct prx_module_info_t));
	result = lv2_prx_get_module_info(process, id, &info, NULL, NULL);
	if (result < 0)
		return result;

	lv2_strncpy(name, info.name, sizeof(info.name));

	return 0;
}

int prx_start_module_with_thread(prx_id_t id, process_t process, uint64_t flags, uint64_t arg) {
	int result;

	uint64_t info[5];
	uint32_t toc[2];
	thread_t thread;
	uint64_t exit_code;

	info[0] = sizeof(info);
	info[1] = 1;

	result = lv2_prx_start_module(id, process, flags, info);
	if (result != 0)
		return result;

	result = lv2_copy_from_process(process, (void*)info[2], toc, sizeof(toc));
	if (result != 0)
		return result;

	result = ppu_user_thread_create(process, &thread, toc, arg, 0, 0x1000, PPU_THREAD_CREATE_JOINABLE, "");
	if (result != 0)
		return result;

	lv2_ppu_thread_join(thread, &exit_code);

	info[1] = 2;
	info[3] = 0;

	return lv2_prx_start_module(id, process, flags, info);
}

int prx_stop_module_with_thread(prx_id_t id, process_t process, uint64_t flags, uint64_t arg) {
	int result;

	uint64_t info[5];
	uint32_t toc[2];
	thread_t thread;
	uint64_t exit_code;

	info[0] = sizeof(info);
	info[1] = 1;

	result = lv2_prx_stop_module(id, process, flags, info);
	if (result != 0)
		return result;

	result = lv2_copy_from_process(process, (void*)info[2], toc, sizeof(toc));
	if (result != 0)
		return result;

	result = ppu_user_thread_create(process, &thread, toc, arg, 0, 0x1000, PPU_THREAD_CREATE_JOINABLE, "");
	if (result != 0)
		return result;

	return lv2_ppu_thread_join(thread, &exit_code);
}

void print_backtrace(int n) {
	int i;
	if (n <= 0)
		return;
	lv2_printf("-=-=-=-=-=-=-=- BACKTRACE -=-=-=-=-=-=-=-\n");
	for (i = 0; i < n; ++i) {
		uint64_t addr = get_call_address(i);
		lv2_printf("  0x%016"PRIx64"\n", addr);
		if (!addr)
			break;
	}
	lv2_printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}
