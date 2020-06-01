/* LPC2300 CRP options. Remove this file from the project if CRP feature is not used. */

#define	NO_CRP	0xFFFFFFFF
#define	CRP1	0x12345678
#define	CRP2	0x87654321
#define	CRP3	0x43218765

unsigned long _crp_magic __attribute__ ((section(".CRP"))) = NO_CRP;

