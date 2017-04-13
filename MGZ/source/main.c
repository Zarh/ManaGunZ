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

#define IRIS		0
#define MM			1
#define SNAKE		2  // cobra else mamba

#define REACTPSN	2

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
#define PS1_STR			27
#define PS2_STR			28
#define PS3_STR			29
#define PSP_STR			30

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

#define BIG_PICT 32

#define FS_S_IFMT 0170000
#define FS_S_IFDIR 0040000

static u32 text_size = 0;
u16 * ttf_texture;

#define PAYLOAD_OFFSET				  0x3d90
#define PERMS_OFFSET					0x8000000000003560ULL
#define PAYLOAD_UMOUNT_OFFSET		   (0x3d90+0x400)
#define PATCH_JUMP(add_orig, add_dest) lv2poke32(add_orig, 0x48000000 | ((add_dest-(add_orig-0x8000000000000000ULL)) & 0x3fffffc))
#define PATCH_CALL(add_orig, add_dest) lv2poke32(add_orig, 0x48000000 | ((add_dest-(add_orig-0x8000000000000000ULL)) & 0x3fffffc) | 1)

#define USB_MASS_STORAGE_1(n)	(0x10300000000000AULL+(n)) // For 0-5 
#define USB_MASS_STORAGE_2(n)	(0x10300000000001FULL+((n)-6)) // For 6-127
#define USB_MASS_STORAGE(n)	(((n) < 6) ? USB_MASS_STORAGE_1(n) : USB_MASS_STORAGE_2(n))

#define MAX_SECTIONS	((0x10000-sizeof(rawseciso_args))/8)

#define MAX_FRAME	1024

#define SCENE_FILEMANAGER			0
#define SCENE_PS3_MENU				1
#define SCENE_PS2_MENU				2
#define SCENE_PS1_MENU				3
#define SCENE_PSP_MENU				4
#define SCENE_PS2_CONFIG_EDITOR		5
#define SCENE_SETTINGS				6
#define SCENE_MAIN					7

u8 scene;

typedef struct
{
	uint64_t device;
	uint32_t emu_mode;
	uint32_t num_sections;
	uint32_t num_tracks;
} __attribute__((packed)) rawseciso_args;

SYS_PROCESS_PARAM(1200, 0x80000);

u64 SYSCALL_TABLE;
u64 HV_START_OFFSET;
u64 OFFSET_FIX;
u64 OFFSET_2_FIX;
u64 OFFSET_FIX_3C;
u64 OFFSET_FIX_2B17;
u64 OFFSET_FIX_LIC;
u64 OPEN_HOOK;
u64 BASE_ADDR;
u64 UMOUNT_SYSCALL_OFFSET;
u64 LV2MOUNTADDR;
u64 LV2MOUNTADDR_ESIZE;
u64 LV2MOUNTADDR_CSIZE;
u64 NEW_POKE_SYSCALL_ADDR;
u64 PAYLOAD_SKY;
size_t PAYLOAD_SKY_SIZE;
u64 UMOUNT;
size_t UMOUNT_SIZE;
u64 MAMBA;
size_t MAMBA_SIZE;
u64 *MAMBA_LOADER;
size_t MAMBA_LOADER_SIZE;
u64 OFFSET_1_IDPS;
u64 OFFSET_2_IDPS;

char temp_buffer[8192];
char temp_title[128];
u64 restore_syscall8[2] = {0,0};

static char *table_compare[19];
static char *table_replace[19];
static int ntable = 0;

static u8 loading = 1;
static char loading_log[20][255];
static u32 time_not = 0;
static char not_msg[255];

static char list_device[20][20]={{0}};
static int8_t device_number=-1;
static int8_t device_plug=0;
static u8 checking=YES;

static int64_t Load_GamePIC_progbar = -1;
static u8 Load_GamePIC=NO;

static u8 load_PIC1=NO;

#define MAX_GAME 512
static char list_game_path[MAX_GAME][128] = {{0}};
static char list_game_title[MAX_GAME][128] = {{0}};
static u8 list_game_platform[MAX_GAME] = {0};
static int game_number = -1;

static char list_FAV_game_path[100][128] = {{0}};
static char list_FAV_game_title[100][128]= {{0}};
static int8_t FAV_game_number = -1;

static char scan_dir[30][128];
static int8_t scan_dir_number=0;

int firmware = 0;

typedef struct
{
	char src[384];
	char dst[384];
} redir_files_struct;
static redir_files_struct file_to_map[8];
static u8 max_mapped=0;

static u8 cobra = NO, iso = NO, splitted_iso = NO, mamba = NO, usb = NO;
static u8 FLOW_inverse_button=YES;
static u8 mount_app_home = NO;
static u8 use_ex_plug = NO;
static u8 emu = NONE;
static u8 prim_USB = NO;
static u8 ext_game_data= NO;
static u8 payload = MM;
static u8 direct_boot = NO;
static u8 real_disk = NO;
static u8 AutoM = NO;
static u8 libfs_from = MM;
static int8_t device = 0;
static u8 gui_called = NO;
static u8 Game_stuff = YES;
static char GamPath[128];
char ManaGunZ_id[10];

static u8 clean_syscall = NO;
static u8 change_IDPS = NO;
static u8 IDPS[0x10]={0};
static u8 LIST_Show_ICON0 = NO;
static u8 FLOW_use_Cover = NO;
static u8 Show_COVER = NO;
static u8 Show_PIC1 = NO;
static u8 Show_PS3 = YES;
static u8 Show_PS2 = YES;
static u8 Show_PS1 = YES;
static u8 Show_PSP = YES;
static u8 Only_FAV = NO;

u8 size_font=20;

float X_MAX = 848.0;
float Y_MAX = 512.0;

typedef struct
{
	void *bmp_out;

	u32 pitch;
	u32 width;
	u32 height;
} imgData; // pngData = jpgData = imgData

u32 * texture_mem;

u32 * ICON0_texture_mem;
imgData ICON0[MAX_GAME];
u32 ICON0_offset[MAX_GAME];

u32 * COVER_texture_mem;
imgData COVER[MAX_GAME];
u32 COVER_offset[MAX_GAME];

// *************************** LIST ***************************
u32 * List_BG_texture_mem;
u32 List_BG_offset;
imgData List_BG;

u32 * List_BG_ICON0_texture_mem;
imgData List_BG_ICON0;
u32 List_BG_ICON0_offset;

// *************************** GRID ***************************
u32 * GRID_BG_texture_mem;
imgData GRID_BG;
u32 GRID_BG_offset;

u32 * GRID_BGS_texture_mem;
imgData GRID_BGS;
u32 GRID_BGS_offset;

// *************************** XMB ***************************

u32 * XMB_Col_texture_mem[6];
imgData XMB_Col[6];
u32 XMB_Col_offset[6];

#define COL_SET		0
#define COL_FAV		1
#define COL_PS3		2
#define COL_PS2		3
#define COL_PS1		4
#define COL_PSP		5
static char *Columns[6]={"SETTINGS", "FAVORITES", "PS3", "PS2", "PS1", "PSP"};

//Icons frm MM thm XMB.PNG
u32 * XMB_MMTHM_XMB_texture_mem;
imgData XMB_MMTHM_XMB;
u32 XMB_MMTHM_XMB_offset;
//Icons frm MM thm XMB2.PNG
u32 * XMB_MMTHM_XMB2_texture_mem;
imgData XMB_MMTHM_XMB2;
u32 XMB_MMTHM_XMB2_offset;
//BG
u32 * XMB_BG_texture_mem;
imgData XMB_BG[MAX_FRAME];
u32 XMB_BG_offset[MAX_FRAME];

//BG Setting
u32 * XMB_BGS_texture_mem;
imgData XMB_BGS;
u32 XMB_BGS_offset;
//Side BG
u32 * XMB_SIDEBAR_texture_mem;
imgData XMB_SIDEBAR;
u32 XMB_SIDEBAR_offset;

// *************************** FLOW ***************************
//Flow BG
u32 * Flow_BG_texture_mem;
imgData Flow_BG;
u32 Flow_BG_offset;
//Flow BG Settings
u32 * Flow_BGS_texture_mem;
imgData Flow_BGS;
u32 Flow_BGS_offset;

// *************************File Manager **********************

u32 * FM_PIC_texture_mem;
imgData FM_PIC;
u32 FM_PIC_offset;
char FM_PIC_path[255];

static u8 XMB_H_position = 2;
static u32 XMB_nb_lin[6] = {0};
static u32 XMB_V_position[6] = {0};
static int XMB_curs_move_x = -180;
static long int XMB_curs_move_y[6] = {0};

static u8 use_sidemenu = NO;
static u8 scan_dir_position=0;

static int Flow_curs_move_x = 0;

u32 * COMMON_texture_mem;
imgData COMMON[32];
u32 COMMON_offset[32];

static u8 XMB_priority = NO;

char *UI[4] = {"List", "Grid", "XMB", "Flow"};
static u8 UI_position = LIST;

static char Themes_Names_list[4][128][255];
static char Themes_Paths_list[4][128][255];
static char Themes[4][128];
static u8 Themes_position[4] = {0}; 
static int8_t Themes_number[4] = {-1,-1,-1,-1}; // ou {[0 ... 3] = -1}

static u8 grid_nb_lines = 5;
static u8 grid_nb_columns = 5;
static u8 grid_type = SCROLL;
static u8 direction = VERTICAL;
static u8 animated = YES;
static u8 keep_prop = YES;
static float Grid_move = 0;

static float Grid_curs_move_x = 0;
static float Grid_curs_move_y = 0;

static char copy_log[10][128];
static char copy_file[128];
static char copy_src[128];
static char copy_dst[128];

static u64 copy_current_size;
u64 total_size;
static u64 file_copy_prog_bar;
static u8 gathering;

static int nb_file = 0;
static int nb_directory = 0;

static u8 copy_flag=NO;
static u8 copy_cancel=NO;
static u8 gathering_cancel=NO;

static char head_title[128];
int64_t prog_bar1_value=-1;
int64_t prog_bar2_value=-1;
u8 cancel = NO;

int8_t videoscale_x = 0;
int8_t videoscale_y = 0;

static int slow_it;
static u64 hold_it;
static int scroll_speed=6;

u32 COLOR_1 = WHITE;
u32 COLOR_2 = GREEN;
u32 COLOR_3 = ORANGE;
u32 COLOR_4 = RED;

uint8_t ERR = FALSE;
uint8_t WAR = FALSE;

int position=0;
int first_line = 0, nb_line=0, last_line;
int hold_CIRCLE=0;
int first_icon = 0, nb_icon, last_icon=-1;
int x_L = 0;
int y_L = 0;

float w_ICON0;  
float h_ICON0;
float e_w = 10;
float e_h = 10;
float speed = 9;
float XMB_w = 72;
float XMB_h = 40;

float FLOW_w = 80;
float FLOW_h = 44;

static u8 picture_viewer_activ = NO;

u8 Display_PIC1 = NO;

// ******* MENU **********

#define MAX_ITEMS				32
#define MAX_ITEMS_LENGTH		128
#define MAX_ITEMS_VALUE			32
#define MAX_ITEMS_VALUE_LENGTH	128

#define MAX_TITLE_LENGHT		128

#define ITEM_TEXTBOX	0
#define ITEM_CHECKBOX	1
#define ITEM_COLORBOX	2

u8 MENU=NO;

char ITEMS[MAX_ITEMS][MAX_ITEMS_LENGTH];
s8 ITEMS_NUMBER;
char ITEMS_VALUE[MAX_ITEMS][MAX_ITEMS_VALUE][MAX_ITEMS_VALUE_LENGTH];
s8 ITEMS_VALUE_NUMBER[MAX_ITEMS];

u8 ITEMS_POSITION;
u8 ITEMS_VALUE_POSITION[MAX_ITEMS];
u8 ITEMS_VALUE_SHOW[MAX_ITEMS];
u8 ITEMS_TYPE[MAX_ITEMS];

u8 IN_ITEMS_VALUE=NO;

float MENU_ITEMS_X;
float MENU_ITEMS_VALUE_X;

int MENU_COLUMN_ITEMS_NUMBER;
float MENU_COLUMN_ITEMS_W;

char TITLES[MAX_ITEMS][MAX_TITLE_LENGHT];

u8 MENU_SIDE;

float x_COLOR;
float y_COLOR;

// **************** //

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
void Draw_FileExplorer(char *path);
void show_msg(char *str);
char *LoadFromISO(char *path, char *filename, int *size);
u8 get_ext(char *file);
void read_fav();
int Draw_Progress_Bar(float x, float y, u8 size, float value, u32 color);
u32 Get_CRC(char *Elf_Name);
void Draw_scene();
void Draw_title(float x, float y, char *str);
void peek_IDPS();
void start_load_PIC1();
void end_load_PIC1();
int SaveFile(char *path, char *mem, int file_size);

//*******************************************************
//GUI
//*******************************************************

void cls()
{
	tiny3d_Clear(0xff000000, TINY3D_CLEAR_ALL);
		
	// Enable alpha Test
	tiny3d_AlphaTest(1, 0x10, TINY3D_ALPHA_FUNC_GEQUAL);

   // Enable alpha blending.
			tiny3d_BlendFunc(1, TINY3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA | TINY3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
				TINY3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA | TINY3D_BLEND_FUNC_DST_ALPHA_ZERO,
				TINY3D_BLEND_RGB_FUNC_ADD | TINY3D_BLEND_ALPHA_FUNC_ADD);
	reset_ttf_frame();
}

void Init_Graph()
{
	tiny3d_Init(1024*1024);
	u32 * texture_pointer;
	texture_mem = tiny3d_AllocTexture(170*1024*1024); // alloc 170MB of space for textures (this pointer can be global)	
	if(!texture_mem) return; 
	texture_pointer = texture_mem;
	ResetFont();
	
	TTFLoadFont(0, "/dev_flash/data/font/SCE-PS3-SR-R-LATIN2.TTF", NULL, 0);
	TTFLoadFont(1, "/dev_flash/data/font/SCE-PS3-DH-R-CGB.TTF", NULL, 0);
	TTFLoadFont(2, "/dev_flash/data/font/SCE-PS3-SR-R-JPN.TTF", NULL, 0);
	TTFLoadFont(3, "/dev_flash/data/font/SCE-PS3-YG-R-KOR.TTF", NULL, 0);
	
	ttf_texture = (u16 *) texture_pointer;
	texture_pointer += 1024 * 16;
	texture_pointer = (u32 *) init_ttf_table((u16 *) texture_pointer);
	text_size = (u32) (u64)(((u8 *) texture_pointer + BIG_PICT * 4096 * 1024 + 1980 * 1080 * 4 + 2048 * 1200 * 4) - ((u8 *) texture_mem));
	
	COMMON_texture_mem = texture_pointer;
	
	double sx = (double) Video_Resolution.width;
	double sy = (double) Video_Resolution.height;
	double psx = (double) (1000 + videoscale_x)/1000.0;
	double psy = (double) (1000 + videoscale_y)/1000.0;
	
	tiny3d_UserViewport(1, 
		(float) ((sx - sx * psx) / 2.0), // 2D position
		(float) ((sy - sy * psy) / 2.0), 
		(float) ((sx * psx) / X_MAX),	// 2D scale
		(float) ((sy * psy) / Y_MAX),
		(float) ((sx / 1920.0) * psx),  // 3D scale
		(float) ((sy / 1080.0) * psy));

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
		(float) ((sx / 1920.0) * psx),  // 3D scale
		(float) ((sy / 1080.0) * psy));
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
		float PI = 3.14159265;
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

float Draw_checkbox(u8 checked, float x, float y, char *str, u32 color)
{
	Draw_Box(x, y, 0, 0, 14, 14, color, NO);
	Draw_Box(x+2, y+2, 0, 0, 10, 10, BLACK, NO);
	
	if(checked) Draw_Box(x+3, y+3, 0, 0, 8, 8, color, NO);
	
	SetFontColor(color, 0x0);
	SetFontSize(15, 15);
	
	return DrawString(x+20, y, str);
}

void Draw_title(float x, float y, char *str)
{
	int xt;
	SetFontSize(18, 18);
	Draw_Box(x+5, y+4, 0, 0, 8, 8, COLOR_3, NO);
	SetFontColor(COLOR_3, 0x0);
	xt=DrawString(x+20, y, str);
	y+=18;
	Draw_Box(x, y, 0, 0, xt-x, 2, COLOR_3, NO); //underline
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
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
		char *mem = LoadFromISO(list_game_path[position], "/PS3_GAME/ICON0.PNG", &size);
		if(mem==NULL) return;
		pngLoadFromBuffer((const void *) mem, size, (pngData *) &ICON0[position]);
		free(mem);
	} else
	if(list_game_platform[position] == _ISO_PSP) {
		int size;
		char *mem = LoadFromISO(list_game_path[position], "/PSP_GAME/ICON0.PNG", &size);
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

	FILE *file = fopen(path, "rb");
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
	u8 loaded=NO;
	
	if(loading == NO) {
		loaded=YES;
		start_loading();
	}
	
	u32 * texture_pointer;
	texture_pointer = FM_PIC_texture_mem;
	
	memset(&FM_PIC, 0, sizeof(FM_PIC));
	FM_PIC_offset = 0;
	
	if(is_apng(FM_PIC_path) == YES) {
		Load_APNG(FM_PIC_path);
		if(loaded == YES) end_loading();
		return;
	}

	imgLoadFromFile(FM_PIC_path, &FM_PIC);
	
	if(FM_PIC.bmp_out) {
		memcpy(texture_pointer, FM_PIC.bmp_out, FM_PIC.pitch * FM_PIC.height);
		free(FM_PIC.bmp_out);
		FM_PIC_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((FM_PIC.pitch * FM_PIC.height + 15) & ~15) / 4;
	}

	if(loaded == YES) end_loading();
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
	u32 * texture_pointer;
	texture_pointer = ICON0_texture_mem;
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
	
	COVER_texture_mem = texture_pointer;
}

u8 COVER_Loaded;
void Load_COVER() 
{
	u32 * texture_pointer;
	texture_pointer = COVER_texture_mem;
	int i;
	
	if(Load_GamePIC==NO) return;
	
	COVER_Loaded = NO;
	
	if(Show_COVER==YES) {
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
		COVER_Loaded = YES;
	}
	Load_GamePIC_progbar = -1;
	
	FM_PIC_texture_mem = texture_pointer;
}

static sys_ppu_thread_t Load_GamePIC_id;

void Load_GamePIC_thread(void *unused)
{
	memset(ICON0_offset, 0, sizeof(ICON0_offset));
	memset(ICON0, 0, sizeof(ICON0));
	memset(COVER_offset, 0, sizeof(COVER_offset));
	memset(COVER, 0, sizeof(COVER));
	FM_PIC_offset = 0;
	
	Load_ICON0();
	Load_COVER();
	
	while(Load_GamePIC == YES) sleep(1);
	
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

void Draw_COVER(int position, float x , float y, float z, float w, float h)
{
	if(position < 0 || game_number < position) return;
	
	if(COVER_offset[position] != 0) {
		tiny3d_SetTexture(0, COVER_offset[position], COVER[position].width, COVER[position].height, COVER[position].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if(h==0 && w!=0) {
			Draw_Box(x, y, z, 0, w, COVER[position].height * w / COVER[position].width, WHITE, YES);
		}
		else if(h!=0 && w==0) {
			Draw_Box(x, y, z, 0, COVER[position].width * h / COVER[position].height, h, WHITE, YES);
		}
		else if(h==0 && w==0) {
			Draw_Box(x, y, z, 0, COVER[position].width, COVER[position].height, WHITE, YES);
		} else Draw_Box(x, y, z, 0, w, h, WHITE, YES);
	}
}

void Draw_CoverFromCenter(int position, float x, float y, float z, float w, float h)
{
	if(position < 0 || game_number < position) return;
	
	if(COVER_offset[position] != 0) {
		tiny3d_SetTexture(0, COVER_offset[position], COVER[position].width, COVER[position].height, COVER[position].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if(h==0 && w!=0) {
			Draw_Box(x-w/2, y-(COVER[position].height*w/COVER[position].width) / 2, z, 0, w, (COVER[position].height*w/COVER[position].width), WHITE, YES);
		}
		else if(h!=0 && w==0) {
			Draw_Box(x-(COVER[position].width*h/COVER[position].height)/2, y-h/2, z, 0, COVER[position].width * h / COVER[position].height, h, WHITE, YES);
		}
		else if(h==0 && w==0) {
			Draw_Box(x-COVER[position].width/2, y-COVER[position].height/2, z, 0, COVER[position].width, COVER[position].height, WHITE, YES);
		} else Draw_Box(x-w/2, y-h/2, z, 0, w, h, WHITE, YES);
	}
}

u8 get_FileOffset(FILE *fd, char *path, u32 *flba, u32 *size)
{
	
	u32 root_table = 0;
	fseek(fd, 0x800*0x10+0xA2, SEEK_SET);
	
	fread(&root_table, sizeof(u32), 1, fd);
	if(root_table == 0) return FAILED;
	
	fseek(fd, 0x800*root_table, SEEK_SET);
	
	char *sector = (char *) malloc(0x800);
	if(sector == NULL) {
		print_load("Error : get_FileOffset : malloc");
		return FAILED;
	}
	
	int i;
	int k=0;
	char item_name[255];
	for(i=0; i <= strlen(path); i++) {
		if(i==0 && path[0] == '/') continue;
		
		if(path[i] == '/' || i==strlen(path)) {
			strncpy(item_name, path+i-k, k);
			memset(sector, 0, sizeof(sector));
			u32 offset=0;
			fread(sector, 0x800, 1, fd);
			int j;
			for(j=0; j<0x800; j++) {
				if(!memcmp((char *) &sector[j], (char *) item_name , strlen(item_name))) {
					if(i==strlen(path)) {
						memcpy(&offset, &sector[j-0x1B], 4);
						*flba = offset;
						memcpy(&offset, &sector[j-0x13], 4);
						*size = offset;
						free(sector);
						return SUCCESS;
					}
					memcpy(&offset, &sector[j-0x1B], 4);
					fseek(fd, 0x800*offset, SEEK_SET);
					
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
	FILE *f;
	f = fopen(isopath, "rb");			
	if(f==NULL) {
		print_load("Error : failed to open %s", isopath);
		return FAILED;
	}
	
	u32 flba=0;
	u32 size=0;
	u8 ret;
	char *mem = NULL;
	
	ret = get_FileOffset(f, filename, &flba, &size); 
	
	if(flba==0 || size==0 || ret == FAILED) {
		print_load("Error : file_pos flba= %X size= %X %s", flba, size, isopath);
		fclose(f);
		return FAILED;
	}

	if((mem = malloc(size)) == NULL)	{
		print_load("Error : failed to malloc");
		fclose(f);
		return FAILED;
	}
	
	fseek(f, 0x800*flba, SEEK_SET);
	fread(mem, size, 1, f);
	
	FILE *fi;
	fi=fopen(output, "wb");
	if(fi==NULL) {
		print_load("Error : Cannot create %s", output);
		free(mem);
		fclose(f);
		return FAILED;
	}
	fwrite((void *) mem, size, 1, fi);
	
	fclose(fi);
	fclose(f);
	
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
		strtok(ICON_OUT, ".");
		strcat(ICON_OUT, ".PNG");
		strcpy(PARAM_OUT, list_game_path[i]);
		strtok(PARAM_OUT, ".");
		strcat(PARAM_OUT, ".SFO");
		
		if(path_info(ICON_OUT)==_NOT_EXIST) {
			ExtractFromISO(list_game_path[i], ICON_IN, ICON_OUT);
		}
		if(path_info(PARAM_OUT)==_NOT_EXIST) {
			if(ExtractFromISO(list_game_path[i], PARAM_IN, PARAM_OUT) == SUCCESS) {
				if(GetParamSFO("TITLE", list_game_title[i], i, NULL)==FAILED) {
					strcpy(list_game_title[i], list_game_path[i]);
					strcpy(list_game_title[i], &strrchr(list_game_title[i], '/')[1]);
					strtok(list_game_title[i], ".");
				}
			}
		}
	}
}

void Draw_DEFAULT(int position, float x , float y, float z,  float w, float h)
{
	if(position < 0 || game_number < position) return;
	
	int type = list_game_platform[position];
	if(type == _JB_PS1 || type == _JB_PS2 || type == _JB_PS3 || type == _JB_PSP) {
		if(COMMON_offset[DEFAULT_JB] != 0) {
			tiny3d_SetTexture(0, COMMON_offset[DEFAULT_JB], COMMON[DEFAULT_JB].width, COMMON[DEFAULT_JB].height, COMMON[DEFAULT_JB].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			Draw_Box(x, y, z, 0, w, h, WHITE, YES);
		}
	} else
	if(type == _ISO_PS1 || type == _ISO_PS2 || type == _ISO_PS3 || type == _ISO_PSP) {
		if(COMMON_offset[DEFAULT_ISO] != 0) {
			tiny3d_SetTexture(0, COMMON_offset[DEFAULT_ISO], COMMON[DEFAULT_ISO].width, COMMON[DEFAULT_ISO].height, COMMON[DEFAULT_ISO].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			Draw_Box(x, y, z, 0, w, h, WHITE, YES);
		}
	} else {
		if(COMMON_offset[DEFAULT] != 0) {
			tiny3d_SetTexture(0, COMMON_offset[DEFAULT], COMMON[DEFAULT].width, COMMON[DEFAULT].height, COMMON[DEFAULT].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
			Draw_Box(x, y, z, 0, w, h, WHITE, YES);
		}		
	}
	
	if(type == _JB_PS1 || type == _ISO_PS1) Draw_Box(x, y, z, 0, w, h, COLOR_PS1 - 0x90, NO);
	if(type == _JB_PS2 || type == _ISO_PS2) Draw_Box(x, y, z, 0, w, h, COLOR_PS2 - 0x90, NO);
	if(type == _JB_PS3 || type == _ISO_PS3) Draw_Box(x, y, z, 0, w, h, COLOR_PS3 - 0x90, NO);
	if(type == _JB_PSP || type == _ISO_PSP) Draw_Box(x, y, z, 0, w, h, COLOR_PSP - 0x90, NO);
}

void Draw_ICON0(int position, float x, float y, float z,  float w, float h)
{
	if(position < 0 || game_number < position) return;
	
	if(UI_position==LIST) {
		if(List_BG_ICON0_offset != 0) {
			tiny3d_SetTexture(0, List_BG_ICON0_offset, List_BG_ICON0.width, List_BG_ICON0.height, List_BG_ICON0.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			Draw_Box(0, 0, z+1, 0, List_BG_ICON0.width, List_BG_ICON0.height, WHITE, YES);
		}
	}
	
	if(ICON0_offset[position] != 0) {
		tiny3d_SetTexture(0, ICON0_offset[position], ICON0[position].width, ICON0[position].height, ICON0[position].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if(ICON0[position].height >= ICON0[position].width) {
			float w1= ICON0[position].width * h / ICON0[position].height;
			float x1 = x + (w-w1)/2;
			Draw_Box(x1, y, z, 0, w1, h, WHITE, YES);
		} else Draw_Box(x, y, z, 0, w, h, WHITE, YES);
		
	}
	else Draw_DEFAULT(position, x, y, z, w, h);
	
	
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

fcTL_data XMB_BG_data[MAX_FRAME];
u32 XMB_BG_frame=0;
u32 XMB_BG_num_frames;

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
	
	u32 * texture_pointer;
	texture_pointer = FM_PIC_texture_mem;
	
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
		} // not animated
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
		
		//FILE *x;
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
	SetFontColor(WHITE, 0);
	DrawStringFromCenterX(424, 462 , &strrchr(FM_PIC_path, '/')[1]);
	
	if(APNG_data[APNG_frame].delay_den == 0) APNG_data[APNG_frame].delay_den=100;
	//usleep((float) APNG_data[APNG_frame].delay_num * 1000000 / (float) APNG_data[APNG_frame].delay_den);
	
	if( get_time(0) > (APNG_data[APNG_frame].delay_num * 1000 / APNG_data[APNG_frame].delay_den) ) {
		start_timer(0);
		APNG_frame++;
	}
	
}

u32 *Load_XMB_BG(char* filename, u32* texture_pointer)
{
	FILE* f;
	u64 magic;
	u32 pos;
	chunk_header ch;
	
	u8 IEND_[0xC] = {0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82};
	
	u8 Frame_Header[0x29];
	acTL_data ad;
	
	memset(XMB_BG_data, 0, sizeof(XMB_BG_data));
	memset(XMB_BG, 0, sizeof(XMB_BG));
	memset(XMB_BG_offset, 0, sizeof(XMB_BG_offset));
	XMB_BG_num_frames = 0;
	
	prog_bar2_value=0;
	
	f = fopen(filename, "rb");

	if(f==NULL) {
		//print_load("Error :  failed to open file");
		return texture_pointer;
	}
	
	fread(&magic, 1, 8, f);
	
	if(magic != MAGIC_PNG) { 
		//print_load("Error :  bad magic"); 
		fclose(f); return texture_pointer;
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
			return texture_pointer;
		} // not animated
	}

	fread(&ad, 1, ch.length, f);
	
	XMB_BG_num_frames = ad.num_frames;

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
		fread(&XMB_BG_data[i], 1, ch.length, f);
		
		*(u32 *) &Frame_Header[0x10] = XMB_BG_data[i].width;
		*(u32 *) &Frame_Header[0x14] = XMB_BG_data[i].height;
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
			return texture_pointer;
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
		
		//FILE *x;
		//char frame_path[128];
		//mkdir("/dev_hdd0/frames", 0777);
		//sprintf(frame_path, "/dev_hdd0/frames/frame_%d.png", i);
		//x = fopen(frame_path, "wb");
		//fwrite(frame, 1, 0x29 + tot_size + 4 + 0xC, x);
		//fclose(x);
		
		pngLoadFromBuffer((const void *) frame, 0x29 + tot_size + 4 + 0xC, (pngData *) &XMB_BG[i]);
		
		free(frame);
		
		if(XMB_BG[i].bmp_out) {
			memcpy(texture_pointer, XMB_BG[i].bmp_out, XMB_BG[i].pitch * XMB_BG[i].height);
			free(XMB_BG[i].bmp_out);
			XMB_BG_offset[i] = tiny3d_TextureOffset(texture_pointer);
			texture_pointer += ((XMB_BG[i].pitch * XMB_BG[i].height + 15) & ~15) / 4;
		}
	}
	
	init_timer(1);
	XMB_BG_frame=0;
	
	prog_bar2_value=-1;
	
	return texture_pointer;
}

void Draw_XMB_BG()
{
	if(time_s[1]==0) start_timer(1);	
	
	if(XMB_BG_frame >= XMB_BG_num_frames) XMB_BG_frame = 0;
	
	if(XMB_BG_offset[XMB_BG_frame] != 0) {
		tiny3d_SetTexture(0, XMB_BG_offset[XMB_BG_frame], XMB_BG[XMB_BG_frame].width, XMB_BG[XMB_BG_frame].height, XMB_BG[XMB_BG_frame].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
	}
	
	if(XMB_BG_data[XMB_BG_frame].delay_den == 0) XMB_BG_data[XMB_BG_frame].delay_den=100;
	
	if( get_time(1) > (XMB_BG_data[XMB_BG_frame].delay_num * 1000 / XMB_BG_data[XMB_BG_frame].delay_den) ) {
		start_timer(1);
		XMB_BG_frame++;
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

int Build_APNG(char (*pngs)[512], uint32_t nb, char *apng, float time)
{
	print_head("Making APNG...");
	
	FILE *in;
	FILE *out;
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
	
	for(i=0; i< nb; i++) {
		prog_bar1_value = i*100/nb;
		print_load("FILE : %s", &strrchr(pngs[i], '/')[1]);
		in = NULL;
		in = fopen(pngs[i], "rb");
		if(in == NULL) {
			fclose(out);
			Delete(apng);
			printf("Error : Failed to open %s", pngs[i]);
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
			
			if(feof(in)) {print_load("Error : EOF, IDAT/IEND not found"); fclose(in); fclose(out); Delete(apng); return FAILED;}
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

static char PNGS[MAX_FRAME][512];

u8 make_ABG(char *dir_path, char *file_out)
{
	
	char JS[255];
	
	int png_number=-1;
	
	u8 Header_REF[0x21];
	u8 Header[0x21];
	
	memset(PNGS, 0, sizeof(PNGS));
	
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

			FILE *fo;
			fo = fopen(temp, "rb");
			fread(&Header, 0x21, 1, fo);
			fclose(fo);
			
			if( png_number == -1 ) {

				u32 w = *(uint32_t *) &Header[0x10];	
				u32 h = *(uint32_t *) &Header[0x14];

				if( w > 640 && h > 480) {

					memcpy(Header_REF, Header, 0x21);
					png_number++;
					strcpy(PNGS[png_number], temp);
				}
 			} 
			else {

				if( memcmp(Header, Header_REF, 0x21) == 0 ) {
					png_number++;
					strcpy(PNGS[png_number], temp);
				}
			}
		}
	}
	closedir(d);
	
	if(png_number < 0) return FAILED; else
	if(png_number==0) return Copy(PNGS[0], file_out);
	
	char ta[255], tb[255];
	int i,j, min;
	for(i = 0; i<png_number; i++) { 
		min = i;
		for (j = i+1; j <= png_number; j++) { 
			strcpy(ta , PNGS[j]);
			strcpy(tb, PNGS[min]);
			if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
			if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
			if (strcmp(ta, tb) < 0) { 
				min = j; 
			} 
		}
		if(min==i) continue;
		strcpy(ta , PNGS[min]);
		strcpy(PNGS[min], PNGS[i]); 
		strcpy(PNGS[i], ta); 
	}

	float time=0.0;
	int size;
	char temp[64];

	char *script = LoadFile(JS, &size);
	if(script == NULL) return Build_APNG(PNGS, png_number, file_out, 0);

	if( strstr(script, " IntervalTimer(") == NULL) {
		free(script);
		return Build_APNG(PNGS, png_number, file_out, 0);
	}

	memcpy(temp, strstr(script, " IntervalTimer(") + 15, 64);
	
	if( strstr(temp, ",") == NULL) {
		free(script);
		return Build_APNG(PNGS, png_number, file_out, 0);
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

	return Build_APNG(PNGS, png_number, file_out, time);
	
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
	FILE *f=NULL;
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
		
		FILE *fp;
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
	FILE *f=NULL;
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
	u8 animated = NO;
	FILE *fp;
	
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
				animated = YES;
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
		if(animated == NO) {
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
				
				print_head("Making animated Background...");
				if(make_ABG((char *) raf_tmp, (char *) dst)  == FAILED) {
					Delete(tmp_dir);
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
		strtok(gim, ".");
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
	
		FILE *fp;
		
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
	
	FILE *fp;
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
			FILE *out;
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

u8 ExtractTheme()
{
	char folder[255];
	u8 ret=SUCCESS;
	
	sprintf(folder, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position],  Themes_Names_list[UI_position][Themes_position[UI_position]]);
	mkdir(folder, 0777);
	
	u8 ThemeType = GetThemeType( Themes_Paths_list[UI_position][Themes_position[UI_position]]);
	
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
		char dst[255];
		if(UI_position == XMB) {
			
			sprintf(dst, "%s/%s.PNG", folder, Columns[0]);
			ret=GetFromP3T(Themes_Paths_list[UI_position][Themes_position[UI_position]], "icon_setting", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, Columns[1]);
			ret=GetFromP3T(Themes_Paths_list[UI_position][Themes_position[UI_position]], "icon_playermet", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, Columns[2]);
			ret=GetFromP3T(Themes_Paths_list[UI_position][Themes_position[UI_position]], "icon_game", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, Columns[3]);
			ret=GetFromP3T(Themes_Paths_list[UI_position][Themes_position[UI_position]], "icon_game", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, Columns[4]);
			ret=GetFromP3T(Themes_Paths_list[UI_position][Themes_position[UI_position]], "icon_game", dst);
			
			sprintf(dst, "%s/%s.PNG", folder, Columns[5]);
			ret=GetFromP3T(Themes_Paths_list[UI_position][Themes_position[UI_position]], "icon_remoteplay", dst);
			
			sprintf(dst, "%s/BG.JPG", folder);
			GetFromP3T(Themes_Paths_list[UI_position][Themes_position[UI_position]], "background", dst); // pas de ret car facultatif
			
		}
	}
	else {
		if(strstr(Themes_Paths_list[UI_position][Themes_position[UI_position]], "dev_hdd0") ==  NULL) {
			ret=Copy(Themes_Paths_list[UI_position][Themes_position[UI_position]], folder);
		}
	}
	
	if(ret==FAILED) Delete(folder);
	
	return ret;

}

u8 is_listed(char *Name, u8 Interface)
{
	int i;
	for(i=0; i<= Themes_number[Interface]; i++) {
		if(strcmp(Themes_Names_list[Interface][i], Name) == 0) {
			return YES;
		}
	}
	return NO;
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
	
		if(strstr(list_device[i], "dev_usb") != NULL || strstr(list_device[i], "ntfs") != NULL) {
			sprintf(THM_path, "/%s/Themes", list_device[i]);
		} 
		else if(strstr(list_device[i], "dev_hdd0") != NULL) {
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
				
				if( is_listed(TempName, XMB) == NO) {
					Themes_number[XMB]++;
					strcpy(Themes_Paths_list[XMB][Themes_number[XMB]], TempPath);
					strcpy(Themes_Names_list[XMB][Themes_number[XMB]], TempName);
				}
				
				if( is_listed(TempName, FLOW) == NO) {
					Themes_number[FLOW]++;
					strcpy(Themes_Paths_list[FLOW][Themes_number[FLOW]], TempPath);
					strcpy(Themes_Names_list[FLOW][Themes_number[FLOW]], TempName);
				}
				
			}
			else if(ThemeType == P3T) {
				
				sprintf(TempPath, "%s/%s", THM_path, dir->d_name);
				ret = GetFromP3T(TempPath, "name", TempName);
				if(ret==FAILED) {
					memcpy(TempName, dir->d_name, strlen(dir->d_name)-4);
				}
				
				if( is_listed(TempName, XMB) == NO) {
					Themes_number[XMB]++;
					strcpy(Themes_Paths_list[XMB][Themes_number[XMB]], TempPath);
					strcpy(Themes_Names_list[XMB][Themes_number[XMB]], TempName);
				}
				
			}
			else if(strcmp(dir->d_name, "List") == 0) k=LIST;
			else if(strcmp(dir->d_name, "Grid") == 0) k=GRID;					
			else if(strcmp(dir->d_name, "XMB")  == 0) k=XMB;
			else if(strcmp(dir->d_name, "Flow") == 0) k=FLOW;
			
			if(k!=-1) {
				sprintf(THM_subpath, "%s/%s", THM_path, dir->d_name);
				DIR *d2;
				struct dirent *dir2;
			
				d2 = opendir(THM_subpath);
				if(d2==NULL) continue;
			
				while ((dir2 = readdir(d2))) {
					if(!strncmp(dir2->d_name,"..", 2) || !strncmp(dir2->d_name,".", 1)) continue;
						
					sprintf(TempPath, "%s/%s", THM_subpath, dir2->d_name);
					strcpy(TempName, dir2->d_name);
					
					if( is_listed(TempName, k) == NO) {
						Themes_number[k]++;
						strcpy(Themes_Paths_list[k][Themes_number[k]], TempPath);
						strcpy(Themes_Names_list[k][Themes_number[k]], TempName);
					}
				}
				closedir(d2);
			}		
		}
		closedir(d);
	}
	
}

void Load_Themes()
{
	char temp[255];
	char thmPath[255];

	u32 * texture_pointer=NULL;
	
	GetThemes();
	
	List_BG_offset = 0;
	List_BG_ICON0_offset = 0;
	GRID_BG_offset = 0;
	GRID_BGS_offset = 0;
	XMB_Col_offset[0] = 0;
	XMB_Col_offset[1] = 0;
	XMB_Col_offset[2] = 0;
	XMB_Col_offset[3] = 0;
	XMB_Col_offset[4] = 0;
	XMB_Col_offset[5] = 0;
	XMB_MMTHM_XMB2_offset = 0;
	XMB_MMTHM_XMB_offset = 0;
	memset(XMB_BG_offset, 0, sizeof(XMB_BG_offset));
	XMB_BGS_offset = 0;
	XMB_SIDEBAR_offset = 0;
	Flow_BG_offset = 0;
	Flow_BGS_offset = 0;
	
	prog_bar1_value = 0;

	sprintf(thmPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s",  ManaGunZ_id, UI[0], Themes[0]);
	
	texture_pointer = List_BG_texture_mem;
	
	sprintf(temp, "%s/BG.PNG", thmPath);

	if(imgLoadFromFile(temp, &List_BG) == FAILED) {
		sprintf(temp, "%s/BG.JPG", thmPath);
		imgLoadFromFile(temp, &List_BG);
	}

	if(List_BG.bmp_out) {
		memcpy(texture_pointer, List_BG.bmp_out, List_BG.pitch * List_BG.height);
		free(List_BG.bmp_out);
		List_BG_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((List_BG.pitch * List_BG.height + 15) & ~15) / 4;
	}
	
	List_BG_ICON0_texture_mem = texture_pointer;
	
	texture_pointer = List_BG_ICON0_texture_mem;
	
	sprintf(temp, "%s/BG_ICON0.PNG", thmPath);
	
	if(imgLoadFromFile(temp, &List_BG_ICON0) == FAILED) {
		sprintf(temp, "%s/BG_ICON0.JPG", thmPath);
		imgLoadFromFile(temp, &List_BG_ICON0);
	}

	if(List_BG_ICON0.bmp_out) {
		memcpy(texture_pointer, List_BG_ICON0.bmp_out, List_BG_ICON0.pitch * List_BG_ICON0.height);
		free(List_BG_ICON0.bmp_out);
		List_BG_ICON0_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((List_BG_ICON0.pitch * List_BG_ICON0.height + 15) & ~15) / 4;
	}

	prog_bar1_value = 25;

	sprintf(thmPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s",  ManaGunZ_id, UI[1], Themes[1]);
	
	GRID_BG_texture_mem = texture_pointer;
	
	texture_pointer = GRID_BG_texture_mem;
	
	sprintf(temp, "%s/BG.PNG", thmPath);
	
	if(imgLoadFromFile(temp, &GRID_BG) == FAILED) {
		sprintf(temp, "%s/BG.JPG", thmPath);
		imgLoadFromFile(temp, &GRID_BG);
	}

	if(GRID_BG.bmp_out) {
		memcpy(texture_pointer, GRID_BG.bmp_out, GRID_BG.pitch * GRID_BG.height);
		free(GRID_BG.bmp_out);
		GRID_BG_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((GRID_BG.pitch * GRID_BG.height + 15) & ~15) / 4;
	}
	
	GRID_BGS_texture_mem = texture_pointer;
	
	texture_pointer = GRID_BGS_texture_mem;
	
	sprintf(temp, "%s/BGS.PNG", thmPath);
	
	if(imgLoadFromFile(temp, &GRID_BGS) == FAILED) {
		sprintf(temp, "%s/BGS.JPG", thmPath);
		imgLoadFromFile(temp, &GRID_BGS);
	}

	if(GRID_BGS.bmp_out) {
		memcpy(texture_pointer, GRID_BGS.bmp_out, GRID_BGS.pitch * GRID_BGS.height);
		free(GRID_BGS.bmp_out);
		GRID_BGS_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((GRID_BGS.pitch * GRID_BGS.height + 15) & ~15) / 4;
	}
	
	prog_bar1_value = 50;

	sprintf(thmPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s",  ManaGunZ_id, UI[2], Themes[2]);
	
	XMB_BG_texture_mem = texture_pointer;

	texture_pointer = XMB_BG_texture_mem;

	sprintf(temp, "%s/BG.PNG", thmPath);
	if(is_apng(temp) == YES) {
		texture_pointer = Load_XMB_BG(temp, texture_pointer);
	} else {
		
		if(imgLoadFromFile(temp, &XMB_BG[0]) == FAILED) {
			sprintf(temp, "%s/BG.JPG", thmPath);
			imgLoadFromFile(temp, &XMB_BG[0]);
		}

		if(XMB_BG[0].bmp_out) {
			memcpy(texture_pointer, XMB_BG[0].bmp_out, XMB_BG[0].pitch * XMB_BG[0].height);
			free(XMB_BG[0].bmp_out);
			XMB_BG_offset[0] = tiny3d_TextureOffset(texture_pointer);
			texture_pointer += ((XMB_BG[0].pitch * XMB_BG[0].height + 15) & ~15) / 4;
		}
	}

	XMB_BGS_texture_mem = texture_pointer;
	
	texture_pointer = XMB_BGS_texture_mem;
	
	sprintf(temp, "%s/BGS.PNG", thmPath);

	if(imgLoadFromFile(temp, &XMB_BGS) == FAILED) {
		sprintf(temp, "%s/BGS.JPG", thmPath);
		imgLoadFromFile(temp, &XMB_BGS);
	}

	if(XMB_BGS.bmp_out) {
		memcpy(texture_pointer, XMB_BGS.bmp_out, XMB_BGS.pitch * XMB_BGS.height);
		free(XMB_BGS.bmp_out);
		XMB_BGS_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((XMB_BGS.pitch * XMB_BGS.height + 15) & ~15) / 4;
	}
	
	XMB_SIDEBAR_texture_mem = texture_pointer;
	
	texture_pointer = XMB_SIDEBAR_texture_mem;

	sprintf(temp, "%s/SIDEBAR.PNG", thmPath);
	if(imgLoadFromFile(temp, &XMB_SIDEBAR) == FAILED) {
		sprintf(temp, "%s/SIDEBAR.JPG", thmPath);
		imgLoadFromFile(temp, &XMB_SIDEBAR);
	}

	if(XMB_SIDEBAR.bmp_out) {
		memcpy(texture_pointer, XMB_SIDEBAR.bmp_out, XMB_SIDEBAR.pitch * XMB_SIDEBAR.height);
		free(XMB_SIDEBAR.bmp_out);
		XMB_SIDEBAR_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((XMB_SIDEBAR.pitch * XMB_SIDEBAR.height + 15) & ~15) / 4;
	}

	int i;
	for(i=0; i<6; i++) {
		XMB_Col_texture_mem[i] = texture_pointer;
		
		texture_pointer = XMB_Col_texture_mem[i];
		
		sprintf(temp, "%s/%s.PNG", thmPath, Columns[i]);

		if(imgLoadFromFile(temp, &XMB_Col[i]) == FAILED) {
			sprintf(temp, "%s/%s.JPG", thmPath, Columns[i]);
			imgLoadFromFile(temp, &XMB_Col[i]);
		}

		if(XMB_Col[i].bmp_out) {
			memcpy(texture_pointer, XMB_Col[i].bmp_out, XMB_Col[i].pitch * XMB_Col[i].height);
			free(XMB_Col[i].bmp_out);
			XMB_Col_offset[i] = tiny3d_TextureOffset(texture_pointer);
			texture_pointer += ((XMB_Col[i].pitch * XMB_Col[i].height + 15) & ~15) / 4;
		}
	}

	XMB_MMTHM_XMB_texture_mem = texture_pointer;
	
	texture_pointer = XMB_MMTHM_XMB_texture_mem;
	
	sprintf(temp, "%s/MMTHM_XMB.PNG", thmPath);

	if(imgLoadFromFile(temp, &XMB_MMTHM_XMB) == FAILED) {
		sprintf(temp, "%s/MMTHM_XMB.JPG", thmPath);
		imgLoadFromFile(temp, &XMB_MMTHM_XMB);
	}

	if(XMB_MMTHM_XMB.bmp_out) {
		memcpy(texture_pointer, XMB_MMTHM_XMB.bmp_out, XMB_MMTHM_XMB.pitch * XMB_MMTHM_XMB.height);
		free(XMB_MMTHM_XMB.bmp_out);
		XMB_MMTHM_XMB_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((XMB_MMTHM_XMB.pitch * XMB_MMTHM_XMB.height + 15) & ~15) / 4;
	}

	XMB_MMTHM_XMB2_texture_mem = texture_pointer;
	
	texture_pointer = XMB_MMTHM_XMB2_texture_mem;
	
	sprintf(temp, "%s/MMTHM_XMB2.PNG", thmPath);

	if(imgLoadFromFile(temp, &XMB_MMTHM_XMB2) == FAILED) {
		sprintf(temp, "%s/MMTHM_XMB2.JPG", thmPath);
		imgLoadFromFile(temp, &XMB_MMTHM_XMB2);
	}

	if(XMB_MMTHM_XMB2.bmp_out) {
		memcpy(texture_pointer, XMB_MMTHM_XMB2.bmp_out, XMB_MMTHM_XMB2.pitch * XMB_MMTHM_XMB2.height);
		free(XMB_MMTHM_XMB2.bmp_out);
		XMB_MMTHM_XMB2_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((XMB_MMTHM_XMB2.pitch * XMB_MMTHM_XMB2.height + 15) & ~15) / 4;
	}
	
	prog_bar1_value = 75;

	sprintf(thmPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s",  ManaGunZ_id, UI[3], Themes[3]);
	
	Flow_BG_texture_mem = texture_pointer;
	
	texture_pointer = Flow_BG_texture_mem;
	
	sprintf(temp, "%s/BG.PNG", thmPath);

	if(imgLoadFromFile(temp, &Flow_BG) == FAILED) {
		sprintf(temp, "%s/BG.JPG", thmPath);
		imgLoadFromFile(temp, &Flow_BG);
	}
	
	if(Flow_BG.bmp_out) {
		memcpy(texture_pointer, Flow_BG.bmp_out, Flow_BG.pitch * Flow_BG.height);
		free(Flow_BG.bmp_out);
		Flow_BG_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((Flow_BG.pitch * Flow_BG.height + 15) & ~15) / 4;
	}
	
	Flow_BGS_texture_mem = texture_pointer;
	
	texture_pointer = Flow_BGS_texture_mem;
	
	sprintf(temp, "%s/BGS.PNG", thmPath);

	if(imgLoadFromFile(temp, &Flow_BGS) == FAILED) {
		sprintf(temp, "%s/BGS.JPG", thmPath);
		imgLoadFromFile(temp, &Flow_BGS);
	}
	
	if(Flow_BGS.bmp_out) {
		memcpy(texture_pointer, Flow_BGS.bmp_out, Flow_BGS.pitch * Flow_BGS.height);
		free(Flow_BGS.bmp_out);
		Flow_BGS_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((Flow_BGS.pitch * Flow_BGS.height + 15) & ~15) / 4;
	}
		
	prog_bar1_value=-1;
	
	ICON0_texture_mem = texture_pointer;
}

char *LoadFromISO(char *path, char *filename, int *size)
{
	FILE *f;
	f = fopen(path, "rb");	
	if(f==NULL) return NULL;
	
	u32 flba=0;
	u8 ret=0;
	int file_size=0;

	ret = get_FileOffset(f, filename, &flba, (u32 *) &file_size);

	if(flba==0 || file_size==0 || ret == FAILED) {fclose(f);	return NULL;}
	char *mem = malloc(file_size);
	if(mem == NULL) {fclose(f); return NULL;}
	
	fseek(f, 0x800*flba, SEEK_SET);
	
	prog_bar1_value=0;
	u64 read = 0;
	while(read < file_size) {
		u32 wrlen = 1024;
		if(read+wrlen > file_size) wrlen = (u32)file_size-read;
		fread(mem+read, sizeof(u8), wrlen, f);
		read += wrlen;
		prog_bar1_value = (read*100)/file_size;
	}
	fclose(f);
	
	prog_bar1_value=-1;
	
	*size= file_size;
	return mem;
}

int position_PIC1=-1;
void LOAD_PIC1()
{
	char *mem = NULL;
	int size=0;
	
	FM_PIC_offset=0;
	
	if( Show_PIC1 == NO ) return; 
	
	if( list_game_platform[position_PIC1] != _ISO_PS3 && list_game_platform[position_PIC1] != _ISO_PSP &&
		list_game_platform[position_PIC1] != _JB_PS3 ) return;
		
	if( list_game_platform[position_PIC1] == _ISO_PS3 ) {
		mem = LoadFromISO(list_game_path[position_PIC1], "/PS3_GAME/PIC1.PNG", &size);
	} else
	if( list_game_platform[position_PIC1] == _ISO_PSP ) {
		mem = LoadFromISO(list_game_path[position_PIC1], "/PSP_GAME/PIC1.PNG", &size);
	} else
	if( list_game_platform[position_PIC1] == _JB_PS3 ) {
		char temp[255];
		sprintf(temp, "%s/PS3_GAME/PIC1.PNG", list_game_path[position_PIC1]);
		mem = LoadFileProg(temp, &size);
		if(mem==NULL) return;
	}
	
	if(pngLoadFromBuffer(mem, size, (pngData *) &FM_PIC) != 0) {free(mem); return;}
	
	free(mem);
	
	u32 * texture_pointer;
	texture_pointer = FM_PIC_texture_mem;

	if(FM_PIC.bmp_out) {
		memcpy(texture_pointer, FM_PIC.bmp_out, FM_PIC.pitch * FM_PIC.height);
		free(FM_PIC.bmp_out);
		FM_PIC_offset = tiny3d_TextureOffset(texture_pointer);
		texture_pointer += ((FM_PIC.pitch * FM_PIC.height + 15) & ~15) / 4;
	}
	
}

void Draw_PIC1()
{
	
	if(Show_PIC1==NO && load_PIC1 == YES) { end_load_PIC1(); return; }
	
	if(Show_PIC1==YES && load_PIC1 == NO) { start_load_PIC1(); return; }
	
	if(Show_PIC1==NO) return;
	
	if(MENU==YES && MENU_SIDE == NO) return;
	
	if((UI_position==LIST || UI_position==GRID) && Display_PIC1 == NO) return;
	
	if(FM_PIC_offset != 0 ) {
		if( UI_position==XMB || UI_position==FLOW)
		{
			tiny3d_SetTexture(0, FM_PIC_offset, FM_PIC.width, FM_PIC.height, FM_PIC.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);	
			Draw_Box(0, 0, 99, 0, 848, 512, WHITE, YES);
		} else
		if( UI_position==LIST || UI_position==GRID) 
		{
			tiny3d_SetTexture(0, FM_PIC_offset, FM_PIC.width, FM_PIC.height, FM_PIC.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
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
			FM_PIC_offset = 0;
			position_PIC1=position;
			usleep(1000000);
			if(position_PIC1 == position) LOAD_PIC1();
		}
		else usleep(100000);
		if( Game_stuff == NO ) FM_PIC_offset=0;
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

void Draw_BG()
{
	if(MENU==YES && MENU_SIDE == NO) return;
	
	if(UI_position==LIST) {
		if(List_BG_offset != 0 ) {
			tiny3d_SetTexture(0, List_BG_offset, List_BG.width, List_BG.height, List_BG.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		} else return;
	}
	else if(UI_position==GRID) {
		if(GRID_BG_offset != 0 ) {
			tiny3d_SetTexture(0, GRID_BG_offset, GRID_BG.width, GRID_BG.height, GRID_BG.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		} else return;
	}
	else if(UI_position==XMB) {
		if(XMB_BG_offset[1] != 0 ) { // Animated
			Draw_XMB_BG();
		} else
		if(XMB_BG_offset[0] != 0 ) {
			tiny3d_SetTexture(0, XMB_BG_offset[0], XMB_BG[0].width, XMB_BG[0].height, XMB_BG[0].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		} else return;
	}
	else if(UI_position==FLOW) {
		if(Flow_BG_offset != 0 ) {
			tiny3d_SetTexture(0, Flow_BG_offset, Flow_BG.width, Flow_BG.height, Flow_BG.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		} else return;
	}

	Draw_Box(0, 0, 1000, 0, 848, 512, WHITE, YES);
	
}

void Draw_BGS()
{	
	if(UI_position==LIST) {
		if(List_BG_offset != 0 ) {
			tiny3d_SetTexture(0, List_BG_offset, List_BG.width, List_BG.height, List_BG.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		} else return;
	}
	else if(UI_position==GRID) {
		if(GRID_BGS_offset != 0 ) {
			tiny3d_SetTexture(0, GRID_BGS_offset, GRID_BGS.width, GRID_BGS.height, GRID_BGS.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		} else return;
	}
	else if(UI_position==XMB) {
		if(XMB_BGS_offset != 0 ) {
			tiny3d_SetTexture(0, XMB_BGS_offset, XMB_BGS.width, XMB_BGS.height, XMB_BGS.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		} else return;
	}
	else if(UI_position==FLOW) {
		if(Flow_BGS_offset != 0 ) {
			tiny3d_SetTexture(0, Flow_BGS_offset, Flow_BGS.width, Flow_BGS.height, Flow_BGS.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		} else return;
	}

	Draw_Box(0, 0, 1000, 0, 848, 512, WHITE, YES);
	
}

void Load_COMMON()
{
	u32 * texture_pointer;
	char temp[128];
	int i;
	texture_pointer = COMMON_texture_mem;
	
	char *COMMON_FILE[31] = {"ALL" , 
							"UP" , "LEFT" , "DOWN" , "RIGHT" , 
							"SELECT" , "START" , 
							"SQUARE" , "CROSS" , "CIRCLE" , "TRIANGLE", 
							"NOT", 
							"L1", "L2", "L3", "L", 
							"R1", "R2", "R3", "R",
							"DEFAULT", "DEFAULT_ISO", "DEFAULT_JB",
							"PS1_DISC", "PS2_DISC", "PS3_DISC", "PSP_DISC",
							"PS1_STR", "PS2_STR", "PS3_STR", "PSP_STR"
							};
	
	for(i=0; i<31; i++) {
		sprintf(temp, "/dev_hdd0/game/%s/USRDIR/GUI/common/%s.PNG", ManaGunZ_id, COMMON_FILE[i]);
		
		if(imgLoadFromFile(temp, &COMMON[i]) == FAILED) {
			sprintf(temp, "/dev_hdd0/game/%s/USRDIR/GUI/common/%s.PNG", ManaGunZ_id, COMMON_FILE[i]);
			imgLoadFromFile(temp, &COMMON[i]);
		}
		
		if(COMMON[i].bmp_out) {
			memcpy(texture_pointer, COMMON[i].bmp_out, COMMON[i].pitch * COMMON[i].height);
			free(COMMON[i].bmp_out);
			COMMON_offset[i] = tiny3d_TextureOffset(texture_pointer);
			texture_pointer += ((COMMON[i].pitch * COMMON[i].height + 15) & ~15) / 4;
		} else COMMON_offset[i]=0;
	}
	
	List_BG_texture_mem = texture_pointer;
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

int Draw_DISK(float x, float y, float z, float d, u32 color)
{
	x+=d/2;
	y+=d/2;
	int t;
	float PI = 3.14159265;
	
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
	
	return x + d/2;
}

int Draw_USB(float x, float y, float font_size, u32 rgba ,int nb)
{
	
	y+=font_size/2;
	
	float s=font_size/4;
	
	float e=font_size/24;
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x + 2*s - e, y - s, 10);
	tiny3d_VertexPos( x + 2*s - e, y + 2*e - s, 10);
	tiny3d_VertexPos( x + 3*s, y + 2*e - s, 10);
	tiny3d_VertexPos( x + 3*s, y - s, 10);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x + 3*s - e, y + s, 10);
	tiny3d_VertexPos( x + 3*s - e, y + s - 2*e, 10);
	tiny3d_VertexPos( x + 4*s, y + s - 2*e, 10);
	tiny3d_VertexPos( x + 4*s, y + s, 10);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x + s - e*1.5 , y  , 10);
	tiny3d_VertexPos( x + s + e , y  , 10);
	tiny3d_VertexPos( x + 2*s + e , y - s , 10);
	tiny3d_VertexPos( x + 2*s - e , y - s , 10);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x + 2*s - e*1.5, y  , 10);
	tiny3d_VertexPos( x + 2*s + e, y  , 10);
	tiny3d_VertexPos( x + 3*s + e, y + s , 10);
	tiny3d_VertexPos( x + 3*s - e, y + s , 10);
	tiny3d_End();
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(rgba);
	tiny3d_VertexPos( x , y - e, 10);
	tiny3d_VertexPos( x , y + e, 10);
	tiny3d_VertexPos( x + 5*s, y + e, 10);
	tiny3d_VertexPos( x + 5*s , y - e, 10);
	tiny3d_End();
	
	SetFontSize(font_size/2, font_size/2);
	SetFontColor(COLOR_1, 0x0);
	DrawFormatString(x+3.5*s, y-font_size/2, "%d", nb);
	SetFontSize(font_size, font_size);
	
	return x + 5*s;
}

void Draw_Button(float x, float y, float d)
{
	x+=d/2;
	y+=d/2;
	int t;
	float PI = 3.14159265;
	
	tiny3d_SetPolygon(TINY3D_POLYGON);
	tiny3d_VertexColor(0x3F3F41ff);
	for(t=0; t<=360 ; t+=10) {
		tiny3d_VertexPos( x + d/1.9*sin(t*PI/180), y + d/1.9*cos(t*PI/180), 0);
	}
	tiny3d_End();
	
}

int Draw_Button_Circle(float x, float y, float size)
{
	if(COMMON_offset[9] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[9], COMMON[9].width, COMMON[9].height, COMMON[9].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, y, 0, 0, size, size, WHITE, YES);

		return x+size;
	}
	else {
		Draw_Button(x, y, size);
		
		x+=size/2;
		y+=size/2;
		int t;
		float PI = 3.14159265;
		
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
	if(COMMON_offset[7] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[7], COMMON[7].width, COMMON[7].height, COMMON[7].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
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
	if(COMMON_offset[10] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[10], COMMON[10].width, COMMON[10].height, COMMON[10].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
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

	if(COMMON_offset[8] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[8], COMMON[8].width, COMMON[8].height, COMMON[8].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
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
	if(COMMON_offset[6] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[6], COMMON[6].width, COMMON[6].height, COMMON[6].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
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

	if(COMMON_offset[5] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[5], COMMON[5].width, COMMON[5].height, COMMON[5].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		Draw_Box(x, y, 0, 0, size, size, WHITE, YES);
		
	} else {
		Draw_Box(x, y+size/3, 0, 2, size, size/3, 0x3F3F41ff, NO);
	}
	
	return x+size;
}

float Draw_Button_L1(float x, float y, float z, float size)
{
	if(COMMON_offset[12] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[12], COMMON[12].width, COMMON[12].height, COMMON[12].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "L1");
}

float Draw_Button_L2(float x, float y, float z, float size)
{
	if(COMMON_offset[13] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[13], COMMON[13].width, COMMON[13].height, COMMON[13].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "L2");
}

float Draw_Button_L3(float x, float y, float z, float size)
{
	if(COMMON_offset[14] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[14], COMMON[14].width, COMMON[14].height, COMMON[14].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "L3");
}

float Draw_Button_L(float x, float y, float z, float size)
{
	if(COMMON_offset[15] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[15], COMMON[15].width, COMMON[15].height, COMMON[15].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "L");
}

float Draw_Button_R2(float x, float y, float z, float size)
{
	if(COMMON_offset[16] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[16], COMMON[16].width, COMMON[16].height, COMMON[16].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "R1");
}

float Draw_Button_R1(float x, float y, float z, float size)
{
	if(COMMON_offset[17] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[17], COMMON[17].width, COMMON[17].height, COMMON[17].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "R2");
}

float Draw_Button_R3(float x, float y, float z, float size)
{
	if(COMMON_offset[18] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[18], COMMON[18].width, COMMON[18].height, COMMON[18].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "R3");
}

float Draw_Button_R(float x, float y, float z, float size)
{
	if(COMMON_offset[19] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[19], COMMON[19].width, COMMON[19].height, COMMON[19].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		Draw_Box(x, y, z, 0, size, size, WHITE, YES);
		return x+size;
	} else	return DrawString(x, y, "R");
}

float Draw_Pad(int button, float x, float y, float z,  float size) {

	if(COMMON_offset[0] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[0], COMMON[0].width, COMMON[0].height, COMMON[0].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
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
	
	if(button == BUTTON_UP || button == (BUTTON_UP | BUTTON_DOWN)) {
		if(COMMON_offset[1] != 0) {
			tiny3d_SetTexture(0, COMMON_offset[1], COMMON[1].width, COMMON[1].height, COMMON[1].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
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
	if(button == BUTTON_LEFT || button == (BUTTON_LEFT | BUTTON_RIGHT)) {
		if(COMMON_offset[2] != 0) {
			tiny3d_SetTexture(0, COMMON_offset[2], COMMON[2].width, COMMON[2].height, COMMON[2].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
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
	if(button == BUTTON_DOWN || button == (BUTTON_UP | BUTTON_DOWN)) {
		if(COMMON_offset[3] != 0) {
			tiny3d_SetTexture(0, COMMON_offset[3], COMMON[3].width, COMMON[3].height, COMMON[3].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
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
	if(button==BUTTON_RIGHT || button == (BUTTON_LEFT | BUTTON_RIGHT)) {
		if(COMMON_offset[4] != 0) {
			tiny3d_SetTexture(0, COMMON_offset[4], COMMON[4].width, COMMON[4].height, COMMON[4].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			
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
	if(button == BUTTON_CROSS) x=Draw_Button_Cross(x, y, 15); else
	if(button == BUTTON_SQUARE) x=Draw_Button_Square(x, y, 15); else
	if(button == BUTTON_TRIANGLE) x=Draw_Button_Triangle(x, y, 15); else
	if(button == BUTTON_CIRCLE) x=Draw_Button_Circle(x, y, 15); else
	if(button == BUTTON_SELECT) x=Draw_Button_Select(x, y, 15); else
	if(button == BUTTON_START) x=Draw_Button_Start(x, y, 15); else
	if(button == BUTTON_L1) x=Draw_Button_L1(x, y, 0, 15); else
	if(button == BUTTON_L2) x=Draw_Button_L2(x, y, 0, 15); else
	if(button == BUTTON_L3) x=Draw_Button_L3(x, y, 0, 15); else
	if(button == BUTTON_L ) x=Draw_Button_L (x, y, 0, 15); else
	if(button == BUTTON_R1) x=Draw_Button_R1(x, y, 0, 15); else
	if(button == BUTTON_R2) x=Draw_Button_R2(x, y, 0, 15); else
	if(button == BUTTON_R3) x=Draw_Button_R3(x, y, 0, 15); else
	if(button == BUTTON_R ) x=Draw_Button_R (x, y, 0, 15); else
	x=Draw_Pad(button,  x, y, 0, 15);
	
	x=DrawString(x+5, y, str);
	
	return x+10;
}

float new_line(float nb)
{
	//return GetFontY() + GetFontHeight()*nb;
	return GetFontHeight()*nb;
}

float GetWidth(char *str)
{
	return DrawString(0, -50, str);
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

u32 SetRED(u8 red, u32 rgba){
	return rgba - GetRED(rgba) * 0x1000000 + red*0x1000000;
}

u32 SetGREEN(u8 green, u32 rgba){
	return rgba - GetGREEN(rgba) * 0x10000 + green*0x10000;
}

u32 SetBLUE(u8 blue, u32 rgba){
	return rgba - GetBLUE(rgba) * 0x100 + blue*0x100;
}

void Draw_NOT(float x, float y, float z, float w, float h)
{	
	if(COMMON_offset[11] != 0) {
		tiny3d_SetTexture(0, COMMON_offset[11], COMMON[11].width, COMMON[11].height, COMMON[11].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		tiny3d_SetPolygon(TINY3D_QUADS);
		tiny3d_VertexPos(x, y, z);
		tiny3d_VertexColor(0xFFFFFFFF);
		tiny3d_VertexTexture(0.0f, 0.0f);
		tiny3d_VertexPos(x + w, y, z);
		tiny3d_VertexTexture(1.0f, 0.0f);
		tiny3d_VertexPos(x + w, y + h, z);
		tiny3d_VertexTexture(1.0f, 1.0f);
		tiny3d_VertexPos(x, y+h, z);
		tiny3d_VertexTexture(0.0f, 1.0f);
		tiny3d_End();
	}
}

void Draw_SIDEBAR(float x)
{
	Draw_Box(0, 0, 0, 0, 848, 512, 0x000000B0, NO);
	if(XMB_SIDEBAR_offset != 0) {
		tiny3d_SetTexture(0, XMB_SIDEBAR_offset, XMB_SIDEBAR.width, XMB_SIDEBAR.height, XMB_SIDEBAR.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		tiny3d_SetPolygon(TINY3D_QUADS);
		tiny3d_VertexPos(x, 0, 0);
		tiny3d_VertexColor(0xFFFFFFFF);
		tiny3d_VertexTexture(0.0f, 0.0f);
		tiny3d_VertexPos(x + 310, 0, 0);
		tiny3d_VertexTexture(1.0f, 0.0f);
		tiny3d_VertexPos(x + 310, 512, 0);
		tiny3d_VertexTexture(1.0f, 1.0f);
		tiny3d_VertexPos(x, 512, 0);
		tiny3d_VertexTexture(0.0f, 1.0f);
		tiny3d_End();
	} else {
		Draw_Box(x, 0, 0, 0, 310, 512, 0xFFFFFF30, NO);
		Draw_Box(x, 0, 0, 0, 1, 512, 0xFFFFFFFF, NO);
	}
	
	if(UI_position==XMB) {
		Draw_ICON0(position, 250-XMB_w-XMB_w , 200-XMB_h, 0, XMB_w*4, XMB_h*4);
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

void Draw_Notification()
{
	if(not_msg[0] == 0)	return;
	time_not++;
	if(time_not > 200+strlen(not_msg)*2) { time_not=0; not_msg[0]=0; return ;}
	
	SetFontZ(0);
	SetFontColor(WHITE, 0);
	int size = 14, x=635, h=50;
	int x1 = x;
	SetFontSize(size, size);
	
	Draw_Box(590, 40, 0, 3, 213, h, 0x555555FF, NO);
	
	char *splited_msg;
	x1=DrawFormatString(x, -50, "%s", not_msg);
	if(x1 < 810) DrawFormatString( x, 58, "%s", not_msg); else
	if(strstr(not_msg, " ") == NULL) DrawFormatString( x, 58, "%s", not_msg);
	else {
		int y = 51;
		char temp[255];
		strcpy(temp, not_msg);
		splited_msg = strtok (temp," ");
		x1=635;
		while (splited_msg != NULL) {
			x1=DrawFormatString( x1, -50, "%s ", splited_msg);
			if(strcmp(splited_msg, "/;/") == 0) { // new line
				x=635;
				y+=size;
				if(y > 51 + size)  { Draw_Box(590, 40+h-3, 0, 3, 213, size+3, 0x555555FF, NO); h+=size; }
				x1=x;
			} else if(x1 < 810) {
				x=DrawFormatString( x, y, "%s ", splited_msg);
			} else {
				x=635;
				y+=size;
				if(y > 51 + size) { Draw_Box(590, 40+h-3, 0, 3, 213, size+3, 0x555555FF, NO); h+=size;  }
				x=DrawFormatString( x, y, "%s ", splited_msg);
				x1=x;
			}
			splited_msg = strtok (NULL, " ");
		}
	}
	
	Draw_NOT(600, 50, 0, 30, 30);
	
	SetFontZ(10);
	SetFontColor(COLOR_1, 0);
}

void show_msg(char *str)
{
	strcpy(not_msg, str);
}

char *get_unit(u64 nb);

static sys_ppu_thread_t loading_id;

void Draw_Loading(void *unused)
{
	int i=0;
	int show_log=YES;
	int direction = 1;
	int h=20, v=70;
	int speed = 3;
	int boost=100;
	cancel=NO;
	
	while(loading) {
		cls();
		
		Draw_BGS();
		int x=50, y=40;
		SetFontAutoCenter(0);
		SetFontSize(20, 20);
		SetFontColor(COLOR_1, 0x0);
		
		if(head_title[0] != 0) {
			SetFontColor(COLOR_2, 0x0);
			DrawString(x, y, head_title);
			SetFontColor(COLOR_1, 0x0);
			y+=20;
		}
		if(prog_bar1_value >= 0) {
			Draw_Progress_Bar(x, y, 2, prog_bar1_value, COLOR_2);
			y+=15;
			if(prog_bar2_value >= 0) Draw_Progress_Bar(x, y, 2, prog_bar2_value, COLOR_2);
			y+=25;
		}
		
		if(gathering==YES){
			DrawString(x, y, "Gathering data...");
			y+=20;
			DrawFormatString(x, y, "Nb of file = %i", nb_file);
			y+=20;
			DrawFormatString(x, y, "Nb of Dir. = %i", nb_directory);
			y+=20;
			char *size_tot = get_unit(total_size);
			DrawFormatString(x, y,"Total size = %s", size_tot);
			y+=20;
		}
		
		if(show_log) {
			for(i=0; i<=20; i++){
			
				if(strstr(loading_log[i], "Error")) SetFontColor(RED, 0x0);
				else if(strstr(loading_log[i], "Warning")) SetFontColor(ORANGE, 0x0);
				else SetFontColor(COLOR_1, 0x0);
				
				DrawString(x , y, loading_log[i]);
				y+=20;
				if(y>450) break;
			}
		}
	
		int t;
		float PI = 3.14159265;
		switch(direction){
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
				
				if(h>= 820) direction = 2; else h+=speed;
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
						
				if(h < 20) direction = 1; else h-=speed;
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
			
				if(v < 20) direction = 4; else v-=speed;
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
				
				if(v > 490) direction = 3; else v+=speed;
			}
			break;
			default: //droite
			{
				direction = 1;
			}
		}
		
		if(speed==9) rumble2_on=1; else rumble2_on=0;
		u32 color;
		if(boost<30) {
			color = RED;
		} else
		if(boost==100) {
			color = BLUE;
		} else
		if(boost<100) {
			color = GREEN;
		}
		
		
		// *** DISPLAY BUTTONS ***
		x=25; y=485;
		SetFontSize(15, 15);
		SetFontColor(COLOR_1, 0x0);
		
		if(show_log)	x=DrawButton(x, y, "Hide logs", BUTTON_SELECT);
		else x=DrawButton(x, y, "Show logs", BUTTON_SELECT);
		
		x=Draw_Button_Square(x, y, 15);
		x=Draw_Progress_Bar(x+5, y+4, 1, boost, color);
		x=DrawString( x+5, y, "Boost!  ");
		
		if(AutoM == YES) {
			x=DrawButton(x, y, "Game menu", BUTTON_TRIANGLE);
		}
		if(prog_bar1_value >= 0) {
			x=DrawButton(x, y, "Cancel", BUTTON_CIRCLE);
		}
		if(gathering==YES) {
			x=DrawButton(x, y, "Cancel Gathering", BUTTON_CIRCLE);
		}
		tiny3d_Flip();
		
		ps3pad_read();
		if(new_pad & BUTTON_RIGHT) {
			direction = 1;
		}
		if(new_pad & BUTTON_LEFT) {
			direction = 2;
		}
		if(new_pad & BUTTON_UP) {
			direction = 3;
		}
		if(new_pad & BUTTON_DOWN) {
			direction = 4;
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
	cancel = NO;
	
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
	
	int i=0;
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

void Draw_Col_header(int x)
{
	int y = 165;
	float y_top;
	
	float w;
	float h;
	
	float BIG = 65;
	float SMALL = 50;
	
	/*
	XMB original look like something like
		...
		-5  x=250-95-90-85-80-75
		-4  x=250-95-90-85-80
		-3  x=250-95-90-85
		-2  x=250-95-90
		-1  x=250-95
		0   x=250
		1   x=250+95
		2   x=250+95+90
		3   x=250+95+90+85
		4   x=250+95+90+85+80
		5   x=250+95+90+85+80+75
		6   x=250+95+90+85+80+75+70
		...
	*/	
	
	int i;
	
	SetFontZ(90);
	if(Themes[UI_position][0] == 0) {
		
		for(i=0; i<6;i++) {
			if(x==250) {SetFontSize(30,30);	y_top = y-30;}
			else {SetFontSize(20,20); 	y_top = y-20;}
			DrawStringFromCenterX(x, y_top, Columns[i]);
			x+=90;
		}
		
		SetFontSize(20,20);
		SetFontZ(10);
		return;
	}
	
	for(i=0; i<6 ; i++) {
		w=h=SMALL;
		if(XMB_Col_offset[i] != 0) {
			if( x==250) {
				w=h=BIG;
				SetFontSize(15,15);
				DrawStringFromCenterX(x, y, Columns[i]);
			}
			tiny3d_SetTexture(0, XMB_Col_offset[i], XMB_Col[i].width, XMB_Col[i].height, XMB_Col[i].pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
			Draw_Box(x-w/2, y-h, 90, 0, w, h, WHITE, YES);
		} 
		else if(XMB_MMTHM_XMB_offset != 0 && XMB_MMTHM_XMB2_offset != 0) { 
			if( x==250) {
				w=h=BIG;
				SetFontSize(15,15);
				DrawStringFromCenterX(x, y, Columns[i]);
			}
			u8 ico=6;
			if(i==0) ico=2 ;else
			if(i==1) ico=12;else
			if(i==2) ico=6 ;else
			if(i==3) ico=29;else
			if(i==4) ico=28;else
			if(i==5) ico=30;
			Draw_MMTHM_XMB(x-w/2 , y-h, 90, w, h,  ico);
		}
		else { 
			if(x==250) {
				SetFontSize(30,30);
				DrawStringFromCenterX(x, y-30, Columns[i]);
			}
			else {
				SetFontSize(20,20);
				DrawStringFromCenterX(x, y-20, Columns[i]);
			}
		}
		x+=90;
	}

	SetFontSize(20,20);
	SetFontZ(10);
	
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

	} else	{return NOK;}
	
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
		struct zip_file *file_zip=NULL;
		
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
		u64 readed = 0, writed = 0;
		FILE *f;
		
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
			
			readed = file_stat.size - pos; if(readed > mem_size) readed = mem_size;
			
			writed = zip_fread(file_zip, mem, (size_t) readed);
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
			
			if(readed != writed) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			writed = fwrite(mem, 1, readed, f);
			if(writed<0) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			if(readed != writed) {
				zip_fclose(file_zip);
				zip_close(f_zip);
				fclose(f);
				free(mem);
				return FAILED;
			}
			
			pos += readed;
			
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
	struct zip_file *file_zip=NULL;
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
}

void get_hash(FILE *log, int hash_type, char *path)
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
	
	char temp[128];
	char game_path[128];
	
	if(path != NULL) {
		strcpy(game_path, path);
	} else strcpy(game_path, list_game_path[position]);
	
	print_load("Deleting %s", game_path);

	if(iso) {
	
		strtok(game_path,".");
		
		sprintf(temp , "%s.PNG" , game_path);
		Delete(temp);
		sprintf(temp, "%s.png" , game_path);
		Delete(temp);
		sprintf(temp , "%s.SFO" , game_path);
		Delete(temp);
		sprintf(temp, "%s.sfo" , game_path);
		Delete(temp);
	
		for(i=0; i<30; i++) {
			sprintf(temp , "%s.iso.%d" , game_path, i);
			Delete(temp);
			sprintf(temp, "%s.ISO.%d" , game_path, i);
			Delete(temp);
		}
		sprintf(temp , "%s.iso" , game_path);
		Delete(temp);
		sprintf(temp , "%s.ISO" , game_path);
		Delete(temp);
	} else {
		Delete(game_path);
	}
	
	if(path != NULL) {
		if(path_info(path) != _NOT_EXIST) return FAILED; else
		return SUCCESS;
	} else
	if(path_info(list_game_path[position]) != _NOT_EXIST ) return FAILED;


	print_load("Removing game from list");
	char setPath[128];
	if(iso) sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[ISO]%s.bin", ManaGunZ_id, list_game_title[position]);
	else	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[JB]%s.bin" , ManaGunZ_id, list_game_title[position]);
	Delete(setPath);
	
	for(i=position; i <= game_number; i++) {
		strcpy(list_game_path[i] , list_game_path[i+1]);
		strcpy(list_game_title[i], list_game_title[i+1]);
	}
	strcpy(list_game_path[game_number] , "");
	strcpy(list_game_title[game_number], "");
	game_number--;

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
	
	if(iso) {
		char iso_path[128];
		char temp[128];
		int i;
		
		strcpy(iso_path, path);
		
		strtok(iso_path,".");
		
		if(strstr(path, ".iso.0") != NULL) {
			for(i=0; i<30; i++) {
				sprintf(temp , "%s.iso.%d" , iso_path, i);
				get_size(temp, YES);
			}
		}
		else if(strstr(path, ".ISO.0") != NULL) {
			for(i=0; i<30; i++) {
				sprintf(temp , "%s.ISO.%d" , iso_path, i);
				get_size(temp, YES);
			}
		}
		else {
			get_size(path, YES);
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
		strcpy(unit, " Gb");
	}
	else
	if(nb >= 1048576) {
		size = (float) nb / 1048576;
		strcpy(unit, " Mb");
	}
	else
	if(nb >= 1024) {
		size = (float) nb / 1024;
		strcpy(unit, " Kb");
	} 
	else {
		size = (float) nb;
		strcpy(unit, "  b");
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
	
	while(copy_flag) {
		
		cls();
		ps3pad_read();
		
		Draw_BGS();
		Draw_Notification();
		int x=50, y=40;
		SetFontAutoCenter(0);
		SetFontSize(20, 20);
		
		SetFontColor(COLOR_4, 0x0);
		
		if(gathering==YES) {
			DrawString(x , y, "Gathering data...");
		} else DrawString(x , y, "Copying...");
		
		SetFontColor(COLOR_1, 0x0);
		
		y+=new_line(1);
		
		DrawString(x , y, "from :");
		DrawString(120, y, copy_src);
		
		y+=new_line(1);
		
		DrawString(x , y, "to :");
		DrawString(120, y, copy_dst);
		
		y+=new_line(1);
		
		if(gathering_cancel==YES) {
			DrawString(x , y, "Nb of file : Unknown");
		} else
		DrawFormatString(x , y, "Nb of file : %d", nb_file);
		
		y+=new_line(1);
		
		if(iso==YES) {
			if(gathering_cancel==YES) {
				DrawString(x , y, "Nb of directory : Unknown");
			} else
			DrawFormatString(x , y, "Nb of directory : %d", nb_directory);
			
			y+=new_line(1);
		}
		
		char *size_current = get_unit(copy_current_size);
		
		DrawString(x, y, size_current);
		
		if(gathering_cancel==YES) DrawString(x+400-GetWidth("Unknown"), y, "Unknown"); 
		else {
			char *size_tot = get_unit(total_size);
			DrawString(x+400-GetWidth(size_tot), y, size_tot);
		}
		
		y+=new_line(1);
		
		float val;
		if(gathering_cancel==YES) val = 100; else 
		val = copy_current_size * 100 / total_size;
		
		Draw_Progress_Bar(x, y, 4, val, COLOR_2);
		
		y+=15;
		Draw_Progress_Bar(x, y, 4, file_copy_prog_bar, COLOR_2);
	
		y+=20;
		
		DrawFormatString(x, y, "File : %s", copy_file);
		
		y+=new_line(2);
	
		SetFontSize(17, 17);
		
		for(i=0; i<10; i++) {
			DrawString(x, y, copy_log[i]);
			y+=new_line(1);
		}
	
		SetFontColor(COLOR_1, 0x0);
		SetFontSize(15, 15);
		x=30;
		
		x=Draw_Button_Circle(x, 485, 15);
		x=DrawString( x+5, 485, "Cancel");
		
		x=Draw_Button_Select(x+5, 485, 15);
		if(shutdown==YES) {
			x=DrawString( x+5, 485, "Turn OFF = YES");
		} else x=DrawString( x+5, 485, "Turn OFF = NO");
		
		if(new_pad & BUTTON_SELECT) {
			if(shutdown==YES) shutdown=NO; else shutdown=YES;
		}
		if(new_pad & BUTTON_CIRCLE) {
			if(gathering==YES) {
				gathering_cancel=YES;
				show_msg("Gathering data cancelled");
			} else 	copy_cancel = YES;
		}
		
		tiny3d_Flip();
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

u8 CopyFile(char* src, char* dst)
{
	u8 ret = SUCCESS;
	u64 lenght = 0LL;
	char *mem = NULL;
	u64 pos = 0ULL;
	u64 readed = 0, writed = 0;
	
	FILE *f;
	FILE *f2;
	
	file_copy_prog_bar=0;

	if(path_info(src) != _FILE) return FAILED;

	lenght = get_size(src, NO);
	
	f = fopen(src, "rb");
	if(f==NULL) {ret = FAILED; goto skip;}
	
	f2 = fopen(dst, "wb");
	if(f2==NULL) {ret = FAILED; goto skip;}
	
	if( is_ntfs(dst) == NO ) sysLv2FsChmod(dst, 0777);
	
	mem = malloc(0x10000);
	
	while(pos < lenght) {
		
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		readed = lenght - pos; if(readed > 0x10000ULL) readed = 0x10000ULL;
		
		writed = fread(mem, 1, readed, f);
		if(writed<0) {ret = FAILED; goto skip;}
		
		if(copy_cancel==YES) {ret = FAILED; goto skip;}
		
		if(readed != writed) {ret = FAILED; goto skip;}
		
		writed =fwrite(mem, 1, readed, f2);
		if(writed<0) {ret = FAILED; goto skip;}
		
		if(readed != writed) {ret = FAILED; goto skip;}
		
		pos += readed;
		
		file_copy_prog_bar=pos*100/lenght;
		
		copy_current_size+=readed;
	
	}
	
skip:
	
	file_copy_prog_bar=0;
	
	if(mem) free(mem);
	if(f) fclose(f);
	if(f2) fclose(f2);
	
	return ret;
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

u8 RefreshList()
{
	int min; 
	char ta[128], tb[128];
	u8 t;
	int i, j;
	for (i = 0; i<game_number; i++) { 
		min = i;
		for (j = i+1; j <= game_number; j++) { 
			strcpy(ta , list_game_title[j]);
			strcpy(tb, list_game_title[min]);
			if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
			if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
			if (strcmp(ta, tb) < 0) { 
				min = j; 
			} 
		}
		if(min==i) continue;
		strcpy(ta , list_game_title[min]);
		strcpy(list_game_title[min], list_game_title[i]); 
		strcpy(list_game_title[i], ta); 
		strcpy(tb, list_game_path[min]);
		strcpy(list_game_path[min], list_game_path[i]); 
		strcpy(list_game_path[i], tb);
		t = list_game_platform[min];
		list_game_platform[min] = list_game_platform[i];
		list_game_platform[i] = t;
	}
	
	//Extract_IconParam();
	
	read_fav();
	start_Load_GamePIC();
	
	return SUCCESS;
}

u8 AddGame(char *path)
{
	if(path_info(path) == _NOT_EXIST) return FAILED;
	
	game_number++;
	strcpy(list_game_path[game_number], path);

	strcpy(list_game_title[game_number], list_game_path[game_number]);
	strcpy(list_game_title[game_number], &strrchr(list_game_title[game_number], '/')[1]);
	strtok(list_game_title[game_number], ".");
	
	u8 ext = get_ext(list_game_path[game_number]);
	
	list_game_platform[game_number] = ext;
	
	if(ext == _ISO_PS3 || ext == _JB_PS3 || ext == _ISO_PSP || ext == _JB_PSP) {
		GetParamSFO("TITLE", list_game_title[game_number], game_number, NULL);
	}
	
	RefreshList();
	
	return SUCCESS;
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
	
	if(iso==NO) {
		Copy(copy_src, copy_dst);
	}
	else {
		char temp_src[128];
		char temp_dst[128];
		char temp_src1[128];
		char temp_dst1[128];
		int i;

		u8 ret;
		
		strcpy(temp_src1, copy_src);
		strcpy(temp_dst1, copy_dst);
		
		strtok(temp_src1,".");
		strtok(temp_dst1,".");
		
		if(strstr(copy_src, ".iso.0") != NULL ) {
			for(i=0; i<32; i++) {
				if(copy_cancel==YES) goto cancel;
				sprintf(temp_src , "%s.iso.%d", temp_src1, i);
				sprintf(temp_dst , "%s.iso.%d", temp_dst1, i);
				ret = Copy(temp_src, temp_dst);
				if(ret==FAILED) break;
			}
		} else
		if(strstr(copy_src, ".ISO.0") != NULL ) {
			for(i=0; i<32; i++) {
				if(copy_cancel==YES) goto cancel;
				sprintf(temp_src , "%s.ISO.%d", temp_src1, i);
				sprintf(temp_dst , "%s.ISO.%d", temp_dst1, i);
				ret = Copy(temp_src, temp_dst);
				if(ret==FAILED) break;
			}
		} else 
		if(strstr(copy_src, ".iso") != NULL ) {
			if(copy_cancel==YES) goto cancel;
			sprintf(temp_src , "%s.iso", temp_src1);
			sprintf(temp_dst , "%s.iso", temp_dst1);
			ret = Copy(temp_src, temp_dst);
		} else 
		if(strstr(copy_src, ".ISO") != NULL ) {
			if(copy_cancel==YES) goto cancel;
			sprintf(temp_src , "%s.ISO", temp_src1);
			sprintf(temp_dst , "%s.ISO", temp_dst1);
			ret = Copy(temp_src, temp_dst);
		}
		
	}

cancel:
	
	if( (total_size <= copy_current_size && copy_current_size != 0) ||	(gathering_cancel == YES && copy_cancel==NO && copy_current_size > 0) ) {
	
		AddGame(copy_dst);
		
		show_msg("Game Copied !");
	} else {
		Delete_Game(copy_dst, -1);
		
		if(copy_cancel==YES) show_msg("Copy cancelled !"); else 
		show_msg("Copy Failed !");
	}
	
	end_copy_loading();

}

void Draw_GameProperties()
{
	
	char *tot_size = get_unit(total_size);
	char sys_vers[8];
	if(list_game_platform[position] == _JB_PS3 || list_game_platform[position] == _ISO_PS3) {
		if(GetParamSFO("PS3_SYSTEM_VER", sys_vers, position, NULL)==FAILED) strcpy(sys_vers, "Unk");
	}
	
	char Game_id[20];
	if(Get_ID(list_game_path[position], list_game_platform[position], Game_id) == FAILED) {
		strcpy(Game_id, "Unk");
	}
	
	char platform[30];
	if(list_game_platform[position] == _JB_PS3 || list_game_platform[position] == _ISO_PS3) {
		strcpy(platform, "PlayStation 3");
	} else
	if(list_game_platform[position] == _JB_PS2 || list_game_platform[position] == _ISO_PS2) {
		strcpy(platform, "PlayStation 2");
	} else
	if(list_game_platform[position] == _JB_PS1 || list_game_platform[position] == _ISO_PS1) {
		strcpy(platform, "PlayStation");
	} else
	if(list_game_platform[position] == _JB_PSP || list_game_platform[position] == _ISO_PSP) {
		strcpy(platform, "PlayStation Portable");
	} else strcpy(platform, "Unk");
	
	char PS2_CRC[10];
	if(list_game_platform[position] == _ISO_PS2) {
		sprintf(PS2_CRC, "%08lX", (long unsigned int) Get_CRC(Game_id));
	}
	
	while(1) {
		
		cls();
		
		Draw_BGS();
		Draw_ICON0(position, 630, 30, 100, 141.3, 75.9);
		
		int x1=50, y=40;
		int xt;
		SetFontAutoCenter(0);
		
		Draw_Box(x1+5, y+4, 0, 0, 8, 8, COLOR_3, NO);
		SetFontColor(COLOR_3, 0x0);
		SetFontSize(18, 18);
		xt=DrawString(x1+20, y, "Game Properties");
		y+=new_line(1);
		Draw_Box(x1, y, 0, 0, xt-x1, 2, COLOR_3, NO);

		y+=new_line(2);
		
		SetFontColor(COLOR_3, 0x0);
		xt=DrawString(x1 , y, "Game :");
		SetFontColor(COLOR_1, 0x0);
		DrawString(xt+10 , y,  list_game_title[position]);
		
		y+=new_line(1);
		
		SetFontColor(COLOR_3, 0x0);
		xt=DrawString(x1 , y, "Game path :");
		SetFontColor(COLOR_1, 0x0);
		DrawString(xt+10 , y,  list_game_path[position]);
		
		y+=new_line(1);
		
		SetFontColor(COLOR_3, 0x0);
		xt=DrawString(x1 , y, "Game format :");
		SetFontColor(COLOR_1, 0x0);
		if(iso==YES) {
			DrawString(xt+10 , y,  "ISO");
		} else DrawString(xt+10 , y,  "JB (folder)");
		
		y+=new_line(1);
		
		SetFontColor(COLOR_3, 0x0);
		xt=DrawString(x1 , y, "Game size :");
		SetFontColor(COLOR_1, 0x0);
		DrawString(xt+10 , y, tot_size);
		
		y+=new_line(1);
		
		SetFontColor(COLOR_3, 0x0);
		xt=DrawString(x1 , y, "File :");
		SetFontColor(COLOR_1, 0x0);
		DrawFormatString(xt+10 , y,  "%d", nb_file);
		
		y+=new_line(1);
		
		if(iso==NO) {
			SetFontColor(COLOR_3, 0x0);
			xt=DrawString(x1 , y, "Directory :");
			SetFontColor(COLOR_1, 0x0);
			DrawFormatString(xt+10 , y,  "%d", nb_directory);
			
			y+=new_line(1);
		}
		
		
		if(list_game_platform[position] == _JB_PS3 || list_game_platform[position] == _ISO_PS3) {
			SetFontColor(COLOR_3, 0x0);
			xt=DrawString(x1 , y, "System version :");
			SetFontColor(COLOR_1, 0x0);
			DrawString(xt+10 , y, sys_vers);
			
			y+=new_line(1);
		}
		
		SetFontColor(COLOR_3, 0x0);
		xt=DrawString(x1 , y, "Game ID :");
		SetFontColor(COLOR_1, 0x0);
		DrawString(xt+10 , y, Game_id);
		
		y+=new_line(1);
		
		if(list_game_platform[position] == _ISO_PS2) {
			SetFontColor(COLOR_3, 0x0);
			xt=DrawString(x1 , y, "ELF CRC :");
			SetFontColor(COLOR_1, 0x0);
			DrawString(xt+10 , y,  PS2_CRC);
			
			y+=new_line(1);
		}
		
		x1=30;
		x1=Draw_Button_Circle(x1, 485, 15);
		x1=DrawString( x1+5, 485, "Back");
		
		tiny3d_Flip();
		
		ps3pad_read();
		
		if(new_pad & BUTTON_CIRCLE) {
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
	FILE *f;
	
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

u8 SetPerms(char* path)
{
	if(is_ntfs(path)) return SUCCESS;
	
	u8 f_info = path_info(path);
	
	if(f_info == _FILE) {
		if(sysLv2FsChmod(path, FS_S_IFMT | 0777) == 0) return SUCCESS;
		else return FAILED;
	} 
	else if(f_info == _NOT_EXIST) return FAILED;
	
	sysLv2FsChmod(path, FS_S_IFDIR | 0777);
	
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
			sysLv2FsChmod(newpath, FS_S_IFMT | 0777);
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

FILE *openSFO(char *path, u32 *start_offset, u32 *size)
{
	FILE *sfo=NULL;
	
	u8 type = get_ext(path);
	
	if(type != _ISO_PS3 && type != _ISO_PSP && type != _JB_PS3 && type != _SFO) return FAILED;
	
	if(type == _SFO) {
		sfo = fopen(path, "rb+");
		if(sfo==NULL) return NULL;
		
		fseek (sfo , 0 , SEEK_END);
		*size = ftell (sfo);
		fseek(sfo, 0, SEEK_SET);
		
		*start_offset=0;
		
		return sfo;
	} else 
	if(type == _ISO_PS3) {
		sfo = fopen(path, "rb+");
		if(sfo==NULL) return NULL;
		u32 flba=0;
		u8 ret=0;
		int file_size=0;
		
		ret = get_FileOffset(sfo, "/PS3_GAME/PARAM.SFO", &flba,  (u32 *) &file_size);
	
		if(flba==0 || file_size==0 || ret == FAILED) {fclose(sfo); return NULL;}
		
		*start_offset=0x800*flba;
		*size=file_size;
		
		return sfo;
	} else
	if(type == _ISO_PSP) {
		sfo = fopen(path, "rb+");
		if(sfo==NULL) return NULL;
		u32 flba=0;
		u8 ret=0;
		int file_size=0;
		
		ret = get_FileOffset(sfo, "/PSP_GAME/PARAM.SFO", &flba,  (u32 *) &file_size);
	
		if(flba==0 || file_size==0 || ret == FAILED) {fclose(sfo); return NULL;}
		
		*start_offset=0x800*flba;
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
		
		fseek (sfo , 0 , SEEK_END);
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
	
	FILE *sfo=NULL;
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
	FILE *sfo=NULL;
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
	
	if(temp16 > key_name)  {fclose(sfo); return FAILED;}
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

FILE *openEBOOT(int pos, u32 *start_offset) 
{
	FILE *eboot=NULL;
	
	u8 type = list_game_platform[pos];
	if(type != _ISO_PS3 && type != _ISO_PSP && type != _JB_PS3)	type = get_ext(list_game_path[pos]);
	if(type != _ISO_PS3 && type != _ISO_PSP && type != _JB_PS3) return FAILED;
	
	if(type == _ISO_PS3) {
		eboot = fopen(list_game_path[pos], "rb+");
		if(eboot==NULL) return NULL;
		u32 flba=0;
		u8 ret=0;
		int file_size=0;
		ret = get_FileOffset(eboot, "/PS3_GAME/USRDIR/EBOOT.BIN", &flba, (u32 *) &file_size);
	
		if(flba==0 || file_size==0 || ret == FAILED) {fclose(eboot); return NULL;}
		
		*start_offset=0x800*flba;

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
	FILE *eboot=NULL;
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

typedef struct
{
	float pkgVers;
	int size;
	char url[255];
	float sysVers;
} upd_data;

static char getBuffer[1024];

int download(char *url, char *dst)
{
	int ret = 0, httpCode = 0;
	s32 cert_size=0;
	httpUri uri;
	httpClientId httpClient = 0;
	httpTransId httpTrans = 0;
	FILE *fp=NULL;
	s32 nRecv = -1;
	s32 size = 0;
	u64 dl=0;
	uint64_t length = 0;
	void *http_pool = NULL;
	void *uri_pool = NULL;
	void *ssl_pool = NULL;
	void *cert_buffer = NULL;
	
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

		ret = sslCertificateLoader(SSL_LOAD_CERT_SCE, NULL, 0, &cert_size);
		if (ret < 0) {
			print_load("Error : sslCertificateLoader failed (%x)", ret);
			ret=FAILED;
			goto end;
		}

		cert_buffer = malloc(cert_size);
		if (ret < 0) {
			print_load("Error : out of memory (cert_buffer)");
			ret=FAILED;
			goto end;
		}

		ret = sslCertificateLoader(SSL_LOAD_CERT_SCE, cert_buffer, cert_size, NULL);
		if (ret < 0) {
			print_load("Error : sslCertificateLoader failed (%x)", ret);
			ret=FAILED;
			goto end;
		}
		httpsData caList;
		caList.ptr = cert_buffer;
		caList.size = cert_size;
		
		ret = httpsInit(1, (const httpsData *) &caList);
		if (ret < 0) {
			print_load("Error : sslCertificateLoader failed (%x)", ret);
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
	
	if(strstr(url, "gamecovers.ezyro.com") != NULL) {
		httpHeader headerCookie = { (const char*) "Cookie", (const char*) "__test=e33ccad40e2c5eb87799048011774abc" };
		httpRequestAddHeader(httpTrans, &headerCookie);
	}
	
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
		//print_load("Status code (%d)", httpCode);
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
	
	upd_data data[512];
	
	print_load("Search Flags");
	for(n=0 ; n<file_size; n++) {
		if(strncmp(&xml[n], "package version", 15)==0) {
			nPKG++;
			sscanf(&xml[n+17], "%f%*s", &data[nPKG].pkgVers);
		}
		if(strncmp(&xml[n], "size", 4)==0) {
			sscanf(&xml[n+6], "%d%*s", &data[nPKG].size);
		}
		if(strncmp(&xml[n], "url", 3)==0) {
			k=n+5;
		}
		if(strncmp(&xml[n], ".pkg", 4)==0) {
			memcpy(data[nPKG].url, &xml[k], n+4-k);
		}
		if(strncmp(&xml[n], "ps3_system_ver", 14)==0) {
			sscanf(&xml[n+16], "%f%*s", &data[nPKG].sysVers);
		}
	}
	
	for(n=0 ; n<=nPKG; n++) {
		size_str[n] = get_unit(data[n].size);
	}
	
screen:

	end_loading();
	
	while(1)
	{
		cls();
		ps3pad_read();
		
		Draw_BGS();
		Draw_Notification();
		
		int x=50, y=40, xt;
		SetFontAutoCenter(0);
		SetFontSize(20,20);
		SetFontColor(COLOR_3, 0x0);
		
		Draw_Box(x, y+5, 0, 0, 10, 10, COLOR_3, NO);
		
		xt=DrawString(x+15, y, list_game_title[position]);
		y+=new_line(1);
		Draw_Box(x, y, 0, 0, xt-x, 2, COLOR_3, NO);
		
		y+=new_line(2);

		SetFontColor(COLOR_4, 0x0);

		DrawFormatString(x, y, "Update found = %d", nPKG+1);
		
		y+=new_line(2);
		
		for(n=0 ; n<=nPKG; n++) {
			if(n==d_position) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
			DrawFormatString(x, y, "Update: %1.2f  -  Size: %s  - System: %1.2f",	data[n].pkgVers, size_str[n], data[n].sysVers);
			y+=new_line(1);
		}
		
		SetFontColor(COLOR_1, 0x0);
		SetFontSize(15,15);
		x=25;
		x=Draw_Button_Circle(x, 485, 15);
		x=DrawString( x+5, 485, "Back ");
		if(nPKG!=-1)  {
			x=Draw_Button_Cross(x+5, 485, 15);
			x=DrawString( x+5, 485, "Download ");
		}
		if(nPKG>0) {
			x=Draw_Button_Square(x+5, 485, 15);
			x=DrawString( x+5, 485, "Download ALL");
		}
		if(nPKG!=-1)  {
			x=Draw_Button_Select(x+5, 485, 15);
			if(shutdown==YES) {
				x=DrawString( x+5, 485, "Turn OFF = YES");
			} else x=DrawString( x+5, 485, "Turn OFF = NO");
		}
		
		tiny3d_Flip();
		
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
			break;
		}
		if(new_pad & BUTTON_CROSS && nPKG!=-1) { 
			sprintf(dst, "/dev_hdd0/packages%s", strrchr(data[d_position].url, '/'));
			if(path_info(dst) == _FILE) show_msg("This file already exist"); 
			else {
				start_loading();
				if(download(data[d_position].url, dst) == SUCCESS) show_msg("Update Downloaded"); else 
				show_msg("Download Failed");
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
				if(download(data[n].url, dst) == SUCCESS) show_msg("Update Downloaded"); else
				show_msg("Download Failed");
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

	FILE *fp=NULL;
	char scanPath[128];
	char temp[128];
	
	scan_dir_number=-1;
	
	sprintf(scanPath, "/dev_hdd0/game/%s/USRDIR/setting/scan_dir.txt", ManaGunZ_id);
	
	if((fp=fopen(scanPath, "rb"))==NULL){
		return FAILED;
	}
	while(fgets(temp, 128, fp) != NULL) {
		strtok(temp, "\r\n");
		scan_dir_number++;
		strcpy(scan_dir[scan_dir_number], temp);
	}
	
	if(scan_dir_number != -1) return SUCCESS; else return FAILED;

}

void write_scan_dir()
{
	FILE *fp=NULL;
	char scanPath[128];
	int i;
	
	sprintf(scanPath, "/dev_hdd0/game/%s/USRDIR/setting/scan_dir.txt", ManaGunZ_id);
	
	if((fp=fopen(scanPath, "wb"))==NULL){
		return;
	}
	
	for(i=0; i<=scan_dir_number; i++) {
		fputs(scan_dir[i], fp);
		fputs("\r\n", fp);
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
		if(strstr(dir->d_name, "dev_usb") || strstr(dir->d_name, "dev_hdd0")) {
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
				
				char new_title_list[MAX_GAME][255]={{0}};
				char new_path_list[MAX_GAME][255]={{0}};
				char new_platform_list[MAX_GAME]={0};
				
				int new_PS3_game_number=-1;
				for(i=0;i<=game_number; i++) {
					if(strstr(list_game_path[i], path_unplug) == NULL) {
						new_PS3_game_number++;
						strcpy(new_path_list[new_PS3_game_number], list_game_path[i]);
						strcpy(new_title_list[new_PS3_game_number], list_game_title[i]);
						new_platform_list[new_PS3_game_number] = list_game_platform[i];
					}
				}
				
				if(game_number == new_PS3_game_number) {
					device_plug = 0;
					start_checking();
					end_loading();
					return;
				}
				
				game_number = new_PS3_game_number;
				memset(list_game_path, 0, sizeof(list_game_path));
				memset(list_game_title, 0, sizeof(list_game_title));
				memset(list_game_platform, 0, sizeof(list_game_platform));
				for(i=0;i<512; i++) {
					strcpy(list_game_path[i], new_path_list[i]);
					strcpy(list_game_title[i], new_title_list[i]);
					list_game_platform[i] = new_platform_list[new_PS3_game_number];
				}
			}
		} 
		else if(device_number > device_number_OLD) { // *** plug device ***
			for(k=0; k < device_number - device_number_OLD ; k++) {
				int old_PS3_game_number = game_number;
				char path_plug[20];
				for(i=0;i<=device_number; i++) {
					for(j=0;j<=device_number_OLD;j++) {
						if(strcmp(list_device_OLD[j], list_device[i])==0) break;
						if(j==device_number_OLD) strcpy(path_plug, list_device[i]);
					}
				}
				
				print_load("%s plugged", path_plug);
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
					print_load("Scanning : %s", scan_path);
					
					DIR *d;
					struct dirent *dir;
					
					d = opendir(scan_path);
					if(d==NULL) continue;
					
					while ((dir = readdir(d))) {
						if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;

						char temp[255];
						sprintf(temp, "%s/%s" , scan_path, dir->d_name);
						u8 ext = get_ext(temp);
						
						if(ext != _ISO_PS3 && ext != _ISO_PS2 && ext != _ISO_PS1 && ext != _ISO_PSP)
						if(ext != _JB_PS3 && ext != _JB_PS2 && ext != _JB_PS1 && ext != _JB_PSP) continue;

						game_number++;
						sprintf(list_game_path[game_number], "%s/%s" , scan_path, dir->d_name);
						
						strcpy(list_game_title[game_number], list_game_path[game_number]);
						strcpy(list_game_title[game_number], &strrchr(list_game_title[game_number], '/')[1]);
						strtok(list_game_title[game_number], ".");
						
						list_game_platform[game_number] = ext;
						
						if(ext == _ISO_PS3 || ext == _JB_PS3 || ext == _ISO_PSP || ext == _JB_PSP) {
							GetParamSFO("TITLE", list_game_title[game_number], game_number, NULL);
						}
						
					}
					closedir(d);
				}
				
				if(game_number == old_PS3_game_number) {
					device_plug = 0;
					start_checking();
					end_loading();
					return;
				}
				
				print_load("Sorting the list");
				int min; 
				char ta[128], tb[128];
				u8 t;
				for (i = 0; i<game_number; i++) { 
					min = i;
					for (j = i+1; j <= game_number; j++) { 
						strcpy(ta , list_game_title[j]);
						strcpy(tb, list_game_title[min]);
						if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
						if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
						if (strcmp(ta, tb) < 0) { 
							min = j; 
						}
					}
					if(min==i) continue;
					strcpy(ta , list_game_title[min]);
					strcpy(list_game_title[min], list_game_title[i]); 
					strcpy(list_game_title[i], ta); 
					strcpy(tb, list_game_path[min]);
					strcpy(list_game_path[min], list_game_path[i]); 
					strcpy(list_game_path[i], tb);
					t = list_game_platform[min];
					list_game_platform[min] = list_game_platform[i];
					list_game_platform[i] = t;
				}
			}
		}
		
		print_load("Reloading...");

		device_plug = 0;
		
		print_load("GetTheme...");
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
	
	if ( md5_file(path, (u8 *) MD5_local) != 0) {
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
	
	FILE *f;
	
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
	
	if(strstr(MD5_buff, MD5_local_STR) != NULL) {
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
	
	FILE *f;
	
	f = fopen(CRC_DB, "r");
	
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
	
    FILE *f;
    size_t n;
	
    unsigned char buf[1024];
	uint64_t read=0;
	uint64_t file_size;
	
    if( ( f = fopen( path, "rb" ) ) == NULL )
        return( 1 );

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
	
	char renaCRC_STR[10];
	sprintf(renaCRC_STR, "%X", renaCRC);
	char realCRC_STR[10];
	sprintf(realCRC_STR, "%X", crc);
	
	f = fopen(dst, "wb");
	if(f == NULL) {
		print_load("Error : cannot create CHECK.crc");
		return FAILED;
	}
	
	fputs("*** CRC from renascene.com ***\n\n", f);
	fputs(renaCRC_STR, f);
	fputs("\n\n*** real CRC ***\n\n", f);
	fputs(realCRC_STR, f);
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

void use_CONFIG()
{
	char CONFIG_path[128];
	
	strcpy(CONFIG_path, list_game_path[position]);
	strcat(CONFIG_path, ".CONFIG");
	
	if( path_info(CONFIG_path) == _FILE ) return;
	
	char ID[20];
	Get_ID(list_game_path[position], _ISO_PS2, ID);
	
	char LOC_CONFIG_path[128];
	
	sprintf(LOC_CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/OFFICIAL/%s.CONFIG", ManaGunZ_id, ID);
	
	if( Copy(LOC_CONFIG_path, CONFIG_path) == SUCCESS ) return;
	
	sprintf(LOC_CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/CUSTOM/%s.CONFIG", ManaGunZ_id, ID);
	
	if( Copy(LOC_CONFIG_path, CONFIG_path) == SUCCESS ) return;
	
}

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
	FILE *f;
	
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
	FILE *f;
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

u8 CheckIRD(char *G_PATH)
{
	char IRD_path[128]={0};
	char IRD_dir[128];
	char titleID[128];
	char SFOPATH[128];
	int i;
	
	print_head("Searching IRD...");
	
	sprintf(SFOPATH, "%s/PS3_GAME/PARAM.SFO", G_PATH);
	
	if(GetParamSFO("TITLE_ID", titleID, -1, SFOPATH) == FAILED ) {
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

u8 Get_PS2ID(char *ps2iso, char *PS2ID);
u8 Get_PS1ID(char *ps1iso, char *PS1ID);

u8 Get_ID(char *isopath, u8 platform, char *game_ID)
{
	char temp[255];
	
	if(platform == _ISO_PS3) {
		return GetParamSFO("TITLE_ID", game_ID, -1, isopath);	
	} else
	if(platform == _JB_PS3) {
		return GetParamSFO("TITLE_ID", game_ID, -1, isopath);	
	} else
	if(platform == _ISO_PSP) {
		return GetParamSFO("DISC_ID", game_ID, -1, isopath);	
	} else
	if(platform == _JB_PSP) {
		return GetParamSFO("DISC_ID", game_ID, -1, isopath);	
	} else
	if(platform == _ISO_PS2) {
		return Get_PS2ID(isopath, game_ID);
	} else
	if(platform == _JB_PS2) {
		sprintf(temp, "%s/SYSTEM.CNF", isopath);
		FILE *f;
		f=fopen(temp, "rb");
		if(f==NULL) return FAILED;
		fgets(temp, 128, f);
		if( strstr(temp, ";") != NULL) strtok(temp, ";");
		strcpy(game_ID, &strrchr(temp, '\\')[1]);
		fclose(f);
	} else
	if(platform == _ISO_PS1) {
		return Get_PS1ID(isopath, game_ID);
	} else
	if(platform == _JB_PS1) {
		sprintf(temp, "%s/SYSTEM.CNF", isopath);
		FILE *f;
		f=fopen(temp, "rb");
		if(f==NULL) return FAILED;
		fgets(temp, 128, f);
		if( strstr(temp, ";") != NULL) strtok(temp, ";");
		strcpy(game_ID, &strrchr(temp, '\\')[1]);
		fclose(f);
	} else return FAILED;
	
	return SUCCESS;
	
}

char lowit(char in){
	if(in<='Z' && in>='A') 
		return in-('Z'-'z');
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
	
	for(i=0; i<game_number; i++) {
		prog_bar1_value = (i*100)/game_number;
		
		if(cancel==YES) break;
		
		memset(game_ID, 0, sizeof(game_ID));
		memset(link, 0, sizeof(link));
		
		if( Get_ID(list_game_path[i], list_game_platform[i], game_ID) == FAILED) {
			print_load("Error : Failed to get ID %s, %d", list_game_path[i], list_game_platform[i]);
			continue;
		}
		
		sprintf(out, "/dev_hdd0/game/%s/USRDIR/covers/%s.JPG", ManaGunZ_id, game_ID);
		
		if(path_info(out)==_FILE) {print_load("OK : %s", list_game_title[i]); continue;}
		
		sprintf(link, "http://gamecovers.ezyro.com/download.php?file=%s.jpg", game_ID);
		
		if(download(link, out) == SUCCESS) {print_load("OK : %s", list_game_title[i]); nb_dl++; continue;}
		
		/*	
		
		// PS3
		http://www.gametdb.com/PS3/BCES00001
		
		// PS2/PSP/PS3
		http://sce.scene7.com/is/image/playstation/bljs10332_jacket
		
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
	
	sprintf(out, "%d cover(s) downloaded", nb_dl+1);
	show_msg(out);
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
		lv2syscall3(392, 0x1004, 0xa, 0x1b6);
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
	strtok(elf, ".");
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
	strtok(elf, ".");
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
	strtok(prx, ".");
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
			SetFontAutoCenter(0);
			SetFontSize(20,20);
			SetFontColor(COLOR_1, 0x0);
		
			DrawString(x, y, "Unplug the following device(s) :");
			for(i=0; i<15; i++){
				y+=20;
				DrawString(x, y, list_to_unplug[i]);
			}
		
			tiny3d_Flip();
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
	FILE *fp;
	char *mem = NULL;
	
	*file_size = 0;
	
	if( path_info(path) == _NOT_EXIST) return NULL;
	
	sysLv2FsChmod(path, FS_S_IFMT | 0777);

	fp = fopen(path, "rb");

	if (fp == NULL) return NULL;
	
	fseek(fp, 0, SEEK_END);
		
	*file_size = ftell(fp);
	int size = ftell(fp);
	
	mem = malloc(*file_size);

	if(!mem) {fclose(fp);return NULL;}
		
	fseek(fp, 0, SEEK_SET);

	prog_bar1_value = 0;
	int read = 0;
	while(read < size) {
		int wrlen = 1024;
		if(read+wrlen > size) wrlen = size-read;
		fread(mem+read, sizeof(u8), wrlen, fp);
		read += wrlen;
		prog_bar1_value = (read*100) / size;
	}
	prog_bar1_value = -1;
	
	fclose(fp);
	
	return mem;
}

char *LoadFile(char *path, int *file_size)
{
	FILE *fp;
	char *mem = NULL;
	
	*file_size = 0;
	
	if( path_info(path) == _NOT_EXIST) return NULL;
	
	sysLv2FsChmod(path, FS_S_IFMT | 0777);

	fp = fopen(path, "rb");

	if (fp == NULL) return NULL;
	
	fseek(fp, 0, SEEK_END);
		
	*file_size = ftell(fp);
		
	mem = malloc(*file_size);

	if(!mem) {fclose(fp);return NULL;}
		
	fseek(fp, 0, SEEK_SET);
	
	fread((void *) mem, 1, *file_size, fp);
	
	fclose(fp);
	
	return mem;
}


int SaveFileProg(char *path, char *mem, int file_size)
{
	FILE *fp;
   
	fp = fopen(path, "wb");

	if (fp == NULL) return FAILED;
	
	prog_bar2_value = 0;
	int write = 0;
	while(write < file_size) {
		int wrlen = 1024;
		if(write+wrlen > file_size) wrlen = file_size-write;
		fwrite(mem+write, sizeof(u8), wrlen, fp);
		write += wrlen;
		prog_bar2_value = (write*100) / file_size;
	}
	prog_bar2_value = -1;
	
	fclose(fp);

	sysLv2FsChmod(path, FS_S_IFMT | 0777);

	return SUCCESS;
}

int SaveFile(char *path, char *mem, int file_size)
{
	FILE *fp;
   
	fp = fopen(path, "wb");

	if (fp == NULL) return FAILED;
	   
	fwrite((void *) mem, 1, file_size, fp);

	fclose(fp);

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
		
		char *data;
		long size;
		size_t result;
		
		if((fp = fopen(ori_prx, "rb"))!=NULL) {

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
			patch_from_MM[0x52]=0x68;
			patch_from_MM[0x53]=0x64;
			patch_from_MM[0x56]=0x64;
			patch_from_MM[0x73]=0x00;
			patch_from_MM[0x72]=0x00;
		} 
		else patch_from_MM[0x73]=0x30+device;
		
		memcpy(&data[n-0x20], patch_from_MM, 0x84);
	
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
			print_load("Error : cannot write the file\n");
			return NOK;
		}
		fclose(fp);
		free(data);
		
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
		
		if((fp = fopen(ori_prx, "rb"))!=NULL) {

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
		
		if((fp = fopen(ori_prx, "rb"))!=NULL) {

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

	char *libfs_path =(char*) malloc(sizeof(char)*128);
	
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
		
		if((fp = fopen(ori_prx, "rb"))!=NULL) {

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
	FILE *f;
	f = fopen(isoPath, "rb");			
	if(f==NULL) {
		print_load("Error : failed top open %s", isoPath);
		return NO;
	}
	
	int i;
	u32 sector_size[4] = {0x800, 0x930, 0x920, 0x990};
	char *mem =  (char *) malloc(0x60);
		if(mem==NULL) {
		fclose(f);
		print_load("Error : malloc failed");
		return NO;
	}

	for(i=0; i<4; i++) {
		memset(mem, 0, sizeof(mem));
		fseek(f, sector_size[i]*0x10, SEEK_SET);

		fread(mem, 0x60, 1, f);
		
		if(!memcmp((char *) &mem[0x28], (char *) "PS3VOLUME", 0x9)) {
			free(mem);
			fclose(f);
			return _ISO_PS3;
		}
		if(!memcmp((char *) &mem[0x8], (char *) "PLAYSTATION", 0xB)) {
			free(mem);
			fclose(f);
			return _ISO_PS2;
		}
		if(!memcmp((char *) &mem[0x8], (char *) "PSP GAME", 0x8)) {
			free(mem);
			fclose(f);
			return _ISO_PSP;
		}
		if(!memcmp((char *) &mem[0x20], (char *) "PLAYSTATION", 0xB)) {
			free(mem);
			fclose(f);
			return _ISO_PS1;
		}
	}
	
	free(mem);
	fclose(f);
	
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
	char ext[128];
	
	u8 is_path=NO;
	
	if(strstr(file, "/")) is_path=YES;
	
	if(is_path==YES) {
		if(path_info(file) == _DIRECTORY)  {
			char temp[255];
			sprintf(temp, "%s/PS3_GAME/PARAM.SFO", file);
			if(path_info(temp) == _FILE) return _JB_PS3;
			sprintf(temp, "%s/PSP_GAME/PARAM.SFO", file);
			if(path_info(temp) == _FILE) return _JB_PSP;
			sprintf(temp, "%s/PSP_GAME/SYSTEM.CNF", file);
			if(path_info(temp) == _FILE) {
				FILE* f;
				f=fopen(temp, "rb");
				fgets(temp, 128, f);
				strtok(temp, " =");
				fclose(f);
				if(!strcmp(temp, "BOOT2")) return _JB_PS2; else
				if(!strcmp(temp, "BOOT")) return _JB_PS1;
			}
			return _DIRECTORY;
		}
		strcpy(file_name, &strrchr(file, '/')[1]);
	} else strcpy(file_name, file);
	

	if(strstr(file_name, ".")) { // get an ext
		strcpy(ext, strrchr(file_name, '.'));
	} else return _FILE;
	
	if (!strcmp(file_name, "xRegistry.sys")) {
		return _XREG;
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
	if (!strcmp(ext, ".ISO") || !strcmp(ext, ".iso") ||
		!strcmp(ext, ".BIN") || !strcmp(ext, ".bin") ||
		!strcmp(ext, ".IMG") || !strcmp(ext, ".img") ||
		!strcmp(ext, ".MDF") || !strcmp(ext, ".mdf") ||
		!strcmp(&file[strlen(file)-6], ".ISO.0") || !strcmp(&file[strlen(file)-6], ".iso.0") ) 
	{
		if(is_path == YES) {
			return ISOtype(file);
		}
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
// PS1
//*******************************************************

u8 Get_PS1ID(char *ps1iso, char *PS1ID)
{
	FILE *f;
	int i;
	
	f = fopen(ps1iso,"rb");
	if(f < 0) {
		print_load("Error : Cannot open %s", ps1iso);
		return FAILED;
	}
	
	u32 all_sizes[4] = {0x930, 0x800, 0x920, 0x990};
	u32 sector_size=0;
	
	char *data = (char *) malloc(0xC);

	for(i=0; i<4; i++) {
		memset(data, 0, sizeof(data));
		fseek(f, all_sizes[i]*0x10+0x20, SEEK_SET);
		fread(data, 0xC, 1, f);
		if(!memcmp((char *) data, (char *) "PLAYSTATION ", 0xC)) {
			sector_size=all_sizes[i];
			break;
		}
	}
	free(data);
	
	if(sector_size==0) {
		fclose(f);
		print_load("Error : sector size not found");
		return FAILED;
	}
	
	fseek(f, sector_size*0x10+0xBA, SEEK_SET);
	
	u32 table=0;
	fread(&table, sizeof(u32), 1, f);
	
	if(table == 0) {
		fclose(f);
		print_load("Error : table offset not found");
		return FAILED;
	}
	fseek(f, table*sector_size, SEEK_SET);
	
	char *mem =  (char *) malloc(sector_size);
	if(mem==NULL) {
		fclose(f);
		return FAILED;
	}
	
	fread(mem, sector_size, 1, f);
	
	u32 file_offset=0;
	u32 file_size=0;
	for(i=0; i<sector_size; i++) {
		if(!memcmp((char *) &mem[i], (char *) "SYSTEM.CNF;1", 12)) {
			memcpy(&file_offset, &mem[i-0x1B], 4);
			memcpy(&file_size, &mem[i-0x13], 4);
			break;
		}
	}
	free(mem);
	
	if(file_offset==0 || file_size==0) {
		fclose(f);
		if(PS1ID == NULL) return FAILED;
		print_load("Error : File not found in table");
		return FAILED;
	}
	
	if(PS1ID == NULL) {
		fclose(f);
		return SUCCESS;
	}
	
	fseek(f, file_offset * sector_size + 0x18, SEEK_SET);

	char temp[128];
	fgets(temp, 128, f);
	if( strstr(temp, ";") != NULL) strtok(temp, ";");
	
	if( strstr(temp, "\\") != NULL) strcpy(PS1ID, &strrchr(temp, '\\')[1]); else
	if( strstr(temp, ":") != NULL) strcpy(PS1ID, &strrchr(temp, ':')[1]);
	
	fclose(f);
	
	return SUCCESS;
}

//*******************************************************
// PS2
//*******************************************************

u8 Get_PS2ID(char *ps2iso, char *PS2ID)
{
	FILE *f;
	int i;
	
	u32 sector_size = 0x800;
	
	f = fopen(ps2iso,"rb");
	if(f < 0) {
		print_load("Error : Cannot open %s", ps2iso);
		return FAILED;
	}
	fseek(f, sector_size*0x10+0xA2, SEEK_SET);
	
	u32 table=0;
	fread(&table, sizeof(u32), 1, f);
	
	if(table == 0) {
		fclose(f);
		print_load("Error : table offset not found");
		return FAILED;
	}
	
	fseek(f, table*sector_size, SEEK_SET);
	
	char *mem =  (char *) malloc(sector_size);
	if(mem==NULL) {
		fclose(f);
		print_load("Error : malloc failed");
		return FAILED;
	}
	
	fread(mem, sector_size, 1, f);
	
	u32 file_offset=0;
	u32 file_size=0;
	for(i=0; i<sector_size; i++) {
		if(!memcmp((char *) &mem[i], (char *) "SYSTEM.CNF;1", 12)) {
			memcpy(&file_offset, &mem[i-0x1B], 4);
			memcpy(&file_size, &mem[i-0x13], 4);
			break;
		}
	}
	free(mem);
	
	if(file_offset==0 || file_size==0) {
		fclose(f);
		if(PS2ID == NULL) return FAILED;
		print_load("Error : File not found in table off : %X size : %X", file_offset, file_size);
		return FAILED;
	}
	
	if(PS2ID == NULL) {
		fclose(f);
		return SUCCESS;
	}
	
	fseek(f, file_offset * sector_size, SEEK_SET);
	
	char temp[128];
	fgets(temp, 128, f);
	if( strstr(temp, ";") != NULL) strtok(temp, ";");
	
	if( strstr(temp, "\\") != NULL) strcpy(PS2ID, &strrchr(temp, '\\')[1]); else
	if( strstr(temp, ":") != NULL) strcpy(PS2ID, &strrchr(temp, ':')[1]);
	fclose(f);
	
	return SUCCESS;
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

	restore_syscall8[0]= SYSCALL_TABLE + 64ULL; // (8*8)
	restore_syscall8[1]= lv2peek(restore_syscall8[0]);

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
		sprintf(temp, "%s", get_libfs_path());
		if(path_info(temp) == _FILE)	add_sys8_path_table("/dev_flash/sys/external/libfs.sprx", temp);
	} else {
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
		sprintf(temp, "%s", get_libfs_path());
		if(path_info(temp) == _FILE)	add_to_map("/dev_flash/sys/external/libfs.sprx", temp);
		
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

int is_cobra(void)
{
	u32 version = 0x99999999;
	if (sys_get_version(&version) < 0)	return 0;
	if (version != 0x99999999 && sys8_mamba() != 0x666)	return 1;
	return 0;
}

int is_usb(char *file_name)
{
	if(strstr(file_name, "/dev_usb")) return YES;
	return NO;
}

int is_iso(char *file_name)
{
	if((strstr(file_name, ".iso") != NULL) || (strstr(file_name, ".ISO") != NULL)) return YES;
	return NO;
}

int is_splitted_iso()
{
	if(strstr(GamPath, ".iso.0") != NULL) return 1;
	if(strstr(GamPath, ".ISO.0") != NULL) return 2;
	return 0;
}

void cobra_MountISO(int EMU)
{
	int i;
	if(strstr(GamPath, "/ntfs")) {
		uint8_t *plugin_args = malloc(0x20000);
		uint32_t *sections = malloc(MAX_SECTIONS * sizeof(uint32_t));
		uint32_t *sections_size = malloc(MAX_SECTIONS * sizeof(uint32_t));
		rawseciso_args *p_args;  
		memset(sections, 0, MAX_SECTIONS * sizeof(uint32_t));
		memset(sections_size, 0, MAX_SECTIONS * sizeof(uint32_t));
		memset(plugin_args, 0, 0x10000);

		int parts = ps3ntfs_file_to_sectors(GamPath, sections, sections_size, MAX_SECTIONS, 1);

		if(!strstr(GamPath, ".iso.0") || !strstr(GamPath, ".ISO.0")) {	   
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
			if (cobra_load_vsh_plugin(0, temp_buffer + 2048, plugin_args, 0x10000) == 0) return;
		}
	} 
	else {
		char *iso_path[30];
		int nb_iso=0;
		unsigned int effective_disctype, iso_disctype;

		splitted_iso = is_splitted_iso();

		switch(splitted_iso) {
			case 1:
			{
				strtok (GamPath,".");
				for(i=0; i<30; i++) {
					char temp[128];
					sprintf(temp, "%s.iso.%d" , GamPath, i);		
					if(path_info(temp) == _NOT_EXIST) {
						break;
					} else {
						iso_path[i] = malloc(1024);
						sprintf(iso_path[i], "%s", temp);
						nb_iso +=1;
					}
				}
			}
			break;
			case 2:
			{
				strtok (GamPath,".");
				for(i=0; i<30; i++) {
					char temp[128];
					sprintf(temp, "%s.ISO.%d" , GamPath, i);
					if(path_info(temp) == _NOT_EXIST) {
						break;
					} else {
						iso_path[i] = malloc(1024);
						sprintf(iso_path[i], "%s", temp);
						nb_iso +=1;
					}
				}
			}
			break;
			default:
			{				
				iso_path[0] = GamPath;
				nb_iso = 1;
			}
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
			sprintf(temp, "%s", get_libfs_path());
			if(path_info(temp) == _FILE)	{sys_map_path("/dev_flash/sys/external/libfs.sprx", temp);}
			
			cobra_map_game(GamPath, (char*)"TEST00000", &i);
		} else if(emu==NONE) {
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
		printf("Error : failed to malloc");
		return FAILED;
	}
	zlib_decompress((char *) MAMBA, (char *) mamba_data, MAMBA_SIZE, (int *) &size);
	if(size==0) {
		printf("Error : failed to decompress");
		free(mamba_data);
		return FAILED;
	}
		
	FILE *f;
	f = fopen(mamba_path, "wb");
	if(f==NULL) {
		printf("Error : failed to create mamba file");
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
	//remove_lv2_protection();

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
	
	if(plugin_args) {
		if(strstr(GamPath, "ntfs")) {	
			uint32_t *sections = malloc(MAX_SECTIONS * sizeof(uint32_t));
			uint32_t *sections_size = malloc(MAX_SECTIONS * sizeof(uint32_t));
			rawseciso_args *p_args; 
			memset(sections, 0, MAX_SECTIONS * sizeof(uint32_t));
			memset(sections_size, 0, MAX_SECTIONS * sizeof(uint32_t));
			memset(plugin_args, 0, 0x10000);

			int parts = ps3ntfs_file_to_sectors(GamPath, sections, sections_size, MAX_SECTIONS, 1);
			
			if(!strstr(GamPath, ".iso.0") || !strstr(GamPath, ".ISO.0")) { 
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
				
				if(strstr(GamPath, ".iso.0") != NULL || strstr(GamPath, ".ISO.0") != NULL) {
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
	}
	if(plugin_args) free(plugin_args); plugin_args = NULL;
	
}

void mamba_Mount()
{
	install_mamba();
	
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
			sprintf(temp, "%s", get_libfs_path());
			if(path_info(temp)==_FILE)	{mamba_map("/dev_flash/sys/external/libfs.sprx", temp);}
			
			{mamba_map("/dev_bdvd", GamPath);}
			
		} else 
		if(emu==NONE) {
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

static int pkg_pack_data(file_table_tr *ftr, pkg_file_entry *table,  int item_count, sha1_context *ctx, FILE *out)
{
	int i;
	FILE *f;
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
	FILE *dec, *out, *temp;
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
		u32 wrlen = 1024;
		if(write+wrlen > tmp) wrlen = tmp-write;
		fwrite(ou+write, sizeof(u8), wrlen, out);
		write += wrlen;
		prog_bar1_value = (write*100)/tmp;
	}
	
	
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
	
	if(cancel == YES) {
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

static int pkg_debug_decrypt (PagedFile *f, PagedFileCryptOperation operation, u8 *ptr, u32 len, void *user_data)
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

u8 pkg_open (const char *filename, PagedFile *in, pkg_header *header, pkg_file_entry **files)
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
	FILE *txt;
	PagedFile in = {0};
	pkg_header header;
	pkg_info info;
	pkg_file_entry *files = NULL;
	char str[255];
	
	
	txt = fopen("/dev_hdd0/tmp/pkg_list.txt", "wb");
	if(txt == NULL) {
		print_load("Error : cannot create pkg_list.txt");
		return FAILED;
	}
	
	if (pkg_open (filename, &in, &header, &files) == FAILED) {
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
	FILE *fp;
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
	
	return SUCCESS;
}

u8 write_AutoMount_setting(char *path)
{
	char Mount_path[128];
	FILE *fp;
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
		strcpy(src, list_game_path[position]);
		strtok(src, ".");
		strcat(src, ".PNG");
	} else {
		sprintf(src, "%s/PS3_GAME/ICON0.PNG", list_game_path[position]);
	}
	if( CopyFile(src, dst) == FAILED ) {
		print_load("Error : failed to copy ICON0.PNG");
		Delete(lch);
		return FAILED;
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
	for(i=0; i<=strlen(list_game_title[position]); i++) {		
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
	mkdir(lch, 0777);
	
	sprintf(dst, "/dev_hdd0/packages/%s.pkg", ascii_name);
	Delete(dst);
	sprintf(src, "/dev_hdd0/game/%s/USRDIR", ManaGunZ_id);
	if( pkg_pack(dst, content_id, src, "launcher") == FAILED ) {
		print_load("Error : Failed to make PKG");
		Delete(lch);
		return FAILED;
	}
	
// Delete launcher directory
	sprintf(dst, "/dev_hdd0/game/%s/USRDIR/launcher", ManaGunZ_id);
	Delete(dst);
	
	return SUCCESS;
}

//*******************************************************
// Settings
//*******************************************************

void read_setting()
{
	FILE *fp=NULL;
	char setPath[128];
	
	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/setting.bin", ManaGunZ_id);
	
	if((fp = fopen(setPath, "rb"))!=NULL) {
		fread(&Themes[0], sizeof(char), 0x40, fp);
		fread(&Themes[1], sizeof(char), 0x40, fp);
		fread(&Themes[2], sizeof(char), 0x40, fp);
		fread(&Themes[3], sizeof(char), 0x40, fp);
		fread(&LIST_Show_ICON0, sizeof(u8), 1, fp);
		fread(&UI_position, sizeof(u8), 1, fp);
		fread(&grid_type, sizeof(u8), 1, fp);
		fread(&direction, sizeof(u8), 1, fp);
		fread(&animated, sizeof(u8), 1, fp);
		fread(&keep_prop, sizeof(u8), 1, fp);
		fread(&grid_nb_lines, sizeof(u8), 1, fp);
		fread(&grid_nb_columns, sizeof(u8), 1, fp);
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
		fread(&FLOW_use_Cover, sizeof(u8), 1, fp);
		fread(&Only_FAV, sizeof(u8), 1, fp);
		fread(&use_sidemenu, sizeof(u8), 1, fp);
		fclose(fp);
	}
	
}

void write_setting()
{
	FILE *fp=NULL;
	char setPath[128];
	
	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/setting.bin", ManaGunZ_id);
	
	if((fp = fopen(setPath, "wb"))!=NULL)	{
		fwrite(&Themes[0], sizeof(char), 0x40, fp);
		fwrite(&Themes[1], sizeof(char), 0x40, fp);
		fwrite(&Themes[2], sizeof(char), 0x40, fp);
		fwrite(&Themes[3], sizeof(char), 0x40, fp);
		fwrite(&LIST_Show_ICON0, sizeof(u8), 1, fp);
		fwrite(&UI_position, sizeof(u8), 1, fp);
		fwrite(&grid_type, sizeof(u8), 1, fp);
		fwrite(&direction, sizeof(u8), 1, fp);
		fwrite(&animated, sizeof(u8), 1, fp);
		fwrite(&keep_prop, sizeof(u8), 1, fp);
		fwrite(&grid_nb_lines, sizeof(u8), 1, fp);
		fwrite(&grid_nb_columns, sizeof(u8), 1, fp);
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
		fwrite(&FLOW_use_Cover, sizeof(u8), 1, fp);
		fwrite(&Only_FAV, sizeof(u8), 1, fp);
		fwrite(&use_sidemenu, sizeof(u8), 1, fp);
		fclose(fp);
	}
	
	char sfo[64];
	sprintf(sfo, "/dev_hdd0/game/%s/PARAM.SFO", ManaGunZ_id);
	SetParamSFO("ITEM_PRIORITY", (char *) &XMB_priority, 0, sfo);
	
	if(Load_GamePIC == NO && COVER_Loaded == NO && Show_COVER == YES) {
		start_Load_GamePIC();
	} 
	
	read_setting();
}

void read_game_setting(char *file_name)
{
	FILE *fp=NULL;
	char setPath[128];
	
	if(iso) sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[ISO]%s.bin", ManaGunZ_id, file_name);
	else	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[JB]%s.bin", ManaGunZ_id, file_name);
	
	if((fp = fopen(setPath, "rb"))!=NULL)	{
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
}

void write_game_setting(char *file_name)
{
	if(AutoM == YES) return;

	FILE *fp=NULL;
	char setPath[128];
	
	if(iso) sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[ISO]%s.bin", ManaGunZ_id, file_name);
	else	sprintf(setPath, "/dev_hdd0/game/%s/USRDIR/setting/game_setting/[JB]%s.bin", ManaGunZ_id, file_name);
	
	if((fp = fopen(setPath, "wb"))!=NULL)	{
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
	FILE *fp=NULL;
	char favPath[128];
	int i;
	u16 path_size;
	
	sprintf(favPath, "/dev_hdd0/game/%s/USRDIR/setting/fav.bin", ManaGunZ_id);
	
	if((fp = fopen(favPath, "wb"))!=NULL)	{
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
	FILE *fp=NULL;
	char favPath[128];
	int i;
	u16 path_size;
	
	sprintf(favPath, "/dev_hdd0/game/%s/USRDIR/setting/fav.bin", ManaGunZ_id);
	
	if((fp = fopen(favPath, "rb"))!=NULL)	{
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
	FILE* fp;
	int i;
	
	cobra = is_cobra();
	mamba = is_mamba();
	
	if((fp = fopen("/dev_hdd0/vsh/pushlist/game.dat", "rb"))!=NULL) {
		fgets(ManaGunZ_id, 10, fp);
		fclose(fp);
	} else {
		print_load("Error : can't get ManaGunZ_id");
		return NOK;
	}
	
	peek_IDPS();
	
	print_load("Reset BD");
	
	unpatch_bdmirror();
	
	clean_tables();
	
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

	if(cobra) {
		unsigned int real_disctype;
		cobra_get_disc_type(&real_disctype, NULL, NULL);
		if (real_disctype == DISC_TYPE_NONE) real_disk = NO; else
		real_disk = YES;
	} else {
		if(path_info("/dev_bdvd") == _NOT_EXIST) real_disk = NO; else
		real_disk = YES;
	}

	getDevices();

	char temp[128];
	for(i=0; i<=device_number; i++) {
		sprintf(temp, "/%s", list_device[i]);
		move_bdemubackup_to_origin(temp);
	}

	return OK;
}

//*******************************************************
// File Manager
//*******************************************************

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
#define MAX_ITEM		4096

static float window_x[10];
static float window_y[10];
static float window_z[10];
static float window_h[10];
static float window_w[10];
static char window_path[10][MAX_ITEM];
static char window_content_Name[10][MAX_ITEM][255];
static u64 window_content_Size[10][MAX_ITEM];
static u8 window_content_Type[10][MAX_ITEM];
static u8 window_content_Selected[10][MAX_ITEM];
static u8 window_sort[10];
static float window_w_col_size[10];
static int window_content_N[10];
static u8 window_open[10] = {0};
static int8_t window_activ;

static u8 window_item_N[10]; // nb of item displayed

static u32 window_scroll_N[10]; //	nb of increment
static u32 window_scroll_P[10]; // 	increment position
static float window_scroll_size[10];
static float window_scroll_y[10];

static char option_sel[512][512];
static int option_sel_N;
static char option_item[64][64];
static int option_item_N;
static char option_copy[512][512];
static int option_copy_N=-1;
static u8 option_cut = NO;
static u8 option_activ = NO;
static float option_x;
static float option_y;
static float option_h;
static float option_w;

static u8 prop_activ;
static u64 prop_md5[2];
static u32 prop_sha1[5];
static char prop_type[64];
static char prop_path[512];
#define PROP_FONT	20
#define PROP_LINE_N	7
#define PROP_H		PROP_FONT*PROP_LINE_N
#define PROP_W		800
#define PROP_COL_W	75
#define PROP_X		848/2-PROP_W/2
#define PROP_Y		512/2-PROP_H/2

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

static u8 txt_viewer_activ = NO;
char *txt_viewer_content;

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
	
	int size;
	char *buff = LoadFile(file_path, &size);
	if(buff==NULL) return;
	
	FILE *f;
	f=fopen(file_path, "a");
	if(f==NULL) {free(buff); return;}
	if(buff[strlen(buff)-1] != '\n' && size != 0) fputs("\n", f);;
	fputs(str, f);
	fclose(f);
	
	free(buff);
}

void remove_from_list(char *file_path, char *str)
{
	FILE *fr;
	FILE *fw;
	char temp[255];
	char line[255];
	
	strcpy(temp, file_path);
	strcat(temp, "_temp");
	
	fr=fopen(file_path, "rb");
	if(fr==NULL) return;
	fw=fopen(temp, "wb");
	if(fw==NULL) return;
	
	while(fgets(line, 255, fr) != NULL) {
		if(strstr(line, str) == NULL) {
			fputs(line, fw);
		}
	}
	
	fclose(fr);
	fclose(fw);
	
	Delete(file_path);
	rename(temp, file_path);
}

// *** ICONS ***

void DrawIcon_Directory(float x, float y, float z)
{
	// CONTENT_FSIZE = 15;
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

void DrawIcon_File(float x, float y, float z, u32 color)
{
	// CONTENT_FSIZE = 15
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

// *** Window ***
void DrawTXTInBox(float x, float y, float z, float w, float h, char *txt, u32 bg_color, u32 font_color);
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
		SetFontSize(TOP_H/2, TOP_H/2);
		SetFontColor(WHITE, 0);
		
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
		SetFontSize(CONTENT_FSIZE, CONTENT_FSIZE);
		SetFontColor(BLACK, 0);

		Draw_Box(window_x[n]+BORDER, window_y[n]+TOP_H, window_z[n], 0,  window_w[n]-BORDER*2, window_h[n]-TOP_H-BORDER, 0xF0F0F0FF, NO);
		
		//COLUMN HEADER BOX
		Draw_Box(window_x[n]+BORDER, window_y[n]+TOP_H,  window_z[n], 0, window_w[n]-BORDER*2, COL_H, 0xD4DBEDFF, NO); 
		DrawString(window_x[n]+BORDER+5, window_y[n]+TOP_H+3, "Name");
		
		if(window_w_col_size[n]< COL_W_MIN) window_w_col_size[n]=COL_W_MIN;
		if(window_w[n] - window_w_col_size[n] - BORDER*2 - SCROLL_W < COL_W_MIN) window_w_col_size[n] = window_w[n] - COL_W_MIN - BORDER*2 - SCROLL_W;
		
		tiny3d_SetPolygon(TINY3D_LINES);
		tiny3d_VertexPos(window_x[n]+window_w[n] - BORDER-SCROLL_W-window_w_col_size[n], window_y[n]+TOP_H+2 , window_z[n]);
		tiny3d_VertexColor(0x505050FF);
		tiny3d_VertexPos(window_x[n]+window_w[n] - BORDER-SCROLL_W-window_w_col_size[n], window_y[n]+TOP_H+COL_H-2 , window_z[n]);
		tiny3d_End();
		
		DrawString(window_x[n]+window_w[n]-BORDER-SCROLL_W-window_w_col_size[n] + 5, window_y[n]+TOP_H+3, "Size");
		
		//SCROLL BAR
		window_item_N[n] = (window_h[n] - TOP_H-COL_H-BORDER) / CONTENT_FSIZE;
		window_scroll_N[n] = 0;
		if(window_content_N[n] > window_item_N[n] ) window_scroll_N[n] = window_content_N[n]+1 - window_item_N[n] ;
		if(window_scroll_P[n] > window_scroll_N[n]) window_scroll_P[n] = window_scroll_N[n];
		
		Draw_Box(window_x[n]+window_w[n]-BORDER-SCROLL_W, window_y[n]+TOP_H+COL_H, window_z[n],  0, SCROLL_W, window_h[n]-TOP_H-COL_H-BORDER, 0xD0D0D0FF, NO);

		if(window_scroll_N[n]>0) {
			window_scroll_size[n] = (window_h[n]-TOP_H-COL_H-BORDER) - (SCROLL_H_MIN*window_scroll_N[n]);
			if( window_scroll_size[n] < SCROLL_H_MIN ) window_scroll_size[n] = SCROLL_H_MIN;
			
			window_scroll_y[n]	= (window_h[n]-TOP_H-COL_H-window_scroll_size[n]-BORDER) * window_scroll_P[n] / window_scroll_N[n]  + curs_move_scroll;
			if(window_scroll_y[n] < 0) window_scroll_y[n]=0;
			
			Draw_Box(window_x[n]+window_w[n]-BORDER-SCROLL_W, window_y[n]+TOP_H+COL_H+window_scroll_y[n], window_z[n], 0, SCROLL_W, window_scroll_size[n], 0x9090C0FF, NO);
		}
		
		// CONTENT
		int i;
		for(i=0 ; i<window_item_N[n]; i++) {
			if(window_content_N[n] < i+window_scroll_P[n]) break;
			
			if(  window_x[window_activ]+BORDER				< curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W
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
			
			if(window_content_Size[n][window_scroll_P[n]+i] != 0) {
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
				Draw_DISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, COLOR_PS3);
			}
			else if(ext == _ISO_PS2) {
				Draw_DISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, COLOR_PS2);
			}
			else if(ext == _ISO_PS1) {
				Draw_DISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, COLOR_PS1);
			}
			else if(ext == _ISO_PSP) {
				Draw_DISK(window_x[n]+BORDER+1 , window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], 16, COLOR_PSP);
			}
			else DrawIcon_File(window_x[n]+BORDER+2, window_y[n]+TOP_H+COL_H+CONTENT_FSIZE*i, window_z[n], WHITE);
			
		}
	}
}

void Draw_cursor()
{	
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

void cursor_input() {

	//L3 Grid_move cursor
	curs_move_x = (paddata.button[6] - 128)/30;
	curs_move_y = (paddata.button[7] - 128)/30;
	curs_x += curs_move_x;
	curs_y += curs_move_y;
	if(curs_x > 848) curs_x=848;
	if(curs_x < 0  ) curs_x=0  ;
	if(curs_y > 512) curs_y=512;
	if(curs_y < 0  ) curs_y=0  ;

}

void sort()
{
	int min;
	u8 t;
	u64 t1;
	char ta[255], tb[255];
	int i, j;
	
	int Folder_N = -1;
	int File_N = -1;
	
	char list_Dir[512][255];
	u8 list_Dir_sel[512];
	char list_Fil[512][255];
	u64 list_Fil_siz[512];
	u8 list_Fil_sel[512];
	
	char temp[255];
	
	for (i = 0; i<=window_content_N[window_activ]; i++) {
		if(strcmp(window_content_Name[window_activ][i], "..") == 0) continue;
		if(window_content_Type[window_activ][i] == _DIRECTORY) {
			Folder_N++;
			strcpy(list_Dir[Folder_N], window_content_Name[window_activ][i]);
			list_Dir_sel[Folder_N] = window_content_Selected[window_activ][i];
		} else {
			File_N++;
			strcpy(list_Fil[File_N], window_content_Name[window_activ][i]);
			list_Fil_sel[File_N] = window_content_Selected[window_activ][i];
			list_Fil_siz[File_N] = window_content_Size[window_activ][i];
		}
	}
	
	for (i = 0; i<Folder_N; i++) { 
		min = i;
		for (j = i+1; j <= Folder_N; j++) { 
			strcpy(ta , list_Dir[j]);
			strcpy(tb, list_Dir[min]);
			if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
			if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
			if(window_sort[window_activ] == ASC) {
				if(strcmp(ta, tb) < 0) min = j;
			} else if(strcmp(ta, tb) > 0) min = j;
		}
		if(min==i) continue;
		
		strcpy(ta , list_Dir[min]);
		strcpy(list_Dir[min], list_Dir[i]); 
		strcpy(list_Dir[i], ta);
		
		t = list_Dir_sel[min];
		list_Dir_sel[min] = list_Dir_sel[i];
		list_Dir_sel[i] = t;
	}
	
	for (i = 0; i<File_N; i++) { 
		min = i;
		for (j = i+1; j <= File_N; j++) { 
			strcpy(ta , list_Fil[j]);
			strcpy(tb, list_Fil[min]);
			if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
			if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
			if(window_sort[window_activ] == ASC) {
				if(strcmp(ta, tb) < 0) min = j;
			} else if(strcmp(ta, tb) > 0) min = j;
		}
		if(min==i) continue;
		
		strcpy(ta , list_Fil[min]);
		strcpy(list_Fil[min], list_Fil[i]); 
		strcpy(list_Fil[i], ta);
		
		t = list_Fil_sel[min];
		list_Fil_sel[min] = list_Fil_sel[i];
		list_Fil_sel[i] = t;
		
		t1 = list_Fil_siz[min];
		list_Fil_siz[min] = list_Fil_siz[i];
		list_Fil_siz[i] = t1;
	}
	
	strcpy(window_content_Name[window_activ][0], "..");
	window_content_Selected[window_activ][0] = NO;
	window_content_Type[window_activ][0] = _DIRECTORY;
	window_content_Size[window_activ][0] = 0;
	
	if(window_sort[window_activ] == ASC) {
		for(j=0; j<=Folder_N; j++) {
			strcpy(window_content_Name[window_activ][j+1], list_Dir[j]);
			window_content_Selected[window_activ][j+1] = list_Dir_sel[j];
			window_content_Type[window_activ][j+1] = _DIRECTORY;
			window_content_Size[window_activ][j+1] = 0;
		}
		for(j=0; j<=File_N; j++) {
			strcpy(window_content_Name[window_activ][j+1+Folder_N+1], list_Fil[j]);
			window_content_Selected[window_activ][j+1+Folder_N+1] = list_Fil_sel[j];
			sprintf(temp, "%s/%s", window_path[window_activ], window_content_Name[window_activ][j+1+Folder_N+1]);
			window_content_Type[window_activ][j+1+Folder_N+1] = get_ext(temp);
			window_content_Size[window_activ][j+1+Folder_N+1] = list_Fil_siz[j];
			
		}
	} else {
		for(j=0; j<=File_N; j++) {
			strcpy(window_content_Name[window_activ][j+1], list_Fil[j]);
			window_content_Selected[window_activ][j+1] = list_Fil_sel[j];
			sprintf(temp, "%s/%s", window_path[window_activ], window_content_Name[window_activ][j+1]);
			window_content_Type[window_activ][j+1] = get_ext(temp);
			window_content_Size[window_activ][j+1] = list_Fil_siz[j];
		}
		for(j=0; j<=Folder_N; j++) {
			strcpy(window_content_Name[window_activ][j+1+File_N+1], list_Dir[j]);
			window_content_Selected[window_activ][j+1+File_N+1] = list_Dir_sel[j];
			window_content_Type[window_activ][j+1+File_N+1] = _DIRECTORY;
			window_content_Size[window_activ][j+1+File_N+1] = 0;
		}
	}
	
}

void Window(char *directory)
{
	int n;
	
	if(directory==NULL) {
		for(n=0; n<10; n++){
			if( window_open[n] == NO ) {
				window_open[n] = YES;
				break;
			}
			if(n==9) {
				show_msg("Error : 10 Windows MAX");
				return;
			}
		}
	
		window_x[n]=100+30*n;
		window_y[n]=30+30*n;
		window_h[n]=335;
		window_w[n]=500;
		strcpy(window_path[n], "/");
		
		int i;
		for(i=0; i<10; i++) {
			if(window_open[i] == YES && i != n) {
				window_z[i]++;
			}
		}
		
		window_z[n]=1;
		window_activ=n;
	} 
	else if( strcmp(directory, "..") == 0) {
		if(strcmp(window_path[window_activ], "/") == 0) return;
		char temp[255];
		strcpy(temp, window_path[window_activ]);
		temp[strrchr(temp, '/') - temp] = 0;
		memset(window_path[window_activ], 0, sizeof(window_path[window_activ]));
		strcpy(window_path[window_activ], temp);
		if(window_path[window_activ][0] == 0) window_path[window_activ][0] = '/';
	}
	else if(strcmp(directory, ".") == 0) {
		//refresh;
	}
	else {
		if(strcmp(window_path[window_activ], "/") != 0) {
			strcat(window_path[window_activ], "/");
		}
		strcat(window_path[window_activ], directory);
	}
	
	MountNTFS();
	
	window_content_N[window_activ]=-1;
	memset(window_content_Name[window_activ], 0, sizeof(window_content_Name[window_activ]));
	memset(window_content_Type[window_activ], 0, sizeof(window_content_Type[window_activ]));
	memset(window_content_Size[window_activ], 0, sizeof(window_content_Size[window_activ]));
	memset(window_content_Selected[window_activ], 0, sizeof(window_content_Selected[window_activ]));
	
	char temp[512];
	
	DIR *d;
	struct dirent *dir;
	
	d = opendir(window_path[window_activ]);
	if(d==NULL) return;
	
	while ((dir = readdir(d))) {
		if(strcmp(dir->d_name, ".")==0) continue;
		if(strcmp(dir->d_name, "..")==0) continue; // NTFS : added for all directories after
		if(!strncmp(dir->d_name, "$", 1)) continue; // NTFS : ignore system files
		
		if(window_content_N[window_activ] == MAX_ITEM) {
			show_msg("Too many files...");
			break;
		}
		window_content_N[window_activ]++;
		if(dir->d_type & DT_DIR) {
			window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
		} else {		
			if(strcmp(window_path[window_activ], "/") != 0) {
				sprintf(temp, "%s/%s", window_path[window_activ], dir->d_name);
				window_content_Size[window_activ][window_content_N[window_activ]] = get_size(temp, NO);
				window_content_Type[window_activ][window_content_N[window_activ]] = get_ext(temp);
			}
			else window_content_Type[window_activ][window_content_N[window_activ]] = get_ext(dir->d_name);
		}
		strcpy(window_content_Name[window_activ][window_content_N[window_activ]], dir->d_name);
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
				strcpy(window_content_Name[window_activ][window_content_N[window_activ]], temp);
			}
		}
	} else {
		window_content_N[window_activ]++;
		window_content_Type[window_activ][window_content_N[window_activ]]= _DIRECTORY;
		strcpy(window_content_Name[window_activ][window_content_N[window_activ]], "..");
	}
	
	sort();
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
		memset(prop_path, 0, sizeof(prop_path));
		memset(prop_type, 0, sizeof(prop_type));
		memset(prop_md5, 0, sizeof(prop_md5));
		memset(prop_sha1, 0, sizeof(prop_sha1));
	}
	
}

void Draw_properties()
{
	if(prop_activ == NO) return;
	
	SetFontZ(0);	
	SetFontSize(PROP_FONT, PROP_FONT);
	SetFontColor(BLACK, 0);
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO); // DARK 50%
	Draw_Box(PROP_X-2, PROP_Y-2, 0, 0, PROP_W+4, PROP_H+4, BLACK, NO); // BORDER
	Draw_Box(PROP_X, PROP_Y, 0, 0, PROP_W, PROP_H, 0xF0F0F0FF, NO);
	Draw_Box(PROP_X, PROP_Y, 0, 0, PROP_COL_W, PROP_H, 0xD4DBEDFF, NO);
	
	int prop_N=-1;
	
	prop_N++;
	DrawString(PROP_X+5, PROP_Y+PROP_FONT*prop_N, "Path");
	DrawString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, prop_path);
	
	prop_N++;
	DrawString(PROP_X+5, PROP_Y+PROP_FONT*prop_N, "Type");
	DrawString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, prop_type);
	
	prop_N++;
	DrawString(PROP_X+5, PROP_Y+PROP_FONT*prop_N, "File");
	DrawFormatString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, "%d", nb_file);
	
	prop_N++;
	DrawString(PROP_X+5, PROP_Y+PROP_FONT*prop_N, "Folder");
	DrawFormatString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, "%d", nb_directory);
	
	prop_N++;
	DrawString(PROP_X+5, PROP_Y+PROP_FONT*prop_N, "Size");
	char *prop_size_str = get_unit(total_size);
	DrawFormatString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, "%s (%llu bytes)", prop_size_str, total_size);
	free(prop_size_str);
	
	prop_N++;
	DrawString(PROP_X+5, PROP_Y+PROP_FONT*prop_N, "MD5");
	if(prop_md5[0] == 0) DrawString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, "-"); else
	DrawFormatString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, "%016llX%016llX", prop_md5[0], prop_md5[1]);
	
	prop_N++;
	DrawString(PROP_X+5, PROP_Y+PROP_FONT*prop_N, "SHA-1");
	if(prop_sha1[0] == 0) DrawString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, "-"); else
	DrawFormatString(PROP_X+PROP_COL_W+5, PROP_Y+PROP_FONT*prop_N, "%08lX%08lX%08lX%08lX%08lX", prop_sha1[0], prop_sha1[1], prop_sha1[2], prop_sha1[3], prop_sha1[4]);
}

void open_properties()
{
	total_size=0;
	nb_file=0;
	nb_directory=0;
	memset(prop_md5, 0, sizeof(prop_md5));
	memset(prop_sha1, 0, sizeof(prop_sha1));
	memset(prop_path, 0, sizeof(prop_path));
	memset(prop_type, 0, sizeof(prop_type));
	
	if(option_sel_N < 0) {
		start_loading();
		gathering=YES;
		get_size(window_path[window_activ], YES);
		gathering=NO;
		end_loading();
		
		strcpy(prop_type, "Directory");
		strcpy(prop_path, window_path[window_activ]);
		
	} else {
		int i;
		int is_fil=NO;
		int is_dir=NO;
		start_loading();
		gathering=YES;
		for(i=0; i<=option_sel_N; i++) {
			get_size(option_sel[i], YES);
			if(is_fil==NO) if(path_info(option_sel[i]) == _FILE) is_fil=YES;
			if(is_dir==NO) if(path_info(option_sel[i]) == _DIRECTORY) is_dir=YES;
		}
		gathering=NO;
		
		if(is_dir == YES && is_fil == YES) {
			strcpy(prop_type, "Multiple");
		} else
		if(is_dir == YES) {
			strcpy(prop_type, "Directory");
		} else
		if(is_fil == YES) {
			strcpy(prop_type, "File");
		}
		strcpy(prop_path, option_sel[0]);
		if(option_sel_N != 0) {
			prop_path[strrchr(prop_path, '/') - prop_path] = 0;
		}
		
		if(option_sel_N == 0 && is_fil == YES) {	
			print_head("Calculating MD5");
			md5_file(option_sel[0], (u8 *) prop_md5);
			if(cancel == NO) {
				print_head("Calculating SHA1");
				sha1_file(option_sel[0], (u8 *) prop_sha1);
			}
			if(cancel == YES) {
				memset(prop_md5, 0, sizeof(prop_md5));
				memset(prop_sha1, 0, sizeof(prop_sha1));
			}
		}
		end_loading();
	}
	
	while(GetWidth(prop_path) > PROP_W-PROP_COL_W-10) {
		prop_path[strlen(prop_path)-1]=0;
		prop_path[strlen(prop_path)-1]=0;
		prop_path[strlen(prop_path)-1]=0;
		prop_path[strlen(prop_path)-1]=0;
		prop_path[strlen(prop_path)]='.';
		prop_path[strlen(prop_path)]='.';
		prop_path[strlen(prop_path)]='.';
	}
	
	if(gathering_cancel==NO) {
		prop_activ = YES;
	}
	else {
		gathering_cancel=NO;
		total_size=0;
		nb_file= 0;
		nb_directory=0;
		memset(prop_path, 0, sizeof(prop_path));
		memset(prop_type, 0, sizeof(prop_type));
	}

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
					sprintf(FM_PIC_path, "%s/%s", window_path[window_activ], window_content_Name[window_activ][i]);
					Load_FM();
					break;
				}
			}
			if(strstr(FM_PIC_path, window_content_Name[window_activ][i]) != NULL) flag=YES;
		}
	}
	
	if(new_pad & BUTTON_LEFT) {	
		int flag=NO, i;
		for(i=window_content_N[window_activ]; i>0; i--) {
			if(flag==YES) {
				if(window_content_Type[window_activ][i] == _JPG || window_content_Type[window_activ][i] == _PNG) {
					sprintf(FM_PIC_path, "%s/%s", window_path[window_activ], window_content_Name[window_activ][i]);
					Load_FM();
					break;
				 }
			}
			if(strstr(FM_PIC_path, window_content_Name[window_activ][i]) != NULL) flag=YES;
		}
	}
	
	if(new_pad & BUTTON_CIRCLE)
	{
		picture_viewer_activ=NO;
		memset(FM_PIC_path, 0, sizeof(FM_PIC_path));
		FM_PIC_offset = 0;
	}
}

void Draw_picture_viewer()
{
	if(picture_viewer_activ == NO) return;	
	
	if(APNG_offset[0]!=0) {Draw_APNG(); return;}
	
	SetFontZ(0);
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO); // DARK 50%
	
	float xi, yi, wi, hi;
	
	if(FM_PIC_offset != 0 ) {
		tiny3d_SetTexture(0, FM_PIC_offset, FM_PIC.width, FM_PIC.height, FM_PIC.pitch, TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
		
		if( FM_PIC.width > 748) {
			wi = 748 ;
			hi = FM_PIC.height * 748 / FM_PIC.width;
		
		} else 
		if (FM_PIC.width > 412) {
			hi = 412;
			wi = FM_PIC.width * 412 / FM_PIC.height;
		} else {
			wi = FM_PIC.width;
			hi = FM_PIC.height;
		}
		xi = (848 - wi) / 2;
		yi = (512 - hi) / 2;
	
		Draw_Box(xi, yi, 0, 0, wi, hi, WHITE, YES);
	}
	
	Draw_Box(0, 460, 0, 0, 848, 20, BLACK, NO);
	SetFontColor(WHITE, 0);
	DrawStringFromCenterX(424, 462 , &strrchr(FM_PIC_path, '/')[1]);
	
}

void open_picture_viewer(char *pict_path)
{
	memset(FM_PIC_path, 0, sizeof(FM_PIC_path));
	
	strcpy(FM_PIC_path, pict_path);

	Load_FM();
	
	picture_viewer_activ = YES;
	
}

//**** txt viewer ****

#define TXT_W 708
#define TXT_H 372
#define TXT_X 70
#define TXT_Y 70

u64 txt_linpos;
u8 txt_scroll;

void nextLine()
{
	u64 i;
	float xt=TXT_X;
	for(i=txt_linpos; i < strlen(txt_viewer_content)-1; i++) {
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
	SetFontColor(font_color, 0);
	float xt = x;
	float yt = y;
	u64 i, j;
	
	for(i=0; i < strlen(txt); i++) {
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
		
		if(yt > y+h) return;
		
		xt = DrawFormatString(xt, yt, "%c", txt[i]);
	}
	
}

void txt_viewer_input()
{
	if(txt_viewer_activ == NO) return;
		
	if((old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_R2) {
		scroll_speed = 6 - paddata.PRE_R2/50;
	} else scroll_speed = 6;
	
	if( ((new_pad & BUTTON_DOWN) || ((old_pad & BUTTON_DOWN) && slow_it==0)) && txt_scroll == YES )
	{
		nextLine();
	}
	if(  ((new_pad & BUTTON_UP) || ((old_pad & BUTTON_UP) && slow_it==0)) && txt_scroll == YES)
	{
		prevLine();
	}
	
	if(new_pad & BUTTON_CIRCLE)
	{
		txt_viewer_activ=NO;
		free(txt_viewer_content);
	}

}

void Draw_txt_viewer()
{
	if(txt_viewer_activ == NO) return;	
	
	SetFontZ(0);
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO); // DARK 50%
	Draw_Box(TXT_X-20-5 , TXT_Y-20-5 , 0, 0, TXT_W+40+10 , TXT_H+40+10 , BLACK, NO); // Black Border
	Draw_Box(TXT_X-20   , TXT_Y-20   , 0, 0, TXT_W+40	, TXT_H+40	, WHITE, NO); // White Border

	DrawTXTInBox(TXT_X, TXT_Y, 0, TXT_W, TXT_H, &txt_viewer_content[txt_linpos], WHITE, BLACK);
}

void open_txt_viewer(char *txt_path)
{
	size_t size;
	FILE *f;
	
	txt_linpos=0;
	txt_scroll=YES;
	
	f=fopen(txt_path, "rb");
	if(f==NULL) return;
	
	fseek (f , 0 , SEEK_END);
	size = ftell (f);
	fseek(f, 0, SEEK_SET);

	txt_viewer_content = (char*) malloc (sizeof(char)*size);
	memset(txt_viewer_content, 0, size);
	
	fread(txt_viewer_content, 1, size, f);
	
	fclose (f);
	
	txt_viewer_activ = YES;
	
}

//**** SFO viewer ****

#define SFO_MAGIC				0x00505346
#define SFO_DATA_TYPE_UTF8S		0x004
#define SFO_DATA_TYPE_UTF8		0x204
#define SFO_DATA_TYPE_INT32		0x404

#define ES16(x)		(((x) & 0xFF) << 8 | ((x) & 0xFF00) >> 8)
#define ES32(x)		(((x) & 0xFF) << 24 | ((x) & 0xFF00) << 8 | ((x) & 0xFF0000) >> 8 | ((x) & 0xFF000000) >> 24)
#define ES(x)		(sizeof(x) == 2 ? ES16(x) : ES32(x))

char SFO_KEY[128][64];
char SFO_DATA[128][512];
u8 SFO_viewer_activ;
u8 SFO_NB;

#define SFO_FONT	20		
#define SFO_W		800
#define SFO_COL2_W	SFO_W-SFO_COL1_W
#define SFO_X		848/2-SFO_W/2

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
	FILE *sfo;
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
	SetFontSize(SFO_FONT, SFO_FONT);
	SetFontColor(BLACK, 0);
	
	int SFO_COL1_W=0;
	int SFO_H=SFO_FONT*SFO_NB;
	int SFO_Y=512/2-SFO_H/2;
	int x=0;
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
	
	if(strcmp(item, "New Folder") == 0) {
		sprintf(temp, "%s/New_Folder", window_path[window_activ]);
		if(path_info(temp) != _NOT_EXIST) {
			for(i=0; i<10; i++) {
				sprintf(temp, "%s/New_Folder_%d", window_path[window_activ], i);
				if(path_info(temp) == _NOT_EXIST) break;
				if(i==9) {
					show_msg("Error!");
					return;
				}
			}
		}
		ret = mkdir(temp, 0777);
		if(ret  != 0 ) {
			sprintf(temp, "Error : 0x%X", ret);
			show_msg(temp);
		}
	} else
	if(strcmp(item, "New File") == 0) {
		sprintf(temp, "%s/New_File.txt", window_path[window_activ]);
		if(path_info(temp) != _NOT_EXIST) {
			for(i=0; i<10; i++) {
				sprintf(temp, "%s/New_File_%d.txt", window_path[window_activ], i);
				if(path_info(temp) == _NOT_EXIST) break;
				if(i==9) {
					show_msg("Error!");
					return;
				}
			}
		}
		FILE *f;
		f = fopen(temp, "wb");
		if(f==NULL) {
			sprintf(temp, "Error : 0x%X", ret);
			show_msg(temp);
			option_activ=NO;
			return;
		}
		fclose(f);
	} else
	if(strcmp(item, "Paste") == 0) {
		start_copy_loading();
		gathering=YES;
		for(i=0; i<=option_copy_N; i++){
			get_size(option_copy[i], YES);
		}
		gathering=NO;
		for(i=0; i<=option_copy_N; i++) {
			strcpy(copy_src, option_copy[i]);
			sprintf(copy_dst, "%s%s", window_path[window_activ], strrchr(copy_src, '/'));
			
			if(option_cut == YES) Move(copy_src, copy_dst); else 
			Copy(copy_src, copy_dst);	
		}
		end_copy_loading();
		memset(option_copy, 0, sizeof(option_copy));
		option_copy_N=-1;
	} else
	if(strcmp(item, "Copy") == 0) {
		memset(option_copy, 0, sizeof(option_copy));
		for(i=0; i<=option_sel_N; i++) {
			strcpy(option_copy[i], option_sel[i]);
		}
		option_copy_N = option_sel_N;
		option_cut = NO;
	} else
	if(strcmp(item, "Cut") == 0) {
		memset(option_copy, 0, sizeof(option_copy));
		for(i=0; i<=option_sel_N; i++) {
			strcpy(option_copy[i], option_sel[i]);
		}
		option_copy_N = option_sel_N;
		option_cut = YES;
	} else
	if(strcmp(item, "Delete") == 0) {
		start_loading();
		for(i=0; i<=option_sel_N; i++) {
			Delete(option_sel[i]);
		}
		end_loading();
	} else
	if(strcmp(item, "Unselect all") == 0) {
		//refresh
	} else
	if(strcmp(item, "Select all") == 0) {
		for(i=0; i<=window_content_N[window_activ]; i++) {
			if(strcmp(window_content_Name[window_activ][i], "..") == 0) {
				window_content_Selected[window_activ][i] = NO;
			} else window_content_Selected[window_activ][i] = YES;
		}
		option_activ=NO;
		return; //avoid refresh
	} else
	if(strcmp(item, "Rename") == 0) {
		char New_Name[255];
		strcpy(New_Name, &strrchr(option_sel[0], '/')[1]);
		if(Get_OSK_String("Rename", New_Name, 255) == SUCCESS) {
			if(New_Name[0] != 0) {
				char New_Path[512];
				sprintf(New_Path, "%s/%s", window_path[window_activ], New_Name);
				rename(option_sel[0], New_Path);
			}
		}
	} else
	if(strcmp(item, "Open New Window")==0) {
		Window(NULL);
	} else
	if(strcmp(item, "Refresh")==0) {
		//Window(".");
	} else
	if(strcmp(item, "Mount /dev_blind")==0) {
		sys_fs_mount("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_FAT", "/dev_blind", 0);
	} else
	if(strcmp(item, "Properties") == 0) {
		open_properties();
	} else
	if(strcmp(item, "View") == 0) {
		open_picture_viewer(option_sel[0]);
	} else
	if(strcmp(item, "View TXT") == 0) {
		open_txt_viewer(option_sel[0]);
	} else
	if(strcmp(item, "View SFO") == 0) {
		start_loading();
		open_SFO_viewer(option_sel[0]);
		end_loading();
	} else
	if(strcmp(item, "Extract ELF") == 0) {
		start_loading();
		char elf[255];
		strcpy(elf, option_sel[0]);	
		strtok(elf, ".");
		strcat(elf, ".elf");
		
		if( path_info(elf) != _NOT_EXIST) Delete(elf);
		
		if(Extract(option_sel[0], elf)==FAILED) {
			print_load("Error : Failed to extract");
		}
		end_loading();
	} else
	if(strcmp(item, "Resign SELF") == 0) {
		start_loading();
		re_sign_SELF(option_sel[0]);
		end_loading();
	} else
	if(strcmp(item, "Launch SELF") == 0) {
		sysProcessExitSpawn2(option_sel[0], NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_64K);
	} else
	if(strcmp(item, "Extract EBOOT") == 0) {
		start_loading();
		char elf[255];
		strcpy(elf, option_sel[0]);	
		strtok(elf, ".");
		strcat(elf, ".ELF");
		
		if( path_info(elf) != _NOT_EXIST) Delete(elf);
		
		if(Extract(option_sel[0], elf)==FAILED) {
			print_load("Error : Failed to extract");
		}
		end_loading();
	} else
	if(strcmp(item, "Resign EBOOT") == 0) {
		start_loading();
		re_sign_EBOOT(option_sel[0]);
		end_loading();
	} else
	if(strcmp(item, "Launch EBOOT") == 0) {
		sysProcessExitSpawn2(option_sel[0], NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_64K);
	} else
	if(strcmp(item, "Sign EBOOT") == 0) {
		start_loading();
		char BIN[255];
		strcpy(BIN, option_sel[0]);	
		strtok(BIN, ".");
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
	} else
	if(strcmp(item, "Sign ELF") == 0) {
		start_loading();
		char SELF[255];
		strcpy(SELF, option_sel[0]);	
		strtok(SELF, ".");
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
	} else
	if(strcmp(item, "Extract PRX") == 0) {
		start_loading();
		char prx[255];
		strcpy(prx, option_sel[0]);	
		strtok(prx, ".");
		strcat(prx, ".prx");
		if( path_info(prx) != _NOT_EXIST) Delete(prx);
		if(Extract(option_sel[0], prx)==FAILED) {
			print_load("Error : Failed to extract");
		}
		end_loading();
	} else
	if(strcmp(item, "Resign SPRX") == 0) {
		start_loading();
		re_sign_SPRX(option_sel[0]);
		end_loading();
	} else
	if(strcmp(item, "Sign PRX") == 0) {
		start_loading();
		
		char SPRX[255];
		strcpy(SPRX, option_sel[0]);	
		strtok(SPRX, ".");
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
	} else
	if(strcmp(item, "Check files (IRD)") == 0) {
		start_loading();
		if ( CheckIRD(option_sel[0]) == SUCCESS) {
			sprintf(temp, "%s/MD5_check.txt", option_sel[0]);
			open_txt_viewer(temp);
		}
		end_loading();
	} else
	if(strcmp(item, "Extract PKG") == 0) {
		start_loading();
		pkg_unpack(option_sel[0], NULL);
		end_loading();
	} else
	if(strcmp(item, "PKG info") == 0) {
		start_loading();
		i=pkg_list(option_sel[0]);
		end_loading();
		if(i==SUCCESS) open_txt_viewer("/dev_hdd0/tmp/pkg_list.txt");
	} else
	if(strcmp(item, "Make PKG") == 0) {
		start_loading();
		make_pkg(option_sel[0]);
		end_loading();
	} else
	if(strcmp(item, "Remove from PRX Loader") == 0) {
		remove_from_list("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, "Add to PRX Loader") == 0) {
		add_to_list("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt", option_sel[0]);
	}  else
	if(strcmp(item, "Remove from PRXLoader") == 0) {
		remove_from_list("/dev_hdd0/prx_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, "Add to PRXLoader") == 0) {
		add_to_list("/dev_hdd0/prx_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, "Remove from Mamba list") == 0) {
		remove_from_list("/dev_hdd0/mamba_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, "Add to Mamba list") == 0) {
		add_to_list("/dev_hdd0/mamba_plugins.txt", option_sel[0]);
	}  else
	if(strcmp(item, "Remove from Cobra list") == 0) {
		remove_from_list("/dev_hdd0/boot_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, "Add to Cobra list") == 0) {
		add_to_list("/dev_hdd0/boot_plugins.txt", option_sel[0]);
	} else
	if(strcmp(item, "Dump lv2") == 0) {
		start_loading();
		dump_lv2("/dev_hdd0/LV2.BIN");
		end_loading();
	} else
	if(strcmp(item, "Dump lv1") == 0) {
		start_loading();
		dump_lv1("/dev_hdd0/LV1.BIN");
		end_loading();
	} else
	if(strcmp(item, "Dump flash") == 0) {
		start_loading();
		dump_flash("/dev_hdd0/FLASH.BIN");
		end_loading();
	} else
	if(strcmp(item, "Extract TRP") == 0) {
		start_loading();
		trophy_extract(option_sel[0]);
		end_loading();
	} else
	if(strcmp(item, "Get MD5") == 0) {
		start_loading();
		HashFolder(MD5_HASH, option_sel[0]);
		if(cancel == NO) {
			char temp[255];
			sprintf(temp, "%s/content.md5", option_sel[0]);
			open_txt_viewer(temp);
		}
		end_loading();
	} else
	if(strcmp(item, "Get SHA1") == 0) {
		start_loading();
		HashFolder(SHA1_HASH, option_sel[0]);
		if(cancel == NO) {
			char temp[255];
			sprintf(temp, "%s/content.sha1", option_sel[0]);
			open_txt_viewer(temp);
		}
		end_loading();
	} else 
	if(strcmp(item, "Check CRC32") == 0) {
		start_loading();
		if(CheckCRC32(option_sel[0]) == SUCCESS) {
			char temp[255];
			strcpy(temp, option_sel[0]);
			temp[strlen(temp)-4]=0;
			strcat(temp, "_CHECK.crc");
			open_txt_viewer(temp);
		}
		end_loading();
	} else
	if(strcmp(item, "Check MD5") == 0) {
		start_loading();
		if(CheckMD5(option_sel[0]) == SUCCESS) {
			char temp[255];
			strcpy(temp, option_sel[0]);
			temp[strlen(temp)-4]=0;
			strcat(temp, "_CHECK.md5");
			open_txt_viewer(temp);
		}
		end_loading();
	} else
	if(strcmp(item, "Extract RCO") == 0) {
		start_loading();
		print_head("Extracting RCO");
		rco_dump(option_sel[0]);
		end_loading();
	} else 
	if(strcmp(item, "Extract ISO") == 0) {
		start_loading();
		print_head("Extracting ISO...");
		
		u8 split = is_usb(option_sel[0]);
		char dst[255];
		strcpy(dst, option_sel[0]);
		if(strstr(dst, ".iso.0") || strstr(dst, ".ISO.0")) dst[strlen(dst)-6]=0; 
		else dst[strlen(dst)-4]=0;
		
		extractps3iso(option_sel[0], dst, split);
		
		end_loading();
	} else
	if(strcmp(item, "Compress ISO") == 0) {
		start_loading();
		print_head("Compressing ISO...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='C';
		dst[strlen(dst)-2]='S';
		dst[strlen(dst)-1]='O';
		if(comp_ciso(option_sel[0], dst, 1)==FAILED) Delete(dst);
		end_loading();
	} else
	if(strcmp(item, "Decompress CSO") == 0) {
		start_loading();
		print_head("Decompressing CSO...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='I';
		dst[strlen(dst)-2]='S';
		dst[strlen(dst)-1]='O';
		if(decomp_ciso(option_sel[0], dst)==FAILED) Delete(dst);
		end_loading();
	}
	else 
	if(strcmp(item, "Extract THM") == 0) {
		start_loading();
		print_head("Extracting THM...");
		ExtractTHM(option_sel[0]);
		end_loading();
	}
	else 
	if(strcmp(item, "Extract P3T") == 0) {
		start_loading();
		print_head("Extracting P3T...");
		cxml_extract(option_sel[0]);
		end_loading();
	}
	else 
	if(strcmp(item, "Extract RAF") == 0) {
		start_loading();
		print_head("Extracting RAF...");
		cxml_extract(option_sel[0]);
		end_loading();
	}
	else 
	if(strcmp(item, "Extract QRC") == 0) {
		start_loading();
		print_head("Extracting QRC...");
		ExtractQRC(option_sel[0]);
		end_loading();
	}
	else
	if(strcmp(item, "Convert GTF to DDS") == 0) {
		start_loading();
		print_head("Converting to DDS...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='d';
		dst[strlen(dst)-2]='d';
		dst[strlen(dst)-1]='s';
		gtf2dds(option_sel[0], dst, 0, 0);
		end_loading();
	}
	else 
	if(strcmp(item, "Convert VAG to WAV") == 0) {
		start_loading();
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='w';
		dst[strlen(dst)-2]='a';
		dst[strlen(dst)-1]='v';
		print_head("Converting to wav...");
		VAG2WAV(option_sel[0], dst);
		end_loading();
	}
	else 
	if(strcmp(item, "Convert JSX to JS") == 0) {
		start_loading();
		print_head("Converting to JS...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-1]=0;
		JSX2JS(option_sel[0], dst);
		end_loading();
	}
	else 
	if(strcmp(item, "Convert DDS to PNG") == 0) { 
		start_loading();
		print_head("Converting to PNG...");
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strlen(dst)-3]='p';
		dst[strlen(dst)-2]='n';
		dst[strlen(dst)-1]='g';
		ConvertImage(option_sel[0], dst);
		end_loading();
	}
	else
	if(strcmp(item, "Make APNG") == 0) { 
		start_loading();
		char dst[255];
		strcpy(dst, option_sel[0]);
		dst[strrchr(dst, '/') - dst] = 0;
		strcat(dst, "/Animated.png\0");
		Build_APNG(option_sel, option_sel_N, dst, 0);
		end_loading();
	}
	else 
	if(strcmp(item, "Read xReg") == 0) { 
		start_loading();
		if( xreg2txt(option_sel[0], "/dev_hdd0/tmp/xreg.txt") == SUCCESS ) 
			open_txt_viewer("/dev_hdd0/tmp/xreg.txt");
		end_loading();
	}
	else
	if(strcmp(item, "Set permission") == 0) { 
		start_loading();
		print_head("Setting permission to 0777...");
		SetPerms(option_sel[0]);
		end_loading();
	}
	else
	if(strcmp(item, "Extract ZIP") == 0) { 
		start_loading();
		print_head("Extracting ZIP");
		ExtractZip(option_sel[0]);
		end_loading();
	}
	
	Window(".");
	option_activ=NO;
}

void Open_option()
{
	option_item_N = -1;
	option_sel_N = -1;
	memset(option_item, 0, sizeof(option_item));
	memset(option_sel, 0, sizeof(option_sel));
	int i;
	
	if(window_activ == -1) {
		option_item_N++;
		strcpy( option_item[option_item_N] , "Open New Window");
	}
	else if(strcmp( window_path[window_activ], "/") == 0) {
		option_item_N++;
		strcpy( option_item[option_item_N] , "Open New Window");
		option_item_N++;
		strcpy( option_item[option_item_N] , "Mount /dev_blind");
		option_item_N++;
		strcpy( option_item[option_item_N] , "Dump lv1");
		option_item_N++;
		strcpy( option_item[option_item_N] , "Dump lv2");
		option_item_N++;
		strcpy( option_item[option_item_N] , "Dump flash");
	}
	else {
		u8 all_is_dir=YES;
		int all_same_ext=-1;
		for(i=0; i<=window_content_N[window_activ]; i++) {
			if(window_content_Selected[window_activ][i] == YES) {
				option_sel_N++;
				sprintf(option_sel[option_sel_N], "%s/%s", window_path[window_activ], window_content_Name[window_activ][i]);
				if(path_info(option_sel[option_sel_N]) != _DIRECTORY) all_is_dir=NO;
				if(all_same_ext != -2) {
					if(all_same_ext == -1) all_same_ext = get_ext(option_sel[option_sel_N]); else
					if(all_same_ext != get_ext(option_sel[option_sel_N])) all_same_ext = -2;
				}
			}
		}
		option_item_N++;
		strcpy( option_item[option_item_N] , "Refresh");
		option_item_N++;
		strcpy( option_item[option_item_N] , "New Folder");
		option_item_N++;		
		strcpy( option_item[option_item_N] , "New File");
		if(0 <= option_copy_N) {
			option_item_N++;
			strcpy( option_item[option_item_N] , "Paste");
		}
		if(0 <= option_sel_N) {
			option_item_N++;
			strcpy(option_item[option_item_N] , "Copy");
			option_item_N++;
			strcpy( option_item[option_item_N] , "Cut");
			option_item_N++;
			strcpy( option_item[option_item_N] , "Delete");
			option_item_N++;
			strcpy( option_item[option_item_N] , "Unselect all");
		}																									
		option_item_N++;
		strcpy( option_item[option_item_N] , "Select all");
		
		if(option_sel_N == 0) {
			option_item_N++;
			strcpy( option_item[option_item_N] , "Rename");
			
			if(path_info(option_sel[0]) == _DIRECTORY ) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Make PKG");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Get MD5");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Get SHA1");				
			}
			
			u8 ext = get_ext(option_sel[0]);
			
			if(ext == _JPG || ext == _PNG) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "View");
			} else 
			if( can_read(ext) == YES) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "View TXT");
			} else
			if(ext == _SFO) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "View SFO");
			} else
			if(ext == _XREG) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Read xReg");
			} else
			if(ext == _SELF) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract ELF");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Resign SELF");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Launch SELF");
			} else 
			if(ext == _EBOOT_BIN) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract EBOOT");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Resign EBOOT");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Launch EBOOT");
			} else 
			if(ext == _EBOOT_ELF) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Sign EBOOT");
			} else 
			if(ext == _ELF) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Sign ELF");
			}  else 
			if(ext == _SPRX) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract PRX");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Resign SPRX");
				
				if(path_info("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt") != _NOT_EXIST) {
					if(is_it_inside("/dev_hdd0/game/PRXLOADER/USRDIR/plugins.txt", option_sel[0]) == YES) {
						option_item_N++;
						strcpy( option_item[option_item_N] , "Remove from PRX Loader");
					} else {
						option_item_N++;
						strcpy( option_item[option_item_N] , "Add to PRX Loader");
					}					
				}
				
				if(path_info("/dev_hdd0/prx_plugins.txt") != _NOT_EXIST) {
					if(is_it_inside("/dev_hdd0/prx_plugins.txt", option_sel[0]) == YES) {
						option_item_N++;
						strcpy( option_item[option_item_N] , "Remove from PRXLoader");
					} else {
						option_item_N++;
						strcpy( option_item[option_item_N] , "Add to PRXLoader");
					}					
				}
				
				
				if(path_info("/dev_hdd0/mamba_plugins.txt") != _NOT_EXIST) {
					if(is_it_inside("/dev_hdd0/mamba_plugins.txt", option_sel[0]) == YES) {
						option_item_N++;
						strcpy( option_item[option_item_N] , "Remove from Mamba list");
					} else {
						option_item_N++;
						strcpy( option_item[option_item_N] , "Add to Mamba list");
					}
				}
				
				if(path_info("/dev_hdd0/boot_plugins.txt") != _NOT_EXIST) {
					if(is_it_inside("/dev_hdd0/boot_plugins.txt", option_sel[0]) == YES) {
						option_item_N++;
						strcpy( option_item[option_item_N] , "Remove from Cobra list");
					} else {
						option_item_N++;
						strcpy( option_item[option_item_N] , "Add to Cobra list");
					}
				}
			} else 
			if(ext == _PRX) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Sign PRX");
			} else
			if(ext == _RCO) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract RCO");
			} else 
			if(ext == _PKG) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract PKG");
				option_item_N++;
				strcpy( option_item[option_item_N] , "PKG info");
			} else
			if(ext == _TRP) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract TRP");
			} else
			if(ext == _ISO_PS1 || ext == _ISO_PS2) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Check MD5");
			} else
			if(ext == _ISO_PS3) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract ISO");
			} else
			if(ext == _JB_PS3) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Check files (IRD)");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Compress ISO");
			} else
			if(ext == _ISO_PSP) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Compress ISO");
				option_item_N++;
				strcpy( option_item[option_item_N] , "Check CRC32");
			} else
			if(ext == _CSO) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Decompress CSO");
			} else
			if(ext == _THM) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract THM");
			} else
			if(ext == _P3T) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract P3T");
			} else
			if(ext == _RAF) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract RAF");
			} else
			if(ext == _QRC) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract QRC");
			} else
			if(ext == _JSX) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Convert JSX to JS");
			} else
			if(ext == _VAG) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Convert VAG to WAV");
			} else
			if(ext == _GTF) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Convert GTF to DDS");
			} else
			if(ext == _DDS) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Convert DDS to PNG");
			} else
			if(ext == _ZIP) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Extract ZIP");
			}
			
		}
		
		if(all_same_ext >= 0 && option_sel_N > 0) {
			if(all_same_ext == _PNG) {
				option_item_N++;
				strcpy( option_item[option_item_N] , "Make APNG");
			}
		}
		
		option_item_N++;
		strcpy( option_item[option_item_N] , "Set permission");
		option_item_N++;
		strcpy(option_item[option_item_N] , "Properties");
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
	
	SetFontColor(BLACK, 0);
	Draw_Box(option_x-1, option_y-1, 0, 0, option_w+2, option_h+2, BLACK, NO); // BORDER
	Draw_Box(option_x, option_y, 0, 0, option_w, option_h, 0xF0F0F0FF, NO);
	SetFontSize(15, 15);
	SetFontZ(0);
	
	int i;
	for(i=0; i<=option_item_N;i++) {
		if(option_x 	 < curs_x && curs_x < option_x+option_w
		&& option_y+15*i < curs_y && curs_y < option_y+15*(i+1)) {
			SetFontColor(GREEN, 0);
			Draw_Box(option_x, option_y+15*i, 0, 0, option_w, 15, 0x00D0FFFF, NO);
		} else SetFontColor(BLACK, 0);
		
		DrawString(option_x+5, option_y+15*i, option_item[i]);
	}
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
		// cancel
		else {
			option_activ = NO;
		}
	}
	
	if((new_pad & BUTTON_TRIANGLE) || (new_pad & BUTTON_CIRCLE))  {
		option_activ = NO;
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

u8 window_input()
{
	int i;
	int k;
	
	if(option_activ == YES) return CONTINUE;
	if(prop_activ == YES) return CONTINUE;
	if(picture_viewer_activ == YES) return CONTINUE;
	if(txt_viewer_activ == YES) return CONTINUE;
	if(SFO_viewer_activ == YES) return CONTINUE;
	
	//R3 Grid_move window
	window_x[window_activ] += (paddata.button[4] - 128)/30;
	window_y[window_activ] += (paddata.button[5] - 128)/30;
	if(window_x[window_activ] + window_w[window_activ] > 848 ) window_x[window_activ]=848-window_w[window_activ];
	if(window_x[window_activ] < 0 ) window_x[window_activ]=0;
	if(window_y[window_activ] + window_h[window_activ] > 512 ) window_y[window_activ]=512-window_h[window_activ];
	if(window_y[window_activ] < 0 ) window_y[window_activ]=0;
	
	//SELECT ITEM
	if((new_pad & BUTTON_SQUARE) && 0 <= window_activ) {
		if(	window_x[window_activ] < curs_x && curs_x < (window_x[window_activ] + window_w[window_activ])
		&& 	window_y[window_activ] < curs_y && curs_y < (window_y[window_activ] + window_h[window_activ])   )
		{
			for(i=0 ; i < window_item_N[window_activ]; i++) {
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
	
	// 'MOUSE CLICK'
	if((new_pad & BUTTON_CROSS) && 0 <= window_activ) {
		//Cursor on activ window
		if(	window_x[window_activ] < curs_x && curs_x < (window_x[window_activ] + window_w[window_activ])
		&& 	window_y[window_activ] < curs_y && curs_y < (window_y[window_activ] + window_h[window_activ])   )
		{
			// browse
			for(i=0 ; i<window_item_N[window_activ]; i++) {
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
					}
				}
			}
			
			// Close
			if( window_x[window_activ]+window_w[window_activ]-10-30 < curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-10
			&&  window_y[window_activ]+10						 	< curs_y && curs_y < window_y[window_activ]+10+20 )
			{
				window_open[window_activ] = NO;
				window_activ=-1;
				for(i=0; i<10; i++) {
					if(window_open[i] == NO) continue;
					if(window_activ==-1) window_activ=i; else
					if(window_z[window_activ] > window_z[window_activ]) window_activ=i; 
				}
				if(window_activ != -1) {
					window_z[window_activ] = 1;
					for(i=0; i<10; i++) {
						if(window_open[i] == NO) continue;
						if(i==window_activ) continue;
						window_z[i]++;
					}
				}
			}

			// scroll
			if(window_scroll_N[window_activ]>0) {
				if( window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W < curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-BORDER ) {	
					if(window_y[window_activ]+TOP_H+COL_H+window_scroll_y[window_activ]+window_scroll_size[window_activ] < curs_y && curs_y < window_y[window_activ]+window_h[window_activ]-BORDER) {
						if(window_scroll_P[window_activ] < window_scroll_N[window_activ]) window_scroll_P[window_activ]++;
					}
					if(window_y[window_activ]+TOP_H+COL_H < curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H+window_scroll_y[window_activ]) {
						if(window_scroll_P[window_activ]>0) window_scroll_P[window_activ]--;
					}
				}
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
	
	if(old_pad & BUTTON_CROSS) curs_push = YES;
	else curs_push = NO;
	
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
	if(window_scroll_N[window_activ]>0) {
		if( window_x[window_activ]+window_w[window_activ]-BORDER-SCROLL_W < curs_x && curs_x < window_x[window_activ]+window_w[window_activ]-BORDER
		&&  window_y[window_activ]+TOP_H+COL_H+window_scroll_y[window_activ] < curs_y && curs_y < window_y[window_activ]+TOP_H+COL_H+window_scroll_y[window_activ]+window_scroll_size[window_activ] )
		{
			if(curs_push==YES && (( curs_move_y < 0 && window_scroll_P[window_activ] > 0) || ( curs_move_y > 0 && window_scroll_P[window_activ] < window_scroll_N[window_activ]))) {
				
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
		}
	}
	
	//Close Window  && Back to MGZ
	if(new_pad & BUTTON_R3) {
		if(window_activ==-1) {
			return BREAK;
		}
		else {
			window_open[window_activ] = NO;
			window_activ=-1;
			for(i=0; i<10; i++) {
				if(window_open[i] == NO) continue;
				if(window_activ==-1) window_activ=i; else
				if(window_z[window_activ] > window_z[window_activ]) window_activ=i; 
			}
			if(window_activ != -1) {
				window_z[window_activ] = 1;
				for(i=0; i<10; i++) {
					if(window_open[i] == NO) continue;
					if(i==window_activ) continue;
					window_z[i]++;
				}
			}
		}
	}
	
	//refresh L3
	if(new_pad & BUTTON_L3) {
		Window(".");
	}

	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_R2) {
		scroll_speed = 6 - paddata.PRE_R2/50;
	} else scroll_speed = 6;

	//Grid_move up scroll
	if(((new_pad & BUTTON_UP) || ((old_pad & BUTTON_UP) && slow_it==0)) && 0 <= window_activ ) {
		if(window_scroll_P[window_activ] >0) window_scroll_P[window_activ]--;
	}
	
	//Grid_move down scroll
	if(((new_pad & BUTTON_DOWN) || ((old_pad & BUTTON_DOWN) && slow_it==0)) && 0 <= window_activ ) {
		if(window_scroll_N[window_activ] != 0)
		if(window_scroll_P[window_activ] < window_scroll_N[window_activ]) window_scroll_P[window_activ]++;
	}
	
	//Parent directory
	if(new_pad & BUTTON_LEFT) {
		Window("..");
	}
	
	// OPTIONS
	if((new_pad & BUTTON_TRIANGLE) || (new_pad & BUTTON_CIRCLE))  {
		Open_option();
	}
	
	// New window
	if(new_pad & BUTTON_SELECT) {
		Window(NULL);
	}

	return CONTINUE;
}

void Draw_input()
{
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	if(option_activ == NO 
	&& prop_activ == NO 
	&& picture_viewer_activ == NO 
	&& txt_viewer_activ == NO
	&& SFO_viewer_activ == NO) {
		x=DrawButton(x, y, "Open", BUTTON_SELECT);
		x=DrawButton(x, y, "Refresh", BUTTON_L3);
		if(window_activ==-1) x=DrawButton(x, y, "Back", BUTTON_R3);	else
		x=DrawButton(x, y, "Close", BUTTON_R3);
		x=DrawButton(x, y, "Click", BUTTON_CROSS);
		x=DrawButton(x, y, "Option", BUTTON_CIRCLE);
		x=DrawButton(x, y, "Select", BUTTON_SQUARE);
		x=DrawButton(x, y, "Scroll", BUTTON_UP | BUTTON_DOWN);
		x=DrawButton(x, y, "Cursor", BUTTON_L);
		x=DrawButton(x, y, "Window", BUTTON_R);
		
	} else
	if(option_activ == YES)	{
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
		x=DrawButton(x, y, "Click", BUTTON_CROSS);
		x=DrawButton(x, y, "Cursor", BUTTON_L);
	} else
	if(prop_activ == YES || SFO_viewer_activ == YES)	{
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	} else
	if(txt_viewer_activ == YES){
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
		x=DrawButton(x, y, "Scroll", BUTTON_UP | BUTTON_DOWN);
	} else
	if(picture_viewer_activ == YES) {
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
		x=DrawButton(x, y, "Previous", BUTTON_LEFT);
		x=DrawButton(x, y, "Next", BUTTON_RIGHT);
	}
}

void Draw_FileExplorer(char *path)
{
	
	Window(NULL);
	
	if(path!=NULL) Window(path);
	
	while(1)
	{
		scene = SCENE_FILEMANAGER;
		
		cls();
		
		Draw_BGS();
		Draw_window();
		Draw_option();
		Draw_properties();
		Draw_picture_viewer();
		Draw_txt_viewer();
		Draw_SFO_viewer();
		Draw_Notification();
		Draw_input();
		Draw_cursor();
		
		tiny3d_Flip();
		
		ps3pad_read();
		
		cursor_input();
		if(	option_input() == OFF)
		if( window_input() == BREAK) break;
		
		properties_input();
		picture_viewer_input();
		txt_viewer_input();
		SFO_viewer_input();
	}

}

//*******************************************************
// MENU
//*******************************************************

void init_MENU()
{
	int i;
	
	memset(ITEMS, 0, sizeof(ITEMS));
	memset(ITEMS_VALUE, 0, sizeof(ITEMS_VALUE));
	
	ITEMS_NUMBER = -1;
	for(i=0; i<MAX_ITEMS; i++) ITEMS_VALUE_NUMBER[i]=-1;
	
	memset(ITEMS_VALUE_SHOW, 0, sizeof(ITEMS_VALUE_SHOW));
	memset(ITEMS_TYPE, 0, sizeof(ITEMS_TYPE));
		
	memset(TITLES, 0, sizeof(TITLES));
	
	MENU_COLUMN_ITEMS_NUMBER=-1;
	MENU_COLUMN_ITEMS_W = 200;
	
}

void add_item_MENU(char *str, u8 type)
{
	ITEMS_NUMBER++;
	strcpy(ITEMS[ITEMS_NUMBER], str);
	ITEMS_TYPE[ITEMS_NUMBER]=type;
	
	if(type==ITEM_CHECKBOX) ITEMS_VALUE_NUMBER[ITEMS_NUMBER] = 1;
}

void add_item_value_MENU(char *str)
{
	ITEMS_VALUE_NUMBER[ITEMS_NUMBER]++;
	strcpy(ITEMS_VALUE[ITEMS_NUMBER][ITEMS_VALUE_NUMBER[ITEMS_NUMBER]], str);
}

void add_title_MENU(char *str)
{
	strcpy(TITLES[ITEMS_NUMBER+1], str);
}

u8 item_is(char *str)
{
	if(strcmp(ITEMS[ITEMS_POSITION], str) == 0) return YES;
	
	return NO;
}

u8 item_value_is(char *str)
{
	if(strcmp(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], str) == 0 ) return YES;

	return NO;
}

void Draw_MENU()
{
	if(MENU == NO) return;
	
	int x1, x2, y=40, y1, i;
	
	y1=y;
	
	SetFontSize(15, 15);
	SetFontZ(0);
	
	if(MENU_SIDE == NO) {
		MENU_ITEMS_X = 50;
		MENU_ITEMS_VALUE_X = 250;
		Draw_BGS();
	} else {
		MENU_ITEMS_X = 550;
		MENU_ITEMS_VALUE_X = 720;
		Draw_SIDEBAR(MENU_ITEMS_X-10);
	}
	
	x1 = MENU_ITEMS_X;
	x2 = MENU_ITEMS_VALUE_X;
	
	for(i=0; i<=ITEMS_NUMBER; i++) {
		
		if(TITLES[i][0] != 0) {
			y+=10;
			Draw_title(x1, y, TITLES[i]);
			y+=new_line(1)+15;
			y1=y;
		}
		
		if(ITEMS_TYPE[i] == ITEM_TEXTBOX) {
			if(ITEMS_POSITION == i) SetFontColor(COLOR_2, 0x0); 
			else SetFontColor(COLOR_1, 0x0);
			
			DrawString(x1, y, ITEMS[i]);
			
			SetFontColor(COLOR_1, 0x0);
			
			if( ITEMS_VALUE_NUMBER[i] != -1 ) {
				if(IN_ITEMS_VALUE == YES && ITEMS_POSITION == i) {
					SetFontColor(COLOR_2, 0x0);
					if( ITEMS_VALUE_NUMBER[i] > 0 ) {
						float w=GetWidth(ITEMS_VALUE[i][ITEMS_VALUE_POSITION[i]]);
						float h=GetFontHeight();
						DrawDown(x2+w/2, y+h*0.85);
						DrawUp(x2+w/2,  y);	
					}
					DrawString(x2, y, ITEMS_VALUE[i][ITEMS_VALUE_POSITION[i]]);
				} else {
					SetFontColor(COLOR_1, 0x0);
					if(ITEMS_VALUE_SHOW[i]==YES) DrawString(x2, y, ITEMS_VALUE[i][ITEMS_VALUE_POSITION[i]]);
				}
			}
			y+=new_line(1);
		} else
		if(ITEMS_TYPE[i] == ITEM_CHECKBOX) {
			if(i>0) {
				if(ITEMS_TYPE[i-1] == ITEM_TEXTBOX) { y+=10; y1=y; }
			}
			
			u32 color;
			if(ITEMS_POSITION==i) color = COLOR_2; else color = COLOR_1;
		
			Draw_checkbox(ITEMS_VALUE_POSITION[i], x1, y, ITEMS[i], color);
			y+=new_line(1);
			
		} else
		if(ITEMS_TYPE[i] == ITEM_COLORBOX) {			
			if(ITEMS_POSITION == i) SetFontColor(COLOR_2, 0x0); 
			else SetFontColor(COLOR_1, 0x0);
			
			DrawString(x1, y, ITEMS[i]);
			
			u32 color;
			memcpy(&color, ITEMS_VALUE[i][0], 4);
			
			Draw_Box(x2, y, 0, 0, 16, 10, color, NO);
			if(ITEMS_POSITION == i) {x_COLOR=x2; y_COLOR=y+12;}
			
			y+=new_line(1);
		}
		
		SetFontColor(COLOR_1, 0x0);
		
		if(1<i && MENU_COLUMN_ITEMS_NUMBER != -1) {
			if( (i+1)%MENU_COLUMN_ITEMS_NUMBER == 0 ) {
				x1+=MENU_COLUMN_ITEMS_W;
				x2+=MENU_COLUMN_ITEMS_W;
				y=y1;
			}
		}
	
	}
	
}

typedef void (*func)();

void EmptyFunc()
{
	return;
}

func Draw_MENU_input = &EmptyFunc;

func input_MENU = &EmptyFunc;


//*******************************************************
// PS2 MENU
//*******************************************************

void open_PS2_GAME_MENU();

char CRC_STR[8];
char PS2_ID[12];
char pnach[128];
char WS[128];

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

int ps2_netemu_cobra(int param)
{
	lv2syscall2(8, (uint64_t)0x1ee9, (uint64_t)(int)param);
	return_to_user_prog(int);
}

u8 Create_PS2_CONFIG()
{
	char config_path[255];
	
	sprintf(config_path, "%s.CONFIG", list_game_path[position]);
	Delete(config_path);
	
	FILE *f;
	f = fopen(config_path, "wb");
	if(f==NULL) {
		return FAILED;
	}
	
	u64 x3D = 0x3D00000057440000;
	fwrite(&x3D, sizeof(u64), 1, f);
	
	int i;
	unsigned int value;
	for(i=0; i<=ITEMS_NUMBER; i++) {
		if(ITEMS_VALUE_POSITION[i]) {
			sscanf(&ITEMS[i][2], "%X", &value);
			value = reverse32(value);
			fwrite(&value, sizeof(u32), 1, f);
		}
	}
	
	value = 0;
	fwrite(&value, sizeof(u32), 1, f);
	
	char ID[12];
	strcpy(ID, PS2_ID);
	ID[4]='-';
	ID[8]=ID[9];
	ID[9]=ID[10];
	ID[10]=0;
	fputs(ID, f);
	
	fclose(f);

	return SUCCESS;
}

void init_PS2_CONFIG_EDITOR()
{
	init_MENU();
	
	add_title_MENU("PS2 CONFIG EDITOR");
	
	add_item_MENU("0x03", ITEM_CHECKBOX);
	add_item_MENU("0x06", ITEM_CHECKBOX);
	add_item_MENU("0x14", ITEM_CHECKBOX);
	add_item_MENU("0x19", ITEM_CHECKBOX);
	add_item_MENU("0x1A", ITEM_CHECKBOX);
	add_item_MENU("0x1B", ITEM_CHECKBOX);
	add_item_MENU("0x22", ITEM_CHECKBOX);
	add_item_MENU("0x23", ITEM_CHECKBOX);
	add_item_MENU("0x2A", ITEM_CHECKBOX);
	add_item_MENU("0x2B", ITEM_CHECKBOX);
	add_item_MENU("0x35", ITEM_CHECKBOX);
	add_item_MENU("0x3E", ITEM_CHECKBOX);
	add_item_MENU("0x40", ITEM_CHECKBOX);
	add_item_MENU("0x41", ITEM_CHECKBOX);
	add_item_MENU("0x44", ITEM_CHECKBOX);
	add_item_MENU("0x45", ITEM_CHECKBOX);
	add_item_MENU("0x46", ITEM_CHECKBOX);
	add_item_MENU("0x47", ITEM_CHECKBOX);
	add_item_MENU("0x49", ITEM_CHECKBOX);
	add_item_MENU("0x4A", ITEM_CHECKBOX);
	add_item_MENU("0x50", ITEM_CHECKBOX);
	
	MENU_COLUMN_ITEMS_NUMBER = 7;
	
}

u8 input_PS2_CONFIG_EDITOR()
{

	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_R2) {
		scroll_speed = 6 - paddata.PRE_R2/50;
	} else scroll_speed = 6;

	if(new_pad & BUTTON_UP || ((old_pad & BUTTON_UP) && slow_it==0)) {
		if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
		else ITEMS_POSITION--;	
	}
	
	if(new_pad & BUTTON_DOWN || ((old_pad & BUTTON_DOWN) && slow_it==0)) {
		if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
		else ITEMS_POSITION++;
	}
	
	if(new_pad & BUTTON_RIGHT || ((old_pad & BUTTON_RIGHT) && slow_it==0)) {
		if(ITEMS_POSITION + MENU_COLUMN_ITEMS_NUMBER <= ITEMS_NUMBER) ITEMS_POSITION += MENU_COLUMN_ITEMS_NUMBER;
	}
	
	if(new_pad & BUTTON_LEFT || ((old_pad & BUTTON_LEFT) && slow_it==0)) {
		if(ITEMS_POSITION - MENU_COLUMN_ITEMS_NUMBER >= 0) ITEMS_POSITION -= MENU_COLUMN_ITEMS_NUMBER;
	}
	
	if(new_pad & BUTTON_CROSS) {
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == YES) {
			ITEMS_VALUE_POSITION[ITEMS_POSITION] = NO;
		} else {
			ITEMS_VALUE_POSITION[ITEMS_POSITION]= YES;
		}
	} else
	if(new_pad & BUTTON_START) {
		if( Create_PS2_CONFIG() == SUCCESS ) show_msg("Done !");
		else show_msg("Failed !");
		return BREAK;
	} else
	if(new_pad & BUTTON_CIRCLE) {
		return BREAK;
	}
	
	return CONTINUE;
}

void Draw_PS2_CONFIG_EDITOR_input()
{
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	x=DrawButton(x, y, "Check/Uncheck", BUTTON_CROSS);
	x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	x=DrawButton(x, y, "Create CONFIG", BUTTON_START );
}

void Draw_PS2_CONFIG_EDITOR()
{
	start_loading();
	init_PS2_CONFIG_EDITOR();
	ITEMS_POSITION = 0;
	memset(ITEMS_VALUE_POSITION, 0, sizeof(ITEMS_VALUE_POSITION));
	MENU_SIDE = NO;
	MENU=YES;
	end_loading();
	
	while(1)
	{		
		cls();
		
		Draw_BGS();
		Draw_Notification();
		
		Draw_MENU();
		
		Draw_PS2_CONFIG_EDITOR_input();
		
		tiny3d_Flip();
		
		ps3pad_read();
		
		if( input_PS2_CONFIG_EDITOR() == BREAK ) break;
		
	}
	
	open_PS2_GAME_MENU();
}

u32 Get_CRC(char *Elf_Name)
{
	int size;
	
	print_head("Getting CRC");
	
	print_load("Loading ELF...");
	char *mem = LoadFromISO(list_game_path[position], Elf_Name, &size);
	if(mem==NULL) { print_load("Error : failed to load %s", Elf_Name); return 0; }
	
	const u32* srcdata = (u32*) mem;
	
	print_load("Calculating CRC...");
	
	u32 CRC=0;
	u32 i;
	
	for(i=size/4; i; --i, ++srcdata) CRC ^= *srcdata;
		
	if(mem) free(mem);
	
	return reverse32(CRC);
	
}

u8 is_pnached()
{
	char PnachRest[128];
	
	sprintf(PnachRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnachrest", ManaGunZ_id, CRC_STR);
	
	if(path_info(PnachRest) == _NOT_EXIST) return NO; else
	return YES;
}

u8 restore_pnach(char *PnachRest)
{
	FILE *fi;
	FILE *fr;
	u32 offset;
	u32 data;

	fi = fopen(list_game_path[position], "rb+");
	if(fi==NULL) { print_load("Error : Cannot open ISO"); return FAILED;}
	
	fr = fopen(PnachRest, "rb");
	if(fr==NULL) { fclose(fi); print_load("Error : Cannot open PnachRestore file"); return FAILED;}
	
	u32 flba=0;
	u32 size=0;
	u8 ret;

	ret = get_FileOffset(fi, PS2_ID, &flba, &size); 

	if(flba==0 || size==0 || ret == FAILED) {
		print_load("Error : file_pos. File : %s flba= %X size= %X", PS2_ID, flba, size);
		fclose(fi);
		fclose(fr);
		return FAILED;
	}
	
	while( fread(&offset, 1, 4, fr) == 4) {
		if( fread(&data, 1, 4, fr) == 4 ) {
			fseek(fi, 0x800*flba + offset, SEEK_SET);
			fwrite(&data, 4, 1, fi);
		}
    }
	
	fclose(fi);
	fclose(fr);
	
	Delete(PnachRest);
	
	sprintf(CRC_STR, "%08lX", (long unsigned int) Get_CRC(PS2_ID));
	
	return SUCCESS;
}

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
	
	u32 flba=0;
	u32 size=0;
	u8 ret;

	ret = get_FileOffset(fi, PS2_ID, &flba, &size); 

	if(flba==0 || size==0 || ret == FAILED) {
		print_load("Error : file_pos. File : %s flba= %X size= %X", PS2_ID, flba, size);
		fclose(fi);
		fclose(fp); 
		fclose(fr);
		Delete(PnachRest);
		return FAILED;
	}
	
	u32 EntryPoint;
	u32 ProgOffset;
	
	fseek(fi, 0x800*flba + 0x18, SEEK_SET);
	fread(&EntryPoint, 4, 1, fi);
	fseek(fi, 0x800*flba + 0x38, SEEK_SET);
	fread(&ProgOffset, 4, 1, fi);
	
	EntryPoint = reverse32(EntryPoint);
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
			
			offset = offset - EntryPoint - 8 + ProgOffset;
			offset = offset - (offset >> 28)*0x10000000;
					
			new_data = reverse32(new_data);
			fseek(fi, 0x800*flba + offset, SEEK_SET);
			fread(&old_data, 4, 1, fi);
			
			if(offset > size) { 
				print_load("Error : offset > Elf_size"); 
				fclose(fr);
				fclose(fi);
				fclose(fp);
				restore_pnach(PnachRest);
				return FAILED;
			}
			
			fseek(fi, 0x800*flba + offset, SEEK_SET);
			
			fwrite(&new_data, 4, 1, fi);
			
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
	
	return SUCCESS;
}

#define CONFIG_NONE      0
#define CONFIG_OFFICIAL  1
#define CONFIG_CUSTOM    2
#define CONFIG_UNK       3

void check_CONFIG(u8* OFFICIAL, u8* CUSTOM, u8* used)
{
	u64 used_md5[2];
	
	char CONFIG_path[128];
	
	u8 tmp_used = CONFIG_UNK;
	
	strcpy(CONFIG_path, list_game_path[position]);
	strcat(CONFIG_path, ".CONFIG");
	
	if( path_info(CONFIG_path) == _NOT_EXIST ) tmp_used = CONFIG_NONE;
	else md5_file(CONFIG_path, (u8 *) used_md5);	
	
	sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/OFFICIAL/%s.CONFIG", ManaGunZ_id, PS2_ID);
	if( path_info(CONFIG_path) == _NOT_EXIST ) *OFFICIAL = 0; else *OFFICIAL = 1;
	
	if(tmp_used == CONFIG_UNK) {	
		u64 md5_off[2];
		md5_file(CONFIG_path, (u8 *) md5_off);
		if(used_md5[0]==md5_off[0] && used_md5[1]==md5_off[1]) tmp_used = CONFIG_OFFICIAL;
	}
	
	sprintf(CONFIG_path, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/CUSTOM/%s.CONFIG", ManaGunZ_id, PS2_ID);	
	if( path_info(CONFIG_path) == _NOT_EXIST ) *CUSTOM = 0; else *CUSTOM = 1;
	
	if(tmp_used == CONFIG_UNK) {
		u64 md5_cus[2];
		md5_file(CONFIG_path, (u8 *) md5_cus);
		if(used_md5[0]==md5_cus[0] && used_md5[1]==md5_cus[1]) tmp_used = CONFIG_CUSTOM;
	}
	
	*used = tmp_used;
}

u8 WS_exist()
{
	sprintf(WS, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.ws", ManaGunZ_id, CRC_STR);
	
	if(path_info(WS) == _NOT_EXIST) return NO;
	
	return YES;
}

void get_WS()
{
	sprintf(WS, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.ws", ManaGunZ_id, CRC_STR);
	
	if(path_info(WS) != _NOT_EXIST) return;
	
	char ZIP_WS[32];
	char ZIP[128];
	
	sprintf(ZIP_WS, "%s.pnach", CRC_STR);
	sprintf(ZIP, "/dev_hdd0/game/%s/USRDIR/sys/ws.zip", ManaGunZ_id);
	
	ExtractZipFile(ZIP, ZIP_WS, WS);
}

u8 is_WS()
{
	char WSRest[128];
	
	sprintf(WSRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, CRC_STR);
	
	if(path_info(WSRest) == _NOT_EXIST) return NO; else
	return YES;
}

void init_PS2_GAME_MENU()
{
	int i,j;
	
	init_MENU();
	
	add_title_MENU("Game Options");
	
	add_item_MENU("Rename", ITEM_TEXTBOX);

	if( is_favorite(list_game_path[position]) == NO )
		add_item_MENU("Add to Favorite", ITEM_TEXTBOX);
	else 
		add_item_MENU("Remove from Favorite", ITEM_TEXTBOX);
	
	if( is_pnached() ) {
		add_item_MENU("Restore PNACH", ITEM_TEXTBOX);
	}
	else {
		sprintf(pnach, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnach", ManaGunZ_id, CRC_STR);
		if(path_info(pnach) == _NOT_EXIST) {
			for(i=0; i<=device_number; i++) {
				sprintf(pnach, "/%s/PNACH/%s.pnach", list_device[i], CRC_STR);
				if(path_info(pnach) == _FILE) break;
			}
		}
		if(path_info(pnach) == _FILE) {
			add_item_MENU("Apply PNACH", ITEM_TEXTBOX);
		}
	}
	
	if( is_WS() ) {
		add_item_MENU("Disable WideScreen", ITEM_TEXTBOX);
	} else 
	if( WS_exist() ) {
		add_item_MENU("Enable WideScreen", ITEM_TEXTBOX);
	}
	
	i = ps2_netemu_cobra(BCNETEMU_STATUS);
	if(i != BCNETEMU_ISNOTBC) {
		if(i == BCNETEMU_OFF) {
			add_item_MENU("Enable NetEMU", ITEM_TEXTBOX);
		} else
		if(i == BCNETEMU_ON) {
			add_item_MENU("Disable NetEMU", ITEM_TEXTBOX);
		}	
	}
	
	add_item_MENU("CONFIG to use", ITEM_TEXTBOX);
	
	u8 OFFICIAL, CUSTOM, used;
	check_CONFIG(&OFFICIAL, &CUSTOM, &used);
	
	add_item_value_MENU("None");
	if(used == CONFIG_NONE) ITEMS_VALUE_POSITION[ITEMS_NUMBER]=ITEMS_VALUE_NUMBER[ITEMS_NUMBER];
	
	if(OFFICIAL) {
		add_item_value_MENU("Official");
		if(used == CONFIG_OFFICIAL) ITEMS_VALUE_POSITION[ITEMS_NUMBER]=ITEMS_VALUE_NUMBER[ITEMS_NUMBER];
	}
	if(CUSTOM) {
		add_item_value_MENU("Custom");
		if(used == CONFIG_CUSTOM) ITEMS_VALUE_POSITION[ITEMS_NUMBER]=ITEMS_VALUE_NUMBER[ITEMS_NUMBER];
	}
	if(used == CONFIG_UNK) {
		add_item_value_MENU("Unknown");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER]=ITEMS_VALUE_NUMBER[ITEMS_NUMBER];
	}
	
	add_item_MENU("Create CONFIG", ITEM_TEXTBOX);
	
	add_item_MENU("Check MD5", ITEM_TEXTBOX);
	
	if(device_number != 0) {
		add_item_MENU("Copy", ITEM_TEXTBOX);
		for(j=0; j<=scan_dir_number; j++) {
			for(i=0; i<=device_number; i++) {
				if(strstr(list_game_path[position], list_device[i])) continue;
				char tmp[128];
				sprintf(tmp, "/%s/%s", list_device[i], scan_dir[j]);
				add_item_value_MENU(tmp);
			}
		}
	}
	
	add_item_MENU("Delete", ITEM_TEXTBOX);
	
	add_item_MENU("Properties", ITEM_TEXTBOX);
	
}

void close_PS2_GAME_MENU()
{
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	MENU=NO;
}

u8 PS2_GAME_MENU_CROSS()
{
	if(item_is("Rename")) {
		char New_Name[255];
		strcpy(New_Name, &strrchr(list_game_path[position], '/')[1]);
		strtok(New_Name, ".");
		if(Get_OSK_String("Rename", New_Name, 255) == SUCCESS) {
			if(New_Name[0] != 0) {
				char DirPath[255];
				char NewPath[255];
				strcpy(DirPath, list_game_path[position]);
				DirPath[strrchr(DirPath, '/') - DirPath] = 0;
				sprintf(NewPath, "%s/%s.iso", DirPath, New_Name);
				if( rename(list_game_path[position], NewPath) == 0) {
					strcpy(list_game_path[position], NewPath);
					strcpy(list_game_title[position], list_game_path[position]);
					strcpy(list_game_title[position], &strrchr(list_game_title[position], '/')[1]);
					strtok(list_game_title[position], ".");
				}
			}
		}
	} else 
	if(item_is("Add to Favorite")) {
		if(add_favorite()==SUCCESS) show_msg("Added to favorites");
		else show_msg("Failed");
	} else 
	if(item_is("Remove from Favorite")) {
		if(remove_favorite()==SUCCESS) show_msg("Removed from favorites"); 
		else show_msg("Failed");
	} else 
	if(item_is("Restore PNACH")) {
		start_loading();
		char PnachRest[128];
		sprintf(PnachRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnachrest", ManaGunZ_id, CRC_STR);
		u8 ret = restore_pnach(PnachRest);
		end_loading();
		if( ret == SUCCESS) show_msg("Done !");
		else show_msg("Failed !");
	} else 
	if(item_is("Apply PNACH")) {
		start_loading();
		char PnachRest[128];
		sprintf(PnachRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnachrest", ManaGunZ_id, PS2_ID);
		u8 ret = apply_pnach(pnach, PnachRest);
		if( ret == SUCCESS) {
			sprintf(CRC_STR, "%08lX", (long unsigned int) Get_CRC(PS2_ID));
			char new_CRC[128];
			sprintf(new_CRC, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.pnachrest", ManaGunZ_id, CRC_STR);	
			if( rename(PnachRest, new_CRC) != 0 ) {
				print_load("Error : failed to rename PnachRestor file");
				if( restore_pnach(PnachRest) == FAILED ) print_load("Error : failed to restore Pnach");
			}
		}		
		end_loading();
		if( ret == SUCCESS) show_msg("Done !");
		else show_msg("Failed !");
	} else 
	if(item_is("Enable WideScreen")) {
		start_loading();
		char WSRest[128];
		sprintf(WSRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, PS2_ID);
		u8 ret = apply_pnach(WS, WSRest);
		if( ret == SUCCESS) {
			sprintf(CRC_STR, "%08lX", (long unsigned int) Get_CRC(PS2_ID));
			char new_CRC[128];
			sprintf(new_CRC, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, CRC_STR);
			if( rename(WSRest, new_CRC) != 0 ) {
				print_load("Error : failed to rename PnachRestor file");
				if( restore_pnach(WSRest) == FAILED ) print_load("Error : failed to restore Pnach");
			}
		}
		end_loading();
		if( ret == SUCCESS) show_msg("Done !");
		else show_msg("Failed !");
	} else 
	if(item_is("Disable WideScreen")) {
		start_loading();
		char WSRest[128];
		sprintf(WSRest, "/dev_hdd0/game/%s/USRDIR/setting/PS2/%s.wsrest", ManaGunZ_id, CRC_STR);
		u8 ret = restore_pnach(WSRest);
		end_loading();
		if( ret == SUCCESS) show_msg("Done !");
		else show_msg("Failed !");
	} else 
	if(item_is("Enable NetEMU")) {
		if( ps2_netemu_cobra(BCNETEMU_ON) == BCNETEMU_ON) show_msg("NetEMU enabled");
		else show_msg("Failed !");
	} else 
	if(item_is("Disable NetEMU")) {
		if( ps2_netemu_cobra(BCNETEMU_OFF) == BCNETEMU_OFF) show_msg("NetEMU disabled");
		else show_msg("Failed !");
	} else 
	if(item_is("Create CONFIG")) {
		Draw_PS2_CONFIG_EDITOR();
	} else 
	if(item_is("Check MD5")) {
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
	if(item_is("Copy")) {
		start_copy_loading();
		gathering=YES;
		get_size(list_game_path[position], YES);
		gathering=NO;
		strcpy(copy_src, list_game_path[position]);
		sprintf(copy_dst, "%s/%s", ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], &strrchr(list_game_path[position], '/')[1] );
		if( Copy(copy_src, copy_dst) == SUCCESS )
			show_msg("Done !");
		else
			show_msg("Failed !");
		end_copy_loading();
	} else 
	if(item_is("Delete")) 
	{
		char diag_msg[512];
		sprintf(diag_msg, "Do you realy want to delete '%s' ?\nPath : %s\n", list_game_title[position], list_game_path[position]);
		if( DrawDialogYesNo(diag_msg) == YES) {
			start_loading();
			u8 ret = Delete_Game(NULL, position);
			end_loading();
			if(ret==SUCCESS) {
				show_msg("Game deleted");
				return BREAK;
			} else show_msg("Failed to delete game");
		}
	} else 
	if(item_is("CONFIG to use"))
	{	
		char CONFIG_path[128];
		strcpy(CONFIG_path, list_game_path[position]);
		strcat(CONFIG_path, ".CONFIG");
		
		if(item_value_is("None")) {
			Delete(CONFIG_path);
		} else
		if(item_value_is("Official")) {
			Delete(CONFIG_path);
			char loc_CONFIG[128];
			sprintf(loc_CONFIG, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/OFFICIAL/%s.CONFIG", ManaGunZ_id, PS2_ID);
			Copy(loc_CONFIG, CONFIG_path);
		} else 
		if(item_value_is("Custom")) {
			Delete(CONFIG_path);
			char loc_CONFIG[128];
			sprintf(loc_CONFIG, "/dev_hdd0/game/%s/USRDIR/sys/CONFIG/CUSTOM/%s.CONFIG", ManaGunZ_id, PS2_ID);
			Copy(loc_CONFIG, CONFIG_path);
		}
		
	} else 
	if(item_is("Properties")) {
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
	
	init_PS2_GAME_MENU();
	
	return CONTINUE;
}

void Draw_PS2_GAME_MENU_input()
{
	if(MENU==NO) return;
	
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	x=DrawButton(x, y, "Enter", BUTTON_CROSS);
	x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	x=DrawButton(x, y, "Navigate", BUTTON_UP | BUTTON_DOWN);
}

void input_PS2_GAME_MENU()
{
	if(MENU==NO) return;
	
	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_R2) {
		scroll_speed = 6 - paddata.PRE_R2/50;
	} else scroll_speed = 6;

	if(new_pad & BUTTON_UP || ((old_pad & BUTTON_UP) && slow_it==0)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	}
	
	if(new_pad & BUTTON_DOWN || ((old_pad & BUTTON_DOWN) && slow_it==0)) {
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
		if(IN_ITEMS_VALUE == NO) close_PS2_GAME_MENU();
		else {
			init_PS2_GAME_MENU();
			IN_ITEMS_VALUE = NO;
		}
	}
}

void open_PS2_GAME_MENU()
{
	start_loading();
	Get_PS2ID(list_game_path[position], PS2_ID);
	sprintf(CRC_STR, "%08lX", (long unsigned int) Get_CRC(PS2_ID));
	get_WS();
	init_PS2_GAME_MENU();
	ITEMS_POSITION = 0;
	memset(ITEMS_VALUE_POSITION, 0, sizeof(ITEMS_VALUE_POSITION));
	MENU_SIDE=use_sidemenu;
	IN_ITEMS_VALUE=NO;
	Draw_MENU_input = &Draw_PS2_GAME_MENU_input;
	input_MENU = &input_PS2_GAME_MENU;
	end_loading();
	MENU=YES;
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
	
	SetFontSize(20, 20);
	
	u8 i;
	for(i=0; i<0x10; i++) x1=DrawString(x1, -50, "FF");
	
	Draw_Box(0, 0, 0, 0, 848, 512, 0x00000080, NO);
	Draw_Box(50, y-15 , 0, 10, x1+20+20, 15+25+10+15, GREY, NO);
	
	
	SetFontColor(COLOR_3, 0x0);
	SetFontZ(0);
	x = DrawString(x,y, "00000001008");

	if(CHOOSE_IDPS_position==0) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x, y, "%X", IDPS[0x5] - (IDPS[5] >> 4)*0x10 );
	if(CHOOSE_IDPS_position==0) {
		if(IDPS[0x5] - (IDPS[0x5] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0x5] - (IDPS[0x5] >> 4)*0x10 > 0x2) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	SetFontColor(COLOR_3, 0x0);
	x = DrawString(x,y, "000");
	
	//0x7
	if(CHOOSE_IDPS_position==1) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0x7] - (IDPS[0x7] >> 4)*0x10);
	if(CHOOSE_IDPS_position==1) {
		if(IDPS[0x7]<0x0E) DrawUp((x+x1)/2, y);
		if(IDPS[0x7]>0x01) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0x8
	if(CHOOSE_IDPS_position==2) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0x8] >> 4));
	if(CHOOSE_IDPS_position==2) {
		if((IDPS[0x8] >> 4) == 0x0 || (IDPS[0x8] >> 4) == 0x1) DrawUp((x+x1)/2, y);
		if((IDPS[0x8] >> 4) == 0x1 || (IDPS[0x8] >> 4) == 0xF) DrawDown((x+x1)/2, y+25*0.85);
	}
	if(CHOOSE_IDPS_position==3) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0x8] - (IDPS[0x8] >> 4)*0x10);
	if(CHOOSE_IDPS_position==3) {
		if(IDPS[0x8] - (IDPS[0x8] >> 4)*0x10 == 0x0) DrawUp((x+x1)/2, y); else
		if(IDPS[0x8] - (IDPS[0x8] >> 4)*0x10 == 0x4) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0x9
	if(CHOOSE_IDPS_position==4) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0x9] >> 4));
	if(CHOOSE_IDPS_position==4) {
		if((IDPS[0x9] >> 4) < 0x3) DrawUp((x+x1)/2, y);
		if((IDPS[0x9] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	if(CHOOSE_IDPS_position==5) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0x9] - (IDPS[0x9] >> 4)*0x10);
	if(CHOOSE_IDPS_position==5) {
		if(IDPS[0x9] - (IDPS[0x9] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0x9] - (IDPS[0x9] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xA
	if(CHOOSE_IDPS_position==6) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xA] >> 4));
	if(CHOOSE_IDPS_position==6) {
		if((IDPS[0xA] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xA] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==7) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xA] - (IDPS[0xA] >> 4)*0x10);
	if(CHOOSE_IDPS_position==7) {
		if(IDPS[0xA] - (IDPS[0xA] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xA] - (IDPS[0xA] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xB
	if(CHOOSE_IDPS_position==8) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xB] >> 4));
	if(CHOOSE_IDPS_position==8) {
		if((IDPS[0xB] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xB] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==9) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xB] - (IDPS[0xB] >> 4)*0x10);
	if(CHOOSE_IDPS_position==9) {
		if(IDPS[0xB] - (IDPS[0xB] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xB] - (IDPS[0xB] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xC
	if(CHOOSE_IDPS_position==10) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xC] >> 4));
	if(CHOOSE_IDPS_position==10) {
		if((IDPS[0xC] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xC] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==11) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xC] - (IDPS[0xC] >> 4)*0x10);
	if(CHOOSE_IDPS_position==11) {
		if(IDPS[0xC] - (IDPS[0xC] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xC] - (IDPS[0xC] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xD
	if(CHOOSE_IDPS_position==12) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xD] >> 4));
	if(CHOOSE_IDPS_position==12) {
		if((IDPS[0xD] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xD] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==13) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xD] - (IDPS[0xD] >> 4)*0x10);
	if(CHOOSE_IDPS_position==13) {
		if(IDPS[0xD] - (IDPS[0xD] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xD] - (IDPS[0xD] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xE
	if(CHOOSE_IDPS_position==14) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xE] >> 4));
	if(CHOOSE_IDPS_position==14) {
		if((IDPS[0xE] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xE] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==15) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xE] - (IDPS[0xE] >> 4)*0x10);
	if(CHOOSE_IDPS_position==15) {
		if(IDPS[0xE] - (IDPS[0xE] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xE] - (IDPS[0xE] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	//0xF
	if(CHOOSE_IDPS_position==16) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", (IDPS[0xF] >> 4));
	if(CHOOSE_IDPS_position==16) {
		if((IDPS[0xF] >> 4) < 0xF) DrawUp((x+x1)/2, y);
		if((IDPS[0xF] >> 4) > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	if(CHOOSE_IDPS_position==17) SetFontColor(COLOR_2, 0x0); else SetFontColor(COLOR_1, 0x0);
	x1=x;
	x=DrawFormatString(x,y, "%X", IDPS[0xF] - (IDPS[0xF] >> 4)*0x10);
	if(CHOOSE_IDPS_position==17) {
		if(IDPS[0xF] - (IDPS[0xF] >> 4)*0x10 < 0xF) DrawUp((x+x1)/2, y);
		if(IDPS[0xF] - (IDPS[0xF] >> 4)*0x10 > 0x0) DrawDown((x+x1)/2, y+25*0.85);
	}
	
	x=70; y+=25;
	SetFontSize(10, 10);
	SetFontColor(COLOR_3, 0x0);
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
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	x=DrawButton(x, y, "Change value", BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT);
	x=DrawButton(x, y, "Load IDPS from lv2", BUTTON_SQUARE);
	x=DrawButton(x, y, "Load IDPS from EID5", BUTTON_TRIANGLE);
	x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
}

void Draw_CHOOSE_IDPS()
{
	while(1)
	{
		cls();
		Draw_scene();
		
		Draw_CHOOSE_IDPS_menu();
		Draw_CHOOSE_IDPS_input();
		
		tiny3d_Flip();
		
		ps3pad_read();
				
		if(input_CHOOSE_IDPS() == BREAK) return;
	}
	old_pad = 0;
	new_pad = 0;
}

void close_PS3_GAME_MENU()
{
	write_game_setting(list_game_title[position]);
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	MENU=NO;
}

void init_PS3_GAME_MENU()
{
	int i, j;
	
	init_MENU();
	
	add_title_MENU("Game Settings");
	
	add_item_MENU("Direct boot", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = direct_boot;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU("Clean syscall", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = clean_syscall;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU("Change IDPS", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = change_IDPS;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU("Ext. Game Data", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = ext_game_data;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU("Payload", ITEM_TEXTBOX);
	add_item_value_MENU("Iris");
	add_item_value_MENU("multiMAN");
	if(cobra) add_item_value_MENU("Cobra");
	else add_item_value_MENU("Mamba");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = payload;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	if(iso == NO) {	
		if(cobra==YES && usb==YES) {
			add_item_MENU("Set Primary USB", ITEM_TEXTBOX);
			add_item_value_MENU("No");
			add_item_value_MENU("Yes");
			ITEMS_VALUE_POSITION[ITEMS_NUMBER] = prim_USB;
			ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		}
		
		add_item_MENU("Emulation", ITEM_TEXTBOX);
		add_item_value_MENU("None");
		add_item_value_MENU("BDMIRROR");
		add_item_value_MENU("BDEMU");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = emu;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		if(emu==BDEMU) {
			add_item_MENU("Patched from", ITEM_TEXTBOX);
			add_item_value_MENU("multiMAN");
			add_item_value_MENU("Iris");
			add_item_value_MENU("reactPSN");
			ITEMS_VALUE_POSITION[ITEMS_NUMBER] = libfs_from;
			ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		}
	}
	
	add_item_MENU("Mount /app_home", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = mount_app_home;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	if(mount_app_home==YES) {
		add_item_MENU("Use patched plugin", ITEM_TEXTBOX);
		add_item_value_MENU("No");
		add_item_value_MENU("Yes");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = use_ex_plug;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	}
	
	add_title_MENU("Game Options");
	
	add_item_MENU("Rename", ITEM_TEXTBOX);
	
	if(is_favorite(list_game_path[position]) == NO) {
		add_item_MENU("Add to favorite", ITEM_TEXTBOX);
	} else {
		add_item_MENU("Remove from favorite", ITEM_TEXTBOX);
	}

	add_item_MENU("Delete game", ITEM_TEXTBOX);
	
	if(device_number != 0) {
		add_item_MENU("Copy game", ITEM_TEXTBOX);
		for(j=0; j<=scan_dir_number; j++) {
			for(i=0; i<=device_number; i++) {
				if(strstr(list_game_path[position], list_device[i])) continue;
				char tmp[255];
				sprintf(tmp, "/%s/%s", list_device[i], scan_dir[j]);
				add_item_value_MENU(tmp);
			}
		}
	}
	
	add_item_MENU("Make PKG", ITEM_TEXTBOX);
	
	add_item_MENU("Patch EBOOT", ITEM_TEXTBOX);
	
	if(iso==NO) {
		if(is_resigned_GAME(list_game_path[position])==NO) {
			add_item_MENU("Re-sign", ITEM_TEXTBOX);
		} else {
			add_item_MENU("Restore", ITEM_TEXTBOX);
		}
	}
	
	if(iso) {
		add_item_MENU("Extract ISO", ITEM_TEXTBOX);
	} else {
		add_item_MENU("Convert to ISO", ITEM_TEXTBOX);
	}
	for(j=0; j<=scan_dir_number; j++) {
		for(i=0; i<=device_number; i++) {
			char tmp[255];
			sprintf(tmp, "/%s/%s", list_device[i], scan_dir[j]);
			add_item_value_MENU(tmp);
		}
	}
	
	add_item_MENU("Fix Permission", ITEM_TEXTBOX);
	
	add_item_MENU("Check files (IRD)", ITEM_TEXTBOX);
	
	add_item_MENU("Download Update", ITEM_TEXTBOX);
	
	add_item_MENU("Properties", ITEM_TEXTBOX);
	
}

void PS3_GAME_MENU_UPDATE()
{
	if(item_is("Direct boot")) {
		direct_boot = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is("Clean syscall")) {
		clean_syscall = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(item_is("Change IDPS")) {
		change_IDPS = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is("Payload")) {
		payload = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is("Ext. Game Data")) {
		ext_game_data = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is("Set Primary USB")) {
		prim_USB = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is("Emulation")) {
		emu = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is("Patched from")) {
		libfs_from = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(item_is("Mount /app_home")) {
		mount_app_home = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(item_is("Use patched plugin")) {
		use_ex_plug = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	}
	
	init_PS3_GAME_MENU();
}

u8 PS3_GAME_MENU_CROSS()
{
	if(item_is("Change IDPS")) {
		Draw_CHOOSE_IDPS();
	} else 
	if(item_is("Rename")) {
		char tmpName[128];
		strcpy(tmpName, list_game_title[position]);
		if(Get_OSK_String("Rename", tmpName, 128) == SUCCESS) {
			if(tmpName[0]!=0) {
				if(SetParamSFO("TITLE", tmpName, position, NULL)==SUCCESS) {
					strcpy(list_game_title[position], tmpName);
					show_msg("Game renamed");
				}
			}
		}
	} else 
	if(item_is("Add to favorite")) {
		if(add_favorite()==SUCCESS) show_msg("Added to favorites");
		else show_msg("Failed");
	} else 
	if(item_is("Remove from favorite")) {
		if(remove_favorite()==SUCCESS) show_msg("Removed from favorites"); 
		else show_msg("Failed");
	} else 
	if(item_is("Make PKG")) {
		
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
				if(ret == SUCCESS) show_msg("Done");
				else show_msg("Failed");
			}
		}
	
	} else 
	if(item_is("Delete game")) {
		char diag_msg[512];
		sprintf(diag_msg, "Do you realy want to delete %s ?\nPath : %s", list_game_title[position], list_game_path[position]);
		if( DrawDialogYesNo(diag_msg) == YES) {
			start_loading();
			u8 ret = Delete_Game(NULL, position);
			end_loading();
			if(ret==SUCCESS) {
				show_msg("Game deleted");
				return BREAK;
			} else show_msg("Failed to delete game");
		}
	} else 
	if(item_is("Copy game")) {
		Copy_Game(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
	} else 
	if(item_is("Patch EBOOT")) {
		start_loading();
		u8 ret;
		if(iso==NO) ret = patch_EBOOT(position);
		else 		ret = patchps3iso(list_game_path[position]);
		if(ret == SUCCESS) show_msg("EBOOT Patched"); 
		else show_msg("Failed");
		end_loading();
	} else 
	if(item_is("Re-sign")) {
		if(iso==NO) {
			start_loading();
			if(re_sign_GAME(list_game_path[position]) == SUCCESS) show_msg("Game re-signed"); else
			show_msg("Failed"); 
			end_loading();
		} else show_msg("TODO for ISO");
	} else 
	if(item_is("Restore")) {
		if(iso==NO) {
			start_loading();
			if(restore_GAME(list_game_path[position]) == SUCCESS) show_msg("Game restored"); else
			show_msg("Failed"); 
			end_loading();
		} else show_msg("TODO for ISO");
	} else 
	if(item_is("Extract ISO")) {
			start_loading();
			print_head("Converting...");
			u8 ret;
			if(is_ntfs(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]])==YES
			|| strstr(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/dev_hdd0")) 
				ret = extractps3iso(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], FULL); 
			else 
				ret = extractps3iso(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], SPLIT);	
			if(ret==FAILED) show_msg("Failed"); else
			show_msg("Done");
			end_loading();
	} else 
	if(item_is("Convert to ISO")) {
		start_loading();
		print_head("Converting...");
		u8 ret;
		if(is_ntfs(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]])==YES
		|| strstr(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], "/dev_hdd0")) 
			ret = makeps3iso(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], FULL);
		else 
			ret = makeps3iso(list_game_path[position], ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]], SPLIT);
		
		if(ret==FAILED) show_msg("Failed"); else
		show_msg("Done");
		end_loading();
	} else 
	if(item_is("Fix Permission")) {
		if(iso==NO) {
			start_loading();
			print_head("Fixing permission...");
			if(SetPerms(list_game_path[position]) == SUCCESS) show_msg("Perms Fixed !");
			else show_msg("Failed");
			end_loading();
		} else show_msg("Useless for ISO");
	} else 
	if(item_is("Check files (IRD)")) {
		if(iso==NO) {
			u8 ret;
			start_loading();
			ret = CheckIRD(list_game_path[position]);
			end_loading();
			
			if( ret == SUCCESS ) {
				char temp[128];
				sprintf(temp, "%s/MD5_check.txt", list_game_path[position]);
				open_txt_viewer(temp);
			} 
			else {
				show_msg("Failed to check IRD");
				end_loading();
			}
		} else show_msg("TODO for ISO");
	} else 
	if(item_is("Download Update")) {
		get_game_update(position);
	} else 
	if(item_is("Properties")) {
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
	
	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_R2) {
		scroll_speed = 6 - paddata.PRE_R2/50;
	} else scroll_speed = 6;

	if(new_pad & BUTTON_UP || ((old_pad & BUTTON_UP) && slow_it==0)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	}
	
	if(new_pad & BUTTON_DOWN || ((old_pad & BUTTON_DOWN) && slow_it==0)) {
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
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		} else {
			PS3_GAME_MENU_SQUARE(); 
		}
	} else
	if(new_pad & BUTTON_TRIANGLE) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
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
	
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	if(IN_ITEMS_VALUE == YES) {
		if(item_is("Dir. to scan")) {
			x=DrawButton(x, y, "Add", BUTTON_CROSS);
			if(scan_dir_number>0) {
				x=DrawButton(x, y, "Delete", BUTTON_TRIANGLE);
				x=DrawButton(x, y, "Rename", BUTTON_SQUARE);
			}
		} else
		if(item_is("Themes")) {
			x=DrawButton(x, y, "Load", BUTTON_CROSS);
			x=DrawButton(x, y, "Delete", BUTTON_TRIANGLE);
			u8 ThemeType = GetThemeType(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
			if(ThemeType == MGZ) {
				x=DrawButton(x, y, "Rename", BUTTON_TRIANGLE);
			}
		}		
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	} else {
		if(strstr(ITEMS[ITEMS_POSITION], "Color") != NULL) {
			x=DrawButton(x, y, "Change", BUTTON_CROSS);
			x=DrawButton(x, y, "Reset", BUTTON_SQUARE);
		} else {
			x=DrawButton(x, y, "Enter", BUTTON_CROSS);
			x=DrawButton(x, y, "Change", BUTTON_SQUARE);
		}
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	}

}

void open_PS3_GAME_MENU()
{
	start_loading();
	read_game_setting(list_game_title[position]);
	ITEMS_POSITION=0;
	IN_ITEMS_VALUE = NO;
	memset(ITEMS_VALUE_POSITION, 0, sizeof(ITEMS_VALUE_POSITION));
	init_PS3_GAME_MENU();
	MENU_SIDE=use_sidemenu;
	Draw_MENU_input = &Draw_PS3_GAME_MENU_input;
	input_MENU = &input_PS3_GAME_MENU;
	end_loading();
	MENU=YES;
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
		show_msg("todo");
	} else
	if(list_game_platform[position] == _JB_PSP || list_game_platform[position] == _ISO_PSP) {
		show_msg("todo");
	}
}

//*******************************************************
// SETTINGS MENU
//*******************************************************

void open_SETTINGS();
void close_SETTINGS();

void close_PLUGINS_MANAGER()
{
	open_SETTINGS();
}

void init_PLUGINS_MANAGER()
{
	init_MENU();
	
	add_title_MENU("PLUGING MANAGER");
	
	add_item_MENU("Boot file", ITEM_TEXTBOX);
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
	
	if(ITEMS_VALUE_NUMBER[0] == -1) return;
	
	char temp[128];
	DIR *d;
	struct dirent *dir;
	
	d = opendir("/dev_hdd0/plugins");
	if(d!=NULL) {			
		while ((dir = readdir(d))) {
			if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
			if(get_ext(dir->d_name) == _SPRX) {
				add_item_MENU(dir->d_name, ITEM_CHECKBOX);
				sprintf(temp, "/dev_hdd0/plugins/%s", dir->d_name);
				ITEMS_VALUE_POSITION[ITEMS_NUMBER] = is_it_inside(ITEMS_VALUE[0][ITEMS_VALUE_POSITION[0]], temp);
			}	
		}
		closedir(d);
	}
}

u8 PLUGINS_MANAGER_CROSS()
{
	if(item_is("Boot file")) {
		open_txt_viewer(ITEMS_VALUE[ITEMS_POSITION][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
	} else {
		char temp[128];
		sprintf(temp, "/dev_hdd0/plugins/%s", ITEMS[ITEMS_POSITION]);
		if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == YES) 
			remove_from_list(ITEMS_VALUE[0][ITEMS_VALUE_POSITION[0]], temp);
		else 
			add_to_list(ITEMS_VALUE[0][ITEMS_VALUE_POSITION[0]], temp);
	}
	
	init_PLUGINS_MANAGER();
	
	return CONTINUE;
}

u8 PLUGINS_MANAGER_SQUARE()
{
	if( item_is("Boot file") == NO ) {
		char diag_msg[512];
		sprintf(diag_msg, "Do you realy want to delete '%s' ?", ITEMS[ITEMS_POSITION]);
		if( DrawDialogYesNo(diag_msg) == YES) {
			char temp[128];
			sprintf(temp, "/dev_hdd0/plugins/%s", ITEMS[ITEMS_POSITION]);
			remove_from_list(ITEMS_VALUE[0][ITEMS_VALUE_POSITION[0]], temp);
			Delete(temp);
		}
		ITEMS_POSITION=0;
	}
	
	init_PLUGINS_MANAGER();
	
	return CONTINUE;
}

u8 PLUGINS_MANAGER_TRIANGLE()
{
	return CONTINUE;
}

void input_PLUGINS_MANAGER()
{
	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_R2) {
		scroll_speed = 6 - paddata.PRE_R2/50;
	} else scroll_speed = 6;
	
	if(new_pad & BUTTON_UP || ((old_pad & BUTTON_UP) && slow_it==0)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	}
	
	if(new_pad & BUTTON_DOWN || ((old_pad & BUTTON_DOWN) && slow_it==0)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	}
	
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
	
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	if(IN_ITEMS_VALUE == YES) {
		if(item_is("Boot file")) {
			x=DrawButton(x, y, "Show", BUTTON_CROSS);
		}	
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	} else {
		if(ITEMS_TYPE[ITEMS_POSITION] == ITEM_CHECKBOX) {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == YES) 
				x=DrawButton(x, y, "Uncheck", BUTTON_CROSS);
			else 
				x=DrawButton(x, y, "Check", BUTTON_CROSS);
			x=DrawButton(x, y, "Delete", BUTTON_SQUARE);
		} else x=DrawButton(x, y, "Enter", BUTTON_CROSS);
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	}
}

void open_PLUGINS_MANAGER()
{
	start_loading();
	
	close_SETTINGS();
	
	ITEMS_POSITION = 0;
	memset(ITEMS_VALUE_POSITION, 0, sizeof(ITEMS_VALUE_POSITION));
	
	init_PLUGINS_MANAGER();
	
	MENU_SIDE = NO;
	MENU=YES;
	IN_ITEMS_VALUE=NO;
	Draw_MENU_input = &Draw_PLUGINS_MANAGER_input;
	input_MENU = &input_PLUGINS_MANAGER;
	
	end_loading();
}

void Draw_AdjustScreen()
{
	while(1){
		int x;
		adjust_screen();

		cls();

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

		SetFontColor(0x000000FF, 0x0);
		SetFontSize(15, 15);
		x=Draw_Button_Circle(25, 485, 15);
		x=DrawString(x+5, 485, "Back  ");

		tiny3d_Flip();
	
		ps3pad_read();
		
		if(new_pad & BUTTON_DOWN) {if(videoscale_y > -120) videoscale_y-=10;}
		if(new_pad & BUTTON_UP) {if(videoscale_y < 120) videoscale_y+=10;}
		if(new_pad & BUTTON_RIGHT) {if(videoscale_x > -120) videoscale_x-=10;}
		if(new_pad & BUTTON_LEFT) {if(videoscale_x < 120) videoscale_x+=10;}
		if(new_pad & BUTTON_CIRCLE) {write_setting(); return;}
	}
}

u8 C_pos=0;

void Draw_RGB_box(int n)
{
	u32 COLOR=0;
	if(n==1) COLOR = COLOR_1; else
	if(n==2) COLOR = COLOR_2; else
	if(n==3) COLOR = COLOR_3; else
	if(n==4) COLOR = COLOR_4;
	
	float w_COLOR = 10+10+10+128+10;
	float h_COLOR = 5+20*3+5;
	
	Draw_Box(x_COLOR, y_COLOR-12, 0, 0, 16, 10, COLOR, NO);
	
	if(x_COLOR + w_COLOR > 848) x_COLOR -= w_COLOR;
	
	Draw_Box(x_COLOR, y_COLOR, 0, 0, w_COLOR, h_COLOR, 0x888888FF, NO);
	
	Draw_Box(x_COLOR+10+10+10, y_COLOR+5+9			, 0, 0, 128, 2, 0x444444FF, NO);
	Draw_Box(x_COLOR+10+10+10, y_COLOR+5+20+9		, 0, 0, 128, 2, 0x444444FF, NO);
	Draw_Box(x_COLOR+10+10+10, y_COLOR+5+20+20+9	, 0, 0, 128, 2, 0x444444FF, NO);
	
	u32 curs_color;
	float e;
	
	if(C_pos == 0) {curs_color = WHITE; e=12;} else {curs_color = 0x666666FF; e=8;}
	Draw_Box(x_COLOR+10+5-e/2, y_COLOR+5+10-e/2, 0, 0, e, e, RED, NO);
	Draw_Box(x_COLOR+10+10+10 + GetRED(COLOR)/2 - 2, y_COLOR+5+10-4, 0, 0, 4, 8, curs_color, NO);
	
	if(C_pos == 1) {curs_color = WHITE; e=12;} else {curs_color = 0x666666FF; e=8;}
	Draw_Box(x_COLOR+10+5-e/2, y_COLOR+5+20+10-e/2, 0, 0, e, e, GREEN, NO);
	Draw_Box(x_COLOR+10+10+10 + GetGREEN(COLOR)/2 - 2, y_COLOR+5+20+10-4, 0, 0, 4, 8, curs_color, NO);
	
	if(C_pos == 2) {curs_color = WHITE; e=12;} else {curs_color = 0x666666FF; e=8;}
	Draw_Box(x_COLOR+10+5-e/2, y_COLOR+5+20+20+10-e/2, 0, 0, e, e, BLUE, NO);
	Draw_Box(x_COLOR+10+10+10 + GetBLUE(COLOR)/2 - 2, y_COLOR+5+20+20+10-4, 0, 0, 4, 8, curs_color, NO);	
}

u8 input_COLOR(int n)
{
	u32 COLOR=0;
	if(n==1) COLOR = COLOR_1; else
	if(n==2) COLOR = COLOR_2; else
	if(n==3) COLOR = COLOR_3; else
	if(n==4) COLOR = COLOR_4;
	
	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_R2) {
		scroll_speed = 6 - paddata.PRE_R2/50;
	} else scroll_speed=6;
	
	if(new_pad & BUTTON_UP || (old_pad & BUTTON_UP && slow_it==0)) {
		if(C_pos==0) C_pos=2;
		else C_pos--;
	}
	
	if(new_pad & BUTTON_DOWN || (old_pad & BUTTON_DOWN && slow_it==0)) {
		if(C_pos==2) C_pos=0;
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
		}
	}
		
	if(n==1) COLOR_1 = COLOR; else
	if(n==2) COLOR_2 = COLOR; else
	if(n==3) COLOR_3 = COLOR; else
	if(n==4) COLOR_4 = COLOR;
		
	if(new_pad & BUTTON_CIRCLE) {
		return BREAK;
	}
	
	return CONTINUE;
}

void Draw_COLOR_input()
{
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	x=DrawButton(x, y, "Set color", BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT);
	x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
}

void Draw_ChooseColor(u8 n)
{
	while(1)
	{
		cls();
		Draw_scene();
		
		Draw_RGB_box(n);
		Draw_COLOR_input();
		
		tiny3d_Flip();
		
		ps3pad_read();
				
		if(input_COLOR(n) == BREAK) return;
	}
}

void close_SETTINGS()
{
	write_setting();
	Draw_MENU_input = &EmptyFunc;
	input_MENU = &EmptyFunc;
	MENU=NO;
}

void init_SETTINGS()
{
	int i;
	
	init_MENU();
	
	add_title_MENU("Global settings");
	
	add_item_MENU("Adjust screen", ITEM_TEXTBOX);
	
	add_item_MENU("Download covers", ITEM_TEXTBOX);
	
	if(path_info("/dev_hdd0/plugins") == _DIRECTORY) {
		add_item_MENU("Plugins Manager", ITEM_TEXTBOX);
	}
	
	add_item_MENU("Dir. to scan", ITEM_TEXTBOX);
	for(i=0; i <= scan_dir_number; i++) {
		add_item_value_MENU(scan_dir[i]);
	}
	
	add_item_MENU("XMB Priority", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = XMB_priority;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU("Game SideMenu", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = use_sidemenu;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU("Show Cover", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Show_COVER;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;

	add_item_MENU("Show PIC1", ITEM_TEXTBOX);
	add_item_value_MENU("No");
	add_item_value_MENU("Yes");
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Show_PIC1;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU("UI", ITEM_TEXTBOX);
	for(i=0; i < 4; i++) {
		add_item_value_MENU(UI[i]);
	}
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = UI_position;
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_title_MENU("Themes settings");
	
	add_item_MENU("Themes", ITEM_TEXTBOX);
	for(i=0; i <= Themes_number[UI_position]; i++) {
		add_item_value_MENU(Themes_Names_list[UI_position][i]);
	}
	ITEMS_VALUE_POSITION[ITEMS_NUMBER] = Themes_position[UI_position];
	ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	
	add_item_MENU("Color 1", ITEM_COLORBOX);
	memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &COLOR_1, 4);
	
	add_item_MENU("Color 2", ITEM_COLORBOX);
	ITEMS_VALUE_NUMBER[ITEMS_NUMBER]++;
	memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &COLOR_2, 4);
	
	add_item_MENU("Color 3", ITEM_COLORBOX);
	ITEMS_VALUE_NUMBER[ITEMS_NUMBER]++;
	memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &COLOR_3, 4);

	add_item_MENU("Color 4", ITEM_COLORBOX);
	ITEMS_VALUE_NUMBER[ITEMS_NUMBER]++;
	memcpy(ITEMS_VALUE[ITEMS_NUMBER][0], &COLOR_4, 4);
	
	if(UI_position!=XMB)
	add_title_MENU("User interface settings");
	
	if(UI_position==LIST) {
		add_item_MENU("Show ICON0", ITEM_TEXTBOX);
		add_item_value_MENU("No");
		add_item_value_MENU("Yes");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = LIST_Show_ICON0;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	}
	else if(UI_position==GRID) {
	
		add_item_MENU("Grid type", ITEM_TEXTBOX);
		add_item_value_MENU("Scroll");
		add_item_value_MENU("Page");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = grid_type;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU("Direction", ITEM_TEXTBOX);
		add_item_value_MENU("Vertical");
		add_item_value_MENU("Horizontal");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = direction;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU("Animated", ITEM_TEXTBOX);
		add_item_value_MENU("No");
		add_item_value_MENU("Yes");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = animated;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU("Keep proportion", ITEM_TEXTBOX);
		add_item_value_MENU("No");
		add_item_value_MENU("Yes");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = keep_prop;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU("Number of columns", ITEM_TEXTBOX);
		for(i=0; i < 16; i++) {
			char tmp[3];
			sprintf(tmp, "%d", i);
			add_item_value_MENU(tmp);
		}
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = grid_nb_columns;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		if(keep_prop==NO) {
			add_item_MENU("Number of lines", ITEM_TEXTBOX);
			for(i=0; i < 16; i++) {
				char tmp[3];
				sprintf(tmp, "%d", i);
				add_item_value_MENU(tmp);
			}
			ITEMS_VALUE_POSITION[ITEMS_NUMBER] = grid_nb_lines;
			ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		}
	} 
	else if(UI_position==FLOW) {
		
		add_item_MENU("Inverse button", ITEM_TEXTBOX);
		add_item_value_MENU("No");
		add_item_value_MENU("Yes");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = FLOW_inverse_button;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
		
		add_item_MENU("Use Cover", ITEM_TEXTBOX);
		add_item_value_MENU("No");
		add_item_value_MENU("Yes");
		ITEMS_VALUE_POSITION[ITEMS_NUMBER] = FLOW_use_Cover;
		ITEMS_VALUE_SHOW[ITEMS_NUMBER] = YES;
	}
}

void SETTINGS_UPDATE()
{
	if(strcmp(ITEMS[ITEMS_POSITION], "Dir. to scan") == 0) {
		scan_dir_position = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], "XMB Priority") == 0) {
		XMB_priority = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Game SideMenu") == 0) {
		use_sidemenu = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "UI") == 0) {
		UI_position = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Themes") == 0) {
		Themes_position[UI_position] = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else
	if(strcmp(ITEMS[ITEMS_POSITION], "Show Cover") == 0) {
		Show_COVER = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Show PIC1") == 0) {
		Show_PIC1 = ITEMS_VALUE_POSITION[ITEMS_POSITION];
	}
	
	if(UI_position==LIST) {
		if(strcmp(ITEMS[ITEMS_POSITION], "Show ICON0") == 0) {
			LIST_Show_ICON0 = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		}
	} else 
	if(UI_position==GRID) {
		if(strcmp(ITEMS[ITEMS_POSITION], "Grid type") == 0) {
			grid_type = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		} else 
		if(strcmp(ITEMS[ITEMS_POSITION], "Direction") == 0) {
			direction = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		} else
		if(strcmp(ITEMS[ITEMS_POSITION], "Animated") == 0) {
			animated = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		} else 
		if(strcmp(ITEMS[ITEMS_POSITION], "Keep proportion") == 0) {
			keep_prop = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		} else
		if(strcmp(ITEMS[ITEMS_POSITION], "Number of columns") == 0) {
			grid_nb_columns = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		} else 
		if(strcmp(ITEMS[ITEMS_POSITION], "Number of lines") == 0) {
			grid_nb_lines = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		}
	} else 
	if(UI_position==FLOW) {
		if(strcmp(ITEMS[ITEMS_POSITION], "Inverse button") == 0) {
			FLOW_inverse_button = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		} else
		if(strcmp(ITEMS[ITEMS_POSITION], "Use Cover") == 0) {
			FLOW_use_Cover = ITEMS_VALUE_POSITION[ITEMS_POSITION];
		}
	}
	
	init_SETTINGS();
}

u8 SETTINGS_CROSS()
{
	if(strcmp(ITEMS[ITEMS_POSITION], "Adjust screen") == 0) {
		Draw_AdjustScreen();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Download covers") == 0) {
		start_loading();
		Download_covers();
		end_loading();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Dir. to scan") == 0) {
		char tmpName[128];
		if(Get_OSK_String("New Directory", tmpName, 128) == SUCCESS) {
			if(tmpName[0]!=0) {
				scan_dir_number++;
				strcpy(scan_dir[scan_dir_number], tmpName);
				write_scan_dir();
			}
		}
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Plugins Manager") == 0) {
		open_PLUGINS_MANAGER();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Themes") == 0) {
		start_loading();
		print_load("Loading theme...");
		u8 ret = ExtractTheme();
		if(ret==SUCCESS) {
			strcpy(Themes[UI_position], Themes_Names_list[UI_position][Themes_position[UI_position]]);		
			Load_Themes();
			start_Load_GamePIC();
		} else print_load("Failed to extract theme");
		end_loading();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Color 1") == 0) {
		Draw_ChooseColor(1);
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Color 2") == 0) {
		Draw_ChooseColor(2);
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Color 3") == 0) {
		Draw_ChooseColor(3);
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Color 4") == 0) {
		Draw_ChooseColor(4);
	}
	
	return CONTINUE;
}

u8 SETTINGS_SQUARE()
{
	if(strcmp(ITEMS[ITEMS_POSITION], "Color 1") == 0) {
		COLOR_1 = WHITE;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Color 2") == 0) {
		COLOR_2 = GREEN;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Color 3") == 0) {
		COLOR_3 = ORANGE;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Color 4") == 0) {
		COLOR_4 = RED;
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Themes") == 0) {
		u8 ThemeType = GetThemeType(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
		if(ThemeType == MGZ) {
			char tmpName[128];
			strcpy(tmpName, Themes_Names_list[UI_position][Themes_position[UI_position]]);
			if(Get_OSK_String("Rename", tmpName, 128) == SUCCESS) {
				char old[128], new[128];
				sprintf(old, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position], Themes_Names_list[UI_position][Themes_position[UI_position]]);
				sprintf(new, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position], tmpName);
				if( rename(old, new) == 0 ) {
					strcpy(Themes_Names_list[UI_position][Themes_position[UI_position]], tmpName);
					show_msg("Theme renamed");
				} else show_msg("Failed");	
			}	
		}
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Dir. to scan") == 0) {
		if(Get_OSK_String("Rename", scan_dir[scan_dir_position], 64) == SUCCESS) {
			if(scan_dir[scan_dir_position][0] != 0) {
				write_scan_dir();
			}
		}
	}
	
	return CONTINUE;
}

u8 SETTINGS_TRIANGLE()
{
	if(strcmp(ITEMS[ITEMS_POSITION], "Themes") == 0) {
		start_loading();
		
		if(strcmp(Themes_Names_list[UI_position][Themes_position[UI_position]], Themes[UI_position]) != 0) {
			
			char locPath[128];
			sprintf(locPath, "/dev_hdd0/game/%s/USRDIR/GUI/%s/%s", ManaGunZ_id, UI[UI_position], Themes_Names_list[UI_position][Themes_position[UI_position]]);
			Delete(locPath);
			
			Delete(Themes_Paths_list[UI_position][Themes_position[UI_position]]);
			
			if(path_info(Themes_Paths_list[UI_position][Themes_position[UI_position]]) == _NOT_EXIST) {
				GetThemes();
				if(Themes_position[UI_position] > Themes_number[UI_position]) Themes_position[UI_position]=Themes_number[UI_position];
				show_msg("Theme removed");
				init_SETTINGS();
			} else show_msg("Failed");
		} else show_msg("Theme used");
		
		end_loading();
	} else 
	if(strcmp(ITEMS[ITEMS_POSITION], "Dir. to scan") == 0) {
		if(scan_dir_number>0) {
			int i;
			for(i=scan_dir_position; i < scan_dir_number; i++) {
				strcpy(scan_dir[i], scan_dir[i+1]);
			}
			memset(scan_dir[scan_dir_number], 0, sizeof(scan_dir[scan_dir_number]));
			if(scan_dir_number==scan_dir_position) scan_dir_position--;
			scan_dir_number--;
			write_scan_dir();
			init_SETTINGS();
		}
	}
	
	return CONTINUE;
}

void input_SETTINGS()
{
	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_R2) {
		scroll_speed = 6 - paddata.PRE_R2/50;
	} else scroll_speed = 6;

	
	if(new_pad & BUTTON_UP || ((old_pad & BUTTON_UP) && slow_it==0)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == 0) ITEMS_POSITION = ITEMS_NUMBER;
			else ITEMS_POSITION--;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		}
	}
	
	if(new_pad & BUTTON_DOWN || ((old_pad & BUTTON_DOWN) && slow_it==0)) {
		if(IN_ITEMS_VALUE == NO) {
			if(ITEMS_POSITION == ITEMS_NUMBER) ITEMS_POSITION = 0;
			else ITEMS_POSITION++;
		} else {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		}
	}
	
	SETTINGS_UPDATE();
	
	if(new_pad & BUTTON_CROSS) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			IN_ITEMS_VALUE = YES;
		} else {
			if(SETTINGS_CROSS() == BREAK) close_SETTINGS();
		}
	} else
	if(new_pad & BUTTON_SQUARE) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == 0) ITEMS_VALUE_POSITION[ITEMS_POSITION] = ITEMS_VALUE_NUMBER[ITEMS_POSITION];
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]--;
		} else {
			if(SETTINGS_SQUARE() == BREAK) close_SETTINGS();
		}
	} else
	if(new_pad & BUTTON_TRIANGLE) {
		if(IN_ITEMS_VALUE == NO && ITEMS_VALUE_NUMBER[ITEMS_POSITION] != -1) {
			if(ITEMS_VALUE_POSITION[ITEMS_POSITION] == ITEMS_VALUE_NUMBER[ITEMS_POSITION]) ITEMS_VALUE_POSITION[ITEMS_POSITION] = 0 ;
			else ITEMS_VALUE_POSITION[ITEMS_POSITION]++;
		} else {
			if(SETTINGS_TRIANGLE() == BREAK) close_SETTINGS();
		}
	} else
	if(new_pad & BUTTON_CIRCLE) {
		if(IN_ITEMS_VALUE == NO) close_SETTINGS();
		else {
			init_SETTINGS();
			IN_ITEMS_VALUE = NO;
		}
	}
}

void Draw_SETTINGS_input()
{
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	if(IN_ITEMS_VALUE == YES) {
		if(strcmp(ITEMS[ITEMS_POSITION], "Dir. to scan") == 0) {
			x=DrawButton(x, y, "Add", BUTTON_CROSS);
			if(scan_dir_number>0) {
				x=DrawButton(x, y, "Delete", BUTTON_TRIANGLE);
				x=DrawButton(x, y, "Rename", BUTTON_SQUARE);
			}
		} else
		if(strcmp(ITEMS[ITEMS_POSITION], "Themes") == 0) {
			x=DrawButton(x, y, "Load", BUTTON_CROSS);
			x=DrawButton(x, y, "Delete", BUTTON_TRIANGLE);
			u8 ThemeType = GetThemeType(Themes_Paths_list[UI_position][ITEMS_VALUE_POSITION[ITEMS_POSITION]]);
			if(ThemeType == MGZ) {
				x=DrawButton(x, y, "Rename", BUTTON_SQUARE);
			}
		}		
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	} else {
		if(strstr(ITEMS[ITEMS_POSITION], "Color") != NULL) {
			x=DrawButton(x, y, "Change", BUTTON_CROSS);
			x=DrawButton(x, y, "Reset", BUTTON_SQUARE);
		} else {
			x=DrawButton(x, y, "Enter", BUTTON_CROSS);
			x=DrawButton(x, y, "Change", BUTTON_SQUARE);
		}
		x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
	}

}

void open_SETTINGS()
{
	start_loading();
	read_scan_dir();
	read_setting();
	ITEMS_POSITION=0;
	IN_ITEMS_VALUE = NO;
	memset(ITEMS_VALUE_POSITION, 0, sizeof(ITEMS_VALUE_POSITION));
	init_SETTINGS();
	MENU_SIDE=NO;
	Draw_MENU_input = &Draw_SETTINGS_input;
	input_MENU = &input_SETTINGS;
	end_loading();
	MENU=YES;
}

//*******************************************************
// MODE AutoMount
//*******************************************************

u8 is_AutoMount()
{

	FILE *fp;
	
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
	
	game_number=0;
	
	print_load("AutoMount = %s", list_game_path[0]);
	
	strcpy(GamPath, list_game_path[0]);
	GetParamSFO("TITLE", list_game_title[0], 0, NULL);

	if(change_IDPS == YES) poke_IDPS();

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
		while(1) {
			cls();
			
			int x=50, y=40;
			SetFontAutoCenter(0);
			SetFontSize(20,20);
			SetFontColor(RED, 0x0);
			
			DrawString(x, y, "Error : Game Not Found");
			y+=20;
			DrawFormatString(x, y, "Path = %s", list_game_path[0]);
			
			SetFontColor(COLOR_1, 0x0);
			SetFontSize(15, 15);
			
			DrawButton(25, 485, "Back to XMB", BUTTON_CIRCLE);
		
			tiny3d_Flip();
			
			ps3pad_read();
			
			if(new_pad & BUTTON_CIRCLE) {
				ioPadEnd();
				exit(0);
			}
		}
	}
	
	sleep(1);
	iso = is_iso(GamPath);
	
	if(gui_called==YES) {
		end_loading();
		
		open_GameMenu();
		
		while(MENU){
			cls();
			
			Draw_MENU();
			Draw_MENU_input();
		
			check_device();
		
			tiny3d_Flip();
		
			ps3pad_read();

			input_MENU();
		}
		
		write_AutoMount_setting(GamPath);
	}

	if(payload==IRIS) iris_Mount(); else
	if(payload==MM) mm_Mount(); else
	if(cobra) cobra_Mount(); else 
	mamba_Mount();
	
	if(clean_syscall) remove_cfw_syscalls();

	if(direct_boot) {
		if(mount_app_home == NO) {
			sysProcessExitSpawn2("/dev_bdvd/PS3_GAME/USRDIR/EBOOT.BIN", NULL, NULL, NULL, 0, 64, SYS_PROCESS_SPAWN_STACK_SIZE_128K);
		} else {
			sysProcessExitSpawn2("/app_home/PS3_GAME/USRDIR/EBOOT.BIN", NULL, NULL, NULL, 0, 64, SYS_PROCESS_SPAWN_STACK_SIZE_128K);
		}
	}		
	
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
	position=0;
	for(position=0; position<=game_number; position++) {
		if(Show_it(position)==YES) break;
	}
	Grid_curs_move_x=0;
	Grid_curs_move_y=0;
	Grid_move=0;
	first_icon=position;
	Flow_curs_move_x = 0;
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
	
	float x=25;
	float y=485;
	SetFontSize(15, 15);
	SetFontColor(COLOR_1, 0x0);
	SetFontZ(0);
	
	x=DrawButton(x, y, "Check/Uncheck", BUTTON_CROSS);
	x=DrawButton(x, y, "Back", BUTTON_CIRCLE);
}

void Draw_filter()
{
	if(filter==NO) return;
	
	SetFontZ(0);
	u32 color=0;
	float x=700;
	float y=300;
	
	Draw_Box(x, y, 0, 10, 100, 115, GREY, NO);
	SetFontSize(18, 18);
	SetFontColor(COLOR_3, 0x0);
	DrawStringFromCenterX(x+50, y+5, "FILTER");
	Draw_Box(x+5, y+23, 0, 0, 90, 2, WHITE, NO);
	SetFontSize(15, 15);
	x+=8;
	y+=33;
	if(filter_position==0) color = COLOR_2; else color = COLOR_1;
	Draw_checkbox(Only_FAV, x+5, y, "Favorite", color);
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
	
	SetFontColor(COLOR_1, 0x0);
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
			scroll_speed = 6 + y_L/20;
		}
	} else 
	if (28 < y_L) {
		if(old_y == 0) new_pad |= BUTTON_DOWN; else
		{
			old_pad |= BUTTON_DOWN;
			scroll_speed = 6 - y_L/20;
		}
	} else 
	if (x_L < -28) {
		if(old_x == 0) new_pad |= BUTTON_LEFT; else
		{
			old_pad |= BUTTON_LEFT;
			scroll_speed = 6 + x_L/20 ;
		}
	} else 
	if (28 < x_L) {
		if(old_x == 0) new_pad |= BUTTON_RIGHT; else
		{
			old_pad |= BUTTON_RIGHT;
			scroll_speed = 6 - x_L/20;
		}
	} else { 
		x_L=0; y_L=0;
		if(old_pad & BUTTON_R2) {
			scroll_speed = 6 - paddata.PRE_R2/50;
		} else scroll_speed=6;
	}
	
	if((old_pad & BUTTON_LEFT) || (old_pad & BUTTON_RIGHT) || (old_pad & BUTTON_UP) || (old_pad & BUTTON_DOWN)) {
		hold_it++;
		if(hold_it>30) {
			slow_it++;
			if(slow_it>scroll_speed) slow_it=0;
		}
	} else {slow_it=1; hold_it=0;}
	
	if(old_pad & BUTTON_CIRCLE) {
		hold_CIRCLE++;
		if(hold_CIRCLE>100) {
			if(Load_GamePIC==YES) end_Load_GamePIC();
			end_load_PIC1();
			end_checking();
			sysModuleUnload(SYSMODULE_PNGDEC);
			sysModuleUnload(SYSMODULE_JPGDEC);
			ioPadEnd();
			exit(0);
		}
	} else hold_CIRCLE=0;
	
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
			if(Load_GamePIC==YES) end_Load_GamePIC();
			end_load_PIC1();
			end_checking();
			
			start_loading();	
			
			strcpy(GamPath, list_game_path[position]);
				
			print_load("Mounting %s", list_game_title[position]);
				
			if(list_game_platform[position] == _ISO_PS3 || list_game_platform[position] == _JB_PS3) {
					
				read_game_setting(list_game_title[position]);
				
				if(payload==IRIS) iris_Mount(); else
				if(payload==MM) mm_Mount(); else
				if(cobra) cobra_Mount(); else
				mamba_Mount();
				
				if(change_IDPS) poke_IDPS();	
				if(clean_syscall) remove_cfw_syscalls();	

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
			} else {
				int emul;
				
				if(list_game_platform[position] == _ISO_PS2) emul = EMU_PS2_DVD;
				if(list_game_platform[position] == _ISO_PS1) emul = EMU_PSX;
				if(list_game_platform[position] == _ISO_PSP) emul = EMU_PSP;
				
				if(!cobra && !mamba) mamba = install_mamba();
				
				if(emul == EMU_PS2_DVD) patch_PS2();
				if(emul == EMU_PS2_DVD) use_CONFIG();
				
				cobra_MountISO(emul);
				cobra_MountISO(emul);
			}
			
			end_loading();
			
			sysModuleUnload(SYSMODULE_PNGDEC);
			sysModuleUnload(SYSMODULE_JPGDEC);
			ioPadEnd();
			
			exit(0);
		} else show_msg("TODO");
	}
	
	if(new_pad & BUTTON_TRIANGLE && Game_stuff == YES) {
		open_GameMenu();
	}
	
	if(new_pad & BUTTON_SELECT) {
		Draw_FileExplorer(NULL);
	}
	
	if(new_pad & BUTTON_SQUARE && UI_position!=XMB) {
		open_filter();
	}
	
	if(new_pad & BUTTON_START) {
		open_SETTINGS();
	}
	
	if(UI_position==LIST) {
		if(new_pad & BUTTON_UP || ((old_pad & BUTTON_UP) && slow_it==0)) {
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
		if(new_pad & BUTTON_DOWN || ((old_pad & BUTTON_DOWN) && slow_it==0)) {
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
		if( ((new_pad & BUTTON_UP   || ((old_pad & BUTTON_UP)   && slow_it==0)) && direction==HORIZONTAL)  ||
			((new_pad & BUTTON_LEFT || ((old_pad & BUTTON_LEFT) && slow_it==0)) && direction==VERTICAL  )  )
		{
			j=-1;
			for(i=position; i>=0;i--){
				if(Show_it(i)==NO) continue;
				j++;
				position=i;
				if(j==1) break;
			}
		}
		if( ((new_pad & BUTTON_DOWN  || ((old_pad & BUTTON_DOWN)  && slow_it==0)) && direction==HORIZONTAL)  ||
			((new_pad & BUTTON_RIGHT || ((old_pad & BUTTON_RIGHT) && slow_it==0)) && direction==VERTICAL  )  )
		{
			j=-1;
			for(i=position; i<=game_number;i++){
				if(Show_it(i)==NO) continue;
				j++;
				position=i;
				if(j==1) break;
			}
		}
		if( ((new_pad & BUTTON_LEFT || ((old_pad & BUTTON_LEFT) && slow_it==0)) && direction==HORIZONTAL)  ||
			((new_pad & BUTTON_UP   || ((old_pad & BUTTON_UP)   && slow_it==0)) && direction==VERTICAL  )  )
		{
			j=-1;
			for(i=position; i>=0;i--){
				if(Show_it(i)==NO) continue;
				j++;
				position=i;
				if(direction==VERTICAL   && j==grid_nb_columns) break;
				if(direction==HORIZONTAL && j==grid_nb_lines) break;
			}
		}
		if( ((new_pad & BUTTON_RIGHT || ((old_pad & BUTTON_RIGHT) && slow_it==0)) && direction==HORIZONTAL)  ||
			((new_pad & BUTTON_DOWN  || ((old_pad & BUTTON_DOWN)  && slow_it==0)) && direction==VERTICAL  )  )
		{
			j=-1;
			for(i=position; i<=game_number;i++){
				if(Show_it(i)==NO) continue;
				j++;
				position=i;
				if(direction==VERTICAL   && j==grid_nb_columns) break;
				if(direction==HORIZONTAL && j==grid_nb_lines) break;
			}
		}	
		if( (new_pad & BUTTON_UP	|| ((old_pad & BUTTON_UP)	&& slow_it==0)) ||
			(new_pad & BUTTON_DOWN  || ((old_pad & BUTTON_DOWN)  && slow_it==0)) ||
			(new_pad & BUTTON_LEFT  || ((old_pad & BUTTON_LEFT)  && slow_it==0)) ||
			(new_pad & BUTTON_RIGHT || ((old_pad & BUTTON_RIGHT) && slow_it==0))   )
		{
			if(grid_type == SCROLL) {
				speed = 9;
				if(position < first_icon) {
					j=-1;
					for(i=first_icon; i>=0; i--){
						if(Show_it(i)==NO) continue;
						j++;
						first_icon=i;
						if(j==grid_nb_lines) break;
					}
					if(direction==HORIZONTAL) {
						if(animated == YES) Grid_move -= w_ICON0 + e_w ;
						else Grid_curs_move_x += w_ICON0 + e_w ;
					} else
					if(direction==VERTICAL) {
						if(animated == YES) Grid_move -= h_ICON0 + e_h ;
						else Grid_curs_move_y += h_ICON0 + e_h ;
					}
				}
				if(position > last_icon) {
					j=-1;
					for(i=last_icon; i<=game_number; i++){
						if(Show_it(i)==NO) continue;
						j++;
						last_icon=i;
						if(direction==VERTICAL   && j==grid_nb_columns) break;
						if(direction==HORIZONTAL && j==grid_nb_lines) break;
					}
					j=-1;
					for(i=first_icon; i<=game_number; i++){
						if(Show_it(i)==NO) continue;
						j++;
						first_icon=i;
						if(direction==VERTICAL   && j==grid_nb_columns) break;
						if(direction==HORIZONTAL && j==grid_nb_lines) break;
					}
					if(direction==HORIZONTAL) {
						if(animated == YES) Grid_move += w_ICON0 + e_w ;
						else Grid_curs_move_x -= w_ICON0 + e_w ;
					} else
					if(direction==VERTICAL) {
						if(animated == YES) Grid_move += h_ICON0 + e_h ;
						else Grid_curs_move_y -= h_ICON0 + e_h ;
					}
				}
			} else
			if(grid_type == PAGE) {
				speed = 18;
				if(position < first_icon) {
					j=-1;
					for(i=first_icon; i>=0; i--){
						if(Show_it(i)==NO) continue;
						j++;
						first_icon=i;
						if(j==nb_icon) break;
					}
					if(direction==HORIZONTAL) {
						if(animated == YES) Grid_move -= (w_ICON0 + e_w) * grid_nb_columns ;
						else Grid_curs_move_x += (w_ICON0 + e_w) * grid_nb_columns;
					} else
					if(direction==VERTICAL) {
						if(animated == YES) Grid_move -= (h_ICON0 + e_h) * grid_nb_lines ;
						else Grid_curs_move_y += (h_ICON0 + e_h) * grid_nb_lines;
					}
				}
				if(position > last_icon) {
					j=-1;
					for(i=last_icon; i<=game_number; i++){
						if(Show_it(i)==NO) continue;
						j++;
						if(j==1) {first_icon=i;	break;}
					}
					if(direction==HORIZONTAL) {
						if(animated == YES) Grid_move += (w_ICON0 + e_w) * grid_nb_columns;
						else Grid_curs_move_x -= (w_ICON0 + e_w) * grid_nb_columns;
					} else
					if(direction==VERTICAL) {
						if(animated == YES) Grid_move += (h_ICON0 + e_h) * grid_nb_lines;
						else Grid_curs_move_y -= (h_ICON0 + e_h) * grid_nb_lines;
					}
				}
			}
		}
	} else
	if(UI_position==XMB) {
		if(new_pad & BUTTON_LEFT || ((old_pad & BUTTON_LEFT) && slow_it==0) ) {
			if(XMB_H_position > 0) XMB_H_position--;
		}
		if(new_pad & BUTTON_RIGHT || ((old_pad & BUTTON_RIGHT) && slow_it==0) ) {
			if(XMB_H_position < 5) XMB_H_position++;
		}
		if(new_pad & BUTTON_UP || ((old_pad & BUTTON_UP) && slow_it==0) ) {
			if(XMB_V_position[XMB_H_position] == 0 && XMB_nb_lin[XMB_H_position] != 0) {
				XMB_V_position[XMB_H_position] = XMB_nb_lin[XMB_H_position];
				XMB_curs_move_y[XMB_H_position] = (XMB_h - XMB_h*(XMB_V_position[XMB_H_position]-1)) - 200; 
			} 
			else if(XMB_V_position[XMB_H_position] > 0) XMB_V_position[XMB_H_position]--;
		}
		if(new_pad & BUTTON_DOWN  || ((old_pad & BUTTON_DOWN) && slow_it==0) ) {
			if(XMB_V_position[XMB_H_position] == XMB_nb_lin[XMB_H_position] && XMB_nb_lin[XMB_H_position] != 0) {
				XMB_V_position[XMB_H_position] = 0;
				XMB_curs_move_y[XMB_H_position] = 0; 
			} else if(XMB_V_position[XMB_H_position] < XMB_nb_lin[XMB_H_position]) XMB_V_position[XMB_H_position]++;
		}
	} else
	if(UI_position==FLOW) {
		if( (FLOW_inverse_button==NO  && (new_pad & BUTTON_RIGHT || ((old_pad & BUTTON_RIGHT) && slow_it==0))) ||
			(FLOW_inverse_button==YES && (new_pad & BUTTON_LEFT  || ((old_pad & BUTTON_LEFT)  && slow_it==0)))   ) 
		{
			for(i=0; i<game_number;i++) {
				position--;
				
				if(position < 0) {
					j=-1;
					for(k=0; k<=game_number; k++) {
						if(Show_it(k) == NO) continue;
						j++;
						position=k;
						if(j==0) Flow_curs_move_x = 0;
						else Flow_curs_move_x = - 2*FLOW_w - FLOW_w*(j-1);
					}
				}
				
				if(Show_it(position) == YES) break;
			}
		}
		if( (FLOW_inverse_button==NO  && (new_pad & BUTTON_LEFT   || ((old_pad & BUTTON_LEFT ) && slow_it==0))) ||
			(FLOW_inverse_button==YES && (new_pad & BUTTON_RIGHT  || ((old_pad & BUTTON_RIGHT) && slow_it==0)))   ) 
		{
			for(i=0; i<game_number;i++) {
				position++;
				if(position > game_number) {
					for(k=0; k<=game_number; k++) {
						if(Show_it(k) == NO) continue;
						position=k;
						Flow_curs_move_x = 0;
						break;
					}
				}
				if(Show_it(position) == YES) break;
			}
		}
	}
}

void Draw_MAIN_input()
{
	if(MENU==YES) return;
	if(filter==YES) return;
	
	int x=25, y=485;
	
	SetFontColor(COLOR_1, 0x0);
	SetFontSize(15, 15);
	x=DrawButton(x, y, "Settings", BUTTON_START);
	if(Game_stuff==YES) {
		x=DrawButton(x, y, "Game Menu", BUTTON_TRIANGLE);
		x=DrawButton(x, y, "Mount game", BUTTON_CROSS);
	}
	if(UI_position!=XMB) {
		x=DrawButton(x, y, "Filter", BUTTON_SQUARE);
	}
	x=DrawButton(x, y, "File Manager", BUTTON_SELECT);
		
	SetFontColor(COLOR_4, 0x0);
	x=DrawString( x+10, y, "Hold");
	SetFontColor(COLOR_1, 0x0);
	x=Draw_Button_Circle(x+5, y, 15);
	x=DrawString( x+5, y, "Back to XMB ");
	if(hold_CIRCLE != 0) {
		SetFontColor(COLOR_3, 0x0);
		x=DrawFormatString( x+5, y, "in %d", (100 - hold_CIRCLE)/30);
		SetFontColor(COLOR_1, 0x0);
	}
	x=750;
	
	if(Game_stuff == YES) {
		if(usb==YES) {
			int t;
			sscanf(list_game_path[position], "/dev_usb%d%*s" , &t);
			x = Draw_USB(x , y, 20, COLOR_1, t);
		}
		if(is_ntfs(list_game_path[position]) == YES) {
			int t;
			sscanf(list_game_path[position], "/ntfs%d%*s" , &t);
			SetFontColor(COLOR_3, 0x0);
			x = DrawString(x, y, "NTFS ");
			x = Draw_USB(x , y, 20, COLOR_3 , t);
		}
		
		if(list_game_platform[position] == _ISO_PS3) {
			Draw_DISK( x + 5, y, 0, 20, COLOR_PS3);
		} else
		if(list_game_platform[position] == _ISO_PS2) {
			Draw_DISK( x + 5, y, 0, 20, COLOR_PS2);
		} else
		if(list_game_platform[position] == _ISO_PS1) {
			Draw_DISK( x + 5, y, 0, 20, COLOR_PS1);
		} else
		if(list_game_platform[position] == _ISO_PSP) {
			Draw_DISK( x + 5, y, 0, 20, COLOR_PSP);
		}
	}
}

void Draw_MAIN()
{
	if(MENU==YES && MENU_SIDE == NO) return;
	
	SetFontZ(10);
	
	int x, y, i, j, k;
	
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
		SetFontColor(COLOR_1, 0x0);
		SetFontAutoCenter(0);
		SetFontSize(size_font,size_font);
	
		nb_line = (460 - y - size_font) / size_font;
		
		SetFontZ(105);
		
		int j=0;
		for(i=first_line;  j <= nb_line; i++) {
			if(i>game_number) break;
			if(Show_it(i) == NO) continue;
			j++;
			
			if(i==position) SetFontColor(COLOR_2, 0x0);
			else SetFontColor(COLOR_1, 0x0);
			
			DrawFormatString(x, y, "%s", list_game_title[i]);
			y+=size_font;
		}
		SetFontZ(10);
		last_line=i-1;
		
		if(position<first_line) position = first_line;
		if(last_line<position) position = last_line;
	}
	else if (UI_position==GRID) {
	
		float x1, y1;
		
		x=20;
		y=20;
		
		float grid_w = X_MAX - 40;
		float grid_h = Y_MAX - 50;
		
		if(keep_prop == NO) {
			w_ICON0 = (grid_w - (grid_nb_columns-1) * e_w) / grid_nb_columns;  
			h_ICON0 = (grid_h - (grid_nb_lines-1) * e_h) / grid_nb_lines;
		}
		else {
			w_ICON0 = (grid_w - (grid_nb_columns-1) * e_w)/grid_nb_columns ; 
			h_ICON0 = w_ICON0/1.86;
			grid_nb_lines = (grid_h+e_h) / (e_h+h_ICON0);
		}
		
		nb_icon = grid_nb_lines * grid_nb_columns;
		
		j=0;
		for(i=first_icon; i<=game_number; i++){
			if(Show_it(i)==NO) continue;
			j++;
			last_icon=i;
			if(j==nb_icon) break;
		}
		
		y += (grid_h - (grid_nb_lines*(h_ICON0+e_h)-e_h))/2 ; // center

		//if(position>game_number) position = game_number ;// ex : si je debranche et rebranche le hdd ext

		y1=y; x1=x;
		
		if(direction == HORIZONTAL)  {
			if(Grid_move != 0) {
				if(Grid_move >= speed ) {Grid_curs_move_x -= speed; Grid_move -= speed;} else 
				if(Grid_move <= -speed) {Grid_curs_move_x += speed; Grid_move += speed;} else 
				{ Grid_curs_move_x -= Grid_move ; Grid_move = 0; }				
			}
				
			x += Grid_curs_move_x ;
		} else
		if(direction == VERTICAL)  {
			if(Grid_move != 0 ) {
				if(Grid_move >= speed ) {Grid_curs_move_y -= speed; Grid_move -= speed;} else 
				if(Grid_move <= -speed) {Grid_curs_move_y += speed; Grid_move += speed;} else 
				{ Grid_curs_move_y -= Grid_move ; Grid_move = 0; }
			}
			y += Grid_curs_move_y;
		}
		
		k=0;
		for(i = 0 ; i<=game_number ; i++) {
			if(Show_it(i)==NO) continue;
			k++;
			
			if(i==position) {
				Draw_ICON0(i, x, y, 100, w_ICON0, h_ICON0);
				Draw_Box(x-5, y-5, 101, 0, w_ICON0+10, h_ICON0+10, 0xFFFFFFFF, NO);
				Draw_Box(x, y, 101, 0, w_ICON0, h_ICON0, 0x000000FF, NO);
			} else {
				Draw_ICON0(i, x, y, 100, w_ICON0, h_ICON0);
				Draw_Box(x, y, 99, 0, w_ICON0, h_ICON0, 0xFFFFFF80, NO); 
			}
			
			if(direction == HORIZONTAL)  {
				y+= h_ICON0 + e_h;
				if(k==grid_nb_lines) {k=0; y = y1; x += w_ICON0 + e_w;}
			} else
			if(direction == VERTICAL)  {
				x+= w_ICON0 + e_w;
				if(k==grid_nb_columns) {k=0; x = x1; y += h_ICON0 + e_h;}
			}
		}
	}
	else if (UI_position==XMB) {
		
		if(XMB_H_position == COL_SET) Game_stuff = NO; else Game_stuff = YES;
		
		x = 250;
		y = 200;
		
		int position_x;
		int position_y;
		
		position_x = x - 90 * XMB_H_position;
		
		int slide_speed;
		
		if(0 <= scroll_speed && scroll_speed < 3) slide_speed = 40; else
		if(3 <= scroll_speed && scroll_speed < 6) slide_speed = 20; else
		slide_speed = 10;
		
		x += XMB_curs_move_x;
		
		if(position_x > x) XMB_curs_move_x+=slide_speed; else
		if(position_x < x) XMB_curs_move_x-=slide_speed;
		
		Draw_Col_header(x);
		
		if(XMB_V_position[XMB_H_position] == 0) {
			position_y = y;
		} else
		if(XMB_V_position[XMB_H_position] > 0) {
			position_y = XMB_h - XMB_h*(XMB_V_position[XMB_H_position]-1); 
		}
		
		y += XMB_curs_move_y[XMB_H_position];
		
		if(position_y > y) {
			if(y == 2*XMB_h) XMB_curs_move_y[XMB_H_position] += 120; else XMB_curs_move_y[XMB_H_position]+=slide_speed;
		}
		else if(position_y < y) {
			if(y==200-XMB_h) XMB_curs_move_y[XMB_H_position] -= 120; else XMB_curs_move_y[XMB_H_position]-=slide_speed;
		}
		
		SetFontZ(90);
		if(XMB_H_position==COL_FAV) {
			int real_FAV_game_number=-1;
			for(j = 0 ; j <= game_number ; j++) {
				if(is_favorite(list_game_path[j]) == NO) continue;
				
				real_FAV_game_number++;
				
				if(y>XMB_h && y<3*XMB_h) y=200-2*XMB_h+y ; else
				if(3*XMB_h<y && y<=200-XMB_h) y=XMB_h;else
				if(y==300-XMB_h) y=200;else
				if(y==2*XMB_h) y=200;
				
				if(200-XMB_h < y && y < 200+XMB_h) {
					position = j;
					if(MENU==NO) {
						Draw_ICON0(position, 250-XMB_w , y, 10, XMB_w*2, XMB_h*2);
						DrawFormatString(250+XMB_w+20, y+XMB_h-10, "%s", list_game_title[position]);
					} else {
						DrawFormatString(250+XMB_w+XMB_w+20, 200+XMB_h-10, "%s", list_game_title[position]);
					}
					y+=2*XMB_h + XMB_h/2;
					if(Show_COVER == YES) {
						Draw_COVER(j, 20, 200, 10, 138, 0);
					}
				}
				else {
					Draw_ICON0(j, 250-XMB_w/2, y, 100, XMB_w, XMB_h);
					y+=XMB_h;
				}
			}
			
			XMB_nb_lin[XMB_H_position] = real_FAV_game_number;
			if(real_FAV_game_number<0) Game_stuff = NO;
			if(XMB_V_position[XMB_H_position]>XMB_nb_lin[XMB_H_position]) XMB_V_position[XMB_H_position] = XMB_nb_lin[XMB_H_position];
			
			
		}
		else if(XMB_H_position==COL_PS3 || XMB_H_position==COL_PS2 || XMB_H_position==COL_PS1 || XMB_H_position==COL_PSP) {

			XMB_nb_lin[XMB_H_position]=-1;
			
			for(j = 0 ; j <= game_number ; j++) {
				if(XMB_H_position==COL_PS3 && (list_game_platform[j] !=_ISO_PS3 && list_game_platform[j] !=_JB_PS3)) continue;
				if(XMB_H_position==COL_PS2 && (list_game_platform[j] !=_ISO_PS2 && list_game_platform[j] !=_JB_PS2)) continue;
				if(XMB_H_position==COL_PS1 && (list_game_platform[j] !=_ISO_PS1 && list_game_platform[j] !=_JB_PS1)) continue;
				if(XMB_H_position==COL_PSP && (list_game_platform[j] !=_ISO_PSP && list_game_platform[j] !=_JB_PSP)) continue;
				
				XMB_nb_lin[XMB_H_position]++;
				
				if(y>XMB_h && y<3*XMB_h) y=200-2*XMB_h+y ; else
				if(3*XMB_h<y && y<=200-XMB_h) y=XMB_h;else
				if(y==300-XMB_h) y=200;else
				if(y==2*XMB_h) y=200;
				
				if(200-XMB_h < y && y < 200+XMB_h) {
					position = j;
					if(MENU==NO) {
						Draw_ICON0(position, 250-XMB_w , y, 10, XMB_w*2, XMB_h*2);
						DrawFormatString(250+XMB_w+20, y+XMB_h-10, "%s", list_game_title[position]);
					} else {
						DrawFormatString(250+XMB_w+XMB_w+20, 200+XMB_h-10, "%s", list_game_title[position]);
					}
					y=300;
					if(Show_COVER == YES) {
						Draw_COVER(position, 20, 200, 10, 138, 0);
					}
				}
				else {
					Draw_ICON0(j, 250-XMB_w/2, y, 100, XMB_w, XMB_h);
					y+=XMB_h;
				}
			}
			
			if(XMB_V_position[XMB_H_position]>XMB_nb_lin[XMB_H_position]) XMB_V_position[XMB_H_position] = XMB_nb_lin[XMB_H_position];
			
			if(XMB_nb_lin[XMB_H_position]==-1) Game_stuff=NO;
		}
			
		SetFontZ(10);
		
	}
	else if (UI_position==FLOW) {
		
		x=848/2;
		y=512/2;
		
		int FLOW_speed;
		
		int FLOW_position_x=x;
		float FLOW_a;
		int FLOW_slide_speed;
		
		if(0 <= scroll_speed && scroll_speed < 3) FLOW_slide_speed = 40; else
		if(3 <= scroll_speed && scroll_speed < 6) FLOW_slide_speed = 20; else
		FLOW_slide_speed = 10;
		
		j=-1;
		for(i=0; i<=game_number; i++) {
			if(Show_it(i) == NO) continue;
			j++;
			if(i==position) {
				if(j==0) FLOW_position_x = x;
				else FLOW_position_x = x - 2*FLOW_w - FLOW_w*(j-1);
				break;
			}
		}
		
		x += Flow_curs_move_x;
		
		if(FLOW_position_x > x) {
			if(264 <= x && x < 584) FLOW_speed=FLOW_slide_speed*2; else FLOW_speed=FLOW_slide_speed;
		} else
		if(FLOW_position_x < x) {
			if(264 < x && x <= 584) FLOW_speed=-FLOW_slide_speed*2; else FLOW_speed=-FLOW_slide_speed;
		} else FLOW_speed=0;
		
		Flow_curs_move_x+=FLOW_speed;
		
		for(j = 0 ; j <= game_number ; j++) {
			if(Show_it(j) == NO) continue;
			
			if(264 < x && x < 584) {
				if(x<=424) {
					FLOW_a= 1/(424-264)*x - (1/(424-264)*424) + 2 ;
				}
				else {
					FLOW_a= 1/(424-584)*x - (1/(424-584)*424) + 2 ;
				}
			} else {
				FLOW_a=1;
			}
			if(x==424) {
				SetFontSize(20, 20);
				DrawStringFromCenterX(424, 100, list_game_title[j]);
			}
			
			if(j==position) {
				if(FLOW_use_Cover == YES && COVER_offset[j] != 0) Draw_CoverFromCenter(j, x, y, 0, FLOW_w*FLOW_a, 0);
				else Draw_ICON0(j, x-(FLOW_w*FLOW_a)/2, y-(FLOW_h*FLOW_a)/2, 0, FLOW_w*FLOW_a, FLOW_h*FLOW_a);
			} else {
				if(FLOW_use_Cover == YES && COVER_offset[j] != 0) Draw_CoverFromCenter(j, x, y, 100, FLOW_w*FLOW_a, 0);
				else Draw_ICON0(j, x-(FLOW_w*FLOW_a)/2, y-(FLOW_h*FLOW_a)/2, 100, FLOW_w*FLOW_a, FLOW_h*FLOW_a);
			}
			
			if(x==424 || x==264) x+=2*FLOW_w; else  
			if(264 < x && x < 424) {
			   x+=FLOW_w*FLOW_a;
			} else
			if(424 < x && x < 584) {
				x+=FLOW_w*(FLOW_a-1) + fabs(584-x)/2;
			} else
			if(184 < x && x < 424) {
				if(speed<0){
					x+=2*FLOW_w;
				}
				if(speed>0){
					x+=FLOW_w;
				}
			} else x+=FLOW_w;
			
			if(speed!=20) {
				if(speed<0){
					if(264 < x && x < 424) {
					x+=fabs(424-x)*speed/10;
					}
				}
				if(speed>0){
					if(264 < x && x < 424) {
						x+=fabs(264-x)*speed/10;
					}
				}
			}
		}
	}

}

u8 Show_it(int pos)
{
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
	
	NTFS_init_system_io();
	
	AutoM = is_AutoMount();
	
	sysModuleLoad(SYSMODULE_PNGDEC); //init PNG
	sysModuleLoad(SYSMODULE_JPGDEC); //init PNG
	
	Init_Graph();
	ioPadInit(7);
	ioPadSetPressMode(0,1);
	SetCurrentFont(-1);
	
	start_loading();
	
	if(lv2peek(0x8000000000003000ULL)==0xFFFFFFFF80010003ULL) {
		end_loading();
		while(1) {
			cls();
			ps3pad_read();
			
			Draw_BGS();
			int x=50, y=40;
			SetFontAutoCenter(0);
			SetFontSize(20,20);
			SetFontColor(0xff0000ff, 0x0);
			
			DrawString(x, y, "Error : ManaGunZ need peek & poke.");
			
			SetFontColor(COLOR_1, 0x0);
			SetFontSize(15, 15);
			
			x=Draw_Button_Start(25, 485, 15);
			x=DrawString( x+5, 485, "Reboot system  ");
			x=Draw_Button_Circle(x, 485, 15);
			x=DrawString( x+5, 485, "Back to XMB  ");
			
			tiny3d_Flip();
			
			if(new_pad & BUTTON_START) {
				Delete("/dev_hdd0/tmp/turnoff");
				lv2syscall4(379,0x200,0,0,0);
			}
			
			if(new_pad & BUTTON_CIRCLE) {
				ioPadEnd();
				return 0;
			}
		}
	}
	
	print_load("Initialisation");
	if(init_fw() == NOK) {
		end_loading();
		while(1) {
			cls();
			ps3pad_read();
			
			SetFontAutoCenter(1);
			SetFontSize(30,30);
			SetFontColor(COLOR_1, 0x0);
			DrawString(50, 30, "ManaGunZ");
			SetFontAutoCenter(0);
			
			SetFontSize(20,20);
			SetFontColor(0xff0000ff, 0x0);
			DrawString(50, 100, "Error : This firmware isn't supported.");
			
			SetFontColor(COLOR_1, 0x0);
			SetFontSize(15, 15);
			int x=25;
			x=Draw_Button_Circle(x, 485, 15);
			x=DrawString( x+5, 485, "Back to XMB  ");
			
			tiny3d_Flip();
			
			if(new_pad & BUTTON_CIRCLE) {
				ioPadEnd();
				return 0;
			}
		}
	}
	
	if(init_ManaGunZ() == FAILED) {
		end_loading();
		while(1) {
			cls();
			ps3pad_read();
			
			SetFontAutoCenter(1);
			SetFontSize(30,30);
			SetFontColor(COLOR_1, 0x0);
			DrawString(50, 30, "ManaGunZ");
			SetFontAutoCenter(0);
			
			SetFontSize(20,20);
			SetFontColor(RED, 0x0);
			DrawString(50, 100, "Error : Cannot init ManaGunZ");
			
			SetFontColor(COLOR_1, 0x0);
			SetFontSize(15, 15);
			int x=25;
			x=Draw_Button_Circle(x, 485, 15);
			x=DrawString( x+5, 485, "Back to XMB  ");
			
			tiny3d_Flip();
			
			if(new_pad & BUTTON_CIRCLE) {
				ioPadEnd();
				return 0;
			}
		}
	}
	
	if(AutoM == YES) AutoMount();	

	start_checking();
	
	print_load("Read setting");
	read_setting();
	
	print_load("Adjust screen");
	adjust_screen();
	
	print_load("Get list of themes");
	GetThemes();
	
	print_load("Load Common images");
	Load_COMMON();
	
	print_load("Load Themes");
	Load_Themes();
	
	print_load("Get directories names from scan_dir.txt");
	if(read_scan_dir()==FAILED){
		end_loading();
		while(1) {
			cls();
			ps3pad_read();
			
			Draw_BGS();
			int x=50, y=40;
			SetFontAutoCenter(0);
			
			SetFontSize(20,20);
			SetFontColor(0xff0000ff, 0x0);
			DrawString(x, y, "Error : Can't read scan_dir.txt");
			
			SetFontColor(COLOR_1, 0x0);
			SetFontSize(15, 15);
			
			x=25;
			x=Draw_Button_Circle(x, 485, 15);
			x=DrawString( x+5, 485, "Back to XMB  ");
			
			tiny3d_Flip();
			
			if(new_pad & BUTTON_CIRCLE) {
				end_checking();
				sysModuleUnload(SYSMODULE_PNGDEC);
				sysModuleUnload(SYSMODULE_JPGDEC);
				ioPadEnd();
				return 0;
			}
		}
	}

	//get game list
	for(j=0; j<=scan_dir_number; j++) {
		for(i=0; i<=device_number; i++) {
			sprintf(scan_path, "/%s/%s", list_device[i], scan_dir[j]);
			print_load("Scanning : %s", scan_path);

			DIR *d;
			struct dirent *dir;
			
			d = opendir(scan_path);
			if(d==NULL) continue;
			
			while ((dir = readdir(d))) {
				if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;

				char temp[255];
				sprintf(temp, "%s/%s" , scan_path, dir->d_name);
				u8 ext = get_ext(temp);
				
				if(ext != _ISO_PS3 && ext != _ISO_PS2 && ext != _ISO_PS1 && ext != _ISO_PSP)
				if(ext != _JB_PS3 && ext != _JB_PS2 && ext != _JB_PS1 && ext != _JB_PSP) continue;

				game_number++;
				sprintf(list_game_path[game_number], "%s/%s" , scan_path, dir->d_name);
				
				strcpy(list_game_title[game_number], list_game_path[game_number]);
				strcpy(list_game_title[game_number], &strrchr(list_game_title[game_number], '/')[1]);
				strtok(list_game_title[game_number], ".");
				
				list_game_platform[game_number] = ext;
				
				if(ext == _ISO_PS3 || ext == _JB_PS3 || ext == _ISO_PSP || ext == _JB_PSP) {
					GetParamSFO("TITLE", list_game_title[game_number], game_number, NULL);
				}
				
			}
			closedir(d);
		}
	}
	
	print_load( "Sorting the games' list");
	int min;
	char ta[255], tb[255];
	u8 t;
	for(i = 0; i<game_number; i++) { 
		min = i;
		for (j = i+1; j <= game_number; j++) { 
			strcpy(ta , list_game_title[j]);
			strcpy(tb, list_game_title[min]);
			if(ta[0]>=97 && ta[0]<=123) ta[0]-=32;
			if(tb[0]>=97 && tb[0]<=123) tb[0]-=32;
			if (strcmp(ta, tb) < 0) { 
				min = j; 
			} 
		}
		if(min==i) continue;
		strcpy(ta , list_game_title[min]);
		strcpy(list_game_title[min], list_game_title[i]); 
		strcpy(list_game_title[i], ta); 
		strcpy(tb, list_game_path[min]);
		strcpy(list_game_path[min], list_game_path[i]); 
		strcpy(list_game_path[i], tb);
		t = list_game_platform[min];
		list_game_platform[min] = list_game_platform[i];
		list_game_platform[i] = t;
	}
	
	start_Load_GamePIC();
	
	print_load("Get Favorite game list");
	read_fav();
	
	position=0;
	for(position=0; position<=game_number; position++) {
		if(Show_it(position)==YES) break;
	}
	
	end_loading();
	
	start_load_PIC1();
	
	while(1) {
		while(game_number < 0) {
			cls();
			ps3pad_read();
			
			Draw_BGS();
			
			check_device();
			
			int x=50, y=40;
			SetFontAutoCenter(0);
			
			SetFontSize(20,20);
			SetFontColor(0xff0000ff, 0x0);
			DrawString(x, y, "Error: 0 game detected");
			
			SetFontColor(COLOR_1, 0x0);
			SetFontSize(15, 15);
			
			x=25;
			x=DrawButton(x, 485, "Back to XMB" , BUTTON_CIRCLE);
			x=DrawButton(x, 485, "File Manager", BUTTON_SELECT);
			
			tiny3d_Flip();	
			
			if(new_pad & BUTTON_SELECT) Draw_FileExplorer(NULL);
			
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
		
		Draw_Notification();
		
		check_device();
		
		tiny3d_Flip();
		
		ps3pad_read();
		
		input_MAIN();
		input_filter();
		input_MENU();
		txt_viewer_input();
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
		Draw_Notification();
	} else
	if(scene == SCENE_MAIN) 
	{
		Draw_BG();
		Draw_MAIN();
		Draw_filter();
		Draw_MENU();
	}
}
