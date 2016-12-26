PAYLOADS := 421 430 431 440 441 446 450 453 455 460 465 466 470 475 476 478 480 481

CC			:= ppu-gcc
STRIP		:= ppu-strip
OBJCOPY		:= ppu-objcopy
CFLAGS = -ffunction-sections -fdata-sections -Os -m64 -fno-builtin -fno-exceptions \
			   -Os -Wall -Wno-strict-aliasing $(foreach dir,$(INCLUDE),-I$(dir)) \
			   -DPS2EMU -DPS2GXEMU -ffreestanding 
CFLAGS += --std=gnu99
LDFLAGS		= -nostartfiles -nostdlib -nodefaultlibs -Wl,-static -Wl,-s -L. $(foreach dir,$(LIBSDIR),-L$(dir)) $(LIBS) \
	-Wl,--gc-sections -Wl,-Map=
INCLUDE		= ../common ../../ps2emu/include ../../lv1/include ../../debug/include
INCLUDE		+= $(PS3DEV)/ppu/ppu/include

define do_payload
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o start.o start.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o crt0.o crt0.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o main.o main.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/libc.o ../../ps2emu/src/libc.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/libc_c.o ../../ps2emu/src/libc_c.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/memory.o ../../ps2emu/src/memory.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/io.o ../../ps2emu/src/io.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/vuart.o ../../ps2emu/src/vuart.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/patch.o ../../ps2emu/src/patch.S
	$(CC) -T ldscript_$@.ld  $(LDFLAGS)ps2gxemu_stage2_$@.map -o ps2gxemu_stage2_$@.elf start.o crt0.o main.o \
	../../ps2emu/src/libc.o ../../ps2emu/src/libc_c.o ../../ps2emu/src/memory.o ../../ps2emu/src/io.o \
	../../ps2emu/src/vuart.o ../../ps2emu/src/patch.o
	$(OBJCOPY) -O binary ps2gxemu_stage2_$@.elf ps2gxemu_stage2_$@.bin
	@rm -f *.o ../../ps2emu/src/*.o ../../lv1/src/*.o ../../debug/src/*.o
endef

all: $(PAYLOADS)

$(PAYLOADS):
	$(do_payload)

clean:
	rm -f *.o *.elf *.bin *.map ../../ps2emu/src/*.o ../../lv1/src/*.o ../../debug/src/*.o
