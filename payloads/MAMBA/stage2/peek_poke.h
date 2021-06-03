//----------------------------------------
// LV1 / LV2 SYSCALLS PEEK/POKE/CALL
//----------------------------------------

LV2_SYSCALL2(u64, sys_cfw_lv1_peek, (u64 lv1_addr))
{
	#ifdef DEBUG
	DPRINTF("lv1_peek %p\n", (void*)lv1_addr);
	#endif

	return lv1_peekd(lv1_addr);
}

LV2_SYSCALL2(void, sys_cfw_lv1_poke, (u64 lv1_addr, u64 lv1_value))
{
	#ifdef DEBUG
	DPRINTF("LV1 poke %p %016lx\n", (void*)lv1_addr, lv1_value);
	#endif

	lv1_poked(lv1_addr, lv1_value);
}

LV2_SYSCALL2(void, sys_cfw_lv1_call, (u64 a1, u64 a2, u64 a3, u64 a4, u64 a5, u64 a6, u64 a7, u64 num))
{
	/* DO NOT modify */
	asm("mflr 0\n");
	asm("std 0, 16(1)\n");
	asm("mr 11, 10\n");
	asm("sc 1\n");
	asm("ld 0, 16(1)\n");
	asm("mtlr 0\n");
	asm("blr\n");
}

LV2_SYSCALL2(void, sys_cfw_lv2_func, (u64 a1, u64 a2, u64 a3, u64 a4, u64 a5, u64 a6, u64 a7, u64 num))
{
	/* DO NOT modify */
	asm("mflr 0\n");
	asm("std 0, 16(1)\n");
	asm("mr 0, 10\n"); //fixed
	asm("mtctr 0\n");
	asm("bctrl\n");
	asm("ld 0, 16(1)\n");
	asm("mtlr 0\n");
	asm("blr\n");
}

//----------------------------------------
//LV2 SYSCALL PEEK/POKE
//----------------------------------------

LV2_SYSCALL2(u64, sys_cfw_peek, (u64 *addr))
{
	#ifdef DEBUG
	DPRINTF("peek %p\n", addr);
	#endif

	u64 ret = *addr;

	// Fix compatibilty issue with prx loader (before v1.08 [U]). It searches for a string... that is also in this payload, and then lv2_peek((vsh_str + 0x70)) crashes the system.
	if (ret == 0x5F6D61696E5F7673)
	{
		extern u64 _start;
		extern u64 __self_end;

		if ((u64)addr >= (u64)&_start && (u64)addr < (u64)&__self_end)
		{
			#ifdef DEBUG
			DPRINTF("peek to addr %p blocked for compatibility.\n", addr);
			#endif
			return 0;
		}
	}

	return ret;
}

void _sys_cfw_poke(u64 *addr, u64 value);

LV2_HOOKED_FUNCTION(void, sys_cfw_new_poke, (u64 *addr, u64 value))
{
	#ifdef DEBUG
	DPRINTF("New poke called %p %016lx\n", addr, value);
	#endif

	_sys_cfw_poke(addr, value);
	asm volatile("icbi 0,%0; isync" :: "r"(addr));
}

LV2_HOOKED_FUNCTION(void *, sys_cfw_memcpy, (void *dst, void *src, u64 len))
{
	#ifdef DEBUG
	DPRINTF("sys_cfw_memcpy: %p %p 0x%lx\n", dst, src, len);
	#endif

	if (len == 8)
	{
		_sys_cfw_poke(dst, *(u64 *)src);
		return dst;
	}

	return memcpy(dst, src, len);
}

static u8 isLoadedFromIrisManager = 0;

int64_t syscall8(u64 function, u64 param1, u64 param2, u64 param3, u64 param4, u64 param5, u64 param6, u64 param7);
f_desc_t extended_syscall8;
static void *current_813;

LV2_SYSCALL2(void, sys_cfw_poke, (u64 *ptr, u64 value))
{
	u64 addr = (u64)ptr;

	#ifdef DEBUG
	DPRINTF("poke %016lx %016lx\n", addr, value);
	#endif

	if (addr >= MKA(syscall_table_symbol))
	{
		u64 syscall_num = (addr-MKA(syscall_table_symbol)) / 8;

		if ((syscall_num >= 6 && syscall_num <= 10) || syscall_num == 35)//Rewrite protection
		{
			u64 sc_null = *(u64 *)MKA(syscall_table_symbol);
			u64 syscall_not_impl = *(u64 *)sc_null;

			if (syscall_num == 8 && (value & 0xFFFFFFFF00000000ULL) == MKA(0))
			{
				// Probably iris manager or similar
				// Lets extend our syscall 8 so that it can call this other syscall 8
				// First check if it is trying to restore our syscall8
				if (*(u64 *)syscall8 == value)
				{
					#ifdef DEBUG
					DPRINTF("Removing syscall 8 extension\n");
					#endif
					if (isLoadedFromIrisManager == 0)
						extended_syscall8.addr = 0;
					return;
				}

				extended_syscall8.addr = (void *) *(u64 *)value;
				if (isLoadedFromIrisManager == 0)
					extended_syscall8.toc = (void *) *(u64 *)(value+8);
				else
					extended_syscall8.toc = (void *) *(u64 *)(MKA(0x3000));

				#ifdef DEBUG
				DPRINTF("Adding syscall 8 extension %p %p\n", extended_syscall8.addr, extended_syscall8.toc);
				#endif

				return;
			}
			else if (((value == sc_null) ||(value == syscall_not_impl)) && (syscall_num != 8)) //Allow remove protected syscall 6 7 9 10 11 35 NOT 8
			{
				#ifdef DEBUG
				DPRINTF("HB remove syscall %ld\n", syscall_num);
				#endif
			}
			else
			{
				#ifdef DEBUG
				DPRINTF("HB has been blocked from rewriting syscall %ld\n", syscall_num);
				#endif
				return;
			}
		}
	}

	else if (addr == MKA(open_path_symbol))
	{

		#ifdef DEBUG
		DPRINTF("open_path poke: %016lx\n", value);
		#endif

		if (value == 0xf821ff617c0802a6ULL)
		{
			#ifdef DEBUG
			DPRINTF("Restoring map_path patches\n");
			#endif
			*ptr = value;
			clear_icache(ptr, 8);
			map_path_patches(0);
			return;
		}
	}
	else
	{
		u64 sc813 = get_syscall_address(813);

		if (addr == sc813)
		{
			if (value == 0xF88300007C001FACULL)
			{
				// Assume app is trying to write the so called "new poke"
				#ifdef DEBUG
				DPRINTF("Making sys_cfw_new_poke\n");
				#endif

				if (current_813)
				{
					unhook_function(sc813, current_813);
				}

				f_desc_t f;
				hook_function(sc813, sys_cfw_new_poke, &f);
				current_813 = sys_cfw_new_poke;
				return;
			}
			else if (value == 0x4800000428250000ULL)
			{
				// Assume app is trying to write a memcpy
				#ifdef DEBUG
				DPRINTF("Making sys_cfw_memcpy\n");
				#endif

				if (current_813)
				{
					unhook_function(sc813, current_813);
				}

				f_desc_t f;
				hook_function(sc813, sys_cfw_memcpy, &f);
				current_813 = sys_cfw_memcpy;
				return;
			}
			else if (value == 0xF821FF017C0802A6ULL)
			{
				// Assume app is trying to restore sc 813
				if (current_813)
				{
					#ifdef DEBUG
					DPRINTF("Restoring syscall 813\n");
					#endif

					unhook_function(sc813, current_813);
					current_813 = NULL;
					return;
				}
			}
			else
			{
				#ifdef DEBUG
				DPRINTF("Warning: syscall 813 being overwritten with unknown value (%016lx). *blocking it*\n", value);
				#endif
				return;
			}
		}
		else if (addr > sc813 && addr < (sc813 + 0x20))
		{
			return;
		}
	}

	*ptr = value;
}
