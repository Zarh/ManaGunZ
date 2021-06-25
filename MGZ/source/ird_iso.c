#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ppu-types.h>
#include "ird_iso.h"

#define ISODCL(from, to) (to - from + 1)
#define MAX_ISO_PATHS 4096

#define YES			1
#define NO 			0
#define SUCCESS		1
#define FAILED 		0

#define IRD_FILE_BUFFSIZE 0x20*0x800

extern u8 DEBUG;
extern void print_load(char *format, ...);
extern void Delete(char* path);
extern u8 cancel;
extern u8 md5_file(char *path, unsigned char output[16] );
extern u8 md5_FromISO_WithFileOffset(char *iso_path, u64 file_offset, u32 file_size, unsigned char output[16]);
extern char *LoadFile(char *path, int *file_size);
extern u8 *LoadMEMfromISO(char *iso_file, u32 sector, u32 offset, u32 size);
extern u8 is_iso(char *file_name);
extern int64_t prog_bar1_value;
extern int64_t prog_bar2_value;
extern char *strcpy_malloc(char *STR_DEFAULT);
extern void task_Init(const u64 max);
extern void task_Update(u64 val);
extern void task_End();
extern ird_t *IRD_new(char *source);
extern u64 get_size(char *path);

extern char copy_file[128];
extern u64 copy_current_size;
extern u64 copy_file_prog_bar;
extern u8 copy_cancel;

char *STR_VALID = "VALID";
char *STR_EXTRA = "EXTRA";
char *STR_NOT_FOUND = "NOT FOUND";
char *STR_MODIFIED = "MODIFIED";

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

u8 check_header(char *HEADER_PATH, char *ISO_PATH)
{
	int size;
	
	char *ird_header = LoadFile(HEADER_PATH, &size);
	if(ird_header==NULL) return NO;
	
	char *iso_header = (char *) LoadMEMfromISO(ISO_PATH, 0, 0, size);
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
    while(SWAP_BE(stw[0])) {
        if((SWAP_BE(stw[0]) & 0xFF80) == 0) {
            *(stb++) = SWAP_BE(stw[0]) & 0xFF;   // utf16 00000000 0xxxxxxx utf8 0xxxxxxx
        } else if((SWAP_BE(stw[0]) & 0xF800) == 0) { // utf16 00000yyy yyxxxxxx utf8 110yyyyy 10xxxxxx
            *(stb++) = ((SWAP_BE(stw[0])>>6) & 0xFF) | 0xC0; *(stb++) = (SWAP_BE(stw[0]) & 0x3F) | 0x80;
        } else if((SWAP_BE(stw[0]) & 0xFC00) == 0xD800 && (SWAP_BE(stw[1]) & 0xFC00) == 0xDC00 ) { // utf16 110110ww wwzzzzyy 110111yy yyxxxxxx (wwww = uuuuu - 1) 
                                                                             // utf8 1111000uu 10uuzzzz 10yyyyyy 10xxxxxx  
            *(stb++)= (((SWAP_BE(stw[0]) + 64)>>8) & 0x3) | 0xF0; *(stb++)= (((SWAP_BE(stw[0])>>2) + 16) & 0x3F) | 0x80; 
            *(stb++)= ((SWAP_BE(stw[0])>>4) & 0x30) | 0x80 | ((SWAP_BE(stw[1])<<2) & 0xF); *(stb++)= (SWAP_BE(stw[1]) & 0x3F) | 0x80;
            stw++;
        } else { // utf16 zzzzyyyy yyxxxxxx utf8 1110zzzz 10yyyyyy 10xxxxxx
            *(stb++)= ((SWAP_BE(stw[0])>>12) & 0xF) | 0xE0; *(stb++)= ((SWAP_BE(stw[0])>>6) & 0x3F) | 0x80; *(stb++)= (SWAP_BE(stw[0]) & 0x3F) | 0x80;
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

static int read_split(u64 position, u8 *mem, int size)
{
    int n;

    if(!split_file[1].size) {

        if(!fp_split0) fp_split0 = fopen(split_file[0].path, "rb");
        if(!fp_split0) return -666;

        if(fseek(fp_split0, position, SEEK_SET)<0) {
            printf("Error!: in ISO file fseek");
            return -668;
        }
		int read = fread(mem, 1, size, fp_split0);
        if(read != size) {
			print_load("Error : read %X, size %X", read, size);
			return -667;
		}
        return 0;
    }

    u64 relpos0 = 0;
    u64 relpos1 = 0;

    for(n = 0; n < 64; n++){
        if(!split_file[n].size) return -669;
        if(position < (relpos0 + (u64) split_file[n].size)) {
            relpos1 = relpos0 + (u64) split_file[n].size;
            break;
        }

        relpos0 += split_file[n].size;
    }
    
    if(fp_split == NULL) split_index = 0;

    if(n == 0) {
        if(split_index && fp_split) {fclose(fp_split); fp_split = NULL;}
        split_index = 0;
        fp_split = fp_split0;

    } else {

        if(n != split_index) {
            if(split_index && fp_split) {fclose(fp_split); fp_split = NULL;}

            split_index = n;

            fp_split = fopen(split_file[split_index].path, "rb");
            if(!fp_split) return -666;


        }
    }

    //int cur = lba / SPLIT_LBA;
    //int cur2 = (lba + sectors) / SPLIT_LBA;

    if(fseek(fp_split, (position - relpos0), SEEK_SET)<0) {
        printf("Error!: in ISO file fseek");
        return -668;
    }

    if(position >= relpos0 && (position + size) < relpos1) {

        if(fread(mem, 1, (int) size, fp_split) != size) return -667;
        return 0;
    }

    int lim = (int) (relpos1 - position);

    if(fread(mem, 1, (int) lim, fp_split) != lim) return -667;

    mem += lim; size-= lim;

    if(split_index && fp_split) {fclose(fp_split); fp_split = NULL;}

    split_index++;

    fp_split = fopen(split_file[split_index].path, "rb");
    if(!fp_split) return -666;

    if(fread(mem, 1, (int) size, fp_split) != size) return -667;

    return 0;
}

u8 IRD_GetFilesPath(char *ISO_PATH, ird_t *ird)
{
    int n;
    
	char path1[0x420];
    char path2[0x420];
    int len_path2 = 0;

    u8 *sectors = NULL;
    u8 *sectors2 = NULL;
    u8 *sectors3 = NULL;

    static char string[0x420];
    static char string2[0x420];
    static u16 wstring[1024];

    struct iso_primary_descriptor sect_descriptor;
    struct iso_directory_record * idr;
    int idx = -1;

	//u32 flba = 0;
	u32 lba;
	u32 p = 0;
	//u32 toc;
	u32 lba0;
	u32 size0;
    
	directory_iso2 = NULL;
	
	strcpy(path1, ISO_PATH);
	
	fixpath(path1);

    FILE *fp = fopen(path1, "rb");
    if(!fp) {
        printf("Error!: Cannot open ISO file");
        return -1;
    }

    
    if(fseek(fp, 0x8800, SEEK_SET)<0) {
        printf("Error!: in sect_descriptor fseek");
        goto err;
    }

    if(fread((void *) &sect_descriptor, 1, 2048, fp) != 2048) {
        printf("Error!: reading sect_descriptor");
        goto err;
    }

    //toc = isonum_733(&sect_descriptor.volume_space_size[0]);

    lba0 = isonum_731(&sect_descriptor.type_l_path_table[0]); // lba
    size0 = isonum_733(&sect_descriptor.path_table_size[0]); // tamaño
    //printf("lba0 %u size %u %u", lba0, size0, ((size0 + 2047)/2048) * 2048);
    
    if(fseek(fp, lba0 * 2048, SEEK_SET)<0) {
        printf("Error!: in path_table fseek");
        goto err;
    }

    directory_iso2 = (_directory_iso2 *) malloc((MAX_ISO_PATHS + 1) * sizeof(_directory_iso2));

    if(!directory_iso2) {
        printf("Error!: in directory_is malloc()");
        goto err;
    }

    memset(directory_iso2, 0, (MAX_ISO_PATHS + 1) * sizeof(_directory_iso2));
 
    sectors = (u8*) malloc(((size0 + 2047)/2048) * 2048);

    if(!sectors) {
        printf("Error!: in sectors malloc()");
        goto err;
    }

    sectors2 = (u8*) malloc(2048 * 2);

    if(!sectors2) {
        printf("Error!: in sectors2 malloc()");
        goto err;
    }

    sectors3 = (u8*) malloc(IRD_FILE_BUFFSIZE);

    if(!sectors3) {
        printf("Error!: in sectors3 malloc()");
        goto err;
    }

    if(fread((void *) sectors, 1, size0, fp) != size0) {
        printf("Error!: reading path_table");
        goto err;
    }

    string2[0] = 0;
	
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
            printf("Too much folders (max %i)", MAX_ISO_PATHS);
            goto err;
        }

        directory_iso2[idx].name = (char *) malloc(strlen(string) + 2);
        if(!directory_iso2[idx].name) {
            printf("Error!: in directory_iso2.name malloc()");
            goto err;
        }

        strcpy(directory_iso2[idx].name, "/");
        strcat(directory_iso2[idx].name, string);
        
        directory_iso2[idx].parent = parent;
        
        get_iso_path(string2, idx);

        strcat(path2, string2);
		
        path2[len_path2] = 0;
   
        u32 file_lba = 0;
        u64 file_size = 0;

        char file_aux[0x420];

        file_aux[0] = 0;

        int q2 = 0;
        int size_directory = 0;

        while(1) {

            if(fseek(fp, ((u64) lba) * 2048ULL, SEEK_SET)<0) {
                printf("Error!: in directory_record fseek");
                goto err;
            }

            memset(sectors2 + 2048, 0, 2048);

            if(fread((void *) sectors2, 1, 2048, fp) != 2048) {
                printf("Error!: reading directory_record sector");
                goto err;
            }

            int q = 0;
            
            if(q2 == 0) {
                idr = (struct iso_directory_record *) &sectors2[q];
                if((int) idr->name_len[0] == 1 && idr->name[0]== 0 && (u64) lba == (u64) (isonum_731((unsigned char *) idr->extent)) && idr->flags[0] == 0x2) {
                    size_directory = isonum_733((unsigned char *) idr->size);
                 
                } else {
                    printf("Error!: Bad first directory record! (LBA %i)", lba);
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

                    printf("Warning! Entry directory break the standard ISO 9660");
                   
                    if(fseek(fp, lba * 2048 + 2048, SEEK_SET)<0) {
                        printf("Error!: in directory_record fseek");
                        goto err;
                    }

                    if(fread((void *) (sectors2 + 2048), 1, 2048, fp) != 2048) {
                        printf("Error!: reading directory_record sector");
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
                        printf("Error!: in directory_record fseek");
                        goto err;
                    }

                    if(fread((void *) (sectors2), 1, 2048, fp) != 2048) {
                        printf("Error!: reading directory_record sector");
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
    
                            printf("Error!: in batch file %s", file_aux);
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
                    
                    int i;
                    for(i=0; i<ird->FileHashesNumber; i++) {
                        if( ird->FileHashes[i].Sector == file_lba) {
                            ird->FileHashes[i].FilePath = strcpy_malloc(string2);
                            if(ird->FileHashes[i].FilePath==NULL) {printf("ird->FileHashes[i].FilePath malloc failed");}
                            break;
                        }
					}
                    
                    path2[len_path2] = 0;
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
    if(sectors) free(sectors);
    if(sectors2) free(sectors2);
    if(sectors3) free(sectors3);

    for(n = 0; n <= idx; n++)
        if(directory_iso2[n].name) {free(directory_iso2[n].name); directory_iso2[n].name = NULL;}
    
    if(directory_iso2) free(directory_iso2); 

    return 0;

err:

    if(fp) fclose(fp);
	
    if(sectors) free(sectors);
    if(sectors2) free(sectors2);
    if(sectors3) free(sectors3);

    for(n = 0; n <= idx; n++)
        if(directory_iso2[n].name) {free(directory_iso2[n].name); directory_iso2[n].name = NULL;}
    
    if(directory_iso2) free(directory_iso2);

    return -1;
}

u8 IRD_FilesInfo(char *ISO_PATH, s64 *nb_file, u64 *total_size)
{
	*nb_file=0;
	*total_size=0;
	
    int n;
    char path1[0x420];

    u8 *sectors = NULL;
    u8 *sectors2 = NULL;

    static char string[0x420];
    static char string2[0x420];
    static u16 wstring[1024];

    struct iso_primary_descriptor sect_descriptor;
    struct iso_directory_record * idr;
    int idx = -1;

    directory_iso2 = NULL;

    split_index = 0;

	strcpy(path1, ISO_PATH);
	
	fixpath(path1);

    n = strlen(path1);
	
    FILE *fp = fopen(path1, "rb");
    if(!fp) {
        printf("Error!: Cannot open ISO file");
        return FAILED;
    }
    
    if(fseek(fp, 0x8800, SEEK_SET)<0) {
        printf("Error!: in sect_descriptor fseek");
        goto err;
    }

    if(fread((void *) &sect_descriptor, 1, 2048, fp) != 2048) {
        printf("Error!: reading sect_descriptor");
        goto err;
    }

    if(!(sect_descriptor.type[0] == 2 && !strncmp((void *) &sect_descriptor.id[0], "CD001",5))) {
        printf("Error!: UTF16 descriptor not found");
        goto err;
    }
	
    u32 lba0 = isonum_731(&sect_descriptor.type_l_path_table[0]); // lba
    u32 size0 = isonum_733(&sect_descriptor.path_table_size[0]); // tamaño
    //printf("lba0 %u size %u %u", lba0, size0, ((size0 + 2047)/2048) * 2048);
    
    if(fseek(fp, lba0 * 2048, SEEK_SET)<0) {
        printf("Error!: in path_table fseek");
        goto err;
    }

    directory_iso2 = malloc((MAX_ISO_PATHS + 1) * sizeof(_directory_iso2));

    if(!directory_iso2) {
        printf("Error!: in directory_is malloc()");
        goto err;
    }

    memset(directory_iso2, 0, (MAX_ISO_PATHS + 1) * sizeof(_directory_iso2));
 
    sectors = malloc(((size0 + 2047)/2048) * 2048);

    if(!sectors) {
        printf("Error!: in sectors malloc()");
        goto err;
    }

    sectors2 = malloc(2048 * 2);

    if(!sectors2) {
        printf("Error!: in sectors2 malloc()");
        goto err;
    }

    if(fread((void *) sectors, 1, size0, fp) != size0) {
        printf("Error!: reading path_table");
        goto err;
    }


    u32 p = 0;

    string2[0] = 0;

    idx = 0;

    directory_iso2[idx].name = NULL;

    while(p < size0) {

        u32 lba;

        u32 snamelen = isonum_721((void *) &sectors[p]);
        if(snamelen == 0) p= ((p/2048) * 2048) + 2048;
        p+=2;
        lba = isonum_731(&sectors[p]);
        p+=4;
        u32 parent =isonum_721((void *) &sectors[p]);
        p+=2;

        memset(wstring, 0, 512 * 2);
        memcpy(wstring, &sectors[p], snamelen);
        
        UTF16_to_UTF8(wstring, (u8 *) string);

        if(idx >= MAX_ISO_PATHS){
            printf("Too much folders (max %i)", MAX_ISO_PATHS);
            goto err;
        }

        directory_iso2[idx].name = malloc(strlen(string) + 2);
        if(!directory_iso2[idx].name) {
            printf("Error!: in directory_iso2.name malloc()");
            goto err;
        }

        strcpy(directory_iso2[idx].name, "/");
        strcat(directory_iso2[idx].name, string);
        
        directory_iso2[idx].parent = parent;
        
        get_iso_path(string2, idx);
   
        u32 file_lba = 0;
        u64 file_size = 0;

        char file_aux[0x420];

        file_aux[0] = 0;

        int q2 = 0;
        int size_directory = 0;

        while(1) {

            if(fseek(fp, ((u64) lba) * 2048ULL, SEEK_SET)<0) {
                printf("Error!: in directory_record fseek");
                goto err;
            }

            memset(sectors2 + 2048, 0, 2048);

            if(fread((void *) sectors2, 1, 2048, fp) != 2048) {
                printf("Error!: reading directory_record sector");
                goto err;
            }

            int q = 0;
            
            if(q2 == 0) {
                idr = (struct iso_directory_record *) &sectors2[q];
                if((int) idr->name_len[0] == 1 && idr->name[0]== 0 && lba == isonum_731((void *) idr->extent) && idr->flags[0] == 0x2) {
                    size_directory = isonum_733((void *) idr->size);
                 
                } else {
                    printf("Error!: Bad first directory record! (LBA %i)", lba);
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

                    printf("Warning! Entry directory break the standard ISO 9660Press ENTER key");
                    

                    if(fseek(fp, lba * 2048 + 2048, SEEK_SET)<0) {
                        printf("Error!: in directory_record fseek");
                        goto err;
                    }

                    if(fread((void *) (sectors2 + 2048), 1, 2048, fp) != 2048) {
                        printf("Error!: reading directory_record sector");
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
                        printf("Error!: in directory_record fseek");
                        goto err;
                    }

                    if(fread((void *) (sectors2), 1, 2048, fp) != 2048) {
                        printf("Error!: reading directory_record sector");
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
    
                            printf("Error!: in batch file %s", file_aux);
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
                    if(len!=1) strcat(string2, "/");
                    strcat(string2, string);
					
					*nb_file = *nb_file + 1;
					*total_size = *total_size + file_size;
					
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
    if(sectors) free(sectors);
    if(sectors2) free(sectors2);

    for(n = 0; n <= idx; n++)
        if(directory_iso2[n].name) {free(directory_iso2[n].name); directory_iso2[n].name = NULL;}
    
    if(directory_iso2) free(directory_iso2);   

    return SUCCESS;

err:

    if(fp) fclose(fp);
    if(sectors) free(sectors);
    if(sectors2) free(sectors2);

    for(n = 0; n <= idx; n++)
        if(directory_iso2[n].name) {free(directory_iso2[n].name); directory_iso2[n].name = NULL;}
    
    if(directory_iso2) free(directory_iso2);

    return FAILED;
}

void fputs_hex(u8 *data, size_t len, FILE *f)
{
   int i = 0;
   char line[33];
   memset(line, 0, 33);
   
   while( i < len) {
       
        sprintf(&line[i%16*2], "%02X",  data[i]);
        if((i>0 && i%16 == 15) || i == (len-1)) {
            fputs(line, f);
            memset(line, 0, 33);
        }
        i++;
   } 
}

u8 IRD_get_md5(char *GAME_PATH, ird_t *ird, int len)
{
	char FULL_PATH[512];
	DIR *d;
	struct dirent *dir;
	
	d = opendir(GAME_PATH);
	if(d==NULL) return FAILED;
	
	while ((dir = readdir(d))) {
		if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) continue;
		
		sprintf(FULL_PATH, "%s/%s", GAME_PATH, dir->d_name);
		
		if(cancel) break;
		
		if(dir->d_type & DT_DIR) {
			if( IRD_get_md5(FULL_PATH, ird, len)==FAILED ) break;
			continue;
		}
		
		ird->FileHashesNumber = ird->FileHashesNumber + 1;
			
		ird->FileHashes = (FileHash_t *) realloc(ird->FileHashes, ird->FileHashesNumber * sizeof(FileHash_t));

		ird->FileHashes[ird->FileHashesNumber-1].FilePath = strcpy_malloc(&FULL_PATH[len]);
								
		memset(ird->FileHashes[ird->FileHashesNumber-1].FileHash, 0, 0x10);
		
		md5_file(FULL_PATH, ird->FileHashes[ird->FileHashesNumber-1].FileHash);
	}
	closedir(d);
	
	if(cancel) return FAILED;
	
	return SUCCESS;
	
}

void IRD_search_md5(char *FILE_PATH, ird_t *ird, u8 output_md5[0x10])
{
	int j;
	memset(output_md5, 0, 0x10);
	
	u64 len = strlen(FILE_PATH);
	for(j=0; j<ird->FileHashesNumber; j++) {
		if( !memcmp(FILE_PATH, ird->FileHashes[j].FilePath, len) ) {
			memcpy(output_md5, ird->FileHashes[j].FileHash, 0x10);
			return;
		}
	}
}

void IRD_check_md5(char *GAME_PATH, char **IRD_PATH, u32 IRD_nPATH)
{
	print_debug("inside IRD_check_md5");
	
	int i, j, n;
	
	char msg[512];
	char IRD_LOG[512];
	char IRD_HEADER[512];
	FILE *log=NULL;
	FILE *res=NULL;
	u32 nValid[IRD_nPATH];
	u32 nModified[IRD_nPATH];
	u32 nExtra[IRD_nPATH];
	u32 nNotFound[IRD_nPATH];
	
	ird_t *ird[IRD_nPATH];
	for(n=0; n<IRD_nPATH; n++) {
		nValid[n]=0;
		nExtra[n]=0;
		nModified[n]=0;
		nNotFound[n]=0;
		ird[n]=NULL;
	}
	ird_t *game_ird=NULL;
	
	u8 gameiso = is_iso(GAME_PATH);
	
	game_ird = IRD_new(GAME_PATH);
	if(game_ird==NULL) {
		print_load("Error : failed to IRD_new, game_ird");
		goto error;
	}
	
	for(n=0; n<IRD_nPATH; n++) {
		sprintf(IRD_HEADER, "%s.header.bin", IRD_PATH[n]);
		
		ird[n]=IRD_load(IRD_PATH[n]);
		if(ird[n]==NULL) {
			print_load("Error : failed to IRD_load %s", IRD_PATH[n]);
			continue;
		}
		
		int ret = GZ_decompress7((char *) ird[n]->Header, ird[n]->HeaderLength, IRD_HEADER);
		if( ret != Z_OK ) {
			printf("Error : failed to decompress header (%s)", ret);
			continue;
		}
		
		IRD_GetFilesPath(IRD_HEADER, ird[n]);
		
		Delete(IRD_HEADER);
	}
	
	if(gameiso) {
		print_load("Gathering data...");
		s64 nFiles;
		u64 tSize;
		
		if( IRD_FilesInfo(GAME_PATH, &nFiles, &tSize) == FAILED) {
			print_load("Error : failed to IRD_FilesInfo");
			goto error;
		}
		
		print_load("Calculating files' MD5...");
		task_Init(tSize);
		int ret = IRD_FilesHashes(GAME_PATH, game_ird, NULL, NULL);
		task_End();
		
		if(ret == FAILED) {
			print_load("Error : failed to get filehashes");
			goto error;
		}
	} else {
		print_load("Gathering data...");
		u64 tSize = get_size(GAME_PATH);
		
		print_load("Calculating MD5...");
		task_Init(tSize);
		print_debug("IRD_get_md5...");
		IRD_get_md5(GAME_PATH, game_ird, strlen(GAME_PATH));
		print_debug("task_End...");
		task_End();	
		
	}
	
	sprintf(IRD_LOG, "%s.check_md5.txt", GAME_PATH);
	log = fopen(IRD_LOG, "wb");
	if(log==NULL) {
		print_load("Error : cannot fopen %s", IRD_LOG);
		goto error;
	}
	
	sprintf(IRD_LOG, "%s.result_md5.txt", GAME_PATH);
	res = fopen(IRD_LOG, "wb");
	if(res==NULL) {
		print_load("Error : cannot fopen %s", IRD_LOG);
		goto error;
	}
	
	sprintf(msg, "Game Name : %s\nGame ID : %s\nUpdate : %s\nGame Version : %s\nApp Version : %s\n\n", ird[0]->GameName, ird[0]->GameId, ird[0]->UpdateVersion, ird[0]->GameVersion, ird[0]->AppVersion);
	fputs(msg, log); fputs(msg, res);
	
	for(i=0; i<IRD_nPATH; i++) {
		
		for(j=0; j<ird[i]->FileHashesNumber; j++) {
				
			u8 game_md5[0x10] = {0};
			
			IRD_search_md5(ird[i]->FileHashes[j].FilePath, game_ird, game_md5);
			
			if( *(u64 *) &game_md5[8] == (u64) 0ULL) {
				nNotFound[i] +=1;
			} else
			if( !memcmp(game_md5, ird[i]->FileHashes[j].FileHash, 0x10) ) {
				nValid[i] += 1;
			} else {
				nModified[i] +=1;
			}
		}
		for(j=0; j<game_ird->FileHashesNumber; j++) {
			u8 ird_md5[0x10] = {0};
			memset(ird_md5, 0, 0x10);
			IRD_search_md5(game_ird->FileHashes[j].FilePath, ird[i], ird_md5);
			
			if( *(u64 *) &ird_md5[8] != (u64) 0ULL) continue;
			
			nExtra[i] += 1;
		}
	}
	
	for(i=0; i<IRD_nPATH; i++) {
		
		if( IRD_nPATH != 1 ) {
			sprintf(msg, "# IRD n°%d/%d\n\n", i+1, IRD_nPATH);
			fputs(msg, log); fputs(msg, res);
		}
		
		sprintf(msg, "Files Number = %d (backup) / %d (ird)\n", game_ird->FileHashesNumber, ird[i]->FileHashesNumber);
		fputs(msg, log); fputs(msg, res);
		
		sprintf(msg, "%-12s : %d\n", STR_VALID     , nValid[i]);    fputs(msg, log); fputs(msg, res);
		sprintf(msg, "%-12s : %d\n", STR_NOT_FOUND , nNotFound[i]); fputs(msg, log); fputs(msg, res);
		sprintf(msg, "%-12s : %d\n", STR_MODIFIED  , nModified[i]); fputs(msg, log); fputs(msg, res);
		sprintf(msg, "%-12s : %d\n", STR_EXTRA     , nExtra[i]);    fputs(msg, log); fputs(msg, res);
		
		fputs("____________________________ _ _ _\n", res);
		fputs("                 |\n", res);
		fputs("  INFO           | PATH\n", res);
		fputs("_________________|__________ _ _ _\n", res);
		fputs("                 |\n", res);
		
		fputs("__________________________________________________________________________________________________ _ _ _\n", log);
		fputs("                 |                                  |                                  |\n", log);
		fputs("  INFO           | MD5 from IRD                     | MD5 from GAME                    | PATH\n", log);
		fputs("_________________|__________________________________|__________________________________|__________ _ _ _\n", log);
		fputs("                 |                                  |                                  |\n", log);
		
		for(j=0; j<ird[i]->FileHashesNumber; j++) {
			
			u8 is_valid=NO;

			u8 game_md5[0x10] = {0};
			
			IRD_search_md5(ird[i]->FileHashes[j].FilePath, game_ird, game_md5);
			
			if( *(u64 *) &game_md5[8] == (u64) 0ULL ) {
				sprintf(msg, " %-16s|", STR_NOT_FOUND); fputs(msg, log); fputs(msg, res);
			} else
			if( !memcmp(game_md5, ird[i]->FileHashes[j].FileHash, 0x10) ) {
				sprintf(msg, " %-16s|", STR_VALID); fputs(msg, log);
				is_valid=YES;
			} else {
				sprintf(msg, " %-16s|", STR_MODIFIED); fputs(msg, log); fputs(msg, res);
			}
			
			sprintf(msg, " %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X |", 
						ird[i]->FileHashes[j].FileHash[0x0],
						ird[i]->FileHashes[j].FileHash[0x1],
						ird[i]->FileHashes[j].FileHash[0x2],
						ird[i]->FileHashes[j].FileHash[0x3],
						ird[i]->FileHashes[j].FileHash[0x4],
						ird[i]->FileHashes[j].FileHash[0x5],
						ird[i]->FileHashes[j].FileHash[0x6],
						ird[i]->FileHashes[j].FileHash[0x7],
						ird[i]->FileHashes[j].FileHash[0x8],
						ird[i]->FileHashes[j].FileHash[0x9],
						ird[i]->FileHashes[j].FileHash[0xA],
						ird[i]->FileHashes[j].FileHash[0xB],
						ird[i]->FileHashes[j].FileHash[0xC],
						ird[i]->FileHashes[j].FileHash[0xD],
						ird[i]->FileHashes[j].FileHash[0xE],
						ird[i]->FileHashes[j].FileHash[0xF]);
			fputs(msg, log);
			
			sprintf(msg, " %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X |", 
						game_md5[0x0],
						game_md5[0x1],
						game_md5[0x2],
						game_md5[0x3],
						game_md5[0x4],
						game_md5[0x5],
						game_md5[0x6],
						game_md5[0x7],
						game_md5[0x8],
						game_md5[0x9],
						game_md5[0xA],
						game_md5[0xB],
						game_md5[0xC],
						game_md5[0xD],
						game_md5[0xE],
						game_md5[0xF]);
			fputs(msg, log);
			
			
			sprintf(msg, " %s\n", ird[i]->FileHashes[j].FilePath);
			fputs(msg, log); 
			if(!is_valid) fputs(msg, res);
		}
		
		for(j=0; j<game_ird->FileHashesNumber; j++) {
			u8 ird_md5[0x10] = {0};
			memset(ird_md5, 0, 0x10);
			
			IRD_search_md5(game_ird->FileHashes[j].FilePath, ird[i], ird_md5);
			
			if( *(u64 *) &ird_md5[8] != (u64) 0ULL) continue; 
			
			sprintf(msg, " %-16s|", STR_EXTRA); fputs(msg, log); fputs(msg, res);
			
			sprintf(msg, " %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X |", 
						ird_md5[0x0],
						ird_md5[0x1],
						ird_md5[0x2],
						ird_md5[0x3],
						ird_md5[0x4],
						ird_md5[0x5],
						ird_md5[0x6],
						ird_md5[0x7],
						ird_md5[0x8],
						ird_md5[0x9],
						ird_md5[0xA],
						ird_md5[0xB],
						ird_md5[0xC],
						ird_md5[0xD],
						ird_md5[0xE],
						ird_md5[0xF]);
			fputs(msg, log);
			
			sprintf(msg, " %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X |", 
						game_ird->FileHashes[j].FileHash[0x0],
						game_ird->FileHashes[j].FileHash[0x1],
						game_ird->FileHashes[j].FileHash[0x2],
						game_ird->FileHashes[j].FileHash[0x3],
						game_ird->FileHashes[j].FileHash[0x4],
						game_ird->FileHashes[j].FileHash[0x5],
						game_ird->FileHashes[j].FileHash[0x6],
						game_ird->FileHashes[j].FileHash[0x7],
						game_ird->FileHashes[j].FileHash[0x8],
						game_ird->FileHashes[j].FileHash[0x9],
						game_ird->FileHashes[j].FileHash[0xA],
						game_ird->FileHashes[j].FileHash[0xB],
						game_ird->FileHashes[j].FileHash[0xC],
						game_ird->FileHashes[j].FileHash[0xD],
						game_ird->FileHashes[j].FileHash[0xE],
						game_ird->FileHashes[j].FileHash[0xF]);
			fputs(msg, log);
			
			sprintf(msg, " %s\n", game_ird->FileHashes[j].FilePath);
			fputs(msg, log); fputs(msg, res);
		}
		fputs("_________________|__________________________________|__________________________________|_________ _ _ _\n\n\n", log);
		fputs("_________________|__________ _ _ _\n\n\n", res);
	}
	
error:
	FCLOSE(log);
	FCLOSE(res);
	for(i=0; i<IRD_nPATH; i++) {
		FREE_IRD(ird[i]);
	}
	FREE_IRD(game_ird);
	
	print_debug("end of IRD_check_md5");
}

u8 IRD_FilesHashes(char *ISO_PATH, ird_t *ird, u64 *start_filetable, u64 *end_filetable)
{
	FileHash_t *TempFH=NULL;
	u32 nFileHashes = 0;
	
	if( ird != NULL ) ird->FileHashesNumber=0;
	if( start_filetable != NULL) *start_filetable=0;
	if( end_filetable != NULL) *end_filetable=0;
	
	struct stat s;
    int n, i;
    
    char path1[0x420];

    u8 *sectors = NULL;
    u8 *sectors2 = NULL;
    u8 *sectors3 = NULL;

    static char string[0x420];
    static char string2[0x420];
    static u16 wstring[1024];

    struct iso_primary_descriptor sect_descriptor;
    struct iso_directory_record * idr;
    int idx = -1;

    directory_iso2 = NULL;

    fp_split = NULL;
    fp_split0 = NULL;
    split_index = 0;

	strcpy(path1, ISO_PATH);
	
    fixpath(path1);

    n = strlen(path1);
	
    if(n >= 4 && (!strncasecmp(&path1[n - 4], ".iso", 4))) {

        sprintf(split_file[0].path, "%s", path1);
        if(stat(split_file[0].path, &s)<0) {
            printf("Error: ISO file don't exists!"); 
			return FAILED;
        }

        split_file[0].size = s.st_size;
        split_file[1].size = 0; // split off
       
    } else if(n >= 6 && (!strncasecmp(&path1[n - 6], ".iso.0", 6))) {

        int m;

        for(m = 0; m < 64; m++) {
            strcpy(string2, path1);
            string2[n - 2] = 0; 
            sprintf(split_file[m].path, "%s.%i%c", string2, m, '\0');
            if(stat(split_file[m].path, &s)<0) break;
            split_file[m].size = s.st_size;
			printf("%s : %llX", split_file[m].path, split_file[m].size);
        }

        for(; m < 64; m++) {
            split_file[m].size = 0;
        }
    } else {
        printf("Error: file must be with .iso, .ISO .iso.0 or .ISO.0 extension");
		return FAILED;
    }
    
	FILE *fp = fopen(path1, "rb");
    if(!fp) {
        printf("Error!: Cannot open ISO file");
        return FAILED;
    }
	
	fp_split0 = fp;
	
    if(fseek(fp, 0x8800, SEEK_SET)<0) {
        printf("Error!: in sect_descriptor fseek");
        goto err;
    }

    if(fread((void *) &sect_descriptor, 1, 2048, fp) != 2048) {
        printf("Error!: reading sect_descriptor");
        goto err;
    }

    if(!(sect_descriptor.type[0] == 2 && !strncmp((void *) &sect_descriptor.id[0], "CD001",5))) {
        printf("Error!: UTF16 descriptor not found");
        goto err;
    }

    u32 lba0 = isonum_731(&sect_descriptor.type_l_path_table[0]); // lba
    u32 size0 = isonum_733(&sect_descriptor.path_table_size[0]); // tamaño
    //printf("lba0 %u size %u %u", lba0, size0, ((size0 + 2047)/2048) * 2048);
    
    if(fseek(fp, lba0 * 2048, SEEK_SET)<0) {
        printf("Error!: in path_table fseek");
        goto err;
    }

    directory_iso2 = malloc((MAX_ISO_PATHS + 1) * sizeof(_directory_iso2));

    if(!directory_iso2) {
        printf("Error!: in directory_is malloc()");
        goto err;
    }

    memset(directory_iso2, 0, (MAX_ISO_PATHS + 1) * sizeof(_directory_iso2));
 
    sectors = malloc(((size0 + 2047)/2048) * 2048);

    if(!sectors) {
        printf("Error!: in sectors malloc()");
        goto err;
    }

    sectors2 = malloc(2048 * 2);

    if(!sectors2) {
        printf("Error!: in sectors2 malloc()");
        goto err;
    }

    sectors3 = malloc(IRD_FILE_BUFFSIZE);
    if(!sectors3) {
        printf("Error!: in sectors3 malloc()");
        goto err;
    }
	
    if(fread((void *) sectors, 1, size0, fp) != size0) {
        printf("Error!: reading path_table");
        goto err;
    }


    u32 p = 0;

    string2[0] = 0;

    idx = 0;

    directory_iso2[idx].name = NULL;

    while(p < size0) {

        u32 lba;

        u32 snamelen = isonum_721((void *) &sectors[p]);
        if(snamelen == 0) p= ((p/2048) * 2048) + 2048;
        p+=2;
        lba = isonum_731(&sectors[p]);
        p+=4;
        u32 parent =isonum_721((void *) &sectors[p]);
        p+=2;

        memset(wstring, 0, 512 * 2);
        memcpy(wstring, &sectors[p], snamelen);
        
        UTF16_to_UTF8(wstring, (u8 *) string);

        if(idx >= MAX_ISO_PATHS){
            printf("Too much folders (max %i)", MAX_ISO_PATHS);
            goto err;
        }

        directory_iso2[idx].name = malloc(strlen(string) + 2);
        if(!directory_iso2[idx].name) {
            printf("Error!: in directory_iso2.name malloc()");
            goto err;
        }

        strcpy(directory_iso2[idx].name, "/");
        strcat(directory_iso2[idx].name, string);
        
        directory_iso2[idx].parent = parent;
        
        get_iso_path(string2, idx);
   
        u32 file_lba = 0;
        u64 file_size = 0;

        char file_aux[0x420];

        file_aux[0] = 0;

        int q2 = 0;
        int size_directory = 0;

        while(1) {

            if(fseek(fp, ((u64) lba) * 2048ULL, SEEK_SET)<0) {
                printf("Error!: in directory_record fseek");
                goto err;
            }

            memset(sectors2 + 2048, 0, 2048);

            if(fread((void *) sectors2, 1, 2048, fp) != 2048) {
                printf("Error!: reading directory_record sector");
                goto err;
            }

            int q = 0;
            
            if(q2 == 0) {
                idr = (struct iso_directory_record *) &sectors2[q];
                if((int) idr->name_len[0] == 1 && idr->name[0]== 0 && lba == isonum_731((void *) idr->extent) && idr->flags[0] == 0x2) {
                    size_directory = isonum_733((void *) idr->size);
                 
                } else {
                    printf("Error!: Bad first directory record! (LBA %i)", lba);
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

                    printf("Warning! Entry directory break the standard ISO 9660Press ENTER key");
                    

                    if(fseek(fp, lba * 2048 + 2048, SEEK_SET)<0) {
                        printf("Error!: in directory_record fseek");
                        goto err;
                    }

                    if(fread((void *) (sectors2 + 2048), 1, 2048, fp) != 2048) {
                        printf("Error!: reading directory_record sector");
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
                        printf("Error!: in directory_record fseek");
                        goto err;
                    }

                    if(fread((void *) (sectors2), 1, 2048, fp) != 2048) {
                        printf("Error!: reading directory_record sector");
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
    
                            printf("Error!: in batch file %s", file_aux);
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
                    if(len!=1) strcat(string2, "/");
                    strcat(string2, string);
					
					/* I prefer not using this just in case I use this function with a not proper/original iso
					if( start_filetable != NULL ) {
						if( strcmp(string2, "/PS3_DISC.SFB") == 0 ) {
							*start_filetable = (u64) file_lba*0x800ULL;
						}
					}
					if( end_filetable != NULL ) {	
						if( strcmp(string2, "/PS3_UPDATE/PS3UPDAT.PUP") == 0 ) {
							*end_filetable = (u64) file_lba* 0x800ULL + (u64) file_size;
						}
					}
					*/
					
					if( start_filetable != NULL ) {
						if(*start_filetable==0) *start_filetable = (u64) file_lba*0x800ULL;
						if((u64) file_lba*0x800ULL < *start_filetable) *start_filetable = (u64) file_lba*0x800ULL;
					}
					if( end_filetable != NULL ) {	
						u64 footer = (u64) file_lba* 0x800ULL + (u64) file_size;
						footer = ((footer + 2047)/2048) * 2048;
						
						if(*end_filetable==0) *end_filetable = footer;
						if(*end_filetable < footer) *end_filetable = footer;
					}
					
					if( ird != NULL) {
						nFileHashes = nFileHashes + 1;
						
						TempFH = (FileHash_t *) realloc(TempFH, nFileHashes * sizeof(FileHash_t));
		
						TempFH[nFileHashes-1].FilePath = strcpy_malloc(string2);
										
						TempFH[nFileHashes-1].Sector = file_lba;
						memset(TempFH[nFileHashes-1].FileHash, 0, 0x10);
						
						md5_context ctx;
						md5_starts( &ctx );
											
						strcpy(copy_file, string2);
						copy_file_prog_bar=0;
						
						u32 fsize;
						u64 to_read = file_size;
											
						u64 read_position = (u64) file_lba * 0x800ULL;
						
						task_Init(to_read);
						while(to_read > 0) {
							if(to_read > IRD_FILE_BUFFSIZE) fsize = IRD_FILE_BUFFSIZE;
							else fsize = (u32) to_read;
							
							memset(sectors3, 0, IRD_FILE_BUFFSIZE);
							
							int read_ret = read_split(read_position, sectors3, (int) fsize);
							if(read_ret < 0) {
								printf("Error!: reading ISO file: fzise %lX, file_offset %llX : return %d", fsize, read_position, read_ret);
								goto err;
							}
							
							md5_update(&ctx, sectors3, fsize);

							to_read-= (u64) fsize;
							
							read_position += fsize;
							
							if( copy_cancel || cancel) goto err;
							copy_current_size+=fsize;
							task_Update(fsize);
							
							copy_file_prog_bar=((file_size - to_read) * 100)/ file_size;
						}
						task_End();
						
						md5_finish(&ctx, TempFH[nFileHashes-1].FileHash);
					}
					
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

	
// sort
	if( ird != NULL ) {
		ird->FileHashes = malloc(nFileHashes * sizeof(FileHash_t) );
		ird->FileHashesNumber = nFileHashes;
		
		u64 smallest_sector = 0;
		for(n=0; n<nFileHashes; n++) {
			
			for(i=0; i<nFileHashes; i++) {
				if( TempFH[i].Sector < TempFH[smallest_sector].Sector ) {
					smallest_sector = i;
				}
			}
			
			memcpy(ird->FileHashes[n].FileHash, TempFH[smallest_sector].FileHash, 0x10);
			ird->FileHashes[n].Sector = TempFH[smallest_sector].Sector;
			ird->FileHashes[n].FilePath = strcpy_malloc(TempFH[smallest_sector].FilePath);
			
			TempFH[smallest_sector].Sector = -1; // MAX !
		}
		
		for(n=0; n<nFileHashes; n++) FREE(TempFH[n].FilePath);
		FREE(TempFH);
	}
	
    return SUCCESS;

err:
	
	for(n=0; n<nFileHashes; n++) FREE(TempFH[n].FilePath);
	FREE(TempFH);
	
    if(fp) fclose(fp);
    if(split_index && fp_split) {fclose(fp_split); fp_split = NULL;}
	
    if(sectors) free(sectors);
    if(sectors2) free(sectors2);
    if(sectors3) free(sectors3);

    for(n = 0; n <= idx; n++)
        if(directory_iso2[n].name) {free(directory_iso2[n].name); directory_iso2[n].name = NULL;}
    
    if(directory_iso2) free(directory_iso2);

    return FAILED;
}
