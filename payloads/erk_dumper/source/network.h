#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "common.h"

int net_startup(void);
int net_shutdown(void);

int has_net_support(void);

int net_send(const uint8_t dest_mac_addr[], uint16_t proto, const void* data, uint64_t size);
int net_send_data(const uint8_t dest_mac_addr[], uint16_t proto, const void* data, uint64_t size);

int net_recv(void* data, uint64_t max_size);
int net_recv_data(void* data, uint64_t max_size);

const uint8_t* net_get_broadcast_mac_addr(void);

/*
int net_print(const char* buffer, uint64_t size);
int net_printf(const char* format, ...) __attribute__ ((format(printf, 1, 2)));
*/

#endif