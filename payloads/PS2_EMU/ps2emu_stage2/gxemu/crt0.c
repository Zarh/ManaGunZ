#include <ps2emu/ps2emu.h>
#include <ps2emu/libc.h>
#include <ps2emu/patch.h>
#include <ps2emu/symbols.h>

#include "restore.h"

extern int main(void);

int crt0(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6)
{
	f_desc_t f;
	int (* overwritten)(uint64_t, uint64_t, uint64_t, uint64_t);
	
	memcpy((void *)overwritten_symbol, restore, sizeof(restore));
	clear_icache((void *)overwritten_symbol, sizeof(restore));
	
	f.addr = (void *)overwritten_symbol;
	f.toc = (void *)TOC;
	
	overwritten = (void *)&f;
	
	main();
	return overwritten(r3, r4, r5, r6);
}
