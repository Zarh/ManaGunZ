#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef struct
{
	uint16_t size;
	uint16_t checksum;
	uint8_t bd_video_region;
	uint8_t dvd_video_region;
	uint8_t ps2softemu;
	uint32_t spoof_version;
	uint32_t spoof_revision;
} __attribute__((packed)) MambaConfig;

extern MambaConfig config;

int read_mamba_config(void);
int save_mamba_config(void);

// Syscalls
int sys_read_mamba_config(MambaConfig *cfg);
int sys_write_mamba_config(MambaConfig *cfg);

#endif /* __CONFIG_H__ */


