#include <lv2/lv2.h>
#include <lv2/error.h>
#include <lv2/libc.h>
#include <lv2/io.h>
#include <lv2/memory.h>

#include "common.h"
#include "config.h"
#include "region.h"
#include "storage_ext.h"
#include "modulespatch.h"

#define MAMBA_CONFIG_FILE	"/dev_hdd0/vm/mamba_cfg.bin"

MambaConfig config;

#ifndef sysmem_obj
 #undef FAN_CONTROL
#endif

#ifdef FAN_CONTROL
int sm_set_fan_policy(uint8_t arg1, uint8_t arg2, uint8_t arg3);
void do_fan_control(void);
#endif

static void check_and_correct(MambaConfig *cfg)
{
	int found = 0;

	int i;
	for (i = 1; i <= BD_VIDEO_REGION_MAX; i *= 2)
	{
		if (cfg->bd_video_region == i)
		{
			found = 1;
			break;
		}
	}

	if (!found)
		cfg->bd_video_region = 0;
	else
		found = 0;

	for (i = 1; i <= DVD_VIDEO_REGION_MAX; i *= 2)
	{
		if (cfg->dvd_video_region == i)
		{
			found = 1;
			break;
		}
	}

	if (!found)
		cfg->dvd_video_region = 0;

	if (cfg->ps2softemu > 1)
		cfg->ps2softemu = 0;

	//cfg->spoof_version  = 0;
	//cfg->spoof_revision = 0;

	//if (cfg->size > sizeof(MambaConfig))
		cfg->size = sizeof(MambaConfig);
}
/*
static uint16_t checksum(MambaConfig *cfg)
{
	uint8_t *buf = &cfg->bd_video_region;
	uint16_t size = cfg->size - sizeof(cfg->size) - sizeof(cfg->checksum);
	uint16_t cs = 0;

	for (int i = 0; i < size; i++)
		cs += buf[i];

	return cs;
}
*/
int read_mamba_config(void)
{
	memset(&config, 0, sizeof(config));

	read_file(MAMBA_CONFIG_FILE, &config, sizeof(config));

	check_and_correct(&config);
	config.size = sizeof(config);

	bd_video_region = config.bd_video_region;
	dvd_video_region = config.dvd_video_region;

	#ifdef DEBUG
		DPRINTF("Configuration read. bd_video_region=%d,dvd_video_region=%d\n",
				bd_video_region, dvd_video_region);
	#endif

	#ifdef FAN_CONTROL
	if(config.fan_speed >= 0x33 && config.fan_speed <= 0x80)
		sm_set_fan_policy(0, 2, config.fan_speed); // Manual mode
	else if(config.fan_speed <= 1)
		sm_set_fan_policy(0, 1, 0); // SYSCON mode
	else // if(config.fan_speed >= 2 && config.fan_speed <= 0x32)
		do_fan_control();  // Dynamic fan control
	#endif

	return SUCCEEDED;
}

static int write_mamba_config(void)
{
	return save_file(MAMBA_CONFIG_FILE, &config, sizeof(config));
}

int sys_read_mamba_config(MambaConfig *cfg)
{
	//int erase_size, copy_size;

	cfg = get_secure_user_ptr(cfg);

	//if (cfg->size > 4096)
	//	return EINVAL;

/*	erase_size = cfg->size-sizeof(config.size);
	if (erase_size < 0)
		erase_size = 0;

	memset(&cfg->checksum, 0, erase_size);

	copy_size = ((cfg->size > config.size) ? config.size : cfg->size) - sizeof(config.size);
	if (copy_size < 0)
		copy_size = 0;

	#ifdef DEBUG
	DPRINTF("erase = %d, copy = %d\n", erase_size, copy_size);
	#endif
*/
	memcpy(&cfg->checksum, &config.checksum, sizeof(MambaConfig));
	return SUCCEEDED;
}

int sys_write_mamba_config(MambaConfig *cfg)
{
	//int copy_size;

	cfg = get_secure_user_ptr(cfg);

	//if (cfg->size > 4096)
	//	return EINVAL;

	memcpy(&config, &cfg, sizeof(config));

	check_and_correct(cfg);

	config.spoof_version  = 0; // deprecated
	config.spoof_revision = 0; // deprecated

/*	cfg->checksum = checksum(cfg);
	copy_size = cfg->size - sizeof(config.size);
	if (copy_size < 0)
		copy_size = 0;

	memcpy(&config.checksum, &cfg->checksum, copy_size);*/
	bd_video_region  = config.bd_video_region;
	dvd_video_region = config.dvd_video_region;

	return write_mamba_config();
}
