#include "hypervisor.h"

uint64_t vas_get_id(void) {
	uint64_t pu_id;
	uint64_t vas_id;

	lv1_get_logical_pu_id(&pu_id);
	lv1_get_virtual_address_space_id_of_pu(pu_id, &vas_id);

	return vas_id;
}
