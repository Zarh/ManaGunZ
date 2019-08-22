include ../Makefile.common

PS3DEV2:=$(PS3SDK)/ps3dev2

CFLAGS += -DPS2NETEMU

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

all: $(PS2_PAYLOADS)

$(PS2_PAYLOADS):
	$(do_payload)

clean:
	rm -f *.o *.elf *.bin *.map ../../ps2emu/src/*.o ../../lv1/src/*.o
