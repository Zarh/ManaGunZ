include ../FIRMWARES

PS3DEV= ps3dev
include $(PSL1GHT)/ppu_rules

export MAMBA_VER

all: $(addprefix release_, $(PAYLOADS)) $(addprefix debug_, $(PAYLOADS))

clean:
	@make -f Makefile_release clean

release: $(addprefix release_, $(PAYLOADS))

release_%:
	$(eval MAMBA_VER = $(subst release_,,$@))
	@echo building mamba_$(MAMBA_VER).bin
	@make -f Makefile_release clean --no-print-directory
	@make -f Makefile_release all --no-print-directory

debug: $(addprefix debug_, $(PAYLOADS))

debug_%:
	$(eval MAMBA_VER = $(subst debug_,,$@))
	@echo building debug/mamba_$(MAMBA_VER).bin
	@make -f Makefile_debug clean --no-print-directory
	@make -f Makefile_debug all --no-print-directory

loader:
	make -f Makefile_loader clean --no-print-directory
	make -f Makefile_loader --no-print-directory
