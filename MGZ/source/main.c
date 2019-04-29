#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <malloc.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <lv2/sysfs.h>
#include <sys/file.h>
#include <sys/process.h>
#include <lv2/process.h>
#include <ppu-lv2.h>
#include <ppu-types.h>
#include <io/pad.h>
#include <tiny3d.h>
#include <sys/memory.h>
#include <ft2build.h>
#include <freetype/freetype.h> 
#include <freetype/ftglyph.h>
#include <sys/thread.h>
#include <pngdec/pngdec.h>
#include <jpgdec/jpgdec.h>
#include <sysmodule/sysmodule.h>
#include <sysutil/osk.h>
#include <sysutil/msg.h>
#include <sysutil/sysutil.h>
#include <sysutil/game.h>
#include <arpa/inet.h>

#include <zip.h>

#include <sys/systime.h>

#include <net/net.h>
#include <http/http.h>
#include <http/https.h>
#include <ssl/ssl.h>

#include <MagickWand/MagickWand.h>

#include "cobra.h"
#include "ntfs.h"
#include "ps3mapi.h"

#include "syscall8.h"
#include "common.h"
#include "pad.h"
#include "zlib.h"
#include "ttf_render.h"
#include "libfont2.h"
#include "iso.h"
#include "osk_input.h"

#include "gtf.h"
#include "gim.h"
#include "gim2png.h"
#include "vag2wav.h"
#include "jsx.h"
#include "cxml.h"

#include "md5.h"
#include "sha1.h"
#include "ird.h"
#include "trpex.h"
#include "ciso.h"

#include "RCO/rco.h"

#include "ps2gen.h"

#include "xreg.h"

#include "payload_sky_421C_bin.h"
#include "umount_421C_bin.h"
#include "mamba_421C_lz_bin.h"
#include "mamba_loader_421C_bin.h"

#include "payload_sky_421D_bin.h"
#include "umount_421D_bin.h"
#include "mamba_421D_lz_bin.h"
#include "mamba_loader_421D_bin.h"

#include "payload_sky_430C_bin.h"
#include "umount_430C_bin.h"
#include "mamba_430C_lz_bin.h"
#include "mamba_loader_430C_bin.h"

#include "payload_sky_430D_bin.h"
#include "umount_430D_bin.h"
#include "mamba_430D_lz_bin.h"
#include "mamba_loader_430D_bin.h"

#include "payload_sky_431C_bin.h"
#include "umount_431C_bin.h"
#include "mamba_431C_lz_bin.h"
#include "mamba_loader_431C_bin.h"

#include "payload_sky_440C_bin.h"
#include "umount_440C_bin.h"
#include "mamba_440C_lz_bin.h"
#include "mamba_loader_440C_bin.h"

#include "payload_sky_441C_bin.h"
#include "umount_441C_bin.h"
#include "mamba_441C_lz_bin.h"
#include "mamba_loader_441C_bin.h"

#include "payload_sky_441D_bin.h"
#include "umount_441D_bin.h"
#include "mamba_441D_lz_bin.h"
#include "mamba_loader_441D_bin.h"

#include "payload_sky_446C_bin.h"
#include "umount_446C_bin.h"
#include "mamba_446C_lz_bin.h"
#include "mamba_loader_446C_bin.h"

#include "payload_sky_446D_bin.h"
#include "umount_446D_bin.h"
#include "mamba_446D_lz_bin.h"
#include "mamba_loader_446D_bin.h"

#include "payload_sky_450C_bin.h"
#include "umount_450C_bin.h"
#include "mamba_450C_lz_bin.h"
#include "mamba_loader_450C_bin.h"

#include "payload_sky_450D_bin.h"
#include "umount_450D_bin.h"
#include "mamba_450D_lz_bin.h"
#include "mamba_loader_450D_bin.h"

#include "payload_sky_453C_bin.h"
#include "umount_453C_bin.h"
#include "mamba_453C_lz_bin.h"
#include "mamba_loader_453C_bin.h"

#include "payload_sky_453D_bin.h"
#include "umount_453D_bin.h"
#include "mamba_453D_lz_bin.h"
#include "mamba_loader_453D_bin.h"

#include "payload_sky_455C_bin.h"
#include "umount_455C_bin.h"
#include "mamba_455C_lz_bin.h"
#include "mamba_loader_455C_bin.h"

#include "payload_sky_455D_bin.h"
#include "umount_455D_bin.h"
#include "mamba_455D_lz_bin.h"
#include "mamba_loader_455D_bin.h"

#include "payload_sky_460C_bin.h"
#include "umount_460C_bin.h"
#include "mamba_460C_lz_bin.h"
#include "mamba_loader_460C_bin.h"

#include "payload_sky_465C_bin.h"
#include "umount_465C_bin.h"
#include "mamba_465C_lz_bin.h"
#include "mamba_loader_465C_bin.h"

#include "payload_sky_465D_bin.h"
#include "umount_465D_bin.h"
#include "mamba_465D_lz_bin.h"
#include "mamba_loader_465D_bin.h"

#include "payload_sky_470C_bin.h"
#include "umount_470C_bin.h"
#include "mamba_470C_lz_bin.h"
#include "mamba_loader_470C_bin.h"

#include "payload_sky_470D_bin.h"
#include "umount_470D_bin.h"
#include "mamba_470D_lz_bin.h"
#include "mamba_loader_470D_bin.h"

#include "payload_sky_475C_bin.h"
#include "umount_475C_bin.h"
#include "mamba_475C_lz_bin.h"
#include "mamba_loader_475C_bin.h"

#include "payload_sky_475D_bin.h"
#include "umount_475D_bin.h"
#include "mamba_475D_lz_bin.h"
#include "mamba_loader_475D_bin.h"

#include "payload_sky_476C_bin.h"
#include "umount_476C_bin.h"
#include "mamba_476C_lz_bin.h"
#include "mamba_loader_476C_bin.h"

#include "payload_sky_476D_bin.h"
#include "umount_476D_bin.h"
#include "mamba_476D_lz_bin.h"
#include "mamba_loader_476D_bin.h"

#include "payload_sky_478C_bin.h"
#include "umount_478C_bin.h"
#include "mamba_478C_lz_bin.h"
#include "mamba_loader_478C_bin.h"

#include "payload_sky_478D_bin.h"
#include "umount_478D_bin.h"
#include "mamba_478D_lz_bin.h"
#include "mamba_loader_478D_bin.h"

#include "payload_sky_480C_bin.h"
#include "umount_480C_bin.h"
#include "mamba_480C_lz_bin.h"
#include "mamba_loader_480C_bin.h"

#include "payload_sky_480D_bin.h"
#include "umount_480D_bin.h"
#include "mamba_480D_lz_bin.h"
#include "mamba_loader_480D_bin.h"

#include "payload_sky_481C_bin.h"
#include "umount_481C_bin.h"
#include "mamba_481C_lz_bin.h"
#include "mamba_loader_481C_bin.h"

#include "payload_sky_481D_bin.h"
#include "umount_481D_bin.h"
#include "mamba_481D_lz_bin.h"
#include "mamba_loader_481D_bin.h"

#include "payload_sky_482C_bin.h"
#include "umount_482C_bin.h"
#include "mamba_482C_lz_bin.h"
#include "mamba_loader_482C_bin.h"

#include "payload_sky_482D_bin.h"
#include "umount_482D_bin.h"
#include "mamba_482D_lz_bin.h"
#include "mamba_loader_482D_bin.h"

#include "payload_sky_483C_bin.h"
#include "umount_483C_bin.h"
#include "mamba_483C_lz_bin.h"
#include "mamba_loader_483C_bin.h"

#include "payload_sky_484C_bin.h"
#include "umount_484C_bin.h"
#include "mamba_484C_lz_bin.h"
#include "mamba_loader_484C_bin.h"

#include "payload_sky_484D_bin.h"
#include "umount_484D_bin.h"
#include "mamba_484D_lz_bin.h"
#include "mamba_loader_484D_bin.h"

#include "ps2gxemu_stage1_421_bin.h"
#include "ps2gxemu_stage1_430_bin.h"
#include "ps2gxemu_stage1_440_bin.h"
#include "ps2gxemu_stage1_453_bin.h"

#include "ps2gxemu_stage2_421_bin.h"
#include "ps2gxemu_stage2_430_bin.h"
#include "ps2gxemu_stage2_440_bin.h"
#include "ps2gxemu_stage2_453_bin.h"

#include "ps2hwemu_stage1_421_bin.h"
#include "ps2hwemu_stage1_440_bin.h"
#include "ps2hwemu_stage1_453_bin.h"

#include "ps2hwemu_stage2_421_bin.h"
#include "ps2hwemu_stage2_430_bin.h"
#include "ps2hwemu_stage2_440_bin.h"
#include "ps2hwemu_stage2_453_bin.h"

#include "ps2netemu_stage2_421_bin.h"
#include "ps2netemu_stage2_430_bin.h"
#include "ps2netemu_stage2_440_bin.h"
#include "ps2netemu_stage2_446_bin.h"
#include "ps2netemu_stage2_450_bin.h"
#include "ps2netemu_stage2_453_bin.h"
#include "ps2netemu_stage2_455_bin.h"
#include "ps2netemu_stage2_460_bin.h"
#include "ps2netemu_stage2_478_bin.h"

#define NO_UID		-1
#define SYSTEM_UID	0
#define NO_GID		-1

#define OK 			1
#define NOK 		0
#define YES			1
#define NO 			0
#define TRUE 		1
#define FALSE 		0
#define SUCCESS 	1
#define FAILED	 	0
#define ON			1
#define OFF			0
#define FOUND		1
#define NOT_FOUND	0
#define UP			1
#define LOW			0
#define VERTICAL	0
#define HORIZONTAL	1
#define STATIC		0
#define DYNAMIC		1
#define SCROLL		0
#define PAGE		1
#define FULL		0
#define SPLIT		1

#define CONTINUE	0
#define BREAK		1

#define REACTPSN	0
#define SNAKE		0 // cobra else mamba
#define IRIS		1
#define MM			2  

#define _EXIST		1
#define _NOT_EXIST	0
#define _FILE		1
#define _DIRECTORY	2
#define _PNG		3
#define _JPG		4
#define _SELF		5
#define _ELF		6
#define _EBOOT_BIN	7
#define _EBOOT_ELF	8
#define _SPRX		9
#define _PRX		10
#define _XML		11
#define _PKG		12
#define _IRD		13
#define _P3T		14
#define _THM		15
#define	_RIF		16
#define _RAP		17
#define _EDAT		18
#define _PFD		19
#define _MP4		20
#define _SFO		21
#define _TXT		22
#define _TRP		23
#define _RCO		24
#define _CSO		25
#define _ISO		26
#define _ISO_PS3	27
#define _ISO_PS2	28
#define _ISO_PS1	29
#define _ISO_PSP	30
#define _JB_PS3		31
#define _JB_PS2		32
#define _JB_PS1		33
#define _JB_PSP		34
#define _GTF		35
#define _DDS		36
#define _RAF		37
#define _JSX		38
#define _QRC		39
#define _VAG		40
#define _JS			41
#define _LOG		42
#define _INI		43
#define _NFO		44
#define _MD5		45
#define _SHA1		46
#define _XREG		47
#define _ZIP		48
#define _66600		49
#define _TTF		50

#define NONE		0
#define BDMIRROR	1
#define BDEMU		2

#define BLACK		0x000000FF
#define WHITE		0xFFFFFFFF
#define ORANGE 		0xFFA000FF
#define BLUE		0x0070FFFF
#define GREEN		0x00A000FF
#define RED			0xFF0000FF
#define PURPLE		0x7D00FFFF
#define YELLOW		0xFFFF00FF
#define GREY		0x808080FF
#define PINK		0xFF00FFFF

#define COLOR_ISO	RED
#define COLOR_PS3	0x00A0FFFF
#define COLOR_PS2	0x0303C0FF
#define COLOR_PS1	BLACK
#define COLOR_PSP	0x909090FF

#define MD5_HASH	0
#define SHA1_HASH	1

#define LIST		0
#define GRID		1
#define XMB			2
#define	FLOW		3

#define MGZ 0
#define P3T 1
#define THM 2

#define ENDIAN_SWAP_16(x)		(((x) & 0xFF) << 8 | ((x) & 0xFF00) >> 8)
#define ENDIAN_SWAP_32(x)		(((x) & 0xFF) << 24 | ((x) & 0xFF00) << 8 | ((x) & 0xFF0000) >> 8 | ((x) & 0xFF000000) >> 24)
#define ENDIAN_SWAP(x)			(sizeof(x) == 2 ? ENDIAN_SWAP_16(x) : ENDIAN_SWAP_32(x))

#define X_MAX		848.0f
#define Y_MAX		512.0f

#define FS_S_IFMT 0170000
#define FS_S_IFDIR 0040000

#define USB_MASS_STORAGE_1(n)	(0x10300000000000AULL+(n)) // For 0-5 
#define USB_MASS_STORAGE_2(n)	(0x10300000000001FULL+((n)-6)) // For 6-127
#define USB_MASS_STORAGE(n)	(((n) < 6) ? USB_MASS_STORAGE_1(n) : USB_MASS_STORAGE_2(n))

#define MAX_SECTIONS	((0x10000-sizeof(rawseciso_args))/8)

#define FREE(x) if(x!=NULL) {free(x);x=NULL;}
#define FCLOSE(x) if(x) {fclose(x);x=NULL;}

#define SCENE_FILEMANAGER			0
#define SCENE_PS3_MENU				1
#define SCENE_PS2_MENU				2
#define SCENE_PS1_MENU				3
#define SCENE_PSP_MENU				4
#define SCENE_PS2_CONFIG_EDITOR		5
#define SCENE_SETTINGS				6
#define SCENE_MAIN					7

#define PI 3.14159265f
#define DEG(x) PI/180*x

#define INPUT_SIZE		16
#define INPUT_X			10
#define INPUT_Y			491-INPUT_SIZE/2


u8 scene=SCENE_MAIN;

typedef struct
{
	uint64_t device;
	uint32_t emu_mode;
	uint32_t num_sections;
	uint32_t num_tracks;
} __attribute__((packed)) rawseciso_args;

SYS_PROCESS_PARAM(1200, 0x100000);

//************ FIRMWARE	***************

int firmware = 0;
static u64 SYSCALL_TABLE;
static u64 HV_START_OFFSET;
static u64 OFFSET_FIX;
static u64 OFFSET_2_FIX;
static u64 OFFSET_FIX_3C;
static u64 OFFSET_FIX_2B17;
static u64 OFFSET_FIX_LIC;
static u64 OPEN_HOOK;
static u64 BASE_ADDR;
static u64 UMOUNT_SYSCALL_OFFSET;
static u64 LV2MOUNTADDR;
static u64 LV2MOUNTADDR_ESIZE;
static u64 LV2MOUNTADDR_CSIZE;
static u64 NEW_POKE_SYSCALL_ADDR;
static u64 PAYLOAD_SKY;
static size_t PAYLOAD_SKY_SIZE;
static u64 UMOUNT;
static size_t UMOUNT_SIZE;
static u64 MAMBA;
static size_t MAMBA_SIZE;
static u64 *MAMBA_LOADER;
static size_t MAMBA_LOADER_SIZE;
static u64 OFFSET_1_IDPS;
static u64 OFFSET_2_IDPS;

//*********** IRIS ****************

#define PAYLOAD_OFFSET						0x3d90
#define PERMS_OFFSET						0x8000000000003560ULL
#define PAYLOAD_UMOUNT_OFFSET				(0x3d90+0x400)
#define PATCH_JUMP(add_orig, add_dest)		lv2poke32(add_orig, 0x48000000 | ((add_dest-(add_orig-0x8000000000000000ULL)) & 0x3fffffc))
#define PATCH_CALL(add_orig, add_dest)		lv2poke32(add_orig, 0x48000000 | ((add_dest-(add_orig-0x8000000000000000ULL)) & 0x3fffffc) | 1)

static char temp_buffer[8192];
//static u64 restore_syscall8[2] = {0,0};
static char *table_compare[19];
static char *table_replace[19];
static int ntable = 0;

//*********** MultiMAN ***************
typedef struct
{
	char src[384];
	char dst[384];
} redir_files_struct;
static redir_files_struct file_to_map[8];
static u8 max_mapped=0;

//****** Thread Loading *************

static u8 loading = 1;
static char loading_log[20][255];
static char head_title[128];
int64_t prog_bar1_value=-1;
int64_t prog_bar2_value=-1;
u8 cancel = NO;
uint8_t ERR = FALSE;
uint8_t WAR = FALSE;
static u32 LoadIconRot=0;

//******* Notification **********

static u32 time_not = 0;
static char not_msg[255];

//****** Thread Check **************

static char list_device[20][20]={{0}};
static int8_t device_number=-1;
static int8_t device_plug=0;
static u8 checking=YES;

//****** Thread LoadPIC **************

static int64_t Load_GamePIC_progbar = -1;
static u8 Load_GamePIC=NO;
static u8 load_PIC1=NO;

//********** Backup LIST ******************


#define MAX_GAME 		512
/*
static char list_game_path[MAX_GAME][128] = {{0}};
static char list_game_title[MAX_GAME][128] = {{0}};
static char list_game_id[MAX_GAME][128] = {{0}};
static u8 list_game_platform[MAX_GAME] = {0};
static int game_number = -1;
*/

static s64 game_number=-1;
static char **list_game_path;
static char **list_game_title;
static char **list_game_id;
static u8 *list_game_platform;

//********** Backup FAV ******************

#define MAX_FAV 		32

static char list_FAV_game_path[MAX_FAV][128] = {{0}};
static char list_FAV_game_title[MAX_FAV][128]= {{0}};
static int8_t FAV_game_number = -1;

//*************** Current Informations *************

static char GamPath[128];
static u8 Game_stuff = YES;
static u8 PEEKnPOKE;
static u8 cobra = NO;
static u8 iso = NO;
static u8 mamba = NO;
static u8 usb = NO;
static int position=0;
char ManaGunZ_id[10];

//********** Scan DIR ****************

#define MAX_SCANDIR 	10
static char scan_dir[MAX_SCANDIR][128];
static int8_t scan_dir_number=0;

//********** THEME ******************

#define MAX_THEME		16
static char Themes_Names_list[4][MAX_THEME][128];
static char Themes_Paths_list[4][MAX_THEME][255];
static char Themes[4][128] = {"Default", "Default", "Default", "Default"};
static u8 Themes_position[4] = {0}; 
static int8_t Themes_number[4] = {-1,-1,-1,-1}; // ou {[0 ... 3] = -1}

//********* FONT *******************

static char Font[128]="/dev_flash/data/font/SCE-PS3-SR-R-LATIN2.TTF";
static char **FontName=NULL;
static char **FontPath=NULL;
static s8 FontNumber=0;

//**************** ManaGunZ UI **************

#define POINT(X,Y,Z) \
		tiny3d_VertexPos(X, Y, Z);\
		tiny3d_Normal(X, Y, Z);

static float ITEM_moveX[MAX_GAME] = {0.0};
static float ITEM_moveY[MAX_GAME] = {0.0};
static float ITEM_moveZ[MAX_GAME] = {0.0};
static float ITEM_angleX[MAX_GAME] = {0.0};
static float ITEM_angleY[MAX_GAME] = {0.0};
static float ITEM_angleZ[MAX_GAME] = {0.0};

static u8 MOVE_init=NO;

MATRIX matrix;

//*************** GAME SETTINGS *******************

static u8 direct_boot = NO;
static u8 clean_syscall = NO;
static u8 change_IDPS = NO;
static u8 IDPS[0x10]={0};
static u8 ext_game_data= NO;
static u8 payload = MM;
static u8 prim_USB = NO;
static u8 emu = NONE;
static u8 libfs_from = MM;
static u8 mount_app_home = NO;
static u8 use_ex_plug = NO;

//*************** GLOBAL SETTINGS *******************
#ifdef FILEMANAGER
static char *UI[4] = {"0", "0", "Win", "0"};
#else
static char *UI[4] = {"List", "Grid", "XMB", "Flow"};
#endif

static u8 UI_position = XMB;
static u8 XMB_priority = NO;
static u8 Show_Help = YES;
static u8 Use_SideMenu = NO;
static u8 Show_COVER = NO;
static u8 Show_PIC1 = NO;
static u8 Show_GameCase = NO;
static int8_t videoscale_x = 0;
static int8_t videoscale_y = 0;
static u32 COLOR_1 = WHITE;
static u32 COLOR_2 = GREEN;
static u32 COLOR_3 = ORANGE;
static u32 COLOR_4 = RED;
static u8 Display_PIC1 = NO;
static u8 Show_Waves = YES;
static u32 WAVES_COLOR = WHITE-0xFF+0x20;
static float filter_x = 700;
static float filter_y = 300;

//*************** LIST SETTINGS *******************

#define LIST_SizeFont		20
static u8 LIST_Show_ICON0 = NO;
static int first_line=0;
static int nb_line=0;
static int last_line;

//*************** GRID SETTINGS *******************

static s16 GRID_FIRST_ICON = 0, GRID_LAST_ICON=-1;
static u8 GRID_NB_LINES = 5;
static u8 GRID_NB_COLUMNS = 5;
static u8 GRID_TYPE = SCROLL;
static u8 GRID_DIRECTION = VERTICAL;
static u8 GRID_ANIMATED = YES;
static u8 GRID_KEEP_PROP = YES;
#define GRID_e 10
#define GRID_X 20
#define GRID_Y 25
#define GRID_W X_MAX-GRID_X*2
#define GRID_H Y_MAX-GRID_Y*2
#define GRID_W_ICON0	(GRID_W - (GRID_NB_COLUMNS-1) * GRID_e) / GRID_NB_COLUMNS 
#define GRID_H_ICON0    ((GRID_H - (GRID_NB_LINES-1) * GRID_e) / GRID_NB_LINES)*(1-GRID_KEEP_PROP) + GRID_KEEP_PROP*GRID_W_ICON0/1.86
#define GRID_NB_ICON0 	GRID_NB_LINES*GRID_NB_COLUMNS

//*************** XMB SETTINGS *******************

#define XMB_W 72.0f
#define XMB_H 40.0f

#define XMB_COLUMN_NUMBER 6

#define XMB_COLUMN_SETTINGS		0
#define XMB_COLUMN_FAVORITES	1
#define XMB_COLUMN_PS3			2
#define XMB_COLUMN_PS2			3
#define XMB_COLUMN_PS1			4
#define XMB_COLUMN_PSP			5

static u8 XMB_H_position = 2;
static s16 XMB_nb_line = -1;
static u16 XMB_value_line[MAX_GAME] = {0};
static u16 XMB_V_position[XMB_COLUMN_NUMBER] = {0};

static char *XMB_COLUMN_NAME[XMB_COLUMN_NUMBER]={"SETTINGS", "FAVORITES", "PS3", "PS2", "PS1", "PSP"};
static float XMB_columnX[XMB_COLUMN_NUMBER]={0.0};
static float XMB_columnY[XMB_COLUMN_NUMBER]={0.0};
static float XMB_columnZ[XMB_COLUMN_NUMBER]={0.0};

//*************** FLOW SETTINGS *******************

#define FLOW_W  	80.0f
#define FLOW_H		44.0f

static u8 FLOW_3D = YES;
static u8 FLOW_Zoom = NO;
static u8 FLOW_ShowBack = NO;
static u8 FLOW_inverse_button=YES;

//*************** FILTER SETTINGS *******************

static u8 Show_PS3 = YES;
static u8 Show_PS2 = YES;
static u8 Show_PS1 = YES;
static u8 Show_PSP = YES;
static u8 Only_FAV = NO;

//*************** AutoMount *******************

static u8 AutoM = NO;
static u8 gui_called = NO;

//************** PICTURE ******************************

typedef struct
{
	void *bmp_out;

	u32 pitch;
	u32 width;
	u32 height;
} imgData; // pngData = jpgData = imgData

imgData ICON0[MAX_GAME];
static u32 ICON0_offset[MAX_GAME];

imgData COVER[MAX_GAME];
static u32 COVER_offset[MAX_GAME];

imgData COVER3D[MAX_GAME];
static u32 COVER3D_offset[MAX_GAME];

imgData TMP_PIC;
static u32 TMP_PIC_offset;
char TMP_PIC_path[255];

// *************** PICTURE ***************************

#define ALL				0
#define UP				1
#define LEFT			2
#define DOWN			3
#define RIGHT			4
#define SELECT			5
#define START			6
#define SQUARE			7
#define CROSS			8
#define CIRCLE			9
#define TRIANGLE		10
#define NOT				11
#define L1				12
#define L2				13
#define L3				14
#define L				15
#define R1				16
#define R2				17
#define R3				18
#define R				19
#define DEFAULT			20
#define DEFAULT_ISO		21
#define DEFAULT_JB		22
#define PS1_DISC		23
#define PS2_DISC		24
#define PS3_DISC		25
#define PSP_DISC		26
#define TAG				27
#define PS1_CASE		28
#define PS2_CASE		29
#define PS3_CASE		30
#define PSP_CASE		31
#define FOLDER			32
#define FILES			33
#define BR_LOGO			34
#define PS_LOGO			35
#define NOTIF			36
#define BOXHEAD			37
#define	BOXBODY			38
#define SIDEBAR			39
#define BGS				40

#define PICTURE_NUMBER	41

char *PICTURE_NAME[PICTURE_NUMBER] = {	"ALL" , 
										"UP" , "LEFT" , "DOWN" , "RIGHT" , 
										"SELECT" , "START" , 
										"SQUARE" , "CROSS" , "CIRCLE" , "TRIANGLE", 
										"NOT", 
										"L1", "L2", "L3", "L", 
										"R1", "R2", "R3", "R",
										"DEFAULT", "DEFAULT_ISO", "DEFAULT_JB",
										"PS1_DISC", "PS2_DISC", "PS3_DISC", "PSP_DISC",
										"TAG",
										"PS1_CASE", "PS2_CASE", "PS3_CASE", "PSP_CASE",
										"FOLDER", "FILES",
										"BR_LOGO", "PS_LOGO",
										"NOTIF", "BOXHEAD", "BOXBODY", "SIDEBAR", "BGS"};

imgData PICTURE[PICTURE_NUMBER];
static u32 PICTURE_offset[PICTURE_NUMBER];

#define TEXTURE_FONT_SIZE			2  * 1024*1024
#define TEXTURE_THEME_SIZE			16 * 1024*1024
#define TEXTURE_GAMEPIC_SIZE		32 * 1024*1024

#define TEXTURE_POINTER_FONT		0
#define TEXTURE_POINTER_THEME		TEXTURE_FONT_SIZE
#define TEXTURE_POINTER_GAMEPIC		TEXTURE_FONT_SIZE+TEXTURE_THEME_SIZE

static u32 *texture_pointer;
static u32 *texture_mem;
static u32 *texture_temp;

#define MAX_FRAME		64
static u32 BG_offset[MAX_FRAME];
imgData BG[MAX_FRAME];


// ***************** PICTURE : XMB ***************************

imgData XMB_Col[6];
static u32 XMB_Col_offset[6];

imgData XMB_MMTHM_XMB;
static u32 XMB_MMTHM_XMB_offset;

imgData XMB_MMTHM_XMB2;
static u32 XMB_MMTHM_XMB2_offset;

// ****************** FILE MANAGER ***************

#define ASC 0
#define DSC 1

#define TOP_H			40
#define COL_H			20
#define COL_W_MIN 		90
#define BORDER			5
#define SCROLL_W		10
#define SCROLL_H_MIN	10
#define WINDOW_MIN		COL_W_MIN*2 + BORDER*2
#define CONTENT_FSIZE	15
#define ICON			CONTENT_FSIZE
#define WINDOW_MAX				5
#define WINDOW_MAX_ITEMS		2048
#define WINDOW_MAX_PATH_LENGTH 512
#define WINDOW_MAX_NAME_LENGTH 128

static float *window_x=NULL;
static float *window_y=NULL;
static float *window_z=NULL;
static float *window_h=NULL;
static float *window_w=NULL;
static char **window_path=NULL;
static char **window_lastpath=NULL;
static char ***window_content_Name=NULL;
static u64 **window_content_Size=NULL;
static u8 **window_content_Type=NULL;
static u8 **window_content_Selected=NULL;
static u8 *window_sort=NULL;
static float *window_w_col_size=NULL;
static int *window_content_N=NULL;
static u8 *window_open=NULL;

static s8 window_activ;

static s8 *window_item_N=NULL; // nb of item displayed

static u32 *window_scroll_N=NULL; //	nb of increment
static u32 *window_scroll_P=NULL; // 	increment position
static float *window_scroll_size=NULL;
static float *window_scroll_y=NULL;

#define OPTION_MAX 16

static char **option_sel=NULL;
static char **option_item=NULL;
static char **option_copy=NULL;
static int option_item_N;
static int option_sel_N;
static int option_copy_N=-1;
static u8 option_cut = NO;
static u8 option_activ = NO;
static float option_x;
static float option_y;
static float option_h;
static float option_w;

static float curs_x = 848/2;
static float curs_y = 512/2;
static float curs_move_x;
static float curs_move_y;
static u8 curs_push=NO;
static float curs_move_scroll=0;

static u8 window_resize_H = NO;
static u8 window_resize_V = NO;
static u8 window_resize_D1 = NO;
static u8 window_resize_D2 = NO;
static u8 window_move = NO;

// ****************** FILE MANAGER : Properties ***************

static u8 prop_activ;

char **PROP_ITEM=NULL;
char **PROP_ITEM_VALUE=NULL;
s8 PROP_ITEM_NUMBER;

#define PROP_FONT		20.0f
#define PROP_W			800.0f
#define PROP_H			(PROP_ITEM_NUMBER+1)*PROP_FONT
#define PROP_X			X_MAX/2.0f-PROP_W/2.0f
#define PROP_Y			Y_MAX/2.0f-PROP_H/2.0f
#define PROP_COL_W		100.0f
#define PROP_MAX_ITEMS	10

// ****************** FILE MANAGER : SFO Viewer ***************

#define SFO_MAGIC				0x00505346
#define SFO_DATA_TYPE_UTF8S		0x004
#define SFO_DATA_TYPE_UTF8		0x204
#define SFO_DATA_TYPE_INT32		0x404

#define ES16(x)		(((x) & 0xFF) << 8 | ((x) & 0xFF00) >> 8)
#define ES32(x)		(((x) & 0xFF) << 24 | ((x) & 0xFF00) << 8 | ((x) & 0xFF0000) >> 8 | ((x) & 0xFF000000) >> 24)
#define ES(x)		(sizeof(x) == 2 ? ES16(x) : ES32(x))

char SFO_KEY[64][64];
char SFO_DATA[64][255];
u8 SFO_viewer_activ;
u8 SFO_NB;

#define SFO_FONT	20		
#define SFO_W		800
#define SFO_COL2_W	SFO_W-SFO_COL1_W
#define SFO_X		848/2-SFO_W/2

// ****************** FILE MANAGER : TXT Viewer ***************

#define TXT_W 708
#define TXT_H 372
#define TXT_X 70
#define TXT_Y 70

u64 txt_linpos;
u8 txt_scroll;
static u8 txt_viewer_activ = NO;
char *txt_viewer_content=NULL;
int txt_viewer_content_size;

//************************ COPY ************************

static char copy_log[10][128];
static char copy_file[128];
static char copy_src[128];
static char copy_dst[128];

static u64 copy_current_size;
static u64 total_size;
static u64 file_copy_prog_bar;
static u8 gathering;

static int nb_file = 0;
static int nb_directory = 0;

static u8 copy_flag=NO;
static u8 copy_cancel=NO;
static u8 gathering_cancel=NO;

//************************** PAD ************************

static int slow_it;
static u64 hold_it;
static int R2speed=6;
static u16 hold_CIRCLE=0;
static int x_L = 0;
static int y_L = 0;

// ************** FILE MANAGER : Picture Viewer ***************

static u8 picture_viewer_activ = NO;

//***************** MENU *************************************

#define MENU_MAX_ITEMS				64
#define MENU_MAX_ITEMS_VALUE		128

#define ITEM_TEXTBOX	0
#define ITEM_CHECKBOX	1
#define ITEM_COLORBOX	2
#define ITEM_COMMAND	3
#define ITEM_TOGGLE		4

static u8 MENU=NO;

static char **ITEMS=NULL;
static s8 ITEMS_NUMBER;
static char ***ITEMS_VALUE=NULL;
static s8 *ITEMS_VALUE_NUMBER=NULL;

static u8 ITEMS_POSITION;
static u8 *ITEMS_VALUE_POSITION=NULL;
static u8 *ITEMS_VALUE_SHOW=NULL;
static u8 *ITEMS_TYPE=NULL;

static u8 IN_ITEMS_VALUE=NO;

static float MENU_ITEMS_X;
static float MENU_ITEMS_VALUE_X;
static int MENU_SCROLL;
static int MENU_SCROLL_START;

static int MENU_COLUMN_ITEMS_NUMBER;
static float MENU_COLUMN_ITEMS_W;
static s8 MENU_TABLE_START;
static s8 MENU_TABLE_END;

static char **TITLES=NULL;

static u8 MENU_SIDE;

static float x_COLOR;
static float y_COLOR;

// ***************** PS2 GAME MENU *************************************

#define LIMG_SIZE 0x4000
static u8 has_LIMG=NO;
static char *PS2ELF_mem = NULL;
static int PS2ELF_mem_size = 0;
static char PS2CRC_STR[8];
static char PS2ORICRC_STR[8];
static char PS2_ID[12];
static char pnach[128];
static char WS[128];

static u8 PS2PATCH_480P = NO;
static u8 PS2PATCH_YFIX = NO;
static u8 PS2PATCH_FMVSKIP = NO;

u32 PS2PATCH_480P_offset;
u32 PS2PATCH_YFIX_offset;
u32 PS2PATCH_FMVSKIP_offset;

static u8 PS2PATCH_480P_FLAG_DISABLE[] = { 
									0x00, 0x2C, 0x05, 0x00, 0x20, 0x00, 0xB2, 0xFF, 
									0x00, 0x34, 0x06, 0x00, 0x10, 0x00, 0xB1, 0xFF, 
									0x00, 0x3C, 0x07, 0x00
								  };

static u8 PS2PATCH_480P_FLAG_ENABLE[] = { 
								   0x00, 0x00, 0x05, 0x3C, 0x20, 0x00, 0xB2, 0xFF,
								   0x50, 0x00, 0x06, 0x3C, 0x10, 0x00, 0xB1, 0xFF,
								   0x01, 0x00, 0x07, 0x3C
								 };

static u8 PS2PATCH_YFIX_FLAG_DISABLE[] = { 
									0x70, 0xFF, 0xBD, 0x27, 0x00, 0x2C, 0x05, 0x00,
									0x70, 0x00, 0xB6, 0xFF, 0x00, 0x34, 0x06, 0x00,
									0x60, 0x00, 0xB5, 0xFF, 0x00, 0x3C, 0x07, 0x00,
									0x50, 0x00, 0xB4, 0xFF, 0x00, 0x44, 0x08, 0x00,
									0x40, 0x00, 0xB3, 0xFF, 0x00, 0x4C, 0x09, 0x00
								  };

static u8 PS2PATCH_YFIX_FLAG_ENABLE[] = { 
								   0x70, 0xFF, 0xBD, 0x27, 0x00, 0x2C, 0x05, 0x00,
								   0x70, 0x00, 0xB6, 0xFF, 0x00, 0x34, 0x06, 0x00, 
								   0x60, 0x00, 0xB5, 0xFF, 0x00, 0x3C, 0x07, 0x00, 
								   0x50, 0x00, 0xB4, 0xFF, 0x00, 0x44, 0x08, 0x00, 
								   0x40, 0x00, 0xB3, 0xFF, 0x10, 0x00, 0x09, 0x3C
								 };

static u8 PS2PATCH_FMVSKIP_FLAG_DISABLE[] = {
									   0x40, 0x00, 0x83, 0x8C, 0x08, 0x00, 0xE0, 0x03,
									   0x00, 0x00, 0x62, 0x8C, 0x00, 0x00, 0x00, 0x00
									 };

static u8 PS2PATCH_FMVSKIP_FLAG_ENABLE[] = {
									  0x40, 0x00, 0x83, 0x8C, 0x08, 0x00, 0xE0, 0x03,
									  0x01, 0x00, 0x02, 0x24, 0x00, 0x00, 0x00, 0x00
									};

//***********************************************************
// Language
//***********************************************************
// http://www.psdevwiki.com/ps3/XRegistry.sys
// 0x0=German
// 0x1=English (US)
// 0x2=Spanish
// 0x3=French
// 0x4=Italian
// 0x5=Dutch
// 0x6=Portuguese (Por)
// 0x7=Russian
// 0x8=Japanese
// 0x9=Korean
// 0xA=Chinese (traditional)
// 0xB=Chinese (simplified)
// 0xC=Finnish
// 0xD=Swedish
// 0xE=Danish
// 0xF=Norwegian
// 0x10=Polish
// 0x11=Portuguese (Bra)
// 0x12=English (UK)
// ...
// CUSTOM
// 0x20=Hungarian
// 0x21=Turkish
//***********************************************************

#define MAX_LANG 32
#define LANG_DEFAULT		0xFF
#define LANG_UNDEFINED		0xEE
#define LANG_NONE			0xDD

uint8_t lang=0;
uint8_t lang_N;
uint8_t lang_code = LANG_UNDEFINED;
uint8_t lang_code_loaded = LANG_NONE;

static char *STR_LANGUAGE[MAX_LANG]; // "English"
static char *STR_LANGCODE[MAX_LANG];
static char *lang_path[MAX_LANG];

static char *STR_LANG=NULL;
#define STR_LANG_DEFAULT					"Language"
static char *STR_LANG_DESC=NULL;
#define STR_LANG_DESC_DEFAULT				"Choose your language."
static char *STR_GATHERING=NULL;
#define STR_GATHERING_DEFAULT				"Gathering data..."
static char *STR_COPYING=NULL;
#define STR_COPYING_DEFAULT					"Copying..."
static char *STR_FROM=NULL;
#define STR_FROM_DEFAULT					"from"
static char *STR_TO=NULL;
#define STR_TO_DEFAULT						"to"
static char *STR_FILES=NULL;
#define STR_FILES_DEFAULT					"Files"
static char *STR_DIRS=NULL;
#define STR_DIRS_DEFAULT					"Directories"
static char *STR_UNKNOWN=NULL;
#define STR_UNKNOWN_DEFAULT					"Unknown"
static char *STR_FILE=NULL;
#define STR_FILE_DEFAULT					"File"
static char *STR_CANCEL=NULL;
#define STR_CANCEL_DEFAULT					"Cancel"
static char *STR_TURNOFF_YES=NULL;
#define STR_TURNOFF_YES_DEFAULT				"Turn OFF = YES"
static char *STR_TURNOFF_NO=NULL;
#define STR_TURNOFF_NO_DEFAULT				"Turn OFF = NO"
static char *STR_CANCELLED=NULL;
#define STR_CANCELLED_DEFAULT				"Cancelled"
static char *STR_UNIT=NULL;
#define STR_UNIT_DEFAULT					"Bytes"
static char *STR_TOTALSIZE=NULL;
#define STR_TOTALSIZE_DEFAULT				"Total size"
static char *STR_HIDELOGS=NULL;
#define STR_HIDELOGS_DEFAULT				"Hide logs"
static char *STR_SHOWLOGS=NULL;
#define STR_SHOWLOGS_DEFAULT				"Show logs"
static char *STR_BOOST=NULL;
#define STR_BOOST_DEFAULT					"Boost!"
static char *STR_GAMEMENU=NULL;
#define STR_GAMEMENU_DEFAULT				"Game Menu"
static char *STR_SETTINGS=NULL;
#define STR_SETTINGS_DEFAULT				"Settings"
static char *STR_MOUNTGAME=NULL;
#define STR_MOUNTGAME_DEFAULT				"Mount Game"
static char *STR_FILTER=NULL;
#define	STR_FILTER_DEFAULT					"Filter"
static char *STR_FAVORITE=NULL;
#define STR_FAVORITE_DEFAULT				"Favorite"
static char *STR_FILEMANAGER=NULL;
#define STR_FILEMANAGER_DEFAULT				"File Manager"
static char *STR_HOLD=NULL;
#define STR_HOLD_DEFAULT					"Hold"
static char *STR_BACKTOXMB=NULL;
#define STR_BACKTOXMB_DEFAULT				"Back to XMB"
static char *STR_GAME_PROP=NULL;
#define STR_GAME_PROP_DEFAULT				"Game Properties"
static char *STR_GAME_TITLE=NULL;
#define STR_GAME_TITLE_DEFAULT				"Title"
static char *STR_GAME_PATH=NULL;
#define STR_GAME_PATH_DEFAULT				"Path"
static char *STR_GAME_FORMAT=NULL;
#define STR_GAME_FORMAT_DEFAULT				"Format"
static char *STR_GAME_SIZE=NULL;
#define STR_GAME_SIZE_DEFAULT				"Size"
static char *STR_GAME_PLATFORM=NULL;
#define STR_GAME_PLATFORM_DEFAULT			"Platform"
static char *STR_SYSVERS=NULL;
#define STR_SYSVERS_DEFAULT					"Firmware"
static char *STR_GAMEID=NULL;
#define STR_GAMEID_DEFAULT					"Game ID"
static char *STR_ELFCRC=NULL;
#define STR_ELFCRC_DEFAULT					"ELF CRC"
static char *STR_ELFCRCO=NULL;
#define STR_ELFCRCO_DEFAULT					"ELF CRC (Original)"
static char *STR_BACK=NULL;
#define STR_BACK_DEFAULT					"Back"
static char *STR_ENTER=NULL;
#define STR_ENTER_DEFAULT					"Enter"
static char *STR_UPDATE_FOUND=NULL;
#define STR_UPDATE_FOUND_DEFAULT			"Update found"
static char *STR_UPDATE=NULL;
#define STR_UPDATE_DEFAULT					"Update"
static char *STR_SIZE=NULL;
#define STR_SIZE_DEFAULT					"Size"
static char *STR_SYSTEM=NULL;
#define STR_SYSTEM_DEFAULT					"System"
static char *STR_DL=NULL;
#define STR_DL_DEFAULT						"Download"
static char *STR_DL_ALL=NULL;
#define STR_DL_ALL_DEFAULT					"Download ALL"
static char *STR_UNPLUG=NULL;
#define STR_UNPLUG_DEFAULT					"Unplug the following device(s)"
static char *STR_PATH=NULL;
#define STR_PATH_DEFAULT					"Path"
static char *STR_TYPE=NULL;
#define STR_TYPE_DEFAULT					"Type"
static char *STR_FOLDER=NULL;
#define STR_FOLDER_DEFAULT					"Folder"
static char *STR_DIR=NULL;
#define STR_DIR_DEFAULT						"Directory"
static char *STR_MULT=NULL;
#define STR_MULT_DEFAULT					"Multiple"
static char *STR_THM_SETTINGS=NULL;
#define STR_THM_SETTINGS_DEFAULT			"Theme settings"
static char *STR_THM=NULL;
#define STR_THM_DEFAULT						"Theme"
static char *STR_THM_DESC=NULL;
#define STR_THM_DESC_DEFAULT				"Load the theme you want. You can install them from /dev_usbXXX/Themes."
static char *STR_CREATE=NULL;
#define STR_CREATE_DEFAULT					"Create"
static char *STR_ZOOM_OUT=NULL;
#define STR_ZOOM_OUT_DEFAULT				"Zoom OUT"
static char *STR_ZOOM_IN=NULL;
#define STR_ZOOM_IN_DEFAULT					"Zoom IN"
static char *STR_MOVE_FRAME=NULL;
#define STR_MOVE_FRAME_DEFAULT				"Move Frame"
static char *STR_CHECK=NULL;
#define STR_CHECK_DEFAULT					"Check"
static char *STR_UNCHECK=NULL;
#define STR_UNCHECK_DEFAULT					"Uncheck"
static char *STR_GAME_OPTION=NULL;
#define STR_GAME_OPTION_DEFAULT				"Game Options"
static char *STR_ADD_FAV=NULL;
#define STR_ADD_FAV_DEFAULT					"Add to favorites"
static char *STR_REM_FAV=NULL;
#define STR_REM_FAV_DEFAULT					"Remove from favorites"
static char *STR_FAV_DESC=NULL;
#define STR_FAV_DESC_DEFAULT				"Manage a list your favorite games."
static char *STR_RENAME=NULL;
#define STR_RENAME_DEFAULT					"Rename"
static char *STR_RENAME_DESC=NULL;
#define STR_RENAME_DESC_DEFAULT				"Rename the title of your backup."
static char *STR_DELETE=NULL;
#define STR_DELETE_DEFAULT					"Delete"
static char *STR_DELETE_DESC=NULL;
#define STR_DELETE_DESC_DEFAULT				"Delete your backup."
static char *STR_COPY=NULL;
#define STR_COPY_DEFAULT					"Copy"
static char *STR_COPY_DESC=NULL;
#define STR_COPY_DESC_DEFAULT				"Copy your backup to another path."
static char *STR_CREATE_ICON0=NULL;
#define STR_CREATE_ICON0_DEFAULT			"Create ICON0"
static char *STR_CREATE_ICON0_DESC=NULL;
#define STR_CREATE_ICON0_DESC_DEFAULT		"Create an 'fake' ICON0 from the cover."
static char *STR_REST_PNACH=NULL;
#define STR_REST_PNACH_DEFAULT				"Restore PNACH"
static char *STR_REST_PNACH_DESC=NULL;
#define STR_REST_PNACH_DESC_DEFAULT			"Remove the patches applied by the pnach file to the backup."
static char *STR_APPLY_PNACH=NULL;
#define STR_APPLY_PNACH_DEFAULT				"Apply PNACH"
static char *STR_APPLY_PNACH_DESC=NULL;
#define STR_APPLY_PNACH_DESC_DEFAULT		"Apply the patches from pnach file to the backup."
static char *STR_DISABLE_WS=NULL;
#define STR_DISABLE_WS_DEFAULT				"Disable WideScreen"
static char *STR_ENABLE_WS=NULL;
#define STR_ENABLE_WS_DEFAULT				"Enable WideScreen"
static char *STR_WS_DESC=NULL;
#define STR_WS_DESC_DEFAULT					"Display the game in 16:9 instead of 4:3."
static char *STR_DISABLE_480P=NULL;
#define STR_DISABLE_480P_DEFAULT			"Disable 480P"
static char *STR_ENABLE_480P=NULL;
#define STR_ENABLE_480P_DEFAULT				"Enable 480P"
static char *STR_480P_DESC=NULL;
#define STR_480P_DESC_DEFAULT				"Progressive scan mode in 480P."
static char *STR_DISABLE_YFIX=NULL;
#define STR_DISABLE_YFIX_DEFAULT			"Disable YFIX"
static char *STR_ENABLE_YFIX=NULL;
#define STR_ENABLE_YFIX_DEFAULT				"Enable YFIX"
static char *STR_YFIX_DESC=NULL;
#define STR_YFIX_DESC_DEFAULT				"Fix the vertical position."
static char *STR_DISABLE_FMVSKIP=NULL;
#define STR_DISABLE_FMVSKIP_DEFAULT			"Disable FMV skip"
static char *STR_ENABLE_FMVSKIP=NULL;
#define STR_ENABLE_FMVSKIP_DEFAULT			"Enable FMV skip"
static char *STR_FMVSKIP_DESC=NULL;
#define STR_FMVSKIP_DESC_DEFAULT			"Allow you to skip the full motion videos."
static char *STR_DISABLE_NETEMU=NULL;
#define STR_DISABLE_NETEMU_DEFAULT			"Disable NetEMU"
static char *STR_ENABLE_NETEMU=NULL;
#define STR_ENABLE_NETEMU_DEFAULT			"Enable NetEMU"
static char *STR_NETEMU_DESC=NULL;
#define STR_NETEMU_DESC_DEFAULT				"Force the use of ps2 netemu."
static char *STR_SAVE_CONFIG=NULL;
#define STR_SAVE_CONFIG_DEFAULT				"Save CONFIG"
static char *STR_CONFIG=NULL;
#define STR_CONFIG_DEFAULT					"Configuration"
static char *STR_CONFIG_DESC=NULL;
#define STR_CONFIG_DESC_DEFAULT				"[Experimental] Create your own CONFIG file to 'fix' your ps2 backup."
static char *STR_NONE=NULL;
#define STR_NONE_DEFAULT					"None"
static char *STR_CHECK_MD5=NULL;
#define STR_CHECK_MD5_DEFAULT				"Check MD5"
static char *STR_PROPS=NULL;
#define STR_PROPS_DEFAULT					"Properties"
static char *STR_PROPS_DESC=NULL;
#define STR_PROPS_DESC_DEFAULT				"Show the properties of your backup."
static char *STR_ASK_DEL=NULL;
#define STR_ASK_DEL_DEFAULT					"Do you realy want to delete"
static char *STR_GAME_SETTINGS=NULL;
#define STR_GAME_SETTINGS_DEFAULT			"Game Settings"
static char *STR_DIRECT_BOOT=NULL;
#define STR_DIRECT_BOOT_DEFAULT				"Direct boot"
static char *STR_DIRECT_BOOT_DESC=NULL;
#define STR_DIRECT_BOOT_DESC_DEFAULT		"Launch the game directly without going back to XMB."
static char *STR_YES=NULL;
#define STR_YES_DEFAULT						"Yes"
static char *STR_NO=NULL;
#define STR_NO_DEFAULT						"No"
static char *STR_CLEAN_SYSCALL=NULL;
#define STR_CLEAN_SYSCALL_DEFAULT			"Clean syscall"
static char *STR_CLEAN_SYSCALL_DESC=NULL;
#define STR_CLEAN_SYSCALL_DESC_DEFAULT		"Disable peek & poke syscalls."
static char *STR_CHANGE_IDPS=NULL;
#define STR_CHANGE_IDPS_DEFAULT				"Change IDPS"
static char *STR_CHANGE_IDPS_DESC=NULL;
#define STR_CHANGE_IDPS_DESC_DEFAULT		"Change your IDPS in the lv2."
static char *STR_EXT_GAME_DATA=NULL;
#define STR_EXT_GAME_DATA_DEFAULT			"Ext. Game Data"
static char *STR_EXT_GAME_DATA_DESC=NULL;
#define STR_EXT_GAME_DATA_DESC_DEFAULT		"Install gamedata in your usb device instead of your system."
static char *STR_PAYLOAD=NULL;
#define STR_PAYLOAD_DEFAULT					"Payload"
static char *STR_PAYLOAD_DESC=NULL;
#define STR_PAYLOAD_DESC_DEFAULT			"Choose the payload to mount your backup."
static char *STR_PRIM_USB=NULL;
#define STR_PRIM_USB_DEFAULT				"Set Primary USB"
static char *STR_PRIM_USB_DESC=NULL;
#define STR_PRIM_USB_DESC_DEFAULT			"Set the USB device where the game is stored as the main USB device."
static char *STR_BDEMU=NULL;
#define STR_BDEMU_DEFAULT					"BD emulation"
static char *STR_BDEMU_DESC=NULL;
#define STR_BDEMU_DESC_DEFAULT				"Choose the type of emulation to mount you backup."
static char *STR_PATCH_LIBFS=NULL;
#define STR_PATCH_LIBFS_DEFAULT				"Patch libfs"
static char *STR_PATCH_LIBFS_DESC=NULL;
#define STR_PATCH_LIBFS_DESC_DEFAULT		"Choose which patched libfs you want to use."
static char *STR_MOUNT_APPHOME=NULL;
#define STR_MOUNT_APPHOME_DEFAULT			"Mount /app_home"
static char *STR_MOUNT_APPHOME_DESC=NULL;
#define STR_MOUNT_APPHOME_DESC_DEFAULT		"Redirect the path /app_home to /dev_bdvd."
static char *STR_PATCH_EXP=NULL;
#define STR_PATCH_EXP_DEFAULT				"Patch explore_plugin"
static char *STR_PATCH_EXP_DESC=NULL;
#define STR_PATCH_EXP_DESC_DEFAULT			"The path /app_home is remplaced by /dev_bdvd inside the plugin explore_plugin."
static char *STR_MAKE_SHTCUT_PKG=NULL;
#define STR_MAKE_SHTCUT_PKG_DEFAULT			"Make Shortcut PKG"
static char *STR_MAKE_SHTCUT_PKG_DESC=NULL;
#define STR_MAKE_SHTCUT_PKG_DESC_DEFAULT	"Create a package file stored to /dev_hdd0/packages. Once installed, it will be a 'shortcut' to mount your backup from the XMB."
static char *STR_PATCH_EBOOT=NULL;
#define STR_PATCH_EBOOT_DEFAULT				"Patch EBOOT"
static char *STR_PATCH_EBOOT_DESC=NULL;
#define STR_PATCH_EBOOT_DESC_DEFAULT		"Change the firmware version to 4.21 of the EBOOT file to prevent error 0x80010009."
static char *STR_RESIGN=NULL;
#define STR_RESIGN_DEFAULT					"Re-sign"
static char *STR_RESIGN_DESC=NULL;
#define STR_RESIGN_DESC_DEFAULT				"Re-sign every executables of your backup with the 4.21 keys."
static char *STR_RESTORE=NULL;
#define STR_RESTORE_DEFAULT					"Restore"
static char *STR_RESTORE_DESC=NULL;
#define STR_RESTORE_DESC_DEFAULT			"Restore the originals executables of your backup."
static char *STR_EXTRACT_ISO=NULL;
#define STR_EXTRACT_ISO_DEFAULT				"Extract ISO"
static char *STR_EXTRACT_ISO_DESC=NULL;
#define STR_EXTRACT_ISO_DESC_DEFAULT		"Extract files from your ISO to a folder."
static char *STR_CONVERT_ISO=NULL;
#define STR_CONVERT_ISO_DEFAULT				"Convert to ISO"
static char *STR_CONVERT_ISO_DESC=NULL;
#define STR_CONVERT_ISO_DESC_DEFAULT		"Convert your JB backup to an ISO."
static char *STR_FIX_PERMS=NULL;
#define STR_FIX_PERMS_DEFAULT				"Fix permissions"
static char *STR_FIX_PERMS_DESC=NULL;
#define STR_FIX_PERMS_DESC_DEFAULT			"Set permission value to 0777 of each folders and files of your backup."
static char *STR_CHECK_IRD=NULL;
#define STR_CHECK_IRD_DEFAULT				"Check files (IRD)"
static char *STR_CHECK_DESC=NULL;
#define STR_CHECK_DESC_DEFAULT				"Check if the files of your backups aren't modified."
static char *STR_DL_UPDATE=NULL;
#define STR_DL_UPDATE_DEFAULT				"Download Update"
static char *STR_DL_UPDATE_DESC=NULL;
#define STR_DL_UPDATE_DESC_DEFAULT			"Download your backup's updates to /dev_hdd0/packages."
static char *STR_OPEN_WINDOW=NULL;
#define STR_OPEN_WINDOW_DEFAULT				"Open New Window"
static char *STR_MOUNT_DEVBLIND=NULL;
#define STR_MOUNT_DEVBLIND_DEFAULT			"Mount /dev_blind"
static char *STR_DUMP_LV1=NULL;
#define STR_DUMP_LV1_DEFAULT				"Dump lv1"
static char *STR_DUMP_LV2=NULL;
#define STR_DUMP_LV2_DEFAULT				"Dump lv2"
static char *STR_DUMP_FLASH=NULL;
#define STR_DUMP_FLASH_DEFAULT				"Dump flash"
static char *STR_REFRESH=NULL;
#define STR_REFRESH_DEFAULT					"Refresh"
static char *STR_NEWFOLDER=NULL;
#define STR_NEWFOLDER_DEFAULT				"New Folder"
static char *STR_NEWFILE=NULL;
#define STR_NEWFILE_DEFAULT					"New File"
static char *STR_PASTE=NULL;
#define STR_PASTE_DEFAULT					"Paste"
static char *STR_CUT=NULL;
#define STR_CUT_DEFAULT						"Cut"
static char *STR_UNSELECT_ALL=NULL;
#define STR_UNSELECT_ALL_DEFAULT			"Unselect all"
static char *STR_SELECT_ALL=NULL;
#define STR_SELECT_ALL_DEFAULT				"Select all"
static char *STR_MAKE_PKG=NULL;
#define STR_MAKE_PKG_DEFAULT				"Make PKG"
static char *STR_GETMD5=NULL;
#define STR_GETMD5_DEFAULT					"Get MD5"
static char *STR_GETSHA1=NULL;
#define STR_GETSHA1_DEFAULT					"Get SHA1"
static char *STR_VIEW=NULL;
#define STR_VIEW_DEFAULT					"View"
static char *STR_VIEW_TXT=NULL;
#define STR_VIEW_TXT_DEFAULT				"View TXT"
static char *STR_VIEW_SFO=NULL;
#define STR_VIEW_SFO_DEFAULT				"View SFO"
static char *STR_READ_XREG=NULL;
#define STR_READ_XREG_DEFAULT				"Read xReg"
static char *STR_EXTRACT_ELF=NULL;
#define STR_EXTRACT_ELF_DEFAULT				"Extract ELF"
static char *STR_RESIGN_SELF=NULL;
#define STR_RESIGN_SELF_DEFAULT				"Resign SELF"
static char *STR_LAUNCH_SELF=NULL;
#define STR_LAUNCH_SELF_DEFAULT				"Launch SELF"
static char *STR_EXTRACT_EBOOT=NULL;
#define STR_EXTRACT_EBOOT_DEFAULT			"Extract EBOOT"
static char *STR_RESIGN_EBOOT=NULL;
#define STR_RESIGN_EBOOT_DEFAULT			"Resign EBOOT"
static char *STR_LAUNCH_EBOOT=NULL;
#define STR_LAUNCH_EBOOT_DEFAULT			"Launch EBOOT"
static char *STR_SIGN_ELF=NULL;
#define STR_SIGN_ELF_DEFAULT				"Sign ELF"
static char *STR_SIGN_EBOOT=NULL;
#define STR_SIGN_EBOOT_DEFAULT				"Sign EBOOT"
static char *STR_SIGN_PRX=NULL;
#define STR_SIGN_PRX_DEFAULT				"Sign PRX"
static char *STR_EXTRACT_PRX=NULL;
#define STR_EXTRACT_PRX_DEFAULT				"Extract PRX"
static char *STR_RESIGN_SPRX=NULL;
#define STR_RESIGN_SPRX_DEFAULT				"Resign SPRX"
static char *STR_REMOVE_PRXLOADER=NULL;
#define STR_REMOVE_PRXLOADER_DEFAULT		"Remove from PRX Loader"
static char *STR_ADD_PRXLOADER=NULL;
#define STR_ADD_PRXLOADER_DEFAULT			"Add to PRX Loader"
static char *STR_REMOVE_PRXLOADER2=NULL;
#define STR_REMOVE_PRXLOADER2_DEFAULT		"Remove from PRXLoader"
static char *STR_ADD_PRXLOADER2=NULL;
#define STR_ADD_PRXLOADER2_DEFAULT			"Add to PRXLoader"
static char *STR_REMOVE_MAMBA=NULL;
#define STR_REMOVE_MAMBA_DEFAULT			"Remove from Mamba list"
static char *STR_ADD_MAMBA=NULL;
#define STR_ADD_MAMBA_DEFAULT				"Add to Mamba list"
static char *STR_REMOVE_COBRA=NULL;
#define STR_REMOVE_COBRA_DEFAULT			"Remove from Cobra list"
static char *STR_ADD_COBRA=NULL;
#define STR_ADD_COBRA_DEFAULT				"Add to Cobra list"
static char *STR_EXTRACT_RCO=NULL;
#define STR_EXTRACT_RCO_DEFAULT				"Extract RCO"
static char *STR_EXTRACT_PKG=NULL;
#define STR_EXTRACT_PKG_DEFAULT				"Extract PKG"
static char *STR_PKG_INFO=NULL;
#define STR_PKG_INFO_DEFAULT				"PKG info"
static char *STR_EXTRACT_TRP=NULL;
#define STR_EXTRACT_TRP_DEFAULT				"Extract TRP"
static char *STR_COMPRESS_ISO=NULL;
#define STR_COMPRESS_ISO_DEFAULT			"Compress ISO"
static char *STR_CHECK_CRC32=NULL;
#define STR_CHECK_CRC32_DEFAULT				"Check CRC32"
static char *STR_DECOMPRESS_CSO=NULL;
#define STR_DECOMPRESS_CSO_DEFAULT			"Decompress CSO"
static char *STR_EXTRACT_THM=NULL;
#define STR_EXTRACT_THM_DEFAULT				"Extract THM"
static char *STR_EXTRACT_P3T=NULL;
#define STR_EXTRACT_P3T_DEFAULT				"Extract P3T"
static char *STR_EXTRACT_RAF=NULL;
#define STR_EXTRACT_RAF_DEFAULT				"Extract RAF"
static char *STR_EXTRACT_QRC=NULL;
#define STR_EXTRACT_QRC_DEFAULT				"Extract QRC"
static char *STR_EXTRACT_ZIP=NULL;
#define STR_EXTRACT_ZIP_DEFAULT				"Extract ZIP"
static char *STR_CONVERT_JSX_JS=NULL;
#define STR_CONVERT_JSX_JS_DEFAULT			"Convert JSX to JS"
static char *STR_CONVERT_VAG_WAV=NULL;
#define STR_CONVERT_VAG_WAV_DEFAULT			"Convert VAG to WAV"
static char *STR_CONVERT_GTF_DDS=NULL;
#define STR_CONVERT_GTF_DDS_DEFAULT			"Convert GTF to DDS"
static char *STR_CONVERT_DDS_PNG=NULL;
#define STR_CONVERT_DDS_PNG_DEFAULT			"Convert DDS to PNG"
static char *STR_MAKE_APNG=NULL;
#define STR_MAKE_APNG_DEFAULT				"Make APNG"
static char *STR_SET_PERMS=NULL;
#define STR_SET_PERMS_DEFAULT				"Set permission"
static char *STR_NOGAME=NULL;
#define STR_NOGAME_DEFAULT					"No Game Found"
static char *STR_GLOB_SETTINGS=NULL;
#define STR_GLOB_SETTINGS_DEFAULT			"Global settings"
static char *STR_ADJUST=NULL;
#define STR_ADJUST_DEFAULT					"Adjust screen"
static char *STR_ADJUST_DESC=NULL;
#define STR_ADJUST_DESC_DEFAULT				"Calibrate your display."
static char *STR_DL_COVER=NULL;
#define STR_DL_COVER_DEFAULT				"Download covers"
static char *STR_DL_COVER_DESC=NULL;
#define STR_DL_COVER_DESC_DEFAULT			"Download every missing game covers to USRDIR/covers/[gameID].jpg"
static char *STR_PLUGIN_MANAGER=NULL;
#define STR_PLUGIN_MANAGER_DEFAULT			"Plugin Manager"
static char *STR_PLUGIN_MANAGER_DESC=NULL;
#define STR_PLUGIN_MANAGER_DESC_DEFAULT		"Manage your plugins stored in /dev_hdd0/plugins."
static char *STR_UPD_MGZ=NULL;
#define STR_UPD_MGZ_DEFAULT					"Update ManaGunZ"
static char *STR_UPD_MGZ_DESC=NULL;
#define STR_UPD_MGZ_DESC_DEFAULT			"Download and install the latest version of ManaGunZ."
static char *STR_GAME_PATHS=NULL;
#define STR_GAME_PATHS_DEFAULT				"Game backup paths"
static char *STR_GAME_PATHS_DESC=NULL;
#define STR_GAME_PATHS_DESC_DEFAULT			"Configure the name of directories where ManaGunZ will find your backups."
static char *STR_XMB_PRIO=NULL;
#define STR_XMB_PRIO_DEFAULT				"XMB Priority"
static char *STR_XMB_PRIO_DESC=NULL;
#define STR_XMB_PRIO_DESC_DEFAULT			"The icon of ManaGunZ in XMB will be displayed at the top. It will be effective after the next system boot."
static char *STR_HELP=NULL;
#define STR_HELP_DEFAULT					"Show help"
static char *STR_HELP_DESC=NULL;
#define STR_HELP_DESC_DEFAULT				"Display the sentences you are reading here."
static char *STR_COLOR_1=NULL;
#define STR_COLOR_1_DEFAULT					"Color 1"
static char *STR_COLOR_2=NULL;
#define STR_COLOR_2_DEFAULT					"Color 2"
static char *STR_COLOR_3=NULL;
#define STR_COLOR_3_DEFAULT					"Color 3"
static char *STR_COLOR_4=NULL;
#define STR_COLOR_4_DEFAULT					"Color 4"
static char *STR_COLOR_DESC=NULL;
#define STR_COLOR_DESC_DEFAULT				"Change the colors used by ManaGunZ."
static char *STR_UI_SETTINGS=NULL;
#define STR_UI_SETTINGS_DEFAULT				"User interface settings"
static char *STR_UI=NULL;
#define STR_UI_DEFAULT						"User interface"
static char *STR_UI_DESC=NULL;
#define STR_UI_DESC_DEFAULT					"Change the interface."
static char *STR_SIDE_MENU=NULL;
#define STR_SIDE_MENU_DEFAULT				"Game SideMenu"
static char *STR_SIDE_MENU_DESC=NULL;
#define STR_SIDE_MENU_DESC_DEFAULT			"Display the game menu in the right side of the screen."
static char *STR_SHOW_PIC1=NULL;
#define STR_SHOW_PIC1_DEFAULT				"Show PIC1"
static char *STR_SHOW_PIC1_DESC=NULL;
#define STR_SHOW_PIC1_DESC_DEFAULT			"Display the background picture of the current selected games 'PIC1'. Use R1 with the UI LIST and GRID to display it."
static char *STR_SHOW_COVER=NULL;
#define STR_SHOW_COVER_DEFAULT				"Show Cover"
static char *STR_SHOW_COVER_DESC=NULL;
#define STR_SHOW_COVER_DESC_DEFAULT			"Display the game cover."
static char *STR_SHOW_GAMECASE=NULL;
#define STR_SHOW_GAMECASE_DEFAULT			"Show Game Case"
static char *STR_SHOW_GAMECASE_DESC=NULL;
#define STR_SHOW_GAMECASE_DESC_DEFAULT		"Display the game cover with the game case."
static char *STR_SHOW_ICON0=NULL;
#define STR_SHOW_ICON0_DEFAULT				"Show ICON0"
static char *STR_SHOW_ICON0_DESC=NULL;
#define STR_SHOW_ICON0_DESC_DEFAULT			"Display the main picture of the game 'ICON0'."
static char *STR_GRID_TYPE=NULL;
#define STR_GRID_TYPE_DEFAULT				"Grid type"
static char *STR_GRID_TYPE_DESC=NULL;
#define STR_GRID_TYPE_DESC_DEFAULT			"Choose how to make the grid move."
static char *STR_SCROLL=NULL;
#define STR_SCROLL_DEFAULT					"Scroll"
static char *STR_PAGE=NULL;	
#define STR_PAGE_DEFAULT					"Page"
static char *STR_DIRECTION=NULL;
#define STR_DIRECTION_DEFAULT				"Direction"
static char *STR_DIRECTION_DESC=NULL;
#define STR_DIRECTION_DESC_DEFAULT			"Choose in which direction the grid will move."
static char *STR_VERTICAL=NULL;
#define STR_VERTICAL_DEFAULT				"Vertical"
static char *STR_HORIZONTAL=NULL;
#define STR_HORIZONTAL_DEFAULT				"Horizontal"
static char *STR_ANIMATED=NULL;
#define STR_ANIMATED_DEFAULT				"Animated"
static char *STR_ANIMATED_DESC=NULL;
#define STR_ANIMATED_DESC_DEFAULT			"Make the grid's moves sliding."
static char *STR_KEEP_PROP=NULL;
#define STR_KEEP_PROP_DEFAULT				"Keep proportion"
static char *STR_KEEP_PROP_DESC=NULL;
#define STR_KEEP_PROP_DESC_DEFAULT			"Keep the original aspect ratio of the ICON0."
static char *STR_NB_COL=NULL;	
#define STR_NB_COL_DEFAULT					"Number of columns"
static char *STR_NB_COL_DESC=NULL;	
#define STR_NB_COL_DESC_DEFAULT				"Choose the number of columns of the grid."
static char *STR_NB_LINE=NULL;	
#define STR_NB_LINE_DEFAULT					"Number of lines"
static char *STR_NB_LINE_DESC=NULL;	
#define STR_NB_LINE_DESC_DEFAULT			"Choose the number of lines of the grid."
static char *STR_INVERSE=NULL;	
#define STR_INVERSE_DEFAULT					"Inverse button"
static char *STR_INVERSE_DESC=NULL;	
#define STR_INVERSE_DESC_DEFAULT			"Inverse the buttons right and left.​"
static char *STR_3D=NULL;	
#define STR_3D_DEFAULT						"3D"
static char *STR_3D_DESC=NULL;	
#define STR_3D_DESC_DEFAULT					"Display the menu with 3D models of gamecases."
static char *STR_ADD=NULL;	
#define STR_ADD_DEFAULT						"Add"
static char *STR_LOAD=NULL;	
#define STR_LOAD_DEFAULT					"Load"
static char *STR_CHANGE=NULL;	
#define STR_CHANGE_DEFAULT					"Change"
static char *STR_COLOR=NULL;	
#define STR_COLOR_DEFAULT					"Color"
static char *STR_RESET=NULL;	
#define STR_RESET_DEFAULT					"Reset"
static char *STR_FAILED=NULL;
#define STR_FAILED_DEFAULT					"Failed"
static char *STR_DONE=NULL;
#define STR_DONE_DEFAULT					"Done"
static char *STR_OPEN=NULL;
#define STR_OPEN_DEFAULT					"Open"
static char *STR_CLOSE=NULL;
#define STR_CLOSE_DEFAULT					"Close"
static char *STR_OPTION=NULL;
#define STR_OPTION_DEFAULT					"Option"
static char *STR_SELECT=NULL;
#define STR_SELECT_DEFAULT					"Select"
static char *STR_WINDOW=NULL;
#define STR_WINDOW_DEFAULT					"Window"
static char *STR_CLICK=NULL;
#define STR_CLICK_DEFAULT					"Click"
static char *STR_CURSOR=NULL;
#define STR_CURSOR_DEFAULT					"Cursor"
static char *STR_NEXT=NULL;
#define STR_NEXT_DEFAULT					"Next"
static char *STR_PREVIOUS=NULL;
#define STR_PREVIOUS_DEFAULT				"Previous"
static char *STR_SET_COLOR=NULL;
#define STR_SET_COLOR_DEFAULT				"Set color"
static char *STR_HIDETV=NULL;
#define STR_HIDETV_DEFAULT					"Hide TV screen test"
static char *STR_SHOWTV=NULL;
#define STR_SHOWTV_DEFAULT					"Show TV screen test"
static char *STR_MOVE_TO_PLUGINS=NULL;
#define STR_MOVE_TO_PLUGINS_DEFAULT			"Move to /dev_hdd0/plugins"
static char *STR_ASK_PLUGINS=NULL;
#define STR_ASK_PLUGINS_DEFAULT				"To use the plugin manager, the plugins must be in '/dev_hdd0/plugins'. Do you accept to use this folder ?"
static char *STR_CHANGE_VALUE=NULL;
#define STR_CHANGE_VALUE_DEFAULT			"Change value"
static char *STR_LOAD_IDPS_LV2=NULL;
#define STR_LOAD_IDPS_LV2_DEFAULT			"Load IDPS from lv2"
static char *STR_LOAD_IDPS_EID5=NULL;
#define STR_LOAD_IDPS_EID5_DEFAULT			"Load IDPS from EID5"
static char *STR_NAME=NULL;
#define STR_NAME_DEFAULT					"Name"
static char *STR_DOCK_RIGHT=NULL;
#define STR_DOCK_RIGHT_DEFAULT				"Dock to right"
static char *STR_DOCK_LEFT=NULL;
#define STR_DOCK_LEFT_DEFAULT				"Dock to left"
static char *STR_DOCK_FULL=NULL;
#define STR_DOCK_FULL_DEFAULT				"Dock to full"
static char *STR_PLUGIN_MONITOR=NULL;
#define STR_PLUGIN_MONITOR_DEFAULT			"Plugin Monitor"
static char *STR_UNUSED=NULL;
#define STR_UNUSED_DEFAULT					"Unused"
static char *STR_UNLOAD=NULL;
#define STR_UNLOAD_DEFAULT					"Unload"
static char *STR_BOOT_FILE=NULL;
#define STR_BOOT_FILE_DEFAULT				"Boot file"
static char *STR_CURRENT=NULL;
#define STR_CURRENT_DEFAULT					"Current"
static char *STR_NET=NULL;
#define STR_NET_DEFAULT						"Net"
static char *STR_SOFT=NULL;
#define STR_SOFT_DEFAULT					"Soft"
static char *STR_GX=NULL;
#define STR_GX_DEFAULT						"GX"
static char *STR_CUSTOM=NULL;
#define STR_CUSTOM_DEFAULT					"Custom"
static char *STR_NEW_CMD=NULL;
#define STR_NEW_CMD_DEFAULT					"New command"
static char *STR_PNACH=NULL;
#define STR_PNACH_DEFAULT					"Pnach"
static char *STR_WIDESCREEN=NULL;
#define STR_WIDESCREEN_DEFAULT				"WideScreen"
static char *STR_480P=NULL;
#define STR_480P_DEFAULT					"480P"
static char *STR_YFIX=NULL;
#define STR_YFIX_DEFAULT					"YFIX"
static char *STR_FMV=NULL;
#define STR_FMV_DEFAULT						"FMV skip"
static char *STR_SIMPLE=NULL;
#define STR_SIMPLE_DEFAULT					"Simple"
static char *STR_ADVANCED=NULL;
#define STR_ADVANCED_DEFAULT				"Advanced"
static char *STR_INSTALL_MGZ=NULL;
#define STR_INSTALL_MGZ_DEFAULT				"Do you want to install ManaGunZ" 
static char *STR_UP2DATE=NULL;
#define STR_UP2DATE_DEFAULT					"It's up to date"
static char *STR_SHOW_WAVES=NULL;
#define STR_SHOW_WAVES_DEFAULT				"Show waves"
static char *STR_SHOW_WAVES_DESC=NULL;
#define STR_SHOW_WAVES_DESC_DEFAULT			"Display waves in background."
static char *STR_WAVES_COLOR=NULL;
#define STR_WAVES_COLOR_DEFAULT				"Waves color"
static char *STR_WAVES_COLOR_DESC=NULL;
#define STR_WAVES_COLOR_DESC_DEFAULT		"Change the color of the waves."
static char *STR_USE_CONFIG=NULL;
#define STR_USE_CONFIG_DEFAULT				"You are not using a PS2 configuration file '*.CONFIG'."
static char *STR_COLORSET=NULL;
#define STR_COLORSET_DEFAULT				"ColorSet"
static char *STR_COLORSET_DESC=NULL;
#define STR_COLORSET_DESC_DEFAULT			"Choose a predefined set of colors to use in ManaGunZ."
static char *STR_GRID_SCROLL=NULL;
#define STR_GRID_SCROLL_DEFAULT				"Scroll"
static char *STR_ADD_LIMG=NULL;
#define STR_ADD_LIMG_DEFAULT				"Add LIMG"
static char *STR_REMOVE_LIMG=NULL;
#define STR_REMOVE_LIMG_DEFAULT				"Remove LIMG"
static char *STR_LIMG_DESC=NULL;
#define STR_LIMG_DESC_DEFAULT				"It may fix few games."
static char *STR_FONT=NULL;
#define STR_FONT_DEFAULT					"Font"
static char *STR_FONT_DESC=NULL;
#define STR_FONT_DESC_DEFAULT				"Change the font."
static char *STR_MOVE=NULL;
#define STR_MOVE_DEFAULT					"Move"
static char *STR_JOIN=NULL;
#define STR_JOIN_DEFAULT					"Join"
static char *STR_JOIN_DESC=NULL;
#define STR_JOIN_DESC_DEFAULT				"Merge .666XX files."


//***********************************************************
// Functions
//***********************************************************

u8 Copy(char *src, char *dst);
void Delete(char* path);
void print_head(char *format2, ...);
void print_load(char *format, ...);
u8 Show_it(int pos);
char *LoadFile(char *path, int *file_size);
char *LoadFileProg(char *path, int *file_size);
u8 GetParamSFO(const char *name, char *value, int position, char *path);
u8 Get_ID(char *isopath, u8 platform, char *game_ID);
u8 is_apng(char *file);
u8 Load_APNG(char* filename);
float DrawStringFromCenterX(float x, float y, char *txt);
void start_loading();
void end_loading();
void open_picture_viewer(char *pict_path);
void open_txt_viewer(char *txt_path);
void open_SFO_viewer(char *path);
void Draw_FileExplorer();
void show_msg(char *str);
char *LoadFileFromISO(u8 prog, char *path, char *filename, int *size);
u8 get_ext(char *file);
void read_fav();
int Draw_Progress_Bar(float x, float y, u8 size, float value, u32 color);
u32 Get_PS2CRC();
u32 Get_Original_PS2CRC();
void Draw_scene();
void Draw_title(float x, float y, char *str);
void peek_IDPS();
void start_load_PIC1();
void end_load_PIC1();
int SaveFile(char *path, char *mem, int file_size);
void read_setting();
void write_setting();
void Draw_input();
void cursor_input();
u8 is_iso(char *file_name);
u8 is_splitted_iso(char *file_name);
u8 is_66600(char *file_name);
u8 is_666XX(char *file_name);
u8 is_usb(char *file_name);
u64 get_size(char *path, u8 upd_data);
void poke_IDPS();
u8 WS_exist();
u8 Pnach_exist();
void CONFIG_check(char *IsoPath);
void DrawTXTInBox(float x, float y, float z, float w, float h, char *txt, u32 bg_color, u32 font_color);
char *get_unit(u64 nb);
char *strcpy_malloc(char *STR_DEFAULT);
void Draw_cursor();
void ScreenShot();
u8 GetALPHA(u32 rgba);
char *get_str_regex(char *mem, char *format);
void LoadFont();
u8 LoadTexture(char *texture_path, u32 *texture_offset, imgData *texture_data);
int sys_fs_chown(char *path, s32 uid, s32 gid);
u8 SetFilePerms(char *path);
void open_SETTINGS();
void close_SETTINGS();
void TranslateTo(float *value, float target);
void remove_GAMELIST(s64 pos);

void Draw_MENU();

typedef void (*func)();
void EmptyFunc()
{
	return;
}
func Draw_MENU_input = &EmptyFunc;
func input_MENU = &EmptyFunc;

//***********************************************************
// Ugly SpeedFix : Original standard I/O function are slow
//***********************************************************

#define FILE int

int FAKE_truncate(const char *path, off_t len)
{
    int ret;
    int fd;

    fd = ret = ps3ntfs_open(path, O_RDWR, 0666);

    if(ret < 0) return ret;

    ret = ps3ntfs_ftruncate(fd, len);
	
    ps3ntfs_close(fd);
	
    return ret;
}

FILE* FAKE_fopen(char *filepath, const char *mode)
{
	int oflags;
	int m, o;
	switch (*mode++) {
		case 'r':	/* open for reading */
			m = O_RDONLY;
			o = 0;
			break;
		case 'w':	/* open for writing */
			m = O_WRONLY;
			o = O_CREAT | O_TRUNC;
			break;
		case 'a':	/* open for appending */
			m = O_WRONLY;
			o = O_CREAT | O_APPEND;
			break;
		default:	/* illegal mode */
			return (0);
		}
		/* [rwa]\+ or [rwa]b\+ means read and write */
		if (*mode == '+' || (*mode == 'b' && mode[1] == '+')) {
			m = O_RDWR;
	}
	
	oflags = m | o;
	
	int *f = malloc(sizeof(int *));
	
	*f = ps3ntfs_open(filepath, oflags, 0777);
	
	if(*f<0) {
		SetFilePerms(filepath);
		*f = ps3ntfs_open(filepath, oflags, 0777);
		if(*f<0) {free(f); return NULL;}
	}
	
	return f;
}

s64 FAKE_fseek(FILE* fp, s64 pos, int dir)
{
	return ps3ntfs_seek64(*fp, (s64) pos, dir);
}

size_t FAKE_fread(void *ptr, size_t size, size_t count, FILE* fp)
{
	return ps3ntfs_read(*fp, (char*)ptr, size*count);
}

size_t FAKE_fwrite(void *ptr, size_t size, size_t count, FILE* fp)
{
	return ps3ntfs_write(*fp, (const char *)ptr, size*count);
}

char *FAKE_fgets(char *str, int length, FILE* fp)
{
	char c;
	int count=0;
	memset(str, 0, sizeof(str));
	if(length==0) return NULL;
	while(ps3ntfs_read(*fp, &c, 1))
	{	
		str[count]=c;
		if(count==length) break;
		count++;
		if(c=='\n' || c==0) break;
	}
	if(count == 0) return NULL;
	
	return str;
}

void FAKE_fputs(char *str, FILE* fp)
{
	ps3ntfs_write(*fp, str, strlen(str));
}

int FAKE_fclose(FILE* fp)
{	
	int ret = ps3ntfs_close(*fp);
	FREE(fp);
	return ret;
}

u64 FAKE_ftell(FILE* fp)
{
	return ps3ntfs_seek64(*fp, 0, SEEK_CUR);
}
#define FAKE_EOF 0
char FAKE_fgetc(FILE* fp)
{
	char c;
	if( ps3ntfs_read(*fp, &c, 1) != 1) return FAKE_EOF;
	return c;
}

char FAKE_fputc(char c, FILE* fp)
{
	ps3ntfs_write(*fp, (const char *) &c, 1);
	return c;
}

#define truncate FAKE_truncate
#define fputc FAKE_fputc
#define fgetc FAKE_fgetc
#define ftell FAKE_ftell
#define fseek FAKE_fseek
#define fopen FAKE_fopen
#define fclose FAKE_fclose
#define fread FAKE_fread
#define fwrite FAKE_fwrite
#define fgets FAKE_fgets
#define fputs FAKE_fputs

//*******************************************************
// 
//*******************************************************

void cls()
{
	tiny3d_Clear(0xff000000, TINY3D_CLEAR_ALL);
		
	// Enable alpha Test
	tiny3d_AlphaTest(1, 1, TINY3D_ALPHA_FUNC_GEQUAL);

   // Enable alpha blending.
			tiny3d_BlendFunc(1, TINY3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA | TINY3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
				TINY3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA | TINY3D_BLEND_FUNC_DST_ALPHA_ZERO,
				TINY3D_BLEND_RGB_FUNC_ADD | TINY3D_BLEND_ALPHA_FUNC_ADD);
	reset_ttf_frame();
}

void Init_Graph()
{
	tiny3d_Init(2*1024*1024);

	texture_mem = tiny3d_AllocTexture(200*1024*1024);
	if(!texture_mem) return;
		
	ResetFont();
	
	double sx = (double) Video_Resolution.width;
	double sy = (double) Video_Resolution.height;
	double psx = (double) (1000 + videoscale_x)/1000.0;
	double psy = (double) (1000 + videoscale_y)/1000.0;
	
	tiny3d_UserViewport(1, 
		(float) ((sx - sx * psx) / 2.0), // 2D position
		(float) ((sy - sy * psy) / 2.0), 
		(float) ((sx * psx) / X_MAX),	// 2D scale
		(float) ((sy * psy) / Y_MAX),
		(float) ((sx / X_MAX) * psx),  // 3D scale
		
		(float) ((sy / Y_MAX) * psy));
}

void adjust_screen()
{
	double sx = (double) Video_Resolution.width;
	double sy = (double) Video_Resolution.height;
	double psx = (double) (1000 + videoscale_x)/1000.0;
	double psy = (double) (1000 + videoscale_y)/1000.0;
	
	tiny3d_UserViewport(1, 
		(float) ((sx - sx * psx) / 2.0), // 2D position
		(float) ((sy - sy * psy) / 2.0), 
		(float) ((sx * psx) / X_MAX),	// 2D scale
		(float) ((sy * psy) / Y_MAX),
		(float) ((sx / X_MAX) * psx),  // 3D scale
		(float) ((sy / Y_MAX) * psy));
}

//*******************************************************
// FONT
//*******************************************************


void FreeFont()
{
	int i;
	for(i=0; i<MENU_MAX_ITEMS_VALUE; i++) FREE(FontName[i]);
	FREE(FontName);
	
	for(i=0; i<MENU_MAX_ITEMS_VALUE; i++) FREE(FontPath[i]);
	FREE(FontPath);
	
	FontNumber=-1;
}

char *get_ttf_name(char *ttf)
{
	char strFullName[255];
	char strVersion[255];
	u32 strFullNameLen=0;
	u32 strVersionLen=0;
	int i,j;
	FILE *f;
	
	f = fopen(ttf, "rb");
	if(f==NULL) return NULL;
	
	u32 entrynumber;
	
	fseek(f, 2, SEEK_SET);
	fread(&entrynumber, sizeof(u32), 1, f);
	
	char entryname[5];
	
	u32 NameTable_offset=0;
	for(i=0; i<entrynumber; i++) {
		fseek(f, 0xC + i*0x10, SEEK_SET);
		fread(&entryname, 4, 1, f);
		entryname[4]=0;
		
		if( strcmp(entryname, "name") == 0) {
			fseek(f, 4, SEEK_CUR);
			fread(&NameTable_offset, sizeof(u32), 1, f);
			break;
		}
	}
	if(NameTable_offset == 0) {
		fclose(f);
		return NULL;
	} 

	u16 strtaboff=0;
	u16 number=0;

	fseek(f, NameTable_offset+2, SEEK_SET);
	fread(&number, sizeof(u16), 1, f);
	fread(&strtaboff, sizeof(u16), 1, f);
	
	u16 lang, name;
	for(i=0; i<number; i++) {
		fseek(f,  NameTable_offset+0xA+i*0xC, SEEK_SET);
		fread(&lang, sizeof(u16), 1, f);
		fread(&name, sizeof(u16), 1, f);
		
		//if(lang==0 && name==4) { //fullname english
		if(name==4) {
			u16 strlen;
			u16 stroff;
			fread(&strlen, sizeof(u16), 1, f);
			fread(&stroff, sizeof(u16), 1, f);
			
			fseek(f, NameTable_offset+strtaboff+stroff, SEEK_SET);
			
			char c;
			for(j=0; j<strlen; j++) {
				fread(&c, 1, 1, f);
				if(c==0) continue;
				strFullName[strFullNameLen]=c;
				strFullNameLen++;
			}
			strFullName[strFullNameLen]=0;
		}
		
		//if(lang==0 && name==5) { //version english
		if(name==5) {
			u16 strlen;
			u16 stroff;
			fread(&strlen, sizeof(u16), 1, f);
			fread(&stroff, sizeof(u16), 1, f);
			
			fseek(f, NameTable_offset+strtaboff+stroff, SEEK_SET);
			
			char c;
			for(j=0; j<strlen; j++) {
				fread(&c, 1, 1, f);
				if(c==0) continue;
				strVersion[strVersionLen]=c;
				strVersionLen++;
			}
			strVersion[strVersionLen]=0;
		}
		
		if(strVersionLen && strFullNameLen) break;
	}
	fclose(f);
	
	if(strFullNameLen==0) return NULL;

	char *ret = (char *) malloc(strFullNameLen+strVersionLen+3);
	if(ret==NULL) return NULL;
	
	if(strVersionLen) {
		sprintf(ret, "%s [%s]", strFullName,  strVersion);
	} else {
		strcpy(ret, strFullName);
	}
	return ret;
}

void ScanFont(char *directory)
{
	char temp[255];
	
	if(FontNumber+2 == MENU_MAX_ITEMS_VALUE) return;
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(directory);
	if(d==NULL) return;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		if(FontNumber+2 == MENU_MAX_ITEMS_VALUE) {
			closedir(d);
			return;
		}
		
		sprintf(temp, "%s/%s", directory, dir->d_name);
		
		if(dir->d_type & DT_DIR) {
			ScanFont(temp);
		}
		if(get_ext(temp) != _TTF) continue;	
				
		FontNumber++;
		FontName[FontNumber] = get_ttf_name(temp);
		if(FontName[FontNumber] == NULL) {
			FontName[FontNumber] = strcpy_malloc(dir->d_name);
		}
		FontPath[FontNumber] = strcpy_malloc(temp);
	}
	closedir(d);
}

void GetFont()
{
	int i;
	
	FontName = (char **) malloc(MENU_MAX_ITEMS_VALUE * sizeof(char*));
	FontPath = (char **) malloc(MENU_MAX_ITEMS_VALUE * sizeof(char*));
	for(i=0; i<MENU_MAX_ITEMS_VALUE; i++) FontName[i]=NULL;
	for(i=0; i<MENU_MAX_ITEMS_VALUE; i++) FontPath[i]=NULL;
	FontNumber = -1;
	
	u8 FontDirNumber = 2;
	char FontDir[FontDirNumber][64];
	
	sprintf(FontDir[0], "/dev_hdd0/game/%s/USRDIR/GUI",  ManaGunZ_id);
	strcpy(FontDir[1], "/dev_flash/data/font");
	
	for(i=0; i<FontDirNumber; i++) {
		ScanFont(FontDir[i]);
		if(FontNumber+2 == MENU_MAX_ITEMS_VALUE) return;
	}
}

void LoadFont()
{
	TTFUnloadFont();
	
	texture_pointer = texture_mem + TEXTURE_POINTER_FONT;
	
	TTFLoadFont(0, Font, NULL, 0);
	TTFLoadFont(1, "/dev_flash/data/font/SCE-PS3-DH-R-CGB.TTF", NULL, 0);
	TTFLoadFont(2, "/dev_flash/data/font/SCE-PS3-SR-R-JPN.TTF", NULL, 0);
	TTFLoadFont(3, "/dev_flash/data/font/SCE-PS3-YG-R-KOR.TTF", NULL, 0);
	
	texture_pointer = (u32 *) init_ttf_table((u16 *) texture_pointer);
}

float new_line(float nb)
{
	//return GetFontY() + GetFontHeight()*nb;
	return GetFontHeight()*nb;
}

float GetWidth(char *str)
{
	return DrawFormatString(0, -50, str);
}

void FontSize(float size)
{
	SetFontSize((float) (3 * size / 4),  size );
}

void FontColor(u32 color)
{
	SetFontColor(color, 0);
}

//*******************************************************
// 
//*******************************************************

void Draw_BoxGradiant(u8 direction, float x, float y, float z, float w, float h, u32 color1, u32 color2, u8 texture) 
{
	
	if(direction == VERTICAL) { 
		tiny3d_SetPolygon(TINY3D_QUADS);
		tiny3d_VertexPos(x	 	, y	 , z);
		tiny3d_VertexColor(color1);
		if(texture) tiny3d_VertexTexture(0.0f, 0.0f);
			
		tiny3d_VertexPos(x + w	, y	 , z);
		tiny3d_VertexColor(color1);
		if(texture) tiny3d_VertexTexture(1.0f, 0.0f);
		
		tiny3d_VertexPos(x + w	, y + h	, z);
		tiny3d_VertexColor(color2);
		if(texture) tiny3d_VertexTexture(1.0f, 1.0f);
		
		tiny3d_VertexPos(x	 	, y + h	, z);
		tiny3d_VertexColor(color2);
		if(texture) tiny3d_VertexTexture(0.0f, 1.0f);
		tiny3d_End();
	} else 
	if(direction == HORIZONTAL) {
		tiny3d_SetPolygon(TINY3D_QUADS);
		tiny3d_VertexPos(x	 	, y	 , z);
		tiny3d_VertexColor(color1);
		if(texture) tiny3d_VertexTexture(0.0f, 0.0f);
			
		tiny3d_VertexPos(x  	, y	+ h , z);
		tiny3d_VertexColor(color1);
		if(texture) tiny3d_VertexTexture(0.0f, 1.0f);
		
		tiny3d_VertexPos(x + w	, y + h	, z);
		tiny3d_VertexColor(color2);
		if(texture) tiny3d_VertexTexture(1.0f, 1.0f);
		
		tiny3d_VertexPos(x + w  , y		, z);
		tiny3d_VertexColor(color2);
		if(texture) tiny3d_VertexTexture(1.0f, 0.0f);
		tiny3d_End();
	}
	
	
	
}

void Draw_Box(float x, float y, float z, float r, float w, float h, u32 rgba, u8 texture) //texture only if r=0
{
	if(r > w || r > h) r=0;
	
	if(r==0){
		tiny3d_SetPolygon(TINY3D_QUADS);
		tiny3d_VertexPos(x	 	, y	 , z);
		tiny3d_VertexColor(rgba);
		if(texture) tiny3d_VertexTexture(0.0f, 0.0f);
		
		tiny3d_VertexPos(x + w	, y	 , z);
		tiny3d_VertexColor(rgba);
		if(texture) tiny3d_VertexTexture(1.0f, 0.0f);
		
		tiny3d_VertexPos(x + w	, y + h	, z);
		tiny3d_VertexColor(rgba);
		if(texture) tiny3d_VertexTexture(1.0f, 1.0f);
		
		tiny3d_VertexPos(x	 	, y + h	, z);
		tiny3d_VertexColor(rgba);
		if(texture) tiny3d_VertexTexture(0.0f, 1.0f);
		
		tiny3d_End();
	}
	else {
		int t;
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(rgba);
		x+=r;
		y+=r;
		for(t=-90; t>=-180 ; t-=10) {
			tiny3d_VertexPos( x + r*cos(t*PI/180), y + r*sin(t*PI/180), z);
		}
		y+= h-2*r;
		for(t=180; t>=90 ; t-=10) {
			tiny3d_VertexPos( x + r*cos(t*PI/180), y + r*sin(t*PI/180), z);
		}
		x+= w-2*r;
		for(t=90; t>=0 ; t-=10) {
			tiny3d_VertexPos( x + r*cos(t*PI/180), y + r*sin(t*PI/180), z);
		}
		y-= h-2*r;
		for(t=0; t>=-90 ; t-=10) {
			tiny3d_VertexPos( x + r*cos(t*PI/180), y + r*sin(t*PI/180), z);
		}
		
		tiny3d_End();
	}
	
}

void Draw_LineBox(float x, float y, float z, float e, float w, float h, u32 color)
{
	Draw_Box(x-e, y-e, z, 0, e, h+2*e, color, NO);
	Draw_Box(x+w, y-e, z, 0, e, h+2*e, color, NO);
	
	Draw_Box(x, y-e, z, 0, w, e, color, NO);
	Draw_Box(x, y+h, z, 0, w, e, color, NO);
}

float Draw_checkbox(u8 checked, float x, float y, char *str, u32 color)
{
	Draw_Box(x, y, 0, 0, 14, 14, color, NO);
	Draw_Box(x+2, y+2, 0, 0, 10, 10, BLACK, NO);
	
	if(checked) Draw_Box(x+3, y+3, 0, 0, 8, 8, color, NO);
	
	FontColor(color);
	FontSize(15);
	
	return DrawString(x+20, y, str);
}

void Draw_title(float x, float y, char *str)
{
	int xt;
	FontSize(18);
	Draw_Box(x+5, y+4, 9, 0, 8, 8, COLOR_3, NO);
	FontColor(COLOR_3);
	xt=DrawString(x+20, y, str);
	y+=18;
	Draw_Box(x, y, 9, 0, xt-x, 2, COLOR_3, NO); //underline
	FontSize(15);
	FontColor(COLOR_1);
}

u8 is_ntfs(char *path)
{
	if(strstr(path, "ntfs")) return YES;
	return NO;
}

u8 path_info(char *path) 
{
	struct stat s;
	if(stat(path, &s) != 0) return _NOT_EXIST;
	if(S_ISDIR(s.st_mode)) return _DIRECTORY; else
	return _FILE;
}

u8 exist(char *path)
{
	if(path_info(path) == _NOT_EXIST) return NO;
	return YES;
}

char *GetExtention(char *path)
{
    int n = strlen(path);
    int m = n;

    while(m > 1 && path[m] != '.' && path[m] != '/') m--;
    
    if(strcmp(&path[m], ".0")==0 || strcmp(&path[m], ".66600")==0) { // splitted
       m--;
       while(m > 1 && path[m] != '.' && path[m] != '/') m--; 
    }
    
    if(path[m] == '.') return &path[m];

    return &path[n];
}

void RemoveExtention(char *path)
{
    char *extention = GetExtention(path);
	
    int le = strlen(extention);
    int lp = strlen(path);
    
    while(le>0) {path[lp-le]=0; le--;}
}

u8 imgLoadFromFile(char *imgPath, imgData *out)
{
	int file_size = 0;
	
	out->bmp_out = NULL;
	
	if(path_info(imgPath) == _NOT_EXIST) return FAILED;

	char *buff = LoadFile((char *) imgPath, &file_size);
	if(buff==NULL) return FAILED;

	if(pngLoadFromBuffer((const void *) buff, file_size, (pngData *) out) != 0)
	if(jpgLoadFromBuffer((const void *) buff, file_size, (jpgData *) out) != 0) {
		free(buff);
		return FAILED;
	}
	
	free(buff);

	return SUCCESS;
}

void Read_ICON0(int position)
{
	char temp[128];

	if(list_game_platform[position] == _ISO_PS3) {
		int size;
		char *mem = LoadFileFromISO(NO, list_game_path[position], "/PS3_GAME/ICON0.PNG", &size);
		if(mem==NULL) return;
		pngLoadFromBuffer((const void *) mem, size, (pngData *) &ICON0[position]);
		free(mem);
	} else
	if(list_game_platform[position] == _ISO_PSP) {
		int size;
		char *mem = LoadFileFromISO(NO, list_game_path[position], "/PSP_GAME/ICON0.PNG", &size);
		if(mem==NULL) return;
		pngLoadFromBuffer((const void *) mem, size, (pngData *) &ICON0[position]);
		free(mem);
	} else	
	if(list_game_platform[position] == _JB_PS3) {
		sprintf(temp, "%s/PS3_GAME/PKGDIR/ICON0.PNG", list_game_path[position]);
		if(imgLoadFromFile(temp, &ICON0[position]) == SUCCESS) return;
		else {
			sprintf(temp, "%s/PS3_GAME/ICON0.PNG", list_game_path[position]);
			if(imgLoadFromFile(temp, &ICON0[position]) == SUCCESS) return;
		}
	} else
	if(list_game_platform[position] == _JB_PSP) {
		sprintf(temp, "%s/PSP_GAME/PKGDIR/ICON0.PNG", list_game_path[position]);
		if(imgLoadFromFile(temp, &ICON0[position]) == SUCCESS) return;
		else {
			sprintf(temp, "%s/PSP_GAME/ICON0.PNG", list_game_path[position]);
			if(imgLoadFromFile(temp, &ICON0[position]) == SUCCESS) return;
		}
	} else
	if(list_game_platform[position] == _ISO_PS2 || list_game_platform[position] == _ISO_PS1) {
		strcpy(temp, list_game_path[position]);
		temp[strlen(temp)-4]=0;
		char temp2[255];
		sprintf(temp2, "%s.jpg", temp);
		if(imgLoadFromFile(temp2, &ICON0[position]) == SUCCESS) return;
		sprintf(temp2, "%s.png", temp);
		if(imgLoadFromFile(temp2, &ICON0[position]) == SUCCESS) return;
		sprintf(temp2, "%s.JPG", temp);
		if(imgLoadFromFile(temp2, &ICON0[position]) == SUCCESS) return;
		sprintf(temp2, "%s.PNG", temp);
		if(imgLoadFromFile(temp2, &ICON0[position]) == SUCCESS) return;
	}
	
}

//*******************************************************
// SCREENSOT
//******************************************************

typedef struct                       /**** BMP file header structure ****/
{
	u32 bfSize;           /* Size of file */
	u16 bfReserved1;      /* Reserved */
	u16 bfReserved2;      /* ... */
	u32 bfOffBits;        /* Offset to bitmap data */
} bmp_file_header;

typedef struct                       /**** BMP file info structure ****/
{
	u32 biSize;           /* Size of info header */
	s32 biWidth;          /* Width of image */
	s32 biHeight;         /* Height of image */
	u16	biPlanes;         /* Number of color planes */
	u16 biBitCount;       /* Number of bits per pixel */
	u32 biCompression;    /* Type of compression to use */
	u32 biSizeImage;      /* Size of image data */
	s32 biXPelsPerMeter;  /* X pixels per meter */
	s32 biYPelsPerMeter;  /* Y pixels per meter */
	u32 biClrUsed;        /* Number of colors used */
	u32 biClrImportant;   /* Number of important colors */
} bmp_info_header;


void es_bmp_file_header(bmp_file_header *w)
{
	w->bfSize = ENDIAN_SWAP_32(w->bfSize);; 
	w->bfReserved1 = ENDIAN_SWAP_16(w->bfReserved1);
	w->bfReserved2 = ENDIAN_SWAP_16(w->bfReserved2);
	w->bfOffBits = ENDIAN_SWAP_32(w->bfOffBits);  
}

void es_bmp_info_header(bmp_info_header *w)
{
	w->biSize = ENDIAN_SWAP_32(w->biSize);
	w->biWidth = ENDIAN_SWAP_32(w->biWidth); 
	w->biHeight = ENDIAN_SWAP_32(w->biHeight);    
	w->biPlanes = ENDIAN_SWAP_16(w->biPlanes);       
	w->biBitCount = ENDIAN_SWAP_16(w->biBitCount);     
	w->biCompression = ENDIAN_SWAP_32(w->biCompression);  
	w->biSizeImage = ENDIAN_SWAP_32(w->biSizeImage);    
	w->biXPelsPerMeter = ENDIAN_SWAP_32(w->biXPelsPerMeter);
	w->biYPelsPerMeter = ENDIAN_SWAP_32(w->biYPelsPerMeter);
	w->biClrUsed = ENDIAN_SWAP_32(w->biClrUsed);      
	w->biClrImportant = ENDIAN_SWAP_32(w->biClrImportant); 
}

// https://en.wikipedia.org/wiki/BMP_file_format
void ScreenShot()
{
	if( !((new_pad & BUTTON_L2) && (old_pad & BUTTON_R2))
	&&  !((new_pad & BUTTON_R2) && (old_pad & BUTTON_L2)) ) return;

	if(Video_currentBuffer==NO) return;
	
	u8 *mem = malloc(Video_Resolution.width*Video_Resolution.height*4 + 1);
	memcpy(mem, Video_buffer[1], Video_Resolution.width*Video_Resolution.height*4);
	
	//start_loading();
	
print_load("Get size scaled...");
	double sx = (double) Video_Resolution.width;
	double sy = (double) Video_Resolution.height;
	double psx = (double) (1000 + videoscale_x)/1000.0;
	double psy = (double) (1000 + videoscale_y)/1000.0;
	
	u32 w = (u32) (sx * psx);
	u32 h = (u32) (sy * psy);
	u32 x = (u32) (((u32)sx - w) / 2);
	u32 y = (u32) (((u32)sy - h) / 2);
	
	mkdir("/dev_hdd0/photo", 0777);
	
	char ScreenShotPath[128];
	int o;
	for(o=0; o<1000; o++) {
		sprintf(ScreenShotPath, "/dev_hdd0/photo/ManaGunZ_%03d.bmp", o);
		if(path_info(ScreenShotPath) == _NOT_EXIST) break;
	}
	
print_load("Open file %s", ScreenShotPath);
	FILE *f = fopen(ScreenShotPath, "wb");
	if (!f) {
		print_load("Error : ScreenShot, failed to open file");
		return;
	}
	
print_load("Define headers");
	bmp_file_header bfh;
	bmp_info_header bih;

	unsigned short bfType=0x424D;           
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfSize = 2+sizeof(bmp_file_header) + sizeof(bmp_info_header)+w*h*3;
	bfh.bfOffBits = 0x36;

	bih.biSize = sizeof(bmp_info_header);
	bih.biWidth = w;
	bih.biHeight = h;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	es_bmp_file_header(&bfh);
	es_bmp_info_header(&bih);

print_load("Write headers");
	fwrite(&bfType,1,sizeof(bfType),f);
	fwrite(&bfh, 1, sizeof(bfh), f);
	fwrite(&bih, 1, sizeof(bih), f);
	
print_head("Get bitmap data...");
	s64 i;
	s64 j;
	s64 k;
	u64 l=0;
	u8 pad  = (4 - ((3*w) & 3)) & 3;
	u8 *bitmap= (u8 *) malloc(w*h*3 + h*pad + 1); 
	prog_bar1_value = 0;
	for(i=y+h-1; i>=y; i--) {
		k=i*Video_Resolution.width;
		prog_bar1_value = (y+h-1-i)/h;
		for(j=x+k; j<x+k+w; j++) {
			bitmap[l] = mem[3+j*4];
			l++;
			bitmap[l] = mem[2+j*4];
			l++;
			bitmap[l] = mem[1+j*4];
			l++;
		}
		for(j=0; j<pad; j++) {
			bitmap[l] = 0; 
			l++;
		}
	}
	free(mem);

print_head("Writing bitmap data...");
	prog_bar1_value = 0;
	int write = 0;
	while(write < l) {
		int wrlen = 1024;
		if(write+wrlen > l) wrlen = l-write;
		fwrite(bitmap+write, wrlen, 1, f);
		write += wrlen;
		prog_bar1_value = (write*100) / l;
	}
	prog_bar1_value = -1;
	
	fclose(f);
	
	SetFilePerms(ScreenShotPath);
	
	free(bitmap);
	
	//end_loading();
}

//*******************************************************
// TEST ZONE
//*******************************************************

//  https://www.imagemagick.org/api/magick-image.php

void ConvertImage(char *file_in, char *file_out)
{
	MagickWandGenesis();
	
	MagickWand *mw = NULL;
	/* Create a wand */
	mw = NewMagickWand();
	/* Read the input image */
	if( MagickReadImage(mw, file_in) == MagickFalse ) {
		print_load("Error : failed to read file_in");
		return;
	}
	
	MagickSetImageType(mw, TrueColorAlphaType); // type 6
	
	/* write it */
	if( MagickWriteImage(mw, file_out) == MagickFalse ) {
		print_load("Error : failed to write file_out");
		return;
	}
	/* Tidy up */
	if(mw) mw = DestroyMagickWand(mw);
	MagickWandTerminus();
}

void Crop_Image(char *file_in, char *file_out, float x, float y, float w, float h)
{
	MagickWandGenesis();
	
	MagickWand *mw = NULL;
	/* Create a wand */
	mw = NewMagickWand();
	/* Read the input image */
	if( MagickReadImage(mw, file_in) == MagickFalse ) {
		print_load("Error : failed to read %s", file_in);
		return;
	}
	
	if( MagickCropImage(mw, w, h, x, y) == MagickFalse ) {
		print_load("Error : failed to crop");
		return;
	}
	
	/* write it */
	if( MagickWriteImage(mw, file_out) == MagickFalse ) {
		print_load("Error : failed to write %s", file_out);
		return;
	}
	/* Tidy up */
	if(mw) mw = DestroyMagickWand(mw);
	MagickWandTerminus();
}
/*
#include "dds_reader.h"

typedef struct
{
	void *bmp_out;

	u32 pitch;
	u32 width;
	u32 height;
} ddsData;

void ddsLoadFromFile(char *path, ddsData *data)
{

	FILE* file = fopen(path, "rb");
	if(file) {
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		fseek(file, 0, SEEK_SET);

		unsigned char *buffer = (unsigned char *)malloc(size);
		fread(buffer, 1, size, file);
		fclose(file);

		int width = ddsGetWidth(buffer);
		int height = ddsGetHeight(buffer);
		int mipmap = ddsGetMipmap(buffer);
		
		if(mipmap > 0) {
			// mipmap
			int i;
			for(i=0; (width > 0) || (height > 0); i++) {
				if(width <= 0) width = 1;
				if(height <= 0) height = 1;
				data->bmp_out = ddsRead(buffer, DDS_READER_ABGR, i);
			}
		}
		else data->bmp_out = ddsRead(buffer, DDS_READER_ABGR, 0);

  		data->width = width;
		data->height = height;
		data->pitch = width*4;
		
		free(buffer);
	}
}
*/

void Load_FM()
{
	if(Load_GamePIC) return;
	
	u8 loaded=NO;
	
	if(loading == NO) {
		loaded=YES;
		start_loading();
	}

#ifdef FILEMANAGER
	texture_pointer = texture_mem + TEXTURE_POINTER_GAMEPIC;
#else
	texture_pointer = texture_temp;
#endif

	memset(&TMP_PIC, 0, sizeof(TMP_PIC));
	TMP_PIC_offset = 0;
	
	if(is_apng(TMP_PIC_path) == YES) {
		Load_APNG(TMP_PIC_path);
		if(loaded == YES) end_loading();
		return;
	}
	
	LoadTexture(TMP_PIC_path, &TMP_PIC_offset ,&TMP_PIC);
	
	if(loaded == YES) end_loading();
}

void Read_COVER3D(int position)
{
	char temp[128];
	char title_id[20];
	
	if(Get_ID(list_game_path[position], list_game_platform[position], title_id) == FAILED) {
		print_load("Error: Read_COVER3D : Get_ID %s", list_game_path[position]);
		return;
	}

	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/3D/%s.JPG", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/3D/%s.jpg", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/3D/%s.PNG", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/3D/%s.png", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	
	return;
read:

	if( imgLoadFromFile(temp, &COVER3D[position]) == 0) return;
	
}

void Read_COVER(int position)
{
	char temp[128];
	char title_id[20];
	
	if(Get_ID(list_game_path[position], list_game_platform[position], title_id) == FAILED) {
		print_load("Error: Read_COVER : Get_ID %s", list_game_path[position]);
		return;
	}
	
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/%s.JPG", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/%s.jpg", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/%s.PNG", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/%s.png", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	
	sprintf(temp, "/dev_hdd0/tmp/covers/%s.JPG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/tmp/covers/%s.jpg", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/tmp/covers/%s.PNG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/tmp/covers/%s.png", title_id);
	if(path_info(temp) == _FILE) goto read;
	
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers/%s.JPG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers/%s.jpg", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers/%s.PNG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers/%s.png", title_id);
	if(path_info(temp) == _FILE) goto read;
	
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers_retro/psx/%s_COV.JPG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers_retro/psx/%s_COV.jpg", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers_retro/psx/%s_COV.PNG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers_retro/psx/%s_COV.png", title_id);
	if(path_info(temp) == _FILE) goto read;
	
	return;
read:

	if( imgLoadFromFile(temp, &COVER[position]) == 0) return;
	
	//Delete(temp);
}

void Load_ICON0()
{
	int i;
	
	Load_GamePIC_progbar = 0;

	for(i=0; i<=game_number; i++) {
		Load_GamePIC_progbar = (i*100)/game_number;
		
		if(Load_GamePIC==NO) return;
		
		Read_ICON0(i);
		
		if(Load_GamePIC==NO) return;
		
		if(ICON0[i].bmp_out) {
			memcpy(texture_pointer, ICON0[i].bmp_out, ICON0[i].pitch * ICON0[i].height);
			free(ICON0[i].bmp_out);
			ICON0_offset[i] = tiny3d_TextureOffset(texture_pointer);
			texture_pointer += ((ICON0[i].pitch * ICON0[i].height + 15) & ~15) / 4;
		} else ICON0_offset[i]=0;
	}
	
	Load_GamePIC_progbar = -1;
}

u8 COVER_Loaded;
void Load_COVER() 
{	
	int i;
	
	if(Load_GamePIC==NO) return;
	
	COVER_Loaded = NO;
	
	if(Show_COVER==YES || (UI_position==FLOW && FLOW_3D==YES) ) {
		Load_GamePIC_progbar=0;
		for(i=0; i<=game_number; i++) {
			Load_GamePIC_progbar = (i*100)/game_number;
			if(Load_GamePIC==NO) return;
			Read_COVER(i);
			if(Load_GamePIC==NO) return;
			if(COVER[i].bmp_out) {
				memcpy(texture_pointer, COVER[i].bmp_out, COVER[i].pitch * COVER[i].height);
				free(COVER[i].bmp_out);
				COVER_offset[i] = tiny3d_TextureOffset(texture_pointer);
				texture_pointer += ((COVER[i].pitch * COVER[i].height + 15) & ~15) / 4;
			} else COVER_offset[i] = 0;
		}
		if(UI_position==FLOW && FLOW_3D==YES) {
			Load_GamePIC_progbar=0;
			for(i=0; i<=game_number; i++) {
				Load_GamePIC_progbar = (i*100)/game_number;
				if(Load_GamePIC==NO) return;
				Read_COVER3D(i);
				if(Load_GamePIC==NO) return;
				if(COVER3D[i].bmp_out) {
					memcpy(texture_pointer, COVER3D[i].bmp_out, COVER3D[i].pitch * COVER3D[i].height);
					free(COVER3D[i].bmp_out);
					COVER3D_offset[i] = tiny3d_TextureOffset(texture_pointer);
					texture_pointer += ((COVER3D[i].pitch * COVER3D[i].height + 15) & ~15) / 4;
				} else COVER3D_offset[i] = 0;
			}
		}
		COVER_Loaded = YES;
	}
	Load_GamePIC_progbar = -1;
}

static sys_ppu_thread_t Load_GamePIC_id;

void Load_GamePIC_thread(void *unused)
{
	memset(ICON0_offset, 0, sizeof(ICON0_offset));
	memset(ICON0, 0, sizeof(ICON0));
	memset(COVER_offset, 0, sizeof(COVER_offset));
	memset(COVER, 0, sizeof(COVER));
	memset(COVER3D_offset, 0, sizeof(COVER3D_offset));
	memset(COVER3D, 0, sizeof(COVER3D));
	TMP_PIC_offset = 0;
	
	texture_pointer = texture_mem + TEXTURE_POINTER_GAMEPIC;
	
	Load_ICON0();
	Load_COVER();
	
	while(Load_GamePIC == YES) usleep(100);
	
	texture_temp = texture_pointer;
	
	sysThreadExit(0);
}

void end_Load_GamePIC()
{
	u64 ret;
	Load_GamePIC = NO;
	sysThreadJoin(Load_GamePIC_id, &ret);
}

void start_Load_GamePIC()
{	
	if(Load_GamePIC==YES) {
		end_Load_GamePIC();
	}
	if(Load_GamePIC==NO) {
		Load_GamePIC = YES;
		sysThreadCreate(&Load_GamePIC_id, Load_GamePIC_thread, NULL, 999, 0x2000, THREAD_JOINABLE, "Load_GamePIC");
	}
}

void Draw_Load_GamePIC()
{
	if(Load_GamePIC == NO) return;
		
	if(Load_GamePIC_progbar >= 0) Draw_Progress_Bar(50, 15, 1, Load_GamePIC_progbar, COLOR_2);
	
	if(Load_GamePIC_progbar == -1) end_Load_GamePIC();
	
}

void Draw_CASE(int pos, float xi, float yi, float z, float wi, float hi)
{
	float xj,yj,wj,hj;
	float xl,yl,wl,hl;
	
	if(list_game_platform[pos] == _ISO_PS3 || list_game_platform[pos] == _JB_PS3) {
		if(PICTURE_offset[PS3_CASE] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[PS3_CASE], PICTURE[PS3_CASE].width, PICTURE[PS3_CASE].height, PICTURE[PS3_CASE].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			xl = 0;
			yl = 30;
			wl = 260;
			hl = 300;
			
			xj = xi - xl * wi / wl;
			yj = yi - yl * hi / hl;
			wj = PICTURE[PS3_CASE].width * wi / wl;
			hj = PICTURE[PS3_CASE].height * hi / hl;
							
			Draw_Box(xj, yj, z, 0, wj, hj, WHITE, YES);
		}
	} else
	if(list_game_platform[pos] == _ISO_PS2 || list_game_platform[pos] == _JB_PS2) {
		if(PICTURE_offset[PS2_CASE] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[PS2_CASE], PICTURE[PS2_CASE].width, PICTURE[PS2_CASE].height, PICTURE[PS2_CASE].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			xl = 0;
			yl = 10;
			wl = 260;
			hl = 370;
			
			xj = xi - xl * wi / wl;
			yj = yi - yl * hi / hl;
			wj = PICTURE[PS2_CASE].width * wi / wl;
			hj = PICTURE[PS2_CASE].height * hi / hl;
							
			Draw_Box(xj, yj, z, 0, wj, hj, WHITE, YES);
		}
	} else
	if(list_game_platform[pos] == _ISO_PS1 || list_game_platform[pos] == _JB_PS1) {
		if(PICTURE_offset[PS1_CASE] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[PS1_CASE], PICTURE[PS1_CASE].width, PICTURE[PS1_CASE].height, PICTURE[PS1_CASE].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			xl = 30;
			yl = 5;
			wl = 240;
			hl = 240;
			
			xj = xi - xl * wi / wl;
			yj = yi - yl * hi / hl;
			wj = PICTURE[PS1_CASE].width * wi / wl;
			hj = PICTURE[PS1_CASE].height * hi / hl;
							
			Draw_Box(xj, yj, z, 0, wj, hj, WHITE, YES);
		}
	} else
	if(list_game_platform[pos] == _ISO_PSP || list_game_platform[pos] == _JB_PSP) {
		if(PICTURE_offset[PSP_CASE] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[PSP_CASE], PICTURE[PSP_CASE].width, PICTURE[PSP_CASE].height, PICTURE[PSP_CASE].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			xl = 0;
			yl = 10;
			wl = 200;
			hl = 340;
			
			xj = xi - xl * wi / wl;
			yj = yi - yl * hi / hl;
			wj = PICTURE[PSP_CASE].width * wi / wl;
			hj = PICTURE[PSP_CASE].height * hi / hl;
							
			Draw_Box(xj, yj, z, 0, wj, hj, WHITE, YES);
		}
	}
	
}

void Draw_COVER(int pos, float x , float y, float z, float w, float h)
{
	if(pos < 0 || game_number < pos) return;
	
	if(COVER_offset[pos] != 0) {
		float xi,yi,wi,hi;
		
		tiny3d_SetTexture(0, COVER_offset[pos], COVER[pos].width, COVER[pos].height, COVER[pos].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if(h==0 && w!=0) {
			xi = x;
			yi = y;
			wi = w;
			hi = COVER[pos].height * w / COVER[pos].width;
		} else 
		if(h!=0 && w==0) {
			xi = x;
			yi = y;
			wi = COVER[pos].width * h / COVER[pos].height;
			hi = h;
		} else
		if(h==0 && w==0) {
			xi = x;
			yi = y;
			wi = COVER[pos].width;
			hi = COVER[pos].height;
		} else {
			xi = x;
			yi = y;
			wi = w;
			hi = h;
		}
		Draw_Box(xi, yi, z, 0, wi, hi, WHITE, YES);
		
		if(Show_GameCase==YES) Draw_CASE(pos, xi, yi, z, wi, hi);
	}
}

void Draw_CoverCaseFromCenter(int pos, float x, float y, float z, float w, float h)
{
	float xi,yi,wi,hi;
	float xj,yj,wj,hj;
	float xl,yl,wl,hl;
	u8 plat;
	
	if(list_game_platform[pos] == _ISO_PS3 || list_game_platform[pos] == _JB_PS3) {
		plat = PS3_CASE;
		xl = 0;
		yl = 30;
		wl = 260;
		hl = 300;
	} else
	if(list_game_platform[pos] == _ISO_PS2 || list_game_platform[pos] == _JB_PS2) {
		plat = PS2_CASE;
		xl = 0;
		yl = 10;
		wl = 260;
		hl = 370;
	}else
	if(list_game_platform[pos] == _ISO_PS1 || list_game_platform[pos] == _JB_PS1) {
		plat = PS1_CASE;
		xl = 30;
		yl = 5;
		wl = 240;
		hl = 240;
	} else
	if(list_game_platform[pos] == _ISO_PSP || list_game_platform[pos] == _JB_PSP) {
		plat = PSP_CASE;
		xl = 0;
		yl = 10;
		wl = 200;
		hl = 340;
	} else return;
	
	if(PICTURE_offset[plat] != 0 && COVER_offset[pos] != 0) {
		
		if(h==0 && w!=0) {
			xi = x-w/2;
			yi = y-(PICTURE[plat].height*w/PICTURE[plat].width) / 2 ;
			wi = w;
			hi = PICTURE[plat].height*w/PICTURE[plat].width;
		} else
		if(h!=0 && w==0) {
			xi = x-(PICTURE[plat].width*h/PICTURE[plat].height)/2;
			yi = y-h/2;
			wi = PICTURE[plat].width*h/PICTURE[plat].height;
			hi = h;
		} else
		if(h==0 && w==0) {
			xi = x-PICTURE[plat].width/2;
			yi = y-PICTURE[plat].height/2;
			wi = PICTURE[plat].width;
			hi = PICTURE[plat].height;
		} else {
			xi = x-w/2;
			yi = y-h/2;
			wi = w;
			hi = h;
		}
		
		
		xj = xi + xl * wi / PICTURE[plat].width;
		yj = yi + yl * hi / PICTURE[plat].height;
		
		wj = wl * wi / PICTURE[plat].width;
		hj = hl * hi / PICTURE[plat].height;
		
		tiny3d_SetTexture(0, COVER_offset[pos], COVER[pos].width, COVER[pos].height, COVER[pos].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(xj, yj, z+1, 0, wj, hj, WHITE, YES);
		
		tiny3d_SetTexture(0, PICTURE_offset[plat], PICTURE[plat].width, PICTURE[plat].height, PICTURE[plat].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(xi, yi, z, 0, wi, hi, WHITE, YES);
	}
}

void Draw_CoverFromCenter(int pos, float x, float y, float z, float w, float h)
{
	if(pos < 0 || game_number < pos) return;
	
	if(Show_GameCase==YES) {
		Draw_CoverCaseFromCenter(pos, x, y, z, w, h);
		return;
	}
	
	if(COVER_offset[pos] != 0) {
		
		float xi,yi,wi,hi;
		
		tiny3d_SetTexture(0, COVER_offset[pos], COVER[pos].width, COVER[pos].height, COVER[pos].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if(h==0 && w!=0) {
			xi = x-w/2;
			yi = y-(COVER[pos].height*w/COVER[pos].width) / 2 ;
			wi = w;
			hi = COVER[pos].height*w/COVER[pos].width;
		}
		else if(h!=0 && w==0) {
			xi = x-(COVER[pos].width*h/COVER[pos].height)/2;
			yi = y-h/2;
			wi = COVER[pos].width * h / COVER[pos].height;
			hi = h;
		}
		else if(h==0 && w==0) {
			xi = x-COVER[pos].width/2;
			yi = y-COVER[pos].height/2;
			wi = COVER[pos].width;
			hi = COVER[pos].height;
		} else {
			xi = x-w/2;
			yi = y-h/2;
			wi = w;
			hi = h;
		}
		Draw_Box(xi, yi, z, 0, wi, hi, WHITE, YES);
		
		if(Show_GameCase==YES) Draw_CASE(pos, xi, yi, z, wi, hi);
	}
}

u8 get_SectorSize(FILE*  fd, u32 *SectorSize, u32 *jmp)
{
	char CD01[8] = {0x01, 0x43, 0x44, 0x30, 0x30, 0x31, 0x01, 0x00};
	
	u32 all_sizes[4] = {0x800, 0x930, 0x920, 0x990};
	u32 sector_size=0;
	u32 jp=0;
	char *data = (char *) malloc(9);
	
	int i;
	for(i=0; i<4; i++) {
		memset(data, 0, sizeof(data));
		fseek(fd, all_sizes[i]*0x10, SEEK_SET);
		fread(data, 8, 1, fd);
		if(!memcmp((char *) data, (char *) CD01, 8)) {
			sector_size=all_sizes[i];
			jp=0;
			break;
		}
		fseek(fd, all_sizes[i]*0x10+0x18, SEEK_SET);
		fread(data, 8, 1, fd);
		if(!memcmp((char *) data, (char *) CD01, 8)) {
			sector_size=all_sizes[i];
			jp=0x18;
			break;
		}
	}
	free(data);
	
	if(sector_size==0) return FAILED;
	
	*SectorSize = sector_size;
	*jmp = jp;
	
	return SUCCESS;
	
}

u8 get_FileOffset(FILE* fd, char *path, u64 *FileOffset, u32 *FileSize)
{
	u32 root_table = 0;
	u32 SectSize=0;
	u32 JP=0;
	
	if( get_SectorSize(fd, &SectSize, &JP) == FAILED) return FAILED;
	
	fseek(fd, SectSize*0x10+0xA2+JP, SEEK_SET);
	
	fread(&root_table, sizeof(u32), 1, fd);
	if(root_table == 0) return FAILED;
	
	fseek(fd, SectSize*root_table, SEEK_SET);
	
	char *sector = (char *) malloc(SectSize);
	if(sector == NULL) {
		print_load("Error : get_FileOffset : malloc");
		return FAILED;
	}
	
	int i;
	int k=0;
	int len = strlen(path);
	char item_name[255];
	for(i=0; i <= len; i++) {
		if(i==0 && path[0] == '/') continue;
		
		if(path[i] == '/' || i==len) {
			strncpy(item_name, path+i-k, k);
			memset(sector, 0, sizeof(sector));
			u32 offset=0;
			fread(sector, 1, SectSize, fd);
			int j;
			for(j=0; j<SectSize; j++) {
				if(strncmpi((char *) &sector[j], (char *) item_name , k)==0) {
					if(i==len) {
						memcpy(&offset, &sector[j-0x1B], 4);
						*FileOffset = (u64)offset*(u64)SectSize+(u64)JP;
						u32 size=0;
						memcpy(&size, &sector[j-0x13], 4);
						*FileSize = size;
						free(sector);
						return SUCCESS;
					}
					memcpy(&offset, &sector[j-0x1B], 4);
					fseek(fd, SectSize*offset, SEEK_SET);
				
					break;
				}
			}
			
			if(offset == 0) {
				free(sector);
				return FAILED;
			}
			memset(item_name, 0, sizeof(item_name));
			k=0;
		}
		else k++;
	}
	
	free(sector);
	return FAILED;
}

u8 ExtractFromISO(char *isopath, char *filename, char *output)
{
	int size;
	char *mem = LoadFileFromISO(NO, isopath, filename, &size);
	if(mem==NULL) return FAILED;

	if( SaveFile(output, mem, size) == FAILED) {
		free(mem);
		return FAILED;
	}
	
	free(mem);
	return SUCCESS;
}

void Extract_IconParam()
{
	char ICON_OUT[128];
	char PARAM_OUT[128];
	char ICON_IN[128];
	char PARAM_IN[128];
	int i;
	for(i=0; i<=game_number; i++) {
		if(list_game_platform[i] != _ISO_PS3 && list_game_platform[i] != _ISO_PSP) continue;
		
		if(list_game_platform[i] == _ISO_PS3) {
			strcpy(ICON_IN, "/PS3_GAME/ICON0.PNG");
			strcpy(PARAM_IN, "/PS3_GAME/PARAM.SFO");
		}
		else
		if(list_game_platform[i] == _ISO_PSP) {
			strcpy(ICON_IN, "/PSP_GAME/ICON0.PNG");
			strcpy(PARAM_IN, "/PSP_GAME/PARAM.SFO");
		}
		
		strcpy(ICON_OUT, list_game_path[i]);
		RemoveExtention(ICON_OUT);
		strcat(ICON_OUT, ".PNG");
		strcpy(PARAM_OUT, list_game_path[i]);
		RemoveExtention(PARAM_OUT);
		strcat(PARAM_OUT, ".SFO");
		
		if(path_info(ICON_OUT)==_NOT_EXIST) {
			ExtractFromISO(list_game_path[i], ICON_IN, ICON_OUT);
		}
		if(path_info(PARAM_OUT)==_NOT_EXIST) {
			if(ExtractFromISO(list_game_path[i], PARAM_IN, PARAM_OUT) == SUCCESS) {
				if(GetParamSFO("TITLE", list_game_title[i], i, NULL)==FAILED) {
					strcpy(list_game_title[i], list_game_path[i]);
					strcpy(list_game_title[i], &strrchr(list_game_title[i], '/')[1]);
					RemoveExtention(list_game_title[i]);
				}
			}
		}
	}
}

void Draw_DEFAULT(int pos, float x , float y, float z,  float w, float h)
{
	if(pos < 0 || game_number < pos) return;
	
	int type = list_game_platform[pos];
	if(type == _JB_PS1 || type == _JB_PS2 || type == _JB_PS3 || type == _JB_PSP) {
		if(PICTURE_offset[DEFAULT_JB] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[DEFAULT_JB], PICTURE[DEFAULT_JB].width, PICTURE[DEFAULT_JB].height, PICTURE[DEFAULT_JB].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			Draw_Box(x, y, z, 0, w, h, WHITE, YES);
		}
	} else
	if(type == _ISO_PS1 || type == _ISO_PS2 || type == _ISO_PS3 || type == _ISO_PSP) {
		if(PICTURE_offset[DEFAULT_ISO] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[DEFAULT_ISO], PICTURE[DEFAULT_ISO].width, PICTURE[DEFAULT_ISO].height, PICTURE[DEFAULT_ISO].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			Draw_Box(x, y, z, 0, w, h, WHITE, YES);
		}
	} else {
		if(PICTURE_offset[DEFAULT] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[DEFAULT], PICTURE[DEFAULT].width, PICTURE[DEFAULT].height, PICTURE[DEFAULT].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
			Draw_Box(x, y, z, 0, w, h, WHITE, YES);
		}		
	}
	
	if(type == _JB_PS1 || type == _ISO_PS1) Draw_Box(x, y, z, 0, w, h, COLOR_PS1 - 0x90, NO);
	if(type == _JB_PS2 || type == _ISO_PS2) Draw_Box(x, y, z, 0, w, h, COLOR_PS2 - 0x90, NO);
	if(type == _JB_PS3 || type == _ISO_PS3) Draw_Box(x, y, z, 0, w, h, COLOR_PS3 - 0x90, NO);
	if(type == _JB_PSP || type == _ISO_PSP) Draw_Box(x, y, z, 0, w, h, COLOR_PSP - 0x90, NO);
	
}

void Draw_ICON0(int pos, float x, float y, float z,  float w, float h)
{
	if(pos < 0 || game_number < pos) return;
	
	if(ICON0_offset[pos] != 0) {
		tiny3d_SetTexture(0, ICON0_offset[pos], ICON0[pos].width, ICON0[pos].height, ICON0[pos].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if(ICON0[pos].height >= ICON0[pos].width) {
			float w1= ICON0[pos].width * h / ICON0[pos].height;
			float x1 = x + (w-w1)/2;
			Draw_Box(x1, y, z, 0, w1, h, WHITE, YES);
		} else Draw_Box(x, y, z, 0, w, h, WHITE, YES);
		
	}
	else Draw_DEFAULT(pos, x, y, z, w, h);
	
}

void DrawFromCenter_ICON0(int pos, float x, float y, float z,  float w, float h)
{
	Draw_ICON0(pos, x-w/2, y-h/2, z, w, h);
}

void Draw_MMTHM_XMB(float x , float y, float z, float w, float h,  u8 n_icon)
{
	
	if(n_icon<24) {
		if(XMB_MMTHM_XMB_offset != 0) {
			
			float local_y = y + h*n_icon;
			float tot_h = h*24;
			
			tiny3d_SetTextureWrap(0, XMB_MMTHM_XMB_offset, XMB_MMTHM_XMB.width, XMB_MMTHM_XMB.height, XMB_MMTHM_XMB.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTWRAP_CLAMP, TEXTWRAP_CLAMP, TEXTURE_LINEAR);
			
			tiny3d_SetPolygon(TINY3D_QUADS);

			tiny3d_VertexPos(x	 , y-local_y , z);
			tiny3d_VertexColor(0xFFFFFF00);
			tiny3d_VertexTexture(0.0f, 0.0f);

			tiny3d_VertexPos(x + w, y-local_y  , z);
			tiny3d_VertexTexture(1.0f, 0.0f);

			tiny3d_VertexPos(x + w, y-local_y+tot_h, z);
			tiny3d_VertexTexture(1.0f, 1.0f);

			tiny3d_VertexPos(x	, y-local_y+tot_h, z);
			tiny3d_VertexTexture(0.0f, 1.0f);

			tiny3d_End();
			
			tiny3d_SetPolygon(TINY3D_QUADS);

			tiny3d_VertexPos(x	 , y , z);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexTexture(0.0f, (local_y-y)/tot_h);

			tiny3d_VertexPos(x + w, y  , z);
			tiny3d_VertexTexture(1.0f, (local_y-y)/tot_h);

			tiny3d_VertexPos(x + w, y+h, z);
			tiny3d_VertexTexture(1.0f, (local_y-y+h)/tot_h);

			tiny3d_VertexPos(x	, y+h, z);
			tiny3d_VertexTexture(0.0f, (local_y-y+h)/tot_h);

			tiny3d_End();
			
		}
	}
	else if(n_icon < 35) {
		if(XMB_MMTHM_XMB2_offset != 0) {
			
			float local_y = y + h*(n_icon-24);
			float tot_h = h*24;
			
			tiny3d_SetTextureWrap(0, XMB_MMTHM_XMB2_offset, XMB_MMTHM_XMB2.width, XMB_MMTHM_XMB2.height, XMB_MMTHM_XMB2.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTWRAP_CLAMP, TEXTWRAP_CLAMP, TEXTURE_LINEAR);
			
			tiny3d_SetPolygon(TINY3D_QUADS);

			tiny3d_VertexPos(x	 , y-local_y , z);
			tiny3d_VertexColor(0xFFFFFF00);
			tiny3d_VertexTexture(0.0f, 0.0f);

			tiny3d_VertexPos(x + w, y-local_y  , z);
			tiny3d_VertexTexture(1.0f, 0.0f);

			tiny3d_VertexPos(x + w, y-local_y+tot_h, z);
			tiny3d_VertexTexture(1.0f, 1.0f);

			tiny3d_VertexPos(x	, y-local_y+tot_h, z);
			tiny3d_VertexTexture(0.0f, 1.0f);

			tiny3d_End();
			
			tiny3d_SetPolygon(TINY3D_QUADS);

			tiny3d_VertexPos(x	 , y , z);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexTexture(0.0f, (local_y-y)/tot_h);

			tiny3d_VertexPos(x + w, y  , z);
			tiny3d_VertexTexture(1.0f, (local_y-y)/tot_h);

			tiny3d_VertexPos(x + w, y+h, z);
			tiny3d_VertexTexture(1.0f, (local_y-y+h)/tot_h);

			tiny3d_VertexPos(x	, y+h, z);
			tiny3d_VertexTexture(0.0f, (local_y-y+h)/tot_h);

			tiny3d_End();
			
		}
	}
}

//*******************************************************
// APNG
//*******************************************************

#define MAGIC_PNG 0x89504E470D0A1A0A

#define IHDR 0x49484452
#define acTL 0x6163544C
#define fcTL 0x6663544C 
#define IDAT 0x49444154
#define fdAT 0x66644154
#define IEND 0x49454E44

typedef struct 
{
	u32 length;
	u32 type;
} chunk_header;

typedef struct 
{
	u32 width;
	u32 height;
	u8 depth;
	u8 color_type;
	u8 compression;
	u8 filter;
	u8 interlace;
} IHDR_data;

typedef struct
{
	u64 magic;
	chunk_header chunk_IHDR;
	IHDR_data data_IHDR;
	u32 IHDR_CRC;
	chunk_header chunk_IDAT;
} frame_header;

typedef struct 
{
	u32 num_frames;
	u32 num_plays;
} acTL_data;

typedef struct 
{
	u32 sequence_number;	// Sequence number of the animation chunk, starting from 0
	u32 width;				// Width of the following frame
	u32 height;				// Height of the following frame
	u32 x_offset;			// X position at which to render the following frame
	u32 y_offset;			// Y position at which to render the following frame
	u16 delay_num;			// Frame delay fraction numerator
	u16 delay_den;			// Frame delay fraction denominator
	u8 dispose_op;			// Type of frame area disposal to be done after rendering this frame
	u8 blend_op;			// Type of frame area rendering for this frame
} fcTL_data;		 

enum {
   APNG_DISPOSE_OP_NONE	   = 0,
   APNG_DISPOSE_OP_BACKGROUND = 1,
   APNG_DISPOSE_OP_PREVIOUS   = 2,
};

enum {
	APNG_BLEND_OP_SOURCE = 0,
	APNG_BLEND_OP_OVER   = 1,
};

u32 APNG_num_frames;
pngData APNG[MAX_FRAME];
fcTL_data APNG_data[MAX_FRAME];
u32 APNG_offset[MAX_FRAME];
u32 APNG_frame=0;

fcTL_data BG_data[MAX_FRAME];
u32 BG_frame=0;
u32 BG_num_frames;

static u64 time_s[5]={0};
static u64 time_e[5]={0};
static u64 time_n_s[5]={0};
static u64 time_n_e[5]={0};

void start_timer(u8 i)
{
	sysGetCurrentTime(&time_s[i], &time_n_s[i]);
}

u64 get_time(u8 i)
{
	sysGetCurrentTime(&time_e[i], &time_n_e[i]);
	return (((1000000000*time_e[i] + time_n_e[i]) - (1000000000*time_s[i] + time_n_s[i]))/1000000.0);
}

void init_timer(u8 i)
{
	time_s[i]=0;
	time_e[i]=0;
	time_n_s[i]=0;
	time_n_e[i]=0;
}
			
u8 is_apng(char *file)
{
	FILE* f;
	u64 magic;
	chunk_header ch;
	u64 pos=0;
	
	memset(APNG_data, 0, sizeof(APNG_data));
	memset(APNG, 0, sizeof(APNG));
	memset(APNG_offset, 0, sizeof(APNG_offset));
	APNG_num_frames = 0;
	
	f=fopen(file, "rb");
	if(f==NULL) return NO;
	
	fread(&magic, 1, 8, f);
	
	if(magic != MAGIC_PNG) { 
		//print_load("Error : Magic number is not correct");
		fclose(f); return NO;
	}

	fread(&ch, 1, 8, f); 
	
	if(ch.type != IHDR) {
		//print_load("Error : ch.type != IHDR");
		fclose(f); return NO;
	}

	do { // loop to ignore unknown chunk
		pos = ftell(f) + ch.length + 4; // length of chunk_data + CRC
		
		fseek(f, pos, SEEK_SET);
		fread(&ch, 1, 8, f);
		
		if(ch.type == acTL) {
			fclose(f); 
			return YES;
		}
		
	} while (ch.type != IDAT);
	
	fclose(f);
	
	return NO;
}

u8 Load_APNG(char* filename)
{
	FILE* f;
	u64 magic;
	u32 pos;
	chunk_header ch;
	
	u8 IEND_[0xC] = {0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82};
	
	u8 Frame_Header[0x29];
	acTL_data ad;

	texture_pointer = texture_temp;	
	
	memset(APNG_data, 0, sizeof(APNG_data));
	memset(APNG, 0, sizeof(APNG));
	memset(APNG_offset, 0, sizeof(APNG_offset));
	APNG_num_frames = 0;
	
	f = fopen(filename, "rb");

	if(f==NULL) {
		//print_load("Error :  failed to open file");
		return NO;
	}
	
	fread(&magic, 1, 8, f);
	
	if(magic != MAGIC_PNG) { 
		//print_load("Error :  bad magic"); 
		fclose(f); return NO;
	}
	
	fseek(f, 0, SEEK_SET);
	fread(&Frame_Header, 1, 0x21, f);
	
	fread(&ch, 1, 8, f);
		
	while (ch.type != acTL)  
	{
		pos = ftell(f) + ch.length + 4; // ignore CRC
		fseek(f, pos, SEEK_SET);
		fread(&ch, 1, 8, f);
		
		if(ch.type == IDAT) {
			//print_load("Error : no actl");
			fclose(f);
			return NO;
		} // not GRID_ANIMATED
	}
	

	fread(&ad, 1, ch.length, f);
	
	APNG_num_frames = ad.num_frames;

	pos = ftell(f) + 4; // ignore CRC
	fseek(f, pos, SEEK_SET);
	u32 i;
	
	for(i=0; i<ad.num_frames; i++) {
		fread(&ch, 1, 8, f);
		
		while (ch.type != fcTL)
		{
			pos = ftell(f) + ch.length + 4; // ignore CRC
			fseek(f, pos, SEEK_SET);
			fread(&ch, 1, 8, f);
		}
		fread(&APNG_data[i], 1, ch.length, f);
		
		*(u32 *) &Frame_Header[0x10] = APNG_data[i].width;
		*(u32 *) &Frame_Header[0x14] = APNG_data[i].height;
		*(u32 *) &Frame_Header[0x25] = IDAT;
		
		pos = ftell(f) + 4; // ignore CRC
		fseek(f, pos, SEEK_SET);
		
		fread(&ch, 1, 8, f);
		
		while (ch.type != IDAT && ch.type != fdAT)
		{	
			pos = ftell(f) + ch.length + 4; // ignore CRC
			fseek(f, pos, SEEK_SET);
			fread(&ch, 1, 8, f);
		}
		
		u32 n_AT=0;
		u32 tot_size=0;
		u32 chunk_size[1024]={0};
		u32 first_pos = ftell(f) - 8;
		
	next:
		if(ch.type == IDAT) {
			tot_size+=ch.length;
			chunk_size[n_AT]=ch.length;
			n_AT++;
			
			pos = ftell(f) + ch.length + 4; // ignore CRC 
			fseek(f, pos, SEEK_SET);
			fread(&ch, 1, 8, f);
			
			goto next;
		} else 
		if(ch.type == fdAT) {
			tot_size+=ch.length - 4; // ignore sequence
			chunk_size[n_AT]=ch.length - 4;
			n_AT++;
			
			pos = ftell(f) + ch.length + 4; // ignore CRC
			fseek(f, pos, SEEK_SET);
			fread(&ch, 1, 8, f);
			
			goto next;
		} else {
			fseek(f, first_pos, SEEK_SET); 
			fread(&ch, 1, 8, f);
		}
		
		*(u32 *) &Frame_Header[0x21] = tot_size;
		
		u32 ihdr_crc = crc32(0L, Z_NULL, 0);
		ihdr_crc = crc32(ihdr_crc, (const unsigned char*)Frame_Header+0xC, 0x11);
		memcpy(Frame_Header+0x1D, &ihdr_crc, 4);
		
		u8 *frame = (u8 *) malloc(0x29 + tot_size + 4 + 0xC);
		if(frame==NULL) {
			//print_load("Error : failed to malloc");
			return NO;
		}
		
		memcpy(frame, &Frame_Header, 0x29);
		
		u32 j, cur_size=0;
		for(j=0; j<n_AT; j++) {
			if(ch.type == IDAT) {
				fread(frame + 0x29 + cur_size, 1, chunk_size[j], f);
				pos = ftell(f) + 4; // ignore CRC
				fseek(f, pos, SEEK_SET);
				fread(&ch, 1, 8, f);
			} else
			if(ch.type == fdAT) {
				pos = ftell(f) + 4; // ignore sequence_number
				fseek(f, pos, SEEK_SET);
				fread(frame + 0x29 + cur_size, 1, chunk_size[j], f);
				pos = ftell(f) + 4; // ignore CRC
				fseek(f, pos, SEEK_SET);
				fread(&ch, 1, 8, f);
			}
			cur_size+=chunk_size[j];
		}
		pos = ftell(f) - 8;
		fseek(f, pos, SEEK_SET);
		
		
		u32 crc = crc32(0L, Z_NULL, 0);
		crc = crc32(crc, (const unsigned char*)frame+0x25, 4 + tot_size);
		memcpy(frame+0x29+tot_size, &crc, 4);
		
		memcpy(frame+0x29+tot_size+4, IEND_, 0xC);
		
		//FILE* x;
		//char frame_path[128];
		//mkdir("/dev_hdd0/frames", 0777);
		//sprintf(frame_path, "/dev_hdd0/frames/frame_%d.png", i);
		//x = fopen(frame_path, "wb");
		//fwrite(frame, 1, 0x29 + tot_size + 4 + 0xC, x);
		//fclose(x);
		
		pngLoadFromBuffer((const void *) frame, 0x29 + tot_size + 4 + 0xC, &APNG[i]);
		
		free(frame);
		
		if(APNG[i].bmp_out) {
			memcpy(texture_pointer, APNG[i].bmp_out, APNG[i].pitch * APNG[i].height);
			free(APNG[i].bmp_out);
			APNG_offset[i] = tiny3d_TextureOffset(texture_pointer);
			texture_pointer += ((APNG[i].pitch * APNG[i].height + 15) & ~15) / 4;
		}
	}
	
	init_timer(0);
	
	return YES;
}

void Draw_APNG()
{
	
	if(time_s[0]==0) start_timer(0);
	
	SetFontZ(0);
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO); // DARK 50%
	
	
	if(APNG_frame >= APNG_num_frames) APNG_frame = 0;
	
	if(APNG_offset[APNG_frame] != 0) {
		tiny3d_SetTexture(0, APNG_offset[APNG_frame], APNG[APNG_frame].width, APNG[APNG_frame].height, APNG[APNG_frame].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		float x0, y0, w0, h0;
		float xf, yf, wf, hf;
		float r;		
		
		if( APNG[0].width > 748) {
			r = 748 / (float) APNG[0].width;
			w0 = 748;
			h0 = (float) APNG[0].height * r;
			wf = (float) APNG[APNG_frame].width * r;
			hf = (float) APNG[APNG_frame].height * r;
		} else 
		if (APNG[0].height > 412) {
			r = 412 / (float) APNG[0].height;
			h0 = 412;
			w0 = (float) APNG[0].width * r;
			wf = (float) APNG[APNG_frame].width * r;
			hf = (float) APNG[APNG_frame].height * r;
		} else {
			w0 = (float) APNG[0].width;
			h0 = (float) APNG[0].height;
			wf = (float) APNG[APNG_frame].width;
			hf = (float) APNG[APNG_frame].height;
		}
		x0 = (848 - w0) / 2;
		y0 = (512 - h0) / 2;
		xf = x0 + (float) APNG_data[APNG_frame].x_offset;
		yf = y0 + (float) APNG_data[APNG_frame].y_offset;
		
		Draw_Box(xf, yf, 0, 0, wf, hf, WHITE, YES);
	}
	
	Draw_Box(0, 460, 0, 0, 848, 20, BLACK, NO);
	FontColor(WHITE);
	DrawStringFromCenterX(424, 462 , &strrchr(TMP_PIC_path, '/')[1]);
	
	if(APNG_data[APNG_frame].delay_den == 0) APNG_data[APNG_frame].delay_den=100;
	//usleep((float) APNG_data[APNG_frame].delay_num * 1000000 / (float) APNG_data[APNG_frame].delay_den);
	
	if( get_time(0) > (APNG_data[APNG_frame].delay_num * 1000 / APNG_data[APNG_frame].delay_den) ) {
		start_timer(0);
		APNG_frame++;
	}
	
}

void Load_ANIMATED_BG(char* filename)
{
	FILE* f;
	u64 magic;
	u32 pos;
	chunk_header ch;
	
	u8 IEND_[0xC] = {0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82};
	
	u8 Frame_Header[0x29];
	acTL_data ad;
	
	memset(BG_data, 0, sizeof(BG_data));
	memset(BG, 0, sizeof(BG));
	memset(BG_offset, 0, sizeof(BG_offset));
	BG_num_frames = 0;
	
	prog_bar2_value=0;
	
	f = fopen(filename, "rb");

	if(f==NULL) {
		//print_load("Error :  failed to open file");
		return;
	}
	
	fread(&magic, 1, 8, f);
	
	if(magic != MAGIC_PNG) { 
		//print_load("Error :  bad magic"); 
		fclose(f); return;
	}
	
	fseek(f, 0, SEEK_SET);
	fread(&Frame_Header, 1, 0x21, f);
	
	fread(&ch, 1, 8, f);
		
	while (ch.type != acTL)  
	{
		pos = ftell(f) + ch.length + 4; // ignore CRC
		fseek(f, pos, SEEK_SET);
		fread(&ch, 1, 8, f);
		
		if(ch.type == IDAT) {
			//print_load("Error : no actl");
			fclose(f);
			return;
		} // not GRID_ANIMATED
	}

	fread(&ad, 1, ch.length, f);
	
	BG_num_frames = ad.num_frames;

	pos = ftell(f) + 4; // ignore CRC
	fseek(f, pos, SEEK_SET);
	u32 i;
	
	for(i=0; i<ad.num_frames; i++) {
		prog_bar2_value=i*100/ad.num_frames;
		fread(&ch, 1, 8, f);
		
		while (ch.type != fcTL)
		{
			pos = ftell(f) + ch.length + 4; // ignore CRC
			fseek(f, pos, SEEK_SET);
			fread(&ch, 1, 8, f);
		}
		fread(&BG_data[i], 1, ch.length, f);
		
		*(u32 *) &Frame_Header[0x10] = BG_data[i].width;
		*(u32 *) &Frame_Header[0x14] = BG_data[i].height;
		*(u32 *) &Frame_Header[0x25] = IDAT;
		
		pos = ftell(f) + 4; // ignore CRC
		fseek(f, pos, SEEK_SET);
		
		fread(&ch, 1, 8, f);
		
		while (ch.type != IDAT && ch.type != fdAT)
		{	
			pos = ftell(f) + ch.length + 4; // ignore CRC
			fseek(f, pos, SEEK_SET);
			fread(&ch, 1, 8, f);
		}
		
		u32 n_AT=0;
		u32 tot_size=0;
		u32 chunk_size[1024]={0};
		u32 first_pos = ftell(f) - 8;
		
	next:
		if(ch.type == IDAT) {
			tot_size+=ch.length;
			chunk_size[n_AT]=ch.length;
			n_AT++;
			
			pos = ftell(f) + ch.length + 4; // ignore CRC 
			fseek(f, pos, SEEK_SET);
			fread(&ch, 1, 8, f);
			
			goto next;
		} else 
		if(ch.type == fdAT) {
			tot_size+=ch.length - 4; // ignore sequence
			chunk_size[n_AT]=ch.length - 4;
			n_AT++;
			
			pos = ftell(f) + ch.length + 4; // ignore CRC
			fseek(f, pos, SEEK_SET);
			fread(&ch, 1, 8, f);
			
			goto next;
		} else {
			fseek(f, first_pos, SEEK_SET); 
			fread(&ch, 1, 8, f);
		}
		
		*(u32 *) &Frame_Header[0x21] = tot_size;
		
		u32 ihdr_crc = crc32(0L, Z_NULL, 0);
		ihdr_crc = crc32(ihdr_crc, (const unsigned char*)Frame_Header+0xC, 0x11);
		memcpy(Frame_Header+0x1D, &ihdr_crc, 4);
		
		u8 *frame = (u8 *) malloc(0x29 + tot_size + 4 + 0xC);
		if(frame==NULL) {
			//print_load("Error : failed to malloc");
			return;
		}
		
		memcpy(frame, &Frame_Header, 0x29);
		
		u32 j, cur_size=0;
		for(j=0; j<n_AT; j++) {
			if(ch.type == IDAT) {
				fread(frame + 0x29 + cur_size, 1, chunk_size[j], f);
				pos = ftell(f) + 4; // ignore CRC
				fseek(f, pos, SEEK_SET);
				fread(&ch, 1, 8, f);
			} else
			if(ch.type == fdAT) {
				pos = ftell(f) + 4; // ignore sequence_number
				fseek(f, pos, SEEK_SET);
				fread(frame + 0x29 + cur_size, 1, chunk_size[j], f);
				pos = ftell(f) + 4; // ignore CRC
				fseek(f, pos, SEEK_SET);
				fread(&ch, 1, 8, f);
			}
			cur_size+=chunk_size[j];
		}
		pos = ftell(f) - 8;
		fseek(f, pos, SEEK_SET);
		
		
		u32 crc = crc32(0L, Z_NULL, 0);
		crc = crc32(crc, (const unsigned char*)frame+0x25, 4 + tot_size);
		memcpy(frame+0x29+tot_size, &crc, 4);
		
		memcpy(frame+0x29+tot_size+4, IEND_, 0xC);
		
		//FILE* x;
		//char frame_path[128];
		//mkdir("/dev_hdd0/frames", 0777);
		//sprintf(frame_path, "/dev_hdd0/frames/frame_%d.png", i);
		//x = fopen(frame_path, "wb");
		//fwrite(frame, 1, 0x29 + tot_size + 4 + 0xC, x);
		//fclose(x);
		
		pngLoadFromBuffer((const void *) frame, 0x29 + tot_size + 4 + 0xC, (pngData *) &BG[i]);
		
		free(frame);
		
		if(BG[i].bmp_out) {
			memcpy(texture_pointer, BG[i].bmp_out, BG[i].pitch * BG[i].height);
			free(BG[i].bmp_out);
			BG_offset[i] = tiny3d_TextureOffset(texture_pointer);
			texture_pointer += ((BG[i].pitch * BG[i].height + 15) & ~15) / 4;
		}
	}
	
	init_timer(1);
	BG_frame=0;
	
	prog_bar2_value=-1;
	
	return;
}

void Draw_ANIMATED_BG()
{
	if(time_s[1]==0) start_timer(1);	
	
	if(BG_frame >= BG_num_frames) BG_frame = 0;
	
	if(BG_offset[BG_frame] != 0) {
		tiny3d_SetTexture(0, BG_offset[BG_frame], BG[BG_frame].width, BG[BG_frame].height, BG[BG_frame].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
	}
	
	if(BG_data[BG_frame].delay_den == 0) BG_data[BG_frame].delay_den=100;
	
	if( get_time(1) > (BG_data[BG_frame].delay_num * 1000 / BG_data[BG_frame].delay_den) ) {
		start_timer(1);
		BG_frame++;
	}
	
}

void float_to_fract(float f, uint16_t *num, uint16_t *den)
{
	uint16_t a, h[3] = { 0, 1, 0 }, k[3] = { 1, 0, 0 };
	int64_t x, d, n = 1;
	int i, neg = 0;

	if (f < 0) { neg = 1; f = -f; }

	while (f != floor(f)) { n <<= 1; f *= 2; }
	d = f;

	for (i = 0; i < 15; i++) {

		a = n ? d / n : 0;
		if (i && !a) break;

		x = d; d = n; n = x % n; x = a;
		
		if (k[1] * a + k[0] >= 0xFFFF) {
			x = (0xFFFF - k[0]) / k[1];
			if (x * 2 >= a || k[1] >= 0xFFFF)
				i = 16;
			else
				break;
		}

		h[2] = x * h[1] + h[0]; h[0] = h[1]; h[1] = h[2];
		k[2] = x * k[1] + k[0]; k[0] = k[1]; k[1] = k[2];
	}
	*den = k[1];
	*num = neg ? -h[1] : h[1];
}

int Build_APNG(char **pngs, uint32_t nb, char *apng, float time)
{
	print_head("Making APNG...");
	
	FILE* in;
	FILE* out;
	int i;
	uint32_t ch[2];
	uint8_t Header[0x21];
	uint32_t crc;
	uint16_t num;
	uint16_t den;
	
	if(time == 0) float_to_fract(0.1, &num, &den);
	else float_to_fract(time, &num, &den);
	
	out = fopen(apng, "wb");
	if(out==NULL) return FAILED;

	prog_bar1_value = 0;
	
	for(i=0; i<nb; i++) {
		prog_bar1_value = i*100/nb;
		print_load("FILE : %s", &strrchr(pngs[i], '/')[1]);
		in = NULL;
		in = fopen(pngs[i], "rb");
		if(in == NULL) {
			fclose(out);
			Delete(apng);
			print_load("Error : Failed to open %s", pngs[i]);
			return FAILED;
		}
		
		if(cancel == YES) {	fclose(in); fclose(out); Delete(apng); return FAILED; }
		
		if(i==0) {

			fread(&Header, 0x21, 1, in);
			
			fwrite(&Header, 0x21, 1, out);
			
			uint32_t ACTL[5];
			ACTL[0]=0x8;
			ACTL[1]=acTL;
			ACTL[2]=nb;
			ACTL[3]=0;
			crc = crc32(0L, Z_NULL, 0);
			crc = crc32(crc, (const unsigned char*) &ACTL[1], 12);
			ACTL[4]	= crc;
			fwrite(&ACTL, 0x14, 1, out);
		}
		
		if(cancel == YES) {	fclose(in); fclose(out); Delete(apng); return FAILED; }

		uint8_t FCTL[0x26];
		FCTL[0] = 0; FCTL[1] = 0; FCTL[2] = 0; FCTL[3] = 0x1A;		// size
		*(uint32_t *) &FCTL[0x4] = (uint32_t) fcTL;					// flag
		if(i==0) *(uint32_t *) &FCTL[0x8] = (uint32_t) 0;
		else *(uint32_t *) &FCTL[0x8] = (uint32_t) i*2-1; 			// sequence number
		*(uint32_t *) &FCTL[0xC] = *(uint32_t *) &Header[0x10];		// w
		*(uint32_t *) &FCTL[0x10] = *(uint32_t *) &Header[0x14];	// h
		*(uint32_t *) &FCTL[0x14] = (uint32_t) 0;					// x
		*(uint32_t *) &FCTL[0x18] = (uint32_t) 0;					// y
		*(uint16_t *) &FCTL[0x1C] = (uint16_t) num;					// n
		*(uint16_t *) &FCTL[0x1E] = (uint16_t) den;					// d : n/d = 100/1000 = 0.1s = 100 ms
		FCTL[0x20] = APNG_DISPOSE_OP_NONE;
		FCTL[0x21] = APNG_BLEND_OP_SOURCE;
		
		crc = crc32(0L, Z_NULL, 0);
		crc = crc32(crc, (const unsigned char*) FCTL+0x4, 0x1E);

		memcpy(FCTL+0x22, &crc, 4);

		fwrite(FCTL, 0x26, 1, out);
		
		fseek(in, 0x21, SEEK_SET);
		
		crc = crc32(0L, Z_NULL, 0);
		uint32_t size = 4;
		char *data;
		
		if(cancel == YES) {	fclose(in); fclose(out); Delete(apng); return FAILED; }
		
		uint32_t pos = ftell(out);
		
		fwrite(&size, 4, 1, out);

		if(i==0) {
			data = malloc(4);
			*(uint32_t *) &data[0x0] = IDAT;
		
			crc = crc32(crc, (const unsigned char*) data, 4);
			fwrite(data, 4, 1, out);
			
		} else {
			data = malloc(8);
			*(uint32_t *) &data[0x0] = fdAT;
			*(uint32_t *) &data[0x4] = i*2;
		
			crc = crc32(crc, (const unsigned char*) data, 8);
			fwrite(data, 8, 1, out);
		}
		
		free(data);	
		
	next:
		
		if(cancel == YES) {	fclose(in); fclose(out); Delete(apng); return FAILED; }
	
		fread(&ch, 1, 8, in);

		while (ch[1] != IDAT && ch[1] != IEND)
		{	

			fseek(in, ch[0] + 4, SEEK_CUR);
			fread(&ch, 1, 8, in);
			
			if(cancel == YES) {	fclose(in); fclose(out); Delete(apng); return FAILED; }
			
			//if(feof(in)) {print_load("Error : EOF, IDAT/IEND not found"); fclose(in); fclose(out); Delete(apng); return FAILED;}
		}
		
		if( ch[1] == IDAT ) {
			data = malloc(ch[0]);
			fread(data, 1, ch[0], in);
			fwrite(data, 1, ch[0], out);
			crc = crc32(crc, (const unsigned char*) data, ch[0]);
			size+=ch[0];
			fseek(in, 4, SEEK_CUR);
			free(data);
			goto next;
		}
		
		
		if(cancel == YES) {	fclose(in); fclose(out); Delete(apng); return FAILED; }
		
		fwrite(&crc, 4, 1, out);
		
		uint32_t pos2 = ftell(out);
		
		fseek(out, pos, SEEK_SET);
		
		if(i==0) size = size-4;
		
		fwrite(&size, 4, 1, out);
		
		fseek(out, pos2, SEEK_SET);
		
		fclose(in);

	}
	
	uint8_t IEND_[0xC] = {0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82};
	fwrite(&IEND_, 0xC, 1, out);
	
	fclose(out);
	
	prog_bar1_value = -1;
	
	return SUCCESS;
}

u8 make_ABG(char *dir_path, char *file_out)
{
	
	int ret;
	char JS[255];
	int i,j,k,l,m, min;
	int png_number=-1;
	
	u8 Header_REF[0x21];
	u8 Header[0x21];
	
	char **PNGS = (char **) malloc(MAX_FRAME*sizeof(char *));
	for(i=0; i<MAX_FRAME; i++) PNGS[i]=NULL;
	
	DIR *d;
	struct dirent *dir;

	d = opendir(dir_path);
	if(d==NULL) return FAILED;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		memset(Header, 0, sizeof(Header));
		
		print_load("%s", dir->d_name);
		
		char temp[255];
		sprintf(temp, "%s/%s", dir_path, dir->d_name);
		u8 ext = get_ext(temp);
		
		if( ext == _JS) {
			strcpy(JS, temp);
		} else
		if( ext == _PNG) {

			FILE* fo;
			fo = fopen(temp, "rb");
			fread(&Header, 0x21, 1, fo);
			fclose(fo);
			
			if( png_number == -1 ) {

				u32 w = *(uint32_t *) &Header[0x10];	
				u32 h = *(uint32_t *) &Header[0x14];

				if( w > 640 && h > 480) {

					memcpy(Header_REF, Header, 0x21);
					png_number++;
					PNGS[png_number] = strcpy_malloc(temp);
				}
 			} 
			else {

				if( memcmp(Header, Header_REF, 0x21) == 0 ) {
					png_number++;
					PNGS[png_number] = strcpy_malloc(temp);
				}
			}
		}
	}
	closedir(d);
	
	if(png_number < 0) return FAILED; else
	if(png_number==0) {
		ret = Copy(PNGS[0], file_out);
		FREE(PNGS[0]);
		FREE(PNGS);
		return ret;
	}
	
	char *ta=NULL;
	char *tb=NULL;
	
	for(i = 0; i<png_number; i++) { 
		min = i;
		for (j = i+1; j <= png_number; j++) { 
						
			ta = strcpy_malloc(PNGS[j]);
			tb = strcpy_malloc(PNGS[min]);
			
			k=-1;
			l=-1;
			
			sscanf(strrchr(ta, '/'), "%*[^0-9]%d", &k);
			sscanf(strrchr(tb, '/'), "%*[^0-9]%d", &l);
			
			if(k==-1 || l==-1) {
				FREE(ta); FREE(tb);
				for(m=0;m<MAX_FRAME; m++) FREE(PNGS[m]);
				FREE(PNGS);
				return FAILED;
			}
			
			if( k < l ) min = j;
			
			FREE(ta); FREE(tb);
		}
		
		if(min==i) continue;
		ta = strcpy_malloc(PNGS[min]);
		FREE(PNGS[min]);
		PNGS[min] = strcpy_malloc(PNGS[i]); 
		FREE(PNGS[i]);
		PNGS[i] = strcpy_malloc(ta); 
	}
	FREE(ta); FREE(tb);

	float time=0.0;
	int size;
	char temp[64];

	char *script = LoadFile(JS, &size);
	if(script == NULL) {
		ret = Build_APNG(PNGS, png_number, file_out, 0);
		for(m=0;m<MAX_FRAME; m++) FREE(PNGS[m]);
		FREE(PNGS);
		return ret;
	}

	if( strstr(script, " IntervalTimer(") == NULL) {
		FREE(script);
		ret = Build_APNG(PNGS, png_number, file_out, 0);
		for(m=0;m<MAX_FRAME; m++) FREE(PNGS[m]);
		FREE(PNGS);
		return ret;
	}

	memcpy(temp, strstr(script, " IntervalTimer(") + 15, 64);
	
	if( strstr(temp, ",") == NULL) {
		FREE(script);
		ret = Build_APNG(PNGS, png_number, file_out, 0);
		for(m=0;m<MAX_FRAME; m++) FREE(PNGS[m]);
		FREE(PNGS);
		return ret;
	}
	strtok(temp, ",");
	sscanf(temp, "%f", &time);

	if(time == 0) {
		strcat(temp, " = ");
		char temp2[64];

		memcpy(temp2, strstr(script, temp) + strlen(temp), 64);
		if( strstr(temp2, ";") != NULL) {
			strtok(temp2, ";");
			sscanf(temp2, "%f", &time);
		}
	}
	
	FREE(script);
	
	ret = Build_APNG(PNGS, png_number, file_out, time);
	
	for(m=0;m<MAX_FRAME; m++) FREE(PNGS[m]);
	FREE(PNGS);
	
	return ret;
}

//###################################################
//	LANGUAGE
//###################################################

char *strcpy_malloc(char *STR_DEFAULT)
{
	if(STR_DEFAULT==NULL) return NULL;
	char *STR = malloc( strlen(STR_DEFAULT)+1);
	if(STR==NULL) return NULL;
	strcpy(STR, STR_DEFAULT);
	strcat(STR, "\0");
	return STR;
}

static char buff3[512];
char *sprintf_malloc(char *format, ...)
{
	char *str = (char *) buff3;
	va_list	opt;
	
	va_start(opt, format);
	vsprintf( (void *) buff3, format, opt);
	va_end(opt);
	
	return strcpy_malloc(str);
}

char *language(FILE* flang, const char *strName, char *str_default)
{
	if(flang==NULL) return strcpy_malloc(str_default);
	
	int c;
	int i;
	
	char str[512];
	memset(str, 0, 512);
	
	uint8_t do_retry = YES;
		
	int l = strlen(strName);
	
retry:
	do {
		c = fgetc(flang);
		for(i=0; i < l; i++)
		{
			if( c != strName[i]) break;
			else if (i==l-1) 
			{
				c = fgetc(flang);
				if(c != '\t' && c != ' ') break;
				
				while(c != '{') {
					c = fgetc(flang);
					if(c == FAKE_EOF) break;
				}
				
				int str_len = 0;
				
				do {
					
					c = fgetc(flang);
					
					if (c == '}') {
						str[str_len] = '\0';
						
						char *ret = (char *) malloc((size_t) str_len+1);
						memcpy(ret, str, str_len+1);
						return ret;
					}
					
					if (c == 92) { 
						c = fgetc(flang);
						if (c == 'n') {
							str[str_len] = '\n';
							str_len++;
						} 
						else if (c == 'r') {
							str[str_len] = '\r';
							str_len++;
						} 
						else if (c == 'x') {
							char Number[2];
							Number[0] = fgetc(flang);
							Number[1] = fgetc(flang);
							short unsigned int val=0;
							sscanf(Number, "%hX", &val);
							str[str_len] = val;
							str_len++;
						}
						else {
							str[str_len] = 92;
							str_len++;
							str[str_len] = c;
							str_len++;
						}
						
					} else {
						str[str_len] = c;
						str_len++;
					}
					
				} while (c != FAKE_EOF);
				
			} 
			else c = fgetc(flang);
		}
		
	} while (c != FAKE_EOF);
	
	if(do_retry == YES) {do_retry=NO; fseek(flang, 0, SEEK_SET); goto retry;}

	return strcpy_malloc(str_default);
}

void init_lang()
{
	
	char LOCPath[128];
	char TXTPath[128];
	
	lang_N = 0;
	STR_LANGUAGE[lang_N] = (char *)  malloc((size_t)18);
	STR_LANGCODE[lang_N] = (char *)  malloc((size_t)2);
	
	strcpy(STR_LANGUAGE[lang_N], "English (default)");
	STR_LANGCODE[lang_N][0] = LANG_DEFAULT;

	lang_N++;
	
	sprintf(LOCPath, "/dev_hdd0/game/%s/USRDIR/sys/loc", ManaGunZ_id);
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(LOCPath);
	if(d==NULL) return;

	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		sprintf(TXTPath, "%s/%s", LOCPath, dir->d_name);
		
		FILE* flang = fopen(TXTPath, "rb");
		if(flang==NULL) continue;
		
		STR_LANGUAGE[lang_N] = language(flang, "STR_LANGUAGE", NULL);
		
		if(STR_LANGUAGE[lang_N] != NULL ) {
			STR_LANGCODE[lang_N] = language(flang, "STR_LANGCODE", NULL);
			FREE(lang_path[lang_N]);
			lang_path[lang_N] = (char *) malloc(strlen(TXTPath)+1);
			strcpy(lang_path[lang_N], TXTPath);
			lang_N++;
			
		}
		
		FCLOSE(flang);
	}
	closedir(d);
	
}

void update_lang()
{
	FILE* flang=NULL;
	if(lang>0) flang = fopen(lang_path[lang], "r");

	FREE(STR_LANG);
	STR_LANG = language(flang, "STR_LANG", STR_LANG_DEFAULT);
	FREE(STR_LANG_DESC);
	STR_LANG_DESC = language(flang, "STR_LANG_DESC", STR_LANG_DESC_DEFAULT);
	FREE(STR_GATHERING);
	STR_GATHERING = language(flang, "STR_GATHERING", STR_GATHERING_DEFAULT);
	FREE(STR_COPYING);
	STR_COPYING = language(flang, "STR_COPYING", STR_COPYING_DEFAULT);
	FREE(STR_FROM);
	STR_FROM = language(flang, "STR_FROM", STR_FROM_DEFAULT);
	FREE(STR_TO);
	STR_TO = language(flang, "STR_TO", STR_TO_DEFAULT);
	FREE(STR_FILES);
	STR_FILES = language(flang, "STR_FILES", STR_FILES_DEFAULT);
	FREE(STR_DIRS);
	STR_DIRS = language(flang, "STR_DIRS", STR_DIRS_DEFAULT);
	FREE(STR_UNKNOWN);
	STR_UNKNOWN = language(flang, "STR_UNKNOWN", STR_UNKNOWN_DEFAULT);
	FREE(STR_FILE);
	STR_FILE = language(flang, "STR_FILE", STR_FILE_DEFAULT);
	FREE(STR_CANCEL);
	STR_CANCEL = language(flang, "STR_CANCEL", STR_CANCEL_DEFAULT);
	FREE(STR_TURNOFF_YES);
	STR_TURNOFF_YES = language(flang, "STR_TURNOFF_YES", STR_TURNOFF_YES_DEFAULT);
	FREE(STR_TURNOFF_NO);
	STR_TURNOFF_NO = language(flang, "STR_TURNOFF_NO", STR_TURNOFF_NO_DEFAULT);
	FREE(STR_CANCELLED);
	STR_CANCELLED = language(flang, "STR_CANCELLED", STR_CANCELLED_DEFAULT);
	FREE(STR_UNIT);
	STR_UNIT = language(flang, "STR_UNIT", STR_UNIT_DEFAULT);
	FREE(STR_TOTALSIZE);
	STR_TOTALSIZE = language(flang, "STR_TOTALSIZE", STR_TOTALSIZE_DEFAULT);
	FREE(STR_HIDELOGS);
	STR_HIDELOGS = language(flang, "STR_HIDELOGS", STR_HIDELOGS_DEFAULT);
	FREE(STR_SHOWLOGS);
	STR_SHOWLOGS = language(flang, "STR_SHOWLOGS", STR_SHOWLOGS_DEFAULT);
	FREE(STR_BOOST);
	STR_BOOST = language(flang, "STR_BOOST", STR_BOOST_DEFAULT);
	FREE(STR_GAMEMENU);
	STR_GAMEMENU = language(flang, "STR_GAMEMENU", STR_GAMEMENU_DEFAULT);
	FREE(STR_SETTINGS);
	STR_SETTINGS = language(flang, "STR_SETTINGS", STR_SETTINGS_DEFAULT);
	FREE(STR_MOUNTGAME);
	STR_MOUNTGAME = language(flang, "STR_MOUNTGAME", STR_MOUNTGAME_DEFAULT);
	FREE(STR_FILTER);
	STR_FILTER = language(flang, "STR_FILTER", STR_FILTER_DEFAULT);
	FREE(STR_FAVORITE);
	STR_FAVORITE = language(flang, "STR_FAVORITE", STR_FAVORITE_DEFAULT);
	FREE(STR_FILEMANAGER);
	STR_FILEMANAGER = language(flang, "STR_FILEMANAGER", STR_FILEMANAGER_DEFAULT);
	FREE(STR_HOLD);
	STR_HOLD = language(flang, "STR_HOLD", STR_HOLD_DEFAULT);
	FREE(STR_BACKTOXMB);
	STR_BACKTOXMB = language(flang, "STR_BACKTOXMB", STR_BACKTOXMB_DEFAULT);
	FREE(STR_GAME_PROP);
	STR_GAME_PROP = language(flang, "STR_GAME_PROP", STR_GAME_PROP_DEFAULT);
	FREE(STR_GAME_TITLE);
	STR_GAME_TITLE = language(flang, "STR_GAME_TITLE", STR_GAME_TITLE_DEFAULT);
	FREE(STR_GAME_PATH);
	STR_GAME_PATH = language(flang, "STR_GAME_PATH", STR_GAME_PATH_DEFAULT);
	FREE(STR_GAME_FORMAT);
	STR_GAME_FORMAT = language(flang, "STR_GAME_FORMAT", STR_GAME_FORMAT_DEFAULT);
	FREE(STR_GAME_SIZE);
	STR_GAME_SIZE = language(flang, "STR_GAME_SIZE", STR_GAME_SIZE_DEFAULT);
	FREE(STR_GAME_PLATFORM);
	STR_GAME_PLATFORM = language(flang, "STR_GAME_PLATFORM", STR_GAME_PLATFORM_DEFAULT);
	FREE(STR_SYSVERS);
	STR_SYSVERS = language(flang, "STR_SYSVERS", STR_SYSVERS_DEFAULT);
	FREE(STR_GAMEID);
	STR_GAMEID = language(flang, "STR_GAMEID", STR_GAMEID_DEFAULT);
	FREE(STR_ELFCRC);
	STR_ELFCRC = language(flang, "STR_ELFCRC", STR_ELFCRC_DEFAULT);
	FREE(STR_ELFCRCO);
	STR_ELFCRCO = language(flang, "STR_ELFCRCO", STR_ELFCRCO_DEFAULT);
	FREE(STR_BACK);
	STR_BACK = language(flang, "STR_BACK", STR_BACK_DEFAULT);
	FREE(STR_ENTER);
	STR_ENTER = language(flang, "STR_ENTER", STR_ENTER_DEFAULT);
	FREE(STR_UPDATE_FOUND);
	STR_UPDATE_FOUND = language(flang, "STR_UPDATE_FOUND", STR_UPDATE_FOUND_DEFAULT);
	FREE(STR_UPDATE);
	STR_UPDATE = language(flang, "STR_UPDATE", STR_UPDATE_DEFAULT);
	FREE(STR_SIZE);
	STR_SIZE = language(flang, "STR_SIZE", STR_SIZE_DEFAULT);
	FREE(STR_SYSTEM);
	STR_SYSTEM = language(flang, "STR_SYSTEM", STR_SYSTEM_DEFAULT);
	FREE(STR_DL);
	STR_DL = language(flang, "STR_DL", STR_DL_DEFAULT);
	FREE(STR_DL_ALL);
	STR_DL_ALL = language(flang, "STR_DL_ALL", STR_DL_ALL_DEFAULT);
	FREE(STR_UNPLUG);
	STR_UNPLUG = language(flang, "STR_UNPLUG", STR_UNPLUG_DEFAULT);
	FREE(STR_PATH);
	STR_PATH = language(flang, "STR_PATH", STR_PATH_DEFAULT);
	FREE(STR_TYPE);
	STR_TYPE = language(flang, "STR_TYPE", STR_TYPE_DEFAULT);
	FREE(STR_FOLDER);
	STR_FOLDER = language(flang, "STR_FOLDER", STR_FOLDER_DEFAULT);
	FREE(STR_DIR);
	STR_DIR = language(flang, "STR_DIR", STR_DIR_DEFAULT);
	FREE(STR_MULT);
	STR_MULT = language(flang, "STR_MULT", STR_MULT_DEFAULT);
	FREE(STR_THM_SETTINGS);
	STR_THM_SETTINGS = language(flang, "STR_THM_SETTINGS", STR_THM_SETTINGS_DEFAULT);
	FREE(STR_THM);
	STR_THM = language(flang, "STR_THM", STR_THM_DEFAULT);
	FREE(STR_THM_DESC);
	STR_THM_DESC = language(flang, "STR_THM_DESC", STR_THM_DESC_DEFAULT);
	FREE(STR_CREATE);
	STR_CREATE = language(flang, "STR_CREATE", STR_CREATE_DEFAULT);
	FREE(STR_ZOOM_OUT);
	STR_ZOOM_OUT = language(flang, "STR_ZOOM_OUT", STR_ZOOM_OUT_DEFAULT);
	FREE(STR_ZOOM_IN);
	STR_ZOOM_IN = language(flang, "STR_ZOOM_IN", STR_ZOOM_IN_DEFAULT);
	FREE(STR_MOVE_FRAME);
	STR_MOVE_FRAME = language(flang, "STR_MOVE_FRAME", STR_MOVE_FRAME_DEFAULT);
	FREE(STR_CHECK);
	STR_CHECK = language(flang, "STR_CHECK", STR_CHECK_DEFAULT);
	FREE(STR_UNCHECK);
	STR_UNCHECK = language(flang, "STR_UNCHECK", STR_UNCHECK_DEFAULT);
	FREE(STR_GAME_OPTION);
	STR_GAME_OPTION = language(flang, "STR_GAME_OPTION", STR_GAME_OPTION_DEFAULT);
	FREE(STR_ADD_FAV);
	STR_ADD_FAV = language(flang, "STR_ADD_FAV", STR_ADD_FAV_DEFAULT);
	FREE(STR_REM_FAV);
	STR_REM_FAV = language(flang, "STR_REM_FAV", STR_REM_FAV_DEFAULT);
	FREE(STR_FAV_DESC);
	STR_FAV_DESC = language(flang, "STR_FAV_DESC", STR_FAV_DESC_DEFAULT);
	FREE(STR_RENAME);
	STR_RENAME = language(flang, "STR_RENAME", STR_RENAME_DEFAULT);
	FREE(STR_RENAME_DESC);
	STR_RENAME_DESC = language(flang, "STR_RENAME_DESC", STR_RENAME_DESC_DEFAULT);
	FREE(STR_DELETE);
	STR_DELETE = language(flang, "STR_DELETE", STR_DELETE_DEFAULT);
	FREE(STR_DELETE_DESC);
	STR_DELETE_DESC = language(flang, "STR_DELETE_DESC", STR_DELETE_DESC_DEFAULT);
	FREE(STR_COPY);
	STR_COPY = language(flang, "STR_COPY", STR_COPY_DEFAULT);
	FREE(STR_COPY_DESC);
	STR_COPY_DESC = language(flang, "STR_COPY_DESC", STR_COPY_DESC_DEFAULT);
	FREE(STR_CREATE_ICON0);
	STR_CREATE_ICON0 = language(flang, "STR_CREATE_ICON0", STR_CREATE_ICON0_DEFAULT);
	FREE(STR_CREATE_ICON0_DESC);
	STR_CREATE_ICON0_DESC = language(flang, "STR_CREATE_ICON0_DESC", STR_CREATE_ICON0_DESC_DEFAULT);
	FREE(STR_REST_PNACH);
	STR_REST_PNACH = language(flang, "STR_REST_PNACH", STR_REST_PNACH_DEFAULT);
	FREE(STR_REST_PNACH_DESC);
	STR_REST_PNACH_DESC = language(flang, "STR_REST_PNACH_DESC", STR_REST_PNACH_DESC_DEFAULT);
	FREE(STR_APPLY_PNACH);
	STR_APPLY_PNACH = language(flang, "STR_APPLY_PNACH", STR_APPLY_PNACH_DEFAULT);
	FREE(STR_APPLY_PNACH_DESC);
	STR_APPLY_PNACH_DESC = language(flang, "STR_APPLY_PNACH_DESC", STR_APPLY_PNACH_DESC_DEFAULT);
	FREE(STR_DISABLE_WS);
	STR_DISABLE_WS = language(flang, "STR_DISABLE_WS", STR_DISABLE_WS_DEFAULT);
	FREE(STR_ENABLE_WS);
	STR_ENABLE_WS = language(flang, "STR_ENABLE_WS", STR_ENABLE_WS_DEFAULT);
	FREE(STR_WS_DESC);
	STR_WS_DESC = language(flang, "STR_WS_DESC", STR_WS_DESC_DEFAULT);
	FREE(STR_DISABLE_480P);
	STR_DISABLE_480P = language(flang, "STR_DISABLE_480P", STR_DISABLE_480P_DEFAULT);
	FREE(STR_ENABLE_480P);
	STR_ENABLE_480P = language(flang, "STR_ENABLE_480P", STR_ENABLE_480P_DEFAULT);
	FREE(STR_480P_DESC);
	STR_480P_DESC = language(flang, "STR_480P_DESC", STR_480P_DESC_DEFAULT);
	FREE(STR_DISABLE_YFIX);
	STR_DISABLE_YFIX = language(flang, "STR_DISABLE_YFIX", STR_DISABLE_YFIX_DEFAULT);
	FREE(STR_ENABLE_YFIX);
	STR_ENABLE_YFIX = language(flang, "STR_ENABLE_YFIX", STR_ENABLE_YFIX_DEFAULT);
	FREE(STR_YFIX_DESC);
	STR_YFIX_DESC = language(flang, "STR_YFIX_DESC", STR_YFIX_DESC_DEFAULT);
	FREE(STR_DISABLE_FMVSKIP);
	STR_DISABLE_FMVSKIP = language(flang, "STR_DISABLE_FMVSKIP", STR_DISABLE_FMVSKIP_DEFAULT);
	FREE(STR_ENABLE_FMVSKIP);
	STR_ENABLE_FMVSKIP = language(flang, "STR_ENABLE_FMVSKIP", STR_ENABLE_FMVSKIP_DEFAULT);
	FREE(STR_FMVSKIP_DESC);
	STR_FMVSKIP_DESC = language(flang, "STR_FMVSKIP_DESC", STR_FMVSKIP_DESC_DEFAULT);
	FREE(STR_DISABLE_NETEMU);
	STR_DISABLE_NETEMU = language(flang, "STR_DISABLE_NETEMU", STR_DISABLE_NETEMU_DEFAULT);
	FREE(STR_ENABLE_NETEMU);
	STR_ENABLE_NETEMU = language(flang, "STR_ENABLE_NETEMU", STR_ENABLE_NETEMU_DEFAULT);
	FREE(STR_NETEMU_DESC);
	STR_NETEMU_DESC = language(flang, "STR_NETEMU_DESC", STR_NETEMU_DESC_DEFAULT);
	FREE(STR_SAVE_CONFIG);
	STR_SAVE_CONFIG = language(flang, "STR_SAVE_CONFIG", STR_SAVE_CONFIG_DEFAULT);
	FREE(STR_CONFIG);
	STR_CONFIG = language(flang, "STR_CONFIG", STR_CONFIG_DEFAULT);	
	FREE(STR_CONFIG_DESC);
	STR_CONFIG_DESC = language(flang, "STR_CONFIG_DESC", STR_CONFIG_DESC_DEFAULT);
	FREE(STR_NONE);
	STR_NONE = language(flang, "STR_NONE", STR_NONE_DEFAULT);
	FREE(STR_CHECK_MD5);
	STR_CHECK_MD5 = language(flang, "STR_CHECK_MD5", STR_CHECK_MD5_DEFAULT);
	FREE(STR_PROPS);
	STR_PROPS = language(flang, "STR_PROPS", STR_PROPS_DEFAULT);
	FREE(STR_PROPS_DESC);
	STR_PROPS_DESC = language(flang, "STR_PROPS_DESC", STR_PROPS_DESC_DEFAULT);
	FREE(STR_ASK_DEL);
	STR_ASK_DEL = language(flang, "STR_ASK_DEL", STR_ASK_DEL_DEFAULT);
	FREE(STR_GAME_SETTINGS);
	STR_GAME_SETTINGS = language(flang, "STR_GAME_SETTINGS", STR_GAME_SETTINGS_DEFAULT);
	FREE(STR_DIRECT_BOOT);
	STR_DIRECT_BOOT = language(flang, "STR_DIRECT_BOOT", STR_DIRECT_BOOT_DEFAULT);
	FREE(STR_DIRECT_BOOT_DESC);
	STR_DIRECT_BOOT_DESC = language(flang, "STR_DIRECT_BOOT_DESC", STR_DIRECT_BOOT_DESC_DEFAULT);
	FREE(STR_YES);
	STR_YES = language(flang, "STR_YES", STR_YES_DEFAULT);
	FREE(STR_NO);
	STR_NO = language(flang, "STR_NO", STR_NO_DEFAULT);
	FREE(STR_CLEAN_SYSCALL);
	STR_CLEAN_SYSCALL = language(flang, "STR_CLEAN_SYSCALL", STR_CLEAN_SYSCALL_DEFAULT);
	FREE(STR_CLEAN_SYSCALL_DESC);
	STR_CLEAN_SYSCALL_DESC = language(flang, "STR_CLEAN_SYSCALL_DESC", STR_CLEAN_SYSCALL_DESC_DEFAULT);
	FREE(STR_CHANGE_IDPS);
	STR_CHANGE_IDPS = language(flang, "STR_CHANGE_IDPS", STR_CHANGE_IDPS_DEFAULT);
	FREE(STR_CHANGE_IDPS_DESC);
	STR_CHANGE_IDPS_DESC = language(flang, "STR_CHANGE_IDPS_DESC", STR_CHANGE_IDPS_DESC_DEFAULT);
	FREE(STR_EXT_GAME_DATA);
	STR_EXT_GAME_DATA = language(flang, "STR_EXT_GAME_DATA", STR_EXT_GAME_DATA_DEFAULT);
	FREE(STR_EXT_GAME_DATA_DESC);
	STR_EXT_GAME_DATA_DESC = language(flang, "STR_EXT_GAME_DATA_DESC", STR_EXT_GAME_DATA_DESC_DEFAULT);
	FREE(STR_PAYLOAD);
	STR_PAYLOAD = language(flang, "STR_PAYLOAD", STR_PAYLOAD_DEFAULT);
	FREE(STR_PAYLOAD_DESC);
	STR_PAYLOAD_DESC = language(flang, "STR_PAYLOAD_DESC", STR_PAYLOAD_DESC_DEFAULT);
	FREE(STR_PRIM_USB);
	STR_PRIM_USB = language(flang, "STR_PRIM_USB", STR_PRIM_USB_DEFAULT);
	FREE(STR_PRIM_USB_DESC);
	STR_PRIM_USB_DESC = language(flang, "STR_PRIM_USB_DESC", STR_PRIM_USB_DESC_DEFAULT);
	FREE(STR_BDEMU);
	STR_BDEMU = language(flang, "STR_BDEMU", STR_BDEMU_DEFAULT);
	FREE(STR_BDEMU_DESC);
	STR_BDEMU_DESC = language(flang, "STR_BDEMU_DESC", STR_BDEMU_DESC_DEFAULT);
	FREE(STR_PATCH_LIBFS);
	STR_PATCH_LIBFS = language(flang, "STR_PATCH_LIBFS", STR_PATCH_LIBFS_DEFAULT);
	FREE(STR_PATCH_LIBFS_DESC);
	STR_PATCH_LIBFS_DESC = language(flang, "STR_PATCH_LIBFS_DESC", STR_PATCH_LIBFS_DESC_DEFAULT);
	FREE(STR_MOUNT_APPHOME);
	STR_MOUNT_APPHOME = language(flang, "STR_MOUNT_APPHOME", STR_MOUNT_APPHOME_DEFAULT);
	FREE(STR_MOUNT_APPHOME_DESC);
	STR_MOUNT_APPHOME_DESC = language(flang, "STR_MOUNT_APPHOME_DESC", STR_MOUNT_APPHOME_DESC_DEFAULT);
	FREE(STR_PATCH_EXP);
	STR_PATCH_EXP = language(flang, "STR_PATCH_EXP", STR_PATCH_EXP_DEFAULT);
	FREE(STR_PATCH_EXP_DESC);
	STR_PATCH_EXP_DESC = language(flang, "STR_PATCH_EXP_DESC", STR_PATCH_EXP_DESC_DEFAULT);
	FREE(STR_MAKE_SHTCUT_PKG);
	STR_MAKE_SHTCUT_PKG = language(flang, "STR_MAKE_SHTCUT_PKG", STR_MAKE_SHTCUT_PKG_DEFAULT);
	FREE(STR_MAKE_SHTCUT_PKG_DESC);
	STR_MAKE_SHTCUT_PKG_DESC = language(flang, "STR_MAKE_SHTCUT_PKG_DESC", STR_MAKE_SHTCUT_PKG_DESC_DEFAULT);
	FREE(STR_PATCH_EBOOT);
	STR_PATCH_EBOOT = language(flang, "STR_PATCH_EBOOT", STR_PATCH_EBOOT_DEFAULT);
	FREE(STR_PATCH_EBOOT_DESC);
	STR_PATCH_EBOOT_DESC = language(flang, "STR_PATCH_EBOOT_DESC", STR_PATCH_EBOOT_DESC_DEFAULT);
	FREE(STR_RESIGN);
	STR_RESIGN = language(flang, "STR_RESIGN", STR_RESIGN_DEFAULT);
	FREE(STR_RESIGN_DESC);
	STR_RESIGN_DESC = language(flang, "STR_RESIGN_DESC", STR_RESIGN_DESC_DEFAULT);
	FREE(STR_RESTORE);
	STR_RESTORE = language(flang, "STR_RESTORE", STR_RESTORE_DEFAULT);
	FREE(STR_RESTORE_DESC);
	STR_RESTORE_DESC = language(flang, "STR_RESTORE_DESC", STR_RESTORE_DESC_DEFAULT);
	FREE(STR_EXTRACT_ISO);
	STR_EXTRACT_ISO = language(flang, "STR_EXTRACT_ISO", STR_EXTRACT_ISO_DEFAULT);
	FREE(STR_EXTRACT_ISO_DESC);
	STR_EXTRACT_ISO_DESC = language(flang, "STR_EXTRACT_ISO_DESC", STR_EXTRACT_ISO_DESC_DEFAULT);
	FREE(STR_CONVERT_ISO);
	STR_CONVERT_ISO = language(flang, "STR_CONVERT_ISO", STR_CONVERT_ISO_DEFAULT);
	FREE(STR_CONVERT_ISO_DESC);
	STR_CONVERT_ISO_DESC = language(flang, "STR_CONVERT_ISO_DESC", STR_CONVERT_ISO_DESC_DEFAULT);
	FREE(STR_FIX_PERMS);
	STR_FIX_PERMS = language(flang, "STR_FIX_PERMS", STR_FIX_PERMS_DEFAULT);
	FREE(STR_FIX_PERMS_DESC);
	STR_FIX_PERMS_DESC = language(flang, "STR_FIX_PERMS_DESC", STR_FIX_PERMS_DESC_DEFAULT);
	FREE(STR_CHECK_IRD);
	STR_CHECK_IRD = language(flang, "STR_CHECK_IRD", STR_CHECK_IRD_DEFAULT);
	FREE(STR_CHECK_DESC);
	STR_CHECK_DESC = language(flang, "STR_CHECK_DESC", STR_CHECK_DESC_DEFAULT);
	FREE(STR_DL_UPDATE);
	STR_DL_UPDATE = language(flang, "STR_DL_UPDATE", STR_DL_UPDATE_DEFAULT);
	FREE(STR_DL_UPDATE_DESC);
	STR_DL_UPDATE_DESC = language(flang, "STR_DL_UPDATE_DESC", STR_DL_UPDATE_DESC_DEFAULT);
	FREE(STR_OPEN_WINDOW);
	STR_OPEN_WINDOW = language(flang, "STR_OPEN_WINDOW", STR_OPEN_WINDOW_DEFAULT);
	FREE(STR_MOUNT_DEVBLIND);
	STR_MOUNT_DEVBLIND = language(flang, "STR_MOUNT_DEVBLIND", STR_MOUNT_DEVBLIND_DEFAULT);
	FREE(STR_DUMP_LV1);
	STR_DUMP_LV1 = language(flang, "STR_DUMP_LV1", STR_DUMP_LV1_DEFAULT);
	FREE(STR_DUMP_LV2);
	STR_DUMP_LV2 = language(flang, "STR_DUMP_LV2", STR_DUMP_LV2_DEFAULT);
	FREE(STR_DUMP_FLASH);
	STR_DUMP_FLASH = language(flang, "STR_DUMP_FLASH", STR_DUMP_FLASH_DEFAULT);
	FREE(STR_REFRESH);
	STR_REFRESH = language(flang, "STR_REFRESH", STR_REFRESH_DEFAULT);
	FREE(STR_NEWFOLDER);
	STR_NEWFOLDER = language(flang, "STR_NEWFOLDER", STR_NEWFOLDER_DEFAULT);
	FREE(STR_NEWFILE);
	STR_NEWFILE = language(flang, "STR_NEWFILE", STR_NEWFILE_DEFAULT);
	FREE(STR_PASTE);
	STR_PASTE = language(flang, "STR_PASTE", STR_PASTE_DEFAULT);
	FREE(STR_CUT);
	STR_CUT = language(flang, "STR_CUT", STR_CUT_DEFAULT);
	FREE(STR_UNSELECT_ALL);
	STR_UNSELECT_ALL = language(flang, "STR_UNSELECT_ALL", STR_UNSELECT_ALL_DEFAULT);
	FREE(STR_SELECT_ALL);
	STR_SELECT_ALL = language(flang, "STR_SELECT_ALL", STR_SELECT_ALL_DEFAULT);
	FREE(STR_MAKE_PKG);
	STR_MAKE_PKG = language(flang, "STR_MAKE_PKG", STR_MAKE_PKG_DEFAULT);
	FREE(STR_GETMD5);
	STR_GETMD5 = language(flang, "STR_GETMD5", STR_GETMD5_DEFAULT);
	FREE(STR_GETSHA1);
	STR_GETSHA1 = language(flang, "STR_GETSHA1", STR_GETSHA1_DEFAULT);
	FREE(STR_VIEW);
	STR_VIEW = language(flang, "STR_VIEW", STR_VIEW_DEFAULT);
	FREE(STR_VIEW_TXT);
	STR_VIEW_TXT = language(flang, "STR_VIEW_TXT", STR_VIEW_TXT_DEFAULT);
	FREE(STR_VIEW_SFO);
	STR_VIEW_SFO = language(flang, "STR_VIEW_SFO", STR_VIEW_SFO_DEFAULT);
	FREE(STR_READ_XREG);
	STR_READ_XREG = language(flang, "STR_READ_XREG", STR_READ_XREG_DEFAULT);
	FREE(STR_EXTRACT_ELF);
	STR_EXTRACT_ELF = language(flang, "STR_EXTRACT_ELF", STR_EXTRACT_ELF_DEFAULT);
	FREE(STR_RESIGN_SELF);
	STR_RESIGN_SELF = language(flang, "STR_RESIGN_SELF", STR_RESIGN_SELF_DEFAULT);
	FREE(STR_LAUNCH_SELF);
	STR_LAUNCH_SELF = language(flang, "STR_LAUNCH_SELF", STR_LAUNCH_SELF_DEFAULT);
	FREE(STR_EXTRACT_EBOOT);
	STR_EXTRACT_EBOOT = language(flang, "STR_EXTRACT_EBOOT", STR_EXTRACT_EBOOT_DEFAULT);
	FREE(STR_RESIGN_EBOOT);
	STR_RESIGN_EBOOT = language(flang, "STR_RESIGN_EBOOT", STR_RESIGN_EBOOT_DEFAULT);
	FREE(STR_LAUNCH_EBOOT);
	STR_LAUNCH_EBOOT = language(flang, "STR_LAUNCH_EBOOT", STR_LAUNCH_EBOOT_DEFAULT);
	FREE(STR_SIGN_ELF);
	STR_SIGN_ELF = language(flang, "STR_SIGN_ELF", STR_SIGN_ELF_DEFAULT);
	FREE(STR_SIGN_EBOOT);
	STR_SIGN_EBOOT = language(flang, "STR_SIGN_EBOOT", STR_SIGN_EBOOT_DEFAULT);
	FREE(STR_SIGN_PRX);
	STR_SIGN_PRX = language(flang, "STR_SIGN_PRX", STR_SIGN_PRX_DEFAULT);
	FREE(STR_EXTRACT_PRX);
	STR_EXTRACT_PRX = language(flang, "STR_EXTRACT_PRX", STR_EXTRACT_PRX_DEFAULT);
	FREE(STR_RESIGN_SPRX);
	STR_RESIGN_SPRX = language(flang, "STR_RESIGN_SPRX", STR_RESIGN_SPRX_DEFAULT);
	FREE(STR_REMOVE_PRXLOADER);
	STR_REMOVE_PRXLOADER = language(flang, "STR_REMOVE_PRXLOADER", STR_REMOVE_PRXLOADER_DEFAULT);
	FREE(STR_ADD_PRXLOADER);
	STR_ADD_PRXLOADER = language(flang, "STR_ADD_PRXLOADER", STR_ADD_PRXLOADER_DEFAULT);
	FREE(STR_REMOVE_PRXLOADER2);
	STR_REMOVE_PRXLOADER2 = language(flang, "STR_REMOVE_PRXLOADER2", STR_REMOVE_PRXLOADER2_DEFAULT);
	FREE(STR_ADD_PRXLOADER2);
	STR_ADD_PRXLOADER2 = language(flang, "STR_ADD_PRXLOADER2", STR_ADD_PRXLOADER2_DEFAULT);
	FREE(STR_REMOVE_MAMBA);
	STR_REMOVE_MAMBA = language(flang, "STR_REMOVE_MAMBA", STR_REMOVE_MAMBA_DEFAULT);
	FREE(STR_ADD_MAMBA);
	STR_ADD_MAMBA = language(flang, "STR_ADD_MAMBA", STR_ADD_MAMBA_DEFAULT);
	FREE(STR_REMOVE_COBRA);
	STR_REMOVE_COBRA = language(flang, "STR_REMOVE_COBRA", STR_REMOVE_COBRA_DEFAULT);
	FREE(STR_ADD_COBRA);
	STR_ADD_COBRA = language(flang, "STR_ADD_COBRA", STR_ADD_COBRA_DEFAULT);
	FREE(STR_EXTRACT_RCO);
	STR_EXTRACT_RCO = language(flang, "STR_EXTRACT_RCO", STR_EXTRACT_RCO_DEFAULT);
	FREE(STR_EXTRACT_PKG);
	STR_EXTRACT_PKG = language(flang, "STR_EXTRACT_PKG", STR_EXTRACT_PKG_DEFAULT);
	FREE(STR_PKG_INFO);
	STR_PKG_INFO = language(flang, "STR_PKG_INFO", STR_PKG_INFO_DEFAULT);
	FREE(STR_EXTRACT_TRP);
	STR_EXTRACT_TRP = language(flang, "STR_EXTRACT_TRP", STR_EXTRACT_TRP_DEFAULT);
	FREE(STR_COMPRESS_ISO);
	STR_COMPRESS_ISO = language(flang, "STR_COMPRESS_ISO", STR_COMPRESS_ISO_DEFAULT);
	FREE(STR_CHECK_CRC32);
	STR_CHECK_CRC32 = language(flang, "STR_CHECK_CRC32", STR_CHECK_CRC32_DEFAULT);
	FREE(STR_DECOMPRESS_CSO);
	STR_DECOMPRESS_CSO = language(flang, "STR_DECOMPRESS_CSO", STR_DECOMPRESS_CSO_DEFAULT);
	FREE(STR_EXTRACT_THM);
	STR_EXTRACT_THM = language(flang, "STR_EXTRACT_THM", STR_EXTRACT_THM_DEFAULT);
	FREE(STR_EXTRACT_P3T);
	STR_EXTRACT_P3T = language(flang, "STR_EXTRACT_P3T", STR_EXTRACT_P3T_DEFAULT);
	FREE(STR_EXTRACT_RAF);
	STR_EXTRACT_RAF = language(flang, "STR_EXTRACT_RAF", STR_EXTRACT_RAF_DEFAULT);
	FREE(STR_EXTRACT_QRC);
	STR_EXTRACT_QRC = language(flang, "STR_EXTRACT_QRC", STR_EXTRACT_QRC_DEFAULT);
	FREE(STR_EXTRACT_ZIP);
	STR_EXTRACT_ZIP = language(flang, "STR_EXTRACT_ZIP", STR_EXTRACT_ZIP_DEFAULT);
	FREE(STR_CONVERT_JSX_JS);
	STR_CONVERT_JSX_JS = language(flang, "STR_CONVERT_JSX_JS", STR_CONVERT_JSX_JS_DEFAULT);
	FREE(STR_CONVERT_VAG_WAV);
	STR_CONVERT_VAG_WAV = language(flang, "STR_CONVERT_VAG_WAV", STR_CONVERT_VAG_WAV_DEFAULT);
	FREE(STR_CONVERT_GTF_DDS);
	STR_CONVERT_GTF_DDS = language(flang, "STR_CONVERT_GTF_DDS", STR_CONVERT_GTF_DDS_DEFAULT);
	FREE(STR_CONVERT_DDS_PNG);
	STR_CONVERT_DDS_PNG = language(flang, "STR_CONVERT_DDS_PNG", STR_CONVERT_DDS_PNG_DEFAULT);
	FREE(STR_MAKE_APNG);
	STR_MAKE_APNG = language(flang, "STR_MAKE_APNG", STR_MAKE_APNG_DEFAULT);
	FREE(STR_SET_PERMS);
	STR_SET_PERMS = language(flang, "STR_SET_PERMS", STR_SET_PERMS_DEFAULT);
	FREE(STR_NOGAME);
	STR_NOGAME = language(flang, "STR_NOGAME", STR_NOGAME_DEFAULT);
	FREE(STR_GLOB_SETTINGS);
	STR_GLOB_SETTINGS = language(flang, "STR_GLOB_SETTINGS", STR_GLOB_SETTINGS_DEFAULT);
	FREE(STR_ADJUST);
	STR_ADJUST = language(flang, "STR_ADJUST", STR_ADJUST_DEFAULT);
	FREE(STR_ADJUST_DESC);
	STR_ADJUST_DESC = language(flang, "STR_ADJUST_DESC", STR_ADJUST_DESC_DEFAULT);
	FREE(STR_DL_COVER);
	STR_DL_COVER = language(flang, "STR_DL_COVER", STR_DL_COVER_DEFAULT);
	FREE(STR_DL_COVER_DESC);
	STR_DL_COVER_DESC = language(flang, "STR_DL_COVER_DESC", STR_DL_COVER_DESC_DEFAULT);
	FREE(STR_PLUGIN_MANAGER);
	STR_PLUGIN_MANAGER = language(flang, "STR_PLUGIN_MANAGER", STR_PLUGIN_MANAGER_DEFAULT);
	FREE(STR_PLUGIN_MANAGER_DESC);
	STR_PLUGIN_MANAGER_DESC = language(flang, "STR_PLUGIN_MANAGER_DESC", STR_PLUGIN_MANAGER_DESC_DEFAULT);
	FREE(STR_UPD_MGZ);
	STR_UPD_MGZ = language(flang, "STR_UPD_MGZ", STR_UPD_MGZ_DEFAULT);
	FREE(STR_UPD_MGZ_DESC);
	STR_UPD_MGZ_DESC = language(flang, "STR_UPD_MGZ_DESC", STR_UPD_MGZ_DESC_DEFAULT);
	FREE(STR_GAME_PATHS);
	STR_GAME_PATHS = language(flang, "STR_GAME_PATHS", STR_GAME_PATHS_DEFAULT);
	FREE(STR_GAME_PATHS_DESC);
	STR_GAME_PATHS_DESC = language(flang, "STR_GAME_PATHS_DESC", STR_GAME_PATHS_DESC_DEFAULT);
	FREE(STR_XMB_PRIO);
	STR_XMB_PRIO = language(flang, "STR_XMB_PRIO", STR_XMB_PRIO_DEFAULT);
	FREE(STR_XMB_PRIO_DESC);
	STR_XMB_PRIO_DESC = language(flang, "STR_XMB_PRIO_DESC", STR_XMB_PRIO_DESC_DEFAULT);
	FREE(STR_HELP);
	STR_HELP = language(flang, "STR_HELP", STR_HELP_DEFAULT);
	FREE(STR_HELP_DESC);
	STR_HELP_DESC = language(flang, "STR_HELP_DESC", STR_HELP_DESC_DEFAULT);
	FREE(STR_COLOR_1);
	STR_COLOR_1 = language(flang, "STR_COLOR_1", STR_COLOR_1_DEFAULT);
	FREE(STR_COLOR_2);
	STR_COLOR_2 = language(flang, "STR_COLOR_2", STR_COLOR_2_DEFAULT);
	FREE(STR_COLOR_3);
	STR_COLOR_3 = language(flang, "STR_COLOR_3", STR_COLOR_3_DEFAULT);
	FREE(STR_COLOR_4);
	STR_COLOR_4 = language(flang, "STR_COLOR_4", STR_COLOR_4_DEFAULT);
	FREE(STR_COLOR_DESC);
	STR_COLOR_DESC = language(flang, "STR_COLOR_DESC", STR_COLOR_DESC_DEFAULT);
	FREE(STR_UI_SETTINGS);
	STR_UI_SETTINGS = language(flang, "STR_UI_SETTINGS", STR_UI_SETTINGS_DEFAULT);
	FREE(STR_UI);
	STR_UI = language(flang, "STR_UI", STR_UI_DEFAULT);
	FREE(STR_UI_DESC);
	STR_UI_DESC = language(flang, "STR_UI_DESC", STR_UI_DESC_DEFAULT);
	FREE(STR_SIDE_MENU);
	STR_SIDE_MENU = language(flang, "STR_SIDE_MENU", STR_SIDE_MENU_DEFAULT);
	FREE(STR_SIDE_MENU_DESC);
	STR_SIDE_MENU_DESC = language(flang, "STR_SIDE_MENU_DESC", STR_SIDE_MENU_DESC_DEFAULT);
	FREE(STR_SHOW_PIC1);
	STR_SHOW_PIC1 = language(flang, "STR_SHOW_PIC1", STR_SHOW_PIC1_DEFAULT);
	FREE(STR_SHOW_PIC1_DESC);
	STR_SHOW_PIC1_DESC = language(flang, "STR_SHOW_PIC1_DESC", STR_SHOW_PIC1_DESC_DEFAULT);
	FREE(STR_SHOW_COVER);
	STR_SHOW_COVER = language(flang, "STR_SHOW_COVER", STR_SHOW_COVER_DEFAULT);
	FREE(STR_SHOW_COVER_DESC);
	STR_SHOW_COVER_DESC = language(flang, "STR_SHOW_COVER_DESC", STR_SHOW_COVER_DESC_DEFAULT);
	FREE(STR_SHOW_GAMECASE);
	STR_SHOW_GAMECASE = language(flang, "STR_SHOW_GAMECASE", STR_SHOW_GAMECASE_DEFAULT);
	FREE(STR_SHOW_GAMECASE_DESC);
	STR_SHOW_GAMECASE_DESC = language(flang, "STR_SHOW_GAMECASE_DESC", STR_SHOW_GAMECASE_DESC_DEFAULT);
	FREE(STR_SHOW_ICON0);
	STR_SHOW_ICON0 = language(flang, "STR_SHOW_ICON0", STR_SHOW_ICON0_DEFAULT);
	FREE(STR_SHOW_ICON0_DESC);
	STR_SHOW_ICON0_DESC = language(flang, "STR_SHOW_ICON0_DESC", STR_SHOW_ICON0_DESC_DEFAULT);
	FREE(STR_GRID_TYPE);
	STR_GRID_TYPE = language(flang, "STR_GRID_TYPE", STR_GRID_TYPE_DEFAULT);
	FREE(STR_GRID_TYPE_DESC);
	STR_GRID_TYPE_DESC = language(flang, "STR_GRID_TYPE_DESC", STR_GRID_TYPE_DESC_DEFAULT);
	FREE(STR_SCROLL);
	STR_SCROLL = language(flang, "STR_SCROLL", STR_SCROLL_DEFAULT);
	FREE(STR_PAGE);
	STR_PAGE = language(flang, "STR_PAGE", STR_PAGE_DEFAULT);
	FREE(STR_DIRECTION);
	STR_DIRECTION = language(flang, "STR_DIRECTION", STR_DIRECTION_DEFAULT);
	FREE(STR_DIRECTION_DESC);
	STR_DIRECTION_DESC = language(flang, "STR_DIRECTION_DESC", STR_DIRECTION_DESC_DEFAULT);
	FREE(STR_VERTICAL);
	STR_VERTICAL = language(flang, "STR_VERTICAL", STR_VERTICAL_DEFAULT);
	FREE(STR_HORIZONTAL);
	STR_HORIZONTAL = language(flang, "STR_HORIZONTAL", STR_HORIZONTAL_DEFAULT);
	FREE(STR_ANIMATED);
	STR_ANIMATED = language(flang, "STR_ANIMATED", STR_ANIMATED_DEFAULT);
	FREE(STR_ANIMATED_DESC);
	STR_ANIMATED_DESC = language(flang, "STR_ANIMATED_DESC", STR_ANIMATED_DESC_DEFAULT);
	FREE(STR_KEEP_PROP);
	STR_KEEP_PROP = language(flang, "STR_KEEP_PROP", STR_KEEP_PROP_DEFAULT);
	FREE(STR_KEEP_PROP_DESC);
	STR_KEEP_PROP_DESC = language(flang, "STR_KEEP_PROP_DESC", STR_KEEP_PROP_DESC_DEFAULT);
	FREE(STR_NB_COL);
	STR_NB_COL = language(flang, "STR_NB_COL", STR_NB_COL_DEFAULT);
	FREE(STR_NB_COL_DESC);
	STR_NB_COL_DESC = language(flang, "STR_NB_COL_DESC", STR_NB_COL_DESC_DEFAULT);
	FREE(STR_NB_LINE);
	STR_NB_LINE = language(flang, "STR_NB_LINE", STR_NB_LINE_DEFAULT);
	FREE(STR_NB_LINE_DESC);
	STR_NB_LINE_DESC = language(flang, "STR_NB_LINE_DESC", STR_NB_LINE_DESC_DEFAULT);
	FREE(STR_INVERSE);
	STR_INVERSE = language(flang, "STR_INVERSE", STR_INVERSE_DEFAULT);
	FREE(STR_INVERSE_DESC);
	STR_INVERSE_DESC = language(flang, "STR_INVERSE_DESC", STR_INVERSE_DESC_DEFAULT);
	FREE(STR_3D);
	STR_3D = language(flang, "STR_3D", STR_3D_DEFAULT);
	FREE(STR_3D_DESC);
	STR_3D_DESC = language(flang, "STR_3D_DESC", STR_3D_DESC_DEFAULT);
	FREE(STR_ADD);
	STR_ADD = language(flang, "STR_ADD", STR_ADD_DEFAULT);
	FREE(STR_LOAD);
	STR_LOAD = language(flang, "STR_LOAD", STR_LOAD_DEFAULT);
	FREE(STR_CHANGE);
	STR_CHANGE = language(flang, "STR_CHANGE", STR_CHANGE_DEFAULT);
	FREE(STR_COLOR);
	STR_COLOR = language(flang, "STR_COLOR", STR_COLOR_DEFAULT);
	FREE(STR_RESET);
	STR_RESET = language(flang, "STR_RESET", STR_RESET_DEFAULT);
	FREE(STR_FAILED);
	STR_FAILED = language(flang, "STR_FAILED", STR_FAILED_DEFAULT);
	FREE(STR_DONE);
	STR_DONE = language(flang, "STR_DONE", STR_DONE_DEFAULT);
	FREE(STR_OPEN);
	STR_OPEN = language(flang, "STR_OPEN", STR_OPEN_DEFAULT);
	FREE(STR_CLOSE);
	STR_CLOSE = language(flang, "STR_CLOSE", STR_CLOSE_DEFAULT);
	FREE(STR_OPTION);
	STR_OPTION = language(flang, "STR_OPTION", STR_OPTION_DEFAULT);
	FREE(STR_SELECT);
	STR_SELECT = language(flang, "STR_SELECT", STR_SELECT_DEFAULT);
	FREE(STR_WINDOW);
	STR_WINDOW = language(flang, "STR_WINDOW", STR_WINDOW_DEFAULT);
	FREE(STR_CLICK);
	STR_CLICK = language(flang, "STR_CLICK", STR_CLICK_DEFAULT);
	FREE(STR_CURSOR);
	STR_CURSOR = language(flang, "STR_CURSOR", STR_CURSOR_DEFAULT);
	FREE(STR_NEXT);
	STR_NEXT = language(flang, "STR_NEXT", STR_NEXT_DEFAULT);
	FREE(STR_PREVIOUS);
	STR_PREVIOUS = language(flang, "STR_PREVIOUS", STR_PREVIOUS_DEFAULT);
	FREE(STR_SET_COLOR);
	STR_SET_COLOR = language(flang, "STR_SET_COLOR", STR_SET_COLOR_DEFAULT);
	FREE(STR_HIDETV);
	STR_HIDETV = language(flang, "STR_HIDETV", STR_HIDETV_DEFAULT);
	FREE(STR_SHOWTV);
	STR_SHOWTV = language(flang, "STR_SHOWTV", STR_SHOWTV_DEFAULT);
	FREE(STR_MOVE_TO_PLUGINS);
	STR_MOVE_TO_PLUGINS = language(flang, "STR_MOVE_TO_PLUGINS", STR_MOVE_TO_PLUGINS_DEFAULT);
	FREE(STR_ASK_PLUGINS);
	STR_ASK_PLUGINS = language(flang, "STR_ASK_PLUGINS", STR_ASK_PLUGINS_DEFAULT);
	FREE(STR_CHANGE_VALUE);
	STR_CHANGE_VALUE = language(flang, "STR_CHANGE_VALUE", STR_CHANGE_VALUE_DEFAULT);
	FREE(STR_LOAD_IDPS_LV2);
	STR_LOAD_IDPS_LV2 = language(flang, "STR_LOAD_IDPS_LV2", STR_LOAD_IDPS_LV2_DEFAULT);
	FREE(STR_LOAD_IDPS_EID5);
	STR_LOAD_IDPS_EID5 = language(flang, "STR_LOAD_IDPS_EID5", STR_LOAD_IDPS_EID5_DEFAULT);
	FREE(STR_NAME);
	STR_NAME = language(flang, "STR_NAME", STR_NAME_DEFAULT);
	FREE(STR_DOCK_RIGHT);
	STR_DOCK_RIGHT = language(flang, "STR_DOCK_RIGHT", STR_DOCK_RIGHT_DEFAULT);
	FREE(STR_DOCK_LEFT);
	STR_DOCK_LEFT = language(flang, "STR_DOCK_LEFT", STR_DOCK_LEFT_DEFAULT);
	FREE(STR_DOCK_FULL);
	STR_DOCK_FULL = language(flang, "STR_DOCK_FULL", STR_DOCK_FULL_DEFAULT);
	FREE(STR_PLUGIN_MONITOR);
	STR_PLUGIN_MONITOR = language(flang, "STR_PLUGIN_MONITOR", STR_PLUGIN_MONITOR_DEFAULT);
	FREE(STR_UNUSED);
	STR_UNUSED = language(flang, "STR_UNUSED", STR_UNUSED_DEFAULT);
	FREE(STR_UNLOAD);
	STR_UNLOAD = language(flang, "STR_UNLOAD", STR_UNLOAD_DEFAULT);
	FREE(STR_BOOT_FILE);
	STR_BOOT_FILE = language(flang, "STR_BOOT_FILE", STR_BOOT_FILE_DEFAULT);
	FREE(STR_CURRENT);
	STR_CURRENT = language(flang, "STR_CURRENT", STR_CURRENT_DEFAULT);	
	FREE(STR_NET);
	STR_NET = language(flang, "STR_NET", STR_NET_DEFAULT);
	FREE(STR_SOFT);
	STR_SOFT = language(flang, "STR_SOFT", STR_SOFT_DEFAULT);	
	FREE(STR_GX);
	STR_GX = language(flang, "STR_GX", STR_GX_DEFAULT);
	FREE(STR_CUSTOM);
	STR_CUSTOM = language(flang, "STR_CUSTOM", STR_CUSTOM_DEFAULT);
	FREE(STR_NEW_CMD);
	STR_NEW_CMD = language(flang, "STR_NEW_CMD", STR_NEW_CMD_DEFAULT);	
	FREE(STR_PNACH);
	STR_PNACH = language(flang, "STR_PNACH", STR_PNACH_DEFAULT);
	FREE(STR_WIDESCREEN);
	STR_WIDESCREEN = language(flang, "STR_WIDESCREEN", STR_WIDESCREEN_DEFAULT);
	FREE(STR_480P);
	STR_480P = language(flang, "STR_480P", STR_480P_DEFAULT);
	FREE(STR_YFIX);
	STR_YFIX = language(flang, "STR_YFIX", STR_YFIX_DEFAULT);	
	FREE(STR_FMV);
	STR_FMV = language(flang, "STR_FMV", STR_FMV_DEFAULT);
	FREE(STR_SIMPLE);
	STR_SIMPLE = language(flang, "STR_SIMPLE", STR_SIMPLE_DEFAULT);	
	FREE(STR_ADVANCED);
	STR_ADVANCED = language(flang, "STR_ADVANCED", STR_ADVANCED_DEFAULT);
	FREE(STR_INSTALL_MGZ);
	STR_INSTALL_MGZ = language(flang, "STR_INSTALL_MGZ", STR_INSTALL_MGZ_DEFAULT);
	FREE(STR_UP2DATE);
	STR_UP2DATE = language(flang, "STR_UP2DATE", STR_UP2DATE_DEFAULT);	
	FREE(STR_SHOW_WAVES);
	STR_SHOW_WAVES = language(flang, "STR_SHOW_WAVES", STR_SHOW_WAVES_DEFAULT);
	FREE(STR_SHOW_WAVES_DESC);
	STR_SHOW_WAVES_DESC = language(flang, "STR_SHOW_WAVES_DESC", STR_SHOW_WAVES_DESC_DEFAULT);
	FREE(STR_WAVES_COLOR);
	STR_WAVES_COLOR = language(flang, "STR_WAVES_COLOR", STR_WAVES_COLOR_DEFAULT);
	FREE(STR_WAVES_COLOR_DESC);
	STR_WAVES_COLOR_DESC = language(flang, "STR_WAVES_COLOR_DESC", STR_WAVES_COLOR_DESC_DEFAULT);
	FREE(STR_USE_CONFIG);
	STR_USE_CONFIG = language(flang, "STR_USE_CONFIG", STR_USE_CONFIG_DEFAULT);
	FREE(STR_COLORSET);
	STR_COLORSET = language(flang, "STR_COLORSET", STR_COLORSET_DEFAULT);
	FREE(STR_COLORSET_DESC);
	STR_COLORSET_DESC = language(flang, "STR_COLORSET_DESC", STR_COLORSET_DESC_DEFAULT);
	FREE(STR_GRID_SCROLL);
	STR_GRID_SCROLL = language(flang, "STR_GRID_SCROLL", STR_GRID_SCROLL_DEFAULT);
	FREE(STR_ADD_LIMG);
	STR_ADD_LIMG = language(flang, "STR_ADD_LIMG", STR_ADD_LIMG_DEFAULT);
	FREE(STR_REMOVE_LIMG);
	STR_REMOVE_LIMG = language(flang, "STR_REMOVE_LIMG", STR_REMOVE_LIMG_DEFAULT);
	FREE(STR_LIMG_DESC);
	STR_LIMG_DESC = language(flang, "STR_LIMG_DESC", STR_LIMG_DESC_DEFAULT);
	FREE(STR_FONT);
	STR_FONT = language(flang, "STR_FONT", STR_FONT_DEFAULT);
	FREE(STR_FONT_DESC);
	STR_FONT_DESC = language(flang, "STR_FONT_DESC", STR_FONT_DESC_DEFAULT);
	FREE(STR_MOVE);
	STR_MOVE = language(flang, "STR_MOVE", STR_MOVE_DEFAULT);
	FREE(STR_JOIN);
	STR_JOIN = language(flang, "STR_JOIN", STR_JOIN_DEFAULT);
	FREE(STR_JOIN_DESC);
	STR_JOIN_DESC = language(flang, "STR_JOIN_DESC", STR_JOIN_DESC_DEFAULT);
	
	FCLOSE(flang);
	lang_code_loaded = lang_code;
}

void load_lang()
{
	int i;
	
#ifndef RPCS3	
	if(lang_code == LANG_UNDEFINED) lang_code = get_xreg_value((char*)"/setting/system/language");
#endif

	for(i=0; i < lang_N ;i++) {
		if((uint8_t) STR_LANGCODE[i][0] == lang_code) {
			lang = i;
			write_setting();
			return;
		}
	}
	
	lang = 0;
	lang_code = LANG_DEFAULT;
	
	write_setting();
}

//###################################################
//	THEME
//###################################################

uint32_t convert32(char * bytes);
uint16_t convert16(char * bytes);

typedef struct
{
	u32 magic;
	u32 version;
	char Name[0x40];
	u8 file_number;
} thm_header;

typedef struct
{
	u32 Offset;
	u32 Size;
	char Name[0x40];
} thm_file;

u8 ExtractTHM(char *thm)
{
	FILE* f=NULL;
	int i;
	thm_header header;
	thm_file file;
	char file_path[255];
	char dir[255];
	strcpy(dir, thm);
	dir[strlen(dir)-4]=0;
	
	Delete(dir);
	if( mkdir(dir, 0777) != 0) {
		print_load("Error : failed to create dir %s", dir);
		return FAILED;
	}
	
	f=fopen(thm, "rb");
	if(f==NULL) {
		print_load("Error : Failed to open thm file");
		return FAILED;
	}
	
	fread(&header, 0x49, 1, f);

	if( header.magic != 0x434D544D ) {
		print_load("Error : bad magic");
		fclose(f);
		return FAILED;
	}

	for(i=0 ; i < header.file_number; i++){
		fseek(f, 0x49 + 0x48*i, SEEK_SET);
		
		fread(&file, sizeof(thm_file), 1, f);
		
		uint8_t *data = (uint8_t *) malloc(file.Size);
		if(data == NULL) {
			print_load("Error : failed to malloc %s %d",  file.Size, file.Name);
			fclose(f);
			return FAILED;
		}
		fseek(f, file.Offset, SEEK_SET);
		fread(data, file.Size, 1, f);
		
		FILE* fp;
		sprintf(file_path, "%s/%s", dir, file.Name);
		fp = fopen(file_path, "wb");
		if(f==NULL) {
			print_load("Error : failed to create %s", file.Name);
			fclose(f);
			fclose(fp);
			free(data);
			return FAILED;
		}
		fwrite(data, file.Size, 1, fp);
		fclose(fp);
		free(data);
	}
	
	fclose(f);
	
	return SUCCESS;
}

u8 GetFromTHM(char *thm, char *file, char *dst)
{
	FILE* f=NULL;
	uint8_t nb_files;
	int i;
	char fileName[0x40];
	uint32_t fileSize=0;
	uint32_t fileOffset=0;

	f=fopen(thm, "rb");
	if(f==NULL) {
		print_load("Error : Failed to open thm file");
		return FAILED;
	}
	
	if(strcmp(file, "name") == 0 ) {
		fseek(f, 0x8, SEEK_SET);
		fread(fileName, 1, 0x40, f);
		fclose(f);
		strcpy(dst, fileName);
		return SUCCESS;
	}
	
	fseek(f, 0x48, SEEK_SET);
	fread(&nb_files, 1, 1, f);

	for(i=0 ; i<nb_files; i++){
		fseek(f, 0x51 + i*0x48, SEEK_SET);
		fread(fileName, 1, 0x40, f);
		if(strcmp(file, fileName) == 0) {
			fseek(f, 0x51 + i*0x48 - 0x8, SEEK_SET);
			fread(&fileOffset, 1, 4, f);
			fread(&fileSize, 1, 4, f);
			break;
		}
	}
	
	if(fileSize==0 || fileOffset==0) {
		print_load("Error : %s not found", file, fileSize, fileOffset);
		return FAILED;
	}
	uint8_t *data = (uint8_t *) malloc(fileSize);
	
	fseek(f, fileOffset, SEEK_SET);
	fread(data, 1, fileSize, f);
	fclose(f);
	
	f=fopen(dst, "wb");
	if(f==NULL) {
		print_load("Error : failed to open %s", dst);
		free(data);
		return FAILED;
	}
	
	fwrite(data, 1, fileSize, f);
	fclose(f);
	
	free(data);
	
	return SUCCESS;
}

extern int gim2png(const char* gimfilename,char* pngfilename);
extern int uncompressGIMBuffer(void* compressed_buffer, size_t compressed_buffer_size, void** gim_buffer);
int GIM2PNG(char *in, char *out)
{
	return gim2png(in, out);
}
int VAG2WAV(char *in, char *out)
{
	return vag_to_wav(in, out);
}
void JSX2JS(char *in, char *out)
{
	JSX_to_JS(in, out);
}

u8 GetFromP3T(char *src, char *file, char *dst)
{

 // *** header ***
	//u32 magic = 0x50335446;	// 0x00 "P3TF"
	//u32 version;				// 0x04
	u32 tree_table_offset;   	// 0x08
	u32 tree_table_size; 		// 0x0C
	u32 ID_table_offset; 		// 0x10
	u32 ID_table_size;			// 0x14
	u32 string_table_offset;	// 0x18
	u32 string_table_size;	// 0x1C
	//u32 integer_array_offset; // 0x20
	//u32 integer_array_size; 	// 0x2C
	//u32 float_Array_offset;	// 0x28
	//u32 float_array_size;		// 0x2C
	u32 file_table_offset;		// 0x30
	//u32 file_table_size;		// 0x34
	//u32 unk_table_offset;		// 0x38
	//u32 unk_table_size;		// 0x3C
	
	u32 file_offset;
	u32 file_size_c;
	int file_size_d;
	u8 GRID_ANIMATED = NO;
	FILE* fp;
	
	fp=fopen(src, "rb");
	if(fp==NULL) {
		print_load("Error : can't read file %s", src);
		return FAILED;
	}
	
	fseek(fp, 0x8, SEEK_SET);
	fread(&tree_table_offset, sizeof(u32), 1, fp);
	fread(&tree_table_size, sizeof(u32), 1, fp);
	fread(&ID_table_offset, sizeof(u32), 1, fp);
	fread(&ID_table_size, sizeof(u32), 1, fp);
	fread(&string_table_offset, sizeof(u32), 1, fp);
	fread(&string_table_size, sizeof(u32), 1, fp);
	
	fseek(fp, 0x30, SEEK_SET);
	fread(&file_table_offset, sizeof(u32), 1, fp);
	
//UGLY !
	if(strcmp(file, "background") == 0 ) {
		fseek(fp, string_table_offset, SEEK_SET);
		
		u8 *string_table = (u8 *) malloc(string_table_size);
		
		fread(string_table, string_table_size, 1, fp);
		u32 flag=0;
		u32 temp;
		unsigned int n;
		for(n=0; n < string_table_size; n++){
			if(memcmp((char *) &string_table[n], "anim\0", 5) == 0) {
				GRID_ANIMATED = YES;
				flag=n;
				break;
			} else
			if(memcmp((char *) &string_table[n], "hd\0", 3) == 0) {
				flag=n;
				break;
			}
		}
		free(string_table);
		
		if(flag == 0) return FAILED;
		
		fseek(fp, 0x40, SEEK_SET);
		
		for(n=0; n < tree_table_size/4; n++){
			fread(&temp, sizeof(u32), 1, fp);
			if(temp==flag) {
				fread(&temp, sizeof(u32), 1, fp);
				if(temp==6) {
					fread(&file_offset, sizeof(u32), 1, fp);
					fread(&file_size_c, sizeof(u32), 1, fp);
					break;
				}
			}
		}
		if(temp != 6) return FAILED;
	}
	else if(strcmp(file, "name") == 0) {
		fseek(fp, string_table_offset, SEEK_SET);
		
		u8 *string_table = (u8 *) malloc(string_table_size);
		fread(string_table, string_table_size, 1, fp);
		fclose(fp);
		
		unsigned int n;
		for(n=0; n < string_table_size; n++){
			if(memcmp((char *) &string_table[n], "name\0", 5) == 0) {
				strcpy((char *) dst, (char *) &string_table[n+5]);
				free(string_table);
				return SUCCESS;
			}
		}
		return FAILED;
	}
	else {
		fseek(fp, ID_table_offset, SEEK_SET);
		u32 file_tree_table_offset = 0;
		u8 *ID_table = (u8 *) malloc(ID_table_size);
		
		fread(ID_table, ID_table_size, 1, fp);
		
		unsigned int n;
		for(n=0; n < ID_table_size; n++){
			if(memcmp((char *) &ID_table[n], (char *) file, strlen(file)) == 0 && memcmp((char *) &ID_table[n+strlen(file)], "\0", 1) == 0) {
				memcpy(&file_tree_table_offset, &ID_table[n-4], 4);
				file_tree_table_offset += tree_table_offset;
				break;
			}
		}
		
		free(ID_table);
		
		if(file_tree_table_offset<=tree_table_offset) {
			fclose(fp);
			print_load("Error : File not found in ID_table");	
			return FAILED;
		}
		
		fseek(fp, file_tree_table_offset + 0x24, SEEK_SET);
		fread(&file_offset, sizeof(u32), 1, fp);
		fread(&file_size_c, sizeof(u32), 1, fp);
		
	}
	
	file_offset += file_table_offset;
	
	fseek(fp, file_offset, SEEK_SET);
	
	char *file_data_c = (char *) malloc(file_size_c);
	if(!file_data_c) {
		print_load("Error : failed to malloc file_size_c");
		return FAILED;
	}
	
	fread(file_data_c, file_size_c, 1, fp);
	fclose(fp);

	if(strcmp(file, "background") == 0) {
		if(GRID_ANIMATED == NO) {
			fp=fopen(dst, "wb");
			fwrite(file_data_c, file_size_c, 1, fp);
			fclose(fp);
			free(file_data_c);
		} else {
			u32 RAF_size = convert32(&file_data_c[4]);
			u8 *RAF_data = (u8 *) malloc(RAF_size);
			RAF_size = 0;
			zlib_decompress((char *) &file_data_c[8], (char *) RAF_data, file_size_c, (int *) &RAF_size);
			
			free(file_data_c);
			
			if(RAF_size != 0) {
				char raf_tmp[128];
				char tmp_dir[128];
				sprintf(tmp_dir, "/dev_hdd0/game/%s/USRDIR/temp", ManaGunZ_id);
				//Delete(tmp_dir);
				mkdir(tmp_dir, 0777);
				
				sprintf(raf_tmp, "%s/bg_anim.raf", tmp_dir);
				
				fp=fopen(raf_tmp, "wb");
				if(fp==NULL) return FAILED;
				fwrite(RAF_data, RAF_size, 1, fp);
				fclose(fp);
				
				free(RAF_data);
				
				print_head("Extracting Background...");
				cxml_extract(raf_tmp);
				
				sprintf(raf_tmp, "%s/bg_anim", tmp_dir);
				
				dst[strlen(dst)-3] = 'P';
				dst[strlen(dst)-2] = 'N';
				dst[strlen(dst)-1] = 'G';
				
				print_head("Making GRID_ANIMATED Background...");
				if(make_ABG((char *) raf_tmp, (char *) dst)  == FAILED) {
					Delete(tmp_dir);
					print_load("Error : Failed to build Animated Background");
					return FAILED;
				}
				Delete(tmp_dir);
				
			} else free(RAF_data);
		}
	}
	else {
		void* file_data_d;
		file_size_d = uncompressGIMBuffer(file_data_c, file_size_c, &file_data_d);	
		free(file_data_c);
		
		// .gim to .png
		char gim[128];
		strcpy(gim, dst);
		RemoveExtention(gim);
		strcat(gim, ".gim");
		fp=fopen(gim, "wb");

		if(fp==NULL) {
			print_load("Error : cannot write file %s", dst);
			return FAILED;
		}
		fwrite(file_data_d, file_size_d, 1, fp);
		fclose(fp);
		
		if( gim2png((char *) gim, (char *) dst) == false) {
			print_load("Error : to convert gim to png");
			return FAILED;
		} 
		remove(gim);
		
	}

	return SUCCESS;
}

u8 ExtractQRC(char *src)
{
	
	int qrc_size;
	
	char *qrc = LoadFile(src, &qrc_size);
	if(qrc==NULL) {
		print_load("Error : Failed to load qrc");
		return FAILED;
	}
	
	if(memcmp((char *) qrc, (char *) "QRCF", 4) == 0) {
		cxml_extract(src);
		return SUCCESS;
	}

	
	if(memcmp((char *) qrc, (char *) "QRCC", 4) != 0) {
		print_load("Error : bad magic QRCC");
		return FAILED;
	}
	
	u32 qrcf_size = convert32(&qrc[4]);
	u8 *qrcf = (u8 *) malloc(qrcf_size);
	qrcf_size = 0;
	
	zlib_decompress((char *) &qrc[8], (char *) qrcf, qrc_size, (int *) &qrcf_size);
			
	free(qrc);
			
	if(qrcf_size != 0) {
		
		char dst[255];

		if(strstr(src, "dev_flash") != NULL) {
			strcpy(dst, "/dev_hdd0/tmp");
			mkdir(dst, 0777);
			strcat(dst, "/CXML");
			mkdir(dst, 0777);
			strcat(dst, &strrchr(src, '/')[1]);
		} 
		else strcpy(dst, src);
		
		strcat(dst, "f"); //QRCF
	
		FILE* fp;
		
		fp=fopen(dst, "wb");
		if(fp==NULL) return FAILED;
		fwrite(qrcf, qrcf_size, 1, fp);
		fclose(fp);
		
		free(qrcf);
		
		cxml_extract(dst);
		
		return SUCCESS;
	}
	
	return FAILED;
}

#define RAFO_INTEGER		1
#define RAFO_FLOAT	 		2
#define RAFO_STRING	 		3
#define RAFO_INT_ARRAY		4
#define RAFO_FLOAT_ARRAY	5
#define RAFO_FILE	 		6
#define RAFO_ID_WITH_REF	7
#define RAFO_ID				8

void ExtractRAFO(char *src)
{
	// *** header ***
	//u32 magic = 0x5241464F;	// 0x00 "RAFO"
	//u32 version;				// 0x04
	u32 tree_table_offset;   	// 0x08
	u32 tree_table_size; 		// 0x0C
	u32 ID_table_offset; 		// 0x10
	u32 ID_table_size;			// 0x14
	u32 string_table_offset;	// 0x18
	u32 string_table_size;		// 0x1C
	//u32 integer_array_offset; // 0x20
	//u32 integer_array_size; 	// 0x2C
	//u32 float_Array_offset;	// 0x28
	//u32 float_array_size;		// 0x2C
	u32 file_table_offset;		// 0x30
	//u32 file_table_size;		// 0x34
	//u32 unk_table_offset;		// 0x38
	//u32 unk_table_size;		// 0x3C

	char dst[128];
	strcpy(dst, src);
	dst[strlen(dst)-4]=0;
	mkdir(dst, 0777);
	
	FILE* fp;
	fp=fopen(src, "rb");
	if(fp==NULL) {print_load("Error : can't read file %s", src); return;}
	
	fseek(fp, 0x8, SEEK_SET);
	fread(&tree_table_offset, sizeof(u32), 1, fp);
	fread(&tree_table_size, sizeof(u32), 1, fp);
	fread(&ID_table_offset, sizeof(u32), 1, fp);
	fread(&ID_table_size, sizeof(u32), 1, fp);
	fread(&string_table_offset, sizeof(u32), 1, fp);
	fread(&string_table_size, sizeof(u32), 1, fp);
	
	fseek(fp, 0x30, SEEK_SET);
	fread(&file_table_offset, sizeof(u32), 1, fp);
	
	fseek(fp, ID_table_offset, SEEK_SET);
	
	u32 item_offset, type, file_offset, file_size;
	u32 pos = ftell(fp);
	
	char name[128];
	while( pos < ID_table_offset + ID_table_size) {
		type=0; file_offset=0; item_offset=0; file_size=0;
		memset(name, 0, 128);
		
		fread(&item_offset,  sizeof(u32), 1, fp);
		char c = fgetc(fp);
		while( c != 0 ) {
			name[strlen(name)]=c;
			c = fgetc(fp);
		}
		
		pos = ftell(fp);
		
		fseek(fp, item_offset+0x40+0x20, SEEK_SET);
		
		fread(&type,  sizeof(u32), 1, fp);

		if(type ==  RAFO_FILE) {
			
			fread(&file_offset,  sizeof(u32), 1, fp);
			fread(&file_size,  sizeof(u32), 1, fp);
			
			fseek(fp, file_table_offset+file_offset, SEEK_SET);
			
			u8 *data = (u8 *) malloc(file_size);
			fread(data, file_size, 1, fp);
			
			char dst_file[128];
			FILE* out;
			sprintf(dst_file, "%s/%s", dst, name);
			out = fopen(dst_file, "wb");
			fwrite(data, file_size, 1, out);
			fclose(out);
			
			free(data);
		}
		
		fseek(fp, pos, SEEK_SET);
	}
	fclose(fp);
}

u8 GetThemeType(char *ThemePath)
{
	int len = strlen(ThemePath)-4;
	
	if( ThemePath[len] == '.'
	&& (ThemePath[len+1] == 't' || ThemePath[len+1] == 'T')
	&& (ThemePath[len+2] == 'h' || ThemePath[len+2] == 'H')
	&& (ThemePath[len+3] == 'm' || ThemePath[len+3] == 'M') ) {
		return THM;
	}
	else if(ThemePath[len] == '.'
	&& (ThemePath[len+1] == 'p' || ThemePath[len+1] == 'P')
	&& (ThemePath[len+2] == '3')
	&& (ThemePath[len+3] == 't' || ThemePath[len+3] == 'T') ) {
		return P3T;
	}
	else return MGZ;
	
}

void GetThemes()
{
	char THM_path[255];
	char THM_subpath[255];
	
	char TempPath[255];
	char TempName[255];
	int i;
	u8 ret;
	
	Themes_number[0]=-1;
	Themes_number[1]=-1;
	Themes_number[2]=-1;
	Themes_number[3]=-1;

	memset(Themes_Paths_list, 0, sizeof(Themes_Paths_list));
	memset(Themes_Names_list, 0, sizeof(Themes_Names_list));

	for(i=0; i<=device_number; i++) {
		
		if(strstr(list_device[i], "dev_usb") != NULL) {
			sprintf(THM_path, "/%s/Themes", list_device[i]);
		} else
		if(strstr(list_device[i], "ntfs") != NULL) {
			sprintf(THM_path, "/%s/Themes", list_device[i]);
		} else
		if(strstr(list_device[i], "dev_hdd0") != NULL) {
			sprintf(THM_path, "/dev_hdd0/game/%s/USRDIR/GUI", ManaGunZ_id);
		} else continue;
		
		DIR *d;
		struct dirent *dir;
	
		d = opendir(THM_path);
		if(d==NULL) continue;
	
		while ((dir = readdir(d))) {
			if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
			
			int k = -1;
			u8 ThemeType = GetThemeType(dir->d_name);
			
			if(ThemeType == THM) {
				
				sprintf(TempPath, "%s/%s", THM_path, dir->d_name);
				ret = GetFromTHM(TempPath, "name", TempName);
				if(ret==FAILED) {
					memcpy(TempName, dir->d_name, strlen(dir->d_name)-4);
				}
				
				Themes_number[XMB]++;
				strcpy(Themes_Paths_list[XMB][Themes_number[XMB]], TempPath);
				strcpy(Themes_Names_list[XMB][Themes_number[XMB]], TempName);
				
				Themes_number[FLOW]++;
				strcpy(Themes_Paths_list[FLOW][Themes_number[FLOW]], TempPath);
				strcpy(Themes_Names_list[FLOW][Themes_number[FLOW]], TempName);
				
				continue;
			} else
			if(ThemeType == P3T) {
			
				sprintf(TempPath, "%s/%s", THM_path, dir->d_name);
				ret = GetFromP3T(TempPath, "name", TempName);
				if(ret==FAILED) {
					memcpy(TempName, dir->d_name, strlen(dir->d_name)-4);
				}
				
				Themes_number[XMB]++;
				strcpy(Themes_Paths_list[XMB][Themes_number[XMB]], TempPath);
				strcpy(Themes_Names_list[XMB][Themes_number[XMB]], TempName);
				
				continue;
			}
			else if(strcmp(dir->d_name, UI[0]) == 0) k=LIST;
			else if(strcmp(dir->d_name, UI[1]) == 0) k=GRID;					
			else if(strcmp(dir->d_name, UI[2]) == 0) k=XMB;
			else if(strcmp(dir->d_name, UI[3]) == 0) k=FLOW;
			
			if(k==-1) continue;
			
			sprintf(THM_subpath, "%s/%s", THM_path, dir->d_name);
			DIR *d2;
			struct dirent *dir2;

			d2 = opendir(THM_subpath);
			if(d2==NULL) continue;
		
			while ((dir2 = readdir(d2))) {
				if(!strncmp(dir2->d_name,"..", 2) || !strncmp(dir2->d_name,".", 1)) continue;

				sprintf(TempPath, "%s/%s", THM_subpath, dir2->d_name);
				strcpy(TempName, dir2->d_name);
				
				Themes_number[k]++;
				strcpy(Themes_Paths_list[k][Themes_number[k]], TempPath);
				strcpy(Themes_Names_list[k][Themes_number[k]], TempName);
			}
			closedir(d2);
		}
		closedir(d);
	}
	
}

u8 InstallTheme()
{
	char folder[255];
	u8 ret=SUCCESS;
	
	if(strstr(Themes_Paths_list[UI_position][Themes_position[UI_position]], "dev_hdd0") != NULL) {
		strcpy(Themes[UI_position], Themes_Names_list[UI_position][Themes_position[UI_position]]);
		return SUCCESS;
	}
	
	u8 ThemeType = GetThemeType( Themes_Paths_list[UI_position][Themes_position[UI_position]]);
	
	sprintf(folder, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position], Themes_Names_list[UI_position][Themes_position[UI_position]]);
	
	print_head("Installing Theme...");
			
	mkdir(folder, 0777);
	
	if(ThemeType == THM) {
		
		char dst[255];
		
		if(UI_position == FLOW) {
			
			sprintf(dst, "%s/BG.PNG", folder);
			ret=GetFromTHM(Themes_Paths_list[UI_position][Themes_position[UI_position]], "PICPA.PNG" , dst);
			
			sprintf(dst, "%s/BGS.JPG", folder);
			ret=GetFromTHM(Themes_Paths_list[UI_position][Themes_position[UI_position]], "PSVBG.JPG" , dst);
			
		}
		else if(UI_position == XMB) {
					
			sprintf(dst, "%s/BG.PNG", folder);
			ret=GetFromTHM(Themes_Paths_list[UI_position][Themes_position[UI_position]], "XMBBG.PNG" , dst);
			
			sprintf(dst, "%s/BGS.JPG", folder);
			ret=GetFromTHM(Themes_Paths_list[UI_position][Themes_position[UI_position]], "PSVBG.JPG" , dst);
			
			sprintf(dst, "%s/MMTHM_XMB.PNG", folder);
			ret=GetFromTHM(Themes_Paths_list[UI_position][Themes_position[UI_position]], "XMB.PNG" , dst);
			
			sprintf(dst, "%s/MMTHM_XMB2.PNG", folder);
			ret=GetFromTHM(Themes_Paths_list[UI_position][Themes_position[UI_position]], "XMB2.PNG" , dst);
			
		}
				
	}
	else if(ThemeType == P3T) {
		char tmp[128];
		sprintf(tmp, "/dev_hdd0/game/%s/USRDIR/temp", ManaGunZ_id);
		Delete(tmp);
		mkdir(tmp, 0777);
		strcat(tmp, "/tmp.p3t");
		
		Copy(Themes_Paths_list[UI_position][Themes_position[UI_position]], tmp);
		
		char dst[255];
		if(UI_position == XMB) {
					
			sprintf(dst, "%s/%s.PNG", folder, XMB_COLUMN_NAME[0]);
			ret=GetFromP3T(tmp, "icon_setting", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, XMB_COLUMN_NAME[1]);
			ret=GetFromP3T(tmp, "icon_playermet", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, XMB_COLUMN_NAME[2]);
			ret=GetFromP3T(tmp, "icon_game", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, XMB_COLUMN_NAME[3]);
			ret=GetFromP3T(tmp, "icon_game", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, XMB_COLUMN_NAME[4]);
			ret=GetFromP3T(tmp, "icon_game", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, XMB_COLUMN_NAME[5]);
			ret=GetFromP3T(tmp, "icon_remoteplay", dst);
			
			sprintf(dst, "%s/BG.JPG", folder);
			GetFromP3T(tmp, "background", dst); // pas de ret car facultatif
			
			Delete(tmp);
		}
	
	}
	else {
		ret=Copy(Themes_Paths_list[UI_position][Themes_position[UI_position]], folder);
	}
	
	if(ret==FAILED) {
		Delete(folder);
		return FAILED;
	}
		
	Themes_number[UI_position]++;
	strcpy(Themes_Paths_list[UI_position][Themes_number[UI_position]], folder);
	strcpy(Themes_Names_list[UI_position][Themes_number[UI_position]], Themes_Names_list[UI_position][Themes_position[UI_position]]);
	Themes_position[UI_position]=Themes_number[UI_position];
	strcpy(Themes[UI_position], Themes_Names_list[UI_position][Themes_number[UI_position]]);
	
	return SUCCESS;

}

char *NextColorSetName(FILE *f)
{
	char line[255];
	
	char *ColorSetName=NULL;
	while(fgets(line, 255, f) != NULL) {
		ColorSetName = get_str_regex(line, "[*]");
		if(ColorSetName!=NULL) return ColorSetName;
		memset(line, 0, 255);
	}
	return NULL;
}

void LoadColorSet(char *ColorSetName)
{
	FILE *f;
	char SysColorSetPath[128];
	sprintf(SysColorSetPath, "/dev_hdd0/game/%s/USRDIR/GUI/colorset.ini",  ManaGunZ_id);

	f = fopen(SysColorSetPath, "rb");
	if(f==NULL) return;
	
	char *SysColorSetName=NULL;
	while((SysColorSetName=NextColorSetName(f)) != NULL) {
		
		if(strcmp(SysColorSetName, ColorSetName) != 0) {FREE(SysColorSetName); continue;}
		
		FREE(SysColorSetName);
		
		char line[255];
		while(fgets(line, 255, f) != NULL) {
			if(strstr(line, "[") != NULL ) break;
			if(strstr(line, "=") == NULL ) continue;
			
			if(strlen(&strrchr(line, '=')[1]) == 0) continue;
			
			u32 loc=0;
			sscanf(&strrchr(line, '=')[1], "%X", (unsigned int *) &loc);
			
			if(strstr(line, "COLOR_1")!=NULL) {
				COLOR_1 = loc;
			} else
			if(strstr(line, "COLOR_2")!=NULL) {
				COLOR_2 = loc;
			} else
			if(strstr(line, "COLOR_3")!=NULL) {
				COLOR_3 = loc;
			} else
			if(strstr(line, "COLOR_4")!=NULL) {
				COLOR_4 = loc;
			} else
			if(strstr(line, "WAVES_COLOR")!=NULL) {
				WAVES_COLOR = loc;
			}
		}
		
		break;
	}
	fclose(f);
	
	write_setting();
}

void AddColorSet(char *ColorSetName)
{
	FILE *f;
	char temp[255];
	char SysColorSetPath[128];
	sprintf(SysColorSetPath, "/dev_hdd0/game/%s/USRDIR/GUI/colorset.ini",  ManaGunZ_id);

	f = fopen(SysColorSetPath, "rb+");
	if(f==NULL) return;
	
	char *SysColorSetName=NULL;
	while((SysColorSetName=NextColorSetName(f)) != NULL) {
		if( strcmp(SysColorSetName, ColorSetName) == 0 ) {
			FREE(SysColorSetName);
			fclose(f);
			return;
		}
		FREE(SysColorSetName);
	}
	
	fseek(f, 0, SEEK_END);
	
	sprintf(temp, "[%s]\n", ColorSetName); fputs(temp, f);
	sprintf(temp, "COLOR_1=%08X\n", COLOR_1); fputs(temp, f);
	sprintf(temp, "COLOR_2=%08X\n", COLOR_2); fputs(temp, f);
	sprintf(temp, "COLOR_3=%08X\n", COLOR_3); fputs(temp, f);
	sprintf(temp, "COLOR_4=%08X\n", COLOR_4); fputs(temp, f);
	sprintf(temp, "WAVES_COLOR=%08X\n\n", WAVES_COLOR); fputs(temp, f);
	
	fclose(f);
}

void RemoveColorSet(char *ColorSetName)
{
	char SysColorSetPath[128];
	int SysColorSetSize;
	sprintf(SysColorSetPath, "/dev_hdd0/game/%s/USRDIR/GUI/colorset.ini",  ManaGunZ_id);
	
	char *ColorSetData = LoadFile(SysColorSetPath, &SysColorSetSize);
	if(ColorSetData == NULL) return;
	
	if(strstr(ColorSetData, ColorSetName) == NULL) {
		FREE(ColorSetData);
		return;
	}
	
	char *NewColorSetData = malloc(SysColorSetSize);
	if(NewColorSetData==NULL) {
		FREE(ColorSetData);
		return;
	}
	
	int i;
	int NewSysColorSetSize=0;
	
	int start = strstr(ColorSetData, ColorSetName) - ColorSetData;
	int end;
	if(strstr(&ColorSetData[start+1], "[") != NULL) {
		end = strstr(&ColorSetData[start+1], "[") - ColorSetData;
	} else {
		end = SysColorSetSize;
	}
	
	for(i=0; i<SysColorSetSize; i++)
	{
		if(i<start || end<=i) {
			NewColorSetData[NewSysColorSetSize] = ColorSetData[i];
			NewSysColorSetSize++;
		}
	}
	
	SaveFile(SysColorSetPath, NewColorSetData, NewSysColorSetSize);
	
	FREE(ColorSetData);
	FREE(NewColorSetData);
}

void AddThemeColorSet()
{
	FILE *f1;
	FILE *f2;
	char ThemeColorSetPath[128];
	char ColorSetPath[128];
	
	sprintf(ThemeColorSetPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s/colorset.ini",  ManaGunZ_id, UI[UI_position], Themes[UI_position]);
	sprintf(ColorSetPath, "/dev_hdd0/game/%s/USRDIR/GUI/colorset.ini",  ManaGunZ_id);

	f1 = fopen(ThemeColorSetPath, "rb");
	if(f1==NULL) return;
	
	f2 = fopen(ColorSetPath, "rb+");
	if(f2==NULL) { fclose(f1); return; }
	
	char *ThemeColorSetName=NULL;
	char *ColorSetName=NULL;
	
	while((ThemeColorSetName=NextColorSetName(f1)) != NULL) {
		fseek(f2, 0, SEEK_SET);
		u8 add = YES;
		while((ColorSetName=NextColorSetName(f2)) != NULL) {
			if( strcmp(ColorSetName, ThemeColorSetName) == 0 ) {
				add = NO;
				FREE(ColorSetName);
				break;
			}
			FREE(ColorSetName);
		}
		if(add) {
			fseek(f2, 0, SEEK_END);
			fputs(ThemeColorSetName, f2);
			fputs("\n", f2);
			
			char line[255];
			memset(line, 0, 255);
			int pos = ftell(f1);
			while(fgets(line, 255, f1) != NULL) {
				
				ColorSetName = get_str_regex(line, "[*]");
				if(ColorSetName!=NULL) {
					fseek(f1, pos, SEEK_SET);
					FREE(ColorSetName);
					break;
				}
				
				if( strstr(line, "WAVES_COLOR") == NULL
				&&  strstr(line, "COLOR_1") == NULL
				&&  strstr(line, "COLOR_2") == NULL
				&&  strstr(line, "COLOR_3") == NULL
				&&  strstr(line, "COLOR_4") == NULL	) continue;
				if( strstr(line, "=") == NULL ) continue;
				
				
				int l=strlen(line);
				int i;
				for(i=0; i<l; i++) {
					if( line[i]==' ') continue;
					if( line[i]=='\n' || line[i]=='r') break;
					
					fputc(line[i], f2);
				}
				fputc('\n', f2);
				memset(line, 0, 255);
				
				pos = ftell(f1);
			}
			fputc('\n', f2);
		}
		FREE(ThemeColorSetName);
	}
	
	fclose(f1);
	fclose(f2);
}

void LoadThemeFont()
{
	char ThemeFontPath[128];
	
	sprintf(ThemeFontPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s/FONT.TTF",  ManaGunZ_id, UI[UI_position], Themes[UI_position]);
	
	if(path_info(ThemeFontPath) == _NOT_EXIST) return;

	strcpy(Font, ThemeFontPath);
	
	LoadFont();
}

void LoadThemeColorSet()
{
	FILE *f;
	char ThemeColorSetPath[128];
	
	sprintf(ThemeColorSetPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s/colorset.ini",  ManaGunZ_id, UI[UI_position], Themes[UI_position]);

	f = fopen(ThemeColorSetPath, "rb");
	if(f==NULL) return;
	
	char *ColorSetName=NextColorSetName(f);
	if(ColorSetName == NULL) return;
	FREE(ColorSetName);
	
	char line[255];
	while(fgets(line, 255, f) != NULL) {
		if(strstr(line, "[") != NULL ) break;
		if(strstr(line, "=") == NULL ) continue;
		if(strlen(&strrchr(line, '=')[1]) == 0) continue;
		
		u32 loc=0;
		sscanf(&strrchr(line, '=')[1], "%X", (unsigned int *) &loc);
		
		if(strstr(line, "COLOR_1")!=NULL) {
			COLOR_1 = loc;
		} else
		if(strstr(line, "COLOR_2")!=NULL) {
			COLOR_2 = loc;
		} else
		if(strstr(line, "COLOR_3")!=NULL) {
			COLOR_3 = loc;
		} else
		if(strstr(line, "COLOR_4")!=NULL) {
			COLOR_4 = loc;
		} else
		if(strstr(line, "WAVES_COLOR")!=NULL) {
			WAVES_COLOR = loc;
		}
	}
	
	fclose(f);
}

u8 LoadTexture(char *texture_path, u32 *texture_offset, imgData *texture_data)
{
	if( imgLoadFromFile(texture_path, texture_data) == FAILED ) { 
		*texture_offset=0;
		return FAILED;
	}
	
	if((*texture_data).bmp_out == NULL) {
		*texture_offset=0;
		return FAILED;
	}
	
	memcpy(texture_pointer, (*texture_data).bmp_out, (*texture_data).pitch * (*texture_data).height);
	free((*texture_data).bmp_out);
	*texture_offset = tiny3d_TextureOffset(texture_pointer);
	texture_pointer += (((*texture_data).pitch * (*texture_data).height + 15) & ~15);
	
	return SUCCESS;
}

void Load_Theme()
{
	char temp[255];
	char thmPath[255];
	int i;
	
	GetThemes();
	
	AddThemeColorSet();
	
	texture_pointer = texture_mem + TEXTURE_POINTER_THEME;
	
	memset(PICTURE_offset, 0, sizeof(PICTURE_offset));
	memset(BG_offset, 0, sizeof(BG_offset));
	memset(XMB_Col_offset, 0, sizeof(XMB_Col_offset));
	XMB_MMTHM_XMB2_offset = 0;
	XMB_MMTHM_XMB_offset = 0;
	
	sprintf(thmPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position], Themes[UI_position]);
	if(path_info(thmPath) == _NOT_EXIST) {
		strcpy(Themes[UI_position], STR_NONE);
		sprintf(thmPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position], Themes[UI_position]);
	}
	
	for(i=0; i<PICTURE_NUMBER; i++) {
		sprintf(temp, "%s/%s.PNG", thmPath, PICTURE_NAME[i]);
		if( LoadTexture(temp, &PICTURE_offset[i], &PICTURE[i]) == SUCCESS ) continue;
		
		sprintf(temp, "%s/%s.JPG", thmPath, PICTURE_NAME[i]);
		if( LoadTexture(temp, &PICTURE_offset[i], &PICTURE[i]) == SUCCESS ) continue;
		
		sprintf(temp, "/dev_hdd0/game/%s/USRDIR/GUI/common/%s.PNG", ManaGunZ_id, PICTURE_NAME[i]);
		if( LoadTexture(temp, &PICTURE_offset[i], &PICTURE[i]) == SUCCESS ) continue;
		
		sprintf(temp, "/dev_hdd0/game/%s/USRDIR/GUI/common/%s.PNG", ManaGunZ_id, PICTURE_NAME[i]);
		if( LoadTexture(temp, &PICTURE_offset[i], &PICTURE[i]) == SUCCESS ) continue;
	}	

	if(UI_position==XMB) {
		int i;
		for(i=0; i<6; i++) {
			sprintf(temp, "%s/%s.PNG", thmPath, XMB_COLUMN_NAME[i]);
			if( LoadTexture(temp, &XMB_Col_offset[i], &XMB_Col[i]) == FAILED ) {
				sprintf(temp, "%s/%s.JPG", thmPath, XMB_COLUMN_NAME[i]);
				LoadTexture(temp, &XMB_Col_offset[i], &XMB_Col[i]);
			}
		}
		
		sprintf(temp, "%s/MMTHM_XMB.PNG", thmPath);
		if( LoadTexture(temp, &XMB_MMTHM_XMB_offset, &XMB_MMTHM_XMB) == FAILED ) {
			sprintf(temp, "%s/MMTHM_XMB.JPG", thmPath);
			LoadTexture(temp, &XMB_MMTHM_XMB_offset, &XMB_MMTHM_XMB);
		}
		
		sprintf(temp, "%s/MMTHM_XMB2.PNG", thmPath);
		if( LoadTexture(temp, &XMB_MMTHM_XMB2_offset, &XMB_MMTHM_XMB2) == FAILED ) {
			sprintf(temp, "%s/MMTHM_XMB2.JPG", thmPath);
			LoadTexture(temp, &XMB_MMTHM_XMB2_offset, &XMB_MMTHM_XMB2);
		}
	}
	
	sprintf(temp, "%s/BG.PNG", thmPath);
	if(is_apng(temp) == YES) {
		Load_ANIMATED_BG(temp);
	} else {
		if( LoadTexture(temp, &BG_offset[0], &BG[0]) == FAILED ) {
			sprintf(temp, "%s/BG.JPG", thmPath);
			LoadTexture(temp, &BG_offset[0], &BG[0]);
		}
	}
}

char *LoadFileFromISO(u8 prog, char *path, char *filename, int *size)
{
	FILE* f;
	f = fopen(path, "rb");	
	if(f==NULL) return NULL;
	
	u64 file_offset=0;
	u8 ret=0;
	int file_size=0;

	ret = get_FileOffset(f, filename, &file_offset, (u32 *) &file_size);
	//print_load("Error : %s %llX", path, file_offset);
	if(file_offset==0 || file_size==0 || ret == FAILED) {fclose(f); return NULL;}
	
	u8 split666 = is_66600(path);
	
	if(is_splitted_iso(path)==YES || split666) {

		char iso_path[128];
		char temp[128];
		u64 fsize=0;
		int i;
		int l = strlen(path);
		
		strcpy(iso_path, path);
		iso_path[l-1]=0;
		if(split666) iso_path[l-2]=0;
		strcpy(temp, iso_path);
		
		for(i=0; i<100; i++) {
			if(split666) sprintf(iso_path, "%s%02d", temp, i);
			else sprintf(iso_path, "%s%d", temp, i);

			fsize = get_size(iso_path, NO);
			
			if(file_offset<fsize) {
				if(i!=0) {					 
					fclose(f);
					f = fopen(iso_path, "rb");	
					if(f==NULL) return NULL;
				}
				break;
			}
			file_offset -= fsize;
		}
	}
	
	u64 val64;
	fseek(f, file_offset-0x14, SEEK_SET);
	fread(&val64, sizeof(u64), 1, f);
	
	u8 is_bin=NO;
	if(val64==0xFFFFFFFFFFFFFF00) is_bin=YES;
	
	fseek(f, file_offset, SEEK_SET);
	
	char *mem = malloc(file_size);
	if(mem == NULL) {fclose(f); return NULL;}
	
	if(prog) prog_bar1_value=0;
	u64 read = 0;
	while(read < file_size) {
		u32 wrlen = 2048;
		if(read+wrlen > file_size) wrlen = (u32)file_size-read;
		fread(mem+read, sizeof(u8), wrlen, f);
		if(is_bin) fseek(f, 0x130, SEEK_CUR);
		read += wrlen;
		if(prog) prog_bar1_value = (read*100)/file_size;
	}
	fclose(f);
	
	if(prog) prog_bar1_value=-1;
	
	*size= file_size;
	return mem;
}

int position_PIC1=-1;
void LOAD_PIC1()
{
	char *mem = NULL;
	int size=0;
	
	TMP_PIC_offset=0;
	
	if( Show_PIC1 == NO ) return; 
	
	if( list_game_platform[position_PIC1] != _ISO_PS3 && list_game_platform[position_PIC1] != _ISO_PSP &&
		list_game_platform[position_PIC1] != _JB_PS3 ) return;
		
	if( list_game_platform[position_PIC1] == _ISO_PS3 ) {
		mem = LoadFileFromISO(YES, list_game_path[position_PIC1], "/PS3_GAME/PIC1.PNG", &size);
	} else
	if( list_game_platform[position_PIC1] == _ISO_PSP ) {
		mem = LoadFileFromISO(YES, list_game_path[position_PIC1], "/PSP_GAME/PIC1.PNG", &size);
	} else
	if( list_game_platform[position_PIC1] == _JB_PS3 ) {
		char temp[255];
		sprintf(temp, "%s/PS3_GAME/PIC1.PNG", list_game_path[position_PIC1]);
		mem = LoadFileProg(temp, &size);
		if(mem==NULL) return;
	}
	
	if(pngLoadFromBuffer(mem, size, (pngData *) &TMP_PIC) != 0) {free(mem); return;}
	
	free(mem);
	
	texture_pointer = texture_temp;
	
	if(TMP_PIC.bmp_out) {
		memcpy(texture_pointer, TMP_PIC.bmp_out, TMP_PIC.pitch * TMP_PIC.height);
		free(TMP_PIC.bmp_out);
		TMP_PIC_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((TMP_PIC.pitch * TMP_PIC.height + 15) & ~15) / 4;
		
	}
	
}

void Draw_PIC1()
{
	
	if(Show_PIC1==NO && load_PIC1 == YES) { end_load_PIC1(); return; }
	
	if(Show_PIC1==YES && load_PIC1 == NO) { start_load_PIC1(); return; }
	
	if(Show_PIC1==NO) return;
	
	if(MENU==YES && MENU_SIDE == NO) return;
	
	if((UI_position==LIST || UI_position==GRID) && Display_PIC1 == NO) return;
	
	if(TMP_PIC_offset != 0 ) {
		if( UI_position==XMB || UI_position==FLOW)
		{
			tiny3d_SetTexture(0, TMP_PIC_offset, TMP_PIC.width, TMP_PIC.height, TMP_PIC.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			if(UI_position==FLOW)
				Draw_Box(0, 0, ITEM_moveZ[position]+1, 0, 848, 512, WHITE, YES);
			else 
				Draw_Box(0, 0, 11, 0, 848, 512, WHITE, YES);
		} else
		if( UI_position==LIST || UI_position==GRID) 
		{
			tiny3d_SetTexture(0, TMP_PIC_offset, TMP_PIC.width, TMP_PIC.height, TMP_PIC.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			Draw_Box(50, 50, 0, 0, 848-100, 512-100, WHITE, YES);
		}
	} else {
		if(0 <= prog_bar1_value && prog_bar1_value < 100) Draw_Progress_Bar(50, 15, 1, prog_bar1_value, COLOR_2);
	}

}

static sys_ppu_thread_t load_PIC1_id;

void load_PIC1_thread(void *unused)
{
	while(load_PIC1 == YES) {
		if(position_PIC1 != position && Load_GamePIC == NO) {
			TMP_PIC_offset = 0;
			position_PIC1=position;
			usleep(1000000);
			if(position_PIC1 == position) LOAD_PIC1();
		}
		else usleep(100000);
		if( Game_stuff == NO ) TMP_PIC_offset=0;
	}

	sysThreadExit(0);
}

void start_load_PIC1()
{
	if(load_PIC1==NO) {
		load_PIC1 = YES;
		sysThreadCreate(&load_PIC1_id, load_PIC1_thread, NULL, 1500, 0x2000, THREAD_JOINABLE, "load_PIC1");
	}
}

void end_load_PIC1()
{
	u64 ret;
	if(load_PIC1==YES) {
		load_PIC1 = NO;
		sysThreadJoin(load_PIC1_id, &ret);
	}
}

void Translate(float *value, float target, float TranslateSpeed)
{
	float local;
	memcpy(&local, value, sizeof(float));
	
	if(local - TranslateSpeed < target && target < local + TranslateSpeed) {
		*value = target;
	} else
	if(local > target) {
		local-=TranslateSpeed;
		*value = local;
	} else
	if(local < target) {
		local+=TranslateSpeed;
		*value = local;
	}
}

void DrawParticle(float x, float y, float r, u32 color)
{
	int t;	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(color);
	for(t=x; t<=x+360; t+=60) {
		tiny3d_VertexPos( x + r*sin(t*PI/180), y + r*cos(t*PI/180), 999);
	}
	tiny3d_End();
}

void DrawSmallParticle(float x, float y, u32 color)
{
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexPos(x,y,999);
	tiny3d_VertexColor(color);
	tiny3d_VertexPos(x+1,y+1,999);
	tiny3d_VertexPos(x-1,y+1,999);
	tiny3d_End();
}

typedef struct
{
	float x;
	float y;
	float r;
	float a;
} particle;

typedef struct
{
	float x;
	float y;
	float a;
} small_particle;

typedef struct
{
	float size;
	float height;
	float phase;
	float frequency;
} wave;

#define WAVES_NUMBER 6
#define PARTICLE_NUMBER 30
#define SMALL_PARTICLE_NUMBER 200

wave *waves = NULL;
wave *new_waves = NULL;
particle *particles = NULL;
small_particle *small_particles = NULL;

#define rand_wave_freq				200 + rand()%500
#define rand_wave_size				rand()%100
#define rand_wave_height			rand()%75
#define rand_wave_phase				rand()%360

#define rand_particle_x				rand()%(int)X_MAX
#define rand_particle_y				Y_MAX/2-75 + rand()%150
#define rand_particle_r				2 + rand()%6
#define rand_particle_a				rand()%0x40

#define rand_small_particle_x				rand()%(int)X_MAX
#define rand_small_particle_y				Y_MAX/2-50 + rand()%100
#define rand_small_particle_a				0x80+rand()%0x80

void Draw_Waves(u32 wav_color)
{	
	int i;
	if(Show_Waves==NO) {
		if(waves != NULL) {
			for(i=0; i<WAVES_NUMBER; i++) {
				FREE(waves);
				FREE(new_waves);
			}
			for(i=0; i<PARTICLE_NUMBER; i++) {
				FREE(particles);
			}
			for(i=0; i<SMALL_PARTICLE_NUMBER; i++) {
				FREE(small_particles);
			}
		}
		return;
	}
	
	if(waves == NULL) {
		srand(1);
		waves = (wave *) malloc( WAVES_NUMBER * sizeof(wave));
		for(i=0; i<WAVES_NUMBER; i++) {
			waves[i].size = rand_wave_size;
			waves[i].phase = rand_wave_phase;
			waves[i].frequency = rand_wave_freq;
			waves[i].height = rand_wave_height;
		}
		new_waves = (wave *) malloc( WAVES_NUMBER * sizeof(wave));
		for(i=0; i<WAVES_NUMBER; i++) {
			new_waves[i].size = rand_wave_size;
			new_waves[i].phase = rand_wave_phase;
			new_waves[i].frequency = rand_wave_freq;
			new_waves[i].height = rand_wave_height;
		}
		particles = (particle *) malloc(PARTICLE_NUMBER * sizeof(particle));
		for(i=0; i<PARTICLE_NUMBER; i++) {
			particles[i].x = rand_particle_x;
			particles[i].y = rand_particle_y;
			particles[i].r = rand_particle_r;
			particles[i].a = rand_particle_a;
		}
		small_particles = (small_particle *) malloc(SMALL_PARTICLE_NUMBER * sizeof(small_particle));
		for(i=0; i<SMALL_PARTICLE_NUMBER; i++) {
			small_particles[i].x = rand_small_particle_x;
			small_particles[i].y = rand_small_particle_y;
			small_particles[i].a = rand_small_particle_a;
		}
		
	}
	
	u8 alpha = GetALPHA(wav_color) / 2;
	
	u32 color = (wav_color>>8)*0x100;
	
	int j=1;
	int x;
	for(i=0; i<WAVES_NUMBER; i++) {
		
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(x=0; x<=X_MAX+8; x+=8) {
			tiny3d_VertexColor(color + alpha - j*alpha);
			tiny3d_VertexPos(x, Y_MAX/2 + sin(j*DEG(waves[i].phase) + x / waves[i].frequency) * waves[i].height                    , 999);
			
			tiny3d_VertexColor(color + alpha + j*alpha);
			tiny3d_VertexPos(x, Y_MAX/2 + sin(j*DEG(waves[i].phase) + x / waves[i].frequency) * waves[i].height + waves[i].size, 999);
		}		
		tiny3d_End();
		
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(x=0; x<=X_MAX+8; x+=8) {
			tiny3d_VertexColor(color + alpha - j*alpha);
			tiny3d_VertexPos(x, Y_MAX/2 + sin(j*DEG(waves[i].phase) + x / waves[i].frequency) * waves[i].height                    , 999);
			
			tiny3d_VertexColor(color + alpha + j*alpha);
			tiny3d_VertexPos(x, Y_MAX/2 + sin(j*DEG(waves[i].phase) + x / waves[i].frequency) * waves[i].height - waves[i].size, 999);
		}		
		tiny3d_End();
		
		Translate(&waves[i].size, new_waves[i].size, 0.2);
		Translate(&waves[i].frequency, new_waves[i].frequency, 0.2);
		Translate(&waves[i].height, new_waves[i].height, 0.2);
		
		if(360 < waves[i].phase) waves[i].phase=0;
		else waves[i].phase += 0.2;
		
		if(	waves[i].frequency == new_waves[i].frequency) {
			new_waves[i].frequency = rand_wave_freq;
		}
		if(	waves[i].size == new_waves[i].size) {
			new_waves[i].size = rand_wave_size;
		}
		if(	waves[i].height == new_waves[i].height) {
			new_waves[i].height = rand_wave_height;
		}
		
		j=j*(-1);
	}
	
	for(i=0; i<PARTICLE_NUMBER; i++) {
		DrawParticle(particles[i].x, particles[i].y, particles[i].r, color + (u8) particles[i].a);	
		
		Translate(&particles[i].x, particles[i].x+j, 0.1);
		//Translate(&particles[i].y, particles[i].y+j, 0.01);
		if(particles[i].r<=8) particles[i].r+=j*0.01;
		particles[i].a-=0.1;
		                                  
		if( particles[i].a<=0 || particles[i].x>X_MAX || particles[i].x<0) {
			particles[i].x = rand_particle_x;
			particles[i].y = rand_particle_y;
			particles[i].r = rand_particle_r;
			particles[i].a = rand_particle_a;
		}
		j=j*(-1);
	}

	//small particles
	for(i=0; i<SMALL_PARTICLE_NUMBER; i++) {
		DrawSmallParticle(small_particles[i].x, small_particles[i].y, color + (u8) small_particles[i].a);
		
		Translate(&small_particles[i].x, small_particles[i].x+j, 0.1);
		//Translate(&small_particles[i].y, small_particles[i].y, 0.1);
		small_particles[i].a-=0.2;
		
		if( small_particles[i].a<=0 || small_particles[i].x>X_MAX || small_particles[i].x<0) {
			small_particles[i].x = rand_small_particle_x;
			small_particles[i].y = rand_small_particle_y;
			small_particles[i].a = rand_small_particle_a;
		}
		j=j*(-1);
	}
	
}

void Draw_BG()
{
	if(MENU==YES && MENU_SIDE == NO) return;
	
	if(BG_offset[1] != 0 ) { // Animated
		Draw_ANIMATED_BG();
	} else
	if(BG_offset[0] != 0 ) {
		tiny3d_SetTexture(0, BG_offset[0], BG[0].width, BG[0].height, BG[0].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(0, 0, 1000, 0, 848, 512, WHITE, YES);
	}
	
	if(UI_position == FLOW || UI_position == XMB) {
		Draw_Waves(WAVES_COLOR);
	}
}

void Draw_BGS()
{	
	if(PICTURE_offset[BGS] != 0 ) {
		tiny3d_SetTexture(0, PICTURE_offset[BGS], PICTURE[BGS].width, PICTURE[BGS].height, PICTURE[BGS].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(0, 0, 1000, 0, 848, 512, WHITE, YES);
	} else 
	if(BG_offset[1] != 0 ) { // Animated
		Draw_ANIMATED_BG();
	} else
	if(BG_offset[0] != 0 ) {
		tiny3d_SetTexture(0, BG_offset[0], BG[0].width, BG[0].height, BG[0].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(0, 0, 1000, 0, 848, 512, WHITE, YES);
	}
}

void DrawUp(float x, float y)  // equilateral abc, b vers le haut Xb=x, Ya=Yc=y
{
	tiny3d_SetPolygon(TINY3D_TRIANGLES);
	tiny3d_VertexPos(x-5 , y , 0); //a
	tiny3d_VertexColor(COLOR_4);
	tiny3d_VertexPos(x, y-5 , 0); //b
	tiny3d_VertexPos(x+5, y, 0); //c
	tiny3d_End();
}

void DrawDown(float x, float y)  // equilateral abc, b vers le bas Xb=x, Ya=Yc=y
{
	tiny3d_SetPolygon(TINY3D_TRIANGLES);
	tiny3d_VertexPos(x-5, y , 0); //a
	tiny3d_VertexColor(COLOR_4);
	tiny3d_VertexPos(x, y+5 , 0); //b
	tiny3d_VertexPos(x+5, y, 0); //c
	tiny3d_End();
}

void Draw_DISK(float x, float y, float z, float d, u32 color)
{
	x+=d/2;
	y+=d/2;
	int t;
		
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(color);
	for(t=0; t<=360 ; t+=10) {
		tiny3d_VertexPos( x + d/2.5*sin(t*PI/180), y + d/2.5*cos(t*PI/180), z);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(WHITE);
	for(t=120; t<=150 ; t+=10) {
		tiny3d_VertexPos( x + d/3*sin(t*PI/180), y + d/3*cos(t*PI/180), z);
	}
	for(t=150; t>=120 ; t-=10) {
		tiny3d_VertexPos( x + d/6*sin(t*PI/180), y + d/6*cos(t*PI/180), z);
	}
	tiny3d_End();
	
	/*
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(WHITE);
	for(t=-60; t<=-30 ; t+=10) {
		tiny3d_VertexPos( x + d/2.5*sin(t*PI/180), y + d/2.5*cos(t*PI/180), z);
	}
	for(t=-30; t>=-60 ; t-=10) {
		tiny3d_VertexPos( x + d/6*sin(t*PI/180), y + d/6*cos(t*PI/180), z);
	}
	tiny3d_End();
	*/
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(WHITE);
	for(t=0; t<=360 ; t+=10) {
		tiny3d_VertexPos( x + d/6*sin(t*PI/180), y + d/6*cos(t*PI/180), z);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(color);
	for(t=0; t<=360 ; t+=10) {
		tiny3d_VertexPos( x + d/8*sin(t*PI/180), y + d/8*cos(t*PI/180), z);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(WHITE);
	for(t=0; t<=360 ; t+=10) {
		tiny3d_VertexPos( x + d/12*sin(t*PI/180), y + d/12*cos(t*PI/180), z);
	}
	tiny3d_End();
}

void Draw_GAMEDISK(float x, float y, float z, float d, u8 platform)
{
	if(platform == _ISO_PS3) {
		if(PICTURE_offset[PS3_DISC] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[PS3_DISC], PICTURE[PS3_DISC].width, PICTURE[PS3_DISC].height, PICTURE[PS3_DISC].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			Draw_Box(x, y, z, 0, d, d, WHITE, YES);
		} else {
			Draw_DISK(x , y, z, 16, COLOR_PS3);
		}
	} else
	if(platform == _ISO_PS2) {
		if(PICTURE_offset[PS2_DISC] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[PS2_DISC], PICTURE[PS2_DISC].width, PICTURE[PS2_DISC].height, PICTURE[PS2_DISC].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			Draw_Box(x, y, z, 0, d, d, WHITE, YES);
		} else {
			Draw_DISK(x , y, z, 16, COLOR_PS2);
		}
	} else
	if(platform == _ISO_PS1) {
		if(PICTURE_offset[PS1_DISC] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[PS1_DISC], PICTURE[PS1_DISC].width, PICTURE[PS1_DISC].height, PICTURE[PS1_DISC].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			Draw_Box(x, y, z, 0, d, d, WHITE, YES);
		} else {
			Draw_DISK(x , y, z, 16, COLOR_PS1);
		}
	} else
	if(platform == _ISO_PSP) {
		if(PICTURE_offset[PSP_DISC] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[PSP_DISC], PICTURE[PSP_DISC].width, PICTURE[PSP_DISC].height, PICTURE[PSP_DISC].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			Draw_Box(x, y, z, 0, d, d, WHITE, YES);
		} else {
			Draw_DISK(x , y, z, 16, COLOR_PS2);
		}
	}
}

int Draw_USB(float x, float y, float font_size, u32 rgba ,int nb)
{
	float s=font_size/4;
	
	float e=font_size/24;
	
	Draw_Box(x, y, 0, 0, 5 + s*5 + 5, font_size, 0xA0A0A0A0, NO);
	
	y+=font_size/2;
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x + 2*s - e, y - s, 0);
	tiny3d_VertexPos( x + 2*s - e, y + 2*e - s, 0);
	tiny3d_VertexPos( x + 3*s, y + 2*e - s, 0);
	tiny3d_VertexPos( x + 3*s, y - s, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x + 3*s - e, y + s, 0);
	tiny3d_VertexPos( x + 3*s - e, y + s - 2*e, 0);
	tiny3d_VertexPos( x + 4*s, y + s - 2*e, 0);
	tiny3d_VertexPos( x + 4*s, y + s, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x + s - e*1.5 , y  , 0);
	tiny3d_VertexPos( x + s + e , y  , 0);
	tiny3d_VertexPos( x + 2*s + e , y - s , 0);
	tiny3d_VertexPos( x + 2*s - e , y - s , 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x + 2*s - e*1.5, y  , 0);
	tiny3d_VertexPos( x + 2*s + e, y  , 0);
	tiny3d_VertexPos( x + 3*s + e, y + s , 0);
	tiny3d_VertexPos( x + 3*s - e, y + s , 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x , y - e, 0);
	tiny3d_VertexPos( x , y + e, 0);
	tiny3d_VertexPos( x + 5*s, y + e, 0);
	tiny3d_VertexPos( x + 5*s , y - e, 0);
	tiny3d_End();
	
	FontSize(font_size/2);
	FontColor(COLOR_1);
	DrawFormatString(x+3.5*s, y-font_size/2, "%d", nb);
	FontSize(font_size);
	
	return x + 10 + 5*s;
}

void Draw_Button(float x, float y, float d)
{
	x+=d/2;
	y+=d/2;
	int t;
		
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(0x3F3F41ff);
	for(t=0; t<=360 ; t+=10) {
		tiny3d_VertexPos( x + d/1.9*sin(t*PI/180), y + d/1.9*cos(t*PI/180), 0);
	}
	tiny3d_End();
	
}

void DrawProgRing(float x, float y, float d, float value, u32 color)
{
	float t;
	float v = value*3.6;
	if(v>360) v=360;
	
	
	float r1 = d / 2;
	float r2 = (d-20*d/100) / 2;
	
	if(v<10) {
		tiny3d_SetPolygon(TINY3D_LINES);
		tiny3d_VertexPos(x, y - r1, 0);
		tiny3d_VertexColor(color);
		tiny3d_VertexPos(x, y - r2, 0);
		tiny3d_End();
		return;
	}
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexColor(color);
	for(t=0; t<=v ; t+=10) {
		tiny3d_VertexPos( x - r1*sin(t*PI/180), y - r1*cos(t*PI/180), 0);
		tiny3d_VertexPos( x - r2*sin(t*PI/180), y - r2*cos(t*PI/180), 0);
	}
	tiny3d_End();
}

int Draw_Button_Circle(float x, float y, float size)
{
	if(PICTURE_offset[9] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[9], PICTURE[9].width, PICTURE[9].height, PICTURE[9].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, y, 0, 0, size, size, WHITE, YES);

		return x+size;
	}
	else {
		Draw_Button(x, y, size);
		
		x+=size/2;
		y+=size/2;
		int t;
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0xFF646Fff);
			
		for(t=0; t<=360 ; t+=10) {
			tiny3d_VertexPos( x + size/2*3/4*sin(t*PI/180), y + size/2*3/4*cos(t*PI/180), 0);
		}
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0x3F3F41ff);
		for(t=0; t<=360 ; t+=10) {
			tiny3d_VertexPos( x + size/2*5/8*sin(t*PI/180), y + size/2*5/8*cos(t*PI/180), 0);
		}
		tiny3d_End();
		
		return x+size/2;
	}	
}

int Draw_Button_Square(float x, float y, float size)
{
	if(PICTURE_offset[7] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[7], PICTURE[7].width, PICTURE[7].height, PICTURE[7].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, y, 0, 0, size, size, WHITE, YES);
		
		return x+size;
	}
	else {
		Draw_Button(x, y, size);
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0xF88DD7ff);
		x+=size/2;
		y+=size/2;
		tiny3d_VertexPos( x - size/2*7/8*sqrt(2)/2, y - size/2*7/8*sqrt(2)/2, 0);
		tiny3d_VertexPos( x + size/2*7/8*sqrt(2)/2, y - size/2*7/8*sqrt(2)/2, 0);
		tiny3d_VertexPos( x + size/2*7/8*sqrt(2)/2, y + size/2*7/8*sqrt(2)/2, 0);
		tiny3d_VertexPos( x - size/2*7/8*sqrt(2)/2, y + size/2*7/8*sqrt(2)/2, 0);
		tiny3d_End();
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0x3F3F41FF);
		tiny3d_VertexPos( x - size/2*11/16*sqrt(2)/2, y - size/2*11/16*sqrt(2)/2, 0);
		tiny3d_VertexPos( x + size/2*11/16*sqrt(2)/2, y - size/2*11/16*sqrt(2)/2, 0);
		tiny3d_VertexPos( x + size/2*11/16*sqrt(2)/2, y + size/2*11/16*sqrt(2)/2, 0);
		tiny3d_VertexPos( x - size/2*11/16*sqrt(2)/2, y + size/2*11/16*sqrt(2)/2, 0);
		tiny3d_End();
		
		return x+size/2;
	}
}

int Draw_Button_Triangle(float x, float y, float size)
{
	if(PICTURE_offset[10] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[10], PICTURE[10].width, PICTURE[10].height, PICTURE[10].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, y, 0, 0, size, size, WHITE, YES);
		
		return x+size;
	}
	else {
		Draw_Button(x, y, size);
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0x00CDC7ff);
		x+=size/2;
		y+=size/2;
		tiny3d_VertexPos( x - size/2*7/8*sqrt(3)/2, y + size/2/2*7/8, 0);
		tiny3d_VertexPos( x + size/2*7/8*sqrt(3)/2, y + size/2/2*7/8, 0);
		tiny3d_VertexPos( x, y - size/2*7/8, 0);
		tiny3d_End();
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0x3F3F41FF);
		tiny3d_VertexPos( x - size/2*11/16*sqrt(3)/2, y + size/2/2*11/16, 0);
		tiny3d_VertexPos( x + size/2*11/16*sqrt(3)/2, y + size/2/2*11/16, 0);
		tiny3d_VertexPos( x, y - size/2*11/16, 0);
		tiny3d_End();
		
		return x+size/2;
	}
}

int Draw_Button_Cross(float x, float y, float size)
{

	if(PICTURE_offset[8] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[8], PICTURE[8].width, PICTURE[8].height, PICTURE[8].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, y, 0, 0, size, size, WHITE, YES);
		
		return x+size;
	}
	else {
		Draw_Button(x, y, size);
		
		x+=size/2;
		y+=size/2;
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0x82B4EBff);
		tiny3d_VertexPos( x - size/2*15/16*sqrt(2)/2, y - size/2*13/16*sqrt(2)/2, 0);
		tiny3d_VertexPos( x - size/2*13/16*sqrt(2)/2, y - size/2*15/16*sqrt(2)/2, 0);
		tiny3d_VertexPos( x + size/2*15/16*sqrt(2)/2 , y + size/2*13/16*sqrt(2)/2 , 0);
		tiny3d_VertexPos( x + size/2*13/16*sqrt(2)/2 , y + size/2*15/16*sqrt(2)/2 , 0);
		tiny3d_End();
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0x82B4EBff);
		tiny3d_VertexPos( x + size/2*13/16*sqrt(2)/2, y - size/2*15/16*sqrt(2)/2, 0);
		tiny3d_VertexPos( x + size/2*15/16*sqrt(2)/2, y - size/2*13/16*sqrt(2)/2, 0);	
		tiny3d_VertexPos( x - size/2*13/16*sqrt(2)/2, y + size/2*15/16*sqrt(2)/2, 0);
		tiny3d_VertexPos( x - size/2*15/16*sqrt(2)/2, y + size/2*13/16*sqrt(2)/2, 0);
		tiny3d_End();
		
		return size/2+x;
	}
}

int Draw_Button_Start(float x, float y, float size)
{	
	if(PICTURE_offset[6] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[6], PICTURE[6].width, PICTURE[6].height, PICTURE[6].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		tiny3d_SetPolygon(TINY3D_QUADS);

		tiny3d_VertexPos(x	 , y	 , 0);
		tiny3d_VertexColor(0xFFFFFFFF);
		tiny3d_VertexTexture(0.0f, 0.0f);

		tiny3d_VertexPos(x + size, y	 , 0);
		tiny3d_VertexTexture(1.0f, 0.0f);

		tiny3d_VertexPos(x + size, y + size, 0);
		tiny3d_VertexTexture(1.0f, 1.0f);

		tiny3d_VertexPos(x	 , y + size, 0);
		tiny3d_VertexTexture(0.0f, 1.0f);

		tiny3d_End();
		return x+size;
	}
	else {
		y-=size/20;
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexColor(0x3F3F41ff);
		tiny3d_VertexPos( x, y + size/4 , 0);
		tiny3d_VertexPos( x, y + 3*size/4 , 0);
		tiny3d_VertexPos( x + size, y + size/2 , 0);
		tiny3d_End();
		return x + size ;
	}
}

int Draw_Button_Select(float x, float y,  float size) {

	if(PICTURE_offset[5] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[5], PICTURE[5].width, PICTURE[5].height, PICTURE[5].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, y, 0, 0, size, size, WHITE, YES);
		
	} else {
		Draw_Box(x, y+size/3, 0, 2, size, size/3, 0x3F3F41ff, NO);
	}
	
	return x+size;
}

float Draw_Button_L1(float x, float y, float z, float size)
{
	if(PICTURE_offset[12] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[12], PICTURE[12].width, PICTURE[12].height, PICTURE[12].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "L1");
}

float Draw_Button_L2(float x, float y, float z, float size)
{
	if(PICTURE_offset[13] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[13], PICTURE[13].width, PICTURE[13].height, PICTURE[13].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "L2");
}

float Draw_Button_L3(float x, float y, float z, float size)
{
	if(PICTURE_offset[14] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[14], PICTURE[14].width, PICTURE[14].height, PICTURE[14].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "L3");
}

float Draw_Button_L(float x, float y, float z, float size)
{
	if(PICTURE_offset[15] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[15], PICTURE[15].width, PICTURE[15].height, PICTURE[15].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "L");
}

float Draw_Button_R2(float x, float y, float z, float size)
{
	if(PICTURE_offset[16] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[16], PICTURE[16].width, PICTURE[16].height, PICTURE[16].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "R1");
}

float Draw_Button_R1(float x, float y, float z, float size)
{
	if(PICTURE_offset[17] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[17], PICTURE[17].width, PICTURE[17].height, PICTURE[17].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "R2");
}

float Draw_Button_R3(float x, float y, float z, float size)
{
	if(PICTURE_offset[18] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[18], PICTURE[18].width, PICTURE[18].height, PICTURE[18].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "R3");
}

float Draw_Button_R(float x, float y, float z, float size)
{
	if(PICTURE_offset[19] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[19], PICTURE[19].width, PICTURE[19].height, PICTURE[19].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "R");
}

float Draw_Pad(int button, float x, float y, float z,  float size) {

	if(PICTURE_offset[0] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[0], PICTURE[0].width, PICTURE[0].height, PICTURE[0].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		tiny3d_SetPolygon(TINY3D_QUADS);
		tiny3d_VertexPos(x, y, z);
		tiny3d_VertexColor(0xFFFFFFFF);
		tiny3d_VertexTexture(0.0f, 0.0f);
		tiny3d_VertexPos(x + size, y, z);
		tiny3d_VertexTexture(1.0f, 0.0f);
		tiny3d_VertexPos(x+size, y+size, z);
		tiny3d_VertexTexture(1.0f, 1.0f);
		tiny3d_VertexPos(x, y+size, z);
		tiny3d_VertexTexture(0.0f, 1.0f);
		tiny3d_End();
	}
	
	if(button & BUTTON_UP) {
		if(PICTURE_offset[1] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[1], PICTURE[1].width, PICTURE[1].height, PICTURE[1].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			tiny3d_SetPolygon(TINY3D_QUADS);
			tiny3d_VertexPos(x, y, z);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexTexture(0.0f, 0.0f);
			tiny3d_VertexPos(x + size, y, z);
			tiny3d_VertexTexture(1.0f, 0.0f);
			tiny3d_VertexPos(x+size, y+size, z);
			tiny3d_VertexTexture(1.0f, 1.0f);
			tiny3d_VertexPos(x, y+size, z);
			tiny3d_VertexTexture(0.0f, 1.0f);
			tiny3d_End();
		}
	}
	if(button & BUTTON_LEFT) {
		if(PICTURE_offset[2] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[2], PICTURE[2].width, PICTURE[2].height, PICTURE[2].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			tiny3d_SetPolygon(TINY3D_QUADS);
			tiny3d_VertexPos(x, y, z);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexTexture(0.0f, 0.0f);
			tiny3d_VertexPos(x + size, y, z);
			tiny3d_VertexTexture(1.0f, 0.0f);
			tiny3d_VertexPos(x+size, y+size, z);
			tiny3d_VertexTexture(1.0f, 1.0f);
			tiny3d_VertexPos(x, y+size, z);
			tiny3d_VertexTexture(0.0f, 1.0f);
			tiny3d_End();
		}
	}
	if(button & BUTTON_DOWN) {
		if(PICTURE_offset[3] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[3], PICTURE[3].width, PICTURE[3].height, PICTURE[3].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			tiny3d_SetPolygon(TINY3D_QUADS);
			tiny3d_VertexPos(x, y, z);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexTexture(0.0f, 0.0f);
			tiny3d_VertexPos(x + size, y, z);
			tiny3d_VertexTexture(1.0f, 0.0f);
			tiny3d_VertexPos(x+size, y+size, z);
			tiny3d_VertexTexture(1.0f, 1.0f);
			tiny3d_VertexPos(x, y+size, z);
			tiny3d_VertexTexture(0.0f, 1.0f);
			tiny3d_End();
		}
	}
	if(button & BUTTON_RIGHT) {
		if(PICTURE_offset[4] != 0) {
			tiny3d_SetTexture(0, PICTURE_offset[4], PICTURE[4].width, PICTURE[4].height, PICTURE[4].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			tiny3d_SetPolygon(TINY3D_QUADS);
			tiny3d_VertexPos(x, y, z);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexTexture(0.0f, 0.0f);
			tiny3d_VertexPos(x + size, y, z);
			tiny3d_VertexTexture(1.0f, 0.0f);
			tiny3d_VertexPos(x+size, y+size, z);
			tiny3d_VertexTexture(1.0f, 1.0f);
			tiny3d_VertexPos(x, y+size, z);
			tiny3d_VertexTexture(0.0f, 1.0f);
			tiny3d_End();
		}
	}
	
	return x+size;
}

float DrawButton(float x, float y, char *str, int button)
{
	float button_size = 16;
	FontSize(button_size);

	if(button & BUTTON_CROSS) x=Draw_Button_Cross(x, y, button_size); 
	if(button & BUTTON_SQUARE) x=Draw_Button_Square(x, y, button_size); 
	if(button & BUTTON_TRIANGLE) x=Draw_Button_Triangle(x, y, button_size);
	if(button & BUTTON_CIRCLE) x=Draw_Button_Circle(x, y, button_size); 
	if(button & BUTTON_SELECT) x=Draw_Button_Select(x, y, button_size); 
	if(button & BUTTON_START) x=Draw_Button_Start(x, y, button_size);
	if(button & BUTTON_L1) x=Draw_Button_L1(x, y, 0, button_size);
	if(button & BUTTON_L2) x=Draw_Button_L2(x, y, 0, button_size);
	if(button & BUTTON_L3) x=Draw_Button_L3(x, y, 0, button_size);
	if(button & BUTTON_L ) x=Draw_Button_L (x, y, 0, button_size);
	if(button & BUTTON_R1) x=Draw_Button_R1(x, y, 0, button_size);
	if(button & BUTTON_R2) x=Draw_Button_R2(x, y, 0, button_size);
	if(button & BUTTON_R3) x=Draw_Button_R3(x, y, 0, button_size);
	if(button & BUTTON_R ) x=Draw_Button_R (x, y, 0, button_size);
	if((button & BUTTON_RIGHT) || (button & BUTTON_LEFT) || (button & BUTTON_DOWN) || (button & BUTTON_UP))	x=Draw_Pad(button, x, y, 0, button_size);
	
	x=DrawString(x+5, y+1, str);
	
	return x+10;
}

u8 GetRED(u32 rgba) 
{
	return (u8) (rgba >> 24) ;
}

u8 GetGREEN(u32 rgba) 
{
	return (u8) ((rgba - (rgba >> 24)*0X1000000) >> 16 );
}

u8 GetBLUE(u32 rgba) {	
	return (u8) ((rgba - (rgba >> 16)*0X10000) >> 8 );
}

u8 GetALPHA(u32 rgba) 
{
	return (u8) (rgba - (rgba>>8)*0x100) ;
}

u32 SetRED(u8 red, u32 rgba){
	return rgba - GetRED(rgba) * 0x1000000 + red*0x1000000;
}

u32 SetGREEN(u8 green, u32 rgba){
	return rgba - GetGREEN(rgba) * 0x10000 + green*0x10000;
}

u32 SetBLUE(u8 blue, u32 rgba){
	return rgba - GetBLUE(rgba) * 0x100 + blue*0x100;
}

u32 SetALPHA(u8 alpha, u32 rgba)
{
	return rgba - GetALPHA(rgba) + alpha;
}

void Draw_NOT(float x, float y, float z, float w, float h)
{	
	if(PICTURE_offset[NOT] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[NOT], PICTURE[NOT].width, PICTURE[NOT].height, PICTURE[NOT].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, y, z, 0, w, h, WHITE, YES);
	}
}

void Draw_SIDEBAR(float x)
{
	Draw_Box(0, 0, 9, 0, 848, 512, 0x000000B0, NO);
	if(PICTURE_offset[SIDEBAR] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[SIDEBAR], PICTURE[SIDEBAR].width, PICTURE[SIDEBAR].height, PICTURE[SIDEBAR].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, 0, 9, 0, X_MAX-x, 512, 0xFFFFFFFF, YES);
	} else {
		Draw_Box(x, 0, 9, 0, X_MAX-x, 512, 0xFFFFFF60, NO);
		Draw_Box(x, 0, 9, 0, 1, 512, 0xFFFFFFFF, NO);
	}
	
}

int Draw_Progress_Bar(float x, float y, u8 size, float value, u32 color)
{	
	float w=size*100;
	
	float e = size;
	float h = size*2;
	
	Draw_Box(x  , y  , 0, 0, w+e*2+2, h+e*2+2,  COLOR_1, NO);
	Draw_Box(x+e, y+e, 0, 0, w+2	, h+2	, 0x000000FF, NO);
	
	Draw_Box(x+e+1, y+e+1, 0, 0, value*size, h, color, NO);
	
	return x+w+2*e;
	
}

void DrawNotBody(float x, float y, float z, float w, float h)
{
	tiny3d_SetTextureWrap(0, PICTURE_offset[NOTIF], PICTURE[NOTIF].width, PICTURE[NOTIF].height, PICTURE[NOTIF].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTWRAP_CLAMP, TEXTWRAP_CLAMP, TEXTURE_LINEAR);
	
	float wn=PICTURE[NOTIF].width/4;
	float hn=PICTURE[NOTIF].height/4;;

	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x, y, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.0f, 0.0f);

	tiny3d_VertexPos(x+wn, y, z);
	tiny3d_VertexTexture(0.25f, 0.0f);

	tiny3d_VertexPos(x+wn, y+hn, z);
	tiny3d_VertexTexture(0.25f, 0.25f);
	
	tiny3d_VertexPos(x, y+hn, z);
	tiny3d_VertexTexture(0.0f, 0.25f);
	
	tiny3d_End();
	
	
	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x+wn, y, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.25f, 0.0f);

	tiny3d_VertexPos(x+w-wn, y, z);
	tiny3d_VertexTexture(0.75f, 0.0f);

	tiny3d_VertexPos(x+w-wn, y+hn, z);
	tiny3d_VertexTexture(0.75f, 0.25f);
	
	tiny3d_VertexPos(x+wn, y+hn, z);
	tiny3d_VertexTexture(0.25f, 0.25f);
	
	tiny3d_End();
	
	
	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x+w-wn, y, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.75f, 0.0f);

	tiny3d_VertexPos(x+w, y, z);
	tiny3d_VertexTexture(1.0f, 0.0f);

	tiny3d_VertexPos(x+w, y+hn, z);
	tiny3d_VertexTexture(1.0f, 0.25f);
	
	tiny3d_VertexPos(x+w-wn, y+hn, z);
	tiny3d_VertexTexture(0.75f, 0.25f);
	
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x, y+hn, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.0f, 0.25f);

	tiny3d_VertexPos(x+wn, y+hn, z);
	tiny3d_VertexTexture(0.25f, 0.25f);

	tiny3d_VertexPos(x+wn, y+h-hn, z);
	tiny3d_VertexTexture(0.25f, 0.75f);
	
	tiny3d_VertexPos(x, y+h-hn, z);
	tiny3d_VertexTexture(0.0f, 0.75f);
	
	tiny3d_End();
	
	
	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x+wn, y+hn, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.25f, 0.25f);

	tiny3d_VertexPos(x+w-wn, y+hn, z);
	tiny3d_VertexTexture(0.75f, 0.25f);

	tiny3d_VertexPos(x+w-wn, y+h-hn, z);
	tiny3d_VertexTexture(0.75f, 0.75f);
	
	tiny3d_VertexPos(x+wn, y+h-hn, z);
	tiny3d_VertexTexture(0.25f, 0.75f);
	
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x+w-wn, y+hn, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.75f, 0.25f);

	tiny3d_VertexPos(x+w, y+hn, z);
	tiny3d_VertexTexture(1.0f, 0.25f);

	tiny3d_VertexPos(x+w, y+h-hn, z);
	tiny3d_VertexTexture(1.0f, 0.75f);
	
	tiny3d_VertexPos(x+w-wn, y+h-hn, z);
	tiny3d_VertexTexture(0.75f, 0.75f);
	
	tiny3d_End();
	
	
	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x, y+h-hn, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.0f, 0.75f);

	tiny3d_VertexPos(x+wn, y+h-hn, z);
	tiny3d_VertexTexture(0.25f, 0.75f);

	tiny3d_VertexPos(x+wn, y+h, z);
	tiny3d_VertexTexture(0.25f, 1.0f);
	
	tiny3d_VertexPos(x, y+h, z);
	tiny3d_VertexTexture(0.0f, 1.0f);
	
	tiny3d_End();
	
	
	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x+wn, y+h-hn, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.25f, 0.75f);

	tiny3d_VertexPos(x+w-wn, y+h-hn, z);
	tiny3d_VertexTexture(0.75f, 0.75f);

	tiny3d_VertexPos(x+w-wn, y+h, z);
	tiny3d_VertexTexture(0.75f, 1.0f);
	
	tiny3d_VertexPos(x+wn, y+h, z);
	tiny3d_VertexTexture(0.25f, 1.0f);
	
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUADS);
	
	tiny3d_VertexPos(x+w-wn, y+h-hn, z);
	tiny3d_VertexColor(0xFFFFFFFF);
	tiny3d_VertexTexture(0.75f, 0.75f);

	tiny3d_VertexPos(x+w, y+h-hn, z);
	tiny3d_VertexTexture(1.0f, 0.75f);

	tiny3d_VertexPos(x+w, y+h, z);
	tiny3d_VertexTexture(1.0f, 1.0f);
	
	tiny3d_VertexPos(x+w-wn, y+h, z);
	tiny3d_VertexTexture(0.75f, 1.0f);
	
	tiny3d_End();
	
}

void Draw_Notification()
{
	if(not_msg[0] == 0)	return;
	time_not++;
	if(time_not > 100) {
		time_not=0; 
		memset(not_msg, 0, sizeof(not_msg));
		return ;
	}
	
	SetFontZ(0);
	FontColor(COLOR_1);
	FontSize(14);
	
	if(PICTURE_offset[NOTIF]!=0) {
		DrawNotBody(590, 40, 0, 213, 50);
	} else {
		Draw_Box(590, 40, 0, 3, 213, 50, 0x555555FF, NO);
	}
	Draw_NOT(600, 50, 0, 30, 30);

	DrawString(635, 58, not_msg);
	
	SetFontZ(10);
	FontSize(15);
}

void show_msg(char *str)
{
	strcpy(not_msg, str);
}

void DrawLoadingIcon()
{
	if(LoadIconRot==720) LoadIconRot=360;
	
	float t;	
	float r1 = 7;
	float r2 = 5;
	float x = X_MAX - 20;
	float y = 20;
	/*
	float r1 = 50;
	float r2 = 30;
	float x = X_MAX/2;
	float y = Y_MAX/2;
	*/
	u32 color = COLOR_1;
	
	color = color - GetALPHA(color);
	
	u8 alpha = 0;
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=LoadIconRot; t<=LoadIconRot+360 ; t+=10) {
		tiny3d_VertexColor(color+alpha);
		tiny3d_VertexPos( x - r1*sin(t*PI/180), y - r1*cos(t*PI/180), 0);
		tiny3d_VertexPos( x - r2*sin(t*PI/180), y - r2*cos(t*PI/180), 0);
		alpha=(t-LoadIconRot)/360*0xFF;
	}
	tiny3d_End();
	
	LoadIconRot+=5;
}

static sys_ppu_thread_t loading_id;	
void Draw_Loading(void *unused)
{
	int i=0;
	int show_log=YES;
	int GRID_DIRECTION = 1;
	int h=20, v=70;
	int speed = 3;
	int boost=100;
	cancel=NO;
	u32 color=GREEN;
	u8 have_log=NO;
	gathering_cancel=NO;
	LoadIconRot=0;
	
	strcpy(head_title, "\0");
	for(i=0; i<=20; i++){
		strcpy(loading_log[i], "\0");
	}
	
	while(loading) {
		cls();

		int x=50, y=40;
				
		if(loading_log[0][0]!=0 || head_title[0] != 0 || gathering || prog_bar1_value >= 0) have_log=YES;
		
		if(scene == SCENE_FILEMANAGER) {
			Draw_scene();
			if(show_log && have_log) Draw_Box(0, 0, 0, 0, 848, 512, 0x000000C0, NO);
		} else Draw_BGS();
		
		FontSize(20);
		FontColor(COLOR_1);
		SetFontZ(0);
		
		if(show_log && have_log) {
			
			if(head_title[0] != 0) {
				FontColor(COLOR_2);
				DrawString(x, y, head_title);
				FontColor(COLOR_1);
				y+=20;
			}
			if(prog_bar1_value >= 0) {
				Draw_Progress_Bar(x, y, 2, prog_bar1_value, COLOR_2);
				y+=15;
				if(prog_bar2_value >= 0) Draw_Progress_Bar(x, y, 2, prog_bar2_value, COLOR_2);
				y+=25;
			}
			if(gathering){
				FontColor(COLOR_1);
				DrawFormatString(x, y, STR_GATHERING);
				y+=20;
				DrawFormatString(x, y, "%s = %i", STR_FILES, nb_file);
				y+=20;
				DrawFormatString(x, y, "%s = %i", STR_DIRS, nb_directory);
				y+=20;
				char *size_tot = get_unit(total_size);
				DrawFormatString(x, y,"%s = %s", STR_TOTALSIZE, size_tot);
				y+=20;
				if(size_tot) free(size_tot);
			}
			for(i=0; i<=20; i++){
			
				if(strstr(loading_log[i], "Error")) FontColor(RED);
				else if(strstr(loading_log[i], "Warning")) FontColor(ORANGE);
				else FontColor(COLOR_1);
				
				DrawFormatString(x , y, loading_log[i]);
				y+=20;
				if(y>450) break;
			}
		}
		
		if(scene != SCENE_FILEMANAGER) {	
			int t;
			switch(GRID_DIRECTION){
				case 1: //droite
				{
					if(speed==9) {
						Draw_Box(h-17, v+2 , 0, 0, 15, 2, 0xFFFFFF50, NO);
						Draw_Box(h-22, v+9 , 0, 0, 20, 2, 0xFFFFFF50, NO);
						Draw_Box(h-17, v+16, 0, 0, 15, 2, 0xFFFFFF50, NO);
					}
					Draw_Box(h  , v, 0, 0, 3 , 20, 0xFFFFFF50, NO);
					Draw_Box(h+4, v, 0, 0, 16, 20, 0xFFFFFF50, NO);
					
					tiny3d_SetPolygon(TINY3D_POLYGON);
					tiny3d_VertexColor(0xFFFFFF50);
					for(t=0; t<=180 ; t+=15) {
						tiny3d_VertexPos( h + 20 + 10*sin(t*PI/180), v + 10 + 10*cos(t*PI/180), 0);
					}
					tiny3d_End();
					
					tiny3d_SetPolygon(TINY3D_POLYGON);
					tiny3d_VertexColor(0x000000A0);
					for(t=-135; t<=45 ; t+=15) {
						tiny3d_VertexPos( h + 20 + 2*sin(t*PI/180), v + 7 + 3*cos(t*PI/180), 0);
					}
					tiny3d_End();
					
					if(h>= 820) GRID_DIRECTION = 2; else h+=speed;
				}
				break;
				case 2: //gauche
				{
					if(speed==9) {
						Draw_Box(h+22, v+2 , 0, 0, 15, 2, 0xFFFFFF50, NO);
						Draw_Box(h+22, v+9 , 0, 0, 20, 2, 0xFFFFFF50, NO);
						Draw_Box(h+22, v+16, 0, 0, 15, 2, 0xFFFFFF50, NO);
					}
					Draw_Box(h+17, v, 0, 0, 3 , 20, 0xFFFFFF50, NO);
					Draw_Box(h   , v, 0, 0, 16, 20, 0xFFFFFF50, NO);
					
					tiny3d_SetPolygon(TINY3D_POLYGON);
					tiny3d_VertexColor(0xFFFFFF50);
					for(t=-180; t<=0 ; t+=15) {
						tiny3d_VertexPos( h + 10*sin(t*PI/180), v + 10 + 10*cos(t*PI/180), 0);
					}
					tiny3d_End();
					
					tiny3d_SetPolygon(TINY3D_POLYGON);
					tiny3d_VertexColor(0x000000A0);
					for(t=-45; t<=135 ; t+=15) {
						tiny3d_VertexPos( h + 2*sin(t*PI/180), v + 7 + 3*cos(t*PI/180), 0);
					}
					tiny3d_End();
							
					if(h < 20) GRID_DIRECTION = 1; else h-=speed;
				}
				break;
				case 3: // haut
				{
					if(speed==9) {
						Draw_Box(h+2 , v+22, 0, 0, 2, 15, 0xFFFFFF50, NO);
						Draw_Box(h+9 , v+22, 0, 0, 2, 20, 0xFFFFFF50, NO);
						Draw_Box(h+16, v+22, 0, 0, 2, 15, 0xFFFFFF50, NO);
					}
					
					Draw_Box(h, v+17, 0, 0, 20,  3, 0xFFFFFF50, NO);
					Draw_Box(h, v   , 0, 0, 20, 16, 0xFFFFFF50, NO);
					
					tiny3d_SetPolygon(TINY3D_POLYGON);
					tiny3d_VertexColor(0xFFFFFF50);
					for(t=90; t<=270 ; t+=15) {
						tiny3d_VertexPos( h + 10 + 10*sin(t*PI/180), v + 10*cos(t*PI/180), 0);
					}
					tiny3d_End();
					
					tiny3d_SetPolygon(TINY3D_POLYGON);
					tiny3d_VertexColor(0x000000A0);
					for(t=45; t<=225 ; t+=15) {
						tiny3d_VertexPos( h + 7 + 2*sin(t*PI/180), v + 3*cos(t*PI/180), 0);
					}
					tiny3d_End();
				
					if(v < 20) GRID_DIRECTION = 4; else v-=speed;
				}
				break;
				case 4: // bas
				{
					if(speed==9) {
						Draw_Box(h+2 , v-17, 0, 0, 2, 15, 0xFFFFFF50, NO);
						Draw_Box(h+9 , v-22, 0, 0, 2, 20, 0xFFFFFF50, NO);
						Draw_Box(h+16, v-17, 0, 0, 2, 15, 0xFFFFFF50, NO);
					}
					Draw_Box(h, v  , 0, 0, 20, 3 , 0xFFFFFF50, NO);
					Draw_Box(h, v+4, 0, 0, 20, 16, 0xFFFFFF50, NO);
					
					tiny3d_SetPolygon(TINY3D_POLYGON);
					tiny3d_VertexColor(0xFFFFFF50);
					for(t=-90; t<=90 ; t+=15) {
						tiny3d_VertexPos( h + 10 + 10*sin(t*PI/180), v + 20 + 10*cos(t*PI/180), 0);
					}
					tiny3d_End();
					
					tiny3d_SetPolygon(TINY3D_POLYGON);
					tiny3d_VertexColor(0x000000A0);
					for(t=45; t<=225 ; t+=15) {
						tiny3d_VertexPos( h + 7 + 2*sin(t*PI/180), v + 20 + 3*cos(t*PI/180), 0);
					}
					tiny3d_End();
					
					if(v > 490) GRID_DIRECTION = 3; else v+=speed;
				}
				break;
				default: //droite
				{
					GRID_DIRECTION = 1;
				}
			}
			
			if(speed==9) rumble2_on=1; else rumble2_on=0;
			if(boost<30) {
				color = RED;
			} else
			if(boost==100) {
				color = BLUE;
			} else
			if(boost<100) {
				color = GREEN;
			}
		}
		
		// *** DISPLAY BUTTONS ***
		x=INPUT_X;
		y=INPUT_Y;
		FontColor(COLOR_1);
		SetFontZ(0);

		if(scene == SCENE_FILEMANAGER) {
			if(LoadIconRot<180) {
				Draw_input();
				y=-50;
			}
		}
		
		if(have_log) {
			if(show_log)	x=DrawButton(x, y, STR_HIDELOGS, BUTTON_SELECT);
			else x=DrawButton(x, y, STR_SHOWLOGS, BUTTON_SELECT);
		}
			
		if(scene != SCENE_FILEMANAGER) {
			x=Draw_Button_Square(x, y, 15);
			x=Draw_Progress_Bar(x+5, y+4, 1, boost, color);
			x=DrawFormatString( x+5, y, "%s  ", STR_BOOST);
		}
		
		if(AutoM == YES) {
			x=DrawButton(x, y, STR_GAMEMENU, BUTTON_TRIANGLE);
		}
		if(prog_bar1_value >= 0 || gathering) {
			x=DrawButton(x, y, STR_CANCEL, BUTTON_CIRCLE);
		}
		
		
		DrawLoadingIcon();
		tiny3d_Flip();
		//ScreenShot();
		
		ps3pad_read();
		
		if(new_pad & BUTTON_RIGHT) {
			GRID_DIRECTION = 1;
		}
		if(new_pad & BUTTON_LEFT) {
			GRID_DIRECTION = 2;
		}
		if(new_pad & BUTTON_UP) {
			GRID_DIRECTION = 3;
		}
		if(new_pad & BUTTON_DOWN) {
			GRID_DIRECTION = 4;
		}
		if(new_pad & BUTTON_CIRCLE && prog_bar1_value >= 0) {
			cancel=YES;
		}
		if(new_pad & BUTTON_CIRCLE && gathering == YES) {
			gathering_cancel=YES;
		}
		if((old_pad & BUTTON_TRIANGLE) && AutoM==YES) {
			gui_called=YES;
		}
		if(new_pad & BUTTON_SELECT) {
			if(show_log) show_log=NO; else show_log=YES;
		}
		if(old_pad & BUTTON_SQUARE) {
			if(0 < boost && boost <= 30 && speed==9 ) {
				speed=9;
				boost--;
			} 
			else if(boost > 30) {
				speed=9;
				boost--;
			}
			else {
				speed=3;
			}
		} else {
			speed=3;
			if(boost<100) {
				boost+=1;
			}
		}
	}
	
	prog_bar1_value=-1;
	prog_bar2_value=-1;
	cancel=NO;
	gathering=NO;
	
	strcpy(head_title, "\0");
	
	for(i=0; i<=20; i++){
		strcpy(loading_log[i], "\0");
	}

	sysThreadExit(0);
}

static char buff[4096];
void print_load(char *format, ...)
{
	if(loading==NO) return;
	
	char *str = (char *) buff;
	va_list	opt;
	
	va_start(opt, format);
	vsprintf( (void *) buff, format, opt);
	va_end(opt);
	
	int i;
	for(i=19; i>0; i--){
		strcpy(loading_log[i], loading_log[i-1]);
	}
	
	if( ERR == TRUE ) {
		sprintf(loading_log[0], "Error : %s", str);
	} else 
	if( WAR == TRUE ) {
		sprintf(loading_log[0], "Warning : %s", str);
	} else strcpy(loading_log[0], str);
	
	time_not=1;
	if(strstr(loading_log[0], "Warning ")) sleep(1);
	if(strstr(loading_log[0], "Error ")) sleep(4);
	
	ERR = FALSE;
	WAR = FALSE;
}

static char buff2[4096];
void print_head(char *format2, ...)
{
	if(loading==NO) return;
	
	char *str2 = (char *) buff2;
	va_list	opt2;
	
	va_start(opt2, format2);
	vsprintf( (void *) buff2, format2, opt2);
	va_end(opt2);
	
	strcpy(head_title, str2);

}

void start_loading()
{
	loading=YES;
	sysThreadCreate(&loading_id, Draw_Loading, NULL, 999, 0x2000, THREAD_JOINABLE, "loading");
}

void end_loading()
{
	u64 ret;
	loading=NO;
	sysThreadJoin(loading_id, &ret);
}

float DrawStringFromCenterX(float x, float y, char *txt)
{
	return DrawString(x-GetWidth(txt)/2, y, txt);
}

//*******************************************************
//lv2 syscalls
//*******************************************************

u64 lv2peek(u64 addr)
{ 
	lv2syscall1(6, (u64) addr >> 0ULL) ;
	return_to_user_prog(u64);
}

u64 lv2poke(u64 addr, u64 value) 
{ 
	lv2syscall2(7, (u64) addr, (u64) value); 
	return_to_user_prog(u64);
}

static void lv2poke32(u64 addr, uint32_t val)
{
	uint32_t next = lv2peek(addr) & 0xffffffff;
	lv2poke(addr, (((u64) val) << 32) | next);
}

static inline void _poke(u64 addr, u64 val)
{
	lv2poke(0x8000000000000000ULL + addr, val);
}

static inline void _poke32(u64 addr, uint32_t val)
{
	lv2poke32(0x8000000000000000ULL + addr, val);
}

u8 lv2peek8(u64 addr) {
	u8 ret = (u8) (lv2peek(addr) >> 56ULL);
	return ret;
}

u64 lv2poke8(u64 addr, u8 value) 
{ 
	return lv2poke(addr, (((u64) value) <<56) | (lv2peek(addr) & 0xffffffffffffffULL));
}

void lv1poke( u64 addr, u64 val)
{
	lv2syscall2(9, addr, val);
}

int sys_fs_mount(char const* deviceName, char const* deviceFileSystem, char const* devicePath, int writeProt) 
{
	lv2syscall8(837, (u64) deviceName, (u64) deviceFileSystem, (u64) devicePath, 0, (u64) writeProt, 0, 0, 0 );
	return_to_user_prog(int);
}

int sys_fs_umount(char const* devicePath) 
{
	lv2syscall3(838,  (u64) devicePath, 0, 0 );
	return_to_user_prog(int);
}

int sys_fs_chown(char *path, s32 uid, s32 gid)
{
	lv2syscall3(835, (u64) path, (u64) uid, (u64) gid);
	return_to_user_prog(int);
}

u64 syscall_40(u64 cmd, u64 arg)
{
	lv2syscall2(40, cmd, arg);
	return_to_user_prog(u64);
}

s32 sys_map_paths(char *paths[], char *new_paths[], unsigned int num)
{
	lv2syscall4(8, SYSCALL8_OPCODE_MAP_PATHS, (uint64_t)paths, (uint64_t)new_paths, num);
	return_to_user_prog(s32);
}

s32 open_device( u64 device_ID, u32* fd )
{
	lv2syscall4( 600, device_ID, 0, (u64)fd, 0 );
	return_to_user_prog(s32);
}

s32 close_device( u32 fd)
{
	lv2syscall1( 601, fd );
	return_to_user_prog(s32);
}

s32 read_device( u32 fd, u64 start_sector, u64 nb_sector, const void* buffer, u32 *number_byte_read, u64 flags )
{
	lv2syscall7( 602, fd, 0, start_sector, nb_sector, (u64)buffer, (u64)number_byte_read, flags );
	return_to_user_prog(s32);
}

s32 write_device( u32 fd, u64 start_sector, u64 nb_sector, const void* buffer, u32 *number_byte_wrote, u64 flags )
{
	lv2syscall7( 603, fd, 0, start_sector, nb_sector, (u64)buffer, (u64)number_byte_wrote, flags );
	return_to_user_prog(s32);
}

//*******************************************************
// Init firmware
//*******************************************************

int init_fw()
{
	if(( lv2peek(FW_DATE_OFFSET_421C    )==FW_DATE_1_421C) &&
	   ( lv2peek(FW_DATE_OFFSET_421C + 8)==FW_DATE_2_421C) )
	{
		
		firmware = 0x421C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_421C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_421C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_421C;
		OFFSET_FIX = OFFSET_FIX_421C;
		HV_START_OFFSET = HV_START_OFFSET_421C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_421C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_421C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_421C;
		SYSCALL_TABLE = SYSCALL_TABLE_421C;
		LV2MOUNTADDR = LV2MOUNTADDR_421C;
		OPEN_HOOK = OPEN_HOOK_421C;
		BASE_ADDR = BASE_ADDR_421C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_421C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_421C;
		
		PAYLOAD_SKY_SIZE = payload_sky_421C_bin_size;
		PAYLOAD_SKY = (u64) payload_sky_421C_bin;
		UMOUNT_SIZE = umount_421C_bin_size;
		UMOUNT = (u64) umount_421C_bin;
		MAMBA_SIZE = mamba_421C_lz_bin_size;
		MAMBA = (u64) mamba_421C_lz_bin;
		MAMBA_LOADER_SIZE = mamba_loader_421C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_421C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_421D    )==FW_DATE_1_421D) &&
	   ( lv2peek(FW_DATE_OFFSET_421D + 8)==FW_DATE_2_421D) )
	{
		firmware = 0x421D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_421D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_421D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_421D;
		OFFSET_FIX = OFFSET_FIX_421D;
		HV_START_OFFSET = HV_START_OFFSET_421D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_421D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_421D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_421D;
		SYSCALL_TABLE = SYSCALL_TABLE_421D;
		LV2MOUNTADDR = LV2MOUNTADDR_421D;
		OPEN_HOOK = OPEN_HOOK_421D;
		BASE_ADDR = BASE_ADDR_421D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_421D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_421D;

		PAYLOAD_SKY = (u64) payload_sky_421D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_421D_bin_size;
		UMOUNT = (u64) umount_421D_bin;
		UMOUNT_SIZE = umount_421D_bin_size;
		MAMBA = (u64) mamba_421D_lz_bin;
		MAMBA_SIZE = mamba_421D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_421D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_421D_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_430C    )==FW_DATE_1_430C) &&
	   ( lv2peek(FW_DATE_OFFSET_430C + 8)==FW_DATE_2_430C) )
	{
		firmware = 0x430C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_430C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_430C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_430C;
		OFFSET_FIX = OFFSET_FIX_430C;
		HV_START_OFFSET = HV_START_OFFSET_430C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_430C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_430C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_430C;
		SYSCALL_TABLE = SYSCALL_TABLE_430C;
		LV2MOUNTADDR = LV2MOUNTADDR_430C;
		OPEN_HOOK = OPEN_HOOK_430C;
		BASE_ADDR = BASE_ADDR_430C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_430C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_430C;
		
		PAYLOAD_SKY = (u64) payload_sky_430C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_430C_bin_size;
		UMOUNT = (u64) umount_430C_bin;
		UMOUNT_SIZE = umount_430C_bin_size;
		MAMBA = (u64) mamba_430C_lz_bin;
		MAMBA_SIZE = mamba_430C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_430C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_430C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_430D    )==FW_DATE_1_430D) &&
	   ( lv2peek(FW_DATE_OFFSET_430D + 8)==FW_DATE_2_430D) )
	{
		firmware = 0x430D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_430D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_430D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_430D;
		OFFSET_FIX = OFFSET_FIX_430D;
		HV_START_OFFSET = HV_START_OFFSET_430D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_430D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_430D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_430D;
		SYSCALL_TABLE = SYSCALL_TABLE_430D;
		LV2MOUNTADDR = LV2MOUNTADDR_430D;
		OPEN_HOOK = OPEN_HOOK_430D;
		BASE_ADDR = BASE_ADDR_430D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_430D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_430D;
		
		PAYLOAD_SKY = (u64) payload_sky_430D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_430D_bin_size;
		UMOUNT = (u64) umount_430D_bin;
		UMOUNT_SIZE = umount_430D_bin_size;
		MAMBA = (u64) mamba_430D_lz_bin;
		MAMBA_SIZE = mamba_430D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_430D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_430D_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_431C    )==FW_DATE_1_431C) &&
	   ( lv2peek(FW_DATE_OFFSET_431C + 8)==FW_DATE_2_431C) )
	{
		firmware = 0x431C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_431C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_431C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_431C;
		OFFSET_FIX = OFFSET_FIX_431C;
		HV_START_OFFSET = HV_START_OFFSET_431C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_431C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_431C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_431C;
		SYSCALL_TABLE = SYSCALL_TABLE_431C;
		LV2MOUNTADDR = LV2MOUNTADDR_431C;
		OPEN_HOOK = OPEN_HOOK_431C;
		BASE_ADDR = BASE_ADDR_431C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_431C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_431C;
		
		PAYLOAD_SKY = (u64) payload_sky_431C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_431C_bin_size;
		UMOUNT = (u64) umount_431C_bin;
		UMOUNT_SIZE = umount_431C_bin_size;
		MAMBA = (u64) mamba_431C_lz_bin;
		MAMBA_SIZE = mamba_431C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_431C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_431C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_440C    )==FW_DATE_1_440C) &&
	   ( lv2peek(FW_DATE_OFFSET_440C + 8)==FW_DATE_2_440C) )
	{
		firmware = 0x440C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_440C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_440C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_440C;
		OFFSET_FIX = OFFSET_FIX_440C;
		HV_START_OFFSET = HV_START_OFFSET_440C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_440C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_440C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_440C;
		SYSCALL_TABLE = SYSCALL_TABLE_440C;
		LV2MOUNTADDR = LV2MOUNTADDR_440C;
		OPEN_HOOK = OPEN_HOOK_440C;
		BASE_ADDR = BASE_ADDR_440C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_440C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_440C;
		
		PAYLOAD_SKY = (u64) payload_sky_440C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_440C_bin_size;
		UMOUNT = (u64) umount_440C_bin;
		UMOUNT_SIZE = umount_440C_bin_size;
		MAMBA = (u64) mamba_440C_lz_bin;
		MAMBA_SIZE = mamba_440C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_440C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_440C_bin;
		
	}	else
	if(( lv2peek(FW_DATE_OFFSET_441C    )==FW_DATE_1_441C) &&
	   ( lv2peek(FW_DATE_OFFSET_441C + 8)==FW_DATE_2_441C) )
	{
		firmware = 0x441C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_441C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_441C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_441C;
		OFFSET_FIX = OFFSET_FIX_441C;
		HV_START_OFFSET = HV_START_OFFSET_441C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_441C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_441C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_441C;
		SYSCALL_TABLE = SYSCALL_TABLE_441C;
		LV2MOUNTADDR = LV2MOUNTADDR_441C;
		OPEN_HOOK = OPEN_HOOK_441C;
		BASE_ADDR = BASE_ADDR_441C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_441C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_441C;
		
		PAYLOAD_SKY = (u64) payload_sky_441C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_441C_bin_size;
		UMOUNT = (u64) umount_441C_bin;
		UMOUNT_SIZE = umount_441C_bin_size;
		MAMBA = (u64) mamba_441C_lz_bin;
		MAMBA_SIZE = mamba_441C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_441C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_441C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_441D    )==FW_DATE_1_441D) &&
	   ( lv2peek(FW_DATE_OFFSET_441D + 8)==FW_DATE_2_441D) )
	{
		firmware = 0x441D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_441D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_441D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_441D;
		OFFSET_FIX = OFFSET_FIX_441D;
		HV_START_OFFSET = HV_START_OFFSET_441D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_441D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_441D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_441D;
		SYSCALL_TABLE = SYSCALL_TABLE_441D;
		LV2MOUNTADDR = LV2MOUNTADDR_441D;
		OPEN_HOOK = OPEN_HOOK_441D;
		BASE_ADDR = BASE_ADDR_441D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_441D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_441D;
		
		PAYLOAD_SKY = (u64) payload_sky_441D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_441D_bin_size;
		UMOUNT = (u64) umount_441D_bin;
		UMOUNT_SIZE = umount_441D_bin_size;
		MAMBA = (u64) mamba_441D_lz_bin;
		MAMBA_SIZE = mamba_441D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_441D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_441D_bin;
		
	}	else
	if(( lv2peek(FW_DATE_OFFSET_446C    )==FW_DATE_1_446C) &&
	   ( lv2peek(FW_DATE_OFFSET_446C + 8)==FW_DATE_2_446C) )
	{
		firmware = 0x446C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_446C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_446C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_446C;
		OFFSET_FIX = OFFSET_FIX_446C;
		HV_START_OFFSET = HV_START_OFFSET_446C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_446C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_446C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_446C;
		SYSCALL_TABLE = SYSCALL_TABLE_446C;
		LV2MOUNTADDR = LV2MOUNTADDR_446C;
		OPEN_HOOK = OPEN_HOOK_446C;
		BASE_ADDR = BASE_ADDR_446C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_446C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_446C;
		
		PAYLOAD_SKY = (u64) payload_sky_446C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_446C_bin_size;
		UMOUNT = (u64) umount_446C_bin;
		UMOUNT_SIZE = umount_446C_bin_size;
		MAMBA = (u64) mamba_446C_lz_bin;
		MAMBA_SIZE = mamba_446C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_446C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_446C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_446D    )==FW_DATE_1_446D) &&
	   ( lv2peek(FW_DATE_OFFSET_446D + 8)==FW_DATE_2_446D) )
	{ 
		firmware = 0x446D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_446D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_446D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_446D;
		OFFSET_FIX = OFFSET_FIX_446D;
		HV_START_OFFSET = HV_START_OFFSET_446D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_446D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_446D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_446D;
		SYSCALL_TABLE = SYSCALL_TABLE_446D;
		LV2MOUNTADDR = LV2MOUNTADDR_446D;
		OPEN_HOOK = OPEN_HOOK_446D;
		BASE_ADDR = BASE_ADDR_446D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_446D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_446D;
		
		PAYLOAD_SKY = (u64) payload_sky_446D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_446D_bin_size;
		UMOUNT = (u64) umount_446D_bin;
		UMOUNT_SIZE = umount_446D_bin_size;
		MAMBA = (u64) mamba_446D_lz_bin;
		MAMBA_SIZE = mamba_446D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_446D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_446D_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_450C    )==FW_DATE_1_450C) &&
	   ( lv2peek(FW_DATE_OFFSET_450C + 8)==FW_DATE_2_450C) )
	{
		firmware = 0x450C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_450C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_450C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_450C;
		OFFSET_FIX = OFFSET_FIX_450C;
		HV_START_OFFSET = HV_START_OFFSET_450C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_450C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_450C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_450C;
		SYSCALL_TABLE = SYSCALL_TABLE_450C;
		LV2MOUNTADDR = LV2MOUNTADDR_450C;
		OPEN_HOOK = OPEN_HOOK_450C;
		BASE_ADDR = BASE_ADDR_450C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_450C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_450C;
		
		PAYLOAD_SKY = (u64) payload_sky_450C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_450C_bin_size;
		UMOUNT = (u64) umount_450C_bin;
		UMOUNT_SIZE = umount_450C_bin_size;
		MAMBA = (u64) mamba_450C_lz_bin;
		MAMBA_SIZE = mamba_450C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_450C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_450C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_450D    )==FW_DATE_1_450D) &&
	   ( lv2peek(FW_DATE_OFFSET_450D + 8)==FW_DATE_2_450D) )
	{
		firmware = 0x450D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_450D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_450D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_450D;
		OFFSET_FIX = OFFSET_FIX_450D;
		HV_START_OFFSET = HV_START_OFFSET_450D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_450D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_450D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_450D;
		SYSCALL_TABLE = SYSCALL_TABLE_450D;
		LV2MOUNTADDR = LV2MOUNTADDR_450D;
		OPEN_HOOK = OPEN_HOOK_450D;
		BASE_ADDR = BASE_ADDR_450D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_450D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_450D;
		
		PAYLOAD_SKY = (u64) payload_sky_450D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_450D_bin_size;
		UMOUNT = (u64) umount_450D_bin;
		UMOUNT_SIZE = umount_450D_bin_size;
		MAMBA = (u64) mamba_450D_lz_bin;
		MAMBA_SIZE = mamba_450D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_450D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_450D_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_453C    )==FW_DATE_1_453C) &&
	   ( lv2peek(FW_DATE_OFFSET_453C + 8)==FW_DATE_2_453C) )
	{
		firmware = 0x453C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_453C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_453C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_453C;
		OFFSET_FIX = OFFSET_FIX_453C;
		HV_START_OFFSET = HV_START_OFFSET_453C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_453C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_453C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_453C;
		SYSCALL_TABLE = SYSCALL_TABLE_453C;
		LV2MOUNTADDR = LV2MOUNTADDR_453C;
		OPEN_HOOK = OPEN_HOOK_453C;
		BASE_ADDR = BASE_ADDR_453C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_453C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_453C;
		
		PAYLOAD_SKY = (u64) payload_sky_453C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_453C_bin_size;
		UMOUNT = (u64) umount_453C_bin;
		UMOUNT_SIZE = umount_453C_bin_size;
		MAMBA = (u64) mamba_453C_lz_bin;
		MAMBA_SIZE = mamba_453C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_453C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_453C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_453D    )==FW_DATE_1_453D) &&
	   ( lv2peek(FW_DATE_OFFSET_453D + 8)==FW_DATE_2_453D) )
	{
		firmware = 0x453D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_453D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_453D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_453D;
		OFFSET_FIX = OFFSET_FIX_453D;
		HV_START_OFFSET = HV_START_OFFSET_453D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_453D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_453D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_453D;
		SYSCALL_TABLE = SYSCALL_TABLE_453D;
		LV2MOUNTADDR = LV2MOUNTADDR_453D;
		OPEN_HOOK = OPEN_HOOK_453D;
		BASE_ADDR = BASE_ADDR_453D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_453D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_453D;
		
		PAYLOAD_SKY = (u64) payload_sky_453D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_453D_bin_size;
		UMOUNT = (u64) umount_453D_bin;
		UMOUNT_SIZE = umount_453D_bin_size;
		MAMBA = (u64) mamba_453D_lz_bin;
		MAMBA_SIZE = mamba_453D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_453D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_453D_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_455C    )==FW_DATE_1_455C) &&
	   ( lv2peek(FW_DATE_OFFSET_455C + 8)==FW_DATE_2_455C) )
	{
		firmware = 0x455C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_455C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_455C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_455C;
		OFFSET_FIX = OFFSET_FIX_455C;
		HV_START_OFFSET = HV_START_OFFSET_455C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_455C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_455C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_455C;
		SYSCALL_TABLE = SYSCALL_TABLE_455C;
		LV2MOUNTADDR = LV2MOUNTADDR_455C;
		OPEN_HOOK = OPEN_HOOK_455C;
		BASE_ADDR = BASE_ADDR_455C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_455C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_455C;
		
		PAYLOAD_SKY = (u64) payload_sky_455C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_455C_bin_size;
		UMOUNT = (u64) umount_455C_bin;
		UMOUNT_SIZE = umount_455C_bin_size;
		MAMBA = (u64) mamba_455C_lz_bin;
		MAMBA_SIZE = mamba_455C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_455C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_455C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_455D    )==FW_DATE_1_455D) &&
	   ( lv2peek(FW_DATE_OFFSET_455D + 8)==FW_DATE_2_455D) )
	{
		firmware = 0x455D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_455D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_455D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_455D;
		OFFSET_FIX = OFFSET_FIX_455D;
		HV_START_OFFSET = HV_START_OFFSET_455D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_455D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_455D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_455D;
		SYSCALL_TABLE = SYSCALL_TABLE_455D;
		LV2MOUNTADDR = LV2MOUNTADDR_455D;
		OPEN_HOOK = OPEN_HOOK_455D;
		BASE_ADDR = BASE_ADDR_455D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_455D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_455D;
		
		PAYLOAD_SKY = (u64) payload_sky_455D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_455D_bin_size;
		UMOUNT = (u64) umount_455D_bin;
		UMOUNT_SIZE = umount_455D_bin_size;
		MAMBA = (u64) mamba_455D_lz_bin;
		MAMBA_SIZE = mamba_455D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_455D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_455D_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_460C    )==FW_DATE_1_460C) &&
	   ( lv2peek(FW_DATE_OFFSET_460C + 8)==FW_DATE_2_460C) )
	{
		firmware = 0x460C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_460C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_460C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_460C;
		OFFSET_FIX = OFFSET_FIX_460C;
		HV_START_OFFSET = HV_START_OFFSET_460C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_460C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_460C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_460C;
		SYSCALL_TABLE = SYSCALL_TABLE_460C;
		LV2MOUNTADDR = LV2MOUNTADDR_460C;
		OPEN_HOOK = OPEN_HOOK_460C;
		BASE_ADDR = BASE_ADDR_460C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_460C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_460C;
		
		PAYLOAD_SKY = (u64) payload_sky_460C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_460C_bin_size;
		UMOUNT = (u64) umount_460C_bin;
		UMOUNT_SIZE = umount_460C_bin_size;
		MAMBA = (u64) mamba_460C_lz_bin;
		MAMBA_SIZE = mamba_460C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_460C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_460C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_465D    )==FW_DATE_1_465D) &&
	   ( lv2peek(FW_DATE_OFFSET_465D + 8)==FW_DATE_2_465D) )
	{
		firmware = 0x465D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_465D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_465D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_465D;
		OFFSET_FIX = OFFSET_FIX_465D;
		HV_START_OFFSET = HV_START_OFFSET_465D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_465D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_465D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_465D;
		SYSCALL_TABLE = SYSCALL_TABLE_465D;
		LV2MOUNTADDR = LV2MOUNTADDR_465D;
		OPEN_HOOK = OPEN_HOOK_465D;
		BASE_ADDR = BASE_ADDR_465D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_465D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_465D;
		
		PAYLOAD_SKY = (u64) payload_sky_465D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_465D_bin_size;
		UMOUNT = (u64) umount_465D_bin;
		UMOUNT_SIZE = umount_465D_bin_size;
		MAMBA = (u64) mamba_465D_lz_bin;
		MAMBA_SIZE = mamba_465D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_465D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_465D_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_465C    )==FW_DATE_1_465C) &&
	   ( lv2peek(FW_DATE_OFFSET_465C + 8)==FW_DATE_2_465C) )
	{
		firmware = 0x465C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_465C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_465C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_465C;
		OFFSET_FIX = OFFSET_FIX_465C;
		HV_START_OFFSET = HV_START_OFFSET_465C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_465C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_465C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_465C;
		SYSCALL_TABLE = SYSCALL_TABLE_465C;
		LV2MOUNTADDR = LV2MOUNTADDR_465C;
		OPEN_HOOK = OPEN_HOOK_465C;
		BASE_ADDR = BASE_ADDR_465C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_465C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_465C;
		
		PAYLOAD_SKY = (u64) payload_sky_465C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_465C_bin_size;
		UMOUNT = (u64) umount_465C_bin;
		UMOUNT_SIZE = umount_465C_bin_size;
		MAMBA = (u64) mamba_465C_lz_bin;
		MAMBA_SIZE = mamba_465C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_465C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_465C_bin;
		
	} else 
	if(( lv2peek(FW_DATE_OFFSET_470C    )==FW_DATE_1_470C) &&
	   ( lv2peek(FW_DATE_OFFSET_470C + 8)==FW_DATE_2_470C) )
	{
		firmware = 0x470C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_470C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_470C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_470C;
		OFFSET_FIX = OFFSET_FIX_470C;
		HV_START_OFFSET = HV_START_OFFSET_470C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_470C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_470C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_470C;
		SYSCALL_TABLE = SYSCALL_TABLE_470C;
		LV2MOUNTADDR = LV2MOUNTADDR_470C;
		OPEN_HOOK = OPEN_HOOK_470C;
		BASE_ADDR = BASE_ADDR_470C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_470C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_470C;
		
		PAYLOAD_SKY = (u64) payload_sky_470C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_470C_bin_size;
		UMOUNT = (u64) umount_470C_bin;
		UMOUNT_SIZE = umount_470C_bin_size;
		MAMBA = (u64) mamba_470C_lz_bin;
		MAMBA_SIZE = mamba_470C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_470C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_470C_bin;
		
	} else 
	if(( lv2peek(FW_DATE_OFFSET_470D    )==FW_DATE_1_470D) &&
	   ( lv2peek(FW_DATE_OFFSET_470D + 8)==FW_DATE_2_470D) )
	{
		firmware = 0x470D;
		
		OFFSET_2_FIX = OFFSET_2_FIX_470D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_470D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_470D;
		OFFSET_FIX = OFFSET_FIX_470D;
		HV_START_OFFSET = HV_START_OFFSET_470D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_470D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_470D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_470D;
		SYSCALL_TABLE = SYSCALL_TABLE_470D;
		LV2MOUNTADDR = LV2MOUNTADDR_470D;
		OPEN_HOOK = OPEN_HOOK_470D;
		BASE_ADDR = BASE_ADDR_470D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_470D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_470D;
		
		PAYLOAD_SKY = (u64) payload_sky_470D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_470D_bin_size;
		UMOUNT = (u64) umount_470D_bin;
		UMOUNT_SIZE = umount_470D_bin_size;
		MAMBA = (u64) mamba_470D_lz_bin;
		MAMBA_SIZE = mamba_470D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_470D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_470D_bin;
		
	} else 
	if(( lv2peek(FW_DATE_OFFSET_475C    )==FW_DATE_1_475C) &&
	   ( lv2peek(FW_DATE_OFFSET_475C + 8)==FW_DATE_2_475C) )
	{
		firmware = 0x475C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_475C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_475C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_475C;
		OFFSET_FIX = OFFSET_FIX_475C;
		HV_START_OFFSET = HV_START_OFFSET_475C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_475C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_475C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_475C;
		SYSCALL_TABLE = SYSCALL_TABLE_475C;
		LV2MOUNTADDR = LV2MOUNTADDR_475C;
		OPEN_HOOK = OPEN_HOOK_475C;
		BASE_ADDR = BASE_ADDR_475C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_475C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_475C;
		
		PAYLOAD_SKY = (u64) payload_sky_475C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_475C_bin_size;
		UMOUNT = (u64) umount_475C_bin;
		UMOUNT_SIZE = umount_475C_bin_size;
		MAMBA = (u64) mamba_475C_lz_bin;
		MAMBA_SIZE = mamba_475C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_475C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_475C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_475D    )==FW_DATE_1_475D) &&
	   ( lv2peek(FW_DATE_OFFSET_475D + 8)==FW_DATE_2_475D) )
	{
		firmware = 0x475D;

		OFFSET_2_FIX = OFFSET_2_FIX_475D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_475D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_475D;
		OFFSET_FIX = OFFSET_FIX_475D;
		HV_START_OFFSET = HV_START_OFFSET_475D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_475D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_475D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_475D;
		SYSCALL_TABLE = SYSCALL_TABLE_475D;
		LV2MOUNTADDR = LV2MOUNTADDR_475D;
		OPEN_HOOK = OPEN_HOOK_475D;
		BASE_ADDR = BASE_ADDR_475D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_475D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_475D;

		PAYLOAD_SKY = (u64) payload_sky_475D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_475D_bin_size;
		UMOUNT = (u64) umount_475D_bin;
		UMOUNT_SIZE = umount_475D_bin_size;
		MAMBA = (u64) mamba_475D_lz_bin;
		MAMBA_SIZE = mamba_475D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_475D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_475D_bin;

	} else 
	if(( lv2peek(FW_DATE_OFFSET_476C    )==FW_DATE_1_476C) &&
	   ( lv2peek(FW_DATE_OFFSET_476C + 8)==FW_DATE_2_476C) )
	{
		firmware = 0x476C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_476C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_476C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_476C;
		OFFSET_FIX = OFFSET_FIX_476C;
		HV_START_OFFSET = HV_START_OFFSET_476C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_476C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_476C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_476C;
		SYSCALL_TABLE = SYSCALL_TABLE_476C;
		LV2MOUNTADDR = LV2MOUNTADDR_476C;
		OPEN_HOOK = OPEN_HOOK_476C;
		BASE_ADDR = BASE_ADDR_476C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_476C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_476C;
		
		PAYLOAD_SKY = (u64) payload_sky_476C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_476C_bin_size;
		UMOUNT = (u64) umount_476C_bin;
		UMOUNT_SIZE = umount_476C_bin_size;
		MAMBA = (u64) mamba_476C_lz_bin;
		MAMBA_SIZE = mamba_476C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_476C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_476C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_476D    )==FW_DATE_1_476D) &&
	   ( lv2peek(FW_DATE_OFFSET_476D + 8)==FW_DATE_2_476D) )
	{
		firmware = 0x476D;

		OFFSET_2_FIX = OFFSET_2_FIX_476D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_476D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_476D;
		OFFSET_FIX = OFFSET_FIX_476D;
		HV_START_OFFSET = HV_START_OFFSET_476D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_476D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_476D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_476D;
		SYSCALL_TABLE = SYSCALL_TABLE_476D;
		LV2MOUNTADDR = LV2MOUNTADDR_476D;
		OPEN_HOOK = OPEN_HOOK_476D;
		BASE_ADDR = BASE_ADDR_476D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_476D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_476D;

		PAYLOAD_SKY = (u64) payload_sky_476D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_476D_bin_size;
		UMOUNT = (u64) umount_476D_bin;
		UMOUNT_SIZE = umount_476D_bin_size;
		MAMBA = (u64) mamba_476D_lz_bin;
		MAMBA_SIZE = mamba_476D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_476D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_476D_bin;

	} else 
	if(( lv2peek(FW_DATE_OFFSET_478C    )==FW_DATE_1_478C) &&
	   ( lv2peek(FW_DATE_OFFSET_478C + 8)==FW_DATE_2_478C) )
	{
		firmware = 0x478C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_478C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_478C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_478C;
		OFFSET_FIX = OFFSET_FIX_478C;
		HV_START_OFFSET = HV_START_OFFSET_478C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_478C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_478C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_478C;
		SYSCALL_TABLE = SYSCALL_TABLE_478C;
		LV2MOUNTADDR = LV2MOUNTADDR_478C;
		OPEN_HOOK = OPEN_HOOK_478C;
		BASE_ADDR = BASE_ADDR_478C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_478C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_478C;
		
		PAYLOAD_SKY = (u64) payload_sky_478C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_478C_bin_size;
		UMOUNT = (u64) umount_478C_bin;
		UMOUNT_SIZE = umount_478C_bin_size;
		MAMBA = (u64) mamba_478C_lz_bin;
		MAMBA_SIZE = mamba_478C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_478C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_478C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_478D    )==FW_DATE_1_478D) &&
	   ( lv2peek(FW_DATE_OFFSET_478D + 8)==FW_DATE_2_478D) )
	{
		firmware = 0x478D;

		OFFSET_2_FIX = OFFSET_2_FIX_478D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_478D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_478D;
		OFFSET_FIX = OFFSET_FIX_478D;
		HV_START_OFFSET = HV_START_OFFSET_478D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_478D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_478D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_478D;
		SYSCALL_TABLE = SYSCALL_TABLE_478D;
		LV2MOUNTADDR = LV2MOUNTADDR_478D;
		OPEN_HOOK = OPEN_HOOK_478D;
		BASE_ADDR = BASE_ADDR_478D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_478D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_478D;

		PAYLOAD_SKY = (u64) payload_sky_478D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_478D_bin_size;
		UMOUNT = (u64) umount_478D_bin;
		UMOUNT_SIZE = umount_478D_bin_size;
		MAMBA = (u64) mamba_478D_lz_bin;
		MAMBA_SIZE = mamba_478D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_478D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_478D_bin;

	} else 
	if(( lv2peek(FW_DATE_OFFSET_480C    )==FW_DATE_1_480C) &&
	   ( lv2peek(FW_DATE_OFFSET_480C + 8)==FW_DATE_2_480C) )
	{
		firmware = 0x480C;
		
		OFFSET_2_FIX = OFFSET_2_FIX_480C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_480C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_480C;
		OFFSET_FIX = OFFSET_FIX_480C;
		HV_START_OFFSET = HV_START_OFFSET_480C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_480C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_480C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_480C;
		SYSCALL_TABLE = SYSCALL_TABLE_480C;
		LV2MOUNTADDR = LV2MOUNTADDR_480C;
		OPEN_HOOK = OPEN_HOOK_480C;
		BASE_ADDR = BASE_ADDR_480C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_480C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_480C;
		
		PAYLOAD_SKY = (u64) payload_sky_480C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_480C_bin_size;
		UMOUNT = (u64) umount_480C_bin;
		UMOUNT_SIZE = umount_480C_bin_size;
		MAMBA = (u64) mamba_480C_lz_bin;
		MAMBA_SIZE = mamba_480C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_480C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_480C_bin;
		
	} else
	if(( lv2peek(FW_DATE_OFFSET_480D    )==FW_DATE_1_480D) &&
	   ( lv2peek(FW_DATE_OFFSET_480D + 8)==FW_DATE_2_480D) )
	{
		firmware = 0x480D;

		OFFSET_2_FIX = OFFSET_2_FIX_480D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_480D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_480D;
		OFFSET_FIX = OFFSET_FIX_480D;
		HV_START_OFFSET = HV_START_OFFSET_480D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_480D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_480D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_480D;
		SYSCALL_TABLE = SYSCALL_TABLE_480D;
		LV2MOUNTADDR = LV2MOUNTADDR_480D;
		OPEN_HOOK = OPEN_HOOK_480D;
		BASE_ADDR = BASE_ADDR_480D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_480D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_480D;

		PAYLOAD_SKY = (u64) payload_sky_480D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_480D_bin_size;
		UMOUNT = (u64) umount_480D_bin;
		UMOUNT_SIZE = umount_480D_bin_size;
		MAMBA = (u64) mamba_480D_lz_bin;
		MAMBA_SIZE = mamba_480D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_480D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_480D_bin;

	} else
	if(( lv2peek(FW_DATE_OFFSET_481C    )==FW_DATE_1_481C) &&
	   ( lv2peek(FW_DATE_OFFSET_481C + 8)==FW_DATE_2_481C) )
	{
		firmware = 0x481C;

		OFFSET_2_FIX = OFFSET_2_FIX_481C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_481C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_481C;
		OFFSET_FIX = OFFSET_FIX_481C;
		HV_START_OFFSET = HV_START_OFFSET_481C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_481C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_481C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_481C;
		SYSCALL_TABLE = SYSCALL_TABLE_481C;
		LV2MOUNTADDR = LV2MOUNTADDR_481C;
		OPEN_HOOK = OPEN_HOOK_481C;
		BASE_ADDR = BASE_ADDR_481C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_481C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_481C;

		PAYLOAD_SKY = (u64) payload_sky_481C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_481C_bin_size;
		UMOUNT = (u64) umount_481C_bin;
		UMOUNT_SIZE = umount_481C_bin_size;
		MAMBA = (u64) mamba_481C_lz_bin;
		MAMBA_SIZE = mamba_481C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_481C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_481C_bin;

	}  else
	if(( lv2peek(FW_DATE_OFFSET_481D    )==FW_DATE_1_481D) &&
	   ( lv2peek(FW_DATE_OFFSET_481D + 8)==FW_DATE_2_481D) )
	{
		firmware = 0x481D;

		OFFSET_2_FIX = OFFSET_2_FIX_481D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_481D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_481D;
		OFFSET_FIX = OFFSET_FIX_481D;
		HV_START_OFFSET = HV_START_OFFSET_481D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_481D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_481D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_481D;
		SYSCALL_TABLE = SYSCALL_TABLE_481D;
		LV2MOUNTADDR = LV2MOUNTADDR_481D;
		OPEN_HOOK = OPEN_HOOK_481D;
		BASE_ADDR = BASE_ADDR_481D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_481D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_481D;

		PAYLOAD_SKY = (u64) payload_sky_481D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_481D_bin_size;
		UMOUNT = (u64) umount_481D_bin;
		UMOUNT_SIZE = umount_481D_bin_size;
		MAMBA = (u64) mamba_481D_lz_bin;
		MAMBA_SIZE = mamba_481D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_481D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_481D_bin;

	} else
	if(( lv2peek(FW_DATE_OFFSET_482C    )==FW_DATE_1_482C) &&
	   ( lv2peek(FW_DATE_OFFSET_482C + 8)==FW_DATE_2_482C) )
	{
		firmware = 0x482C;

		OFFSET_2_FIX = OFFSET_2_FIX_482C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_482C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_482C;
		OFFSET_FIX = OFFSET_FIX_482C;
		HV_START_OFFSET = HV_START_OFFSET_482C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_482C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_482C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_482C;
		SYSCALL_TABLE = SYSCALL_TABLE_482C;
		LV2MOUNTADDR = LV2MOUNTADDR_482C;
		OPEN_HOOK = OPEN_HOOK_482C;
		BASE_ADDR = BASE_ADDR_482C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_482C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_482C;

		PAYLOAD_SKY = (u64) payload_sky_482C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_482C_bin_size;
		UMOUNT = (u64) umount_482C_bin;
		UMOUNT_SIZE = umount_482C_bin_size;
		MAMBA = (u64) mamba_482C_lz_bin;
		MAMBA_SIZE = mamba_482C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_482C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_482C_bin;

	} else
	if(( lv2peek(FW_DATE_OFFSET_482D    )==FW_DATE_1_482D) &&
	   ( lv2peek(FW_DATE_OFFSET_482D + 8)==FW_DATE_2_482D) )
	{
		firmware = 0x482D;

		OFFSET_2_FIX = OFFSET_2_FIX_482D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_482D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_482D;
		OFFSET_FIX = OFFSET_FIX_482D;
		HV_START_OFFSET = HV_START_OFFSET_482D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_482D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_482D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_482D;
		SYSCALL_TABLE = SYSCALL_TABLE_482D;
		LV2MOUNTADDR = LV2MOUNTADDR_482D;
		OPEN_HOOK = OPEN_HOOK_482D;
		BASE_ADDR = BASE_ADDR_482D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_482D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_482D;

		PAYLOAD_SKY = (u64) payload_sky_482D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_482D_bin_size;
		UMOUNT = (u64) umount_482D_bin;
		UMOUNT_SIZE = umount_482D_bin_size;
		MAMBA = (u64) mamba_482D_lz_bin;
		MAMBA_SIZE = mamba_482D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_482D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_482D_bin;

	} else
	if(( lv2peek(FW_DATE_OFFSET_483C    )==FW_DATE_1_483C) &&
	   ( lv2peek(FW_DATE_OFFSET_483C + 8)==FW_DATE_2_483C) )
	{
		firmware = 0x483C;

		OFFSET_2_FIX = OFFSET_2_FIX_483C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_483C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_483C;
		OFFSET_FIX = OFFSET_FIX_483C;
		HV_START_OFFSET = HV_START_OFFSET_483C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_483C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_483C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_483C;
		SYSCALL_TABLE = SYSCALL_TABLE_483C;
		LV2MOUNTADDR = LV2MOUNTADDR_483C;
		OPEN_HOOK = OPEN_HOOK_483C;
		BASE_ADDR = BASE_ADDR_483C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_483C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_483C;

		PAYLOAD_SKY = (u64) payload_sky_483C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_483C_bin_size;
		UMOUNT = (u64) umount_483C_bin;
		UMOUNT_SIZE = umount_483C_bin_size;
		MAMBA = (u64) mamba_483C_lz_bin;
		MAMBA_SIZE = mamba_483C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_483C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_483C_bin;

	} else
	if(( lv2peek(FW_DATE_OFFSET_484C    )==FW_DATE_1_484C) &&
	   ( lv2peek(FW_DATE_OFFSET_484C + 8)==FW_DATE_2_484C) )
	{
		firmware = 0x484C;

		OFFSET_2_FIX = OFFSET_2_FIX_484C;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_484C;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_484C;
		OFFSET_FIX = OFFSET_FIX_484C;
		HV_START_OFFSET = HV_START_OFFSET_484C;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_484C;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_484C;
		OFFSET_FIX_3C = OFFSET_FIX_3C_484C;
		SYSCALL_TABLE = SYSCALL_TABLE_484C;
		LV2MOUNTADDR = LV2MOUNTADDR_484C;
		OPEN_HOOK = OPEN_HOOK_484C;
		BASE_ADDR = BASE_ADDR_484C;
		OFFSET_1_IDPS = OFFSET_1_IDPS_484C;
		OFFSET_2_IDPS = OFFSET_2_IDPS_484C;

		PAYLOAD_SKY = (u64) payload_sky_484C_bin;
		PAYLOAD_SKY_SIZE = payload_sky_484C_bin_size;
		UMOUNT = (u64) umount_484C_bin;
		UMOUNT_SIZE = umount_484C_bin_size;
		MAMBA = (u64) mamba_484C_lz_bin;
		MAMBA_SIZE = mamba_484C_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_484C_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_484C_bin;

	} else
	if(( lv2peek(FW_DATE_OFFSET_484D    )==FW_DATE_1_484D) &&
	   ( lv2peek(FW_DATE_OFFSET_484D + 8)==FW_DATE_2_484D) )
	{
		firmware = 0x484D;

		OFFSET_2_FIX = OFFSET_2_FIX_484D;
		LV2MOUNTADDR_ESIZE = LV2MOUNTADDR_ESIZE_484D;
		LV2MOUNTADDR_CSIZE = LV2MOUNTADDR_CSIZE_484D;
		OFFSET_FIX = OFFSET_FIX_484D;
		HV_START_OFFSET = HV_START_OFFSET_484D;
		OFFSET_FIX_2B17 = OFFSET_FIX_2B17_484D;
		OFFSET_FIX_LIC = OFFSET_FIX_LIC_484D;
		OFFSET_FIX_3C = OFFSET_FIX_3C_484D;
		SYSCALL_TABLE = SYSCALL_TABLE_484D;
		LV2MOUNTADDR = LV2MOUNTADDR_484D;
		OPEN_HOOK = OPEN_HOOK_484D;
		BASE_ADDR = BASE_ADDR_484D;
		OFFSET_1_IDPS = OFFSET_1_IDPS_484D;
		OFFSET_2_IDPS = OFFSET_2_IDPS_484D;

		PAYLOAD_SKY = (u64) payload_sky_484D_bin;
		PAYLOAD_SKY_SIZE = payload_sky_484D_bin_size;
		UMOUNT = (u64) umount_484D_bin;
		UMOUNT_SIZE = umount_484D_bin_size;
		MAMBA = (u64) mamba_484D_lz_bin;
		MAMBA_SIZE = mamba_484D_lz_bin_size;
		MAMBA_LOADER_SIZE = mamba_loader_484D_bin_size;
		MAMBA_LOADER = (u64 *) mamba_loader_484D_bin;

	} else {return NOK;}
	
	NEW_POKE_SYSCALL_ADDR = lv2peek( lv2peek(SYSCALL_TABLE + NEW_POKE_SYSCALL*8) ) + 0ULL;
	UMOUNT_SYSCALL_OFFSET = lv2peek( lv2peek(SYSCALL_TABLE + 838*8) )  + 8ULL;
	
	return OK;
}

//*******************************************************
// ZIP
//*******************************************************

u8 ExtractZip(char* ZipFile)
{
	char FileOUT[255];
	char Folder[255];
	
	int err=0;
	struct zip *f_zip=NULL;
	
	strcpy(Folder, ZipFile);
	Folder[strlen(Folder)-4]=0;
	
	mkdir(Folder, 0777);
	
	f_zip = zip_open(ZipFile, ZIP_CHECKCONS, &err);
	if(err != ZIP_ER_OK || f_zip==NULL)
	{
		print_load("Error : zip_open");
		return FAILED;
	}

	int count = zip_get_num_files(f_zip);
	if(count==-1)
	{
		print_load("Error : zip_get_num_files");
		zip_close(f_zip);
		return FAILED;
	}
	
	prog_bar1_value = 0;
	int i;
	for(i=0; i<count; i++)
	{
		prog_bar1_value = (i*100)/count;
		
		struct zip_stat file_stat;
		struct zip_file* file_zip=NULL;
		
		zip_stat_index(f_zip, i, 0, &file_stat);
		
		if(zip_stat(f_zip, file_stat.name, 0, &file_stat) == -1)
		{
			print_load("Error : zip_stat");
			zip_close(f_zip);
			return FAILED;
		}
		
		print_load((char*)file_stat.name);
		
		sprintf(FileOUT, "%s/%s", Folder, file_stat.name);
		
		if(FileOUT[strlen(FileOUT)-1]=='/') {
			FileOUT[strlen(FileOUT)-1]=0;
			mkdir(FileOUT, 0777);
			continue;
		}
		
		file_zip=zip_fopen(f_zip, file_stat.name, ZIP_FL_UNCHANGED);
		if(!file_zip)
		{
			print_load("Error : zip_fopen");
			zip_close(f_zip);
			return FAILED;
		}
		
		u64 pos = 0ULL;
		u64 read = 0, writed = 0;
		FILE* f;
		
		prog_bar2_value=0;
		
		f = fopen(FileOUT, "wb");
		if(f==NULL) {
			zip_fclose(file_zip);
			zip_close(f_zip);
			return FAILED;
		}

		if( is_ntfs(FileOUT) == NO ) sysLv2FsChmod(FileOUT, 0777);

		int mem_size = 0x1000;
		char *mem = malloc(mem_size);

		while(pos < file_stat.size) {
			
			if(cancel==YES) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			read = file_stat.size - pos; if(read > mem_size) read = mem_size;
			
			writed = zip_fread(file_zip, mem, (size_t) read);
			if(writed<0) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			if(copy_cancel==YES) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			if(read != writed) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			writed = fwrite(mem, 1, read, f);
			if(writed<0) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			if(read != writed) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			pos += read;
			
			prog_bar2_value=pos*100/file_stat.size;
		}
		fclose(f);
		zip_fclose(file_zip);
		
		free(mem);
		
	}
		
	prog_bar1_value = -1;
	prog_bar2_value = -1;
	
	zip_close(f_zip);

	return SUCCESS;
}

u8 ExtractZipFile(char* ZipFile, char* File, char* out)
{

	int id = 0;
	struct zip *f_zip=NULL;
	int err=0;

	f_zip=zip_open(ZipFile, ZIP_CHECKCONS, &err);
	/* s'il y a des erreurs */
	if(err != ZIP_ER_OK || f_zip==NULL)
	{
		print_load("Error : zip_open");
		return FAILED;
	}

	id=zip_name_locate(f_zip,File,0);
	if (id==-1)
	{
		zip_close(f_zip);
		return FAILED;
	}

	
	struct zip_stat file_stat;
	struct zip_file* file_zip=NULL;
	zip_stat_index(f_zip, id, 0, &file_stat);

	if(zip_stat(f_zip, file_stat.name, 0, &file_stat) == -1)
	{
		print_load("Error : zip_stat");
		zip_close(f_zip);
		return FAILED;
	}

	file_zip=zip_fopen(f_zip, file_stat.name, ZIP_FL_UNCHANGED);

	if(!file_zip)
	{
		print_load("Error : zip_fopen");
		zip_close(f_zip);
		return FAILED;
	}

	char *data=NULL;
	data = malloc((size_t)(file_stat.size+1));
	memset(data, 0, (size_t)(file_stat.size+1));
	if(data == NULL)
	{
		print_load("Error : malloc");
		zip_fclose(file_zip);
		zip_close(f_zip);
		return FAILED;
	}

	if(zip_fread(file_zip, data, (size_t)(file_stat.size)) != file_stat.size)
	{
		print_load("Error : zip_fread");
		free(data);
		zip_fclose(file_zip);
		zip_close(f_zip);
		return FAILED;
	}
	zip_fclose(file_zip);
	zip_close(f_zip);

	if( SaveFile(out, data, file_stat.size) == FAILED ) {
		print_load("Error : SaveFile");
		free(data);
		return FAILED;
	}
	free(data);
	
	return SUCCESS;
}

//*******************************************************
//NTFS
//*******************************************************

ntfs_md *mounts;
int mountCount;

int NTFS_Test_Device(char *name)
{
	int i;

	for (i = 0; i < mountCount; i++) {
		if(!strncmp(mounts[i].name, name, 5 - 1 *( name[0] == 'e'))) 
			return (mounts[i].interface->ioType & 0xff) - '0';
	}

	return -1;
	
}

void MountNTFS()
{
	u8 i;
	for (i = 0; i < mountCount; i++) ntfsUnmount(mounts[i].name, 1);
	
	mounts = NULL;
	mountCount = 0;
	mountCount = ntfsMountAll(&mounts, NTFS_SU | NTFS_FORCE);
	if(mountCount < 0) print_load("Error : ntfsMountAll failed	%d", mountCount);

}

//*******************************************************
// Game OPTION
//*******************************************************

volatile u8 dialog_action = 0;

void my_dialog(msgButton button, void *userdata)
{
	switch(button)
	{
		case MSG_DIALOG_BTN_YES:
			dialog_action = 2;
			break;
		case MSG_DIALOG_BTN_NO:
		case MSG_DIALOG_BTN_ESCAPE:
		case MSG_DIALOG_BTN_NONE:
			dialog_action = 1;
			break;
		default:
			break;
	}
}

void wait_dialog()
{
	while(!dialog_action)
	{
		sysUtilCheckCallback();
		tiny3d_Flip();
	}

	msgDialogAbort();
	usleep(100000);
}

u8 DrawDialogYesNo(char * str)
{
	dialog_action = 0;

	msgDialogOpen2(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_YESNO, str, my_dialog, (void*)	0x0000aaaa, NULL );

	wait_dialog();
	
	return (dialog_action-1);
}

u8 DrawDialogOK(char * str)
{
	dialog_action = 0;

	msgDialogOpen2(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_BKG_INVISIBLE, str, my_dialog, (void*)	0x0000aaaa, NULL );

	wait_dialog();
	
	return (dialog_action-1);
}

//*******************************************************
// HASH
//*******************************************************

u8 sha1_file(char *path, unsigned char output[20] )
{
    FILE *f;
    size_t n;
    sha1_context ctx;
    unsigned char buf[1024];
	uint64_t read=0;
	uint64_t file_size;
	
    f = fopen( path, "rb");
    if( f == NULL ) {
		print_load("Error : sha1_file, failed to open file");
		return FAILED;
	}

    sha1_starts( &ctx );
	
	print_head("Calculating SHA1...");
	prog_bar1_value=0;
	
	fseek (f , 0 , SEEK_END);
	file_size = ftell (f);
	fseek(f, 0, SEEK_SET);
	
    while( ( n = fread( buf, 1, sizeof( buf ), f ) ) > 0 ) {
		read+=n;
		prog_bar1_value=(read*100)/file_size;
		sha1_update( &ctx, buf, (int) n );
		if(cancel==YES) break;
	}

    sha1_finish( &ctx, output );

    memset( &ctx, 0, sizeof( sha1_context ) );

    fclose(f);
	
	if(cancel==YES) {
		memset(output, 0, sizeof(output));
		return FAILED;
	}
	
    return SUCCESS;
}

u8 md5_file(char *path, unsigned char output[16])
{
    FILE *f;
    size_t n;
    md5_context ctx;
    unsigned char buf[1024];
	uint64_t read=0;
	uint64_t file_size;
	
	f = fopen( path, "rb");
    if( f == NULL ) {
		//print_load("Error : md5_file, failed to open file");
		return FAILED;
	}

    md5_starts( &ctx );
	
	print_head("Calculating MD5...");
	prog_bar1_value=0;
	
	fseek (f , 0 , SEEK_END);
	file_size = ftell (f);
	fseek(f, 0, SEEK_SET);
	
    while( ( n = fread( buf, 1, sizeof( buf ), f ) ) > 0 ) 
	{
		read+=n;
		prog_bar1_value=(read*100)/file_size;
		md5_update( &ctx, buf, n );
		if(cancel==YES) break;
	}

    md5_finish( &ctx, output );

    memset( &ctx, 0, sizeof( md5_context ) );

    fclose(f);
	
	if(cancel==YES) {
		memset(output, 0, sizeof(output));
		return FAILED;
	}
	
    return SUCCESS;
}

//*******************************************************
// Game OPTION
//*******************************************************

void print_copy_log(char *str)
{	
	int i=0;
	for(i=9; i > 0; i--){
		strcpy(copy_log[i], copy_log[i-1]);
	}
	
	strcpy(copy_log[0], str);
	
	if(strncmp(copy_log[0], "Error", 5) == 0)  sleep(4);
}

void get_hash(FILE* log, int hash_type, char *path)
{
	u8 info = path_info(path);
	char str[255];
	
	if( info == _NOT_EXIST) return; else
	if( info == _FILE) {
		
		print_load(&strrchr(path, '/')[1]);
		if(hash_type == MD5_HASH) {
			u64 res[2];
			md5_file(path, (u8 *) res);	
			sprintf(str, "%016llX%016llX  %s\n", (long long unsigned int) res[0], (long long unsigned int) res[1], &strrchr(path, '/')[1]);
			fputs(str, log);
			return;
		} else
		if(hash_type == SHA1_HASH) {
			u32 res[5];
			sha1_file(path, (u8 *) res);
			sprintf(str, "%08lX%08lX%08lX%08lX%08lX  %s\n",
			(long unsigned int) res[0],(long unsigned int) res[1],(long unsigned int) res[2],
			(long unsigned int) res[3],(long unsigned int) res[4], &strrchr(path, '/')[1]);
			fputs(str, log);
			return;
		}
	}
	
	sprintf(str, "\nPath : %s\n", path);
	fputs(str, log);
	
	char temp[255];
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(path);
	if(d==NULL) return;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		sprintf(temp, "%s/%s", path, dir->d_name);
	
		if(cancel==YES) break;
		
		get_hash(log, hash_type, temp);
	}
	closedir(d);
	
}

void HashFolder(int hash_type, char *dir)
{
	
	FILE* log;
	char log_path[255];
	char str[255];
	
	if(hash_type == MD5_HASH) {
		sprintf(log_path, "%s/content.md5", dir);
	} else
	if(hash_type == SHA1_HASH) {
		sprintf(log_path, "%s/content.sha1", dir);
	}
	
	log = fopen(log_path, "wb");
	if(log==NULL){
		print_load("Error : failed to create %s", log_path);
		return;
	}
	
	print_head("Calculating hash...");
	sprintf(str, "Path : %s\n", dir);
	print_load(str);
	
	get_hash(log, hash_type, dir);
	
	fclose(log);
	
	if(cancel == YES) {
		Delete(log_path);
	}
}

u64 get_size(char *path, u8 upd_data)
{
	struct stat s;
	
	if(stat(path, &s) != 0) return 0; else 
	if(!S_ISDIR(s.st_mode)) { //FILE
		if(upd_data==YES) {
			total_size+=s.st_size;
			nb_file+=1;
		}
		return s.st_size;
	}
	
	if(gathering_cancel==YES) return 0;
	
	if(upd_data == YES) nb_directory+=1;
	
	u64 dir_size=0;
	DIR *d;
	struct dirent *dir;
	
	d = opendir(path);
	if(d==NULL) return 0;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		char temp[255];
		sprintf(temp, "%s/%s", path, dir->d_name);
		
		if(gathering_cancel==YES) return 0;
		
		dir_size += get_size(temp, upd_data);		
	}
	closedir(d);
	
	
	return dir_size;
}

void Delete(char* path)
{
	DIR *d;
	struct dirent *dir;
	
	u8 info_file = path_info(path);
	
	if(info_file == _NOT_EXIST) return; else
	if(info_file == _FILE) {
		unlink(path);
		return;
	} else if(info_file == _DIRECTORY) {
		rmdir(path);
	}
	
	d = opendir(path);
	if(d==NULL) return;
			
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
	
		char newpath[0x440];

		strcpy(newpath, path);
		strcat(newpath, "/");
		strcat(newpath, dir->d_name);
		
		Delete(newpath);
		
	}
	closedir(d);
	rmdir(path);
	
}

int Delete_Game(char *path, int position)
{
	int i;
	char temp[512];
	char game_path[512];
	
	if(path != NULL) {
		strcpy(game_path, path);
	} else strcpy(game_path, list_game_path[position]);
	
	print_load("Deleting %s", game_path);

	
	u8 split666 = is_66600(game_path);
	if( is_splitted_iso(game_path) || split666) {
			
		int l= strlen(game_path);
		game_path[l-1]=0;
		if(split666) game_path[l-2]=0;

		for(i=0; i<100; i++) {
			if(split666) sprintf(temp , "%s%02d" , game_path, i);
			else sprintf(temp , "%s%d" , game_path, i);
			Delete(temp);
		}
	} 
	else {
		Delete(game_path);
	}
		
	if(path != NULL) {
		if(path_info(path) != _NOT_EXIST) return FAILED; else
		return SUCCESS;
	} else
	if(path_info(list_game_path[position]) != _NOT_EXIST ) return FAILED;

	
	print_load("Removing game from list");
	char setPath[128];
	if(iso) sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[ISO]%s.bin", ManaGunZ_id, list_game_id[position]);
	else	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[JB]%s.bin" , ManaGunZ_id, list_game_id[position]);
	Delete(setPath);
	
	remove_GAMELIST(position);
		
	print_load("Update Favorite");
	read_fav();

	print_load("Load game pictures");
	start_Load_GamePIC();
	
	if(position>game_number) position=game_number;
	
	return SUCCESS;
}

void Get_Game_Size(char *path)
{
	total_size=0;
	nb_file= 0;
	nb_directory=0;
	
	u8 split666 = is_66600(path);
	if( is_splitted_iso(path) || split666) {
		char iso_path[255];
		char temp[255];
		int i;
		
		strcpy(iso_path, path);
		
		int l= strlen(iso_path);
		iso_path[l-1]=0;
		if(split666) iso_path[l-2]=0;

		for(i=0; i<100; i++) {
			if(split666) sprintf(temp , "%s%02d" , iso_path, i);
			else sprintf(temp , "%s%d" , iso_path, i);
			get_size(temp, YES);
		}
	} 
	else {
		get_size(path, YES);
	}
}

char *get_unit(u64 nb)
{
	char *str =(char*) malloc(sizeof(char)*32);

	char unit[3];
	
	float size = 0.00;
	
	if(nb >= 1073741824) {
		size = (float) nb / 1073741824;
		sprintf(unit, " G%c", STR_UNIT[0]);
	}
	else
	if(nb >= 1048576) {
		size = (float) nb / 1048576;
		sprintf(unit, " M%c", STR_UNIT[0]);
	}
	else
	if(nb >= 1024) {
		size = (float) nb / 1024;
		sprintf(unit, " K%c", STR_UNIT[0]);
	} 
	else {
		size = (float) nb;
		sprintf(unit, "  %c", STR_UNIT[0]);
	}
  
	float decimal = (int)(100*(size - (int)size));
	if(decimal !=0) {
		char s[10];
		sprintf(s, "%.2g", decimal/100);
		sprintf(str, "%d%s", (int) size , &s[1]);
	} else sprintf(str, "%d", (int) size);
	
	strcat(str, unit);
	
	return str;
	
}

u8 reading = 0;
u8 writing = 0;

static sys_ppu_thread_t Copy_id;

void Draw_Copy_screen(void *unused)
{
	int i;
	
	uint8_t shutdown = NO;
	copy_current_size=0;
	total_size=0;
	nb_file=0;
	nb_directory=0;
	gathering_cancel=NO;
	copy_cancel=NO;
	u8 is_dir = NO;
	if(path_info(copy_src) == _DIRECTORY) is_dir=YES;
	
	u64 previous_size=0;
	
	char speed_STR[32];
	init_timer(4);
	start_timer(4);
	
	while(copy_flag) {
		
		cls();
		ps3pad_read();
		
		Draw_BGS();
		Draw_Notification();
		int x=50, y=40;
		
		FontSize(20);
		
		FontColor(COLOR_4);
		
		if(gathering==YES) {
			DrawString(x , y, STR_GATHERING);
		} else DrawString(x , y, STR_COPYING);
		
		FontColor(COLOR_1);
		
		y+=new_line(1);
		
		DrawFormatString(x , y, "%s :", STR_FROM);
		DrawString(120, y, copy_src);
		
		y+=new_line(1);
		
		DrawFormatString(x , y, "%s :", STR_TO);
		DrawString(120, y, copy_dst);
		
		y+=new_line(1);
		
		if(gathering_cancel==YES)
			DrawFormatString(x , y, "%s : %s", STR_FILES, STR_UNKNOWN);
		else
			DrawFormatString(x , y, "%s : %d", STR_FILES, nb_file);
		
		y+=new_line(1);
		
		if(is_dir) {
			if(gathering_cancel==YES)
				DrawFormatString(x , y, "%s : %s", STR_DIRS, STR_UNKNOWN);
			else
				DrawFormatString(x , y, "%s : %d", STR_DIRS, nb_directory);
			
			y+=new_line(1);
		}
		
		char *size_current = get_unit(copy_current_size);
		DrawString(x, y, size_current);
		if(size_current) free(size_current);
		
		
		if(gathering_cancel==YES) DrawString(x+400-GetWidth(STR_UNKNOWN), y, STR_UNKNOWN); 
		else {
			
			char *size_tot = get_unit(total_size);
			DrawString(x+400-GetWidth(size_tot), y, size_tot);
			if(size_tot) free(size_tot);
		}
		
		if( get_time(4) > 1000 ) {
			char *copy_speed = get_unit(copy_current_size-previous_size);
			
			sprintf(speed_STR, "%s/s", copy_speed);
			if(copy_speed) free(copy_speed);
			
			previous_size = copy_current_size;
			start_timer(4);
		}
		
		
		DrawStringFromCenterX(x+200, y, speed_STR);
		
		y+=new_line(1);
		
		float val;
		if(gathering_cancel==YES) val = 100; else 
		val = copy_current_size * 100 / total_size;
		
		Draw_Progress_Bar(x, y, 4, val, COLOR_2);
		
		y+=15;
		Draw_Progress_Bar(x, y, 4, file_copy_prog_bar, COLOR_2);
	
		y+=20;
		
		DrawFormatString(x, y, "%s : %s", STR_FILE, copy_file);
		
		
		y+=new_line(2);
		
		FontSize(17);
		
		for(i=0; i<10; i++) {
			DrawString(x, y, copy_log[i]);
			y+=new_line(1);
		}

		x=INPUT_X;
		y=INPUT_Y;
		FontColor(COLOR_1);
		SetFontZ(0);

		x=DrawButton(x, y, STR_CANCEL, BUTTON_CIRCLE);
		
		if(shutdown==YES) {
			x=DrawButton(x, y, STR_TURNOFF_YES, BUTTON_SELECT);
		} else {
			x=DrawButton(x, y, STR_TURNOFF_NO, BUTTON_SELECT);
		}
		if(new_pad & BUTTON_SELECT) {
			if(shutdown==YES) shutdown=NO; else shutdown=YES;
		}
		if(new_pad & BUTTON_CIRCLE) {
			if(gathering==YES) {
				gathering_cancel=YES;
				show_msg(STR_CANCELLED);
			} else 	copy_cancel = YES;
		}
		
		tiny3d_Flip();
		//ScreenShot();
	}
	
	if(copy_cancel == YES) Delete_Game(copy_dst, -1);
	else if(shutdown==YES) {
		Delete("/dev_hdd0/tmp/turnoff");
		lv2syscall4(379,0x1100,0,0,0);
	}
	
	memset(copy_src, 0, sizeof(copy_src));
	memset(copy_dst, 0, sizeof(copy_dst));
	copy_current_size=0;
	total_size=0;
	copy_cancel=NO;
	gathering=NO;
	gathering_cancel=NO;
	nb_file=0;
	nb_directory=0;
	
	for(i=0; i<10; i++){
		strcpy(copy_log[i], "\0");
	}
	
	sysThreadExit(0);
}

void start_copy_loading()
{
	copy_flag=YES;
	sysThreadCreate(&Copy_id, Draw_Copy_screen, NULL, 999, 0x2000, THREAD_JOINABLE, "copying");	
}

void end_copy_loading()
{
	u64 ret;
	copy_flag=NO;
	sysThreadJoin(Copy_id, &ret);
}

void initAIO()
{

#ifdef RPCS3
	sysFsAioInit("/dev_hdd0");
	sysFsAioInit("/dev_hdd1");
	sysFsAioInit("/dev_usb000");
	sysFsAioInit("/dev_flash");
	return;
#endif
	
	char mount_point[32];

	DIR *d;
	struct dirent *dir;
	d = opendir("/");		
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		if(strncmp(dir->d_name, "dev_", 4)==0) {
			sprintf(mount_point, "/%s", dir->d_name);
			if(sysFsAioInit(mount_point) != 0) {
				print_load("Warning : failed to sysFsAioInit(%s)", mount_point);
			}
		}
	}
	closedir(d);

}

#define BUFFNUMBER 4
#define AIONUMBER  2
// FAILED 0
#define READY 1
#define BUSY  2
#define DATA_EMPTY 0
#define DATA_FULL  1

u64 BUFFSIZE=0x200000ULL;

static sysFSAio aio_read[AIONUMBER];
static sysFSAio aio_write[AIONUMBER];

u8 reading_statut[AIONUMBER];
u8 writing_statut[AIONUMBER];
	
u8 buffer_statut[BUFFNUMBER] = {DATA_EMPTY};
u8 buffer_to_write;
u8 buffer_to_read;
u64 reading_pos;
u64 writing_pos;
u64 writed;

static void reading_callback(sysFSAio *xaio, s32 error, s32 xid, u64 size)
{
	int i = xaio->usrdata;

	char tmp[128];
    if(error != 0) {
		reading_statut[i] = FAILED;
		sprintf(tmp, "Error : reading error %X", (unsigned int) error); print_copy_log(tmp);
	} else 
	if(size != xaio->size) {
		reading_statut[i] = FAILED;
		sprintf(tmp, "Error : reading size %X / %X", (unsigned int) size, (unsigned int) xaio->size); print_copy_log(tmp);
	} else {
		buffer_statut[buffer_to_read] = DATA_FULL;
		buffer_to_read++;
		if(buffer_to_read==BUFFNUMBER) buffer_to_read=0;
		reading_statut[i] = READY;
	}		
}

static void writing_callback(sysFSAio *xaio, s32 error, s32 xid, u64 size)
{

	int i = xaio->usrdata;
	
	char tmp[128];
	if(error != 0) {
		writing_statut[i] = FAILED;
		sprintf(tmp, "Error : writing error %X", (unsigned int) error); print_copy_log(tmp);
	} else 
	if(size != xaio->size) {
		writing_statut[i] = FAILED;
		sprintf(tmp, "Error : writing size %X / %X", (unsigned int) size, (unsigned int) xaio->size); print_copy_log(tmp);
	} else {
		buffer_statut[buffer_to_write] = DATA_EMPTY;
		buffer_to_write++;
		if(buffer_to_write==BUFFNUMBER) buffer_to_write=0;
		writing_statut[i] = READY;
		copy_current_size+=size;
		writed+=size;
	}		
}

// Asynchronous Copy - include <lv2/sysfs.h>
// sysFsAioInit - sysFsOpen - sysFsAioRead - sysFsAioWrite - sysFsAioFinish - sysFsAioCancel
int CopyFile_async(char *src, char *dst)
{
    
    int fdr, fdw;
    static int id_r[2] = {-1, -1};
	static int id_w[2] = {-1, -1};
	int i;
	
	struct stat s;
	if(stat(src, &s) != 0) return FAILED; 
	if(S_ISDIR(s.st_mode)) return FAILED;
	u64 size = s.st_size;
		
/*	if(sysFsAioInit(src)!= 0) {
		print_load("Error : failed to copy_async / sysFsAioInit(src)");
		return FAILED;
	}
*/
	if(sysFsOpen(src, SYS_O_RDONLY, &fdr, 0,0) != 0) {
		//sysFsAioFinish(src);
		print_copy_log("Error : failed to copy_async / sysFsOpen(src)");
		return FAILED;
	}
/*
    if(sysFsAioInit(dst)!= 0)  {
		sysFsAioFinish(src);
		sysFsClose(fdr);
		print_load("Error : failed to copy_async / sysFsAioInit(dst)");
		return FAILED;
	}
*/
	if(sysFsOpen(dst, SYS_O_CREAT | SYS_O_TRUNC | SYS_O_WRONLY, &fdw, 0, 0) != 0) {
		//sysFsAioFinish(src);
		//sysFsAioFinish(dst);
		sysFsClose(fdr);
		print_copy_log("Error : failed to copy_async / sysFsOpen(src)");
		return FAILED;
	}

	char *mem = (char *) malloc(BUFFNUMBER * BUFFSIZE);
	if(mem == NULL) {
		print_copy_log("Error : failed to copy_async / malloc");
		return FAILED;
	}
	
	for(i=0; i<BUFFNUMBER; i++)	buffer_statut[i] = DATA_EMPTY;
	for(i=0; i<AIONUMBER; i++) {
		aio_read[i].fd  = -1;
		aio_write[i].fd = -1;
		reading_statut[i]=READY;
		writing_statut[i]=READY;
	}

	reading_pos=0ULL;
	writing_pos=0ULL;		
	buffer_to_write=0;
	buffer_to_read=0;
	writed=0;
	
    while(writed<size) {
		
        if(cancel) goto error;
		
		for(i=0; i<AIONUMBER; i++) {
		
			if(reading_statut[i] == READY) {
				
				if(buffer_statut[buffer_to_read] == DATA_EMPTY) {			
				
					if( reading_pos < size) {
						aio_read[i].fd = fdr;
						aio_read[i].offset = reading_pos;
						aio_read[i].buffer_addr = (u32) (u64) &mem[buffer_to_read * BUFFSIZE];
						aio_read[i].size = size - reading_pos;
						if(aio_read[i].size > BUFFSIZE) aio_read[i].size = BUFFSIZE;
						aio_read[i].usrdata = i;
										
						reading_statut[i] = BUSY;
						
						reading_pos+=aio_read[i].size;
						
						if(sysFsAioRead(&aio_read[i], &id_r[i], reading_callback) != 0) {
							print_copy_log("Error : failed to copy_async / sysFsAioRead");
							goto error;
						}
					}
				}
            }
        
		
			if(reading_statut[i] == FAILED) {
				print_copy_log("Error : failed to copy_async / reading_statut = FAILED !");
				goto error;
			}
			
			if(writing_statut[i] == READY) {

				if(buffer_statut[buffer_to_write] == DATA_FULL) {
					if( writing_pos < size) {
						aio_write[i].fd = fdw;
						aio_write[i].offset = writing_pos;
						aio_write[i].buffer_addr = (u32) (u64) &mem[buffer_to_write * BUFFSIZE];
						aio_write[i].size = size - writing_pos;
						if(aio_write[i].size > BUFFSIZE) aio_write[i].size = BUFFSIZE;
						aio_write[i].usrdata = i;
									
						writing_statut[i] = BUSY;
						
						writing_pos += aio_write[i].size;
						
						if(sysFsAioWrite(&aio_write[i], &id_w[i], writing_callback) != 0) {
							print_copy_log("Error : failed to copy_async / sysFsAioWrite");
							goto error;
						}
					} 
				}
			}
			
			if(writing_statut[i] == FAILED) {
				print_copy_log("Error : failed to copy_async / writing_statut = FAILED !");
				goto error;
			}
			
			file_copy_prog_bar=writed*100/size;
			
		}
    }
	
	for(i=0; i<AIONUMBER; i++) {
		sysFsClose(aio_read[i].fd);
		sysFsClose(aio_write[i].fd);
	}
//  sysFsAioFinish(src);
//	sysFsAioFinish(dst);
    free(mem);
	SetFilePerms(dst);
	
    return SUCCESS;

error:
	for(i=0; i<AIONUMBER; i++) {
		sysFsAioCancel(id_r[i]);
		sysFsAioCancel(id_w[i]);
	}
	for(i=0; i<AIONUMBER; i++) {
		sysFsClose(aio_read[i].fd);
		sysFsClose(aio_write[i].fd);
	}
	
	
//  sysFsAioFinish(src);
//	sysFsAioFinish(dst);
    free(mem);
   
    return FAILED;
}

// sysFs Copy - include <lv2/sysfs.h>
// sysLv2FsOpen - sysLv2FsRead - sysLv2FsWrite - sysLv2FsClose
u8 CopyFile_sysFs(char* src, char* dst)
{
	u8 ret = SUCCESS;
	u64 lenght = 0LL;
	char *mem = NULL;
	u64 pos = 0ULL;
	u64 read = 0, writed = 0;
	int f1;
	int f2;
	
	file_copy_prog_bar=0;

	struct stat s;
	if(stat(src, &s) != 0) return FAILED; 
	if(S_ISDIR(s.st_mode)) return FAILED;
	lenght = s.st_size;
	
	ret = sysFsOpen(src, SYS_O_RDONLY, &f1, NULL, 0);
	if(ret) return FAILED;
	
	ret = sysFsOpen(dst, SYS_O_WRONLY | SYS_O_CREAT | SYS_O_TRUNC, &f2, NULL, 0);
	if(ret) {sysFsClose(f1);return FAILED;}
	
	mem = malloc(BUFFSIZE);
	if(mem == NULL) {
		sysFsClose(f1);
		sysFsClose(f2);
		return FAILED;
	}
	
	while(pos < lenght)
	{
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		read = lenght - pos; 
		if(read > BUFFSIZE) read = BUFFSIZE;
		
		ret=sysFsRead(f1, mem, read, &writed);
		if(ret!=0) {ret = FAILED; goto skip;}
		if(read != writed) {ret = FAILED; goto skip;}
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		ret=sysFsWrite(f2, mem, read, &writed);
		if(ret!=0) {ret = FAILED; goto skip;}
		if(read != writed) {ret = FAILED; goto skip;}

		pos += read;
		
		file_copy_prog_bar=pos*100/lenght;
		copy_current_size+=read;
	}

skip:

	file_copy_prog_bar=0;
	
	if(mem) free(mem);
	if(f1) sysFsClose(f1);
	if(f2) sysFsClose(f2);
	
	return ret;
}

// sysLv2Fs Copy - include <sys/file.h>
// sysLv2FsOpen - sysLv2FsRead - sysLv2FsWrite - sysLv2FsClose
u8 CopyFile_sysFsLv2(char* src, char* dst)
{
	u8 ret = SUCCESS;
	u64 lenght = 0LL;
	char *mem = NULL;
	u64 pos = 0ULL;
	u64 read = 0, writed = 0;
	s32 fd = -1;
	s32 fd2 = -1;
	
	file_copy_prog_bar=0;

	struct stat s;
	if(stat(src, &s) != 0) return FAILED; 
	if(S_ISDIR(s.st_mode)) return FAILED;
	lenght = s.st_size;
	
	ret = sysLv2FsOpen(src, 0, &fd, S_IRWXU | S_IRWXG | S_IRWXO, NULL, 0);
	if(ret) return FAILED;

	ret = sysLv2FsOpen(dst, SYS_O_WRONLY | SYS_O_CREAT | SYS_O_TRUNC, &fd2, 0777, NULL, 0);
	if(ret) {sysLv2FsClose(fd); return FAILED;}
	
	mem = malloc(BUFFSIZE);
	if(mem == NULL) return FAILED;

	while(pos < lenght)
	{
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		read = lenght - pos; 
		if(read > BUFFSIZE) read = BUFFSIZE;
		
		ret=sysLv2FsRead(fd, mem, read, &writed);
		if(ret!=0) {ret = FAILED; goto skip;}
		if(read != writed) {ret = FAILED; goto skip;}
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		ret=sysLv2FsWrite(fd2, mem, read, &writed);
		if(ret!=0) {ret = FAILED; goto skip;}
		if(read != writed) {ret = FAILED; goto skip;}

		pos += read;
		
		file_copy_prog_bar=pos*100/lenght;
		copy_current_size+=read;
	}

skip:

	file_copy_prog_bar=0;
	
	if(mem) free(mem);
	if(fd >=0) sysLv2FsClose(fd);
	if(fd2>=0) sysLv2FsClose(fd2);
	if(ret) return ret;
	
	return ret;

}

// ps3_ntfs COPY - include <ntfs.h>
// ps3_ntfs_open/ps3_ntfs_read/ps3_ntfs_write/ps3_ntfs_close
u8 CopyFile_ps3ntfs(char* src, char* dst)
{
	u8 ret = SUCCESS;
	u64 lenght = 0LL;
	char *mem = NULL;
	u64 pos = 0ULL;
	u64 read = 0, writed = 0;
	int f1=-1;
	int f2=-1;
	u8 join=NO;
	u8 split=NO;
	u8 cur_file=0;
	char temp[1024];
	char source[1024];
	char destination[1024];
	
	u64 SPLITSIZE = 4000000000ULL;
	
	strcpy(source, src);
	strcpy(destination, dst);
	if(strcmp(src, dst)==0) {
		RemoveExtention(destination);
		char *temp_str = strcpy_malloc(destination);
		int o;
		for(o=0; o<1000; o++) {
			sprintf(destination, "%s_%03d%s", temp_str, o, GetExtention(dst));
			if(path_info(destination) == _NOT_EXIST) break;
		}
		free(temp_str);
	}
	
	file_copy_prog_bar=0;
	
	struct stat s;
	if(stat(src, &s) != 0) return FAILED; 
	if(S_ISDIR(s.st_mode)) return FAILED;
	lenght = s.st_size;
	
	if(lenght>SPLITSIZE) {
		if(strncmp(dst, "/dev_usb", 8)==0) split=YES;
	}
	if(is_66600(src)==YES && is_66600(dst)==NO) join = YES;
	
	mem = malloc(BUFFSIZE);
	if(mem == NULL) return FAILED;
	
next_file:
	
	if(split) {
		sprintf(destination, "%s.666%02d", dst, cur_file);
	}
	if(f2<0) f2 = ps3ntfs_open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(f2<0) {split=NO; goto skip;}

	if(join) {
		strcpy(temp, src);
		temp[strlen(temp)-2]=0;
		sprintf(source, "%s%02d", temp, cur_file);	
		
		if(0<cur_file) {
			if(stat(source, &s) != 0) {join=NO; goto skip;}
			lenght = s.st_size;
			pos=0;
		}
	}
	
	if(f1<0) f1 = ps3ntfs_open(source, O_RDONLY, 0766);
	if(f1<0) {join=NO; goto skip;}

	while(pos < lenght)
	{
		if(split && pos == SPLITSIZE*(cur_file+1) ) break;
		
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		read = lenght - pos;
		if(split) {
			if(lenght > SPLITSIZE*(cur_file+1))
				read = SPLITSIZE*(cur_file+1) - pos;
		}
		if(read > BUFFSIZE) read = BUFFSIZE;
		
		writed=ps3ntfs_read(f1, mem, read);
		if(read != writed) {ret = FAILED; goto skip;}
		
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		writed=ps3ntfs_write(f2, mem, read);
		if(read != writed) {ret = FAILED; goto skip;}

		pos += read;
		
		file_copy_prog_bar=pos*100/lenght;
		copy_current_size+=read;
	}
	
	if(join) {
		if(f1>=0) {
			ps3ntfs_close(f1);
			f1=-1;
		}
		cur_file++; 
		goto next_file; 
	}
	if(split) {
		if(pos==lenght) goto skip;
		if(f2>=0) {
			ps3ntfs_close(f2);
			f2=-1;
			SetFilePerms(destination);
		}
		cur_file++; 
		goto next_file; 
	}
	
skip:

	file_copy_prog_bar=0;
	
	if(mem) FREE(mem);
	
	if(f1>=0) {
		ps3ntfs_close(f1);
		f1=-1;
	}
	if(f2>=0) {
		ps3ntfs_close(f2);
		f2=-1;
	}
	
	SetFilePerms(destination);
	
	return ret;
}

// fcntl COPY - include <fcntl.h>
// open/read/write/close
u8 CopyFile_fcntl(char* src, char* dst)
{
	u8 ret = SUCCESS;
	u64 lenght = 0LL;
	char *mem = NULL;
	u64 pos = 0ULL;
	u64 rd = 0, writed = 0;
	int f1=-1;
	int f2=-1;
	
	file_copy_prog_bar=0;
	
	struct stat s;
	if(stat(src, &s) != 0) return FAILED; 
	if(S_ISDIR(s.st_mode)) return FAILED;
	lenght = s.st_size;
	
	f1 = open(src, O_RDONLY, 0766);
	if(f1<0) goto skip;

	f2 = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(f2<0) {close(f1);goto skip;}
	
	mem = malloc(BUFFSIZE);
	if(mem == NULL) return FAILED;

	while(pos < lenght)
	{
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		rd = lenght - pos; 
		if(rd > BUFFSIZE) rd = BUFFSIZE;
		
		writed=read(f1, mem, rd);
		if(rd != writed) {ret = FAILED; goto skip;}
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		writed=write(f2, mem, rd);
		if(rd != writed) {ret = FAILED; goto skip;}

		pos += rd;
		
		file_copy_prog_bar=pos*100/lenght;
		copy_current_size+=rd;
	}

skip:

	file_copy_prog_bar=0;
	
	if(mem) free(mem);
	if(f1) close(f1);
	if(f2) close(f2);

	return ret;
}

// Standard I/O - include <stdio.h>
// fopen/fread/fwrite/fclose
// NTFS supported with NTFS_init_system_io();
u8 CopyFile_stdio(char* src, char* dst)
{
	u8 ret = SUCCESS;
	u64 lenght = 0LL;
	char *mem = NULL;
	u64 pos = 0ULL;
	u64 read = 0, writed = 0;

	FILE* f;
	FILE* f2;
	
	file_copy_prog_bar=0;
	
	struct stat s;
	if(stat(src, &s) != 0) return FAILED; 
	if(S_ISDIR(s.st_mode)) return FAILED;
	lenght = s.st_size;
	
	f = fopen(src, "rb");
	if(f==NULL) {ret = FAILED; goto skip;}
	
	f2 = fopen(dst, "wb");
	if(f2==NULL) {ret = FAILED; goto skip;}
	
	if( is_ntfs(dst) == NO ) sysLv2FsChmod(dst, 0777);
	
	mem = malloc(BUFFSIZE);
	
	while(pos < lenght) {
		
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		read = lenght - pos; if(read > BUFFSIZE) read = BUFFSIZE;
		
		writed = fread(mem, 1, read, f);
		if(writed<0) {ret = FAILED; goto skip;}
		
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		if(read != writed) {ret = FAILED; goto skip;}
		
		writed = fwrite(mem, 1, read, f2);
		if(writed<0) {ret = FAILED; goto skip;}
		
		if(read != writed) {ret = FAILED; goto skip;}
		
		pos += read;
		
		file_copy_prog_bar=pos*100/lenght;
		
		copy_current_size+=read;
	
	}
	
skip:
	
	file_copy_prog_bar=0;
	
	if(mem) free(mem);
	if(f) fclose(f);
	if(f2) fclose(f2);
	
	return ret;
}

void TestCopy(char *src, char *dst, int i)
{
	if(i==0) CopyFile_stdio(src, dst); else
	if(i==1) CopyFile_fcntl(src, dst); else
	if(i==2) CopyFile_sysFs(src, dst); else
	if(i==3) CopyFile_sysFsLv2(src, dst); else
	if(i==4) CopyFile_ps3ntfs(src, dst); else
	if(i==5) CopyFile_async(src, dst);
}

#define CopyFile CopyFile_ps3ntfs
void end_checking();

void SpeedTest()
{

	char *TestFile = "/dev_hdd0/TEST.BIN";
	
	char dst[128];
	char dst2[128];
	char dst3[128];
	char tmp[128];
	time_t time_start;
	
	u64 previous_size=0;
	
	if(path_info(TestFile) == _NOT_EXIST) return;
	char *copy_speed=NULL;
	
	init_timer(3);
	
	FILE* f=NULL;
	
	f = fopen("/dev_hdd0/speed_test.txt", "wb");
	if(f==NULL) return;
	
	gathering_cancel=YES;
	
	int i,j;
	copy_speed = get_unit(BUFFSIZE);
	sprintf(tmp, "BUFFSIZE = %s\n", copy_speed); fputs(tmp,f); 
	if(copy_speed) free(copy_speed);
	
	for(j=4; j<6; j++) {		
		
		if(j==0) {strcpy(tmp, "*** CopyFile_stdio ***\n"); fputs(tmp,f);} else
		if(j==1) {strcpy(tmp, "\n*** CopyFile_fcntl ***\n"); fputs(tmp,f);} else
		if(j==2) {strcpy(tmp, "\n*** CopyFile_sysFs ***\n"); fputs(tmp,f);} else
		if(j==3) {strcpy(tmp, "\n*** CopyFile_sysFsLv2 ***\n"); fputs(tmp,f);} else
		if(j==4) {strcpy(tmp, "\n*** CopyFile_ps3_ntfs ***\n"); fputs(tmp,f);} else
		if(j==5) {strcpy(tmp, "\n*** CopyFile_async ***\n"); fputs(tmp,f);}		 

		strcpy(tmp, "HDD0 to HDD0"); fputs(tmp,f); 
		
		strcpy(dst, "/dev_hdd0/tmp/DST.BIN");
		
		start_timer(3);
		time_start = time(NULL);
		TestCopy(TestFile, dst, j);
		copy_speed = get_unit((copy_current_size-previous_size)*1000/get_time(3));
		sprintf(tmp, " = %s/s\n", copy_speed); fputs(tmp,f); 
		sprintf(tmp, "temps : %ds\n", (int)(time(NULL)-time_start)); fputs(tmp,f); 
		if(copy_speed) free(copy_speed);
		previous_size=copy_current_size;
		
		Delete(dst);
		
		strcpy(tmp, "HDD0 to HDD1"); fputs(tmp,f); 
		
		strcpy(dst, "/dev_hdd1/DST.BIN");
		
		start_timer(3);
		time_start = time(NULL);
		TestCopy(TestFile, dst, j);
		copy_speed = get_unit((copy_current_size-previous_size)*1000/get_time(3));
		sprintf(tmp, " = %s/s\n", copy_speed); fputs(tmp,f);
		sprintf(tmp, "temps : %ds\n", (int)(time(NULL)-time_start)); fputs(tmp,f); 
		if(copy_speed) free(copy_speed);
		previous_size=copy_current_size;
		
		Delete(dst);
		
		for(i=0; i<=device_number; i++) {
			if(strstr(list_device[i], "dev_hdd0") != NULL) continue;
			
			sprintf(tmp, "HDD0 to %s", list_device[i]); fputs(tmp,f); 
			
			sprintf(dst, "/%s/DST.BIN", list_device[i]);
			
			start_timer(3);
			time_start = time(NULL);
			TestCopy(TestFile, dst, j);
			copy_speed = get_unit((copy_current_size-previous_size)*1000/get_time(3));
			sprintf(tmp, " = %s/s\n", copy_speed); fputs(tmp,f);
			sprintf(tmp, "temps : %ds\n", (int)(time(NULL)-time_start)); fputs(tmp,f);
			if(copy_speed) free(copy_speed);
			previous_size=copy_current_size;
			
			sprintf(tmp, "%s to HDD0", list_device[i]); fputs(tmp,f); 
			
			strcpy(dst2, "/dev_hdd0/tmp/DST.BIN");
			
			start_timer(3);
			time_start = time(NULL);
			TestCopy(dst, dst2, j);
			copy_speed = get_unit((copy_current_size-previous_size)*1000/get_time(3));
			sprintf(tmp, " = %s/s\n", copy_speed); fputs(tmp,f);
			sprintf(tmp, "temps : %ds\n", (int)(time(NULL)-time_start)); fputs(tmp,f);
			if(copy_speed) free(copy_speed);
			previous_size=copy_current_size;
			
			sprintf(tmp, "%s to %s", list_device[i], list_device[i]); fputs(tmp,f); 
			
			sprintf(dst3, "/%s/DST2.BIN", list_device[i]);
			
			start_timer(3);
			time_start = time(NULL);
			TestCopy(dst, dst3, j);
			copy_speed = get_unit((copy_current_size-previous_size)*1000/get_time(3));
			sprintf(tmp, " = %s/s\n", copy_speed); fputs(tmp,f);
			sprintf(tmp, "temps : %ds\n", (int)(time(NULL)-time_start)); fputs(tmp,f);
			if(copy_speed) free(copy_speed);
			previous_size=copy_current_size;
			
			Delete(dst);
			Delete(dst2);
			Delete(dst3);
		}
	}
	if(f) {fclose(f); f=NULL;}
}

u8 Copy(char *src, char *dst)
{
	
	u8 info_file = path_info(src);
	
	if(info_file == _NOT_EXIST) return FAILED; else
	if(info_file == _FILE) {
		char *tmp;
		tmp = strrchr(src,'/');
		tmp = &tmp[1];
		strcpy(copy_file, tmp);
		return CopyFile(src, dst);
	}

	char temp_src[255];
	char temp_dst[255];
	
	if(path_info(dst) == _NOT_EXIST) mkdir(dst, 0777);
	
	DIR *d;
	struct dirent *dir;
			
	d = opendir(src);
	if(d==NULL) return FAILED;
			
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		sprintf(temp_src, "%s/%s", src, dir->d_name);
		sprintf(temp_dst, "%s/%s", dst, dir->d_name);
		
		if(dir->d_type & DT_DIR) mkdir(temp_dst, 0777);
		
		if( Copy(temp_src, temp_dst) == FAILED) {closedir(d); return FAILED;}
			
		if(copy_cancel==YES) break;
			
	}
	closedir(d);
	
	if(copy_cancel==YES) return FAILED;
	
	return SUCCESS;
	
}

u8 CopyJoin(char *src, char *dst)
{
	
	u8 info_file = path_info(src);
	
	if(info_file == _NOT_EXIST) return FAILED; else
	if(info_file == _FILE) {
		char *tmp;
		tmp = strrchr(src,'/');
		tmp = &tmp[1];
		strcpy(copy_file, tmp);
		
	// JOIN
		if(is_usb(dst)==NO) {
			if(is_666XX(src)==YES) return SUCCESS;
			if(is_66600(src) && is_66600(dst)) dst[strlen(dst)-6]=0;
		}
	// ****
	
		return CopyFile(src, dst);
	}
	

	char temp_src[255];
	char temp_dst[255];
	
	if(path_info(dst) == _NOT_EXIST) mkdir(dst, 0777);
	
	DIR *d;
	struct dirent *dir;
			
	d = opendir(src);
	if(d==NULL) return FAILED;
			
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		sprintf(temp_src, "%s/%s", src, dir->d_name);
		sprintf(temp_dst, "%s/%s", dst, dir->d_name);
		
		if(dir->d_type & DT_DIR) mkdir(temp_dst, 0777);
		
		if( Copy(temp_src, temp_dst) == FAILED) {closedir(d); return FAILED;}
			
		if(copy_cancel==YES) break;
			
	}
	closedir(d);
	
	if(copy_cancel==YES) return FAILED;
	
	return SUCCESS;
	
}

u8 Move(char *src, char *dst)
{
	char dev_src[30];
	char dev_dst[30];
	
	memcpy(dev_src, src, 29);
	memcpy(dev_dst, dst, 29);
	
	if(dev_src[0]=='/') strtok(&dev_src[1], "/");
	else strtok(dev_src, "/");
	if(dev_dst[0]=='/') strtok(&dev_dst[1], "/");
	else strtok(dev_dst, "/");

	if(strcmp(dev_src, dev_dst) == 0) {
		if( rename(src, dst) != 0) return FAILED;
	} else {
		if(Copy(src, dst) == FAILED) return FAILED;
		Delete(src);
	}
	
	return SUCCESS;
}

//*********************************************
// GAME LIST TODOOOOO
//*********************************************

void free_GAMELIST()
{
	s64 i;
	for(i=0; i<=game_number; i++) {
		FREE(list_game_path[i]);
		FREE(list_game_title[i]);
	}
	
	FREE(list_game_path);
	FREE(list_game_title);
	FREE(list_game_platform);
}

void sort_GAMELIST()
{
	print_load("Sorting the game list");
	
	int min; 
	char ta[512], tb[512];
	u8 t;
	int i, j;
	for (i = 0; i<game_number; i++) { 
		min = i;
		for (j = i+1; j <= game_number; j++) { 
			strcpy(ta , list_game_title[j]);
			strcpy(tb, list_game_title[min]);
			if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
			if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
			
			if (strcmp(ta, tb) < 0) min = j;
		}
		if(min==i) continue;
		
		strcpy(ta , list_game_title[min]);
		
		FREE(list_game_title[min]);
		list_game_title[min] = strcpy_malloc(list_game_title[i]);
		
		FREE(list_game_title[i]);
		list_game_title[i] = strcpy_malloc(ta); 
		
		strcpy(tb, list_game_path[min]);
		
		FREE(list_game_path[min]);
		list_game_path[min] = strcpy_malloc(list_game_path[i]);
		
		FREE(list_game_path[i]);
		list_game_path[i] = strcpy_malloc(tb);
		
		t = list_game_platform[min];
		list_game_platform[min] = list_game_platform[i];
		list_game_platform[i] = t;
	}
	
}

void add_GAMELIST(char *path)
{
	u8 ext = get_ext(path);
	
	if(ext != _ISO_PS3 && ext != _JB_PS3
	&& ext != _ISO_PSP && ext != _JB_PSP
	&& ext != _ISO_PS2 && ext != _JB_PS2
	&& ext != _ISO_PS1 && ext != _JB_PS1) return;
	
	game_number++;
	list_game_path = (char **) realloc( list_game_path, (game_number+1) * sizeof(char *));
	list_game_title = (char **) realloc(list_game_title, (game_number+1) * sizeof(char *));
	list_game_id = (char **) realloc(list_game_id, (game_number+1) * sizeof(char *));
	list_game_platform = (u8 *) realloc(list_game_platform, (game_number+1) * sizeof(u8) );
	
	list_game_path[game_number] = strcpy_malloc(path);
	list_game_platform[game_number] = ext;
	
	char title[512];
	char gameID[512];
	strcpy(title, &strrchr(path, '/')[1]);
	RemoveExtention(title);
	
	if(ext == _ISO_PS3 || ext == _JB_PS3 || ext == _ISO_PSP || ext == _JB_PSP) {
		GetParamSFO("TITLE", title, game_number, NULL);
		GetParamSFO("TITLE_ID", gameID, game_number, NULL);
	}
	
	list_game_title[game_number] = strcpy_malloc(title);
	list_game_id[game_number] = strcpy_malloc(gameID);
}

void remove_GAMELIST(s64 pos)
{
	if(pos>game_number) return;
	
	s64 i;
	for(i=pos; i<game_number; i++) {
		FREE(list_game_path[i]);
		list_game_path[i] = strcpy_malloc(list_game_path[i+1]);
		
		FREE(list_game_title[i]);
		list_game_title[i] = strcpy_malloc(list_game_title[i+1]);

		FREE(list_game_id[i]);
		list_game_id[i] = strcpy_malloc(list_game_id[i+1]);
		
		list_game_platform[i] = list_game_platform[i+1];
	}
	
	FREE(list_game_title[game_number]);
	FREE(list_game_path[game_number]);
	FREE(list_game_id[game_number]);
	
	game_number--;
}

void get_GAMELIST(char *scan_path)
{
	print_load("Scanning : %s", scan_path);
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(scan_path);
	if(d==NULL) return;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;

		print_head("[%03d] %s", game_number+1, dir->d_name);
				
		if(game_number+2==MAX_GAME) {
			print_load("Warning : too many games !");
			break;
		}
		
		char temp[512];
		sprintf(temp, "%s/%s" , scan_path, dir->d_name);
		
		add_GAMELIST(temp);
	}
	closedir(d);
}

void Copy_Game(char *src, char *dst)
{
	start_copy_loading();	
	
	strcpy(copy_src, src);
	strcpy(copy_dst, dst);
	
	mkdir(copy_dst, 0777);
	
	char *tmp = strrchr(copy_src, '/');
	strcat(copy_dst, tmp);
	
	gathering=YES;
	Get_Game_Size(copy_src);
	gathering=NO;
	
	u8 ret;
	u8 split666 = is_66600(copy_src);		  
	
	if(split666) {
		if(is_usb(copy_dst)==NO) { 
			ret = CopyJoin(copy_src, copy_dst);
			goto end;
		}
	}
	
	if(is_splitted_iso(copy_src) || split666) {
		char temp_src[128];
		char temp_dst[128];
		char temp_src1[128];
		char temp_dst1[128];			

		int i;
		int l;

		strcpy(temp_src1, copy_src);
		strcpy(temp_dst1, copy_dst);
		
		l= strlen(temp_src1);
		temp_src1[l-1]=0;
		if(split666) temp_src1[l-2]=0;
		
		l= strlen(temp_dst1);
		temp_dst1[l-1]=0;
		if(split666) temp_dst1[l-2]=0;
		
		for(i=0; i<99; i++) {
			if(split666) {
				sprintf(temp_src , "%s%02d", temp_src1, i);
				sprintf(temp_dst , "%s%02d", temp_dst1, i);
			} else {
				sprintf(temp_src , "%s%d", temp_src1, i);
				sprintf(temp_dst , "%s%d", temp_dst1, i);
			}
			if(copy_cancel==YES) goto end;
			ret = Copy(temp_src, temp_dst);
			if(ret==FAILED) break;
		}
		
	} else {
		ret = CopyJoin(copy_src, copy_dst);
	}

end:
	
	if( (total_size <= copy_current_size && copy_current_size != 0) ||	(gathering_cancel == YES && copy_cancel==NO && copy_current_size > 0) ) {
	
		//AddGame(copy_dst);
		
		add_GAMELIST(copy_dst);
		
		sort_GAMELIST();
		
		read_fav();
		start_Load_GamePIC();
		
		show_msg(STR_DONE);
	} else {
		Delete_Game(copy_dst, -1);
		
		if(copy_cancel==YES) show_msg(STR_CANCELLED); else 
		show_msg(STR_FAILED);
	}
	
	end_copy_loading();

}

void Draw_GameProperties()
{
	
	char *tot_size = get_unit(total_size);
	char sys_vers[64];
	memset(sys_vers, 0, 64);
	if(list_game_platform[position] == _JB_PS3 || list_game_platform[position] == _ISO_PS3) {
		char tmp[10];
		if(GetParamSFO("PS3_SYSTEM_VER", tmp, position, NULL)==SUCCESS) {
			float f;
			sscanf(tmp, "%f", &f);
			sprintf(sys_vers, "%.2f", f);
		} else strcpy(sys_vers, STR_UNKNOWN);
	}
	
	char Game_id[20];
	if(Get_ID(list_game_path[position], list_game_platform[position], Game_id) == FAILED) {
		strcpy(Game_id, STR_UNKNOWN);
	}
	
	u8 LoopBreak=1;
	while(LoopBreak) {
		
		cls();
		
		Draw_BGS();
		Draw_ICON0(position, 630, 30, 100, 141.3, 75.9);
		
		int x1=50, y=40;
		int xt;
		
		Draw_Box(x1+5, y+4, 0, 0, 8, 8, COLOR_3, NO);
		FontColor(COLOR_3);
		FontSize(18);
		xt=DrawString(x1+20, y, STR_GAME_PROP);
		y+=new_line(1);
		Draw_Box(x1, y, 0, 0, xt-x1, 2, COLOR_3, NO);

		y+=new_line(2);
		
		FontColor(COLOR_3);
		xt=DrawFormatString(x1 , y, "%s :", STR_GAME_TITLE);
		FontColor(COLOR_1);
		DrawString(xt+10 , y,  list_game_title[position]);
		
		y+=new_line(1);
		
		FontColor(COLOR_3);
		xt=DrawFormatString(x1 , y, "%s :", STR_GAME_PATH);
		FontColor(COLOR_1);
		DrawString(xt+10 , y,  list_game_path[position]);
		
		y+=new_line(1);
		
		FontColor(COLOR_3);
		xt=DrawFormatString(x1 , y, "%s :", STR_GAME_PLATFORM);
		FontColor(COLOR_1);
		if(list_game_platform[position] == _JB_PS3 || list_game_platform[position] == _ISO_PS3) {
			DrawString(xt+10 , y,  "PlayStation 3");
		} else
		if(list_game_platform[position] == _JB_PS2 || list_game_platform[position] == _ISO_PS2) {
			DrawString(xt+10 , y,  "PlayStation 2");
		} else
		if(list_game_platform[position] == _JB_PS1 || list_game_platform[position] == _ISO_PS1) {
			DrawString(xt+10 , y,  "PlayStation");
		} else
		if(list_game_platform[position] == _JB_PSP || list_game_platform[position] == _ISO_PSP) {
			DrawString(xt+10 , y,  "PlayStation Portable");
		} else DrawString(xt+10 , y,  STR_UNKNOWN);
		
		y+=new_line(1);
		
		
		FontColor(COLOR_3);
		xt=DrawFormatString(x1 , y, "%s :", STR_GAME_FORMAT);
		FontColor(COLOR_1);
		if(iso==YES) {
			DrawString(xt+10 , y,  "ISO");
		} else DrawString(xt+10 , y,  "JB");
		
		y+=new_line(1);
		
		FontColor(COLOR_3);
		xt=DrawFormatString(x1 , y, "%s :", STR_GAME_SIZE);
		FontColor(COLOR_1);
		DrawString(xt+10 , y, tot_size);
		
		y+=new_line(1);
		
		FontColor(COLOR_3);
		xt=DrawFormatString(x1 , y, "%s :", STR_FILES);
		FontColor(COLOR_1);
		DrawFormatString(xt+10 , y,  "%d", nb_file);
		
		y+=new_line(1);
		
		if(iso==NO) {
			FontColor(COLOR_3);
			xt=DrawFormatString(x1 , y, "%s :", STR_DIRS);
			FontColor(COLOR_1);
			DrawFormatString(xt+10 , y,  "%d", nb_directory);
			
			y+=new_line(1);
		}
		
		
		if(list_game_platform[position] == _JB_PS3 || list_game_platform[position] == _ISO_PS3) {
			FontColor(COLOR_3);
			xt=DrawFormatString(x1 , y, "%s :", STR_SYSVERS);
			FontColor(COLOR_1);
			DrawString(xt+10 , y, sys_vers);
			
			y+=new_line(1);
		}

		FontColor(COLOR_3);
		xt=DrawFormatString(x1 , y, "%s :", STR_GAMEID);
		FontColor(COLOR_1);
		DrawString(xt+10 , y, Game_id);
		
		y+=new_line(1);
		
		if(list_game_platform[position] == _ISO_PS2) {
		
			
			FontColor(COLOR_3);
			xt=DrawFormatString(x1 , y, "%s :", STR_ELFCRC);
			FontColor(COLOR_1);
			DrawString(xt+10 , y,  PS2CRC_STR);
			
			y+=new_line(1);
			
			if(strcmp(PS2CRC_STR, PS2ORICRC_STR) != 0) {
				FontColor(COLOR_3);
				xt=DrawFormatString(x1 , y, "%s :", STR_ELFCRCO);
				FontColor(COLOR_1);
				DrawString(xt+10 , y,  PS2ORICRC_STR);
				
				y+=new_line(1);
			}
			
		}
		
		x1=INPUT_X;
		y=INPUT_Y;
		FontColor(COLOR_1);
		SetFontZ(0);
		
		x1=DrawButton(x1, y, STR_BACK , BUTTON_CIRCLE);
		
		tiny3d_Flip();
		ScreenShot();
		
		ps3pad_read();
		
		if(new_pad & BUTTON_CIRCLE) {
			LoopBreak = 0;
			return;
		}
	}
	
	total_size=0;
	nb_file=0;
	nb_directory=0;
	
}

void dump_lv1(char *dump_path) 
{
	show_msg("TODO");
}

void dump_lv2(char *dump_path) 
{
	FILE* f=NULL;
	u64 i, data;
	char temp[128];
	
	int j=0;
	
	sprintf(temp, "%s_%d", dump_path, j);
	
	while(path_info(temp) != _NOT_EXIST) {
		j+=1;
		sprintf(temp, "%s_%d", dump_path, j);
	}
	
	f=fopen(temp, "wb");
	if(f==NULL) {
		print_load("Error : cannot dump %s", temp);
		return;
	} else
	
	prog_bar1_value = 0;
	
	for(i=0x8000000000000000ULL ; i < 0x8000000000800000ULL; i+=0x8) {
		data=lv2peek(i);
		fwrite(&data, sizeof(u64), 1, f);
		prog_bar1_value = (i*100)/0x800000;
		if(cancel==YES) break;
	}
	fclose(f);
	
	if(cancel==YES) {
		Delete(temp);
		cancel=NO;
	}

}

void dump_flash(char *dump_path)
{
	FILE* f;
	
	u32 source, read;
	u64 sector[0x40];
	int ret = -1;
	u64 i;
	u64 size_dump;
	
	char temp[255];
	int j=0;
	
	sprintf(temp, "%s_%d", dump_path, j);
	
	while(path_info(temp) != _NOT_EXIST) {
		j+=1;
		sprintf(temp, "%s_%d", dump_path, j);
	}
	
	ret = open_device( 0x100000000000004ull, &source );
	if( ret != 0 ) { 
		size_dump=0x77E00;
		close_device(source);
		open_device(0x100000000000001ull, &source);
	} 
	else {
		size_dump=0x8000 ;
	}
	
	prog_bar1_value = 0;
	
	f = fopen(temp, "wb");
	if(f==NULL) return;
	for(i=0x0; i < size_dump; i+=0x1) {
		read_device( source, i, 0x1, sector, &read, 0x22 );
		fwrite(sector, sizeof(sector), 1, f);
		prog_bar1_value = (i*100)/size_dump;
		if(cancel==YES) break;
	}
	fclose(f);
	close_device(source);
	
	if(cancel==YES) {
		Delete(temp);
		cancel=NO;
	}
}

u8 SetFilePerms(char *path)
{
	if(sysLv2FsChmod(path, FS_S_IFMT | 0777)==0 && sys_fs_chown(path, NO_UID, NO_GID)==0) return SUCCESS;
	
	return FAILED;
	
}

u8 SetPerms(char* path)
{
	if(is_ntfs(path)) return SUCCESS;
	
	u8 f_info = path_info(path);
	
	if(f_info == _FILE) return SetFilePerms(path);
	else if(f_info == _NOT_EXIST) return FAILED;
	
	sysLv2FsChmod(path, FS_S_IFDIR | 0777);
	sys_fs_chown(path, NO_UID, NO_GID);
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(path);
	if(d==NULL) {
		print_load("Error: Cannot open dir %s",  path);
		return FAILED;
	}
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
	
		char newpath[0x440];
		sprintf(newpath, "%s/%s", path, dir->d_name);
		
		if(cancel==YES) {
			cancel=NO;
			closedir(d);
			return FAILED;
		}
		
		if (dir->d_type & DT_DIR) {
			print_load("Dir = %s", dir->d_name);
			if(SetPerms(newpath) == FAILED) {
				closedir(d);
				return FAILED;
			}
		}
		else {
			print_load("File = %s", dir->d_name);
			SetFilePerms(newpath);
		}
	}
	closedir(d);
	
	return SUCCESS;
}

uint32_t reverse32(uint32_t val)
{
   return ((val>>24)&0x000000FF) | ((val>>8)&0x0000FF00) | ((val<<8)&0x00FF0000) | ((val<<24)&0xFF000000);
}

uint16_t reverse16(uint16_t val)
{
   return (((val>>8)&0x00FF) | ((val<<8)&0xFF00));
}

uint32_t convert32(char * bytes) {
	return (uint32_t) bytes[0] <<24 | (uint32_t) bytes[1]<<16 |  (uint32_t) bytes[2]<<8 | (uint32_t) bytes[3];
}

uint16_t convert16(char * bytes) {
	return (uint16_t) bytes[0]<<8 | (uint16_t) bytes[1];
}

FILE* openSFO(char *path, u32 *start_offset, u32 *size)
{
	FILE* sfo=NULL;
	
	u8 type = get_ext(path);
	
	if(type != _ISO_PS3 && type != _ISO_PSP && type != _JB_PS3 && type != _JB_PSP && type != _SFO) return NULL;
	
	if(type == _SFO) {
		sfo = fopen(path, "rb+");
		if(sfo==NULL) return NULL;
		
		fseek(sfo , 0 , SEEK_END);
		*size = ftell (sfo);
		fseek(sfo, 0, SEEK_SET);
		
		*start_offset=0;
		
		return sfo;
	} else 
	if(type == _ISO_PS3) {
		sfo = fopen(path, "rb+");
		if(sfo==NULL) return NULL;
		u64 file_offset=0;
		u8 ret=0;
		int file_size=0;
		
		ret = get_FileOffset(sfo, "/PS3_GAME/PARAM.SFO", &file_offset,  (u32 *) &file_size);
	
		if(file_offset==0 || file_size==0 || ret == FAILED) {fclose(sfo); return NULL;}
		
		*start_offset=file_offset;
		*size=file_size;
		
		return sfo;
	} else
	if(type == _ISO_PSP) {
		sfo = fopen(path, "rb+");
		if(sfo==NULL) return NULL;
		u64 file_offset=0;
		u8 ret=0;
		int file_size=0;
		
		ret = get_FileOffset(sfo, "/PSP_GAME/PARAM.SFO", &file_offset,  (u32 *) &file_size);
	
		if(file_offset==0 || file_size==0 || ret == FAILED) {fclose(sfo); return NULL;}
		
		*start_offset=file_offset;
		*size=file_size;
		
		return sfo;
	} else
	if(type== _JB_PS3) {
	
		char SFO_path[255];
		sprintf(SFO_path, "%s/PS3_GAME/PKGDIR/PARAM.SFO", path);
		if(path_info(SFO_path) == _NOT_EXIST) sprintf(SFO_path, "%s/PS3_GAME/PARAM.SFO", path);
		if(path_info(SFO_path) == _NOT_EXIST) return NULL;
		
		sfo = fopen(SFO_path, "rb+");
		if(sfo==NULL) return NULL;
		
		fseek(sfo , 0 , SEEK_END);
		*size = ftell (sfo);
		fseek(sfo, 0, SEEK_SET);
		
		*start_offset=0;
		
		return sfo;
	} else
	if(type == _JB_PSP) {
		char SFO_path[255];
		
		sprintf(SFO_path, "%s/PSP_GAME/PARAM.SFO", path);
				
		sfo = fopen(SFO_path, "rb+");
		if(sfo==NULL) return NULL;
		
		fseek(sfo , 0 , SEEK_END);
		*size = ftell (sfo);
		fseek(sfo, 0, SEEK_SET);
		
		*start_offset=0;
		
		return sfo;
	}
	
	return NULL;
}

u8 SetParamSFO(const char *name, char *value, int pos, char *path)
{	
	uint32_t key_start;
	uint32_t data_start;
	uint32_t key_name = 0;
	uint32_t data_name = 0;
	uint32_t maxlen_name = 0;
	
	uint32_t temp32 = 0;
	uint16_t temp16 = 0;
	int c, i;
	
	FILE* sfo=NULL;
	u32 sfo_start=0;
	u32 sfo_size=0;
	
	if(path == NULL) {
		sfo = openSFO(list_game_path[pos], &sfo_start, &sfo_size);
		if(sfo==NULL) return FAILED;
	}
	else {
		sfo = openSFO(path, &sfo_start, &sfo_size);
		if(sfo==NULL) return FAILED;
	}
	
	fseek(sfo, 0x8 + sfo_start, SEEK_SET); 
	fread(&key_start, sizeof(uint32_t), 1, sfo);
	fread(&data_start, sizeof(uint32_t), 1, sfo);
	key_start=reverse32(key_start);
	data_start=reverse32(data_start);
	fseek(sfo, key_start + sfo_start, SEEK_SET);

	do {
		c=fgetc(sfo);
		for(i=0; i <=strlen(name)-1 ; i++) {
			if(c == name[i]) {
				if (i==strlen(name)-1) {
					key_name = ftell(sfo) - strlen(name) - sfo_start;
					goto out;
				}
				c=fgetc(sfo);
			} else break;
		}
	} while (ftell(sfo) - sfo_start < sfo_size);
	
out:
	if(key_name==0) {fclose(sfo); return FAILED;}
	key_name -= key_start;
	fseek(sfo, 0x14 + sfo_start, SEEK_SET );
	
	while(temp16 < key_name) {
		fread(&temp16, sizeof(uint16_t), 1, sfo);
		temp16=reverse16(temp16);
		if(key_name == temp16) break;
		fseek(sfo, 0xE, SEEK_CUR);
	}
	if(temp16 > key_name) {fclose(sfo); return FAILED;}
	
	fseek(sfo, 0x2, SEEK_CUR);
	
	temp32 = reverse32(strlen(value)+1);
	if(strcmp(name, "ITEM_PRIORITY") == 0) temp32 = 0x04000000;
	fwrite(&temp32, sizeof(uint32_t), 1, sfo);
	
	fread(&temp32, sizeof(uint32_t), 1, sfo);
	maxlen_name = reverse32(temp32);

	fread(&temp32, sizeof(uint32_t), 1, sfo);
	temp32 = reverse32(temp32);
	data_name = data_start + temp32;
	
	fseek(sfo, data_name + sfo_start, SEEK_SET);
	
	if(strcmp(name, "ITEM_PRIORITY") == 0) {
		temp32 = 0;
		if(*(u8 *) value==1) temp32=0xFFFFFF7F;
		fwrite(&temp32, sizeof(u32), 1, sfo);
		fclose(sfo);
		return SUCCESS;
	}
	
	char *temp = (char *) malloc(maxlen_name);
	if(temp==NULL) {
		print_load("Error : Failed to malloc");
		fclose(sfo);
		return FAILED;
	}
	memset(temp, 0, maxlen_name);
	memcpy(temp, value, strlen(value));
	fwrite(temp, 1, maxlen_name, sfo);
	fclose(sfo);
	free(temp);
	
	return SUCCESS;
}

u8 GetParamSFO(const char *name, char *value, int pos, char *path)
{	
	FILE* sfo=NULL;
	u32 sfo_start=0;
	u32 sfo_size=0;

	if(path == NULL) {
		sfo = openSFO(list_game_path[pos], &sfo_start, &sfo_size);
		if(sfo==NULL) return FAILED;
	}
	else {
		sfo = openSFO(path, &sfo_start, &sfo_size);
		if(sfo==NULL) return FAILED;
	}
	
	uint32_t key_start;
	uint32_t data_start;
	uint32_t key_name = 0;
	uint32_t data_name = 0;
	uint32_t temp32 = 0;
	uint16_t temp16 = 0;
	int i, c;
	
	fseek(sfo, 0x8 + sfo_start, SEEK_SET);
	fread(&key_start, sizeof(uint32_t), 1, sfo);
	fread(&data_start, sizeof(uint32_t), 1, sfo);
	key_start=reverse32(key_start);
	data_start=reverse32(data_start);
	fseek(sfo, key_start + sfo_start, SEEK_SET);
	
	do {
		c=fgetc(sfo);
		for(i=0; i <=strlen(name)-1 ; i++) {
			if(c == name[i]) {
				if (i==strlen(name)-1) {
					key_name = ftell(sfo) - strlen(name) - sfo_start;
					goto out1;
				}
				c=fgetc(sfo);
			} else break;
		}
	} while (ftell(sfo) - sfo_start < sfo_size);
	{fclose(sfo); return FAILED;}
	out1:
	if(key_name==0) {fclose(sfo); return FAILED;}
	key_name -= key_start;
	fseek(sfo, 0x14 + sfo_start, SEEK_SET);
	
	while(temp16 < key_name) {
		fread(&temp16, sizeof(uint16_t), 1, sfo);
		temp16=reverse16(temp16);
		if(key_name == temp16) break;
		fseek(sfo, 0xE, SEEK_CUR);
	}
	
	if(temp16 > key_name)  {fclose(sfo);return FAILED;}
	fseek(sfo, 0xA, SEEK_CUR);
	fread(&temp32, sizeof(uint32_t), 1, sfo);
	temp32 = reverse32(temp32);
	data_name = data_start + temp32;
	fseek(sfo, data_name + sfo_start, SEEK_SET);
	fgets(value, 128, sfo);
	if(strstr(value, "\n") != NULL ) strtok(value, "\n");
	if(strstr(value, "\r") != NULL ) strtok(value, "\r");
	fclose(sfo);
	
	return SUCCESS;
}

FILE* openEBOOT(int pos, u32 *start_offset) 
{
	FILE* eboot=NULL;
	
	u8 type = list_game_platform[pos];
	if(type != _ISO_PS3 && type != _ISO_PSP && type != _JB_PS3)	type = get_ext(list_game_path[pos]);
	if(type != _ISO_PS3 && type != _ISO_PSP && type != _JB_PS3) return FAILED;
	
	if(type == _ISO_PS3) {
		eboot = fopen(list_game_path[pos], "rb+");
		if(eboot==NULL) return NULL;
		u64 file_offset=0;
		u8 ret=0;
		int file_size=0;
		ret = get_FileOffset(eboot, "/PS3_GAME/USRDIR/EBOOT.BIN", &file_offset, (u32 *) &file_size);
	
		if(file_offset==0 || file_size==0 || ret == FAILED) {fclose(eboot); return NULL;}
		
		*start_offset=file_offset;

		return eboot;
	} else
	if(type == _JB_PS3) {
		char EBOOT_path[255];
		sprintf(EBOOT_path, "%s/PS3_GAME/USRDIR/EBOOT.BIN", list_game_path[pos]);
		
		eboot = fopen(EBOOT_path, "rb+");
		if(eboot==NULL) return NULL;
		
		*start_offset=0;
		
		return eboot;
	}
	
	return NULL;
}

u8 patch_EBOOT(int position)
{
	FILE* eboot=NULL;
	u32 fw_in_eboot;
	u32 start_offset=0;
	//u32 cur_fw = (u32) (c_firmware*10000);
	
	eboot = openEBOOT(position, &start_offset);
	if(eboot==NULL) return FAILED;
	
	fseek(eboot, 0x40C+start_offset, SEEK_SET);
	fread(&fw_in_eboot, sizeof(u32), 1, eboot);
	
	if(fw_in_eboot > 99900) {
		fseek(eboot, 0x42C+start_offset, SEEK_SET);
		fread(&fw_in_eboot, sizeof(u32), 1, eboot);
		if(fw_in_eboot > 99900) return FAILED;
		fseek(eboot, 0x42C+start_offset, SEEK_SET);
	} else fseek(eboot, 0x40C+start_offset, SEEK_SET);
	
	//if(cur_fw >= fw_in_eboot) return SUCCESS; //useless to patch it.
	
	u32 firmware_421 = 42100;
	fwrite(&firmware_421, sizeof(u32), 1, eboot);
	
	fclose(eboot);
	
	if(SetParamSFO("PS3_SYSTEM_VER", "04.2100", position, NULL) == FAILED) return FAILED;
	
	return SUCCESS;
}

//====================================|
// DigiCert High Assurance EV Root CA |
//====================================|
static char github_cert[] __attribute__((aligned(64))) =
	"-----BEGIN CERTIFICATE-----\n"
	"MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBs\n"
	"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
	"d3cuZGlnaWNlcnQuY29tMSswKQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5j\n"
	"ZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAwMFoXDTMxMTExMDAwMDAwMFowbDEL\n"
	"MAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZMBcGA1UECxMQd3d3\n"
	"LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFuY2Ug\n"
	"RVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm\n"
	"+9S75S0tMqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTW\n"
	"PNt0OKRKzE0lgvdKpVMSOO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEM\n"
	"xChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFB\n"
	"Ik5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQNAQTXKFx01p8VdteZOE3\n"
	"hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUeh10aUAsg\n"
	"EsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQF\n"
	"MAMBAf8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaA\n"
	"FLE+w2kD+L9HAdSYJhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3Nec\n"
	"nzyIZgYIVyHbIUf4KmeqvxgydkAQV8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6z\n"
	"eM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFpmyPInngiK3BD41VHMWEZ71jF\n"
	"hS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkKmNEVX58Svnw2\n"
	"Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe\n"
	"vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep\n"
	"+OkuE6N36B9K\n"
	"-----END CERTIFICATE-----\n";
	
static char getBuffer[1024];

int download(char *url, char *dst)
{
	int ret = 0, httpCode = 0;
	s32 cert_size=0;
	httpUri uri;
	httpClientId httpClient = 0;
	httpTransId httpTrans = 0;
	FILE* fp=NULL;
	s32 nRecv = -1;
	s32 size = 0;
	u64 dl=0;
	uint64_t length = 0;
	void *http_pool = NULL;
	void *uri_pool = NULL;
	void *ssl_pool = NULL;
	void *cert_buffer = NULL;
	httpsData *caList=NULL;
	
	u8 module_https_loaded=NO;
	u8 module_http_loaded=NO;
	u8 module_net_loaded=NO;
	u8 module_ssl_loaded=NO;
	
	u8 https_init=NO;
	u8 http_init=NO;
	u8 net_init=NO;
	u8 ssl_init=NO;

	//init
	ret = sysModuleLoad(SYSMODULE_NET);
	if (ret < 0) {
		print_load("Error : sysModuleLoad(SYSMODULE_NET) failed (%x)", ret);
		ret=FAILED;
		goto end;
	} else module_net_loaded=YES;

	ret = netInitialize();
	if (ret < 0) {
		print_load("Error : netInitialize failed (%x)", ret);
		ret=FAILED;
		goto end;
	} else net_init=YES;

	ret = sysModuleLoad(SYSMODULE_HTTP);
	if (ret < 0) {
		print_load("Error : sysModuleLoad(SYSMODULE_HTTP) failed (%x)", ret);
		ret=FAILED;
		goto end;
	} else module_http_loaded=YES;

	http_pool = malloc(0x10000);
	if (http_pool == NULL) {
		print_load("Error : out of memory (http_pool)");
		ret=FAILED;
		goto end;
	}

	ret = httpInit(http_pool, 0x10000);
	if (ret < 0) {
		print_load("Error : httpInit failed (%x)", ret);
		ret=FAILED;
		goto end;
	} else http_init=YES;

	// init SSL
	if(strstr(url, "https")) {
		ret = sysModuleLoad(SYSMODULE_HTTPS);
		if (ret < 0) {
			print_load("Error : sysModuleLoad(SYSMODULE_HTTP) failed (%x)", ret);
			ret=FAILED;
			goto end;
		} else module_https_loaded=YES;

		ret = sysModuleLoad(SYSMODULE_SSL);
		if (ret < 0) {
			print_load("Error : sysModuleLoad(SYSMODULE_HTTP) failed (%x)", ret);
			ret=FAILED;
			goto end;
		} else module_ssl_loaded=YES;

		ssl_pool = malloc(0x40000);
		if (ret < 0) {
			print_load("Error : out of memory (http_pool)");
			ret=FAILED;
			goto end;
		}

		ret = sslInit(ssl_pool, 0x40000);
		if (ret < 0) {
			print_load("Error : sslInit failed (%x)", ret);
			ret=FAILED;
			goto end;
		} else ssl_init=YES;

		caList = (httpsData *)malloc(sizeof(httpsData));
		ret = sslCertificateLoader(SSL_LOAD_CERT_ALL, NULL, 0, &cert_size);
		if (ret < 0) {
			print_load("Error : sslCertificateLoader failed (%x)", ret);
			ret=FAILED;
			goto end;
		}

		cert_buffer = malloc(cert_size);
		if (cert_buffer==NULL) {
			print_load("Error : out of memory (cert_buffer)");
			ret=FAILED;
			goto end;
		}

		ret = sslCertificateLoader(SSL_LOAD_CERT_ALL, cert_buffer, cert_size, NULL);
		if (ret < 0) {
			print_load("Error : sslCertificateLoader failed (%x)", ret);
			ret=FAILED;
			goto end;
		}

		(&caList[0])->ptr = cert_buffer;
		(&caList[0])->size = cert_size;
		
		(&caList[1])->ptr = github_cert;
		(&caList[1])->size = sizeof(github_cert);

		ret = httpsInit(2, (httpsData *) caList);
		if (ret < 0) {
			print_load("Error : httpsInit failed (%x)", ret);
			ret=FAILED;
			goto end;
		} else https_init=YES;

	}
	// END of SSL
	httpClient = 0;
	httpTrans = 0;
 
	ret = httpCreateClient(&httpClient);
	if (ret < 0) {
		print_load("Error : httpCreateClient failed (%x)", ret);
		ret=FAILED;
		goto end;
	}
	// End of init

	//URI
	ret = httpUtilParseUri(&uri, url, NULL, 0, &size);
	if (ret < 0) {
		print_load("Error : httpUtilParseUri() failed (%x)", ret);
		ret=FAILED;
		goto end;
	}

	uri_pool = malloc(size);
	if (uri_pool == NULL) {
		print_load("Error : out of memory (uri_pool)");
		ret=FAILED;
		goto end;
	}

	ret = httpUtilParseUri(&uri, url, uri_pool, size, 0);
	if (ret < 0) {
		print_load("Error : httpUtilParseUri() failed (%x)", ret);
		ret=FAILED;
		goto end;
	}
	//END of URI	

	//SEND REQUEST
	ret = httpCreateTransaction(&httpTrans, httpClient, HTTP_METHOD_GET, &uri);
	if (ret < 0) {
		print_load("Error : httpCreateTransaction() failed (%x)", ret);
		ret=FAILED;
		goto end;
	}
	/*
	if(strstr(url, "gamecovers.ezyro.com") != NULL) {
		httpHeader headerCookie = { (const char*) "Cookie", (const char*) "__test=8f82a74fa6f891b017602f64b6aa7942" };
		httpRequestAddHeader(httpTrans, &headerCookie);
	}
	*/
	ret = httpSendRequest(httpTrans, NULL, 0, NULL);
	if (ret < 0) {
		print_load("Error : httpSendRequest() failed (%x)", ret);
		ret=FAILED;
		goto end;
	}
	
	//GET SIZE
	httpResponseGetContentLength(httpTrans, &length);

	ret = httpResponseGetStatusCode(httpTrans, &httpCode);
	if (ret < 0) {
		print_load("Error : cellHttpResponseGetStatusCode() failed (%x)", ret);
		ret=FAILED;
		goto end;
	}

	if(httpCode != HTTP_STATUS_CODE_OK && httpCode >= 400 ) {
		//print_load("Error : Status code (%d)", httpCode);
		ret=FAILED;
		goto end;
	}
	
//TRANSFERT
	fp=NULL;
	fp = fopen(dst, "wb");
	if(fp == NULL) {
		print_load("Error : fopen() failed : %s", dst);
		ret=FAILED;
		goto end;
	}
	
	if(length != 0) {
		if(prog_bar1_value!=-1) prog_bar2_value=0;
		else prog_bar1_value=0;
	}
	
	while(nRecv != 0) {
		if(httpRecvResponse(httpTrans, (void*) getBuffer, sizeof(getBuffer)-1, &nRecv) > 0) break;
		if(nRecv == 0)	break;
		fwrite((char*) getBuffer, nRecv, 1, fp);
		if(cancel==YES) break;
		dl+=nRecv;
		if(length != 0) {
			if(prog_bar2_value!=-1) prog_bar2_value=(dl*100)/length;
			else prog_bar1_value = (dl*100)/length;
		}
	}
	fclose(fp);
	
	if(cancel==YES) {
		Delete(dst);
		ret=FAILED;
		cancel=NO;
	}
	
	if(prog_bar2_value!=-1) prog_bar2_value=-1;
	else prog_bar1_value=-1;
	
//END of TRANSFERT

	ret=SUCCESS;
	
end:
	if(caList) free(caList);
	if(httpTrans) httpDestroyTransaction(httpTrans);
	if(httpClient) httpDestroyClient(httpClient);
	if(https_init) httpsEnd();
	if(ssl_init) sslEnd();
	if(http_init) httpEnd();
	if(net_init) netDeinitialize();
	
	if(module_http_loaded) sysModuleUnload(SYSMODULE_HTTP);
	if(module_https_loaded) sysModuleUnload(SYSMODULE_HTTPS);
	if(module_net_loaded) sysModuleUnload(SYSMODULE_NET);
	if(module_ssl_loaded) sysModuleUnload(SYSMODULE_SSL);
	
	if(uri_pool) free(uri_pool);
	if(http_pool) free(http_pool);
	if(ssl_pool) free(ssl_pool);
	if(cert_buffer) free(cert_buffer);
	
	return ret;
}

typedef struct
{
	float pkgVers;
	u64 size;
	char url[255];
	float sysVers;
} update_data;

void get_game_update(int position)
{
	
	start_loading();
	
	int shutdown=NO;
	char url[128];
	char dst[128];
	char title_id[10];
	int file_size=0;
	int n=0;
	int k=0;
	int nPKG = -1;
	char *xml;
	int d_position=0;
	char *size_str[512];
	
	if(GetParamSFO("TITLE_ID", title_id, position, NULL)==FAILED) {
		print_load("Error: Get title_id failed");
		goto screen;
	}
	
	sprintf(url, "https://a0.ww.np.dl.playstation.net/tpl/np/%s/%s-ver.xml", title_id, title_id);
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/sys/%s.xml", ManaGunZ_id, title_id);

	if(download(url, dst)==FAILED) {
		print_load("Error: Download xml failed");
		goto screen;
	}
	
	if(path_info(dst)==_NOT_EXIST) goto screen; //0 update, status code = 0
	
	xml = LoadFile(dst, &file_size);
	
	Delete(dst);
	if(file_size==0) {
		print_load("Error: Load xml failed");
		goto screen;
	}
	
	update_data data[512];
	
	print_load("Search Flags");
	for(n=0 ; n<file_size; n++) {
		if(strncmp(&xml[n], "package version", 15)==0) {
			nPKG++;
			sscanf(&xml[n+17], "%f", &data[nPKG].pkgVers);
		}
		if(strncmp(&xml[n], "size", 4)==0) {
			sscanf(&xml[n+6], "%lld", (long long int *) &data[nPKG].size);
		}
		if(strncmp(&xml[n], "url", 3)==0) {
			k=n+5;
		}
		if(strncmp(&xml[n], ".pkg", 4)==0) {
			memcpy(data[nPKG].url, &xml[k], n+4-k);
		}
		if(strncmp(&xml[n], "ps3_system_ver", 14)==0) {
			sscanf(&xml[n+16], "%f", &data[nPKG].sysVers);
		}
	}
	
	for(n=0 ; n<=nPKG; n++) {
		size_str[n] = get_unit(data[n].size);
	}
	
screen:

	end_loading();
	
	u8 LoopBreak=1;
	while(LoopBreak)
	{
		cls();
		ps3pad_read();
		
		Draw_BGS();
		Draw_Notification();
		
		int x=50, y=40, xt;
		
		FontSize(20);
		FontColor(COLOR_3);
		
		Draw_Box(x, y+5, 0, 0, 10, 10, COLOR_3, NO);
		
		xt=DrawString(x+15, y, list_game_title[position]);
		y+=new_line(1);
		Draw_Box(x, y, 0, 0, xt-x, 2, COLOR_3, NO);
		
		y+=new_line(2);

		FontColor(COLOR_4);
		
		DrawFormatString(x, y, "%s = %d", STR_UPDATE_FOUND, nPKG+1);
		
		y+=new_line(2);
		
		for(n=0 ; n<=nPKG; n++) {
			if(n==d_position) FontColor(COLOR_2); else FontColor(COLOR_1);
			DrawFormatString(x, y, "%s: %1.2f  -  %s: %s  - %s: %1.2f", STR_UPDATE, data[n].pkgVers, STR_SIZE, size_str[n], STR_SYSTEM, data[n].sysVers);
			y+=new_line(1);
		}
		
		x=INPUT_X;
		y=INPUT_Y;
		FontColor(COLOR_1);
		SetFontZ(0);
	
		x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
		
		if(nPKG!=-1)  {
			x=DrawButton(x, y, STR_DL, BUTTON_CROSS);
		} 
		if(nPKG>0) {
			x=DrawButton(x, y, STR_DL_ALL, BUTTON_SQUARE);
		}
		if(nPKG!=-1)  {
			if(shutdown==YES) {
				x=DrawButton(x, y, STR_TURNOFF_YES, BUTTON_SELECT);
			} else {
				x=DrawButton(x, y, STR_TURNOFF_NO, BUTTON_SELECT);
			}
		}
		
		tiny3d_Flip();
		ScreenShot();
		
		if(new_pad & BUTTON_SELECT && nPKG!=-1) {
			if(shutdown==YES) shutdown=NO; else shutdown=YES;
		}
		if(new_pad & BUTTON_UP) {
			if(d_position>0) d_position--;
		}
		if(new_pad & BUTTON_DOWN) {
			if(d_position<nPKG) d_position++;
		}
		if(new_pad & BUTTON_CIRCLE) {
			LoopBreak=0;
			return;
		}
		if(new_pad & BUTTON_CROSS && nPKG!=-1) { 
			sprintf(dst, "/dev_hdd0/packages%s", strrchr(data[d_position].url, '/'));
			if(path_info(dst) == _FILE) show_msg(STR_DONE);
			else {
				start_loading();
				if(download(data[d_position].url, dst) == SUCCESS) show_msg(STR_DONE); 
				else show_msg(STR_FAILED);
				end_loading();
				if(shutdown==YES) {
					Delete("/dev_hdd0/tmp/turnoff");
					lv2syscall4(379,0x1100,0,0,0);
				}
			}
		}
		if(new_pad & BUTTON_SQUARE && nPKG>0) {
			start_loading();
			for(n=0; n<=nPKG; n++) {
				sprintf(dst, "/dev_hdd0/packages%s", strrchr(data[n].url, '/'));
				if(path_info(dst) == _FILE) continue;
				if(download(data[n].url, dst) == SUCCESS)  show_msg(STR_DONE); 
				else show_msg(STR_FAILED);
			}
			end_loading();
			if(shutdown==YES) {
				Delete("/dev_hdd0/tmp/turnoff");
				lv2syscall4(379,0x1100,0,0,0);
			}
		}
	}
	
}

int read_scan_dir() 
{

	FILE* fp=NULL;
	char scanPath[128];
	char temp[128];
	
	scan_dir_number=-1;
	
	sprintf(scanPath, "/dev_hdd0/game/%s/USRDIR/setting/scan_dir.txt", ManaGunZ_id);
	
	fp=fopen(scanPath, "rb");
	if(fp==NULL){
		print_load("Error : failed to open SCAN_DIR.");
		return FAILED;
	}
	while(fgets(temp, 128, fp) != NULL) {
		//print_load("fgets %s", temp);
		if(strstr(temp, "\n") != NULL ) strtok(temp, "\n");
		if(strstr(temp, "\r") != NULL ) strtok(temp, "\r");
		scan_dir_number++;
		strcpy(scan_dir[scan_dir_number], temp);
		
	}
	
	fclose(fp);
	
	if(scan_dir_number != -1) return SUCCESS; else return FAILED;

}

void write_scan_dir()
{
	FILE* fp=NULL;
	char scanPath[128];
	int i;
	
	sprintf(scanPath, "/dev_hdd0/game/%s/USRDIR/setting/scan_dir.txt", ManaGunZ_id);
	
	fp=fopen(scanPath, "wb");
	if(fp==NULL)return;
	
	for(i=0; i<=scan_dir_number; i++) {
		fputs(scan_dir[i], fp);
		fputs("\n", fp);
	}
	fclose(fp);
	
}

//*******************************************************
// DEVICE
//*******************************************************

void getDevices()
{
	MountNTFS();
	
	print_load("Get devices");

	char temp[128];
	
	device_number=-1;
	
	int r, i;
	for(i = 0; i < 8 ; i++) {
		r = -1;
		sprintf(temp, "ntfs%c", 48+i);
		r = NTFS_Test_Device(temp);
		if(r>=0) {
			device_number++;
			sprintf(list_device[device_number], "ntfs%c:", 48+i);
		}
	}
	
	DIR *d;
	struct dirent *dir;
	d = opendir("/");		
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		if(	strstr(dir->d_name, "dev_usb")
		||  strstr(dir->d_name, "dev_hdd0")
		||  strstr(dir->d_name, "dev_sd")
		||  strstr(dir->d_name, "dev_ms")
		||  strstr(dir->d_name, "dev_cd")
		  ) 
		{
			device_number++;
			strcpy(list_device[device_number], dir->d_name);
		}
	}
	closedir(d);

}

static sys_ppu_thread_t check_device_id;

void check_device_thread(void *unused)
{
	int i;
	u8 device_number_OLD = 0;
	
	for(i=0; i<8; i++) {
		if( PS3_NTFS_IsInserted(i) == true ) {
			device_number_OLD++;
		}
	}
	
	while(checking == YES) {
	
		u8 device_number_NEW = 0;
		
		for(i=0; i<8; i++) {
			if( PS3_NTFS_IsInserted(i) == true ) {
				device_number_NEW++;
			}
		}
		device_plug = device_number_NEW - device_number_OLD;
		sleep(1);
		if(device_plug != 0) {
			checking=NO;
			break;
		}
	}

	sysThreadExit(0);
}

void start_checking()
{
	checking = YES;
	sysThreadCreate(&check_device_id, check_device_thread, NULL, 999, 0x2000, THREAD_JOINABLE, "check");
}

void end_checking()
{
	u64 ret;
	checking = NO;
	sysThreadJoin(check_device_id, &ret);
}

int move_bdemubackup_to_origin(char *device_path);

void check_device()
{
	if(device_plug != 0) {

		int i=0, j=0, k;
		char scan_path[128], temp[128];
		
		end_checking();
		
		start_loading();
		
		char list_device_OLD[20][20]={{0}};
		int8_t device_number_OLD=-1;
		
		memcpy(list_device_OLD, list_device, sizeof(list_device));
		device_number_OLD = device_number;
		
		getDevices();
		
		if(device_number < device_number_OLD) {  // *** unplug device ***
			for(k=0; k < device_number_OLD - device_number ; k++) {
				char path_unplug[20];
				for(i=0; i<=device_number_OLD; i++) {
					for(j=0;j<=device_number;j++) {
						if(strcmp(list_device[j], list_device_OLD[i]) == 0) break;
						if(j==device_number) strcpy(path_unplug, list_device_OLD[i]);
					}
				}
				
				print_load("%s unplugged", path_unplug);
				
				if(strncmp(path_unplug, "dev_", 4)==0) {
					char mount_point[20];
					sprintf(mount_point, "/%s", path_unplug);
					sysFsAioFinish(mount_point);
				} 
				
				s64 old_game_number = game_number;
				
				for(i=0; i<=game_number; i++) {
					
					if(strstr(list_game_path[i], path_unplug) == NULL) {
						remove_GAMELIST(i);
						i--;
					}
				}
				
				if(game_number == old_game_number) {
					device_plug = 0;
					start_checking();
					end_loading();
					return;
				}
			}
		} 
		else if(device_number > device_number_OLD) { // *** plug device ***
			for(k=0; k < device_number - device_number_OLD ; k++) {
				
				char path_plug[20];
				for(i=0;i<=device_number; i++) {
					for(j=0;j<=device_number_OLD;j++) {
						if(strcmp(list_device_OLD[j], list_device[i])==0) break;
						if(j==device_number_OLD) strcpy(path_plug, list_device[i]);
					}
				}
				
				print_load("%s plugged", path_plug);
				
				if(strncmp(path_plug, "dev_", 4)==0) {
					char mount_point[20];
					sprintf(mount_point, "/%s", path_plug);
					if(sysFsAioInit(mount_point) != 0)
						print_load("Warning :  failed to sysFsAioInit(%s)", mount_point);
					
				} 
				
				s64 old_game_number = game_number;
							
				print_load( "Get directories names from scan_dir.txt");
				//get scan dir
				if(read_scan_dir()==FAILED) {
					device_plug = 0;
					start_checking();
					end_loading();
					return;
				}
				
				sprintf(temp, "/%s", path_plug);
				move_bdemubackup_to_origin(temp);
				
				//get game list
				for(j=0; j<=scan_dir_number; j++) {
					sprintf(scan_path, "/%s/%s", path_plug, scan_dir[j]);
										
					get_GAMELIST(scan_path);
				}
				
				if(game_number == old_game_number) {
					device_plug = 0;
					start_checking();
					end_loading();
					return;
				}
				
				sort_GAMELIST();
			}
		}
		
		print_load("Reloading...");

		device_plug = 0;
		
		GetThemes();
		
		read_fav();
		
		start_Load_GamePIC();
		
		start_checking();
		end_loading();

	} 
	else if(checking==NO) start_checking();
}

//*******************************************************
// MD5 from redump.org to check PS1 and PS2
//*******************************************************

u8 Download_MD5(char *gameID)
{
	char url[255];
	char dst[255];
	char redumpID[20];
	
	strcpy(redumpID, gameID);
	redumpID[4]='-';
	redumpID[8]=redumpID[9];
	redumpID[9]=redumpID[10];
	redumpID[10]=0;
	
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/sys/Check", ManaGunZ_id);
	mkdir(dst, 0777);
	
	// it's better to http_set_autoredirect=false and then get header.value of "Location" header...
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/sys/Check/temp.txt", ManaGunZ_id);
	sprintf(url, "http://redump.org/discs/quicksearch/%s/", redumpID);
	
	if( download(url, dst) == FAILED) {
		print_load("Error : failed to download result");
		Delete(dst);
		return FAILED;
	}

	int size;
	char *buff = LoadFile(dst, &size);
	
	Delete(dst);
	
	if(buff==NULL) {
		print_load("Error : failed to load result");
		return FAILED;
	}
	
	char pageID[10];
	if(strstr(buff, "/disc/") == NULL) {
		print_load("Error : md5 not found");
		free(buff);
		return FAILED;
	}
	memcpy(pageID, strstr(buff, "/disc/") + 6, 9);
	strtok(pageID, "/");
	free(buff);
	
	sprintf(url, "http://redump.org/disc/%s/md5/", pageID);
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/sys/Check/%s.md5", ManaGunZ_id, gameID);

	if( download(url, dst) == FAILED) {
		print_load("Error : failed to download md5");
		Delete(dst);
		return FAILED;
	}

	return SUCCESS;
}

u8 CheckMD5(char *path)
{
	char MD5_redump[255];
	long long unsigned int MD5_local[2];
	char MD5_local_STR[33];
	char gameID[20];
	char MD5_DB[128];
	char MD5_FILE[25];
	
	print_head("Checking MD5...");
	
	u8 platform = get_ext(path);
	
	if(platform != _ISO_PS2 && platform != _ISO_PS1) {
		print_load("Error : this platform isn't supported");
		return FAILED;
	}
	
	if( Get_ID(path, platform, gameID) == FAILED ) {
		print_load("Error : failed to get game ID");
		return FAILED;
	}
	
	sprintf(MD5_redump, "/dev_hdd0/game/%s/USRDIR/sys/Check/%s.md5", ManaGunZ_id, gameID);
	sprintf(MD5_DB, "/dev_hdd0/game/%s/USRDIR/sys/Check.zip", ManaGunZ_id);
	sprintf(MD5_FILE, "%s.md5", gameID);
	
	ExtractZipFile(MD5_DB, MD5_FILE, MD5_redump);
	
	if( path_info(MD5_redump) == _NOT_EXIST )
	if( Download_MD5(gameID) == FAILED ) return FAILED;
	
	if ( md5_file(path, (u8 *) MD5_local) == FAILED ) {
		print_load("Error : failed to get MD5");
		return FAILED;
	}
	if(cancel == YES) return FAILED;
	
	sprintf(MD5_local_STR, "%016llX%016llX", MD5_local[0], MD5_local[1]);
	
	int size;
	char *MD5_buff =  LoadFile(MD5_redump, &size);
	if(MD5_buff == NULL) {
		print_load("Error : failed to load MD5 redump");
		return FAILED;
	}
	
	char dst[255];
	strcpy(dst, path);
	dst[strlen(dst)-4]=0;
	strcat(dst, "_CHECK.md5");
	
	FILE* f;
	
	f = fopen(dst, "wb");
	if(f == NULL) {
		print_load("Error : cannot create CHECK.md5");
		free(MD5_buff);
		return FAILED;
	}
	
	fputs("*** MD5 from redump.org ***\n\n", f);
	fputs(MD5_buff, f);
	fputs("\n\n*** real MD5 ***\n\n", f);
	fputs(MD5_local_STR, f);
	fputs(" ", f);
	fputs(&strrchr(path, '/')[1], f);
	
	fputs("\n\n*** RESULT ***\n\n", f);
	
	if(strcasestr(MD5_buff, MD5_local_STR) != NULL) {
		fputs("VALID", f);
	} else fputs("NOT VALID", f);
	
	fclose(f);
	
	free(MD5_buff);
	
	return SUCCESS;
	
}

u32 GetRenaCRC32(char *path)
{
	char game_ID[20];
	char link[128];
	u32 renaCRC = 0;
	
	if( Get_ID(path, _ISO_PSP, game_ID) == FAILED) return 0;
	
	sprintf(link, "http://renascene.com/?target=search1&srchser=1&srch=%s", game_ID);
	Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
	if(download(link, "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp")==SUCCESS) {
		char *data;
		int file_size;
		char tmp[255];
		data = LoadFile("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp", &file_size);
		Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
		char *pch = strstr(data, "http://renascene.com/info/umd/");
		if(pch != NULL) {
			strncpy(tmp, pch, 40);
			if( strstr(tmp, "'") != NULL) strtok(tmp, "'");
			if(download(tmp, "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp")==SUCCESS) {
				free(data);
				data = LoadFile("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp", &file_size);
				Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
				char *pch2 = strstr(data, "CRC32</td><td class=\"infRightTd\">");
				if(pch2 != NULL) {
					strncpy(tmp, pch2+33, 255);
					if( strstr(tmp, "<") != NULL) strtok(tmp, "<");
					sscanf(tmp, "%X", &renaCRC);
					return renaCRC;
				}
			}
		}
		free(data);
	}
	
	return 0;
}

u32 GetPSPCRC32(char *path)
{
	char game_ID[20];
	unsigned int CRC = 0;
	char CRC_DB[128];
	
	if( Get_ID(path, _ISO_PSP, game_ID) == FAILED) return 0;
	
	sprintf(CRC_DB, "/dev_hdd0/game/%s/USRDIR/sys/PSP_CRC.txt", ManaGunZ_id);
	
	FILE* f;
	
	f = fopen(CRC_DB, "r");
	if(f==NULL) return 0;
	
	char line[128];
	
	while(fgets(line, 128, f) != NULL) {
		if(strstr(line, game_ID) != NULL) {
			sscanf(line, "%*s %X", &CRC);
			break;
		}
	}
	
	fclose(f);
	
	return (u32) CRC;

}

u8 CheckCRC32(char *path)
{
	u32 renaCRC = 0;
	
	renaCRC = GetPSPCRC32(path);
	
	if(renaCRC == 0) renaCRC = GetRenaCRC32(path);
	
	if(renaCRC == 0) return FAILED;
	
	print_load("CRC from renascene : %X", renaCRC);
	
	print_head("Getting CRC32");
	
    FILE* f;
    size_t n;
	
    unsigned char buf[1024];
	uint64_t read=0;
	uint64_t file_size;
	f = fopen(path, "rb");
    if(f==NULL) return FAILED;

	prog_bar1_value=0;
	
	fseek (f , 0 , SEEK_END);
	file_size = ftell (f);
	fseek(f, 0, SEEK_SET);
	
	u32 crc = crc32(0L, Z_NULL, 0);
	
    while( ( n = fread( buf, 1, sizeof( buf ), f ) ) > 0 ) {
		read+=n;
		prog_bar1_value=(read*100)/file_size;
		
		crc = crc32(crc, (const unsigned char*) buf, n);
		
		if(cancel==YES) break;
	}
	
	prog_bar1_value=-1;

    fclose( f );
	
	char dst[255];
	strcpy(dst, path);
	dst[strlen(dst)-4]=0;
	strcat(dst, "_CHECK.crc");
	
	char renaPS2CRC_STR[10];
	sprintf(renaPS2CRC_STR, "%X", renaCRC);
	char realPS2CRC_STR[10];
	sprintf(realPS2CRC_STR, "%X", crc);
	
	f = fopen(dst, "wb");
	if(f == NULL) {
		print_load("Error : cannot create CHECK.crc");
		return FAILED;
	}
	
	fputs("*** CRC from renascene.com ***\n\n", f);
	fputs(renaPS2CRC_STR, f);
	fputs("\n\n*** real CRC ***\n\n", f);
	fputs(realPS2CRC_STR, f);
	fputs(" ", f);
	fputs(&strrchr(path, '/')[1], f);
	
	fputs("\n\n*** RESULT ***\n\n", f);
	
	if(crc == renaCRC) fputs("VALID", f);
	else fputs("NOT VALID", f);
	
	fclose(f);
	
	return SUCCESS;
}

//*******************************************************
// PS2 emu
//*******************************************************

uint8_t PS2emu_is_patched()
{
	struct stat s;
	if(stat("/dev_flash/ps2emu/ps2gxemu_stage2.bin", &s) == 0)
	if(stat("/dev_flash/ps2emu/ps2hwemu_stage2.bin", &s) == 0)	return YES;
	return NO;
}

uint8_t patch_PS2()
{	

	if( PS2emu_is_patched() == YES ) return SUCCESS;
	
	uint8_t *ps2gxemu_stage1;
	uint32_t ps2gxemu_stage1_size;
	uint8_t *ps2gxemu_stage2;
	uint32_t ps2gxemu_stage2_size;
	
	uint8_t *ps2hwemu_stage1;
	uint32_t ps2hwemu_stage1_size;
	uint8_t *ps2hwemu_stage2;
	uint32_t ps2hwemu_stage2_size;
	
	uint8_t *ps2netemu_stage2;
	uint32_t ps2netemu_stage2_size;
	
	uint64_t value;
	FILE* f;
	
	char tmp_dir[128];
	char tmp_hw[128];
	char tmp_gx[128];
	char tmp_net[128];
	
	sprintf(tmp_dir, "/dev_hdd0/game/%s/USRDIR/temp", ManaGunZ_id);
	sprintf(tmp_hw, "/dev_hdd0/game/%s/USRDIR/temp/ps2_emu.self", ManaGunZ_id);
	sprintf(tmp_gx, "/dev_hdd0/game/%s/USRDIR/temp/ps2_gxemu.self", ManaGunZ_id);
	sprintf(tmp_net, "/dev_hdd0/game/%s/USRDIR/temp/ps2_netemu.self", ManaGunZ_id);
	
	Delete(tmp_dir);
	mkdir(tmp_dir, 0777);
	
	f = fopen("/dev_flash/ps2emu/ps2_gxemu.self", "rb");
	if(f==NULL) return FAILED;
	fseek(f, 0xF8, SEEK_SET);
	fread(&value, 8, 1, f);
	fclose(f);
	
	if(value == 0x2BB8028) { // 421+
		ps2gxemu_stage1_size = (uint32_t) ps2gxemu_stage1_421_bin_size;
		ps2gxemu_stage1 = (uint8_t *) ps2gxemu_stage1_421_bin;
		ps2gxemu_stage2_size = (uint32_t) ps2gxemu_stage2_421_bin_size;
		ps2gxemu_stage2 = (uint8_t *) ps2gxemu_stage2_421_bin;
	} else
	if(value == 0x2BB8A28) { // 430+
		ps2gxemu_stage1_size = (uint32_t) ps2gxemu_stage1_430_bin_size;
		ps2gxemu_stage1 = (uint8_t *) ps2gxemu_stage1_430_bin;
		ps2gxemu_stage2_size = (uint32_t) ps2gxemu_stage2_430_bin_size;
		ps2gxemu_stage2 = (uint8_t *) ps2gxemu_stage2_430_bin;
	} else
	if(value == 0x2BB8C28) { // 440+
		ps2gxemu_stage1_size = (uint32_t) ps2gxemu_stage1_440_bin_size;
		ps2gxemu_stage1 = (uint8_t *) ps2gxemu_stage1_440_bin;
		ps2gxemu_stage2_size = (uint32_t) ps2gxemu_stage2_440_bin_size;
		ps2gxemu_stage2 = (uint8_t *) ps2gxemu_stage2_440_bin;
	} else
	if(value == 0x2BBAB28) { // 453+
		ps2gxemu_stage1_size = (uint32_t) ps2gxemu_stage1_453_bin_size;
		ps2gxemu_stage1 = (uint8_t *) ps2gxemu_stage1_453_bin;
		ps2gxemu_stage2_size = (uint32_t) ps2gxemu_stage2_453_bin_size;
		ps2gxemu_stage2 = (uint8_t *) ps2gxemu_stage2_453_bin;
	} else return FAILED;
	
	if ( ps2gen("/dev_flash/ps2emu/ps2_gxemu.self", tmp_gx, ps2gxemu_stage1, ps2gxemu_stage1_size) == FAILED) {
		return FAILED;
	}
	
	f = fopen("/dev_flash/ps2emu/ps2_emu.self", "rb");
	if(f==NULL) return FAILED;
	fseek(f, 0xF8, SEEK_SET);
	fread(&value, 8, 1, f);
	fclose(f);
	
	if(value == 0x1079370) { // 421+
		ps2hwemu_stage1_size = (uint32_t) ps2hwemu_stage1_421_bin_size;
		ps2hwemu_stage1 = (uint8_t *) ps2hwemu_stage1_421_bin;
		ps2hwemu_stage2_size = (uint32_t) ps2hwemu_stage2_421_bin_size;
		ps2hwemu_stage2 = (uint8_t *) ps2hwemu_stage2_421_bin;
	} else
	if(value == 0x1079C70) { // 430+
		ps2hwemu_stage1_size = (uint32_t) ps2hwemu_stage1_421_bin_size;
		ps2hwemu_stage1 = (uint8_t *) ps2hwemu_stage1_421_bin;
		ps2hwemu_stage2_size = (uint32_t) ps2hwemu_stage2_430_bin_size;
		ps2hwemu_stage2 = (uint8_t *) ps2hwemu_stage2_430_bin;
	} else
	if(value == 0x1079DF0) { // 440+
		ps2hwemu_stage1_size = (uint32_t) ps2hwemu_stage1_440_bin_size;
		ps2hwemu_stage1 = (uint8_t *) ps2hwemu_stage1_440_bin;
		ps2hwemu_stage2_size = (uint32_t) ps2hwemu_stage2_440_bin_size;
		ps2hwemu_stage2 = (uint8_t *) ps2hwemu_stage2_440_bin;
	} else
	if(value == 0x107BDF0) { // 453+
		ps2hwemu_stage1_size = (uint32_t) ps2hwemu_stage1_453_bin_size;
		ps2hwemu_stage1 = (uint8_t *) ps2hwemu_stage1_453_bin;
		ps2hwemu_stage2_size = (uint32_t) ps2hwemu_stage2_453_bin_size;
		ps2hwemu_stage2 = (uint8_t *) ps2hwemu_stage2_453_bin;
	} else return FAILED;
	
	if ( ps2gen("/dev_flash/ps2emu/ps2_emu.self", tmp_hw, ps2hwemu_stage1, ps2hwemu_stage1_size) == FAILED) {
		return FAILED;
	}
	
	f = fopen("/dev_flash/ps2emu/ps2_netemu.self", "rb");
	if(f==NULL) return FAILED;
	fseek(f, 0xF8, SEEK_SET);
	fread(&value, 8, 1, f);
	fclose(f);
	
	if(value == 0x283B90) { // 421+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_421_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_421_bin;
	} else
	if(value == 0x284578) { // 430+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_430_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_430_bin;
	} else
	if(value == 0x288F68) { // 440+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_440_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_440_bin;
	} else
	if(value == 0x2890A8) { // 446+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_446_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_446_bin;
	} else
	if(value == 0x28E8F8) { // 450+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_450_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_450_bin;
	} else
	if(value == 0x28F638) { // 453+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_453_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_453_bin;
	} else
	if(value == 0x28F6B8) { // 455+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_455_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_455_bin;
	} else
	if(value == 0x28F878) { // 460+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_460_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_460_bin;
	} else
	if(value == 0x28F940) { // 478+
		ps2netemu_stage2_size = (uint32_t) ps2netemu_stage2_478_bin_size;
		ps2netemu_stage2 = (uint8_t *) ps2netemu_stage2_478_bin;
	} else return FAILED;
	
	if ( ps2gen("/dev_flash/ps2emu/ps2_netemu.self", tmp_net, ps2netemu_stage2, ps2netemu_stage2_size) == FAILED) {
		return FAILED;
	}
	
	if(path_info("/dev_blind") == _NOT_EXIST) {
		sys_fs_mount("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_FAT", "/dev_blind", 0);
		usleep(1000);
	}
	/*
	print_load("Saving Original files...")
	char bak[128];
	sprintf(bak, "/dev_hdd0/game/%s/USRDIR/PS2BAK", ManaGunZ_id);
	Delete(bak);
	mkdir(bak, 0777);
	if ( Copy("/dev_blind/ps2emu", bak) == FAILED ) {
		print_load("Error : failed to copy original files");
		return FAILED;
	}
	*/
	
	Delete("/dev_blind/ps2emu");
	mkdir("/dev_blind/ps2emu", 0777);
	
	if( Copy(tmp_net, "/dev_blind/ps2emu/ps2_netemu.self") == FAILED ) {
		print_load("Error : failed to copy patched ps2_netemu");
		return FAILED;
	} else 
	if( Copy(tmp_hw, "/dev_blind/ps2emu/ps2_hwemu.self") == FAILED ) {
		print_load("Error : failed to copy patched ps2_hwemu");
		return FAILED;
	} else 
	if( Copy(tmp_gx, "/dev_blind/ps2emu/ps2_gxemu.self") == FAILED ) {
		print_load("Error : failed to copy patched ps2_gxemu");
		return FAILED;
	}
	
	f = fopen("/dev_blind/ps2emu/ps2hwemu_stage2.bin", "wb");
	if(f==NULL) {
		print_load("Error : failed to create ps2hwemu_stage2.bin");
		return FAILED;
	}
	fwrite(ps2hwemu_stage2, ps2hwemu_stage2_size, 1, f);
	fclose(f);
	
	f = fopen("/dev_blind/ps2emu/ps2gxemu_stage2.bin", "wb");
	if(f==NULL)  {
		print_load("Error : failed to create ps2gxemu_stage2.bin");
		return FAILED;
	}
	fwrite(ps2gxemu_stage2, ps2gxemu_stage2_size, 1, f);
	fclose(f);
	
	return SUCCESS;
}

//*******************************************************
// IRD
//*******************************************************

int Download_IRD(char *titleID) 
{
	
	print_head("Downloading IRD ...");
	FILE* f;
	char url[255]="http://jonnysp.bplaced.net/data.php?columns%5B0%5D%5Bdata%5D=id&columns%5B0%5D%5Bsearchable%5D=true&columns%5B0%5D%5Bsearch%5D%5Bvalue%5D=";
	strcat(url, titleID);
	if( download(url, "/dev_hdd0/tmp/ird.tmp") == FAILED ) {
		return FAILED;
	}
	
	f = fopen("/dev_hdd0/tmp/ird.tmp", "rb");
	if(f == NULL) {
		print_load("Error : ird.tmp not found");
		return FAILED;
	}
	fseek (f , 0 , SEEK_END);
	u32 size = ftell (f);
	fseek(f, 0, SEEK_SET);
	
	char *mem = (char *) malloc(size);
	fread(mem,1,size, f);
	fclose(f);
	Delete("/dev_hdd0/tmp/ird.tmp");
	
	char IRD_url[128];
	char IRD_dst[128];
	int n;
	strcpy(IRD_url, "http://jonnysp.bplaced.net/ird/");
	
	for(n=0; n<size ; n++) {
		if(!memcmp((char *) &mem[n], (char *) titleID, 9)) {
			if( mem[n+9] == '-' ) {
				strncat(IRD_url, &mem[n], 46);
				break;
			}
		}
	}
	free(mem);
	
	sprintf(IRD_dst, "/dev_hdd0/game/%s/USRDIR/sys/Check", ManaGunZ_id);
	
	if(path_info(IRD_dst) == _NOT_EXIST) mkdir(IRD_dst, 0777);
	
	sprintf(IRD_dst, "/dev_hdd0/game/%s/USRDIR/sys/Check/%s.ird", ManaGunZ_id, titleID);
	
	if( download(IRD_url, IRD_dst) == FAILED) {
		Delete(IRD_dst);
		return FAILED;
	}
	
	//check
	if(IRD_match(titleID, IRD_dst) == YES ) return SUCCESS;
	
	Delete(IRD_dst);
	return FAILED;

}

int search_IRD(char *titleID, char *dir_path, char *IRD_path)
{
	char temp[128];
	
	sprintf(temp, "%s/%s.ird", dir_path, titleID);
	
	if(path_info(temp) == _FILE) {
		if ( IRD_match(titleID, temp) == YES ) {
			strcpy(IRD_path, temp);
			return FOUND;
		}
	}
	
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(dir_path);
	if(d==NULL) return NOT_FOUND;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		if(dir->d_type & DT_DIR) continue;
			
		sprintf(temp, "%s/%s", dir_path, dir->d_name);
		
		if(strstr(dir->d_name, ".ird")) {
			if ( IRD_match(titleID, temp) == YES ) {
				strcpy(IRD_path, temp);
				closedir(d);
				return FOUND;
			}
		}
	}
	closedir(d);
	
	return NOT_FOUND;
}

u8 md5_filefromISO(char *path, char *filename, unsigned char output[16])
{
	FILE* f;
	f = fopen(path, "rb");	
	if(f==NULL) {
		memset(output, 0, sizeof(output));
		return FAILED;
	}
	
	u64 file_offset=0;
	u8 ret=0;
	u32 file_size=0;

	ret = get_FileOffset(f, filename, &file_offset, (u32 *) &file_size);
	//print_load("Warning : %s offset %llX, size %llX, ret %d", filename, file_offset, file_size, ret);
	if(file_offset==0 || file_size==0 || ret == FAILED) {fclose(f);return FAILED;}
	
	u8 split666 = is_66600(path);
	if(is_splitted_iso(path)==YES || split666) {
	
		char iso_path[128];
		char temp[128];
		u64 fsize=0;
		int i;
		int l = strlen(path);
		
		strcpy(iso_path, path);
		iso_path[l-1]=0;
		if(split666) iso_path[l-2]=0;
		strcpy(temp, iso_path);
		
		for(i=0; i<32; i++) {
			if(split666) sprintf(iso_path, "%s%02d", temp, i);
			else sprintf(iso_path, "%s%d", temp, i);
			
			fsize = get_size(iso_path, NO);
			
			if(file_offset<fsize) {
				if(i!=0) {					 
					fclose(f);
					f = fopen(iso_path, "rb");	
					if(f==NULL) return FAILED;
				}
				break;
			}
			file_offset -= fsize;
		}
	}
	
	u64 val64;
	fseek(f, file_offset-0x14, SEEK_SET);
	fread(&val64, sizeof(u64), 1, f);
	
	u8 is_bin=NO;
	if(val64==0xFFFFFFFFFFFFFF00) is_bin=YES;
	
	fseek(f, file_offset, SEEK_SET);
	
    md5_context ctx;
	u32 wrlen = 2048;
    unsigned char buf[wrlen];
	u64 read = 0;
	
	prog_bar1_value=0;
	
	md5_starts( &ctx );	
	
	while(read < file_size) {
		if(read+wrlen > file_size) wrlen = (u32)file_size-read;
		fread(buf, sizeof(u8), wrlen, f);
		if(is_bin) fseek(f, 0x130, SEEK_CUR);
		read += wrlen;
		prog_bar1_value = (read*100)/file_size;
		md5_update(&ctx, buf, wrlen);
		if(cancel) break;
	}
	
	fclose(f);
	
	prog_bar1_value=-1;
	
    md5_finish(&ctx, output);

    memset(&ctx, 0, sizeof(md5_context));
	
	if(cancel==YES) {
		memset(output, 0, sizeof(output));
		return FAILED;
	}
	
    return SUCCESS;
}

u8 CheckIRD(char *G_PATH)
{
	char IRD_path[128]={0};
	char IRD_dir[128];
	char titleID[32];
	int i;
	
	print_head("Searching IRD...");
	
	if(GetParamSFO("TITLE_ID", titleID, -1, G_PATH) == FAILED ) {
		print_load("Error : Cannot get title ID");
		return FAILED;
	}

	sprintf(IRD_dir, "/dev_hdd0/game/%s/USRDIR/sys/Check", ManaGunZ_id);
	
	if( search_IRD(titleID, IRD_dir, IRD_path) == FOUND ) goto check;
	
	for(i=0; i<=device_number; i++) {
	
		if(strstr(list_device[i], "dev_usb")  || strstr(list_device[i], "dev_hdd0")) {
			sprintf(IRD_dir, "/%s/IRD", list_device[i]);
		} else continue;
		
		if( search_IRD(titleID, IRD_dir, IRD_path) == FOUND ) goto check;
		
	}
	
	if( Download_IRD(titleID) == SUCCESS) {
		sprintf(IRD_path, "/dev_hdd0/game/%s/USRDIR/sys/Check/%s.ird", ManaGunZ_id, titleID);
		goto check;
	}
	
	print_load ("Error : IRD not found !");
	return FAILED;
	
check:
	print_head("Checking MD5...");
	IRDMD5(IRD_path, G_PATH);
	
	if(cancel == YES) return FAILED;
	
	return SUCCESS;
}

//*******************************************************
// Covers
//*******************************************************

u8 Get_ID(char *gpath, u8 platform, char *game_ID)
{
	if(platform == _ISO_PS3 || platform == _JB_PS3) {
		return GetParamSFO("TITLE_ID", game_ID, -1, gpath);	
	} else
	if(platform == _ISO_PSP || platform == _JB_PSP) {
		return GetParamSFO("DISC_ID", game_ID, -1, gpath);	
	} else
	if(platform == _ISO_PS2 || platform == _ISO_PS1) {
		char *mem = NULL;
		int size;
		mem = LoadFileFromISO(NO, gpath, "SYSTEM.CNF", &size);
		if(mem==NULL) return FAILED;
		if( strstr(mem, ";") != NULL) strtok(mem, ";");
		if( strstr(mem, "\\") != NULL) strcpy(game_ID, &strrchr(mem, '\\')[1]); else
		if( strstr(mem, ":") != NULL) strcpy(game_ID, &strrchr(mem, ':')[1]);
		free(mem);
	} else
	if(platform == _JB_PS2 || platform == _JB_PS1) {
		char temp[255];
		sprintf(temp, "%s/SYSTEM.CNF", gpath);
		char *mem = NULL;
		int size;
		mem = LoadFile(temp, &size);
		if(mem==NULL) return FAILED;
		if( strstr(mem, ";") != NULL) strtok(mem, ";");
		if( strstr(mem, "\\") != NULL) strcpy(game_ID, &strrchr(mem, '\\')[1]); else
		if( strstr(mem, ":") != NULL) strcpy(game_ID, &strrchr(mem, ':')[1]);
		free(mem);
	} 
	else return FAILED;
	
	return SUCCESS;
	
}

char lowit(char in){
	if('A'<=in && in<='Z') 
		return in-('Z'-'z');
	return in;
} 

char upit(char in){
	if('a'<=in && in<='z') 
		return in+('Z'-'z');
	return in;
} 

void Download_covers()
{
	int i;
	char game_ID[20];
	char link[255];
	char out[255];
	
	int nb_dl = -1;
	
	print_head("Downloading covers");
	
	for(i=0; i<=game_number; i++) {
		prog_bar1_value = (i*100)/game_number;
		
		if(cancel==YES) break;
		
		memset(game_ID, 0, sizeof(game_ID));
		memset(link, 0, sizeof(link));
		
		if( Get_ID(list_game_path[i], list_game_platform[i], game_ID) == FAILED) {
			print_load("Error : Failed to get ID %s", list_game_path[i]);
			continue;
		}
		int j;
		for(j=0; j < strlen(game_ID); j++) game_ID[j] = upit(game_ID[j]);
		
		if(list_game_platform[i] == _JB_PS3 || list_game_platform[i] == _ISO_PS3)
		if(strstr(game_ID, "NP") != NULL) continue;
		
		sprintf(out, "/dev_hdd0/game/%s/USRDIR/covers/%s.JPG", ManaGunZ_id, game_ID);
		
		if(path_info(out)==_FILE) {print_load("OK : %s", list_game_title[i]); continue;}
		
		sprintf(link, "http://gamecovers.free.fr/download.php?file=%s.jpg", game_ID);

		if(download(link, out) == SUCCESS) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
		
		/*	
		
		// PS3
		http://www.gametdb.com/PS3/BCES00001
		
		// PS2/PSP/PS3
		http://sce.scene7.com/is/image/playstation/bljs10332_jacket
		http://sce.scene7.com/is/image/playstation/sles51800_jacket
		sles51800
		SLES-51800
		
		// PS2/PS2/PSX/PSP
		http://www.gameswave.com/media/PS3/BCES-00001/pics/_source.png
		http://www.gameswave.com/media/PS2/SCES-50000/pics/_source.png
		http://www.gameswave.com/media/PSX/SCES-00001/pics/_source.png
		http://www.gameswave.com/media/PSP/UCES-00001/pics/_source.png 
		
		// PSP/PS3
		http://renascene.com
		
		// PS2
		http://opl.sksapps.com
		
		// PSX/PS2/PSP
		http://psxdatacenter.com
		
		// PSX
		http://playstationmuseum.com/product-codes/slus-00870/
		
		http://www.play-asia.com
		http://www.suruga-ya.jp	
		http://www.jeuxactu.com
		http://www.jeuxvideo.com
		
		
		u8 found = NO;
		int n,k;
		if(list_game_platform[i] == _JB_PS3 || list_game_platform[i] == _ISO_PS3) {
			//sprintf(link, "http://damox.net/images/covers/PS3/%s.JPG", game_ID);
			
			//if(download(link, out) == SUCCESS) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}

			char region[17][4] = {"US","EN","FR","ES","DE","IT","AU","NL","PT","SE","DK","NO","FI","TR","KO","RU","JA"};
			for (n = 0; n < 17; n++) {
				sprintf(link, "http://art.gametdb.com/ps3/cover/%s/%s.jpg", &region[n][0], game_ID);
				if(download(link, out) == SUCCESS) {found=YES; break;} 
			}
			if(found==YES) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
			
			char lowID[10];
			strcpy(lowID, game_ID);
			lowID[0]=lowit(lowID[0]);
			lowID[1]=lowit(lowID[1]);
			lowID[2]=lowit(lowID[2]);
			lowID[3]=lowit(lowID[3]);
			sprintf(link, "http://sce.scene7.com/is/image/playstation/%s_jacket", lowID);
			if(download(link, out) == SUCCESS) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
			
			sprintf(link, "http://renascene.com/ps3/?target=search&srchser=1&srch=%s", game_ID);
			if(download(link, "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp")==SUCCESS) {
				char *data;
				int file_size;
				char tmp[255];
				data = LoadFile("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp", &file_size);
				Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
				char *pch = strstr(data, "http://renascene.com/ps3/info/");
				if(pch != NULL) {
					strncpy(tmp, pch, 40);
					if( strstr(tmp, "\"") != NULL) strtok(tmp, "\"");
					if(download(tmp, "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp")==SUCCESS) {
						free(data);
						data = LoadFile("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp", &file_size);
						Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
						char *pch2 = strstr(data, "http://renascene.com/pics/ps3/poster/");
						if(pch2 != NULL) {
							strncpy(tmp, pch2, 255);
							if( strstr(tmp, ">") != NULL) strtok(tmp, ">");
							if(download(tmp, out)==SUCCESS) found=YES;
						}
					}
				}
				free(data);
			}
			
			if(found==YES) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
			print_load("FAILED : %s", list_game_title[i]); 
		} else
		if(list_game_platform[i] == _JB_PS2 || list_game_platform[i] == _ISO_PS2) {
			
			//sprintf(link, "http://opl.sksapps.com/art/%s_COV.jpg", game_ID);
			//if( download(link, out) == SUCCESS) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
			
			sprintf(link, "http://oplmanager.no-ip.info/site/?gamedetails&game=%s", game_ID);
			if(download(link, "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp")==SUCCESS) {
				char *data;
				int file_size;
				char tmp[128];
				data = LoadFile("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp", &file_size);
				char *pch = strstr(data, "/files/COV/");
				if(pch != NULL) {
					strncpy(tmp, pch, 127);
					if( strstr(tmp, "'") != NULL) strtok(tmp, "'");
					sprintf(link, "http://oplmanager.no-ip.info%s", tmp);
					if(download(link, out)==SUCCESS) found=YES; 
				}
				Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
				free(data);
			}
			
			if(found==YES) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
			
			char region[3] = {'U','P','J'};
			char letter[27][4];
			strcpy(letter[0], "0-9"); for(n=0; n < 26; n++) sprintf(letter[1+n], "%c", 65+n);
			
			char ID[20];				
			strcpy(ID, game_ID);
			ID[4]='-';
			ID[8]=ID[9];
			ID[9]=ID[10];
			ID[10]=0;
			
			n=-1;
			
			if(ID[2]=='U') n = 0; else
			if(ID[2]=='E') n = 1; else
			if(ID[2]=='P') n = 2;
				
			if(n != -1) {
				for(k=0; k<27; k++) {
					sprintf(link, "http://psxdatacenter.com/psx2/images2/covers/%c/%s/%s.jpg", region[n], letter[k], ID);
					if(download(link, out)==SUCCESS) {found=YES; break;} 
				}
			} else {
				u8 found = NO;
				for(n=0; n<3; n++) {
					for(k=0; k<27; k++) {
						sprintf(link, "http://psxdatacenter.com/psx2/images2/covers/%c/%s/%s.jpg", region[n], letter[k], ID);
						if(download(link, out)==SUCCESS) {found = YES; break;}
					}
					if(found==YES) break;
				}
			}
			if(found==YES) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
						
			print_load("FAILED : %s", list_game_title[i]); 
		} else
		if(list_game_platform[i] == _JB_PS1 || list_game_platform[i] == _ISO_PS1) {
			
			//see http://playstationmuseum.com/product-codes/%s
			
			char region[3] = {'U','P','J'};
			char letter[27][4];
			strcpy(letter[0], "0-9"); for(n=0; n < 26; n++) sprintf(letter[1+n], "%c", 65+n);
			
			char ID[20];				
			strcpy(ID, game_ID);
			ID[4]='-';
			ID[8]=ID[9];
			ID[9]=ID[10];
			ID[10]=0;
				
			n=-1;
			
			if(ID[2]=='U') n = 0; else
			if(ID[2]=='E') n = 1; else
			if(ID[2]=='P') n = 2;
			
			if(n != -1) {
				for(k=0; k<27; k++) {
					sprintf(link, "http://psxdatacenter.com/images/covers/%c/%s/%s.jpg", region[n], letter[k], ID);
					if(download(link, out)==SUCCESS) {found=YES; break;}
				}
			} else {
				for(n=0; n<3; n++) {
					for(k=0; k<27; k++) {
						sprintf(link, "http://psxdatacenter.com/images/covers/%c/%s/%s.jpg", region[n], letter[k], ID);
						if(download(link, out)==SUCCESS)  {found = YES; break;}
					}
					if(found==YES) break;
				}
			}
			
			if(found==YES) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
			else print_load("FAILED : %s", list_game_title[i]); 
		} else
		if(list_game_platform[i] == _JB_PSP || list_game_platform[i] == _ISO_PSP) {
			
			//sprintf(link, "http://damox.net/images/covers/PSP/%s.jpg", game_ID);
			//if(download(link, out) == SUCCESS) found=YES;
			
			//if(found==YES) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
			
			char lowID[10];
			strcpy(lowID, game_ID);
			lowID[0]=lowit(lowID[0]);
			lowID[0]=lowit(lowID[1]);
			lowID[0]=lowit(lowID[2]);
			lowID[0]=lowit(lowID[3]);
			sprintf(link, "http://sce.scene7.com/is/image/playstation/%s_jacket", lowID);
			if(download(link, out) == SUCCESS) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
			
			sprintf(link, "http://renascene.com/?target=search1&srchser=1&srch=%s", game_ID);
			if(download(link, "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp")==SUCCESS) {
				char *data;
				int file_size;
				char tmp[255];
				data = LoadFile("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp", &file_size);
				Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
				char *pch = strstr(data, "http://renascene.com/info/umd/");
				if(pch != NULL) {
					strncpy(tmp, pch, 40);
					if( strstr(tmp, "'") != NULL) strtok(tmp, "'");
					if(download(tmp, "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp")==SUCCESS) {
						free(data);
						data = LoadFile("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp", &file_size);
						Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
						char *pch2 = strstr(data, "http://renascene.com/pics/poster/Norm/");
						if(pch2 != NULL) {
							strncpy(tmp, pch2, 255);
							if( strstr(tmp, ">") != NULL) strtok(tmp, ">");
							if(download(tmp, out)==SUCCESS) found=YES;
						}
					}
				}
				free(data);
			}
			
			if(found==YES) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
		}
		*/
		
		print_load("FAILED : %s", list_game_title[i]); 
		
	}
	
	if(0 <= nb_dl) start_Load_GamePIC();
}

//*******************************************************
//Remove P&P
//*******************************************************

void remove_cfw_syscalls()
{
	u64 syscall_not_impl ;
	
	syscall_not_impl = lv2peek(SYSCALL_TABLE);
	
	lv2poke(SYSCALL_TABLE + (8*6), syscall_not_impl);
	lv2poke(SYSCALL_TABLE + (8*8), syscall_not_impl);
	lv2poke(SYSCALL_TABLE + (8*9), syscall_not_impl);
	lv2poke(SYSCALL_TABLE + (8*10), syscall_not_impl);
	lv2poke(SYSCALL_TABLE + (8*35), syscall_not_impl);
	lv2poke(SYSCALL_TABLE + (8*36), syscall_not_impl);
	lv2poke(SYSCALL_TABLE + (8*7), syscall_not_impl);
	
	if(lv2peek(0x8000000000003000ULL)==0xFFFFFFFF80010003ULL) {
		lv2syscall3(392, 0x1004, 0xa, 0x1b6); //buzzer
		return;
	}
	
	u64 sc_not_impl_pt = lv2peek(syscall_not_impl);
	u64 sc6 = lv2peek(SYSCALL_TABLE + (8*6));
	//u64 sc8 = lv2peek(SYSCALL_TABLE + (8*8));
	u64 sc9 = lv2peek(SYSCALL_TABLE + (8*9));
	u64 sc10 = lv2peek(SYSCALL_TABLE + (8*10));
	u64 sc35 = lv2peek(SYSCALL_TABLE + (8*35));
	u64 sc36 = lv2peek(SYSCALL_TABLE + (8*36));
	u64 sc7 = lv2peek(SYSCALL_TABLE + (8*7));
	
	if(sc6!=syscall_not_impl) lv2poke(sc6, sc_not_impl_pt);
	//if(sc8!=syscall_not_impl) lv2poke(sc8, sc_not_impl_pt);
	if(sc9!=syscall_not_impl) lv2poke(sc9, sc_not_impl_pt);
	if(sc10!=syscall_not_impl) lv2poke(sc10, sc_not_impl_pt);
	if(sc35!=syscall_not_impl) lv2poke(sc35, sc_not_impl_pt);
	if(sc36!=syscall_not_impl) lv2poke(sc36, sc_not_impl_pt);
	if(sc7!=syscall_not_impl) lv2poke(sc7, sc_not_impl_pt);
	
	if(lv2peek(0x8000000000003000ULL)==0xFFFFFFFF80010003ULL) {
		lv2syscall3(392, 0x1004, 0xa, 0x1b6);
	}
	
}

//*******************************************************
// Signed ELF
//*******************************************************

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <getopt.h>

#include "types.h"
#include "config.h"
#include "aes.h"
#include "util.h"
#include "keys.h"
#include "sce.h"
#include "np.h"
#include "self.h"
#include "rvk.h"
#include "frontend.h"

/*! Shorter Versions of arg options. */
#define ARG_NULL no_argument
#define ARG_NONE no_argument
#define ARG_REQ required_argument
#define ARG_OPT optional_argument

/*! Verbose mode. */
BOOL _verbose = FALSE;
/*! Raw mode. */
BOOL _raw = FALSE;

/*! List keys. */
//static BOOL _list_keys = FALSE;
/*! Print infos on file. */
//static BOOL _print_info = FALSE;
/*! Decrypt file. */
static BOOL _decrypt_file = FALSE;
/*! Encrypt file. */
static BOOL _encrypt_file = FALSE;

/*! Parameters. */
char *_template = NULL;
char *_file_type = NULL;
char *_compress_data = NULL;
char *_skip_sections = NULL;
char *_key_rev = NULL;
char *_meta_info = NULL;
char *_keyset = NULL;
char *_auth_id = NULL;
char *_vendor_id = NULL;
char *_self_type = NULL;
char *_app_version = NULL;
char *_fw_version = NULL;
char *_add_shdrs = NULL;
char *_ctrl_flags = NULL;
char *_cap_flags = NULL;
#ifdef CONFIG_CUSTOM_INDIV_SEED
char *_indiv_seed = NULL;
#endif
char *_license_type = NULL;
char *_app_type = NULL;
char *_content_id = NULL;
char *_klicensee = NULL;
char *_real_fname = NULL;
char *_add_sig = NULL;

int make_EBOOT_NPDRM(char *in, char *out, char *content_id)
{
	_template = NULL;
	_file_type = NULL;
	_compress_data = NULL;
	_skip_sections = NULL;
	_key_rev = NULL;
	_meta_info = NULL;
	_keyset = NULL;
	_auth_id = NULL;
	_vendor_id = NULL;
	_self_type = NULL;
	_app_version = NULL;
	_fw_version = NULL;
	_add_shdrs = NULL;
	_ctrl_flags = NULL;
	_cap_flags = NULL;
	#ifdef CONFIG_CUSTOM_INDIV_SEED
	_indiv_seed = NULL;
	#endif
	_license_type = NULL;
	_app_type = NULL;
	_content_id = NULL;
	_klicensee = NULL;
	_real_fname = NULL;
	_add_sig = NULL;
	
	_decrypt_file = FALSE;
	_encrypt_file = FALSE;
	
	_file_type=(char*) "SELF";
	_compress_data=(char*) "TRUE";
	_skip_sections =(char*) "TRUE";
	_key_rev=(char*) "1C"; 
	_auth_id=(char*) "1010000001000003";
	_vendor_id=(char*) "01000002";
	_app_version=(char*) "0001000000000000";
	_fw_version=(char*) "0004002100000000";
	_add_shdrs=(char*) "TRUE";
	_license_type=(char*) "FREE";
	_app_type=(char*) "EXEC";
	_self_type=(char*) "NPDRM";
	_content_id = (char*) content_id;
	_real_fname=(char*) "EBOOT.BIN";
	_ctrl_flags = "4000000000000000000000000000000000000000000000000000000000000002";
	_cap_flags = "00000000000000000000000000000000000000000000007B0000000100000000";
	_encrypt_file = TRUE;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/keys", ManaGunZ_id);
	if(keys_load(temp_buffer) == FALSE) return NOK;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/ldr_curves", ManaGunZ_id);
	if(curves_load(temp_buffer) == FALSE) return NOK;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/vsh_curves", ManaGunZ_id);
	if(vsh_curves_load(temp_buffer) == FALSE) return NOK;
	
	if(frontend_encrypt(in, out) != 0) return NOK;

	return OK;
}

int Sign_PRX(char *in, char *out)
{
	_template = NULL;
	_file_type = NULL;
	_compress_data = NULL;
	_skip_sections = NULL;
	_key_rev = NULL;
	_meta_info = NULL;
	_keyset = NULL;
	_auth_id = NULL;
	_vendor_id = NULL;
	_self_type = NULL;
	_app_version = NULL;
	_fw_version = NULL;
	_add_shdrs = NULL;
	_ctrl_flags = NULL;
	_cap_flags = NULL;
	#ifdef CONFIG_CUSTOM_INDIV_SEED
	_indiv_seed = NULL;
	#endif
	_license_type = NULL;
	_app_type = NULL;
	_content_id = NULL;
	_klicensee = NULL;
	_real_fname = NULL;
	_add_sig = NULL;

	
	_file_type=(char*) "SELF";
	_compress_data=(char*) "TRUE";
	_skip_sections =(char*) "FALSE";
	_key_rev=(char*) "1C"; 
	_auth_id=(char*) "1010000001000003";
	_vendor_id=(char*) "01000002";
	_app_version=(char*) "0001000000000000";
	_fw_version=(char*) "0004002100000000";
	_add_shdrs=(char*) "TRUE";
	_self_type=(char*) "APP";
	_encrypt_file = TRUE;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/keys", ManaGunZ_id);
	if(keys_load(temp_buffer) == FALSE) return NOK;

	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/ldr_curves", ManaGunZ_id);
	if(curves_load(temp_buffer) == FALSE) return NOK;

	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/vsh_curves", ManaGunZ_id);
	if(vsh_curves_load(temp_buffer) == FALSE) return NOK;

	if(frontend_encrypt(in, out)) return NOK;

	return OK;

}

int Sign_ELF(char *in, char *out)
{
	_template = NULL;
	_file_type = NULL;
	_compress_data = NULL;
	_skip_sections = NULL;
	_key_rev = NULL;
	_meta_info = NULL;
	_keyset = NULL;
	_auth_id = NULL;
	_vendor_id = NULL;
	_self_type = NULL;
	_app_version = NULL;
	_fw_version = NULL;
	_add_shdrs = NULL;
	_ctrl_flags = NULL;
	_cap_flags = NULL;
	#ifdef CONFIG_CUSTOM_INDIV_SEED
	_indiv_seed = NULL;
	#endif
	_license_type = NULL;
	_app_type = NULL;
	_content_id = NULL;
	_klicensee = NULL;
	_real_fname = NULL;
	_add_sig = NULL;

	_file_type=(char*) "SELF";
	_compress_data=(char*) "TRUE";
	_key_rev=(char*) "1C"; 
	_auth_id=(char*) "1010000001000003";
	_vendor_id=(char*) "01000002";
	_app_version=(char*) "0001000000000000";
	_fw_version=(char*) "0004002100000000";
	_license_type=(char*) "FREE";
	_app_type=(char*) "EXEC";
	_self_type=(char*) "APP";
	_ctrl_flags = "4000000000000000000000000000000000000000000000000000000000000002";
	_cap_flags = "00000000000000000000000000000000000000000000007B0000000100000000";
	_encrypt_file = TRUE;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/keys", ManaGunZ_id);
	if(keys_load(temp_buffer) == FALSE) return NOK;

	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/ldr_curves", ManaGunZ_id);
	if(curves_load(temp_buffer) == FALSE) return NOK;

	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/vsh_curves", ManaGunZ_id);
	if(vsh_curves_load(temp_buffer) == FALSE) return NOK;

	if(frontend_encrypt(in, out)) return NOK;

	return OK;

}

int Sign_EBOOT(char *in, char *out)
{
	_template = NULL;
	_file_type = NULL;
	_compress_data = NULL;
	_skip_sections = NULL;
	_key_rev = NULL;
	_meta_info = NULL;
	_keyset = NULL;
	_auth_id = NULL;
	_vendor_id = NULL;
	_self_type = NULL;
	_app_version = NULL;
	_fw_version = NULL;
	_add_shdrs = NULL;
	_ctrl_flags = NULL;
	_cap_flags = NULL;
	#ifdef CONFIG_CUSTOM_INDIV_SEED
	_indiv_seed = NULL;
	#endif
	_license_type = NULL;
	_app_type = NULL;
	_content_id = NULL;
	_klicensee = NULL;
	_real_fname = NULL;
	_add_sig = NULL;
	
	_decrypt_file = FALSE;
	_encrypt_file = FALSE;
	
	_file_type=(char*) "SELF";
	_compress_data=(char*) "TRUE";
	_skip_sections =(char*) "TRUE";
	_key_rev=(char*) "1C"; 
	_auth_id=(char*) "1010000001000003";
	_vendor_id=(char*) "01000002";
	_app_version=(char*) "0001000000000000";
	_fw_version=(char*) "0004002100000000";
	_add_shdrs=(char*) "TRUE";
	_app_type=(char*) "EXEC";
	_self_type=(char*) "APP";
	_real_fname=(char*) "EBOOT.BIN";
	_ctrl_flags = "4000000000000000000000000000000000000000000000000000000000000002";
	_cap_flags = "00000000000000000000000000000000000000000000007B0000000100000000";
	_encrypt_file = TRUE;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/keys", ManaGunZ_id);
	if(keys_load(temp_buffer) == FALSE) return NOK;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/ldr_curves", ManaGunZ_id);
	if(curves_load(temp_buffer) == FALSE) return NOK;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/vsh_curves", ManaGunZ_id);
	if(vsh_curves_load(temp_buffer) == FALSE) return NOK;
	
	if(frontend_encrypt(in, out) != 0) return NOK;

	return OK;
}

int Sign_PS2ELF(char *in, char *out)
{
	_template = NULL;
	_file_type = NULL;
	_compress_data = NULL;
	_skip_sections = NULL;
	_key_rev = NULL;
	_meta_info = NULL;
	_keyset = NULL;
	_auth_id = NULL;
	_vendor_id = NULL;
	_self_type = NULL;
	_app_version = NULL;
	_fw_version = NULL;
	_add_shdrs = NULL;
	_ctrl_flags = NULL;
	_cap_flags = NULL;
	#ifdef CONFIG_CUSTOM_INDIV_SEED
	_indiv_seed = NULL;
	#endif
	_license_type = NULL;
	_app_type = NULL;
	_content_id = NULL;
	_klicensee = NULL;
	_real_fname = NULL;
	_add_sig = NULL;

	_file_type=(char*) "SELF";
	_compress_data=(char*) "TRUE";
	_skip_sections =(char*) "FALSE";
	_auth_id=(char*) "1020000401000001";
	_add_shdrs=(char*) "TRUE";
	_vendor_id=(char*) "02000003";
	_self_type=(char*) "LV2";
	_fw_version=(char*) "0004002100000000";
	_key_rev=(char*) "0";
	_app_version=(char*) "0004002100000000";
	_encrypt_file = TRUE;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/keys", ManaGunZ_id);
	if(keys_load(temp_buffer) == FALSE) return NOK;

	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/ldr_curves", ManaGunZ_id);
	if(curves_load(temp_buffer) == FALSE) return NOK;

	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/vsh_curves", ManaGunZ_id);
	if(vsh_curves_load(temp_buffer) == FALSE) return NOK;

	if(frontend_encrypt(in, out)) return NOK;

	return OK;

}

int Extract(char *in, char *out)
{
	_template = NULL;
	_file_type = NULL;
	_compress_data = NULL;
	_skip_sections = NULL;
	_key_rev = NULL;
	_meta_info = NULL;
	_keyset = NULL;
	_auth_id = NULL;
	_vendor_id = NULL;
	_self_type = NULL;
	_app_version = NULL;
	_fw_version = NULL;
	_add_shdrs = NULL;
	_ctrl_flags = NULL;
	_cap_flags = NULL;
	#ifdef CONFIG_CUSTOM_INDIV_SEED
	_indiv_seed = NULL;
	#endif
	_license_type = NULL;
	_app_type = NULL;
	_content_id = NULL;
	_klicensee = NULL;
	_real_fname = NULL;
	_add_sig = NULL;

	_decrypt_file = FALSE;
	_encrypt_file = FALSE;
	
	_file_type=(char*) "SELF";
	_decrypt_file = TRUE;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/keys", ManaGunZ_id);
	if(keys_load(temp_buffer) == FALSE) return NOK;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/ldr_curves", ManaGunZ_id);
	if(curves_load(temp_buffer) == FALSE) return NOK;
	
	memset(temp_buffer, 0, sizeof(temp_buffer));
	sprintf(temp_buffer, "/dev_hdd0/game/%s/USRDIR/sys/data/vsh_curves", ManaGunZ_id);
	if(vsh_curves_load(temp_buffer) == FALSE) return NOK;
	
	if(frontend_decrypt(in, out)) return NOK;

	return OK;

}

u8 re_sign_EBOOT(char *path)
{
	print_load("Re-signing EBOOT.BIN");
	
	char elf[128];
	char bak[128];
	
	char local_path[128]; //faster in local if file is in usb
	
	sprintf(local_path, "/dev_hdd0/game/%s/USRDIR/sys/EBOOT.BIN", ManaGunZ_id);

	if(CopyFile(path, local_path) != SUCCESS){
		print_load("Error : Failed to copy EBOOT.BIN to the local path");
		return FAILED;
	}
	
	strcpy(elf, local_path);	
	RemoveExtention(elf);
	strcat(elf, ".elf");
	
	if(Extract(local_path, elf)==FAILED) {
		print_load("Error : Failed extract EBOOT.BIN");
		return FAILED;
	}
	
	Delete(local_path);
	
	if(Sign_EBOOT(elf, local_path)==FAILED) {
		print_load("Error : Failed sign EBOOT.BIN");
		return FAILED;
	}
	
	strcpy(bak, path);
	strcat(bak, ".MGZBAK");
	
	rename(path, bak);
	
	if(CopyFile(local_path, path) != SUCCESS) {
		print_load("Error : Failed to copy re-signed EBOOT.BIN to the original path");
		rename(bak, path);
		return FAILED;
	}
	
	Delete(local_path);
	Delete(elf);
	
	return SUCCESS;
}

u8 re_sign_SELF(char *path)
{	
	char elf[128];
	char bak[128];
	char local_path[128]; //faster in local if file is in usb
	char *filename;
	
	filename=strrchr(path, '/');
	filename=&filename[1];
	
	print_load("Re-signing %s", filename);
	
	sprintf(local_path, "/dev_hdd0/game/%s/USRDIR/sys/%s", ManaGunZ_id, filename);

	if(CopyFile(path, local_path) != SUCCESS){
		print_load("Error : Failed to copy %s to the local path", filename);
		return FAILED;
	}
	
	strcpy(elf, local_path);	
	RemoveExtention(elf);
	strcat(elf, ".elf");
	
	if(Extract(local_path, elf)==FAILED) {
		print_load("Error : Failed extract %s", filename);
		return FAILED;
	}
	
	Delete(local_path);
	
	if(Sign_ELF(elf, local_path)==FAILED) {
		print_load("Error : Failed sign %s", filename);
		return FAILED;
	}
	
	strcpy(bak, path);
	strcat(bak, ".MGZBAK");
	
	rename(path, bak);
	
	if(CopyFile(local_path, path) != SUCCESS) {
		print_load("Error : Failed to copy re-signed %s to the original path", filename);
		rename(bak, path);
		return FAILED;
	}
	
	Delete(local_path);
	Delete(elf);
	
	return SUCCESS;
}

u8 re_sign_SPRX(char *path)
{	
	char prx[128];
	char bak[128];
	char local_path[128]; //faster in local if file is in usb
	char *filename;
	
	filename=strrchr(path, '/');
	filename=&filename[1];
	
	print_load("Re-signing %s", filename);
	
	sprintf(local_path, "/dev_hdd0/game/%s/USRDIR/sys/%s", ManaGunZ_id, filename);
	
	if(CopyFile(local_path, path) != SUCCESS) {
		print_load("Error : Failed to copy %s to the local path", filename);
		return FAILED;
	}
	
	strcpy(prx, local_path);	
	RemoveExtention(prx);
	strcat(prx, ".prx");
	
	if(Extract(local_path, prx)==FAILED) {
		print_load("Error : Failed extract %s", filename);
		return FAILED;
	}
	
	Delete(local_path);
	
	if(Sign_PRX(prx, local_path)==FAILED) {
		print_load("Error : Failed sign %s", filename);
		return FAILED;
	}
	
	strcpy(bak, path);
	strcat(bak, ".MGZBAK");
	
	rename(path, bak);
	
	if(CopyFile(local_path, path) != SUCCESS) {
		print_load("Error : Failed to copy re-signed %s to the original path", filename);
		rename(bak, path);
		return FAILED;
	}
	
	Delete(local_path);
	Delete(prx);
	
	return SUCCESS;
	
}

u8 is_resigned_GAME(char *path)
{
	char temp[255];
	
	sprintf(temp, "%s/PS3_GAME/USRDIR/EBOOT.BIN.MGZBAK", path);
	
	if(path_info(temp) == _FILE) return YES;
	
	return NO;

}

u8 restore_GAME(char *path)
{
	char temp[255];
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(path);
	if(d==NULL) return FAILED;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		sprintf(temp, "%s/%s", path, dir->d_name);
		
		if(dir->d_type & DT_DIR) {
			restore_GAME(temp);
		}
		else if (strcmp(&temp[strlen(temp)-7], ".MGZBAK")==0) {
			char temp2[255];
			strcpy(temp2, temp);
			temp2[strlen(temp2)-7]= 0;
			if(unlink(temp2) == 0) {
				rename(temp, temp2);
			}	
		}
	}
	closedir(d);

	return SUCCESS;

}

u8 re_sign_GAME(char *path)
{	
	char temp[255];
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(path);
	if(d==NULL) return FAILED;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		sprintf(temp, "%s/%s", path, dir->d_name);
		
		if(dir->d_type & DT_DIR) {
			re_sign_GAME(temp);
		}
		else if(strcmp(dir->d_name, "EBOOT.BIN")==0)	{
			if(re_sign_EBOOT(temp)==FAILED) {closedir(d); return FAILED;}
		}
		else if (strcmp(&dir->d_name[strlen(dir->d_name)-5], ".sprx")==0) {
			if(re_sign_SPRX(temp)==FAILED) {closedir(d); return FAILED;}
		}
		else if (strcmp(&dir->d_name[strlen(dir->d_name)-5], ".self")==0) {
			if(re_sign_SELF(temp)==FAILED) {closedir(d); return FAILED;}
		}
	}
	closedir(d);
	
	if(SetParamSFO("PS3_SYSTEM_VER", "04.2100", position, NULL) == FAILED) return FAILED;

	return SUCCESS;
}

//*******************************************************
// Common Mount stuff
//*******************************************************

void remove_lv2_protection()
{
	lv1poke(HV_START_OFFSET +  0, 0x0000000000000001ULL);
	lv1poke(HV_START_OFFSET +  8, 0xe0d251b556c59f05ULL);
	lv1poke(HV_START_OFFSET + 16, 0xc232fcad552c80d7ULL);
	lv1poke(HV_START_OFFSET + 24, 0x65140cd200000000ULL); 
}

void fix_error()
{
	if (OFFSET_FIX_3C != 0)
	{
		_poke	(OFFSET_FIX_3C				, 0x386000007C6307B4); // error 3C
		_poke32	(OFFSET_FIX_3C + 0x8		, 0x4E800020		); // error 3C
	}
	
	if (OFFSET_FIX != 0)
	{
		_poke	(OFFSET_FIX					, 0x63FF003D60000000); // error 3D
		_poke	(OFFSET_FIX + 0xC8  		, 0x3BE000004BFFFF0C); // error 3E + unk
		_poke32	(OFFSET_FIX + 0x74		   	, 0x60000000); // unk
		_poke32	(OFFSET_FIX + 0x74 + 0x8   	, 0x48000098); // unk
	}
	
	if (OFFSET_2_FIX != 0)
	{
		_poke32	(OFFSET_2_FIX		   		, 0x60000000); // error 09
		_poke32	(OFFSET_2_FIX + 0x14  		, 0x60000000); // error 19
	}
	
	if (OFFSET_FIX_LIC != 0) _poke	(OFFSET_FIX_LIC				, 0x386000012F830000ULL ); // ignore LIC.DAT check
	if (OFFSET_FIX_2B17 != 0) _poke	(OFFSET_FIX_2B17			, 0x38600000F8690000ULL ); // error 2B and 17
	
	
}

char list_to_unplug[15][15];

u8 need_unplug()
{
	u8 i=0;
	memset(list_to_unplug, 0, sizeof(list_to_unplug));
	
	DIR *d;
	struct dirent *dir;
	d = opendir("/");
	while ((dir = readdir(d))) {
		if(strstr(dir->d_name, "dev_usb")) {
			if(strstr(GamPath, dir->d_name) == NULL) {
				strcpy(list_to_unplug[i], dir->d_name);
				i++;
			}	
		}
	}
	closedir(d);
	
	if(i>0) return YES; else return NO;
}

void unplug_device()
{
	if(need_unplug()==YES) {
		end_loading();
		while(need_unplug()==YES) {
			int i;
			cls();
			ps3pad_read();
		
			Draw_BGS();
			int x=50, y=40;
			
			FontSize(20);
			FontColor(COLOR_1);
			
			DrawFormatString(x, y, "%s :", STR_UNPLUG);
			for(i=0; i<15; i++){
				y+=20;
				DrawString(x, y, list_to_unplug[i]);
			}
		
			tiny3d_Flip();
			ScreenShot();
		}
		sleep(1);
		start_loading();
	}
}

s32 sys_storage_ext_fake_storage_event(uint64_t event, uint64_t param, uint64_t device)
{
	lv2syscall4(8, SYSCALL8_OPCODE_FAKE_STORAGE_EVENT, event, param, device);
	return_to_user_prog(s32);
}

void SetPrimaryUSB()
{
	if(strstr(GamPath, "/dev_usb") && path_info(GamPath) != _NOT_EXIST) {
		
		if(need_unplug()==NO) return;
		
		u8 f0;
		int indx=0;
		
		print_load("Disconnecting all USB device");
		for(f0=0; f0<8; f0++) sys_storage_ext_fake_storage_event(4, 0, ((f0<6)?USB_MASS_STORAGE_1(f0):USB_MASS_STORAGE_2(f0)));
		for(f0=0; f0<8; f0++) sys_storage_ext_fake_storage_event(8, 0, ((f0<6)?USB_MASS_STORAGE_1(f0):USB_MASS_STORAGE_2(f0)));

		sleep(1);

		if(strstr(GamPath, "/dev_usb00")) indx=GamPath[10]-0x30;
		
		print_load("Setting primary USB device: /dev_usb00%i", indx);
		sys_storage_ext_fake_storage_event(7, 0, ((indx<6)?USB_MASS_STORAGE_1(indx):USB_MASS_STORAGE_2(indx)));
		sys_storage_ext_fake_storage_event(3, 0, ((indx<6)?USB_MASS_STORAGE_1(indx):USB_MASS_STORAGE_2(indx)));

		sleep(3);
		
		for(f0=0; f0<8; f0++) {
			if(f0!=indx) {
				sys_storage_ext_fake_storage_event(7, 0, ((f0<6)?USB_MASS_STORAGE_1(f0):USB_MASS_STORAGE_2(f0)));
				sys_storage_ext_fake_storage_event(3, 0, ((f0<6)?USB_MASS_STORAGE_1(f0):USB_MASS_STORAGE_2(f0)));
			}
		}

	}
}

char *LoadFileProg(char *path, int *file_size)
{
	*file_size = 0;
	
	sysLv2FsChmod(path, FS_S_IFMT | 0777);
	
	struct stat s;
	if(stat(path, &s) != 0) return NULL;  
	if(S_ISDIR(s.st_mode)) return NULL;
	
	*file_size = s.st_size;
	int size = s.st_size;
	
	char *mem = malloc(*file_size);
	if(mem==NULL) return NULL;
	
	int f1 = ps3ntfs_open(path, O_RDONLY, 0766);
	if(f1<0) return NULL;
	
	prog_bar1_value = 0;
	int read = 0;
	while(read < size) {
		int wrlen = 1024;
		if(read+wrlen > size) wrlen = size-read;
		ps3ntfs_read(f1, mem+read, wrlen);
		read += wrlen;
		prog_bar1_value = (read*100) / size;
	}
	prog_bar1_value = -1;
		
	ps3ntfs_close(f1);
	
	if(read != *file_size) {
		free(mem); 
		*file_size=0;
		return NULL;
	}
	
	return mem;
}

char *LoadFile(char *path, int *file_size)
{
	*file_size = 0;
	
	sysLv2FsChmod(path, FS_S_IFMT | 0777);
	
	struct stat s;
	if(stat(path, &s) != 0) return NULL;  
	if(S_ISDIR(s.st_mode)) return NULL;
	
	*file_size = s.st_size;
	
	char *mem = malloc(*file_size);
	if(mem==NULL) return NULL;
	
	int f1 = ps3ntfs_open(path, O_RDONLY, 0766);
	if(f1<0) return NULL;
	
	u64 read = ps3ntfs_read(f1, mem, *file_size);
		
	ps3ntfs_close(f1);
	
	if(read != *file_size) {
		free(mem); 
		*file_size=0;
		return NULL;
	}
	
	return mem;
}

u8 SaveFileProg(char *path, char *mem, int file_size)
{
	int fd;
	
	fd = ps3ntfs_open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(fd<0) {return FAILED;}
	
	prog_bar1_value = 0;
	int write = 0;
	while(write < file_size) {
		int wrlen = 1024;
		if(write+wrlen > file_size) wrlen = file_size-write;
		ps3ntfs_write(fd, mem+write, wrlen);
		write += wrlen;
		prog_bar1_value = (write*100) / file_size;
	}
	prog_bar1_value = -1;
	
	ps3ntfs_close(fd);

	sysLv2FsChmod(path, FS_S_IFMT | 0777);

	return SUCCESS;
}

int SaveFile(char *path, char *mem, int file_size)
{
	int fd;
	
	fd = ps3ntfs_open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(fd<0) {return FAILED;}
	
	ps3ntfs_write(fd, (void *) mem, file_size);
	
	ps3ntfs_close(fd);

	sysLv2FsChmod(path, FS_S_IFMT | 0777);

	return SUCCESS;
}

int move_origin_to_bdemubackup(char *path)
{
	int ret=0;
	memset(temp_buffer, 0, sizeof(temp_buffer));
	
	if(strncmp(path, "/dev_usb00", 10) && strncmp(path, "/dev_hdd0", 9)) return 1;

	sprintf(temp_buffer, "%s/PS3_GAME/PS3PATH.BUP", path);
	sprintf(temp_buffer + 1024, "%s/PS3_GAME", path);

	if(SaveFile(temp_buffer, temp_buffer + 1024, strlen(temp_buffer + 1024)) == FAILED) return -1;

	if(!strncmp(temp_buffer, "/dev_hdd0", 9))	strncpy(temp_buffer + 9, "/PS3_GAME", 16); 
	else	strncpy(temp_buffer + 11, "/PS3_GAME", 16);
	
	ret=rename(temp_buffer  + 1024, temp_buffer);
	
	if(ret != 0)	return -1;

	// PS3_GM01

	sprintf(temp_buffer, "%s/PS3_GM01/PS3PATH2.BUP", path);
	sprintf(temp_buffer + 1024, "%s/PS3_GM01", path);

	if(path_info(temp_buffer + 1024) == _NOT_EXIST) {
		
		sprintf(temp_buffer, "%s/PS3_GAME/PS3PATH.BUP", path);
		if(!strncmp(temp_buffer, "/dev_hdd0", 9)) strncpy(temp_buffer + 9, "/PS3_GAME", 16);
		else	strncpy(temp_buffer + 11, "/PS3_GAME", 16);
		
		return 0;
	}

	if(SaveFile(temp_buffer, temp_buffer + 1024, strlen(temp_buffer + 1024)) == FAILED) return -1;

	if(!strncmp(temp_buffer, "/dev_hdd0", 9)) strncpy(temp_buffer + 9, "/PS3_GM01", 16);
	else	strncpy(temp_buffer + 11, "/PS3_GM01", 16);

	if((rename(temp_buffer  + 1024, temp_buffer)) != 0) return -1;

	return 0;
}

int move_bdemubackup_to_origin(char *device_path)
{
	int n;
	memset(temp_buffer, 0, sizeof(temp_buffer));
	
	sprintf(temp_buffer, "%s/PS3_GAME", device_path);
	sprintf(temp_buffer + 256, "%s/PS3_GAME/PS3PATH.BUP", device_path);

	int file_size;
	char *file;
	int ret = 0;

	if(path_info(temp_buffer) == _NOT_EXIST) {ret = -1;goto PS3_GM01;}

	file = LoadFile(temp_buffer + 256, &file_size);

	if(!file) {ret = -1;goto PS3_GM01;}

	memset(temp_buffer + 1024, 0, 0x420);

	if(file_size > 0x400) file_size = 0x400;

	memcpy(temp_buffer + 1024, file, file_size);

	free(file);

	for(n=0; n< 0x400; n++) {
		if(temp_buffer[1024 + n] == 0) break;
		if(((u8)temp_buffer[1024 + n]) < 32) {temp_buffer[1024 + n] = 0; break;}
	}

	if(strncmp(temp_buffer, temp_buffer + 1024, 10))  {ret = -1;goto PS3_GM01;} // if not /dev_usb00x return

	if(!strncmp(temp_buffer, "/dev_hdd0", 9)) {
	} else	memcpy(temp_buffer + 1024, temp_buffer, 11);

	if(rename(temp_buffer, temp_buffer + 1024) != 0)  {ret= -1; goto PS3_GM01;}

	// PS3_GM01
PS3_GM01:

	sprintf(temp_buffer, "%s/PS3_GM01", device_path);
	sprintf(temp_buffer + 256, "%s/PS3_GM01/PS3PATH2.BUP", device_path);
	
	if(path_info(temp_buffer) == _NOT_EXIST) return -1;;

	file = LoadFile(temp_buffer + 256, &file_size);
	if(!file) return -1;
	memset(temp_buffer + 1024, 0, 0x420);
	if(file_size > 0x400) file_size = 0x400;
	memcpy(temp_buffer + 1024, file, file_size);
	free(file);

	for(n=0; n< 0x400; n++) {
		if(temp_buffer[1024 + n] == 0) break;
		if(((u8)temp_buffer[1024 + n]) < 32) {temp_buffer[1024 + n] = 0; break;}
	}

	if(strncmp(temp_buffer, temp_buffer + 1024, 10)) return -1; // if not /dev_usb00x return

	if(!strncmp(temp_buffer, "/dev_hdd0", 9)) {
	} else		memcpy(temp_buffer + 1024, temp_buffer, 11);
	
	if(rename(temp_buffer, temp_buffer + 1024) != 0)  return -1;

	return ret;
}

int patch_bdmirror()
{
   	u64 n;
	u64 dat;
	int pos=-1;
	int pos2=-1;
	int device;
	char path_name[512];
	char * mem = temp_buffer;
	u64 dev_bdvd[2]  ={0x2F6465765F626476ULL, 0x6400000000000000ULL};
	//u64 dev_usb[2]	 ={0x006465765F757362ULL, 0x3030300000000000ULL};
	u64 temp_bdvd[2] ={0x2F74656D705F6264ULL, 0x7664000000000000ULL};
	//u64 esp_bdvd[2]  ={0x006573705F626476ULL, 0x6400000000000000ULL};
	int ret;
	
	ret = move_origin_to_bdemubackup(GamPath);
	if(ret!=0) print_load("Error %d: move_origin_to_bdemubackup failed", ret);

	if(strstr(GamPath, "/dev_hdd") != NULL) {
		
		device=-1;
		print_load("mount ps2disc");
		sys_fs_mount("CELL_FS_IOS:BDVD_DRIVE", "CELL_FS_ISO9660", "/dev_ps2disc", 1);
		sleep(1);
		
		for(n=0; n<10;n++) {
			if(path_info("/dev_ps2disc") != _NOT_EXIST) break;
			sys_fs_mount("CELL_FS_IOS:BDVD_DRIVE", "CELL_FS_ISO9660", "/dev_ps2disc", 1);
			usleep(1000);
		}
	
	} else {

		device = (GamPath[8]-0x30)*100 + (GamPath[9]-0x30)*10 + GamPath[10]-0x30;
		unplug_device();
		sprintf(path_name, "CELL_FS_IOS:USB_MASS_STORAGE%03d", device);
		//dev_usb[1] = GamPath[8]*0x100000000000000 + GamPath[9]*0x1000000000000 + GamPath[10]*0x10000000000 ;
	}
	
	memset(mem, 0, 0x10 * LV2MOUNTADDR_ESIZE);
	
	for(n=0 ; n < 0x10 * LV2MOUNTADDR_ESIZE ; n+=0x8) {
		dat = lv2peek(LV2MOUNTADDR + n);
		memcpy(&mem[n], &dat, sizeof(u64));
	}
	
	for(n = 0; n< 0x116c; n+= LV2MOUNTADDR_ESIZE) {
		if(!memcmp(mem + n, "CELL_FS_IOS:PATA0_BDVD_DRIVE", 29) 
			&& (!memcmp(mem + n + 0x69, "dev_bdvd", 9)) 
			&& mem[n-9]== 1 && mem[n-13]== 1)
		{
			print_load("Patch BDVD");
			lv2poke(LV2MOUNTADDR + n + 0x68		, temp_bdvd[0]);
			lv2poke(LV2MOUNTADDR + n + 0x68 + 8	, temp_bdvd[1]);
		}
		else if(device >= 0 
			&& !memcmp(mem + n, path_name, 32) 
			&& mem[n-9]== 1 && mem[n-13]== 1) 
		{	
			print_load("Patch USB");
			lv2poke(LV2MOUNTADDR + n + 0x68		, dev_bdvd[0]);
			lv2poke(LV2MOUNTADDR + n + 0x68	+ 8	, dev_bdvd[1]);
			//lv2poke(LV2MOUNTADDR + n + 0x78		, dev_usb[0]);
			//lv2poke(LV2MOUNTADDR + n + 0x78	+ 8	, dev_usb[1]);
		}
		else if(device==-1 && !memcmp(mem + n, "CELL_FS_IOS:BDVD_DRIVE", 29) 
			&& !memcmp(mem + n + 0x69, "dev_ps2disc", 12) 
			&& mem[n-9]== 1 && mem[n-13]== 1)
		{
			if(pos2 < 0) pos2 = n;
		}
		else if(device==-1 && !memcmp(mem + n, "CELL_FS_UTILITY:HDD0", 21)
			&& !memcmp(mem + n + 0x48, "CELL_FS_UFS", 11)
			&& !memcmp(mem + n + 0x69, "dev_hdd0", 9) 
			&& mem[n-9] == 1 && mem[n-13] == 1) 
		{
			if(pos < 0) pos = n;
		}
	}
	
	if(pos>0 && pos2>0) {
		print_load("Patch HDD");
	
		u64 LV2HDDADDR = 0x80000000007EF000ULL;
		
		for(n=0; n < LV2MOUNTADDR_CSIZE; n+=8) {
			dat = lv2peek(LV2MOUNTADDR + pos2 - 0x10 + n);
			lv2poke(LV2HDDADDR+0x20+n, dat);
		}
		
		dat = LV2MOUNTADDR + (u64) (pos2 - 0x10);
		lv2poke(LV2HDDADDR, dat);
		
		dat = (u64) UMOUNT_SYSCALL_OFFSET;
		lv2poke(LV2HDDADDR+0x8, dat);
		
		lv2poke(LV2HDDADDR+0x10, 0xFBA100E800000000ULL + LV2MOUNTADDR_CSIZE);
		
		for(n=0; n < LV2MOUNTADDR_CSIZE-0x10; n+=8) {
			dat = lv2peek(LV2MOUNTADDR + pos + n);
			lv2poke(LV2MOUNTADDR + pos2 + n, dat);
		}
		
		lv2poke(LV2MOUNTADDR + pos2 + 0x68		, dev_bdvd[0]);
		lv2poke(LV2MOUNTADDR + pos2 + 0x68 + 0x8, dev_bdvd[1]);
		
		//lv2poke(LV2MOUNTADDR + pos2 + 0x78		, esp_bdvd[0]);
		//lv2poke(LV2MOUNTADDR + pos2 + 0x78 + 0x8  , esp_bdvd[1]);
		
		lv2poke(LV2MOUNTADDR + pos2 + 0xA4, 0ULL);
		
		int k;
		for(k= 0; k < 100; k++) {
			PATCH_CALL(UMOUNT_SYSCALL_OFFSET, PAYLOAD_UMOUNT_OFFSET); // UMOUNT ROUTINE PATCH
			usleep(1000);
		}
	}
	else {
		if(device==-1) {
			if(pos==-1) {
				print_load("Error : hdd0 not found");
			}
			if(pos2==-1) {
				print_load("Error : ps2disk not found");
			}
		}
	}
	
	return 0;
}

void unpatch_bdmirror()
{
	u64 dat, n, m;
	
	u64 dev_bdvd[2]  ={0x2F6465765F626476ULL, 0x6400000000000000ULL};
   // u64 dev_hdd1[2]	 ={0x2F6465765F686464ULL, 0x3100000000000000ULL};
	u64 dev_usb[2]	 ={0x2F6465765F757362ULL, 0x3030300000000000ULL};
	
	char * mem = temp_buffer;
	memset(mem, 0, 0x10 * LV2MOUNTADDR_ESIZE);
	
	for(n=0 ; n < 0x10 * LV2MOUNTADDR_ESIZE ; n+=0x8) {
		dat = lv2peek(LV2MOUNTADDR + n);
		memcpy(&mem[n], &dat, sizeof(u64));
	}
	
	for(n = 0; n< 0x116c; n+= LV2MOUNTADDR_ESIZE)
	{
		/*
		if(memcmp(mem + n, "CELL_FS_UTILITY:HDD1", 20) == 0 
		&& memcmp(mem + n + 0x69, "dev_hdd1", 8) != 0 
		//&& mem[n-9 ]==1 
		//&& mem[n-13]==1 
		)
		{
			print_load("Unpatch HDD1");
			lv2poke(LV2MOUNTADDR + n + 0x68		, dev_hdd1[0]);
			lv2poke(LV2MOUNTADDR + n + 0x68 + 8	, dev_hdd1[1]);
			lv2poke(LV2MOUNTADDR + n + 0x78		, 0ULL);
			lv2poke(LV2MOUNTADDR + n + 0x78 + 8	, 0ULL);
		} else
		*/
		if(memcmp(mem + n, "CELL_FS_IOS:PATA0_BDVD_DRIVE", 28) == 0
		&& memcmp(mem + n + 0x69, "dev_bdvd", 8) != 0
		//&& memcmp(mem + n + 0x69, "temp_bdvd", 9) != 0
		//&& mem[n-9 ]==1 
		//&& mem[n-13]==1 
		)
		{
			print_load("Unpatch BDVD");
			lv2poke(LV2MOUNTADDR + n + 0x68		, dev_bdvd[0]);
			lv2poke(LV2MOUNTADDR + n + 0x68 + 8	, dev_bdvd[1]);
			lv2poke(LV2MOUNTADDR + n + 0x78		, 0ULL);
			lv2poke(LV2MOUNTADDR + n + 0x78 + 8	, 0ULL);
		} else 
		if(memcmp(mem + n, "CELL_FS_IOS:USB_MASS_STORAGE", 28)  == 0
		&& memcmp(mem + n + 0x69, "dev_usb", 7) != 0
		//&& mem[n-9 ]==1 
		//&& mem[n-13]==1 
		)
		{
			print_load("Unpatch USB %d", mem[n+30]-0x30);
			dev_usb[1] = mem[n+28]*0x100000000000000 + mem[n+29]*0x1000000000000 +mem[n+30]*0x10000000000 ;
			lv2poke(LV2MOUNTADDR + n + 0x68, dev_usb[0]);
			lv2poke(LV2MOUNTADDR + n + 0x68 + 8, dev_usb[1]);
			lv2poke(LV2MOUNTADDR + n + 0x78		, 0ULL);
			lv2poke(LV2MOUNTADDR + n + 0x78 + 8	, 0ULL);
		} else 
		if(memcmp(mem + n, "CELL_FS_UTILITY:HDD0", 20) == 0
		&& memcmp(mem + n + 0x48, "CELL_FS_UFS", 11) == 0
		&& memcmp(mem + n + 0x69, "dev_hdd0", 8) != 0 
		//&& mem[n-9 ]==1 
		//&& mem[n-13]==1 
		)
		{
			print_load("Unpatch HDD0");
			dat = lv2peek(0x80000000007EF020ULL);
			lv2poke(LV2MOUNTADDR + n - 0x10, dat);
			for(m=0; m < (u64) LV2MOUNTADDR_CSIZE; m+=8) {
				dat = lv2peek(0x80000000007EF030ULL + m);
				lv2poke(LV2MOUNTADDR+n+m, dat);
			}
			
			for(m=0; m < (u64) LV2MOUNTADDR_ESIZE + 0x30; m+=8) {
				lv2poke(0x80000000007EF000ULL + m, 0ULL);
			}
		
		}
	}
	for(n= 0; n < 100; n++) {
		lv2poke32(UMOUNT_SYSCALL_OFFSET, 0xFBA100E8); // UMOUNT RESTORE
		usleep(1000);
	}
	
	lv2poke(0x80000000007EF000ULL, 0ULL);
}

int patch_libfs(int8_t device)
{
	unsigned char compare[16]= {
	/*00*/	0x88,0x09,0x00,0x00,0x7C,0x00,0x07,0x74, 	0x2F,0x80,0x00,0x00, 0x2F,0x00,0x00,0x2F
	};

	unsigned char patch_from_reactPSN[0xA8]= { // -0x68
	/*00*/	0x2B,0x83,0x00,0x01,0x40,0x9D,0x00,0x84,	0x88,0x1F,0x00,0x00,0x2F,0x80,0x00,0x2F,
	/*10*/	0x40,0x9E,0x00,0x78,0x7B,0xDF,0x00,0x20,	0x7F,0xA4,0xEB,0x78,0x7F,0xE3,0xFB,0x78,
	/*20*/	0x48,0x00,0x21,0x75,0xE8,0x41,0x00,0x28,	0x7B,0xC9,0x00,0x20,0x38,0x60,0x00,0x00,
	/*30*/	0x88,0x09,0x00,0x09,0x2F,0x80,0x00,0x2F,	0x40,0x9E,0x00,0x08,0x98,0x69,0x00,0x09,	
	/*40*/	0x88,0x09,0x00,0x0A,0x2F,0x80,0x00,0x2F,	0x40,0x9E,0x00,0x08,0x98,0x69,0x00,0x0A,
	/*50*/	0x88,0x09,0x00,0x0B,0x2F,0x80,0x00,0x2F,	0x40,0x9E,0x00,0x08,0x98,0x69,0x00,0x0B,
	/*60*/	0x88,0x09,0x00,0x07,0x2F,0x80,0x00,0x76,	0x40,0x9E,0x00,0x1C,0x3C,0x60,0x5F,0x75,
	/*70*/	0x60,0x63,0x73,0x62,0x78,0x63,0x00,0x02,	0x64,0x63,0x30,0x30,0x60,0x63,0x30,0x00,
	/*80*/	0xF8,0x69,0x00,0x04,0x39,0x20,0x00,0x00,	0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,			
	/*90*/	0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,	0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,
	/*A0*/	0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00
	};

	unsigned char patch_from_iris[0xB4] = { //-0x20
	/*00*/	0x7C,0x1E,0xEA,0x14,0x78,0x09,0x00,0x20,	0x88,0x09,0x00,0x06,0x7C,0x00,0x07,0x74,
	/*10*/	0x2F,0x80,0x00,0x6D,0x41,0x9E,0x00,0x18,	0x2F,0x80,0x00,0x76,0x41,0x9E,0x00,0x10,
	/*20*/	0x2F,0x80,0x00,0x62,0x41,0x9E,0x00,0x2C,	0x48,0x00,0x00,0x48,0x38,0x00,0x00,0x68,
	/*30*/	0x98,0x09,0x00,0x04,0x38,0x00,0x00,0x64,	0x98,0x09,0x00,0x05,0x98,0x09,0x00,0x06,
	/*40*/	0x38,0x00,0x00,0x30,0x98,0x09,0x00,0x07,	0x38,0x00,0x00,0x00,0x98,0x09,0x00,0x08,
	/*50*/	0x38,0x00,0x00,0x00,0x98,0x09,0x00,0x0A,	0x60,0x00,0x00,0x00,0x39,0x20,0x00,0x00,
	/*60*/	0x4B,0xFF,0xFF,0x18,0x38,0x60,0x00,0x00,	0x7C,0x63,0x07,0xB4,0x4E,0x80,0x00,0x20,
	/*70*/	0x2F,0x80,0x00,0x00,0x41,0x9E,0xFF,0xE8,	0x2F,0x80,0x00,0x2F,0x40,0x9E,0x00,0x10,
	/*80*/	0x38,0x00,0x00,0x00,0x98,0x09,0x00,0x06,	0x4B,0xFF,0xFF,0xD4,0x88,0x09,0x00,0x08,
	/*90*/	0x7C,0x00,0x07,0x74,0x2F,0x80,0x00,0x2F,	0x41,0x9E,0xFF,0xB0,0x2F,0x80,0x00,0x00,
	/*A0*/	0x41,0x9E,0xFF,0xBC,0x38,0x00,0x00,0x00,	0x98,0x09,0x00,0x09,0x4B,0xFF,0xFF,0xA4,
	/*B0*/	0x60,0x00,0x00,0x00
	};
	
	unsigned char patch_from_MM[0x84] = { // -0x20
	/*00*/	0x7C,0x1E,0xEA,0x14,0x78,0x09,0x00,0x20,	0x38,0x60,0x00,0x00,0x88,0x09,0x00,0x08,
	/*10*/	0x2F,0x80,0x00,0x2F,0x40,0x9E,0x00,0x08,	0x98,0x69,0x00,0x08,0x88,0x09,0x00,0x09, 
	/*20*/	0x2F,0x80,0x00,0x2F,0x40,0x9E,0x00,0x08,	0x98,0x69,0x00,0x09,0x88,0x09,0x00,0x0A, 
	/*30*/	0x2F,0x80,0x00,0x2F,0x40,0x9E,0x00,0x08,	0x98,0x69,0x00,0x0A,0x88,0x09,0x00,0x06,
	/*40*/	0x2F,0x80,0x00,0x76,0x41,0x9E,0x00,0x0C,	0x2F,0x80,0x00,0x6D,0x40,0x9E,0x00,0x30,
	/*50*/	0x3C,0x60,0x75,0x73,0x60,0x63,0x62,0x30,	0x78,0x63,0xF8,0x00,0x78,0x63,0x08,0x00,
	/*60*/	0x48,0x00,0x00,0x10,0x38,0x60,0x00,0x00,	0x7C,0x63,0x07,0xB4,0x4E,0x80,0x00,0x20,
	/*70*/	0x64,0x63,0x30,0x30,0x60,0x63,0x00,0x00,	0xF8,0x69,0x00,0x04,0x39,0x20,0x00,0x00,
	/*80*/	0x4B,0xFF,0xFE,0xF8
	};
	
	FILE* fp;
	char patched_libfs_from_MM[128];
	char patched_libfs_from_iris[128];
	char patched_libfs_from_reactPSN[128];
	
	sprintf(patched_libfs_from_iris, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_from_iris_%X.sprx", ManaGunZ_id, firmware);
	
	if(device<0) {
		sprintf(patched_libfs_from_MM, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_int_from_MM_%X.sprx", ManaGunZ_id, firmware);
		sprintf(patched_libfs_from_reactPSN, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_int_from_reactPSN_%X.sprx", ManaGunZ_id, firmware);
	}
	else {
		sprintf(patched_libfs_from_MM, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_usb%d_from_MM_%X.sprx", ManaGunZ_id, device, firmware);
		sprintf(patched_libfs_from_reactPSN, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_usb%d_from_reactPSN_%X.sprx", ManaGunZ_id, device, firmware);
	}
	
	if(path_info(patched_libfs_from_MM) == _NOT_EXIST) {
		print_load("Apply MM patch to libfs...");
		char ori_sprx[128];
		char ori_prx[128];
		char patched_prx[128];
		
		sprintf(ori_sprx, "/dev_hdd0/game/%s/USRDIR/sys/original_libfs_%X.sprx", ManaGunZ_id, firmware);
		sprintf(ori_prx, "/dev_hdd0/game/%s/USRDIR/sys/original_libfs_%X.prx", ManaGunZ_id, firmware);
		sprintf(patched_prx, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_from_MM_%X.prx", ManaGunZ_id, firmware);
		
		if(CopyFile("/dev_flash/sys/external/libfs.sprx", ori_sprx) != SUCCESS) {
			print_load("Error : can't copy original sprx");
			return NOK;
		}

		if(Extract(ori_sprx, ori_prx)==NOK) {
			return NOK;
		}
		
		int size;
		
		char *data = LoadFile(ori_prx, &size);
		if(data==NULL) {
			print_load("Error : can't read the original libfs");
			return NOK;
		}
		
		//patch
		int m=0, n;
		for(n = 0; n < size - 16; n++) {
			if(!memcmp((char *) &data[n], (char *) compare, 16)) {		
				m=n;
				break;
			}
		}
		if(m==0) {
			print_load("Error : cannot find the flag to apply the patch");
			return FAILED;
		}
		if(device<0) {
			patch_from_MM[0x52]=0x68;
			patch_from_MM[0x53]=0x64;
			patch_from_MM[0x56]=0x64;
			patch_from_MM[0x73]=0x00;
			patch_from_MM[0x72]=0x00;
		} 
		else patch_from_MM[0x73]=0x30+device;
		
		memcpy(&data[n-0x20], patch_from_MM, 0x84);
	
		//write
		if( SaveFile(patched_prx, data, size) == FAILED) 
		{
			free(data);
			print_load("Error : cannot create the file");
			return NOK;
		}
		
		if(Sign_PRX(patched_prx, patched_libfs_from_MM) == NOK) {
			print_load("Error : cannot sign the prx\n");
			return NOK;
		}
	
		Delete(ori_sprx);
		Delete(ori_prx);
		Delete(patched_prx);
	}
	
	if(path_info(patched_libfs_from_iris) == _NOT_EXIST) {
		print_load("Apply IRIS patch to libfs...");
		char ori_sprx[128];
		char ori_prx[128];
		char patched_prx[128];
		
		sprintf(ori_sprx, "/dev_hdd0/game/%s/USRDIR/sys/original_libfs_%X.sprx", ManaGunZ_id, firmware);
		sprintf(ori_prx, "/dev_hdd0/game/%s/USRDIR/sys/original_libfs_%X.prx", ManaGunZ_id, firmware);
		sprintf(patched_prx, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_from_iris_%X.prx", ManaGunZ_id, firmware);
		
		if(CopyFile("/dev_flash/sys/external/libfs.sprx", ori_sprx) != SUCCESS) {
			print_load("Error : can't copy original sprx");
			return NOK;
		}

		if(Extract(ori_sprx, ori_prx)==NOK) {
			return NOK;
		}
		
		char *data;
		long size;
		size_t result;
		fp = fopen(ori_prx, "rb");
		if(fp!=NULL) {
			fseek (fp , 0 , SEEK_END);
			size = ftell (fp);
			fseek(fp, 0, SEEK_SET);
			
			data = (char*) malloc (sizeof(char)*size);
			if (data == NULL) {
				free(data); 
				fclose(fp);
				print_load("Error : failed to malloc data");
				return NOK;
			}
				
			result = fread(data, 1, size, fp);
			if (result != size) {
				free (data);
				fclose (fp); 
				print_load("Error : Failed to read data");
				return NOK;
			}
			fclose (fp);
				
		} else {
			print_load("Error : can't read the original libfs");
			return NOK;
		}
		
		//patch
		int m=0, n;
		for(n = 0; n < size - 16; n++) {
			if(!memcmp((char *) &data[n], (char *) compare, 16)) {		
				m=n;
				break;
			}
		}
		if(m==0) {
			print_load("Error : cannot find the flag to apply the patch");
			return FAILED;
		}
		
		memcpy(&data[n-0x20], patch_from_iris, 0xB4);
		
		// to skip "li	  %r9, 0; b ...."
		// memcpy(&data[m], patch_from_iris, 0x5c);
		// memcpy(&data[m + 0x64], patch_from_iris + 0x64, 0xB4 - 0x64);
		
		//write
		fp = fopen(patched_prx, "wb");
		if(fp==NULL){
			free(data);
			fclose(fp);
			print_load("Error : cannot create the file");
			return NOK;
		}
		result = fwrite(data, 1, size, fp);
		if(result != size) {
			free(data);
			fclose(fp);
			print_load("Error : cannot write the file\n");
			return NOK;
		}
		fclose(fp);
		free(data);
		
		if(Sign_PRX(patched_prx, patched_libfs_from_iris) == NOK) {
			print_load("Error : cannot sign the prx\n");
			return NOK;
		}
	
		Delete(ori_sprx);
		Delete(ori_prx);
		Delete(patched_prx);
	}
	
	if(path_info(patched_libfs_from_reactPSN) == _NOT_EXIST) {
		print_load("Apply reactPSN patch to libfs...");
		char ori_sprx[128];
		char ori_prx[128];
		char patched_prx[128];

		
		sprintf(ori_sprx, "/dev_hdd0/game/%s/USRDIR/sys/original_libfs_%X.sprx", ManaGunZ_id, firmware);
		sprintf(ori_prx, "/dev_hdd0/game/%s/USRDIR/sys/original_libfs_%X.prx", ManaGunZ_id, firmware);
		sprintf(patched_prx, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_from_reactPSN_%X.prx", ManaGunZ_id, firmware);
		
		if(CopyFile("/dev_flash/sys/external/libfs.sprx", ori_sprx) != SUCCESS) {
			print_load("Error : can't copy original sprx");
			return NOK;
		}

		if(Extract(ori_sprx, ori_prx)==NOK) {
			return NOK;
		}
		
		char *data;
		long size;
		size_t result;
		fp = fopen(ori_prx, "rb");
		if(fp!=NULL) {

			fseek (fp , 0 , SEEK_END);
			size = ftell (fp);
			fseek(fp, 0, SEEK_SET);
			
			data = (char*) malloc (sizeof(char)*size);
			if (data == NULL) {
				free(data); 
				fclose(fp);
				print_load("Error : failed to malloc data");
				return NOK;
			}
				
			result = fread(data, 1, size, fp);
			if (result != size) {
				free (data);
				fclose (fp); 
				print_load("Error : Failed to read data");
				return NOK;
			}
			fclose (fp);
				
		} else {
			print_load("Error : can't read the original libfs");
			return NOK;
		}
		
		//patch
		int m=0, n;
		for(n = 0; n < size - 16; n++) {
			if(!memcmp((char *) &data[n], (char *) compare, 16)) {		
				m=n;
				break;
			}
		}
		if(m==0) {
			print_load("Error : cannot find the flag to apply the patch");
			return FAILED;
		}
		
		if(device<0) {
			patch_from_reactPSN[0x6F]=0x68;
			patch_from_reactPSN[0x72]=0x64;
			patch_from_reactPSN[0x73]=0x64;
			patch_from_reactPSN[0x7B]=0x00;
			patch_from_reactPSN[0x7E]=0x00;
		}
		else {
			patch_from_reactPSN[0x7E]=0x30+device;
		}
		memcpy(&data[n-0x68], patch_from_reactPSN, 0xA8);
		
		//write
		fp = fopen(patched_prx, "wb");
		if(fp==NULL){
			free(data);
			fclose(fp);
			print_load("Error : cannot create the file");
			return NOK;
		}
		result = fwrite(data, 1, size, fp);
		if(result != size) {
			free(data);
			fclose(fp);
			print_load("Error : cannot write the file\n");
			return NOK;
		}
		fclose(fp);
		free(data);
		
		if(Sign_PRX(patched_prx, patched_libfs_from_reactPSN) == NOK) {
			print_load("Error : cannot sign the prx\n");
			return NOK;
		}
	
		Delete(ori_sprx);
		Delete(ori_prx);
		Delete(patched_prx);
	}
	
	return OK;
}

char *get_libfs_path() 
{
	int device;
	char *libfs_path = (char*) malloc(sizeof(char)*128);
	
	if(strstr(GamPath, "/dev_usb")) {
		device=(GamPath[8]-0x30)*100 + (GamPath[9]-0x30)*10 + GamPath[10]-0x30;		
	}
	else device=-1;
		
	if(libfs_from == IRIS) {
		sprintf(libfs_path, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_from_iris_%X.sprx", ManaGunZ_id, firmware);
	}
	else if(libfs_from == MM) {
		if(device==-1) {
			sprintf(libfs_path, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_int_from_MM_%X.sprx", ManaGunZ_id, firmware);
		}
		else {
			sprintf(libfs_path, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_usb%d_from_MM_%X.sprx", ManaGunZ_id, device, firmware);
		}
	} else if(libfs_from == REACTPSN) {
		if(device==-1) {
			sprintf(libfs_path, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_int_from_reactPSN_%X.sprx", ManaGunZ_id, firmware);
		}
		else {
			sprintf(libfs_path, "/dev_hdd0/game/%s/USRDIR/sys/patched_libfs_usb%d_from_reactPSN_%X.sprx", ManaGunZ_id, device, firmware);
		}
	}
	
	patch_libfs(device);
	
	return libfs_path;
}

int patch_exp_plug()
{
	FILE* fp;
	char patched_sprx[128];
	
	sprintf(patched_sprx, "/dev_hdd0/game/%s/USRDIR/sys/patched_explore_plugin_%X.sprx", ManaGunZ_id, firmware);
	
	if(path_info(patched_sprx) == _NOT_EXIST) {
		print_load("Patching explore_pluging...");
		char ori_sprx[128];
		char ori_prx[128];
		char patched_prx[128];
		int k;
		
		sprintf(ori_sprx, "/dev_hdd0/game/%s/USRDIR/sys/original_explore_plugin_%X.sprx", ManaGunZ_id, firmware);
		sprintf(ori_prx, "/dev_hdd0/game/%s/USRDIR/sys/original_explore_plugin_%X.prx", ManaGunZ_id, firmware);
		sprintf(patched_prx, "/dev_hdd0/game/%s/USRDIR/sys/patched_explore_plugin_%X.prx", ManaGunZ_id, firmware);
		
		if(CopyFile("/dev_flash/vsh/module/explore_plugin.sprx", ori_sprx) != SUCCESS) {
			print_load("Error : can't copy original sprx");
			return NOK;
		}

		if(Extract(ori_sprx, ori_prx)==NOK) {
			return NOK;
		}
		
		char *data;
		long size;
		size_t result;
		
		fp = fopen(ori_prx, "rb");
		if(fp!=NULL) {

			fseek (fp , 0 , SEEK_END);
			size = ftell (fp);
			fseek(fp, 0, SEEK_SET);
			
			data = (char*) malloc (sizeof(char)*size);
			if (data == NULL) {
				free(data); 
				fclose(fp);
				print_load("Error : failed to malloc data");
				return NOK;
			}
				
			result = fread(data, 1, size, fp);
			if (result != size) {
				free (data);
				fclose (fp); 
				print_load("Error : Failed to read data");
				return NOK;
			}
			fclose (fp);
				
		} else {
			print_load("Error : can't read the original explore_plugin.prx");
			return NOK;
		}
		
		//patch
		int n;
		for(n = 0; n < size - 16; n++) {
			if(!memcmp((char *) &data[n], (char *) "/app_home", 9)) {
				memcpy(&data[n], "/dev_bdvd", 9);
				n+=8;
			}
			
			if(!memcmp((char *) &data[n], (char *) "msg_tool_app_home_ps3_game", 27)) {			
				memcpy(&data[n], "msg_playstation3\0\0\0\0\0\0\0\0\0\0", 26);
				//memcpy(&data[n], "msg_playstation3\0", 18);
				
				for(k = n - 256; k < n + 256; k++) {
					if(!memcmp((char *) &data[k], (char *) "tex_album_icon", 15)) {
						memcpy(&data[k], "item_tex_disc_bd", 16);
						memcpy(&data[k+16], "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16); //reactPSN
					}
				}
				n+=27;
			}
		}
		
		//write
		fp = fopen(patched_prx, "wb");
		if(!fp){
			free(data);
			fclose(fp);
			print_load("Error : cannot create the file");
			return NOK;
		}
		result = fwrite(data, 1, size, fp);
		if(result != size) {
			free(data);
			fclose(fp);
			print_load("Error : cannot write the file");
			return NOK;
		}
		fclose(fp);
		free(data);
		
		if(Sign_PRX(patched_prx, patched_sprx) == NOK) {
			return NOK;
		}
	
		Delete(ori_sprx);
		Delete(ori_prx);
		Delete(patched_prx);
	}
	
	return OK;
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
	
	FILE* f = fopen(ret, "wb");
	if(f==NULL) {
		free(buf);
		free(ret);
		return NULL;
	}
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

void mount_fake_BR()
{
	int ret;
	unsigned int real_disctype;

	cobra_get_disc_type(&real_disctype, NULL, NULL);
	
	if (real_disctype == DISC_TYPE_NONE)
	{
		print_load("mount Fake BR");
		char *files[1];
		char *blank_iso = build_blank_iso("TEST00000");
		
		if (blank_iso)
		{
			files[0] = blank_iso;			
			ret = cobra_mount_ps3_disc_image(files, 1);
			free(blank_iso);
			
			if (ret == 0)
			{
				cobra_send_fake_disc_insert_event();
			}
		}
	}
}

u8 ISOtype(char *isoPath)
{
	FILE* f;
	f = fopen(isoPath, "rb");			
	if(f==NULL) {
		//print_load("Error : failed to open %s", isoPath);
		return NO;
	}
	
	u32 SectSize=0;
	u32 JP=0;
	
	if( get_SectorSize(f, &SectSize, &JP) == FAILED) { 
		fclose(f);
		return _ISO;
	}
	
	char *mem =  (char *) malloc(0x40);
	if(mem==NULL) {
		fclose(f);
		//print_load("Error : malloc failed");
		return NO;
	}
	memset(mem, 0, sizeof(mem));
	fseek(f, SectSize*0x10+JP, SEEK_SET);

	fread(mem, 1, 0x40, f);
		
	if(!memcmp((char *) &mem[0x28], (char *) "PS3VOLUME", 0x9)) {
		free(mem);
		fclose(f);
		return _ISO_PS3;
	}
	if(!memcmp((char *) &mem[0x8], (char *) "PSP GAME", 0x8)) {
		free(mem);
		fclose(f);
		return _ISO_PSP;
	}
/* bad idea : bin/cue PS2 exist too..
	if(!memcmp((char *) &mem[0x8], (char *) "PLAYSTATION", 0xB)) {
		free(mem);
		fclose(f);
		if(JP==0) return _ISO_PS2; 
		else	  return _ISO_PS1;
	}
*/
	free(mem);
	fclose(f);
	
	int file_size;
	
	mem = LoadFileFromISO(NO, isoPath, "SYSTEM.CNF", &file_size);
	if( mem != NULL ) {
		if(strstr(mem, "BOOT2") != NULL) {
			free(mem);
			return _ISO_PS2;
		} else
		if(strstr(mem, "BOOT") != NULL) {
			free(mem);
			return _ISO_PS1;
		} else {
			free(mem);
			return _ISO;
		}
	}

	mem = LoadFileFromISO(NO, isoPath, "/PS3_GAME/PARAM.SFO", &file_size);
	if( mem != NULL ) {
		free(mem);
		return _ISO_PS3;
	}
	mem = LoadFileFromISO(NO, isoPath, "/PSP_GAME/PARAM.SFO", &file_size);
	if( mem != NULL ) {
		free(mem);
		return _ISO_PSP;
	}
	
	return _ISO;
	
}

u8 can_read(u8 ext)
{
	if(	   ext == _TXT 
		|| ext == _XML 
		|| ext == _JS
		|| ext == _MD5
		|| ext == _SHA1
		|| ext == _LOG
		|| ext == _INI
		|| ext == _NFO
	) return YES;
	
	return NO;
}

u8 get_ext(char *file)
{
	char file_name[128];
	
	u8 is_path=NO;
	
	if(strstr(file, "/")) is_path=YES;
	
	if(is_path==YES) {
		if(path_info(file) == _DIRECTORY)  {
			char temp[255];
			sprintf(temp, "%s/PS3_GAME/PARAM.SFO", file);
			if(path_info(temp) == _FILE) return _JB_PS3;
			sprintf(temp, "%s/PSP_GAME/PARAM.SFO", file);
			if(path_info(temp) == _FILE) return _JB_PSP;
			sprintf(temp, "%s/SYSTEM.CNF", file);
			if(path_info(temp) == _FILE) {
				FILE* f;
				f=fopen(temp, "rb");
				if(f!=NULL) {
					fgets(temp, 128, f);
					strtok(temp, " =");
					fclose(f);
					if(!strcmp(temp, "BOOT2")) return _JB_PS2; else
					if(!strcmp(temp, "BOOT")) return _JB_PS1;
				}
				return _FILE;
			}
			return _DIRECTORY;
		}
		strcpy(file_name, &strrchr(file, '/')[1]);
	} else strcpy(file_name, file);
	
	char *ext = GetExtention(file_name);
	if(ext==NULL) return _FILE;
	
	if (!strcmp(file_name, "xRegistry.sys")) {
		return _XREG;
	} else
	if (!strcmp(ext, ".66600")) {
		return _66600;
	} else
	if (!strcmp(ext, ".TTF") || !strcmp(ext, ".ttf")) {
		return _TTF;
	} else
	if (!strcmp(ext, ".JPG") || !strcmp(ext, ".jpg")) {
		return _JPG;
	} else
	if (!strcmp(ext, ".PNG") || !strcmp(ext, ".png")) {
		return _PNG;
	} else 
	if (!strcmp(ext, ".P3T") || !strcmp(ext, ".p3t")) {
		return _P3T;
	} else 
	if (!strcmp(ext, ".THM") || !strcmp(ext, ".thm")) {
		return _THM;
	} else 
	if (!strcmp(ext, ".RAF") || !strcmp(ext, ".raf")) {
		return _RAF;
	} else
	if (!strcmp(ext, ".JSX") || !strcmp(ext, ".jsx")) {
		return _JSX;
	} else
	if (!strcmp(ext, ".JS") || !strcmp(ext, ".js")) {
		return _JS;
	} else
	if (!strcmp(ext, ".MD5") || !strcmp(ext, ".md5")) {
		return _MD5;
	} else
	if (!strcmp(ext, ".SHA1") || !strcmp(ext, ".sha1")) {
		return _SHA1;
	} else
	if (!strcmp(ext, ".NFO") || !strcmp(ext, ".nfo")) {
		return _NFO;
	} else
	if (!strcmp(ext, ".LOG") || !strcmp(ext, ".log")) {
		return _LOG;
	} else
	if (!strcmp(ext, ".INI") || !strcmp(ext, ".ini")) {
		return _INI;
	} else
	if (!strcmp(ext, ".VAG") || !strcmp(ext, ".vag")) {
		return _VAG;
	} else
	if (!strcmp(ext, ".QRC") || !strcmp(ext, ".qrc")) {
		return _QRC;
	} else 
	if (!strcmp(file_name, "EBOOT.ELF") || !strcmp(file_name, "EBOOT.elf")) {
		return _EBOOT_ELF;
	} else 
	if (!strcmp(file_name, "EBOOT.BIN")) {
		return _EBOOT_BIN;
	} else 
	if (!strcmp(ext, ".SELF") || !strcmp(ext, ".self")) {
		return _SELF;
	} else 
	if (!strcmp(ext, ".ELF") || !strcmp(ext, ".elf")) {
		return _ELF;
	} else
	if (!strcmp(ext, ".TXT") || !strcmp(ext, ".txt")) {
		return _TXT;
	} else 
	if (!strcmp(ext, ".XML") || !strcmp(ext, ".xml")) {
		return _XML;
	} else 
	if (!strcmp(ext, ".SPRX") || !strcmp(ext, ".sprx")) {
		return _SPRX;
	} else
	if (!strcmp(ext, ".PRX") || !strcmp(ext, ".prx")) {
		return _PRX;
	} else
	if (!strcmp(ext, ".PKG") || !strcmp(ext, ".pkg")) {
		return _PKG;
	} else 
	if (!strcmp(ext, ".TRP") || !strcmp(ext, ".trp")) {
		return _TRP;
	} else 
	if (!strcmp(ext, ".SFO") || !strcmp(ext, ".sfo")) {
		return _SFO;
	} else 
	if (!strcmp(ext, ".RCO") || !strcmp(ext, ".rco")) {
		return _RCO;
	} else 
	if (!strcmp(ext, ".CSO") || !strcmp(ext, ".cso")) {
		return _CSO;
	} else
	if (is_iso(file)==YES) {
		if(is_path == YES) return ISOtype(file);
		return _ISO;
	} else 
	if (!strcmp(ext, ".GTF") || !strcmp(ext, ".gtf")) {
		return _GTF;
	} else 
	if (!strcmp(ext, ".DDS") || !strcmp(ext, ".dds")) {
		return _DDS;
	}  else 
	if (!strcmp(ext, ".ZIP") || !strcmp(ext, ".zip")) {
		return _ZIP;
	} 
	
	return _FILE;
}

//*******************************************************
//Iris Mount Game
//*******************************************************

void reset_sys8_path_table()
{
	while(ntable > 0) {
		if(table_compare[ntable - 1]) free(table_compare[ntable - 1]);
		if(table_replace[ntable - 1]) free(table_replace[ntable - 1]);
		ntable --;
	}
}

void add_sys8_path_table(char * compare, char * replace)
{
	if(ntable >= 16) return;

	table_compare[ntable] = malloc(strlen(compare) + 1);
	if(!table_compare[ntable]) return;
	strncpy(table_compare[ntable], compare, strlen(compare) + 1);
	
	table_replace[ntable] = malloc(strlen(replace) + 1);
	if(!table_replace[ntable]) return;
	strncpy(table_replace[ntable], replace, strlen(replace) + 1);

	ntable++;

	table_compare[ntable] = NULL;
}

void add_sys8_bdvd(char * bdvd, char * app_home)
{
	static char compare1[]="/dev_bdvd";
	static char compare2[]="/app_home";
	static char replace1[0x420];
	static char replace2[0x420];
	int pos = 17;

	table_compare[pos] = NULL;
	table_compare[pos + 1] = NULL;

	if(bdvd) {
		strncpy(replace1, bdvd, 0x420);
		table_compare[pos] = compare1;
		table_replace[pos] = replace1;
		pos++;
	}
	
	if(app_home) {
		strncpy(replace2, app_home, 0x420);
		table_compare[pos] = compare2;
		table_replace[pos] = replace2;
		pos++;
	}
	
}

void build_sys8_path_table()
{

	path_open_entry *pentries;

	int entries = 0;

	int arena_size = 0;

	int n, m;

	sys8_path_table(0LL);

	if(ntable <= 0 && !table_compare[17] && !table_compare[18]) return;
	if(ntable <= 0) {table_compare[0] = 0; ntable = 0;}

	while(ntable>0 && table_compare[entries] != NULL) entries++;

	// /dev_bdvd & /app_home entries
	if(table_compare[17]) {
		table_compare[entries] = table_compare[17]; 
		table_replace[entries] = table_replace[17];
		entries++;
	}

	if(table_compare[18]) {
		table_compare[entries] = table_compare[18];
		table_replace[entries] = table_replace[18];
		entries++;
	}

	table_compare[entries] = NULL;

	entries = 0;

	while(table_compare[entries] != NULL) {
		int l = strlen(table_compare[entries]);

		arena_size += 0x420;
		for(m = 0x80; m <= 0x420; m += 0x20)
			if(l < m) {arena_size += m;break;}

	entries++;
	}


	if(!entries) return;

	char * datas = memalign(16, arena_size + sizeof(path_open_entry) * (entries + 2));
	
	if(!datas) return;

	u64 dest_table_addr = 0x80000000007FE000ULL - (u64)((arena_size + sizeof(path_open_entry) * (entries + 1) + 15) & ~15);

	u32 arena_offset = (sizeof(path_open_entry) * (entries + 1));

	pentries = (path_open_entry *) datas;

	for(n = 0; n < entries; n++) {
	
		int l = strlen(table_compare[n]);

		int size = 0;
		for(m = 0x80; m <= 0x420; m += 0x20)
			if(l < m) {size += m; break;}

		pentries->compare_addr = dest_table_addr + (u64) (arena_offset);

		pentries->replace_addr = dest_table_addr + (u64) (arena_offset + size);
		

		strncpy(&datas[arena_offset], table_compare[n], size);
		strncpy(&datas[arena_offset + size], table_replace[n], 0x420);

		pentries->compare_len = strlen(&datas[arena_offset]);
		pentries->replace_len = strlen(&datas[arena_offset + size]);

		arena_offset += size + 0x420;
		pentries ++;
	   
	}
	
	pentries->compare_addr = 0ULL;

	sys8_memcpy(dest_table_addr, (u64) datas, (u64) (arena_size + sizeof(path_open_entry) * (entries + 1)));

	free(datas);

	reset_sys8_path_table();

	// set the path table
	sys8_path_table( dest_table_addr);
}

static inline void lv2_memcpy( u64 to, u64 from, size_t sz)
{
	lv2syscall3(NEW_POKE_SYSCALL, to, from, sz);
}

static inline void lv2_memset( u64 dst, const u64 val, size_t sz)
{
	u64 *tmp = memalign(32, (sz*(sizeof(u64))) );
	if(!tmp)
		return;

	memset(tmp, val, sz);
	
	lv2syscall3(NEW_POKE_SYSCALL, dst, (u64) tmp, sz);

	free(tmp);
}

static inline void install_lv2_memcpy()
{
	int n;

	for(n = 0; n < 50; n++) {
	/* install memcpy */
	/* This does not work on some PS3s */
		lv2poke(NEW_POKE_SYSCALL_ADDR, 0x4800000428250000ULL);
		lv2poke(NEW_POKE_SYSCALL_ADDR + 8, 0x4182001438a5ffffULL);
		lv2poke(NEW_POKE_SYSCALL_ADDR + 16, 0x7cc428ae7cc329aeULL);
		lv2poke(NEW_POKE_SYSCALL_ADDR + 24, 0x4bffffec4e800020ULL);
		usleep(5000);
	}
}

static inline void remove_lv2_memcpy()
{
	int n;

	for(n = 0; n < 50; n++) {
	/* restore syscall */
	//remove_new_poke();
  
		lv2poke(NEW_POKE_SYSCALL_ADDR, 0xF821FF017C0802A6ULL);
		lv2poke(NEW_POKE_SYSCALL_ADDR + 8, 0xFBC100F0FBE100F8ULL);
		lv2poke(NEW_POKE_SYSCALL_ADDR + 16, 0xEBC2FEB07C7F1B78ULL);
		lv2poke(NEW_POKE_SYSCALL_ADDR + 24, 0x3860032DFBA100E8ULL);
		usleep(5000);
	}
}

void load_payload()
{

	remove_lv2_protection();

	install_lv2_memcpy();

	/* WARNING!! It supports only payload with a size multiple of 8 */
	lv2_memcpy(0x8000000000000000ULL + (u64) PAYLOAD_OFFSET,
				   (u64) PAYLOAD_SKY, 
				   PAYLOAD_SKY_SIZE);

	lv2_memcpy(0x8000000000000000ULL + (u64) PAYLOAD_UMOUNT_OFFSET, // copy umount routine
					  (u64) UMOUNT, 
					  UMOUNT_SIZE);

	//restore_syscall8[0]= SYSCALL_TABLE + 64ULL; // (8*8)
	//restore_syscall8[1]= lv2peek(restore_syscall8[0]);

	u64 id[2];
	// copy the id
	id[0]= 0x534B314500000000ULL | (u64) PAYLOAD_OFFSET;
	id[1] = SYSCALL_TABLE + 64ULL; // (8*8)
	lv2_memcpy(0x80000000000004f0ULL, (u64) &id[0], 16);

	u64 inst8 =  lv2peek(0x8000000000003000ULL);					 // get TOC
	lv2_memcpy(0x8000000000000000ULL + (u64) (PAYLOAD_OFFSET + 0x28), (u64) &inst8, 8);
	inst8 = 0x8000000000000000ULL + (u64) (PAYLOAD_OFFSET + 0x20); // syscall_8_desc - sys8
	lv2_memcpy(SYSCALL_TABLE + (u64) (8 * 8), (u64) &inst8, 8);
	
	usleep(1000);
	
	remove_lv2_memcpy();

	lv2poke(0x80000000007EF000ULL, 0ULL);// BE Emu mount
	lv2poke(0x80000000007EF220ULL, 0ULL);

	fix_error();
	
	PATCH_JUMP	(OPEN_HOOK + 0x24	, (PAYLOAD_OFFSET+0x30));  // lv2poke32	(OPEN_HOOK + 0x24	, 0x4bd63ae0);
	lv2poke32	(OPEN_HOOK			, 0xF821FF61);
	lv2poke		(OPEN_HOOK + 0x8	, 0xFB810080FBA10088ULL);

	PATCH_JUMP	(PERMS_OFFSET		, (PAYLOAD_OFFSET+0x18));
	
}

void iris_Mount()
{
	int ret;
	
	if(cobra) {
		if(prim_USB == YES) SetPrimaryUSB();
		mount_fake_BR();
	}
	
	load_payload();
	__asm__("sync");
	sleep(1);
	
	char temp[128];
	
	if(emu==BDMIRROR) {
		print_load("Patching BD-Mirror");
		ret = patch_bdmirror();
		if( ret != 0) print_load("Error %d: failed to patch bdmirroir", ret);
		sleep(1);
		
		sprintf(temp_buffer, "%s/PS3_DISC.SFB", GamPath);
		add_sys8_path_table("/dev_bdvd/PS3_DISC.SFB", temp_buffer);
		
		add_sys8_bdvd(NULL, NULL);
		
	} else
	if(emu == BDEMU) {
		char *libfs_path = get_libfs_path();
		if(path_info(libfs_path) == _FILE)	add_sys8_path_table("/dev_flash/sys/external/libfs.sprx", libfs_path);
		if(libfs_path) free(libfs_path);
		
		add_sys8_bdvd(GamPath, NULL);
	} else 
	if(emu == NONE) {
		add_sys8_bdvd(GamPath, NULL);
	}
	
	if(mount_app_home == YES) {
		if(emu == BDMIRROR) {
			add_sys8_bdvd(NULL, "/dev_bdvd");
		} else {
			add_sys8_bdvd(GamPath, GamPath);
		}
		
		if(use_ex_plug==YES) {
			if(patch_exp_plug() == SUCCESS) {
				sprintf(temp, "/dev_hdd0/game/%s/USRDIR/sys/patched_explore_plugin_%X.sprx", ManaGunZ_id, firmware);
				if(path_info(temp) == _FILE)	add_sys8_path_table( (char*)"/dev_flash/vsh/module/explore_plugin.sprx", temp);
			} else  print_load("Error : cannot patch explore_plugin.sprx");
		}
	}

	if(ext_game_data==YES) {
		int i;
		for(i=0; i<=device_number; i++) {
			sprintf(temp, "/%s", list_device[i]);
			if(strstr(temp, "/dev_usb")) {
				strcat(temp, "/GAMEI");
				if(path_info(temp)==_NOT_EXIST) mkdir(temp, 0777);
				add_sys8_path_table("/dev_hdd0/game", temp);
			}
		}
	}
	
	build_sys8_path_table();
	
}

//*******************************************************
//multiMan Mount
//*******************************************************

void add_to_map(char *path1, char *path2)
{
	u8 n=0;
	if(max_mapped==0) lv2poke(MAP_BASE + 0x00, 0x0000000000000000ULL);

	if(max_mapped<8)
	{
		for(n=0; n<max_mapped; n++)
		{
			if(!strcmp(file_to_map[n].src, path1)) goto leave;
		}
		sprintf(file_to_map[max_mapped].src, "%s", path1);
		sprintf(file_to_map[max_mapped].dst, "%s", path2);
		max_mapped++;
	}
leave:
	return;
}

void string_to_lv2(char* path, u64 addr)
{
	u16 len=(strlen(path)+8)&0x7f8;
	if(len<8) len=8;
	if(len>384) len=384;
	u16 len2=strlen(path); if(len2>len) len2=len;

	u8 data2[384];
	u8* data = data2;
	memset(data, 0, 384);
	memcpy(data, path, len2);

	u64 val=0x0000000000000000ULL;
	u64 n;
	for(n = 0; n < len; n += 8)
	{
		memcpy(&val, &data[n], 8);
		lv2poke(addr+n, val);
	}
}

void install_MM_payload() 
{
	
	remove_lv2_protection();
	
	fix_error();
	
	u64 sc_600 = lv2peek(SYSCALL_TABLE + (8*600));
	u64 sc_604 = lv2peek(SYSCALL_TABLE + (8*604));
	u64 sc_142 = lv2peek(SYSCALL_TABLE + (8*142));
	
	// restore syscall table  ==> // useless ??
	u64 sc_null = lv2peek(SYSCALL_PTR( 0));
	if(sc_null == lv2peek(SYSCALL_PTR(79)))
	{
		lv2poke(SYSCALL_PTR(  35), sc_null);
		lv2poke(SYSCALL_PTR(  36), sc_null);
		lv2poke(SYSCALL_PTR(  37), sc_null);
		//lv2poke(SYSCALL_PTR(1023), sc_null);

		if(sc_600)
		{
			lv2poke(SYSCALL_PTR(600), sc_600); // sys_storage_open 600
			lv2poke(SYSCALL_PTR(604), sc_604); // sys_storage_send_device_cmd 604
			lv2poke(SYSCALL_PTR(142), sc_142); // sys_timer_sleep 142
		}
	}
	
	// disable mM path table
	lv2poke(0x8000000000000000ULL+MAP_ADDR, 0x0000000000000000ULL);
	lv2poke(0x8000000000000008ULL+MAP_ADDR, 0x0000000000000000ULL);

	// disable Iris path table
	lv2poke(0x80000000007FD000ULL,		   0x0000000000000000ULL);
	
	// restore hook used by all payloads)
	lv2poke(OPEN_HOOK + 0x00, 0xF821FF617C0802A6ULL);
	lv2poke(OPEN_HOOK + 0x08, 0xFB810080FBA10088ULL);
	lv2poke(OPEN_HOOK + 0x10, 0xFBE10098FB410070ULL);
	lv2poke(OPEN_HOOK + 0x18, 0xFB610078F80100B0ULL);
	lv2poke(OPEN_HOOK + 0x20, 0x7C9C23787C7D1B78ULL);
	
	// poke mM payload
	lv2poke(BASE_ADDR + 0x00, 0x7C7D1B783B600001ULL);
	lv2poke(BASE_ADDR + 0x08, 0x7B7BF806637B0000ULL | MAP_ADDR);
	lv2poke(BASE_ADDR + 0x10, 0xEB5B00002C1A0000ULL);
	lv2poke(BASE_ADDR + 0x18, 0x4D820020EBFB0008ULL);
	lv2poke(BASE_ADDR + 0x20, 0xE8BA00002C050000ULL);
	lv2poke(BASE_ADDR + 0x28, 0x418200CC7FA3EB78ULL);
	lv2poke(BASE_ADDR + 0x30, 0xE89A001089640000ULL);
	lv2poke(BASE_ADDR + 0x38, 0x892300005560063EULL);
	lv2poke(BASE_ADDR + 0x40, 0x7F895800409E0040ULL);
	lv2poke(BASE_ADDR + 0x48, 0x2F8000007CA903A6ULL);
	lv2poke(BASE_ADDR + 0x50, 0x409E002448000030ULL);
	lv2poke(BASE_ADDR + 0x58, 0x8964000089230000ULL);
	lv2poke(BASE_ADDR + 0x60, 0x5560063E7F895800ULL);
	lv2poke(BASE_ADDR + 0x68, 0x2F000000409E0018ULL);
	lv2poke(BASE_ADDR + 0x70, 0x419A001438630001ULL);
	lv2poke(BASE_ADDR + 0x78, 0x388400014200FFDCULL);
	lv2poke(BASE_ADDR + 0x80, 0x4800000C3B5A0020ULL);
	lv2poke(BASE_ADDR + 0x88, 0x4BFFFF98E89A0018ULL);
	lv2poke(BASE_ADDR + 0x90, 0x7FE3FB7888040000ULL);
	lv2poke(BASE_ADDR + 0x98, 0x2F80000098030000ULL);
	lv2poke(BASE_ADDR + 0xA0, 0x419E00187C691B78ULL);
	lv2poke(BASE_ADDR + 0xA8, 0x8C0400012F800000ULL);
	lv2poke(BASE_ADDR + 0xB0, 0x9C090001409EFFF4ULL);
	lv2poke(BASE_ADDR + 0xB8, 0xE8BA00087C632A14ULL);
	lv2poke(BASE_ADDR + 0xC0, 0x7FA4EB78E8BA0000ULL);
	lv2poke(BASE_ADDR + 0xC8, 0x7C842A1488040000ULL);
	lv2poke(BASE_ADDR + 0xD0, 0x2F80000098030000ULL);
	lv2poke(BASE_ADDR + 0xD8, 0x419E00187C691B78ULL);
	lv2poke(BASE_ADDR + 0xE0, 0x8C0400012F800000ULL);
	lv2poke(BASE_ADDR + 0xE8, 0x9C090001409EFFF4ULL);
	lv2poke(BASE_ADDR + 0xF0, 0x7FFDFB787FA3EB78ULL);
	lv2poke(BASE_ADDR + 0xF8, 0x4E8000204D4D504CULL); //blr + "MMPL"
	
	lv2poke(MAP_BASE  + 0x00, 0x0000000000000000ULL);
	lv2poke(MAP_BASE  + 0x08, 0x0000000000000000ULL);
	lv2poke(MAP_BASE  + 0x10, 0x8000000000000000ULL);
	lv2poke(MAP_BASE  + 0x18, 0x8000000000000000ULL);

	lv2poke(0x8000000000000000ULL+MAP_ADDR, MAP_BASE);
	lv2poke(0x8000000000000008ULL+MAP_ADDR, 0x80000000007FDBE0ULL);

	lv2poke(OPEN_HOOK + 0x20, (0x7C9C237848000001ULL | (BASE_ADDR-OPEN_HOOK-0x24)));

}

void mm_Mount()
{
	int ret;
	
	if(cobra) {
		if(prim_USB == YES) SetPrimaryUSB();
		mount_fake_BR();
	}
	
	install_MM_payload();
	
	max_mapped=0;
	
	char path[strlen(GamPath)+4];
	sprintf(path, "%s", GamPath);
	char temp[128];
	
	if(emu == BDMIRROR) {
		print_load("Patching BD-Mirror");
		ret = patch_bdmirror();
		if( ret != 0) print_load("Error %d: patch_bdmirror failed", ret);
		sleep(1);

		sprintf(temp, "%s/PS3_DISC.SFB", GamPath);
		add_to_map("/dev_bdvd/PS3_DISC.SFB", temp);
		
	} else
	if(emu == BDEMU) {
		char *libfs_path = get_libfs_path();
		if(path_info(libfs_path) == _FILE)	add_to_map("/dev_flash/sys/external/libfs.sprx", libfs_path);
		if(libfs_path) free(libfs_path);
		
		add_to_map("/dev_bdvd", path);
	} else 
	if(emu==NONE) {
		add_to_map("/dev_bdvd", path);
	}
	
	if(mount_app_home == YES)	{
		if(emu == BDMIRROR) {
			add_to_map("/app_home", "/dev_bdvd");
		} else {
			add_to_map("/app_home", path);
		}
		
		if(use_ex_plug==YES) {
			if(patch_exp_plug() == SUCCESS) {
				sprintf(temp, "/dev_hdd0/game/%s/USRDIR/sys/patched_explore_plugin_%X.sprx", ManaGunZ_id, firmware);
				if(path_info(temp) == _FILE )	add_to_map( (char*)"/dev_flash/vsh/module/explore_plugin.sprx", temp);
			} else  print_load("Error : cannot patch explore_plugin.sprx");
		}
	}

	if(ext_game_data==YES) {
		int i;
		for(i=0; i<=device_number; i++) {
			sprintf(temp, "/%s", list_device[i]);
			if(strstr(temp, "/dev_usb")) {
				strcat(temp, "/GAMEI");
				if(path_info(temp)==_NOT_EXIST) mkdir(temp, 0777);
				add_to_map("/dev_hdd0/game", temp);
			}
		}
	}
	
	u64 map_data  = (MAP_BASE);
	u64 map_paths = (MAP_BASE) + (max_mapped+1) * 0x20;
	u8 n;
	for(n=0; n<32; n++)
	{
		lv2poke(map_data + (n*32) + 0x00, 0);
		lv2poke(map_data + (n*32) + 0x08, 0);
		lv2poke(map_data + (n*32) + 0x10, 0);
		lv2poke(map_data + (n*32) + 0x18, 0);
	}

	if(!max_mapped) return;

	for(n=0; n<max_mapped; n++)
	{
		if(map_paths>0x80000000007FE800ULL) break;
		lv2poke(map_data + (n*32) + 0x10, map_paths);
		string_to_lv2(file_to_map[n].src, map_paths);
		map_paths+= (strlen(file_to_map[n].src)+8)&0x7f8;

		lv2poke(map_data + (n*32) + 0x18, map_paths);
		string_to_lv2(file_to_map[n].dst, map_paths);
		map_paths+= (strlen(file_to_map[n].dst)+8)&0x7f8;

		lv2poke(map_data + (n*32) + 0x08, strlen(file_to_map[n].dst));
		lv2poke(map_data + (n*32) + 0x00, strlen(file_to_map[n].src));
	}
	
	if(path_info("/dev_bdvd") == _NOT_EXIST) sleep(1);

}

//*******************************************************
//Cobra Mount
//*******************************************************

s32 sys_map_path(char *oldpath, char *newpath)
{
	lv2syscall2(35, (uint64_t)oldpath, (uint64_t)newpath);
	return_to_user_prog(s32);
}

int sys_get_version(u32 *version)
{
	lv2syscall2(8, SYSCALL8_OPCODE_GET_VERSION, (u64)version);
	return_to_user_prog(int);
}

u8 is_cobra(void)
{
	u32 version = 0x99999999;
	if (sys_get_version(&version) < 0)	return 0;
	if (version != 0x99999999 && sys8_mamba() != 0x666)	return 1;
	return 0;
}

u8 is_usb(char *file_name)
{
	if(strstr(file_name, "/dev_usb")) return YES;
	return NO;
}

u8 is_iso(char *file_name)
{
	char *Ext = GetExtention(file_name);
	
	if( (Ext[1] == 'I' || Ext[1] == 'i')
	&& 	(Ext[2] == 'S' || Ext[2] == 's')
	&&	(Ext[3] == 'O' || Ext[3] == 'o') )	return YES;
	
	if( (Ext[1] == 'B' || Ext[1] == 'b')
	&& 	(Ext[2] == 'I' || Ext[2] == 'i')
	&&	(Ext[3] == 'N' || Ext[3] == 'n') )	return YES;
	
	if( (Ext[1] == 'M' || Ext[1] == 'm')
	&& 	(Ext[2] == 'D' || Ext[2] == 'd')
	&&	(Ext[3] == 'F' || Ext[3] == 'f') )	return YES;
	
	if( (Ext[1] == 'I' || Ext[1] == 'i')
	&& 	(Ext[2] == 'M' || Ext[2] == 'm')
	&&	(Ext[3] == 'G' || Ext[3] == 'g') )	return YES;
	
	return NO;
}

u8 is_66600(char *file_name)
{
	int l = strlen(file_name);
	
	if( file_name[l-6] == '.'
	&&	file_name[l-5] == '6'
	&&	file_name[l-4] == '6'
	&&	file_name[l-3] == '6'
	&&	file_name[l-2] == '0'
	&&	file_name[l-1] == '0' ) return YES;

	return NO;
}

u8 is_666XX(char *file_name)
{
	if(is_66600(file_name)) return NO;
	
	int l = strlen(file_name);
	
	if( file_name[l-6] == '.'
	&&	file_name[l-5] == '6'
	&&	file_name[l-4] == '6'
	&&	file_name[l-3] == '6') return YES;
	
	return NO;
}

u8 is_splitted_iso(char *file_name)
{
	if(is_iso(file_name) == NO) return NO;
	
	int l = strlen(file_name);
	
	if( file_name[l-2] == '.'
	&&	file_name[l-1] == '0' ) return YES;

	return NO;
}

u8 can_mount()
{
	if(cobra) return YES;
	if(mamba) return YES;
	if(PEEKnPOKE) return YES;
	
	return NO;
}


void cobra_MountISO(int EMU)
{
	int i;

	if(is_ntfs(GamPath)==YES) {
		uint8_t *plugin_args = malloc(0x20000);
		uint32_t *sections = malloc(MAX_SECTIONS * sizeof(uint32_t));
		uint32_t *sections_size = malloc(MAX_SECTIONS * sizeof(uint32_t));
		rawseciso_args *p_args;  
		memset(sections, 0, MAX_SECTIONS * sizeof(uint32_t));
		memset(sections_size, 0, MAX_SECTIONS * sizeof(uint32_t));
		memset(plugin_args, 0, 0x10000);

		int parts = ps3ntfs_file_to_sectors(GamPath, sections, sections_size, MAX_SECTIONS, 1);

		if(is_splitted_iso(GamPath)==YES) {	   
			int o;
			for (o = 1; o < 32; o++) {
				struct stat s;
				sprintf(temp_buffer + 3072, "%s", GamPath);
				temp_buffer[3072 + strlen(temp_buffer + 3072) - 1] = 0;
				sprintf(temp_buffer + 2048, "%s%i", temp_buffer + 3072, o);
				if(parts >= MAX_SECTIONS) break;
				if(stat(temp_buffer + 2048, &s)!=0) break;
				parts += ps3ntfs_file_to_sectors(temp_buffer + 2048, sections + parts, sections_size + parts, MAX_SECTIONS - parts, 1);		   
			}
		}

		if (parts>0 && parts < MAX_SECTIONS) {
			p_args = (rawseciso_args *)plugin_args;
			p_args->device = USB_MASS_STORAGE(NTFS_Test_Device(&GamPath[1]));
			p_args->emu_mode = EMU;
			p_args->num_sections = parts;
			p_args->num_tracks = 0;
			memcpy(plugin_args+sizeof(rawseciso_args), sections, parts*sizeof(uint32_t));
			memcpy(plugin_args+sizeof(rawseciso_args)+(parts*sizeof(uint32_t)), sections_size, parts*sizeof(uint32_t)); 
			cobra_unload_vsh_plugin(0);
			sprintf(temp_buffer + 2048, "/dev_hdd0/game/%s/USRDIR/sys/sprx_iso", ManaGunZ_id);
			if (cobra_load_vsh_plugin(0, temp_buffer + 2048, plugin_args, 0x10000) == 0) return;
		}
	} 
	else {
		char *iso_path[30];
		int nb_iso=0;
		unsigned int effective_disctype, iso_disctype;

		if(is_splitted_iso(GamPath)==YES) {
			GamPath[strlen(GamPath)-1]=0;
			for(i=0; i<32; i++) {
				char temp[128];
				sprintf(temp, "%s%d" , GamPath, i);		
				if(path_info(temp) == _NOT_EXIST) break;
				
				iso_path[i] = malloc(255);
				strcpy(iso_path[i], temp);
				nb_iso++;
			}
		} else {
			iso_path[0] = GamPath;
			nb_iso = 1;
		}
		
		cobra_get_disc_type(NULL, &effective_disctype, &iso_disctype);
		if (effective_disctype != DISC_TYPE_NONE)	{
			cobra_send_fake_disc_eject_event();
			usleep(25000);
		}
		if (iso_disctype != DISC_TYPE_NONE)	{
			cobra_umount_disc_image();
			usleep(25000);
		}
		
		if(EMU == EMU_PS3) {
			cobra_mount_ps3_disc_image(iso_path, nb_iso);
		} else
		if(EMU == EMU_PS2_DVD) {
			TrackDef tracks[1];
			tracks[0].lba = 0;
			tracks[0].is_audio = 0;
			cobra_mount_ps2_disc_image(iso_path, nb_iso, tracks, 1);
		} else 
		if(EMU == EMU_PSX) {
			TrackDef tracks[1];
			tracks[0].lba = 0;
			tracks[0].is_audio = 0;
			cobra_mount_psx_disc_image(iso_path[0], tracks, 1);
		} else
		if(EMU == EMU_PSP) {
			cobra_set_psp_umd2(iso_path[0], NULL, (char*)"/dev_hdd0/tmp/psp_icon.png", 2);
		}
		
		usleep(25000);
		cobra_send_fake_disc_insert_event();
	}
}

void cobra_Mount()
{
	int i;
	char temp[128];
	
	fix_error();
	
	if(iso) {
		if(mount_app_home == YES)	{
			{sys_map_path("/app_home", "/dev_bdvd");}
			
			if(use_ex_plug==YES) {
				if(patch_exp_plug() == SUCCESS) {
					sprintf(temp, "/dev_hdd0/game/%s/USRDIR/sys/patched_explore_plugin_%X.sprx", ManaGunZ_id, firmware);
					if(path_info(temp) != _NOT_EXIST) {sys_map_path("/dev_flash/vsh/module/explore_plugin.sprx", temp);}
				} else  print_load("Error : cannot patch explore_plugin.sprx");
			}
		}
		
		cobra_MountISO(EMU_PS3);
	}
	else {
		i=0;	
		int ret;
		
		if(prim_USB == YES) SetPrimaryUSB();
		
		mount_fake_BR();
		
		if(emu == BDMIRROR) {
			print_load("Patching BD-Mirror");
			ret = patch_bdmirror();
			if( ret != 0) print_load("Error %d: patch_bdmirror failed", ret);
			sleep(1);

			sprintf(temp, "%s/PS3_DISC.SFB", GamPath);
			{sys_map_path("/dev_bdvd/PS3_DISC.SFB", temp);}
		} else
		if(emu == BDEMU) {		
			char *libfs_path = get_libfs_path();
			if(path_info(libfs_path) == _FILE)	{sys_map_path("/dev_flash/sys/external/libfs.sprx", libfs_path);}
			if(libfs_path) free(libfs_path);
			
			cobra_map_game(GamPath, (char*)"TEST00000", &i);
		} else 
		if(emu == NONE) {
			cobra_map_game(GamPath, (char*)"TEST00000", &i);
		}
		
		if(mount_app_home == YES)	{
			if(emu == BDMIRROR) {
				{sys_map_path("/app_home", "/dev_bdvd");}
			} else {
				{sys_map_path("/app_home", GamPath);}
			}
			
			if(use_ex_plug==YES) {
				if(patch_exp_plug() == SUCCESS) {
					sprintf(temp, "/dev_hdd0/game/%s/USRDIR/sys/patched_explore_plugin_%X.sprx", ManaGunZ_id, firmware);
					if((path_info(temp)==_FILE) )	{sys_map_path("/dev_flash/vsh/module/explore_plugin.sprx", temp);}
				} else  print_load("Error : cannot patch explore_plugin.sprx");
			}
		}
	}
	
	if(ext_game_data==YES) {
		int i;
		for(i=0; i<=device_number; i++) {
			sprintf(temp, "/%s", list_device[i]);
			if(strstr(temp, "/dev_usb")) {
				strcat(temp, "/GAMEI");
				if(path_info(temp)==_NOT_EXIST) mkdir(temp, 0777);
				{sys_map_path("/dev_hdd0/game", temp);}
			}
		}
	}
}

//*******************************************************
// Mamba
//*******************************************************

#define MAMBA_PRX_LOADER_INSTALL_OFFSET				0x80000000007F0000ULL
#define MAMBA_PRX_LOADER_SYSCALL_NUM				1022

#define IS_MAMBA_PRX_LOADER_PAYLOAD 				0x333
#define IS_MAMBA_LOADER_PAYLOAD 					0x222
#define IS_PRX_LOADER_PAYLOAD 						0x111

#define SYSCALL1022_OPCODE_IS_ENABLED				0x7750
#define SYSCALL1022_OPCODE_LOAD_MAMBA				0x7755

int is_mamba()
{
	u32 version = 0x99999999;
	if (sys_get_version(&version) < 0)	return 0;
	if (version != 0x99999999 && sys8_mamba() == 0x666)	return 1;
	return 0;
}

void write_htab(void)
{
	uint64_t cont = 0;
	uint64_t reg5, reg6;
	uint32_t val;
	while(cont < 0x80)
	{
		val = (cont << 7);
		reg5 = lv2peek(0x800000000f000000ULL | ((uint64_t) val));
		reg6 = lv2peek(0x800000000f000008ULL | ((uint64_t) val));
		reg6 = (reg6  & 0xff0000ULL) | 0x190ULL;
		lv2syscall8(10, 0, (cont << 3ULL), reg5, reg6, 0, 0, 0, 1);
		cont++;
	}
}

int syscall_mpl_payload_is_enabled()
{
	lv2syscall1(MAMBA_PRX_LOADER_SYSCALL_NUM, SYSCALL1022_OPCODE_IS_ENABLED);
	return_to_user_prog(int);
}

int syscall_load_mamba(char* payload_path)
{
	lv2syscall2(MAMBA_PRX_LOADER_SYSCALL_NUM, SYSCALL1022_OPCODE_LOAD_MAMBA, (uint64_t)payload_path);
	return_to_user_prog(int);
}

int load_mamba()
{
	char mamba_path[255];
	sprintf(mamba_path, "/dev_hdd0/game/%s/USRDIR/sys/mamba_%X.bin", ManaGunZ_id, firmware);
	
	Delete(mamba_path);
	
	u32 size=0;
	u8 *mamba_data = (u8 *) malloc(0x20000);
	if(mamba_data==NULL){
		print_load("Error : failed to malloc");
		return FAILED;
	}
	zlib_decompress((char *) MAMBA, (char *) mamba_data, MAMBA_SIZE, (int *) &size);
	if(size==0) {
		print_load("Error : failed to decompress");
		free(mamba_data);
		return FAILED;
	}
		
	FILE* f;
	f = fopen(mamba_path, "wb");
	if(f==NULL) {
		print_load("Error : failed to create mamba file");
		free(mamba_data);
		return FAILED;
	}
	fwrite(mamba_data, size, 1, f);
	fclose(f);
	free(mamba_data);
	
	switch(syscall_mpl_payload_is_enabled())
	{
		case IS_MAMBA_LOADER_PAYLOAD:
		case IS_MAMBA_PRX_LOADER_PAYLOAD:
			if (syscall_load_mamba(mamba_path) != 0) return FAILED;
			else return SUCCESS;
		break;
		default:
			return FAILED;
		break;
	}
}

int load_mamba_loader()
{
	remove_lv2_protection();

	write_htab();

	uint64_t payload_opd = MAMBA_PRX_LOADER_INSTALL_OFFSET + MAMBA_LOADER_SIZE + 0x10;
	int i;
	for(i=0;i<(MAMBA_LOADER_SIZE/8);i++) lv2poke(MAMBA_PRX_LOADER_INSTALL_OFFSET+(i*8),  MAMBA_LOADER[i]);
	lv2poke(payload_opd, MAMBA_PRX_LOADER_INSTALL_OFFSET);
	lv2poke(SYSCALL_TABLE + (8*MAMBA_PRX_LOADER_SYSCALL_NUM), payload_opd);
	
	lv2poke(0x80000000000004E8ULL, 0);						//Disable the disc-less payload (if it was previously loaded)
	lv2poke(0x8000000000003D90ULL, 0x386000014E800020ULL); //Patch permission 4.xx, usually "fixed" by warez payload

	fix_error();

	switch(syscall_mpl_payload_is_enabled())
	{
		case IS_MAMBA_LOADER_PAYLOAD:
		case IS_PRX_LOADER_PAYLOAD:
		case IS_MAMBA_PRX_LOADER_PAYLOAD:
			return SUCCESS; //MAMBA + PRX LOADER
		break;
		default:
			return FAILED;
		break;
	}
}

u8 install_mamba()
{
	mamba = is_mamba();
	if(mamba) return YES;
	
	if(load_mamba_loader() == FAILED) {
		print_load("Error : failed to install mamba loader");
		return NO;
	}
	
	if(load_mamba() == FAILED) {
		print_load("Error : failed to install mamba");
		return NO;
	}
	
	return YES;
}

void mamba_map(char *oldpath, char* newpath)
{
	//char *old_path[1]={NULL};
	//char *new_path[1]={NULL};
	
	//old_path[0]=oldpath;
	//new_path[0]=newpath;
	
	//sys_map_paths(old_path, new_path, 1);
	sys_map_path(oldpath, newpath);
}

void mamba_MountISO(int EMU)
{
	uint8_t *plugin_args = malloc(0x20000);
	
	if(plugin_args==NULL) {
		print_load("Error : failed to malloc plugin_args");
		return;
	}
	
	if(is_ntfs(GamPath)) {	
		uint32_t *sections = malloc(MAX_SECTIONS * sizeof(uint32_t));
		uint32_t *sections_size = malloc(MAX_SECTIONS * sizeof(uint32_t));
		rawseciso_args *p_args; 
		memset(sections, 0, MAX_SECTIONS * sizeof(uint32_t));
		memset(sections_size, 0, MAX_SECTIONS * sizeof(uint32_t));
		memset(plugin_args, 0, 0x10000);

		int parts = ps3ntfs_file_to_sectors(GamPath, sections, sections_size, MAX_SECTIONS, 1);
		
		if(is_splitted_iso(GamPath)==YES) { 
			int o;
			for (o = 1; o < 64; o++) {
				struct stat s;
				sprintf(temp_buffer + 3072, "%s", GamPath);
				temp_buffer[3072 + strlen(temp_buffer + 3072) - 1] = 0;
				sprintf(temp_buffer + 2048, "%s%i", temp_buffer + 3072, o);
				if(parts >= MAX_SECTIONS) break;
				if(stat(temp_buffer + 2048, &s)!=0) break;
				parts += ps3ntfs_file_to_sectors(temp_buffer + 2048, sections + parts, sections_size + parts, MAX_SECTIONS - parts, 1);		   
			}
		}

		if (parts>0 && parts < MAX_SECTIONS) {
			
			p_args = (rawseciso_args *)plugin_args;
			p_args->device = USB_MASS_STORAGE(NTFS_Test_Device(&GamPath[1]));
			p_args->emu_mode = EMU;
			p_args->num_sections = parts;
			p_args->num_tracks = 0;
			
			memcpy(plugin_args+sizeof(rawseciso_args), sections, parts*sizeof(uint32_t));
			memcpy(plugin_args+sizeof(rawseciso_args)+(parts*sizeof(uint32_t)), sections_size, parts*sizeof(uint32_t)); 
			
			cobra_unload_vsh_plugin(0);
			
			sprintf(temp_buffer + 2048, "/dev_hdd0/game/%s/USRDIR/sys/sprx_iso", ManaGunZ_id);
			
			if( cobra_load_vsh_plugin(0, temp_buffer + 2048, plugin_args, 0x10000) != 0) {
				print_load("Error : Failed to load plugin");
			}
			sleep(1);
			return;
		}
	}
	else {
		sprintf((char *) plugin_args, "/dev_hdd0/game/%s/USRDIR/sys/sprx_iso", ManaGunZ_id);
		
		if(path_info((char *) plugin_args) == _NOT_EXIST) {free(plugin_args); return;}

		char *sections = malloc(64 * 0x200);
		uint32_t *sections_size = malloc(64 * sizeof(uint32_t));

		if(plugin_args && sections && sections_size) {
			
			rawseciso_args *p_args;

			memset(sections, 0, 64 * 0x200);
			memset(sections_size, 0, 64 * sizeof(uint32_t));
			memset(plugin_args, 0, 0x10000);

			int parts = 0;	
			
			if(is_splitted_iso(GamPath)==YES) {
				int o;				
				for (o = 0; o < 64; o++) {
					struct stat s;
					sprintf(temp_buffer + 3072, "%s", GamPath);
					temp_buffer[3072 + strlen(temp_buffer + 3072) - 1] = 0;
					sprintf(&sections[0x200 * o], "%s%i", temp_buffer + 3072, o);
					if(stat(&sections[0x200 * o], &s) != 0) {memset(&sections[0x200 * o], 0, 0x200); break;}
					sections_size[o] = s.st_size/2048;
					parts++;
				}
			} 
			else {
				struct stat s;
				parts = 1;
				strncpy(&sections[0], GamPath, 0x1ff);
				sections[0x1ff] = 0;
				if(stat(&sections[0], &s) != 0) goto skip_load;
				sections_size[0] = s.st_size/2048;
			}
			
			p_args = (rawseciso_args *)plugin_args;
			p_args->device = USB_MASS_STORAGE(NTFS_Test_Device(&GamPath[1]));
			p_args->emu_mode = EMU | 1024;
			p_args->num_sections = parts;
			p_args->num_tracks = 0;
			
			memcpy(plugin_args+sizeof(rawseciso_args), sections, parts * 0x200);
			memcpy(plugin_args+sizeof(rawseciso_args)+(parts* 0x200), sections_size, parts*sizeof(uint32_t));

			cobra_unload_vsh_plugin(0);

			sprintf(temp_buffer + 2048, "/dev_hdd0/game/%s/USRDIR/sys/sprx_iso", ManaGunZ_id);

			if( cobra_load_vsh_plugin(0, temp_buffer + 2048, plugin_args, 0x10000) != 0) {
				print_load("Error : failed to load plugin");
			}
			sleep(1);
			return; 
		}

		skip_load:
		
		print_load("Error : load skipped");
		
		if(plugin_args) free(plugin_args); plugin_args = NULL;
		if(sections) free(sections);
		if(sections_size) free(sections_size);
	}
	if(plugin_args) free(plugin_args); plugin_args = NULL;
	
}

void mamba_Mount()
{
	mamba = install_mamba();
	
	char temp[128];
	
	if(ext_game_data==YES) {
		int i;
		
		for(i=0; i<=device_number; i++) {
			sprintf(temp, "/%s", list_device[i]);
			if(strstr(temp, "/dev_usb")) {
				strcat(temp, "/GAMEI");
				if(path_info(temp)==_NOT_EXIST) mkdir(temp, 0777);
				{mamba_map("/dev_hdd0/game", temp);}
			}
		}
	}
	
	if(iso) {
		mamba_MountISO(EMU_PS3);
		mamba_MountISO(EMU_PS3);
		
		if(mount_app_home == YES)	{
			{mamba_map("/app_home", "/dev_bdvd");}
			
			if(use_ex_plug==YES) {
				if(patch_exp_plug() == SUCCESS) {
					sprintf(temp, "/dev_hdd0/game/%s/USRDIR/sys/patched_explore_plugin_%X.sprx", ManaGunZ_id, firmware);
					if(path_info(temp) != _NOT_EXIST)	{mamba_map("/dev_flash/vsh/module/explore_plugin.sprx", temp);}
				} else  print_load("Error : cannot patch explore_plugin.sprx");
			}
		}	
	}
	else {

		int ret;
		
		if(prim_USB == YES) SetPrimaryUSB();
		
		if(emu == BDMIRROR) {
			print_load("Patching BD-Mirror");
			ret = patch_bdmirror();
			if( ret != 0) print_load("Error %d: patch_bdmirror failed", ret);
			sleep(1);

			sprintf(temp, "%s/PS3_DISC.SFB", GamPath);
			{mamba_map("/dev_bdvd/PS3_DISC.SFB", temp);}
		} else
		if(emu == BDEMU) {
			char *libfs_path = get_libfs_path();
			if(path_info(libfs_path) == _FILE)	{mamba_map("/dev_flash/sys/external/libfs.sprx", libfs_path);}
			if(libfs_path) free(libfs_path);
			
			{mamba_map("/dev_bdvd", GamPath);}
			
		} else 
		if(emu == NONE) {
			{mamba_map("/dev_bdvd", GamPath);}
		}
		
		if(mount_app_home == YES)	{
			if(emu == BDMIRROR) {
				{mamba_map("/app_home", "/dev_bdvd");}
			} else {
				{mamba_map("/app_home", GamPath);}
			}
			
			if(use_ex_plug==YES) {
				if(patch_exp_plug() == SUCCESS) {
					sprintf(temp, "/dev_hdd0/game/%s/USRDIR/sys/patched_explore_plugin_%X.sprx", ManaGunZ_id, firmware);
					if((path_info(temp) == _FILE) )	{mamba_map("/dev_flash/vsh/module/explore_plugin.sprx", temp);}
				} else  print_load("Error : cannot patch explore_plugin.sprx");
			}
		}
	}
}

u8 MountGame(char *GamePath)
{
	if(can_mount()==NO) return FAILED;
	if(is_66600(GamePath)) return FAILED;
	
	strcpy(GamPath, GamePath); // todo : something better...
	
	u8 platform = get_ext(GamePath);
	iso = is_iso(GamePath);
	
	if(platform == _ISO_PS3 || platform == _JB_PS3) {
		
		if(PEEKnPOKE) {
			if(payload==IRIS) iris_Mount(); else
			if(payload==MM) mm_Mount(); else
			if(cobra) cobra_Mount(); else 
			mamba_Mount();
			if(change_IDPS) poke_IDPS();	
			if(clean_syscall) remove_cfw_syscalls();
		} else {
			if(cobra) cobra_Mount(); else 
			if(mamba) mamba_Mount();
		}
				
		if(direct_boot) {
			end_loading();
			sysModuleUnload(SYSMODULE_PNGDEC);
			sysModuleUnload(SYSMODULE_JPGDEC);
			ioPadEnd();
			if(mount_app_home == NO) {
				sysProcessExitSpawn2("/dev_bdvd/PS3_GAME/USRDIR/EBOOT.BIN", NULL, NULL, NULL, 0, 64, SYS_PROCESS_SPAWN_STACK_SIZE_128K);
			} else {
				sysProcessExitSpawn2("/app_home/PS3_GAME/USRDIR/EBOOT.BIN", NULL, NULL, NULL, 0, 64, SYS_PROCESS_SPAWN_STACK_SIZE_128K);
			}
		}
	} else 
	if(platform == _ISO_PS2 || platform == _ISO_PS1 || platform == _ISO_PSP) {
		int emul;
		
		if(platform == _ISO_PS2) emul = EMU_PS2_DVD;
		if(platform == _ISO_PS1) emul = EMU_PSX;
		if(platform == _ISO_PSP) emul = EMU_PSP;
		
		if(PEEKnPOKE) {
			if(!cobra && !mamba) mamba = install_mamba();
		}
		
		if(emul == EMU_PS2_DVD) { 
			patch_PS2();
			CONFIG_check(GamePath);
		}
		
		cobra_MountISO(emul);
		cobra_MountISO(emul);
	} else 
		return FAILED;
	
	// todo : check if game mounted...
	
	return SUCCESS;
}

//*******************************************************
// Make PKG
//*******************************************************

#define ntohll(x) (((uint64_t) ntohl (x) ) | (uint64_t) ntohl ((x) ) )
#define htonll(x) (((uint64_t) htonl (x) ) | (uint64_t) htonl ((x) ) )
#define conv_ntohl(x) { x = ntohl(x); }
#define conv_ntohll(x) { x = ntohll(x); }
#define conv_htonl(x) { x = htonl(x); }
#define conv_htonll(x) { x = htonll(x); }

#define HASH_LEN 16
#define BUF_SIZE 4096

#define PKG_HEADER__MAGIC 						0x7f504b47
#define PKG_HEADER__PKG_REVISION_RETAIL 		0x8000
#define PKG_HEADER__PKG_REVISION_DEBUG  		0x0000
#define PKG_HEADER__PKG_TYPE_PS3 				0x0001
#define PKG_HEADER__PKG_TYPE_PSP 				0x0002
#define PKG_HEADER__PKG_INFO_OFFSET 			sizeof(pkg_header)
#define PKG_HEADER__PKG_INFO_COUNT				0x05
#define PKG_HEADER__PKG_INFO_SIZE 				sizeof(pkg_info)

#define PKG_INFO__DRM_TYPE_NETWORK  				1
#define PKG_INFO__DRM_TYPE_LOCAL  					2
#define PKG_INFO__DRM_TYPE_FREE  					3
#define PKG_INFO__DRM_TYPE_FREE2  					0xD
#define PKG_INFO__DRM_TYPE_PSP  					4

#define PKG_INFO__CONTENT_TYPE_GAMEDATA  			4				// /dev_hdd0/game/
#define PKG_INFO__CONTENT_TYPE_GAME_EXEC 			5				// /dev_hdd0/game/
#define PKG_INFO__CONTENT_TYPE_PS1EMU				6				// /dev_hdd0/game/
#define PKG_INFO__CONTENT_TYPE_PSP					7				// /dev_hdd0/game/
#define PKG_INFO__CONTENT_TYPE_THEME				9				// /dev_hdd0/theme
#define PKG_INFO__CONTENT_TYPE_WIDGET				0xA				// /dev_hdd0/widget
#define PKG_INFO__CONTENT_TYPE_LICENCE				0xB				// /dev_hdd0/home/<current user>/exdata	
#define PKG_INFO__CONTENT_TYPE_VSH_MODULE			0xC				// /dev_hdd0/vsh/modules/
#define PKG_INFO__CONTENT_TYPE_PSN_AVATAR			0xE				// /dev_hdd0/home/<current user>/psn_avatar
#define PKG_INFO__CONTENT_TYPE_PSPGO				0xF				// /dev_hdd0/game/
#define PKG_INFO__CONTENT_TYPE_NEOGEO				0x10			// /dev_hdd0/game/
#define PKG_INFO__CONTENT_TYPE_VMC					0x11			// /dev_hdd0/tmp/vmc/
#define PKG_INFO__CONTENT_TYPE_PS2_CLASSIC			0x12			// /dev_hdd0/game/
#define PKG_INFO__CONTENT_TYPE_PSP_REMASTERED		0x14			// /dev_hdd0/game/
#define PKG_INFO__CONTENT_TYPE_PSVITA_PSPGD			0x15
#define PKG_INFO__CONTENT_TYPE_PSVITA_PSPAC			0x16
#define PKG_INFO__CONTENT_TYPE_PSVITA_PSPLA			0x17
#define PKG_INFO__CONTENT_TYPE_WT					0x19			// /dev_hdd0/game/

#define PKG_FILE_ENTRY_OVERWRITE 					0x80000000
#define PKG_FILE_ENTRY_NPDRM 						0x0001
#define PKG_FILE_ENTRY_NPDRMEDAT 					0x0002 
#define PKG_FILE_ENTRY_REGULAR 						0x0003
#define PKG_FILE_ENTRY_FOLDER 						0x0004
#define PKG_FILE_ENTRY_SDAT 						0x0009

#define unpack32(x) ((uint32_t) ((uint32_t)*(x) << 24 | \
						(uint32_t)*(x+1) << 16 | 		\
						(uint32_t)*(x+2) << 8 | 		\
						(uint32_t)*(x+3) << 0))

#define unpack64(x) ((uint64_t)unpack32(x) << 32 | (uint64_t)unpack32(x+4))

#define pack32(x, p) 									\
					{									\
						*(x) = (uint8_t)(p >> 24);		\
						*((x)+1) = (uint8_t)(p >> 16);	\
						*((x)+2) = (uint8_t)(p >> 8);	\
						*((x)+3) = (uint8_t)(p >> 0);	\
					}

#define pack64(x, p) { pack32((x + 4), p); pack32((x), p >> 32); }


typedef struct 
{
	uint32_t magic;
	uint32_t pkg_rev_type;
	uint32_t pkg_info_offset;
	uint32_t pkg_info_count;
	uint32_t pkg_info_size;
	uint32_t item_count;
	uint64_t total_size;
	uint64_t data_offset;
	uint64_t data_size;
	char content_id[48];
	uint8_t qa_digest[16];
	uint8_t KLicensee[16];
} pkg_header;


#define PKG_HEADER_FROM_BE(x)								   \
  (x).magic = FROM_BE (32, (x).magic);						  \
	 (x).pkg_rev_type = FROM_BE (32, (x).pkg_rev_type);				 \
	 (x).pkg_info_offset = FROM_BE (32, (x).pkg_info_offset);   \
	 (x).pkg_info_count = FROM_BE (32, (x).pkg_info_count);				 \
	 (x).pkg_info_size = FROM_BE (32, (x).pkg_info_size);		   \
	 (x).item_count = FROM_BE (32, (x).item_count);			 \
	 (x).total_size = FROM_BE (64, (x).total_size);			 \
	 (x).data_offset = FROM_BE (64, (x).data_offset);		   \
	 (x).data_size = FROM_BE (64, (x).data_size);
#define PKG_HEADER_TO_BE(x) PKG_HEADER_FROM_BE (x)

typedef struct 
{
	uint32_t drm_type_id; 
	uint32_t drm_type_size;
	uint32_t drm_type; 
	uint32_t content_type_id;
	uint32_t content_type_size;
	uint32_t content_type; 
	uint32_t pkg_type_id;
	uint32_t pkg_type_size;
	uint32_t pkg_type;
	uint32_t data_size_id;
	uint32_t data_size_size;
	uint32_t data_size[2]; 
	uint32_t vers_id;
	uint32_t vers_size;
	uint32_t vers;
} pkg_info;

typedef struct
{
	uint32_t name_offset;
	uint32_t name_size;
	uint64_t file_offset;
	uint64_t file_size;
	uint32_t type;
	uint32_t pad;
} pkg_file_entry;

#define PKG_FILE_ENTRY_FROM_BE(x)							 \
	(x).name_offset = FROM_BE (32, (x).name_offset);		  \
	(x).name_size = FROM_BE (32, (x).name_size);			  \
	(x).file_offset = FROM_BE (64, (x).file_offset);		  \
	(x).file_size = FROM_BE (64, (x).file_size);			  \
	(x).type = FROM_BE (32, (x).type);						  \
	(x).pad = FROM_BE (32, (x).pad); 
#define PKG_FILE_ENTRY_TO_BE(x) PKG_FILE_ENTRY_FROM_BE (x)


typedef struct
{
	pkg_file_entry fe;
	char *name;
	char *path;
} file_table_tr;

static const uint8_t PKG_AES_KEY[16] = 
{
	0x2e, 0x7b, 0x71, 0xd7,
	0xc9, 0xc9, 0xa1, 0x4e,
	0xa3, 0x22, 0x1f, 0x18,
	0x88, 0x28, 0xb8, 0xf8
};

static void keyToContext(uint8_t *key, uint8_t *largekey)
{
	int i;
	for(i=0; i<0x8;i++) largekey[i]=key[i];
	for(i=0; i<0x8;i++) largekey[i+0x8]=key[i];
	for(i=0; i<0x10;i++) largekey[i+0x10]=key[i+0x8];
	for(i=0; i<0x10;i++) largekey[i+0x18]=key[i+0x8];
	for(i=0; i<0x20;i++) largekey[i+0x20]=0;
}

static void manipulate(uint8_t *key) 
{
	uint64_t temp = (uint64_t) key[0x38] << 56 | 
					(uint64_t) key[0x39ULL] << 48 | 
					(uint64_t) key[0x3a] << 40 | 
					(uint64_t) key[0x3b] << 32 | 
					(uint64_t) key[0x3c] << 24 | 
					(uint64_t) key[0x3d] << 16 | 
					(uint64_t) key[0x3e] <<  8 | 
					(uint64_t) key[0x3f];
	temp++;
	key[0x38] = (temp >> 56) & 0xff;
	key[0x39] = (temp >> 48) & 0xff;
	key[0x3a] = (temp >> 40) & 0xff;
	key[0x3b] = (temp >> 32) & 0xff;
	key[0x3c] = (temp >> 24) & 0xff;
	key[0x3d] = (temp >> 16) & 0xff;
	key[0x3e] = (temp >>  8) & 0xff;
	key[0x3f] = (temp >>  0) & 0xff;
}

static void crypt(uint8_t *key, uint8_t *inbuff, uint64_t length, uint8_t *out)
{
	uint64_t offset = 0;
	uint64_t bytes_to_dump;
	uint64_t remaining=length;
	int i;
	 
	while (remaining > 0) {
		bytes_to_dump = remaining;
		if (remaining > 0x10) bytes_to_dump = 0x10;
		uint8_t outhash[bytes_to_dump];
		sha1(key, sizeof(uint8_t)*0x40, outhash);
		for(i = 0; i < bytes_to_dump; i++) {
			out[offset] = outhash[i] ^ inbuff[offset];
			offset++;
		}
		manipulate(key);
		remaining -= bytes_to_dump;
	}
}

//*******
//PACK 
//*******

static int pkg_pack_traverse(const char *global_path, file_table_tr **ftr, int item_count,  const char *local_path)
{
	file_table_tr *cur = NULL;
	struct stat s;
	char full_path_item[255];
	char full_path[255];
	char local_path_item[255];
	char *temp;
	char name[512];

	DIR *d;
	struct dirent *dir;
	
	strcpy(full_path, global_path);
	strcat(full_path, "/");
	strcat(full_path, local_path);
	d = opendir(full_path);
	if(d==NULL) return 0;
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		strcpy(full_path_item, global_path);
		strcat(full_path_item, "/");
		strcat(full_path_item, local_path);
		strcat(full_path_item, "/");
		strcat(full_path_item, dir->d_name);
	
		if(stat(full_path_item, &s) != 0) continue;
		
		strcpy(local_path_item, local_path);
		strcat(local_path_item, "/");
		strcat(local_path_item, dir->d_name);
		
		if(strstr(local_path, "/") !=NULL) {
			temp = strchr(local_path,'/');
			temp = &temp[1];
			strcpy(name, temp);
			strcat(name, "/");
			strcat(name, dir->d_name);
		} else strcpy(name, dir->d_name);
		
		(*ftr) = realloc((*ftr), ++item_count*sizeof(file_table_tr));
		cur = (*ftr) + (item_count - 1);
		cur->fe.name_size = htonl(strlen(name));
		cur->name = strdup(name);
		cur->path = strdup(full_path_item);
		cur->fe.type = 0;
		cur->fe.type |= PKG_FILE_ENTRY_OVERWRITE;
		
		if(dir->d_type & DT_DIR) {
			cur->fe.file_size = 0;
			cur->fe.type |= PKG_FILE_ENTRY_FOLDER;
			conv_htonl(cur->fe.type);
			
			item_count = pkg_pack_traverse(global_path, ftr, item_count, local_path_item);
		} else {
			cur->fe.file_size = htonll(s.st_size);
			
			if (!strcasecmp(dir->d_name, "EBOOT.BIN"))	{
				cur->fe.type |= PKG_FILE_ENTRY_NPDRM;
			} 
			else if (!strcasecmp(dir->d_name + strlen(dir->d_name) - 5, ".sdat")) {
				cur->fe.type |= PKG_FILE_ENTRY_SDAT;
			}
			else if (!strcasecmp(dir->d_name + strlen(dir->d_name) - 5, ".edat")) {
				cur->fe.type |= PKG_FILE_ENTRY_NPDRMEDAT;
			}
			else {
				cur->fe.type |= PKG_FILE_ENTRY_REGULAR;
			}
			conv_htonl(cur->fe.type);
			
		}
	}
	closedir(d);
	return item_count;
}

static void *pkg_pack_create_filetable(file_table_tr *tr, int item_count, char **n_table, uint32_t *n_table_len)
{
	pkg_file_entry *table;
	int i;
	uint64_t tmp;

	tmp = sizeof(pkg_file_entry)*item_count;
	table = malloc(tmp);
	
	print_load("Building filetable...");
	
	for (i = 0; i < item_count; i++)
	{
		memcpy((table+i), &((tr+i)->fe), sizeof(pkg_file_entry));
		(table+i)->name_offset = htonl(tmp);
		tmp += (ntohl((table+i)->name_size) + 0x0f) & ~0x0f;
		(table+i)->pad = 0;
	}
	
	(*n_table_len) = tmp - sizeof(pkg_file_entry)*item_count;
	(*n_table) = malloc(*n_table_len);
	memset(*n_table, 0, *n_table_len);
	
	for (i = 0; i < item_count; i++)
	{
		(table+i)->file_offset = htonll(tmp);
		tmp += (ntohll((table+i)->file_size) + 0x0f) & ~0x0f;
		
		memcpy((*n_table)+((ntohl((table+i)->name_offset) - 
						 sizeof(*table)*item_count)),
			   (tr+i)->name, ntohl((table+i)->name_size));
		
		free((tr+i)->name);
		
	}
	
	
	return table;
}

static int pkg_pack_data(file_table_tr *ftr, pkg_file_entry *table,  int item_count, sha1_context *ctx, FILE* out)
{
	int i;
	FILE* f;
	uint64_t tmp;
	uint8_t buf[BUF_SIZE];
	
	sha1_starts(ctx);
	
	print_head("Packing data...");
	
	prog_bar1_value=0;
	
	for (i = 0; i < item_count; i++)
	{
		prog_bar1_value = (i*100)/item_count;
		if(cancel == YES) {
			for (; i < item_count; i++)	free((ftr+i)->path);
			return FAILED;
		}
		
		if (ntohl((ftr+i)->fe.type) & PKG_FILE_ENTRY_FOLDER) continue;
		
		f = fopen((ftr+i)->path, "rb");
		if (f == NULL) {
			for (; i < item_count; i++)	free((ftr+i)->path);	
			return FAILED;
		}
		
		print_load((ftr+i)->path);
		
		prog_bar2_value=0;
		
		u64 read=0;
		
		while ((tmp = fread(buf, 1, BUF_SIZE, f)) > 0) {
		
			read += tmp;
			prog_bar2_value = (read*100)/ntohll((table+i)->file_size);
			
			if(cancel == YES) {
				for (; i < item_count; i++) free((ftr+i)->path);	
				fclose(f);
				return FAILED;
			}
			
			sha1_update(ctx, buf, tmp);
			fwrite(buf, 1, tmp, out);
		}
		
		tmp = (ntohll((table+i)->file_size) + 0x0f) & ~0x0f;
		memset(buf, 0, sizeof(buf));
		fwrite(buf, 1, tmp - ntohll((table+i)->file_size), out);
		
		fclose(f);
		
		free((ftr+i)->path);
	}
	
	return SUCCESS;
}

int pkg_pack(char *fname, const char *content_id, const char *path, const char *dir)
{
	pkg_header header;
	pkg_info info;
	file_table_tr *ftr = NULL;
	pkg_file_entry *table = NULL;
	char *n_table = NULL;
	uint32_t n_table_len;
	int item_count;
	sha1_context ctx;
	unsigned char tmpdigest[32];
	uint64_t tmp;
	FILE* dec, *out;
	FILE* temp;
	char *dec_fname;
	int i;
	
	if (strlen(content_id) > sizeof(header.content_id)){
		return 1;
	}
	
	out = fopen(fname, "wb+");
	if (out == NULL){
		return NOK;
	}
	
	item_count = pkg_pack_traverse(path, &ftr, 0, dir);
	if (item_count <= 0) {
		return NOK;
	}
	table = pkg_pack_create_filetable(ftr, item_count, &n_table, &n_table_len);
	
	dec_fname = malloc(strlen(fname)+4);
	memset(dec_fname, 0, strlen(fname)+4);
	sprintf(dec_fname, "%s.dec", fname);
	
	dec = fopen(dec_fname, "wb+");
	if (dec == NULL) {
		free(ftr);
		free(n_table);
		return NOK;
	}
	
	fwrite(table, 1, item_count*sizeof(pkg_file_entry), dec);
	fwrite(n_table, 1, n_table_len, dec);
	
	if (pkg_pack_data(ftr, table, item_count, &ctx, dec)==FAILED) {
		free(ftr);
		free(table);
		free(n_table);
		Delete(dec_fname);
		return FAILED;
	}
	
	fseek(dec, 0, SEEK_END);	
	tmp = ftell(dec);
	fseek(dec, 0, SEEK_SET);
	
	prog_bar2_value=-1;
	prog_bar1_value=0;
	print_head("Making PKG...");
	
	header.magic = htonl(PKG_HEADER__MAGIC);
	header.pkg_rev_type = htonl((PKG_HEADER__PKG_REVISION_DEBUG << 16) | PKG_HEADER__PKG_TYPE_PS3);
	header.pkg_info_offset = htonl(PKG_HEADER__PKG_INFO_OFFSET + 0x40); //
	header.pkg_info_count = htonl(PKG_HEADER__PKG_INFO_COUNT);
	header.pkg_info_size = htonl(PKG_HEADER__PKG_INFO_SIZE + 0x40);
	header.item_count = htonl((uint32_t)item_count);
	header.data_offset = htonll((uint64_t)(PKG_HEADER__PKG_INFO_OFFSET + 0x40 + PKG_HEADER__PKG_INFO_SIZE + 0x40 ));
	header.data_size = htonll(tmp);
	header.total_size = htonll(tmp + PKG_HEADER__PKG_INFO_OFFSET + PKG_HEADER__PKG_INFO_SIZE + 0x60 + 0x40 + 0x40); 
	memset(header.content_id, 0, sizeof(header.content_id));
	memset(header.qa_digest, 0, sizeof(header.qa_digest));
	memset(header.KLicensee, 0, sizeof(header.KLicensee));
	
	uint8_t *in = (uint8_t *) malloc(sizeof(uint8_t)*tmp);
	uint8_t *ou = (uint8_t *) malloc(sizeof(uint8_t)*tmp);
	uint8_t section[0x80];
	memcpy(section, &header, sizeof(section));
	
	temp=fopen(dec_fname, "rb");
	fread(in, tmp, sizeof(uint8_t), temp);
	fclose(temp);
	
	uint64_t fileDescLength = item_count*sizeof(pkg_file_entry) + n_table_len ;
	sha1_update(&ctx, section, sizeof(uint8_t)*0x80);
	sha1_update(&ctx, in, fileDescLength);
	sha1_finish(&ctx, tmpdigest);
	memcpy(&header.qa_digest, tmpdigest, sizeof(header.qa_digest));
	memcpy(header.content_id, content_id, strlen(content_id));
	info.drm_type_id = htonl(1);
	info.drm_type_size = htonl(sizeof(info.drm_type));
	info.drm_type = htonl(PKG_INFO__DRM_TYPE_FREE);
	info.content_type_id = htonl(2);
	info.content_type_size = htonl(sizeof(info.content_type));
	info.content_type = htonl(PKG_INFO__CONTENT_TYPE_GAME_EXEC);
	info.pkg_type_id = htonl(3);
	info.pkg_type_size = htonl(sizeof(info.pkg_type));
	info.pkg_type = htonl(0xE); //??
	info.data_size_id = htonl(4);
	info.data_size_size = htonl(sizeof(info.data_size));
	info.data_size[0] = htonll(tmp<<32);
	info.data_size[1] = htonll(tmp);
	info.vers_id = htonl(5);
	info.vers_size = htonl(sizeof(info.vers));
	info.vers = htonl(0x10610000);
	
	uint8_t context[0x40]; uint8_t licensee[0x10];
	memset(context, 0, sizeof(uint8_t)*0x40);
	keyToContext(header.qa_digest, context);
	for(i=0x38; i<0x40;i++) {context[i] = 0xFF;}
	crypt(context, header.KLicensee, 0x10, licensee);
	memcpy(header.KLicensee, licensee, sizeof(uint8_t)*0x10);
	fwrite(&header, 1, sizeof(header), out);
	memcpy(section, &header, sizeof(section));
	sha1(section, sizeof(uint8_t)*0x80, tmpdigest);
	uint8_t headerSHA[0x10];
	memcpy(headerSHA, tmpdigest+0x03, sizeof(uint8_t)*0x10);
	fwrite(headerSHA, 0x10, sizeof(uint8_t), out);
	uint8_t infoDataHeader[0x40]; 
	uint8_t infoSHA[0x10];
	memcpy(infoDataHeader, &info, sizeof(infoDataHeader));
	sha1(infoDataHeader, sizeof(uint8_t)*0x40, tmpdigest);
	memcpy(infoSHA, tmpdigest+0x03, sizeof(uint8_t)*0x10);
	uint8_t infoSHAPad[0x30];
	memset(infoSHAPad, 0, sizeof(infoSHAPad));
	uint8_t infoSHAPadEnc[0x30];
	uint8_t infoSHAPadEnc2[0x30];
	keyToContext(infoSHA, context);
	crypt(context, infoSHAPad, 0x30, infoSHAPadEnc);
	keyToContext(headerSHA, context);
	crypt(context, infoSHAPadEnc, 0x30, infoSHAPadEnc2);
	fwrite(infoSHAPadEnc2, 0x30, sizeof(uint8_t), out);
	fwrite(&info, 1, sizeof(info), out);
	fwrite(infoSHA, 0x10, sizeof(uint8_t), out);
	fwrite(infoSHAPadEnc, 0x30, sizeof(uint8_t), out);
	keyToContext(header.qa_digest, context);
	
	crypt(context, in, tmp, ou);
	
	//fwrite(ou, tmp, sizeof(uint8_t), out);
	u64 write = 0;
	while(write < tmp)
	{
		if(cancel) break;
		u32 wrlen = 1024;
		if(write+wrlen > tmp) wrlen = tmp-write;
		fwrite(ou+write, sizeof(u8), wrlen, out);
		write += wrlen;
		prog_bar1_value = (write*100)/tmp;
	}
	prog_bar1_value=-1;
	
	/*/
	uint64_t empty[12];
	memset(empty, 0 ,sizeof(empty));
	fwrite(empty, 1, sizeof(empty), out);
	
	uint64_t size =  ftell(out);
	uint8_t *sha_crap = (uint8_t *) malloc(sizeof(uint8_t)*size);																							 
	temp=fopen(fname, "rb");
	fread(sha_crap, size , sizeof(uint8_t), temp);
	fclose(temp);
	memset(tmpdigest, 0, sizeof(tmpdigest));
	sha1(sha_crap, sizeof(uint8_t)*size, tmpdigest);
	fwrite(tmpdigest, 1, sizeof(tmpdigest), out);
	/*/

	fclose(dec);
	fclose(out);
	unlink(dec_fname);

	free(ftr);
	free(table);
	free(n_table);
	free(ou);
	free(in);
	free(dec_fname);
	
	if(cancel) {
		Delete(fname);
		return NOK;
	}
	
	return OK;
}

void make_pkg(const char *dir_path)
{
	FILE* f;
	
	char content_id[37];
	char dir_name[255];
	char src[255];
	char dst[255];
	char file[255];
	
	strcpy(file, dir_path);
	strcat(file, "/USRDIR/EBOOT.BIN");

	f = fopen(file, "rb");
	if(f==NULL) {
		print_load("Warning : EBOOT not found");
		char title_id[10];
		strcpy(file, dir_path);
		strcat(file, "/PARAM.SFO");
		if( path_info(file) == _NOT_EXIST ) {
			print_load("Warning : PARAM.SFO not found");
			print_load("Error : Cannot get Content ID");
			return;
		}
		if(GetParamSFO("TITLE_ID", title_id, -1, file) == FAILED ) {
			print_load("Error : Cannot get Content ID");
			return;
		}
		sprintf(content_id, "EP0001-%s_00-0000000000000000", title_id);
	} else {
		char check_npd[3];
		fseek(f, 0x420, SEEK_SET);
		fread(check_npd, 3, 1, f);
		if(strstr(check_npd, "NPD") == NULL) {
			print_load("Error : EBOOT is not NPDRM %s", check_npd);
			return;
		}
		fseek(f, 0x430, SEEK_SET);
		fread(&content_id, sizeof(char), 37, f);
		fclose(f);
	}
	
	strcpy(dir_name, &strrchr(dir_path, '/')[1]);
	
	strcpy(src, dir_path);
	src[strrchr(src, '/') - src] = 0;
	
	sprintf(dst, "%s/%s.pkg", src, content_id);
	
	pkg_pack(dst, content_id, src, dir_name);
}

//*******************************************************
//Extract PKG
//*******************************************************

#include "paged_file.h"

static int pkg_debug_decrypt (PagedFile* f, PagedFileCryptOperation operation, u8 *ptr, u32 len, void *user_data)
{
  u64 *crypt_offset = user_data;
  u8 key[0x40];
  u8 bfr[0x14];
  u64 i;
  s64 seek;

  if (operation == PAGED_FILE_CRYPT_DECRYPT ||
	  operation == PAGED_FILE_CRYPT_ENCRYPT) {
	memset(key, 0, 0x40);
	memcpy(key, f->key, 8);
	memcpy(key + 0x08, f->key, 8);
	memcpy(key + 0x10, f->key + 8, 8);
	memcpy(key + 0x18, f->key + 8, 8);
	seek = (signed) ((f->page_pos + f->pos) - *crypt_offset) / 0x10;
	if (seek > 0)
	  wbe64(key + 0x38, be64(key + 0x38) + seek);

	for (i = 0; i < len; i++) {
	  if (i % 16 == 0) {
		sha1(key, 0x40, bfr);
		wbe64(key + 0x38, be64(key + 0x38) + 1);
	  }
	  ptr[i] ^= bfr[i & 0xf];
	}
  }

  return TRUE;
}

u8 pkg_open (const char *filename, PagedFile* in, pkg_header *header, pkg_file_entry **files)
{
	u32 i;

	if (paged_file_open (in, filename, TRUE) == FAILED) {
		print_load("Error : Unable to open package file");
		return FAILED;
	}

	paged_file_read (in, header, sizeof(pkg_header));
	PKG_HEADER_FROM_BE (*header);

	if (header->magic != 0x7f504b47) {
		print_load("Error : Magic number is not correct");
		 goto error;
	}

	paged_file_seek (in, header->data_offset);
	if (header->pkg_rev_type == 0x80000001) {
		paged_file_crypt (in, (u8 *) PKG_AES_KEY, header->KLicensee,PAGED_FILE_CRYPT_AES_128_CTR, NULL, NULL);
	} else {
		paged_file_crypt (in, header->qa_digest, header->KLicensee,
		PAGED_FILE_CRYPT_CUSTOM, pkg_debug_decrypt, &header->data_offset);
	}

	*files = malloc (header->item_count * sizeof(pkg_file_entry));
	paged_file_read (in, *files, header->item_count * sizeof(pkg_file_entry));

	for (i = 0; i < header->item_count; i++) {
		PKG_FILE_ENTRY_FROM_BE((*files)[i]);
	}

	return SUCCESS;

error:
	if (*files)
	free (*files);
	*files = NULL;

	paged_file_close (in);

	return FAILED;
}

u8 pkg_list(const char *filename)
{
	FILE* txt;
	PagedFile in = {0};
	pkg_header header;
	pkg_info info;
	pkg_file_entry *files = NULL;
	char str[255];
	
	strcpy(str, "/dev_hdd0/tmp");
	mkdir(str, 0777);
	
	txt = fopen("/dev_hdd0/tmp/pkg_list.txt", "wb");
	if(txt == NULL) {
		print_load("Error : cannot create pkg_list.txt");
		return FAILED;
	}
	
	if (pkg_open(filename, &in, &header, &files) == FAILED) {
		print_load("Error : pkg_open failed");
		fclose(txt);
		return FAILED;
	}
	
	sprintf(str, "PKG file : %s\n\n", &strrchr(filename, '/')[1]);
	fputs(str, txt);
	
	if(((header.pkg_rev_type >> 16) & (0xffff)) == PKG_HEADER__PKG_REVISION_RETAIL) {
		strcpy(str, "Revision : RETAIL (0x8000)\n");
	} else
	if(((header.pkg_rev_type >> 16) & (0xffff)) == PKG_HEADER__PKG_REVISION_DEBUG) {
		strcpy(str, "Revision : DEBUG (0x0000)\n");
	} else  {
		sprintf(str, "Revision : 0x%X\n", ((header.pkg_rev_type >> 16) & (0xffff)));
	}
	
	fputs(str, txt);
	
	if(((header.pkg_rev_type) & (0xffff)) == PKG_HEADER__PKG_TYPE_PS3) {
		strcpy(str, "Type : PS3 (0x0001)\n");
	} else
	if(((header.pkg_rev_type) & (0xffff)) == PKG_HEADER__PKG_TYPE_PSP) {
		strcpy(str, "Type : PSP (0x0002)\n");
	} else {
		sprintf(str, "Type : 0x%X\n", ((header.pkg_rev_type) & (0xffff)) );
	}
	fputs(str, txt);
	
	sprintf(str, "Item count : %d\n",	  header.item_count);
	fputs(str, txt);
	sprintf(str, "PKG size : %d\n",	(int) header.total_size);
	fputs(str, txt);
	sprintf(str, "Content ID : %s\n",	  header.content_id);
	fputs(str, txt);

	fseek(in.fd, header.pkg_info_offset, SEEK_SET);
	
	fread(&info, 1, sizeof(pkg_info), in.fd);
	
	switch (info.drm_type)
	{
		case PKG_INFO__DRM_TYPE_NETWORK:
			sprintf(str, "DRM : NETWORK (0x%X)\n", info.drm_type);
			break;
		case PKG_INFO__DRM_TYPE_LOCAL:
			sprintf(str, "DRM : LOCAL (0x%X)\n", info.drm_type);
			break;
		case PKG_INFO__DRM_TYPE_FREE:
			sprintf(str, "DRM : FREE (0x%X)\n", info.drm_type);
			break;
		case PKG_INFO__DRM_TYPE_FREE2:
			sprintf(str, "DRM : FREE2 (0x%X)\n", info.drm_type);
			break;
		case PKG_INFO__DRM_TYPE_PSP:
			sprintf(str, "DRM : PSP (0x%X)\n", info.drm_type);
			break; 
		default:
			sprintf(str, "DRM : UNKNOWN (0x%X)\n", info.drm_type);
			break;
	}
	fputs(str, txt);
	
	switch(info.content_type)
	{
		case PKG_INFO__CONTENT_TYPE_GAMEDATA:
			sprintf(str, "CONTENT : GAMEDATA * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_GAME_EXEC:
			sprintf(str, "CONTENT : GAME EXEC * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PS1EMU:
			sprintf(str, "CONTENT : PS1EMU * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PSP:
			sprintf(str, "CONTENT : PSP * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_THEME:
			sprintf(str, "CONTENT : THEME * /dev_hdd0/theme/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_WIDGET:
			sprintf(str, "CONTENT : WIDGET * /dev_hdd0/widget/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_LICENCE:
			sprintf(str, "CONTENT : LICENCE * /dev_hdd0/home/<current user>/exdata * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_VSH_MODULE:
			sprintf(str, "CONTENT : VSH_MODULE * /dev_hdd0/modules/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PSN_AVATAR:
			sprintf(str, "CONTENT : PSN_AVATAR * /dev_hdd0/home/<current user>/psn_avatar * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_NEOGEO:
			sprintf(str, "CONTENT : NEOGEO * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PSPGO:
			sprintf(str, "CONTENT : PSPGO * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_VMC:
			sprintf(str, "CONTENT : VMC * /dev_hdd0/tmp/vmc/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PS2_CLASSIC:
			sprintf(str, "CONTENT : PS2_CLASSIC * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PSP_REMASTERED:
			sprintf(str, "CONTENT : PSP_REMASTERED * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PSVITA_PSPGD:
			sprintf(str, "CONTENT : PSVITA_PSPGD (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PSVITA_PSPAC:
			sprintf(str, "CONTENT : PSVITA_PSPAC (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_PSVITA_PSPLA:
			sprintf(str, "CONTENT : PSVITA_PSPLA (0x%X)\n\n", info.drm_type);
			break;
		case PKG_INFO__CONTENT_TYPE_WT:
			sprintf(str, "CONTENT : WT * /dev_hdd0/game/ * (0x%X)\n\n", info.drm_type);
		default:
			break;
			sprintf(str, "CONTENT : UNKNOWN (0x%X)\n\n", info.drm_type);
	}
	
	fputs(str, txt);
	
	strcpy(str, "*** Item list ***\n");
	
	char *pkg_file_path = NULL;
	u32 i;
	for (i = 0; i < header.item_count; i++) {
		paged_file_seek (&in, files[i].name_offset + header.data_offset);
		pkg_file_path = malloc (files[i].name_size + 1);
		paged_file_read (&in, pkg_file_path, files[i].name_size);
		pkg_file_path[files[i].name_size] = 0;
		sprintf(str, "Item %d : %s", i, pkg_file_path);
		fputs(str, txt);
		if(files[i].file_size != 0) {
			sprintf(str, "   Size : %ld\n",  files[i].file_size);
		} else strcpy(str, "\n");
		fputs(str, txt);
		free (pkg_file_path);
	}
	fclose(txt);
	paged_file_close (&in);

	return SUCCESS;
}

void pkg_unpack (const char *filename, const char *destination)
{
	PagedFile in = {0};
	PagedFile out = {0};
	char out_dir[1024];
	char *pkg_file_path = NULL;
	char path[1024];
	pkg_header header;
	pkg_file_entry *files = NULL;
	u32 i;

	if( pkg_open(filename, &in, &header, &files) == FAILED) {
		print_load("Error : Unable to open pkg file");
		return;
	}
	
	print_head("Extracting %s", &strrchr(filename, '/')[1]);
	
	if (destination == NULL) {
		//char temp[255];
		//strcpy(temp, filename);
		//temp[strrchr(temp, '/') - temp] = 0;
		//sprintf(out_dir, "%s/%s", temp, header.content_id);
		strcpy(out_dir, filename);
		out_dir[strlen(out_dir)-4]=0;
	} else {
		strncpy (out_dir, destination, sizeof(out_dir));
	}
	mkdir_recursive (out_dir);
	
	prog_bar1_value = 0;
	for (i = 0; i < header.item_count; i++) {
		int j;
		
		prog_bar1_value = (i*100)/header.item_count;
		if(cancel==YES) break;
		
		paged_file_seek (&in, files[i].name_offset + header.data_offset);
		pkg_file_path = malloc (files[i].name_size + 1);
		paged_file_read (&in, pkg_file_path, files[i].name_size);
		pkg_file_path[files[i].name_size] = 0;

		snprintf (path, sizeof(path), "%s/%s", out_dir, pkg_file_path);
		if ((files[i].type & 0xFF) == 4) {
			mkdir_recursive (path);
		} else {
			j = strlen (path);
			while (j > 0 && path[j] != '/') j--;
			if (j > 0) {
				path[j] = 0;
				mkdir_recursive (path);
				path[j] = '/';
			}
			paged_file_seek (&in, files[i].file_offset + header.data_offset);
			print_load("%s", pkg_file_path);
			if (paged_file_open (&out, path, FALSE) == FAILED){
				print_load("Error : Unable to open file : %s", path);
				return;
			}
			
			paged_file_splice (&out, &in, files[i].file_size);
			paged_file_close (&out);
		}
	}
	
	paged_file_close (&in);
	
	if(cancel==YES) Delete(out_dir);
}

//*******************************************************
//Make launcher package
//*******************************************************

u8 read_AutoMount_setting()
{
	char Mount_path[128];
	FILE* fp;
	u16 path_size;
	
	sprintf(Mount_path, "/dev_hdd0/game/%s/USRDIR/AutoMount", ManaGunZ_id);
	
	fp=fopen(Mount_path, "rb");
	
	if(fp==NULL) return FAILED;
	
	fread(&direct_boot, sizeof(u8), 1, fp);
	fread(&clean_syscall, sizeof(u8), 1, fp);
	fread(&change_IDPS, sizeof(u8), 1, fp);
	fread(&IDPS, sizeof(u8), 0x10, fp);
	fread(&ext_game_data, sizeof(u8), 1, fp);
	fread(&payload, sizeof(u8), 1, fp);
	fread(&prim_USB, sizeof(u8), 1, fp);
	fread(&emu, sizeof(u8), 1, fp);
	fread(&libfs_from, sizeof(u8), 1, fp);
	fread(&mount_app_home, sizeof(u8), 1, fp);
	fread(&use_ex_plug, sizeof(u8), 1, fp);
	fread(&path_size, sizeof(u16), 1, fp);
	fread(list_game_path[0], path_size, 1, fp);
	fclose(fp);
	
	if(iso) payload=SNAKE;
	if(PEEKnPOKE==NO) payload=SNAKE;
	
	return SUCCESS;
}

u8 write_AutoMount_setting(char *path)
{
	char Mount_path[128];
	FILE* fp;
	u16 path_size = strlen(path);
	
	sprintf(Mount_path, "/dev_hdd0/game/%s/USRDIR/launcher/USRDIR/AutoMount", ManaGunZ_id);
	
	fp = fopen(Mount_path, "wb");
	if(fp==NULL) return FAILED;
	
	fwrite(&direct_boot, sizeof(u8), 1, fp);
	fwrite(&clean_syscall, sizeof(u8), 1, fp);
	fwrite(&change_IDPS, sizeof(u8), 1, fp);
	fwrite(&IDPS, sizeof(u8), 0x10, fp);
	fwrite(&ext_game_data, sizeof(u8), 1, fp);
	fwrite(&payload, sizeof(u8), 1, fp);
	fwrite(&prim_USB, sizeof(u8), 1, fp);
	fwrite(&emu, sizeof(u8), 1, fp);
	fwrite(&libfs_from, sizeof(u8), 1, fp);
	fwrite(&mount_app_home, sizeof(u8), 1, fp);
	fwrite(&use_ex_plug, sizeof(u8), 1, fp);
	fwrite(&path_size, sizeof(u16), 1, fp);
	fwrite(path, path_size, 1, fp);
	fclose(fp);
	
	return SUCCESS;
}

int make_launcher_pkg(char *title_id)
{
print_load("Start...");
	char content_id[37];
	char src[128];
	char dst[128];
	char lch[128];
	sprintf(lch, "/dev_hdd0/game/%s/USRDIR/launcher", ManaGunZ_id);
	Delete(lch);
	mkdir(lch, 0777);

	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/launcher/USRDIR", ManaGunZ_id);
	mkdir(dst, 0777);
	
//	sys
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/launcher/USRDIR/sys", ManaGunZ_id);
	sprintf(src, "/dev_hdd0/game/%s/USRDIR/sys", ManaGunZ_id);
	if( Copy(src, dst) == FAILED ) {
		print_load("Error : failed to copy sys directory");
		Delete(lch);
		return FAILED;
	}

//  self
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/launcher/USRDIR/ManaGunZ.self", ManaGunZ_id);
	sprintf(src, "/dev_hdd0/game/%s/USRDIR/ManaGunZ.self", ManaGunZ_id);
	if( CopyFile(src, dst) == FAILED ) {
		print_load("Error : failed to copy ManaGunZ.self");
		Delete(lch);
		return FAILED;
	}
	
//	ICON0
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/launcher/ICON0.PNG", ManaGunZ_id);
	if(iso==YES) {
		if( ExtractFromISO(list_game_path[position], "/PS3_GAME/ICON0.PNG", dst) == FAILED) {
			print_load("Error : failed to get ICON0.PNG");
			Delete(lch);
			return FAILED;
		}
	} else {
		sprintf(src, "%s/PS3_GAME/ICON0.PNG", list_game_path[position]);
		if( CopyFile(src, dst) == FAILED ) {
			print_load("Error : failed to copy ICON0.PNG");
			Delete(lch);
			return FAILED;
		}
	}
	
print_load("param");
//	PARAM.SFO
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/launcher/PARAM.SFO", ManaGunZ_id);
	sprintf(src, "/dev_hdd0/game/%s/PARAM.SFO", ManaGunZ_id);
	if( CopyFile(src, dst) == FAILED ) {
		print_load("Error : failed to copy PARAM.SFO");
		Delete(lch);
		return FAILED;
	}
print_load("titleID");
	if( SetParamSFO("TITLE_ID", title_id, -1, dst) == FAILED ) {
		print_load("Error : failed to change TITLE_ID");
		Delete(lch);
		return FAILED;
	}
print_load("title");
	if( SetParamSFO("TITLE", list_game_title[position], -1, dst) == FAILED ) {
		print_load("Error : failed to change TITLE");
		Delete(lch);
		return FAILED;
	}
print_load("AutoMount");
// AUTOMOUNT
	if( write_AutoMount_setting(list_game_path[position]) == FAILED ) {
		print_load("Error : failed to write AutoMount file");
		Delete(lch);
		return FAILED;
	}
print_load("EBOOT.ELF");
// EBOOT.BIN
	sprintf(src, "/dev_hdd0/game/%s/USRDIR/EBOOT.BIN", ManaGunZ_id);
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/launcher/USRDIR/EBOOT.elf", ManaGunZ_id);
	if( Extract(src, dst) == FAILED ) {
		print_load("Error : Failed extract EBOOT.BIN");
		Delete(lch);
		return FAILED;
	}
print_load("EBOOT.BIN");
	sprintf(src, "/dev_hdd0/game/%s/USRDIR/launcher/USRDIR/EBOOT.elf", ManaGunZ_id);
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/launcher/USRDIR/EBOOT.BIN", ManaGunZ_id);
	sprintf(content_id, "EP0001-%s_00-0000000000000000", title_id);
	if(make_EBOOT_NPDRM(src, dst, content_id) == FAILED) {
		print_load("Error : Failed to make EBOOT.BIN");
		Delete(lch);
		return FAILED;
	}
	Delete(src);
	
print_load("ASCII");
// Name of Package file
	char ascii_name[60]={0};
	int i;
	int k=0;
	int l=strlen(list_game_title[position]);
	for(i=0; i<=l; i++) {		
		if(list_game_title[position][i]==32 //	space	
		|| (48<=list_game_title[position][i] && list_game_title[position][i]<=57) //number
		|| (65<=list_game_title[position][i] && list_game_title[position][i]<=90) // A..Z
		|| (97<=list_game_title[position][i] && list_game_title[position][i]<=122)) //a..z
		{
			ascii_name[k]=list_game_title[position][i];
			k++;
			if(k>40) {
				break;
			}
		}
	}
	strcat(ascii_name, " [");
	strcat(ascii_name, title_id);
	strcat(ascii_name, "]");
	
print_load("Make Package");
// Make package	
	strcpy(dst, "/dev_hdd0/packages");
	mkdir(dst, 0777);
	
	sprintf(dst, "/dev_hdd0/packages/%s.pkg", ascii_name);
	Delete(dst);
	sprintf(src, "/dev_hdd0/game/%s/USRDIR", ManaGunZ_id);
	if( pkg_pack(dst, content_id, src, "launcher") == FAILED ) {
		print_load("Error : Failed to make PKG");
		Delete(lch);
		return FAILED;
	}
	
// Delete launcher directory
	Delete(lch);
	
	return SUCCESS;
}

//*******************************************************
// Update ManaGunZ
//*******************************************************

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

char *get_str_regex(char *mem, char *format)
{
	char str[255];
	memset(str, 0, 255);
	
	int formatlen = strlen(format);
	int memlen = strlen(mem);
    
	int i,j=0, l=0;
	for(i=0; i<memlen; i++) {
       
		if(format[j]=='*') {
			if(format[j+1] == mem[i]) {
				j++;
			} else {
				str[l] = mem[i];
				l++;
				continue;
			}
		}
		
		if(mem[i] == format[j]) {
			str[l] = mem[i];
			l++;
			j++;
			
			if(j==formatlen) return strcpy_malloc(str);
			
			continue;
		}
		
		j=0;
		l=0;
		memset(str, 0, sizeof(str));
	}
	return NULL;
	
}

void update_MGZ()
{
	start_loading();
	
	char mgz_title[32];
	float current_version;
	float latest_version;
	char link[255];
	
	if(GetParamSFO("TITLE", mgz_title, -1, "/dev_hdd0/game/MANAGUNZ0/PARAM.SFO") == FAILED) {
		print_load("Error : Get current version failed");
		end_loading();
		return;
	}
	
	sscanf(&strrchr(mgz_title, 'v')[1], "%f", &current_version);
		
	print_load("Current version : %.2f", current_version);
	
	Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
	mkdir("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp", 0777);

	if(download("https://github.com/Zarh/ManaGunZ/releases/latest", "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp/upd_mgz")==FAILED) {
		print_load("Error : Download latest failed");
		Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
		end_loading();
		return;
	}
	
	int file_size;
	char *mem = LoadFile("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp/upd_mgz", &file_size);
	if(mem==NULL) {
		print_load("Error : Loadfile latest failed");
		Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
		end_loading();
		return;
	}
	
	char *temp = get_str_regex(mem, "ManaGunZ/releases/download/*/ManaGunZ_v*pkg");
	if(temp==NULL) {
		print_load("Error : link not found");
		free(mem);
		Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
		end_loading();
		return;
	}
	
	sprintf(link, "https://github.com/Zarh/%s", temp);
	
	free(temp);
	
	sscanf(&strrchr(link, 'v')[1], "%f", &latest_version);

	print_load("Latest version : %.2f", latest_version);
	
	if(current_version >= latest_version) {
		show_msg(STR_UP2DATE);
		free(mem);
		Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
		end_loading();
		return;
	}
	
	end_loading();
	
	char diag_msg[64];
	sprintf(diag_msg, "%s v%.2f ?", STR_INSTALL_MGZ, latest_version);
	
	if( DrawDialogYesNo(diag_msg) == YES) {
		start_loading();
		print_head("Downloading...");
		if(download(link, "/dev_hdd0/game/MANAGUNZ0/USRDIR/temp/mgz.pkg")==FAILED) {
			print_load("Error : Download failed");
			free(mem);
			Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
			return;
		}
		
		pkg_unpack("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp/mgz.pkg", "/dev_hdd0/game/MANAGUNZ0");
		Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");		
		
		char *changelog = &strstr(mem, "<div class=\"markdown-body\">")[41];
		if(changelog) {
			changelog[strstr(changelog, "</div>")-changelog] = 0;
			changelog = str_replace(changelog, "<p>", "");
			changelog = str_replace(changelog, "</p>", "\n");
			changelog = str_replace(changelog, "<br>", "");
			
			char temp0[64];
			sprintf(temp0, "***** Changelog ManaGunZ v%.2f *****\n\n", latest_version);
		
			FILE* f;
			f=fopen("/dev_hdd0/game/MANAGUNZ0/USRDIR/sys/Changelog.txt", "w");
			if(f!=NULL) {
				fputs(temp0, f);
				fputs(changelog, f);
				fclose(f);
			}
			if(changelog) free(changelog);
		}
		
		free(mem);
		
		if(Load_GamePIC==YES) end_Load_GamePIC();
		end_load_PIC1();
		end_checking();
		end_loading();
		sysModuleUnload(SYSMODULE_PNGDEC);
		sysModuleUnload(SYSMODULE_JPGDEC);
		ioPadEnd();
		
		sysProcessExitSpawn2("/dev_hdd0/game/MANAGUNZ0/USRDIR/ManaGunZ.self", NULL, NULL, NULL, 0, 64, SYS_PROCESS_SPAWN_STACK_SIZE_128K);
	}
	
	free(mem);
	
	Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/temp");
	
	return;
}

//*******************************************************
// Settings
//*******************************************************

void read_setting()
{
	FILE* fp=NULL;
	char setPath[128];
	
	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/setting.bin", ManaGunZ_id);
	
	fp = fopen(setPath, "rb");
	if(fp!=NULL) {
		fread(&Themes[0], sizeof(char), 0x40, fp);
		fread(&Themes[1], sizeof(char), 0x40, fp);
		fread(&Themes[2], sizeof(char), 0x40, fp);
		fread(&Themes[3], sizeof(char), 0x40, fp);
		fread(&LIST_Show_ICON0, sizeof(u8), 1, fp);
		fread(&UI_position, sizeof(u8), 1, fp);
		fread(&GRID_TYPE, sizeof(u8), 1, fp);
		fread(&GRID_DIRECTION, sizeof(u8), 1, fp);
		fread(&GRID_ANIMATED, sizeof(u8), 1, fp);
		fread(&GRID_KEEP_PROP, sizeof(u8), 1, fp);
		fread(&GRID_NB_LINES, sizeof(u8), 1, fp);
		fread(&GRID_NB_COLUMNS, sizeof(u8), 1, fp);
		fread(&FLOW_inverse_button, sizeof(u8), 1, fp);
		fread(&videoscale_x, sizeof(int8_t), 1, fp);
		fread(&videoscale_y, sizeof(int8_t), 1, fp);
		fread(&COLOR_1, sizeof(u32), 1, fp);
		fread(&COLOR_2, sizeof(u32), 1, fp);
		fread(&COLOR_3, sizeof(u32), 1, fp);
		fread(&COLOR_4, sizeof(u32), 1, fp);
		fread(&XMB_priority, sizeof(u8), 1, fp);
		fread(&Show_COVER, sizeof(u8), 1, fp);
		fread(&Show_PIC1, sizeof(u8), 1, fp);
		fread(&Show_PS3, sizeof(u8), 1, fp);
		fread(&Show_PS2, sizeof(u8), 1, fp);
		fread(&Show_PS1, sizeof(u8), 1, fp);
		fread(&Show_PSP, sizeof(u8), 1, fp);
		fread(&Only_FAV, sizeof(u8), 1, fp);
		fread(&Use_SideMenu, sizeof(u8), 1, fp);
		fread(&Show_GameCase, sizeof(u8), 1, fp);
		fread(&lang_code, sizeof(u8), 1, fp);
		fread(&FLOW_3D, sizeof(u8), 1, fp);
		fread(&Show_Help, sizeof(u8), 1, fp);
		fread(&Show_Waves, sizeof(u8), 1, fp);
		fread(&WAVES_COLOR, sizeof(u32), 1, fp);
		fread(&Font, sizeof(char), 0x40, fp);
		fread(&filter_x, sizeof(float), 1, fp);
		fread(&filter_y, sizeof(float), 1, fp);
		fclose(fp);
	}	
}

void write_setting()
{
#ifdef FILAMANAGER
	UI_position=XMB;
#endif
	
	FILE* fp=NULL;
	char setPath[128];
	
	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/setting.bin", ManaGunZ_id);
	fp = fopen(setPath, "wb");
	if(fp!=NULL) {
		fwrite(&Themes[0], sizeof(char), 0x40, fp);
		fwrite(&Themes[1], sizeof(char), 0x40, fp);
		fwrite(&Themes[2], sizeof(char), 0x40, fp);
		fwrite(&Themes[3], sizeof(char), 0x40, fp);
		fwrite(&LIST_Show_ICON0, sizeof(u8), 1, fp);
		fwrite(&UI_position, sizeof(u8), 1, fp);
		fwrite(&GRID_TYPE, sizeof(u8), 1, fp);
		fwrite(&GRID_DIRECTION, sizeof(u8), 1, fp);
		fwrite(&GRID_ANIMATED, sizeof(u8), 1, fp);
		fwrite(&GRID_KEEP_PROP, sizeof(u8), 1, fp);
		fwrite(&GRID_NB_LINES, sizeof(u8), 1, fp);
		fwrite(&GRID_NB_COLUMNS, sizeof(u8), 1, fp);
		fwrite(&FLOW_inverse_button, sizeof(u8), 1, fp);
		fwrite(&videoscale_x, sizeof(int8_t), 1, fp);
		fwrite(&videoscale_y, sizeof(int8_t), 1, fp);
		fwrite(&COLOR_1, sizeof(u32), 1, fp);
		fwrite(&COLOR_2, sizeof(u32), 1, fp);
		fwrite(&COLOR_3, sizeof(u32), 1, fp);
		fwrite(&COLOR_4, sizeof(u32), 1, fp);
		fwrite(&XMB_priority, sizeof(u8), 1, fp);
		fwrite(&Show_COVER, sizeof(u8), 1, fp);
		fwrite(&Show_PIC1, sizeof(u8), 1, fp);
		fwrite(&Show_PS3, sizeof(u8), 1, fp);
		fwrite(&Show_PS2, sizeof(u8), 1, fp);
		fwrite(&Show_PS1, sizeof(u8), 1, fp);
		fwrite(&Show_PSP, sizeof(u8), 1, fp);
		fwrite(&Only_FAV, sizeof(u8), 1, fp);
		fwrite(&Use_SideMenu, sizeof(u8), 1, fp);
		fwrite(&Show_GameCase, sizeof(u8), 1, fp);
		fwrite(&lang_code, sizeof(u8), 1, fp);
		fwrite(&FLOW_3D, sizeof(u8), 1, fp);
		fwrite(&Show_Help, sizeof(u8), 1, fp);
		fwrite(&Show_Waves, sizeof(u8), 1, fp);
		fwrite(&WAVES_COLOR, sizeof(u32), 1, fp);
		fwrite(&Font, sizeof(char), 0x40, fp);
		fwrite(&filter_x, sizeof(float), 1, fp);
		fwrite(&filter_y, sizeof(float), 1, fp);
		fclose(fp);
		SetFilePerms(setPath);
	}
	
	char sfo[64];
	sprintf(sfo, "/dev_hdd0/game/%s/PARAM.SFO", ManaGunZ_id);
	SetParamSFO("ITEM_PRIORITY", (char *) &XMB_priority, 0, sfo);
	
	if(lang_code != lang_code_loaded) update_lang();

	if(Load_GamePIC == NO && COVER_Loaded == NO && Show_COVER == YES) {
		start_Load_GamePIC();
	}
	
	read_setting();
}

void read_game_setting(char *file_name)
{
	FILE* fp=NULL;
	char setPath[128];
	
	if(iso) sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[ISO]%s.bin", ManaGunZ_id, file_name);
	else	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[JB]%s.bin", ManaGunZ_id, file_name);
	fp = fopen(setPath, "rb");
	if(fp!=NULL)	{
		fread(&direct_boot, sizeof(u8), 1, fp);
		fread(&clean_syscall, sizeof(u8), 1, fp);
		fread(&change_IDPS, sizeof(u8), 1, fp);
		fread(&IDPS, sizeof(long long unsigned int), 2, fp);
		fread(&ext_game_data, sizeof(u8), 1, fp);
		fread(&payload, sizeof(u8), 1, fp);
		fread(&prim_USB, sizeof(u8), 1, fp);
		fread(&emu, sizeof(u8), 1, fp);
		fread(&libfs_from, sizeof(u8), 1, fp);
		fread(&mount_app_home, sizeof(u8), 1, fp);
		fread(&use_ex_plug, sizeof(u8), 1, fp);
		fclose(fp);
	} 
	else {
		direct_boot = NO;
		clean_syscall = NO;
		change_IDPS = NO;
		peek_IDPS();
		ext_game_data = NO;
		if(iso) payload=SNAKE;
		else payload=MM;
		prim_USB=NO;
		emu=NONE;
		libfs_from=MM;
		mount_app_home=NO;
		use_ex_plug=NO;
	}
	
	if(iso) payload=SNAKE;
	if(PEEKnPOKE==NO) payload=SNAKE;
}

void write_game_setting(char *file_name)
{
	if(AutoM == YES) return;

	FILE* fp=NULL;
	char setPath[128];
	
	if(iso) sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[ISO]%s.bin", ManaGunZ_id, file_name);
	else	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[JB]%s.bin", ManaGunZ_id, file_name);
	fp = fopen(setPath, "wb");
	if(fp!=NULL)	{
		fwrite(&direct_boot, sizeof(u8), 1, fp);
		fwrite(&clean_syscall, sizeof(u8), 1, fp);
		fwrite(&change_IDPS, sizeof(u8), 1, fp);
		fwrite(&IDPS, sizeof(long long unsigned int), 2, fp);
		fwrite(&ext_game_data, sizeof(u8), 1, fp);
		fwrite(&payload, sizeof(u8), 1, fp);
		fwrite(&prim_USB, sizeof(u8), 1, fp);
		fwrite(&emu, sizeof(u8), 1, fp);
		fwrite(&libfs_from, sizeof(u8), 1, fp);
		fwrite(&mount_app_home, sizeof(u8), 1, fp);
		fwrite(&use_ex_plug, sizeof(u8), 1, fp);
		fclose(fp);
	}
	read_game_setting(file_name);
}

void write_fav()
{
	FILE* fp=NULL;
	char favPath[128];
	int i;
	u16 path_size;
	
	sprintf(favPath, "/dev_hdd0/game/%s/USRDIR/setting/fav.bin", ManaGunZ_id);
	fp = fopen(favPath, "wb");
	if(fp!=NULL)	{
		fwrite(&FAV_game_number, sizeof(u8), 1, fp);
		for(i=0; i <= FAV_game_number; i++) {
			path_size = sizeof(char)*strlen(list_FAV_game_title[i]);
			fwrite(&path_size, sizeof(u16), 1, fp);
			fwrite(list_FAV_game_title[i], path_size, 1, fp);
			path_size = sizeof(char)*strlen(list_FAV_game_path[i]);
			fwrite(&path_size, sizeof(u16), 1, fp);
			fwrite(list_FAV_game_path[i], path_size, 1, fp);
		}
		fclose(fp);
	}
}

void read_fav()
{
	FILE* fp=NULL;
	char favPath[128];
	int i;
	u16 path_size;
	
	sprintf(favPath, "/dev_hdd0/game/%s/USRDIR/setting/fav.bin", ManaGunZ_id);
	fp = fopen(favPath, "rb");
	if(fp!=NULL)	{
		fread(&FAV_game_number, sizeof(u8), 1, fp);
		for(i=0; i <= FAV_game_number; i++) {
			path_size = sizeof(char)*strlen(list_FAV_game_title[i]);
			fread(&path_size, sizeof(u16), 1, fp);
			fread(list_FAV_game_title[i], path_size, 1, fp);
			path_size = sizeof(char)*strlen(list_FAV_game_path[i]);
			fread(&path_size, sizeof(u16), 1, fp);
			fread(list_FAV_game_path[i], path_size, 1, fp);
		}
		fclose(fp);
	}
}

u8 is_favorite(char *path)
{
	int j;
	for(j=0;j <= FAV_game_number; j++) {
		if(strcmp(list_FAV_game_path[j], path) == 0) return YES;
	}
	return NO;
}

u8 add_favorite()
{
	FAV_game_number++;
	strcpy(list_FAV_game_title[FAV_game_number], list_game_title[position]);
	strcpy(list_FAV_game_path[FAV_game_number], list_game_path[position]);
	write_fav();

	return is_favorite(list_game_path[position]);
}

u8 remove_favorite()
{
	int i, j;
	for(i=0; i <= FAV_game_number; i++) {
		if(strcmp(list_game_path[position], list_FAV_game_path[i]) == 0 ) {
			for(j=i; j<=FAV_game_number; j++) {
				strcpy(list_FAV_game_path[j], list_FAV_game_path[j+1]);
			}
			strcpy(list_FAV_game_path[FAV_game_number], "");
			FAV_game_number--;
			write_fav();
			
			break;
		}
	}
	
	if(is_favorite(list_game_path[position]) == YES) return FAILED;
	
	return SUCCESS;
}

//*******************************************************
//ResetBD
//*******************************************************

int umount_iso()
{
	u8 m;
	unsigned int real_disctype, effective_disctype, iso_disctype;
	cobra_get_disc_type(&real_disctype, &effective_disctype, &iso_disctype);

	//if (iso_disctype == DISC_TYPE_NONE)	return 0;
	
	if (effective_disctype != DISC_TYPE_NONE) {
		cobra_send_fake_disc_eject_event();
		usleep(4000);
	}
	
	cobra_umount_disc_image();
	
	// If there is a real disc in the system, issue an insert event
	if (real_disctype != DISC_TYPE_NONE)
	{
		cobra_send_fake_disc_insert_event();
		for(m=0; m<22; m++)
		{
			usleep(4000);
			if(path_info("/dev_bdvd") != _NOT_EXIST) break;
		}
		cobra_disc_auth();
	}
	return 0;
}

void clean_tables()
{
	int i;
	for(i=0; i<0x400; i+=8) {
		lv2poke(0x80000000007FAE00ULL + i, 0x0000000000000000ULL);
		lv2poke(0x80000000007FDB00ULL + i, 0x0000000000000000ULL);
	}
}

//*******************************************************
// Init ManaGunZ
//*******************************************************

int init_ManaGunZ()
{
	int i;

	cobra = is_cobra();
	mamba = is_mamba();
	
	if(PEEKnPOKE) {
		peek_IDPS();
		print_load("Reset BD");
		unpatch_bdmirror();
		clean_tables();
	}
	
	if(cobra) {
		cobra_lib_init();
		umount_iso();
		usleep(4000);
		//cobra_map_game(NULL,NULL,NULL); bug
		//cobra_map_paths(NULL,NULL, 0); bug
		{sys_map_path((char*)"/dev_bdvd", NULL);}
		{sys_map_path((char*)"//dev_bdvd", NULL);}
		{sys_map_path((char*)"/app_home", NULL);}
		{sys_map_path((char*)"//app_home", NULL);}
		{sys_map_path("/dev_flash/sys/external/libfs.sprx", NULL);}
		{sys_map_path("/dev_flash/vsh/module/explore_plugin.sprx", NULL);}
		usleep(4000);
		cobra_unset_psp_umd();
	}
	else if(mamba) {
		umount_iso();
		usleep(4000);
		{mamba_map((char*)"/dev_bdvd", NULL);}
		{mamba_map((char*)"//dev_bdvd", NULL);}
		{mamba_map((char*)"/app_home", NULL);}
		{mamba_map((char*)"//app_home", NULL);}
		{mamba_map((char*)"//app_home", NULL);}
		{mamba_map("/dev_flash/sys/external/libfs.sprx", NULL);}
		{mamba_map("/dev_flash/vsh/module/explore_plugin.sprx", NULL);}
	}

	sys_fs_umount("/dev_bdvd");
	sys_fs_umount("/dev_ps2disk");
	sys_fs_mount("CELL_FS_IOS:PATA0_BDVD_DRIVE", "CELL_FS_ISO9660", "/dev_bdvd", 1);
	
	/*
	if(cobra) {
		unsigned int real_disctype;
		cobra_get_disc_type(&real_disctype, NULL, NULL);
		if (real_disctype == DISC_TYPE_NONE) real_disk = NO; else
		real_disk = YES;
	} else {
		if(path_info("/dev_bdvd") == _NOT_EXIST) real_disk = NO; else
		real_disk = YES;
	}
	*/
	
	getDevices();

	char temp[128];
	for(i=0; i<=device_number; i++) {
		sprintf(temp, "/%s", list_device[i]);
		move_bdemubackup_to_origin(temp);
	}
	if(path_info("/dev_hdd0/game/MANAGUNZ0/USRDIR/sys/Changelog.txt") == _FILE) {
		open_txt_viewer("/dev_hdd0/game/MANAGUNZ0/USRDIR/sys/Changelog.txt");
		Delete("/dev_hdd0/game/MANAGUNZ0/USRDIR/sys/Changelog.txt");
	}
	
	return OK;
}

//*******************************************************
// PAD
//*******************************************************

void get_R2speed()
{
	if(old_pad & BUTTON_R2) {
		R2speed = 6 - paddata.PRE_R2/50;
	} else R2speed=6;
	
	if(old_pad & BUTTON_LEFT || old_pad & BUTTON_RIGHT || old_pad & BUTTON_UP || old_pad & BUTTON_DOWN) {
		hold_it++;
		if(hold_it > 30) {
			slow_it++;
			if(R2speed < slow_it) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}	
}

u8 R2pad(int button)
{
	return (new_pad & button || ((old_pad & button) && slow_it==0));
}

float R2JoyStick_X(int joystick)
{
	float joy_x;
	
	if(joystick == BUTTON_R) {
		joy_x = (paddata.button[4] - 128.0f);
	} else
	if(joystick == BUTTON_L) {
		joy_x = (paddata.button[6] - 128.0f);
	} else return 0;
	
	if(28.0f < abs(joy_x) ) {
		return (float) (joy_x / (R2speed*5+1));
	}
	
	return 0;
}

float R2JoyStick_Y(int joystick)
{
	float joy_y;
	
	if(joystick == BUTTON_R) {
		joy_y = (paddata.button[5] - 128.0f);
	} else
	if(joystick == BUTTON_L) {
		joy_y = (paddata.button[7] - 128.0f);
	} else return 0;
	
	if(28.0f < abs(joy_y)) {
		return (float) (joy_y / (R2speed*5+1));
	}
	
	return 0;
}

//*******************************************************
// File Manager
//*******************************************************

void init_FileExplorer()
{
	int i;

	window_x = (float *) malloc(WINDOW_MAX * sizeof(float));
	window_y = (float *) malloc(WINDOW_MAX * sizeof(float));
	window_z = (float *) malloc(WINDOW_MAX * sizeof(float));
	window_h = (float *) malloc(WINDOW_MAX * sizeof(float));
	window_w = (float *) malloc(WINDOW_MAX * sizeof(float));
		
	window_path = (char **) malloc(WINDOW_MAX * sizeof(char *));
	for(i=0; i<WINDOW_MAX; i++) window_path[i]=NULL;
	window_lastpath = (char **) malloc(WINDOW_MAX * sizeof(char *));
	for(i=0; i<WINDOW_MAX; i++) window_lastpath[i]=NULL;
	window_content_Name = (char ***) malloc(WINDOW_MAX * sizeof(char **));
	for(i=0; i<WINDOW_MAX; i++) window_content_Name[i]=NULL;
	window_content_Size = (u64 **) malloc(WINDOW_MAX * sizeof(u64 *));
	for(i=0; i<WINDOW_MAX; i++) window_content_Size[i]=NULL;
	window_content_Type = (u8 **) malloc(WINDOW_MAX * sizeof(u8 *));
	for(i=0; i<WINDOW_MAX; i++) window_content_Type[i]=NULL;
	window_content_Selected = (u8 **) malloc(WINDOW_MAX * sizeof(u8 *));
	for(i=0; i<WINDOW_MAX; i++) window_content_Selected[i]=NULL;
	
	window_sort = (u8 *) malloc(WINDOW_MAX * sizeof(u8));
	window_w_col_size = (float *) malloc(WINDOW_MAX * sizeof(float));
	
	window_content_N = (int *) malloc(WINDOW_MAX * sizeof(int));
	window_open = (u8 *) malloc(WINDOW_MAX * sizeof(u8));
	//for(i=0; i<WINDOW_MAX; i++) window_open[i]=NO; freeze...
	memset(window_open, 0, sizeof(window_open));
	
	window_scroll_N = (u32 *) malloc(WINDOW_MAX * sizeof(u32));
	window_scroll_P = (u32 *) malloc(WINDOW_MAX * sizeof(u32));
	window_scroll_size = (float *) malloc(WINDOW_MAX * sizeof(float));
	window_scroll_y = (float *) malloc(WINDOW_MAX * sizeof(float));
	
	window_item_N = (s8 *) malloc(WINDOW_MAX * sizeof(s8));
	
	option_copy = (char **) malloc(WINDOW_MAX_ITEMS * sizeof(char *));
	for(i=0; i<WINDOW_MAX_ITEMS; i++) option_copy[i]=NULL;
}

void finalize_FileExplorer()
{

	u32 i,j;

	FREE(window_x);
	FREE(window_y);
	FREE(window_z);
	FREE(window_h);
	FREE(window_w);

	for(i=0; i<WINDOW_MAX; i++) FREE(window_path[i]);
	FREE(window_path);

	for(i=0; i<WINDOW_MAX; i++) FREE(window_lastpath[i]);
	FREE(window_lastpath);
	
	for(i=0; i<WINDOW_MAX; i++) {
		if(window_content_Name[i] == NULL) continue;
		for(j=0; j<WINDOW_MAX_ITEMS; j++) {
			FREE(window_content_Name[i][j]);
		}
		FREE(window_content_Name[i]);
	}
	FREE(window_content_Name);

	for(i=0; i<WINDOW_MAX; i++) FREE(window_content_Size[i]);
	FREE(window_content_Size);
	for(i=0; i<WINDOW_MAX; i++) FREE(window_content_Type[i]);
	FREE(window_content_Type);
	for(i=0; i<WINDOW_MAX; i++) FREE(window_content_Selected[i]);
	FREE(window_content_Selected);

	FREE(window_sort);
	FREE(window_w_col_size);

	FREE(window_content_N);
	FREE(window_open);

	FREE(window_scroll_N);
	FREE(window_scroll_P);
	FREE(window_scroll_size);
	FREE(window_scroll_y);

	FREE(window_item_N);

	for(i=0; i<WINDOW_MAX_ITEMS; i++) FREE(option_copy[i]);
	FREE(option_copy);
}

// *** PRX list tools ***
u8 is_it_inside(char *file_path, char *str)
{
	int size;
	char *buff = LoadFile(file_path, &size);
	if(buff==NULL) return NO;
	
	if(strstr(buff, str) != NULL) {
		free(buff);
		return YES;
	}
	
	free(buff);

	return NO;

}

void add_to_list(char *file_path, char *str)
{
	FILE* fr;
	FILE* fw;
	char line[255];
	char temp[255];
	
	strcpy(temp, file_path);
	strcat(temp, "_temp");
	
	fr=fopen(file_path, "rb");
	if(fr==NULL) return;
	fw=fopen(temp, "wb");
	if(fw==NULL) return;
	
	uint8_t FirstLine = YES;
	
	while(fgets(line, 255, fr) != NULL) {
		if(line[0]=='\r' || line[0]=='\n') continue;
		
		strtok(line, "\r\n");
		if(FirstLine==NO) fputs("\n", fw);
		fputs(line, fw);
		FirstLine=NO;
	}
	
	if(FirstLine==NO) fputs("\n", fw);
	fputs(str, fw);
	
	fclose(fr);
	fclose(fw);
	
	unlink(file_path);
	rename(temp, file_path);
}

void remove_from_list(char *file_path, char *str)
{
	FILE* fr;
	FILE* fw;
	char line[255];
	char temp[255];
	
	strcpy(temp, file_path);
	strcat(temp, "_temp");
	
	fr=fopen(file_path, "rb");
	if(fr==NULL) return;
	fw=fopen(temp, "wb");
	if(fw==NULL) return;
	
	uint8_t FirstLine = YES;
	
	while(fgets(line, 255, fr) != NULL) {
		if(line[0]=='\r' || line[0]=='\n') continue;
		strtok(line, "\r\n");
		if(strcmp(line, str) == 0) continue;
		if(FirstLine==NO) fputs("\n", fw);
		fputs(line, fw);
		FirstLine=NO;
	}
	
	fclose(fr);
	fclose(fw);
	
	unlink(file_path);
	rename(temp, file_path);
}

void plugins_move(char *file_path, char *plugin_dir)
{
	FILE* fr;
	FILE* fw;
	char line[255];
	char temp[255];
	
	char Plug_NEW[255];
	
	int len = strlen(plugin_dir);
	
	strcpy(temp, file_path);
	strcat(temp, "_temp");
	
	fr=fopen(file_path, "rb");
	if(fr==NULL) return;
	fw=fopen(temp, "wb");
	if(fw==NULL) return;
	
	uint8_t FirstLine = YES;
	
	while(fgets(line, 255, fr) != NULL) {
		if(line[0]=='\r' || line[0]=='\n') continue;
		strtok(line, "\r\n");
		
		if(strncmp(line, plugin_dir, len) != 0) {
			sprintf(Plug_NEW, "%s/%s", plugin_dir, &strrchr(line, '/')[1]);
			if( Move(line, Plug_NEW) == SUCCESS) strcpy(line, Plug_NEW);
		}
		
		if(FirstLine==NO) fputs("\n", fw);
		fputs(line, fw);
		FirstLine=NO;
	}
	
	fclose(fr);
	fclose(fw);
	
	unlink(file_path);
	rename(temp, file_path);
}

// *** ICONS ***
void DrawIcon_Directory(float x, float y, float z)
{
	// CONTENT_FSIZE = 15;
	
	if(PICTURE_offset[FOLDER] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[FOLDER], PICTURE[FOLDER].width, PICTURE[FOLDER].height, PICTURE[FOLDER].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x+1, y+1, z, 0, 13, 13, WHITE, YES);
	} else {
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(x+1 , y+1 , z);
		tiny3d_VertexColor(0xFFC90EFF);
		tiny3d_VertexPos(x+11 , y+1 , z);
		tiny3d_VertexPos(x+11 , y+6 , z);
		tiny3d_VertexPos(x+13 , y+8 , z);
		tiny3d_VertexPos(x+13 , y+12 , z);
		tiny3d_VertexPos(x+1  , y+12 , z);
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(x+1 , y+1 , z);
		tiny3d_VertexColor(0xFFE280FF);
		tiny3d_VertexPos(x+7 , y+3 , z);
		tiny3d_VertexPos(x+7 , y+14 , z);
		tiny3d_VertexPos(x+1 , y+12 , z);
		tiny3d_End();

		tiny3d_SetPolygon(TINY3D_LINES);
		tiny3d_VertexPos(x+1 , y+1 , z);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(x+11 , y+1 , z);
		tiny3d_VertexPos(x+11 , y+6 , z);
		tiny3d_VertexPos(x+13 , y+8 , z);
		tiny3d_VertexPos(x+13 , y+12 , z);
		tiny3d_VertexPos(x+7  , y+12 , z);
		tiny3d_End();

		tiny3d_SetPolygon(TINY3D_LINE_LOOP);
		tiny3d_VertexPos(x+1 , y+1 , z);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(x+7 , y+3 , z);
		tiny3d_VertexPos(x+7 , y+14 , z);
		tiny3d_VertexPos(x+1 , y+12 , z);
		tiny3d_End();

		tiny3d_SetPolygon(TINY3D_LINES);
		tiny3d_VertexPos(x+12 , y+9 , z);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(x+12 , y+11 , z);
		tiny3d_End();
	}

}

void DrawIcon_File(float x, float y, float z, u32 color)
{
	// CONTENT_FSIZE = 15
	
	if(PICTURE_offset[FILES] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[FILES], PICTURE[FILES].width, PICTURE[FILES].height, PICTURE[FILES].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x+1, y+1, z, 0, 13, 13, color, YES);
	} else {
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(x+2 , y+1 , z);
		tiny3d_VertexColor(color);
		tiny3d_VertexPos(x+10, y+1 , z);
		tiny3d_VertexPos(x+13, y+4 , z);
		tiny3d_VertexPos(x+13, y+14 , z);
		tiny3d_VertexPos(x+2 , y+14 , z);
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_LINE_LOOP);
		tiny3d_VertexPos(x+2 , y+1 , z);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(x+10, y+1 , z);
		tiny3d_VertexPos(x+13, y+4 , z);
		tiny3d_VertexPos(x+13, y+14 , z);
		tiny3d_VertexPos(x+2 , y+14 , z);
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_LINES);
		tiny3d_VertexPos(x+10 , y+1 , z);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(x+10, y+4 , z);
		tiny3d_VertexPos(x+13, y+4 , z);
		tiny3d_End();
	}
	
}

void DrawIcon_TXT(float x, float y, float z, u32 color)
{
	DrawIcon_File(x, y, z, WHITE);
	
	tiny3d_SetPolygon(TINY3D_LINES);
	tiny3d_VertexPos(x+2 , y+6 , z);
	tiny3d_VertexColor(BLUE);
	tiny3d_VertexPos(x+13, y+6 , z);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_LINES);
	tiny3d_VertexPos(x+2 , y+8 , z);
	tiny3d_VertexColor(BLUE);
	tiny3d_VertexPos(x+13, y+8 , z);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_LINES);
	tiny3d_VertexPos(x+2 , y+10 , z);
	tiny3d_VertexColor(BLUE);
	tiny3d_VertexPos(x+13, y+10 , z);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_LINES);
	tiny3d_VertexPos(x+2 , y+12 , z);
	tiny3d_VertexColor(BLUE);
	tiny3d_VertexPos(x+13, y+12 , z);
	tiny3d_End();

}

//**** DOCK ****

#define WINDOW_LOC_UNK			0
#define WINDOW_LOC_DEFAULT		1
#define WINDOW_LOC_RIGHT		2
#define WINDOW_LOC_LEFT			3
#define WINDOW_LOC_FULL			4

void SetWindowLocation(int WINDOW_LOC)
{
	switch(WINDOW_LOC)
	{
		case WINDOW_LOC_DEFAULT:
		{
			window_x[window_activ]=100+30*window_activ;
			window_y[window_activ]=30+30*window_activ;
			window_h[window_activ]=335;
			window_w[window_activ]=500;
			break;
		}
		case WINDOW_LOC_RIGHT:
		{
			window_x[window_activ]=X_MAX/2;
			window_y[window_activ]=0;
			window_w[window_activ]=X_MAX/2;
			window_h[window_activ]=Y_MAX-45;
			break;
		}
		case WINDOW_LOC_LEFT:
		{
			window_x[window_activ]=0;
			window_y[window_activ]=0;
			window_w[window_activ]=X_MAX/2;
			window_h[window_activ]=Y_MAX-45;
			break;
		}
		case WINDOW_LOC_FULL:
		{
			window_x[window_activ]=0;
			window_y[window_activ]=0;
			window_w[window_activ]=X_MAX;
			window_h[window_activ]=Y_MAX-45;
			break;
		}
		default:
			break;
	}
}

u8 GetWindowLocation()
{
	if( window_x[window_activ]==100+30*window_activ
	&&	window_y[window_activ]==30+30*window_activ
	&&	window_h[window_activ]==335
	&&	window_w[window_activ]==500) 
		return WINDOW_LOC_DEFAULT;
	else 
	if(	window_x[window_activ]==X_MAX/2
	&&	window_y[window_activ]==0
	&&	window_w[window_activ]==X_MAX/2
	&&	window_h[window_activ]==Y_MAX-45)
		return WINDOW_LOC_RIGHT;
	else
	if( window_x[window_activ]==0
	&&	window_y[window_activ]==0
	&&	window_w[window_activ]==X_MAX/2
	&&	window_h[window_activ]==Y_MAX-45)
		return WINDOW_LOC_LEFT;
	else
	if( window_x[window_activ]==0
	&&	window_y[window_activ]==0
	&&	window_w[window_activ]==X_MAX
	&&	window_h[window_activ]==Y_MAX-45)
		return WINDOW_LOC_FULL;
	
	return WINDOW_LOC_UNK;
	
}

// *** Window ***
void Draw_window()
{
	int n;
	
	for(n=0; n<10; n++) {
		if(window_open[n]==NO) continue;
		
		SetFontZ(window_z[n]);	
		
		//MAIN BOX
		if(window_activ==n) Draw_Box(window_x[n], window_y[n], window_z[n], 3, window_w[n], window_h[n], 0x4080D0FF, NO);
		else Draw_Box(window_x[n], window_y[n], window_z[n], 3, window_w[n], window_h[n], 0x205070FF, NO);
		
		//TOP
		
		char TOP_str[255];
		FontSize(TOP_H/2);
		FontColor(WHITE);
		
		strcpy(TOP_str, window_path[n]);
		if(strcmp(TOP_str, "/") == 0 ) strcat(TOP_str, "root");
		if( GetWidth(TOP_str) > window_w[n] - 50) {
			sprintf(TOP_str, "...%s", strrchr(window_path[n], '/'));
			while(GetWidth(TOP_str) > window_w[n] - 50) {
				TOP_str[strlen(TOP_str)-1] = 0;
				TOP_str[strlen(TOP_str)-1] = 0;
				TOP_str[strlen(TOP_str)-1] = 0;
				TOP_str[strlen(TOP_str)-1] = 0;
				TOP_str[strlen(TOP_str)] = '.';
				TOP_str[strlen(TOP_str)] = '.';
				TOP_str[strlen(TOP_str)] = '.';
			}
		}
		DrawString(window_x[n]+BORDER, window_y[n]+10, TOP_str);
		
		//CLOSE BOX
		Draw_Box(window_x[n]+window_w[n]-40, window_y[n]+10, window_z[n], 0, 30, 20, RED, NO);	
		DrawStringFromCenterX(window_x[n]+window_w[n]-40+15, window_y[n]+11, "X");

		//CONTENT BOX
		FontSize(CONTENT_FSIZE);
		FontColor(BLACK);

		Draw_Box(window_x[n]+BORDER, window_y[n]+TOP_H, window_z[n], 0,  window_w[n]-BORDER*2, window_h[n]-TOP_H-BORDER, 0xF0F0F0FF, NO);
		
		//COLUMN HEADER BOX
		Draw_Box(window_x[n]+BORDER, window_y[n]+TOP_H,  window_z[n], 0, window_w[n]-BORDER*2, COL_H, 0xD4DBEDFF, NO); 
		DrawString(window_x[n]+BORDER+5, window_y[n]+TOP_H+3, STR_NAME);
		
		if(window_w_col_size[n]< COL_W_MIN) window_w_col_size[n]=COL_W_MIN;
		if(window_w[n] - window_w_col_size[n] - BORDER*2 - SCROLL_W < COL_W_MIN) window_w_col_size[n] = window_w[n] - COL_W_MIN - BORDER*2 - SCROLL_W;
		
		tiny3d_SetPolygon(TINY3D_LINES);
		tiny3d_VertexPos(window_x[n]+window_w[n] - BORDER-SCROLL_W-window_w_col_size[n], window_y[n]+TOP_H+2 , window_z[n]);
		tiny3d_VertexColor(0x505050FF);
		tiny3d_VertexPos(window_x[n]+window_w[n] - BORDER-SCROLL_W-window_w_col_size[n], window_y[n]+TOP_H+COL_H-2 , window_z[n]);
		tiny3d_End();
		
		DrawString(window_x[n]+window_w[n]-BORDER-SCROLL_W-window_w_col_size[n] + 5, window_y[n]+TOP_H+3, STR_SIZE);
		
		//SCROLL BAR
		window_item_N[n] = ((window_h[n] - TOP_H-COL_H-BORDER) / CONTENT_FSIZE) - 1;
		window_scroll_N[n] = 0;
		if(window_content_N[n] > window_item_N[n] ) window_scroll_N[n] = window_content_N[n] - window_item_N[n];
		if(window_scroll_P[n] > window_scroll_N[n]) window_scroll_P[n] = window_scroll_N[n];
		
		Draw_Box(window_x[n]+window_w[n]-BORDER-SCROLL_W, window_y[n]+TOP_H+COL_H, window_z[n],  0, SCROLL_W, window_h[n]-TOP_H-COL_H-BORDER, 0xD0D0D0FF, NO);

		if(window_scroll_N[n]>0) {
			window_scroll_size[n] = (window_h[n]-TOP_H-COL_H-BORDER) - (SCROLL_H_MIN*window_scroll_N[n]);
			if( window_scroll_size[n] < SCROLL_H_MIN ) window_scroll_size[n] = SCROLL_H_MIN;
			
			window_scroll_y[n]	= (window_h[n]-TOP_H-COL_H-window_scroll_size[n]-BORDER) * window_scroll_P[n] / window_scroll_N[n];
			if(n==window_activ) window_scroll_y[n] += curs_move_scroll;
			if(window_scroll_y[n] < 0) window_scroll_y[n]=0;
			
			Draw_Box(window_x[n]+window_w[n]-BORDER-SCROLL_W, window_y[n]+TOP_H+COL_H+window_scroll_y[n], window_z[n], 0, SCROLL_W, window_scroll_size[n], 0x9090C0FF, NO);
		}
		
		// CONTENT
		int i;
		for(i=0 ; i<=window_item_N[n]; i++) {
			if(window_content_N[n] < i+window_scroll_P[n]) break;
			
			if(  window_x[window_activ]+BORDER				        < curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W
			&&	 window_y[window_activ]+TOP_H+COL_H+CONTENT_FSIZE*i	< curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H+CONTENT_FSIZE*(i+1)				
			&& n==window_activ	&& option_activ == NO && prop_activ == NO)
			{
				Draw_Box(window_x[window_activ]+BORDER, window_y[window_activ]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[window_activ], 0, window_w[window_activ]-5-10-5, CONTENT_FSIZE,  0x00D0FFFF, NO);
			}
			
			if(window_content_Selected[n][i+window_scroll_P[n]] == YES) {
				Draw_Box(window_x[n]+5, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 0, window_w[n]-5-10-5, CONTENT_FSIZE,  0x0090FFFF, NO);
			}
			
			DrawTXTInBox(window_x[n]+BORDER+ICON+5, 
						 window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, 
						 window_z[n], 
						 window_w[n]- BORDER*2-SCROLL_W-window_w_col_size[n]-ICON-5-5-5, 
						 1, 
						 window_content_Name[n][window_scroll_P[n]+i], 
						 0, BLACK);
			
			if(window_content_Type[n][window_scroll_P[n]+i] != _DIRECTORY) {
				char *size_str = get_unit(window_content_Size[n][window_scroll_P[n]+i]);
				float size_str_w = GetWidth(size_str);
				DrawString(window_x[n]+window_w[n]-BORDER-SCROLL_W-size_str_w - 5  , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, size_str);
				free(size_str);
			}
			
			u8 ext = window_content_Type[n][window_scroll_P[n]+i];
			
			if(ext == _DIRECTORY) {
				DrawIcon_Directory(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n]);
			} 
			else if(ext == _PNG || ext == _JPG) {
				DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], GREEN);
			}
			else if(ext == _SELF || ext == _SPRX || ext == _EBOOT_BIN) {
				DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], RED);
			}
			else if(ext == _ELF || ext == _PRX || ext == _EBOOT_ELF) {
				DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], ORANGE);
			}
			else if(ext == _PKG) {
				DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], BLUE);
			}
			else if(ext == _RCO) {
				DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], PURPLE);
			}
			else if(ext == _TRP) {
				DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], PINK);
			}
			else if(ext == _SFO) {
				DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], GREY);
			}
			else if(can_read(ext)==YES) {
				DrawIcon_TXT(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], WHITE);
			}
			else if(ext == _ISO) {
				Draw_DISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, COLOR_ISO);
			}
			else if(ext == _ISO_PS3) {
				Draw_GAMEDISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, _ISO_PS3);
			}
			else if(ext == _ISO_PS2) {
				Draw_GAMEDISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, _ISO_PS2);
			}
			else if(ext == _ISO_PS1) {
				Draw_GAMEDISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, _ISO_PS1);
			}
			else if(ext == _ISO_PSP) {
				Draw_GAMEDISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, _ISO_PSP);
			}
			else DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], WHITE);
			
		}
	}
}

void Draw_cursor()
{	
	if(loading) return; 
	
	if(window_resize_H == YES) {
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x-9 , curs_y , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x-5 , curs_y-4 , 0);
		tiny3d_VertexPos(curs_x-5 , curs_y+4 , 0);
		tiny3d_End();
		
		if(curs_push==YES) Draw_Box(curs_x-5, curs_y-1, 0, 0, 10, 2, RED, NO); else Draw_Box(curs_x-5, curs_y-1, 0, 0, 10, 2, WHITE, NO);
		
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x+9 , curs_y , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x+5 , curs_y-4 , 0);
		tiny3d_VertexPos(curs_x+5 , curs_y+4 , 0);
		tiny3d_End();
		
		tiny3d_SetPolygon(TINY3D_LINE_LOOP);
		tiny3d_VertexPos(curs_x-9 , curs_y , 0);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(curs_x-5 , curs_y-4 , 0);
		tiny3d_VertexPos(curs_x-5 , curs_y-1 , 0);
		tiny3d_VertexPos(curs_x+5 , curs_y-1 , 0);
		tiny3d_VertexPos(curs_x+5 , curs_y-4 , 0);
		tiny3d_VertexPos(curs_x+9 , curs_y , 0);
		tiny3d_VertexPos(curs_x+5 , curs_y+4 , 0);
		tiny3d_VertexPos(curs_x+5 , curs_y+1 , 0);
		tiny3d_VertexPos(curs_x-5 , curs_y+1 , 0);
		tiny3d_VertexPos(curs_x-5 , curs_y+4 , 0);
		tiny3d_End();
	} else 
	if(window_resize_V == YES) {
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x   , curs_y-9 , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x-4 , curs_y-5 , 0);
		tiny3d_VertexPos(curs_x+4 , curs_y-5 , 0);
		tiny3d_End();
		if(curs_push==YES) Draw_Box(curs_x-1, curs_y-5, 0, 0, 2, 10, RED, NO); else Draw_Box(curs_x-1, curs_y-5, 0, 0, 2, 10, WHITE, NO);
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x   , curs_y+9 , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x-4 , curs_y+5 , 0);
		tiny3d_VertexPos(curs_x+4 , curs_y+5 , 0);
		tiny3d_End();
		
		tiny3d_SetPolygon(TINY3D_LINE_LOOP);
		tiny3d_VertexPos(curs_x   , curs_y-9 , 0);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(curs_x-4 , curs_y-5 , 0);
		tiny3d_VertexPos(curs_x-1 , curs_y-5 , 0);
		tiny3d_VertexPos(curs_x-1 , curs_y+5 , 0);
		tiny3d_VertexPos(curs_x-4 , curs_y+5 , 0);
		tiny3d_VertexPos(curs_x   , curs_y+9 , 0);
		tiny3d_VertexPos(curs_x+4 , curs_y+5 , 0);
		tiny3d_VertexPos(curs_x+1 , curs_y+5 , 0);
		tiny3d_VertexPos(curs_x+1 , curs_y-5 , 0);
		tiny3d_VertexPos(curs_x+4 , curs_y-5 , 0);
		tiny3d_End();
	} else
	if(window_resize_D1 == YES) {
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x-6 , curs_y-6 , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x-6 , curs_y-2 , 0);
		tiny3d_VertexPos(curs_x-2 , curs_y-6 , 0);
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x-5 , curs_y-4 , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x-4 , curs_y-5 , 0);
		tiny3d_VertexPos(curs_x+5 , curs_y+4 , 0);
		tiny3d_VertexPos(curs_x+4 , curs_y+5 , 0);
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x+6 , curs_y+6 , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x+6 , curs_y+2 , 0);
		tiny3d_VertexPos(curs_x+2 , curs_y+6 , 0);
		tiny3d_End();
		
		tiny3d_SetPolygon(TINY3D_LINE_LOOP);
		tiny3d_VertexPos(curs_x-6 , curs_y-6 , 0);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(curs_x-6 , curs_y-2 , 0);
		tiny3d_VertexPos(curs_x-4 , curs_y-3 , 0);
		tiny3d_VertexPos(curs_x+3 , curs_y+4 , 0);
		tiny3d_VertexPos(curs_x+2 , curs_y+6 , 0);
		tiny3d_VertexPos(curs_x+6 , curs_y+6 , 0);
		tiny3d_VertexPos(curs_x+6 , curs_y+2 , 0);
		tiny3d_VertexPos(curs_x+4 , curs_y+3 , 0);
		tiny3d_VertexPos(curs_x-3 , curs_y-4 , 0);
		tiny3d_VertexPos(curs_x-2 , curs_y-6 , 0);
		tiny3d_End();
		
	} else
	if(window_resize_D2 == YES) {
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x+6 , curs_y-6 , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x+6 , curs_y-2 , 0);
		tiny3d_VertexPos(curs_x+2 , curs_y-6 , 0);
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x+5 , curs_y-4 , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x+4 , curs_y-5 , 0);
		tiny3d_VertexPos(curs_x-5 , curs_y+4 , 0);
		tiny3d_VertexPos(curs_x-4 , curs_y+5 , 0);
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_POLYGON);
		tiny3d_VertexPos(curs_x-6 , curs_y+6 , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x-6 , curs_y+2 , 0);
		tiny3d_VertexPos(curs_x-2 , curs_y+6 , 0);
		tiny3d_End();
		
		tiny3d_SetPolygon(TINY3D_LINE_LOOP);
		tiny3d_VertexPos(curs_x+6 , curs_y-6 , 0);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(curs_x+6 , curs_y-2 , 0);
		tiny3d_VertexPos(curs_x+4 , curs_y-3 , 0);
		tiny3d_VertexPos(curs_x-3 , curs_y+4 , 0);
		tiny3d_VertexPos(curs_x-2 , curs_y+6 , 0);
		tiny3d_VertexPos(curs_x-6 , curs_y+6 , 0);
		tiny3d_VertexPos(curs_x-6 , curs_y+2 , 0);
		tiny3d_VertexPos(curs_x-4 , curs_y+3 , 0);
		tiny3d_VertexPos(curs_x+3 , curs_y-4 , 0);
		tiny3d_VertexPos(curs_x+2 , curs_y-6 , 0);
		tiny3d_End();
	}
	else {
		tiny3d_SetPolygon(TINY3D_TRIANGLES);
		tiny3d_VertexPos(curs_x , curs_y , 0);
		if(curs_push==YES) tiny3d_VertexColor(RED); else tiny3d_VertexColor(WHITE);
		tiny3d_VertexPos(curs_x  , curs_y + 15, 0);
		tiny3d_VertexPos(curs_x+9, curs_y + 12, 0);
		tiny3d_End();
		tiny3d_SetPolygon(TINY3D_LINE_LOOP);
		tiny3d_VertexPos(curs_x , curs_y , 0);
		tiny3d_VertexColor(BLACK);
		tiny3d_VertexPos(curs_x  , curs_y + 15, 0);
		tiny3d_VertexPos(curs_x+9, curs_y + 12, 0);
		tiny3d_End();
	}
}

void sort()
{
	int min;
	u8 t;
	u64 t1;
	int i, j;
	
	int Folder_N = -1;
	int File_N = -1;
	
	for (i = 0; i<=window_content_N[window_activ]; i++) {
		if(strcmp(window_content_Name[window_activ][i], "..") == 0) continue;
		if(window_content_Type[window_activ][i] == _DIRECTORY) Folder_N++;
		else File_N++;
	}
	
	char **list_Dir = (char **) malloc( (Folder_N+2) * sizeof(char*) );
	u8 *list_Dir_sel = (u8 *) malloc( (Folder_N+2) * sizeof(u8) );
	char **list_Fil = (char **) malloc( (File_N+2) * sizeof(char*) );
	u64 *list_Fil_siz = (u64 *) malloc( (File_N+2) * sizeof(u64) );
	u8 *list_Fil_sel = (u8 *) malloc( (File_N+2) * sizeof(u8) );	

	Folder_N = -1;
	File_N = -1;
	for (i = 0; i<=window_content_N[window_activ]; i++) {
		if(strcmp(window_content_Name[window_activ][i], "..") == 0) continue;
		if(window_content_Type[window_activ][i] == _DIRECTORY) {
			Folder_N++;
			list_Dir[Folder_N] = strcpy_malloc(window_content_Name[window_activ][i]);
			list_Dir_sel[Folder_N] = window_content_Selected[window_activ][i];
		} else {
			File_N++;
			list_Fil[File_N] = strcpy_malloc(window_content_Name[window_activ][i]);
			list_Fil_sel[File_N] = window_content_Selected[window_activ][i];
			list_Fil_siz[File_N] = window_content_Size[window_activ][i];
		}
	}
	
	char *ta=NULL;
	char *tb=NULL;
	
	for (i = 0; i<Folder_N; i++) { 
		min = i;
		for (j = i+1; j <= Folder_N; j++) { 
			FREE(ta);
			FREE(tb);
			ta = strcpy_malloc(list_Dir[j]);
			tb = strcpy_malloc(list_Dir[min]);
			if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
			if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
			if(window_sort[window_activ] == ASC) {
				if(strcmp(ta, tb) < 0) min = j;
			} else if(strcmp(ta, tb) > 0) min = j;
		}
		if(min==i) continue;
		
		FREE(ta);
		ta = strcpy_malloc(list_Dir[min]);
		FREE(list_Dir[min]);
		list_Dir[min] = strcpy_malloc(list_Dir[i]);
		FREE(list_Dir[i]);
		list_Dir[i] = strcpy_malloc(ta);
		
		t = list_Dir_sel[min];
		list_Dir_sel[min] = list_Dir_sel[i];
		list_Dir_sel[i] = t;
	}
	
	for (i = 0; i<File_N; i++) { 
		min = i;
		for (j = i+1; j <= File_N; j++) {
			FREE(ta);
			FREE(tb);
			ta = strcpy_malloc(list_Fil[j]);
			tb = strcpy_malloc(list_Fil[min]);
			if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
			if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
			if(window_sort[window_activ] == ASC) {
				if(strcmp(ta, tb) < 0) min = j;
			} else if(strcmp(ta, tb) > 0) min = j;
		}
		if(min==i) continue;
		
		FREE(ta);
		ta = strcpy_malloc(list_Fil[min]);
		FREE(list_Fil[min]);
		list_Fil[min] = strcpy_malloc(list_Fil[i]);
		FREE(list_Fil[i]);
		list_Fil[i] = strcpy_malloc(ta);
		
		t = list_Fil_sel[min];
		list_Fil_sel[min] = list_Fil_sel[i];
		list_Fil_sel[i] = t;
		
		t1 = list_Fil_siz[min];
		list_Fil_siz[min] = list_Fil_siz[i];
		list_Fil_siz[i] = t1;
	}
	
	FREE(ta);
	FREE(tb);
	
	u32 n;
	for(n=0; n<WINDOW_MAX_ITEMS; n++) FREE(window_content_Name[window_activ][n]);
	
	u8 Parent=NO;
	if(strcmp(window_path[window_activ], "/") != 0) {
		Parent=YES;
		window_content_Name[window_activ][0] = strcpy_malloc("..");
		window_content_Selected[window_activ][0] = NO;
		window_content_Type[window_activ][0] = _DIRECTORY;
		window_content_Size[window_activ][0] = 0;
	}

	if(window_sort[window_activ] == ASC) {
		for(j=0; j<=Folder_N; j++) {
			window_content_Name[window_activ][j+Parent] = strcpy_malloc(list_Dir[j]);
			window_content_Selected[window_activ][j+Parent] = list_Dir_sel[j];
			window_content_Type[window_activ][j+Parent] = _DIRECTORY;
			window_content_Size[window_activ][j+Parent] = 0;
		}
		for(j=0; j<=File_N; j++) {
			window_content_Name[window_activ][j+Parent+Folder_N+1] = strcpy_malloc(list_Fil[j]);
			window_content_Selected[window_activ][j+Parent+Folder_N+1] = list_Fil_sel[j];
			window_content_Type[window_activ][j+Parent+Folder_N+1] = get_ext(list_Fil[j]);
			window_content_Size[window_activ][j+Parent+Folder_N+1] = list_Fil_siz[j];
		}
	} else {
		for(j=0; j<=File_N; j++) {
			window_content_Name[window_activ][j+Parent] = strcpy_malloc(list_Fil[j]);
			window_content_Selected[window_activ][j+Parent] = list_Fil_sel[j];
			window_content_Type[window_activ][j+Parent] = get_ext(list_Fil[j]);
			window_content_Size[window_activ][j+Parent] = list_Fil_siz[j];
		}
		for(j=0; j<=Folder_N; j++) {
			window_content_Name[window_activ][j+Parent+File_N+1] = strcpy_malloc(list_Dir[j]);
			window_content_Selected[window_activ][j+Parent+File_N+1] = list_Dir_sel[j];
			window_content_Type[window_activ][j+Parent+File_N+1] = _DIRECTORY;
			window_content_Size[window_activ][j+Parent+File_N+1] = 0;
		}
	}
	
	free(list_Dir);
	free(list_Dir_sel);
	free(list_Fil);
	free(list_Fil_siz);
	free(list_Fil_sel);
}

void CloseWindow()
{
	if(window_activ==-1) return;
	
	u32 i;
	
	FREE(window_path[window_activ]);
	FREE(window_lastpath[window_activ]);	
	for(i=0; i<WINDOW_MAX_ITEMS; i++) FREE(window_content_Name[window_activ][i]);
	FREE(window_content_Name[window_activ]);
	FREE(window_content_Size[window_activ]);
	FREE(window_content_Type[window_activ]);
	FREE(window_content_Selected[window_activ]);
	
	window_open[window_activ] = NO;
	window_activ=-1;
	
	for(i=0; i<WINDOW_MAX; i++) {
		if(window_open[i] == NO) continue;
		if(window_activ==-1) window_activ=i; else
		if(window_z[window_activ] > window_z[i]) window_activ=i; 
	}
	if(window_activ != -1) {
		window_z[window_activ] = 1;
		for(i=0; i<WINDOW_MAX; i++) {
			if(window_open[i] == NO) continue;
			if(i==window_activ) continue;
			window_z[i]++;
		}
	}
}

u8 OpenWindow()
{
	u32 n;
	for(n=0; n<WINDOW_MAX; n++){
		if( window_open[n] == NO ) {
			window_open[n] = YES;
			break;
		}
		if(n==WINDOW_MAX-1) {
			show_msg("MAX Windows");
			return FAILED;
		}
	}
	
	window_activ=n;
	
	SetWindowLocation(WINDOW_LOC_DEFAULT);
	
	window_lastpath[window_activ] = (char *) malloc(WINDOW_MAX_PATH_LENGTH * sizeof(char));
	window_path[window_activ] = (char *) malloc(WINDOW_MAX_PATH_LENGTH * sizeof(char));
	window_content_Name[window_activ] = (char **) malloc(WINDOW_MAX_ITEMS * sizeof(char *));
	
	for(n=0; n<WINDOW_MAX_ITEMS; n++) window_content_Name[window_activ][n]=NULL;

	window_content_Size[window_activ] = (u64 *) malloc(WINDOW_MAX_ITEMS * sizeof(u64));
	window_content_Type[window_activ] = (u8 *) malloc(WINDOW_MAX_ITEMS * sizeof(u8));
	window_content_Selected[window_activ] = (u8 *) malloc(WINDOW_MAX_ITEMS * sizeof(u8));
	
	strcpy(window_path[window_activ], "/");
	strcpy(window_lastpath[window_activ], window_path[window_activ]);
	
	for(n=0; n<WINDOW_MAX; n++) {
		if(window_open[n] == YES && n != window_activ) {
			window_z[n]++;
		}
	}
	
	window_z[window_activ]=1;
	
	//print_load("Error : End of Open window");
	return SUCCESS;
}

void UpdateLastPath()
{
	if( strncmp(window_lastpath[window_activ], window_path[window_activ], strlen(window_path[window_activ])) != 0) {
        strcpy(window_lastpath[window_activ], window_path[window_activ]);
    }
}

void Window(char *directory)
{
	if(directory==NULL) {
		if( OpenWindow() == FAILED) return;		
	} 
	else if( strcmp(directory, "..") == 0) {
		if(window_activ==-1) return;
		if(strcmp(window_path[window_activ], "/") == 0) return;
		char temp[255];
		strcpy(temp, window_path[window_activ]);
		temp[strrchr(temp, '/') - temp] = 0;
		memset(window_path[window_activ], 0, sizeof(window_path[window_activ]));
		strcpy(window_path[window_activ], temp);
		if(window_path[window_activ][0] == 0) window_path[window_activ][0] = '/';
	}
	else if(strcmp(directory, ".") == 0) {
		if(window_activ==-1) return;
		//refresh;
	}
	else {
		if(window_activ==-1) return;
		if(strcmp(window_path[window_activ], "/") != 0) {
			strcat(window_path[window_activ], "/");
		}
		strcat(window_path[window_activ], directory);
	}
	
	UpdateLastPath();
	
	if(window_activ==-1) return;
	
	MountNTFS();
	
	window_content_N[window_activ]=-1;
	u32 n;
	for(n=0; n<WINDOW_MAX_ITEMS; n++) {
		FREE(window_content_Name[window_activ][n]);
		window_content_Type[window_activ][n] = _FILE;
		window_content_Size[window_activ][n] = 0;
		window_content_Selected[window_activ][n] = NO;
	}
	
#ifdef RPCS3
	if(strcmp(window_path[window_activ], "/") == 0) {
		window_content_N[window_activ]++;
		window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
		window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc("dev_hdd0");
		window_content_N[window_activ]++;
		window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
		window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc("dev_hdd1");
		window_content_N[window_activ]++;
		window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
		window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc("dev_usb000");
		window_content_N[window_activ]++;
		window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
		window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc("dev_flash");
		return;
	}
#endif
	
	if(path_info("/dev_hdd1")==_NOT_EXIST) {
		sys_fs_mount("CELL_FS_UTILITY:HDD1", "CELL_FS_FAT", "/dev_hdd1", 0);
		sysFsAioInit("/dev_hdd1");
	}
	
	char temp[512];
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(window_path[window_activ]);
	if(d==NULL) return;
	
	while ((dir = readdir(d))) {
		if(strcmp(dir->d_name, ".")==0) continue;
		if(strcmp(dir->d_name, "..")==0) continue; // NTFS : added for all directories after
		if(!strncmp(dir->d_name, "$", 1)) continue; // NTFS : ignore system files

		if(window_content_N[window_activ] == WINDOW_MAX_ITEMS-1) {
			show_msg("Too many files...");
			closedir(d);
			sort();
			return;
		}
		window_content_N[window_activ]++;
		if(dir->d_type & DT_DIR) {
			window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
		} else {		
			if(strcmp(window_path[window_activ], "/") != 0) {
				sprintf(temp, "%s/%s", window_path[window_activ], dir->d_name);
				window_content_Size[window_activ][window_content_N[window_activ]] = get_size(temp, NO);
			}
			window_content_Type[window_activ][window_content_N[window_activ]] = get_ext(dir->d_name);
		}
		window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc(dir->d_name);
	}
	closedir(d);
	
// can't see NTFS with opendir("/")
	if(strcmp(window_path[window_activ], "/") == 0) {
		
		int r,i;
		for(i = 0; i < 8 ; i++) {
			r = -1;
			sprintf(temp, "ntfs%c", 48+i);
			r = NTFS_Test_Device(temp);
			if(r>=0) {
				window_content_N[window_activ]++;
				window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
				sprintf(temp, "ntfs%c:", 48+i);
				window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc(temp);
			}
		}
	} else {
		window_content_N[window_activ]++;
		window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
		window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc("..");
	}
	
	sort();
}

void GotoLastPath()
{
	UpdateLastPath();
	
	int curr_l = strlen(window_path[window_activ]);
    int last_l = strlen(window_lastpath[window_activ]);
    
	if(last_l<=curr_l) return;
	
	int dir_l = last_l-curr_l;
	
	char dir_n[dir_l];
	memset(dir_n, 0, dir_l);
    if(window_lastpath[window_activ][curr_l] != '/' && strcmp(window_path[window_activ], "/") != 0) return;
    
    int r=1;
    if(strcmp(window_path[window_activ], "/")==0) r=0;
	
    int j=0;
	int i;
    for(i=curr_l+r ; i<last_l ; i++) {
        if(window_lastpath[window_activ][i] == '/') break;
		dir_n[j]=window_lastpath[window_activ][i];
        j++;
    }
	dir_n[j]=0;
	j++;
	
	if(j==1) return;
	
	Window(dir_n);
}

//**** properties ****

void properties_input()
{
	if(prop_activ == NO) return;
	
	if(new_pad & BUTTON_CIRCLE)
	{
		prop_activ=NO;
		total_size=0;
		nb_file= 0;
		nb_directory=0;
		int i;
		for(i=0; i<=PROP_ITEM_NUMBER; i++) {
			FREE(PROP_ITEM[i]);
			FREE(PROP_ITEM_VALUE[i]);
		}
		FREE(PROP_ITEM);
		FREE(PROP_ITEM_VALUE);
		PROP_ITEM_NUMBER=-1;
	}
	
}

void Draw_properties()
{
	if(prop_activ == NO) return;
	
	SetFontZ(0);	
	FontSize(PROP_FONT);
	FontColor(BLACK);	
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO); // DARK 50%
	
	Draw_Box(PROP_X-2, PROP_Y-2, 0, 0, PROP_W+4, PROP_H+4, BLACK, NO); // BORDER
	Draw_Box(PROP_X, PROP_Y, 0, 0, PROP_W, PROP_H, 0xF0F0F0FF, NO);
	Draw_Box(PROP_X, PROP_Y, 0, 0, PROP_COL_W, PROP_H, 0xD4DBEDFF, NO);
	
	int i;
	for(i=0; i<=PROP_ITEM_NUMBER; i++) {
		DrawFormatString(PROP_X+5, PROP_Y+PROP_FONT*i, PROP_ITEM[i]);
		DrawFormatString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*i, PROP_ITEM_VALUE[i]);
	}
	
}

void open_properties()
{
	start_loading();
	
	total_size=0;
	nb_file=0;
	nb_directory=0;
	
	u8 is_fil=NO;
	u8 is_dir=NO;
	gathering=YES;
	if(option_sel_N < 0) {
		get_size(window_path[window_activ], YES);
		is_dir=YES;
	} else {
		int i;
		for(i=0; i<=option_sel_N; i++) {
			get_size(option_sel[i], YES);
			if(is_fil==NO) if(path_info(option_sel[i]) == _FILE) is_fil=YES;
			if(is_dir==NO) if(path_info(option_sel[i]) == _DIRECTORY) is_dir=YES;
		}
	}
	gathering=NO;
	
	if(gathering_cancel) {
		gathering_cancel=NO;	
		total_size=0;
		nb_file=0;
		nb_directory=0;
		end_loading();
		return;
	}

	
	PROP_ITEM = (char **) malloc(PROP_MAX_ITEMS*sizeof(char *));
	PROP_ITEM_VALUE = (char **) malloc(PROP_MAX_ITEMS*sizeof(char *));
	PROP_ITEM_NUMBER = -1;
	
	PROP_ITEM_NUMBER++;
	PROP_ITEM[PROP_ITEM_NUMBER] = strcpy_malloc(STR_PATH);
	if(option_sel_N == 0) {
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = strcpy_malloc(option_sel[0]);
	} else {
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = strcpy_malloc(window_path[window_activ]);
	}
	
// TOFIX : GetWidth use DrawString : It can't be used here while the "loading thread" is running !
/* 
	int l = strlen(PROP_ITEM_VALUE[PROP_ITEM_NUMBER]); 
	while((float) GetWidth(PROP_ITEM_VALUE[PROP_ITEM_NUMBER]) > (float) PROP_W - (float) PROP_COL_W - (float) 10.0f) {
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER][l-1]=0;
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER][l-2]='.';
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER][l-3]='.';
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER][l-4]='.';
		l--;
	}
*/
	PROP_ITEM_NUMBER++;
	PROP_ITEM[PROP_ITEM_NUMBER] = strcpy_malloc(STR_TYPE);
	if(is_dir == YES && is_fil == YES) {
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = strcpy_malloc(STR_MULT);
	} else
	if(is_dir == YES) {
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = strcpy_malloc(STR_DIR);
	} else
	if(is_fil == YES) {
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = strcpy_malloc(STR_FILE);
	}

	if(nb_directory!=0 && nb_file!=1) {
		PROP_ITEM_NUMBER++;
		PROP_ITEM[PROP_ITEM_NUMBER] = strcpy_malloc(STR_FILE);
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = sprintf_malloc("%d", nb_file);
		
		PROP_ITEM_NUMBER++;
		PROP_ITEM[PROP_ITEM_NUMBER] = strcpy_malloc(STR_FOLDER);
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = sprintf_malloc("%d", nb_directory);
	}

	PROP_ITEM_NUMBER++;
	PROP_ITEM[PROP_ITEM_NUMBER] = strcpy_malloc(STR_SIZE);
	char *prop_size_str = get_unit(total_size);
	if(total_size<1024) {
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = strcpy_malloc(prop_size_str);
	} else {
		PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = sprintf_malloc("%s (%llu %s)", prop_size_str, (long long unsigned int) total_size, STR_UNIT);
	}
	free(prop_size_str);

	if(option_sel_N == 0 && is_fil == YES) {
		u64 prop_md5[2];
		if( md5_file(option_sel[0], (u8 *) prop_md5) == SUCCESS) {
			PROP_ITEM_NUMBER++;
			PROP_ITEM[PROP_ITEM_NUMBER] = strcpy_malloc("MD5");
			PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = sprintf_malloc("%016llX%016llX", (long long unsigned int) prop_md5[0],
																				 (long long unsigned int) prop_md5[1]);
		}
		
		u32 prop_sha1[5];
		if( sha1_file(option_sel[0], (u8 *) prop_sha1) == SUCCESS) {
			PROP_ITEM_NUMBER++;
			PROP_ITEM[PROP_ITEM_NUMBER] = strcpy_malloc("SHA-1");
			PROP_ITEM_VALUE[PROP_ITEM_NUMBER] = sprintf_malloc("%08lX%08lX%08lX%08lX%08lX ", (long unsigned int) prop_sha1[0], (long unsigned int) prop_sha1[1], (long unsigned int) prop_sha1[2], (long unsigned int) prop_sha1[3], (long unsigned int) prop_sha1[4]);
		}			
	}

	total_size=0;
	nb_file= 0;
	nb_directory=0;
	
	prop_activ = YES;

	end_loading();
}

//**** picture viewer ****

void picture_viewer_input()
{
	if(picture_viewer_activ == NO) return;
	
	if(new_pad & BUTTON_RIGHT) {	
		int flag=NO, i;
		for(i=0; i<=window_content_N[window_activ]; i++) {
			if(flag==YES) {
				if(window_content_Type[window_activ][i] == _JPG || window_content_Type[window_activ][i] == _PNG) {
					sprintf(TMP_PIC_path, "%s/%s", window_path[window_activ], window_content_Name[window_activ][i]);
					Load_FM();
					break;
				}
			}
			if(strcmp(&strrchr(TMP_PIC_path, '/')[1], window_content_Name[window_activ][i])==0) flag=YES;
		}
	}
	
	if(new_pad & BUTTON_LEFT) {	
		int flag=NO, i;
		for(i=window_content_N[window_activ]; i>0; i--) {
			if(flag==YES) {
				if(window_content_Type[window_activ][i] == _JPG || window_content_Type[window_activ][i] == _PNG) {
					sprintf(TMP_PIC_path, "%s/%s", window_path[window_activ], window_content_Name[window_activ][i]);
					Load_FM();
					break;
				 }
			}
			if(strcmp(&strrchr(TMP_PIC_path, '/')[1], window_content_Name[window_activ][i])==0) flag=YES;
		}
	}
	
	if(new_pad & BUTTON_CIRCLE)
	{
		picture_viewer_activ=NO;
		memset(TMP_PIC_path, 0, sizeof(TMP_PIC_path));
		TMP_PIC_offset = 0;
	}
}

void Draw_picture_viewer()
{
	if(picture_viewer_activ == NO) return;	
	
	if(APNG_offset[0]!=0) {Draw_APNG(); return;}
	
	SetFontZ(0);
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO); // DARK 50%
	
	float xi, yi, wi, hi;
	
	if(TMP_PIC_offset != 0 ) {
		tiny3d_SetTexture(0, TMP_PIC_offset, TMP_PIC.width, TMP_PIC.height, TMP_PIC.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if( TMP_PIC.width > 748) {
			wi = 748 ;
			hi = TMP_PIC.height * 748 / TMP_PIC.width;
		
		} else 
		if (TMP_PIC.width > 412) {
			hi = 412;
			wi = TMP_PIC.width * 412 / TMP_PIC.height;
		} else {
			wi = TMP_PIC.width;
			hi = TMP_PIC.height;
		}
		xi = (848 - wi) / 2;
		yi = (512 - hi) / 2;
	
		Draw_Box(xi, yi, 0, 0, wi, hi, WHITE, YES);
	}
	
	Draw_Box(0, 460, 0, 0, 848, 20, BLACK, NO);
	FontColor(WHITE);
	DrawStringFromCenterX(424, 462 , &strrchr(TMP_PIC_path, '/')[1]);
	
}

void open_picture_viewer(char *pict_path)
{
	memset(TMP_PIC_path, 0, sizeof(TMP_PIC_path));
	
	strcpy(TMP_PIC_path, pict_path);

	Load_FM();
	
	picture_viewer_activ = YES;
	
}

//**** txt viewer ****

void nextLine()
{
	u64 i;
	float xt=TXT_X;
	for(i=txt_linpos; i < txt_viewer_content_size; i++) {
		if(txt_viewer_content[i] == '\n'  || xt > TXT_X+TXT_W) {
			txt_linpos = i+1;
			return;
		}
		xt = DrawFormatString(xt, -50, "%c", txt_viewer_content[i]);
	}
}

void prevLine()
{
	u64 i;
	float xt=TXT_X;
	if(txt_linpos == 0) return;
	if(txt_linpos == 1) {
		txt_linpos=0;
		return;
	}
	for(i=txt_linpos-2; i >= 0; i--) {
		if(txt_viewer_content[i] == '\n'  || xt > TXT_X+TXT_W) {
			txt_linpos = i+1;
			return;
		}
		if(i==0) {
			txt_linpos=0;
			return;
		}
		xt = DrawFormatString(xt, -50, "%c", txt_viewer_content[i]);
	}
}

void DrawTXTInBox(float x, float y, float z, float w, float h, char *txt, u32 bg_color, u32 font_color)
{
	Draw_Box(x, y, z, 0, w, h, bg_color, NO);
	SetFontZ(z);
	FontColor(font_color);
	float xt = x;
	float yt = y;
	u64 i, j;
	u64 l = strlen(txt);
	
	for(i=0; i < l ; i++) {
		if(txt[i] == '\r') continue;
		if(txt[i] == '\n') {
			xt = x; 
			yt+=new_line(1);
			continue;
		} 
		else if(txt[i] == '\t') {
			for(j=x; j < x+w; j+=30) {
				if(j>xt) {
					xt=j;
					break;
				}
			}
			continue;
		}
		
		if(xt > x+w) {
			if(h==1) {xt = DrawString(xt, yt, "..."); return;}
			xt = x;
			yt+=new_line(1);
		}
		
		if(yt > y+h) { txt_scroll=YES; return;}
		
		xt = DrawFormatString(xt, yt, "%c", txt[i]);
	}
	
}

void txt_viewer_input()
{
	if(txt_viewer_activ == NO) return;
	
	get_R2speed();
	
	if( R2pad(BUTTON_DOWN) && txt_scroll == YES )
	{
		nextLine();
	}
	if( R2pad(BUTTON_UP) && txt_linpos != 0)
	{
		prevLine();
	}
	
	if(new_pad & BUTTON_CIRCLE)
	{
		txt_viewer_activ=NO;
		if(txt_viewer_content) {free(txt_viewer_content); txt_viewer_content=NULL; txt_viewer_content_size=0;}
	}

}

void Draw_txt_viewer_input()
{
	if(txt_viewer_activ == NO) return;	
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
	x=DrawButton(x, y, STR_SCROLL, BUTTON_UP | BUTTON_DOWN);
	
}

void Draw_txt_viewer()
{
	if(txt_viewer_activ == NO) return;	
	
	SetFontZ(0);
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO); // DARK 50%
	Draw_Box(TXT_X-20-5 , TXT_Y-20-5 , 0, 0, TXT_W+40+10 , TXT_H+40+10 , BLACK, NO); // Black Border
	Draw_Box(TXT_X-20   , TXT_Y-20   , 0, 0, TXT_W+40	, TXT_H+40	, WHITE, NO); // White Border
	
	
	Draw_Box(TXT_X, TXT_Y, 0, 0, TXT_W, TXT_H, WHITE, NO);
	
	SetFontZ(0);
	FontColor(BLACK);
	
	float xt = TXT_X;
	float yt = TXT_Y;
	u64 i, j;
	
	for(i=txt_linpos; i < txt_viewer_content_size ; i++) {
		if(txt_viewer_content[i] == '\r') continue;
		if(txt_viewer_content[i] == '\n') {
			xt = TXT_X; 
			yt+=new_line(1);
			continue;
		} 
		else if(txt_viewer_content[i] == '\t') {
			for(j=TXT_X; j < TXT_X+TXT_W; j+=30) {
				if(j>xt) {
					xt=j;
					break;
				}
			}
			continue;
		}
		
		if(xt > TXT_X+TXT_W) {
			xt = TXT_X;
			yt+=new_line(1);
		}
		
		if(yt > TXT_Y+TXT_H) { txt_scroll=YES; return;}
		
		xt = DrawFormatString(xt, yt, "%c", txt_viewer_content[i]);
	}
}

void open_txt_viewer(char *txt_path)
{
	txt_linpos=0;
	txt_scroll=NO;
			
	txt_viewer_content = LoadFile(txt_path, &txt_viewer_content_size);
	
	txt_viewer_activ = YES;
	
}

//**** SFO viewer ****

typedef struct
{
	uint32_t magic; 				/* Always PSF */
	uint32_t version; 				/* Usually 1.1 */
	uint32_t key_table_start; 		/* Start offset of key_table */
	uint32_t data_table_start; 		/* Start offset of data_table */
	uint32_t nb_entries; 			/* Number of entries in all tables */
} sfo_header;

typedef struct 
{
	uint16_t key_offset; 	/* param_key offset (relative to start offset of key_table) */
	uint16_t data_type;		/* param_data data type */
	uint32_t data_len;		/* param_data used bytes */
	uint32_t data_max_len;	/* param_data total bytes */
	uint32_t data_offset;	/* param_data offset (relative to start offset of data_table) */
} sfo_table_entry;

void es_header(sfo_header *h)
{	
	//h->magic = ES(h->magic);
	h->version = ES(h->version);
	h->key_table_start = ES(h->key_table_start);
	h->data_table_start = ES(h->data_table_start);
	h->nb_entries = ES(h->nb_entries);
}

void es_table_entry(sfo_table_entry *e)
{	
	e->key_offset = ES(e->key_offset);
	e->data_type = ES(e->data_type);
	e->data_len = ES(e->data_len);
	e->data_max_len = ES(e->data_max_len);
	e->data_offset = ES(e->data_offset);
}

void SFO_viewer_input()
{
	if(SFO_viewer_activ == NO) return;
	
	if(new_pad & BUTTON_CIRCLE)
	{
		SFO_viewer_activ=NO;
	}
}

void open_SFO_viewer(char *path)
{
	FILE* sfo;
	sfo_header header;
	
	sfo = fopen(path, "rb");
	if(sfo == NULL)  {
		print_load("Error : failed to open file");
		return;
	}
	
// read header
	fread(&header, sizeof(sfo_header), 1, sfo);
	es_header(&header);

	if(header.magic != SFO_MAGIC) {
		print_load("Error : wrong magic value");
		return;
	}
	
	sfo_table_entry table_entry[header.nb_entries];
	
// read table entries
	int i;
	for(i=0; i < header.nb_entries; i++) {
		fread(&table_entry[i], sizeof(sfo_table_entry), 1, sfo);
		es_table_entry(&table_entry[i]);
	}

	memset(SFO_KEY, 0, sizeof(SFO_KEY));
	memset(SFO_DATA, 0, sizeof(SFO_DATA));
	SFO_NB = 0;
	
// get KEYS
	for(i=0; i < header.nb_entries; i++) {
		if(table_entry[i].data_type == SFO_DATA_TYPE_UTF8S) continue ; // ignore
		fseek(sfo, header.key_table_start + table_entry[i].key_offset, SEEK_SET );
		fgets(SFO_KEY[i], 64, sfo);
		SFO_NB++;
	}
	
	char *entry_data_utf8;
	uint32_t entry_data_int32;
	
// get DATAS
	for(i=0; i < header.nb_entries; i++) {
		
		fseek(sfo, header.data_table_start + table_entry[i].data_offset, SEEK_SET );
		
		if(table_entry[i].data_type == SFO_DATA_TYPE_UTF8S) continue ; // ignore
		if(table_entry[i].data_type == SFO_DATA_TYPE_UTF8) {
			entry_data_utf8 = (char *) malloc(table_entry[i].data_max_len);
			fread(entry_data_utf8, table_entry[i].data_max_len, 1, sfo);
			strcpy(SFO_DATA[i], entry_data_utf8);
			free(entry_data_utf8);
		}
		if(table_entry[i].data_type == SFO_DATA_TYPE_INT32) {
			fread(&entry_data_int32, table_entry[i].data_max_len, 1, sfo);
			entry_data_int32 = ES(entry_data_int32);
			sprintf(SFO_DATA[i], "%d", entry_data_int32);
		}
	}

	fclose(sfo);
	
	SFO_viewer_activ = TRUE;
}

void Draw_SFO_viewer()
{
	if(SFO_viewer_activ == NO) return;
	int i;
	
	SetFontZ(0);	
	FontSize(SFO_FONT);
	FontColor(BLACK);
	
	int SFO_COL1_W=0;
	int SFO_H=SFO_FONT*SFO_NB;
	int SFO_Y=512/2-SFO_H/2;
	float x=0;
	for(i=0; i<SFO_NB; i++) {
		if(x < GetWidth(SFO_KEY[i])) x = GetWidth(SFO_KEY[i]);
	}
	SFO_COL1_W = x + 10;
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO);
	Draw_Box(SFO_X-2, SFO_Y-2, 0, 0, SFO_W+4, SFO_H+4, BLACK, NO);
	Draw_Box(SFO_X, SFO_Y, 0, 0, SFO_W, SFO_H, 0xF0F0F0FF, NO);
	Draw_Box(SFO_X, SFO_Y, 0, 0, SFO_COL1_W, SFO_H, 0xD4DBEDFF, NO);
	
	for(i=0; i<SFO_NB; i++) {
		DrawString(SFO_X+5, SFO_Y+SFO_FONT*i, SFO_KEY[i]);
		DrawTXTInBox(SFO_X+SFO_COL1_W+5, SFO_Y+SFO_FONT*i, 0, SFO_COL2_W-10-5, 1, SFO_DATA[i], 0, BLACK);
	}
}

//**** Option ****

void Option(char *item)
{
	char temp[512];
	int i;
	int ret=-1;
	
	if(strcmp(item, STR_NEWFOLDER) == 0) {
		sprintf(temp, "%s/New_Folder", window_path[window_activ]);
		if(path_info(temp) != _NOT_EXIST) {
			for(i=0; i<100; i++) {
				sprintf(temp, "%s/New_Folder_%d", window_path[window_activ], i);
				if(path_info(temp) == _NOT_EXIST) break;
			}
		}
		ret = mkdir(temp, 0777);
		if(ret != 0 ) {
			show_msg(STR_FAILED);
		} else {
			window_content_N[window_activ]++;
			window_content_Size[window_activ][window_content_N[window_activ]] = 0;
			window_content_Type[window_activ][window_content_N[window_activ]] = _DIRECTORY;
			window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc(&strrchr(temp, '/')[1]);
			sort();
		}
	} else
	if(strcmp(item, STR_NEWFILE) == 0) {
		sprintf(temp, "%s/New_File.txt", window_path[window_activ]);
		if(path_info(temp) != _NOT_EXIST) {
			for(i=0; i<100; i++) {
				sprintf(temp, "%s/New_File_%d.txt", window_path[window_activ], i);
				if(path_info(temp) == _NOT_EXIST) break;
			}
		}
		FILE* f;
		f = fopen(temp, "wb");
		if(f==NULL) show_msg(STR_FAILED);
		else {
			fclose(f);
			window_content_N[window_activ]++;
			window_content_Size[window_activ][window_content_N[window_activ]] = 0;
			window_content_Type[window_activ][window_content_N[window_activ]] = _FILE;
			window_content_Name[window_activ][window_content_N[window_activ]] = strcpy_malloc(&strrchr(temp, '/')[1]);
			sort();
		}
	} else
	if(strcmp(item, "SpeedTest") == 0) {
		start_copy_loading();
		SpeedTest();
		end_copy_loading();
		open_txt_viewer("/dev_hdd0/speed_test.txt");
		
	} else
	if(strcmp(item, STR_PASTE) == 0) {
		start_copy_loading();
		
		if(option_copy_N==0 && is_66600(option_copy[0])) {
			gathering=YES;
			strcpy(copy_src, option_copy[0]);
			sprintf(copy_dst, "%s%s", window_path[window_activ], strrchr(copy_src, '/'));
			Get_Game_Size(option_copy[0]);
			gathering=NO;
			CopyJoin(copy_src, copy_dst);
			
		} else {
			gathering=YES;
			for(i=0; i<=option_copy_N; i++){
				get_size(option_copy[i], YES);
			}
			gathering=NO;
			for(i=0; i<=option_copy_N; i++) {
				strcpy(copy_src, option_copy[i]);
				sprintf(copy_dst, "%s%s", window_path[window_activ], strrchr(copy_src, '/'));
				
				if(option_cut == YES) 
					Move(copy_src, copy_dst); 
				else {
					Copy(copy_src, copy_dst);
				}
			}
		}
		
		for(i=0; i<WINDOW_MAX_ITEMS; i++) FREE(option_copy[i]);	
		option_copy_N=-1;
		end_copy_loading();
		Window(".");
	} else
	if(strcmp(item, STR_JOIN) == 0) {
		start_copy_loading();
		gathering=YES;
		strcpy(copy_src, option_sel[0]);
		sprintf(copy_dst, "%s%s", window_path[window_activ], strrchr(copy_src, '/'));
		Get_Game_Size(option_sel[0]);
		gathering=NO;
		CopyJoin(copy_src, copy_dst);
		end_copy_loading();
		Window(".");
	} else
	if(strcmp(item, STR_COPY) == 0) {
		for(i=0; i<WINDOW_MAX_ITEMS; i++) FREE(option_copy[i]);
		for(i=0; i<=option_sel_N; i++) {
			option_copy[i] = strcpy_malloc(option_sel[i]);
		}
		option_copy_N = option_sel_N;
		option_cut = NO;
	} else
	if(strcmp(item, STR_CUT) == 0) {
		for(i=0; i<WINDOW_MAX_ITEMS; i++) FREE(option_copy[i]);
		for(i=0; i<=option_sel_N; i++) {
			option_copy[i] = strcpy_malloc(option_sel[i]);
		}
		option_copy_N = option_sel_N;
		option_cut = YES;
	} else
	if(strcmp(item, STR_DELETE) == 0) {
		start_loading();
		for(i=0; i<=option_sel_N; i++) {
			Delete(option_sel[i]);
		}
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_UNSELECT_ALL) == 0) {
		for(i=0; i<WINDOW_MAX_ITEMS; i++) window_content_Selected[window_activ][i]=NO;
	} else
	if(strcmp(item, STR_SELECT_ALL) == 0) {
		for(i=0; i<=window_content_N[window_activ]; i++) {
			if(strcmp(window_content_Name[window_activ][i], "..") == 0) {
				window_content_Selected[window_activ][i] = NO;
			} else window_content_Selected[window_activ][i] = YES;
		}
		option_activ=NO;
	} else
	if(strcmp(item, STR_RENAME) == 0) {
		char New_Name[255];
		strcpy(New_Name, &strrchr(option_sel[0], '/')[1]);
		if(Get_OSK_String(STR_RENAME, New_Name, 255) == SUCCESS) {
			if(New_Name[0] != 0) {
				char New_Path[512];
				sprintf(New_Path, "%s/%s", window_path[window_activ], New_Name);
				rename(option_sel[0], New_Path);
			}
		}
		Window(".");
	} else
	if(strcmp(item, STR_OPEN_WINDOW)==0) {
		Window(NULL);
	} else
	if(strcmp(item, STR_REFRESH)==0) {
		Window(".");
	} else
	if(strcmp(item, STR_MOUNT_DEVBLIND)==0) {
		sys_fs_mount("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_FAT", "/dev_blind", 0);
		Window(".");
	} else
	if(strcmp(item, STR_PROPS) == 0) {
		open_properties();
	} else
	if(strcmp(item, STR_VIEW) == 0) {
		open_picture_viewer(option_sel[0]);
	} else
	if(strcmp(item, STR_VIEW_TXT) == 0) {
		open_txt_viewer(option_sel[0]);
	} else
	if(strcmp(item, STR_VIEW_SFO) == 0) {
		start_loading();
		open_SFO_viewer(option_sel[0]);
		end_loading();
	} else
	if(strcmp(item, STR_EXTRACT_ELF) == 0) {
		start_loading();
		char elf[255];
		strcpy(elf, option_sel[0]);	
		RemoveExtention(elf);
		strcat(elf, ".elf");
		
		if( path_info(elf) != _NOT_EXIST) Delete(elf);
		
		if(Extract(option_sel[0], elf)==FAILED) {
			print_load("Error : Failed to extract");
		}
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_RESIGN_SELF) == 0) {
		start_loading();
		re_sign_SELF(option_sel[0]);
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_LAUNCH_SELF) == 0) {
		sysProcessExitSpawn2(option_sel[0], NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_64K);
	} else
	if(strcmp(item, STR_EXTRACT_EBOOT) == 0) {
		start_loading();
		char elf[255];
		strcpy(elf, option_sel[0]);	
		RemoveExtention(elf);
		strcat(elf, ".ELF");
		
		if( path_info(elf) != _NOT_EXIST) Delete(elf);
		
		if(Extract(option_sel[0], elf)==FAILED) {
			print_load("Error : Failed to extract");
		}
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_RESIGN_EBOOT) == 0) {
		start_loading();
		re_sign_EBOOT(option_sel[0]);
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_LAUNCH_EBOOT) == 0) {
		sysProcessExitSpawn2(option_sel[0], NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_64K);
	} else
	if(strcmp(item, STR_SIGN_EBOOT) == 0) {
		start_loading();
		char BIN[255];
		strcpy(BIN, option_sel[0]);	
		RemoveExtention(BIN);
		strcat(BIN, ".BIN");
		
		char BIN_ORI[255];
		strcpy(BIN_ORI, BIN);
		strcat(BIN_ORI, "_ORI");
		
		if( path_info(BIN) != _NOT_EXIST) {
			rename(BIN, BIN_ORI);
		}
		
		if( Sign_EBOOT(option_sel[0], BIN) == FAILED) {
			print_load("Error : failed to sign EBOOT");
			rename(BIN_ORI, BIN);
		}
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_SIGN_ELF) == 0) {
		start_loading();
		char SELF[255];
		strcpy(SELF, option_sel[0]);	
		RemoveExtention(SELF);
		strcat(SELF, ".self");
		
		char SELF_ORI[255];
		strcpy(SELF_ORI, SELF);
		strcat(SELF_ORI, "_ORI");
		
		if( path_info(SELF) != _NOT_EXIST) {
			rename(SELF, SELF_ORI);
		}
		
		if( Sign_ELF(option_sel[0], SELF) == FAILED) {
			print_load("Error : failed to sign ELF");
			rename(SELF_ORI, SELF);
		}
		
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_EXTRACT_PRX) == 0) {
		start_loading();
		char prx[255];
		strcpy(prx, option_sel[0]);	
		RemoveExtention(prx);
		strcat(prx, ".prx");
		if( path_info(prx) != _NOT_EXIST) Delete(prx);
		if(Extract(option_sel[0], prx)==FAILED) {
			print_load("Error : Failed to extract");
		}
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_RESIGN_SPRX) == 0) {
		start_loading();
		re_sign_SPRX(option_sel[0]);
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_SIGN_PRX) == 0) {
		start_loading();
		
		char SPRX[255];
		strcpy(SPRX, option_sel[0]);	
		RemoveExtention(SPRX);
		strcat(SPRX, ".sprx");
		
		char SPRX_ORI[255];
		strcpy(SPRX_ORI, SPRX);
		strcat(SPRX_ORI, "_ORI");
		
		if( path_info(SPRX) != _NOT_EXIST) {	
			rename(SPRX, SPRX_ORI);
		}
		
		if( Sign_ELF(option_sel[0], SPRX) == FAILED) {
			print_load("Error : failed to sign SPRX");
			rename(SPRX_ORI, SPRX);
		}
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_CHECK_IRD) == 0) {
		start_loading();
		if ( CheckIRD(option_sel[0]) == SUCCESS) {
			if(is_iso(option_sel[0])) sprintf(temp, "%s.MD5_check.txt", option_sel[0]);
			else sprintf(temp, "%s/MD5_check.txt", option_sel[0]);
			open_txt_viewer(temp);
		}
		end_loading();
	} else
	if(strcmp(item, STR_EXTRACT_PKG) == 0) {
		start_loading();
		pkg_unpack(option_sel[0], NULL);
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_PKG_INFO) == 0) {
		start_loading();
		i=pkg_list(option_sel[0]);
		end_loading();
		if(i==SUCCESS) open_txt_viewer("/dev_hdd0/tmp/pkg_list.txt");
	} else
	if(strcmp(item, STR_MAKE_PKG) == 0) {
		start_loading();
		make_pkg(option_sel[0]);
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_REMOVE_PRXLOADER) == 0) {
		remove_from_list("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, STR_ADD_PRXLOADER) == 0) {
		add_to_list("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt", option_sel[0]);
	}  else
	if(strcmp(item, STR_REMOVE_PRXLOADER2) == 0) {
		remove_from_list("/dev_hdd0/prx_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, STR_ADD_PRXLOADER2) == 0) {
		add_to_list("/dev_hdd0/prx_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, STR_REMOVE_MAMBA) == 0) {
		remove_from_list("/dev_hdd0/mamba_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, STR_ADD_MAMBA) == 0) {
		add_to_list("/dev_hdd0/mamba_plugins.txt", option_sel[0]);
	}  else
	if(strcmp(item, STR_REMOVE_COBRA) == 0) {
		remove_from_list("/dev_hdd0/boot_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, STR_ADD_COBRA) == 0) {
		add_to_list("/dev_hdd0/boot_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, STR_DUMP_LV2) == 0) {
		start_loading();
		dump_lv2("/dev_hdd0/LV2.BIN");
		end_loading();
	} else
	if(strcmp(item, STR_DUMP_LV1) == 0) {
		start_loading();
		dump_lv1("/dev_hdd0/LV1.BIN");
		end_loading();
	} else
	if(strcmp(item, STR_DUMP_FLASH) == 0) {
		start_loading();
		dump_flash("/dev_hdd0/FLASH.BIN");
		end_loading();
	} else
	if(strcmp(item, STR_EXTRACT_TRP) == 0) {
		start_loading();
		trophy_extract(option_sel[0]);
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_GETMD5) == 0) {
		start_loading();
		HashFolder(MD5_HASH, option_sel[0]);
		if(cancel == NO) {
			char temp[255];
			sprintf(temp, "%s/content.md5", option_sel[0]);
			open_txt_viewer(temp);
		}
		end_loading();
	} else
	if(strcmp(item, STR_GETSHA1) == 0) {
		start_loading();
		HashFolder(SHA1_HASH, option_sel[0]);
		if(cancel == NO) {
			char temp[255];
			sprintf(temp, "%s/content.sha1", option_sel[0]);
			open_txt_viewer(temp);
		}
		end_loading();
	} else 
	if(strcmp(item, STR_CHECK_CRC32) == 0) {
		start_loading();
		if(CheckCRC32(option_sel[0]) == SUCCESS) {
			char temp[255];
			strcpy(temp, option_sel[0]);
			temp[strlen(temp)-4]=0;
			strcat(temp, "_CHECK.crc");
			open_txt_viewer(temp);
		}
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_CHECK_MD5) == 0) {
		start_loading();
		if(CheckMD5(option_sel[0]) == SUCCESS) {
			char temp[255];
			strcpy(temp, option_sel[0]);
			temp[strlen(temp)-4]=0;
			strcat(temp, "_CHECK.md5");
			open_txt_viewer(temp);
		}
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_EXTRACT_RCO) == 0) {
		start_loading();
		print_head("Extracting RCO");
		rco_dump(option_sel[0]);
		end_loading();
		Window(".");
	} else 
	if(strcmp(item, STR_EXTRACT_ISO) == 0) {
		start_loading();
		print_head("Extracting ISO...");
		
		char dst[255];
		strcpy(dst, option_sel[0]);
		if(strstr(dst, ".iso.0") || strstr(dst, ".ISO.0")) dst[strlen(dst)-6]=0; 
		else dst[strlen(dst)-4]=0;
		
		u8 ret = extractps3iso(option_sel[0], dst, is_usb(option_sel[0]));
		
		if(ret==FAILED) show_msg(STR_FAILED); 
		else show_msg(STR_DONE);
		
		end_loading();
		Window(".");
	} 
	else
	if(strcmp(item, STR_CONVERT_ISO) == 0) {
		start_loading();
		print_head("Converting to ISO...");
		
		char dst[255];
		sprintf(dst, "%s.ISO", option_sel[0]);
		
		u8 ret = makeps3iso(option_sel[0], dst, is_usb(option_sel[0]));
		
		if(ret==FAILED) show_msg(STR_FAILED); 
		else show_msg(STR_DONE);
		
		end_loading();
		Window(".");
	}
	else
	if(strcmp(item, STR_COMPRESS_ISO) == 0) {
		start_loading();
		print_head("Compressing ISO...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='C';
		dst[strlen(dst)-2]='S';
		dst[strlen(dst)-1]='O';
		if(comp_ciso(option_sel[0], dst, 1)==FAILED) Delete(dst);
		end_loading();
		Window(".");
	} else
	if(strcmp(item, STR_DECOMPRESS_CSO) == 0) {
		start_loading();
		print_head("Decompressing CSO...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='I';
		dst[strlen(dst)-2]='S';
		dst[strlen(dst)-1]='O';
		if(decomp_ciso(option_sel[0], dst)==FAILED) Delete(dst);
		end_loading();
		Window(".");
	}
	else 
	if(strcmp(item, STR_EXTRACT_THM) == 0) {
		start_loading();
		print_head("Extracting THM...");
		ExtractTHM(option_sel[0]);
		end_loading();
		Window(".");
	}
	else 
	if(strcmp(item, STR_EXTRACT_P3T) == 0) {
		start_loading();
		print_head("Extracting P3T...");
		cxml_extract(option_sel[0]);
		end_loading();
		Window(".");
	}
	else 
	if(strcmp(item, STR_EXTRACT_RAF) == 0) {
		start_loading();
		print_head("Extracting RAF...");
		cxml_extract(option_sel[0]);
		end_loading();
		Window(".");
	}
	else 
	if(strcmp(item, STR_EXTRACT_QRC) == 0) {
		start_loading();
		print_head("Extracting QRC...");
		ExtractQRC(option_sel[0]);
		end_loading();
		Window(".");
	}
	else
	if(strcmp(item, STR_CONVERT_GTF_DDS) == 0) {
		start_loading();
		print_head("Converting to DDS...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='d';
		dst[strlen(dst)-2]='d';
		dst[strlen(dst)-1]='s';
		gtf2dds(option_sel[0], dst, 0, 0);
		end_loading();
		Window(".");
	}
	else 
	if(strcmp(item, STR_CONVERT_VAG_WAV) == 0) {
		start_loading();
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='w';
		dst[strlen(dst)-2]='a';
		dst[strlen(dst)-1]='v';
		print_head("Converting to wav...");
		VAG2WAV(option_sel[0], dst);
		end_loading();
		Window(".");
	}
	else 
	if(strcmp(item, STR_CONVERT_JSX_JS) == 0) {
		start_loading();
		print_head("Converting to JS...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-1]=0;
		JSX2JS(option_sel[0], dst);
		end_loading();
		Window(".");
	}
	else 
	if(strcmp(item, STR_CONVERT_DDS_PNG) == 0) { 
		start_loading();
		print_head("Converting to PNG...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='p';
		dst[strlen(dst)-2]='n';
		dst[strlen(dst)-1]='g';
		ConvertImage(option_sel[0], dst);
		end_loading();
		Window(".");
	}
	else
	if(strcmp(item, STR_MAKE_APNG) == 0) { 
		start_loading();
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strrchr(dst, '/') - dst] = 0;
		strcat(dst, "/Animated.png\0");
		Build_APNG(option_sel, option_sel_N, dst, 0);
		end_loading();
		Window(".");
	}
	else 
	if(strcmp(item, STR_READ_XREG) == 0) { 
		start_loading();
		if( xreg2txt(option_sel[0], "/dev_hdd0/tmp/xreg.txt") == SUCCESS ) 
			open_txt_viewer("/dev_hdd0/tmp/xreg.txt");
		end_loading();
	}
	else
	if(strcmp(item, STR_SET_PERMS) == 0) {
		start_loading();
		print_head("Setting permissions...");
		for(i=0; i<=option_sel_N; i++) {
			SetPerms(option_sel[i]);
		}
		end_loading();
	}
	else
	if(strcmp(item, STR_EXTRACT_ZIP) == 0) { 
		start_loading();
		print_head("Extracting ZIP");
		ExtractZip(option_sel[0]);
		end_loading();
		Window(".");
	}
	else
	if(strcmp(item, STR_MOUNTGAME) == 0) {
		start_loading();
		read_game_setting(NULL);
		MountGame(option_sel[0]);
		end_loading();
	}
	else
	if(strcmp(item, STR_DOCK_FULL) == 0) {
		SetWindowLocation(WINDOW_LOC_FULL);
	} 
	else
	if(strcmp(item, STR_DOCK_LEFT) == 0) {
		SetWindowLocation(WINDOW_LOC_LEFT);
	} 
	else
	if(strcmp(item, STR_DOCK_RIGHT) == 0) {
		SetWindowLocation(WINDOW_LOC_RIGHT);
	} 
	else
	if(strcmp(item, STR_RESTORE) == 0) {
		SetWindowLocation(WINDOW_LOC_DEFAULT);
	} 
	else
	if(strcmp(item, STR_CLOSE) == 0) {
		CloseWindow();
	}
	
}

void add_option_item(char *str)
{
	option_item_N++;
	option_item[option_item_N] = strcpy_malloc(str);
}

void Open_option()
{
	option_item_N = -1;
	option_sel_N = -1;
	
	int i;
	option_item = (char **) malloc(OPTION_MAX * sizeof(char *));
	option_sel = (char **) malloc(WINDOW_MAX_ITEMS * sizeof(char *));
	
	for(i=0; i<WINDOW_MAX_ITEMS; i++) option_sel[i]=NULL;
	for(i=0; i<OPTION_MAX; i++) option_item[i]=NULL;
	
	if(window_activ == -1) {
		add_option_item(STR_OPEN_WINDOW);
	} else
	if( window_x[window_activ] + BORDER < curs_x && curs_x < window_x[window_activ] + window_w[window_activ] - BORDER - 40
	&&  window_y[window_activ] + BORDER < curs_y && curs_y < window_y[window_activ] + TOP_H ) {
		u8 loc = GetWindowLocation();
		if(loc!=WINDOW_LOC_FULL) add_option_item(STR_DOCK_FULL);
		if(loc!=WINDOW_LOC_LEFT) add_option_item(STR_DOCK_LEFT);
		if(loc!=WINDOW_LOC_RIGHT) add_option_item(STR_DOCK_RIGHT);
		if(loc!=WINDOW_LOC_DEFAULT) add_option_item(STR_RESTORE);
		add_option_item(STR_CLOSE);
	} else
	if(strcmp( window_path[window_activ], "/") == 0) {
		add_option_item(STR_OPEN_WINDOW);
		add_option_item(STR_MOUNT_DEVBLIND);
		if(PEEKnPOKE) {
			add_option_item(STR_DUMP_LV1);
			add_option_item(STR_DUMP_LV2);
			
		}
		add_option_item(STR_DUMP_FLASH);
		add_option_item("SpeedTest");
	}
	else {
		u8 all_is_dir=YES;
		int all_same_ext=-1;
		for(i=0; i<=window_content_N[window_activ]; i++) {
			if(window_content_Selected[window_activ][i] == YES) {
				option_sel_N++;
				option_sel[option_sel_N] = sprintf_malloc("%s/%s", window_path[window_activ], window_content_Name[window_activ][i]);
				if(path_info(option_sel[option_sel_N]) != _DIRECTORY) all_is_dir=NO;
				if(all_same_ext != -2) {
					if(all_same_ext == -1) all_same_ext = get_ext(option_sel[option_sel_N]); else
					if(all_same_ext != get_ext(option_sel[option_sel_N])) all_same_ext = -2;
				}
			}
		}
		
		add_option_item(STR_REFRESH);
		add_option_item(STR_NEWFOLDER);
		add_option_item(STR_NEWFILE);
		
		if(0 <= option_copy_N) {
			add_option_item(STR_PASTE);
		}
		if(0 <= option_sel_N) {
			add_option_item(STR_COPY);
			add_option_item(STR_CUT);
			add_option_item(STR_DELETE);
			add_option_item(STR_UNSELECT_ALL);
		}																									
		add_option_item(STR_SELECT_ALL);
		
		if(option_sel_N == 0) {
			add_option_item(STR_RENAME);
			
			if(path_info(option_sel[0]) == _DIRECTORY ) {
				add_option_item(STR_MAKE_PKG);
				add_option_item(STR_GETMD5);
				add_option_item(STR_GETSHA1);				
			}
			
			u8 ext = get_ext(option_sel[0]);
			
			if(ext == _JPG || ext == _PNG) {
				add_option_item(STR_VIEW);
			} else 
			if( can_read(ext) == YES) {
				add_option_item(STR_VIEW_TXT);
			} else
			if(ext == _SFO) {
				add_option_item(STR_VIEW_SFO);
			} else
			if(ext == _XREG) {
				add_option_item(STR_READ_XREG);
			} else
			if(ext == _SELF) {
				add_option_item(STR_EXTRACT_ELF);
				add_option_item(STR_RESIGN_SELF);
				add_option_item(STR_LAUNCH_SELF);
			} else 
			if(ext == _EBOOT_BIN) {
				add_option_item(STR_EXTRACT_EBOOT);
				add_option_item(STR_RESIGN_EBOOT);
				add_option_item(STR_LAUNCH_EBOOT);
			} else 
			if(ext == _EBOOT_ELF) {
				add_option_item(STR_SIGN_EBOOT);
			} else 
			if(ext == _ELF) {
				add_option_item(STR_SIGN_ELF);
			}  else		
			if(ext == _SPRX) {
				add_option_item(STR_EXTRACT_PRX);
				add_option_item(STR_RESIGN_SPRX);
				
				if(path_info("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt") != _NOT_EXIST) {
					if(is_it_inside("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt", option_sel[0]) == YES) {
						add_option_item(STR_REMOVE_PRXLOADER);
					} else {
						add_option_item(STR_ADD_PRXLOADER);
					}					
				}
				
				if(path_info("/dev_hdd0/prx_plugins.txt") != _NOT_EXIST) {
					if(is_it_inside("/dev_hdd0/prx_plugins.txt", option_sel[0]) == YES) {
						add_option_item(STR_REMOVE_PRXLOADER2);
					} else {
						add_option_item(STR_ADD_PRXLOADER2);
					}					
				}
				
				if(path_info("/dev_hdd0/mamba_plugins.txt") != _NOT_EXIST) {
					if(is_it_inside("/dev_hdd0/mamba_plugins.txt", option_sel[0]) == YES) {
						add_option_item(STR_REMOVE_MAMBA);
					} else {
						add_option_item(STR_ADD_MAMBA);
					}
				}
				
				if(path_info("/dev_hdd0/boot_plugins.txt") != _NOT_EXIST) {
					if(is_it_inside("/dev_hdd0/boot_plugins.txt", option_sel[0]) == YES) {
						add_option_item(STR_REMOVE_COBRA);
					} else {
						add_option_item(STR_ADD_COBRA);
					}
				}
			} else
			if(ext == _PRX) {
				add_option_item(STR_SIGN_PRX);
			} else
			if(ext == _RCO) {
				add_option_item(STR_EXTRACT_RCO);
			} else 
			if(ext == _PKG) {
				add_option_item(STR_EXTRACT_PKG);
				add_option_item(STR_PKG_INFO);
			} else
			if(ext == _TRP) {
				add_option_item(STR_EXTRACT_TRP);
			} else
			if(ext == _JB_PS3 || ext == _ISO_PS3) {
				if(ext == _ISO_PS3) {
					add_option_item(STR_EXTRACT_ISO);
				} else
				if(ext == _JB_PS3) {
					add_option_item(STR_CONVERT_ISO);
				}
				add_option_item(STR_CHECK_IRD);
			} else
			if(ext == _ISO_PSP) {
				add_option_item(STR_COMPRESS_ISO);
				add_option_item(STR_CHECK_CRC32);
			} else
			if(ext == _CSO) {
				add_option_item(STR_DECOMPRESS_CSO);
			} else
			if(ext == _THM) {
				add_option_item(STR_EXTRACT_THM);
			} else
			if(ext == _P3T) {
				add_option_item(STR_EXTRACT_P3T);
			} else
			if(ext == _RAF) {
				add_option_item(STR_EXTRACT_RAF);
			} else
			if(ext == _QRC) {
				add_option_item(STR_EXTRACT_QRC);
			} else
			if(ext == _JSX) {
				add_option_item(STR_CONVERT_JSX_JS);
			} else
			if(ext == _VAG) {
				add_option_item(STR_CONVERT_VAG_WAV);
			} else
			if(ext == _GTF) {
				add_option_item(STR_CONVERT_GTF_DDS);
			} else
			if(ext == _DDS) {
				add_option_item(STR_CONVERT_DDS_PNG);
			} else
			if(ext == _ZIP) {
				add_option_item(STR_EXTRACT_ZIP);
			}
			
			if( is_66600(option_sel[0])) {
				add_option_item(STR_JOIN);
			}
			
			if(can_mount()) {
				if(ext == _ISO_PS3 || ext == _ISO_PS2 || ext == _ISO_PS1 || ext == _ISO_PSP || ext == _JB_PS3) {
					add_option_item(STR_MOUNTGAME);
				}
			}
			
			
		}
		
		if(all_same_ext >= 0 && option_sel_N > 0) {
			if(all_same_ext == _PNG) {
				add_option_item(STR_MAKE_APNG);
			}
		}
		
		if(0 <= option_sel_N) {
			add_option_item(STR_SET_PERMS);
		}
		
		add_option_item(STR_PROPS);
	}
	
	float k=0;
	for(i=0; i<=option_item_N; i++) {
		if(k<GetWidth(option_item[i])) k=GetWidth(option_item[i]);
	}
	option_activ = YES;
	option_x = curs_x - 7;
	option_y = curs_y - 7;
	option_h = (option_item_N+1)*15;
	option_w = k+30;
	if(option_y+option_h > 485) option_y = 485 - option_h; 

}

void Draw_option()
{
	if(option_activ == NO) return;
	
	FontColor(BLACK);
	Draw_Box(option_x-1, option_y-1, 0, 0, option_w+2, option_h+2, BLACK, NO); // BORDER
	Draw_Box(option_x, option_y, 0, 0, option_w, option_h, 0xF0F0F0FF, NO);
	FontSize(15);
	SetFontZ(0);
	
	int i;
	for(i=0; i<=option_item_N;i++) {
		if(option_x 	 < curs_x && curs_x < option_x+option_w
		&& option_y+15*i < curs_y && curs_y < option_y+15*(i+1)) {
			FontColor(GREEN);
			Draw_Box(option_x, option_y+15*i, 0, 0, option_w, 15, 0x00D0FFFF, NO);
		} else FontColor(BLACK);
		
		DrawFormatString(option_x+5, option_y+15*i, option_item[i]);
	}
}

void close_option()
{
	int i;
	for(i=0; i<OPTION_MAX; i++) FREE(option_item[i]);
	FREE(option_item);
	
	for(i=0; i<WINDOW_MAX_ITEMS; i++) FREE(option_sel[i]);
	FREE(option_sel);
		
	option_activ = NO;
}

u8 option_input()
{
	if(option_activ == NO) return OFF;
	
	if(new_pad & BUTTON_CROSS) {	
		//Cursor on option
		if(	option_x < curs_x && curs_x < option_x + option_w
		&& 	option_y < curs_y && curs_y < option_y + option_h )
		{
			int i;
			for(i=0; i<=option_item_N; i++) {
				if(option_x 	 < curs_x && curs_x < option_x+option_w
				&& option_y+15*i < curs_y && curs_y < option_y+15*(i+1)) {
					Option(option_item[i]);
				}
			}
		}
		close_option();
	}
	
	if((new_pad & BUTTON_TRIANGLE) || (new_pad & BUTTON_CIRCLE))  {
		close_option();
	}
	
	if(new_pad & BUTTON_UP) {
		if(	option_x < curs_x && curs_x < option_x + option_w
		&& 	option_y + 15 < curs_y && curs_y < option_y + option_h )
		{
			curs_y -= 15;
		}
	}
	
	if(new_pad & BUTTON_DOWN) {
		if(	option_x < curs_x && curs_x < option_x + option_w
		&& 	option_y < curs_y && curs_y < option_y + option_h - 15 )
		{
			curs_y += 15;
		}
	}
	
	return ON;
}

void cursor_input() 
{
	curs_move_x = R2JoyStick_X(BUTTON_L);
	curs_move_y = R2JoyStick_Y(BUTTON_L);
	curs_x += curs_move_x;
	curs_y += curs_move_y;
	if(curs_x > 848) curs_x=848;
	if(curs_x < 0  ) curs_x=0  ;
	if(curs_y > 512) curs_y=512;
	if(curs_y < 0  ) curs_y=0  ;

}

u8 window_input()
{
	int i;
	int k;
	
	if(option_activ == YES) return CONTINUE;
	if(prop_activ == YES) return CONTINUE;
	if(picture_viewer_activ == YES) return CONTINUE;
	if(txt_viewer_activ == YES) return CONTINUE;
	if(SFO_viewer_activ == YES) return CONTINUE;
	
	get_R2speed();

	if(old_pad & BUTTON_CROSS) curs_push = YES;
	else curs_push = NO;

// Exit FileManager
#ifdef FILEMANAGER
	if(window_activ < 0) {
		if(new_pad & BUTTON_CIRCLE) {
			while(hold_CIRCLE%30!=0) hold_CIRCLE++;
			hold_CIRCLE+=15;
		} else
		if(old_pad & BUTTON_CIRCLE) {
			hold_CIRCLE++;
		} else {
			if(hold_CIRCLE%30==0) hold_CIRCLE=0;
			else hold_CIRCLE--;
		}

		if(hold_CIRCLE>90) {
			finalize_FileExplorer();
			return BREAK;
		}
	} else {
		if(new_pad & BUTTON_CIRCLE) {
			CloseWindow();
			return CONTINUE;
		}
	}
#else
	if(new_pad & BUTTON_CIRCLE) {
		if(window_activ < 0) {
			finalize_FileExplorer();
			return BREAK;
		} else {
			CloseWindow();
			return CONTINUE;
		}
	}
#endif

	// OPTIONS
	if((new_pad & BUTTON_TRIANGLE))  {
		Open_option();
		return CONTINUE;
	}
	
	// New window
	if(new_pad & BUTTON_START) {
		Window(NULL);
	}
	
#ifdef FILEMANAGER
	if(new_pad & BUTTON_SELECT) {
		open_SETTINGS();
		return CONTINUE;
	}
#endif
	
	if(window_activ < 0) return CONTINUE;

	// R3 move window
	window_x[window_activ] += R2JoyStick_X(BUTTON_R);
	window_y[window_activ] += R2JoyStick_Y(BUTTON_R);
	if(window_x[window_activ] + window_w[window_activ] > 848 ) window_x[window_activ]=848-window_w[window_activ];
	if(window_x[window_activ] < 0 ) window_x[window_activ]=0;
	if(window_y[window_activ] + window_h[window_activ] > 512 ) window_y[window_activ]=512-window_h[window_activ];
	if(window_y[window_activ] < 0 ) window_y[window_activ]=0;

	// 'MOUSE CLICK'
	if(new_pad & BUTTON_CROSS) {
		//Cursor on activ window
		if(	window_x[window_activ] < curs_x && curs_x < (window_x[window_activ] + window_w[window_activ])
		&& 	window_y[window_activ] < curs_y && curs_y < (window_y[window_activ] + window_h[window_activ])   )
		{
			// browse
			for(i=0 ; i<=window_item_N[window_activ]; i++) {
				if(window_content_N[window_activ] < i+window_scroll_P[window_activ]) break;
				if(  window_x[window_activ]+BORDER						< curs_x && curs_x < window_x[window_activ]	+ window_w[window_activ]-SCROLL_W-BORDER
				&&	 window_y[window_activ]+TOP_H+COL_H+CONTENT_FSIZE*i	< curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H+CONTENT_FSIZE*(i+1)				)
				{
					if(window_content_Type[window_activ][i+window_scroll_P[window_activ]] == _DIRECTORY) {
						Window(window_content_Name[window_activ][i+window_scroll_P[window_activ]]);
					} else 
					if(window_content_Type[window_activ][i+window_scroll_P[window_activ]] == _JPG || window_content_Type[window_activ][i+window_scroll_P[window_activ]] == _PNG) {
						char picpath[255];
						sprintf(picpath, "%s/%s", window_path[window_activ], window_content_Name[window_activ][i+window_scroll_P[window_activ]]);
						open_picture_viewer(picpath);
					} else 
					if( can_read(window_content_Type[window_activ][i+window_scroll_P[window_activ]] ) == YES ) {
						char txtpath[255];
						sprintf(txtpath, "%s/%s", window_path[window_activ], window_content_Name[window_activ][i+window_scroll_P[window_activ]]);
						open_txt_viewer(txtpath);
					} else 
					if(window_content_Type[window_activ][i+window_scroll_P[window_activ]] == _SFO) {
						char sfopath[255];
						sprintf(sfopath, "%s/%s", window_path[window_activ], window_content_Name[window_activ][i+window_scroll_P[window_activ]]);
						open_SFO_viewer(sfopath);
					} else 
					if(window_content_Type[window_activ][i+window_scroll_P[window_activ]] == _ISO) {
						char IsoPath[255];
						sprintf(IsoPath, "%s/%s", window_path[window_activ], window_content_Name[window_activ][i+window_scroll_P[window_activ]]);
						read_game_setting(NULL);
						if( MountGame(IsoPath) == SUCCESS) {
							finalize_FileExplorer();
							exit(0);
						}
					}
				}
			}
			
			// Close
			if( window_x[window_activ]+window_w[window_activ]-10-30 < curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-10
			&&  window_y[window_activ]+10						 	< curs_y && curs_y < window_y[window_activ]+10+20 )
			{
				CloseWindow();
			}
						
			// sort Name
			if( window_x[window_activ]+BORDER   < curs_x && curs_x < window_x[window_activ] + window_w[window_activ]-BORDER-SCROLL_W - window_w_col_size[window_activ]- 10
			&&	window_y[window_activ]+TOP_H	< curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H )
			{
				if(window_sort[window_activ] == ASC) window_sort[window_activ] = DSC;
				else window_sort[window_activ] = ASC;
				sort();
			}
		}
		// cursor on passiv window
		else {
			k=-1;
			for(i=0; i<10; i++) {
				if(i==window_activ) continue;
				if(window_open[i]==NO) continue;
				if(	window_x[i] < curs_x && curs_x < (window_x[i] + window_w[i])
				&& 	window_y[i] < curs_y && curs_y < (window_y[i] + window_h[i])   )
				{
					if(k==-1) k=i; else
					if(window_z[i] < window_z[k]) k=i;
				}
			}
			if(k!=-1) {
				window_activ = k;
				window_z[window_activ] = 1;
				for(i=0; i<10; i++) {
					if(window_open[i] == NO) continue;
					if(i==window_activ) continue;
					window_z[i]++;
				}
			}
		}
	}
	
	//SELECT ITEM
	if(new_pad & BUTTON_SQUARE) {
		if(	window_x[window_activ] < curs_x && curs_x < (window_x[window_activ] + window_w[window_activ])
		&& 	window_y[window_activ] < curs_y && curs_y < (window_y[window_activ] + window_h[window_activ])   )
		{
			for(i=0 ; i <=window_item_N[window_activ]; i++) {
				if(window_content_N[window_activ] < i+window_scroll_P[window_activ]) break;
				if(  window_x[window_activ]+BORDER							< curs_x && curs_x < window_x[window_activ] + window_w[window_activ]-SCROLL_W-BORDER
				&&	 window_y[window_activ]+TOP_H+COL_H+CONTENT_FSIZE*i		< curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H+CONTENT_FSIZE*(i+1)				)
				{
					if(window_content_Selected[window_activ][i+window_scroll_P[window_activ]] == NO) {
						if(strcmp(window_content_Name[window_activ][i+window_scroll_P[window_activ]], "..") != 0) {
							window_content_Selected[window_activ][i+window_scroll_P[window_activ]]=YES;
						}
					} else window_content_Selected[window_activ][i+window_scroll_P[window_activ]]=NO;
				}
			}
		}
	}
	
	//MOVE WINDOW
	if((window_x[window_activ] + BORDER < curs_x && curs_x < window_x[window_activ] + window_w[window_activ] - BORDER - 40
	&&  window_y[window_activ] + BORDER < curs_y && curs_y < window_y[window_activ] + TOP_H)
	||
	((	window_move == YES && curs_push) &&
	(	window_x[window_activ] - BORDER*3 < curs_x && curs_x < window_x[window_activ] + window_w[window_activ] + BORDER*3 
	&&  window_y[window_activ] - BORDER*3 < curs_y && curs_y < window_y[window_activ] + TOP_H + BORDER*3) ) )
	{
		window_move = YES;
		if(curs_push) {
			window_x[window_activ] += curs_move_x;
			window_y[window_activ] += curs_move_y;
			if(window_x[window_activ] + window_w[window_activ] > 848 ) window_x[window_activ]=848-window_w[window_activ];
			if(window_x[window_activ] < 0 ) window_x[window_activ]=0;
			if(window_y[window_activ] + window_h[window_activ] > 512 ) window_y[window_activ]=512-window_h[window_activ];
			if(window_y[window_activ] < 0 ) window_y[window_activ]=0;
		}
	} else window_move = NO;
	
	// LEFT
	if((window_x[window_activ] < curs_x && curs_x < window_x[window_activ] + BORDER  
	&&  window_y[window_activ] + BORDER < curs_y && curs_y < window_y[window_activ] + window_h[window_activ] - BORDER )
	||
	((window_resize_H && curs_push) && 
	(	window_x[window_activ] - BORDER*3 < curs_x && curs_x < window_x[window_activ] + BORDER*3  
	&&  window_y[window_activ] + BORDER*3 < curs_y && curs_y < window_y[window_activ] + window_h[window_activ] - BORDER*3 ) ) )
	{
		window_resize_H = YES;
		if(curs_push && (window_w[window_activ] > WINDOW_MIN || curs_move_x < 0)) {
			window_w[window_activ] -= curs_move_x ;
			window_x[window_activ] += curs_move_x;
		}
	} else
	// RIGHT
	if((window_x[window_activ] + window_w[window_activ] - BORDER < curs_x && curs_x < window_x[window_activ] + window_w[window_activ] 
	&&  window_y[window_activ] + BORDER < curs_y && curs_y < window_y[window_activ] + window_h[window_activ] - BORDER )
	||
	((window_resize_H && curs_push) && 
	(   window_x[window_activ] + window_w[window_activ] - BORDER*3 < curs_x && curs_x < window_x[window_activ] + window_w[window_activ] + BORDER*3
	&&  window_y[window_activ] + BORDER*3 < curs_y && curs_y < window_y[window_activ] + window_h[window_activ] - BORDER*3 ) ) )
	{
		window_resize_H = YES;
		if(curs_push && (window_w[window_activ] > WINDOW_MIN || curs_move_x > 0)) window_w[window_activ] += curs_move_x ;
	} else 
	//resize column
	if((window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W-window_w_col_size[window_activ] - 5 < curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W-window_w_col_size[window_activ] + 5
	&&  window_y[window_activ]+TOP_H < curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H )
	||( window_resize_H 
	&&  curs_push
	&& 	window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W-window_w_col_size[window_activ] - 30 < curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W-window_w_col_size[window_activ] + 30
	&&  window_y[window_activ]+TOP_H < curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H) )
	{
		window_resize_H = YES;
		if(curs_push==YES) window_w_col_size[window_activ] -= curs_move_x;
	} else window_resize_H = NO;
	
	//TOP
	if((window_y[window_activ]  < curs_y && curs_y < window_y[window_activ] + BORDER
	&&	window_x[window_activ] + BORDER < curs_x && curs_x < window_x[window_activ] + window_w[window_activ] - BORDER )
	||
	((window_resize_V && curs_push) && 
	(	window_y[window_activ] - BORDER*3 < curs_y && curs_y < window_y[window_activ] + BORDER*3
	&&	window_x[window_activ] + BORDER*3 < curs_x && curs_x < window_x[window_activ] + window_w[window_activ] - BORDER*3 ) ) )
	{
		window_resize_V = YES;
		if(curs_push && (window_h[window_activ] > WINDOW_MIN || curs_move_y < 0)) {
			window_h[window_activ] -= curs_move_y;
			window_y[window_activ] += curs_move_y;
		}
		
	} else 
	//BOT
	if((window_y[window_activ] + window_h[window_activ] - BORDER < curs_y && curs_y < window_y[window_activ] + window_h[window_activ]
	&&	window_x[window_activ] + BORDER							< curs_x && curs_x < window_x[window_activ] + window_w[window_activ] - BORDER )
	||
	((window_resize_V && curs_push) && 
	(	window_y[window_activ] + window_h[window_activ] - BORDER*3   < curs_y && curs_y < window_y[window_activ] + window_h[window_activ] + BORDER*3
	&&	window_x[window_activ] + BORDER*3							 < curs_x && curs_x < window_x[window_activ] + window_w[window_activ] - BORDER*3 ) ) )
	{
		window_resize_V = YES;
		if(curs_push && (window_h[window_activ] > WINDOW_MIN || curs_move_y > 0)) {
			window_h[window_activ] += curs_move_y;
		}
	} else window_resize_V = NO;
	
	//TOP-LEFT
	if((window_x[window_activ] < curs_x && curs_x < window_x[window_activ] + BORDER 
	&&  window_y[window_activ] < curs_y && curs_y < window_y[window_activ] + BORDER )
	||
	((window_resize_D1 && curs_push) && 
	(	window_x[window_activ]-BORDER*3 < curs_x && curs_x < window_x[window_activ]+BORDER*3 
	&&  window_y[window_activ]-BORDER*3 < curs_y && curs_y < window_y[window_activ]+BORDER*3) ) )
	{
		window_resize_D1 = YES;
		if(curs_push && (window_h[window_activ] > WINDOW_MIN || curs_move_y < 0)) {
			window_h[window_activ] -= curs_move_y;
			window_y[window_activ] += curs_move_y;
		}
		if(curs_push && (window_w[window_activ] > WINDOW_MIN || curs_move_x < 0)) {
			window_w[window_activ] -= curs_move_x ;
			window_x[window_activ] += curs_move_x;
		}
	} else
	//BOT-RIGHT
	if((window_x[window_activ]+window_w[window_activ]-BORDER < curs_x && curs_x < window_x[window_activ]+window_w[window_activ] 
	&&  window_y[window_activ]+window_h[window_activ]-BORDER < curs_y && curs_y < window_y[window_activ]+window_h[window_activ]  )
	||
	((window_resize_D1 && curs_push) && 
	(	window_x[window_activ]+window_w[window_activ]-BORDER*3 < curs_x && curs_x < window_x[window_activ]+window_w[window_activ] +BORDER*3 
	&&  window_y[window_activ]+window_h[window_activ]-BORDER*3 < curs_y && curs_y < window_y[window_activ]+window_h[window_activ] +BORDER*3 ) ) )
	{
		window_resize_D1 = YES;
		if(curs_push && (window_h[window_activ] > WINDOW_MIN || curs_move_y > 0)) window_h[window_activ] += curs_move_y;
		if(curs_push && (window_w[window_activ] > WINDOW_MIN || curs_move_x > 0)) window_w[window_activ] += curs_move_x ;
	} else window_resize_D1 = NO;
	
	//TOP-RIGHT
	if((window_x[window_activ]+window_w[window_activ]-BORDER < curs_x && curs_x < window_x[window_activ]+window_w[window_activ] 
	&&  window_y[window_activ]								 < curs_y && curs_y < window_y[window_activ]+BORDER )
	||
	(	window_resize_D2 
	&& 	curs_push 
	&&  window_x[window_activ]+window_w[window_activ]-BORDER*3	< curs_x && curs_x < window_x[window_activ]+window_w[window_activ] + BORDER*3 
	&&  window_y[window_activ]-BORDER*3							< curs_y && curs_y < window_y[window_activ]+BORDER*3 ) )
	{
		window_resize_D2 = YES;
		if(curs_push && (window_h[window_activ] > WINDOW_MIN || curs_move_y < 0)) {
			window_h[window_activ] -= curs_move_y;
			window_y[window_activ] += curs_move_y;
		}
		if(curs_push && (window_w[window_activ] > WINDOW_MIN || curs_move_x > 0)) window_w[window_activ] += curs_move_x ;
	} else
	//BOT-LEFT
	if((window_x[window_activ]							< curs_x && curs_x < window_x[window_activ]+BORDER 
	&&  window_y[window_activ]+window_h[window_activ]-BORDER < curs_y && curs_y < window_y[window_activ]+window_h[window_activ] )
	||
	(window_resize_D2
	&& curs_push
	&& window_x[window_activ]-BORDER*3 							< curs_x && curs_x < window_x[window_activ]+BORDER*3 
	&& window_y[window_activ]+window_h[window_activ]-BORDER*3   < curs_y && curs_y < window_y[window_activ]+window_h[window_activ]+BORDER*3 ) )	
	{
		window_resize_D2 = YES;
		if(curs_push && (window_h[window_activ] > WINDOW_MIN || curs_move_y > 0)) window_h[window_activ] += curs_move_y;
		if(curs_push && (window_w[window_activ] > WINDOW_MIN || curs_move_x < 0)) {
			window_w[window_activ] -= curs_move_x ;
			window_x[window_activ] += curs_move_x;
		}
	} else window_resize_D2 = NO;
	
	//scroll
	if(window_scroll_N[window_activ]>0 && curs_push) {
		if( window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W < curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-BORDER) {
			// Hold it to move
			if( window_y[window_activ]+TOP_H+COL_H+window_scroll_y[window_activ] < curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H+window_scroll_y[window_activ]+window_scroll_size[window_activ] )
			{
				if(( curs_move_y < 0 && window_scroll_P[window_activ] > 0) 
				|| ( curs_move_y > 0 && window_scroll_P[window_activ] < window_scroll_N[window_activ])) 
				{
					
					curs_move_scroll += curs_move_y;
					
					if(curs_move_scroll > 0 && (window_h[window_activ]-TOP_H-COL_H-window_scroll_size[window_activ]-BORDER) * (window_scroll_P[window_activ]+1) / window_scroll_N[window_activ] < window_scroll_y[window_activ] ) {
						window_scroll_P[window_activ]++;
						curs_move_scroll=0;
					}
					if(curs_move_scroll < 0 && window_scroll_y[window_activ] < (window_h[window_activ]-TOP_H-COL_H-window_scroll_size[window_activ]-BORDER) * (window_scroll_P[window_activ]-1) / window_scroll_N[window_activ] ) {
						window_scroll_P[window_activ]--;
						curs_move_scroll=0;
					}
				}
				else curs_move_scroll=0;
			} else
			// Down
			if(window_y[window_activ]+TOP_H+COL_H+window_scroll_y[window_activ]+window_scroll_size[window_activ] < curs_y && curs_y < window_y[window_activ]+window_h[window_activ]-BORDER) {
				if(window_scroll_P[window_activ] < window_scroll_N[window_activ]) window_scroll_P[window_activ]++;
			} else
			// Up
			if(window_y[window_activ]+TOP_H+COL_H < curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H+window_scroll_y[window_activ]) {
				if(window_scroll_P[window_activ]>0) window_scroll_P[window_activ]--;
			}
		}
	}
	
	// DOCK screen
	if(old_pad & BUTTON_R1) {
		if(new_pad & BUTTON_LEFT) {
			SetWindowLocation(WINDOW_LOC_LEFT);
			return CONTINUE;
		} else
		if(new_pad & BUTTON_UP) {
			SetWindowLocation(WINDOW_LOC_FULL);
			return CONTINUE;
		} else
		if(new_pad & BUTTON_RIGHT) {
			SetWindowLocation(WINDOW_LOC_RIGHT);
			return CONTINUE;
		} else
		if(new_pad & BUTTON_DOWN) {
			SetWindowLocation(WINDOW_LOC_DEFAULT);
			return CONTINUE;
		}
	 }
	
	//Refresh Window 
	if(new_pad & BUTTON_L3) {
		Window(".");
	}
	
	//Parent directory
	if(old_pad & BUTTON_L1) {
		if(new_pad & BUTTON_LEFT) {
			Window("..");
			return CONTINUE;
		} else
		if(new_pad & BUTTON_RIGHT) {
			GotoLastPath();
			return CONTINUE;
		}
	}
	
	
	//Grid_move up page
	if( R2pad(BUTTON_LEFT) ) {
		if(window_scroll_P[window_activ]>0) {
			if(window_scroll_P[window_activ] > window_item_N[window_activ] ) window_scroll_P[window_activ]-=window_item_N[window_activ];
			else window_scroll_P[window_activ]=0;
		}
	}
	
	//Grid_move down page
	if( R2pad(BUTTON_RIGHT) ){
		if(window_scroll_N[window_activ]>0) {
			if(window_scroll_P[window_activ] < window_scroll_N[window_activ]) {
				if(window_scroll_P[window_activ] + window_item_N[window_activ] < window_scroll_N[window_activ])	window_scroll_P[window_activ]+=window_item_N[window_activ];
				else window_scroll_P[window_activ] = window_scroll_N[window_activ];
			}
		}
	}
	
	//Grid_move up scroll
	if( R2pad(BUTTON_UP) ) {
		if(window_scroll_P[window_activ]>0) window_scroll_P[window_activ]--;
	}
	
	//Grid_move down scroll
	if( R2pad(BUTTON_DOWN) ) {
		if(window_scroll_N[window_activ] > 0)
		if(window_scroll_P[window_activ] < window_scroll_N[window_activ]) window_scroll_P[window_activ]++;
	}

	return CONTINUE;
}

void Draw_input()
{
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);

	if(option_activ == NO 
	&& prop_activ == NO 
	&& picture_viewer_activ == NO 
	&& txt_viewer_activ == NO
	&& SFO_viewer_activ == NO) {
		if(window_activ < 0) {
#ifdef FILEMANAGER 
			if(hold_CIRCLE) {
				DrawProgRing(x+7, y+7.5, 20, ((hold_CIRCLE%30)*100)/30, COLOR_3);
				FontColor(COLOR_3);
				DrawFormatString(x+10, y-12, "%d", (90 - hold_CIRCLE)/30);
				FontColor(COLOR_1);
			}
			x=DrawButton(x, y, STR_BACKTOXMB, BUTTON_CIRCLE);
#else
			x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
#endif
		} else {
			x=DrawButton(x, y, STR_CLOSE, BUTTON_CIRCLE);
		}
#ifdef FILEMANAGER
		x=DrawButton(x, y, STR_SETTINGS, BUTTON_SELECT);
#endif
		x=DrawButton(x, y, STR_OPEN, BUTTON_START);
		x=DrawButton(x, y, STR_OPTION, BUTTON_TRIANGLE);
		x=DrawButton(x, y, STR_CLICK, BUTTON_CROSS);
		if(0 <= window_activ) {
			x=DrawButton(x, y, STR_SELECT, BUTTON_SQUARE);
			x=DrawButton(x, y, STR_CURSOR, BUTTON_L);
			x=DrawButton(x, y, STR_REFRESH, BUTTON_L3);
			x=DrawButton(x, y, STR_WINDOW, BUTTON_R);
			x=DrawButton(x, y, STR_SCROLL, BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT);
		}
	} else
	if(option_activ == YES)	{
		x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
		x=DrawButton(x, y, STR_CLICK, BUTTON_CROSS);
		x=DrawButton(x, y, STR_CURSOR, BUTTON_L);
	} else
	if(prop_activ == YES || SFO_viewer_activ == YES) {
		x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
	} else
	if(txt_viewer_activ == YES){
		Draw_txt_viewer_input();
	} else
	if(picture_viewer_activ == YES) {
		x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
		x=DrawButton(x, y, STR_PREVIOUS, BUTTON_LEFT);
		x=DrawButton(x, y, STR_NEXT, BUTTON_RIGHT);
	}
}

void Draw_FileExplorer()
{
	start_loading();
	init_FileExplorer();
	Window(NULL);
	end_loading();
	
	u8 LoopBreak=1;
	while(LoopBreak)
	{		
		cls();
		
		Draw_BGS();
		
		if(MENU) {
			scene = SCENE_SETTINGS;
			Draw_MENU();
			Draw_MENU_input();
		} else {
			scene = SCENE_FILEMANAGER;
			Draw_window();
			Draw_option();
			Draw_properties();
			Draw_input();
			Draw_cursor();
		}
		
		Draw_picture_viewer();
		Draw_txt_viewer();
		Draw_SFO_viewer();
		Draw_Notification();

		tiny3d_Flip();
		ScreenShot();
		
		ps3pad_read();
		
		if(MENU) {
			input_MENU();
		} else {
			if(	option_input() == OFF)
			if( window_input() == BREAK) {
				LoopBreak =0;
				return;
			}
			cursor_input();
			properties_input();
		}
				
		picture_viewer_input();
		txt_viewer_input();
		SFO_viewer_input();
	}

}

//*******************************************************
// MENU
//*******************************************************
	
void free_MENU()
{
	int i, j;
	for(i=0; i<MENU_MAX_ITEMS; i++) FREE(ITEMS[i]);
	FREE(ITEMS);

	for(i=0; i<MENU_MAX_ITEMS; i++) {
		for(j=0; j<MENU_MAX_ITEMS_VALUE; j++) {
			FREE(ITEMS_VALUE[i][j]);
		}
		FREE(ITEMS_VALUE[i]);
	}
	FREE(ITEMS_VALUE);
	
	FREE(ITEMS_VALUE_NUMBER);
	FREE(ITEMS_VALUE_POSITION);
	FREE(ITEMS_VALUE_SHOW);
	FREE(ITEMS_TYPE);
	
	for(i=0; i<MENU_MAX_ITEMS; i++) FREE(TITLES[i]);
	FREE(TITLES);
}

void new_MENU()
{
	int i, j;
	
	if(ITEMS!=NULL) free_MENU();
	
	ITEMS = (char **) malloc(MENU_MAX_ITEMS*sizeof(char *));
	for(i=0; i<MENU_MAX_ITEMS; i++) ITEMS[i]=NULL;
	
	ITEMS_VALUE = (char ***) malloc(MENU_MAX_ITEMS*sizeof(char **));
	for(i=0; i<MENU_MAX_ITEMS; i++) {
		ITEMS_VALUE[i] = (char **) malloc(MENU_MAX_ITEMS_VALUE*sizeof(char *));
		for(j=0; j<MENU_MAX_ITEMS_VALUE; j++) ITEMS_VALUE[i][j]=NULL;
	}
	
	ITEMS_VALUE_NUMBER = (s8 *) malloc(MENU_MAX_ITEMS*sizeof(s8));
	ITEMS_VALUE_POSITION = (u8 *) malloc(MENU_MAX_ITEMS*sizeof(u8));
	ITEMS_VALUE_SHOW = (u8 *) malloc(MENU_MAX_ITEMS*sizeof(u8));
	ITEMS_TYPE = (u8 *) malloc(MENU_MAX_ITEMS*sizeof(u8));
	
	for(i=0; i<MENU_MAX_ITEMS; i++) {
		ITEMS_VALUE_NUMBER[i]=-1;
		ITEMS_VALUE_POSITION[i]=0;
		ITEMS_VALUE_SHOW[i]=NO;
		ITEMS_TYPE[i]=ITEM_TEXTBOX;
	}
	
	TITLES = (char **) malloc(MENU_MAX_ITEMS*sizeof(char *));
	for(i=0; i<MENU_MAX_ITEMS; i++) TITLES[i]=NULL;
	
	ITEMS_POSITION = 0;	
	MENU=YES;
	IN_ITEMS_VALUE=NO;
	
}

void init_MENU()
{
	int i, j;
	for(i=0; i<MENU_MAX_ITEMS; i++) {
		FREE(ITEMS[i]);
		for(j=0; j<MENU_MAX_ITEMS_VALUE; j++) {
			FREE(ITEMS_VALUE[i][j]);
		}
		ITEMS_VALUE_NUMBER[i]=-1;
		ITEMS_VALUE_SHOW[i]=NO;
		ITEMS_TYPE[i]=ITEM_TEXTBOX;
		FREE(TITLES[i]);
	}
	
	ITEMS_NUMBER = -1;
	
	MENU_COLUMN_ITEMS_NUMBER=-1;
	MENU_COLUMN_ITEMS_W = 200;
	MENU_TABLE_START=-1;
	MENU_TABLE_END=-1;
}

void add_item_MENU(char *str, u8 type)
{
	if(MENU_MAX_ITEMS <= ITEMS_NUMBER) {
		show_msg("MAX items !");
		return;
	}
	
	ITEMS_NUMBER++;
	FREE(ITEMS[ITEMS_NUMBER]);
	ITEMS[ITEMS_NUMBER] = strcpy_malloc(str);
	ITEMS_TYPE[ITEMS_NUMBER]=type;
	
	if(type==ITEM_CHECKBOX || type==ITEM_COMMAND) {
		ITEMS_VALUE_POSITION[ITEMS_NUMBER]=NO;
		ITEMS_VALUE_NUMBER[ITEMS_NUMBER] = 1;
	}
}

void add_item_value_MENU(char *str)
{
	if(MENU_MAX_ITEMS_VALUE <= ITEMS_VALUE_NUMBER[ITEMS_NUMBER]) {
		show_msg("MAX items value !");
		return;
	}
	ITEMS_VALUE_NUMBER[ITEMS_NUMBER]++;
	FREE(ITEMS_VALUE[ITEMS_NUMBER][ITEMS_VALUE_NUMBER[ITEMS_NUMBER]]);
	ITEMS_VALUE[ITEMS_NUMBER][ITEMS_VALUE_NUMBER[ITEMS_NUMBER]] = strcpy_malloc(str);
}

void add_title_MENU(char *str)
{
	FREE(TITLES[ITEMS_NUMBER+1]);
	TITLES[ITEMS_NUMBER+1] = strcpy_malloc(str);
}

u8 item_is(char *str)
{
	if(ITEMS[ITEMS_POSITION]==NULL) return NO;
	if(strcmp(ITEMS[ITEMS_POSITION], str) == 0) return YES;
	
	return NO;
}

u8 item_value_is(char *str)
{
	if(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]==NULL) return NO;
	if(strcmp(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], str) == 0 ) return YES;

	return NO;
}

void Draw_HELP()
{
	float x=50;
	float y=23;
	FontColor(COLOR_1);
	FontSize(13);

	if(item_is(STR_3D)) {
		DrawString(x, y, STR_3D_DESC);
	} else
	if(item_is(STR_INVERSE)) {
		DrawString(x, y, STR_INVERSE_DESC);
	} else
	if(item_is(STR_NB_LINE)) {
		DrawString(x, y, STR_NB_LINE_DESC);
	} else
	if(item_is(STR_NB_COL)) {
		DrawString(x, y, STR_NB_COL_DESC);
	} else
	if(item_is(STR_KEEP_PROP)) {
		DrawString(x, y, STR_KEEP_PROP_DESC);
	} else
	if(item_is(STR_ANIMATED)) {
		DrawString(x, y, STR_ANIMATED_DESC);
	} else
	if(item_is(STR_DIRECTION)) {
		DrawString(x, y, STR_DIRECTION_DESC);
	} else
	if(item_is(STR_GRID_TYPE)) {
		DrawString(x, y, STR_GRID_TYPE_DESC);
	} else
	if(item_is(STR_SHOW_ICON0)) {
		DrawString(x, y, STR_SHOW_ICON0_DESC);
	} else
	if(item_is(STR_SHOW_GAMECASE)) {
		DrawString(x, y, STR_SHOW_GAMECASE_DESC);
	} else
	if(item_is(STR_SHOW_COVER)) {
		DrawString(x, y, STR_SHOW_COVER_DESC);
	} else
	if(item_is(STR_SHOW_PIC1)) {
		DrawString(x, y, STR_SHOW_PIC1_DESC);
	} else
	if(item_is(STR_SIDE_MENU)) {
		DrawString(x, y, STR_SIDE_MENU_DESC);
	} else
	if(item_is(STR_UI)) {
		DrawString(x, y, STR_UI_DESC);
	} else
	if(item_is(STR_COLOR_1) || item_is(STR_COLOR_2) || item_is(STR_COLOR_3) || item_is(STR_COLOR_4)) {
		DrawString(x, y, STR_COLOR_DESC);
	} else
	if(item_is(STR_SHOW_WAVES)) {
		DrawString(x, y, STR_SHOW_WAVES_DESC);
	} else
	if(item_is(STR_WAVES_COLOR)) {
		DrawString(x, y, STR_WAVES_COLOR_DESC);
	} else
	if(item_is(STR_XMB_PRIO)) {
		DrawString(x, y, STR_XMB_PRIO_DESC);
	} else
	if(item_is(STR_HELP)) {
		DrawString(x, y, STR_HELP_DESC);
	} else
	if(item_is(STR_GAME_PATHS)) {
		DrawString(x, y, STR_GAME_PATHS_DESC);
	} else
	if(item_is(STR_UPD_MGZ)) {
		DrawString(x, y, STR_UPD_MGZ_DESC);
	} else
	if(item_is(STR_PLUGIN_MANAGER)) {
		DrawString(x, y, STR_PLUGIN_MANAGER_DESC);
	} else
	if(item_is(STR_DL_COVER)) {
		DrawString(x, y, STR_DL_COVER_DESC);
	} else
	if(item_is(STR_ADJUST)) {
		DrawString(x, y, STR_ADJUST_DESC);
	} else
	if(item_is(STR_DL_UPDATE)) {
		DrawString(x, y, STR_DL_UPDATE_DESC);
	} else
	if(item_is(STR_CHECK_IRD) || item_is(STR_CHECK_CRC32) || item_is(STR_CHECK_MD5)) {
		DrawString(x, y, STR_CHECK_DESC);
	} else
	if(item_is(STR_FIX_PERMS)) {
		DrawString(x, y, STR_FIX_PERMS_DESC);
	} else
	if(item_is(STR_CONVERT_ISO)) {
		DrawString(x, y, STR_CONVERT_ISO_DESC);
	} else
	if(item_is(STR_EXTRACT_ISO)) {
		DrawString(x, y, STR_EXTRACT_ISO_DESC);
	} else
	if(item_is(STR_RESTORE)) {
		DrawString(x, y, STR_RESTORE_DESC);
	} else
	if(item_is(STR_RESIGN)) {
		DrawString(x, y, STR_RESIGN_DESC);
	} else
	if(item_is(STR_PATCH_EBOOT)) {
		DrawString(x, y, STR_PATCH_EBOOT_DESC);
	} else
	if(item_is(STR_MAKE_SHTCUT_PKG)) {
		DrawString(x, y, STR_MAKE_SHTCUT_PKG_DESC);
	} else
	if(item_is(STR_PATCH_EXP)) {
		DrawString(x, y, STR_PATCH_EXP_DESC);
	} else
	if(item_is(STR_MOUNT_APPHOME)) {
		DrawString(x, y, STR_MOUNT_APPHOME_DESC);
	} else
	if(item_is(STR_PATCH_LIBFS)) {
		DrawString(x, y, STR_PATCH_LIBFS_DESC);
	} else
	if(item_is(STR_BDEMU)) {
		DrawString(x, y, STR_BDEMU_DESC);
	} else
	if(item_is(STR_PRIM_USB)) {
		DrawString(x, y, STR_PRIM_USB_DESC);
	} else
	if(item_is(STR_PAYLOAD)) {
		DrawString(x, y, STR_PAYLOAD_DESC);
	} else
	if(item_is(STR_EXT_GAME_DATA)) {
		DrawString(x, y, STR_EXT_GAME_DATA_DESC);
	} else
	if(item_is(STR_CHANGE_IDPS)) {
		DrawString(x, y, STR_CHANGE_IDPS_DESC);
	} else
	if(item_is(STR_CLEAN_SYSCALL)) {
		DrawString(x, y, STR_CLEAN_SYSCALL_DESC);
	} else
	if(item_is(STR_DIRECT_BOOT)) {
		DrawString(x, y, STR_DIRECT_BOOT_DESC);
	} else
	if(item_is(STR_CONFIG)) {
		DrawString(x, y, STR_CONFIG_DESC);
	} else
	if(item_is(STR_PROPS)) {
		DrawString(x, y, STR_PROPS_DESC);
	} else
	if(item_is(STR_ENABLE_NETEMU) || item_is(STR_DISABLE_NETEMU)) {
		DrawString(x, y, STR_NETEMU_DESC);
	} else
	if(item_is(STR_ENABLE_YFIX) || item_is(STR_DISABLE_YFIX)) {
		DrawString(x, y, STR_YFIX_DESC);
	} else
	if(item_is(STR_ENABLE_FMVSKIP) || item_is(STR_DISABLE_FMVSKIP)) {
		DrawString(x, y, STR_FMVSKIP_DESC);
	} else
	if(item_is(STR_ENABLE_480P) || item_is(STR_DISABLE_480P)) {
		DrawString(x, y, STR_480P_DESC);
	} else
	if(item_is(STR_ENABLE_WS) || item_is(STR_DISABLE_WS)) {
		DrawString(x, y, STR_WS_DESC);
	} else
	if(item_is(STR_APPLY_PNACH)) {
		DrawString(x, y, STR_APPLY_PNACH_DESC);
	} else
	if(item_is(STR_REST_PNACH)) {
		DrawString(x, y, STR_REST_PNACH_DESC);
	} else
	if(item_is(STR_CREATE_ICON0)) {
		DrawString(x, y, STR_CREATE_ICON0_DESC);
	} else
	if(item_is(STR_COPY)) {
		DrawString(x, y, STR_COPY_DESC);
	} else
	if(item_is(STR_JOIN)) {
		DrawString(x, y, STR_JOIN_DESC);
	} else
	if(item_is(STR_DELETE)) {
		DrawString(x, y, STR_DELETE_DESC);
	} else
	if(item_is(STR_RENAME)) {
		DrawString(x, y, STR_RENAME_DESC);
	} else
	if(item_is(STR_ADD_FAV) || item_is(STR_REM_FAV)) {
		DrawString(x, y, STR_FAV_DESC);
	} else
	if(item_is(STR_THM)) {
		DrawString(x, y, STR_THM_DESC);
	} else
	if(item_is(STR_LANG)) {
		DrawString(x, y, STR_LANG_DESC);
	} else
	if(item_is(STR_ADD_LIMG) || item_is(STR_REMOVE_LIMG)) {
		DrawString(x, y, STR_LIMG_DESC);
	} else
	if(item_is(STR_FONT)) {
		DrawString(x, y, STR_FONT_DESC);
	} else
	if(item_is(STR_COLORSET)) {
		DrawString(x, y, STR_COLORSET_DESC);
	} else
/*
	if(item_is("Tri-Ace Hack")) {
		DrawString(x, y, "Fixes Tri-Ace games boot crash. VU Add/Sub hack.");
	} else
*/
	if(item_is("0x0F")) {
		DrawString(x, y, "FPU/VU Improved calculations result. ADD/SUB");
	} else
	if(item_is("0x10")) {
		DrawString(x, y, "COP2? Improved calculations result. ADD?/SUB?/MUL?/DIV?");
	} else
	if(item_is("0x26")) {
		DrawString(x, y, "FPU/VU Improved calculations result. ADD?/SUB?/MUL?/DIV?");
	} else
	if(item_is("0x27")) {
		DrawString(x, y, "COP2 Improved calculations result. ADD?/SUB?/MUL?/DIV?");
	} else
	if(item_is("0x2B")) {
		DrawString(x, y, "Setting mecha HACK to show GODZCD as GODZCDDA. So, it fake cd to be cdda");
	} else
	if(item_is("0x2F")) {
		DrawString(x, y, "Set new SPU2 param");
	} else
	if(item_is("0x35")) {
		DrawString(x, y, "Enable Force Flip Field  - Fix for '[Hang] For soft-lock'");
	} else
	if(item_is("0x41")) {
		DrawString(x, y, "(?) Speedhack (?)");
	} else
	if(item_is("0x44")) {
		DrawString(x, y, "Disable smoothing");
	} else
	if(item_is("0x46")) {
		DrawString(x, y, "Enable L2H Improvement - Fix screen shakes - Dedicated to 2D games");
	} else
	if(item_is("0x47")) {
		DrawString(x, y, "Enable XOR CSR - Fix fullscreen line corruption");
	} else
	if(item_is("0x50")) {
		DrawString(x, y, "(?) Switch to default gamepad config (?)");
	}

	FontSize(15);
}

void Draw_MENU()
{
	if(MENU == NO) return;
	
	int x1, x2, y=40, y1, i, j;
	u32 color;
	
	y1=y;
	
	FontSize(15);
	SetFontZ(10);
	
	if(MENU_SIDE == NO) {
		MENU_ITEMS_X = 50;
		MENU_ITEMS_VALUE_X = 250;
		Draw_BGS();
	} else {
		TranslateTo(&MENU_ITEMS_X, 593.0);
		MENU_ITEMS_VALUE_X = (X_MAX-MENU_ITEMS_X)/2 + MENU_ITEMS_X;
		Draw_SIDEBAR(MENU_ITEMS_X-10);
		SetFontZ(9);
	}
	
	x1 = MENU_ITEMS_X;
	x2 = MENU_ITEMS_VALUE_X;

	if(ITEMS_POSITION < MENU_SCROLL_START) MENU_SCROLL = 0;
	if(MENU_SCROLL_START <= ITEMS_POSITION && ITEMS_POSITION <= MENU_SCROLL_START + MENU_SCROLL ) MENU_SCROLL = ITEMS_POSITION - MENU_SCROLL_START;
	
	if(Show_Help) Draw_HELP();
	
	for(i=0; i<=ITEMS_NUMBER; i++) {
		
		if(TITLES[i] != NULL) {
			
			y+=10;
			Draw_title(x1, y, TITLES[i]);
			
			if(strcmp( TITLES[i], STR_THM_SETTINGS)==0) {
				FontColor(COLOR_4);
				FontSize(18);
				DrawFormatString(x2, y, Themes[UI_position]);
				FontSize(15);
				FontColor(COLOR_1);
			}
			
			y+=new_line(1)+15;
			y1=y;
			
			if(MENU_SCROLL > 0) {
				for(j=ITEMS_NUMBER; j>=0; j--){
					if(TITLES[j] != NULL) {
						MENU_SCROLL_START=j;
						break;
					}
				}
				if(MENU_SCROLL_START==i) {
					DrawUp(x1-7, y1+5);
					i+=MENU_SCROLL;
				}
			}
		}
		
		if(i==MENU_TABLE_START) y1=y;
		
		if(ITEMS_TYPE[i] == ITEM_TEXTBOX) {
			if(ITEMS_POSITION == i) FontColor(COLOR_2); 
			else FontColor(COLOR_1);
			
			DrawFormatString(x1, y, ITEMS[i]);
			
			FontColor(COLOR_1);
			
			if( ITEMS_VALUE_NUMBER[i] != -1 ) {
				if(IN_ITEMS_VALUE == YES && ITEMS_POSITION == i) {
					FontColor(COLOR_2);
					if( ITEMS_VALUE_NUMBER[i] > 0 ) {
						float w=GetWidth(ITEMS_VALUE[i][ITEMS_VALUE_POSITION[i]]);
						float h=GetFontHeight();
						DrawDown(x2+w/2, y+h*0.85);
						DrawUp(x2+w/2,  y);	
					}
					DrawFormatString(x2, y, ITEMS_VALUE[i][ITEMS_VALUE_POSITION[i]]);					
					/*					
					// START OF .:THEME TAGS:.
					if(strcmp(ITEMS[i], STR_THM)==0) {
						if(!(strcmp(ITEMS_VALUE[i][ITEMS_VALUE_POSITION[i]], STR_NONE) == 0)) {
							char tags[10];
							if(strstr(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/dev_hdd0") != NULL) {
								strcpy(tags, "HDD ");
							} else 
							if(strstr(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/dev_usb") != NULL) {
								int t;
								sscanf(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/dev_usb%d%*s" , &t);
								sprintf(tags, "USB%d ", t);
							} else 
							if(strstr(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/ntfs") != NULL) {
								int t;
								sscanf(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/ntfs%d%*s" , &t);
								sprintf(tags, "NTFS%d ", t);
							}
							u8 ThemeType = GetThemeType(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
							if(ThemeType==MGZ) strcat(tags, "MGZ"); else
							if(ThemeType==P3T) strcat(tags, "P3T"); else
							if(ThemeType==THM) strcat(tags, "THM"); 
							FontColor(COLOR_3);
							DrawFormatString(x2-90, y, tags);
						}
					}
					// END OF .:THEME TAGS:.
					*/
				} else {
					FontColor(COLOR_1);
					if(ITEMS_VALUE_SHOW[i]==YES) DrawFormatString(x2, y, ITEMS_VALUE[i][ITEMS_VALUE_POSITION[i]]);
				}
				
			}
			
			y+=new_line(1);
		} else
		if(ITEMS_TYPE[i] == ITEM_CHECKBOX) {
			if(i>0) {
				if(ITEMS_TYPE[i-1] == ITEM_TEXTBOX) { y+=10; y1=y; }
			}
			
			if(ITEMS_POSITION==i) color = COLOR_2; else color = COLOR_1;
		
			Draw_checkbox(ITEMS_VALUE_POSITION[i], x1, y, ITEMS[i], color);
			y+=new_line(1);
			
		} else
		if(ITEMS_TYPE[i] == ITEM_COMMAND) {
			if(i>0) {
				if(ITEMS_TYPE[i-1] == ITEM_TEXTBOX) { y+=10; y1=y; }
			}
			
			if(ITEMS_POSITION==i) {
				if(ITEMS_VALUE_SHOW[i]==YES) color = COLOR_3;
				else color = COLOR_2; 
			} else {
				if(ITEMS_VALUE_SHOW[i]==YES) color = COLOR_4;
				else color = COLOR_1;
			}
			Draw_checkbox(ITEMS_VALUE_POSITION[i], x1, y, ITEMS[i], color);
			y+=new_line(1);
			
			if(ITEMS_POSITION==i) {	
				for(j=2; j<=ITEMS_VALUE_NUMBER[i]; j++) {
					if(ITEMS_VALUE[i][j] == NULL) break;
					
					if( strncmp( ITEMS_VALUE[i][j], "*", 1) == 0) FontColor(COLOR_4);
					else FontColor(COLOR_1);
					
					DrawFormatString(x1+20, y, ITEMS_VALUE[i][j]);
					y+=new_line(1);
					if(y>450) {
						DrawFormatString(x1+20, y-5, ". . .");
						break;
					}
				}
				FontColor(COLOR_1);
			}
			
		} else
		if(ITEMS_TYPE[i] == ITEM_COLORBOX) {			
			if(ITEMS_POSITION == i) FontColor(COLOR_2); 
			else FontColor(COLOR_1);
			
			DrawFormatString(x1, y, ITEMS[i]);

			memcpy(&color, ITEMS_VALUE[i][0], 4);
			
			color=color - GetALPHA(color) + 0xFF;
			Draw_Box(x2, y, 10, 0, 16, 10, color, NO);
			if(ITEMS_POSITION == i) {x_COLOR=x2; y_COLOR=y;}
			
			y+=new_line(1);
		}
			
		if(MENU_COLUMN_ITEMS_NUMBER != -1) {
			if(MENU_TABLE_START<i && i<=MENU_TABLE_END ) {
				if( (i-MENU_TABLE_START)%MENU_COLUMN_ITEMS_NUMBER == 0 ) {
					x1+=MENU_COLUMN_ITEMS_W;
					x2+=MENU_COLUMN_ITEMS_W;
					y=y1;
				}
				if(i==MENU_TABLE_END) {
					y=y1+new_line(1)*MENU_COLUMN_ITEMS_NUMBER;
					x1=MENU_ITEMS_X;
					x2=MENU_ITEMS_VALUE_X;
				}
			}
		}
		
		if(y>450) {
			if(ITEMS_POSITION > i) MENU_SCROLL += ITEMS_POSITION - i;
			if(i<ITEMS_NUMBER) DrawDown(x1-7, 450);
			break;
		}
	}
}

//*******************************************************
// PS2 MENU
//*******************************************************

float X_ICON0_creator=0;
float Y_ICON0_creator=0;
float W_ICON0_creator=0;
float H_ICON0_creator=0;
char ICON0_creator_PATH[255];
u8 ICON0_creator=NO;

void input_ICON0_creator()
{
	if(ICON0_creator == NO) return;

	if(old_pad & BUTTON_UP) {
		if(Y_ICON0_creator>0) Y_ICON0_creator--;
	}
	
	if(old_pad & BUTTON_DOWN) {
		if(Y_ICON0_creator + H_ICON0_creator < COVER[position].height) Y_ICON0_creator++;
	}
	
	if(old_pad & BUTTON_LEFT) {
		if(X_ICON0_creator>0) X_ICON0_creator--;
	}
	
	if(old_pad & BUTTON_RIGHT) {
		if(X_ICON0_creator + W_ICON0_creator < COVER[position].width) X_ICON0_creator++;
	}
	
	if(old_pad & BUTTON_L1) {
		if(W_ICON0_creator < COVER[position].width) {
			W_ICON0_creator++;
			H_ICON0_creator = 176 * W_ICON0_creator / 320;
			if(X_ICON0_creator + W_ICON0_creator > COVER[position].width) X_ICON0_creator=COVER[position].width-W_ICON0_creator;
			if(Y_ICON0_creator + H_ICON0_creator > COVER[position].height) Y_ICON0_creator=COVER[position].height-H_ICON0_creator;
		}
	}
	
	if(old_pad & BUTTON_L2) {
		if(W_ICON0_creator > COVER[position].width / 4) {
			W_ICON0_creator--;
			H_ICON0_creator = 176 * W_ICON0_creator / 320;
		}
	}
	
	if(old_pad & BUTTON_SQUARE) {
		start_loading();
		char out[255];
		strcpy(out, list_game_path[position]);
		out[strlen(out)-3]='j';
		out[strlen(out)-2]='p';
		out[strlen(out)-1]='g';
		Crop_Image(ICON0_creator_PATH, out, X_ICON0_creator, Y_ICON0_creator, W_ICON0_creator, H_ICON0_creator);
		ICON0_creator=NO;
		memset(ICON0_creator_PATH, 0, sizeof(ICON0_creator_PATH));
		end_loading();
		start_Load_GamePIC();
	}
	
	if(new_pad & BUTTON_CIRCLE)
	{
		ICON0_creator=NO;
		memset(ICON0_creator_PATH, 0, sizeof(ICON0_creator_PATH));
	}
}

void Draw_ICON0_creator()
{
	if(ICON0_creator == NO) return;	
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO); // DARK 50%
	
	float xi, yi, wi, hi;
	float xj, yj, wj, hj;
	
	if(COVER_offset[position] != 0 ) {
		tiny3d_SetTexture(0, COVER_offset[position], COVER[position].width, COVER[position].height, COVER[position].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if( COVER[position].width > 748) {
			wi = 748;
			hi = COVER[position].height * 748 / COVER[position].width;
		} else 
		if (COVER[position].width > 412) {
			hi = 412;
			wi = COVER[position].width * 412 / COVER[position].height;
		} else {
			wi = COVER[position].width;
			hi = COVER[position].height;
		}
		xi = (848 - wi) / 2;
		yi = (512 - hi) / 2;
	
		Draw_Box(xi, yi, 0, 0, wi, hi, WHITE, YES);
		
		wj = W_ICON0_creator * wi / COVER[position].width;
		hj = H_ICON0_creator * hi / COVER[position].height;
		
		xj = X_ICON0_creator * wi / COVER[position].width;
		yj = Y_ICON0_creator * hi / COVER[position].height ;
		
		Draw_LineBox(xi+xj, yi+yj, 0, 5, wj, hj, RED);
	}
}

void Draw_ICON0_creator_input()
{
	if(ICON0_creator == NO) return;	
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	x=DrawButton(x, y, STR_CREATE, BUTTON_SQUARE);
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
	x=DrawButton(x, y, STR_ZOOM_OUT, BUTTON_L1 );
	x=DrawButton(x, y, STR_ZOOM_IN, BUTTON_L2 );
	x=DrawButton(x, y, STR_MOVE_FRAME, BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT );
}

void open_ICON0_creator()
{
	char temp[128];
	char title_id[20];
	
	if(Get_ID(list_game_path[position], list_game_platform[position], title_id) == FAILED) return;
	
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/%s.JPG", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/%s.jpg", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/%s.PNG", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/%s/USRDIR/covers/%s.png", ManaGunZ_id, title_id);
	if(path_info(temp) == _FILE) goto read;
	
	sprintf(temp, "/dev_hdd0/tmp/covers/%s.JPG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/tmp/covers/%s.jpg", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/tmp/covers/%s.PNG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/tmp/covers/%s.png", title_id);
	if(path_info(temp) == _FILE) goto read;
	
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers/%s.JPG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers/%s.jpg", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers/%s.PNG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers/%s.png", title_id);
	if(path_info(temp) == _FILE) goto read;
	
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers_retro/psx/%s_COV.JPG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers_retro/psx/%s_COV.jpg", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers_retro/psx/%s_COV.PNG", title_id);
	if(path_info(temp) == _FILE) goto read;
	sprintf(temp, "/dev_hdd0/game/BLES80608/USRDIR/covers_retro/psx/%s_COV.png", title_id);
	if(path_info(temp) == _FILE) goto read;
	
	return;
read:
	
	memset(ICON0_creator_PATH, 0, sizeof(ICON0_creator_PATH));
	strcpy(ICON0_creator_PATH, temp);
	
	X_ICON0_creator=0;
	Y_ICON0_creator=0;
	W_ICON0_creator=COVER[position].width;
	H_ICON0_creator= 176 * W_ICON0_creator / 320;
	
	ICON0_creator = YES;
}

void open_PS2_GAME_MENU();

#define BCNETEMU_ON			1
#define BCNETEMU_OFF		0
#define BCNETEMU_STATUS		2
#define BCNETEMU_ISNOTBC	-1		

// param=1		enable patch
// param=0		disable patch
// param=2		return current status​
// return  1	enabled patch
// return  0	disabled patch
// return -1	its not a bc or semi bc ps3

#define NETCONFIG	1
#define GXCONFIG	2
#define SOFTCONFIG	4
#define CUSTCONFIG	8
#define CURRCONFIG	16
	
int ps2_netemu_cobra(int param)
{
	lv2syscall2(8, (uint64_t)0x1ee9, (uint64_t)(int)param);
	return_to_user_prog(int);
}

void config_command(u8 state, char *str)
{
	int i;
	for(i=0; i<=ITEMS_NUMBER; i++){
		if(strcmp(ITEMS[i], str) == 0){
			ITEMS_VALUE_POSITION[i] = state;
		}
	}
}

u8 *LoadMEMfromISO(char *iso_file, u32 sector, u32 offset, u32 size)
{
	FILE *f;	
	u32 SectSize=0;
	u32 JP=0;
	
	//print_load("Open %s", iso_file);
	f = fopen(iso_file, "rb");
	if(f==NULL) {
		print_load("Error : LoadMEMfromISO, failed to fopen");
		return NULL;
	}
	if( get_SectorSize(f, &SectSize, &JP) == FAILED) {
		fclose(f);
		print_load("Error : LoadMEMfromISO, failed to get_SectorSize");
		return NULL;
	}
	u8 *mem = (u8*) malloc(size+1);
	if(mem==NULL) {
		print_load("Error : LoadMEMfromISO, failed to malloc");
		fclose(f);
		return NULL;
	}	
	
	u64 iso_offset = (u64)SectSize*(u64)sector+(u64)offset+(u64)JP;
	
	u8 split666 = is_66600(iso_file);
	if(is_splitted_iso(iso_file)==YES || split666) {
			
		char iso_path[128];
		char temp[128];
		u64 fsize=0;
		int i;
		int l = strlen(iso_file);
		
		strcpy(iso_path, iso_file);
		iso_path[l-1]=0;
		if(split666) iso_path[l-2]=0;
		strcpy(temp, iso_path);
		
		for(i=0; i<32; i++) {
			if(split666) sprintf(iso_path, "%s%02d", temp, i);
			else sprintf(iso_path, "%s%d", temp, i);
			
			fsize = get_size(iso_path, NO);
			
			if(iso_offset<fsize) {
				if(i!=0) {
					fclose(f);
					f = fopen(iso_path, "rb");	
					if(f==NULL) return NULL;
				}
				break;
			}
			iso_offset -= fsize;
		}
	}
	
	fseek(f, iso_offset, SEEK_SET);
	
	//print_load("ISO offset : %016llX", iso_offset);
	if( fread(mem, size, 1, f) != size) {
		print_load("Error : LoadMEMfromISO, failed to fread");
		free(mem);
		fclose(f);
		return NULL;
	}
	fclose(f);
	
	return mem;
}

u8 PS2ELF_compare(u32 EE_offset, u8 *data, u32 data_size)
{
	u32 EntryPoint=0;
	u32 ProgOffset=0;
	u16 ProgHeaderNumber=0;
	u32 ProgType=0;
	u32 filesz=0;
	
	memcpy(&EntryPoint, &PS2ELF_mem[0x18], 4);
	EntryPoint = reverse32(EntryPoint);
	
	memcpy(&ProgHeaderNumber, &PS2ELF_mem[0x2C], 2);
	ProgHeaderNumber = reverse16(ProgHeaderNumber);
	
	int i;
	for(i=0; i < ProgHeaderNumber; i++) {
		memcpy(&ProgType, &PS2ELF_mem[0x34+i*0x20], 4);
		ProgType = reverse32(ProgType);
	
		memcpy(&filesz, &PS2ELF_mem[0x34+0x10+i*0x20], 4);
		filesz = reverse32(filesz);

		if(ProgType==1 && filesz!=0) {
			memcpy(&ProgOffset, &PS2ELF_mem[0x38+i*0x20], 4);
			ProgOffset = reverse32(ProgOffset);
			break;
		}
	}
	
	if(ProgType!=1 || filesz==0) {
		print_load("Error : ProgOffset not found");
		return NO;
	}
	
	u32 elf_offset;
	elf_offset = EE_offset - (EntryPoint - 8 - ProgOffset);
	
	print_load("elf_offset %X", elf_offset);
	print_load("data %02X%02X%02X%02X", data[0], data[1], data[2], data[3]);
	print_load("data %02X%02X%02X%02X", PS2ELF_mem[elf_offset], PS2ELF_mem[elf_offset+1], PS2ELF_mem[elf_offset+2], PS2ELF_mem[elf_offset+3]);
	
	if(!memcmp((char *) &PS2ELF_mem[elf_offset], (char *) data, data_size))
		return YES;
	
	return NO;
}

u8 Create_PS2_CONFIG()
{
	char CONFIG_path[255];
	int i,j;
	unsigned int val32=0;
	unsigned int val32_2=0;
	unsigned int cmdID;
	char CFG_path[255];
	u64 cur_MD5[2];
	u64 cfg_md5[2];
	
	sprintf(CONFIG_path, "%s.CONFIG", list_game_path[position]);
	Delete(CONFIG_path);
	
	FILE* f;
	f = fopen(CONFIG_path, "wb");
	if(f==NULL) return FAILED;
	
	for(i=0; i<=ITEMS_NUMBER; i++) {
		if( ITEMS_TYPE[i] != ITEM_COMMAND) continue;
		if( ITEMS_VALUE_POSITION[i] == NO) continue;
		
		if(strcmp(ITEMS[i], "0x3D") == 0) {
			sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X", &val32);
			val32=reverse32(val32);
			break;
		}
	}
	
	u32 x3D = 0x3D000000;
	fwrite(&x3D, sizeof(u32), 1, f);
	if(val32==0) val32=0x57440000;
	fwrite(&val32, sizeof(u32), 1, f);
	
	for(i=0; i<=ITEMS_NUMBER; i++) {
				
		if( ITEMS_TYPE[i] != ITEM_COMMAND) continue;
		if( ITEMS_VALUE_POSITION[i] == NO) continue;
		if(strcmp(ITEMS[i], "0x00") == 0) continue;
		if(strcmp(ITEMS[i], "0x3D") == 0) continue;
			
		sscanf(&ITEMS[i][2], "%X", &cmdID);
		cmdID = reverse32(cmdID);
		fwrite(&cmdID, sizeof(u32), 1, f);
		cmdID=reverse32(cmdID);
		
		switch(cmdID) {
			case 0x01 :
			case 0x02 :
			case 0x0F :
			case 0x10 :
			case 0x26 :
			case 0x27 :
			case 0x29 :
			case 0x48 :
			case 0x4B :
			case 0x4C :
			{
				sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X", &val32);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				
				sscanf(&strrchr(ITEMS_VALUE[i][3], ':')[2], "%X", &val32);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				
				break;
			}
			case 0x04 :
			case 0x07 :
			case 0x0D :
			case 0x0E :
			case 0x11 :
			case 0x15 :
			case 0x1F :
			case 0x21 :
			case 0x28 :
			case 0x2C :
			case 0x2E :
			case 0x2F :
			case 0x3D :
			case 0x3F :
			case 0x42 :
			case 0x43 :
			case 0x4D :
			case 0x17 : //u8
			case 0x1C : //u8
			case 0x1D : //u8
			case 0x1E : //u8
			{
				sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X", &val32);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				
				break;
			}
			case 0x08 :
			{
				sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X %X", &val32, &val32_2);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				fwrite(&val32_2, sizeof(u32), 1, f);
				
				sscanf(&strrchr(ITEMS_VALUE[i][3], ':')[2], "%X %X", &val32, &val32_2);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				fwrite(&val32_2, sizeof(u32), 1, f);
				
				sscanf(&strrchr(ITEMS_VALUE[i][4], ':')[2], "%X %X", &val32, &val32_2);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				fwrite(&val32_2, sizeof(u32), 1, f);
				
				sscanf(&strrchr(ITEMS_VALUE[i][5], ':')[2], "%X %X", &val32, &val32_2);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				fwrite(&val32_2, sizeof(u32), 1, f);
				
				break;
			}
			case 0x09 :
			{
				u32 nb;
				sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X", &nb);
				nb=reverse32(nb);
				fwrite(&nb, sizeof(u32), 1, f);
				nb=reverse32(nb);
				
				for(j=0; j<nb; j++)
				{
					sscanf(&strrchr(ITEMS_VALUE[i][3+j*3], ':')[2], "%X", &val32);
					val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
					
					sscanf(&strrchr(ITEMS_VALUE[i][4+j*3], ':')[2], "%X %X", &val32_2, &val32);
					//val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
					//val32_2=reverse32(val32_2);
					fwrite(&val32_2, sizeof(u32), 1, f);
					
					sscanf(&strrchr(ITEMS_VALUE[i][5+j*3], ':')[2], "%X %X", &val32_2, &val32);
					//val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
					//val32_2=reverse32(val32_2);
					fwrite(&val32_2, sizeof(u32), 1, f);
				}
				break;
			}
			case 0x0A :
			{
				u32 nb;						
				sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X", &nb);
				nb=reverse32(nb);
				fwrite(&nb, sizeof(u32), 1, f);
				nb=reverse32(nb);
				for(j=0; j<nb; j++)
				{
					sscanf(&strrchr(ITEMS_VALUE[i][3+j*3], ':')[2], "%X", &val32);
					val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
					
					sscanf(&strrchr(ITEMS_VALUE[i][4+j*3], ':')[2], "%X", &val32);
					//val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
				
					sscanf(&strrchr(ITEMS_VALUE[i][5+j*3], ':')[2], "%X", &val32);
					//val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
				}
				break;
			}
			case 0x0B :
			{			
				u32 nb;						
				sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X", &nb);
				nb=reverse32(nb);
				fwrite(&nb, sizeof(u32), 1, f);
				nb=reverse32(nb);
				
				int t=3;
				for(j=0; j<nb; j++)
				{
					sscanf(&strrchr(ITEMS_VALUE[i][t], ':')[2], "%X", &val32);
					val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
					t++;
					
					sscanf(&strrchr(ITEMS_VALUE[i][t], ':')[2], "%X", &val32);
					val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
					t++;				
					
					u32 size;
					sscanf(&strrchr(ITEMS_VALUE[i][t], ':')[2], "%X", &size);
					size=reverse32(size);
					fwrite(&size, sizeof(u32), 1, f);
					t++;
					
					size=reverse32(size);
					int k;
					for(k=0; k<size/4; k++) {
						if(k%8==0 && k!=0) t++;
						sscanf(&strrchr(ITEMS_VALUE[i][t], ':')[2+9*(k%10)], "%X", &val32);
						val32=reverse32(val32);
						fwrite(&val32, sizeof(u32), 1, f);
					}
					t++;
					for(k=0; k<size/4; k++) {
						if(k%8==0 && k!=0) t++;
						sscanf(&strrchr(ITEMS_VALUE[i][t], ':')[2+9*(k%10)], "%X", &val32);
						val32=reverse32(val32);
						fwrite(&val32, sizeof(u32), 1, f);
					}
					t++;
				}
				break;
			}
			case 0xC :
			{
				sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X", &val32);
				sscanf(&strrchr(ITEMS_VALUE[i][3], ':')[2], "%X", &val32_2);
				u32 val = val32*0x10000 + val32_2;
				val=reverse32(val);
				fwrite(&val, sizeof(u32), 1, f);				
				
				break;
			}
			case 0x12 :
			{
				u32 nb;						
				sscanf(&strrchr(ITEMS_VALUE[i][2], ':')[2], "%X", &nb);
				nb=reverse32(nb);
				fwrite(&nb, sizeof(u32), 1, f);
				nb=reverse32(nb);
								
				for(j=0; j<nb; j++)
				{
					sscanf(&strrchr(ITEMS_VALUE[i][3+j], ':')[2], "%X", &val32);
					val32=reverse32(val32);
					fwrite(&val32, sizeof(u32), 1, f);
				}
				
				break;
			}
			case 0x13 :
			case 0x20 :
			case 0x24 :
			{			
				char str_val[9];
				
				strncpy(str_val, &strrchr(ITEMS_VALUE[i][2], ':')[2], 8);
				sscanf(str_val, "%X", &val32);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				
				strncpy(str_val, &strrchr(ITEMS_VALUE[i][2], ':')[2+8], 8);
				sscanf(str_val, "%X", &val32);
				val32=reverse32(val32);
				fwrite(&val32, sizeof(u32), 1, f);
				
				break;
			}
			default :
				break;
		}		
	}
	
	val32 = 0;
	fwrite(&val32, sizeof(u32), 1, f);
	
	char ID[12];
	for(i=0; i<=ITEMS_NUMBER; i++) {
		if(strcmp(ITEMS[i], "0x00") == 0) {
			if(ITEMS_VALUE[i][2] == NULL) break;
			strcpy(ID, &strrchr(ITEMS_VALUE[i][2], ':')[2]);
			fputs(ID, f);
			fclose(f);
			goto CopyCustom;
		}
	}
	
	strcpy(ID, PS2_ID);
	ID[4]='-';
	ID[8]=ID[9];
	ID[9]=ID[10];
	ID[10]=0;
	fputs(ID, f);
	
	fclose(f);
	
CopyCustom:
	
	md5_file(CONFIG_path, (u8 *) cur_MD5);
	
	sprintf(CFG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/NET/%s.CONFIG", ManaGunZ_id, PS2_ID);
	if(path_info(CFG_path) == _FILE) { 
		md5_file(CFG_path, (u8 *) cfg_md5);
		if(cur_MD5[0]==cfg_md5[0] && cur_MD5[1]==cfg_md5[1]) return SUCCESS;
	}
	
	sprintf(CFG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/GX/%s.CONFIG", ManaGunZ_id, PS2_ID);
	if(path_info(CFG_path) == _FILE) { 
		md5_file(CFG_path, (u8 *) cfg_md5);
		if(cur_MD5[0]==cfg_md5[0] && cur_MD5[1]==cfg_md5[1]) return SUCCESS;
	}
	
	sprintf(CFG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/SOFT/%s.CONFIG", ManaGunZ_id, PS2_ID);
	if(path_info(CFG_path) == _FILE) { 
		md5_file(CFG_path, (u8 *) cfg_md5);
		if(cur_MD5[0]==cfg_md5[0] && cur_MD5[1]==cfg_md5[1]) return SUCCESS;
	}
	
	sprintf(CFG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/CUSTOM/%s.CONFIG", ManaGunZ_id, PS2_ID);
	CopyFile(CONFIG_path, CFG_path);
	
	return SUCCESS;
}

u8 MGZCONFIG()
{
	u8 ret=0;
	char CONFIG_path[128];
	
	sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/NET/%s.CONFIG", ManaGunZ_id, PS2_ID);
	if(path_info(CONFIG_path) == _FILE) ret += NETCONFIG;
	
	sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/GX/%s.CONFIG", ManaGunZ_id, PS2_ID);
	if(path_info(CONFIG_path) == _FILE) ret += GXCONFIG;
	
	sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/SOFT/%s.CONFIG", ManaGunZ_id, PS2_ID);
	if(path_info(CONFIG_path) == _FILE) ret += SOFTCONFIG;
	
	sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/CUSTOM/%s.CONFIG", ManaGunZ_id, PS2_ID);
	if(path_info(CONFIG_path) == _FILE) ret += CUSTCONFIG;
	
	sprintf(CONFIG_path, "%s.CONFIG", list_game_path[position]);
	if(path_info(CONFIG_path) == _FILE) ret += CURRCONFIG;
	
	return ret;
}

void CONFIG_check(char *IsoPath)
{
	char CurrentCONFIG[128];
	
	sprintf(CurrentCONFIG, "%s.CONFIG", IsoPath);
	
	if(path_info(CurrentCONFIG) == _FILE) return;
		
	if( Get_ID(IsoPath, _ISO_PS2, PS2_ID) == FAILED) return;
	
	u8 MGZCFGS = MGZCONFIG();
	
	if(MGZCFGS != NONE) {
	
		end_loading();
			
		u8 config_position=0;
		s8 config_number=-1;
		char CONFIG_STR[4][10];
		
		if(MGZCFGS & NETCONFIG) {
			config_number++;
			strcpy(CONFIG_STR[config_number], "NET");
		}
		if(MGZCFGS & GXCONFIG) {
			config_number++;
			strcpy(CONFIG_STR[config_number], "GX");
		}
		if(MGZCFGS & SOFTCONFIG) {
			config_number++;
			strcpy(CONFIG_STR[config_number], "SOFT");
		}
		if(MGZCFGS & CUSTCONFIG)  {
			config_number++;
			strcpy(CONFIG_STR[config_number], "CUSTOM");
		}
		
		u8 LoopBreak=1;
		while(LoopBreak)
		{
			cls();
			Draw_BGS();
			
			FontColor(COLOR_1);
			FontSize(20);
			
			float x=250, y=200; 
			DrawFormatString(x, y, "%s", STR_USE_CONFIG);
			y+=20;
			x = DrawFormatString(x, y, "%s : ", STR_LOAD);
			FontColor(COLOR_2);
			DrawString(x, y, CONFIG_STR[config_position]);
			
			FontColor(COLOR_1);
			
			x=INPUT_X;
			y=INPUT_Y;
			FontColor(COLOR_1);
			SetFontZ(0);
			
			x = DrawButton(x, y, STR_ENTER, BUTTON_CROSS);
			x = DrawButton(x, y, STR_CANCEL, BUTTON_CIRCLE);
			
			if(config_number>0) DrawButton(x, y, STR_CHANGE, BUTTON_SQUARE);
			
			tiny3d_Flip();
			ScreenShot();
			
			ps3pad_read();
			
			if(config_number>0 && new_pad & BUTTON_SQUARE) {
				if(config_position==config_number) config_position=0;
				else config_position++;
			}
			if(new_pad & BUTTON_CROSS) {
				char CONFIG_path[128];
				sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/%s/%s.CONFIG", ManaGunZ_id, CONFIG_STR[config_number], PS2_ID);
				CopyFile(CONFIG_path, CurrentCONFIG);
				LoopBreak = 0;
				break;
			}
			if(new_pad & BUTTON_CIRCLE) {
				LoopBreak=0;
				break;
			}
		}
		start_loading();
	}

}

u32 GetEntryProg()
{
	u32 EntryPoint=0;
	u32 ProgOffset=0;
	u16 ProgHeaderNumber=0;
	u32 ProgType=0;
	u32 filesz=0;
	
	memcpy(&EntryPoint, &PS2ELF_mem[0x18], 4);
	EntryPoint = reverse32(EntryPoint);
		
	memcpy(&ProgHeaderNumber, &PS2ELF_mem[0x2C], 2);
	ProgHeaderNumber = reverse16(ProgHeaderNumber);
	
	int i;
	for(i=0; i < ProgHeaderNumber; i++) {
		memcpy(&ProgType, &PS2ELF_mem[0x34+i*0x20], 4);
		ProgType = reverse32(ProgType);
	
		memcpy(&filesz, &PS2ELF_mem[0x34+0x10+i*0x20], 4);
		filesz = reverse32(filesz);

		if(ProgType==1 && filesz!=0) {
			memcpy(&ProgOffset, &PS2ELF_mem[0x38+i*0x20], 4);
			ProgOffset = reverse32(ProgOffset);
			break;
		}
	}
	
	if(ProgType!=1 || filesz==0) {
		print_load("Error : ProgOffset not found");
		return 0;
	}
	
	return (EntryPoint - 8 - ProgOffset);

}

u8 CONFIG_exist_PS2PATCH(u32 ELF_offset, u32 EE_offset)
{
	int i;
	u32 ELFoffset;
	u32 EEoffset;
	
	EEoffset=EE_offset;
	ELFoffset=ELF_offset;
	
	u32 EntryProg = GetEntryProg();
	if(EntryProg==0) return NO;
	
	if(EEoffset==0) EEoffset = ELFoffset + EntryProg;
	if(ELFoffset==0) ELFoffset = EEoffset - EntryProg;
	
	if(ELFoffset > PS2ELF_mem_size) return NO;
	
	int ITEM_A=-1;
	for(i=0; i<=ITEMS_NUMBER; i++) {
		if( ITEMS_TYPE[i] != ITEM_COMMAND) continue;
		if(strcmp(ITEMS[i], "0x0A") == 0) {ITEM_A=i; break;}
	}
	
	if(ITEM_A==-1) return NO;
	
	u32 nb;
	u32 val32;
	sscanf(&strrchr(ITEMS_VALUE[ITEM_A][2], ':')[2], "%X", &nb);
	
	for(i=0; i<nb; i++)
	{
		sscanf(&strrchr(ITEMS_VALUE[ITEM_A][3+i*3], ':')[2], "%X", &val32);
		if(val32==EEoffset) return YES;
	}
	
	return NO;
}

u8 CONFIG_exist_TRIACEHACK()
{
	u32 val32;
	int i;
	for(i=0; i<=ITEMS_NUMBER; i++) {
		if( ITEMS_TYPE[i] != ITEM_COMMAND) continue;
		if(strcmp(ITEMS[i], "0x01") == 0) {
			sscanf(&strrchr(ITEMS_VALUE[i][3], ':')[2], "%X", &val32);
			if(val32==0x0A) return YES;
		}
	}
	return NO;
}

u8 CONFIG_add_TRIACEHACK()
{
	add_item_MENU("0x01", ITEM_COMMAND);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
	
	add_item_value_MENU("Offset : 00000000");
	add_item_value_MENU("Hack ID : 0000000A");
	
	return SUCCESS;
}

u8 CONFIG_remove_TRIACEHACK()
{
	u32 val32;
	int i;
	int ITEM_TRIACE=-1;
	for(i=0; i<=ITEMS_NUMBER; i++) {
		if( ITEMS_TYPE[i] != ITEM_COMMAND) continue;
		if(strcmp(ITEMS[i], "0x01") == 0) {
			sscanf(&strrchr(ITEMS_VALUE[i][3], ':')[2], "%X", &val32);
			if(val32==0x0A) {ITEM_TRIACE=i; break;}
		}
	}
	if(ITEM_TRIACE==-1) return FAILED;
	
	int j;
	for(i=ITEM_TRIACE; i<=ITEMS_NUMBER; i++) {
		FREE(ITEMS[i]);
		ITEMS[i] = strcpy_malloc(ITEMS[i+1]);
		for(j=0; j<MENU_MAX_ITEMS_VALUE; j++) {
			FREE(ITEMS_VALUE[i][j]);
			ITEMS_VALUE[i][j] = strcpy_malloc(ITEMS_VALUE[i+1][j]);
		}
		ITEMS_VALUE_NUMBER[i] = ITEMS_VALUE_NUMBER[i+1];
		ITEMS_VALUE_POSITION[i] = ITEMS_VALUE_POSITION[i+1];
		ITEMS_VALUE_SHOW[i] = ITEMS_VALUE_SHOW[i+1];
		ITEMS_TYPE[i] = ITEMS_TYPE[i+1];
	}
	ITEMS_NUMBER--;
	
	return SUCCESS;
}

void CONFIG_remove_PS2PATCH(u32 ELF_offset, u32 EE_offset, u32 patch_size)
{
	int i,j;
	u32 ELFoffset;
	u32 EEoffset;
	
	EEoffset=EE_offset;
	ELFoffset=ELF_offset;
	
	u32 EntryProg = GetEntryProg();
	if(EntryProg==0) return;
	
	if(EEoffset==0) EEoffset = ELFoffset + EntryProg;
	if(ELFoffset==0) ELFoffset = EEoffset - EntryProg;
	
	// don't know how to get the original data if it's not in the elf
	if(ELFoffset+patch_size > PS2ELF_mem_size) return; 
	
	int ITEM_A=-1;
	for(i=0; i<=ITEMS_NUMBER; i++) {
		if( ITEMS_TYPE[i] != ITEM_COMMAND) continue;
		if(strcmp(ITEMS[i], "0x0A") == 0) {ITEM_A=i; break;}
	}
	
	if(ITEM_A==-1) return;
	
	u32 nb;
	u32 val32;
	int k=0;
	sscanf(&strrchr(ITEMS_VALUE[ITEM_A][2], ':')[2], "%X", &nb);
	for(i=0; i<nb; i++)
	{
		sscanf(&strrchr(ITEMS_VALUE[ITEM_A][3+i*3], ':')[2], "%X", &val32);
		if(val32==EEoffset+k*4) {
			for(j=i; j<nb; j++) {
				FREE(ITEMS_VALUE[ITEM_A][3+j*3]);
				FREE(ITEMS_VALUE[ITEM_A][4+j*3]);
				FREE(ITEMS_VALUE[ITEM_A][5+j*3]);
				
				if(5+(j+1)*3 < MENU_MAX_ITEMS_VALUE) {
					ITEMS_VALUE[ITEM_A][3+j*3] = strcpy_malloc(ITEMS_VALUE[ITEM_A][3+(j+1)*3]);
					ITEMS_VALUE[ITEM_A][4+j*3] = strcpy_malloc(ITEMS_VALUE[ITEM_A][4+(j+1)*3]);
					ITEMS_VALUE[ITEM_A][5+j*3] = strcpy_malloc(ITEMS_VALUE[ITEM_A][5+(j+1)*3]);
				}
			}
			nb--;
			i--;
			k++;
			if(k==patch_size/4) break;
			continue;
		}
	}
	
	FREE(ITEMS_VALUE[ITEM_A][2]);
	ITEMS_VALUE[ITEM_A][2] = sprintf_malloc("Number : %08X", nb);
	if(nb==0) {
		int j;
		for(i=ITEM_A; i<=ITEMS_NUMBER; i++) {
			FREE(ITEMS[i]);
			ITEMS[i] = strcpy_malloc(ITEMS[i+1]);
			for(j=0; j<MENU_MAX_ITEMS_VALUE; j++) {
				FREE(ITEMS_VALUE[i][j]);
				ITEMS_VALUE[i][j] = strcpy_malloc(ITEMS_VALUE[i+1][j]);
			}
			ITEMS_VALUE_NUMBER[i] = ITEMS_VALUE_NUMBER[i+1];
			ITEMS_VALUE_POSITION[i] = ITEMS_VALUE_POSITION[i+1];
			ITEMS_VALUE_SHOW[i] = ITEMS_VALUE_SHOW[i+1];
			ITEMS_TYPE[i] = ITEMS_TYPE[i+1];
		}
		ITEMS_NUMBER--;
	}
}

void add_item_value(int item, char *str)
{
	if(MENU_MAX_ITEMS_VALUE <= ITEMS_VALUE_NUMBER[item]-1) {
		show_msg("Max ITEMS value !");
		return;
	}
	
	ITEMS_VALUE_NUMBER[item]++;
	FREE(ITEMS_VALUE[item][ITEMS_VALUE_NUMBER[item]]);
	ITEMS_VALUE[item][ITEMS_VALUE_NUMBER[item]] = strcpy_malloc(str);
}

void CONFIG_add_PS2PATCH(u32 ELF_offset, u32 EE_offset, u8 *patch, u32 patch_size)
{
	int i,j;
	u32 ELFoffset;
	u32 EEoffset;
	
	EEoffset=EE_offset;
	ELFoffset=ELF_offset;

	u32 EntryProg = GetEntryProg();
	if(EntryProg==0) return;
	
	if(EEoffset==0) EEoffset = ELFoffset + EntryProg;
	if(ELFoffset==0) ELFoffset = EEoffset - EntryProg;
	
	// don't know how to get the original data if it's not in the elf
	if(ELFoffset+patch_size > PS2ELF_mem_size) return;
	
	char str[128];
	int ITEM_A=-1;
	for(i=0; i<=ITEMS_NUMBER; i++) {
		if( ITEMS_TYPE[i] != ITEM_COMMAND) continue;

		if(strcmp(ITEMS[i], "0x0A") == 0) {ITEM_A=i; break;}
	}
	
	if(ITEM_A==-1) {
		add_item_MENU("0x0A", ITEM_COMMAND);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
		
		ITEM_A=ITEMS_NUMBER;
		
		sprintf(str, "Number : %08X", 0);
		add_item_value_MENU(str);
	}

	u32 nb;
	u32 val32;
	u32 new_patch_number=0;
	sscanf(&strrchr(ITEMS_VALUE[ITEM_A][2], ':')[2], "%X", &nb);
	
	for(i=0; i<patch_size/4; i++)
	{
		u8 patch_exist=NO;
		for(j=0; j<nb; j++) {
			sscanf(&strrchr(ITEMS_VALUE[ITEM_A][3+j*3], ':')[2], "%X", &val32);
			if(val32==EEoffset+i*4) {patch_exist=YES; break;}
		}
		if(patch_exist) continue;
		
		if(MENU_MAX_ITEMS_VALUE <= ITEMS_VALUE_NUMBER[ITEM_A] + 3) {
			show_msg("Too much Patches !");
			break;
		}
		
		new_patch_number++;
		sprintf(str, "Offset : %08X", EEoffset+i*4);
		print_load(str);
		add_item_value(ITEM_A, str);
		
		memcpy(&val32, &PS2ELF_mem[ELFoffset+i*4], 4);
		sprintf(str, "Original data : %08X", val32);
		print_load(str);
		add_item_value(ITEM_A, str);
		
		memcpy(&val32, &patch[i*4], 4);
		sprintf(str, "Patched data : %08X", val32);
		print_load(str);
		add_item_value(ITEM_A, str);
	}
	
	FREE(ITEMS_VALUE[ITEM_A][2]);
	ITEMS_VALUE[ITEM_A][2] = sprintf_malloc("Number : %08X", nb+new_patch_number);
}

u8 CONFIG_exist_PNACH(char *PnachPath)
{
	FILE* fp;
	char line[128];
	u8 ret=NO;
	
	u32 EEoffset;
	u32 Patched_Data;
	
	fp = fopen(PnachPath, "rb");
	if(fp==NULL) {
		print_load("Error : failed to open pnach file");
		return NO;
	}
	
	while(fgets(line, 128, fp) != NULL) {
		if( strstr(line, "patch") == NULL && strstr(line, "comment")==NULL && strstr(line, "gametitle")==NULL ) continue;
		
		if(strncmp(line, "patch=1", 7) == 0) 
		{			
			if(strstr(line, ",") == NULL) continue;
			
			char *token;
			unsigned long int value=0;
			token = strtok (line, ", "); //toggle patch
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //cpu
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //addr
			if(token == NULL) continue;
			sscanf(token, "%8lX", &value);
			EEoffset = value;
			value = 0;
			token = strtok (NULL, ", "); //type
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //data
			sscanf(token, "%8lX", &value);
			Patched_Data = value;

			EEoffset = EEoffset - (EEoffset >> 28)*0x10000000;
			
			ret += CONFIG_exist_PS2PATCH(0, EEoffset);
		}
	}

	fclose(fp);
	if(ret) ret=YES;
	return ret;
}

void CONFIG_remove_PNACH(char *PnachPath)
{
	FILE* fp;
	char line[128];
	
	u32 EEoffset;
	u32 Patched_Data;
	
	fp = fopen(PnachPath, "rb");
	if(fp==NULL) {
		print_load("Error : failed to open pnach file");
		return;
	}
	
	while(fgets(line, 128, fp) != NULL) {
		if( strstr(line, "patch") == NULL && strstr(line, "comment")==NULL && strstr(line, "gametitle")==NULL ) continue;
		
		if(strncmp(line, "patch=1", 7) == 0) 
		{			
			if(strstr(line, ",") == NULL) continue;
			
			char *token;
			unsigned long int value=0;
			token = strtok (line, ", "); //toggle patch
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //cpu
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //addr
			if(token == NULL) continue;
			sscanf(token, "%8lX", &value);
			EEoffset = value;
			value = 0;
			token = strtok (NULL, ", "); //type
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //data
			sscanf(token, "%8lX", &value);
			Patched_Data = value;

			EEoffset = EEoffset - (EEoffset >> 28)*0x10000000;
			
			CONFIG_remove_PS2PATCH(0, EEoffset, 4);
			
		} else
		if(strncmp(line, "gametitle=", 10) || strncmp(line, "comment=", 8)==0) {
			print_load(&strrchr(line, '=')[1]);
		}
	}

	fclose(fp);
}

void CONFIG_add_PNACH(char *PnachPath)
{
	FILE* fp;
	char line[128];
	
	u32 EEoffset;
	u32 Patched_Data;
	fp = fopen(PnachPath, "rb");
	if(fp==NULL) {
		print_load("Error : failed to open pnach file");
		return;
	}
	
	while(fgets(line, 128, fp) != NULL) {
		if( strstr(line, "patch") == NULL && strstr(line, "comment")==NULL && strstr(line, "gametitle")==NULL ) continue;
		
		if(strncmp(line, "patch=1", 7) == 0) 
		{			
			if(strstr(line, ",") == NULL) continue;
			
			char *token;
			unsigned long int value=0;
			token = strtok (line, ", "); //toggle patch
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //cpu
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //addr
			if(token == NULL) continue;
			sscanf(token, "%8lX", &value);
			EEoffset = value;
			value = 0;
			token = strtok (NULL, ", "); //type
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //data
			sscanf(token, "%8lX", &value);
			Patched_Data = value;
			
			EEoffset = EEoffset - (EEoffset >> 28)*0x10000000;
			
			CONFIG_add_PS2PATCH(0, EEoffset, (u8 *) &Patched_Data, 4);
			
		} else
		if(strncmp(line, "gametitle=", 10) || strncmp(line, "comment=", 8)==0) {
			print_load(&strrchr(line, '=')[1]);
		}
	}

	fclose(fp);
}

void init_PS2_CONFIG_EDITOR()
{
	init_MENU();
	
	add_title_MENU(STR_CONFIG);
	
	u8 MGZCFGS = MGZCONFIG();	
	if(MGZCFGS != NONE) {
		add_item_MENU(STR_LOAD, ITEM_TEXTBOX);
		
		if(MGZCFGS & CURRCONFIG) {
			add_item_value_MENU(STR_CURRENT);
		}
		if(MGZCFGS & NETCONFIG) {
			add_item_value_MENU(STR_NET);
		}
		if(MGZCFGS & SOFTCONFIG) {
			add_item_value_MENU(STR_SOFT);
		}
		if(MGZCFGS & GXCONFIG) {
			add_item_value_MENU(STR_GX);
		}
		if(MGZCFGS & CUSTCONFIG) {
			add_item_value_MENU(STR_CUSTOM);
		}
	}
		
	add_item_MENU(STR_NEW_CMD, ITEM_TEXTBOX);
	
	char str[5];
	int i;
	for(i=0; i<=0x50; i++) {
		if(i == 0x30 || i == 0x31 || i == 0x32 || i == 0x33					////////////
		|| i == 0x34 || i == 0x36 || i == 0x37 || i == 0x38					// ??
		|| i == 0x39 || i == 0x3A || i == 0x3B || i == 0x4E || i == 0x4F	////////////
		|| i == 0x03 || i == 0x06 || i == 0x14 || i == 0x19					////////////
		|| i == 0x1A || i == 0x1B || i == 0x22 || i == 0x23					//
		|| i == 0x2A || i == 0x2B || i == 0x35 || i == 0x3E					// simple
		|| i == 0x40 || i == 0x41 || i == 0x44 || i == 0x45					//
		|| i == 0x46 || i == 0x47 || i == 0x49 || i == 0x4A || i == 0x50	////////////
		|| i == 0x2D || i == 0x25 || i == 0x18 || i == 0x16 || i == 0x05	// Next ID
		)	continue;
			
		sprintf(str, "0x%02X", i);
		add_item_value_MENU(str);	
	}
	
	if( Pnach_exist() ) {
		add_item_MENU(STR_PNACH, ITEM_CHECKBOX);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER]=CONFIG_exist_PNACH(pnach);
	}
	
	if( WS_exist() ) {
		add_item_MENU(STR_WIDESCREEN, ITEM_CHECKBOX);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER]=CONFIG_exist_PNACH(WS);
	} 
	
	if(PS2PATCH_480P_offset) {
		add_item_MENU(STR_480P, ITEM_CHECKBOX);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER]=CONFIG_exist_PS2PATCH(PS2PATCH_480P_offset, 0);
	}
	
	if(PS2PATCH_YFIX_offset) {
		add_item_MENU(STR_YFIX, ITEM_CHECKBOX);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER]=CONFIG_exist_PS2PATCH(PS2PATCH_YFIX_offset+0x24, 0);
	}
	
	if(PS2PATCH_FMVSKIP_offset) {
		add_item_MENU(STR_FMV, ITEM_CHECKBOX);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER]=CONFIG_exist_PS2PATCH(PS2PATCH_FMVSKIP_offset+8, 0);
	}
/*	
	add_item_MENU("Tri-Ace Hack", ITEM_CHECKBOX);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER]=CONFIG_exist_TRIACEHACK();
*/	
	add_title_MENU(STR_SIMPLE);
	
	MENU_TABLE_START = ITEMS_NUMBER;
	add_item_MENU("0x03", ITEM_COMMAND);
	add_item_MENU("0x06", ITEM_COMMAND);
	add_item_MENU("0x14", ITEM_COMMAND);
	add_item_MENU("0x19", ITEM_COMMAND);
	add_item_MENU("0x1A", ITEM_COMMAND);
	add_item_MENU("0x1B", ITEM_COMMAND);
	add_item_MENU("0x22", ITEM_COMMAND);
	add_item_MENU("0x23", ITEM_COMMAND);
	add_item_MENU("0x2A", ITEM_COMMAND);
	add_item_MENU("0x2B", ITEM_COMMAND);
	add_item_MENU("0x35", ITEM_COMMAND);
	add_item_MENU("0x3E", ITEM_COMMAND);
	add_item_MENU("0x40", ITEM_COMMAND);
	add_item_MENU("0x41", ITEM_COMMAND);
	add_item_MENU("0x44", ITEM_COMMAND);
	add_item_MENU("0x45", ITEM_COMMAND);
	add_item_MENU("0x46", ITEM_COMMAND);
	add_item_MENU("0x47", ITEM_COMMAND);
	add_item_MENU("0x49", ITEM_COMMAND);
	add_item_MENU("0x4A", ITEM_COMMAND);
	add_item_MENU("0x50", ITEM_COMMAND);
	MENU_TABLE_END = ITEMS_NUMBER;
	MENU_COLUMN_ITEMS_NUMBER = 3;
	MENU_COLUMN_ITEMS_W = 100;
	
	add_title_MENU(STR_ADVANCED);
	
}

void load_PS2_CONFIG(char *CONFIG_path)
{
	init_PS2_CONFIG_EDITOR();

	int i;
	u32 cmdID;
	u32 val32;
	u32 val32_2;
	char str[128];
	
	FILE *f;
	
	f = fopen(CONFIG_path, "rb");
	if(f==NULL) return;

	print_load("Open %s", CONFIG_path);
	
	u8 LoopBreak=1;
	while(LoopBreak)
	{
		if( fread(&cmdID, sizeof(u32), 1, f) != 4) {
			LoopBreak=0;
			goto end;
		}

		cmdID=reverse32(cmdID);
		sprintf(str, "0x%02X", cmdID);
		
		print_load("Command %s", str);
		
		switch(cmdID)
		{
			case 0x03 :
			case 0x06 :
			case 0x14 :
			case 0x19 :
			case 0x1A :
			case 0x1B :
			case 0x22 :
			case 0x23 :
			case 0x2A :
			case 0x2B :
			case 0x35 :
			case 0x3E :
			case 0x40 :
			case 0x41 :
			case 0x44 :
			case 0x45 :
			case 0x46 :
			case 0x47 :
			case 0x49 :
			case 0x4A :
			case 0x50 :
			{
				config_command(YES, str);
				break;
			}
			case 0x2D :
			case 0x25 :
			case 0x18 :
			case 0x16 :
			case 0x05 :
			{
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				print_load("Next ID");
				add_item_value_MENU("Next ID");
				break;
			}
			case 0x00 :
			{
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				char gameID[10];
				
				if( fread(&gameID, sizeof(char), 10, f) != 10) 	{
					LoopBreak=0;
					goto end;
				}		
				
				sprintf(str, "Game ID : %s", gameID);
				print_load(str);
				add_item_value_MENU(str);
				
				LoopBreak=0;
				goto end;
				
				break;
			}
			case 0x01 :
			{
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				sprintf(str, "Offset : %08X", val32);
				print_load(str);
				add_item_value_MENU(str);
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				sprintf(str, "Hack ID : %08X", val32);
				print_load(str);
				add_item_value_MENU(str);
				
				break;
			}
			case 0x02 :
			case 0x0F :
			case 0x10 :
			case 0x26 :
			case 0x27 :
			case 0x29 :
			case 0x48 :
			case 0x4B :
			case 0x4C :
			{
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				sprintf(str, "Param 1 : %08X", val32);
				print_load(str);
				add_item_value_MENU(str);
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				sprintf(str, "Param 2 : %08X", val32);
				print_load(str);
				add_item_value_MENU(str);
				
				break;
			}
			case 0x04 :
			case 0x07 :
			case 0x0D :
			case 0x0E :
			case 0x11 :
			case 0x15 :
			case 0x1F :
			case 0x21 :
			case 0x28 :
			case 0x2C :
			case 0x2E :
			case 0x2F :
			case 0x3D :
			case 0x3F :
			case 0x42 :
			case 0x43 :
			case 0x4D :
			{
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				sprintf(str, "Param : %08X", val32);
				print_load(str);
				add_item_value_MENU(str);
				
				break;
			}
			case 0x08 :
			{
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				fread(&val32_2, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				sprintf(str, "PatchedDataMask : %08X %08X", val32, val32_2);
				print_load(str);
				add_item_value_MENU(str);
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				fread(&val32_2, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				sprintf(str, "PatchedData : %08X %08X", val32, val32_2);
				print_load(str);
				add_item_value_MENU(str);
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				fread(&val32_2, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				sprintf(str, "OriginalDataMask : %08X %08X", val32, val32_2);
				print_load(str);
				add_item_value_MENU(str);
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				fread(&val32_2, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				sprintf(str, "OriginalData : %08X %08X", val32, val32_2);
				print_load(str);
				add_item_value_MENU(str);
				
				break;
			}
			case 0x09 :
			{
				u32 nb;
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				fread(&nb, sizeof(u32), 1, f);
				nb=reverse32(nb);
				sprintf(str, "Number : %08X", nb);
				print_load(str);
				add_item_value_MENU(str);
				
				for(i=0; i<nb; i++)
				{
					u32 offset;
					fread(&offset, sizeof(u32), 1, f);
					offset=reverse32(offset);
					sprintf(str, "Offset : %08X", offset);
					print_load(str);
					add_item_value_MENU(str);
					
					fread(&val32, sizeof(u32), 1, f);
					//val32=reverse32(val32);
					fread(&val32_2, sizeof(u32), 1, f);
					//val32_2=reverse32(val32_2);
					
					if( PS2ELF_compare(offset, (u8 *) &val32_2, 4) == NO ||
						PS2ELF_compare(offset+4, (u8 *) &val32, 4) == NO )
					{
						ITEMS_VALUE_SHOW[ITEMS_NUMBER]=YES;
						sprintf(str, "*Original data : %08X %08X", val32_2, val32);
					} else {
						sprintf(str, "Original data : %08X %08X", val32_2, val32);
					}
					print_load(str);
					add_item_value_MENU(str);
					
					fread(&val32, sizeof(u32), 1, f);
					//val32=reverse32(val32);
					fread(&val32_2, sizeof(u32), 1, f);
					//val32_2=reverse32(val32_2);
					sprintf(str, "Patched data : %08X %08X", val32_2, val32);
					print_load(str);
					add_item_value_MENU(str);
					
				}
				break;
			}
			case 0x0A :
			{
				u32 nb;
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&nb, sizeof(u32), 1, f);
				nb=reverse32(nb);
				sprintf(str, "Number : %08X", nb);
				print_load(str);
				add_item_value_MENU(str);
				
				for(i=0; i<nb; i++)
				{
					u32 offset;
					fread(&offset, sizeof(u32), 1, f);
					offset=reverse32(offset);
					sprintf(str, "Offset : %08X", offset);
					print_load(str);
					add_item_value_MENU(str);
					
					fread(&val32, sizeof(u32), 1, f);
					//val32=reverse32(val32);
					if( PS2ELF_compare(offset, (u8 *) &val32, 4) == NO ) {
						ITEMS_VALUE_SHOW[ITEMS_NUMBER]=YES;
						sprintf(str, "*Original data : %08X", val32);
					} else {
						sprintf(str, "Original data : %08X", val32);
					}
					print_load(str);
					add_item_value_MENU(str);
					
					fread(&val32, sizeof(u32), 1, f);
					//val32=reverse32(val32);
					sprintf(str, "Patched data : %08X", val32);
					print_load(str);
					add_item_value_MENU(str);
				}
				break;
			}
			case 0x0B :
			{
				u32 nb;
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&nb, sizeof(u32), 1, f);
				nb=reverse32(nb);
				sprintf(str, "Number : %08X", nb);
				print_load(str);
				add_item_value_MENU(str);
								
				for(i=0; i<nb; i++)
				{
					u32 sector;
					fread(&sector, sizeof(u32), 1, f);
					sector=reverse32(sector);
					sprintf(str, "Sector : %08X", sector);
					print_load(str);
					add_item_value_MENU(str);
					
					u32 offset;
					fread(&offset, sizeof(u32), 1, f);
					offset=reverse32(offset);
					sprintf(str, "Offset : %08X", offset);
					print_load(str);
					add_item_value_MENU(str);
					
					u32 size;
					fread(&size, sizeof(u32), 1, f);
					size=reverse32(size);
					sprintf(str, "Size : %08X", size);
					print_load(str);
					add_item_value_MENU(str);
										
					char temp[128];
					int k;
					
					strcpy(str, "Patched data :");
					for(k=0; k<size/4; k++) {
						if(k%8==0 && k!=0) {
							add_item_value_MENU(str);
							strcpy(str, "               :");
						}
						strcpy(temp, str);
						if( fread(&val32, sizeof(u32), 1, f) == 0) break;
						val32=reverse32(val32);
						sprintf(str, "%s %08X", temp, val32);
					}
					print_load(str);
					add_item_value_MENU(str);
					
					u8 *ISO_data = LoadMEMfromISO(list_game_path[position], sector, offset, size);
					strcpy(str, "Original data :");
					for(k=0; k<size/4; k++) {
						if(k%8==0 && k!=0) {
							print_load(str);
							add_item_value_MENU(str);
							strcpy(str, "              :");
						}
						strcpy(temp, str);
						if( fread(&val32, sizeof(u32), 1, f) == 0) break;
						val32=reverse32(val32);
						sprintf(str, "%s %08X", temp, val32);
						
						if(ISO_data && str[0] != '*') {
							
							if(memcmp((char *) &ISO_data[k*4], (char *) &val32, 4) != 0) {
								ITEMS_VALUE_SHOW[ITEMS_NUMBER]=YES;
								sprintf(str, "*%s %08X", temp, val32);
								
								//print_load("%X : ISO    : %02X%02X%02X%02X", k*4, ISO_data[k*4], ISO_data[k*4+1], ISO_data[k*4+2], ISO_data[k*4+3]);
								//print_load("%X : CONFIG : %08X",k*4, val32);
							}
						}
					}
					print_load(str);
					add_item_value_MENU(str);
					if(ISO_data) free(ISO_data);
				}
				break;
			}
			case 0xC :
			{
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				sprintf(str, "Param 1 : %02X\n", val32 >> 16);
				print_load(str);
				add_item_value_MENU(str);
				sprintf(str, "Param 2 : %02X\n", val32 & 0xFFFF);
				print_load(str);
				add_item_value_MENU(str);				
				
				break;
			}
			case 0x12 :
			{
				u32 nb;
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&nb, sizeof(u32), 1, f);
				nb=reverse32(nb);
				sprintf(str, "Number : %08X", nb);
				print_load(str);
				add_item_value_MENU(str);
								
				for(i=0; i<nb; i++)
				{
					fread(&val32, sizeof(u32), 1, f);
					val32=reverse32(val32);
					sprintf(str, "Param : %08X", val32);
					print_load(str);
					add_item_value_MENU(str);
				}
				
				break;
			}
			case 0x13 :
			case 0x20 :
			case 0x24 :
			{			
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				fread(&val32_2, sizeof(u32), 1, f);
				val32_2=reverse32(val32_2);
				sprintf(str, "Param : %08X%08X", val32, val32_2);
				print_load(str);
				add_item_value_MENU(str);
				
				break;
			}
			case 0x17 :
			case 0x1C :
			case 0x1D :
			case 0x1E :
			{			
				add_item_MENU(str, ITEM_COMMAND);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER]=YES;
				
				fread(&val32, sizeof(u32), 1, f);
				val32=reverse32(val32);
				sprintf(str, "Param : %02X", val32>>24);
				print_load(str);
				add_item_value_MENU(str);
				
				break;
			}
			default :
				break;
		}
	}

end:
	if(f) fclose(f);
	
	for(i=0; i <= ITEMS_NUMBER; i++) {
		if(strcmp(ITEMS[i], STR_PNACH) == 0) 
			ITEMS_VALUE_POSITION[i]=CONFIG_exist_PNACH(pnach);
		else
		if(strcmp(ITEMS[i], STR_WIDESCREEN) == 0) 
			ITEMS_VALUE_POSITION[i]=CONFIG_exist_PNACH(WS);
		else
		if(strcmp(ITEMS[i], STR_480P) == 0) 
			ITEMS_VALUE_POSITION[i]=CONFIG_exist_PS2PATCH(PS2PATCH_480P_offset, 0);
		else
		if(strcmp(ITEMS[i], STR_YFIX) == 0) 
			ITEMS_VALUE_POSITION[i]=CONFIG_exist_PS2PATCH(PS2PATCH_YFIX_offset+0x24, 0);
		else
		if(strcmp(ITEMS[i], STR_FMV) == 0) 
			ITEMS_VALUE_POSITION[i]=CONFIG_exist_PS2PATCH(PS2PATCH_FMVSKIP_offset+8, 0);
		
		//else
		//if(strcmp(ITEMS[i], "Tri-Ace Hack") == 0)
		//	ITEMS_VALUE_POSITION[i]=CONFIG_exist_TRIACEHACK();
		
	}
	
}

void PS2_CONFIG_MENU_CROSS()
{
	if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_COMMAND) {
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == YES) 
			ITEMS_VALUE_POSITION[ITEMS_POSITION]=NO;
		else
			ITEMS_VALUE_POSITION[ITEMS_POSITION]=YES;
	} else
	if(item_is(STR_PNACH)) {
		//start_loading();
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == NO) 
			CONFIG_add_PNACH(pnach);
		else
			CONFIG_remove_PNACH(pnach);
			
		ITEMS_VALUE_POSITION[ITEMS_POSITION]=CONFIG_exist_PNACH(pnach);
		//end_loading();
	} else
	if(item_is(STR_WIDESCREEN)) {
		//start_loading();
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == NO) 
			CONFIG_add_PNACH(WS);
		else
			CONFIG_remove_PNACH(WS);
		ITEMS_VALUE_POSITION[ITEMS_POSITION]=CONFIG_exist_PNACH(WS);
		//end_loading();
	} else
	if(item_is(STR_YFIX)) {
		//start_loading();
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == NO) 
			CONFIG_add_PS2PATCH(PS2PATCH_YFIX_offset+0x24, 0, &PS2PATCH_YFIX_FLAG_ENABLE[0x24], 4);
		else
			CONFIG_remove_PS2PATCH(PS2PATCH_YFIX_offset+0x24, 0, 4);
		ITEMS_VALUE_POSITION[ITEMS_POSITION]=CONFIG_exist_PS2PATCH(PS2PATCH_YFIX_offset+0x24, 0);
		//end_loading();
	} else
	if(item_is(STR_480P)) {
		//start_loading();
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == NO) {
			CONFIG_add_PS2PATCH(PS2PATCH_480P_offset, 0, PS2PATCH_480P_FLAG_ENABLE, 4);
			CONFIG_add_PS2PATCH(PS2PATCH_480P_offset+8, 0, &PS2PATCH_480P_FLAG_ENABLE[8], 4);
			CONFIG_add_PS2PATCH(PS2PATCH_480P_offset+0x10, 0, &PS2PATCH_480P_FLAG_ENABLE[0x10], 4);
		}
		else {
			CONFIG_remove_PS2PATCH(PS2PATCH_480P_offset, 0, 4);
			CONFIG_remove_PS2PATCH(PS2PATCH_480P_offset+8, 0, 4);
			CONFIG_remove_PS2PATCH(PS2PATCH_480P_offset+0x10, 0, 4);
		}
		ITEMS_VALUE_POSITION[ITEMS_POSITION]=CONFIG_exist_PS2PATCH(PS2PATCH_480P_offset, 0);
		//end_loading();
	} else
	if(item_is(STR_FMV)) {
		//start_loading();
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == NO) 
			CONFIG_add_PS2PATCH(PS2PATCH_FMVSKIP_offset+8, 0, &PS2PATCH_FMVSKIP_FLAG_ENABLE[8], 4);
		else
			CONFIG_remove_PS2PATCH(PS2PATCH_FMVSKIP_offset+8, 0, 4);
		ITEMS_VALUE_POSITION[ITEMS_POSITION]=CONFIG_exist_PS2PATCH(PS2PATCH_FMVSKIP_offset+8, 0);
		//end_loading();
	} else
/*
	if(item_is("Tri-Ace Hack")) {
		start_loading();
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == NO) 
			CONFIG_add_TRIACEHACK();
		else
			CONFIG_remove_TRIACEHACK();
		ITEMS_VALUE_POSITION[ITEMS_POSITION]=CONFIG_exist_TRIACEHACK();
		end_loading();
	} else
*/
	if(item_is(STR_LOAD)) {
		char CONFIG_path[128];
		if(item_value_is(STR_CURRENT)) {
			sprintf(CONFIG_path, "%s.CONFIG", list_game_path[position]);
		} else
		if(item_value_is(STR_NET)) {
			sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/NET/%s.CONFIG", ManaGunZ_id, PS2_ID);
		} else
		if(item_value_is(STR_SOFT)) {
			sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/SOFT/%s.CONFIG", ManaGunZ_id, PS2_ID);
		} else
		if(item_value_is(STR_GX)) {
			sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/GX/%s.CONFIG", ManaGunZ_id, PS2_ID);
		} else
		if(item_value_is(STR_CUSTOM)) {
			sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/CUSTOM/%s.CONFIG", ManaGunZ_id, PS2_ID);
		}
		//start_loading();
		load_PS2_CONFIG(CONFIG_path);
		//end_loading();
	} else
	if(item_is(STR_NEW_CMD)) {
		show_msg("TODO");
	}
	
}

void close_PS2_CONFIG_EDITOR()
{	
	free_MENU();
	open_PS2_GAME_MENU();
}

void input_PS2_CONFIG_EDITOR()
{
	get_R2speed();
		
	if(MENU_TABLE_START < ITEMS_POSITION && ITEMS_POSITION <=MENU_TABLE_END) {
		if(R2pad(BUTTON_RIGHT)) {
			if(ITEMS_POSITION + MENU_COLUMN_ITEMS_NUMBER <= MENU_TABLE_END) ITEMS_POSITION += MENU_COLUMN_ITEMS_NUMBER;
		} else
		if(R2pad(BUTTON_LEFT)) {
			if(ITEMS_POSITION - MENU_COLUMN_ITEMS_NUMBER > MENU_TABLE_START) ITEMS_POSITION -= MENU_COLUMN_ITEMS_NUMBER;
		}
		if(MENU_TABLE_END < ITEMS_NUMBER) {
			if(R2pad(BUTTON_DOWN)) {
				if( (ITEMS_POSITION-MENU_TABLE_START)%MENU_COLUMN_ITEMS_NUMBER == 0 ) ITEMS_POSITION=MENU_TABLE_END;
			}
		}
		if(0<MENU_TABLE_START) {
			if(R2pad(BUTTON_UP)) {
				if( (ITEMS_POSITION-MENU_TABLE_START)%MENU_COLUMN_ITEMS_NUMBER == 1 ) ITEMS_POSITION=MENU_TABLE_START+1;
			}
		}
	}
	
	if(R2pad(BUTTON_UP)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
			if(ITEMS_POSITION==MENU_TABLE_END) ITEMS_POSITION=MENU_TABLE_START+MENU_COLUMN_ITEMS_NUMBER; 
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	} else
	if(R2pad(BUTTON_DOWN)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	} else
	if(new_pad & BUTTON_CROSS) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1 
		&& ITEMS_TYPE[ITEMS_POSITION] != ITEM_COMMAND && ITEMS_TYPE[ITEMS_POSITION] != ITEM_CHECKBOX) 
		{
			IN_ITEMS_VALUE = YES;
		} else {
			PS2_CONFIG_MENU_CROSS();
		}
	} else
	if(new_pad & BUTTON_CIRCLE) {
		if(IN_ITEMS_VALUE == NO)
			close_PS2_CONFIG_EDITOR();
		else
			IN_ITEMS_VALUE = NO;
	} else
	if(new_pad & BUTTON_START) {
		if(IN_ITEMS_VALUE == NO) {
			start_loading();
			if( Create_PS2_CONFIG() ) show_msg(STR_DONE);
			else show_msg(STR_FAILED);
			
			end_loading();
		}
	}
	
}

void Draw_PS2_CONFIG_EDITOR_input()
{
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_COMMAND || ITEMS_TYPE[ITEMS_POSITION] == ITEM_CHECKBOX) {
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == YES) {
			x=DrawButton(x, y, STR_UNCHECK, BUTTON_CROSS);
		} else {
			x=DrawButton(x, y, STR_CHECK, BUTTON_CROSS);
		}
	} else
	if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_TEXTBOX) {
		x=DrawButton(x, y, STR_ENTER, BUTTON_CROSS);
	}
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
	if(IN_ITEMS_VALUE == NO) {
		x=DrawButton(x, y, STR_SAVE_CONFIG, BUTTON_START );
	}
}

void close_PS2_GAME_MENU();
void open_PS2_CONFIG_EDITOR()
{
	start_loading();
	
	close_PS2_GAME_MENU();
	
	new_MENU();
	
	char CONFIG_path[128];
	sprintf(CONFIG_path, "%s.CONFIG", list_game_path[position]);
	load_PS2_CONFIG(CONFIG_path);
	
	MENU_SIDE=NO;
	Draw_MENU_input = &Draw_PS2_CONFIG_EDITOR_input;
	input_MENU = &input_PS2_CONFIG_EDITOR;
	
	end_loading();

}

u32 Get_PS2CRC()
{
	if(PS2ELF_mem == NULL) return 0;
	
	print_load("Getting current CRC...");
	
	u32 CRC=0;
	u32 i;
	prog_bar1_value=0;
	for(i=0; i<PS2ELF_mem_size; i+=4) {
		CRC ^= *(u32 *) &PS2ELF_mem[i];
		prog_bar1_value = (i*100)/PS2ELF_mem_size;
	}
	prog_bar1_value=-1;
	
	return reverse32(CRC);
	
}

u32 Get_Original_PS2CRC()
{	
	
	if(PS2ELF_mem == NULL) return 0;
	
	print_load("Getting original CRC...");
	
	const u32* srcdata = (u32*) PS2ELF_mem;

	FILE* f;
	char Rest[128];
	u32 offset;
	u32 data;
	
	sprintf(Rest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnachrest", ManaGunZ_id, PS2CRC_STR);	
	f = fopen(Rest, "rb");
	if(f != NULL) {
		while( fread(&offset, 1, 4, f) == 4) {
			if( fread(&data, 1, 4, f) == 4 ) {
				*(u32 *) &srcdata[offset/4] = data; 
			}
		}
		
		fclose(f);
	}
	
	sprintf(Rest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, PS2CRC_STR);
	
	f = fopen(Rest, "rb");
	if(f != NULL) {
		while( fread(&offset, 1, 4, f) == 4) {
			if( fread(&data, 1, 4, f) == 4 ) {
				*(u32 *) &srcdata[offset/4] = data; 
			}
		}
		
		fclose(f);
	}
	
	if(PS2PATCH_480P_offset) {
		memcpy((char *) srcdata + PS2PATCH_480P_offset,  (char *) PS2PATCH_480P_FLAG_DISABLE, sizeof(PS2PATCH_480P_FLAG_DISABLE));	
	}
	
	if(PS2PATCH_YFIX_offset) {
		memcpy((char *) srcdata + PS2PATCH_YFIX_offset,  (char *) PS2PATCH_YFIX_FLAG_DISABLE, sizeof(PS2PATCH_YFIX_FLAG_DISABLE));	
	}
	
	if(PS2PATCH_FMVSKIP_offset) {
		memcpy((char *) srcdata + PS2PATCH_FMVSKIP_offset,  (char *) PS2PATCH_FMVSKIP_FLAG_DISABLE, sizeof(PS2PATCH_FMVSKIP_FLAG_DISABLE));	
	}
	
	u32 CRC=0;
	u32 i;

	for(i=PS2ELF_mem_size/4; i; --i, ++srcdata) CRC ^= *srcdata;
	
	return reverse32(CRC);
	
}

void find_PS2PATCH()
{
	print_load("Searching PS2 patches...");
	
	PS2PATCH_480P = NO;
	PS2PATCH_YFIX = NO;
	PS2PATCH_FMVSKIP = NO;

	PS2PATCH_480P_offset = 0;
	PS2PATCH_YFIX_offset = 0;
	PS2PATCH_FMVSKIP_offset = 0;
	
	int n;
	prog_bar1_value=0;
	prog_bar2_value=0;
	for(n=0; n < PS2ELF_mem_size ; n+=4) {
	
		prog_bar1_value=(n*100)/PS2ELF_mem_size;
		
		if(!PS2PATCH_480P_offset) {
			if(!memcmp((char *) &PS2ELF_mem[n], (char *) PS2PATCH_480P_FLAG_DISABLE, sizeof(PS2PATCH_480P_FLAG_DISABLE)))
			{
				print_load("480P patch found !");
				PS2PATCH_480P_offset = n;
				PS2PATCH_480P = NO;
				prog_bar2_value += 100/3;
			} else
			if(!memcmp((char *) &PS2ELF_mem[n], (char *) PS2PATCH_480P_FLAG_ENABLE, sizeof(PS2PATCH_480P_FLAG_ENABLE)))
			{
				print_load("480P patch found !");
				PS2PATCH_480P_offset = n;
				PS2PATCH_480P = YES;
				prog_bar2_value += 100/3;
			}			
		}
		
		if(!PS2PATCH_YFIX_offset) {
			if(!memcmp((char *) &PS2ELF_mem[n], (char *) PS2PATCH_YFIX_FLAG_DISABLE, sizeof(PS2PATCH_YFIX_FLAG_DISABLE)))
			{
				print_load("YFIX patch found !");
				PS2PATCH_YFIX_offset = n;
				PS2PATCH_YFIX = NO;
				prog_bar2_value += 100/3;
			} else
			if(!memcmp((char *) &PS2ELF_mem[n], (char *) PS2PATCH_YFIX_FLAG_ENABLE, sizeof(PS2PATCH_YFIX_FLAG_ENABLE)))
			{
				print_load("YFIX patch found !");
				PS2PATCH_YFIX_offset = n;
				PS2PATCH_YFIX = YES;
				prog_bar2_value += 100/3;
			}
		}
		
		if(!PS2PATCH_FMVSKIP_offset) {
			if(!memcmp((char *) &PS2ELF_mem[n], (char *) PS2PATCH_FMVSKIP_FLAG_DISABLE, sizeof(PS2PATCH_FMVSKIP_FLAG_DISABLE)))
			{
				print_load("FMV SKIP patch found !");
				PS2PATCH_FMVSKIP_offset = n;
				PS2PATCH_FMVSKIP = NO;
				prog_bar2_value += 100/3;
			} else
			if(!memcmp((char *) &PS2ELF_mem[n], (char *) PS2PATCH_FMVSKIP_FLAG_ENABLE, sizeof(PS2PATCH_FMVSKIP_FLAG_ENABLE)))
			{
				print_load("FMV SKIP patch found !");
				PS2PATCH_FMVSKIP_offset = n;
				PS2PATCH_FMVSKIP = YES;
				prog_bar2_value += 100/3;
			}
		}
		
		if(PS2PATCH_480P_offset)
		if(PS2PATCH_YFIX_offset)
		if(PS2PATCH_FMVSKIP_offset)
		break;
	}
	
	prog_bar1_value=-1;
	prog_bar2_value=-1;
}

void update_PS2CRC()
{
	
	if(PS2ELF_mem==NULL) {
		print_head("Loading...");
		
		PS2ELF_mem = LoadFileFromISO(YES, list_game_path[position], PS2_ID, &PS2ELF_mem_size);
		if(PS2ELF_mem==NULL) print_load("Error : failed to load elf %s", PS2_ID);
		
		find_PS2PATCH();
		
		sprintf(PS2CRC_STR, "%08lX", (long unsigned int) Get_PS2CRC());
		
		sprintf(PS2ORICRC_STR, "%08lX", (long unsigned int) Get_Original_PS2CRC());
		
		return;
		
	}

	char old_PS2CRC[8];
	
	strcpy(old_PS2CRC, PS2CRC_STR);
	
	sprintf(PS2CRC_STR, "%08lX", (long unsigned int) Get_PS2CRC());
	
	char old_PnatchRes[128];
	char new_PnatchRes[128];
		
	sprintf(old_PnatchRes, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnatchrest", ManaGunZ_id, old_PS2CRC);
	sprintf(new_PnatchRes, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnatchrest", ManaGunZ_id, PS2CRC_STR);
	
	rename(old_PnatchRes, new_PnatchRes);
	
	char old_WSRes[128];
	char new_WSRes[128];
	
	sprintf(old_WSRes, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, old_PS2CRC);
	sprintf(new_WSRes, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, PS2CRC_STR);
	
	rename(old_WSRes, new_WSRes);	
	
	sprintf(PS2ORICRC_STR, "%08lX", (long unsigned int) Get_Original_PS2CRC());
}

u8 Apply_PS2PATCH(u32 patch_offset, u8 *patch_value, int patch_size)
{
	FILE* fi;
	
	fi = fopen(list_game_path[position], "rb+");
	if(fi==NULL) {print_load(list_game_path[position]); print_load("Error : failed to open iso file"); return FAILED; }

	u64 file_offset=0;
	u32 size=0;
	u8 ret;

	ret = get_FileOffset(fi, PS2_ID, &file_offset, &size); 

	if(file_offset==0 || size==0 || ret == FAILED) {
		print_load("Error : file_pos. File : %s file_offset= %X size= %X", PS2_ID, file_offset, size);
		fclose(fi);
		return FAILED;
	}
	
	fseek(fi, file_offset + patch_offset, SEEK_SET);
	
	fwrite(patch_value, 1, patch_size, fi);
	
	fclose(fi);
	
	memcpy((char *) &PS2ELF_mem[patch_offset], patch_value, patch_size);
	
	update_PS2CRC();
	
	return SUCCESS;
}

u8 is_pnached()
{
	char PnachRest[128];
	
	sprintf(PnachRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnachrest", ManaGunZ_id, PS2CRC_STR);
	
	if(path_info(PnachRest) == _NOT_EXIST) return NO; else
	return YES;
}

u8 Pnach_exist()
{
	sprintf(pnach, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnach", ManaGunZ_id, PS2ORICRC_STR);
	if(path_info(pnach) == _FILE) return YES;
	
	int i;
	for(i=0; i<=device_number; i++) {
		sprintf(pnach, "/%s/PNACH/%s.pnach", list_device[i], PS2ORICRC_STR);
		if(path_info(pnach) == _FILE) return YES;
	}
	
	return NO;
}

u8 restore_pnach(char *PnachRest)
{
	FILE* fi;
	FILE* fr;
	u32 offset;
	u32 data;

	fi = fopen(list_game_path[position], "rb+");
	if(fi==NULL) { print_load("Error : Cannot open ISO"); return FAILED;}
	
	fr = fopen(PnachRest, "rb");
	if(fr==NULL) { fclose(fi); print_load("Error : Cannot open PnachRestore file"); return FAILED;}
	
	u64 file_offset=0;
	u32 size=0;
	u8 ret;

	ret = get_FileOffset(fi, PS2_ID, &file_offset, &size); 

	if(file_offset==0 || size==0 || ret == FAILED) {
		print_load("Error : file_pos. File : %s file_offset= %X size= %X", PS2_ID, file_offset, size);
		fclose(fi);
		fclose(fr);
		return FAILED;
	}
	
	while( fread(&offset, 1, 4, fr) == 4) {
		if( fread(&data, 1, 4, fr) == 4 ) {
			fseek(fi, file_offset + offset, SEEK_SET);
			fwrite(&data, 4, 1, fi);
			*(u32 *) &PS2ELF_mem[offset] = data; 
		}
    }
	
	fclose(fi);
	fclose(fr);
	
	Delete(PnachRest);
	
	update_PS2CRC();
	
	return SUCCESS;
}

/*
struct ELF_HEADER {
	u8	e_ident[16];	//0x7f,"ELF"  (ELF file identifier)
	u16	e_type;			//ELF type: 0=NONE, 1=REL, 2=EXEC, 3=SHARED, 4=CORE
	u16	e_machine;	  //Processor: 8=MIPS R3000
	u32	e_version;	  //Version: 1=current
	u32	e_entry;		//Entry point address
	u32	e_phoff;		//Start of program headers (offset from file start)
	u32	e_shoff;		//Start of section headers (offset from file start)
	u32	e_flags;		//Processor specific flags = 0x20924001 noreorder, mips
	u16	e_ehsize;	   //ELF header size (0x34 = 52 bytes)
	u16	e_phentsize;	//Program headers entry size
	u16	e_phnum;		//Number of program headers
	u16	e_shentsize;	//Section headers entry size
	u16	e_shnum;		//Number of section headers
	u16	e_shstrndx;	 //Section header stringtable index
};

struct ELF_PHR {
	u32 p_type;		 //see notes1
	u32 p_offset;	   //Offset from file start to program segment.
	u32 p_vaddr;		//Virtual address of the segment
	u32 p_paddr;		//Physical address of the segment
	u32 p_filesz;	   //Number of bytes in the file image of the segment
	u32 p_memsz;		//Number of bytes in the memory image of the segment
	u32 p_flags;		//Flags for segment
	u32 p_align;		//Alignment. The address of 0x08 and 0x0C must fit this alignment. 0=no alignment
};
*/

u8 apply_pnach(char *pnach_file, char *PnachRest)
{
	FILE* fp;
	FILE* fi;
	FILE* fr;
	char line[128];
	
	u32 offset;
	u32 new_data;
	u32 old_data;
	
	fp = fopen(pnach_file, "rb");
	if(fp==NULL) { print_load("Error : failed to open pnach file");return FAILED; }
	
	fi = fopen(list_game_path[position], "rb+");
	if(fi==NULL) { fclose(fp); print_load(list_game_path[position]); print_load("Error : failed to open iso file"); return FAILED; }
	
	fr = fopen(PnachRest, "wb");
	if(fr==NULL) { fclose(fp); fclose(fi); print_load("Error : failed to open pnachrest file"); return FAILED; }
	
	u64 file_offset=0;
	u32 size=0;
	u8 ret;

	ret = get_FileOffset(fi, PS2_ID, &file_offset, &size); 

	if(file_offset==0 || size==0 || ret == FAILED) {
		print_load("Error : file_pos. File : %s file_offset= %X size= %X", PS2_ID, file_offset, size);
		fclose(fi);
		fclose(fp); 
		fclose(fr);
		Delete(PnachRest);
		return FAILED;
	}
	
	u32 EntryPoint;
	u32 ProgOffset;
	u16 ProgHeaderNumber;
	u32 ProgType;
	u32 filesz;
	
	fseek(fi, file_offset + 0x18, SEEK_SET);
	fread(&EntryPoint, 4, 1, fi);
	EntryPoint = reverse32(EntryPoint);
	
	fseek(fi, file_offset + 0x2C, SEEK_SET);
	fread(&ProgHeaderNumber, 2, 1, fi);
	
	ProgHeaderNumber = reverse16(ProgHeaderNumber);
	
	int i;
	for(i=0; i < ProgHeaderNumber; i++) {
		fseek(fi, file_offset + 0x34+i*0x20, SEEK_SET);
		fread(&ProgType, 4, 1, fi);
		ProgType = reverse32(ProgType);
		
		fseek(fi, file_offset + 0x34+0x10+i*0x20, SEEK_SET);
		fread(&filesz, 4, 1, fi);
		
		if(ProgType==1 && filesz!=0) {
			fseek(fi, file_offset + 0x38+i*0x20, SEEK_SET);
			break;
		}
	}
		
	if(ProgType != 1 || filesz==0) {
		print_load("Error : ProgOffset not found");
		fclose(fi);
		fclose(fp); 
		fclose(fr);
		Delete(PnachRest);
		return FAILED;
	}
	
	fread(&ProgOffset, 4, 1, fi);
	ProgOffset = reverse32(ProgOffset);
	
	while(fgets(line, 128, fp) != NULL) {
		if( strstr(line, "patch") == NULL && strstr(line, "comment")==NULL && strstr(line, "gametitle")==NULL ) continue;
		
		if(strncmp(line, "patch=1", 7) == 0) 
		{			
			if(strstr(line, ",") == NULL) continue;
			
			char *token;
			unsigned long int value=0;
			token = strtok (line, ", "); //toggle patch
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //cpu
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //addr
			if(token == NULL) continue;
			sscanf(token, "%8lX", &value);
			offset = value;
			value = 0;
			token = strtok (NULL, ", "); //type
			if(token == NULL) continue;
			token = strtok (NULL, ", "); //data
			sscanf(token, "%8lX", &value);
			new_data = value;
			
			offset = offset - (EntryPoint - 8 - ProgOffset);
			offset = offset - (offset >> 28)*0x10000000;
			
			if(offset > size) { 
				print_load("Error : offset %X > Elf_size %X", offset, size);
				fclose(fr);
				fclose(fi);
				fclose(fp);
				restore_pnach(PnachRest);
				return FAILED;
			}
			
			new_data = reverse32(new_data);
			fseek(fi, file_offset + offset, SEEK_SET);
			fread(&old_data, 4, 1, fi);
			
			fseek(fi, file_offset + offset, SEEK_SET);
			
			fwrite(&new_data, 4, 1, fi);
			
			*(u32 *) &PS2ELF_mem[offset] = new_data;
			
			fwrite(&offset, 4, 1, fr);
			fwrite(&old_data, 4, 1, fr);
			
		} else
		if(strncmp(line, "gametitle=", 10) || strncmp(line, "comment=", 8)==0) {
			print_load(&strrchr(line, '=')[1]);
		}
	}
	
	fclose(fr);
	fclose(fi);
	fclose(fp);
	
	update_PS2CRC();
	
	return SUCCESS;
}

u8 WS_exist()
{
	sprintf(WS, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.ws", ManaGunZ_id, PS2ORICRC_STR);
	
	if(path_info(WS) == _NOT_EXIST) return NO;
	
	return YES;
}

void get_WS()
{
	sprintf(WS, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.ws", ManaGunZ_id, PS2ORICRC_STR);
	
	if(path_info(WS) != _NOT_EXIST) return;
	
	char ZIP_WS[32];
	char ZIP[128];
	
	sprintf(ZIP_WS, "%s.pnach", PS2ORICRC_STR);
	sprintf(ZIP, "/dev_hdd0/game/%s/USRDIR/sys/ws.zip", ManaGunZ_id);
	
	ExtractZipFile(ZIP, ZIP_WS, WS);
}

u8 is_WS()
{
	char WSRest[128];
	
	sprintf(WSRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, PS2CRC_STR);
	
	if(path_info(WSRest) == _NOT_EXIST) return NO; else
	return YES;
}

u8 LIMG_exist(char *iso_file)
{
	u8 split666 = is_66600(iso_file);
	if(is_splitted_iso(iso_file)==YES || split666) {
		//TODO
		return NO;
	}
	
	FILE *f;
	f = fopen(iso_file, "rb");
	if(f==NULL) {
		print_load("Error : LIMG_exist, failed to fopen");
		return NO;
	}
	fseek(f, 0, SEEK_END);
	u64 LIMG_OFFSET = ftell(f) - LIMG_SIZE;
	fseek(f, LIMG_OFFSET, SEEK_SET);
	
	char LIMG_FLAG[5];
	fread(&LIMG_FLAG, 4, 1, f);
	LIMG_FLAG[4]=0;
	
	fclose(f);
	
	if(strcmp(LIMG_FLAG, "LIMG")==0) return YES;
	
	else return NO;
}

// return has_LIMG
u8 Remove_LIMG(char *iso_file)
{
	if(LIMG_exist(iso_file) == NO) return NO; 
	
	u8 split666 = is_66600(iso_file);
	if(is_splitted_iso(iso_file)==YES || split666) {
		//TODO
		print_load("Error : splitted ISO not supported yet");
		return NO;
	}
	
	u64 size = get_size(iso_file, NO) - LIMG_SIZE;
	
	if(truncate(iso_file, size) == 0) return NO;
	
	return LIMG_exist(iso_file);
}

// return has_LIMG
u8 Add_LIMG(char *iso_file)
{
	if(LIMG_exist(iso_file) == YES) return SUCCESS; 
	
	u8 split666 = is_66600(iso_file);
	if(is_splitted_iso(iso_file)==YES || split666) {
		//TODO
		print_load("Error : splitted ISO not supported yet");
		return FAILED;
	}
	
	FILE *f;	
	u32 SectSize=0;
	u32 JP=0;
	
	f = fopen(iso_file, "rb");
	if(f==NULL) {
		print_load("Error : LIMG_exist, failed to fopen");
		return FAILED;
	}
	if( get_SectorSize(f, &SectSize, &JP) == FAILED) {
		fclose(f);
		print_load("Error : Add_LIMG, failed to get_SectorSize");
		return FAILED;
	}
	FCLOSE(f);
	
	u64 Size = get_size(iso_file, NO);
	
	// it must be a better way to detect properly cd / dvd ...
	u32 DiskType=2; // CD
	if(Size > 700*1024*1024) DiskType=1; // DVD 
	
	u32 SectorNumber = Size/SectSize + 1;
	
	f = fopen(iso_file, "ab");
	if(f==NULL) {
		print_load("Error : LIMG_exist, failed to fopen");
		return FAILED;
	}
	fputs("LIMG", f);
	fwrite(&DiskType, sizeof(u32), 1, f);
	fwrite(&SectorNumber, sizeof(u32), 1, f);
	fwrite(&SectSize, sizeof(u32), 1, f);
	fclose(f);
	
	truncate(iso_file, Size+LIMG_SIZE);
	
	return LIMG_exist(iso_file);
}

void init_PS2_GAME_MENU()
{
	int i,j;
		
	init_MENU();

	add_title_MENU(STR_GAME_OPTION);
	
	if( is_favorite(list_game_path[position]) == NO )
		add_item_MENU(STR_ADD_FAV, ITEM_TEXTBOX);
	else 
		add_item_MENU(STR_REM_FAV, ITEM_TEXTBOX);
	
	
	add_item_MENU(STR_RENAME, ITEM_TEXTBOX);
	
	add_item_MENU(STR_DELETE, ITEM_TEXTBOX);
	
	if(device_number != 0) {
		add_item_MENU(STR_COPY, ITEM_TEXTBOX);
		for(j=0; j<=scan_dir_number; j++) {
			for(i=0; i<=device_number; i++) {
				if(strstr(list_game_path[position], list_device[i])) continue;
				char tmp[128];
				sprintf(tmp, "/%s/%s", list_device[i], scan_dir[j]);
				add_item_value_MENU(tmp);
			}
		}
	}
	
	if(is_66600(list_game_path[position])==YES && is_usb(list_game_path[position])==NO) {
		add_item_MENU(STR_JOIN, ITEM_TEXTBOX);
	}

	if(has_LIMG==YES) {
		add_item_MENU(STR_REMOVE_LIMG, ITEM_TEXTBOX);
	} else {
		add_item_MENU(STR_ADD_LIMG, ITEM_TEXTBOX);
	}
	
	if(COVER_offset[position] != 0) {
		add_item_MENU(STR_CREATE_ICON0, ITEM_TEXTBOX);
	}
	
	if( is_pnached() ) {
		add_item_MENU(STR_REST_PNACH, ITEM_TEXTBOX);
	}
	else 
	if( Pnach_exist() ) {
		add_item_MENU(STR_APPLY_PNACH, ITEM_TEXTBOX);
	}
	
	if( is_WS() ) {
		add_item_MENU(STR_DISABLE_WS, ITEM_TEXTBOX);
	} else 
	if( WS_exist() ) {
		add_item_MENU(STR_ENABLE_WS, ITEM_TEXTBOX);
	}
	
	if(PS2PATCH_480P_offset) {
		if(PS2PATCH_480P == YES) {
			add_item_MENU(STR_DISABLE_480P, ITEM_TEXTBOX);
		} else {
			add_item_MENU(STR_ENABLE_480P, ITEM_TEXTBOX);
		}
	}
	
	if(PS2PATCH_YFIX_offset) {
		if(PS2PATCH_YFIX == YES) {
			add_item_MENU(STR_DISABLE_YFIX, ITEM_TEXTBOX);
		} else {
			add_item_MENU(STR_ENABLE_YFIX, ITEM_TEXTBOX);
		}
	}
	
	if(PS2PATCH_FMVSKIP_offset) {
		if(PS2PATCH_FMVSKIP == YES) {
			add_item_MENU(STR_DISABLE_FMVSKIP, ITEM_TEXTBOX);
		} else {
			add_item_MENU(STR_ENABLE_FMVSKIP, ITEM_TEXTBOX);
		}
	}
	
	i = ps2_netemu_cobra(BCNETEMU_STATUS);
	if(i != BCNETEMU_ISNOTBC) {
		if(i == BCNETEMU_OFF) {
			add_item_MENU(STR_ENABLE_NETEMU, ITEM_TEXTBOX);
		} else
		if(i == BCNETEMU_ON) {
			add_item_MENU(STR_DISABLE_NETEMU, ITEM_TEXTBOX);
		}	
	}
	
	add_item_MENU(STR_CONFIG, ITEM_TEXTBOX);
	
	add_item_MENU(STR_CHECK_MD5, ITEM_TEXTBOX);
	
	add_item_MENU(STR_PROPS, ITEM_TEXTBOX);

}

void close_PS2_GAME_MENU()
{
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	MENU=NO;
	free_MENU();
}

u8 PS2_GAME_MENU_CROSS()
{
	
	if(item_is(STR_ADD_LIMG)) {
		start_loading();
		has_LIMG = Add_LIMG(list_game_path[position]);
		end_loading();
	} else 
	if(item_is(STR_REMOVE_LIMG)) {
		start_loading();
		has_LIMG = Remove_LIMG(list_game_path[position]);
		end_loading();
	} else
	if(item_is(STR_RENAME)) {
		char NewName[255];
		strcpy(NewName, list_game_title[position]);
		char *extention = GetExtention(list_game_path[position]);
		if(Get_OSK_String(STR_RENAME, NewName, 255) == SUCCESS) {
			if(NewName[0] != 0) {
				char DirPath[255];
				char NewPath[255];
				strcpy(DirPath, list_game_path[position]);
				DirPath[strrchr(DirPath, '/') - DirPath] = 0;
				sprintf(NewPath, "%s/%s%s", DirPath, NewName, extention);
				if( rename(list_game_path[position], NewPath) == 0) {
					FREE(list_game_path[position]);				
					list_game_path[position] = strcpy_malloc(NewPath);
					FREE(list_game_path[position])
					list_game_title[position] = strcpy_malloc(NewName);
				}
			}
		}
	} else 
	if(item_is(STR_CREATE_ICON0)) {
		open_ICON0_creator();
	} else 
	if(item_is(STR_ADD_FAV)) {
		if(add_favorite()==SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_REM_FAV)) {
		if(remove_favorite()==SUCCESS) show_msg(STR_DONE); 
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_REST_PNACH)) {
		start_loading();
		char PnachRest[128];
		sprintf(PnachRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnachrest", ManaGunZ_id, PS2CRC_STR);
		u8 ret = restore_pnach(PnachRest);
		end_loading();
		if( ret == SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_APPLY_PNACH)) {
		start_loading();
		char PnachRest[128];
		sprintf(PnachRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnachrest", ManaGunZ_id, PS2CRC_STR);
		u8 ret = apply_pnach(pnach, PnachRest);
		end_loading();
		
		if( ret == SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_ENABLE_WS)) {
		start_loading();
		char WSRest[128];
		sprintf(WSRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, PS2CRC_STR);
		u8 ret = apply_pnach(WS, WSRest);
		end_loading();
		if( ret == SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_DISABLE_WS)) {
		start_loading();
		char WSRest[128];
		sprintf(WSRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, PS2CRC_STR);
		u8 ret = restore_pnach(WSRest);
		end_loading();
		if( ret == SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_ENABLE_NETEMU)) {
		if( ps2_netemu_cobra(BCNETEMU_ON) == BCNETEMU_ON) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_DISABLE_NETEMU)) {
		if( ps2_netemu_cobra(BCNETEMU_OFF) == BCNETEMU_OFF) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_CONFIG)) {
		open_PS2_CONFIG_EDITOR();
		return CONTINUE;
	} else 
	if(item_is(STR_CHECK_MD5)) {
		start_loading();
		u8 ret = CheckMD5(list_game_path[position]);
		end_loading();
		if(ret == SUCCESS) {
			char temp[255];
			strcpy(temp, list_game_path[position]);
			temp[strlen(temp)-4]=0;
			strcat(temp, "_CHECK.md5");
			open_txt_viewer(temp);
		}
	} else 
	if(item_is(STR_COPY)) {
		Copy_Game(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
	} else 
	if(item_is(STR_JOIN)) {
		char dest[255];
		strcpy(dest, list_game_path[position]);
		dest[strrchr(dest, '/') - dest] = 0;
		Copy_Game(list_game_path[position], dest);
	} else 
	if(item_is(STR_DELETE)) 
	{
		char diag_msg[512];
		sprintf(diag_msg, "%s '%s' ?\n%s : %s\n", STR_ASK_DEL, list_game_title[position], STR_PATH, list_game_path[position]);
		if( DrawDialogYesNo(diag_msg) == YES) {
			start_loading();
			u8 ret = Delete_Game(NULL, position);
			end_loading();
			if(ret==SUCCESS) {
				show_msg(STR_DONE);
				return BREAK;
			} else show_msg(STR_FAILED);
		}
	} else 
	if(item_is(STR_PROPS)) {
		start_loading();
		gathering=YES;
		Get_Game_Size(list_game_path[position]);
		gathering=NO;
		end_loading();
			
		if(gathering_cancel==NO) Draw_GameProperties();
		else gathering_cancel=NO;
		total_size=0;
		nb_file= 0;
		nb_directory=0;
	} else
	if(item_is(STR_ENABLE_480P)) {
		start_loading();
		u8 ret = Apply_PS2PATCH(PS2PATCH_480P_offset, PS2PATCH_480P_FLAG_ENABLE, sizeof(PS2PATCH_480P_FLAG_ENABLE));
		end_loading();
		if( ret == SUCCESS) {
			PS2PATCH_480P = YES;
			show_msg(STR_DONE);
		} 
		else show_msg(STR_FAILED);
	} else
	if(item_is(STR_DISABLE_480P)) {
		start_loading();
		u8 ret = Apply_PS2PATCH(PS2PATCH_480P_offset, PS2PATCH_480P_FLAG_DISABLE, sizeof(PS2PATCH_480P_FLAG_DISABLE));
		end_loading();
		if( ret == SUCCESS) {
			PS2PATCH_480P = NO;
			show_msg(STR_DONE);
		} 
		else show_msg(STR_FAILED);
	} else
	if(item_is(STR_ENABLE_YFIX)) {
		start_loading();
		u8 ret = Apply_PS2PATCH(PS2PATCH_YFIX_offset, PS2PATCH_YFIX_FLAG_ENABLE, sizeof(PS2PATCH_YFIX_FLAG_ENABLE));
		end_loading();
		if( ret == SUCCESS) {
			PS2PATCH_YFIX = YES;
			show_msg(STR_DONE);
		} 
		else show_msg(STR_FAILED);
	} else
	if(item_is(STR_DISABLE_YFIX)) {
		start_loading();
		u8 ret = Apply_PS2PATCH(PS2PATCH_YFIX_offset, PS2PATCH_YFIX_FLAG_DISABLE, sizeof(PS2PATCH_YFIX_FLAG_DISABLE));
		end_loading();
		if( ret == SUCCESS) {
			PS2PATCH_YFIX = NO;
			show_msg(STR_DONE);
		} 
		else show_msg(STR_FAILED);
	} else
	if(item_is(STR_ENABLE_FMVSKIP)) {
		start_loading();
		u8 ret = Apply_PS2PATCH(PS2PATCH_FMVSKIP_offset, PS2PATCH_FMVSKIP_FLAG_ENABLE,  sizeof(PS2PATCH_FMVSKIP_FLAG_ENABLE));
		end_loading();
		if( ret == SUCCESS) {
			PS2PATCH_FMVSKIP = YES;
			show_msg(STR_DONE);
		} 
		else show_msg(STR_FAILED);
	} else
	if(item_is(STR_DISABLE_FMVSKIP)) {
		start_loading();
		u8 ret = Apply_PS2PATCH(PS2PATCH_FMVSKIP_offset, PS2PATCH_FMVSKIP_FLAG_DISABLE, sizeof(PS2PATCH_FMVSKIP_FLAG_DISABLE));
		end_loading();
		if( ret == SUCCESS) {
			PS2PATCH_FMVSKIP = NO;
			show_msg(STR_DONE);
		} 
		else show_msg(STR_FAILED);
	}
	
	init_PS2_GAME_MENU();
	
	return CONTINUE;
}

void Draw_PS2_GAME_MENU_input()
{
	if(MENU==NO) return;
	if(ICON0_creator == YES) return;
	if(txt_viewer_activ == YES) return;
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	x=DrawButton(x, y, STR_ENTER, BUTTON_CROSS);
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
}

void input_PS2_GAME_MENU()
{
	if(MENU==NO) return;
	if(ICON0_creator == YES) return;
	if(txt_viewer_activ == YES) return;
	
	get_R2speed();
	
	if(R2pad(BUTTON_UP)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	}
	
	if(R2pad(BUTTON_DOWN)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	}
	
	if(new_pad & BUTTON_CROSS) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			IN_ITEMS_VALUE = YES;
		} else {
			if( PS2_GAME_MENU_CROSS() == BREAK ) close_PS2_GAME_MENU();
		}
	} else
	if(new_pad & BUTTON_CIRCLE) {
		if(IN_ITEMS_VALUE == NO) {
			close_PS2_GAME_MENU();
			if(PS2ELF_mem != NULL) {
				free(PS2ELF_mem);
				PS2ELF_mem_size=0;
				PS2ELF_mem=NULL;
			}
		}
		else {
			init_PS2_GAME_MENU();
			IN_ITEMS_VALUE = NO;
		}
	}
}

void open_PS2_GAME_MENU()
{
	start_loading();
	
	new_MENU();
	
	Get_ID(list_game_path[position], list_game_platform[position], PS2_ID);
	
	update_PS2CRC();
	get_WS();
	
	has_LIMG = LIMG_exist(list_game_path[position]);
	
	init_PS2_GAME_MENU();
	MENU_SIDE=Use_SideMenu;
	if(MENU_SIDE) MENU_ITEMS_X=X_MAX;
	Draw_MENU_input = &Draw_PS2_GAME_MENU_input;
	input_MENU = &input_PS2_GAME_MENU;
	
	end_loading();
}

//*******************************************************
// PSP MENU
//*******************************************************

void init_PSP_GAME_MENU()
{
	int i,j;
	
	init_MENU();
	
	add_title_MENU(STR_GAME_OPTION);
	
	if( is_favorite(list_game_path[position]) == NO )
		add_item_MENU(STR_ADD_FAV, ITEM_TEXTBOX);
	else 
		add_item_MENU(STR_REM_FAV, ITEM_TEXTBOX);
	
	
	add_item_MENU(STR_RENAME, ITEM_TEXTBOX);
	
	add_item_MENU(STR_DELETE, ITEM_TEXTBOX);
	
	if(device_number != 0) {
		add_item_MENU(STR_COPY, ITEM_TEXTBOX);
		for(j=0; j<=scan_dir_number; j++) {
			for(i=0; i<=device_number; i++) {
				if(strstr(list_game_path[position], list_device[i])) continue;
				char tmp[128];
				sprintf(tmp, "/%s/%s", list_device[i], scan_dir[j]);
				add_item_value_MENU(tmp);
			}
		}
	}
	
	if(is_66600(list_game_path[position])==YES && is_usb(list_game_path[position])==NO) {
		add_item_MENU(STR_JOIN, ITEM_TEXTBOX);
	}
	
	add_item_MENU(STR_CHECK_CRC32, ITEM_TEXTBOX);
	
	add_item_MENU(STR_PROPS, ITEM_TEXTBOX);
	
}

void close_PSP_GAME_MENU()
{
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	MENU=NO;
	free_MENU();
}

u8 PSP_GAME_MENU_CROSS()
{
	if(item_is(STR_RENAME)) {
		char NewName[255];
		strcpy(NewName, list_game_title[position]);
		char *extention = GetExtention(list_game_path[position]);
		if(Get_OSK_String(STR_RENAME, NewName, 255) == SUCCESS) {
			if(NewName[0] != 0) {
				char DirPath[255];
				char NewPath[255];
				strcpy(DirPath, list_game_path[position]);
				DirPath[strrchr(DirPath, '/') - DirPath] = 0;
				sprintf(NewPath, "%s/%s%s", DirPath, NewName, extention);
				if( rename(list_game_path[position], NewPath) == 0) {
					FREE(list_game_path[position]);				
					list_game_path[position] = strcpy_malloc(NewPath);
					FREE(list_game_path[position])
					list_game_title[position] = strcpy_malloc(NewName);
				}
			}
		}
	} else 
	if(item_is(STR_ADD_FAV)) {
		if(add_favorite()==SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_REM_FAV)) {
		if(remove_favorite()==SUCCESS) show_msg(STR_DONE); 
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_CHECK_CRC32)) {
		start_loading();
		u8 ret = CheckCRC32(list_game_path[position]);
		end_loading();
		if(ret == SUCCESS) {
			char temp[255];
			strcpy(temp, list_game_path[position]);
			temp[strlen(temp)-4]=0;
			strcat(temp, "_CHECK.crc");
			open_txt_viewer(temp);
		}
	} else 
	if(item_is(STR_COPY)) {
		Copy_Game(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
	} else 
	if(item_is(STR_JOIN)) {
		char dest[255];
		strcpy(dest, list_game_path[position]);
		dest[strrchr(dest, '/') - dest] = 0;
		Copy_Game(list_game_path[position], dest);
	} else 
	if(item_is(STR_DELETE)) {
		char diag_msg[512];
		sprintf(diag_msg, "%s '%s' ?\n%s : %s\n", STR_ASK_DEL, list_game_title[position], STR_DONE, list_game_path[position]);
		if( DrawDialogYesNo(diag_msg) == YES) {
			start_loading();
			u8 ret = Delete_Game(NULL, position);
			end_loading();
			if(ret==SUCCESS) {
				show_msg(STR_DONE);
				return BREAK;
			} else show_msg(STR_FAILED);
		}
	} else 
	if(item_is(STR_PROPS)) {
		start_loading();
		gathering=YES;
		Get_Game_Size(list_game_path[position]);
		gathering=NO;
		end_loading();
			
		if(gathering_cancel==NO) Draw_GameProperties();
		else gathering_cancel=NO;
		total_size=0;
		nb_file= 0;
		nb_directory=0;
	}
	
	init_PSP_GAME_MENU();
	
	return CONTINUE;
}

void Draw_PSP_GAME_MENU_input()
{
	if(MENU==NO) return;
	if(ICON0_creator == YES) return;
	if(txt_viewer_activ == YES) return;
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	x=DrawButton(x, y, STR_ENTER, BUTTON_CROSS);
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
}

void input_PSP_GAME_MENU()
{
	if(MENU==NO) return;
	if(ICON0_creator == YES) return;
	if(txt_viewer_activ == YES) return;
	
	get_R2speed();

	if(R2pad(BUTTON_UP)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	}
	
	if(R2pad(BUTTON_DOWN)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	}
	
	if(new_pad & BUTTON_CROSS) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			IN_ITEMS_VALUE = YES;
		} else {
			if( PSP_GAME_MENU_CROSS() == BREAK ) close_PSP_GAME_MENU();
		}
	} else
	if(new_pad & BUTTON_CIRCLE) {
		if(IN_ITEMS_VALUE == NO) close_PSP_GAME_MENU();
		else {
			init_PSP_GAME_MENU();
			IN_ITEMS_VALUE = NO;
		}
	}
}

void open_PSP_GAME_MENU()
{
	start_loading();
	new_MENU();
	init_PSP_GAME_MENU();
	MENU_SIDE=Use_SideMenu;
	if(MENU_SIDE) MENU_ITEMS_X=X_MAX;
	Draw_MENU_input = &Draw_PSP_GAME_MENU_input;
	input_MENU = &input_PSP_GAME_MENU;
	end_loading();
}

//*******************************************************
// PS1 MENU
//*******************************************************

void init_PS1_GAME_MENU()
{
	int i,j;
	
	init_MENU();
	
	add_title_MENU(STR_GAME_OPTION);
	
	if( is_favorite(list_game_path[position]) == NO )
		add_item_MENU(STR_ADD_FAV, ITEM_TEXTBOX);
	else 
		add_item_MENU(STR_REM_FAV, ITEM_TEXTBOX);
	
	
	add_item_MENU(STR_RENAME, ITEM_TEXTBOX);
	
	add_item_MENU(STR_DELETE, ITEM_TEXTBOX);
	
	if(device_number != 0) {
		add_item_MENU(STR_COPY, ITEM_TEXTBOX);
		for(j=0; j<=scan_dir_number; j++) {
			for(i=0; i<=device_number; i++) {
				if(strstr(list_game_path[position], list_device[i])) continue;
				char tmp[128];
				sprintf(tmp, "/%s/%s", list_device[i], scan_dir[j]);
				add_item_value_MENU(tmp);
			}
		}
	}
	
	if(is_66600(list_game_path[position])==YES && is_usb(list_game_path[position])==NO) {
		add_item_MENU(STR_JOIN, ITEM_TEXTBOX);
	}
	
	if(COVER_offset[position] != 0) {
		add_item_MENU(STR_CREATE_ICON0, ITEM_TEXTBOX);
	}
	
	add_item_MENU(STR_CHECK_MD5, ITEM_TEXTBOX);
	
	add_item_MENU(STR_PROPS, ITEM_TEXTBOX);
	
}

void close_PS1_GAME_MENU()
{
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	MENU=NO;
	free_MENU();
}

u8 PS1_GAME_MENU_CROSS()
{
	if(item_is(STR_RENAME)) {
		char NewName[255];
		strcpy(NewName, list_game_title[position]);
		char *extention = GetExtention(list_game_path[position]);
		if(Get_OSK_String(STR_RENAME, NewName, 255) == SUCCESS) {
			if(NewName[0] != 0) {
				char DirPath[255];
				char NewPath[255];
				strcpy(DirPath, list_game_path[position]);
				DirPath[strrchr(DirPath, '/') - DirPath] = 0;
				sprintf(NewPath, "%s/%s%s", DirPath, NewName, extention);
				if( rename(list_game_path[position], NewPath) == 0) {
					FREE(list_game_path[position]);				
					list_game_path[position] = strcpy_malloc(NewPath);
					FREE(list_game_path[position])
					list_game_title[position] = strcpy_malloc(NewName);
				}
			}
		}
	} else 
	if(item_is(STR_CREATE_ICON0)) {
		open_ICON0_creator();
	} else 
	if(item_is(STR_ADD_FAV)) {
		if(add_favorite()==SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_REM_FAV)) {
		if(remove_favorite()==SUCCESS) show_msg(STR_DONE); 
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_CHECK_MD5)) {
		start_loading();
		u8 ret = CheckMD5(list_game_path[position]);
		end_loading();
		if(ret == SUCCESS) {
			char temp[255];
			strcpy(temp, list_game_path[position]);
			temp[strlen(temp)-4]=0;
			strcat(temp, "_CHECK.md5");
			open_txt_viewer(temp);
		}
	} else 
	if(item_is(STR_COPY)) {
		Copy_Game(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
	} else 
	if(item_is(STR_JOIN)) {
		char dest[255];
		strcpy(dest, list_game_path[position]);
		dest[strrchr(dest, '/') - dest] = 0;
		Copy_Game(list_game_path[position], dest);
	} else 
	if(item_is(STR_DELETE)) {
		char diag_msg[512];
		sprintf(diag_msg, "%s '%s' ?\n%s : %s\n", STR_ASK_DEL, list_game_title[position], STR_PATH, list_game_path[position]);
		if( DrawDialogYesNo(diag_msg) == YES) {
			start_loading();
			u8 ret = Delete_Game(NULL, position);
			end_loading();
			if(ret==SUCCESS) {
				show_msg(STR_DONE);
				return BREAK;
			} else show_msg(STR_FAILED);
		}
	} else 
	if(item_is(STR_PROPS)) {
		start_loading();
		gathering=YES;
		Get_Game_Size(list_game_path[position]);
		gathering=NO;
		end_loading();
			
		if(gathering_cancel==NO) Draw_GameProperties();
		else gathering_cancel=NO;
		total_size=0;
		nb_file= 0;
		nb_directory=0;
	}
	
	init_PS1_GAME_MENU();
	
	return CONTINUE;
}

void Draw_PS1_GAME_MENU_input()
{
	if(MENU==NO) return;
	if(ICON0_creator == YES) return;
	if(txt_viewer_activ == YES) return;
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	x=DrawButton(x, y, STR_ENTER, BUTTON_CROSS);
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
}

void input_PS1_GAME_MENU()
{
	if(MENU==NO) return;
	if(ICON0_creator == YES) return;
	if(txt_viewer_activ == YES) return;
	
	get_R2speed();

	if(R2pad(BUTTON_UP)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	}
	
	if(R2pad(BUTTON_DOWN)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	}
	
	if(new_pad & BUTTON_CROSS) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			IN_ITEMS_VALUE = YES;
		} else {
			if( PS1_GAME_MENU_CROSS() == BREAK ) close_PS1_GAME_MENU();
		}
	} else
	if(new_pad & BUTTON_CIRCLE) {
		if(IN_ITEMS_VALUE == NO) close_PS1_GAME_MENU();
		else {
			init_PS1_GAME_MENU();
			IN_ITEMS_VALUE = NO;
		}
	}
}

void open_PS1_GAME_MENU()
{
	start_loading();
	new_MENU();
	init_PS1_GAME_MENU();
	MENU_SIDE=Use_SideMenu;
	if(MENU_SIDE) MENU_ITEMS_X=X_MAX;
	Draw_MENU_input = &Draw_PS1_GAME_MENU_input;
	input_MENU = &input_PS1_GAME_MENU;
	end_loading();
}

//*******************************************************
// PS3 MENU
//*******************************************************

void peek_IDPS()
{
	u8 i;
	for(i=0; i<0x10; i++) {
		IDPS[i]=lv2peek8(OFFSET_2_IDPS + i);
	}
}

void poke_IDPS()
{
	u8 i;
	for(i=0; i<0x10; i++) {
		lv2poke8(OFFSET_1_IDPS + i, IDPS[i]);
		lv2poke8(OFFSET_2_IDPS + i, IDPS[i]);
	}
}

void LoadEID5_IDPS()
{
	u32 source, read;
	u64 offset;
    u64 buffer[ 0x40 ];
    int ret = 1;
    
    ret = open_device( 0x100000000000004ull, &source );
    
    if( ret != 0 ) {
		offset = 0x20D; 
		close_device( source );
		open_device( 0x100000000000001ull, &source );
	}
	else offset = 0x181; 
   
    read_device( source, offset, 0x1, buffer, &read, 0x22 );
	close_device( source );
	
	memcpy(IDPS, &buffer[ 0x3a ], 0x10);
}

u8 CHOOSE_IDPS_position=0;

void Draw_CHOOSE_IDPS_menu()
{
	int x = 70;
	int y = 512/2;
	int x1=x;
	
	FontSize(20);
	
	u8 i;
	for(i=0; i<0x10; i++) x1=DrawString(x1, -50, "FF");
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO);
	Draw_Box(50, y-15 , 0, 10, x1+20+20, 15+25+10+15, GREY, NO);
	
	
	FontColor(COLOR_3);
	SetFontZ(0);
	x = DrawString(x,y, "00000001008");

	if(CHOOSE_IDPS_position==0) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x, y, "%X", IDPS[0x5] - (IDPS[5] >> 4)*0x10 );
	if(CHOOSE_IDPS_position==0) {
		if(IDPS[0x5] - (IDPS[0x5] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0x5] - (IDPS[0x5] >> 4)*0x10 > 0x2) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	FontColor(COLOR_3);
	x = DrawString(x,y, "000");
	
	//0x7
	if(CHOOSE_IDPS_position==1) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0x7] - (IDPS[0x7] >> 4)*0x10);
	if(CHOOSE_IDPS_position==1) {
		if(IDPS[0x7]<0x0E) DrawUp((x+x1)/2, y);
		if(IDPS[0x7]>0x01) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0x8
	if(CHOOSE_IDPS_position==2) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0x8] >> 4));
	if(CHOOSE_IDPS_position==2) {
		if((IDPS[0x8] >> 4) == 0x0 || (IDPS[0x8] >> 4) == 0x1) DrawUp((x+x1)/2, y);
		if((IDPS[0x8] >> 4) == 0x1 || (IDPS[0x8] >> 4) == 0xF) DrawDown((x+x1)/2, y+25*0.85);
	}
	if(CHOOSE_IDPS_position==3) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0x8] - (IDPS[0x8] >> 4)*0x10);
	if(CHOOSE_IDPS_position==3) {
		if(IDPS[0x8] - (IDPS[0x8] >> 4)*0x10 == 0x0) DrawUp((x+x1)/2, y); else
		if(IDPS[0x8] - (IDPS[0x8] >> 4)*0x10 == 0x4) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0x9
	if(CHOOSE_IDPS_position==4) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0x9] >> 4));
	if(CHOOSE_IDPS_position==4) {
		if((IDPS[0x9] >> 4) < 0x3) DrawUp((x+x1)/2, y);
		if((IDPS[0x9] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	if(CHOOSE_IDPS_position==5) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0x9] - (IDPS[0x9] >> 4)*0x10);
	if(CHOOSE_IDPS_position==5) {
		if(IDPS[0x9] - (IDPS[0x9] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0x9] - (IDPS[0x9] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xA
	if(CHOOSE_IDPS_position==6) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xA] >> 4));
	if(CHOOSE_IDPS_position==6) {
		if((IDPS[0xA] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xA] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==7) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xA] - (IDPS[0xA] >> 4)*0x10);
	if(CHOOSE_IDPS_position==7) {
		if(IDPS[0xA] - (IDPS[0xA] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xA] - (IDPS[0xA] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xB
	if(CHOOSE_IDPS_position==8) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xB] >> 4));
	if(CHOOSE_IDPS_position==8) {
		if((IDPS[0xB] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xB] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==9) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xB] - (IDPS[0xB] >> 4)*0x10);
	if(CHOOSE_IDPS_position==9) {
		if(IDPS[0xB] - (IDPS[0xB] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xB] - (IDPS[0xB] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xC
	if(CHOOSE_IDPS_position==10) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xC] >> 4));
	if(CHOOSE_IDPS_position==10) {
		if((IDPS[0xC] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xC] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==11) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xC] - (IDPS[0xC] >> 4)*0x10);
	if(CHOOSE_IDPS_position==11) {
		if(IDPS[0xC] - (IDPS[0xC] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xC] - (IDPS[0xC] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xD
	if(CHOOSE_IDPS_position==12) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xD] >> 4));
	if(CHOOSE_IDPS_position==12) {
		if((IDPS[0xD] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xD] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==13) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xD] - (IDPS[0xD] >> 4)*0x10);
	if(CHOOSE_IDPS_position==13) {
		if(IDPS[0xD] - (IDPS[0xD] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xD] - (IDPS[0xD] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xE
	if(CHOOSE_IDPS_position==14) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xE] >> 4));
	if(CHOOSE_IDPS_position==14) {
		if((IDPS[0xE] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xE] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==15) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xE] - (IDPS[0xE] >> 4)*0x10);
	if(CHOOSE_IDPS_position==15) {
		if(IDPS[0xE] - (IDPS[0xE] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xE] - (IDPS[0xE] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xF
	if(CHOOSE_IDPS_position==16) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xF] >> 4));
	if(CHOOSE_IDPS_position==16) {
		if((IDPS[0xF] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xF] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==17) FontColor(COLOR_2); else FontColor(COLOR_1);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xF] - (IDPS[0xF] >> 4)*0x10);
	if(CHOOSE_IDPS_position==17) {
		if(IDPS[0xF] - (IDPS[0xF] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xF] - (IDPS[0xF] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	x=70; y+=25;
	FontSize(10);
	FontColor(COLOR_3);
	x=DrawString(x,y, "Target ID : ");
	
	if((IDPS[5] >> 4) == 0) x=DrawString(x,y, "PSP "); else
	if((IDPS[5] >> 4) == 8) x=DrawString(x,y, "PS3 ");
	
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0x2) DrawString(x,y, "DEX"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0x3) DrawString(x,y, "JAPAN"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0x4) DrawString(x,y, "USA"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0x5) DrawString(x,y, "EUROPE"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0x6) DrawString(x,y, "KOREA"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0x7) DrawString(x,y, "UK"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0x8) DrawString(x,y, "MEXICO"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0x9) DrawString(x,y, "AUSTRALIA"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0xA) DrawString(x,y, "SOUTH ASIA"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0xB) DrawString(x,y, "TAIWAN"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0xC) DrawString(x,y, "RUSSIA"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0xD) DrawString(x,y, "CHINA"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0xE) DrawString(x,y, "HONG KONG"); else
	if(IDPS[5] - (IDPS[5] >> 4)*0x10 == 0xF) DrawString(x,y, "BRAZIL");
}

u8 input_CHOOSE_IDPS()
{
	if(new_pad & BUTTON_DOWN) {
	
		if(CHOOSE_IDPS_position==0) {
			if(IDPS[0x5] - (IDPS[0x5] >> 4)*0x10 > 0x2) IDPS[0x5]--;
		} else
		if(CHOOSE_IDPS_position==1) {
			if(IDPS[0x7]>0x01) IDPS[0x7]--;
		} else
		if(CHOOSE_IDPS_position==2) {
			if((IDPS[0x8] >> 4) == 0x1) IDPS[0x8] = IDPS[0x8] -(IDPS[0x8] >> 4)*0x10;
			else if((IDPS[0x8] >> 4) == 0xF) IDPS[0x8] = IDPS[0x8] - (IDPS[0x8] >> 4)*0x10 + 0x10;
		} else
		if(CHOOSE_IDPS_position==3) {
			if(IDPS[0x8] - (IDPS[0x8] >> 4)*0x10 == 0x4) IDPS[0x8]= (IDPS[0x8] >> 4)*0x10;
		} else
		if(CHOOSE_IDPS_position==4) {
			if((IDPS[0x9] >> 4) > 0x0) IDPS[0x9]= IDPS[0x9] - 0x10;
		} else
		if(CHOOSE_IDPS_position==5) {
			if(IDPS[0x9] - (IDPS[0x9] >> 4)*0x10 > 0x0) IDPS[0x9]--;
		} else
		if(CHOOSE_IDPS_position==6) {
			if((IDPS[0xA] >> 4) > 0x0) IDPS[0xA] = IDPS[0xA] - 0x10;
		} else
		if(CHOOSE_IDPS_position==7) {
			if(IDPS[0xA] - (IDPS[0xA] >> 4)*0x10 > 0x0) IDPS[0xA]--;
		}  else
		if(CHOOSE_IDPS_position==8) {
			if((IDPS[0xB] >> 4) > 0x0) IDPS[0xB] = IDPS[0xB] - 0x10;
		} else
		if(CHOOSE_IDPS_position==9) {
			if(IDPS[0xB] - (IDPS[0xB] >> 4)*0x10 > 0x0) IDPS[0xB]--;
		}  else
		if(CHOOSE_IDPS_position==10) {
			if((IDPS[0xC] >> 4) > 0x0) IDPS[0xC] = IDPS[0xC] - 0x10;
		} else
		if(CHOOSE_IDPS_position==11) {
			if(IDPS[0xC] - (IDPS[0xC] >> 4)*0x10 > 0x0) IDPS[0xC]--;
		} else
		if(CHOOSE_IDPS_position==12) {
			if((IDPS[0xD] >> 4) > 0x0) IDPS[0xD] = IDPS[0xD] - 0x10;
		} else
		if(CHOOSE_IDPS_position==13) {
			if(IDPS[0xD] - (IDPS[0xD] >> 4)*0x10 > 0x0) IDPS[0xD]--;
		}  else
		if(CHOOSE_IDPS_position==14) {
			if((IDPS[0xE] >> 4) > 0x0) IDPS[0xE] = IDPS[0xE] - 0x10;
		} else
		if(CHOOSE_IDPS_position==15) {
			if(IDPS[0xE] - (IDPS[0xE] >> 4)*0x10 > 0x0) IDPS[0xE]--;
		}  else
		if(CHOOSE_IDPS_position==16) {
			if((IDPS[0xF] >> 4) > 0x0) IDPS[0xF] = IDPS[0xF] - 0x10;
		} else
		if(CHOOSE_IDPS_position==17) {
			if(IDPS[0xF] - (IDPS[0xF] >> 4)*0x10 > 0x0) IDPS[0xF]--;
		}
	}
	
	if(new_pad & BUTTON_UP) {
		if(CHOOSE_IDPS_position==0) {
			if(IDPS[0x5] - (IDPS[0x5] >> 4)*0x10 < 0xF)	IDPS[0x5]++;
		} else
		if(CHOOSE_IDPS_position==1) {
			if(IDPS[0x7]<0x0E) IDPS[0x7]++;
		} else
		if(CHOOSE_IDPS_position==2) {
			if((IDPS[0x8] >> 4) == 0x1) IDPS[0x8] = IDPS[0x8] -(IDPS[0x8] >> 4)*0x10 + 0xF0;
			else if((IDPS[0x8] >> 4) == 0x0) IDPS[0x8] = IDPS[0x8] - (IDPS[0x8] >> 4)*0x10 + 0x10;
		} else
		if(CHOOSE_IDPS_position==3) {
			if(IDPS[0x8] - (IDPS[0x8] >> 4)*0x10 == 0x0) IDPS[0x8]= (IDPS[0x8] >> 4)*0x10 + 0x4;
		} else
		if(CHOOSE_IDPS_position==4) {
			if((IDPS[0x9] >> 4) < 0x3) IDPS[0x9]= IDPS[0x9] + 0x10;
		} else
		if(CHOOSE_IDPS_position==5) {
			if(IDPS[0x9] - (IDPS[0x9] >> 4)*0x10 < 0xF) IDPS[0x9]++;
		} else
		if(CHOOSE_IDPS_position==6) {
			if((IDPS[0xA] >> 4) < 0xF) IDPS[0xA] = IDPS[0xA] + 0x10;
		} else
		if(CHOOSE_IDPS_position==7) {
			if(IDPS[0xA] - (IDPS[0xA] >> 4)*0x10 < 0xF) IDPS[0xA]++;
		}  else
		if(CHOOSE_IDPS_position==8) {
			if((IDPS[0xB] >> 4) < 0xF) IDPS[0xB] = IDPS[0xB] + 0x10;
		} else
		if(CHOOSE_IDPS_position==9) {
			if(IDPS[0xB] - (IDPS[0xB] >> 4)*0x10 < 0xF) IDPS[0xB]++;
		}  else
		if(CHOOSE_IDPS_position==10) {
			if((IDPS[0xC] >> 4) < 0xF) IDPS[0xC] = IDPS[0xC] + 0x10;
		} else
		if(CHOOSE_IDPS_position==11) {
			if(IDPS[0xC] - (IDPS[0xC] >> 4)*0x10 < 0xF) IDPS[0xC]++;
		}  else
		if(CHOOSE_IDPS_position==12) {
			if((IDPS[0xD] >> 4) < 0xF) IDPS[0xD] = IDPS[0xD] + 0x10;
		} else
		if(CHOOSE_IDPS_position==13) {
			if(IDPS[0xD] - (IDPS[0xD] >> 4)*0x10 < 0xF) IDPS[0xD]++;
		}  else
		if(CHOOSE_IDPS_position==14) {
			if((IDPS[0xE] >> 4) < 0xF) IDPS[0xE] = IDPS[0xE] + 0x10;
		} else
		if(CHOOSE_IDPS_position==15) {
			if(IDPS[0xE] - (IDPS[0xE] >> 4)*0x10 < 0xF) IDPS[0xE]++;
		}  else
		if(CHOOSE_IDPS_position==16) {
			if((IDPS[0xF] >> 4) < 0xF) IDPS[0xF] = IDPS[0xF] + 0x10;
		} else
		if(CHOOSE_IDPS_position==17) {
			if(IDPS[0xF] - (IDPS[0xF] >> 4)*0x10 < 0xF) IDPS[0xF]++;
		}
	}
	
	if(new_pad & BUTTON_RIGHT) {
		if(0 <= CHOOSE_IDPS_position && CHOOSE_IDPS_position < 17) {
			CHOOSE_IDPS_position++;
		}
	}
	
	if(new_pad & BUTTON_LEFT) {
		if(0 < CHOOSE_IDPS_position && CHOOSE_IDPS_position <= 17) {
			CHOOSE_IDPS_position--;
		}
	}
	
	if(new_pad & BUTTON_SQUARE) {
		peek_IDPS();
	}
	
	if(new_pad & BUTTON_TRIANGLE) {
		LoadEID5_IDPS();
	}
	
	if(new_pad & BUTTON_CIRCLE) {
		return BREAK;
	}
	
	return CONTINUE;
}

void Draw_CHOOSE_IDPS_input()
{
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	x=DrawButton(x, y, STR_CHANGE_VALUE, BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT);
	x=DrawButton(x, y, STR_LOAD_IDPS_LV2, BUTTON_SQUARE);
	x=DrawButton(x, y, STR_LOAD_IDPS_EID5, BUTTON_TRIANGLE);
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
}

void Draw_CHOOSE_IDPS()
{
	u8 LoopBreak=1;
	while(LoopBreak)
	{
		cls();
		Draw_scene();
		
		Draw_CHOOSE_IDPS_menu();
		Draw_CHOOSE_IDPS_input();
		
		tiny3d_Flip();
		ScreenShot();
		
		ps3pad_read();
				
		if(input_CHOOSE_IDPS() == BREAK) {
			LoopBreak=0;
			break;
		}
	}
	old_pad = 0;
	new_pad = 0;
}

void close_PS3_GAME_MENU()
{
	write_game_setting(list_game_id[position]);
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	MENU=NO;
	free_MENU();
}

void init_PS3_GAME_MENU()
{
	int i, j;
	
	init_MENU();
	
	add_title_MENU(STR_GAME_SETTINGS);
	
	add_item_MENU(STR_DIRECT_BOOT, ITEM_TEXTBOX);
	add_item_value_MENU(STR_NO);
	add_item_value_MENU(STR_YES);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = direct_boot;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	if(PEEKnPOKE) {

		add_item_MENU(STR_CLEAN_SYSCALL, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = clean_syscall;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU(STR_CHANGE_IDPS, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = change_IDPS;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	}
	
	add_item_MENU(STR_EXT_GAME_DATA, ITEM_TEXTBOX);
	add_item_value_MENU(STR_NO);
	add_item_value_MENU(STR_YES);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = ext_game_data;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU(STR_PAYLOAD, ITEM_TEXTBOX);
	if(cobra) add_item_value_MENU("Cobra");
	else add_item_value_MENU("Mamba");
	if(PEEKnPOKE) {
		if(iso == NO) {	
			add_item_value_MENU("Iris");
			add_item_value_MENU("multiMAN");
		}
	}
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = payload;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	if(iso == NO) {	
		if(cobra==YES && usb==YES) {
			add_item_MENU(STR_PRIM_USB, ITEM_TEXTBOX);
			add_item_value_MENU(STR_NO);
			add_item_value_MENU(STR_YES);
			ITEMS_VALUE_POSITION[ITEMS_NUMBER] = prim_USB;
			ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		}
		
		add_item_MENU(STR_BDEMU, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NONE);
		add_item_value_MENU("BDMIRROR");
		add_item_value_MENU("BDEMU");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = emu;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		if(emu==BDEMU) {
			add_item_MENU(STR_PATCH_LIBFS, ITEM_TEXTBOX);
			add_item_value_MENU("reactPSN");
			add_item_value_MENU("Iris");
			add_item_value_MENU("multiMAN");
			ITEMS_VALUE_POSITION[ITEMS_NUMBER] = libfs_from;
			ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		}
	}
	
	add_item_MENU(STR_MOUNT_APPHOME, ITEM_TEXTBOX);
	add_item_value_MENU(STR_NO);
	add_item_value_MENU(STR_YES);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = mount_app_home;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	if(mount_app_home==YES) {
		add_item_MENU(STR_PATCH_EXP, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = use_ex_plug;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	}
	
	add_title_MENU(STR_GAME_OPTION);
		
	if(is_favorite(list_game_path[position]) == NO) {
		add_item_MENU(STR_ADD_FAV, ITEM_TEXTBOX);
	} else {
		add_item_MENU(STR_REM_FAV, ITEM_TEXTBOX);
	}
	
	add_item_MENU(STR_RENAME, ITEM_TEXTBOX);
	
	add_item_MENU(STR_DELETE, ITEM_TEXTBOX);
	
	if(device_number != 0) {
		add_item_MENU(STR_COPY, ITEM_TEXTBOX);
		for(j=0; j<=scan_dir_number; j++) {
			for(i=0; i<=device_number; i++) {
				if(strstr(list_game_path[position], list_device[i])) continue;
				char tmp[255];
				sprintf(tmp, "/%s/%s", list_device[i], scan_dir[j]);
				add_item_value_MENU(tmp);
			}
		}
	}
	
	if(is_66600(list_game_path[position])==YES && is_usb(list_game_path[position])==NO) {
		add_item_MENU(STR_JOIN, ITEM_TEXTBOX);
	}
	
	add_item_MENU(STR_MAKE_SHTCUT_PKG, ITEM_TEXTBOX);
	
	add_item_MENU(STR_PATCH_EBOOT, ITEM_TEXTBOX);
	
	if(iso==NO) {
		if(is_resigned_GAME(list_game_path[position])==NO) {
			add_item_MENU(STR_RESIGN, ITEM_TEXTBOX);
		} else {
			add_item_MENU(STR_RESTORE, ITEM_TEXTBOX);
		}
	}
	
	if(iso) {
		add_item_MENU(STR_EXTRACT_ISO, ITEM_TEXTBOX);
	} else {
		add_item_MENU(STR_CONVERT_ISO, ITEM_TEXTBOX);
	}
	for(j=0; j<=scan_dir_number; j++) {
		for(i=0; i<=device_number; i++) {
			char tmp[255];
			sprintf(tmp, "/%s/%s", list_device[i], scan_dir[j]);
			add_item_value_MENU(tmp);
		}
	}
	
	if(iso==NO) {
		add_item_MENU(STR_FIX_PERMS, ITEM_TEXTBOX);
	}
	
	add_item_MENU(STR_CHECK_IRD, ITEM_TEXTBOX);
	add_item_MENU(STR_DL_UPDATE, ITEM_TEXTBOX);
	
	add_item_MENU(STR_PROPS, ITEM_TEXTBOX);
	
}

void PS3_GAME_MENU_UPDATE()
{
	if(item_is(STR_DIRECT_BOOT)) {
		direct_boot = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is(STR_CLEAN_SYSCALL)) {
		clean_syscall = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(item_is(STR_CHANGE_IDPS)) {
		change_IDPS = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is(STR_PAYLOAD)) {
		payload = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is(STR_EXT_GAME_DATA)) {
		ext_game_data = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is(STR_PRIM_USB)) {
		prim_USB = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is(STR_BDEMU)) {
		emu = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is(STR_PATCH_LIBFS)) {
		libfs_from = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(item_is(STR_MOUNT_APPHOME)) {
		mount_app_home = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is(STR_PATCH_EXP)) {
		use_ex_plug = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	}
	
	init_PS3_GAME_MENU();
}

u8 PS3_GAME_MENU_CROSS()
{
	if(item_is(STR_CHANGE_IDPS)) {
		Draw_CHOOSE_IDPS();
	} else 
	if(item_is(STR_RENAME)) {
		char tmpName[128];
		strcpy(tmpName, list_game_title[position]);
		if(Get_OSK_String(STR_RENAME, tmpName, 128) == SUCCESS) {
			if(tmpName[0]!=0) {
				if(SetParamSFO("TITLE", tmpName, position, NULL)==SUCCESS) {
					FREE(list_game_title[position]);
					list_game_title[position] = strcpy_malloc(tmpName);
					show_msg(STR_DONE);
				}
			}
		}
	} else 
	if(item_is(STR_ADD_FAV)) {
		if(add_favorite()==SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_REM_FAV)) {
		if(remove_favorite()==SUCCESS) show_msg(STR_DONE); 
		else show_msg(STR_FAILED);
	} else 
	if(item_is(STR_MAKE_SHTCUT_PKG)) {
		
		char mk_pkg_ID[10];
		if( GetParamSFO("TITLE_ID", mk_pkg_ID, position, NULL) == SUCCESS ) {
			mk_pkg_ID[0]='N';
			mk_pkg_ID[1]='P'; 
			mk_pkg_ID[3]='B';
			mk_pkg_ID[4]='4';
		} else strcpy(mk_pkg_ID, "NPEB40000");
		if(Get_OSK_String("Title ID", mk_pkg_ID, 10) == SUCCESS) {
			if(mk_pkg_ID[0]!=0) {
				u8 ret;
				start_loading();
				ret=make_launcher_pkg(mk_pkg_ID);
				end_loading();
				if(ret == SUCCESS) show_msg(STR_DONE);
				else show_msg(STR_FAILED);
			}
		}
	
	} else 
	if(item_is(STR_DELETE)) {
		char diag_msg[512];
		sprintf(diag_msg, "%s %s ?\n%s : %s", STR_ASK_DEL, list_game_title[position], STR_PATH, list_game_path[position]);
		if( DrawDialogYesNo(diag_msg) == YES) {
			start_loading();
			u8 ret = Delete_Game(NULL, position);
			end_loading();
			if(ret==SUCCESS) {
				show_msg(STR_DONE);
				return BREAK;
			} else show_msg(STR_FAILED);
		}
	} else 
	if(item_is(STR_COPY)) {
		Copy_Game(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
	} else
	if(item_is(STR_JOIN)) {
		char dest[255];
		strcpy(dest, list_game_path[position]);
		dest[strrchr(dest, '/') - dest] = 0;
		Copy_Game(list_game_path[position], dest);
	} else 
	if(item_is(STR_PATCH_EBOOT)) {
		start_loading();
		u8 ret;
		if(iso==NO) ret = patch_EBOOT(position);
		else 		ret = patchps3iso(list_game_path[position]);
		if(ret == SUCCESS) show_msg(STR_DONE); 
		else show_msg(STR_FAILED);
		end_loading();
	} else 
	if(item_is(STR_RESIGN)) {
		start_loading();
		if(re_sign_GAME(list_game_path[position]) == SUCCESS) show_msg(STR_DONE); else
		show_msg(STR_FAILED); 
		end_loading();
	} else 
	if(item_is(STR_RESTORE)) {
		start_loading();
		if(restore_GAME(list_game_path[position]) == SUCCESS) show_msg(STR_DONE); else
		show_msg(STR_FAILED); 
		end_loading();
	} else 
	if(item_is(STR_EXTRACT_ISO)) {
		start_loading();
		print_head("Converting...");
		u8 ret;
		if(is_ntfs(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]])==YES
		|| strstr(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/dev_hdd0")) 
			ret = extractps3iso(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], FULL); 
		else 
			ret = extractps3iso(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], SPLIT);	
		if(ret==SUCCESS) {
			char ExtGame[512];
						
			sprintf(ExtGame, "%s%s", ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], strrchr(list_game_path[position], '/'));

			int l= strlen(ExtGame);
			if(!strcmp(&ExtGame[l - 2], ".0")) ExtGame[l - 6] = 0; else ExtGame[l - 4] = 0;
			
			add_GAMELIST(ExtGame);
			
			sort_GAMELIST();
		
			read_fav();
			
			start_Load_GamePIC();
			
			show_msg(STR_DONE);
		} 
		else 
			show_msg(STR_FAILED);
			
		end_loading();
	} else 
	if(item_is(STR_CONVERT_ISO)) {
		start_loading();
		print_head("Converting...");
		u8 ret;
		if(is_ntfs(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]])==YES
		|| strstr(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/dev_hdd0")) 
			ret = makeps3iso(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], FULL);
		else 
			ret = makeps3iso(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], SPLIT);
		
		if(ret==SUCCESS) {
			char IsoGame[512];
						
			if(is_ntfs(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]])==YES
			|| strstr(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/dev_hdd0")) {
				sprintf(IsoGame, "%s%s.iso", ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], strrchr(list_game_path[position], '/'));
			} else {
				sprintf(IsoGame, "%s%s.iso.0", ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], strrchr(list_game_path[position], '/'));
			
			}
			
			add_GAMELIST(IsoGame);
			
			sort_GAMELIST();
		
			read_fav();
			
			start_Load_GamePIC();
			
			show_msg(STR_DONE);
		} 
		else 
			show_msg(STR_FAILED);
			
		end_loading();
	} else 
	if(item_is(STR_FIX_PERMS)) {
		start_loading();
		print_head("Fixing permissions...");
		if(SetPerms(list_game_path[position]) == SUCCESS) show_msg(STR_DONE);
		else show_msg(STR_FAILED);
		end_loading();
	} else 
	if(item_is(STR_CHECK_IRD)) {
		u8 ret;
		start_loading();
		ret = CheckIRD(list_game_path[position]);
		end_loading();
		
		if( ret == SUCCESS ) {
			char temp[128];
			if(iso) sprintf(temp, "%s.MD5_check.txt", list_game_path[position]);
			else sprintf(temp, "%s/MD5_check.txt", list_game_path[position]);
			open_txt_viewer(temp);
		}
		else {
			show_msg(STR_FAILED);
			end_loading();
		}
	} else 
	if(item_is(STR_DL_UPDATE)) {
		get_game_update(position);
	} else 
	if(item_is(STR_PROPS)) {
		start_loading();
		gathering=YES;
		Get_Game_Size(list_game_path[position]);
		gathering=NO;
		end_loading();
			
		if(gathering_cancel==NO) Draw_GameProperties();
		else gathering_cancel=NO;
		total_size=0;
		nb_file= 0;
		nb_directory=0;
	}
	
	return CONTINUE;
}

void PS3_GAME_MENU_SQUARE()
{
	
}

void PS3_GAME_MENU_TRIANGLE()
{
	
}

void input_PS3_GAME_MENU()
{
	if(MENU==NO) return;
	if(ICON0_creator == YES) return;
	if(txt_viewer_activ == YES) return;
	
	get_R2speed();

	if(R2pad(BUTTON_UP)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	}
	
	if(R2pad(BUTTON_DOWN)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	}
	
	PS3_GAME_MENU_UPDATE();
	
	if(new_pad & BUTTON_CROSS) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			IN_ITEMS_VALUE = YES;
		} else {
			if(PS3_GAME_MENU_CROSS() == BREAK) close_PS3_GAME_MENU();
		}
	} else
	if(new_pad & BUTTON_SQUARE) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_SHOW[ITEMS_POSITION] == YES) {
				if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
				else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
			}
		} else {
			PS3_GAME_MENU_SQUARE(); 
		}
	} else
	if(new_pad & BUTTON_TRIANGLE) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_SHOW[ITEMS_POSITION] == YES) {
				if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
				else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
			}
		} else {
			PS3_GAME_MENU_TRIANGLE(); 
		}
	} else
	if(new_pad & BUTTON_CIRCLE) {
		if(IN_ITEMS_VALUE == NO) close_PS3_GAME_MENU();
		else {
			init_PS3_GAME_MENU();
			IN_ITEMS_VALUE = NO;
		}
	}
}

void Draw_PS3_GAME_MENU_input()
{
	if(MENU==NO) return;
	if(ICON0_creator == YES) return;
	if(txt_viewer_activ == YES) return;
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	if(IN_ITEMS_VALUE == YES) {
		x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
	} else {
		x=DrawButton(x, y, STR_ENTER, BUTTON_CROSS);
		x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
		if(ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_SHOW[ITEMS_POSITION] == YES) {
				x=DrawButton(x, y, STR_CHANGE, BUTTON_SQUARE | BUTTON_TRIANGLE);
			}
		}	
	}

}

void open_PS3_GAME_MENU()
{
	start_loading();
	new_MENU();
	read_game_setting(list_game_id[position]);
	init_PS3_GAME_MENU();
	MENU_SIDE=Use_SideMenu;
	if(MENU_SIDE) MENU_ITEMS_X=X_MAX;
	Draw_MENU_input = &Draw_PS3_GAME_MENU_input;
	input_MENU = &input_PS3_GAME_MENU;
	end_loading();
}

void open_GameMenu()
{
	
	if(list_game_platform[position] == _JB_PS3 || list_game_platform[position] == _ISO_PS3) {
		open_PS3_GAME_MENU();
	} else
	if(list_game_platform[position] == _JB_PS2 || list_game_platform[position] == _ISO_PS2) {
		open_PS2_GAME_MENU();
	} else
	if(list_game_platform[position] == _JB_PS1 || list_game_platform[position] == _ISO_PS1) {
		open_PS1_GAME_MENU();
	} else
	if(list_game_platform[position] == _JB_PSP || list_game_platform[position] == _ISO_PSP) {
		open_PSP_GAME_MENU();
	}

}

//*******************************************************
// SETTINGS MENU
//*******************************************************

u8 BOOTFILE_ITEM;

void close_PLUGINS_MANAGER()
{
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	free_MENU();
	open_SETTINGS();
}

void init_PLUGINS_MANAGER()
{
	init_MENU();
	
	char temp[128];
		
	if(cobra || mamba) {
		add_title_MENU(STR_PLUGIN_MONITOR);
		
		unsigned int i;
		
		char plugin_name[30];
		char plugin_path[128];
		
		for(i=1; i<7; i++) {
			memset(plugin_name, 0, sizeof(plugin_name));
			memset(plugin_path, 0, sizeof(plugin_path));
			memset(temp, 0, sizeof(temp));
			
			ps3mapi_get_vsh_plugin_info(i, plugin_name, plugin_path);

			if(strlen(plugin_name)==0) {
				sprintf(temp, "[ %d ] : %s", i, STR_UNUSED);
			} else {
				sprintf(temp, "[ %d ] : %s | %s", i, plugin_name, plugin_path);
			}

			add_item_MENU(temp, ITEM_TEXTBOX);
		}
	}
	
	add_title_MENU(STR_PLUGIN_MANAGER);
	add_item_MENU(STR_BOOT_FILE, ITEM_TEXTBOX);
	if(path_info("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt") == _FILE) {
		add_item_value_MENU("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt");
	}
	if(path_info("/dev_hdd0/prx_plugins.txt") == _FILE) {
		add_item_value_MENU("/dev_hdd0/prx_plugins.txt");
	}
	if(path_info("/dev_hdd0/mamba_plugins.txt") == _FILE) {
		add_item_value_MENU("/dev_hdd0/mamba_plugins.txt");
	}
	if(path_info("/dev_hdd0/boot_plugins.txt") == _FILE) {
		add_item_value_MENU("/dev_hdd0/boot_plugins.txt");
	}
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	BOOTFILE_ITEM = ITEMS_NUMBER;
	if(ITEMS_VALUE_NUMBER[BOOTFILE_ITEM] == -1) return;
	
	MENU_TABLE_START=ITEMS_NUMBER;
	
	FILE* f = fopen(ITEMS_VALUE[BOOTFILE_ITEM][ITEMS_VALUE_POSITION[BOOTFILE_ITEM]], "r");
	if(f) {
		char line[255];
		int l = strlen("/dev_hdd0/plugins");
		while(fgets(line, 255, f) != NULL) {
			if(line[0]=='\r' || line[0]=='\n') continue;
			strtok(line, "\r\n");
			if(strncmp(line, "/dev_hdd0/plugins", l) != 0) {
				if(ITEMS_NUMBER==MENU_MAX_ITEMS-1) break;
				add_item_MENU(line, ITEM_TEXTBOX);
			}
		}
		fclose(f);
	}
	
	DIR *d;
	struct dirent *dir;
	d = opendir("/dev_hdd0/plugins");
	if(d!=NULL) {			
		while ((dir = readdir(d))) {
			if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
			if(get_ext(dir->d_name) == _SPRX) {
				if(ITEMS_NUMBER==MENU_MAX_ITEMS-1) break;
				add_item_MENU(dir->d_name, ITEM_CHECKBOX);
				sprintf(temp, "/dev_hdd0/plugins/%s", dir->d_name);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER] = is_it_inside(ITEMS_VALUE[BOOTFILE_ITEM][ITEMS_VALUE_POSITION[BOOTFILE_ITEM]], temp);
			}	
		}
		closedir(d);
	}
	
	MENU_TABLE_END=ITEMS_NUMBER;
	MENU_COLUMN_ITEMS_NUMBER = 1+(ITEMS_NUMBER-BOOTFILE_ITEM)/4;
}

u8 PLUGINS_MANAGER_CROSS()
{
// PLUGIN MONITOR
	if(ITEMS_POSITION < BOOTFILE_ITEM) {
		if(ITEMS_TYPE[ITEMS_POSITION]==ITEM_TEXTBOX) {
			u32 slot;
			sscanf(ITEMS[ITEMS_POSITION], "%*s %d", &slot);
			cobra_unload_vsh_plugin(slot);
		}
	} else
// BOOT FILE
	if(ITEMS_POSITION == BOOTFILE_ITEM) {
		if(ITEMS_VALUE_NUMBER[ITEMS_POSITION] == -1) {
			if(cobra || mamba) {
				FILE* f=NULL;
				if(cobra) f=fopen("/dev_hdd0/boot_plugins.txt", "wb"); else
				if(mamba) f=fopen("/dev_hdd0/mamba_plugins.txt", "wb");	
				if(f) fclose(f);
			}
		} else {
			open_txt_viewer(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
		}

	} else 
// PLUGIN MANAGER
	if(ITEMS_POSITION > BOOTFILE_ITEM) { 
		if(ITEMS_TYPE[ITEMS_POSITION]==ITEM_TEXTBOX) {
			char NewPath[255];
			sprintf(NewPath, "/dev_hdd0/plugins/%s", &strrchr(ITEMS[ITEMS_POSITION], '/')[1]);
			if( Move(ITEMS[ITEMS_POSITION], NewPath) == SUCCESS) {
				remove_from_list(ITEMS_VALUE[BOOTFILE_ITEM][ITEMS_VALUE_POSITION[BOOTFILE_ITEM]], ITEMS[ITEMS_POSITION]);
				add_to_list(ITEMS_VALUE[BOOTFILE_ITEM][ITEMS_VALUE_POSITION[BOOTFILE_ITEM]], NewPath);
			}
		} else 
		if(ITEMS_TYPE[ITEMS_POSITION]==ITEM_CHECKBOX) {
			char temp[128];
			sprintf(temp, "/dev_hdd0/plugins/%s", ITEMS[ITEMS_POSITION]);
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == YES) 
				remove_from_list(ITEMS_VALUE[BOOTFILE_ITEM][ITEMS_VALUE_POSITION[BOOTFILE_ITEM]], temp);
			else 
				add_to_list(ITEMS_VALUE[BOOTFILE_ITEM][ITEMS_VALUE_POSITION[BOOTFILE_ITEM]], temp);
		}
	}
	
	init_PLUGINS_MANAGER();
	
	return CONTINUE;
}

u8 PLUGINS_MANAGER_SQUARE()
{
	
	if(ITEMS_POSITION > BOOTFILE_ITEM) {
		char diag_msg[512];
		sprintf(diag_msg, "%s '%s' ?", STR_ASK_DEL, ITEMS[ITEMS_POSITION]);
		if( DrawDialogYesNo(diag_msg) == YES) {
			char prx_path[128];
			if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_CHECKBOX) {
				sprintf(prx_path, "/dev_hdd0/plugins/%s", ITEMS[ITEMS_POSITION]);
			} else 
			if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_TEXTBOX) {
				strcpy(prx_path, ITEMS[ITEMS_POSITION]);
			}
			remove_from_list(ITEMS_VALUE[BOOTFILE_ITEM][ITEMS_VALUE_POSITION[BOOTFILE_ITEM]], prx_path);
			Delete(prx_path);
			ITEMS_POSITION=0;
		}
	}
	
	init_PLUGINS_MANAGER();
	
	return CONTINUE;
}

u8 PLUGINS_MANAGER_TRIANGLE()
{
	if(ITEMS_POSITION > BOOTFILE_ITEM) {
		int i;
		for(i=0; i<6; i++) {
			if(strcmp(&strrchr(ITEMS[i], ' ')[1], STR_UNUSED)==0) {
				char prx_path[128];
				if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_CHECKBOX) {
					sprintf(prx_path, "/dev_hdd0/plugins/%s", ITEMS[ITEMS_POSITION]);
				} else 
				if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_TEXTBOX) {
					strcpy(prx_path, ITEMS[ITEMS_POSITION]);
				}
				cobra_load_vsh_plugin(i+1, prx_path, NULL, 0);
				break;
			}
		}
	}
	
	init_PLUGINS_MANAGER();
	
	return CONTINUE;
}

void input_PLUGINS_MANAGER()
{
	get_R2speed();
	
	if(MENU_TABLE_START < ITEMS_POSITION && ITEMS_POSITION <=MENU_TABLE_END) {
		if(R2pad(BUTTON_RIGHT)) {
			if(ITEMS_POSITION + MENU_COLUMN_ITEMS_NUMBER <= ITEMS_NUMBER) ITEMS_POSITION += MENU_COLUMN_ITEMS_NUMBER;
		} else
		if(R2pad(BUTTON_LEFT)) {
			if(ITEMS_POSITION - MENU_COLUMN_ITEMS_NUMBER >= 0) ITEMS_POSITION -= MENU_COLUMN_ITEMS_NUMBER;
		}
	}
	
	if(R2pad(BUTTON_UP)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	} else
	if(R2pad(BUTTON_DOWN)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	} else
	if(new_pad & BUTTON_CROSS) {
		if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_CHECKBOX ) {
			PLUGINS_MANAGER_CROSS();
		} else
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1 ) {
			IN_ITEMS_VALUE = YES;
		} else {
			if(PLUGINS_MANAGER_CROSS() == BREAK) close_PLUGINS_MANAGER();
		}
	} else
	if(new_pad & BUTTON_SQUARE) {
		if(PLUGINS_MANAGER_SQUARE() == BREAK) close_PLUGINS_MANAGER();
	} else
	if(new_pad & BUTTON_TRIANGLE) {
		if(PLUGINS_MANAGER_TRIANGLE() == BREAK) close_PLUGINS_MANAGER();
	} else
	if(new_pad & BUTTON_CIRCLE) {
		if(IN_ITEMS_VALUE == NO) close_PLUGINS_MANAGER();
		else {
			init_PLUGINS_MANAGER();
			IN_ITEMS_VALUE = NO;
		}
	}
}

void Draw_PLUGINS_MANAGER_input()
{
	if(MENU==NO) return;
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	if(ITEMS_POSITION < BOOTFILE_ITEM) {
		x=DrawButton(x, y, STR_UNLOAD, BUTTON_CROSS);
	} else
	if(ITEMS_POSITION == BOOTFILE_ITEM) {
		if(IN_ITEMS_VALUE == YES) {
			x=DrawButton(x, y, STR_VIEW, BUTTON_CROSS);
		} else
		if(ITEMS_VALUE_NUMBER[ITEMS_POSITION] == -1) {
			if(cobra || mamba)	x=DrawButton(x, y, STR_CREATE, BUTTON_CROSS);
		} else {
			x=DrawButton(x, y, STR_ENTER, BUTTON_CROSS);
		}
	} else
	if(ITEMS_POSITION > BOOTFILE_ITEM) {
		if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_CHECKBOX) {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == YES) 
				x=DrawButton(x, y, STR_UNCHECK, BUTTON_CROSS);
			else 
				x=DrawButton(x, y, STR_CHECK, BUTTON_CROSS);			
		} else {
			x=DrawButton(x, y, STR_MOVE_TO_PLUGINS, BUTTON_CROSS);
		}
		x=DrawButton(x, y, STR_DELETE, BUTTON_SQUARE);
		x=DrawButton(x, y, STR_LOAD, BUTTON_TRIANGLE);
	}
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
}

u8 open_PLUGINS_MANAGER()
{
	if( path_info("/dev_hdd0/plugins") == _NOT_EXIST) {
		if( DrawDialogYesNo(STR_ASK_PLUGINS) == YES) mkdir("/dev_hdd0/plugins", 0777);
		else return CONTINUE;
	}
	
	start_loading();
	
	close_SETTINGS();
	
	new_MENU();
	
	if(PEEKnPOKE) {
		if(!cobra && !mamba) mamba = install_mamba();
	}
	init_PLUGINS_MANAGER();
	MENU_SIDE = NO;
	Draw_MENU_input = &Draw_PLUGINS_MANAGER_input;
	input_MENU = &input_PLUGINS_MANAGER;
	
	end_loading();
	
	return BREAK;
}

void Draw_TVTEST()
{
	if(TMP_PIC_offset != 0) {
		tiny3d_SetTexture(0, TMP_PIC_offset, TMP_PIC.width, TMP_PIC.height, TMP_PIC.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(0, 0, 0, 0, 848, 512, WHITE, YES);
	}
}

void Draw_AdjustScreen()
{
	int Show_TVTEST=NO;
	
	char TVTEST[128];
	sprintf(TVTEST, "/dev_hdd0/game/%s/USRDIR/GUI/common/TVTEST.PNG", ManaGunZ_id);

	if(path_info(TVTEST) != _FILE) Show_TVTEST=-1;
	
	u8 LoopBreak=1;
	while(LoopBreak)
	{
			
		float x=INPUT_X;
		float y=INPUT_Y;
		SetFontZ(0);
		
		adjust_screen();
		
		cls();
		
		if(Show_TVTEST==YES)
		{
			Draw_TVTEST();
			FontColor(WHITE);
			x=DrawButton(x, y, STR_HIDETV, BUTTON_CROSS);
		} else {
			Draw_Box(0,0,10,   0,   X_MAX,Y_MAX,  0xFFFFFFFF, NO);
			Draw_Box(30,30,9 , 0,   X_MAX-30*2,Y_MAX-30*2,  0x000000FF, NO);

			int l=150, h=70;
			Draw_Box(110,150,8,   5,   15,Y_MAX-150*2,  0xFFFFFFFF, NO);

			tiny3d_SetPolygon(TINY3D_TRIANGLES);
			tiny3d_VertexPos(110+15+5+h, Y_MAX/2, 8);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexPos(110+15+5 , Y_MAX/2 -l/2 , 8);
			tiny3d_VertexPos(110+15+5 , Y_MAX/2 +l/2 , 8);
			tiny3d_End();
			Draw_Pad(BUTTON_RIGHT,  110+15+5+5,Y_MAX/2-20,8, 40);			

			tiny3d_SetPolygon(TINY3D_TRIANGLES);
			tiny3d_VertexPos(110-5-h, Y_MAX/2, 8);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexPos(110-5 , Y_MAX/2 -l/2 , 8);
			tiny3d_VertexPos(110-5 , Y_MAX/2 +l/2 , 8);
			tiny3d_End();
			Draw_Pad(BUTTON_LEFT,  110-5-40-5,Y_MAX/2-20,8, 40);
			
			Draw_Box(150,110,8,   5,   X_MAX-120*2,15,  0xFFFFFFFF, NO);

			tiny3d_SetPolygon(TINY3D_TRIANGLES);
			tiny3d_VertexPos(X_MAX/2, 110+15+5+h, 8);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexPos(X_MAX/2 -l/2, 110+15+5 , 8);
			tiny3d_VertexPos(X_MAX/2 +l/2, 110+15+5 , 8);
			tiny3d_End();
			Draw_Pad(BUTTON_DOWN,  X_MAX/2-20,110+15+5+5,8, 40);
		
			tiny3d_SetPolygon(TINY3D_TRIANGLES);
			tiny3d_VertexPos(X_MAX/2, 110-5-h , 8);
			tiny3d_VertexColor(0xFFFFFFFF);
			tiny3d_VertexPos(X_MAX/2 -l/2 , 110-5 , 8);
			tiny3d_VertexPos(X_MAX/2 +l/2 , 110-5 , 8);
			tiny3d_End();
			Draw_Pad(BUTTON_UP,  X_MAX/2-20,110-5-40-5,8, 40);

			FontColor(BLACK);
			FontSize(15);
			if(Show_TVTEST != -1 && Load_GamePIC==NO) x=DrawButton(x, INPUT_Y, STR_SHOWTV, BUTTON_CROSS);
		} 
		
		x=DrawButton(x, INPUT_Y, STR_RESET, BUTTON_SQUARE);
		x=DrawButton(x, INPUT_Y, STR_BACK, BUTTON_CIRCLE);
		
		tiny3d_Flip();
		ScreenShot();
		
		ps3pad_read();
		
		if(new_pad & BUTTON_SQUARE) {
			videoscale_x = 0;
			videoscale_y = 0;
		}
		if(Show_TVTEST != -1 && Load_GamePIC==NO) {
			if(new_pad & BUTTON_CROSS) {
				if(Show_TVTEST==NO) {
					memset(TMP_PIC_path, 0, sizeof(TMP_PIC_path));
					strcpy(TMP_PIC_path, TVTEST);
					Load_FM();
					Show_TVTEST=YES;
				} else {
					Show_TVTEST=NO;
					TMP_PIC_offset=0;
				}
			}
		}
		if(new_pad & BUTTON_DOWN) {if(videoscale_y > -120) videoscale_y-=10;}
		if(new_pad & BUTTON_UP) {if(videoscale_y < 120) videoscale_y+=10;}
		if(new_pad & BUTTON_RIGHT) {if(videoscale_x > -120) videoscale_x-=10;}
		if(new_pad & BUTTON_LEFT) {if(videoscale_x < 120) videoscale_x+=10;}
		if(new_pad & BUTTON_CIRCLE) {
			write_setting(); 
			LoopBreak=0;
			return;
		}
	}
}

u8 C_pos=0;

void Draw_RGBA_box(int n)
{
	u32 COLOR=0;
	if(n==1) COLOR = COLOR_1; else
	if(n==2) COLOR = COLOR_2; else
	if(n==3) COLOR = COLOR_3; else
	if(n==4) COLOR = COLOR_4; else
	if(n==5) COLOR = WAVES_COLOR;
	
	float h_COLOR = 5+20*4+5;
	float w_COLOR = h_COLOR + 10+10+10+128+10;
	
	if(x_COLOR + w_COLOR > X_MAX) x_COLOR -= w_COLOR-16;
	if(y_COLOR + h_COLOR > Y_MAX) y_COLOR -= h_COLOR-10;
	
	Draw_Box(x_COLOR, y_COLOR, 0, 0, w_COLOR, h_COLOR, 0x888888FF, NO);
	
	Draw_Box(x_COLOR+10, y_COLOR+10, 0, 0, h_COLOR-20, h_COLOR-20, COLOR, NO);
	
	Draw_Box(x_COLOR+h_COLOR+10+10+10, y_COLOR+5+9			, 0, 0, 128, 2, 0x444444FF, NO);
	Draw_Box(x_COLOR+h_COLOR+10+10+10, y_COLOR+5+20+9		, 0, 0, 128, 2, 0x444444FF, NO);
	Draw_Box(x_COLOR+h_COLOR+10+10+10, y_COLOR+5+20+20+9	, 0, 0, 128, 2, 0x444444FF, NO);
	Draw_Box(x_COLOR+h_COLOR+10+10+10, y_COLOR+5+20+20+20+9	, 0, 0, 128, 2, 0x444444FF, NO);
	
	u32 curs_color;
	float e;
	
	if(C_pos == 0) {curs_color = WHITE; e=12;} else {curs_color = 0x666666FF; e=8;}
	Draw_Box(x_COLOR+h_COLOR+10+5-e/2, y_COLOR+5+10-e/2, 0, 0, e, e, RED, NO);
	Draw_Box(x_COLOR+h_COLOR+10+10+10 + GetRED(COLOR)/2 - 2, y_COLOR+5+10-4, 0, 0, 4, 8, curs_color, NO);
	
	if(C_pos == 1) {curs_color = WHITE; e=12;} else {curs_color = 0x666666FF; e=8;}
	Draw_Box(x_COLOR+h_COLOR+10+5-e/2, y_COLOR+5+20+10-e/2, 0, 0, e, e, GREEN, NO);
	Draw_Box(x_COLOR+h_COLOR+10+10+10 + GetGREEN(COLOR)/2 - 2, y_COLOR+5+20+10-4, 0, 0, 4, 8, curs_color, NO);
	
	if(C_pos == 2) {curs_color = WHITE; e=12;} else {curs_color = 0x666666FF; e=8;}
	Draw_Box(x_COLOR+h_COLOR+10+5-e/2, y_COLOR+5+20+20+10-e/2, 0, 0, e, e, BLUE, NO);
	Draw_Box(x_COLOR+h_COLOR+10+10+10 + GetBLUE(COLOR)/2 - 2, y_COLOR+5+20+20+10-4, 0, 0, 4, 8, curs_color, NO);
	
	if(C_pos == 3) {curs_color = WHITE; e=12;} else {curs_color = 0x666666FF; e=8;}
	Draw_Box(x_COLOR+h_COLOR+10+5-e/2, y_COLOR+5+20+20+20+10-e/2, 0, 0, e, e, BLACK-0xFF+GetALPHA(COLOR), NO);
	Draw_Box(x_COLOR+h_COLOR+10+10+10 + GetALPHA(COLOR)/2 - 2, y_COLOR+5+20+20+20+10-4, 0, 0, 4, 8, curs_color, NO);	
}

u8 input_COLOR(int n)
{
	u32 COLOR=0;
	if(n==1) COLOR = COLOR_1; else
	if(n==2) COLOR = COLOR_2; else
	if(n==3) COLOR = COLOR_3; else
	if(n==4) COLOR = COLOR_4; else
	if(n==5) COLOR = WAVES_COLOR;
	
	get_R2speed();
	
	if(new_pad & BUTTON_UP || (old_pad & BUTTON_UP && slow_it==0)) {
		if(C_pos==0) C_pos=3;
		else C_pos--;
	}
	
	if(new_pad & BUTTON_DOWN || (old_pad & BUTTON_DOWN && slow_it==0)) {
		if(C_pos==3) C_pos=0;
		else C_pos++;
	}
	
	if(new_pad & BUTTON_LEFT  || (old_pad & BUTTON_LEFT  && slow_it==0)) {
		if(C_pos == 0) {
			if(GetRED(COLOR) > 0) {
				COLOR = SetRED(GetRED(COLOR)-5, COLOR);
			}
		} else
		if(C_pos == 1) {
			if(GetGREEN(COLOR) > 0) {
				COLOR = SetGREEN(GetGREEN(COLOR)-5, COLOR);
			}
		} else
		if(C_pos == 2) {
			if(GetBLUE(COLOR) > 0) {
				COLOR = SetBLUE(GetBLUE(COLOR)-5, COLOR);
			}
		} else
		if(C_pos == 3) {
			if(GetALPHA(COLOR) > 0) {
				COLOR = SetALPHA(GetALPHA(COLOR)-5, COLOR);
			}
		}
	}
		
	if(new_pad & BUTTON_RIGHT || (old_pad & BUTTON_RIGHT && slow_it==0)) {
		if(C_pos == 0) {
			if(GetRED((u32) COLOR) < 0xFF) {
				COLOR = SetRED(GetRED(COLOR)+5, COLOR);
			}
		} else
		if(C_pos == 1) {
			if(GetGREEN((u32) COLOR) < 0xFF) {
				COLOR = SetGREEN(GetGREEN(COLOR)+5, COLOR);
			}
		} else
		if(C_pos == 2) {
			if(GetBLUE((u32) COLOR) < 0xFF) {
				COLOR = SetBLUE(GetBLUE(COLOR)+5, COLOR);
			}
		} else
		if(C_pos == 3) {
			if(GetALPHA((u32) COLOR) < 0xFF) {
				COLOR = SetALPHA(GetALPHA(COLOR)+5, COLOR);
			}
		}
	}
		
	if(n==1) COLOR_1 = COLOR; else
	if(n==2) COLOR_2 = COLOR; else
	if(n==3) COLOR_3 = COLOR; else
	if(n==4) COLOR_4 = COLOR; else
	if(n==5) WAVES_COLOR = COLOR;
		
	if(new_pad & BUTTON_CIRCLE) {
		return BREAK;
	}
	
	return CONTINUE;
}

void Draw_COLOR_input()
{
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	x=DrawButton(x, y, STR_SET_COLOR, BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT);
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
}

void Draw_ChooseColor(u8 n)
{
	u8 LoopBreak=1;
	while(LoopBreak)
	{
		cls();
		Draw_scene();
		
		Draw_RGBA_box(n);
		Draw_COLOR_input();
		
		tiny3d_Flip();
		ScreenShot();
		
		ps3pad_read();
				
		if(input_COLOR(n) == BREAK) {
			LoopBreak=0;
			return;
		}
	}
}

void close_SETTINGS()
{
	FreeFont();
	write_setting();
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	MENU=NO;
	free_MENU();
}

void init_SETTINGS()
{
	int i;
	
	init_MENU();
	
	add_title_MENU(STR_GLOB_SETTINGS);
	
	add_item_MENU(STR_ADJUST, ITEM_TEXTBOX);
	
#ifndef FILEMANAGER
	add_item_MENU(STR_DL_COVER, ITEM_TEXTBOX);
#endif

	add_item_MENU(STR_PLUGIN_MANAGER, ITEM_TEXTBOX);
	
#ifndef FILEMANAGER
	add_item_MENU(STR_UPD_MGZ, ITEM_TEXTBOX);
	
	add_item_MENU(STR_GAME_PATHS, ITEM_TEXTBOX);
	for(i=0; i <= scan_dir_number; i++) {
		add_item_value_MENU(scan_dir[i]);
	}
#endif

	add_item_MENU(STR_LANG, ITEM_TEXTBOX);
	for(i=0; i < lang_N ;i++) {
		add_item_value_MENU(STR_LANGUAGE[i]);
	}
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = lang;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU(STR_XMB_PRIO, ITEM_TEXTBOX);
	add_item_value_MENU(STR_NO);
	add_item_value_MENU(STR_YES);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = XMB_priority;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU(STR_HELP, ITEM_TEXTBOX);
	add_item_value_MENU(STR_NO);
	add_item_value_MENU(STR_YES);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Show_Help;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
	add_title_MENU(STR_THM_SETTINGS);
	
	add_item_MENU(STR_THM, ITEM_TEXTBOX);
	for(i=0; i <= Themes_number[UI_position]; i++) {
		add_item_value_MENU(Themes_Names_list[UI_position][i]);
	}
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Themes_position[UI_position];
	
	FILE *f;
	char ColorSetPath[128];
	sprintf(ColorSetPath, "/dev_hdd0/game/%s/USRDIR/GUI/colorset.ini",  ManaGunZ_id);
	f = fopen(ColorSetPath, "rb");
	if(f!=NULL) {
		char *ColorSetName = NextColorSetName(f);
		if(ColorSetName) {
			add_item_MENU(STR_COLORSET, ITEM_TEXTBOX);

			add_item_value_MENU(ColorSetName);
			FREE(ColorSetName);
			
			while((ColorSetName=NextColorSetName(f)) != NULL ) {
				add_item_value_MENU(ColorSetName);
				FREE(ColorSetName);
			}
		}
		fclose(f);
	}

	add_item_MENU(STR_FONT, ITEM_TEXTBOX);
	for(i=0; i<=FontNumber; i++) {
		add_item_value_MENU(FontName[i]);
		if(strcmp(Font, FontPath[i]) == 0) ITEMS_VALUE_POSITION[ITEMS_NUMBER]=i;
	}
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU(STR_COLOR_1, ITEM_COLORBOX);
	FREE(ITEMS_VALUE[ITEMS_NUMBER][0]);
	ITEMS_VALUE[ITEMS_NUMBER][0] = malloc(4);
	memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &COLOR_1, 4);
	
	add_item_MENU(STR_COLOR_2, ITEM_COLORBOX);
	FREE(ITEMS_VALUE[ITEMS_NUMBER][0]);
	ITEMS_VALUE[ITEMS_NUMBER][0] = malloc(4);
	memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &COLOR_2, 4);
	
	add_item_MENU(STR_COLOR_3, ITEM_COLORBOX);
	FREE(ITEMS_VALUE[ITEMS_NUMBER][0]);
	ITEMS_VALUE[ITEMS_NUMBER][0] = malloc(4);
	memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &COLOR_3, 4);

	add_item_MENU(STR_COLOR_4, ITEM_COLORBOX);
	FREE(ITEMS_VALUE[ITEMS_NUMBER][0]);
	ITEMS_VALUE[ITEMS_NUMBER][0] = malloc(4);
	memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &COLOR_4, 4);	
	
#ifndef FILEMANAGER
	add_title_MENU(STR_UI_SETTINGS);
	
	add_item_MENU(STR_UI, ITEM_TEXTBOX);
	for(i=0; i < 4; i++) {
		add_item_value_MENU(UI[i]);
	}
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = UI_position;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU(STR_SIDE_MENU, ITEM_TEXTBOX);
	add_item_value_MENU(STR_NO);
	add_item_value_MENU(STR_YES);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Use_SideMenu;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU(STR_SHOW_PIC1, ITEM_TEXTBOX);
	add_item_value_MENU(STR_NO);
	add_item_value_MENU(STR_YES);
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Show_PIC1;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	if(UI_position==LIST) {
		add_item_MENU(STR_SHOW_ICON0, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = LIST_Show_ICON0;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	} else
	if(UI_position==GRID) {
		add_item_MENU(STR_GRID_TYPE, ITEM_TEXTBOX);
		add_item_value_MENU(STR_GRID_SCROLL);
		add_item_value_MENU(STR_PAGE);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = GRID_TYPE;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU(STR_DIRECTION, ITEM_TEXTBOX);
		add_item_value_MENU(STR_VERTICAL);
		add_item_value_MENU(STR_HORIZONTAL);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = GRID_DIRECTION;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU(STR_ANIMATED, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = GRID_ANIMATED;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU(STR_KEEP_PROP, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = GRID_KEEP_PROP;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU(STR_NB_COL, ITEM_TEXTBOX);
		for(i=0; i < 16; i++) {
			char tmp[3];
			sprintf(tmp, "%d", i);
			add_item_value_MENU(tmp);
		}
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = GRID_NB_COLUMNS;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		if(GRID_KEEP_PROP==NO) {
			add_item_MENU(STR_NB_LINE, ITEM_TEXTBOX);
			for(i=0; i < 16; i++) {
				char tmp[3];
				sprintf(tmp, "%d", i);
				add_item_value_MENU(tmp);
			}
			ITEMS_VALUE_POSITION[ITEMS_NUMBER] = GRID_NB_LINES;
			ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		}
	} else
	if(UI_position==FLOW) {
		add_item_MENU(STR_INVERSE, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = FLOW_inverse_button;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU(STR_3D, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = FLOW_3D;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	}
	
	if((UI_position==FLOW && FLOW_3D == NO)
	||	UI_position==XMB
	||  UI_position==LIST ) 
	{
		add_item_MENU(STR_SHOW_COVER, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Show_COVER;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		if(Show_COVER==YES) {
			add_item_MENU(STR_SHOW_GAMECASE, ITEM_TEXTBOX);
			add_item_value_MENU(STR_NO);
			add_item_value_MENU(STR_YES);
			ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Show_GameCase;
			ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		}
	}
	
	if(UI_position==FLOW || UI_position==XMB) {
		add_item_MENU(STR_SHOW_WAVES, ITEM_TEXTBOX);
		add_item_value_MENU(STR_NO);
		add_item_value_MENU(STR_YES);
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Show_Waves;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		if(Show_Waves) {
			add_item_MENU(STR_WAVES_COLOR, ITEM_COLORBOX);
			FREE(ITEMS_VALUE[ITEMS_NUMBER][0]);
			ITEMS_VALUE[ITEMS_NUMBER][0] = malloc(4);
			memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &WAVES_COLOR, 4);	
		}
	}
#endif

}

void update_SETTINGS()
{
	if(item_is(STR_FONT)) {
		if(strcmp(Font, FontPath[ITEMS_VALUE_POSITION[ITEMS_POSITION]]) != 0) {
			if(Load_GamePIC) show_msg("Try Later");
			else {
				start_loading();
				strcpy(Font, FontPath[ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
				LoadFont();
				end_loading();
			}
		}
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], STR_LANG) == 0) {
		lang = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		lang_code = (uint8_t) STR_LANGCODE[lang][0];
		if(lang_code != lang_code_loaded) {
			update_lang();
			init_SETTINGS();
		}
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], STR_HELP) == 0) {
		Show_Help = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_XMB_PRIO) == 0) {
		XMB_priority = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_SIDE_MENU) == 0) {
		Use_SideMenu = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_UI) == 0) {
		if(UI_position != ITEMS_VALUE_POSITION[ITEMS_POSITION]) {
			if(Load_GamePIC) {
				ITEMS_VALUE_POSITION[ITEMS_POSITION] = UI_position;
				show_msg("Try Later");
			} else {
				start_loading();
				print_head("Loading Theme...");
				UI_position = ITEMS_VALUE_POSITION[ITEMS_POSITION];
				Load_Theme();
				init_SETTINGS();
				end_loading();
			}
		}
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_THM) == 0) {
		Themes_position[UI_position] = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], STR_SHOW_COVER) == 0) {
		if( Show_COVER != ITEMS_VALUE_POSITION[ITEMS_POSITION]) {
			Show_COVER = ITEMS_VALUE_POSITION[ITEMS_POSITION];
			init_SETTINGS();
		}
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_SHOW_GAMECASE) == 0) {
		Show_GameCase = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_SHOW_PIC1) == 0) {
		Show_PIC1 = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_SHOW_WAVES) == 0) {
		if( Show_Waves != ITEMS_VALUE_POSITION[ITEMS_POSITION]) {
			Show_Waves = ITEMS_VALUE_POSITION[ITEMS_POSITION];
			init_SETTINGS();
		}
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], STR_SHOW_ICON0) == 0) {
		LIST_Show_ICON0 = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_GRID_TYPE) == 0) {
		GRID_TYPE = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_DIRECTION) == 0) {
		GRID_DIRECTION = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], STR_ANIMATED) == 0) {
		GRID_ANIMATED = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_KEEP_PROP) == 0) {
		if( GRID_KEEP_PROP != ITEMS_VALUE_POSITION[ITEMS_POSITION] ) {
			GRID_KEEP_PROP = ITEMS_VALUE_POSITION[ITEMS_POSITION];
			init_SETTINGS();
		}
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], STR_NB_COL) == 0) {
		GRID_NB_COLUMNS = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_NB_LINE) == 0) {
		GRID_NB_LINES = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], STR_INVERSE) == 0) {
		FLOW_inverse_button = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], STR_3D) == 0) {
		if( FLOW_3D != ITEMS_VALUE_POSITION[ITEMS_POSITION]) {
			FLOW_3D = ITEMS_VALUE_POSITION[ITEMS_POSITION];
			init_SETTINGS();
		}
	}
}

u8 SETTINGS_CROSS()
{
	if(strcmp(ITEMS[ITEMS_POSITION], STR_ADJUST) == 0) {
		Draw_AdjustScreen();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_DL_COVER) == 0) {
		start_loading();
		Download_covers();
		end_loading();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_GAME_PATHS) == 0) {
		char tmpName[128];
		memset(tmpName, 0, sizeof(tmpName));
		if(Get_OSK_String(STR_NEWFOLDER, tmpName, 128) == SUCCESS) {
			if(tmpName[0]!=0) {
				scan_dir_number++;
				strcpy(scan_dir[scan_dir_number], tmpName);
				write_scan_dir();
			}
		}
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_PLUGIN_MANAGER) == 0) {
		return open_PLUGINS_MANAGER();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_UPD_MGZ) == 0) {
		show_msg("To Fix");
		//update_MGZ();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_THM) == 0) {
		if(Load_GamePIC) show_msg("Try Later");
		else {
			start_loading();
			print_load("Loading theme...");
			u8 ret = InstallTheme();
			if(ret==SUCCESS) {
				Load_Theme();
				LoadThemeColorSet();
				LoadThemeFont();
				write_setting();
			}
			end_loading();
		}
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_COLOR_1) == 0) {
		Draw_ChooseColor(1);
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_COLOR_2) == 0) {
		Draw_ChooseColor(2);
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_COLOR_3) == 0) {
		Draw_ChooseColor(3);
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_COLOR_4) == 0) {
		Draw_ChooseColor(4);
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_WAVES_COLOR)==0) {
		Draw_ChooseColor(5);
	} else
	if(item_is(STR_COLORSET)) {
		LoadColorSet(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
	} else
		return CONTINUE;
	
	update_SETTINGS();
	init_SETTINGS();
	
	return CONTINUE;
}

u8 SETTINGS_SQUARE()
{
	if(strcmp(ITEMS[ITEMS_POSITION], STR_COLOR_1) == 0) {
		COLOR_1 = WHITE;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_COLOR_2) == 0) {
		COLOR_2 = GREEN;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_COLOR_3) == 0) {
		COLOR_3 = ORANGE;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_COLOR_4) == 0) {
		COLOR_4 = RED;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_WAVES_COLOR) == 0) {
		WAVES_COLOR = WHITE-0xFF+0x20;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_THM) == 0) {
		u8 ThemeType = GetThemeType(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
		if(ThemeType == MGZ) {
			char tmpName[128];
			strcpy(tmpName, Themes_Names_list[UI_position][Themes_position[UI_position]]);
			if(Get_OSK_String(STR_RENAME, tmpName, 128) == SUCCESS) {
				char old[128], new[128];
				sprintf(old, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position], Themes_Names_list[UI_position][Themes_position[UI_position]]);
				sprintf(new, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position], tmpName);
				if( rename(old, new) == 0 ) {
					strcpy(Themes_Names_list[UI_position][Themes_position[UI_position]], tmpName);
					show_msg(STR_DONE);
				} else show_msg(STR_FAILED);	
			}	
		}
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_GAME_PATHS) == 0) {
		if(Get_OSK_String(STR_RENAME, scan_dir[ITEMS_VALUE_POSITION[ITEMS_POSITION]], 128) == SUCCESS) {
			if(scan_dir[ITEMS_VALUE_POSITION[ITEMS_POSITION]][0] != 0) {
				write_scan_dir();
			}
		}
	} else
	if(item_is(STR_COLORSET)) {
		char NewColorSet[128];
		memset(NewColorSet, 0, 128);
		if(Get_OSK_String(STR_COLORSET, NewColorSet, 128) == SUCCESS) {
			AddColorSet(NewColorSet);
		}
	} else
		return CONTINUE;
	
	update_SETTINGS();
	init_SETTINGS();
	
	return CONTINUE;
}

u8 SETTINGS_TRIANGLE()
{
	if(strcmp(ITEMS[ITEMS_POSITION], STR_THM) == 0) {
		start_loading();
				
		Delete(Themes_Paths_list[UI_position][Themes_position[UI_position]]);
			
		if(path_info(Themes_Paths_list[UI_position][Themes_position[UI_position]]) == _NOT_EXIST) {			
			GetThemes();
			if(Themes_position[UI_position] > Themes_number[UI_position]) Themes_position[UI_position]=Themes_number[UI_position];
			ITEMS_VALUE_NUMBER[ITEMS_POSITION] = Themes_number[UI_position];
			ITEMS_VALUE_POSITION[ITEMS_POSITION] = Themes_position[UI_position];
			show_msg(STR_DONE);
		} else show_msg(STR_FAILED);
		
		end_loading();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], STR_GAME_PATHS) == 0) {
		if(scan_dir_number>0) {
			int i;
			for(i=ITEMS_VALUE_POSITION[ITEMS_POSITION]; i < scan_dir_number; i++) {
				strcpy(scan_dir[i], scan_dir[i+1]);
			}
			memset(scan_dir[scan_dir_number], 0, sizeof(scan_dir[scan_dir_number]));
			
			if(scan_dir_number==ITEMS_VALUE_POSITION[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
			scan_dir_number--;
			write_scan_dir();
		}
	} else
	if(item_is(STR_COLORSET)) {
		if( ITEMS_VALUE_NUMBER[ITEMS_POSITION] > 0) {
			RemoveColorSet(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
			ITEMS_VALUE_NUMBER[ITEMS_POSITION]--;
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION]>ITEMS_VALUE_NUMBER[ITEMS_POSITION]) 
				ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
		}
	} else
		return CONTINUE;
	
	update_SETTINGS();
	init_SETTINGS();

	return CONTINUE;
}

void input_SETTINGS()
{
	get_R2speed();
		
	if(R2pad(BUTTON_UP)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	} else
	if(R2pad(BUTTON_DOWN)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	} else
	if(new_pad & BUTTON_CROSS) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			IN_ITEMS_VALUE = YES;
		} else {
			if(SETTINGS_CROSS() == BREAK) return;
		}
	} else
	if(new_pad & BUTTON_SQUARE) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_SHOW[ITEMS_POSITION] == YES) {
				if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
				else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
			}
		} else {
			if(SETTINGS_SQUARE() == BREAK) return;
		}
	} else
	if(new_pad & BUTTON_TRIANGLE) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_SHOW[ITEMS_POSITION] == YES) {
				if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
				else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
			}
		} else {
			if(SETTINGS_TRIANGLE() == BREAK) return;
		}
	} else
	if(new_pad & BUTTON_CIRCLE) {
		if(IN_ITEMS_VALUE == NO) {close_SETTINGS(); return;}
		else {
			init_SETTINGS();
			IN_ITEMS_VALUE = NO;
		}
	}
	
	update_SETTINGS();
}

void Draw_SETTINGS_input()
{
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	if(IN_ITEMS_VALUE == YES) {
		if(strcmp(ITEMS[ITEMS_POSITION], STR_GAME_PATHS) == 0) {
			x=DrawButton(x, y, STR_ADD, BUTTON_CROSS);
			if(scan_dir_number>0) {
				x=DrawButton(x, y, STR_DELETE, BUTTON_TRIANGLE);
				x=DrawButton(x, y, STR_RENAME, BUTTON_SQUARE);
			}
		} else
		if(strcmp(ITEMS[ITEMS_POSITION], STR_THM) == 0) {
			x=DrawButton(x, y, STR_LOAD, BUTTON_CROSS);
			x=DrawButton(x, y, STR_DELETE, BUTTON_TRIANGLE);
			u8 ThemeType = GetThemeType(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
			if(ThemeType == MGZ) {
				x=DrawButton(x, y, STR_RENAME, BUTTON_SQUARE);
			}
		} else
		if(item_is(STR_COLORSET)) {
			x=DrawButton(x, y, STR_LOAD, BUTTON_CROSS);
			x=DrawButton(x, y, STR_ADD, BUTTON_SQUARE);
			if(ITEMS_VALUE_NUMBER[ITEMS_POSITION]>0) {
				x=DrawButton(x, y, STR_DELETE, BUTTON_TRIANGLE);
			}
		}
		x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
	} else {
		x=DrawButton(x, y, STR_ENTER, BUTTON_CROSS);
		x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
		if(ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_SHOW[ITEMS_POSITION] == YES) {
				x=DrawButton(x, y, STR_CHANGE, BUTTON_SQUARE | BUTTON_TRIANGLE);
			}
		} else
		if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_COLORBOX) {
			x=DrawButton(x, y, STR_RESET, BUTTON_SQUARE);
		}
	}

}

void open_SETTINGS()
{
	start_loading();
	new_MENU();
#ifndef FILEMANAGER
	read_scan_dir();
#endif
	read_setting();
	GetFont();
	init_SETTINGS();
	MENU_SIDE=NO;
	Draw_MENU_input = &Draw_SETTINGS_input;
	input_MENU = &input_SETTINGS;
	end_loading();
}


//*******************************************************
// MODE AutoMount
//*******************************************************

u8 is_AutoMount()
{

	FILE* fp;
	
	fp = fopen("/dev_hdd0/vsh/pushlist/game.dat", "rb");
	if(fp==NULL) return FAILED;
	
	fgets(ManaGunZ_id, 10, fp);
	fclose(fp);
	
	char M_path[128];
	sprintf(M_path, "/dev_hdd0/game/%s/USRDIR/AutoMount", ManaGunZ_id);
	
	if(path_info(M_path) == _NOT_EXIST) return NO;
	
	return YES;
}

void AutoMount()
{

	if(read_AutoMount_setting()==FAILED) {
		print_load("Error : Failed to read AutoMount file");
		exit(0);
	}
	
	print_load("AutoMount = %s", list_game_path[0]);
	
	game_number=0;
	GetParamSFO("TITLE", list_game_title[0], 0, NULL);
	list_game_platform[0] = get_ext(list_game_path[0]);
	iso = is_iso(list_game_path[0]);
	usb = is_usb(list_game_path[0]);
	
	u8 Path_exist=NO;
	
	MountNTFS();
	
	//check GamPath
	if(path_info(GamPath)==_NOT_EXIST) {
		print_load("Warning : Game path not exist.");
		print_load("Searching in other ports");
		memset(temp_buffer, 0, sizeof(temp_buffer));
		if(strstr(GamPath, "/ntfs") != NULL) {
			strcpy(temp_buffer, &GamPath[5]);
			int i;
			for(i=0; i<8; i++) {
				sprintf(GamPath, "/ntfs%c:%s", 48+i, temp_buffer);
				if(path_info(GamPath)!=_NOT_EXIST) {
					print_load("Game found !");
					Path_exist=YES;
					break;
				}
			}
		}
		else {
			if(strstr(GamPath, "/dev_usb") != NULL) {
				strcpy(temp_buffer, &GamPath[11]);
			} else strcpy(temp_buffer, &GamPath[9]);
			int device;
			for(device=0; device<=10; device++) {
				if(device!=10) sprintf(GamPath, "/dev_usb00%c%s", 48+device, temp_buffer); else
				sprintf(GamPath, "/dev_hdd0%s", temp_buffer);
				if(path_info(GamPath) != _NOT_EXIST) {
					print_load("Game found !");
					Path_exist=YES;
					break;
				}
			}
		}
	} else Path_exist=YES;
	
	if(Path_exist==NO) {	
		end_loading();
		u8 LoopBreak=1;
		while(LoopBreak)
		{
			cls();
			
			float x=50, y=40;
			
			FontSize(20);
			FontColor(RED);
			
			DrawString(x, y, STR_NOGAME);
			y+=20;
			DrawFormatString(x, y, "%s = %s", STR_PATH, list_game_path[0]);
			
			x=INPUT_X;
			y=INPUT_Y;
			FontColor(COLOR_1);
			SetFontZ(0);			
			
			DrawButton(x, y, STR_BACKTOXMB, BUTTON_CIRCLE);
		
			tiny3d_Flip();
			ScreenShot();
			
			ps3pad_read();
			
			if(new_pad & BUTTON_CIRCLE) {
				ioPadEnd();
				LoopBreak=0;
				exit(0);
			}
		}
	}
	
	sleep(1);
	
	if(gui_called==YES) {
		end_loading();
		
		open_GameMenu();
		
		while(MENU){
			cls();
			
			Draw_MENU();
			Draw_MENU_input();
		
			check_device();
		
			tiny3d_Flip();
			ScreenShot();
		
			ps3pad_read();

			input_MENU();
		}
		
		write_AutoMount_setting(GamPath);
	}
	
	MountGame(list_game_path[0]);	
	
	end_loading();
	
	exit(0);

}

//*******************************************************
// Filter
//*******************************************************

u8 filter=NO;
u8 filter_position=0;

void open_filter()
{
	filter = YES;
	read_setting();
}

void close_filter()
{
	filter=NO;
	write_setting();
}

void input_filter()
{
	if(filter==NO) return;
	
	if(new_pad & BUTTON_CROSS) {
		if(filter_position==0) {
			if(Only_FAV==YES) Only_FAV=NO;
			else Only_FAV=YES;
		} else
		if(filter_position==1) {
			if(Show_PS3==YES) Show_PS3=NO;
			else Show_PS3=YES;
		} else
		if(filter_position==2) {
			if(Show_PS2==YES) Show_PS2=NO;
			else Show_PS2=YES;
		} else
		if(filter_position==3) {
			if(Show_PS1==YES) Show_PS1=NO;
			else Show_PS1=YES;
		} else
		if(filter_position==4) {
			if(Show_PSP==YES) Show_PSP=NO;
			else Show_PSP=YES;
		}
	}
	
	filter_x += R2JoyStick_X(BUTTON_L);
	filter_y += R2JoyStick_Y(BUTTON_L);
	
	if(new_pad & BUTTON_UP) {
		if(filter_position==0) filter_position=4;
		else filter_position--;
	}
	
	if(new_pad & BUTTON_DOWN) {
		if(filter_position==4) filter_position=0;
		else filter_position++;
	}
	
	if(new_pad & BUTTON_CIRCLE) {
		close_filter();
	}
}

void Draw_filter_input()
{
	if(filter==NO) return;
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	u8 is_checked=NO;
	
	if(filter_position==0) {
		if(Only_FAV==YES) is_checked=YES;
	} else
	if(filter_position==1) {
		if(Show_PS3==YES) is_checked=YES;
	} else
	if(filter_position==2) {
		if(Show_PS2==YES) is_checked=YES;
	} else
	if(filter_position==3) {
		if(Show_PS1==YES) is_checked=YES;
	} else
	if(filter_position==4) {
		if(Show_PSP==YES) is_checked=YES;
	}
	
	if(is_checked) x=DrawButton(x, y, STR_UNCHECK, BUTTON_CROSS);
	else x=DrawButton(x, y, STR_CHECK, BUTTON_CROSS);
	x=DrawButton(x, y, STR_MOVE, BUTTON_L);
	x=DrawButton(x, y, STR_BACK, BUTTON_CIRCLE);
}

void Draw_filter()
{
	if(filter==NO) return;
	
	SetFontZ(0);
	u32 color=0;
	float x=filter_x;
	float y=filter_y;
	
	if(PICTURE_offset[BOXBODY]) {
		tiny3d_SetTexture(0, PICTURE_offset[BOXBODY], PICTURE[BOXBODY].width, PICTURE[BOXBODY].height, PICTURE[BOXBODY].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, 0, 0, 100, 115, WHITE, YES);
	} else {
		Draw_Box(x, y, 0, 0, 100, 115, 0xC0C0C0FF, NO);
		Draw_Box(x+2, y+2, 0, 0, 100-4, 115-4, GREY, NO);
	}
	if(PICTURE_offset[BOXHEAD]) {
		tiny3d_SetTexture(0, PICTURE_offset[BOXHEAD], PICTURE[BOXHEAD].width, PICTURE[BOXHEAD].height, PICTURE[BOXHEAD].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, 0, 0, 100, 25, WHITE, YES);
	} else {
		Draw_BoxGradiant(VERTICAL, x+2, y+2, 0, 100-4, 25,  0x505050FF, 0x101010FF, NO);
	}
	
	FontSize(18);
	FontColor(COLOR_3);
	DrawStringFromCenterX(x+50, y+5, STR_FILTER);
	
	FontSize(15);
	x+=8;
	y+=30;
	if(filter_position==0) color = COLOR_2; else color = COLOR_1;
	Draw_checkbox(Only_FAV, x+5, y, STR_FAVORITE, color);
	y+=15;
	if(filter_position==1) color = COLOR_2; else color = COLOR_1;
	Draw_checkbox(Show_PS3, x+5, y, "PS3", color);
	y+=15;
	if(filter_position==2) color = COLOR_2; else color = COLOR_1;
	Draw_checkbox(Show_PS2, x+5, y, "PS2", color);
	y+=15;
	if(filter_position==3) color = COLOR_2; else color = COLOR_1;
	Draw_checkbox(Show_PS1, x+5, y, "PS1", color);
	y+=15;
	if(filter_position==4) color = COLOR_2; else color = COLOR_1;
	Draw_checkbox(Show_PSP, x+5, y, "PSP", color);
	
	FontColor(COLOR_1);
	
	if(Show_it(position) == NO) {
		int i;
		for(i=0; i<=game_number; i++) {
			if(position-i<0 && game_number<position+i) break;
			if(Show_it(position+i) == YES) {position+=i; break;}
			if(Show_it(position-i) == YES) {position-=i; break;}
		}
	}	
}

//*******************************************************
// USER INTERFACE
//*******************************************************

void TranslateTo(float *value, float target)
{
	float local;
	float TranslateSpeed = 1; 
	memcpy(&local, value, sizeof(float));
	
	if(local > target) {
		while(local-TranslateSpeed*10 > target ) 
			TranslateSpeed=TranslateSpeed*2;
	} else
	if(local < target) {
		while(local+TranslateSpeed*10 < target ) 
			TranslateSpeed=TranslateSpeed*2;
	}
	
	if((local - TranslateSpeed < target && target < local + TranslateSpeed) || MOVE_init==NO) {
		*value = target;
	} else
	if(local > target) {
		local -= TranslateSpeed;
		*value = local;
	} else
	if(local < target) {
		local += TranslateSpeed;
		*value = local;
	}
}

void RotateTo(float *value, float target)
{
	float local;
	float RotateSpeed = DEG(1);
	memcpy(&local, value, sizeof(float));
	
	if(local > target) {
		while(local-RotateSpeed*10 > target ) 
			RotateSpeed=RotateSpeed*2;
	} else
	if(local < target) {
		while(local+RotateSpeed*10 < target ) 
			RotateSpeed=RotateSpeed*2;
	}
	
	if((local - RotateSpeed < target && target < local + RotateSpeed) || MOVE_init==NO) {
		*value = target;
	} else
	if(local > target) {
		local -= RotateSpeed;
		*value = local;
	} else
	if(local < target) {
		local += RotateSpeed;
		*value = local;
	}
}

float FLOW_FakeZoom(float z)
{
    return 2-(z-10)/90;
}


//*******************************************************
// FLOW 3D
//*******************************************************

// ** TINY3D_QUAD_STRIP **
//
// ** FULL COVER OUVERT **
//
//	 BACK CORN COTE CORN FRONT
//	1----3----5----7----9----11
//  |  / |  / |  / |  / |  / |  
//	| /  | /  | /  | /  | /  |  
//  2----4----6----8----10---12
//
//
// ** Inferieur **
//					|
//	 CORN BACK      
//	5----3----1
//  | \  | \  |
//	|  \ |  \ |
//  6----4----2
//

void Draw_PS3COVER_3D()
{
	// la boite est de face
	
	//float l;
	
	float x=0,y=0,z=0; // 0,0,0 au centre du volume 
	
	x-=0.1; // pour avoir la jaquette autour de la boite
	
	float w=129; // largeur de la jaquette de face
	float h=149; // hauteur de la jaquettte de face
	float e=14+0.1; // epaisseur de la boite + 0.1 pixel de chaque coté pour garder la jaquette autour de la boite.
	float r=3; // rayon des arrondies

	
	float l_tot = w*2-2*r + e-2*r + PI*r;
	
	float SW=0; // longueur de la texture
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		
	tiny3d_VertexPos(x+w/2, y+h/2 , z+e/2);  // inferieur / haut / droite  [1]
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexTexture(0.0f, 0.0f);
	
	tiny3d_VertexPos(x+w/2, y-h/2 , z+e/2); // inferieur / bas / droite  [2]
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexTexture(0.0f, 1.0f);
	
	tiny3d_VertexPos(x-w/2 + r, y+h/2	, z+e/2); // inferieur / haut / gauche [3]
	tiny3d_Normal(0, 0, 1);
	SW += w-r;
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	 
	tiny3d_VertexPos(x-w/2 + r	, y-h/2	, z+e/2); // inferieur / bas / gauche [4]
	tiny3d_Normal(0, 0, 1);
	
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	// COIN INFERIEUR
	int t;
	for(t=80; t>=0 ; t-=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x-w/2+r - r*cos(t*PI/180), y+h/2 , z+e/2-r + r*sin(t*PI/180));  //  [5]
		tiny3d_Normal(-cos(t*PI/180), 0, sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		
		tiny3d_VertexPos(x-w/2+r - r*cos(t*PI/180), y-h/2 , z+e/2-r + r*sin(t*PI/180));  //  [6]
		tiny3d_Normal(-cos(t*PI/180), 0, sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += e-2*r;
	tiny3d_VertexPos(x-w/2, y+h/2, z-e/2+r);										// [7]
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	tiny3d_VertexPos(x-w/2, y-h/2, z-e/2+r);										// [8]
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f); 
	
	// COIN SUPERIEUR
	for(t=190; t<=270 ; t+=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x-w/2+r + r*cos(t*PI/180), y+h/2 , z-e/2+r + r*sin(t*PI/180));	// [9] 
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		tiny3d_VertexPos(x-w/2+r + r*cos(t*PI/180), y-h/2 , z-e/2+r + r*sin(t*PI/180));	// [10] 
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += w-r;
	tiny3d_VertexPos(x+w/2, y+h/2, z-e/2); // superieur / haut / droite 		// [11] 
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	
	tiny3d_VertexPos(x+w/2, y-h/2, z-e/2); // superieur / bas / droite 		// [12]
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	tiny3d_End();
	
}

void Draw_PS3COVER()
{
	
	float x=0,y=0,z=0; // 0,0,0 au centre du volume 
	
	x-=0.1; // pour avoir la jaquette autour de la boite
	
	float w=129; // largeur de la jaquette de face
	float h=149; // hauteur de la jaquettte de face
	float e=14+0.1; // epaisseur de la boite + 0.1 pixel de chaque coté pour garder la jaquette autour de la boite.
	float r=3; // rayon des arrondies
	
	float l_tot = w-r + PI*r/2 ;
	
	y=-h/2;
	x=-w/2;
	z=-e/2;
	
	float SW=0; // longueur de la texture
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	
	tiny3d_VertexPos(x, y+h, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture(0, 0.0f);
	tiny3d_VertexPos(x, y, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture(0, 1.0f); 
	
	// COIN SUPERIEUR
	int t;
	for(t=190; t<=270 ; t+=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x+r + r*cos(t*PI/180), y+h , z+r + r*sin(t*PI/180));
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		tiny3d_VertexPos(x+r + r*cos(t*PI/180), y , z+r + r*sin(t*PI/180));
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += w-r;
	tiny3d_VertexPos(x+w, y+h, z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	
	tiny3d_VertexPos(x+w, y, z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	tiny3d_End();
}

void Draw_PS3GAMECASE_3D()
{
	//float l;
	int t,i;
	
	float x=0,y=0,z=0; // 0,0,0 au centre du volume de la jaquette
	
	float w=129; // largeur de la jaquette de face
	float h=149; // hauteur de la jaquettte de face
	float e=14; // epaisseur de la boite 
	float r=3; // rayon des arrondies
	
	float wb = 135; // largeur de la boite
	float hb = 172; // hauteur de la boite
	//float l1 = 15; // hauteur de l'en-tete de la boite 
	float r1 = 7.5; // rayon du haut
	float l2 = 7; // distance entre le bas de la boite et la jaquette
	float r2 = 5; // rayon du bas
	
	float l3 = 36; // distance entre le bas et l'ouverture lateral
	
	x = -w/2;
	y = -h/2-l2;
	z = -e/2;
	
// surface superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - (r1-r)*sin(t*PI/180)   , y+hb-r1 + (r1-r)*cos(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos( x+wb-r1 + (r1-r)*sin(t*PI/180),y+hb-r1  + (r1-r)*cos((t)*PI/180), z );
		tiny3d_Normal(0, 0, -1);
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2    - (r2-r)*cos(t*PI/180), y+r2 - (r2-r)*sin(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos(x+wb-r2 + (r2-r)*cos(t*PI/180), y+r2 - (r2-r)*sin(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
	}
	tiny3d_End();
	
	
// arrondie superieur bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2   , y+r - r*sin(t*PI/180) , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), -cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r2, y+r - r*sin(t*PI/180) , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), -cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin superieur bas droit TORE
	for(t=270; t<=350; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie droit superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+r2     , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, -cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+hb-r1  , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, -cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin superieur haut droite TORE
	for(t=0; t<=80; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie haut superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 , y+hb-r + r*sin(t*PI/180), z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), -cos(t*PI/180));
		tiny3d_VertexPos(x+r1    , y+hb-r + r*sin(t*PI/180), z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), -cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin superieur haut gauche TORE
	for(t=90; t<=170; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie gauche superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r1 , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, -cos(t*PI/180));
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r2    , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, -cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin superieur haut gauche TORE
	for(t=180; t<=260; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// surface du bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb-r2, y, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+wb-r2, y, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+r2, y, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+r2, y, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_End();
	
// coin bas droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r2 + r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+r );
		tiny3d_Normal(sin(t*PI/180), -cos(t*PI/180), 0);
		tiny3d_VertexPos(x+wb-r2 + r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(sin(t*PI/180), -cos(t*PI/180), 0);
	}
	tiny3d_End();
	
// surfaces de droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+r2, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+r2, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+l3, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+l3, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+l3+5 - 5*cos(t*PI/180) , z+r );
		tiny3d_Normal(sin(t*PI/180), cos(t*PI/180), 0);
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+l3+5 - 5*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(sin(t*PI/180), cos(t*PI/180), 0);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb-5, y+l3+5, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+l3+5, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+hb-l3-5, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+hb-l3-5, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*cos(t*PI/180), y+hb-l3-5 + 5*sin(t*PI/180) , z+r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
		tiny3d_VertexPos(x+wb - 5*cos(t*PI/180), y+hb-l3-5 + 5*sin(t*PI/180) , z+e-r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-r1, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-r1, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();


	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+l3+5 - 5*cos(t*PI/180) , z+r );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+hb-l3-5 + 5*cos(t*PI/180) , z+r );
		tiny3d_Normal(0, 0, 1);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+l3+5 - 5*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+hb-l3-5 + 5*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(0, 0, -1);
	}
	tiny3d_End();
	
// coin haut droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 + r1*cos(t*PI/180), y+hb-r1 + r1*sin(t*PI/180) , z+r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
		tiny3d_VertexPos(x+wb-r1 + r1*cos(t*PI/180), y+hb-r1 + r1*sin(t*PI/180) , z+e-r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
	}
	tiny3d_End();
	
// surface du haut
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+r1, y+hb, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+r1, y+hb, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-r1, y+hb, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-r1, y+hb, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_End();
	
// coin haut gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r1 - r1*sin(t*PI/180), y+hb-r1 + r1*cos(t*PI/180) , z+r );
		tiny3d_Normal(-sin(t*PI/180), cos(t*PI/180), 0);
		tiny3d_VertexPos(x+r1 - r1*sin(t*PI/180), y+hb-r1 + r1*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(-sin(t*PI/180), cos(t*PI/180), 0);
	}
	tiny3d_End();
	
// surface de gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x, y+hb-r1, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+hb-r1, z+e-r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+r2, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+r2, z+e-r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_End();
	
	
// coin bas gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2 - r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+r );
		tiny3d_Normal(-sin(t*PI/180), -cos(t*PI/180), 0);
		tiny3d_VertexPos(x+r2 - r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(-sin(t*PI/180), -cos(t*PI/180), 0);
	}
	tiny3d_End();

// 	arrondie inferieur bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2   , y+r - r*sin(t*PI/180) , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r2, y+r - r*sin(t*PI/180) , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin inferieur bas droit TORE
	for(t=270; t<=350; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie droit inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+r2     , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+hb-r1  , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut droite TORE
	for(t=0; t<=80; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie haut inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 , y+hb-r + r*sin(t*PI/180), z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), cos(t*PI/180));
		tiny3d_VertexPos(x+r1    , y+hb-r + r*sin(t*PI/180), z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut gauche TORE
	for(t=90; t<=170; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie gauche inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r1 , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r2    , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut gauche TORE
	for(t=180; t<=270; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// surface inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2    - (r2-r)*sin(t*PI/180), y+r2 - (r2-r)*cos(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos(x+wb-r2 + (r2-r)*sin(t*PI/180), y+r2 - (r2-r)*cos(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - (r1-r)*cos(t*PI/180)   , y+hb-r1 + (r1-r)*sin(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos( x+wb-r1 + (r1-r)*cos(t*PI/180), y+hb-r1 + (r1-r)*sin((t)*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
	}
	tiny3d_End();
	
	// BR logo
	if(PICTURE_offset[BR_LOGO]) {
		tiny3d_SetPolygon(TINY3D_QUADS);
		tiny3d_VertexPos(x+wb-r1-20, y+hb-r   , z);
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexTexture(0.0f, 0.0f);
		tiny3d_VertexPos(x+wb-r1   , y+hb-r   , z);
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexTexture(1.0f, 0.0f);
		tiny3d_VertexPos(x+wb-r1   , y+hb-r-10, z);
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexTexture(1.0f, 1.0f);
		tiny3d_VertexPos(x+wb-r1-20, y+hb-r-10, z);
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexTexture(0.0f, 1.0f);
		tiny3d_End();
	}

/*
// ligne d'ouverture
	wb+=0.1f;
	hb+=0.1f;
	tiny3d_SetPolygon(TINY3D_LINE_LOOP);
	tiny3d_VertexColor(0x000000FF);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - r1*cos(t*PI/180)   , y+hb-r1 + r1*sin(t*PI/180), z+e/2 );
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+wb-r1 + r1*sin(t*PI/180)   , y+hb-r1 + r1*cos(t*PI/180), z+e/2 );
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+hb-l3-5 + 5*cos(t*PI/180) , z+e/2 );
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*cos(t*PI/180), y+l3+5 - 5*sin(t*PI/180) , z+e/2 );
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+wb-r2 - r2*cos(t*PI/180)   , y+r2 - r2*sin(t*PI/180), z+e/2 );
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r2 - r2*sin(t*PI/180)   , y+r2 - r2*cos(t*PI/180), z+e/2 );
	}
	tiny3d_End();
*/

/*	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	
// surface gauche
	tiny3d_VertexPos(x, y+hb , z);  // superieur / haut / gauche  
	tiny3d_VertexPos(x, y+hb , z+e);  // inferieur / haut / gauche 
	tiny3d_VertexPos(x, y , z);  // superieur / bas / gauche
	tiny3d_VertexPos(x, y , z+e);  // superieur / bas / gauche

// surface du bas
	tiny3d_VertexPos(x+wb, y, z+e);  // inferieur / bas / droite  
	tiny3d_VertexPos(x, y , z);  // superieur / bas / gauche 
	tiny3d_VertexPos(x+wb, y , z);  // superieur / bas / droite
	
// surface superieur
	tiny3d_VertexPos(x, y+hb , z);  // superieur / haut / gauche  
	tiny3d_VertexPos(x+wb, y+hb, z);  // superieur / haut / droite 

// surface du haut
	tiny3d_VertexPos(x, y+hb , z+e);  // inferieur / haut / gauche  
	tiny3d_VertexPos(x+wb, y+hb, z+e);  // inferieur / haut / droite
	
// surface inferieur
	tiny3d_VertexPos(x, y , z+e);  // inferieur / bas / gauche  
	tiny3d_VertexPos(x+wb, y, z+e);  // inferieur / bas / droite
	
// surface droite
	tiny3d_VertexPos(x+wb, y , z);  // superieur / bas / droite  
	tiny3d_VertexPos(x+wb, y+hb, z+e);  // inferieur / haut / droite
	tiny3d_VertexPos(x+wb, y+hb, z);  // superieur / haut / droite
	
	tiny3d_End();
*/

}

void Draw_PS2COVER()
{
	float x=0,y=0,z=0; // 0,0,0 au centre du volume 
	
	x-=0.1; // pour avoir la jaquette autour de la boite
	
	float w=130; // largeur de la jaquette de face
	float h=180; // hauteur de la jaquettte de face
	float e=14+0.1; // epaisseur de la boite + 0.1 pixel de chaque coté pour garder la jaquette autour de la boite.
	float r=3; // rayon des arrondies

	float l_tot = w-r + PI*r/2 ;
	
	y=-h/2;
	x=-w/2;
	z=-e/2;
	
	float SW=0; // longueur de la texture
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	
	tiny3d_VertexPos(x, y+h, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture(0, 0.0f);
	tiny3d_VertexPos(x, y, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture(0, 1.0f); 
	
	// COIN SUPERIEUR
	int t;
	for(t=190; t<=270 ; t+=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x+r + r*cos(t*PI/180), y+h , z+r + r*sin(t*PI/180));
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		tiny3d_VertexPos(x+r + r*cos(t*PI/180), y , z+r + r*sin(t*PI/180));
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += w-r;
	tiny3d_VertexPos(x+w, y+h, z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	
	tiny3d_VertexPos(x+w, y, z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	tiny3d_End();
}

void Draw_PS2COVER_3D()
{
	// la boite est de face
	
	//float l;
	
	float x=0,y=0,z=0; // 0,0,0 au centre du volume 
	
	x-=0.1; // pour avoir la jaquette autour de la boite
	
	float w=130; // largeur de la jaquette de face
	float h=180; // hauteur de la jaquettte de face
	float e=14+0.1; // epaisseur de la boite + 0.1 pixel de chaque coté pour garder la jaquette autour de la boite.
	float r=3; // rayon des arrondies

	
	float l_tot = w*2-2*r + e-2*r + PI*r;
	
	float SW=0; // longueur de la texture
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		
	tiny3d_VertexPos(x+w/2, y+h/2 , z+e/2);  // inferieur / haut / droite  [1]
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexTexture(0.0f, 0.0f);
	
	tiny3d_VertexPos(x+w/2, y-h/2 , z+e/2); // inferieur / bas / droite  [2]
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexTexture(0.0f, 1.0f);
	
	tiny3d_VertexPos(x-w/2 + r, y+h/2	, z+e/2); // inferieur / haut / gauche [3]
	tiny3d_Normal(0, 0, 1);
	SW += w-r;
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	 
	tiny3d_VertexPos(x-w/2 + r	, y-h/2	, z+e/2); // inferieur / bas / gauche [4]
	tiny3d_Normal(0, 0, 1);
	
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	// COIN INFERIEUR
	int t;
	for(t=80; t>=0 ; t-=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x-w/2+r - r*cos(t*PI/180), y+h/2 , z+e/2-r + r*sin(t*PI/180));  //  [5]
		tiny3d_Normal(-cos(t*PI/180), 0, sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		
		tiny3d_VertexPos(x-w/2+r - r*cos(t*PI/180), y-h/2 , z+e/2-r + r*sin(t*PI/180));  //  [6]
		tiny3d_Normal(-cos(t*PI/180), 0, sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += e-2*r;
	tiny3d_VertexPos(x-w/2, y+h/2, z-e/2+r);										// [7]
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	tiny3d_VertexPos(x-w/2, y-h/2, z-e/2+r);										// [8]
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f); 
	
	// COIN SUPERIEUR
	for(t=190; t<=270 ; t+=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x-w/2+r + r*cos(t*PI/180), y+h/2 , z-e/2+r + r*sin(t*PI/180));	// [9] 
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		tiny3d_VertexPos(x-w/2+r + r*cos(t*PI/180), y-h/2 , z-e/2+r + r*sin(t*PI/180));	// [10] 
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += w-r;
	tiny3d_VertexPos(x+w/2, y+h/2, z-e/2); // superieur / haut / droite 		// [11] 
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	
	tiny3d_VertexPos(x+w/2, y-h/2, z-e/2); // superieur / bas / droite 		// [12]
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	tiny3d_End();
	
}

void Draw_PS2GAMECASE_3D()
{
	//float l;
	int t,i;
	
	float x=0,y=0,z=0; // 0,0,0 au centre du volume de la jaquette
	
	float w=129; // largeur de la jaquette de face
	float h=180; // hauteur de la jaquettte de face
	float e=14; // epaisseur de la boite 
	float r=3; // rayon des arrondies
	
	float wb = 135; // largeur de la boite
	float hb = 190; // hauteur de la boite
	//float l1 = 15; // hauteur de l'en-tete de la boite 
	float r1 = 5; // rayon du haut
	float l2 = 5; // distance entre le coté de la boite et la jaquette = distance entre le bas de la boite et la jaquette
	float r2 = 5; // rayon du bas
	
	float l3 = 50; // distance entre le bas et l'ouverture lateral
	
	x = -w/2;
	y = -h/2-l2;
	z = -e/2;
	
// surface superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - (r1-r)*sin(t*PI/180)   , y+hb-r1 + (r1-r)*cos(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos( x+wb-r1 + (r1-r)*sin(t*PI/180),y+hb-r1  + (r1-r)*cos((t)*PI/180), z );
		tiny3d_Normal(0, 0, -1);
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2    - (r2-r)*cos(t*PI/180), y+r2 - (r2-r)*sin(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos(x+wb-r2 + (r2-r)*cos(t*PI/180), y+r2 - (r2-r)*sin(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
	}
	tiny3d_End();
	
	
// arrondie superieur bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2   , y+r - r*sin(t*PI/180) , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), -cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r2, y+r - r*sin(t*PI/180) , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), -cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin superieur bas droit TORE
	for(t=270; t<=350; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie droit superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+r2     , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, -cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+hb-r1  , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, -cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin superieur haut droite TORE
	for(t=0; t<=80; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie haut superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 , y+hb-r + r*sin(t*PI/180), z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), -cos(t*PI/180));
		tiny3d_VertexPos(x+r1    , y+hb-r + r*sin(t*PI/180), z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), -cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin superieur haut gauche TORE
	for(t=90; t<=170; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie gauche superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r1 , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, -cos(t*PI/180));
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r2    , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, -cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin superieur haut gauche TORE
	for(t=180; t<=260; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// surface du bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb-r2, y, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+wb-r2, y, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+r2, y, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+r2, y, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_End();
	
// coin bas droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r2 + r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+r );
		tiny3d_Normal(sin(t*PI/180), -cos(t*PI/180), 0);
		tiny3d_VertexPos(x+wb-r2 + r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(sin(t*PI/180), -cos(t*PI/180), 0);
	}
	tiny3d_End();
	
// surfaces de droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+r2, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+r2, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+l3, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+l3, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+l3, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb, y+l3, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-5, y+l3, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-5, y+l3, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb-5, y+l3, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+l3, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+hb-l3, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+hb-l3, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+wb-5, y+hb-l3, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+wb-5, y+hb-l3, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-r1, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-r1, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();

	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+l3, z+r );
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexPos(x+wb-5, y+l3 , z+r );
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+r );
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexPos(x+wb-5, y+hb-l3, z+r );
	tiny3d_Normal(0, 0, 1);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+l3, z+e-r );
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexPos(x+wb-5, y+l3 , z+e-r );
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+e-r );
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexPos(x+wb-5, y+hb-l3, z+e-r );
	tiny3d_Normal(0, 0, -1);
	tiny3d_End();
	
// coin haut droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 + r1*cos(t*PI/180), y+hb-r1 + r1*sin(t*PI/180) , z+r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
		tiny3d_VertexPos(x+wb-r1 + r1*cos(t*PI/180), y+hb-r1 + r1*sin(t*PI/180) , z+e-r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
	}
	tiny3d_End();
	
// surface du haut
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+r1, y+hb, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+r1, y+hb, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-r1, y+hb, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-r1, y+hb, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_End();
	
// coin haut gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r1 - r1*sin(t*PI/180), y+hb-r1 + r1*cos(t*PI/180) , z+r );
		tiny3d_Normal(-sin(t*PI/180), cos(t*PI/180), 0);
		tiny3d_VertexPos(x+r1 - r1*sin(t*PI/180), y+hb-r1 + r1*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(-sin(t*PI/180), cos(t*PI/180), 0);
	}
	tiny3d_End();
	
// surface de gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x, y+hb-r1, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+hb-r1, z+e-r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+r2, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+r2, z+e-r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_End();
	
	
// coin bas gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2 - r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+r );
		tiny3d_Normal(-sin(t*PI/180), -cos(t*PI/180), 0);
		tiny3d_VertexPos(x+r2 - r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(-sin(t*PI/180), -cos(t*PI/180), 0);
	}
	tiny3d_End();

// 	arrondie inferieur bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2   , y+r - r*sin(t*PI/180) , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r2, y+r - r*sin(t*PI/180) , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin inferieur bas droit TORE
	for(t=270; t<=350; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie droit inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+r2     , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+hb-r1  , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut droite TORE
	for(t=0; t<=80; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie haut inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 , y+hb-r + r*sin(t*PI/180), z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), cos(t*PI/180));
		tiny3d_VertexPos(x+r1    , y+hb-r + r*sin(t*PI/180), z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut gauche TORE
	for(t=90; t<=170; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie gauche inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r1 , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r2    , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut gauche TORE
	for(t=180; t<=270; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// surface inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2    - (r2-r)*sin(t*PI/180), y+r2 - (r2-r)*cos(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos(x+wb-r2 + (r2-r)*sin(t*PI/180), y+r2 - (r2-r)*cos(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - (r1-r)*cos(t*PI/180)   , y+hb-r1 + (r1-r)*sin(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos( x+wb-r1 + (r1-r)*cos(t*PI/180), y+hb-r1 + (r1-r)*sin((t)*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
	}
	tiny3d_End();

	
}

void Draw_PS1COVER_FRONT()
{
	float x=0,y=0,z=0; // 0,0,0 au centre du volume 
		
	float wb = 140; // largeur de la boite
	float hb = 130; // hauteur de la boite
	
	float w=126; // largeur de la jaquette de face
	float e=15+0.2; // epaisseur de la boite + 0.1 pixel de chaque coté pour garder la jaquette autour de la boite.
	float r=2; // rayon des arrondies

	float l=wb-r-w; // largeur de la marge noire à gauche

// x,y,z : superieur bas gauche
	x = -wb/2;
	y = -hb/2;
	z = -e/2; 
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	
	tiny3d_VertexPos(x+l, y+hb-r , z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture(0.0f, 0.0f);
	
	tiny3d_VertexPos(x+l, y+r , z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture(0.0f, 1.0f);
	
	tiny3d_VertexPos(x+wb-r, y+hb-r	, z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture(1.0f, 0.0f);
	 
	tiny3d_VertexPos(x+wb-r, y+r	, z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture(1.0f, 1.0f);
	
	tiny3d_End();
}

void Draw_PS1COVER_BACK()
{
	float x=0,y=0,z=0; // 0,0,0 au centre du volume 
		
	float wb = 140+0.2; // largeur de la boite
	float hb = 130; // hauteur de la boite
	
	float e=15+0.2; // epaisseur de la boite + 0.1 pixel de chaque coté pour garder la jaquette autour de la boite.
	float r=2; // rayon des arrondies

// x,y,z : superieur bas gauche
	x = -wb/2;
	y = -hb/2;
	z = -e/2;
	
	float l_tot = wb-2*r + 2*(e-r) + PI*r;
	
	float SW=0; // longueur de la texture
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		
	tiny3d_VertexPos(x+wb, y+hb-r , z+r);  
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexTexture(0.0f, 0.0f);

	tiny3d_VertexPos(x+wb, y+r , z+r); 
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexTexture(0.0f, 1.0f);
	
	tiny3d_VertexPos(x+wb, y+hb-r , z+e-r); 
	tiny3d_Normal(1, 0, 0);
	SW+=e-r;
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);

	tiny3d_VertexPos(x+wb, y+r , z+e-r); 
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);

	int t;
	for(t=10; t<=90; t+=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x+wb-r + r*cos(t*PI/180), y+hb-r  , z+e-r + r*sin(t*PI/180) );
		tiny3d_Normal(cos(t*PI/180), 0, sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		
		tiny3d_VertexPos(x+wb-r + r*cos(t*PI/180), y+r    , z+e-r + r*sin(t*PI/180) );
		tiny3d_Normal(cos(t*PI/180), 0, sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	}
	
	SW += wb-2*r;
	tiny3d_VertexPos(x+r, y+hb-r, z+e);
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	
	tiny3d_VertexPos(x+r, y+r, z+e);
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f); 
	
	for(t=10; t<=90; t+=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r    , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	}
	
	SW += e-r;
	tiny3d_VertexPos(x, y+hb-r, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	
	tiny3d_VertexPos(x, y+r, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f); 
	
	tiny3d_End();
	
}

void Draw_PS1GAMECASE_3D()
{
	//float l;
	int t,i;
	
	float x=0,y=0,z=0; // 0,0,0 au centre du volume
	
	float e=15; // epaisseur de la boite 
	float wb=140; // largeur de la boite
	float hb=130; // hauteur de la boite
	
	float r=2; // rayon des bordures
	float r1=r, r2=r;
	
	float w=126; // largeur de la jaquette de face 

	float l=wb-r-w; // largeur de la marge noire à gauche

	x = -wb/2;
	y = -hb/2;
	z = -e/2;
	
// surface superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - (r1-r)*sin(t*PI/180)   , y+hb-r1 + (r1-r)*cos(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos( x+wb-r1 + (r1-r)*sin(t*PI/180),y+hb-r1  + (r1-r)*cos((t)*PI/180), z );
		tiny3d_Normal(0, 0, -1);
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2    - (r2-r)*cos(t*PI/180), y+r2 - (r2-r)*sin(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos(x+wb-r2 + (r2-r)*cos(t*PI/180), y+r2 - (r2-r)*sin(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
	}
	tiny3d_End();
	
	
// arrondie superieur bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2   , y+r - r*sin(t*PI/180) , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), -cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r2, y+r - r*sin(t*PI/180) , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), -cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin superieur bas droit TORE
	for(t=270; t<=350; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie droit superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+r2     , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, -cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+hb-r1  , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, -cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin superieur haut droite TORE
	for(t=0; t<=80; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie haut superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 , y+hb-r + r*sin(t*PI/180), z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), -cos(t*PI/180));
		tiny3d_VertexPos(x+r1    , y+hb-r + r*sin(t*PI/180), z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), -cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin superieur haut gauche TORE
	for(t=90; t<=170; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie gauche superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r1 , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, -cos(t*PI/180));
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r2    , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, -cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin superieur haut gauche TORE
	for(t=180; t<=260; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// surface du bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb-r2, y, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+wb-r2, y, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+r2, y, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+r2, y, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_End();
	
// coin bas droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r2 + r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+r );
		tiny3d_Normal(sin(t*PI/180), -cos(t*PI/180), 0);
		tiny3d_VertexPos(x+wb-r2 + r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(sin(t*PI/180), -cos(t*PI/180), 0);
	}
	tiny3d_End();
	
// surfaces de droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+r2, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+r2, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-r1, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-r1, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();
	
// coin haut droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 + r1*cos(t*PI/180), y+hb-r1 + r1*sin(t*PI/180) , z+r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
		tiny3d_VertexPos(x+wb-r1 + r1*cos(t*PI/180), y+hb-r1 + r1*sin(t*PI/180) , z+e-r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
	}
	tiny3d_End();
	
// surface du haut
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+r1, y+hb, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+r1, y+hb, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-r1, y+hb, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-r1, y+hb, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_End();
	
// coin haut gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r1 - r1*sin(t*PI/180), y+hb-r1 + r1*cos(t*PI/180) , z+r );
		tiny3d_Normal(-sin(t*PI/180), cos(t*PI/180), 0);
		tiny3d_VertexPos(x+r1 - r1*sin(t*PI/180), y+hb-r1 + r1*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(-sin(t*PI/180), cos(t*PI/180), 0);
	}
	tiny3d_End();
	
// surface de gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x, y+hb-r1, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+hb-r1, z+e-r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+r2, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+r2, z+e-r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_End();
	
	
// coin bas gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2 - r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+r );
		tiny3d_Normal(-sin(t*PI/180), -cos(t*PI/180), 0);
		tiny3d_VertexPos(x+r2 - r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(-sin(t*PI/180), -cos(t*PI/180), 0);
	}
	tiny3d_End();

// 	arrondie inferieur bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2   , y+r - r*sin(t*PI/180) , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r2, y+r - r*sin(t*PI/180) , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin inferieur bas droit TORE
	for(t=270; t<=350; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie droit inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+r2     , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+hb-r1  , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut droite TORE
	for(t=0; t<=80; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie haut inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 , y+hb-r + r*sin(t*PI/180), z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), cos(t*PI/180));
		tiny3d_VertexPos(x+r1    , y+hb-r + r*sin(t*PI/180), z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut gauche TORE
	for(t=90; t<=170; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie gauche inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r1 , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r2    , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut gauche TORE
	for(t=180; t<=270; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// surface inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2    - (r2-r)*sin(t*PI/180), y+r2 - (r2-r)*cos(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos(x+wb-r2 + (r2-r)*sin(t*PI/180), y+r2 - (r2-r)*cos(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - (r1-r)*cos(t*PI/180)   , y+hb-r1 + (r1-r)*sin(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos( x+wb-r1 + (r1-r)*cos(t*PI/180), y+hb-r1 + (r1-r)*sin((t)*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
	}
	tiny3d_End();
	
	
	if(PICTURE_offset[PS_LOGO]) {
	
		float l_tot = l-1-r + PI*r/2 ;
	
		float SW=0; // longueur de la texture
		
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		
		tiny3d_VertexPos(x, y+hb-r, z+r);
		tiny3d_Normal(-1, 0, 0);
		tiny3d_VertexTexture(0, 0.0f);
		tiny3d_VertexPos(x, y+r, z+r);
		tiny3d_Normal(-1, 0, 0);
		tiny3d_VertexTexture(0, 1.0f); 
		
		// COIN SUPERIEUR
		for(t=190; t<=270 ; t+=10) {
			SW += (PI*r) * 10/180;
			
			tiny3d_VertexPos(x+r + r*cos(t*PI/180), y+hb-r , z+r + r*sin(t*PI/180));
			tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
			tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
			tiny3d_VertexPos(x+r + r*cos(t*PI/180), y+r , z+r + r*sin(t*PI/180));
			tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
			tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
			
		}
		
		
		SW += l-1-r;
		tiny3d_VertexPos(x+l-1, y+hb-r, z);
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		
		tiny3d_VertexPos(x+l-1, y+r, z);
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
		tiny3d_End();
	}
}

void Draw_PSPCOVER()
{
	float x=0,y=0,z=0; // 0,0,0 au centre du volume 
	
	x-=0.1; // pour avoir la jaquette autour de la boite

	float w=92; // largeur de la jaquette de face
	float h=158; // hauteur de la jaquettte de face
	float e=14+0.1; // epaisseur de la boite + 0.1 pixel de chaque coté pour garder la jaquette autour de la boite.
	float r=3; // rayon des arrondies

	float l_tot = w-r + PI*r/2 ;
	
	y=-h/2;
	x=-w/2;
	z=-e/2;
	
	float SW=0; // longueur de la texture
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	
	tiny3d_VertexPos(x, y+h, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture(0, 0.0f);
	tiny3d_VertexPos(x, y, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture(0, 1.0f); 
	
	// COIN SUPERIEUR
	int t;
	for(t=190; t<=270 ; t+=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x+r + r*cos(t*PI/180), y+h , z+r + r*sin(t*PI/180));
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		tiny3d_VertexPos(x+r + r*cos(t*PI/180), y , z+r + r*sin(t*PI/180));
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += w-r;
	tiny3d_VertexPos(x+w, y+h, z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	
	tiny3d_VertexPos(x+w, y, z);
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	tiny3d_End();
}

void Draw_PSPCOVER_3D()
{
	// la boite est de face
	
	//float l;
	
	float x=0,y=0,z=0; // 0,0,0 au centre du volume 
	
	x-=0.1; // pour avoir la jaquette autour de la boite

	float w=92; // largeur de la jaquette de face
	float h=158; // hauteur de la jaquettte de face
	float e=14+0.1; // epaisseur de la boite + 0.1 pixel de chaque coté pour garder la jaquette autour de la boite.
	float r=3; // rayon des arrondies

	float l_tot = w*2-2*r + e-2*r + PI*r;
	
	float SW=0; // longueur de la texture
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		
	tiny3d_VertexPos(x+w/2, y+h/2 , z+e/2);  // inferieur / haut / droite  [1]
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexTexture(0.0f, 0.0f);
	
	tiny3d_VertexPos(x+w/2, y-h/2 , z+e/2); // inferieur / bas / droite  [2]
	tiny3d_Normal(0, 0, 1);
	tiny3d_VertexTexture(0.0f, 1.0f);
	
	tiny3d_VertexPos(x-w/2 + r, y+h/2	, z+e/2); // inferieur / haut / gauche [3]
	tiny3d_Normal(0, 0, 1);
	SW += w-r;
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	 
	tiny3d_VertexPos(x-w/2 + r	, y-h/2	, z+e/2); // inferieur / bas / gauche [4]
	tiny3d_Normal(0, 0, 1);
	
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	// COIN INFERIEUR
	int t;
	for(t=80; t>=0 ; t-=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x-w/2+r - r*cos(t*PI/180), y+h/2 , z+e/2-r + r*sin(t*PI/180));  //  [5]
		tiny3d_Normal(-cos(t*PI/180), 0, sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		
		tiny3d_VertexPos(x-w/2+r - r*cos(t*PI/180), y-h/2 , z+e/2-r + r*sin(t*PI/180));  //  [6]
		tiny3d_Normal(-cos(t*PI/180), 0, sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += e-2*r;
	tiny3d_VertexPos(x-w/2, y+h/2, z-e/2+r);										// [7]
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	tiny3d_VertexPos(x-w/2, y-h/2, z-e/2+r);										// [8]
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f); 
	
	// COIN SUPERIEUR
	for(t=190; t<=270 ; t+=10) {
		SW += (PI*r) * 10/180;
		
		tiny3d_VertexPos(x-w/2+r + r*cos(t*PI/180), y+h/2 , z-e/2+r + r*sin(t*PI/180));	// [9] 
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
		tiny3d_VertexPos(x-w/2+r + r*cos(t*PI/180), y-h/2 , z-e/2+r + r*sin(t*PI/180));	// [10] 
		tiny3d_Normal(0, cos(t*PI/180), sin(t*PI/180));
		tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
		
	}
	
	SW += w-r;
	tiny3d_VertexPos(x+w/2, y+h/2, z-e/2); // superieur / haut / droite 		// [11] 
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 0.0f);
	
	tiny3d_VertexPos(x+w/2, y-h/2, z-e/2); // superieur / bas / droite 		// [12]
	tiny3d_Normal(0, 0, -1);
	tiny3d_VertexTexture((float) SW / l_tot, 1.0f);
	
	tiny3d_End();
	
}

void Draw_PSPGAMECASE_3D()
{
	//float l;
	int t,i;
	
	float x=0,y=0,z=0; // 0,0,0 au centre du volume de la jaquette
	
	float w=92; // largeur de la jaquette de face
	float h=158; // hauteur de la jaquettte de face
	float e=14; // epaisseur de la boite 
	float r=3; // rayon des arrondies
	
	float wb = 99; // largeur de la boite
	float hb = 168; // hauteur de la boite
	//float l1 = 15; // hauteur de l'en-tete de la boite 
	float r1 = 5; // rayon du haut
	float l2 = 5; // distance entre le coté de la boite et la jaquette
	float r2 = 5; // rayon du bas
	
	float l3 = 36; // distance entre le bas et l'ouverture lateral
	
	x = -w/2;
	y = -h/2-l2;
	z = -e/2;
	
// surface superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - (r1-r)*sin(t*PI/180)   , y+hb-r1 + (r1-r)*cos(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos( x+wb-r1 + (r1-r)*sin(t*PI/180),y+hb-r1  + (r1-r)*cos((t)*PI/180), z );
		tiny3d_Normal(0, 0, -1);
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2    - (r2-r)*cos(t*PI/180), y+r2 - (r2-r)*sin(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos(x+wb-r2 + (r2-r)*cos(t*PI/180), y+r2 - (r2-r)*sin(t*PI/180), z );
		tiny3d_Normal(0, 0, -1);
	}
	tiny3d_End();
	
	
// arrondie superieur bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2   , y+r - r*sin(t*PI/180) , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), -cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r2, y+r - r*sin(t*PI/180) , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), -cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin superieur bas droit TORE
	for(t=270; t<=350; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie droit superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+r2     , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, -cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+hb-r1  , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, -cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin superieur haut droite TORE
	for(t=0; t<=80; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie haut superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 , y+hb-r + r*sin(t*PI/180), z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), -cos(t*PI/180));
		tiny3d_VertexPos(x+r1    , y+hb-r + r*sin(t*PI/180), z+r - r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), -cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin superieur haut gauche TORE
	for(t=90; t<=170; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie gauche superieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r1 , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, -cos(t*PI/180));
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r2    , z+r - r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, -cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin superieur haut gauche TORE
	for(t=180; t<=260; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=270; i<=360; i+=10) {
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// surface du bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb-r2, y, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+wb-r2, y, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+r2, y, z+r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_VertexPos(x+r2, y, z+e-r);
	tiny3d_Normal(0, -1, 0);
	tiny3d_End();
	
// coin bas droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r2 + r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+r );
		tiny3d_Normal(sin(t*PI/180), -cos(t*PI/180), 0);
		tiny3d_VertexPos(x+wb-r2 + r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(sin(t*PI/180), -cos(t*PI/180), 0);
	}
	tiny3d_End();
	
// surfaces de droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+r2, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+r2, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+l3, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+l3, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+l3+5 - 5*cos(t*PI/180) , z+r );
		tiny3d_Normal(sin(t*PI/180), cos(t*PI/180), 0);
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+l3+5 - 5*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(sin(t*PI/180), cos(t*PI/180), 0);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb-5, y+l3+5, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+l3+5, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+hb-l3-5, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb-5, y+hb-l3-5, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*cos(t*PI/180), y+hb-l3-5 + 5*sin(t*PI/180) , z+r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
		tiny3d_VertexPos(x+wb - 5*cos(t*PI/180), y+hb-l3-5 + 5*sin(t*PI/180) , z+e-r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-l3, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-r1, z+r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_VertexPos(x+wb, y+hb-r1, z+e-r);
	tiny3d_Normal(1, 0, 0);
	tiny3d_End();


	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+l3+5 - 5*cos(t*PI/180) , z+r );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+hb-l3-5 + 5*cos(t*PI/180) , z+r );
		tiny3d_Normal(0, 0, 1);
	}
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+l3+5 - 5*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(0, 0, -1);
		tiny3d_VertexPos(x+wb - 5*sin(t*PI/180), y+hb-l3-5 + 5*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(0, 0, -1);
	}
	tiny3d_End();
	
// coin haut droite
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 + r1*cos(t*PI/180), y+hb-r1 + r1*sin(t*PI/180) , z+r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
		tiny3d_VertexPos(x+wb-r1 + r1*cos(t*PI/180), y+hb-r1 + r1*sin(t*PI/180) , z+e-r );
		tiny3d_Normal(cos(t*PI/180), sin(t*PI/180), 0);
	}
	tiny3d_End();
	
// surface du haut
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x+r1, y+hb, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+r1, y+hb, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-r1, y+hb, z+r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_VertexPos(x+wb-r1, y+hb, z+e-r);
	tiny3d_Normal(0, 1, 0);
	tiny3d_End();
	
// coin haut gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r1 - r1*sin(t*PI/180), y+hb-r1 + r1*cos(t*PI/180) , z+r );
		tiny3d_Normal(-sin(t*PI/180), cos(t*PI/180), 0);
		tiny3d_VertexPos(x+r1 - r1*sin(t*PI/180), y+hb-r1 + r1*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(-sin(t*PI/180), cos(t*PI/180), 0);
	}
	tiny3d_End();
	
// surface de gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	tiny3d_VertexPos(x, y+hb-r1, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+hb-r1, z+e-r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+r2, z+r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_VertexPos(x, y+r2, z+e-r);
	tiny3d_Normal(-1, 0, 0);
	tiny3d_End();
	
	
// coin bas gauche
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2 - r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+r );
		tiny3d_Normal(-sin(t*PI/180), -cos(t*PI/180), 0);
		tiny3d_VertexPos(x+r2 - r2*sin(t*PI/180), y+r2 - r2*cos(t*PI/180) , z+e-r );
		tiny3d_Normal(-sin(t*PI/180), -cos(t*PI/180), 0);
	}
	tiny3d_End();

// 	arrondie inferieur bas
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2   , y+r - r*sin(t*PI/180) , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r2, y+r - r*sin(t*PI/180) , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, -sin(t*PI/180), cos(t*PI/180));
	}
	tiny3d_End();

// arrondie coin inferieur bas droit TORE
	for(t=270; t<=350; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// arrondie droit inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+r2     , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexPos(x+wb-r + r*sin(t*PI/180), y+hb-r1  , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(sin(t*PI/180), 0, cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut droite TORE
	for(t=0; t<=80; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+wb-r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie haut inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+wb-r1 , y+hb-r + r*sin(t*PI/180), z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), cos(t*PI/180));
		tiny3d_VertexPos(x+r1    , y+hb-r + r*sin(t*PI/180), z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(0, sin(t*PI/180), cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut gauche TORE
	for(t=90; t<=170; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r1 + ((r1-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+hb-r1 + ((r1-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}

// arrondie gauche inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+hb-r1 , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
		tiny3d_VertexPos(x+r - r*sin(t*PI/180), y+r2    , z+e-r + r*cos(t*PI/180) );
		tiny3d_Normal(-sin(t*PI/180), 0, cos(t*PI/180));
	}
	tiny3d_End();
	
// arrondie coin inferieur haut gauche TORE
	for(t=180; t<=270; t+=10) {
		tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
		for(i=0; i<=90; i+=10) {
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos(t*PI/180)      , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin(t*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos(t*PI/180), cos(i*PI/180)*sin(t*PI/180), sin(i*PI/180));
			tiny3d_VertexPos(x+r2 + ((r2-r)+r*cos(i*PI/180))*cos((t+10)*PI/180) , y+r2 + ((r2-r)+r*cos(i*PI/180))*sin((t+10)*PI/180) , z+e-r +  r*sin(i*PI/180) );
			tiny3d_Normal(cos(i*PI/180)*cos((t+10)*PI/180), cos(i*PI/180)*sin((t+10)*PI/180), sin(i*PI/180));
		}
		tiny3d_End();
	}
	
// surface inferieur
	tiny3d_SetPolygon(TINY3D_QUAD_STRIP);
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos(x+r2    - (r2-r)*sin(t*PI/180), y+r2 - (r2-r)*cos(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos(x+wb-r2 + (r2-r)*sin(t*PI/180), y+r2 - (r2-r)*cos(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
	}
	for(t=0; t<=90; t+=10) {
		tiny3d_VertexPos( x+r1 - (r1-r)*cos(t*PI/180)   , y+hb-r1 + (r1-r)*sin(t*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
		tiny3d_VertexPos( x+wb-r1 + (r1-r)*cos(t*PI/180), y+hb-r1 + (r1-r)*sin((t)*PI/180), z+e );
		tiny3d_Normal(0, 0, 1);
	}
	tiny3d_End();

}

void update_3DFLOW()
{
	float e=0;
	int i;
	
	if(ITEM_moveZ[position]==0) MOVE_init=NO;
	
	int previous=-1;
	int next=-1;
	
	e=170;
	for(i=position+1; i<=game_number; i++) {
		if(Show_it(i) == NO) continue;
		TranslateTo(&ITEM_moveX[i], e);
		TranslateTo(&ITEM_moveY[i], 0.0);
		TranslateTo(&ITEM_moveZ[i], 700.0);
		RotateTo(&ITEM_angleX[i], 0.0);
		RotateTo(&ITEM_angleY[i], -PI/2);
		RotateTo(&ITEM_angleZ[i], 0.0);
		e+=30;
		
		if(next==-1) next=i;
	}
	
	e=-170;
	for(i=position-1; i>=0; i--) {
		if(Show_it(i) == NO) continue;
		TranslateTo(&ITEM_moveX[i], e);
		TranslateTo(&ITEM_moveY[i], 0.0);
		TranslateTo(&ITEM_moveZ[i], 700.0);
		RotateTo(&ITEM_angleX[i], 0.0);
		RotateTo(&ITEM_angleY[i], -PI/2);
		RotateTo(&ITEM_angleZ[i], 0.0);
		e-=30;
		
		if(previous==-1) previous=i;
	}
	
	TranslateTo(&ITEM_moveX[position], 0.0);
	TranslateTo(&ITEM_moveY[position], 0.0);
	if(FLOW_Zoom) TranslateTo(&ITEM_moveZ[position], 300.0);
	else TranslateTo(&ITEM_moveZ[position], 500.0);
	
	RotateTo(&ITEM_angleX[position], 0.0);
	// don't rotate if the boxes are too close
	if( ( previous!=-1 && ITEM_moveX[position] - ITEM_moveX[previous] < 50)
	 || ( next!=-1     && ITEM_moveX[next] - ITEM_moveX[position] < 50))
	{
		RotateTo(&ITEM_angleY[position], -PI/2);
	} else {
		if(FLOW_ShowBack==YES) 
			RotateTo(&ITEM_angleY[position], PI);
		else 
			RotateTo(&ITEM_angleY[position], 0.0);
	}	
	RotateTo(&ITEM_angleZ[position], 0.0);
	
	MOVE_init=YES;
}

void Draw_FLOW_3D()
{
	MATRIX tmp;
	
    // fix Perspective Projection Matrix 
	// Video_aspect = 1 -> 4:3 
	// Video_aspect = 2 -> 16:9
    tmp = MatrixProjPerspective( 90, (float) (Video_aspect == 1) ? 9.0f / 16.0f :  1.0f, 0.00125F, 300.0F);
    tiny3d_SetProjectionMatrix(&tmp);
    // calculating modelview
    tmp    = MatrixTranslation(0, 0, 80);
    matrix = MatrixRotationY(0);
    matrix = MatrixMultiply(matrix, tmp);
    // fix ModelView Matrix
	tiny3d_SetMatrixModelView(&matrix);
	
// *** LIGHT ***
    tiny3d_SetLightsOff();
    tiny3d_SetAmbientLight(0.8f, 0.8f, 0.8f);
	tiny3d_SetLight(0,  0.0f , 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  LIGHT_DIFFUSE);
	tiny3d_SetLight(1,  0.0f , 0.0f, -500.0f, 1.0f, 1.0f, 1.0f,  LIGHT_DIFFUSE);
	tiny3d_SetLight(2,  0.0f , 0.0f, -1000.0f, 1.0f, 1.0f, 1.0f,  LIGHT_DIFFUSE);
	tiny3d_SetLight(3,  -500.0f , 500.0f, 0.0f, 0.5f, 0.5f, 0.5f,  LIGHT_SPECULAR);

	int i=position;
	int k=0;
	int j=-1;
	int Box_Displayed = 0;
	
	while(Box_Displayed != 16)
	{
		if(Box_Displayed == 8 && j==-1) {j=1; k=0;}
		
		i=position+k*j;
		
		k++;
		
		if(i<0) {j=1; k=0; continue; }
		if(i>game_number) break;
		
		if(Show_it(i)==NO) continue;
		
		Box_Displayed++;
		
		// *** MOVEMENT ***
		MATRIX m_axis;
		m_axis = MatrixRotationX(ITEM_angleX[i]);
		tmp = MatrixRotationY(ITEM_angleY[i]);
		m_axis = MatrixMultiply(m_axis, tmp);
		tmp = MatrixRotationZ(ITEM_angleZ[i]);
		m_axis = MatrixMultiply(m_axis, tmp);
		tmp    = MatrixTranslation(ITEM_moveX[i], ITEM_moveY[i], ITEM_moveZ[i]);
		matrix = MatrixMultiply(m_axis, tmp);
		
		tiny3d_SetMatrixModelView(&matrix);
		
		if( list_game_platform[i] == _ISO_PS3 || list_game_platform[i] == _JB_PS3 ) {
			// texture
			if(PICTURE_offset[BR_LOGO]) tiny3d_SetTexture(0, PICTURE_offset[BR_LOGO], PICTURE[BR_LOGO].width, PICTURE[BR_LOGO].height, PICTURE[BR_LOGO].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

			// material
			tiny3d_EmissiveMaterial(0.0f, 0.0f, 0.0f, 0.0f); // r,g,b,unused
			tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f); // r,g,b,a
			tiny3d_DiffuseMaterial( 0.4f, 0.4f, 0.4f, 1.0f); // r,g,b,enable
			tiny3d_SpecularMaterial(0.5f, 0.5f, 0.5f, 5.0f); // r,g,b,shininess
			
			// Object
			Draw_PS3GAMECASE_3D();
			
			if(COVER3D_offset[i]) {
				// texture
				tiny3d_SetTexture(0, COVER3D_offset[i], COVER3D[i].width, COVER3D[i].height, COVER3D[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
				
				// material
				tiny3d_EmissiveMaterial(0.1f, 0.1f, 0.1f, 0.00f);
				tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f);
				tiny3d_DiffuseMaterial( 0.5f, 0.5f, 0.5f, 1.0f);
				tiny3d_SpecularMaterial(1.0f, 1.0f, 1.0f, 13.0f);
				
				// Object
				Draw_PS3COVER_3D();
				
			} else
			if(COVER_offset[i]) {
				// texture
				tiny3d_SetTexture(0, COVER_offset[i], COVER[i].width, COVER[i].height, COVER[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
				
				// material
				tiny3d_EmissiveMaterial(0.1f, 0.1f, 0.1f, 0.00f);
				tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f);
				tiny3d_DiffuseMaterial( 0.5f, 0.5f, 0.5f, 1.0f);
				tiny3d_SpecularMaterial(1.0f, 1.0f, 1.0f, 13.0f);
				
				// Object
				Draw_PS3COVER();
			}
		
		} else
		if( list_game_platform[i] == _ISO_PS2 || list_game_platform[i] == _JB_PS2 ) {
			// material
			tiny3d_EmissiveMaterial(0.0f, 0.0f, 0.0f, 0.0f); // r,g,b,unused
			tiny3d_AmbientMaterial( 0.1f, 0.1f, 0.1f, 1.0f); // r,g,b,a
			tiny3d_DiffuseMaterial( 0.1f, 0.1f, 0.1f, 1.0f); // r,g,b,enable
			tiny3d_SpecularMaterial(0.2f, 0.2f, 0.2f, 5.0f); // r,g,b,shininess
			
			// Object
			Draw_PS2GAMECASE_3D();
			
			if(COVER3D_offset[i]) {
				// texture
				tiny3d_SetTexture(0, COVER3D_offset[i], COVER3D[i].width, COVER3D[i].height, COVER3D[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
				
				// material
				tiny3d_EmissiveMaterial(0.1f, 0.1f, 0.1f, 0.00f);
				tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f);
				tiny3d_DiffuseMaterial( 0.5f, 0.5f, 0.5f, 1.0f);
				tiny3d_SpecularMaterial(1.0f, 1.0f, 1.0f, 13.0f);
				
				// Object
				Draw_PS2COVER_3D();
				
			} else
			if(COVER_offset[i]) {
				// texture
				tiny3d_SetTexture(0, COVER_offset[i], COVER[i].width, COVER[i].height, COVER[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
				
				// material
				tiny3d_EmissiveMaterial(0.1f, 0.1f, 0.1f, 0.00f);
				tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f);
				tiny3d_DiffuseMaterial( 0.5f, 0.5f, 0.5f, 1.0f);
				tiny3d_SpecularMaterial(1.0f, 1.0f, 1.0f, 13.0f);
				
				// Object
				Draw_PS2COVER();
			}
			
		} else
		if( list_game_platform[i] == _ISO_PS1 || list_game_platform[i] == _JB_PS1 ) {
			
			// texture
			if(PICTURE_offset[PS_LOGO]) tiny3d_SetTexture(0, PICTURE_offset[PS_LOGO], PICTURE[PS_LOGO].width, PICTURE[PS_LOGO].height, PICTURE[PS_LOGO].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

			// material
			tiny3d_EmissiveMaterial(0.0f, 0.0f, 0.0f, 0.0f); // r,g,b,unused
			tiny3d_AmbientMaterial( 0.1f, 0.1f, 0.1f, 1.0f); // r,g,b,a
			tiny3d_DiffuseMaterial( 0.2f, 0.2f, 0.2f, 1.0f); // r,g,b,enable
			tiny3d_SpecularMaterial(0.3f, 0.3f, 0.3f, 1.0f); // r,g,b,shininess
			
			// Object
			Draw_PS1GAMECASE_3D();
						
			if(COVER_offset[i]) {
				// texture
				tiny3d_SetTexture(0, COVER_offset[i], COVER[i].width, COVER[i].height, COVER[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
				// material
				tiny3d_EmissiveMaterial(0.1f, 0.1f, 0.1f, 0.00f);
				tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f);
				tiny3d_DiffuseMaterial( 0.5f, 0.5f, 0.5f, 1.0f);
				tiny3d_SpecularMaterial(1.0f, 1.0f, 1.0f, 13.0f);
				
				// Object
				Draw_PS1COVER_FRONT();
			}
			
			if(COVER3D_offset[i]) {
				// texture
				tiny3d_SetTexture(0, COVER3D_offset[i], COVER3D[i].width, COVER3D[i].height, COVER3D[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
				// material
				tiny3d_EmissiveMaterial(0.1f, 0.1f, 0.1f, 0.00f);
				tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f);
				tiny3d_DiffuseMaterial( 0.5f, 0.5f, 0.5f, 1.0f);
				tiny3d_SpecularMaterial(1.0f, 1.0f, 1.0f, 13.0f);
				
				// Object
				Draw_PS1COVER_BACK();
			}
		
		} else
		if( list_game_platform[i] == _ISO_PSP || list_game_platform[i] == _JB_PSP ) {
			// material
			tiny3d_EmissiveMaterial(0.0f, 0.0f, 0.0f, 0.0f); // r,g,b,unused
			tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f); // r,g,b,a
			tiny3d_DiffuseMaterial( 0.4f, 0.4f, 0.4f, 1.0f); // r,g,b,enable
			tiny3d_SpecularMaterial(0.5f, 0.5f, 0.5f, 5.0f); // r,g,b,shininess
			
			// Object
			Draw_PSPGAMECASE_3D();
			
			if(COVER3D_offset[i]) {
				// texture
				tiny3d_SetTexture(0, COVER3D_offset[i], COVER3D[i].width, COVER3D[i].height, COVER3D[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
				
				// material
				tiny3d_EmissiveMaterial(0.1f, 0.1f, 0.1f, 0.00f);
				tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f);
				tiny3d_DiffuseMaterial( 0.5f, 0.5f, 0.5f, 1.0f);
				tiny3d_SpecularMaterial(1.0f, 1.0f, 1.0f, 13.0f);
				
				// Object
				Draw_PSPCOVER_3D();
				
			} else
			if(COVER_offset[i]) {
				// texture
				tiny3d_SetTexture(0, COVER_offset[i], COVER[i].width, COVER[i].height, COVER[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
				
				// material
				tiny3d_EmissiveMaterial(0.1f, 0.1f, 0.1f, 0.00f);
				tiny3d_AmbientMaterial( 0.3f, 0.3f, 0.3f, 1.0f);
				tiny3d_DiffuseMaterial( 0.5f, 0.5f, 0.5f, 1.0f);
				tiny3d_SpecularMaterial(1.0f, 1.0f, 1.0f, 13.0f);
				
				// Object
				Draw_PSPCOVER();
			}
		}
	}
}

void update_FLOW()
{
	int i;
	float x=848/2;
	float y=512/2;
	float e;
	
	// Init
	if(ITEM_moveX[position]==0 && ITEM_moveY[position]==0) MOVE_init=NO;
	
	TranslateTo(&ITEM_moveX[position], x);
	TranslateTo(&ITEM_moveY[position], y);
	TranslateTo(&ITEM_moveZ[position], 10.0);
	
	e=x+160;
	for(i=position+1; i<=game_number; i++) {	
		if(Show_it(i)==NO) continue;
		TranslateTo(&ITEM_moveX[i], e);
		TranslateTo(&ITEM_moveY[i], y);
		TranslateTo(&ITEM_moveZ[i], 100.0);
		e+=FLOW_W * FLOW_FakeZoom(ITEM_moveZ[i]) + 10;
	}
	
	e=x-160;
	for(i=position-1; i>=0; i--) {
		if(Show_it(i)==NO) continue;
		TranslateTo(&ITEM_moveX[i], e);
		TranslateTo(&ITEM_moveY[i], y);
		TranslateTo(&ITEM_moveZ[i], 100.0);
		e-=FLOW_W * FLOW_FakeZoom(ITEM_moveZ[i]) + 10;
	}
	
	MOVE_init=YES;
}

void Draw_FLOW()
{
	int i;
	for(i=0; i<=game_number; i++) {
		if(Show_it(i)==NO) continue;
		
		if( ITEM_moveX[i] < - FLOW_W) continue;
		if( X_MAX < ITEM_moveX[i] - FLOW_W ) continue;
		
		float w_3D = FLOW_W * FLOW_FakeZoom(ITEM_moveZ[i]);
		float h_3D = FLOW_H * FLOW_FakeZoom(ITEM_moveZ[i]);
		
		if(ITEM_moveX[i] < -w_3D) continue;
		if(X_MAX + w_3D < ITEM_moveX[i]) break;
		
		if(Show_COVER == YES && COVER_offset[i] != 0) {
			Draw_CoverFromCenter(i, ITEM_moveX[i], ITEM_moveY[i], ITEM_moveZ[i], w_3D, 0);
		}
		else {
			Draw_ICON0(i, ITEM_moveX[i]-w_3D/2, ITEM_moveY[i]-h_3D/2, ITEM_moveZ[i], w_3D, h_3D);
		}
	}

}

//*******************************************************
// XMB
//*******************************************************

#define XMB_X_COLUMN 250.0
#define XMB_Y_COLUMN 165.0

#define XMB_X_LINE XMB_X_COLUMN
#define XMB_Y_LINE 240.0

void init_XMB()
{
	if(XMB_H_position != XMB_COLUMN_SETTINGS) {

		XMB_nb_line=-1;
		memset(XMB_value_line, 0, sizeof(XMB_value_line));
		
		int i;
		for(i = 0 ; i <= game_number ; i++) {
			if(XMB_H_position==XMB_COLUMN_PS3 && (list_game_platform[i] !=_ISO_PS3 && list_game_platform[i] !=_JB_PS3)) continue;
			if(XMB_H_position==XMB_COLUMN_PS2 && (list_game_platform[i] !=_ISO_PS2 && list_game_platform[i] !=_JB_PS2)) continue;
			if(XMB_H_position==XMB_COLUMN_PS1 && (list_game_platform[i] !=_ISO_PS1 && list_game_platform[i] !=_JB_PS1)) continue;
			if(XMB_H_position==XMB_COLUMN_PSP && (list_game_platform[i] !=_ISO_PSP && list_game_platform[i] !=_JB_PSP)) continue;
			if(XMB_H_position==XMB_COLUMN_FAVORITES && is_favorite(list_game_path[i]) == NO) continue;
			
			XMB_nb_line++;
			XMB_value_line[XMB_nb_line]=i;
			
			if(XMB_V_position[XMB_H_position]==XMB_nb_line) position=i;
		}
		
		if(XMB_V_position[XMB_H_position]>XMB_nb_line) XMB_V_position[XMB_H_position] = XMB_nb_line;
		if(XMB_nb_line==-1) Game_stuff=NO;
		
	}
}

float XMB_FakeZoom(float z)
{
	if(10<=z && z<=100) return 2 - (z-10)/90; else
	if(0<=z && z<10) return 4 - 3*(z/10); else
	return 1;
}

void Draw_XMB_COLUMNS()
{
	int i;
	
	for(i=0; i<XMB_COLUMN_NUMBER; i++) {
		
		float l = 85.0 - XMB_columnZ[i];
		
		SetFontZ(XMB_columnZ[i]);
		
		if(XMB_Col_offset[i] != 0) {
			tiny3d_SetTexture(0, XMB_Col_offset[i], XMB_Col[i].width, XMB_Col[i].height, XMB_Col[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			Draw_Box(XMB_columnX[i]-l/2, XMB_columnY[i]-l, XMB_columnZ[i], 0, l, l, WHITE, YES);
		} else
		if(XMB_MMTHM_XMB_offset != 0 && XMB_MMTHM_XMB2_offset != 0) { 
			u8 ico=6;
			if(i==0) ico=2 ;else
			if(i==1) ico=12;else
			if(i==2) ico=6 ;else
			if(i==3) ico=29;else
			if(i==4) ico=28;else
			if(i==5) ico=30;
			Draw_MMTHM_XMB(XMB_columnX[i]-l/2, XMB_columnY[i]-l, XMB_columnZ[i], l, l,  ico);
		} 
		else {
			FontSize(l-30);
			DrawStringFromCenterX(XMB_columnX[i], XMB_columnY[i]-XMB_columnZ[i], XMB_COLUMN_NAME[i]);
		}
	}
	
	FontSize(12);
	SetFontZ(100);
	if(XMB_H_position==XMB_COLUMN_SETTINGS) {
		DrawStringFromCenterX(XMB_X_COLUMN, XMB_Y_COLUMN, STR_SETTINGS);
	} else 
	if(XMB_H_position==XMB_COLUMN_FAVORITES) {
		DrawStringFromCenterX(XMB_X_COLUMN, XMB_Y_COLUMN, STR_FAVORITE);
	} else {
		DrawStringFromCenterX(XMB_X_COLUMN, XMB_Y_COLUMN, XMB_COLUMN_NAME[XMB_H_position]);
	}
	
	FontSize(20);
	SetFontZ(10);	

}

void Draw_XMB_LINES()
{	
	int i;
	float w, h;
	
	SetFontZ(10);
	FontSize(20);
	if(XMB_H_position != XMB_COLUMN_SETTINGS && Game_stuff) {
		
		for(i=XMB_V_position[XMB_H_position]-6; i<=XMB_V_position[XMB_H_position]+6; i++) {
			if(i < 0) continue;
			if(i > XMB_nb_line) break;
			
			w = XMB_W * XMB_FakeZoom(ITEM_moveZ[i]);
			h = XMB_H * XMB_FakeZoom(ITEM_moveZ[i]);
			DrawFromCenter_ICON0(XMB_value_line[i], ITEM_moveX[i], ITEM_moveY[i], ITEM_moveZ[i], w, h);			
		}
		
		if(Show_COVER == YES) Draw_COVER(position, 30, 200, 10, 130, 0);
		
		if(MENU) w = XMB_W * 4;
		else w = XMB_W * 2;
		DrawString(XMB_X_LINE+w/2+20, XMB_Y_LINE, list_game_title[position]);
	}

}

void update_XMB_COLUMNS()
{	
	int i;
	float x=XMB_X_COLUMN;
	float y=XMB_Y_COLUMN;
	float e;
	float e2=95.0;
	
	// Init
	if(XMB_columnY[XMB_H_position] != y) MOVE_init=NO;
	else MOVE_init=YES;
	
	TranslateTo(&XMB_columnX[XMB_H_position], x);
	TranslateTo(&XMB_columnY[XMB_H_position], y);
	TranslateTo(&XMB_columnZ[XMB_H_position], 20.0);
	
	e=x+e2;
	for(i=XMB_H_position+1; i<XMB_COLUMN_NUMBER; i++) {
		TranslateTo(&XMB_columnX[i], e);
		TranslateTo(&XMB_columnY[i], y);
		TranslateTo(&XMB_columnZ[i], 35.0);
		e2-=5;
		e+=e2;
	}
	
	e2=95.0;
	e=x-e2;
	for(i=XMB_H_position-1; i>=0; i--) {
		TranslateTo(&XMB_columnX[i], e);
		TranslateTo(&XMB_columnY[i], y);
		TranslateTo(&XMB_columnZ[i], 35.0);
		e2-=5;
		e-=e2;
	}
}

void update_XMB_LINES()
{
	int i;
	float x=XMB_X_LINE;
	float y=XMB_Y_LINE;
	float e;
	
	if(Game_stuff==NO) return;
	
	// Init
	if(ITEM_moveX[XMB_V_position[XMB_H_position]] != x) MOVE_init=NO;
	
	TranslateTo(&ITEM_moveX[XMB_V_position[XMB_H_position]], x);
	TranslateTo(&ITEM_moveY[XMB_V_position[XMB_H_position]], y);
	if(MENU) 
		TranslateTo(&ITEM_moveZ[XMB_V_position[XMB_H_position]], 0.0);
	else 
		TranslateTo(&ITEM_moveZ[XMB_V_position[XMB_H_position]], 10.0);
	
	e=y+120.0;
	for(i=XMB_V_position[XMB_H_position]+1; i<=XMB_nb_line; i++) {
		TranslateTo(&ITEM_moveX[i], x);
		TranslateTo(&ITEM_moveY[i], e);
		TranslateTo(&ITEM_moveZ[i], 100.0);
		e+=XMB_H+2;
	}
	
	e=y-175.0;
	for(i=XMB_V_position[XMB_H_position]-1; i>=0; i--) {
		TranslateTo(&ITEM_moveX[i], x);
		TranslateTo(&ITEM_moveY[i], e);
		TranslateTo(&ITEM_moveZ[i], 100.0);
		e-=XMB_H+2;
	}
	
	MOVE_init=YES;
	
}

//*******************************************************
// GRID
//*******************************************************

void init_GRID()
{	
	int i, j=0;
	
	if(GRID_KEEP_PROP==YES) GRID_NB_LINES = (GRID_H+GRID_e) / (GRID_e+GRID_H_ICON0);
	
	if(position < GRID_FIRST_ICON) {
		j=-1;
		for(i=GRID_FIRST_ICON; i>=0; i--){
			if(Show_it(i)==NO) continue;
			j++;
			GRID_FIRST_ICON=i;
			if(GRID_TYPE == PAGE && j==GRID_NB_ICON0) break;
			if(GRID_TYPE == SCROLL && GRID_DIRECTION==HORIZONTAL && j==GRID_NB_LINES) break;
			if(GRID_TYPE == SCROLL && GRID_DIRECTION==VERTICAL && j==GRID_NB_COLUMNS) break;
		}
	} else
	if(position > GRID_LAST_ICON) {
		j=-1;
		for(i=GRID_FIRST_ICON; i<=game_number; i++){
			if(Show_it(i)==NO) continue;
			j++;
			GRID_FIRST_ICON=i;
			if(GRID_TYPE == PAGE && j==GRID_NB_ICON0) break;
			if(GRID_TYPE == SCROLL && GRID_DIRECTION==HORIZONTAL && j==GRID_NB_LINES) break;
			if(GRID_TYPE == SCROLL && GRID_DIRECTION==VERTICAL && j==GRID_NB_COLUMNS) break;
		}
	}
	
	j=0;
	for(i=GRID_FIRST_ICON; i<=game_number; i++) {
		if(Show_it(i)==NO) continue;
		j++;
		GRID_LAST_ICON=i;
		if(j==GRID_NB_ICON0) break;
	}
}

void Draw_GRID()
{
	int i;
	for(i = GRID_FIRST_ICON-GRID_NB_ICON0 ; i<=GRID_LAST_ICON+GRID_NB_ICON0 ; i++) {
		if(i<0) continue;
		if(i>game_number) break;
		if(Show_it(i)==NO) continue;
		
		Draw_ICON0(i, ITEM_moveX[i], ITEM_moveY[i], ITEM_moveZ[i], GRID_W_ICON0, GRID_H_ICON0);
		if(i==position) {
			Draw_Box(ITEM_moveX[i]-5, ITEM_moveY[i]-5, ITEM_moveZ[i]+1, 0, GRID_W_ICON0+10, GRID_H_ICON0+10, WHITE, NO);
			Draw_Box(ITEM_moveX[i], ITEM_moveY[i], ITEM_moveZ[i]+1, 0, GRID_W_ICON0, GRID_H_ICON0, BLACK, NO);
		} else {
			Draw_Box(ITEM_moveX[i], ITEM_moveY[i], ITEM_moveZ[i]-1, 0, GRID_W_ICON0, GRID_H_ICON0, 0xFFFFFF80, NO); 
		}
	}
}

void update_GRID()
{
	// Init
	if(ITEM_moveZ[position]!=100.0 || GRID_ANIMATED == NO) MOVE_init=NO;
	
	float x, y, x1, y1;
	int i, k=0;
	x = GRID_X;
	y = GRID_Y;
	x1=x;
	y1=y;
	for(i = GRID_FIRST_ICON ; i<=GRID_LAST_ICON ; i++) {
		if(Show_it(i)==NO) continue;
		k++;
		
		TranslateTo(&ITEM_moveX[i], x);
		TranslateTo(&ITEM_moveY[i], y);
		TranslateTo(&ITEM_moveZ[i], 100.0);
			
		if(GRID_DIRECTION == HORIZONTAL)  {
			y+= GRID_H_ICON0 + GRID_e;
			if(k==GRID_NB_LINES) {k=0; y = GRID_Y; x += GRID_W_ICON0 + GRID_e;}
		} else
		if(GRID_DIRECTION == VERTICAL)  {
			x+= GRID_W_ICON0 + GRID_e;
			if(k==GRID_NB_COLUMNS) {k=0; x = GRID_X; y += GRID_H_ICON0 + GRID_e;}
		}
	}
	
	x = GRID_X;
	y = GRID_Y;
	if(GRID_DIRECTION == HORIZONTAL) {
		y+= (GRID_NB_LINES-1) * (GRID_H_ICON0 + GRID_e);
		x-= GRID_W_ICON0 + GRID_e;
	} else
	if(GRID_DIRECTION == VERTICAL) {
		x+= (GRID_NB_COLUMNS-1) * (GRID_W_ICON0 + GRID_e);
		y-= GRID_H_ICON0 + GRID_e;
	}
	x1=x;
	y1=y;
	k=0;
	for(i = GRID_FIRST_ICON-1 ; i>=0 ; i--) {
		if(Show_it(i)==NO) continue;
		k++;
		
		TranslateTo(&ITEM_moveX[i], x);
		TranslateTo(&ITEM_moveY[i], y);
		TranslateTo(&ITEM_moveZ[i], 100.0);
			
		if(GRID_DIRECTION == HORIZONTAL)  {
			y-= GRID_H_ICON0 + GRID_e;
			if(k==GRID_NB_LINES) {k=0; y = y1; x -= GRID_W_ICON0 + GRID_e;}
		} else
		if(GRID_DIRECTION == VERTICAL)  {
			x-= GRID_W_ICON0 + GRID_e;
			if(k==GRID_NB_COLUMNS) {k=0; x = x1; y -= GRID_H_ICON0 + GRID_e;}
		}
	}
	
	x = GRID_X;
	y = GRID_Y;
	if(GRID_DIRECTION == HORIZONTAL) {
		x+= GRID_NB_COLUMNS * (GRID_W_ICON0 + GRID_e);
	} else
	if(GRID_DIRECTION == VERTICAL) {
		y+= GRID_NB_LINES * (GRID_H_ICON0 + GRID_e);
	}
	x1=x;
	y1=y;
	k=0;
	for(i = GRID_LAST_ICON+1 ; i<=game_number ; i++) {
		if(Show_it(i)==NO) continue;
		k++;
		
		TranslateTo(&ITEM_moveX[i], x);
		TranslateTo(&ITEM_moveY[i], y);
		TranslateTo(&ITEM_moveZ[i], 100.0);
			
		if(GRID_DIRECTION == HORIZONTAL)  {
			y+= GRID_H_ICON0 + GRID_e;
			if(k==GRID_NB_LINES) {k=0; y = GRID_Y; x += GRID_W_ICON0 + GRID_e;}
		} else
		if(GRID_DIRECTION == VERTICAL)  {
			x+= GRID_W_ICON0 + GRID_e;
			if(k==GRID_NB_COLUMNS) {k=0; x = GRID_X; y += GRID_H_ICON0 + GRID_e;}
		}
	}
	
	MOVE_init=YES;
}

//*******************************************************
//Main
//*******************************************************

void input_MAIN()
{
	if(filter==YES) return;
	if(MENU==YES) return;
	if(txt_viewer_activ == YES) return;
	
	int i,j,k;
	
	u8 old_x = x_L;
	u8 old_y = y_L;
	
	x_L = (paddata.button[6] - 128);
	y_L = (paddata.button[7] - 128);
	
	if (y_L < -28) {
		if(old_y == 0) new_pad |= BUTTON_UP; else
		{
			old_pad |= BUTTON_UP;
			R2speed = 6 + y_L/20;
		}
	} else 
	if (28 < y_L) {
		if(old_y == 0) new_pad |= BUTTON_DOWN; else
		{
			old_pad |= BUTTON_DOWN;
			R2speed = 6 - y_L/20;
		}
	} else 
	if (x_L < -28) {
		if(old_x == 0) new_pad |= BUTTON_LEFT; else
		{
			old_pad |= BUTTON_LEFT;
			R2speed = 6 + x_L/20 ;
		}
	} else 
	if (28 < x_L) {
		if(old_x == 0) new_pad |= BUTTON_RIGHT; else
		{
			old_pad |= BUTTON_RIGHT;
			R2speed = 6 - x_L/20;
		}
	} else { 
		x_L=0; y_L=0;
		if(old_pad & BUTTON_R2) {
			R2speed = 6 - paddata.PRE_R2/50;
		} else R2speed=6;
	}
	
	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>R2speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(new_pad & BUTTON_CIRCLE) {
		while(hold_CIRCLE%30!=0) hold_CIRCLE++;
		hold_CIRCLE+=15;
	} else
	if(old_pad & BUTTON_CIRCLE) {
		hold_CIRCLE++;
	} else {
		if(hold_CIRCLE%30==0) hold_CIRCLE=0;
		else hold_CIRCLE--;
	}

	if(hold_CIRCLE>90) {
		if(Load_GamePIC==YES) end_Load_GamePIC();
		end_load_PIC1();
		end_checking();
		sysModuleUnload(SYSMODULE_PNGDEC);
		sysModuleUnload(SYSMODULE_JPGDEC);
		ioPadEnd();
		exit(0);
	}
	
	if((old_pad & BUTTON_L3) && (old_pad & BUTTON_R3)) {
		sysProcessExitSpawn2("/dev_hdd0/game/MANAGUNZ0/USRDIR/ManaGunZ.self", NULL, NULL, NULL, 0, 64, SYS_PROCESS_SPAWN_STACK_SIZE_128K);
	}	
	
	if(old_pad & BUTTON_R1) Display_PIC1=YES;
	else Display_PIC1=NO;
	
	if(new_pad & BUTTON_CROSS && Game_stuff == YES) {
		
		if( list_game_platform[position] == _ISO_PS3 || list_game_platform[position] == _JB_PS3
		||	list_game_platform[position] == _ISO_PS2 
		||	list_game_platform[position] == _ISO_PS1
		||	list_game_platform[position] == _ISO_PSP			
		) {
#ifndef RPCS3
			if(Load_GamePIC==YES) end_Load_GamePIC();
			end_load_PIC1();
			end_checking();
#endif

			start_loading();	
			
			read_game_setting(list_game_id[position]);
			
			u8 mounted = MountGame(list_game_path[position]);
			
			end_loading();
#ifdef RPCS3
			if(mounted) show_msg("EXIT !");
#else
			if(mounted) {
				sysModuleUnload(SYSMODULE_PNGDEC);
				sysModuleUnload(SYSMODULE_JPGDEC);
				ioPadEnd();
				exit(0);
			} else {
				start_load_PIC1();
				start_checking();
			}
#endif
	
		} else show_msg("TODO");
	} else
	if(new_pad & BUTTON_TRIANGLE && Game_stuff == YES) {
		open_GameMenu();
	} else
	if(new_pad & BUTTON_SELECT) {
		Draw_FileExplorer(NULL);
	} else
	if(new_pad & BUTTON_SQUARE && UI_position!=XMB) {
		open_filter();
	} else
	if(new_pad & BUTTON_START) {
		open_SETTINGS();
	}
	
	if(UI_position==LIST) {
		if(R2pad(BUTTON_UP)) {
			for(i=0; i<=game_number;i++) {
				position--;
				if(position<0) position=game_number;
				if(Show_it(position) == YES) break;
			}
			if(position>last_line) {
				last_line=position;
				j=0;
				for(i=last_line;  j<=nb_line; i--) {
					if(Show_it(i) == NO) continue;
					j++;
				}
				first_line=i+1;
			} else
			if(position<first_line) {
				first_line=position;
				j=0;
				for(i=first_line; j<=nb_line; i++) {
					if(Show_it(i) == NO) continue;
					j++;
				}
				last_line=i-1;
			}
		}
		if(R2pad(BUTTON_DOWN)) {
			for(i=0; i<=game_number;i++) {
				position++;
				if(position>game_number) position=0;
				if(Show_it(position) == YES) break;
			}
			if(position>last_line) {
				last_line=position;
				j=0;
				for(i=last_line;  j<=nb_line; i--) {
					if(Show_it(i) == NO) continue;
					j++;
				}
				first_line=i+1;
			} else
			if(position<first_line) {
				first_line=position;
				j=0;
				for(i=first_line; j<=nb_line; i++) {
					if(Show_it(i) == NO) continue;
					j++;
				}
				last_line=i-1;
			}	
		}
	} else
	if(UI_position==GRID) {
		if( (R2pad(BUTTON_UP) && GRID_DIRECTION==HORIZONTAL)  ||
			(R2pad(BUTTON_LEFT) && GRID_DIRECTION==VERTICAL  )  )
		{
			j=-1;
			for(i=position; i>=0;i--){
				if(Show_it(i)==NO) continue;
				j++;
				position=i;
				if(j==1) break;
			}
		}
		if( (R2pad(BUTTON_DOWN) && GRID_DIRECTION==HORIZONTAL)  ||
			(R2pad(BUTTON_RIGHT) && GRID_DIRECTION==VERTICAL  )  )
		{
			j=-1;
			for(i=position; i<=game_number;i++){
				if(Show_it(i)==NO) continue;
				j++;
				position=i;
				if(j==1) break;
			}
		}
		if( (R2pad(BUTTON_LEFT) && GRID_DIRECTION==HORIZONTAL)  ||
			(R2pad(BUTTON_UP) && GRID_DIRECTION==VERTICAL  )  )
		{
			j=-1;
			for(i=position; i>=0;i--){
				if(Show_it(i)==NO) continue;
				j++;
				position=i;
				if(GRID_DIRECTION==VERTICAL   && j==GRID_NB_COLUMNS) break;
				if(GRID_DIRECTION==HORIZONTAL && j==GRID_NB_LINES) break;
			}
		}
		if( (R2pad(BUTTON_RIGHT) && GRID_DIRECTION==HORIZONTAL)  ||
			(R2pad(BUTTON_DOWN) && GRID_DIRECTION==VERTICAL  )  )
		{
			j=-1;
			for(i=position; i<=game_number;i++){
				if(Show_it(i)==NO) continue;
				j++;
				position=i;
				if(GRID_DIRECTION==VERTICAL   && j==GRID_NB_COLUMNS) break;
				if(GRID_DIRECTION==HORIZONTAL && j==GRID_NB_LINES) break;
			}
		}
	} else
	if(UI_position==XMB) {
		if(R2pad(BUTTON_LEFT) ) {
			if(XMB_H_position > 0) { XMB_H_position--; MOVE_init=NO; }
		} else
		if(R2pad(BUTTON_RIGHT)) {
			if(XMB_H_position < 5) { XMB_H_position++; MOVE_init=NO; }
		} else
		if(R2pad(BUTTON_UP)) {
			if(XMB_V_position[XMB_H_position] == 0 && XMB_nb_line != 0) {
				XMB_V_position[XMB_H_position] = XMB_nb_line;
				MOVE_init=NO;
			} 
			else if(XMB_V_position[XMB_H_position] > 0) XMB_V_position[XMB_H_position]--;
		} else
		if(R2pad(BUTTON_DOWN)) {
			if(XMB_V_position[XMB_H_position] == XMB_nb_line && XMB_nb_line != 0) {
				XMB_V_position[XMB_H_position] = 0;
				MOVE_init=NO;
			} else if(XMB_V_position[XMB_H_position] < XMB_nb_line) XMB_V_position[XMB_H_position]++;
		}
	} else
	if(UI_position==FLOW) {
		if( (FLOW_inverse_button==NO  && R2pad(BUTTON_RIGHT)) ||
			(FLOW_inverse_button==YES && R2pad(BUTTON_LEFT))   ) 
		{
			for(i=0; i<game_number;i++) {
				position--;
				FLOW_ShowBack=NO;
				if(position < 0) {
					for(k=game_number; k>=0; k--) {
						if(Show_it(k) == NO) continue;
						position=k;
						MOVE_init=NO;
						break;
					}
				}
				if(Show_it(position) == YES) break;
			}
		}
		if( (FLOW_inverse_button==NO  && R2pad(BUTTON_LEFT) ) ||
			(FLOW_inverse_button==YES && R2pad(BUTTON_RIGHT))   ) 
		{
			for(i=0; i<game_number;i++) {
				position++;
				FLOW_ShowBack=NO;
				if(position > game_number) {
					for(k=0; k<=game_number; k++) {
						if(Show_it(k) == NO) continue;
						position=k;
						MOVE_init=NO;
						break;
					}
				}
				if(Show_it(position) == YES) break;
			}
		}
		if( (new_pad & BUTTON_R3) &&  FLOW_3D) {
			if(FLOW_ShowBack==YES) FLOW_ShowBack=NO;
			else FLOW_ShowBack=YES;
		}
		if( (new_pad & BUTTON_L3) &&  FLOW_3D) {
			if(FLOW_Zoom==YES) FLOW_Zoom=NO;
			else FLOW_Zoom=YES;
		}
		
	}
}

float DrawTAG(float x, float y, float z, float min_width, float font_height, char *str)
{	

	float w = min_width;
	
	float w_str = GetWidth(str) + 8.0;
	
	while( w_str > w ) w += 4.0;
	
	float e = (w - (w_str-8.0))/2.0;
	
	if(PICTURE_offset[TAG] != 0) {
		tiny3d_SetTexture(0, PICTURE_offset[TAG], PICTURE[TAG].width, PICTURE[TAG].height, PICTURE[TAG].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z+1, 0, w, font_height, WHITE, YES);
	} else	
		Draw_Box(x, y, z+1, 0, w, font_height, 0xA0A0A0A0, NO);
	
	DrawFormatString(x + e + 1, y+1, str);
	
	return x+w+1;
}

#define INPUT_TAG_WIDTH_MIN 

void Draw_MAIN_input()
{
	if(MENU==YES) return;
	if(filter==YES) return;
	
	float tagbox_min_width = 50;
	
	float x=INPUT_X;
	float y=INPUT_Y;
	FontColor(COLOR_1);
	SetFontZ(0);
	
	x=DrawButton(x, y, STR_SETTINGS, BUTTON_START);
	if(Game_stuff==YES) {
		x=DrawButton(x, y, STR_GAMEMENU, BUTTON_TRIANGLE);
		x=DrawButton(x, y, STR_MOUNTGAME, BUTTON_CROSS);
	}
	if(UI_position!=XMB) {
		x=DrawButton(x, y, STR_FILTER, BUTTON_SQUARE);
	}
	x=DrawButton(x, y, STR_FILEMANAGER, BUTTON_SELECT);
		
	//FontColor(COLOR_4);
	//x=DrawFormatString( x+10, y, "%s", STR_HOLD);
	FontColor(COLOR_1); 
	if(hold_CIRCLE) {
		DrawProgRing(x+7, y+7.5, 20, ((hold_CIRCLE%30)*100)/30, COLOR_3);
		FontColor(COLOR_3);
		DrawFormatString(x+10, y-12, "%d", (90 - hold_CIRCLE)/30);
		FontColor(COLOR_1);
	}
	x=DrawButton(x, y, STR_BACKTOXMB, BUTTON_CIRCLE);
	
	x=X_MAX-10-4*tagbox_min_width;
	y=INPUT_Y;
	if(Game_stuff == YES) {
		char tag_str[20];
		int t;
		
		FontColor(COLOR_1);
		
		if(list_game_platform[position] == _ISO_PS3 || list_game_platform[position] == _JB_PS3) {
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "PS3");
		} else
		if(list_game_platform[position] == _ISO_PS2 || list_game_platform[position] == _JB_PS2) {
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "PS2");
		} else
		if(list_game_platform[position] == _ISO_PS1 || list_game_platform[position] == _JB_PS1) {
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "PS1");
		} else
		if(list_game_platform[position] == _ISO_PSP || list_game_platform[position] == _JB_PSP) {
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "PSP");
		} else {
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "UNK");
		}
		
		float x1 = x;
		
		char *Ext = GetExtention(list_game_path[position]);
	
		if( (Ext[1] == 'I' || Ext[1] == 'i')
		&& 	(Ext[2] == 'S' || Ext[2] == 's')
		&&	(Ext[3] == 'O' || Ext[3] == 'o') )	{
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "ISO");
		} else	
		if( (Ext[1] == 'B' || Ext[1] == 'b')
		&& 	(Ext[2] == 'I' || Ext[2] == 'i')
		&&	(Ext[3] == 'N' || Ext[3] == 'n') )	{
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "BIN");
		} else
		if( (Ext[1] == 'M' || Ext[1] == 'm')
		&& 	(Ext[2] == 'D' || Ext[2] == 'd')
		&&	(Ext[3] == 'F' || Ext[3] == 'f') )	{
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "MDF");
		} else
		if( (Ext[1] == 'I' || Ext[1] == 'i')
		&& 	(Ext[2] == 'M' || Ext[2] == 'm')
		&&	(Ext[3] == 'G' || Ext[3] == 'g') )	{
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "IMG");
		} else
		if( (Ext[1] == 'C' || Ext[1] == 'c')
		&& 	(Ext[2] == 'S' || Ext[2] == 's')
		&&	(Ext[3] == 'O' || Ext[3] == 'o') )	{
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "CSO");
		} else {
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "JB");
		}
		
		if(is_66600(list_game_path[position])) {
			FontColor(COLOR_4);
			FontSize(INPUT_SIZE/2);
			DrawTAG(x1, y-INPUT_SIZE/2, 0, 0, INPUT_SIZE/2, "666");
			FontColor(COLOR_1);
			FontSize(INPUT_SIZE);
		}	
				
		if(usb) {
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "FAT32");
			sscanf(list_game_path[position], "/dev_usb%d%*s" , &t);
			sprintf(tag_str, "USB%d", t);
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, tag_str);

		} else
		if(is_ntfs(list_game_path[position]) == YES) {
					
			sscanf(list_game_path[position], "/ntfs%d%*s" , &t);
			sprintf(tag_str, "NTFS%d", t);
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, tag_str);
			
			char dev[10];
			sprintf(dev, "ntfs%d", t);
			sprintf(tag_str, "USB%d", NTFS_Test_Device(dev));
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, tag_str);

		} else 
		if( strstr(list_game_path[position], "/dev_hdd0") != NULL) {
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "UFS2");
			x = DrawTAG(x, y, 0, tagbox_min_width, INPUT_SIZE, "HDD0");
		}
		
	}
}

void Draw_MAIN()
{
	if(MENU==YES && MENU_SIDE == NO) return;
	
	SetFontZ(10);
	
	int x, y, i;

	iso = is_iso(list_game_path[position]);
	usb = is_usb(list_game_path[position]);
	
	Game_stuff = YES;	
	
	if(UI_position==LIST) {
		
		if(LIST_Show_ICON0 == YES) {
			Draw_ICON0(position, 630, 30, 100, 141.3, 75.9);
		}
		if(Show_COVER == YES) {
			Draw_COVER(position, 630, 150, 100, 141.3, 0);
		}
		
		x=50, y=40;
		FontColor(COLOR_1);
		FontSize(LIST_SizeFont);
		
	
		nb_line = (460 - y - LIST_SizeFont) / LIST_SizeFont;
		
		SetFontZ(105);
				
		int j=0;
		
		for(i=first_line;  j <= nb_line; i++) {
			if(i>game_number) break;
			if(Show_it(i) == NO) continue;
			
			j++;
			
			if(i==position) FontColor(COLOR_2);
			else FontColor(COLOR_1);
			
			DrawFormatString(x, y, "%s", list_game_title[i]);
			y+=LIST_SizeFont;
		}
		SetFontZ(10);
		last_line=i-1;
		
		if(position<first_line) position = first_line;
		if(last_line<position) position = last_line;
	}
	else if (UI_position==GRID) {
	
		init_GRID();
		update_GRID();
		Draw_GRID();
	
	}
	else if (UI_position==XMB) {
		
		if(XMB_H_position == XMB_COLUMN_SETTINGS) Game_stuff = NO; else Game_stuff = YES;
		
		init_XMB();
		
		Draw_XMB_LINES();
		update_XMB_LINES();
		
		Draw_XMB_COLUMNS();
		update_XMB_COLUMNS();
		
	}
	else if (UI_position==FLOW) {
		if(FLOW_3D) {
			FontSize(20);
			DrawStringFromCenterX(424, 50, list_game_title[position]);
			
			update_3DFLOW();
		
			tiny3d_Project3D();
			
			Draw_FLOW_3D();

			tiny3d_Project2D(); 
			
			tiny3d_SetMatrixModelView(NULL);
		
		} else {
			FontSize(20);
			DrawStringFromCenterX(424, 75, list_game_title[position]);
			
			update_FLOW();
			
			Draw_FLOW();
		}
	}

}

u8 Show_it(int pos)
{
	if(pos<0 || game_number<pos) return NO;
	
	if( Show_PS3==NO && (list_game_platform[pos]==_ISO_PS3 || list_game_platform[pos]==_JB_PS3)) return NO;
	if( Show_PS2==NO && (list_game_platform[pos]==_ISO_PS2 || list_game_platform[pos]==_JB_PS2)) return NO;
	if(	Show_PS1==NO && (list_game_platform[pos]==_ISO_PS1 || list_game_platform[pos]==_JB_PS1)) return NO;
	if(	Show_PSP==NO && (list_game_platform[pos]==_ISO_PSP || list_game_platform[pos]==_JB_PSP)) return NO;
	
	if( UI_position != XMB && Only_FAV==YES && is_favorite(list_game_path[pos])==NO) return NO;
	
	return YES;
}

int main(void)
{
	int i, j;
	char scan_path[128];
	u8 LoopBreak=1;

	NTFS_init_system_io();
	AutoM = is_AutoMount(); // ManaGunZ_id

	sysModuleLoad(SYSMODULE_PNGDEC);
	sysModuleLoad(SYSMODULE_JPGDEC);
	
	Init_Graph();
	initAIO();
	ioPadInit(7);
	ioPadSetPressMode(0,1);
	SetCurrentFont(-1);
	
#ifdef RPCS3
#ifdef FILEMANAGER
	strcpy(ManaGunZ_id, "FILEMANAG");
#else
	strcpy(ManaGunZ_id, "MANAGUNZ0");
#endif
	cobra = NO;
	mamba = NO;
	device_number++;
	strcpy(list_device[device_number], "dev_hdd0");
	device_number++;
	strcpy(list_device[device_number], "dev_usb000");
#endif // RPCS3
	
	read_setting(); //Need ManaGunZ_id
	
	LoadFont();
	init_lang();
	load_lang();

	start_loading();

	u64 test_peek = lv2peek(0x8000000000003000ULL);
	if( test_peek == 0xFFFFFFFF80010003ULL || test_peek == 0 ) // rpcs3 return 0
		PEEKnPOKE = NO;
	else
		PEEKnPOKE = YES;

	print_load("Initialisation");
	if(PEEKnPOKE) {
		if(init_fw() == NOK) {
			//This firmware isn't supported
			PEEKnPOKE = NO;
		}
	}
	
#ifdef FILEMANAGER

#ifndef RPCS3
	getDevices();
	cobra = is_cobra();
	mamba = is_mamba();
#endif

	print_load(STR_ADJUST);
	adjust_screen();

	print_load("Load Theme");
	Load_Theme();
	
	end_loading();
	
	Draw_FileExplorer();
	
	ioPadEnd();
	sysModuleUnload(SYSMODULE_PNGDEC);
	sysModuleUnload(SYSMODULE_JPGDEC);
	
	return 0;
#endif // FILEMANAGER
	
	
#ifndef RPCS3
	if(init_ManaGunZ() == FAILED) {
		end_loading();
		LoopBreak=1;
		while(LoopBreak) {
			cls();
			ps3pad_read();
			
			FontSize(20);
			FontColor(RED);
			DrawString(50, 100, "Error : Cannot init ManaGunZ");
			
			float x=INPUT_X;
			float y=INPUT_Y;
			FontColor(COLOR_1);
			SetFontZ(0);

			DrawButton(x, y, STR_BACKTOXMB, BUTTON_CIRCLE);
			
			tiny3d_Flip();
			ScreenShot();
			
			if(new_pad & BUTTON_CIRCLE) {
				ioPadEnd();
				sysModuleUnload(SYSMODULE_PNGDEC);
				sysModuleUnload(SYSMODULE_JPGDEC);
				LoopBreak=0;
				return 0;
			}
		}
	}
#endif	
		
	if(AutoM) AutoMount();	

	start_checking();

	print_load(STR_ADJUST);
	adjust_screen();

	print_load("Load Theme");
	Load_Theme();
	
	print_load("Get directories names from scan_dir.txt");
	if(read_scan_dir()==FAILED){
		end_loading();
		LoopBreak=1;
		while(LoopBreak) 
		{
			cls();
			ps3pad_read();
			
			Draw_BGS();		
			
			FontSize(20);
			FontColor(RED);
			DrawString(50, 40, "Error : Can't read scan_dir.txt");
			
			float x=INPUT_X;
			float y=INPUT_Y;
			FontColor(COLOR_1);
			SetFontZ(0);
			
			DrawButton(x, y, STR_BACKTOXMB, BUTTON_CIRCLE);
			
			tiny3d_Flip();
			ScreenShot();
			
			if(new_pad & BUTTON_CIRCLE) {
				end_checking();
				sysModuleUnload(SYSMODULE_PNGDEC);
				sysModuleUnload(SYSMODULE_JPGDEC);
				ioPadEnd();
				LoopBreak=0;
				return 0;
			}
		}
	}

	//get game list
	for(j=0; j<=scan_dir_number; j++) {
		for(i=0; i<=device_number; i++) {
			sprintf(scan_path, "/%s/%s", list_device[i], scan_dir[j]);
			
			get_GAMELIST(scan_path);
		}
	}
	
	sort_GAMELIST();
	
	start_Load_GamePIC();
	
	print_load("Get Favorite game list");
	read_fav();

	position=0;
	for(position=0; position<=game_number; position++) {
		if(Show_it(position)==YES) break;
	}
	
	end_loading();

	start_load_PIC1();
	
	LoopBreak=1;
	while(LoopBreak) {

		while(game_number < 0) {
			cls();
			ps3pad_read();
			
			Draw_BGS();
			
			check_device();
			
			FontSize(20);
			FontColor(RED);
			DrawString(50, 40, STR_NOGAME);
			
			float x=INPUT_X;
			float y=INPUT_Y;
			FontColor(COLOR_1);
			SetFontZ(0);
			
			x=DrawButton(x, y, STR_BACKTOXMB , BUTTON_CIRCLE);
			x=DrawButton(x, y, STR_FILEMANAGER, BUTTON_SELECT);
			
			tiny3d_Flip();	
			ScreenShot();
			
			if(new_pad & BUTTON_SELECT) Draw_FileExplorer();
			
			if(new_pad & BUTTON_CIRCLE) {
				end_checking();
				sysModuleUnload(SYSMODULE_PNGDEC);
				sysModuleUnload(SYSMODULE_JPGDEC);
				ioPadEnd();
				return 0;
			}
		}

		scene = SCENE_MAIN;
		
		cls();
		
		Draw_BG();

		Draw_PIC1();
		Draw_MAIN();
		Draw_MAIN_input();
		Draw_Load_GamePIC();
		
		Draw_filter();
		Draw_filter_input();
		
		Draw_MENU();
		Draw_MENU_input();
		
		Draw_txt_viewer();
		Draw_txt_viewer_input();
		
		Draw_ICON0_creator();
		Draw_ICON0_creator_input();
		
		Draw_Notification();
		
		check_device();
		
		tiny3d_Flip();
		ScreenShot();
		
		ps3pad_read();
		
		input_MAIN();
		input_filter();
		input_MENU();
		txt_viewer_input();
		input_ICON0_creator();
	}
	
	return 0;
}

void Draw_scene()
{
	if(scene == SCENE_FILEMANAGER) 
	{
		Draw_BGS();
		Draw_window();
		Draw_option();
		Draw_properties();
		Draw_picture_viewer();
		Draw_txt_viewer();
		Draw_SFO_viewer();
		Draw_Notification();
		Draw_cursor();
	} else
	if(scene == SCENE_MAIN) 
	{
		Draw_BG();
		Draw_MAIN();
		Draw_filter();
		Draw_MENU();
	}
}
