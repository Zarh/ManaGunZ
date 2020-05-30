#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

#define KERNEL_BASE 0x8000000000000000

#ifdef FIRMWARE_421C
	#define KERNEL_TOC			                 0x346390
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06F748
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F85C
	#define KERNEL_SYMBOL_MEMSET                 0x04E508
	#define KERNEL_SYMBOL_MEMCPY                 0x07DFD0
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000370A38ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000370A40ULL
#endif

#ifdef FIRMWARE_421D
	#define KERNEL_TOC			                 0x363E80
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0731E0
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEA4
	#define KERNEL_SYMBOL_MEMSET                 0x051DF8
	#define KERNEL_SYMBOL_MEMCPY                 0x081FF4
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000038F238ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000038F240ULL
#endif

#ifdef FIRMWARE_430C
	#define KERNEL_TOC			                 0x348200
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06F874
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F858
	#define KERNEL_SYMBOL_MEMSET                 0x04E544
	#define KERNEL_SYMBOL_MEMCPY                 0x07E0FC
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003729B8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003729C0ULL
#endif

#ifdef FIRMWARE_430D
	#define KERNEL_TOC			                 0x365CA0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x07330C
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEA0
	#define KERNEL_SYMBOL_MEMSET                 0x051E34
	#define KERNEL_SYMBOL_MEMCPY                 0x082120
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000391138ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000391140ULL
#endif

#ifdef FIRMWARE_431C
	#define KERNEL_TOC			                 0x348210
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06F878
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F85C
	#define KERNEL_SYMBOL_MEMSET                 0x04E548
	#define KERNEL_SYMBOL_MEMCPY                 0x07E100
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003729B8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003729C0ULL
#endif

#ifdef FIRMWARE_440C
	#define KERNEL_TOC			                 0x3487D0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06E7C0
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F858
	#define KERNEL_SYMBOL_MEMSET                 0x04D490
	#define KERNEL_SYMBOL_MEMCPY                 0x07D048
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000373038ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000373040ULL
#endif

#ifdef FIRMWARE_441C
	#define KERNEL_TOC			                 0x3487E0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06E7C4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F85C
	#define KERNEL_SYMBOL_MEMSET                 0x04D494
	#define KERNEL_SYMBOL_MEMCPY                 0x07D04C
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000373038ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000373040ULL
#endif

#ifdef FIRMWARE_441D
	#define KERNEL_TOC			                 0x3665C0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x07225C
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEA4
	#define KERNEL_SYMBOL_MEMSET                 0x050D84
	#define KERNEL_SYMBOL_MEMCPY                 0x081070
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000391AB8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000391AC0ULL
#endif

#ifdef FIRMWARE_446C
	#define KERNEL_TOC			                 0x348DF0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06E7C4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F85C
	#define KERNEL_SYMBOL_MEMSET                 0x04D494
	#define KERNEL_SYMBOL_MEMCPY                 0x07D04C
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000373638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000373640ULL
#endif

#ifdef FIRMWARE_446D
	#define KERNEL_TOC			                 0x366BD0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x07225C
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEA4
	#define KERNEL_SYMBOL_MEMSET                 0x050D84
	#define KERNEL_SYMBOL_MEMCPY                 0x081070
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003920B8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003920C0ULL
#endif

#ifdef FIRMWARE_450C
	#define KERNEL_TOC			                 0x34B160
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06E7C0
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F858
	#define KERNEL_SYMBOL_MEMSET                 0x04D490
	#define KERNEL_SYMBOL_MEMCPY                 0x07D048
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000375A38ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000375A40ULL
#endif

#ifdef FIRMWARE_450D
	#define KERNEL_TOC			                 0x36EC40
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x072310
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEA0
	#define KERNEL_SYMBOL_MEMSET                 0x050E38
	#define KERNEL_SYMBOL_MEMCPY                 0x081124
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000039A2B8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000039A2C0ULL
#endif

#ifdef FIRMWARE_453C
	#define KERNEL_TOC			                 0x34B2E0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06E7C4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F85C
	#define KERNEL_SYMBOL_MEMSET                 0x04D494
	#define KERNEL_SYMBOL_MEMCPY                 0x07D04C
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000375C38ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000375C40ULL
#endif

#ifdef FIRMWARE_453D
	#define KERNEL_TOC			                 0x370620
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x072314
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEA4
	#define KERNEL_SYMBOL_MEMSET                 0x050E3C
	#define KERNEL_SYMBOL_MEMCPY                 0x081128
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000039BDB8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000039BDC0ULL
#endif

#ifdef FIRMWARE_455C
	#define KERNEL_TOC			                 0x34E620
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x06FC00
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D6D8
	#define KERNEL_SYMBOL_MEMCPY                 0x07E488
	#define GAMEOS_LPAR_BASE_PTR                 0x8000000000378FB8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x8000000000378FC0ULL
#endif

#ifdef FIRMWARE_455D
	#define KERNEL_TOC			                 0x3738E0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073750
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB4
	#define KERNEL_SYMBOL_MEMSET                 0x051080
	#define KERNEL_SYMBOL_MEMCPY                 0x082564
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000039F138ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000039F140ULL
#endif

#ifdef FIRMWARE_460C
	#define KERNEL_TOC			                 0x34F950
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x070018
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F868
	#define KERNEL_SYMBOL_MEMSET                 0x04D668
	#define KERNEL_SYMBOL_MEMCPY                 0x07E8A0
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A3B8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A3C0ULL
#endif

#ifdef FIRMWARE_465C
	#define KERNEL_TOC			                 0x34F960
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x07001C
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E8A4
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A3B8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A3C0ULL
#endif

#ifdef FIRMWARE_465D
	#define KERNEL_TOC			                 0x375510
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073B6C
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB4
	#define KERNEL_SYMBOL_MEMSET                 0x051014
	#define KERNEL_SYMBOL_MEMCPY                 0x082980
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A0DB8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A0DC0ULL
#endif

#ifdef FIRMWARE_470C
	#define KERNEL_TOC			                 0x34FB10
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A0
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F868
	#define KERNEL_SYMBOL_MEMSET                 0x04D668
	#define KERNEL_SYMBOL_MEMCPY                 0x07E928
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A5B8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A5C0ULL
#endif

#ifdef FIRMWARE_470D
	#define KERNEL_TOC			                 0x375850
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073BF0
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB0
	#define KERNEL_SYMBOL_MEMSET                 0x051010
	#define KERNEL_SYMBOL_MEMCPY                 0x082A04
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A10B8ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A10C0ULL
#endif

#ifdef FIRMWARE_475C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_475D
	#define KERNEL_TOC			                 0x3758E0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073BF4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB4
	#define KERNEL_SYMBOL_MEMSET                 0x051014
	#define KERNEL_SYMBOL_MEMCPY                 0x082A08
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A1138ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A1140ULL
#endif

#ifdef FIRMWARE_476C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_476D
	#define KERNEL_TOC			                 0x3758E0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073BF4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB4
	#define KERNEL_SYMBOL_MEMSET                 0x051014
	#define KERNEL_SYMBOL_MEMCPY                 0x082A08
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A1138ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A1140ULL
#endif

#ifdef FIRMWARE_478C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_478D
	#define KERNEL_TOC			                 0x3758E0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073BF4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB4
	#define KERNEL_SYMBOL_MEMSET                 0x051014
	#define KERNEL_SYMBOL_MEMCPY                 0x082A08
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A1138ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A1140ULL
#endif

#ifdef FIRMWARE_480C
	#define KERNEL_TOC			                 0x34FBA0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A0
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F868
	#define KERNEL_SYMBOL_MEMSET                 0x04D668
	#define KERNEL_SYMBOL_MEMCPY                 0x07E928
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_480D
	#define KERNEL_TOC			                 0x3759B0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073BF0
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB0
	#define KERNEL_SYMBOL_MEMSET                 0x051010
	#define KERNEL_SYMBOL_MEMCPY                 0x082A04
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A1238ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A1240ULL
#endif

#ifdef FIRMWARE_481C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_481D
	#define KERNEL_TOC			                 0x3759C0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073BF4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB4
	#define KERNEL_SYMBOL_MEMSET                 0x051014
	#define KERNEL_SYMBOL_MEMCPY                 0x082A08
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A1238ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A1240ULL
#endif

#ifdef FIRMWARE_482C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_482D
	#define KERNEL_TOC			                 0x3759C0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073BF4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB4
	#define KERNEL_SYMBOL_MEMSET                 0x051014
	#define KERNEL_SYMBOL_MEMCPY                 0x082A08
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A1238ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A1240ULL
#endif

#ifdef FIRMWARE_483C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_484C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_484D
	#define KERNEL_TOC			                 0x3759C0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x073BF4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00FEB4
	#define KERNEL_SYMBOL_MEMSET                 0x051014
	#define KERNEL_SYMBOL_MEMCPY                 0x082A08
	#define GAMEOS_LPAR_BASE_PTR                 0x80000000003A1238ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x80000000003A1240ULL
#endif

#ifdef FIRMWARE_485C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif

#ifdef FIRMWARE_486C
	#define KERNEL_TOC			                 0x34FBB0
	#define KERNEL_SYMBOL_EXTEND_KSTACK          0x0700A4
	#define KERNEL_SYMBOL_COPY_TO_USER           0x00F86C
	#define KERNEL_SYMBOL_MEMSET                 0x04D66C
	#define KERNEL_SYMBOL_MEMCPY                 0x07E92C
	#define GAMEOS_LPAR_BASE_PTR                 0x800000000037A638ULL
	#define GAMEOS_LPAR_SIZE_PTR                 0x800000000037A640ULL
#endif


#endif /* __SYMBOLS_H__ */
