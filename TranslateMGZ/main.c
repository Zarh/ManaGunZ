#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000)
#ifdef FAILED
#undef FAILED
#endif
#endif

#define FAILED		0
#define SUCCESS		1

typedef uint8_t		u8;
typedef uint16_t 	u16;
typedef uint32_t	u32;
typedef uint64_t 	u64;

#define print_debug printf
#define print_load printf

#define source_lang_code	"en"

typedef struct{
	char filename[32];
	char lang_code[32];  // code used in PS3/ManaGunZ
	char lang_code2[32]; // code used in libretranslate
	char lang_name[32];
} lang_t;

//#define USE_CROW 1

#ifdef USE_CROW
#define crow_path "\"C:\\Program Files\\Crow Translate\\crow.exe\""
lang_t languages[] = 
{	
	{"EN.txt", "\\x01", "en", "English"},
	{"ES.txt", "\\x02", "es", "Español"},
	{"FR.txt", "\\x03", "fr", "Français"},
	{"HU.txt", "\\x20", "hu", "Magyar"},
	{"Chinese_S.txt", "\\x0B", "zh-CN", "简体中文"},
	{"IT.txt", "\\x04", "it", "Italiano"},
	{"NL.txt", "\\x05", "nl", "Nederlands"},
	{"PL.txt", "\\x10", "pl", "Polski"},
	{"RU.txt", "\\x08", "ru", "Русский"},
	{"SE.txt", "\\x0D", "sv", "Svenska"},
	{"GE.txt", "\\x00", "de", "Deutsch"},
	{"JP.txt", "\\x08", "ja", "日本語"},
	{"KR.txt", "\\x09", "ko", "한국인"},
	{"PT.txt", "\\x06", "pt", "Português"},
	{"TR.txt", "\\x21", "tr", "Türkçe"}
};
#define enginesCount 5
const char *engines[enginesCount]= {"bing",
									"libretranslate",
									"google",
									"yandex",
									"lingva"
									};
int current_engine=0;
#else
lang_t languages[] = 
{	
	{"EN.txt", "\\x01", "en", "English"},
	{"ES.txt", "\\x02", "es", "Español"},
	{"FR.txt", "\\x03", "fr", "Français"},
	{"HU.txt", "\\x20", "hu", "Magyar"},
	{"Chinese_S.txt", "\\x0B", "zh", "简体中文"},
	{"IT.txt", "\\x04", "it", "Italiano"},
	{"NL.txt", "\\x05", "nl", "Nederlands"},
	{"PL.txt", "\\x10", "pl", "Polski"},
	{"RU.txt", "\\x08", "ru", "Русский"},
	{"SE.txt", "\\x0D", {0}, "Svenska"},
	{"GE.txt", "\\x00", "de", "Deutsch"},
	{"JP.txt", "\\x08", "ja", "日本語"},
	{"KR.txt", "\\x09", "ko", "한국인"},
	{"PT.txt", "\\x06", "pt", "Português"},
	{"TR.txt", "\\x21", "tr", "Türkçe"}
};
#define enginesCount 6
const char *engines[enginesCount]= {"https://trans.zillyhuhn.com",
									"https://libretranslate.de",
									"https://translate.mentality.rip",
									"https://translate.argosopentech.com",
									"https://translate.astian.org",
									"https://translate.mentality.rip"
									};
int current_engine=0;
#endif

#define languagesCount 15


void TranslateString(char *input, char *output, char *lang_code2)
{
	if(lang_code2[0] == 0 || strcmp(source_lang_code, lang_code2) == 0) {
		strcpy(output, input);
		return;
	}
	char msg[1024]={0};
	
	//it's not working anymore on my computer...
	//sprintf(msg, "py translate.py \"%s\" \"%s\" \"%s\"", input, source_lang_code, lang_code2);
	
#ifdef USE_CROW	
	u8 wait=1;
	u8 loop_number=0;
retry:
	sprintf(msg, "\"" crow_path " -e \"%s\" -b -s \"%s\" -t \"%s\" \"%s\" > res_ansi.txt" "\"", engines[current_engine], source_lang_code, lang_code2, input);
	system(msg);
	system("iconv -f \"windows-1252\" -t \"UTF-8\" res_ansi.txt > res_utf8.txt")
	memset(msg,0,1024);
	FILE *f = fopen("res_utf8.txt", "rb");
	if(f==NULL) return;
	fread(msg, 1024, 1, f);
	fclose(f);
	if( strcmp(msg, "\r\n") == 0) {
		if( wait ) {
			printf("Engine %s return nothing, waiting 30s\n",  engines[current_engine]);
			sleep(30);
			wait=0;
			goto retry;
		}
		if( loop_number == 3 ) {
			printf("Error: can't translate string...\n");
			exit(0);
		}
		current_engine++;
		wait=1;
		if(current_engine==enginesCount) {
			loop_number++;
			current_engine=0;
		}
		printf("Next engine: %s\n", engines[current_engine]);
		goto retry;
	}
#else
retry:
	current_engine=1;
	sprintf(msg, "curl -s -X POST %s/translate -H \"Content-Type: application/json\" -d \"{\\\"q\\\":\\\"%s\\\",\\\"source\\\":\\\"%s\\\",\\\"target\\\":\\\"%s\\\"}\" | jq -r \".translatedText\" > res.txt", engines[current_engine], input, source_lang_code, lang_code2);
	system(msg);
	// to avoid ban for spam, I don't know if it's necessary...
	sleep(1);
	memset(msg,0,1024);
	FILE *f = fopen("res.txt", "rb");
	if(f==NULL) {
		current_engine++;
		if(current_engine==enginesCount) {
			current_engine=0;
			printf("New engine: %s", engines[current_engine]);
		}
		goto retry;
	}
	fread(msg, 1024, 1, f);
	fclose(f);
	if( strcmp(msg, "null\r\n") == 0) {
		current_engine++;
		if(current_engine==enginesCount) {
			current_engine=0;
			printf("New engine: %s", engines[current_engine]);
		}
		goto retry;
	}
#endif

	int l = strlen(msg);
	if( msg[l-1] == '\n' ) msg[l-1]= 0;
	if( msg[l-2] == '\r' ) msg[l-2]= 0;

	//if( strstr(msg, "translatedText") == NULL) return;
	
	strcpy(output, msg);
	system("rm -f res.txt");
	system("rm -f res_ansi.txt");
	system("rm -f res_utf8.txt");
	
}

u8 FileExist(char *path)
{
	struct stat s;
	if( stat(path, &s) == 0) return 1;
	return 0;
}

char *LoadFile(char *path)
{
	struct stat s;
	if(stat(path, &s) != 0) return NULL;  
	if(S_ISDIR(s.st_mode)) return NULL;
	if(s.st_size == 0) return NULL;
	
	char *mem = malloc(s.st_size);
	if(mem==NULL) return NULL;
	memset(mem, 0, s.st_size);

	FILE *f1 = fopen(path, "rb");
	if(f1==NULL) return NULL;
	
	u64 read = fread(mem, sizeof(char), s.st_size, f1);
	
	fclose(f1);
	
	if(read != s.st_size) {
		free(mem); 
		return NULL;
	}
	
	return mem;
}

void Translate(char *source, char *WDIR)
{	
	FILE *f;
	char FilePath[512];
	
	f = fopen(source, "rb");
	if( f==NULL ) {
		printf("Error : cannot open %s", source);
		return;
	}
	
	int i;
	for(i=0; i<languagesCount; i++) {
		printf("Translating %s\n", languages[i].filename);
		sprintf(FilePath, "%s\%s", WDIR, languages[i].filename);
		
		u8 full=0;
		char *f1_mem = LoadFile(FilePath);
		if( f1_mem==NULL ) {
			full = 1;
		}
		
		FILE *f1 = NULL;
		if( full ) f1 = fopen(FilePath, "wb");
		else f1 = fopen(FilePath, "ab");
		
		if( f1 == NULL) {
			printf("Error: failed to open %s", FilePath);
			continue;
		}
		
		char line[512];
		char strName[128];
		char STR_MSG[512];
		char STR_TRANSLATED[512];
		char MSG[512];
		
		memset(MSG, 0, 512);
		
		if(full) {
			sprintf(MSG, "%-30s{%s}\n", (char *) "STR_LANGUAGE", languages[i].lang_name);
			fputs(MSG, f1);
			sprintf(MSG, "%-30s{%s}\n\n", (char *) "STR_LANGCODE", languages[i].lang_code);
			fputs(MSG, f1);
		}
		
		fseek(f, 0, SEEK_SET);
		while(fgets(line, 512, f) != NULL) {
			memset(strName, 0, 128);
			memset(STR_MSG, 0, 512);
			memset(STR_TRANSLATED, 0, 512);
			
			char *STR=strstr(line, "char *STR_");
			if( STR == NULL) continue;
			STR += 6;
			
			//get strName (name of the string)
			int l = 0;
			while(STR[l] != ';' && STR[l] != ' ' && STR[l] != '=') l++;
			strncpy(strName, STR, l);
			
			// check if it's not already inside the translate file...
			if( f1_mem != NULL) {
				char t[30];
				sprintf(t, "%s\t", strName);
				char *res = strstr(f1_mem, t);
				if(res != NULL) continue;
				sprintf(t, "%s ", strName);
				res = strstr(f1_mem, t);
				if(res != NULL) continue;	
			}
			
			while(fgets(line, 512, f) != NULL) {
				if(strstr(line, "#define ") !=NULL) break;
			}
			
			//get STR_MSG, string to translate
			char *start=strchr(line, '\"');
			if(start == NULL) continue;
			start+=1;
			char *end=strrchr(start, '\"');
			if(end == NULL)	continue;
			strncpy(STR_MSG, start, end-start);
			
			TranslateString(STR_MSG, STR_TRANSLATED, languages[i].lang_code2);
			
			memset(MSG, 0, 512);
			sprintf(MSG, "%-30s{%s}\n", strName, STR_TRANSLATED);
			fputs(MSG, f1);
			memset(line, 0, 512);
			fflush(f1);
		}
		fclose(f1);
		if( f1_mem ) {free(f1_mem); f1_mem=NULL;}
	}
	
	fclose(f);
}

u8 is_dir(char *path)
{
	struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

#define do_translate	 	0

void do_task(char *source, char *dir, u8 task)
{
	switch(task)
	{
		case do_translate:
		{
			Translate(source, dir);
		}
		break;
		default:
		{
			printf("error !");
		}
		break;
	}
}

int main (int argc, char **argv)
{
	u8 task = do_translate;
	
	u32 a = 1;
    int i;
    for(i=1; i<argc; i++) {
        if( !strcmp(argv[i], "-t") || !strcmp(argv[i], "--translate") ) {
            task = do_translate;
            a++;
        }
    }
	if( a+1 < argc) do_task(argv[a], argv[a+1], task);
	
	return 0;
}
