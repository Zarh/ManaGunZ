#ifndef __SCSI_H__
#define __SCSI_H__

#define SCSI_CMD_TEST_UNIT_READY				0x00
#define SCSI_CMD_REQUEST_SENSE					0x03
#define SCSI_CMD_FORMAT_UNIT					0x04
#define SCSI_CMD_FORMAT_INQUIRY					0x12
#define SCSI_CMD_START_STOP_UNIT				0x1B
#define SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL	0x1E
#define SCSI_CMD_READ_FORMAT_CAPACITIES			0x23
#define SCSI_CMD_READ_CAPACITY					0x25
#define SCSI_CMD_READ_10						0x28
#define SCSI_CMD_WRITE_10						0x2A
#define SCSI_CMD_SEEK_10						0x2B
#define SCSI_CMD_WRITE_AND_VERIFY_10			0x2E
#define SCSI_CMD_VERIFY_10						0x2F
#define SCSI_CMD_SYNCHRONIZE_CACHE				0x35
#define SCSI_CMD_WRITE_BUFFER					0x3B
#define SCSI_CMD_READ_BUFFER					0x3C
#define SCSI_CMD_READ_TOC_PMA_ATIP				0x43
#define SCSI_CMD_GET_CONFIGURATION				0x46
#define SCSI_CMD_GET_EVENT_STATUS_NOTIFICATION	0x4A
#define SCSI_CMD_READ_DISC_INFORMATION			0x51
#define SCSI_CMD_READ_TRACK_INFORMATION			0x52
#define SCSI_CMD_RESERVE_TRACK					0x53
#define SCSI_CMD_SEND_OPC_INFORMATION			0x54
#define SCSI_CMD_MODE_SELECT_10					0x55
#define SCSI_CMD_REPAIR_TRACK					0x58
#define SCSI_CMD_MODE_SENSE_10					0x5A
#define SCSI_CMD_CLOSE_TRACK_SESSION			0x5B
#define SCSI_CMD_READ_BUFFER_CAPACITY			0x5C
#define SCSI_CMD_SEND_CUE_SHEET					0x5D
#define SCSI_CMD_REPORT_LUNS					0xA0
#define SCSI_CMD_BLANK							0xA1
#define SCSI_CMD_SECURITY_PROTOCOL_IN			0xA2
#define SCSI_CMD_SEND_KEY						0xA3
#define SCSI_CMD_REPORT_KEY						0xA4
#define SCSI_CMD_LOAD_UNLOAD_MEDIUM				0xA6
#define SCSI_CMD_SET_READ_AHEAD					0xA7
#define SCSI_CMD_READ_12						0xA8
#define SCSI_CMD_WRITE_12						0xAA
#define SCSI_CMD_READ_MEDIA_SERIAL_NUMBER		0xAB
#define SCSI_CMD_GET_PERFORMANCE				0xAC
#define SCSI_CMD_READ_DISC_STRUCTURE			0xAD
#define SCSI_CMD_SECURITY_PROTOCOL_OUT			0xB5
#define SCSI_CMD_SET_STREAMING					0xB6
#define SCSI_CMD_READ_CD_MSF					0xB9
#define SCSI_CMD_SET_CD_SPEED					0xBB
#define SCSI_CMD_MECHANISM_STATUS				0xBD
#define SCSI_CMD_READ_CD 						0xBE
#define SCSI_CMD_SEND_DISC_STRUCTURE			0xBF
#define SCSI_CMD_READ_2064						0xD1 /* Not reall name. Not standard cmd? */

#define itob(i)               					((i)/10*16 + (i)%10)

enum DvdBookType
{
	BOOKTYPE_DVDROM,
	BOOKTYPE_DVDRAM,
	BOOKTYPE_DVDMR,
	BOOKTYPE_DVDMRW,
	BOOKTYPE_HDDVDROM,
	BOOKTYPE_HDDVDRAM,
	BOOKTYPE_HDDVDR,
	BOOKTYPE_DVDPRW = 9,
	BOOKTYPE_DVDPR,
	BOOKTYPE_DVDPRWDL = 13,
	BOOKTYPE_DVDPRDL
};

typedef struct _ScsiCmdTestUnitReady
{
	u8 opcode;
	u8 reserved[4];
	u8 control;
} __attribute__((packed)) ScsiCmdTestUnitReady;

enum
{
	FORMAT_TOC,
	FORMAT_SESSION_INFO,
	FORMAT_FULL_TOC,
	FORMAT_PMA,
	FORMAT_ATIP,
	FORMAT_CDTEXT
};

typedef struct _ScsiCmdReadTocPmaAtip
{
	u8 opcode;
	u8 rv_msf;
	u8 rv_format;
	u8 reserved[3];
	u8 track_session_num;
	uint16_t alloc_length;
	u8 control;
} __attribute__((packed)) ScsiCmdReadTocPmaAtip;

typedef struct _ScsiTocResponse
{
	uint16_t toc_length;
	u8 first_track;
	u8 last_track;
} __attribute__((packed)) ScsiTocResponse;

typedef struct _ScsiTrackDescriptor
{
	u8 reserved;
	u8 adr_control;
	u8 track_number;
	u8 reserved2;
	u32 track_start_addr;
} __attribute__((packed)) ScsiTrackDescriptor;

typedef struct _ScsiFullTrackDescriptor
{
	u8 session_number;
	u8 adr_control;
	u8 tno;
	u8 point;
	u8 min;
	u8 sec;
	u8 frame;
	u8 zero;
	u8 pmin;
	u8 psec;
	u8 pframe;
} __attribute__((packed)) ScsiFullTrackDescriptor;

typedef struct _ScsiCmdReadTrackInformation
{
	u8 opcode;
	u8 rv_o_type;
	u32 lba_tsn;
	u8 reserved;
	uint16_t alloc_length;
	u8 control;
} __attribute__((packed)) ScsiCmdReadTrackInformation;

typedef struct _ScsiReadTrackInformationResponse
{
	uint16_t length;
	u8 ltn;
	u8 sn;
	u8 reserved;
	u8 misc;
	u8 misc2;
	u8 misc3;
	u32 lt_start_addr;
	u32 next_write_addr;
	u32 free_blocks;
	u32 fixed_packet_size;
	u32 lt_size;
	u32 lr_addr;
	u8 ltn_ms;
	u8 sn_ms;
	u8 reserved2[2];
	u32 read_compat_lba;
} __attribute__((packed)) ScsiReadTrackInformationResponse;

typedef struct _ScsiCmdGetConfiguration
{
	u8 opcode;
	u8 rv_rt;
	uint16_t starting_feature_number;
	u8 reserved[3];
	uint16_t alloc_length;
	u8 control;
} __attribute__((packed)) ScsiCmdGetConfiguration;

typedef struct _ScsiCmdGetEventStatusNotification
{
	u8 opcode;
	u8 rv_polled;
	u8 reserved[2];
	u8 notification_class_request;
	u8 reserved2[2];
	uint16_t alloc_length;
	u8 control;
} __attribute__((packed)) ScsiCmdGetEventStatusNotification;

typedef struct _ScsiEventHeader
{
	uint16_t event_length;
	u8 nea_rv_nc;
	u8 supported_event_class;
} __attribute__((packed)) ScsiEventHeader;

typedef struct _ScsiMediaEventResponse
{
	ScsiEventHeader event_header;
	u8 rv_ec;
	u8 media_status;
	u8 start_slot;
	u8 end_slot;
} __attribute__((packed)) ScsiMediaEventResponse;

typedef struct _ScsiCmdReadCd
{
	u8 opcode;
	u8 rv_est_raddr;
	u32 lba;
	u8 length[3];
	u8 misc;
	u8 rv_scsb;
	u8 control;
} __attribute__((packed)) ScsiCmdReadCd;

typedef struct _SubChannelQ
{
	u8 control_adr;
	u8 track_number;
	u8 index_number;
	u8 min;
	u8 sec;
	u8 frame;
	u8 zero;
	u8 amin;
	u8 asec;
	u8 aframe;
	uint16_t crc;
	u8 pad[3];
	u8 p;
} __attribute__((packed)) SubChannelQ;

typedef struct _ScsiCmdReadDiscInformation
{
	u8 opcode;
	u8 reserved[6];
	uint16_t alloc_length;
	u8 control;
} __attribute__((packed)) ScsiCmdReadDiscInformation;

typedef struct _ScsiReadDiscInformationResponse
{
	uint16_t length;
	u8  misc;
	u8 first_track;
	u8 num_sessions_lb;
	u8 first_track_lastsession_lb;
	u8 last_track_lastsession_lb;
	u8 misc2;
	u8 disctype;
	u8 num_sessions_mb;
	u8 first_track_lastsession_mb;
	u8 last_track_lastsession_mb;
	u32 disc_identification;
	u32 last_session_leadin;
	u32 last_session_leadout;
	u8 barcode[8];
	u8 reserved;
	u8 num_opc;
} __attribute__((packed)) ScsiReadDiscInformationResponse;

typedef struct _ScsiCmdReadDiscStructure
{
	u8 opcode;
	u8 rv_mediatype;
	u32 address;
	u8 layer_num;
	u8 format;
	uint16_t alloc_length;
	u8 reserved;
	u8 control;
} __attribute__((packed)) ScsiCmdReadDiscStructure;

typedef struct _ScsiReadDiscStructureFormat0Response
{
	uint16_t length;
	u8 reserved[2];
	u8 disccategory_partversion;
	u8 discsize_maximumrate;
	u8 misc;
	u8 density;
	u8 zero;
	u8 start_sector[3];
	u8 zero2;
	u8 end_sector[3];
	u8 zero3;
	u8 end_sector_layer0[3];
	u8 reserved2;
} __attribute__((packed)) ScsiReadDiscStructureFormat0Response;

typedef struct _ScsiRead10
{
	u8 opcode;
	u8 dpo_fua;
	u32 lba;
	u8 rv;
	uint16_t length;
	u8 control;
} __attribute__((packed)) ScsiRead10;

typedef struct _ScsiRead2064
{
	u8 opcode;
	u8 unk;
	u32 lba;
	u8 unk2[2];
	uint16_t length;
	u8 control;
} __attribute__((packed)) ScsiRead2064;

static INLINE void lba_to_msf(u64 lba, u8 *m, u8 *s, u8 *f)
{
	*m = lba/(75*60);
	*s = (lba /75) % 60;
	*f = lba % 75;
}

static INLINE void lba_to_msf_bcd(u64 lba, u8 *m, u8 *s, u8 *f)
{
	lba_to_msf(lba, m, s, f);
	*m = itob(*m);
	*s = itob(*s);
	*f = itob(*f);
}
/*
static inline u64 msf_to_lba(u8 m, u8 s, u8 f)
{
	u64 lba = m;
	lba = (lba*60)+s;
	lba = (lba*75)+f;
	return lba;
}
*/
#ifdef DEBUG

static const char * get_scsi_cmd_name(u8 cmd) __attribute__((unused));
static const char * get_scsi_cmd_name(u8 cmd)
{
	static const char *cmd_str[0x100] =
	{
		"TEST UNIT READY",
		NULL,
		NULL,
		"REQUEST SENSE",
		"FORMAT UNIT",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL, /* 0x10 */
		NULL,
		"INQUIRY",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"START STOP UNIT",
		NULL,
		NULL,
		"PREVENT ALLOW MEDIUM REMOVAL",
		NULL,
		NULL, /* 0x20 */
		NULL,
		NULL,
		"READ FORMAT CAPACITIES",
		NULL,
		"READ CAPACITY",
		NULL,
		NULL,
		"READ (10)",
		NULL,
		"WRITE (10)",
		"SEEK (10)",
		NULL,
		NULL,
		"WRITE AND VERIFY (10)",
		"VERIFY (10)",
		NULL, /* 0x30 */
		NULL,
		NULL,
		NULL,
		NULL,
		"SYNCHRONIZE CACHE",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"WRITE BUFFER",
		"READ BUFFER",
		NULL,
		NULL,
		NULL,
		NULL, /* 0x40 */
		NULL,
		NULL,
		"READ TOC/PMA/ATIP",
		NULL,
		NULL,
		"GET CONFIGURATION",
		NULL,
		NULL,
		NULL,
		"GET EVENT STATUS NOTIFICATION",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL, /* 0x50 */
		"READ DISC INFORMATION",
		"READ TRACK INFORMATION",
		"RESERVE TRACK",
		"SEND OPC INFORMATION",
		"MODE SELECT (10)",
		NULL,
		NULL,
		"REPAIR TRACK",
		NULL,
		"MODE SENSE (10)",
		"CLOSE TRACK SESSION",
		"READ BUFFER CAPACITY",
		"SEND CUE SHEET",
		NULL,
		NULL,
		NULL, /* 0x60 */
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL, /* 0x70 */
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL, /* 0x80 */
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL, /* 0x90 */
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"REPORT LUNS", /* 0xA0 */
		"BLANK",
		"SECURITY PROTOCOL IN",
		"SEND KEY",
		"REPORT KEY",
		NULL,
		"LOAD/UNLOAD MEDIUM",
		"SET READ AHEAD",
		"READ (12)",
		NULL,
		"WRITE (12)",
		"READ MEDIA SERIAL NUMBER",
		"GET PERFORMANCE",
		"READ DISC STRUCTURE",
		NULL,
		NULL,
		NULL, /* 0xB0 */
		NULL,
		NULL,
		NULL,
		NULL,
		"SECUIRTY PROTOCOL OUT",
		"SET STREAMING",
		NULL,
		NULL,
		"READ CD MSF",
		NULL,
		"SET CD SPEED",
		NULL,
		"MECHANISM STATUS",
		"READ CD",
		"SEND DISC STRUCTURE",
		NULL, /* 0xC0 */
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL, /* 0xD0 */
		"READ 2064",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL, /* 0xE0 */
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL, /* 0xF0 */
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
	};

	return cmd_str[cmd];
}

#endif

#endif /* __SCSI_H__ */

