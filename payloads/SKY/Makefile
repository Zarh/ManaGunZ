PPU_CC = ppu-gcc
PPU_OBJCOPY = ppu-objcopy

PAYLOADS := 421C 421D 430C 430D 431C 440C 441C 441D 446C 446D 450C 450D 453C 453D 455C 455D 460C \
			465C 465D 470C 470D 475C 475D 476C 476D 478C 478D 480C 480D 481C 481D 482C 482D 483C

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


