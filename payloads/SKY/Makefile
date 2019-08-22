PPU_CC = ppu-gcc
PPU_OBJCOPY = ppu-objcopy

include ../FIRMWARES

define do_payload
	$(PPU_CC) -c payload_sky.S -o payload_sky_$@.o -DCFW_$@
	@$(PPU_OBJCOPY) -O binary payload_sky_$@.o ../../MGZ/data/payload_sky_$@.bin
endef

define do_umount
	$(PPU_CC) -c umount.S -o umount_$@.o -DCFW_$@
	@$(PPU_OBJCOPY) -O binary umount_$@.o ../../MGZ/data/umount_$@.bin
endef

all: $(PAYLOADS)

$(PAYLOADS):
	$(do_payload)
	$(do_umount)
	@rm -f *.o
	@echo ----------------------------------------------------------------


