#include <lv2/lv2.h>
#include <lv2/symbols.h>
#include <lv2/error.h>
#include <lv2/thread.h>
#include <lv2/process.h>
#include <lv2/memory.h>

LV2_EXPORT thread_t create_user_thread(void *unk, void *entry, u64 arg, u64 unk2, u32 stack, u64 stacksize, process_t process, u64 flags, void *unk3, const char *name);
LV2_EXPORT thread_t create_user_thread2(void *unk, void *entry, u64 arg, u64 unk2, u32 stack, u64 stacksize, process_t process, u64 flags, const char *name);
LV2_EXPORT int start_thread(thread_t thread, int priority, u64 unk);
LV2_EXPORT int register_thread(process_t process, thread_t thread, u64 unk);
LV2_EXPORT int run_thread(thread_t thread);
LV2_EXPORT u32 allocate_user_stack(process_t process, u64 *stacksize);
LV2_EXPORT void deallocate_user_stack(process_t process, u32 stack, u64 stacksize);

int ppu_user_thread_create(process_t process, thread_t *thread, void *entry, u64 arg, int prio, u64 stacksize, u64 flags, const char *threadname)
{
	u64 *spr0;
	u32 user_stack;
	u64 translated_flags;

	user_stack = allocate_user_stack(process, &stacksize);
	if (user_stack == 0)
	{
		return ENOMEM;
	}

	if (flags & PPU_THREAD_CREATE_JOINABLE)
	{
		translated_flags = 0x10003;
	}
	else
	{
		translated_flags = 0x10001;
	}

	if (flags & PPU_THREAD_CREATE_INTERRUPT)
	{
		translated_flags |= 0x4000;
	}

	spr0 = mfsprg0();
	*thread = create_user_thread2((void *)spr0[0x48/8], entry, arg, 200, user_stack, stacksize, process, translated_flags, threadname);

	if (!(thread))
	{
		deallocate_user_stack(process, user_stack, stacksize);
		return EAGAIN;
	}

	start_thread(*thread, prio + 0x300, 0);
	register_thread(process, *thread, 0);

	if (!(flags & PPU_THREAD_CREATE_INTERRUPT))
	{
		run_thread(*thread);
	}

	return 0;
}
