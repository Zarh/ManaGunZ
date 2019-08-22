#include "scsi.h"

#define CONFIG_FILE	"/tmp/cfg.bin"

#define IS_2352() (num_tracks != 0)

static int iso_fd = -1;
static uint64_t iso_size;
static uint32_t iso_size_sectors;
static int is_dual_layer;
static int layer0_size;
static uint16_t device_type;
static int total_emulation;
static ScsiTrackDescriptor *tracks;
static uint8_t num_tracks;

static INLINE void my_memcpy(uint8_t *dst, uint8_t *src, int size)
{
	for (int i = 0; i < size; i++)
		dst[i] = src[i];
}

static INLINE void my_memcpy2(uint8_t *dst, uint8_t *src, int size)
{
	for (int i = size-1; i >= 0; i--)
		dst[i] = src[i];
}

static INLINE int cd_iso_read2048(uint8_t *buf, uint32_t lba, uint32_t length)
{
	if (IS_2352())
	{
		uint32_t capacity = length*2048;
		uint32_t fit = capacity/2352;
		uint32_t rem = (length-fit);
		uint32_t i;
		uint8_t *in = buf;
		uint8_t *out = buf;
		
		if (fit > 0)
		{
			ufs_read(iso_fd, lba*2352, buf, fit*2352);
			
			for (i = 0; i < fit; i++)
			{
				my_memcpy(out, in+24, 2048);
				in += 2352;
				out += 2048;
				lba++;
			}
		}
		
		for (i = 0; i < rem; i++)
		{
			ufs_read(iso_fd, (lba*2352)+24, out, 2048);
			out += 2048;
			lba++;
		}
	}
	else
	{
		ufs_read(iso_fd, lba*2048, buf, length*2048);
	}
	
	return 0;
}

// 2328. Offset 0 -> 2048 user data
static INLINE int cd_iso_read2328(uint8_t *buf, uint32_t lba, uint32_t length)
{
	DPRINTF("cd_iso_read2328: NOT IMPLEMENTED, calling to 2048!!!!!! (lba=%x, length=%x)\n", lba, length);
	return cd_iso_read2048(buf, lba, length);
}

// 2340. Offset 0 -> offset 12;
static INLINE int cd_iso_read2340(uint8_t *buf, uint32_t lba, uint32_t length)
{
	if (IS_2352())
	{
		uint32_t capacity = length*2340;
		uint32_t fit = capacity/2352;
		uint32_t rem = (length-fit);
		uint32_t i;
		uint8_t *in = buf;
		uint8_t *out = buf;
		
		if (fit > 0)
		{
			ufs_read(iso_fd, lba*2352, buf, fit*2352);
			
			for (i = 0; i < fit; i++)
			{
				my_memcpy(out, in+12, 2340);
				in += 2352;
				out += 2340;
				lba++;
			}
		}
		
		for (i = 0; i < rem; i++)
		{
			ufs_read(iso_fd, (lba*2352)+12, out, 2340);
			out += 2340;
			lba++;
		}
	}
	else
	{
		ufs_read(iso_fd, lba*2048, buf, length*2048);
		
		uint8_t *in = buf+(2048*(length-1));
		uint8_t *out = buf+(2340*(length-1));
		
		lba = lba+length-1;
	
		for (int i = 0; i < length; i++, in -= 2048, out -= 2340, lba--)
		{
			my_memcpy2(out+12, in, 2048);
			
			lba_to_msf_bcd(lba+150, &out[0], &out[1], &out[2]);
			out[3] = 2;
			memset(out+4, 0, 8);
			memset(out+2060, 0, 280);			
		}
	}
	
	return 0;
}

static INLINE int cd_iso_read2352(uint8_t *buf, uint32_t lba, uint32_t length)
{
	if (IS_2352())
	{
		ufs_read(iso_fd, lba*2352, buf, length*2352);
	}
	else
	{
		ufs_read(iso_fd, lba*2048, buf, length*2048);
		
		uint8_t *in = buf+(2048*(length-1));
		uint8_t *out = buf+(2352*(length-1));
		
		lba = lba+length-1;
	
		for (int i = 0; i < length; i++, in -= 2048, out -= 2352, lba--)
		{
			my_memcpy2(out+24, in, 2048);
			
			out[0] = out[11] = 0;
			memset(out+1, 0xFF, 10);
			lba_to_msf_bcd(lba+150, &out[12], &out[13], &out[14]);
			out[15] = 2;
			memset(out+16, 0, 8);
			memset(out+2072, 0, 280);
		}
	}
	
	return 0;
}

static INLINE ScsiTrackDescriptor *find_track_by_lba(uint32_t lba)
{
	int n = num_tracks;
	
	for (int i = 0; i < n; i++)
	{
		uint32_t track_start = tracks[i].track_start_addr;
		uint32_t track_end;
		
		if (i == (n-1))
		{
			track_end = iso_size_sectors;
		}
		else
		{
			track_end = tracks[i+1].track_start_addr;
		}
		
		if (lba >= track_start && lba < track_end)
		{
			return &tracks[i];
		}
	}
	
	return NULL;
}

static INLINE int cd_iso_read2364(uint8_t *buf, uint32_t lba, uint32_t length)
{
	uint32_t sector_size;
	
	if (IS_2352())
	{
		sector_size = 2352;
	}
	else
	{
		sector_size = 2048;
	}
	
	ufs_read(iso_fd, lba*sector_size, buf, length*sector_size);
		
	uint8_t *in = buf+(sector_size*(length-1));
	uint8_t *out = buf+(2364*(length-1));
		
	lba = lba+length-1;
	
	for (int i = 0; i < length; i++, in -= sector_size, out -= 2364, lba--)
	{
		SubChannelQ *subq;
		
		if (sector_size == 2048)
		{
			my_memcpy2(out+24, in, 2048);
			
			out[0] = out[11] = 0;
			memset(out+1, 0xFF, 10);
			lba_to_msf_bcd(lba+150, &out[12], &out[13], &out[14]);
			out[15] = 2;
			memset(out+16, 0, 8);
			memset(out+2072, 0, 280);
		}
		else
		{
			my_memcpy2(out, in, 2352);
		}
		
		subq = (SubChannelQ *)(out+2352);
		memset(subq, 0, sizeof(SubChannelQ));
		
		if (sector_size == 2048)
		{
			subq->control_adr = 0x41;
			subq->track_number = 1;
		}
		else
		{
			ScsiTrackDescriptor *track = find_track_by_lba(lba);
			
			if (!track)
			{
				DPRINTF("Cannot find track for lba: %x\n", lba);
				return -1;
			}
			
			subq->control_adr = ((track->adr_control << 4)&0xF0) | (track->adr_control >> 4);
			subq->track_number = track->track_number;
		}
		
		subq->index_number = 1;
		lba_to_msf_bcd(lba, &subq->min, &subq->sec, &subq->frame);
		lba_to_msf_bcd(lba+150, &subq->amin, &subq->asec, &subq->aframe);
	}
	
	return 0;
}

static INLINE int dvd_iso_read2048(uint8_t *buf, uint64_t lba, uint32_t length)
{
	ufs_read(iso_fd, lba*2048, buf, length*2048);
	return 0;
}

static INLINE int dvd_iso_read2064(uint8_t *buf, uint64_t lba, uint32_t length)
{
	if (length == 0)
	{
		DPRINTF("Length = 0!!!\n");
		return 0;
	}
	
	ufs_read(iso_fd, lba*2048, buf, length*2048);
		
	uint8_t *in = buf+(2048*(length-1));
	uint8_t *out = buf+(2064*(length-1));
	
	lba = lba+length-1;
	
	for (int i = 0; i < length; i++, in -= 2048, out -= 2064, lba--)
	{
		my_memcpy2(out+12, in, 2048);
		
		// It seems the ps2emu only cares about the sector ID...
		uint32_t id;
		
		if (!is_dual_layer || lba < layer0_size)
		{
			id = 0x030000 + lba;
		}
		else
		{
			id = 0x030000 + (lba-layer0_size);
			id |= (1 << 24); // Layer 1
		}
		
		*(uint32_t *)out = id;
		memset(out+4, 0, 8);
		memset(out+2060, 0, 4);
	}
	
	return 0;
}

#ifdef PS2HWEMU

static void *temp_buf;

static INLINE void *get_temp_buf(void)
{
	if (!temp_buf)
	{
		temp_buf = malloc(0x800);
	}
	
	return temp_buf;
}

static INLINE void release_temp_buf(void)
{
	if (temp_buf)
	{
		free(temp_buf);
		temp_buf = NULL;
	}
}

#else
#define get_temp_buf get_data_buffer
#define release_temp_buf()
#endif

static void check_double_layer(void)
{
	uint8_t *buf = get_temp_buf();
	
	dvd_iso_read2048(buf, 0x10, 1);
	
	if (buf[0] != 1 || memcmp(buf+1, "CD001", 5) != 0)
		return;
		
	uint32_t sector = *(uint32_t *)&buf[0x54];
	
	if (sector >= iso_size_sectors)
		return;
	
	dvd_iso_read2048(buf, sector, 1);
	
	if (buf[0] != 1 || memcmp(buf+1, "CD001", 5) != 0)
		return;
		
	layer0_size = sector;
	is_dual_layer = 1;
	DPRINTF("Dual layer detected. Layer1 start = 0x%x\n", layer0_size);	
}

static INLINE int setup_iso(void)
{
	int cfg_fd;
	char *buf, *file;
		
	cfg_fd = ufs_open(0, CONFIG_FILE);
	if (cfg_fd < 0)
		return -1;
		
	
	buf = get_temp_buf();

	if (ufs_read(cfg_fd, 0, buf, 0x800) <= 0)
	{
		release_temp_buf();
		ufs_close(cfg_fd);
		return -2;
	}
		
	if (memcmp(buf+1, "/dev_hdd0/", 10) != 0)
	{		
		release_temp_buf();
		ufs_close(cfg_fd);
		return -1;
	}
	if(memcmp(buf+0x702, "mount", 5)!=0)
	{
		ufs_close(cfg_fd);
		release_temp_buf();
		return -1;
	}
	//uint8_t disable=0x00;
	//ufs_write(cfg_fd, 0x702, &disable, 1);
	
	file = buf+10;
	
	iso_fd =  ufs_open(0, file);
	if (iso_fd < 0)
	{
		release_temp_buf();
		ufs_close(cfg_fd);
		return -1;
	}
	
	iso_size = get_file_size(iso_fd);
	iso_size_sectors = iso_size / 2048;
	device_type = ((buf[0]&1) == 0) ? DEVICE_TYPE_PS2_DVD : DEVICE_TYPE_PS2_CD;
	total_emulation = (buf[0]&2);
	is_dual_layer = 0;
	layer0_size = iso_size_sectors;
	
	if (device_type == DEVICE_TYPE_PS2_DVD)
	{
		check_double_layer();
	}
	else
	{
		ufs_read(cfg_fd, 0x800, &num_tracks, sizeof(num_tracks));
		if (IS_2352())
		{
			tracks = malloc(num_tracks*sizeof(ScsiTrackDescriptor));
			ufs_read(cfg_fd, 0x801, tracks, num_tracks*sizeof(ScsiTrackDescriptor));
			iso_size_sectors = iso_size / 2352;
		}
	}
	
	memset(buf, 0, 0x800);

	release_temp_buf();
	ufs_close(cfg_fd);
	
	DPRINTF("iso_size = %ld, nsectors = 0x%x. num_tracks = %d\n", iso_size, iso_size_sectors, num_tracks);	
	return 0;
}

#define GET_READ_SIZE(x) (((x)->length[0] << 16) | ((x)->length[1] << 8) | ((x)->length[2])) 

static INLINE int process_other_cmd(uint8_t *cmd, uint8_t *out, uint64_t outlen)
{
	int ret;
	
	//DPRINTF("\nOther command %02X(%s)\n", cmd[0], get_scsi_cmd_name(cmd[0]));
	
	if (total_emulation)
	{
		ret = 1;
		if (out)
		{
			memset(out, 0, outlen);
		}
	}
	else
	{
		ret = 0;
	}
	
	switch (cmd[0])
	{
		case SCSI_CMD_GET_EVENT_STATUS_NOTIFICATION: 
		{
			if (total_emulation)
			{
				ScsiCmdGetEventStatusNotification *esn = (ScsiCmdGetEventStatusNotification *)cmd;
			
				if (esn->notification_class_request == 0x10)
				{
					ScsiMediaEventResponse *resp = (ScsiMediaEventResponse *)out;
								
					memset(resp, 0, sizeof(ScsiMediaEventResponse));				
					resp->event_header.event_length = sizeof(ScsiMediaEventResponse) - sizeof(ScsiEventHeader);
					resp->event_header.nea_rv_nc = 4;
					resp->event_header.supported_event_class = 0xF;
					resp->media_status = 2;					
				}
				else
				{
					DPRINTF("Event status: %02X\n", esn->notification_class_request);
				}
			}
		}
		
		break;
		
		// Known unprocessed commands MODE_SENSE, MODE_SELECT, SEEK_10 and TEST_UNIT_READY only appear on the hw emu
		case SCSI_CMD_SET_CD_SPEED: case SCSI_CMD_MODE_SENSE_10: 
		case SCSI_CMD_MODE_SELECT_10: case SCSI_CMD_TEST_UNIT_READY:
		case SCSI_CMD_SEEK_10:
		break;		
		
		default:
			DPRINTF("\n********UNKOWN UNPROCESSED COMMAND = %02X(%s)\n", cmd[0], get_scsi_cmd_name(cmd[0]));
			dump_stack_trace2(16);
	}
	
	return ret;
}

static INLINE int process_scsi_cmd_iso(uint8_t *cmd, uint8_t *out, uint64_t outlen)
{
	int ret = 0;
	
	switch (cmd[0])
	{	
		case SCSI_CMD_GET_CONFIGURATION:
			*(uint16_t *)&out[6] = device_type;
			ret = 1;			
		break;
		
		case SCSI_CMD_READ_DISC_STRUCTURE:
		{
			ScsiCmdReadDiscStructure *rds = (ScsiCmdReadDiscStructure *)cmd;
			ScsiReadDiscStructureFormat0Response *resp = (ScsiReadDiscStructureFormat0Response *)out;
			uint32_t start_sector;
			uint32_t end_sector; 
			
			if (device_type == DEVICE_TYPE_PS2_CD)
			{
				DPRINTF("Read Disc Structure on CD!!!! \n");
			}
			
			if (rds->format != 0)
			{
				DPRINTF("SCSI_CMD_READ_DISC_STRUCTURE: Requesting a format other than 0!!!!\n");
				dump_stack_trace2(16);
			}
			
			start_sector = 0x030000;
			
			if (is_dual_layer)
			{
				if (rds->layer_num == 0)
				{
					end_sector = start_sector + layer0_size - 1;
				}
				else
				{
					DPRINTF("SCSI_CMD_READ_DISC_STRUCTURE: Requesting layer1 structure.\n");
					end_sector = start_sector + (iso_size_sectors - layer0_size) - 1;
				}
			}
			else
			{				
				end_sector = start_sector + iso_size_sectors - 1;
			}
			
			memset(resp, 0, sizeof(ScsiReadDiscStructureFormat0Response));
			resp->length = 2050;
			resp->disccategory_partversion = 1;
			resp->discsize_maximumrate = 2;
			resp->misc = (is_dual_layer) ? 0x21 : 1;
			resp->start_sector[0] = start_sector>>16;
			resp->start_sector[1] = (start_sector>>8)&0xFF;
			resp->start_sector[2] = start_sector&0xFF;
			resp->end_sector[0] = end_sector>>16;
			resp->end_sector[1] = (end_sector>>8)&0xFF;
			resp->end_sector[2] = end_sector&0xFF;	
					
			ret = 1;			
		}
		break;
		
		case SCSI_CMD_READ_TOC_PMA_ATIP:
		{
			ScsiCmdReadTocPmaAtip *tpa = (ScsiCmdReadTocPmaAtip *)cmd;
			
			if (tpa->rv_format != 2)
			{
				DPRINTF("Requesting something other than full toc. Not implemented.\n");
				break;
			}
			
			if (device_type == DEVICE_TYPE_PS2_DVD)
			{
				DPRINTF("Read TOC on DVD!!!\n");
			}
			
			ScsiTocResponse *resp = (ScsiTocResponse *)out;
			ScsiFullTrackDescriptor *full_tracks = (ScsiFullTrackDescriptor *)(resp+1);
			int ntracks;
			
			ntracks = num_tracks;
			if (ntracks == 0)
				ntracks = 1;
			
			resp->toc_length = 2 + ((ntracks+3)*sizeof(ScsiFullTrackDescriptor));
			resp->first_track = 1; // First session
			resp->last_track = 1; // Last session
			
			memset(full_tracks, 0, (ntracks+3)*sizeof(ScsiFullTrackDescriptor));			
			
			full_tracks[0].session_number = 1;
			full_tracks[0].adr_control = 0x14;
			full_tracks[0].point = 0xA0;
			full_tracks[0].pmin = 1;
			full_tracks[0].psec = 0x20;
			
			full_tracks[1].session_number = 1;
			full_tracks[1].adr_control = 0x10;
			full_tracks[1].point = 0xA1;
			full_tracks[1].pmin = ntracks;
			
			full_tracks[2].session_number = 1;
			full_tracks[2].adr_control = 0x10;
			full_tracks[2].point = 0xA2;			
			lba_to_msf(iso_size_sectors+150, &full_tracks[2].pmin, &full_tracks[2].psec, &full_tracks[2].pframe);
			
			for (int i = 0; i < ntracks; i++)
			{
				full_tracks[3+i].session_number = 1;
				
				if (IS_2352())
				{				
					full_tracks[3+i].adr_control = tracks[i].adr_control;
					full_tracks[3+i].point = tracks[i].track_number;
					lba_to_msf(tracks[i].track_start_addr+150, &full_tracks[3+i].pmin, &full_tracks[3+i].psec, &full_tracks[3+i].pframe);
				}
				else
				{
					full_tracks[3+i].adr_control = 0x14;
					full_tracks[3+i].point = 1;
					full_tracks[3+i].psec = 2; // 150 frames
				}
				
				DPRINTF("Track %d  %x\n", tracks[i].track_number, tracks[i].track_start_addr);
			}
			
			ret = 1;
		}			
		break;
		
		case SCSI_CMD_READ_10:
		{
			ScsiRead10 *read10 = (ScsiRead10 *)cmd;		
			
			if (device_type == DEVICE_TYPE_PS2_CD)
				cd_iso_read2048(out, read10->lba, read10->length);
			else
				dvd_iso_read2048(out, read10->lba, read10->length);		
			
			ret = 1;
		}		
		break;
		
		case SCSI_CMD_READ_2064:
		{
			ScsiRead2064 *read2064 = (ScsiRead2064 *)cmd;		
			dvd_iso_read2064(out, read2064->lba, read2064->length);		
			ret = 1;
		}
		break;
		
		case SCSI_CMD_READ_CD:
		{
			ScsiCmdReadCd *readcd = (ScsiCmdReadCd *)cmd;
			uint32_t length = GET_READ_SIZE(readcd);
			
			//DPRINTF("Read CD (lba=%x,length=%x,misc=%x,scsb=%x)\n", readcd->lba, length, readcd->misc, readcd->rv_scsb);
			
			if (readcd->misc == 0x10)
			{
				cd_iso_read2328(out, readcd->lba, length);
			}
			else if (readcd->misc == 0x78)
			{
				cd_iso_read2340(out, readcd->lba, length);
			}
			else if (readcd->misc == 0xF8)
			{
				if (readcd->rv_scsb == 0)
					cd_iso_read2352(out, readcd->lba, length);
				else
					cd_iso_read2364(out, readcd->lba, length);
			}
			else
			{
				DPRINTF("Unexpeted value for misc in READ_CD: %02X\n", readcd->misc);
				dump_stack_trace2(16);
			}
			
			
			ret = 1;
		}
		break;
		
		default:
			return process_other_cmd(cmd, out, outlen);			
	}
	
	return ret;
}

static INLINE void optical_dvd_read_2064(uint8_t *buf, uint64_t lba, uint32_t length)
{
	uint8_t *in = buf+(2048*(length-1));
	uint8_t *out = buf+(2064*(length-1));
	
	lba = lba+length-1;
	
	//DPRINTF("Read 2064 %x %x\n", lba, length);
	
	for (int i = 0; i < length; i++, in -= 2048, out -= 2064, lba--)
	{
		my_memcpy2(out+12, in, 2048);
		
		// It seems the ps2emu only cares about the sector ID...
		uint32_t id;
		
		if (!is_dual_layer || lba < layer0_size)
		{
			id = 0x030000 + lba;
		}
		else
		{
			id = 0x030000 + (lba-layer0_size);
			id |= (1 << 24); // Layer 1
		}
		
		*(uint32_t *)out = id;
		memset(out+4, 0, 8);
		memset(out+2060, 0, 4);
	}
}

static INLINE int post_process_scsi_cmd_optical(uint8_t *cmd, uint8_t *out, uint64_t outlen)
{
	switch (cmd[0])
	{
		case SCSI_CMD_GET_CONFIGURATION:
			device_type = *(uint16_t *)&out[6]; // Real device type
			
			DPRINTF("Device type %x\n", device_type);
			
			if (device_type == DEVICE_TYPE_CD)
			{
				*(uint16_t *)&out[6] = DEVICE_TYPE_PS2_CD;
			}
			else if (device_type == DEVICE_TYPE_DVD)
			{
				*(uint16_t *)&out[6] = DEVICE_TYPE_PS2_DVD;
			}
		break;	
		
		case SCSI_CMD_READ_DISC_STRUCTURE:
		{
			ScsiCmdReadDiscStructure *rds = (ScsiCmdReadDiscStructure *)cmd;
			ScsiReadDiscStructureFormat0Response *resp = (ScsiReadDiscStructureFormat0Response *)out;
			
			if (rds->format == 0)
			{
				// For PTP DL discs, we must set variables here
				if (!(resp->misc & 0x10) && (resp->misc & 0x20))
				{
					// Untested code, i don't have any PTP disc!!
					layer0_size = (resp->end_sector[0] << 16) | (resp->end_sector[1] << 8) | (resp->end_sector[2]);
					layer0_size = layer0_size - 0x030000 + 1;
					is_dual_layer = 1;
				}
			}
		}
		break;
		
		case SCSI_CMD_READ_2064:
		{		
			if (device_type == DEVICE_TYPE_DVD) // Optical dvd backups can't execute the read 2064 command
			{
				ScsiRead2064 *read2064 = (ScsiRead2064 *)cmd;
				
				optical_dvd_read_2064(out, read2064->lba, read2064->length);
			}
		}			
		break;	
	}
	
	return 0;
}


