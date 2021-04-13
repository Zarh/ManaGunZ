//----------------------------------------
// ReactPSN by habib
//----------------------------------------

#ifndef USE_EXTERNAL_REACTPSN_PLUGIN

#define IDPS_KEYBITS 128
#define ACT_DAT_KEYBITS 128
#define RIF_KEYBITS 128
#define RAP_KEYBITS 128

static unsigned char RAP_KEY[]  = {0x86, 0x9F, 0x77, 0x45, 0xC1, 0x3F, 0xD8, 0x90, 0xCC, 0xF2, 0x91, 0x88, 0xE3, 0xCC, 0x3E, 0xDF};
static unsigned char RAP_PBOX[] = {0x0C, 0x03, 0x06, 0x04, 0x01, 0x0B, 0x0F, 0x08, 0x02, 0x07, 0x00, 0x05, 0x0A, 0x0E, 0x0D, 0x09};
static unsigned char RAP_E1[]   = {0xA9, 0x3E, 0x1F, 0xD6, 0x7C, 0x55, 0xA3, 0x29, 0xB7, 0x5F, 0xDD, 0xA6, 0x2A, 0x95, 0xC7, 0xA5};
static unsigned char RAP_E2[]   = {0x67, 0xD4, 0x5D, 0xA3, 0x29, 0x6D, 0x00, 0x6A, 0x4E, 0x7C, 0x53, 0x7B, 0xF5, 0x53, 0x8C, 0x74};

static void get_rif_key(unsigned char *rap, unsigned char *key)
{
	int i;

	unsigned char iv[0x10];

	clear_key(key);
	clear_key(iv);

	// Initial decrypt.
	aescbccfb_dec(key, rap, 0x10, RAP_KEY, RAP_KEYBITS, iv);

	// rap2rifkey round.
	for (int round = 0; round < 5; ++round)
	{
		for (i = 0; i < 0x10; ++i)
		{
			int p = RAP_PBOX[i];
			key[p] ^= RAP_E1[p];
		}
		for (i = 15; i >= 1; --i)
		{
			int p = RAP_PBOX[i];
			int pp = RAP_PBOX[i - 1];
			key[p] ^= key[pp];
		}
		int o = 0;
		for (i = 0; i < 0x10; ++i)
		{
			int p = RAP_PBOX[i];
			unsigned char kc = key[p] - o;
			unsigned char ec2 = RAP_E2[p];
			if (o != 1 || kc != 0xFF)
			{
				o = kc < ec2 ? 1 : 0;
				key[p] = kc - ec2;
			}
			else if (kc == 0xFF)
			{
				key[p] = kc - ec2;
			}
			else
			{
				key[p] = kc;
			}
		}
	}
}

static uint8_t make_rif_buf[0x20 + 0x28 + 0x50 + 0x20 + 0x28]; // ACT_DAT[0x20] + CONTENT_ID[0x28] + RAP_PATH[0x50] + RIF_BUFFER[0x20] (rif_buffer reuse rap_path + 0x20 = 0x70) +0x28(signaturs)

//////// make_rif memory allocation ////////////
#define ALLOC_ACT_DAT	 (uint8_t*)(make_rif_buf)
#define ALLOC_CONTENT_ID	(char*)(make_rif_buf + 0x20)
#define ALLOC_PATH_BUFFER	(char*)(make_rif_buf + 0x20 + 0x28)
#define ALLOC_RIF_BUFFER (uint8_t*)(make_rif_buf + 0x20 + 0x28)
////////////////////////////////////////////////

static void read_act_dat_and_make_rif(uint8_t *rap, uint8_t *act_dat, const char *content_id, const char *rif_path)
{
	int fd;
	if(cellFsOpen(rif_path, CELL_FS_O_WRONLY | CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &fd, 0666, NULL, 0) == CELL_FS_SUCCEEDED)
	{
		uint8_t idps_const[0x10]    = {0x5E,0x06,0xE0,0x4F,0xD9,0x4A,0x71,0xBF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01};
		uint8_t rif_key_const[0x10] = {0xDA,0x7D,0x4B,0x5E,0x49,0x9A,0x4F,0x53,0xB1,0xC1,0xA1,0x4A,0x74,0x84,0x44,0x3B};

		uint8_t *rif = ALLOC_RIF_BUFFER;
		uint8_t *key_index = rif + 0x40;
		uint8_t *rif_key   = rif + 0x50;
		memset(rif, 0, 0x70);

		get_rif_key(rap, rif_key); //convert rap to rifkey (klicensee)

		uint8_t *iv = rif + 0x60;
	//	memset(iv, 0, 0x10); // already done
		aescbccfb_enc(idps_const, idps_const, 0x10, (void*)PS3MAPI_IDPS_2, IDPS_KEYBITS, iv);

		uint8_t *act_dat_key = rap;
		memcpy(act_dat_key, act_dat + 0x10, 0x10);

		clear_key(iv);
		aescbccfb_dec(act_dat_key, act_dat_key, 0x10, idps_const, IDPS_KEYBITS, iv);

		clear_key(iv);
		aescbccfb_enc(rif_key, rif_key, 0x10, act_dat_key, ACT_DAT_KEYBITS, iv);

		clear_key(iv);
		aescbccfb_enc(key_index, key_index, 0x10, rif_key_const, RIF_KEYBITS, iv);

		const uint32_t version_number = 1;
		const uint32_t license_type = 0x00010002;
		const uint64_t timestamp = 0x000001619BF6DDCA;
		const uint64_t expiration_time = 0;

		memcpy(rif,        &version_number,  4); // 0x00 version_number
		memcpy(rif + 0x04, &license_type,    4); // 0x04 license_type
		memcpy(rif + 0x08, act_dat + 0x8,    8); // 0x08 account_id
		memcpy(rif + 0x10, content_id,    0x24); // 0x10 content_id
												 // 0x40 encrypted key index (Used for choosing act.dat key)
												 // 0x50 encrypted rif_key
		memcpy(rif + 0x60, &timestamp,       8); // 0x60 timestamp
		memcpy(rif + 0x68, &expiration_time, 8); // 0x68 expiration time
		memset(rif + 0x70, 0x11, 0x28);			 // 0x70 ECDSA Signature

		uint64_t size;
		cellFsWrite(fd, rif, 0x98, &size);
		cellFsClose(fd);
	}
}
#else
#define KPLUGIN_ADDRESS		0x7f0000

static void read_act_dat_and_make_rif(uint8_t *rap, uint8_t *act_dat, const char *content_id, const char *rif_path)
{
	CellFsStat stat;
	if(cellFsStat("/dev_usb000/reactPSN.BIN",   &stat) /* != CELL_FS_SUCCEEDED */)
	if(cellFsStat("/dev_usb001/reactPSN.BIN",   &stat) /* != CELL_FS_SUCCEEDED */)
	if(cellFsStat("/dev_hdd0/hen/reactPSN.BIN", &stat) /* != CELL_FS_SUCCEEDED */) return;
	{
		uint64_t payload_size = stat.st_size; if(payload_size < 0x5000) return;

		int fd;
		if(cellFsOpen("/dev_usb000/reactPSN.BIN",   CELL_FS_O_RDONLY, &fd, 0666, NULL, 0) /* != CELL_FS_SUCCEEDED */)
		if(cellFsOpen("/dev_usb001/reactPSN.BIN",   CELL_FS_O_RDONLY, &fd, 0666, NULL, 0) /* != CELL_FS_SUCCEEDED */)
		if(cellFsOpen("/dev_hdd0/hen/reactPSN.BIN", CELL_FS_O_RDONLY, &fd, 0666, NULL, 0) /* != CELL_FS_SUCCEEDED */) return;
		{
			uint64_t nread;

			f_desc_t f;
			f.addr = (void*)MKA(KPLUGIN_ADDRESS); //malloc(payload_size);
			f.toc = (void*)MKA(TOC);
			int(*reactpsn_plugin)(uint8_t *idps,uint8_t *rap, uint8_t *act_dat, const char *content_id, const char *out) = (void *)&f;

			cellFsRead(fd, f.addr, payload_size, &nread);
			cellFsClose(fd);

			#ifdef DEBUG
			DPRINTF("calling reactPSN.BIN %s -> %s\n", content_id, rif_path);
			#endif

			uint8_t idps[0x10];
			memcpy(idps, (void*)PS3MAPI_IDPS_2, 0x10);

			if(payload_size == nread) reactpsn_plugin(idps, rap, act_dat, content_id, rif_path);
			memset((void *)MKA(KPLUGIN_ADDRESS), 0, payload_size);
		}
	}
}
#endif

uint8_t skip_existing_rif = 1;

static void make_rif(const char *path)
{
	//if(!is_hdd0) return; // checked in homebrew_blocker.h

	if(strncmp(path + 9, "/home/", 6)) return; // /dev_hdd0/home/

	int path_len = strlen(path); if(path_len != 71) return; // example: /dev_hdd0/home/00000001/exdata/2P0001-PS2U10000_00-0000111122223333.rif

	if(!strcmp(path + path_len - 4, ".rif"))
	{
		CellFsStat stat;
		if(skip_existing_rif && (cellFsStat(path, &stat) == CELL_FS_SUCCEEDED)) return; // rif already exists

		#ifdef DEBUG
		DPRINTF("open_path_hook: %s (looking for rap)\n", path);
		#endif

		char *content_id = ALLOC_CONTENT_ID;
		strncpy(content_id, path + 31, 0x24); content_id[0x24] = 0;

		char *rap_path = ALLOC_PATH_BUFFER;

		uint8_t is_ps2_classic = !strcmp(content_id, "2P0001-PS2U10000_00-0000111122223333");

		if(!is_ps2_classic)
		{
			sprintf(rap_path, "/dev_usb000/exdata/%.36s.rap", content_id);
			if(cellFsStat(rap_path, &stat) /* != CELL_FS_SUCCEEDED */) {rap_path[10] = '1'; //usb001
			if(cellFsStat(rap_path, &stat) /* != CELL_FS_SUCCEEDED */) sprintf(rap_path, "/dev_hdd0/exdata/%.36s.rap", content_id);}
		}

		// default: ps2classic rap
		uint8_t rap[0x10] = {0xF5, 0xDE, 0xCA, 0xBB, 0x09, 0x88, 0x4F, 0xF4, 0x02, 0xD4, 0x12, 0x3C, 0x25, 0x01, 0x71, 0xD9};

		if(is_ps2_classic || (read_file(rap_path, rap, 0x10) == 0x10))
		{
			#ifdef DEBUG
			DPRINTF("rap_path:%s output:%s\n", rap_path, path);
			#endif

			char *act_path = ALLOC_PATH_BUFFER;
			strncpy(act_path, path, 31);
			strcpy(act_path + 31, "act.dat\0");

			#ifdef DEBUG
			DPRINTF("act_path:%s content_id:%s\n", act_path, content_id);
			#endif

			uint8_t *act_dat = ALLOC_ACT_DAT;
			if(read_file(act_path, act_dat, 0x20) == 0x20)
			{
				char *rif_path = ALLOC_PATH_BUFFER;
				sprintf(rif_path, "/%s", path);
				read_act_dat_and_make_rif(rap, act_dat, content_id, rif_path);

				#ifdef DEBUG
				DPRINTF("rif_path:%s\n", rif_path);
				#endif
			}
			#ifdef DEBUG
			else
			{
					DPRINTF("act.dat not found: %s\n", act_path);
			}
			#endif
		}
	}
}
