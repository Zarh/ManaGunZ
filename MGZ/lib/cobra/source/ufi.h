#ifndef __UFI_H__
#define __UFI_H__

#define UFI_CMD_INQUIRY		0x12

typedef struct _UfiCmdInquiry
{
	uint8_t opcode;
	uint8_t lun_rv_evpd;
	uint8_t page_code;
	uint8_t reserved;
	uint8_t alloc_length;
	uint8_t reserved2[7];	
} __attribute__((packed)) UfiCmdInquiry;

typedef struct _UfiInquiryResponse
{
	uint8_t rv_pdt;
	uint8_t rmb_rv;
	uint8_t iso_ecma_ansi_version;
	uint8_t rv_rdf;
	uint8_t additional_length;
	uint8_t reserved[3];
	char vendor[8];
	char product[16];
	char revision[4];
} __attribute__((packed)) UfiInquiryResponse;

#endif

