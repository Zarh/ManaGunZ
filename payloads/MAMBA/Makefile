PAYLOADS = 421C 421D 430C 430D 431C 440C 441C 441D 446C 446D 450C 450D 453C 453D 455C 455D 460C \
		   465C 465D 470C 470D 475C 475D 476C 476D 478C 478D 480C 480D 481C 481D 482C 482D 483C

PS3DEV= ps3dev
include $(PSL1GHT)/ppu_rules

ifeq ($(OS),Windows_NT)
	ZLIBUTIL = ./zlibutil.exe
endif
ifeq ($(shell uname -s),Linux)
	ZLIBUTIL = ./zlibutil
endif

CC		:= ppu-gcc
CXX		:= ppu-g++
LD		:= ppu-ld 
OBJCOPY		:= ppu-objcopy
OBJDUMP		:= ppu-objdump
AR 		:= ppu-ar
STRIP		:= ppu-strip
INCLUDE		= $(PS3DEV)/ppu/ppu/include lv2/include lv1/include debug/include
LIBSDIR         =
LIBS           	=
BUILD_TYPE     	= release
EMU_SUPPORT		= full

CFLAGS = -ffunction-sections -fdata-sections -Os -m64 -fno-builtin -fno-exceptions \
			   -Wall -Wno-strict-aliasing -Wno-multichar $(foreach dir,$(INCLUDE),-I$(dir)) \
			   -DLV2 -DUSE_LV1_PEEK_POKE -DPS3M_API -DKW_STEALTH_EXT -DIS_MAMBA -ffreestanding
CFLAGS += --std=gnu99

ifeq ($(EMU_SUPPORT), full)
CFLAGS += -DDO_PATCH_PSP -DDO_PATCH_PS2
endif

ifeq ($(EMU_SUPPORT), psp)
CFLAGS += -DDO_PATCH_PSP
endif

ifeq ($(EMU_SUPPORT), ps2)
CFLAGS += -DDO_PATCH_PS2
endif

ifeq ($(BUILD_TYPE), debug)
CFLAGS += -DDEBUG -DTEST 
endif

LDFLAGS= -T stage2/stage2.ld -nostartfiles -nostdlib -nodefaultlibs -Wl,-static -L. $(foreach dir,$(LIBSDIR),-L$(dir)) $(LIBS) \
	 -Wl,--gc-sections -Wl,-Map=stage2/stage2.map

OBJS = stage2/start.o stage2/main.o stage2/ps3mapi_core.o stage2/mappath.o stage2/storage_ext.o stage2/crypto.o stage2/modulespatch.o stage2/config.o stage2/region.o \
	lv2/src/patch.o lv2/src/interrupt.o lv2/src/interrupt_c.o lv2/src/io.o lv2/src/libc.o \
	lv2/src/libc_c.o lv2/src/memory.o lv2/src/memory_c.o lv2/src/thread.o lv2/src/thread_c.o lv2/src/process.o \
	lv2/src/synchronization.o lv2/src/modules.o lv2/src/modules_c.o lv2/src/storage.o lv2/src/object.o \
	lv2/src/security.o lv2/src/time.o  lv2/src/syscall.o \
	lv1/src/hvcall.o lv1/src/stor.o lv1/src/device.o 

ifeq ($(EMU_SUPPORT),$(filter $(EMU_SUPPORT),psp full))
OBJS += stage2/psp_s.o stage2/psp.o
endif

ifeq ($(BUILD_TYPE), debug)
OBJS += debug/src/debug.o debug/src/debug_util.o debug/src/printf.o
endif
	 
define do_payload
	@rm -f *.o *.elf stage2/*.map stage2/*.o lv2/src/*.o lv1/src/*.o debug/src/*.o  
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/start.o stage2/start.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/main.o stage2/main.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/ps3mapi_core.o stage2/ps3mapi_core.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/mappath.o stage2/mappath.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/storage_ext.o stage2/storage_ext.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/crypto.o stage2/crypto.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/modulespatch.o stage2/modulespatch.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/config.o stage2/config.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/region.o stage2/region.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/patch.o lv2/src/patch.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/interrupt.o lv2/src/interrupt.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/interrupt_c.o lv2/src/interrupt_c.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/io.o lv2/src/io.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/libc.o lv2/src/libc.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/libc_c.o lv2/src/libc_c.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/memory.o lv2/src/memory.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/memory_c.o lv2/src/memory_c.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/thread.o lv2/src/thread.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/thread_c.o lv2/src/thread_c.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/process.o lv2/src/process.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/synchronization.o lv2/src/synchronization.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/modules.o lv2/src/modules.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/modules_c.o lv2/src/modules_c.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/storage.o lv2/src/storage.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/object.o lv2/src/object.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/security.o lv2/src/security.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/time.o lv2/src/time.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv2/src/syscall.o lv2/src/syscall.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv1/src/hvcall.o lv1/src/hvcall.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv1/src/stor.o lv1/src/stor.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o lv1/src/device.o  lv1/src/device.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/psp_s.o stage2/psp_s.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o stage2/psp.o stage2/psp.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o debug/src/debug.o debug/src/debug.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o debug/src/debug_util.o debug/src/debug_util.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o debug/src/printf.o debug/src/printf.c
	$(CC) $(LDFLAGS) -o mamba_$@.elf $(OBJS)
	$(OBJCOPY) -O binary mamba_$@.elf mamba_$@.bin
	$(ZLIBUTIL) mamba_$@.bin mamba_$@.lz.bin
	@rm -f *.o *.elf stage2/*.map stage2/*.o lv2/src/*.o lv1/src/*.o debug/src/*.o
endef

all: $(PAYLOADS)

$(PAYLOADS):
	$(do_payload)

loader:
	make -f Makefile_loader clean --no-print-directory
	make -f Makefile_loader --no-print-directory
clean:
	rm -f *.bin *.o *.elf stage2/*.map stage2/*.o lv2/src/*.o lv1/src/*.o debug/src/*.o loader_src/*.o 
