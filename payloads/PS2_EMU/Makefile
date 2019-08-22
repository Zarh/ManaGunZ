
all:
	@$(MAKE) all -C ps2emu_stage1_file --no-print-directory
	@$(MAKE) all -C ps2emu_stage2/hwemu --no-print-directory
	@$(MAKE) all -C ps2emu_stage2/gxemu --no-print-directory
	@$(MAKE) all -C ps2emu_stage2/netemu --no-print-directory
	mkdir -p BIN
	mv -f ps2emu_stage1_file/*.bin BIN
	mv -f ps2emu_stage2/hwemu/*.bin BIN
	mv -f ps2emu_stage2/gxemu/*.bin BIN
	mv -f ps2emu_stage2/netemu/*.bin BIN

clean:
	@$(MAKE) clean -C ps2emu_stage1_file --no-print-directory
	@$(MAKE) clean -C ps2emu_stage2/hwemu --no-print-directory
	@$(MAKE) clean -C ps2emu_stage2/gxemu --no-print-directory
	@$(MAKE) clean -C ps2emu_stage2/netemu --no-print-directory
