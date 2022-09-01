#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include <ppu-lv2.h>
#include <openssl/aes.h>
#include <openssl/des.h>
#include "storage.h"
#include "ioctl.h"
#include "bd.h"
#include "../extern.h"
#include "../mgz_io.h"

#define SG_DXFER_TO_DEV		ATAPI_PIO_DATA_OUT_PROTO, ATAPI_DIR_WRITE
#define SG_DXFER_FROM_DEV		ATAPI_PIO_DATA_IN_PROTO, ATAPI_DIR_READ

unsigned int version=2;

unsigned char FixedKey30[] = { 220, 8, 0x2f, 0x83, 0x7f, 20, 0x87, 0xc2, 0, 0x8b, 0x7b, 0xc9, 0x20, 0xc5, 0x5b, 0xd9 };
unsigned char FixedKey31[] = { 0xe8, 8, 0x85, 0xf9, 110, 0xd0, 0xf3, 0x67, 0x52, 0xce, 0x52, 190, 0xc3, 0xc7, 0x4e, 0xf3 };
unsigned char InitialSeed[] = 
{
  0x3e, 0xc2, 12, 0x17, 2, 0x19, 1, 0x97, 0x8a, 0x29, 0x71, 0x79, 0x38, 0x29, 0xd3, 8,
  4, 0x29, 250, 0x84, 0xe3, 0x3e, 0x7f, 0x73, 12, 0x1d, 0x41, 110, 0xea, 0x25, 0xca, 0xfb,
  0x3d, 0xe0, 0x2b, 0xc0, 5, 0xea, 0x49, 11, 3, 0xe9, 0x91, 0x98, 0xf8, 0x3f, 0x10, 0x1f,
  0x1b, 0xa3, 0x4b, 80, 0x58, 0x94, 40, 0xad, 210, 0xb3, 0xeb, 0x3f, 0xf4, 0xc3, 0x1a, 0x58
};
unsigned char IV1[] = { 0x22, 0x26, 0x92, 0x8d, 0x44, 3, 0x2f, 0x43, 0x6a, 0xfd, 0x26, 0x7e, 0x74, 0x8b, 0x23, 0x93 };
unsigned char IV2[] = { 0xe8, 11, 0x3f, 12, 0xd6, 0x56, 0x6d, 0xd0 };
unsigned char IV3[] = { 0x3b, 0xd6, 0x24, 2, 11, 0xd3, 0xf8, 0x65, 0xe8, 11, 0x3f, 12, 0xd6, 0x56, 0x6d, 0xd0 };
unsigned char Key1[0x10];
unsigned char Key2[0x10];
unsigned char Key3[] = { 0x12, 0x6c, 0x6b, 0x59, 0x45, 0x37, 14, 0xee, 0xca, 0x68, 0x26, 0x2d, 2, 0xdd, 0x12, 210 };
unsigned char Key4[] = { 0xd9, 0xa2, 10, 0x79, 0x66, 0x6c, 0x27, 0xd1, 0x10, 50, 0xac, 0xcf, 13, 0x7f, 0xb5, 1 };
unsigned char Key5[] = { 0x19, 0x76, 0x6f, 0xbc, 0x77, 0xe4, 0xe7, 0x5c, 0xf4, 0x41, 0xe4, 0x8b, 0x94, 0x2c, 0x5b, 0xd9 };
unsigned char Key6[] = { 80, 0xcb, 0xa7, 240, 0xc2, 0xa7, 0xc0, 0xf6, 0xf3, 0x3a, 0x21, 0x43, 0x26, 0xac, 0x4e, 0xf3 };
unsigned char Key7[0x10];
unsigned char Key8[0x10];

/* Handler to the BD-ROM */
int g_fd = 0;
FILE *g_file_log = NULL;

void calculate_session_keys(unsigned char* r1, unsigned char* r2);
int do_send_key(char keyFormat, unsigned char* payload, int payload_len);
int do_report_key(char keyFormat, unsigned char* payload, int payload_len);
int establish_session_keys(char keyselection, unsigned char* KA, unsigned char* KB);
void triple_des_encrypt(unsigned char* Key, unsigned char* IV, unsigned char* Source, int SOffset, int SLength, unsigned char* Destination, int DOffset);
int do_unknown_e0(unsigned char* header, unsigned char* payload);
int do_unknown_e1(unsigned char* header, unsigned char* payload);
void load_keys(unsigned char* EID4, unsigned char* CMAC, unsigned char* KE, unsigned char* IE);
int get_dec_key(unsigned char* d1, unsigned char* d2);
int get_data(unsigned char* data1, unsigned char* data2);
void hex_fprintf(FILE *fp, unsigned char *buf, size_t len);

int do_cdb(unsigned char* cdb, int cdb_len, unsigned char* transfer, int transfer_len, uint32_t proto, uint32_t type)
{
	int ret;
	struct lv2_atapi_cmnd_block atapi_cmnd;

	sys_storage_init_atapi_cmnd(&atapi_cmnd, transfer_len, proto, type);
	memcpy(atapi_cmnd.pkt, cdb, cdb_len);
	if(transfer_len == 0 || transfer == NULL) atapi_cmnd.blocks = 0;
	
	ret = sys_storage_send_atapi_command(g_fd, &atapi_cmnd, transfer);
	if(ret != 0) {
		print_debug("ioctl indicates command failed: %d", ret);
		if(g_file_log) MGZ_fprintf(g_file_log, "ioctl indicates command failed: %d\r\n", ret);
		return FAILED;
	}
	
	if(g_file_log) MGZ_fprintf(g_file_log, "return value of ioctl indicates success\r\n");
	print_debug("SUCCESS");
	return SUCCESS;
}

int test_unit_ready()
{
	print_debug("Test unit ready: ");
	if(g_file_log) MGZ_fprintf(g_file_log, "Test unit ready: ");
	unsigned char cdb[]= {0, 0, 0, 0, 0, 0};
	return do_cdb(cdb, 6, NULL, 0, ATAPI_NON_DATA_PROTO, ATAPI_DIR_WRITE);
}

int read_pic(unsigned char* ret, int len)
{
	if(g_file_log) MGZ_fprintf(g_file_log, "Read pic: ");
	unsigned char cdb[]= { 0xad, 1, 0, 0, 0, 0, 0, 0, 0x10, 0x04, 0, 0 };
	return do_cdb(cdb, 12, ret, len, SG_DXFER_FROM_DEV);
}

u8 get_redump_log(char *log_path, char *pic_path)
{
	FILE* file_io=NULL;

	unsigned char d_3dump[0x60];
	unsigned char* eid4=d_3dump;
	unsigned char* cmac=d_3dump+0x20;
	unsigned char* ke=d_3dump+0x30;
	unsigned char* ie=d_3dump+0x50;
	unsigned char d1[16];
	unsigned char d2[16];
	
	unsigned char* pic;
	int pic_len;
	unsigned char all=3;
	
	g_file_log = fopen(log_path, "wb");
	if( g_file_log == NULL) {
		print_load("Error : failed to fopen %s", log_path);
		return FAILED;
	}
	MGZ_fprintf(g_file_log, "\r\nGetKey r%u\r\n", version);
	
	memset(d1, 0, 16);
	memset(d2, 0, 16);
	
	dump_3Dump();
	
	/*Read 3Dump.bin*/
	if( (file_io=fopen("/dev_hdd0/tmp/3Dump.bin", "rb"))==NULL )
	{
		MGZ_fprintf(g_file_log, "Error opening 3Dump.bin\r\n");
		FCLOSE(g_file_log);
		return FAILED;
	}
	if( fread(d_3dump, 1, 0x60, file_io)!=0x60 )
	{
		MGZ_fprintf(g_file_log, "Error reading 3Dump.bin\r\n");
		FCLOSE(g_file_log);
		return FAILED;
	}
	FCLOSE(file_io);
	
	load_keys(eid4, cmac, ke, ie);
	
	/* Start the drive communication */
	if(sys_storage_open(BD_DEVICE, &g_fd) != 0) {
		MGZ_fprintf(g_file_log, "sys_storage_open failed...\n");
	    FCLOSE(g_file_log);
		return FAILED;
	}

	if(test_unit_ready()!=SUCCESS)
	{
		MGZ_fprintf(g_file_log, "Test unit failed, are you sure a disc is in the drive?\r\n");
		sys_storage_close(g_fd);
		FCLOSE(g_file_log);
		return FAILED;
	}
	
	/*get PIC*/
	pic=malloc(4100);
	if(pic==NULL) {
		print_load("Error : cannot malloc pic");
		sys_storage_close(g_fd);
		FCLOSE(g_file_log);
		return FAILED;
	}
	memset(pic, 0, 4100);
	read_pic(pic, 4100);
	pic_len=0x83;
	while(pic[pic_len]==0 && pic_len>=0)
		--pic_len;
	
	++pic_len;
	if(pic_len==0)
	{
		MGZ_fprintf(g_file_log, "  Empty PIC, probably wrong. Continuing anyway to try and get key\r\n");
		all-=1;
	}
	
	if(get_dec_key(d1, d2)==SUCCESS)
	{
		MGZ_fprintf(g_file_log, "get_dec_key succeeded!\r\n");
		enc_d1(d1);
		dec_d2(d2);
	}
	else
	{
		MGZ_fprintf(g_file_log, "get_dec_key failed, key was not dumped\r\n");
		if(pic_len==0)
		{
			MGZ_fprintf(g_file_log, "Nothing could be dumped. Your drive may be unsupported, please report it\r\n");
			sys_storage_close(g_fd);
			FCLOSE(g_file_log);
			FREE(pic);
			return FAILED;
		}
		all-=2;
	}
	
	if(all>1)
	{
		MGZ_fprintf(g_file_log, "\r\n\r\ndisc_key = ");
		hex_fprintf(g_file_log, d1, 16);
		MGZ_fprintf(g_file_log, "\r\n\r\ndisc_id = ");
		if(d2[12]==0 && d2[13]==0 && d2[14]==0 && d2[15]==0)
			hex_fprintf(g_file_log, d2, 16);
		else
		{
			hex_fprintf(g_file_log, d2, 12);
			MGZ_fprintf(g_file_log, "XXXXXXXX");
		}
	}
	if(pic_len!=0)
	{
		MGZ_fprintf(g_file_log, "\r\nPIC:\r\n");
		hex_fprintf(g_file_log, pic, 0x84);
		MGZ_fprintf(g_file_log, "\r\n");
	}
	
	/*dump pic in full*/
	if( (file_io=fopen(pic_path, "wb"))==NULL )
	{
		MGZ_fprintf(g_file_log, "Failed to open big.pic for writing\r\n");
		sys_storage_close(g_fd);
		FCLOSE(g_file_log);
		FREE(pic);
		return FAILED;
	}
	if(fwrite(pic, 1, 4100, file_io)!=4100)
	{
		MGZ_fprintf(g_file_log, "Failed to write to big.pic\r\n");
		sys_storage_close(g_fd);
		FCLOSE(g_file_log);
		FCLOSE(file_io);
		FREE(pic);
		return FAILED;
	}
	FCLOSE(file_io);
	FREE(pic);
	
	if(all==3)
	{
		MGZ_fprintf(g_file_log, "\r\nSUCCESS: Everything was correctly dumped.\r\n");
		sys_storage_close(g_fd);
		FCLOSE(g_file_log);
		return SUCCESS;
	}
	else if(all==2)
	{
		MGZ_fprintf(g_file_log, "\r\nWARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING\r\n\r\n");
		MGZ_fprintf(g_file_log, "WARNING: Not everything was correctly dumped (PIC missing)\r\n");
		sys_storage_close(g_fd);
		FCLOSE(g_file_log);
		return FAILED;
	}
	else if(all==1)
	{
		MGZ_fprintf(g_file_log, "\r\nWARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING\r\n\r\n");
		MGZ_fprintf(g_file_log, "WARNING: Not everything was correctly dumped (d1 missing)\r\n");
		sys_storage_close(g_fd);
		FCLOSE(g_file_log);
		return FAILED;
	}
	
	sys_storage_close(g_fd);
	FCLOSE(g_file_log);
	
	return SUCCESS;/*suppress warning*/
}

u8 get_keys(u8 *d1, u8 *d2, u8 *pic)
{
	u8 ret = FAILED;
	u8* d_3dump = NULL;
	
	print_debug("sys_storage_open");
	if(sys_storage_open(BD_DEVICE, &g_fd) != 0) {
		print_load("Error : sys_storage_open failed...");
		return FAILED;
	}
	
	print_debug("test_unit_ready");
	if(test_unit_ready()==FAILED) {
		print_load("Error : Test unit failed, are you sure a disc is in the drive?");
		goto error;	
	}
	
	print_debug("Load_3Dump");
	d_3dump = Load_3Dump();
	if(d_3dump==NULL) {
		print_load("Error : Failed to load 3Dump");
		goto error;
	}
	
	u8* eid4=d_3dump;
	u8* cmac=d_3dump+0x20;
	u8* ke=d_3dump+0x30;
	u8* ie=d_3dump+0x50;
	
	print_debug("load_keys");
	load_keys(eid4, cmac, ke, ie);
	
	memset(d1,  0, 0x10);
	memset(d2,  0, 0x10);
	memset(pic, 0, PIC_LEN);
	
	print_debug("Getting PIC");
	if( read_pic(pic, PIC_LEN) == FAILED ) {
		print_load("Error : failed to get PIC");
		goto error;
	}
	
	print_load("Getting Data1 and Data2"); // If I remove this line it doesn't work, I don't know why ! Even if I use sleep(1);
	if( get_dec_key(d1, d2)==FAILED ) {
		print_load("Error : failed to get d1 and d2");
		goto error;
	}
	
/** From IRD documentation by 3key team
	
		The original iso contains plain and encrypted content. To be able to successfully re-encrypt the plain
	files, we need the original keys from the disc. First, the D1 key is written (16 bytes long). Next up, the
		D2 key is written (also 16 bytes long). Finally, the PIC data is written (115 bytes long).
	A special note about the D2 key is in order. This key is a unique fingerprint, which is different on each
	disc produced. Therefore, we need to change this key to hide the origin. The origin *could* lead to a
	PSN account. As a result, the D2 key is decrypted. The first 12 bytes are copied, but the last 4 bytes
	are changed. If the last 4 bytes are all zeroes, then no change will be made. If they contain a different
	value, then it will be changed to 1 (0x00 0x00 0x00 0x01). Then the key is encrypted again, and stored
	in the IRD file.
		When building an ISO file, the D2 is decrypted once again, and the last four bytes are checked for a
	value other than 0. If it finds that, it will supply a random value between 0 and 0x1FFFFF.
	
**/

	dec_d2(d2);
	
	u32 id = *(u32 *) &d2[12];
	if( id != 0 ) {
		d2[12]=0;
		d2[13]=0;
		d2[14]=0;
		d2[15]=1;
	}
	enc_d2(d2);
	
	ret=SUCCESS;
error:

	print_debug("sys_storage_close");
	sys_storage_close(g_fd);
	FREE(d_3dump);
	
	return ret;
}

/*glevand*/
void
aes_cbc_encrypt(const unsigned char *iv, const unsigned char *key, int key_length,
	const unsigned char *data, int data_length, unsigned char *out)
{
	AES_KEY aes_key;
	unsigned char cbc[AES_BLOCK_SIZE];
	int i;

	AES_set_encrypt_key(key, key_length, &aes_key);

	memcpy(cbc, iv, AES_BLOCK_SIZE);

	while (data_length >= AES_BLOCK_SIZE) {
		for (i = 0; i < AES_BLOCK_SIZE; i++) out[i] = cbc[i] ^ data[i];

		AES_encrypt(out, out, &aes_key);

		memcpy(cbc, out, AES_BLOCK_SIZE);

		data += AES_BLOCK_SIZE;
		out += AES_BLOCK_SIZE;
		data_length -= AES_BLOCK_SIZE;
	}
}

/*lazy wrapper*/
void AESEncrypt(unsigned char* Key, unsigned int bits, unsigned char* IV, unsigned char* Source, int SOffset, int SLength, unsigned char* Destination, int DOffset)
{
	aes_cbc_encrypt(IV, Key, bits, Source+SOffset, SLength, Destination+DOffset);
}

/*glevand*/
static void
aes_cbc_decrypt(const unsigned char *iv, const unsigned char *key, int key_length,
	const unsigned char *data, int data_length, unsigned char *out)
{
	AES_KEY aes_key;
	unsigned char cbc[AES_BLOCK_SIZE];
	unsigned char buf[AES_BLOCK_SIZE];
	int i;

	AES_set_decrypt_key(key, key_length, &aes_key);

	memcpy(cbc, iv, AES_BLOCK_SIZE);

	while (data_length >= AES_BLOCK_SIZE) {
		memcpy(buf, data, AES_BLOCK_SIZE);

		AES_decrypt(data, out, &aes_key);

		for (i = 0; i < AES_BLOCK_SIZE; i++)
		 out[i] ^= cbc[i];

		memcpy(cbc, buf, AES_BLOCK_SIZE);

		data += AES_BLOCK_SIZE;
		out += AES_BLOCK_SIZE;
		data_length -= AES_BLOCK_SIZE;
	}
}

/*lazy wrapper*/
void AESDecrypt(unsigned char* Key, unsigned int bits, unsigned char* IV, unsigned char* Source, int SOffset, int SLength, unsigned char* Destination, int DOffset)
{
	aes_cbc_decrypt(IV, Key, bits, Source+SOffset, SLength, Destination+DOffset);
}

/*glevand*/
void triple_des_encrypt(unsigned char* Key, unsigned char* IV, unsigned char* Source, int SOffset, int SLength, unsigned char* Destination, int DOffset)
{
	DES_cblock kcb1;
	DES_cblock kcb2;
	DES_cblock ivcb;
	DES_key_schedule ks1;
	DES_key_schedule ks2;

	memcpy(kcb1, Key, DES_KEY_SZ);
	memcpy(kcb2, Key + DES_KEY_SZ, DES_KEY_SZ);
	memcpy(ivcb, IV, DES_KEY_SZ);

	DES_set_key_unchecked(&kcb1, &ks1);
	DES_set_key_unchecked(&kcb2, &ks2);

	DES_ede2_cbc_encrypt(Source+SOffset, Destination+DOffset, SLength, &ks1, &ks2, &ivcb, DES_ENCRYPT);
}

int get_dec_key(unsigned char* d1, unsigned char* d2)
{
	print_debug("get dec key");
	if(g_file_log) MGZ_fprintf(g_file_log, "get dec key\r\n");
	if(establish_session_keys(0, Key1, Key2) == FAILED) {
		print_load("Error : establish_session_keys failed");
		return FAILED;
	}
	if(get_data(d1, d2)==FAILED) {
		print_load("Error: get data failed");
		if(g_file_log) MGZ_fprintf(g_file_log, "  get data failed\r\n");
		return FAILED;
	}
	return SUCCESS;
}

int establish_session_keys(char keyselection, unsigned char* KA, unsigned char* KB)
{
	unsigned char source[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	unsigned char buffer7[4];
	unsigned char* sourceArray = buffer7;
	unsigned char destinationArray[20];
	unsigned char payload[0x24];
	unsigned char destination[0x10];
	unsigned char buffer6[0x10];
	
	print_debug("establish session keys");
 	if(g_file_log) MGZ_fprintf(g_file_log, "  establish session keys:\r\n");
	buffer7[1] = 0x10;
	memcpy(destinationArray, sourceArray, 4);

	AESEncrypt(KA, 128, IV1, source, 0, 0x10, destinationArray, 4);
	
	if(do_send_key(keyselection, destinationArray, 20) == FAILED) return FAILED;
	
	if(do_report_key(keyselection, payload, 0x24) == FAILED) return FAILED;
	
	AESDecrypt(KB, 128, IV1, payload, 4, 0x10, destination, 0);
	AESDecrypt(KB, 128, IV1, payload, 20, 0x10, buffer6, 0);
	
	if(memcmp(source, destination, 0x10)!=0)
	{
		print_load("Error : Memory comparison failed (rnd1 mismatch?). Check if your 3Dump.bin is correct.");
		if(g_file_log) MGZ_fprintf(g_file_log, "    Memory comparison failed (rnd1 mismatch?)\r\n");
		return FAILED;
	}
	calculate_session_keys(destination, buffer6);
	if(keyselection == 0)
	{
		memcpy(destinationArray, sourceArray, 4);
		AESEncrypt(KA, 128, IV1, buffer6, 0, 0x10, destinationArray, 4);
		if(do_send_key(2, destinationArray, 20) == FAILED) return FAILED;
	}
	else
	{
		if(do_report_key(keyselection, payload, 0x24) == FAILED) return FAILED;
	}
	return SUCCESS;
}

void hex_fprintf(FILE *fp, unsigned char *buf, size_t len)
{
	int i=0;

	if (len <= 0)
		return;
	
	while(i < len)
	{
		if(i>0&&i%16==0)
			MGZ_fprintf(fp, "\r\n");
		MGZ_fprintf(fp, "%02x", buf[i]);
		++i;
	}
}

int do_report_key(char keyFormat, unsigned char* payload, int payload_len)
{
	unsigned char buffer2[12];
	print_debug("do report key");
	if(g_file_log) MGZ_fprintf(g_file_log, "    do report key: ");
	memset(buffer2, 0, 12);
	buffer2[0] = 0xa4;
	buffer2[7] = 0xe0;
	buffer2[8]=(unsigned char) (payload_len>>8);
	buffer2[9]=(unsigned char) (payload_len);
	buffer2[10] = keyFormat;
	return do_cdb(buffer2, 12, payload, payload_len, SG_DXFER_FROM_DEV);
}

int do_send_key(char keyFormat, unsigned char* payload, int payload_len)
{
	unsigned char buffer2[12];
	print_debug("do send key");
	if(g_file_log) MGZ_fprintf(g_file_log, "    do send key: ");
	memset(buffer2, 0, 12);
	buffer2[0] = 0xa3;
	buffer2[7] = 0xe0;
	buffer2[8]=(unsigned char) (payload_len>>8);
	buffer2[9]=(unsigned char) (payload_len);
	buffer2[10] = keyFormat;
	return do_cdb(buffer2, 12, payload, payload_len, SG_DXFER_TO_DEV);
}

void calculate_session_keys(unsigned char* r1, unsigned char* r2)
{
	unsigned char destinationArray[0x10];
	print_debug("calculate session keys");
	if(g_file_log) MGZ_fprintf(g_file_log, "    calculate session keys\r\n");
	memcpy(destinationArray, r1, 8);
	memcpy(destinationArray+8, r2+8, 8);
	AESEncrypt(Key3, 128, IV1, destinationArray, 0, 0x10, Key7, 0);
	memcpy(destinationArray, r1+8, 8);
	memcpy(destinationArray+8, r2, 8);
	AESEncrypt(Key4, 128, IV1, destinationArray, 0, 0x10, Key8, 0);
}

int get_data(unsigned char* data1, unsigned char* data2)
{
	unsigned char destination[0x30];
	unsigned char buffer7[8];
	unsigned char* source = buffer7;
	unsigned char buffer3[] = { 3, 0, 0, 0, 0, 0, 0x61, 0x9b };
	unsigned char buffer4[8];
	unsigned char buffer5[0x54];
	unsigned char buffer6[] = {
		 0x9b, 0xcd, 0, 0, 0x63, 0x17, 0xa8, 0xcd, 0x12, 80, 0xd7, 10, 0x19, 0x5d, 0x7e, 2,
		 0xb0, 0xdb, 0x94, 0x6f, 0xcf, 0x2c, 0xcf, 0x4d, 0xef, 0x20, 0xe7, 0x4c, 0x9a, 30, 0x68, 6,
		 2, 0x8a, 0, 70, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 110, 0x8a, 0x6f, 0x2d, 0xde, 7, 0x20, 0x2b, 0xf4, 0xd0, 0xbb, 0xdb,
		 0x8a, 11, 0x80, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	
	print_debug("get data");
	if(g_file_log) MGZ_fprintf(g_file_log, "  get data\r\n");
	memset(buffer7, 0, 8);
	buffer7[6] = 10;
	buffer7[7] = 0xf5;
	memset(buffer5, 0, 0x54);
	buffer5[0] = 0;
	buffer5[1] = 80;
	buffer5[2] = 0;
	buffer5[3] = 0;
	AESEncrypt(Key7, 128, IV3, buffer6, 0, 80, buffer5, 4);
	triple_des_encrypt(Key7, IV2, source, 0, 8, buffer4, 0);
	
	if(do_unknown_e1(buffer4, buffer5) == FAILED) return FAILED;
	triple_des_encrypt(Key7, IV2, buffer3, 0, 8, buffer4, 0);
	if(do_unknown_e0(buffer4, buffer5) == FAILED) return FAILED;
	
	AESDecrypt(Key7, 128, IV3, buffer5, 4, 0x30, destination, 0);
	AESDecrypt(Key8, 128, IV3, destination, 3, 0x10, data1, 0);
	AESDecrypt(Key8, 128, IV3, destination, 0x13, 0x10, data2, 0);
	return SUCCESS;
}

int do_unknown_e1(unsigned char* header, unsigned char* payload)
{
	unsigned char buffer2[12];
	print_debug("do unknown e1: ");
	if(g_file_log) MGZ_fprintf(g_file_log, "    do unknown e1:\r\n");
	memset(buffer2, 0, 12);
	buffer2[0]=0xe1;
	buffer2[2]=0x54;
	memcpy(buffer2+4, header, 8);
	print_debug("unknown e1 cdb: ");
	if( DEBUG ) hex_print_load((char *)buffer2, 12);
	if(g_file_log) {
		MGZ_fprintf(g_file_log, "    unknown e1 cdb: ");
		hex_fprintf(g_file_log, buffer2, 12);
		MGZ_fprintf(g_file_log, "\r\n    ");
	}
	return do_cdb(buffer2, 12, payload, 0x54, SG_DXFER_TO_DEV);/*orig: SG_DXFER_TO_DEV*/
}

int do_unknown_e0(unsigned char* header, unsigned char* payload)
{
	unsigned char buffer2[12];
	print_debug("do unknown e0: ");
	if(g_file_log) MGZ_fprintf(g_file_log, "    do unknown e0:\r\n");
	memset(buffer2, 0, 12);
	buffer2[0]=0xe0;
	buffer2[2]=0x34;
	memcpy(buffer2+4, header, 8);
	print_debug("unknown e0 cdb: ");
	if( DEBUG ) hex_print_load((char *)buffer2, 12);
	if(g_file_log) {
		MGZ_fprintf(g_file_log, "    unknown e0 cdb: ");
		hex_fprintf(g_file_log, buffer2, 12);
		MGZ_fprintf(g_file_log, "\r\n    ");
	}
	return do_cdb(buffer2, 12, payload, 0x34, SG_DXFER_FROM_DEV);
}

void load_keys(unsigned char* EID4, unsigned char* CMAC, unsigned char* KE, unsigned char* IE)
{
	unsigned char destinationArray[0x20];
	unsigned char buffer2[0x10];
	unsigned char destination[0x40];

	print_debug("Load keys");
	if(g_file_log) MGZ_fprintf(g_file_log, "Load keys\r\n");
	AESEncrypt(KE, 256, IE, InitialSeed, 0, 0x40, destination, 0);
	memcpy(destinationArray, destination+0x20, 0x20);
	memcpy(buffer2, destination+0x10, 0x10);
	AESDecrypt(destinationArray, 256, buffer2, EID4, 0, 0x20, destination, 0);
	memcpy(Key1, destination, 0x10);
	memcpy(Key2, destination+0x10, 0x10);
}

void dec_d1(unsigned char* d1)
{
	unsigned char key[]= { 0x38, 11, 0xcf, 11, 0x53, 0x45, 0x5b, 60, 120, 0x17, 0xab, 0x4f, 0xa3, 0xba, 0x90, 0xed };
	unsigned char iV[] = { 0x69, 0x47, 0x47, 0x72, 0xaf, 0x6f, 0xda, 0xb3, 0x42, 0x74, 0x3a, 0xef, 170, 0x18, 0x62, 0x87 };
	aes_cbc_decrypt(iV, key, 128, d1, 16, d1);
}

void dec_d2(unsigned char* d2)
{
	unsigned char key[]= { 0x7c, 0xdd, 14, 2, 7, 110, 0xfe, 0x45, 0x99, 0xb1, 0xb8, 0x2c, 0x35, 0x99, 0x19, 0xb3 };
	unsigned char iV[] = { 0x22, 0x26, 0x92, 0x8d, 0x44, 3, 0x2f, 0x43, 0x6a, 0xfd, 0x26, 0x7e, 0x74, 0x8b, 0x23, 0x93 };
	aes_cbc_decrypt(iV, key, 128, d2, 16, d2);
}

void enc_d1(unsigned char* d1)
{
	unsigned char key[]= { 0x38, 11, 0xcf, 11, 0x53, 0x45, 0x5b, 60, 120, 0x17, 0xab, 0x4f, 0xa3, 0xba, 0x90, 0xed };
	unsigned char iV[] = { 0x69, 0x47, 0x47, 0x72, 0xaf, 0x6f, 0xda, 0xb3, 0x42, 0x74, 0x3a, 0xef, 170, 0x18, 0x62, 0x87 };
	aes_cbc_encrypt(iV, key, 128, d1, 16, d1);
}

void enc_d2(unsigned char* d2)
{
	unsigned char key[]= { 0x7c, 0xdd, 14, 2, 7, 110, 0xfe, 0x45, 0x99, 0xb1, 0xb8, 0x2c, 0x35, 0x99, 0x19, 0xb3 };
	unsigned char iV[] = { 0x22, 0x26, 0x92, 0x8d, 0x44, 3, 0x2f, 0x43, 0x6a, 0xfd, 0x26, 0x7e, 0x74, 0x8b, 0x23, 0x93 };
	aes_cbc_encrypt(iV, key, 128, d2, 16, d2);
}

