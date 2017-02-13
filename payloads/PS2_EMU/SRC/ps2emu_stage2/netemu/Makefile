PAYLOADS := 421 430 431 440 441 446 450 453 455 460 465 466 470 475 476 478 480 481

CC			:= ppu-gcc
OBJCOPY		:= ppu-objcopy
CFLAGS = -ffunction-sections -fdata-sections -Os -m64 -fno-builtin -fno-exceptions \
			   -Wall -Wno-strict-aliasing $(foreach dir,$(INCLUDE),-I$(dir)) \
			   -DPS2EMU -DPS2NETEMU
CFLAGS += --std=gnu99
LDFLAGS= -T ldscript.ld -nostartfiles -nostdlib -nodefaultlibs -Wl,-static -Wl,-s -L. $(foreach dir,$(LIBSDIR),-L$(dir)) $(LIBS) \
	-Wl,--gc-sections -Wl,-Map=

INCLUDE		= ../common ../../ps2emu/include ../../lv1/include
INCLUDE		+= $(PS3DEV)/ppu/ppu/include

define do_payload
	@rm -f *.o ../../ps2emu/src/*.o ../../lv1/src/*.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -ffreestanding -c -o start.o start.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -ffreestanding -c -o main.o main.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -ffreestanding -c -o ../../ps2emu/src/libc.o ../../ps2emu/src/libc.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -ffreestanding -c -o ../../ps2emu/src/libc_c.o ../../ps2emu/src/libc_c.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -ffreestanding -c -o ../../ps2emu/src/memory.o ../../ps2emu/src/memory.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -ffreestanding -c -o ../../ps2emu/src/io.o ../../ps2emu/src/io.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -ffreestanding -c -o ../../ps2emu/src/patch.o ../../ps2emu/src/patch.S
	$(CC) $(LDFLAGS)ps2netemu_stage2_$@.map -o ps2netemu_stage2_$@.elf start.o main.o \
	../../ps2emu/src/libc.o ../../ps2emu/src/libc_c.o ../../ps2emu/src/memory.o ../../ps2emu/src/io.o ../../ps2emu/src/patch.o
	$(OBJCOPY) -O binary ps2netemu_stage2_$@.elf ps2netemu_stage2_$@.bin
	@rm -f *.o ../../ps2emu/src/*.o ../../lv1/src/*.o
endef

all: $(PAYLOADS)

$(PAYLOADS):
	$(do_payload)

clean:
	rm -f *.o *.elf *.bin *.map ../../ps2emu/src/*.o ../../lv1/src/*.o
