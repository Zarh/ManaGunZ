#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ppu-types.h>
#include "zpipe.h"
#include "md5.h"

#define ISODCL(from, to) (to - from + 1)
#define SWAP16(x) (x) // NO SWAP ! ((((u16)(x))>>8) | ((x) << 8))
#define MAX_ISO_PATHS 4096

#define YES			1
#define NO 			0
#define SUCCESS		1
#define FAILED 		0

extern void print_load(char *format, ...);
extern void Delete(char* path);
extern u8 cancel;
extern u8 md5_file(char *path, unsigned char output[16] );
extern u8 md5_FromISO_WithFileOffset(char *iso_path, u64 file_offset, u32 file_size, unsigned char output[16]);
extern char *LoadFile(char *path, int *file_size);
extern u8 *LoadMEMfromISO(char *iso_file, u32 sector, u32 offset, u32 size);
extern u8 is_iso(char *file_name);

typedef struct {
    int parent;
    char *name;

} _directory_iso2;

static _directory_iso2 *directory_iso2 = NULL;

typedef struct {
    u32 size;
    char path[0x420];

} _split_file;

static _split_file split_file[64];
static FILE *fp_split = NULL;
static FILE *fp_split0 = NULL;

static int split_index = 0;
static int split_files = 0;

typedef struct
{
	u32 Magic; //= 0x33495244; // Magic of "Iso Rebuild Data" file
	u8 GAME_ID_size;
	char GAME_ID[10];
	u8 GAME_NAME_size;
	char GAME_NAME[255];
	char UPDATE[5];
	char GAME_VERS[6];
	char APP_VERS[6];
} IRDU_header;

typedef struct
{
	char FILE_PATH[255];
	u64 sector;
	u64 MD5[2];
	u64 size;
} IRDU_fileInfo;

extern uint32_t reverse32(uint32_t val);

u64 reverse64(u64 x) {

	x = (x & 0x00000000FFFFFFFFULL) << 32 | (x & 0xFFFFFFFF00000000ULL) >> 32;
	x = (x & 0x0000FFFF0000FFFFULL) << 16 | (x & 0xFFFF0000FFFF0000ULL) >> 16;
	x = (x & 0x00FF00FF00FF00FFULL) << 8  | (x & 0xFF00FF00FF00FF00ULL) >> 8 ;
	return x;
}

u8 IRD_match(char *titleID, char *IRD_PATH)
{
	FILE *in;
	FILE *out;

	char IRDU_PATH[255];
	u32 magic;
	strcpy(IRDU_PATH, IRD_PATH);
	strcat(IRDU_PATH, "u");
	
	in = fopen(IRD_PATH, "rb");
	
	fread(&magic, 1, sizeof(u32), in);
	if(magic != 0x1F8B0800) {
		fclose(in);
		return  NO;
	}
	
	fseek(in, 0, SEEK_SET);
	
	out = fopen(IRDU_PATH, "wb");
	
	int ret = inf(in, out);
	fclose(in);
	fclose(out);
	if(ret != Z_OK) {
		Delete(IRDU_PATH);
		return NO;
	}
	
	in = fopen(IRDU_PATH, "rb");
	magic = 0;
	fread(&magic, 1, sizeof(u32), in);
	if(magic != 0x33495244) {
		print_load("Error : IRDU magic...");
		fclose(in);
		Delete(IRDU_PATH);
		return  NO;
	}
	
	fseek(in, 5, SEEK_SET);
	
	char *mem = (char *) malloc(9);
	fread(mem,1,9, in);
	fclose(in);
	
	Delete(IRDU_PATH);
	
	if(strcmp(titleID, mem) == 0) {
		free(mem);
		return YES;
	}
	
	free(mem);
	
	return NO;
}

u8 Extract_IRD(char *IRD_PATH, IRDU_header *header)
{
	FILE *in;
	FILE *out;
	
	char IRDU_PATH[255];
	strcpy(IRDU_PATH, IRD_PATH);
	strcat(IRDU_PATH, "u");
	
	char IRDH_PATH[255];
	strcpy(IRDH_PATH, IRD_PATH);
	strcat(IRDH_PATH, "h");
	
	char IRDF_PATH[255];
	strcpy(IRDF_PATH, IRD_PATH);
	strcat(IRDF_PATH, "f");
	
	char IRDMD5_PATH[255];
	strcpy(IRDMD5_PATH, IRD_PATH);
	strcat(IRDMD5_PATH, "md5");
	
	in = fopen(IRD_PATH, "rb");
	out = fopen(IRDU_PATH, "wb");
	
	int ret = inf(in, out);
	if(ret != Z_OK) {
		fclose(in);
		fclose(out);
		Delete(IRDU_PATH);
		return FAILED;
	}
	
	fclose(in);
	fclose(out);
	
	in = fopen(IRDU_PATH, "rb");
	
//	*************
//	IRD HEADER **
//	*************
	
	memset(header, 0, sizeof(IRDU_header));
	
	fread(&header->Magic, sizeof(u32), 1, in);
	fread(&header->GAME_ID_size, sizeof(header->GAME_ID_size), 1, in);
	fread(header->GAME_ID, header->GAME_ID_size, 1, in);
	fread(&header->GAME_NAME_size, sizeof(u8), 1, in);
	fread(header->GAME_NAME, header->GAME_NAME_size, 1, in);
	fread(header->UPDATE, 4, 1, in);
	fread(header->GAME_VERS, 5, 1, in);
	fread(header->APP_VERS, 5, 1, in);
	
//	**********************
//	ISO header & footer **
//	**********************
	
	u32 Zhead_size; // endian
	u32 Zfoot_size; // endian
	fread(&Zhead_size, sizeof(u32), 1, in);
	
	Zhead_size = reverse32(Zhead_size);
	
	u32 Zfoot_off = ftell(in) + Zhead_size;
	
	out = fopen(IRDH_PATH, "wb");
	inf(in, out);
	fclose(out);
	
	fseek(in, Zfoot_off, SEEK_SET);
	fread(&Zfoot_size, sizeof(u32), 1, in);
	Zfoot_size = reverse32(Zfoot_size);

	out = fopen(IRDF_PATH, "wb");
	inf(in, out);
	fclose(out);

//	**********************
//	MD5 TABLE			**
//	**********************
	
	u32 MD5_table_off = Zfoot_size + Zfoot_off + 4 + 0x35;

	out = fopen(IRDMD5_PATH, "wb");
	
	fseek(in, 0, SEEK_END);	
	size_t size = ftell(in);
	fseek(in, MD5_table_off, SEEK_SET);
	
	u8 data;
	int i;
	for(i=0; i < (int) (size - MD5_table_off) ; i++) {
		fread(&data, 1, 1, in);
		fwrite(&data, 1, 1, out);
	}
	fclose(in);
	fclose(out);
	
	return SUCCESS;
}

u8 check_header(char *IRD_PATH, char *GAME_PATH)
{
	char IRDH_PATH[255];
	sprintf(IRDH_PATH, "%sh", IRD_PATH);
	
	int size;
	
	char *ird_header = LoadFile(IRDH_PATH, &size);
	if(ird_header==NULL) return NO;
	
	char *iso_header = (char *) LoadMEMfromISO(GAME_PATH, 0, 0, size);
	if(iso_header==NULL) {free(ird_header); return NO;}
	
	int res = memcmp(ird_header, iso_header, size);
	
	free(ird_header);
	free(iso_header);
	
	if(res==0) return YES;
	else return NO;
}

u8 check_footer(char *IRD_PATH, char *GAME_PATH)
{
	//todo
	return YES;
}

u8 Get_IRDMD5(char *IRD_PATH, IRDU_fileInfo *fileInfo)
{
	FILE *in=NULL;
	size_t size;
	char IRDMD5_PATH[255];
	u64 i;
	u64 sector_r; //endian
	u64 MD5_r[2];
	
	strcpy(IRDMD5_PATH, IRD_PATH);
	strcat(IRDMD5_PATH, "md5");

	in = fopen(IRDMD5_PATH, "rb");
	if(in==NULL) print_load("Error : failed to read irdmd5");
	size = fseek(in, 0, SEEK_END);	
	size = ftell(in);
	fseek(in, 0, SEEK_SET);
	
	for(i=0; i < size / 8; i++) {
		fread(&sector_r, 1, sizeof(u64), in);
		sector_r = reverse64(sector_r);
		fread(&MD5_r, 2, sizeof(u64), in);

		if(sector_r == fileInfo->sector) {
			fileInfo->MD5[0] = MD5_r[0];
			fileInfo->MD5[1] = MD5_r[1];
			fclose(in);
			return 1;
		}
		
	}
	fclose(in);
	return 0;

}

static int get_input_char()
{
    char c = getchar();
    char c2 = c;
    while (c != '\n' && c != EOF)
     	c = getchar();
    return c2;
}

static int isonum_731 (unsigned char * p)
{
	return ((p[0] & 0xff)
		| ((p[1] & 0xff) << 8)
		| ((p[2] & 0xff) << 16)
		| ((p[3] & 0xff) << 24));
}

static int isonum_733 (unsigned char * p)
{
	return (isonum_731 (p));
}

static int isonum_721 (char * p)
{
	return ((p[0] & 0xff) | ((p[1] & 0xff) << 8));
}

struct iso_primary_descriptor {
	unsigned char type			[ISODCL (  1,   1)]; /* 711 */
	unsigned char id				[ISODCL (  2,   6)];
	unsigned char version			[ISODCL (  7,   7)]; /* 711 */
	unsigned char unused1			[ISODCL (  8,   8)];
	unsigned char system_id			[ISODCL (  9,  40)]; /* aunsigned chars */
	unsigned char volume_id			[ISODCL ( 41,  72)]; /* dunsigned chars */
	unsigned char unused2			[ISODCL ( 73,  80)];
	unsigned char volume_space_size		[ISODCL ( 81,  88)]; /* 733 */
	unsigned char unused3			[ISODCL ( 89, 120)];
	unsigned char volume_set_size		[ISODCL (121, 124)]; /* 723 */
	unsigned char volume_sequence_number	[ISODCL (125, 128)]; /* 723 */
	unsigned char logical_block_size		[ISODCL (129, 132)]; /* 723 */
	unsigned char path_table_size		[ISODCL (133, 140)]; /* 733 */
	unsigned char type_l_path_table		[ISODCL (141, 144)]; /* 731 */
	unsigned char opt_type_l_path_table	[ISODCL (145, 148)]; /* 731 */
	unsigned char type_m_path_table		[ISODCL (149, 152)]; /* 732 */
	unsigned char opt_type_m_path_table	[ISODCL (153, 156)]; /* 732 */
	unsigned char root_directory_record	[ISODCL (157, 190)]; /* 9.1 */
	unsigned char volume_set_id		[ISODCL (191, 318)]; /* dunsigned chars */
	unsigned char publisher_id		[ISODCL (319, 446)]; /* achars */
	unsigned char preparer_id		[ISODCL (447, 574)]; /* achars */
	unsigned char application_id		[ISODCL (575, 702)]; /* achars */
	unsigned char copyright_file_id		[ISODCL (703, 739)]; /* 7.5 dchars */
	unsigned char abstract_file_id		[ISODCL (740, 776)]; /* 7.5 dchars */
	unsigned char bibliographic_file_id	[ISODCL (777, 813)]; /* 7.5 dchars */
	unsigned char creation_date		[ISODCL (814, 830)]; /* 8.4.26.1 */
	unsigned char modification_date		[ISODCL (831, 847)]; /* 8.4.26.1 */
	unsigned char expiration_date		[ISODCL (848, 864)]; /* 8.4.26.1 */
	unsigned char effective_date		[ISODCL (865, 881)]; /* 8.4.26.1 */
	unsigned char file_structure_version	[ISODCL (882, 882)]; /* 711 */
	unsigned char unused4			[ISODCL (883, 883)];
	unsigned char application_data		[ISODCL (884, 1395)];
	unsigned char unused5			[ISODCL (1396, 2048)];
};

struct iso_directory_record {
	unsigned char length			[ISODCL (1, 1)]; /* 711 */
	unsigned char ext_attr_length		[ISODCL (2, 2)]; /* 711 */
	unsigned char extent			[ISODCL (3, 10)]; /* 733 */
	unsigned char size			[ISODCL (11, 18)]; /* 733 */
	unsigned char date			[ISODCL (19, 25)]; /* 7 by 711 */
	unsigned char flags			[ISODCL (26, 26)];
	unsigned char file_unit_size		[ISODCL (27, 27)]; /* 711 */
	unsigned char interleave			[ISODCL (28, 28)]; /* 711 */
	unsigned char volume_sequence_number	[ISODCL (29, 32)]; /* 723 */
	unsigned char name_len		[1]; /* 711 */
	unsigned char name			[1];
};

struct iso_path_table{
	unsigned char  name_len[2];	/* 721 */
	char extent[4];		/* 731 */
	char  parent[2];	/* 721 */
	char name[1];
};

static void UTF16_to_UTF8(u16 *stw, u8 *stb)
{
    while(SWAP16(stw[0])) {
        if((SWAP16(stw[0]) & 0xFF80) == 0) {
            *(stb++) = SWAP16(stw[0]) & 0xFF;   // utf16 00000000 0xxxxxxx utf8 0xxxxxxx
        } else if((SWAP16(stw[0]) & 0xF800) == 0) { // utf16 00000yyy yyxxxxxx utf8 110yyyyy 10xxxxxx
            *(stb++) = ((SWAP16(stw[0])>>6) & 0xFF) | 0xC0; *(stb++) = (SWAP16(stw[0]) & 0x3F) | 0x80;
        } else if((SWAP16(stw[0]) & 0xFC00) == 0xD800 && (SWAP16(stw[1]) & 0xFC00) == 0xDC00 ) { // utf16 110110ww wwzzzzyy 110111yy yyxxxxxx (wwww = uuuuu - 1) 
                                                                             // utf8 1111000uu 10uuzzzz 10yyyyyy 10xxxxxx  
            *(stb++)= (((SWAP16(stw[0]) + 64)>>8) & 0x3) | 0xF0; *(stb++)= (((SWAP16(stw[0])>>2) + 16) & 0x3F) | 0x80; 
            *(stb++)= ((SWAP16(stw[0])>>4) & 0x30) | 0x80 | ((SWAP16(stw[1])<<2) & 0xF); *(stb++)= (SWAP16(stw[1]) & 0x3F) | 0x80;
            stw++;
        } else { // utf16 zzzzyyyy yyxxxxxx utf8 1110zzzz 10yyyyyy 10xxxxxx
            *(stb++)= ((SWAP16(stw[0])>>12) & 0xF) | 0xE0; *(stb++)= ((SWAP16(stw[0])>>6) & 0x3F) | 0x80; *(stb++)= (SWAP16(stw[0]) & 0x3F) | 0x80;
        } 
        
        stw++;
    }
    
    *stb= 0;
}

static void fixpath(char *p)
{
    u8 * pp = (u8 *) p;

    if(*p == '"') {
        p[strlen(p) -1] = 0;
        memcpy(p, p + 1, strlen(p));
    }

    #ifdef __CYGWIN__
    if(p[0]!=0 && p[1] == ':') {
        p[1] = p[0];
        memmove(p + 9, p, strlen(p) + 1);
        memcpy(p, "/cygdrive/", 10);
    }
    #endif

    while(*pp) {
        if(*pp == '"') {*pp = 0; break;}
        else
        if(*pp == '\\') *pp = '/';
        else
        if(*pp > 0 && *pp < 32) {*pp = 0; break;}
        pp++;
    }

}

static void get_iso_path(char *path, int indx) 
{
    char aux[0x420];

    path[0] = 0;

    if(!indx) {path[0] = '/'; path[1] = 0; return;}

    while(1) {
        strcpy(aux, directory_iso2[indx].name);
        strcat(aux, path);
        strcpy(path, aux);
       
        indx = directory_iso2[indx].parent - 1;
        if(indx == 0) break;     
    }

}

int Check_IRDMD5(char *IRD_PATH, char *GAME_PATH, FILE *log)
{

    struct stat s;
    int n;
	
	char path1[0x420];
	
	u8 gameiso = is_iso(GAME_PATH);
	
	strcpy(path1, IRD_PATH);
	strcat(path1, "h");
	
    u8 *sectors = NULL;
    u8 *sectors2 = NULL;
    u8 *sectors3 = NULL;

    static char string[0x420];
    static char string2[0x420];
    static u16 wstring[1024];

    struct iso_primary_descriptor sect_descriptor;
    struct iso_directory_record * idr;
    int idx = -1;
	
	u64 real_MD5[3];
	char msg[255];
	char GAMEFILE_PATH[255];
	
	//u32 flba = 0;
	u32 lba;
	u32 p = 0;
	//u32 toc;
	u32 lba0;
	u32 size0;
    
	directory_iso2 = NULL;

    fp_split = NULL;
    fp_split0 = NULL;
    split_index = 0;
    split_files = 0; 
	
    // libc test
    if(sizeof(s.st_size) != 8) {
        print_load("Error!: stat st_size must be a 64 bit number!  (size %i)\n", sizeof(s.st_size));
        get_input_char();
        return -1;
    }
	
    fixpath(path1);

    n = strlen(path1);

    sprintf(split_file[0].path, "%s", path1);
	
    if(stat(split_file[0].path, &s)<0) {
        print_load("Error: ISO file don't exists!"); get_input_char();return -1;
    }
    split_file[0].size = s.st_size;
    split_file[1].size = 0; // split off


    FILE *fp = fopen(path1, "rb");
    if(!fp) {
        print_load("Error!: Cannot open ISO file\n");
        get_input_char();
        return -1;
    }

    if(fseek(fp, 0x8800, SEEK_SET)<0) {
        print_load("Error!: in sect_descriptor fseek\n\n");
        goto err;
    }

    if(fread((void *) &sect_descriptor, 1, 2048, fp) != 2048) {
        print_load("Error!: reading sect_descriptor\n\n");
        goto err;
    }

    if(!(sect_descriptor.type[0] == 2 && !strncmp((const char *) &sect_descriptor.id[0], "CD001",5))) {
        print_load("Error!: UTF16 descriptor not found");
        goto err;
    }

    lba0 = isonum_731(&sect_descriptor.type_l_path_table[0]); // lba
    size0 = isonum_733(&sect_descriptor.path_table_size[0]); // tamaño
    
    if(fseek(fp, lba0 * 2048, SEEK_SET)<0) {
        print_load("Error!: in path_table fseek\n\n");
        goto err;
    }

    directory_iso2 = (_directory_iso2 *) malloc((MAX_ISO_PATHS + 1) * sizeof(_directory_iso2));

    if(!directory_iso2) {
        print_load("Error!: in directory_is malloc()\n\n");
        goto err;
    }

    memset(directory_iso2, 0, (MAX_ISO_PATHS + 1) * sizeof(_directory_iso2));
 
    sectors = (u8*) malloc(((size0 + 2047)/2048) * 2048);

    if(!sectors) {
        print_load("Error!: in sectors malloc()\n\n");
        goto err;
    }

    sectors2 = (u8*) malloc(2048 * 2);

    if(!sectors2) {
        print_load("Error!: in sectors2 malloc()\n\n");
        goto err;
    }

    sectors3 = (u8*) malloc(128 * 2048);

    if(!sectors3) {
        print_load("Error!: in sectors3 malloc()\n\n");
        goto err;
    }

    if(fread((void *) sectors, 1, size0, fp) != size0) {
        print_load("Error!: reading path_table\n\n");
        goto err;
    }

    string2[0] = 0;

    fp_split = NULL;
    fp_split0 = NULL;

    split_index = 0;

    idx = 0;

    directory_iso2[idx].name = NULL;

    while(p < size0) {
	
        u32 snamelen = isonum_721((char *) &sectors[p]);
        if(snamelen == 0) p= ((p/2048) * 2048) + 2048;
        p+=2;
        lba = isonum_731(&sectors[p]);
        p+=4;
        u32 parent =isonum_721((char *) &sectors[p]);
        p+=2;

        memset(wstring, 0, 512 * 2);
        memcpy(wstring, &sectors[p], snamelen);
        UTF16_to_UTF8(wstring, (u8 *) string);
        if(idx >= MAX_ISO_PATHS){
            print_load("Error :Too much folders (max %i)\n\n", MAX_ISO_PATHS);
            goto err;
        }

        directory_iso2[idx].name = (char *) malloc(strlen(string) + 2);
        if(!directory_iso2[idx].name) {
            print_load("Error!: in directory_iso2.name malloc()\n\n");
            goto err;
        }

        strcpy(directory_iso2[idx].name, "/");
        strcat(directory_iso2[idx].name, string);
		
		directory_iso2[idx].parent = parent;
        get_iso_path(string2, idx);
		
		//string2 is cur_dir //todo : LF not necessary files
		
        u32 file_lba = 0;
        u64 file_size = 0;

        char file_aux[0x420];

        file_aux[0] = 0;

        int q2 = 0;
        int size_directory = 0;

        while(1) {

            if(fseek(fp, ((u64) lba) * 2048ULL, SEEK_SET)<0) {
                print_load("Error!: in directory_record fseek\n\n");
                goto err;
            }

            memset(sectors2 + 2048, 0, 2048);

            if(fread((void *) sectors2, 1, 2048, fp) != 2048) {
                print_load("Error!: reading directory_record sector\n\n");
                goto err;
            }

            int q = 0;
            
            if(q2 == 0) {
                idr = (struct iso_directory_record *) &sectors2[q];
                if((int) idr->name_len[0] == 1 && idr->name[0]== 0 && (u64) lba == (u64) (isonum_731((unsigned char *) idr->extent)) && idr->flags[0] == 0x2) {
                    size_directory = isonum_733((unsigned char *) idr->size);
                 
                } else {
                    print_load("Error!: Bad first directory record! (LBA %i)\n\n", lba);
                    goto err;
                }
            }

            int signal_idr_correction = 0;

            while(1) {
			
                if(signal_idr_correction) {
                    signal_idr_correction = 0;
                    q-= 2048; // sector correction
                    // copy next sector to first
                    memcpy(sectors2, sectors2 + 2048, 2048);
                    memset(sectors2 + 2048, 0, 2048);
                    lba++;

                    q2 += 2048;

                }

                if(q2 >= size_directory) goto end_dir_rec;
               
                idr = (struct iso_directory_record *) &sectors2[q];

                if(idr->length[0]!=0 && (idr->length[0] + q) > 2048) {
					get_input_char();

                    if(fseek(fp, lba * 2048 + 2048, SEEK_SET)<0) {
                        print_load("Error!: in directory_record fseek\n\n");
                        goto err;
                    }

                    if(fread((void *) (sectors2 + 2048), 1, 2048, fp) != 2048) {
                        print_load("Error!: reading directory_record sector\n\n");
                        goto err;
                    }

                    signal_idr_correction = 1;

                }

                if(idr->length[0] == 0 && (2048 - q) > 255) goto end_dir_rec;

                if((idr->length[0] == 0 && q != 0) || q == 2048)  { 
                    
                    lba++;
                    q2 += 2048;

                    if(q2 >= size_directory) goto end_dir_rec;

                    if(fseek(fp, (((u64) lba) * 2048ULL), SEEK_SET)<0) {
                        print_load("Error!: in directory_record fseek\n\n");
                        goto err;
                    }

                    if(fread((void *) (sectors2), 1, 2048, fp) != 2048) {
                        print_load("Error!: reading directory_record sector\n\n");
                        goto err;
                    }
                    memset(sectors2 + 2048, 0, 2048);

                    q = 0;
                    idr = (struct iso_directory_record *) &sectors2[q];

                    if(idr->length[0] == 0 || ((int) idr->name_len[0] == 1 && !idr->name[0])) goto end_dir_rec;
                    
                }

                if((int) idr->name_len[0] > 1 && idr->flags[0] != 0x2 &&
                    idr->name[idr->name_len[0] - 1]== '1' && idr->name[idr->name_len[0] - 3]== ';') { // skip directories

                    memset(wstring, 0, 512 * 2);
                    memcpy(wstring, idr->name, idr->name_len[0]);

                    UTF16_to_UTF8(wstring, (u8 *) string); 

                    if(file_aux[0]) {
                        if(strcmp(string, file_aux)) {
                            print_load("Error!: in batch file %s\n", file_aux);
                            goto err;
                        }

                        file_size += (u64) (u32) isonum_733(&idr->size[0]);
                        if(idr->flags[0] == 0x80) {// get next batch file
                            q+= idr->length[0]; 
                            continue;
                        } 

                        file_aux[0] = 0; // stop batch file

                    } else {

                        file_lba = isonum_733(&idr->extent[0]);
                        file_size = (u64) (u32) isonum_733(&idr->size[0]);
                        if(idr->flags[0] == 0x80) {
                            strcpy(file_aux, string);
                            q+= idr->length[0];
                            continue;  // get next batch file
                        }
                    }

                    int len = strlen(string);

                    string[len - 2] = 0; // break ";1" string
                    
                    len = strlen(string2);
					if(strcmp(string2, "/") != 0)	strcat(string2, "/");
                    strcat(string2, string);

					IRDU_fileInfo fileInfo;
					memset(&fileInfo, 0, sizeof(IRDU_fileInfo));
					
					strcpy(fileInfo.FILE_PATH, string2);
					fileInfo.sector = file_lba;
					fileInfo.size = file_size;

					Get_IRDMD5(IRD_PATH, &fileInfo);
					
					strcpy(GAMEFILE_PATH, GAME_PATH);
					strcat(GAMEFILE_PATH, fileInfo.FILE_PATH);
					
					memset(real_MD5, 0, sizeof(real_MD5));
					
					if(gameiso) md5_FromISO_WithFileOffset(GAME_PATH, fileInfo.sector * 0x800, fileInfo.size, (u8 *) real_MD5);
					else md5_file(GAMEFILE_PATH, (u8 *) real_MD5);
					
					if(cancel == YES) goto err;
					
					if(real_MD5[0] == 0) {
						sprintf(msg, "| NOT FOUND		| %s\n", fileInfo.FILE_PATH);
					}
					else
					if(real_MD5[0] == fileInfo.MD5[0] && real_MD5[1] == fileInfo.MD5[1]) {
						sprintf(msg, "| VALID			| %s\n", fileInfo.FILE_PATH);	
					}
					else {
						sprintf(msg, "| MODIFIED		| %s\n", fileInfo.FILE_PATH);
					}
					
					//print_load("Error : real %X : ird %X", real_MD5[0],  fileInfo.MD5[0]);
					print_load(msg);
					
					if(log!=NULL) fputs(msg, log);
					
                    string2[len] = 0;
					
                }

                q+= idr->length[0];
            }

            lba ++; 
            q2+= 2048;
            if(q2 >= size_directory) goto end_dir_rec;

        }

        end_dir_rec:

        p+= snamelen;
        if(snamelen & 1) p++;

        idx++;

    }

    if(fp) fclose(fp);
    if(split_index && fp_split) {fclose(fp_split); fp_split = NULL;}
    if(sectors) free(sectors);
    if(sectors2) free(sectors2);
    if(sectors3) free(sectors3);

    for(n = 0; n <= idx; n++)
        if(directory_iso2[n].name) {free(directory_iso2[n].name); directory_iso2[n].name = NULL;}
    
    if(directory_iso2) free(directory_iso2); 
	
    return 0;

err:

    if(fp) fclose(fp);
    if(split_index && fp_split) {fclose(fp_split); fp_split = NULL;}

    if(sectors) free(sectors);
    if(sectors2) free(sectors2);
    if(sectors3) free(sectors3);

    for(n = 0; n <= idx; n++)
        if(directory_iso2[n].name) {free(directory_iso2[n].name); directory_iso2[n].name = NULL;}
    
    if(directory_iso2) free(directory_iso2);

    return -1;
}

void IRDMD5(char *IRD_PATH, char *GAME_PATH)
{	
	FILE *log=NULL;
	IRDU_header ird_info;
	char msg[1024];
	char LOG_PATH[255];
	
	u8 gameiso = is_iso(GAME_PATH);
	
	if(gameiso) sprintf(LOG_PATH, "%s.MD5_check.txt", GAME_PATH);
	else sprintf(LOG_PATH, "%s/MD5_check.txt", GAME_PATH);
	
	log = fopen(LOG_PATH, "wb");
			
	if( Extract_IRD(IRD_PATH, &ird_info) == FAILED) {
		print_load("Error : Extract IRD");
		return;
	}
		
	
	if(log!=NULL) {
		sprintf(msg, "Game Name : %s\nGame ID : %s\nSystem Version : %s\nGame Version : %s\n", ird_info.GAME_NAME, ird_info.GAME_ID, ird_info.UPDATE, ird_info.GAME_VERS);
		fputs(msg, log);
		if(gameiso) {
			strcpy(msg, "Proper ISO : ");
			if(check_header(IRD_PATH, GAME_PATH) == SUCCESS && check_footer(IRD_PATH, GAME_PATH) == SUCCESS) 
				strcat(msg, "YES\n");
			else 
				strcat(msg, "NO\n");
			fputs(msg, log);
		}
		fputs("\n|				|\n", log);
		fputs("| INFO			| PATH\n", log);
		fputs("|				|\n", log);
	}
	Check_IRDMD5(IRD_PATH, GAME_PATH, log);
	
	if(log!=NULL) 
		fputs("|				|", log);
	
	if(log!=NULL) fclose(log);
	
	if(cancel==YES) Delete(LOG_PATH);
	
	//clean
	char temp[255];
	strcpy(temp, IRD_PATH);
	strcat(temp, "u");
	Delete(temp);
	strcpy(temp, IRD_PATH);
	strcat(temp, "h");
	Delete(temp);
	strcpy(temp, IRD_PATH);
	strcat(temp, "f");
	Delete(temp);
	strcpy(temp, IRD_PATH);
	strcat(temp, "md5");
	Delete(temp);

}