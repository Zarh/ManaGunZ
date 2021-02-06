//----------------------------------------
// LV1 / LV2 SYSCALLS PEEK/POKE/CALL
//----------------------------------------

LV2_SYSCALL2(uint64_t, sys_cfw_lv1_peek, (uint64_t lv1_addr))
{
	#ifdef DEBUG
	DPRINTF("lv1_peek %p\n", (void*)lv1_addr);
	#endif

	return lv1_peekd(lv1_addr);
}

LV2_SYSCALL2(void, sys_cfw_lv1_poke, (uint64_t lv1_addr, uint64_t lv1_value))
{
	#ifdef DEBUG
	DPRINTF("LV1 poke %p %016lx\n", (void*)lv1_addr, lv1_value);
	#endif

	lv1_poked(lv1_addr, lv1_value);
}

LV2_SYSCALL2(void, sys_cfw_lv1_call, (uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7, uint64_t num))
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

LV2_SYSCALL2(void, sys_cfw_lv2_func, (uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7, uint64_t num))
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

LV2_SYSCALL2(uint64_t, sys_cfw_peek, (uint64_t *addr))
{
	#ifdef DEBUG
	DPRINTF("peek %p\n", addr);
	#endif

	uint64_t ret = *addr;

	// Fix compatibilty issue with prx loader (before v1.08 [U]). It searches for a string... that is also in this payload, and then lv2_peek((vsh_str + 0x70)) crashes the system.
	if (ret == 0x5F6D61696E5F7673)
	{
		extern uint64_t _start;
		extern uint64_t __self_end;

		if ((uint64_t)addr >= (uint64_t)&_start && (uint64_t)addr < (uint64_t)&__self_end)
		{
			#ifdef DEBUG
			DPRINTF("peek to addr %p blocked for compatibility.\n", addr);
			#endif
			return 0;
		}
	}

	return ret;
}

void _sys_cfw_poke(uint64_t *addr, uint64_t value);

LV2_HOOKED_FUNCTION(void, sys_cfw_new_poke, (uint64_t *addr, uint64_t value))
{
	#ifdef DEBUG
	DPRINTF("New poke called %p %016lx\n", addr, value);
	#endif

	_sys_cfw_poke(addr, value);
	asm volatile("icbi 0,%0; isync" :: "r"(addr));
}

LV2_HOOKED_FUNCTION(void *, sys_cfw_memcpy, (void *dst, void *src, uint64_t len))
{
	#ifdef DEBUG
	DPRINTF("sys_cfw_memcpy: %p %p 0x%lx\n", dst, src, len);
	#endif

	if (len == 8)
	{
		_sys_cfw_poke(dst, *(uint64_t *)src);
		return dst;
	}

	return memcpy(dst, src, len);
}

static uint8_t isLoadedFromIrisManager = 0;

int64_t syscall8(uint64_t function, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5, uint64_t param6, uint64_t param7);
f_desc_t extended_syscall8;
static void *current_813;

LV2_SYSCALL2(void, sys_cfw_poke, (uint64_t *ptr, uint64_t value))
{
	uint64_t addr = (uint64_t)ptr;

	#ifdef DEBUG
	DPRINTF("poke %016lx %016lx\n", addr, value);
	#endif

	if (addr >= MKA(syscall_table_symbol))
	{
		uint64_t syscall_num = (addr-MKA(syscall_table_symbol)) / 8;

		if ((syscall_num >= 6 && syscall_num <= 10) || syscall_num == 35)//Rewrite protection
		{
			uint64_t sc_null = *(uint64_t *)MKA(syscall_table_symbol);
			uint64_t syscall_not_impl = *(uint64_t *)sc_null;

			if (syscall_num == 8 && (value & 0xFFFFFFFF00000000ULL) == MKA(0))
			{
				// Probably iris manager or similar
				// Lets extend our syscall 8 so that it can call this other syscall 8
				// First check if it is trying to restore our syscall8
				if (*(uint64_t *)syscall8 == value)
				{
					#ifdef DEBUG
					DPRINTF("Removing syscall 8 extension\n");
					#endif
					if (isLoadedFromIrisManager == 0)
						extended_syscall8.addr = 0;
					return;
				}

				extended_syscall8.addr = (void *) *(uint64_t *)value;
				if (isLoadedFromIrisManager == 0)
					extended_syscall8.toc = (void *) *(uint64_t *)(value+8);
				else
					extended_syscall8.toc = (void *) *(uint64_t *)(MKA(0x3000));

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
		uint64_t sc813 = get_syscall_address(813);

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
