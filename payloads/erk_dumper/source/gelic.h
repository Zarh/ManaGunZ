#ifndef __GELIC_H__
#define __GELIC_H__

#define GELIC_NET_MAX_MTU VLAN_ETH_FRAME_LEN

#define GELIC_BUS_ID 1
#define GELIC_DEV_ID 0

#define GELIC_PORT_ETHERNET_0 0
#define GELIC_PORT_WIRELESS   1

#define GELIC_LV1_GET_MAC_ADDRESS      1
#define GELIC_LV1_GET_ETH_PORT_STATUS  2
#define GELIC_LV1_SET_NEGOTIATION_MODE 3
#define GELIC_LV1_GET_VLAN_ID          4
#define GELIC_LV1_SET_WOL              5
#define GELIC_LV1_GET_CHANNEL          6
#define GELIC_LV1_POST_WLAN_CMD        9
#define GELIC_LV1_GET_WLAN_CMD_RESULT  10
#define GELIC_LV1_GET_WLAN_EVENT       11

#define GELIC_LV1_VLAN_TX_ETHERNET_0 0x0000000000000002L
#define GELIC_LV1_VLAN_TX_WIRELESS   0x0000000000000003L
#define GELIC_LV1_VLAN_RX_ETHERNET_0 0x0000000000000012L
#define GELIC_LV1_VLAN_RX_WIRELESS   0x0000000000000013L

#define GELIC_DESCR_DMA_COMPLETE         0x00000000
#define GELIC_DESCR_DMA_BUFFER_FULL      0x00000000
#define GELIC_DESCR_DMA_RESPONSE_ERROR   0x10000000
#define GELIC_DESCR_DMA_PROTECTION_ERROR 0x20000000
#define GELIC_DESCR_DMA_FRAME_END        0x40000000
#define GELIC_DESCR_DMA_FORCE_END        0x50000000
#define GELIC_DESCR_DMA_CARDOWNED        0xA0000000
#define GELIC_DESCR_DMA_NOT_IN_USE       0xB0000000
#define GELIC_DESCR_DMA_STAT_MASK        0xF0000000

#define GELIC_DESCR_TX_DMA_IKE        0x00080000
#define GELIC_DESCR_TX_DMA_FRAME_TAIL 0x00040000
#define GELIC_DESCR_TX_DMA_TCP_CHKSUM 0x00020000
#define GELIC_DESCR_TX_DMA_UDP_CHKSUM 0x00030000
#define GELIC_DESCR_TX_DMA_NO_CHKSUM  0x00000000
#define GELIC_DESCR_TX_DMA_CHAIN_END  0x00000002

#define GELIC_DESCR_RXDMADU   0x80000000
#define GELIC_DESCR_RXLSTFBF  0x40000000
#define GELIC_DESCR_RXIPCHK   0x20000000
#define GELIC_DESCR_RXTCPCHK  0x10000000
#define GELIC_DESCR_RXWTPKT   0x00C00000
#define GELIC_DESCR_RXVLNPKT  0x00200000
#define GELIC_DESCR_RXRRECNUM 0x0000ff00

#define GELIC_DESCR_RXALNERR     0x40000000
#define GELIC_DESCR_RXOVERERR    0x20000000
#define GELIC_DESCR_RXRNTERR     0x10000000
#define GELIC_DESCR_RXIPCHKERR   0x08000000
#define GELIC_DESCR_RXTCPCHKERR  0x04000000
#define GELIC_DESCR_RXDRPPKT     0x00100000
#define GELIC_DESCR_RXIPFMTERR   0x00080000
#define GELIC_DESCR_RXDATAERR    0x00020000
#define GELIC_DESCR_RXCALERR     0x00010000
#define GELIC_DESCR_RXCREXERR    0x00008000
#define GELIC_DESCR_RXMLTCST     0x00004000

#define VLAN_HLEN          4
#define VLAN_ETH_ALEN      6
#define VLAN_ETH_HLEN      18
#define VLAN_ETH_DATA_LEN  1500
#define VLAN_ETH_FRAME_LEN 1518
#define VLAN_VID_MASK      0x0FFF

#define ETH_ALEN      6
#define ETH_HLEN      14
#define ETH_DATA_LEN  1500
#define ETH_FRAME_LEN 1518
#define ETH_FCS_LEN   4
#define ETH_P_IP      0x0800
#define ETH_P_8021Q   0x8100

#define IPV4_VERSION     4
#define IPV4_MAX_TTL     255
#define IPV4_DEFAULT_TTL 64

struct vlan_hdr_t {
	uint16_t tci;
	uint16_t encap_proto;
};

struct vlan_eth_hdr_t {
	uint8_t dest[VLAN_ETH_ALEN];
	uint8_t src[VLAN_ETH_ALEN];
	uint16_t proto;
	uint16_t tci;
	uint16_t encap_proto;
};

struct eth_hdr_t {
	uint8_t dest[ETH_ALEN];
	uint8_t src[ETH_ALEN];
	uint16_t proto;
};

struct ipv4_hdr {
	uint8_t version: 4;
	uint8_t ihl: 4;
	uint8_t tos;
	uint16_t total_len;
	uint16_t id;
	uint16_t frag_off;
	uint8_t ttl;
	uint8_t proto;
	uint16_t cksum;
	uint32_t src;
	uint32_t dest;
};

struct gelic_params_t {
	int bus_id;
	int dev_id;
	uint64_t bus_addr;
	uint64_t vlan_id;
	uint8_t mac_addr[VLAN_ETH_ALEN];
};

struct gelic_descr_t {
	uint32_t buf_addr;
	uint32_t buf_size;
	uint32_t next_descr_addr;
	uint32_t dmac_cmd_status;
	uint32_t result_size;
	uint32_t valid_size;
	uint32_t data_status;
	uint32_t data_error;
};

#endif