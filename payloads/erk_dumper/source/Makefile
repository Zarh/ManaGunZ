CC      := ppu-gcc
OBJCOPY := ppu-objcopy

TARGET = erk_dumper

CFLAGS = -std=c99 -m64 -fno-builtin -fno-exceptions -fdata-sections -ffunction-sections -Os -Wno-strict-aliasing -Wno-multichar -Wall -I.
ifeq ($(BUILD_TYPE),debug)
	CFLAGS += -DDEBUG
endif
CFLAGS += -D__STDC_FORMAT_MACROS
ASFLAGS = -m64 -Os -Wall -I.
ASFLAGS += -D__ASSEMBLY__
ifeq ($(BUILD_TYPE),debug)
	ASFLAGS += -DDEBUG
endif
LDFLAGS = -Tldscript.ld -nostartfiles -nostdlib -nodefaultlibs -Wl,--gc-sections -Wl,-Map=$(TARGET)_$@.map

include ../../FIRMWARES

define do_payload
	$(CC) $(ASFLAGS) -DFIRMWARE_$@ -c start.S -o start.S.o
	$(CC) $(ASFLAGS) -DFIRMWARE_$@ -c kernel.S -o kernel.S.o
	$(CC) $(ASFLAGS) -DFIRMWARE_$@ -c hypervisor.S -o hypervisor.S.o
	$(CC) $(ASFLAGS) -DFIRMWARE_$@ -c syscalls.S -o syscalls.S.o
	$(CC) $(ASFLAGS) -DFIRMWARE_$@ -c util.S -o util.S.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c main.c -o main.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c device.c -o device.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c network.c -o network.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c mm.c -o mm.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c kernel.c -o kernel.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c hypervisor.c -o hypervisor.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c spu.c -o spu.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c debug.c -o debug.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c util.c -o util.c.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@  -c dumper.c -o dumper.c.o
	$(CC) $(LDFLAGS) -L. -o $(TARGET)_$@.elf start.S.o kernel.S.o hypervisor.S.o syscalls.S.o util.S.o main.c.o device.c.o network.c.o mm.c.o kernel.c.o hypervisor.c.o spu.c.o debug.c.o util.c.o dumper.c.o
	$(OBJCOPY) -O binary $(TARGET)_$@.elf $(TARGET)_$@.bin
	mv -f $(TARGET)_$@.bin ../bin/$(TARGET)_$@.bin
	rm -f *.o *.elf *.bin *.map
endef

			
all: $(PAYLOADS)

$(PAYLOADS):
	$(do_payload)
	@echo ----------------------------------------------------------------

clean:
	rm -f *.o *.elf *.bin *.map
