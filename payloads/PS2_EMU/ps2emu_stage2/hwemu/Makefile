include ../Makefile.common

PS3DEV2:=$(PS3SDK)/ps3dev2

CFLAGS += -DPS2HWEMU

define do_payload
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o start.o start.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o crt0.o crt0.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o main.o main.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/libc.o ../../ps2emu/src/libc.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/libc_c.o ../../ps2emu/src/libc_c.c
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/memory.o ../../ps2emu/src/memory.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/io.o ../../ps2emu/src/io.S
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -c -o ../../ps2emu/src/patch.o ../../ps2emu/src/patch.S
	$(CC) $(LDFLAGS)ps2hwemu_stage2_$@.map -o ps2hwemu_stage2_$@.elf start.o crt0.o main.o \
	../../ps2emu/src/libc.o ../../ps2emu/src/libc_c.o ../../ps2emu/src/memory.o ../../ps2emu/src/io.o ../../ps2emu/src/patch.o
	$(OBJCOPY) -O binary ps2hwemu_stage2_$@.elf ps2hwemu_stage2_$@.bin
	@rm -f *.elf *.map *.o ../../ps2emu/src/*.o ../../lv1/src/*.o ../../debug/src/*.o
endef

all: $(PS2_PAYLOADS)

$(PS2_PAYLOADS):
	$(do_payload)

clean:
	rm -f *.o *.elf *.bin *.map ../../ps2emu/src/*.o ../../lv1/src/*.o ../../debug/src/*.o
