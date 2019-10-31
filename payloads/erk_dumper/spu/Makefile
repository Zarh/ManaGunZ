CC=spu-gcc
STRIP=spu-strip
BIN2C=bin2c

TARGET=dumper

ASFLAGS=-Os
CFLAGS=-ffunction-sections -fdata-sections -fno-builtin -Os
LDFLAGS=-Tldscript.ld -nostartfiles -nostdlib -nodefaultlibs -Wl,--gc-sections $(LIB)

SCETOOLS_FLAGS = --compress-data=FALSE --sce-type=SELF --key-revision=00 --self-auth-id=1FF000000C000001 --self-vendor-id=FF000000
SCETOOLS_FLAGS+= --self-type=LDR --self-app-version=0004005000000000 --self-fw-version=0000000000000000
SCETOOLS_FLAGS+= --self-ctrl-flags=0000000000000000000000000000000000000000000000000000000000000000
SCETOOLS_FLAGS+= --self-cap-flags=0000000000000000000000000000000000000000000000780000000000000000

all:
	$(CC) $(ASFLAGS) -c start.s
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(LDFLAGS) start.o main.o -o $(TARGET).elf
	$(STRIP) $(TARGET).elf
	fake_scetool $(SCETOOLS_FLAGS) --encrypt $(shell pwd)/$(TARGET).elf $(shell pwd)/$(TARGET).spu.self
	$(BIN2C) -n $(TARGET)_payload -o $(TARGET).c $(TARGET).spu.self
	mv $(TARGET).c ../source/$(TARGET).c
	rm -f *.elf *.self *.o
	
clean:
	rm -f *.elf *.self *.o
