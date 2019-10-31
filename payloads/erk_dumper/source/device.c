#include "device.h"
#include "hypervisor.h"

int map_dma_mem(int bus_id, int dev_id, void* start, uint64_t size, uint64_t* out_bus_addr) {
	int result;

	uint64_t real_start = ((uint64_t)start) & ~0x8000000000000000ULL;
	uint64_t real_end = real_start + size;
	uint64_t map_start = real_start & ~0xFFF;
	uint64_t map_end = (real_end + 0xFFF) & ~0xFFF;
	uint64_t bus_addr;
	uint64_t flags = 0xF800000000000000ULL;

	result = lv1_allocate_device_dma_region(bus_id, dev_id, map_end - map_start, 12, 0, &bus_addr);
	if (result != 0)
		return result;
	
	result = lv1_map_device_dma_region(bus_id, dev_id, map_start, bus_addr, map_end - map_start, flags);
	if (result != 0) {
		lv1_free_device_dma_region(bus_id, dev_id, bus_addr);
		return result;
	}

	*out_bus_addr = bus_addr + real_start - map_start;

	return 0;
}

int unmap_dma_mem(int bus_id, int dev_id, uint64_t bus_addr, uint64_t size) {
	int result;

	uint64_t real_bus_addr = bus_addr & ~0xFFF;
	size += bus_addr - real_bus_addr;
	size = (size + 0xFFF) & ~0xFFF;

	result = lv1_unmap_device_dma_region(bus_id, dev_id, real_bus_addr, size);
	if (result != 0)
		return result;

	return lv1_free_device_dma_region(bus_id, dev_id, real_bus_addr);
}

int find_device_by_type(int type, int index, int* out_bus_id, int* out_dev_id, int* out_irq) {
	int result;

	uint64_t v2;
	uint64_t bus_index;

	for (bus_index = 0; bus_index < 10; ++bus_index) {
		uint64_t bus_id = 0, bus_type = 0, num_devices = 0;

		result = lv1_get_repository_node_value(LPAR_ID_PME, FIELD_FIRST("bus", bus_index), FIELD("type", 0), 0, 0, &bus_type, &v2);
		if (result != 0)
			continue;

		result = lv1_get_repository_node_value(LPAR_ID_PME, FIELD_FIRST("bus", bus_index), FIELD("id", 0), 0, 0, &bus_id, &v2);
		if (result != 0)
			continue;

		result = lv1_get_repository_node_value(LPAR_ID_PME, FIELD_FIRST("bus", bus_index), FIELD("num_dev", 0), 0, 0, &num_devices, &v2);
		if (result != 0)
			continue;

		uint64_t dev_index;
		for (dev_index = 0; dev_index < num_devices; ++dev_index) {
			int64_t dev_id = 0, dev_type = 0, dev_intr = 0;

			result = lv1_get_repository_node_value(LPAR_ID_PME, FIELD_FIRST("bus", bus_index), FIELD("dev", dev_index), FIELD("id", 0), 0, (uint64_t*)&dev_id, &v2);
			if (result != 0)
				dev_id = -1;

			result = lv1_get_repository_node_value(LPAR_ID_PME, FIELD_FIRST("bus", bus_index), FIELD("dev", dev_index), FIELD("type", 0), 0, (uint64_t*)&dev_type, &v2);
			if (result != 0)
				dev_type = -1;

			result = lv1_get_repository_node_value(LPAR_ID_PME, FIELD_FIRST("bus", bus_index), FIELD("dev", dev_index), FIELD("intr", 0), 0, (uint64_t*)&dev_intr, &v2);
			if (result != 0)
				dev_intr = -1;

			if (dev_type == type) {
				if (index) {
					index--;
					continue;
				}

				if (out_bus_id)
					*out_bus_id = bus_id;
				if (out_dev_id)
					*out_dev_id = dev_id;
				if (out_irq)
					*out_irq = dev_intr;

				return 0;
			}
		}
	}

	return -1;
}
