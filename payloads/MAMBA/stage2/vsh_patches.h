int vsh_type = 0x666;

//Only rebug
static INLINE void get_rebug_vsh()
{
	CellFsStat stat;

	if(cellFsStat("/dev_flash/vsh/module/vsh.self.cexsp", &stat) == SUCCEEDED)
		vsh_type = 0xDE;
	else if(cellFsStat("/dev_flash/vsh/module/vsh.self.dexsp", &stat) == SUCCEEDED)
		vsh_type = 0xCE;

	#ifdef DEBUG
	if(vsh_type != 0x666)
		DPRINTF("We are in CFW Rebug REX, VSH is %XX\n", vsh_type);
	#endif
}

uint64_t vsh_offset = vsh_pos_in_ram;

static INLINE int get_vsh_offset()
{
	get_rebug_vsh();

	//First try with default static offset..
	if( (lv1_peekd(vsh_offset + 0x200) == 0xF821FF917C0802A6ULL) &&
		(lv1_peekd(vsh_offset + 0x208) == 0xF80100804800039DULL) &&
		(lv1_peekd(vsh_offset + 0x210) == 0x6000000048000405ULL) )
	{
		//vsh_offset = vsh_pos_in_ram;
		#ifdef DEBUG
		DPRINTF("Vsh.self found with static offset at address 0x%lx\n", vsh_offset);
		#endif
	}
	//..if that not work brute-force the address
	else
	{
		vsh_offset = 0;
		for(int addr = 0x10000; addr < 0x3000000; addr += 0x10000)
		{
			if(lv1_peekd(addr + 0x200) == 0xF821FF917C0802A6ULL)
			{
				if(lv1_peekd(addr + 0x208) == 0xF80100804800039DULL)
				{
					if(lv1_peekd(addr + 0x210) == 0x6000000048000405ULL)
					{
						vsh_offset = addr;
						#ifdef DEBUG
						DPRINTF("Vsh.self found with brute-force at address 0x%lx\n", vsh_offset);
						#endif
						break;
					}
				}
			}
		}
		//Vsh not found
		if(vsh_offset == 0)
		{
			#ifdef DEBUG
			DPRINTF("Vsh.self not found!!\n");
			#endif
			return FAILED;
		}
	}

	return SUCCEEDED;
}


#ifdef DO_PATCH_PS2
//int ps2_patches_done = 0;

static INLINE int ps2_vsh_patches()
{
	if(condition_ps2softemu == 0)
		return 0;

	if(vsh_offset == 0)
		return EINVAL;

	uint64_t addr = 0, addr2 = 0;
	int i = 0, mv_offset = 0;

	#ifdef ps2tonet_patch
	uint64_t ps2tonet = ps2tonet_patch, ps2tonet_size = ps2tonet_size_patch;

	if(vsh_type == 0xCE)
	{
		//REBUG REX lv2 DEX and vsh CEX
		#ifdef cex_ps2tonet_patch
		ps2tonet = cex_ps2tonet_patch;
		#endif
		#ifdef cex_ps2tonet_size_patch
		ps2tonet_size = cex_ps2tonet_size_patch;
		#endif
	}
	else if(vsh_type == 0xDE)
	{
		//REBUG REX lv2 CEX and vsh DEX
		#ifdef dex_ps2tonet_patch
		ps2tonet = dex_ps2tonet_patch;
		#endif
		#ifdef dex_ps2tonet_size_patch
		ps2tonet_size = dex_ps2tonet_size_patch;
		#endif
	}

	//Find ps2tonet_patch patches
	//First try with static offset..
	uint64_t value = 0;
	addr = (vsh_offset + ps2tonet_size);
	addr2 = (vsh_offset + ps2tonet);

	for(mv_offset = 0; mv_offset < 0x2000000; mv_offset += 0x100000)
	{
		value = lv1_peekd(addr + mv_offset);
		if(value == 0x3800004078640020ULL)
		{
			if(lv1_peekw(addr2 + mv_offset) == 0x60638204)
			{
				#ifdef DEBUG
				DPRINTF("Ps2tonet patches are always there, nothing to do!\n");
				#endif
				return 0;
			}
		}
		else if(value == 0x38A004F078640020ULL)
		{
			if(lv1_peekw(addr2 + mv_offset) == 0x60638202)
			{
				#ifdef DEBUG
				DPRINTF("Offset ps2tonet_size_patch found with static offset at address: 0x%lx\n", addr + mv_offset);
				DPRINTF("Offset ps2tonet_patch found with static offset at address: 0x%lx\n", addr2 + mv_offset);
				#endif

				lv1_pokew(addr + mv_offset, LI(R5, 0x40));
				lv1_pokew(addr2 + mv_offset, ORI(R3, R3, 0x8204));

				#ifdef DEBUG
				value = lv1_peekw(addr + mv_offset);
				DPRINTF("First poke: 0x%lx\n", value);
				value = lv1_peekw(addr2 + mv_offset);
				DPRINTF("Second poke: 0x%lx\n", value);
				DPRINTF("SUCCESS: all patches DONE!\n");
				#endif
				return 0;
			}
		}
	}
	#endif

	//brute-force
	mv_offset = (vsh_offset + 0x700);

	for(i = 0; i < 0x2000000; i += 4)
	{
		if(lv1_peekd(mv_offset + i) == 0x3860000060638202ULL)
		{
			addr = (mv_offset + i + 4);
			#ifdef DEBUG
			DPRINTF("Offset ps2tonet_patch found with brute-force at address 0x%lx\n", addr);
			#endif

			addr2 = (addr - 12);
			if(lv1_peekd(addr2) == 0x38A004F078640020ULL)
			{
				#ifdef DEBUG
				DPRINTF("Offset ps2tonet_size_patch found with brute-force at address 0x%lx\n", addr2);
				#endif

				lv1_pokew(addr, ORI(R3, R3, 0x8204));
				lv1_pokew(addr2, LI(R5, 0x40));

				#ifdef DEBUG
				value = lv1_peekw(addr);
				DPRINTF("First poke: 0x%lx\n", value);
				value = lv1_peekw(addr2);
				DPRINTF("Second poke: 0x%lx\n", value);
				DPRINTF("SUCCESS: all ps2tonet patches DONE!\n");
				#endif
				return 0;
			}
			#ifdef DEBUG
			else
			{
				DPRINTF("WARNING: ps2tonet_size_patch not found!!\n");
			}
			#endif
		}
	}

	#ifdef DEBUG
	DPRINTF("WARNING: ps2tonet patches not found!!\n");
	#endif
	return EINVAL;
}

#endif
