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

#ifdef FAN_CONTROL
extern uint8_t set_fan_speed;		// fan_control.h
void load_fan_control(void);
#endif
#ifdef DO_AUTO_MOUNT_DEV_BLIND
extern uint8_t auto_dev_blind;		// homebrew_blocker.h
#endif
#ifdef DO_AUTO_RESTORE_SC
extern uint8_t allow_restore_sc;	// homebrew_blocker.h
#endif
#ifdef DO_PHOTO_GUI
extern uint8_t photo_gui;			// mappath.c
#endif
#ifdef DO_AUTO_EARTH
extern uint8_t auto_earth;			// mappath.c
#endif
#ifdef MAKE_RIF
extern uint8_t skip_existing_rif;	// make_rif.h;
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

	if(cfg->size == 0)
	{
		#ifdef MAKE_RIF
		config.skip_existing_rif = 1;
		#endif
		#ifdef DO_AUTO_MOUNT_DEV_BLIND
		config.auto_dev_blind = 1;
		#endif
		#ifdef DO_AUTO_RESTORE_SC
		config.allow_restore_sc = 1;
		#endif
		#ifdef DO_PHOTO_GUI
		config.photo_gui = 1;
		#endif
	}

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
	#ifdef MAKE_RIF
	skip_existing_rif = config.skip_existing_rif;
	#endif
	#ifdef DO_AUTO_MOUNT_DEV_BLIND
	auto_dev_blind   = config.auto_dev_blind;	// 1 = Allow auto-mount /dev_blind   | 0 = Does not allow auto-mount /dev_blind
	#endif
	#ifdef DO_AUTO_RESTORE_SC
	allow_restore_sc = config.allow_restore_sc;	// 1 = Allow to restore CFW syscalls | 0 = Does not allow to restore CFW syscalls
	#endif
	#ifdef DO_PHOTO_GUI
	photo_gui        = config.photo_gui;		// 1 = Allow Photo GUI				 | 0 = Does not allow Photo GUI
	#endif
	#ifdef DO_AUTO_EARTH
	auto_earth       = config.auto_earth;		// 1 = Allow auto-map earth.qrc      | 0 = Does not allow auto-map earth.qrc
	#endif
	#ifdef FAN_CONTROL
	set_fan_speed    = config.fan_speed;		// 1 = DISABLED, 1 = SYSCON, 2 = Dynamic Fan Controller, 0x33 to 0xFF = Set manual fan speed
	load_fan_control();
	#endif

	#ifdef DEBUG
		DPRINTF("Configuration read. bd_video_region=%d,dvd_video_region=%d\n",
				bd_video_region, dvd_video_region);
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

	#ifdef FAN_CONTROL
	set_fan_speed = config.fan_speed;
	#endif
	#ifdef DO_AUTO_RESTORE_SC
	allow_restore_sc = config.allow_restore_sc;
	#endif
	#ifdef DO_PHOTO_GUI
	photo_gui = config.photo_gui;
	#endif
	#ifdef DO_AUTO_EARTH
	auto_earth = config.auto_earth
	#endif
	#ifdef DO_AUTO_MOUNT_DEV_BLIND
	auto_dev_blind = config.auto_dev_blind;
	#endif
	#ifdef MAKE_RIF
	skip_existing_rif = config.skip_existing_rif;
	#endif
/*	cfg->checksum = checksum(cfg);
	copy_size = cfg->size - sizeof(config.size);
	if (copy_size < 0)
		copy_size = 0;

	memcpy(&config.checksum, &cfg->checksum, copy_size);*/
	bd_video_region  = config.bd_video_region;
	dvd_video_region = config.dvd_video_region;

	return write_mamba_config();
}
