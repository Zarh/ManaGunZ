#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "common.h"

enum {
	DEV_TYPE_STOR_DISK = 0,
	DEV_TYPE_GELIC = 3,
	DEV_TYPE_USB = 4,
	DEV_TYPE_STOR_ROM = 5,
	DEV_TYPE_SB_GPIO = 6,
	DEV_TYPE_STOR_FLASH = 14,
};

int map_dma_mem(int bus_id, int dev_id, void* start, uint64_t size, uint64_t* bus_addr);
int unmap_dma_mem(int bus_id, int dev_id, uint64_t bus_addr, uint64_t size);

int find_device_by_type(int type, int index, int* bus_id, int* dev_id, int* irq);

#endif