#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef struct
{
	uint16_t size; // size of structure, this will be set automatically by the library
	uint16_t checksum; // this check now is disabled
	uint8_t bd_video_region; // One of BDRegion, or 0 for default
	uint8_t dvd_video_region; // One of DVDRegion or 0 for default
	uint8_t ps2softemu; // Non-zero to show ps2 discs in non bc consoles
	uint32_t spoof_version;  // deprecated (use SEN Enabler for version spoofer) // version in BCD, eg. 0x0484, Max value: 0x0999
	uint32_t spoof_revision; // deprecated (use SEN Enabler for version spoofer) // revision number (decimal), MAx value: 99999
	uint8_t fan_speed; // 0 = SYSCON, 1 = Dynamic Fan Controller, 0x33 to 0xFF = Set manual fan speed
} __attribute__((packed)) MambaConfig;

extern MambaConfig config;

int read_mamba_config(void);

// Syscalls
int sys_read_mamba_config(MambaConfig *cfg);
int sys_write_mamba_config(MambaConfig *cfg);

#endif /* __CONFIG_H__ */
