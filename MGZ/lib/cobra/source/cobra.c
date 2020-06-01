#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/systime.h>
#include <lv2/sysfs.h>
#include <ppu-lv2.h>
#include <lv2/syscalls.h>
#include <usb/usb.h>

#include "cobra.h"
#include "error.h"
#include "storage.h"
#include "syscall8.h"
#include "scsi.h"
#include "ufi.h"
#include "psp.h"
#include "base_mds.h"


#define TYPE_HOST2DEV (USB_REQTYPE_DIR_TO_DEVICE|USB_REQTYPE_TYPE_VENDOR)
#define TYPE_DEV2HOST (USB_REQTYPE_DIR_TO_HOST|USB_REQTYPE_TYPE_VENDOR)


#define SWAP32(x) ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) >> 24) & 0xff))

#define PSPL_ICON		"/dev_hdd0/game/PSPC66820/ICON0.PNG"
#define PSPL_PATH		"/dev_hdd0/game/PSPC66820"
#define PSPL_LAMBDA		"/dev_hdd0/game/PSPC66820/USRDIR/CONTENT/lambda.db"
#define PSPL_LAMBDA_NONCE 	0x0ab40b3bbd1f1a7bULL

#define DPRINTF(...)

enum
{
	// Reads the flash rawly. Used by PC flasher.
	CMD_SPI_FLASH_READ = 0x10,
	// Reads flash and decrypts with keys 2. Deprecated since version 3.0.
	CMD_SPI_FLASH_READ_AND_DECRYPT, 
	// Programs a page. Used by PC flasher.
	CMD_SPI_FLASH_PAGE_PROGRAM,
	// Decrypts buffer with key 0 and programs to flash. Used by PC flasher.
	CMD_SPI_FLASH_DECRYPT_AND_PAGE_PROGRAM,	
	// Erase a sector. Used by PC flasher
	CMD_SPI_FLASH_ERASE_SECTOR,
	// Erases the chip.
	CMD_SPI_FLASH_CHIP_ERASE,
	// Read the scp flashrom. Used by PC flasher, but its value is not used currenttly.
	CMD_SCP_FLASHROM_READ,
	// Sets buffer for crypt operation. There is one special mode which should be forbidden if not in PS3 mode.
	CMD_SCP_SET_BUFFER,
	// Starts a decryption/encryption operation. Encryption operations are forbidden on preprogrammed keys. Used by PC flasher (key 1 and 3 decryption).
	CMD_SCP_CRYPT,
	// Starts a handshake operation. 
	CMD_SCP_HANDSHAKE,
	// Sets user key for encryption/decryption
	CMD_SCP_SET_USER_KEY,	
	// Unused scp jtag opcodes
	CMD_SCP_SET_JTAG, /* UNUSED */
	CMD_SCP_READ_TDO, /* UNUSED */
	// Decrypts with key 2 and writes to eeprom. Used by PC flasher.
	CMD_MCU_EEPROM_DECRYPT_AND_WRITE,
	// Reboots MCU. Used by PC flasher, but no current firmware has used this opcode.
	CMD_MCU_REBOOT,
	// Starts bootloader. Used by PC flasher.
	CMD_MCU_START_BOOTLOADER,	
	// Reads flash and decrypts with keys 1. Scurity panic if used and not ps3 mode.
	CMD_SPI_FLASH_READ_AND_DECRYPT2, 
	// LEDs control. Added in firmware 3.0
	CMD_LED_CONTROL,
	// PS3 security. Added in firmware 3.0. IT MUST ONLY BE USED by PS3.
	CMD_PS3_SECURITY_IN,
	CMD_PS3_SECURITY_OUT,
	// Sets ps3 mode
	CMD_PS3_SET,
	// Validates a PS3 encoded psid
	CMD_PS3_VALIDATE,
	// Hashes flash
	CMD_SPI_FLASH_HASH,
	// Set Hash size
	CMD_SPI_FLASH_SET_HASH_SIZE
};

typedef struct
{
	char key[64];
	int value;
} KeyValue;

typedef struct
{
	char server[0x40];
	char path[0x420];
	uint32_t emu_mode;
	uint32_t numtracks;
	uint16_t port;
	uint8_t pad[6];
	ScsiTrackDescriptor tracks[1];
} __attribute__((packed)) netiso_args;


#define N_TITLE_IDS	102
#define N_TITLE_NAMES	24

static KeyValue emu_by_title_ids[N_TITLE_IDS] =
{
	/* First, games really fixed */
	// Lunar silver star
	{ "NPJH-90073", EMU_400 },
	{ "NPUH-90053", EMU_400 },
	{ "ULUS-10482", EMU_400 },
	{ "NPEH-00076", EMU_400 },
	{ "ULJM-05535", EMU_400 },
	{ "ULUS-10514", EMU_400 },
	// Tekken 6
	{ "ULES-01376", EMU_400 },
	{ "NPJH-50184", EMU_400 },
	{ "ULJS-00224", EMU_400 },
	{ "ULUS-10466", EMU_400 },
	{ "ULAS-42214", EMU_400 },
	{ "ULJS-19054", EMU_400 },
	// BlazBlue - Continuum Shift II
	{ "ULJM-05850", EMU_400 },
	{ "ULUS-10579", EMU_400 },
	// Exit
	{ "ULES-00285", EMU_400 },
	{ "ULUS-10074", EMU_400 },
	{ "ULJM-05062", EMU_400 },
	{ "ULJM-05271", EMU_400 },
	// DJ max portable 3
	{ "ULKS-46236", EMU_400 },
	{ "ULUS-10538", EMU_400 },
	{ "ULJM-05836", EMU_400 },
	{ "CF00-20046", EMU_400 },
	// Fate/Extra
	{ "ULUS-10576", EMU_400 },
	{ "NPJH-50247", EMU_400 },
	{ "ULJS-00254", EMU_400 },
	{ "ULJS-00253", EMU_400 },
	{ "ULUS-10588", EMU_400 },
	// 3rd birthday
	{ "ULES-01513", EMU_400 },
	{ "ULJM-05798", EMU_400 },
	{ "ULUS-10567", EMU_400 },
	// Lego pirates of the caribbean
	{ "ULES-01528", EMU_400 },
	{ "ULES-01529", EMU_400 },
	{ "ULUS-10575", EMU_400 },
	// Persona 2: innocent sin
	{ "ULUS-10584", EMU_400 },
	{ "ULJM-05759", EMU_400 },
	{ "UCAS-40338", EMU_400 },
	{ "NPJH-50329", EMU_400 },
	// Resistance retribution
	{ "NPEG-90013", EMU_400 },
	{ "NPJG-90037", EMU_400 },
	{ "NPUG-22850", EMU_400 },
	{ "UCES-01184", EMU_400 },
	{ "UCUS-98668", EMU_400 },
	{ "UCJS-10090", EMU_400 },
	// Soul calibur broken destiny
	{ "ULES-01298", EMU_400 },
	{ "ULJS-00202", EMU_400 },
	{ "ULUS-10457", EMU_400 },
	{ "ULJS-19055", EMU_400 },
	// Star ocean first departure
	{ "ULJM-05290", EMU_400 },
	{ "ULJM-05298", EMU_400 },
	{ "ULES-01154", EMU_400 },
	{ "ULUS-10374", EMU_400 },
	{ "ULJM-05590", EMU_400 },	
	// Valhalla Knights
	{ "ULJS-00075", EMU_400 },
	{ "ULUS-10230", EMU_400 },
	{ "ULJM-00075", EMU_400 },
	{ "ULKS-46133", EMU_400 },
	{ "ULJS-19010", EMU_400 },
	{ "ULES-00657", EMU_400 },
	// White Knight Chronicles: origins
	{ "UCJS-10115", EMU_400 },
	{ "UCES-01511", EMU_400 },
	// Z.H.P. : Unlosing Ranger Vs Darkdeath
	{ "ULUS-10559", EMU_400 },
	{ "ULJS-00262", EMU_400 },
	{ "ULJS-00261", EMU_400 },
	
	/* Games that still don't work, but show VISIBLE progress */
	// Ben 10 Ultimate Alien: Cosmic Destruction -> Warning, we don't have yet a proper title_name for this one, and we aer missing title id's
	{ "ULUS-10542", EMU_400 },
	// Final Fantasy Dissidia 012
	{ "ULES-01505", EMU_400 },
	{ "ULJM-05814", EMU_400 },
	{ "ULUS-10566", EMU_400 },
	// Final Fantasy IV Complete Collection
	{ "ULJM-05855", EMU_400 },
	{ "ULUS-10560", EMU_400 },
	{ "NPJH-50414", EMU_400 },
	// Gods Eater Burst -> Warning, we don't have yet a proper title name
	{ "ULES-01519", EMU_400 },
	{ "NPJH-50352", EMU_400 },
	{ "ULUS-10563", EMU_400 },
	{ "ULJS-00351", EMU_400 },
	{ "ULJS-00350", EMU_400 },
	{ "ULJS-19056", EMU_400 },
	// Need for Speed: Most Wanted
	{ "ULAS-42031", EMU_400 },
	{ "ULES-00196", EMU_400 },
	{ "ULJM-05073", EMU_400 },
	{ "ULKS-46044", EMU_400 },
	{ "ULUS-10036", EMU_400 },
	{ "ULJM-05183", EMU_400 },
	// Persona 3
	{ "ULES-01523", EMU_400 },
	{ "NPJH-50040", EMU_400 },
	{ "ULUS-10512", EMU_400 },
	{ "UCAS-40288", EMU_400 },
	{ "ULJM-05489", EMU_400 },
	{ "ULJM-08044", EMU_400 },
	// Ridge Racer 1
	{ "ULJS-00001", EMU_400 },
	{ "UCES-00002", EMU_400 },
	{ "UCAS-40015", EMU_400 },
	{ "ULUS-10001", EMU_400 },
	{ "UCKS-45002", EMU_400 },
	{ "ULJS-19002", EMU_400 },
	{ "UCKS-45053", EMU_400 },
	// Tactics ogre
	{ "ULJM-05753", EMU_400 },
	{ "ULUS-10565", EMU_400 },
	{ "ULES-01500", EMU_400 },
	// Warhammer 40000 Squad Team
	{ "NPEH-90001", EMU_400 },
	{ "ULUD-90004", EMU_400 },
	{ "ULES-00873", EMU_400 },
	{ "ULUS-10313", EMU_400 },	
};

static KeyValue emu_by_title_name[N_TITLE_NAMES] =
{
	/* First, games really fixed */
	{ { 0x42, 0x4C, 0x41, 0x5A, 0x42, 0x4C, 0x55, 0x45, 0x20, 0x43, 0x4F, 0x4E, 0x54, 0x49, 
	    0x4E, 0x55, 0x55, 0x4D, 0x20, 0x53, 0x48, 0x49, 0x46, 0x54, 0x20, 0xE2, 0x85, 0xA1, 0x00 }, EMU_400 }, // BLAZBLUE CONTINUUM SHIFT II
	{ "DJMAX PORTABLE 3", EMU_400 },
	{ "EXIT", EMU_400 },
	{ "Fate/EXTRA", EMU_400 },
	{ { 0x4C, 0x45, 0x47, 0x4F, 0xC2, 0xAE, 0x20, 0x50, 0x69, 0x72, 0x61, 0x74, 0x65, 0x73, 0x20, 0x6F, 
	    0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x43, 0x61, 0x72, 0x69, 0x62, 0x62, 0x65, 0x61, 0x6E, 0x20, 
	    0x54, 0x68, 0x65, 0x20, 0x56, 0x69, 0x64, 0x65, 0x6F, 0x20, 0x47, 0x61, 0x6D, 0x65, 0x20, 0x00 }, EMU_400 }, //LEGOÂ® Pirates of the Caribbean The Video Game 
	{ "LUNAR: SILVER STAR HARMONY", EMU_400 },
	{ { 0x52, 0x45, 0x53, 0x49, 0x53, 0x54, 0x41, 0x4E, 0x43, 0x45, 0xC2, 0xAE, 0x20, 0xEF, 0xBD, 0x9E, 
	    0xE5, 0xA0, 0xB1, 0xE5, 0xBE, 0xA9, 0xE3, 0x81, 0xAE, 0xE5, 0x88, 0xBB, 0xEF, 0xBD, 0x9E, 0x00 }, EMU_400 }, // Resistance retribution (JP)
	{ { 0x52, 0x65, 0x73, 0x69, 0x73, 0x74, 0x61, 0x6E, 0x63, 0x65, 0x3A, 0x20, 0x52, 0x65, 0x74, 0x72, 
	    0x69, 0x62, 0x75, 0x74, 0x69, 0x6F, 0x6E, 0xE2, 0x84, 0xA2, 0x00 }, EMU_400 }, // Resistance: Retributionâ„¢
	{ "SMT: Persona 2: Innocent Sin", EMU_400 },
	{ { 0x50, 0x45, 0x52, 0x53, 0x4F, 0x4E, 0x41, 0x32, 0x20, 0xE7, 0xBD, 0xAA, 0x00 }, EMU_400 }, // Persona 2 jap
	{ "SOULCALIBUR: Broken Destiny", EMU_400 },
	{ "STAR OCEAN: First Departure", EMU_400 },
	{ "TEKKEN 6", EMU_400 },
	{ "The 3rd Birthday", EMU_400 },
	{ "VALHALLAKNIGHTS", EMU_400 },	
	{ { 0x57, 0x68, 0x69, 0x74, 0x65, 0x20, 0x4B, 0x6E, 0x69, 0x67, 0x68, 0x74, 0x20, 0x43, 0x68, 0x72, 
	    0x6F, 0x6E, 0x69, 0x63, 0x6C, 0x65, 0x73, 0xE2, 0x84, 0xA2, 0x3A, 0x20, 0x4F, 0x72, 0x69, 0x67, 
	    0x69, 0x6E, 0x73, 0x00 }, EMU_400 }, // White Knight Chroniclesâ„¢: Origins	    
	{ "Z.H.P.: Unlosing Ranger VS Darkdeath Evilman", EMU_400 },
	
	
	    
	/* Games that don't work yet, but show progress */
	{ "DISSIDIA duodecim FINAL FANTASY", EMU_400 },
	{ "FINAL FANTASY IV Complete Collection", EMU_400 },
	{ { 0x4E, 0x45, 0x45, 0x44, 0x20, 0x46, 0x4F, 0x52, 0x20, 0x53, 0x50, 0x45, 0x45, 0x44, 0xE2, 0x84, 
	    0xA2, 0x20, 0x4D, 0x4F, 0x53, 0x54, 0x20, 0x57, 0x41, 0x4E, 0x54, 0x45, 0x44, 0x20, 0x35, 0x2D, 
	    0x31, 0x2D, 0x30, 0x00 }, EMU_400 }, // NEED FOR SPEEDâ„¢ MOST WANTED 5-1-0	    
	{ "Persona3 PORTABLE", EMU_400 },
	{ "RIDGE RACER", EMU_400 },
	{ "TACTICS OGRE Let Us Cling Together", EMU_400 },
	{ "Warhammer 40,000: Squad Command", EMU_400 },
};

static inline int translate_type(unsigned int type)
{
	if (type == 0)
		return DISC_TYPE_NONE;
	
	else if (type == DEVICE_TYPE_PS3_BD)
		return DISC_TYPE_PS3_BD;
	
	else if (type == DEVICE_TYPE_PS3_DVD)
		return DISC_TYPE_PS3_DVD;
	
	else if (type == DEVICE_TYPE_PS2_DVD)
		return DISC_TYPE_PS2_DVD;
	
	else if (type == DEVICE_TYPE_PS2_CD)
		return DISC_TYPE_PS2_CD;
	
	else if (type == DEVICE_TYPE_PSX_CD)
		return DISC_TYPE_PSX_CD;
	
	else if (type == DEVICE_TYPE_BDROM)
		return DISC_TYPE_BDROM;
	
	else if (type == DEVICE_TYPE_BDMR_SR)
		return DISC_TYPE_BDMR_SR;
	
	else if (type == DEVICE_TYPE_BDMR_RR)
		return DISC_TYPE_BDMR_RR;
	
	else if (type == DEVICE_TYPE_BDMRE)
		return DISC_TYPE_BDMRE;
	
	else if (type == DEVICE_TYPE_DVD)
		return DISC_TYPE_DVD;
	
	else if (type == DEVICE_TYPE_CD)
		return DISC_TYPE_CD;
	
	return DISC_TYPE_UNKNOWN;
}

static char *get_blank_iso_path(void)
{
	char *s = malloc(32);
	
	strcpy(s, "/dev_hdd0/");
	s[10] = 'v';
	s[11] = 's';
	s[12] = 'h';
	s[13] = '/';
	s[14] = 't';
	s[15] = 'a';
	s[16] = 's';
	s[17] = 'k';
	s[18] = '.';
	s[19] = 'd';
	s[20] = 'a';
	s[21] = 't';
	s[22] = 0;
	
	return s;
}

static char *build_blank_iso(char *title_id)
{
	uint8_t *buf = malloc(128*1024);
	
	memset(buf, 0, 128*1024);
	
	buf[3] = 2;
	buf[0x17] = 0x3F;
	strcpy((char *)buf+0x800, "PlayStation3");
	memcpy(buf+0x810, title_id, 4);
	buf[0x814] = '-';
	memcpy(buf+0x815, title_id+4, 5);
	memset(buf+0x81A, ' ', 0x16);
	buf[0x8000] = 1;
	strcpy((char *)buf+0x8001, "CD001");
	buf[0x8006] = 1;
	memset(buf+0x8008, ' ', 0x20);
	memcpy(buf+0x8028, "PS3VOLUME", 9);
	memset(buf+0x8031, ' ', 0x17);
	buf[0x8050] = buf[0x8057] = 0x40;
	buf[0x8078] = buf[0x807B] = buf[0x807C] = buf[0x807F] = 1;
	buf[0x8081] = buf[0x8082] = 8;
	buf[0x8084] = buf[0x808B] = 0xA;
	buf[0x808C] = 0x14;
	buf[0x8097] = 0x15;
	buf[0x809C] = 0x22;
	buf[0x809E] = buf[0x80A5] = 0x18;
	buf[0x80A7] = buf[0x80AC] = 8;
	buf[0x80AE] = 0x6F;
	buf[0x80AF] = 7;
	buf[0x80B0] = 0x16;
	buf[0x80B1] = 2;
	buf[0x80B2] = 0x2B;
	buf[0x80B3] = buf[0x80B5] = 2;
	buf[0x80B8] = buf[0x80BB] = buf[0x80BC] = 1;
	memcpy(buf+0x80be, "PS3VOLUME", 9);
	memset(buf+0x80C7, ' ', 0x266);
	strcpy((char *)buf+0x832d, "2011072202451800");
	strcpy((char *)buf+0x833e, "0000000000000000");
	strcpy((char *)buf+0x834f, "0000000000000000");
	strcpy((char *)buf+0x8360, "0000000000000000");
	buf[0x8371] = 1;
	buf[0x8800] = 2;
	strcpy((char *)buf+0x8801, "CD001");
	buf[0x8806] = 1;
	buf[0x8829] = 'P';
	buf[0x882B] = 'S';
	buf[0x882D] = '3';
	buf[0x882F] = 'V';
	buf[0x8831] = 'O';
	buf[0x8833] = 'L';
	buf[0x8835] = 'U';
	buf[0x8837] = 'M';
	buf[0x8839] = 'E';
	buf[0x8850] = buf[0x8857] = 0x40;
	strcpy((char *)buf+0x8858, "%/@");
	buf[0x8878] = buf[0x887B] = buf[0x887C] = buf[0x887F] = 1;
	buf[0x8881] = buf[0x8882] = 8;
	buf[0x8884] = buf[0x888B] = 0xA;
	buf[0x888C] = 0x16;
	buf[0x8897] = 0x17;
	buf[0x889C] = 0x22;
	buf[0x889E] = buf[0x88A5] = 0x19;
	buf[0x88A7] = buf[0x88AC] = 8;
	buf[0x88AE] = 0x6F;
	buf[0x88AF] = 7;
	buf[0x88B0] = 0x16;
	buf[0x88B1] = 2;
	buf[0x88B2] = 0x2B;
	buf[0x88B3] = buf[0x88B5] = 2;
	buf[0x88B8] = buf[0x88BB] = buf[0x88BC] = 1;
	buf[0x88BF] = 'P';
	buf[0x88C1] = 'S';
	buf[0x88C3] = '3';
	buf[0x88C5] = 'V';
	buf[0x88C7] = 'O';
	buf[0x88C9] = 'L';
	buf[0x88CB] = 'U';
	buf[0x88CD] = 'M';
	buf[0x88CF] = 'E';
	
	strcpy((char *)buf+0x8B2D, "2011072202451800");
	strcpy((char *)buf+0x8B3E, "0000000000000000");
	strcpy((char *)buf+0x8B4F, "0000000000000000");
	strcpy((char *)buf+0x8b60, "0000000000000000");
	buf[0x8B71] = 1;
	buf[0x9000] = 0xFF;
	strcpy((char *)buf+0x9001, "CD001");
	buf[0xA000] = 1;
	buf[0xA002] = 0x18;
	buf[0xA006] = 1;
	buf[0xA800] = 1;
	buf[0xA805] = 0x18;
	buf[0xA807] = 1;
	buf[0xB000] = 1;
	buf[0xB002] = 0x19;
	buf[0xB006] = 1;
	buf[0xB800] = 1;
	buf[0xB805] = 0x19;
	buf[0xB807] = 1;
	buf[0xC000] = 0x28;
	buf[0xC002] = buf[0xC009] = 0x18;
	buf[0xC00B] = buf[0xC010] = 8;
	buf[0xC012] = 0x6F;
	buf[0xC013] = 7;
	buf[0xC014] = 0x16;
	buf[0xC015] = 2;
	buf[0xC016] = 0x2B;
	buf[0xC017] = buf[0xC019] = 2;
	buf[0xC01C] = buf[0xC01F] = buf[0xC020] = 1;
	buf[0xC028] = 0x28;
	buf[0xC02A] = buf[0xC031] = 0x18;
	buf[0xC033] = buf[0xC038] = 8;
	buf[0xC03A] = 0x6F;
	buf[0xC03B] = 7;
	buf[0xC03C] = 0x16;
	buf[0xC03D] = 2;
	buf[0xC03E] = 0x2B;
	buf[0xC03F] = buf[0xC041] = 2;
	buf[0xC044] = buf[0xC047] = buf[0xC048] = buf[0xC049] = 1;
	buf[0xC800] = 0x28;
	buf[0xC802] = buf[0xC809] = 0x19;
	buf[0xC80B] = buf[0xC810] = 8;
	buf[0xC812] = 0x6F;
	buf[0xC813] = 7;
	buf[0xC814] = 0x16;
	buf[0xC815] = 2;
	buf[0xC816] = 0x2B;
	buf[0xC817] = buf[0xC819] = 2;
	buf[0xC81C] = buf[0xC81F] = buf[0xC820] = 1;
	buf[0xC828] = 0x28;
	buf[0xC82A] = buf[0xC831] = 0x19;
	buf[0xC833] = buf[0xC838] = 8;
	buf[0xC83A] = 0x6F;
	buf[0xC83B] = 7;
	buf[0xC83C] = 0x16;
	buf[0xC83D] = 2;
	buf[0xC83E] = 0x2B;
	buf[0xC83F] = buf[0xC841] = 2;
	buf[0xC844] = buf[0xC847] = buf[0xC848] = buf[0xC849] = 1;
	
	char *ret = get_blank_iso_path();
	
	FILE *f = fopen(ret, "wb");
	if (fwrite(buf, 1, 128*1024, f) != (128*1024))
	{
		fclose(f);
		free(buf);
		free(ret);
		return NULL;
	}
	
	fclose(f);
	free(buf);
	return ret;
}

static int copy_file(char *src, char *dst)
{
	int ret;
	int fd_s, fd_d;
	const uint32_t buf_size = 512*1024;
	uint8_t *buf = (uint8_t *)malloc(buf_size);
	
	ret = sysFsOpen(src, SYS_O_RDONLY, &fd_s, NULL, 0);
	if (ret == 0)
	{	
		ret = sysFsOpen(dst, SYS_O_WRONLY | SYS_O_CREAT | SYS_O_TRUNC, &fd_d, NULL, 0);
		if (ret == 0)
		{
			while (1)
			{
				uint64_t nread, nwritten;
								
				ret = sysFsRead(fd_s, buf, buf_size, &nread);
				if (ret != 0 || nread == 0)
					break;
				
				ret = sysFsWrite(fd_d, buf, nread, &nwritten);
				if (ret != 0)
					break;
				
				if (nwritten != nread)
				{
					ret = -1;
					break;
				}				
			}
			
			sysFsClose(fd_d);
		}
		
		sysFsClose(fd_s);
		
		if (ret != 0)
		{		
			sysFsUnlink(dst);
		}
		else
		{
			if (sysFsChmod(dst, S_IFMT  | 0777) != 0)
			{
				//DPRINTF("Chmod failed.\n");
			}
		}
	}
	
	//DPRINTF("Copy file returning: %x\n", ret);
	
	free(buf);
	return ret;
}

LV2_SYSCALL sys_get_hw_config(uint8_t *ret, uint8_t *config)
{
	lv2syscall2(393, (uint64_t)ret, (uint64_t)config);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_get_version(uint32_t *version)
{
	lv2syscall2(8, SYSCALL8_OPCODE_GET_VERSION, (uint64_t)version);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_get_version2(uint16_t *version)
{
	lv2syscall2(8, SYSCALL8_OPCODE_GET_VERSION2, (uint64_t)version);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_read_cobra_config(CobraConfig *cfg)
{
	cfg->size = sizeof(CobraConfig);
	lv2syscall2(8, SYSCALL8_OPCODE_READ_COBRA_CONFIG, (uint64_t)cfg);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_write_cobra_config(CobraConfig *cfg)
{
	lv2syscall2(8, SYSCALL8_OPCODE_WRITE_COBRA_CONFIG, (uint64_t)cfg);
	return_to_user_prog(s32);
}

static char *trim(char *str)
{
	int len = strlen(str);
	uint8_t *temp = (uint8_t *)strdup(str);
	uint8_t *p = temp;
	int i;
	
	for (i = 0; i < len; i++)
	{
		if (temp[i] <= ' ')
			p++;
		else
			break;		
	}
	
	len = strlen((char *)p);
	
	for (i = len-1; i >= 0; i--)
	{
		if (p[i] <= ' ')
			p[i] = 0;
		else
			break;
	}
	
	strcpy(str, (char *)p);
	free(temp);
	return str;
}

static int parse_param_sfo(char *file, const char *field, char *title_name)
{
	FILE *fp;

	fp = fopen(file, "rb");
	if (fp != NULL) {
		unsigned len, pos, str;
		unsigned char *mem = NULL;

		fseek(fp, 0, SEEK_END);
		len = ftell(fp);

		mem = (unsigned char *) malloc(len + 16);
		if (!mem) {
			fclose(fp);
			return -2;
		}

		memset(mem, 0, len + 16);

		fseek(fp, 0, SEEK_SET);
		fread((void *) mem, len, 1, fp);

		fclose(fp);

		str = (mem[8] + (mem[9] << 8));
		pos = (mem[0xc] + (mem[0xd] << 8));

		int indx = 0;

		while (str < len) {
			if (mem[str] == 0)
				break;

			if (!strcmp((char *) &mem[str], field)) {
				strncpy(title_name, (char *) &mem[pos], 63);
				free(mem);
				return 0;
			}
			while (mem[str])
				str++;
			str++;
			pos += (mem[0x1c + indx] + (mem[0x1d + indx] << 8));
			indx += 16;
		}
		if (mem)
			free(mem);
	}

	return -1;
}

LV2_SYSCALL sys_permissions_get_access(void)
{
	lv2syscall1(8, SYSCALL8_OPCODE_GET_ACCESS);
	return_to_user_prog(s32);
}

LV2_SYSCALL sys_permissions_remove_access(void)
{
	lv2syscall1(8, SYSCALL8_OPCODE_REMOVE_ACCESS);
	return_to_user_prog(s32);
}

LV2_SYSCALL cobra_usb_command(uint8_t command, int requestType, uint32_t addr, void *buf, uint16_t size)
{
	lv2syscall6(8, SYSCALL8_OPCODE_COBRA_USB_COMMAND, command, requestType, addr, (uint64_t)buf, size);
	return_to_user_prog(s32);
}

int cobra_lib_init(void)
{
	return sys_permissions_get_access();
}

int cobra_lib_finalize(void)
{
	return sys_permissions_remove_access();
}

int cobra_get_disc_type(unsigned int *real_disctype, unsigned int *effective_disctype, unsigned int *iso_disctype)
{
	sys_emu_state_t emu_state;
	unsigned int rdt, edt;
	int ret;
	
	ret = sys_storage_ext_get_disc_type(&rdt, &edt, NULL);
	if (ret != 0)
		return ret;
	
	rdt = translate_type(rdt);
	edt = translate_type(edt);
	
	if (real_disctype)
	{
		*real_disctype = rdt;
	}
	
	if (effective_disctype)
	{
		*effective_disctype = edt;
	}
	
	if (iso_disctype)
	{
		*iso_disctype = DISC_TYPE_NONE;
		
		emu_state.size = sizeof(sys_emu_state_t);
		ret = sys_storage_ext_get_emu_state(&emu_state);
		
		if (ret == 0)
		{
			int disc_emulation = emu_state.disc_emulation;
			
			if (disc_emulation != EMU_OFF)
			{
				switch (disc_emulation)
				{
					case EMU_PS3:
						*iso_disctype = DISC_TYPE_PS3_BD;
					break;
					
					case EMU_PS2_DVD:
						*iso_disctype = DISC_TYPE_PS2_DVD;
					break;
					
					case EMU_PS2_CD:
						*iso_disctype = DISC_TYPE_PS2_CD;
					break;
					
					case EMU_PSX:
						*iso_disctype = DISC_TYPE_PSX_CD;
					break;
					
					case EMU_BD:
						if (edt != DISC_TYPE_NONE)
							*iso_disctype = edt;
						else
							*iso_disctype = DISC_TYPE_BDMR_SR;
					break;
					
					case EMU_DVD:
						*iso_disctype = DISC_TYPE_DVD;
					break;
					
					default:
						*iso_disctype = DISC_TYPE_UNKNOWN;
						
				}
			}
		}
	}
		
	return 0;
}

int cobra_disc_auth(void)
{
	unsigned int real_disctype;
	int ret;
	
	ret = sys_storage_ext_get_disc_type(&real_disctype, NULL, NULL);
	if (ret != 0)
		return ret;
	
	if (real_disctype == 0)
		return ENODEV;
	
	if (real_disctype == DEVICE_TYPE_PS3_BD || real_disctype == DEVICE_TYPE_PS3_DVD)
	{
		static uint8_t buf[1024];
	
		memset(buf, 0, 0124);
	
		sys_ss_disc_auth(0x5007, (uint64_t)buf);	
	}
	else
	{
		sys_ss_disc_auth(0x5004, 0x29);
	}
	
	return 0;
}

static unsigned int ejected_realdisc;

int cobra_send_fake_disc_eject_event(void)
{
	sys_storage_ext_get_disc_type(&ejected_realdisc, NULL, NULL);
	
	sys_storage_ext_fake_storage_event(4, 0, BDVD_DRIVE);
	return sys_storage_ext_fake_storage_event(8, 0, BDVD_DRIVE);	
}

int cobra_send_fake_disc_insert_event(void)
{
	uint64_t param;	
	unsigned int real_disctype, effective_disctype, iso_disctype;
	
	cobra_get_disc_type(&real_disctype, &effective_disctype, &iso_disctype);
	
	if (ejected_realdisc == 0 && real_disctype == 0 && effective_disctype == 0 && iso_disctype == 0)
	{
		//printf("Alll disc types 0, aborting\n");
		return EABORT;
	}
	
	param = (uint64_t)(ejected_realdisc) << 32ULL;	
	sys_storage_ext_get_disc_type(&ejected_realdisc, NULL, NULL);
	sys_storage_ext_fake_storage_event(7, 0, BDVD_DRIVE);
	return sys_storage_ext_fake_storage_event(3, param, BDVD_DRIVE);
}

uint32_t *translate_str_array(char *array[], unsigned int num)
{
	uint32_t *out = malloc(num * sizeof(uint32_t));
	
	for (unsigned int i = 0; i < num; i++)
	{
		out[i] = (uint32_t)(uint64_t)array[i];
	}
	
	return out;
}

int cobra_mount_ps3_disc_image(char *files[], unsigned int num)
{
	uint32_t *files32;
	int ret;
	
	if (!files)
		return EINVAL;
	
	files32 = translate_str_array(files, num);
	ret = sys_storage_ext_mount_ps3_discfile(num, files32);
	free(files32);
	
	return ret;
}

int cobra_mount_dvd_disc_image(char *files[], unsigned int num)
{
	uint32_t *files32;
	int ret;
	
	if (!files)
		return EINVAL;
	
	files32 = translate_str_array(files, num);
	ret = sys_storage_ext_mount_dvd_discfile(num, files32);
	free(files32);
	
	return ret;
}

int cobra_mount_bd_disc_image(char *files[], unsigned int num)
{
	uint32_t *files32;
	int ret;
	
	if (!files)
		return EINVAL;
	
	files32 = translate_str_array(files, num);
	ret = sys_storage_ext_mount_bd_discfile(num, files32);
	free(files32);
	
	return ret;
}

int cobra_mount_psx_disc_image(char *file, TrackDef *tracks, unsigned int num_tracks)
{	
	ScsiTrackDescriptor scsi_tracks[100];	
	
	if (!file || num_tracks >= 100)
		return EINVAL;
	
	memset(scsi_tracks, 0, sizeof(scsi_tracks));
	
	for (int i = 0; i < num_tracks; i++)
	{
		scsi_tracks[i].adr_control = (!tracks[i].is_audio) ? 0x14 : 0x10;
		scsi_tracks[i].track_number = i+1;
		scsi_tracks[i].track_start_addr = tracks[i].lba;
	}
	
	return sys_storage_ext_mount_psx_discfile(file, num_tracks, scsi_tracks);
}

int cobra_mount_ps2_disc_image(char *files[], int num, TrackDef *tracks, unsigned int num_tracks)
{
	uint32_t *files32;
	int ret;
	ScsiTrackDescriptor scsi_tracks[100];
	
	if (tracks)
	{
		for (int i = 0; i < num_tracks; i++)
		{
			scsi_tracks[i].adr_control = (!tracks[i].is_audio) ? 0x14 : 0x10;
			scsi_tracks[i].track_number = i+1;
			scsi_tracks[i].track_start_addr = tracks[i].lba;
		}	
	}
	
	files32 = translate_str_array(files, num);
	ret = sys_storage_ext_mount_ps2_discfile(num, files32, num_tracks, (tracks) ? scsi_tracks : NULL);
	free(files32);
	
	return ret;
}

int cobra_umount_disc_image(void)
{
	int ret = sys_storage_ext_umount_discfile();
	if (ret == -1)
		ret = ENODEV;
	
	return ret;
}

int cobra_read_ps3_disc(void *buf, uint64_t sector, uint32_t count)
{
	return sys_storage_ext_read_ps3_disc(buf, sector, count);
}

int cobra_get_disc_phys_info(uint32_t handle, uint8_t layer, DiscPhysInfo *info)
{
	ScsiReadDiscStructureFormat0Response *response;
	uint8_t scsi_cmd[56];
	static uint8_t output[64] __attribute__((aligned(64)));
	int ret;
	
	if (!info)
		return EINVAL;
		
	ScsiCmdReadDiscStructure *cmd = (ScsiCmdReadDiscStructure *)scsi_cmd;
	StorageCmdScsiData *data = (StorageCmdScsiData *)(scsi_cmd+32);
					
	memset(scsi_cmd, 0, sizeof(scsi_cmd));
	cmd->opcode = SCSI_CMD_READ_DISC_STRUCTURE;
	cmd->alloc_length = sizeof(ScsiReadDiscStructureFormat0Response);
	cmd->layer_num = layer;
	data->inlen = 12;
	data->unk1 = data->unk2 = data->unk3 = 1;
	data->outlen = sizeof(ScsiReadDiscStructureFormat0Response);
		
	response = (ScsiReadDiscStructureFormat0Response *)output;			
	ret = sys_storage_send_device_command(handle, STORAGE_COMMAND_NATIVE, scsi_cmd, sizeof(scsi_cmd), response, sizeof(ScsiReadDiscStructureFormat0Response));
	
	if (ret != 0)
		return ret;
	
	memcpy(info, output+4, 17);
	return 0;
}

int cobra_get_cd_td(uint32_t handle, TrackDef *td, unsigned int max_tracks, unsigned int *num_tracks, uint32_t *lba_end)
{
	uint32_t cd_num_tracks, cd_total_tracks;
	uint8_t scsi_cmd[56];
	int ret;
	int i, j;
	
	if (!td || !num_tracks)
		return EINVAL;
	
	ScsiCmdReadTocPmaAtip *cmd = (ScsiCmdReadTocPmaAtip *)scsi_cmd;
	StorageCmdScsiData *data = (StorageCmdScsiData *)(scsi_cmd+32);
	ScsiTocResponse toc_info;
			
	memset(scsi_cmd, 0, sizeof(scsi_cmd));	
	cmd->opcode = SCSI_CMD_READ_TOC_PMA_ATIP;
	cmd->alloc_length = sizeof(toc_info);
	data->inlen = 12;
	data->unk1 = data->unk2 = data->unk3 = 1;
	data->outlen = cmd->alloc_length;
		
	ret = sys_storage_send_device_command(handle, STORAGE_COMMAND_NATIVE, scsi_cmd, sizeof(scsi_cmd), &toc_info, sizeof(toc_info));
	if (ret != 0)
		return ret;
	
	cd_num_tracks = toc_info.last_track;
	uint8_t *response = (uint8_t *) malloc(toc_info.toc_length+2);
	cmd->alloc_length = toc_info.toc_length+2;
	data->outlen = cmd->alloc_length;
				
	ret = sys_storage_send_device_command(handle, STORAGE_COMMAND_NATIVE, scsi_cmd, sizeof(scsi_cmd), response, cmd->alloc_length);
	if (ret != 0)
	{
		free(response);
		return ret;
	}	
	
	if (toc_info.first_track != 1)
	{
		return ENOTSUP;
	}
	else if ((unsigned int)(toc_info.toc_length-2) < (unsigned int)toc_info.last_track*sizeof(ScsiTrackDescriptor))
	{
		return ENOTSUP;
	}

	ScsiTrackDescriptor *tracks = (ScsiTrackDescriptor *)(response+sizeof(ScsiTocResponse));
	cd_total_tracks = (toc_info.toc_length-2) / sizeof(ScsiTrackDescriptor);
					
	for (i = 1; i <= cd_num_tracks; i++)
	{
		int found = 0;
						
		for (j = 0; j < cd_total_tracks; j++)
		{
			if (tracks[j].track_number == i)
			{
				int track_type = tracks[j].adr_control & 0xD;
				int is_audio = (track_type == 0 || track_type == 1 || track_type == 8 || track_type == 9);
				
				if (i  <= max_tracks)
				{				
					td[i-1].lba = tracks[j].track_start_addr;
					td[i-1].is_audio = is_audio;	
				}
								
				found = 1;
				break;				
			}							
		}
						
		if (!found)
		{
			ret = ENOTSUP;
			break;
		}		
	}
	
	if (ret != 0)
	{
		free(response);
		return ret;
	}
	
	for (i = 0; i < cd_total_tracks; i++)
	{
		if (tracks[i].track_number == 0xAA)
		{
			if (lba_end)
			{
				*lba_end = tracks[i].track_start_addr;
			}
			break;
		}
	}
	
	if (i == cd_total_tracks)
		return ENOTSUP;
	
	free(response);
	
	if (cd_num_tracks > max_tracks)
		*num_tracks = max_tracks;
	else
		*num_tracks = cd_num_tracks;
	
	DPRINTF("Track dump\n");
	for (i = 0; i < cd_num_tracks; i++)
	{
		DPRINTF("LBA:%08X, is_audio=%d\n", td[i].lba, td[i].is_audio);
	}
	DPRINTF("Last lba: %d\n", (lba_end) ? -7 : *lba_end);
	
	return 0;
}

int cobra_cd_read(uint32_t handle, void *buf, uint32_t sector, uint32_t count, int is_audio, int *num_errors)
{
	uint8_t scsi_cmd[56];
	ScsiCmdReadCd *cmd = (ScsiCmdReadCd *)scsi_cmd;
	StorageCmdScsiData *data = (StorageCmdScsiData *)(scsi_cmd+32);
	int nerrors = 0;
	
	if (!buf)
		return EINVAL;
	
	uint8_t *read_buf = (uint8_t *)buf;
	
	DPRINTF("Function begin, sector=%08X, count=%d, audio=%d\n", sector, count, is_audio);
	
	for (uint32_t i = 0; i < count; i++)
	{	
		memset(scsi_cmd, 0, sizeof(scsi_cmd));
		cmd->opcode = SCSI_CMD_READ_CD;
		cmd->lba = sector;
		cmd->length[0] = 0;
		cmd->length[1] = 0;
		cmd->length[2] = 1;
		cmd->misc = (is_audio) ? 0x10 : 0xF8;
		data->inlen = 12;
		data->unk1 = data->unk2 = data->unk3 = 1;
		data->outlen = 2352;
		
		DPRINTF("Reading sector %08X, try=%d\n", sector, i+1);
		
		for (int j = 0; j < 10; j++)
		{	
			int ret = sys_storage_send_device_command(handle, STORAGE_COMMAND_NATIVE, scsi_cmd, sizeof(scsi_cmd), read_buf, 2352);
			if (ret == 0)
			{
				break;
			}
			else if (j == 9)
			{
				unsigned int disctype;
				
				memset(read_buf, 0, 2352);
				nerrors++;
				DPRINTF("Read sector: %lx all retries failed (%x)\n", (long unsigned int)sector, ret);
				
				sys_storage_ext_get_disc_type(NULL, &disctype, NULL);
				if (disctype == 0)
				{
					DPRINTF("Disc was removed!!\n");
					return ENODEV;
				}
			}
		}
		
		sector++;
		read_buf += 2352;
	}
	
	if (num_errors)
		*num_errors = nerrors;
	
	DPRINTF("Returning, number_of_errors=%d\n", nerrors);
	
	return (nerrors > 0) ? EIO : 0;
}

int cobra_parse_cue(void *cue, uint32_t size, TrackDef *tracks, unsigned int max_tracks, unsigned int *num_tracks, char *filename, unsigned int fn_size)
{
#define skip_spaces() \
	while (*p <= ' ' && *p >= 0) \
	{ \
		p++; \
		\
		if (*(p-1) == '\n') \
			goto continue_loop; \
		\
		else if (*(p-1) == 0) \
			goto exit_loop; \
	}
	
	char *cue_buf = cue;
	char *p;
	char *bin_file;
	int read_index;
	int ntracks;
	uint32_t tracks_lba[max_tracks];
	int ret = EABORT;
	
	if (!cue)
		return EINVAL;
	
	p = cue_buf;
	ntracks = 0;
	bin_file = NULL;
	read_index = 0;		
	
	while (ntracks < max_tracks)
	{
continue_loop:	
		skip_spaces();		
		
		if (strncasecmp(p, "FILE", 4) == 0 && p[4] <= ' ' && p[4] > 0)
		{
			if (bin_file)
			{
				// We don't support more than one file, leave here
				break;
			}
			
			p = p+4;
			
			skip_spaces();
			
			if (*p == '"')
			{
				p++;
				bin_file = p;
				
				while (*p != '"')
				{
					p++;
					
					if (*(p-1) == '\n')
						goto continue_loop;
					
					else if (*(p-1) == 0)
					{
						ntracks = 0;
						ret = EABORT;
						break;
					}
						
				}
				
				*p = 0;
				p++;
				
				char *last_trail1 = strrchr(bin_file, '/');
				char *last_trail2 = strrchr(bin_file, '\\');
				
				char *last_trail = (last_trail1 > last_trail2) ? last_trail1 : last_trail2;
				
				if (last_trail)
				{
					bin_file = last_trail+1;
				}
				
				strncpy(filename, bin_file, fn_size);				
			}
		}
		else if (strncasecmp(p, "TRACK", 5) == 0 && p[5] <= ' ' && p[5] > 0)
		{
			if (read_index)
			{
				//DPRINTF("Found other track before INDEX 01\n");
				ret = ENOTSUP;
				break;
			}
			
			if (!bin_file)
			{
				//DPRINTF("TRACK before file!!!\n");
				ret = ENOTSUP;
				break;
			}
			
			p = p+5;
			
			skip_spaces();
			
			if (strtol(p, &p, 10) != (ntracks+1))
				break;
			
			skip_spaces();
			
			if (ntracks == 0)
			{
				if (strncasecmp(p, "MODE2/2352", 9) != 0 || !(p[10] <= ' ' && p[10] >= 0))
				{
					//DPRINTF("First track is not MODE2/2352!!!\n");
					ret = ENOTSUP;
					break;	
				}
			}
			else if (strncasecmp(p, "AUDIO", 5) != 0 || !(p[5] <= ' ' && p[5] >= 0))
			{
				//DPRINTF("Found a track which is not AUDIO!!!\n");
				ret = ENOTSUP;
				break;
			}
			
			read_index = 1;			
		}
		else if (strncasecmp(p, "INDEX", 5) == 0 && p[5] <= ' ' && p[5] > 0)
		{
			if (read_index)
			{
				p += 5;
				skip_spaces();
				
				if (strtol(p, &p, 10) == 1)
				{
					skip_spaces();
					
					int minutes, seconds, frames;
					
					minutes = strtol(p, &p, 10);
					if (minutes >= 256 || minutes < 0)
					{
						//DPRINTF("Bad minutes format.\n");
					}
					
					if (*p != ':')
					{
						//DPRINTF("Bad index formatting (1)\n");
					}
					
					seconds = strtol(p+1, &p, 10);
					if (seconds >= 256 || seconds < 0)
					{
						//DPRINTF("Bad seconds format\n");
					}
					
					if (*p != ':')
					{
						//DPRINTF("Bad index formatting(2)\n");
					}
					
					frames = strtol(p+1, &p, 10);					
					if (frames >= 256 || frames < 0)
					{
						//DPRINTF("Bad frames format\n");
					}
					
					uint32_t lba = msf_to_lba(minutes, seconds, frames);
					
					if (ntracks == 0)
					{
						if (lba != 0)
						{
							//DPRINTF("First track must be at 00:00:00, but it is at %02d:%02d:%02d\n", minutes, seconds, frames);
							ret = ENOTSUP;
							break;
						}
					}
					/*else if ((lba*2352) > bin_size)
					{
						//DPRINTF("Track outside file scope.\n");
						break;
					}*/
					
					tracks_lba[ntracks++] = lba;	
					read_index = 0;
				}
			}
			else
			{
				//DPRINTF("Warning: INDEX before track.\n");
			}
		}
		
		while (*p != '\n' && *p != 0)
			p++;
		
		if (*p == 0)
			break;		
	} 
	
exit_loop:

	if (ntracks == 0)
	{
		//DPRINTF("No tracks or error.\n");
		return ret;
	}
	
	for (int i = 0; i < ntracks; i++)
	{
		if (i < max_tracks)
		{
			tracks[i].lba = tracks_lba[i];
			tracks[i].is_audio = (i != 0);
		}
	}
	
	if (num_tracks)
	{
		if (ntracks > max_tracks)
			*num_tracks = max_tracks;
		else
			*num_tracks = ntracks;
	}
	
	return 0;
}

int cobra_create_cue(char *path, char *filename, TrackDef *tracks, unsigned int num_tracks)
{
	if (!path || !tracks || !num_tracks)
		return EINVAL;
	
	FILE *cue = fopen(path, "w");
	if (!cue)
		return EIO;
	
	fprintf(cue, "FILE \"%s\" BINARY\r\n", filename);
	
	for (int i = 0; i < num_tracks; i++)
	{
		uint32_t lba;
		uint8_t m, s, f;
		
		lba = tracks[i].lba-tracks[0].lba;
		
		lba_to_msf(lba, &m, &s, &f);
		fprintf(cue, "  TRACK %02d %s\r\n", i+1, (!tracks[i].is_audio) ? "MODE2/2352" : "AUDIO");
		fprintf(cue, "    INDEX 01 %02d:%02d:%02d\r\n", m, s, f);
	}
	
	fclose(cue);
	return 0;
}

int cobra_create_mds(char *path, uint64_t size_in_sectors, DiscPhysInfo *layer0, DiscPhysInfo *layer1)
{
	uint32_t size = size_in_sectors;
	
	if (!path || !layer0 || !layer1)
		return EINVAL;
	
	FILE *mds = fopen(path, "wb");
	if (mds)
	{
		*(uint32_t *)&base_mds[0x5C] = *(uint32_t *)&base_mds[0x7C] = SWAP32(size);					
		memcpy(base_mds+0x8C4, layer0, 17);
		memcpy(base_mds+0x18c8, layer1, 17);
			
		fwrite(base_mds, 1, sizeof(base_mds), mds);
		fclose(mds);
	}
	else
	{
		return EIO;
	}
	
	return 0;
}

int cobra_map_game(char *path, char *title_id, int *special_mode)
{
	int sm = 0;
	int ret;
	unsigned int real_disctype;
	
	if (!path)
	{
		ret = sys_map_path("/dev_bdvd", NULL);
		if (ret != 0)
			return ret;
		
		sys_map_path("/app_home", "/dev_usb000");
		return 0;
	}
	
	if (!title_id || strlen(title_id) != 9)
		return EINVAL;
	
	sm = 0;
			
	ret = sys_map_path("/dev_bdvd", path);
	if (ret != 0)
		return ret;
	
	sys_map_path("/app_home", path);		
	sys_storage_ext_get_disc_type(&real_disctype, NULL, NULL);
			
	if (real_disctype == 0)
	{
		char *files[1];
		char *blank_iso = build_blank_iso(title_id);
		
		if (blank_iso)
		{
			files[0] = blank_iso;			
			ret = cobra_mount_ps3_disc_image(files, 1);
			free(blank_iso);
			
			if (ret == 0)
			{
				cobra_send_fake_disc_insert_event();
				sm = 1;
			}
		}		
	}
	
	if (special_mode)
		*special_mode = sm;
	
	return 0;
}

int cobra_map_paths(char *paths[], char *new_paths[], unsigned int num)
{
	return sys_map_paths(paths, new_paths, num);
}

int cobra_set_psp_umd(char *path, char *umd_root, char *icon_save_path)
{
	sysFSStat stat;
	char umd_file[256];
	char title_id[11];
	char *root;
	unsigned int real_disctype, effective_disctype, iso_disctype;
	int ret;
	
	int decrypt_patch = 1;
	uint32_t tag = 0;
	uint8_t *keys = NULL;
	uint8_t code = 0;
	uint8_t sector[2048];
	
	if (!path || !icon_save_path)
		return EINVAL;
	
	if (sysFsStat(PSPL_ICON, &stat) != 0)
	{
		return EABORT;
	}
	
	uint64_t pos, nread;
	int fd;
	
	if (sysFsOpen(path, SYS_O_RDONLY, &fd, NULL, 0) != 0)
		return EIO;
	
	if (sysFsLseek(fd, 0x8000, SEEK_SET, &pos) != 0)
	{
		sysFsClose(fd);
		return EIO;
	}
	
	if (sysFsRead(fd, sector, sizeof(sector), &nread) != 0)
	{
		sysFsClose(fd);
		return EIO;
	}
	
	sysFsClose(fd);
	if (sector[0] != 1 || memcmp(sector+1, "CD001", 5) != 0)
		return EIO;
	
	memset(title_id, 0, sizeof(title_id));
	memcpy(title_id, sector+0x373, 10);
		
	root = umd_root;
	
	if (!root)
	{
		char *files[1];
		int i;
		
		cobra_get_disc_type(&real_disctype, &effective_disctype, &iso_disctype);
		
		if (iso_disctype != DISC_TYPE_NONE)
			return EBUSY;
		
		if (effective_disctype != DISC_TYPE_NONE)
		{
			cobra_send_fake_disc_eject_event();
		}
		
		files[0] = path;
		ret = cobra_mount_dvd_disc_image(files, 1);
		if (ret != 0)
		{
			if (real_disctype != DISC_TYPE_NONE)
				cobra_send_fake_disc_insert_event();
			
			return ret;
		}
		
		cobra_send_fake_disc_insert_event();
		
		// Wait 0.5 seconds for automonter to mount iso
		for (i = 0; i < 25; i++)
		{
			sysFSStat stat;
		
			if (sysFsStat("/dev_bdvd", &stat) == 0)
			{
				break;
			}
		
			sysUsleep(20000);
		}
		
		if (i == 25)
		{			
			cobra_send_fake_disc_eject_event();
			sys_storage_ext_umount_discfile();
			
			if (real_disctype != DISC_TYPE_NONE)
				cobra_send_fake_disc_insert_event();
			
			return EIO;
		}
		
		root = "/dev_bdvd";
	}
	else
	{
		real_disctype = DISC_TYPE_NONE;
	}
	
	snprintf(umd_file, sizeof(umd_file), "%s/PSP_GAME/ICON0.PNG", root);
	
	if (copy_file(umd_file, icon_save_path) == 0)
	{
		int fd;
		
		sys_map_path((char *)PSPL_ICON, icon_save_path);
		snprintf(umd_file, sizeof(umd_file), "%s/PSP_GAME/SYSDIR/prometheus.prx", root);
		
		if (sysFsStat(umd_file, &stat) != 0)
		{
			snprintf(umd_file, sizeof(umd_file), "%s/PSP_GAME/SYSDIR/EBOOT.BIN", root);
			
			if (sysFsOpen(umd_file, SYS_O_RDONLY, &fd, NULL, 0) == 0)
			{
				uint32_t header[0xD4/4];
				uint64_t read;
			
				sysFsRead(fd, header, sizeof(header), &read);
				if (read == sizeof(header))
				{
					if (header[0] == 0x7E505350)
					{
						unsigned int i;
					
						decrypt_patch = 0;
						for (i = 0; i < NUM_SUPPORTED_TAGS; i++)
						{
							if (emulator_supported_tags355[i] == header[0xD0/4])
								break;
						}
					
						if (i == NUM_SUPPORTED_TAGS)
						{
							unsigned int j;
						
							//DPRINTF("Tag not supported natively.\n");
						
							for (j = 0; j < NUM_EXTRA_KEYS; j++)
							{
								if (psp_extra_keys[j].tag == header[0xD0/4])
								{
									tag = psp_extra_keys[j].tag;
									code = psp_extra_keys[j].code;
									keys = psp_extra_keys[j].keys;
									//DPRINTF("Tag %08X found\n", psp_extra_keys[j].tag);
									break;
								}
							}
						
							if (j == NUM_EXTRA_KEYS)
							{
								//DPRINTF("No tag found. Game will crash.\n");
							}
						}
						else
						{
							//DPRINTF("Tag supported natively.\n");
						}
					}
				}
				sysFsClose(fd);
			}
			ret = 0;
		}
		else
		{
			ret = ENOTSUP;
		}		
	}
	else
	{
		ret = EIO;
	}
	
	if (!umd_root)
	{
		cobra_send_fake_disc_eject_event();
		sys_storage_ext_umount_discfile();
			
		if (real_disctype != DISC_TYPE_NONE)
			cobra_send_fake_disc_insert_event();
	}
	
	if (ret == 0)
	{
		sys_psp_set_umdfile(path, title_id, 0);
		sys_psp_set_decrypt_options(decrypt_patch, tag, keys, code, 0, NULL, 0);
	}
	
	return ret;
}

static int get_emu(char *title_id, char *title_name)
{
	for (int i = 0; i < N_TITLE_IDS; i++)
	{
		if (strcmp(title_id, emu_by_title_ids[i].key) == 0)
			return emu_by_title_ids[i].value;
	}
	
	if (title_name[0])
	{
		for (int i = 0; i < N_TITLE_NAMES; i++)
		{
			if (strcmp(title_name, emu_by_title_name[i].key) == 0)
				return emu_by_title_name[i].value;
		}
	}
	
	return EMU_355;
}

static int check_lambda(void)
{
	// Meh, removed. lambda.db is not used anymore anyways
	return 0;
}

int cobra_set_psp_umd2(char *path, char *umd_root, char *icon_save_path, uint64_t options)
{
	sysFSStat stat;
	char umd_file[256];
	char title_id[11];
	char title_name[256];
	char *root;
	unsigned int real_disctype, effective_disctype, iso_disctype;
	int ret;
	
	int decrypt_patch = 1;
	uint32_t tag = 0;
	uint8_t *keys = NULL;
	uint8_t code = 0;
	uint8_t sector[2048];
	int prometheus = 0;
	int emu = options&0xF;
	
	if (!path || !icon_save_path)
		return EINVAL;
	
	if (sysFsStat(PSPL_ICON, &stat) != 0)
	{
		return EABORT;
	}
	
	if (sysFsStat(PSPL_LAMBDA, &stat) != 0)
	{
		return ESYSVER;
	}
	
	uint64_t pos, nread;
	int fd;
	
	if (sysFsOpen(path, SYS_O_RDONLY, &fd, NULL, 0) != 0)
		return EIO;
	
	if (sysFsLseek(fd, 0x8000, SEEK_SET, &pos) != 0)
	{
		sysFsClose(fd);
		return EIO;
	}
	
	if (sysFsRead(fd, sector, sizeof(sector), &nread) != 0)
	{
		sysFsClose(fd);
		return EIO;
	}
	
	sysFsClose(fd);
	if (sector[0] != 1 || memcmp(sector+1, "CD001", 5) != 0)
		return EIO;
	
	memset(title_id, 0, sizeof(title_id));
	memcpy(title_id, sector+0x373, 10);
		
	root = umd_root;
	
	if (!root)
	{
		char *files[1];
		int i;
		
		cobra_get_disc_type(&real_disctype, &effective_disctype, &iso_disctype);
		
		if (iso_disctype != DISC_TYPE_NONE)
			return EBUSY;
		
		if (effective_disctype != DISC_TYPE_NONE)
		{
			cobra_send_fake_disc_eject_event();
		}
		
		files[0] = path;
		ret = cobra_mount_dvd_disc_image(files, 1);
		if (ret != 0)
		{
			if (real_disctype != DISC_TYPE_NONE)
				cobra_send_fake_disc_insert_event();
			
			return ret;
		}
		
		cobra_send_fake_disc_insert_event();
		
		// Wait 0.5 seconds for automonter to mount iso
		for (i = 0; i < 25; i++)
		{
			sysFSStat stat;
		
			if (sysFsStat("/dev_bdvd", &stat) == 0)
			{
				break;
			}
		
			sysUsleep(20000);
		}
		
		if (i == 25)
		{			
			cobra_send_fake_disc_eject_event();
			sys_storage_ext_umount_discfile();
			
			if (real_disctype != DISC_TYPE_NONE)
				cobra_send_fake_disc_insert_event();
			
			return EIO;
		}
		
		root = "/dev_bdvd";
	}
	else
	{
		real_disctype = DISC_TYPE_NONE;
	}
	
	snprintf(umd_file, sizeof(umd_file), "%s/PSP_GAME/ICON0.PNG", root);
	
	if (copy_file(umd_file, icon_save_path) == 0)
	{
		int fd;
		
		sys_map_path((char *)PSPL_ICON, icon_save_path);
		snprintf(umd_file, sizeof(umd_file), "%s/PSP_GAME/SYSDIR/EBOOT.OLD", root);
		
		if (sysFsStat(umd_file, &stat) != 0)
		{
			snprintf(umd_file, sizeof(umd_file), "%s/PSP_GAME/SYSDIR/EBOOT.BIN", root);
		}
		else
		{
			prometheus = 1;
		}
			
		if (sysFsOpen(umd_file, SYS_O_RDONLY, &fd, NULL, 0) == 0)
		{
			uint32_t header[0xD4/4];
			uint64_t read;
			
			sysFsRead(fd, header, sizeof(header), &read);
			if (read == sizeof(header))
			{
				if (header[0] == 0x7E505350)
				{
					unsigned int i;
				
					decrypt_patch = 0;
					for (i = 0; i < NUM_SUPPORTED_TAGS; i++)
					{
						if (emulator_supported_tags355[i] == header[0xD0/4])
							break;
					}
					
					if (i == NUM_SUPPORTED_TAGS)
					{
						unsigned int j;
						
						//DPRINTF("Tag not supported natively.\n");
						
						for (j = 0; j < NUM_EXTRA_KEYS; j++)
						{
							if (psp_extra_keys[j].tag == header[0xD0/4])
							{
								tag = psp_extra_keys[j].tag;
								code = psp_extra_keys[j].code;
								keys = psp_extra_keys[j].keys;
								//DPRINTF("Tag %08X found\n", psp_extra_keys[j].tag);
								break;
							}
						}
						
						if (j == NUM_EXTRA_KEYS)
						{
							//DPRINTF("No tag found. Game will crash.\n");
						}
					}
					else
					{
						//DPRINTF("Tag supported natively.\n");
					}
				}
			}
			sysFsClose(fd);
		}
		
		if (emu == EMU_AUTO)
		{		
			snprintf(umd_file, sizeof(umd_file), "%s/PSP_GAME/PARAM.SFO", root);
			if (parse_param_sfo(umd_file, "TITLE", title_name) != 0)
			{
				title_name[0] = 0;
			}
			
			emu = get_emu(title_id, title_name);
		}
		
		ret = 0;			
	}
	else
	{
		ret = EIO;
	}
	
	if (!umd_root)
	{
		cobra_send_fake_disc_eject_event();
		sys_storage_ext_umount_discfile();
			
		if (real_disctype != DISC_TYPE_NONE)
			cobra_send_fake_disc_insert_event();
	}
	
	if (ret == 0)
	{
		if (emu == EMU_400)
		{
			if (check_lambda() < 0)
				return ECANCELED;
			
			sys_storage_ext_mount_encrypted_image(PSPL_LAMBDA, "/dev_moo", "CELL_FS_FAT", PSPL_LAMBDA_NONCE);
			sys_psp_change_emu_path("/dev_moo/pspemu");
		}
		
		sys_psp_set_umdfile(path, title_id, prometheus);
		sys_psp_set_decrypt_options(decrypt_patch, tag, keys, code, 0, NULL, 0);	
	}
	
	return ret;
}

int cobra_unset_psp_umd(void)
{
	int ret = sys_map_path((char *)PSPL_ICON, NULL);
	if (ret == ENOSYS)
		return ret;
	
	sys_psp_set_umdfile(NULL, NULL, 0);
	sys_psp_change_emu_path(NULL);
	sys_storage_ext_mount_encrypted_image(NULL, "/dev_moo", NULL, 0);

	return 0;
}

int cobra_get_usb_device_name(char *mount_point, char *dev_name)
{
	int ret;
	uint64_t i, size, device;
	CellFsMountInfo *info;
	sys_device_handle_t handle;

	ret = cellFsUtilGetMountInfoSize(&size);
	if (ret != 0)
		return ret;
	
	info = malloc(size*sizeof(CellFsMountInfo));
	ret = cellFsUtilGetMountInfo(info, size, &size);
	if (ret != 0)
	{
		free(info);
		return ret;
	}
	
	for (i = 0; i < size; i++)
	{
		if (strcmp(info[i].mount_point, mount_point) == 0)
			break;
	}
	
	if (i == size)
	{
		free(info);
		return -1;
	}
	
	device = get_device(info[i].block_dev);	
	free(info);
	
	if (device == 0)
	{
		//DPRINTF("Cannot translate device name: %s\n", info[i].block_dev);
		return -1;
	}
	
	ret = sys_storage_open(device, 0, &handle, 0);
	if (ret == 0)
	{
		uint8_t cmd[64];		
		memset(cmd, 0, 64);
		
		UfiCmdInquiry *inquiry_cmd = (UfiCmdInquiry *)(cmd+4);
		
		inquiry_cmd->opcode = UFI_CMD_INQUIRY;
		inquiry_cmd->alloc_length = sizeof(UfiInquiryResponse);
		cmd[23] = 1;
		
		ret = sys_storage_send_device_command(handle, STORAGE_COMMAND_NATIVE, cmd, 28, cmd, 64);
		if (ret == 0)
		{
			UfiInquiryResponse *response = (UfiInquiryResponse *)(cmd+28);
			
			memcpy(dev_name, response->product, 16);
			dev_name[17] = 0;
			trim(dev_name);
		}
		else
		{
			//DPRINTF("sys_storage_send_device_command failed: %x\n", ret);
		}
		
		sys_storage_close(handle);
	}
	else
	{
		//DPRINTF("sys_storge_open failed: %x\n", ret);
	}
	
	return ret;
}

int cobra_get_ps2_emu_type(void)
{
	int ret;
	uint8_t hw_config[8], ret2;
	
	ret = sys_get_hw_config(&ret2, hw_config);
	if (ret != 0)
	{
		return ret;
	}
	
	if (hw_config[6]&1)
	{
		ret = PS2_EMU_HW;
	}
	else if (hw_config[0]&0x20)
	{
		ret = PS2_EMU_GX;
	}
	else
	{
		ret = PS2_EMU_SW;
	}
	
	return ret;
}

int cobra_get_version(uint16_t *cobra_version, uint16_t *ps3_version)
{
	uint32_t version1;
	uint16_t version2;
	int ret;
	
	ret = sys_get_version(&version1);
	if (ret != 0)
		return ret;
	
	if (cobra_version && sys_get_version2(&version2) == 0)
	{
		*cobra_version = version2;
	}
	else if (cobra_version)
	{
		switch (version1&0xFF)
		{
			case 1:
				*cobra_version = 0x0102;
			break;
			
			case 2:
				*cobra_version = 0x0200;
			break;
			
			case 3:
				*cobra_version = 0x0300;
			break;
			
			case 4:
				*cobra_version = 0x0310;
			break;
			
			case 5:
				*cobra_version = 0x0320;
			break;
			
			case 6:
				*cobra_version = 0x0330;
			break;
			
			case 7:
				*cobra_version = 0x0400;
			break;
			
			default:
				*cobra_version = 0x0410;
			break;
		}
	}
	
	if (ps3_version)
	{
		*ps3_version = ((version1>>8)&0xFFFF);
		
		if (*ps3_version == 0x0000)
		{
			*ps3_version = 0x0341;
		}
	}
	
	return 0;
}

int cobra_read_config(CobraConfig *cfg)
{
	if (!cfg)
		return EINVAL;
	
	cfg->size = sizeof(CobraConfig);	
	return sys_read_cobra_config(cfg);
}

int cobra_write_config(CobraConfig *cfg)
{
	if (!cfg)
		return EINVAL;
	
	cfg->size = sizeof(CobraConfig);	
	return sys_write_cobra_config(cfg);
}

int cobra_led_control(unsigned int led)
{
	return cobra_usb_command(CMD_LED_CONTROL, TYPE_HOST2DEV, led, NULL, 0);
}

int cobra_build_netiso_params(void *param_buf, char *server, uint16_t port, char *remote_path, int emu_mode, int num_tracks, TrackDef *tracks)
{
	netiso_args *args = (netiso_args *)param_buf;
	ScsiTrackDescriptor *scsi_tracks = (ScsiTrackDescriptor *)&args->tracks[0];
	
	memset(param_buf, 0, 65536);
	
	if (emu_mode < EMU_PS3 || emu_mode >= EMU_MAX || num_tracks >= 100)
		return EINVAL;
	
	
	if (strlen(server) >= 0x40 || strlen(remote_path) >= 0x420)
		return EINVAL;
	
	strcpy(args->server, server);
	strcpy(args->path, remote_path);
	args->port = port;
	args->emu_mode = emu_mode;
	args->numtracks = num_tracks;
	
	if (tracks)
	{
		for (int i = 0; i < num_tracks; i++)
		{
			scsi_tracks[i].adr_control = (tracks[i].is_audio) ? 0x10 : 0x14;
			scsi_tracks[i].track_number = i+1;
			scsi_tracks[i].track_start_addr = tracks[i].lba;
		}
	}
	
	return 0;
}

int cobra_load_vsh_plugin(unsigned int slot, char *path, void *arg, uint32_t arg_size)
{
	lv2syscall5(8, SYSCALL8_OPCODE_LOAD_VSH_PLUGIN, slot, (uint64_t)path, (uint64_t)arg, arg_size);
	return_to_user_prog(s32);
}

int cobra_unload_vsh_plugin(unsigned int slot)
{
	lv2syscall2(8, SYSCALL8_OPCODE_UNLOAD_VSH_PLUGIN, slot);
	return_to_user_prog(s32);
}


