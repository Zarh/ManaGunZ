#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <lv1/inttypes.h>

typedef struct
{
	uint16_t size; // size of structure, this will be set automatically by the library
	uint16_t checksum; // this check now is disabled
	u8 bd_video_region; // One of BDRegion, or 0 for default
	u8 dvd_video_region; // One of DVDRegion or 0 for default
	u8 ps2softemu; // Non-zero to show ps2 discs in non bc consoles
	u32 spoof_version;  // deprecated (use SEN Enabler for version spoofer) // version in BCD, eg. 0x0484, Max value: 0x0999
	u32 spoof_revision; // deprecated (use SEN Enabler for version spoofer) // revision number (decimal), MAx value: 99999
	u8 fan_speed; // 0 = Disabled, 1 = SYSCON, 2 = Dynamic Fan Controller, 0x33 to 0xFF = Set manual fan speed
	u8 allow_restore_sc;	// 1 = Allow to restore CFW syscalls | 0 = Does not allow to restore CFW syscalls
	u8 skip_existing_rif;	// 1 = skip if .rif already exists   | 0 = Skip if .rif already exists
	u8 photo_gui;			// 1 = Allow Photo GUI               | 0 = Does not allow Photo GUI
	u8 auto_earth;			// deprecated
	u8 auto_dev_blind;		// 1 = Allow auto-mount /dev_blind   | 0 = Does not allow auto-mount /dev_blind
} __attribute__((packed)) MambaConfig;

extern MambaConfig config;

int read_mamba_config(void);

// Syscalls
int sys_read_mamba_config(MambaConfig *cfg);
int sys_write_mamba_config(MambaConfig *cfg);

#endif /* __CONFIG_H__ */
