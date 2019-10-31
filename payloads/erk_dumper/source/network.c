#include "network.h"
#include "device.h"
#include "kernel.h"
#include "hypervisor.h"
#include "gelic.h"
#include "util.h"

#define PKT_HDR_SIZE  16
#define PKT_MAGIC     0x0FACE0FF
#define PKT_FLAG_LAST 0x00000001

struct pkt_hdr_t {
	uint32_t magic;
	uint32_t offset;
	uint32_t size;
	uint32_t flags;
};

static int net_initialized = 0;

static struct gelic_params_t params;

static uint8_t dma_buf[0x1000] __attribute__ ((aligned(32)));
static volatile struct gelic_descr_t* descr = (struct gelic_descr_t*)dma_buf;

static const uint8_t broadcast_mac_addr[VLAN_ETH_ALEN] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

int net_startup(void) {
	int result;

	int bus_id;
	int dev_id;
	uint64_t bus_addr;
	uint64_t vlan_id;
	uint64_t mac_addr;
	uint64_t dummy;

	if (net_initialized)
		return 0;

	result = find_device_by_type(DEV_TYPE_GELIC, 0, &bus_id, &dev_id, NULL);
	if (result != 0)
		return result;

	result = lv1_net_control(bus_id, dev_id, GELIC_LV1_GET_MAC_ADDRESS, 0, 0, 0, &mac_addr, &dummy);
	if (result != 0)
		return result;

	result = lv1_net_control(bus_id, dev_id, GELIC_LV1_GET_VLAN_ID, GELIC_LV1_VLAN_TX_ETHERNET_0, 0, 0, &vlan_id, &dummy);
	if (result != 0)
		vlan_id = 0;

	result = map_dma_mem(bus_id, dev_id, dma_buf, sizeof(dma_buf), &bus_addr);
	if (result != 0)
		return result;

	mac_addr = mac_addr << 16;

	lv2_memset(&params, 0, sizeof(struct gelic_params_t));
	params.bus_id = bus_id;
	params.dev_id = dev_id;
	params.bus_addr = bus_addr;
	params.vlan_id = vlan_id;
	lv2_memcpy(params.mac_addr, &mac_addr, VLAN_ETH_ALEN);

	net_initialized = 1;

	return 0;
}

int net_shutdown(void) {
	int result;

	if (!net_initialized)
		return 0;

	result = unmap_dma_mem(params.bus_id, params.dev_id, params.bus_addr, sizeof(dma_buf));
	if (result != 0)
		return -1;

	lv2_memset(&descr, 0, sizeof(struct gelic_descr_t));
	lv2_memset(&params, 0, sizeof(struct gelic_params_t));

	return 0;
}

int has_net_support(void) {
	return net_initialized;
}

int net_send(const uint8_t dest_mac_addr[VLAN_ETH_ALEN], uint16_t proto, const void* data, uint64_t size) {
	int result;

	struct vlan_eth_hdr_t* vlan_eth_hdr;

	if (size > VLAN_ETH_DATA_LEN)
		return -1;

	descr->dmac_cmd_status = GELIC_DESCR_DMA_CARDOWNED | GELIC_DESCR_TX_DMA_IKE | GELIC_DESCR_TX_DMA_NO_CHKSUM | GELIC_DESCR_TX_DMA_FRAME_TAIL;
	descr->next_descr_addr = 0;
	descr->result_size = 0;
	descr->valid_size = 0;
	descr->data_status = 0;
	descr->data_error = 0;
	descr->buf_addr = params.bus_addr + 0x100;
	descr->buf_size = VLAN_ETH_HLEN + size;

	vlan_eth_hdr = (struct vlan_eth_hdr_t*)((uint8_t*)descr + 0x100);
	lv2_memcpy(vlan_eth_hdr->dest, dest_mac_addr, VLAN_ETH_ALEN);
	lv2_memcpy(vlan_eth_hdr->src, params.mac_addr, VLAN_ETH_ALEN);
	vlan_eth_hdr->proto = ETH_P_8021Q;
	vlan_eth_hdr->tci = params.vlan_id & VLAN_VID_MASK;
	vlan_eth_hdr->encap_proto = proto;
	lv2_memcpy((uint8_t*)vlan_eth_hdr + VLAN_ETH_HLEN, data, size);

	wmb();

	result = lv1_net_start_tx_dma(params.bus_id, params.dev_id, params.bus_addr, 0);
	if (result != 0)
		return result;

	for (;;) {
		if (!((descr->dmac_cmd_status & GELIC_DESCR_DMA_STAT_MASK) == GELIC_DESCR_DMA_CARDOWNED))
			break;
	}

	return 0;
}

int net_send_data(const uint8_t dest_mac_addr[VLAN_ETH_ALEN], uint16_t proto, const void* data, uint64_t size) {
	int result;

	uint64_t offset;
	uint64_t pkt_size;
	int i;

	offset = 0;

	while (offset < size) {
		pkt_size = MIN(size - offset, ETH_DATA_LEN);

		result = net_send(dest_mac_addr, proto, (uint8_t*)data + offset, pkt_size);
		if (result != 0)
			return result;

		offset += pkt_size;

		for (i = 0; i < 100000; ++i)
			__asm__ __volatile__ ("nop");
	}

	return 0;
}

int net_recv(void* data, uint64_t max_size) {
	int result;

	int status;
	int size;
	int n;

again:
	descr->dmac_cmd_status = GELIC_DESCR_DMA_CARDOWNED;
	descr->next_descr_addr = 0;
	descr->result_size = 0;
	descr->valid_size = 0;
	descr->data_status = 0;
	descr->data_error = 0;
	descr->buf_addr = params.bus_addr + 0x100;
	descr->buf_size = GELIC_NET_MAX_MTU;

	wmb();

	result = lv1_net_start_rx_dma(params.bus_id, params.dev_id, params.bus_addr, 0);
	if (result != 0)
		return result;

	for (;;) {
		if (!((descr->dmac_cmd_status & GELIC_DESCR_DMA_STAT_MASK) == GELIC_DESCR_DMA_CARDOWNED))
			break;
	}

	status = descr->dmac_cmd_status & GELIC_DESCR_DMA_STAT_MASK;
	if (status == GELIC_DESCR_DMA_NOT_IN_USE || status == GELIC_DESCR_DMA_RESPONSE_ERROR || status == GELIC_DESCR_DMA_PROTECTION_ERROR || status == GELIC_DESCR_DMA_FORCE_END)
		goto again;

	descr->next_descr_addr = 0;
	descr->dmac_cmd_status &= ~GELIC_DESCR_DMA_STAT_MASK;
	descr->dmac_cmd_status |= GELIC_DESCR_DMA_NOT_IN_USE;

	wmb();

	if (descr->valid_size)
		size = descr->valid_size;
	else
		size = descr->result_size;

	n = MIN(size, max_size);

	lv2_memcpy(data, (uint8_t*)descr + 0x100, n);

	return n;
}

int net_recv_data(void* data, uint64_t max_size) {
 	int result;

	uint8_t buf[ETH_FRAME_LEN + 2];
	struct eth_hdr_t* eth_hdr;
	struct pkt_hdr_t* pkt_hdr;
	uint64_t offset;
	uint32_t flags;

	offset = 0;

	for (;;) {
		result = net_recv(buf, ETH_FRAME_LEN + 2);
		if (result < (ETH_HLEN + 2 + PKT_HDR_SIZE))
			continue;

		eth_hdr = (struct eth_hdr_t*)(buf + 2);
		pkt_hdr = (struct pkt_hdr_t*)(eth_hdr + 1);

		if (pkt_hdr->magic != PKT_MAGIC)
			continue;
		if (offset != pkt_hdr->offset)
			continue;

		lv2_memcpy((uint8_t*)data + offset, pkt_hdr + 1, pkt_hdr->size);

		offset += pkt_hdr->size;
		flags = pkt_hdr->flags;

		pkt_hdr->magic = PKT_MAGIC;
		pkt_hdr->offset = offset;
		pkt_hdr->size = 0;
		pkt_hdr->flags = 0;
		if (flags & PKT_FLAG_LAST)
			pkt_hdr->flags |= PKT_FLAG_LAST;

		result = net_send_data(eth_hdr->src, eth_hdr->proto, pkt_hdr, sizeof(struct pkt_hdr_t));
		if (result != 0)
			return result;

		if (flags & PKT_FLAG_LAST)
			break;
	}

	return offset;
}

const uint8_t* net_get_broadcast_mac_addr(void) {
	return broadcast_mac_addr;
}
