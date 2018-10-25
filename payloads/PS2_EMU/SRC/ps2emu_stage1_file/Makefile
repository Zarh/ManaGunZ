PAYLOADS := 421 430 431 440 441 446 450 453 455 460 465 466 470 475 476 478 480 481 482 483

CC			:= ppu-gcc
STRIP		:= ppu-strip
OBJCOPY		:= ppu-objcopy
CFLAGS		+=-mno-toc -ffunction-sections -fdata-sections -Os $(INC) -DPS2EMU
LDFLAGS		=-Tldscript.ld -nostartfiles -nostdlib -nodefaultlibs -Wl,--gc-sections
INC			=-I. -I../ps2emu/include

define do_payload
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -DPS2HWEMU -c start.S -o start.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -DPS2HWEMU -c icache.S -o icache.o
	$(CC) $(LDFLAGS) start.o icache.o -o ps2hwemu_stage1_$@.elf
	$(STRIP) -s ps2hwemu_stage1_$@.elf
	@$(OBJCOPY) -j .start -j .text -j .data -j .got -j .bss -O binary ps2hwemu_stage1_$@.elf ps2hwemu_stage1_$@.bin
	@rm -f *.elf *.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -DPS2GXEMU -c start.S -o start.o
	$(CC) $(CFLAGS) -DFIRMWARE_$@ -DPS2GXEMU -c icache.S -o icache.o
	$(CC) $(LDFLAGS) start.o icache.o -o ps2gxemu_stage1_$@.elf
	$(STRIP) -s ps2gxemu_stage1_$@.elf
	@$(OBJCOPY) -j .start -j .text -j .data -j .got -j .bss -O binary ps2gxemu_stage1_$@.elf ps2gxemu_stage1_$@.bin
	@rm -f *.elf *.o
endef

all: $(PAYLOADS)

$(PAYLOADS):
	$(do_payload)

clean:
	rm -f *.elf *.o *.bin
