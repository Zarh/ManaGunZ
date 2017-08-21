// http://www.psdevwiki.com/ps3/VSMX

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VSMX_MAGIC		0x584D5356
#define VSMX_PSP		0x00010000
#define VSMX_PS3 		0x00020000

#define true 	1
#define false 	0

#define ENDIAN_SWAP_16(x)		(((x) & 0xFF) << 8 | ((x) & 0xFF00) >> 8)
#define ENDIAN_SWAP_32(x)		(((x) & 0xFF) << 24 | ((x) & 0xFF00) << 8 | ((x) & 0xFF0000) >> 8 | ((x) & 0xFF000000) >> 24)
#define ENDIAN_SWAP(x)			(sizeof(x) == 2 ? ENDIAN_SWAP_16(x) : ENDIAN_SWAP_32(x))
//#define ENDIAN_SWAP(x) 			x

extern void print_load(char *format, ...);

typedef struct
{
	uint32_t magic; 
	uint32_t version; 
	  
	uint32_t OPcodeOffset; 
	uint32_t OPcodeLength;
	  
	uint32_t stringOffset; 
	uint32_t stringLength;
	uint32_t stringEntries;
	  
	uint32_t attrOffset;
	uint32_t attrLength; 
	uint32_t attrEntries;
	  
	uint32_t globOffset;
	uint32_t globLength;
	uint32_t globEntries;
} VSMXHeader;

typedef struct 
{
	uint8_t code;
	uint8_t arg;
	uint8_t unknown;
	uint8_t var;
	uint32_t val;
} OPcode;

enum
{
//	Assignment Operators ?
	NOP									=	0x00,
	ASSIGN								=	0x01,
//	Arithmetic Operators	
	ADD									=	0x02, 
	SUB									=	0x03, 
	MUL									=	0x04, 
	DIV									=	0x05, 
	MOD									=	0x06, 
	TO_NUMBER							=	0x07, 
	CSIGN								=	0x08, 
	NOT									=	0x09, 
	INC									=	0x0A, 
	DEC									=	0x0B, 
	POST_INC							=	0x0C, 
	POST_DEC							=	0x0D, 
//	Compare Operators
	CMPEQ								=	0x0E, 
	CMPNEQ								=	0x0F, 
	CMPSEQ								=	0x10, 
	CMPSNEQ								=	0x11, 
	CMPLT								=	0x12, 
	CMPLE								=	0x13, 
	CMPGE								=	0x14, 
	CMPGT								=	0x15, 
//	Bitwise Operators ?
	INSTANCEOF							=	0x16, 
	IN									=	0x17, 
	TYPEOF								=	0x18, 
	BIT_AND								=	0x19, 
	BIT_XOR								=	0x1A, 
	BIT_OR								=	0x1B, 
	BIT_NOT								=	0x1C, 
	LSHIFT								=	0x1D, 
	S_RSHIFT							=	0x1E, 
	U_RSHIFT							=	0x1F, 
//	?
	COPY								=	0x20, 
	SWAP								=	0x21, 
	REMOVE								=	0x22, 
//	Data Types
	PUSH_UNDEFINED						=	0x23, 
	PUSH_NULL							=	0x24, 
	PUSH_BOOL							=	0x25, 
	PUSH_INT							=	0x26, 
	PUSH_FLOAT							=	0x27, 
	PUSH_STRING							=	0x28, 
//	Complex Data Types
	PUSH_OBJECT							=	0x29, 
	PUSH_FUNC							=	0x2A, 
	PUSH_ARRAY							=	0x2B, 
	PUSH_THIS							=	0x2C, 
	PUSH_LOCAL							=	0x2D, 
	PUSH_GLOBAL							=	0x2E, 
//	Attributes related
	GETATTR								=	0x2F, 
	GETATTR_KEEPOBJ						=	0x30, 
	SETATTR								=	0x31, 
	DELATTR								=	0x32, 
	APPEND_ATTR							=	0x33, 
//	Items related
	GETITEM								=	0x34, 
	GETITEM_KEEPOBJ						=	0x35, 
	SETITEM								=	0x36, 
	DELITEM								=	0x37, 
	APPEND_ITEM							=	0x38, 
//	if/else/for (opcode jumps)
	JUMP								=	0x39, 
	JUMPT								=	0x3A, 
	JUMPF								=	0x3B, 
//	Code structure builders
	CALL_FUNC							=	0x3C, 
	CALL_METHOD							=	0x3D, 
	CALL_CONSTRUCTOR					=	0x3E, 
	RET									=	0x3F, 
	THROW								=	0x40, 
	TRYBLK_IN							=	0x41, 
	TRYBLK_OUT							=	0x42, 
	CATCH_FINALLYBLK_IN					=	0x43, 
	CATCH_FINALLYBLK_OUT				=	0x44, 
	HALT								=	0x45, 
//	Debug
	DEBUG_FILE							=	0x46, 
	DEBUG_LINE							=	0x47, 
//	VSMX v2 (new opcodes for PS3) ?
	GETITEM_KEEPOBJNAME					=	0x48, 
	PUSH_VECTOR							=	0x49, 
	GET_VECTOR_ELEMENT					=	0x4A, 
	GET_VECTOR_ELEMENT_KEEPVECTOR		=	0x4B, 
	ASSGN_VECTOR_ELEMENT				=	0x4C, 
	SETATTR_VECTOR_ELEMENT				=	0x4D, 
	SETITEM_VECTOR_ELEMENT				=	0x4E,
} CODE;

char *CODE_str[] = //to debug
{
//	Assignment Operators ?
	"NOP",									//	0x00
	"ASSIGN",								//	0x01
//	Arithmetic Operators	
	"ADD",									//	0x02
	"SUB",									//	0x03
	"MUL",									//	0x04
	"DIV",									//	0x05
	"MOD",									//	0x06
	"TO_NUMBER",							//	0x07
	"CSIGN",								//	0x08
	"NOT",									//	0x09
	"INC",									//	0x0A
	"DEC",									//	0x0B
	"POST_INC",								//	0x0C
	"POST_DEC",								//	0x0D
//	Compare Operators
	"CMPEQ",								//	0x0E
	"CMPNEQ",								//	0x0F
	"CMPSEQ",								//	0x10
	"CMPSNEQ",								//	0x11
	"CMPLT",								//	0x12
	"CMPLE",								//	0x13
	"CMPGE",								//	0x14
	"CMPGT",								//	0x15
//	Bitwise Operators ?
	"INSTANCEOF",							//	0x16
	"IN",									//	0x17
	"TYPEOF",								//	0x18
	"BIT_AND",								//	0x19
	"BIT_XOR",								//	0x1A
	"BIT_OR",								//	0x1B
	"BIT_NOT",								//	0x1C
	"LSHIFT",								//	0x1D
	"S_RSHIFT",								//	0x1E
	"U_RSHIFT",								//	0x1F
//	?
	"COPY",									//	0x20
	"SWAP",									//	0x21
	"REMOVE",								//	0x22
//	Data Types
	"PUSH_UNDEFINED",						//	0x23
	"PUSH_NULL",							//	0x24
	"PUSH_BOOL",							//	0x25
	"PUSH_INT",								//	0x26
	"PUSH_FLOAT",							//	0x27
	"PUSH_STRING",							//	0x28
//	Complex Data Types
	"PUSH_OBJECT",							//	0x29
	"PUSH_FUNC",							//	0x2A
	"PUSH_ARRAY",							//	0x2B
	"PUSH_THIS",							//	0x2C
	"PUSH_LOCAL",							//	0x2D
	"PUSH_GLOBAL",							//	0x2E
//	Attributes related
	"GETATTR",								//	0x2F
	"GETATTR_KEEPOBJ",						//	0x30
	"SETATTR",								//	0x31
	"DELATTR",								//	0x32
	"APPEND_ATTR",							//	0x33
//	Items related
	"GETITEM",								//	0x34
	"GETITEM_KEEPOBJ",						//	0x35
	"SETITEM",								//	0x36
	"DELITEM",								//	0x37
	"APPEND_ITEM",							//	0x38
//	if/else/for (opcode jumps)
	"JUMP",									//	0x39
	"JUMPT",								//	0x3A
	"JUMPF",								//	0x3B
//	Code structure builders
	"CALL_FUNC",							//	0x3C
	"CALL_METHOD",							//	0x3D
	"CALL_CONSTRUCTOR",						//	0x3E
	"RET",									//	0x3F
	"THROW",								//	0x40
	"TRYBLK_IN",							//	0x41
	"TRYBLK_OUT",							//	0x42
	"CATCH_FINALLYBLK_IN",					//	0x43
	"CATCH_FINALLYBLK_OUT",					//	0x44
	"HALT",									//	0x45
//	Debug
	"DEBUG_FILE",							//	0x46
	"DEBUG_LINE",							//	0x47
//	VSMX v2 (new opcodes for PS3) ?
	"GETITEM_KEEPOBJNAME",					//	0x48
	"PUSH_VECTOR",							//	0x49
	"GET_VECTOR_ELEMENT",					//	0x4A
	"GET_VECTOR_ELEMENT_KEEPVECTOR",		//	0x4B
	"ASSGN_VECTOR_ELEMENT",					//	0x4C
	"SETATTR_VECTOR_ELEMENT",				//	0x4D
	"SETITEM_VECTOR_ELEMENT"				//	0x4E
};

void es_VSMXHeader(VSMXHeader *h)
{
	h->magic = ENDIAN_SWAP(h->magic);
	h->version = ENDIAN_SWAP(h->version);
	
	h->OPcodeOffset = ENDIAN_SWAP(h->OPcodeOffset);
	h->OPcodeLength = ENDIAN_SWAP(h->OPcodeLength);
	  
	h->stringOffset	= ENDIAN_SWAP(h->stringOffset); 
	h->stringLength	= ENDIAN_SWAP(h->stringLength);
	h->stringEntries = ENDIAN_SWAP(h->stringEntries);
	  
	h->attrOffset = ENDIAN_SWAP(h->attrOffset);
	h->attrLength = ENDIAN_SWAP(h->attrLength); 
	h->attrEntries = ENDIAN_SWAP(h->attrEntries);
	  
	h->globOffset = ENDIAN_SWAP(h->globOffset);
	h->globLength = ENDIAN_SWAP(h->globLength);
	h->globEntries = ENDIAN_SWAP(h->globEntries);
}

float IEEE_754_to_float(uint32_t raw_value) {
	float f;
	memcpy(&f, &raw_value, sizeof(f));
	return f;
}

void JSX_to_JS(char *jsx_p, char *js_p)
{
	int i,j,k;
	

	FILE *fjsx = fopen(jsx_p, "rb");
	if (fjsx == NULL ) {print_load("Error : Failed to open JSX file"); return;}

	VSMXHeader header;
	
	fread(&header, sizeof(header), 1, fjsx);

	es_VSMXHeader(&header);
	
	if(header.magic != VSMX_MAGIC) {
		print_load("Error : bad magic %X", header.magic);
		fclose(fjsx);
		return;
	}
	if(header.version != VSMX_PS3) {
		print_load("Error : bad version");
		fclose(fjsx);
		return;
	}


	char string[header.stringEntries][128];
	char attr[header.attrEntries][128];
	char glob[header.globEntries][128];
	uint32_t OPcodeEntries = 0;
	OPcodeEntries = header.OPcodeLength/sizeof(OPcode);
	OPcode OPCODE[OPcodeEntries];

	uint16_t char_16;
	char char_8;
// *** OPcode Table *** 
	fseek(fjsx, header.OPcodeOffset, SEEK_SET);
	for(i=0; i<=OPcodeEntries; i++) {
		fread(&OPCODE[i], 8, 1, fjsx);
		OPCODE[i].val = ENDIAN_SWAP(OPCODE[i].val);
	}

// *** STRING Table *** 
	fseek(fjsx, header.stringOffset, SEEK_SET);
	
	for(i=0; i < header.stringEntries; i++) {
		fread(&char_16, sizeof(uint16_t), 1, fjsx);
		j=0;
		while(char_16 != 00) {
			string[i][j] = (char) ENDIAN_SWAP(char_16);
			j++;
			fread(&char_16, sizeof(uint16_t), 1, fjsx);
		}
		string[i][j]=0;
	}

// *** ATTR Table ***	
	fseek(fjsx, header.attrOffset, SEEK_SET);
	
	for(i=0; i < header.attrEntries; i++) {
		fread(&char_16, sizeof(uint16_t), 1, fjsx);
		j=0;
		while(char_16 != 0) {
			attr[i][j] = (char) ENDIAN_SWAP(char_16);
			j++;
			fread(&char_16, sizeof(uint16_t), 1, fjsx);
		}
		attr[i][j]=0;
	}

// *** GLOB table ***
	fseek(fjsx, header.globOffset, SEEK_SET);
	
	for(i=0; i < header.globEntries; i++) {
		fread(&char_8, sizeof(uint8_t), 1, fjsx);
		j=0;
		while(char_8 != 00) {
			glob[i][j] = char_8;
			j++;
			fread(&char_8, sizeof(uint8_t), 1, fjsx);
		}
		glob[i][j]=0;
	}
	fclose(fjsx);

// *** DECODE ***
	char *CODE[OPcodeEntries];
	uint8_t *ACTIVE = malloc(OPcodeEntries);
	uint8_t *DONE = malloc(OPcodeEntries);
	char tab[128];

	memset(CODE, 0, sizeof(CODE));
	memset(ACTIVE, 0, sizeof(ACTIVE));
	memset(DONE, 0, sizeof(DONE));
	memset(tab, 0, sizeof(tab));
	
	uint32_t for_flags[10][3] = {{0}};
	int	lvl_for=-1;
	uint32_t if_flags[10] = {0};
	int	lvl_if=-1;
	uint32_t func_flags[3] = {0};

	char GlobVar[255][255];
	uint8_t nGlobVar = 0;
	
	char *BUFFER = (char *) malloc(2048);
	
	for(i=0; i<OPcodeEntries; i++) {
		ACTIVE[i]=true;
		DONE[i]=false;
		
		
		memset(BUFFER, 0, sizeof(BUFFER));
		
		switch (OPCODE[i].code) {
			case NOP:
			
			break;
			case ASSIGN:
			{
				int func=false;
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if(OPCODE[j].code == 0x2A) func = true;
						if (num == 2) break;
					}
				}
				if(func==true) {
					sprintf(BUFFER, "%s%s %s()", tab, CODE[text[0]], CODE[text[1]]);
				} else {
					
					uint8_t exist = false;
					if(strstr(CODE[j], " ") == NULL && strstr(CODE[j], "(") == NULL
					&& strstr(CODE[j], "++") == NULL && strstr(CODE[j], "--") == NULL) 
					{ 
						for(j=0; j < nGlobVar; j++) {
							if(strcmp(CODE[text[1]], GlobVar[j]) == 0) exist = true;
						}
					} else exist = true;
					
					if(exist == true) {
						sprintf(BUFFER,"%s = %s", CODE[text[1]], CODE[text[0]]);
					}
					else  {
						sprintf(BUFFER,"var %s = %s", CODE[text[1]], CODE[text[0]]);
						sprintf(GlobVar[nGlobVar], CODE[text[1]]);
						nGlobVar++;
					}
				}
			}
			break;
			case ADD:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						num += 1;
						ACTIVE[j] = false;
						if (num == 2) break;
					}
				}
				sprintf(BUFFER, "%s + %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case SUB:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s - %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case MUL:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s * %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case DIV:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s / %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case MOD:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}
				sprintf(BUFFER, "%s %% %s", CODE[text[1]], CODE[text[0]]);
			}
			break;	
			case TO_NUMBER:
			
			break;
			case CSIGN:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						sprintf(BUFFER, "-%s", CODE[j]);
						ACTIVE[j] = false;
						break;
					}
				}
			}
			
			break;
			case NOT:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						sprintf(BUFFER, "!%s", CODE[j]);
						ACTIVE[j] = false;
						break;
					}
				}
			}
			
			break;
			case INC:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						ACTIVE[j] = false;
						sprintf(BUFFER, "++%s", CODE[j]);
						break;
					}
				}
			}
			
			break;
			case DEC:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						ACTIVE[j] = false;
						sprintf(BUFFER, "--%s", CODE[j]);
						break;
					}
				}
			}
			
			break;
			case POST_INC:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						ACTIVE[j] = false;
						sprintf(BUFFER, "%s++", CODE[j]);
						break;
					}
				}
			}
			
			break;
			case POST_DEC:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						ACTIVE[j] = false;
						sprintf(BUFFER, " %s--", CODE[j]);
						break;
					}
				}
			}
			
			break;
			case CMPEQ:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, " %s == %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case CMPNEQ:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, " %s != %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case CMPSEQ:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s === %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case CMPSNEQ:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s !== %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case CMPLT:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}
				sprintf(BUFFER, "%s < %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case CMPLE:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s <= %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case CMPGE:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s >= %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case CMPGT:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s > %s", CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case INSTANCEOF:
				break;

			case IN:
				break;

			case TYPEOF:
				break;

			case BIT_AND:
				break;

			case BIT_XOR:
				break;

			case BIT_OR:
				break;

			case BIT_NOT:
				break;

			case LSHIFT:
				break;

			case S_RSHIFT:
				break;

			case U_RSHIFT:
				break;

			case COPY: // "todo : it's "m = m + s", and it should be "m += s"
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						sprintf(BUFFER, "%s", CODE[j]);
						break;
					}
				}	
			
			break;
			case SWAP:
				break;

			case REMOVE:
			{	
				if(for_flags[lvl_for][0]==true){
					int num = 0;
					uint32_t text[3];
					for (j = i - 1; j >= 0; j--) {
						if (ACTIVE[j] || DONE[j]) {
							text[num]=j;
							ACTIVE[j]=false;
							DONE[j]=false;
							num += 1;
							if(num==3) break;
						}
					}
					sprintf(BUFFER, "%sfor(%s %s; %s)", tab, &CODE[text[2]][strlen(tab)], CODE[text[1]], CODE[text[0]]);
					for_flags[lvl_for][0]=false;
					DONE[i] = true;
					ACTIVE[i] = true;
					break;
				}
				
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						ACTIVE[j] = false;
						if(func_flags[0]==true) sprintf(BUFFER, "%s%s", tab, CODE[j]); 
						else
						if(strstr(CODE[j], " ") == NULL && strstr(CODE[j], "(") == NULL
						&& strstr(CODE[j], "++") == NULL && strstr(CODE[j], "--") == NULL) { 
							int exist=false;
							for(k=func_flags[2]; k<j; k++) {
								if(ACTIVE[k]){
									if(strstr(CODE[j], CODE[k]) != NULL) {exist=true; break;}
								}
							}
							if(exist==false) {
								sprintf(BUFFER, "%svar %s;", tab, CODE[j]);
								sprintf(GlobVar[nGlobVar], CODE[j]);
								nGlobVar++;
							}
							else sprintf(BUFFER, "%s%s;", tab, CODE[j]);
						}
						else sprintf(BUFFER, "%s%s;", tab, CODE[j]);
						break;
					}
				}
				
				while( ( if_flags[lvl_if] == i+1) || (if_flags[lvl_if] == i+2 && OPCODE[i+1].code == 0x39) ) 
				{
					if(if_flags[lvl_if] == i+1) {
						tab[strlen(tab)-1]=0;
						if_flags[lvl_if]=0;
						lvl_if--;
						strcat(BUFFER, "\n");
						strcat(BUFFER, tab);
						strcat(BUFFER, "}");
					} else
					if(if_flags[lvl_if] == i+2 && OPCODE[i+1].code == 0x39) {
						tab[strlen(tab)-1]=0;
						if_flags[lvl_if]=0;
						lvl_if--;
						strcat(BUFFER, "\n");
						strcat(BUFFER, tab);
						strcat(BUFFER, "}");
						strcat(BUFFER, " else {");
						strcat(tab, "\t");
						lvl_if++;
						if_flags[lvl_if]=OPCODE[i+1].val;
					}
				}
				
				DONE[i] = true;
				ACTIVE[i] = false;
			}
			
			break;
			case PUSH_UNDEFINED:
			{
				if(OPCODE[i-1].code==0x3F && OPCODE[i+1].code==0x3F) {
					for ( j = i - 1; j >= 0; j--) {
						if (ACTIVE[j]) {
							sprintf(BUFFER, "%sreturn %s;", tab, CODE[j]);
							ACTIVE[j]=false;
							DONE[j]=false;
							break;
						}
					}
					DONE[i]=true;
				} else {
					ACTIVE[i]=false;
					DONE[i]=false;
				}
				
			}
			
			break;
			case PUSH_NULL:
				strcpy(BUFFER, "null");
				
			break;
			case PUSH_BOOL:
			{
				if (OPCODE[i].val == 0)
					strcpy(BUFFER, "false");
				else
					strcpy(BUFFER, "true");
			}
			
			break;
			case PUSH_INT:
				sprintf(BUFFER, "%d", (int) OPCODE[i].val);
				
			break;
			case PUSH_FLOAT:
				sprintf(BUFFER, "%#.1f", IEEE_754_to_float(OPCODE[i].val));
				
			break;
			case PUSH_STRING:
				sprintf(BUFFER, "\"%s\"", string[OPCODE[i].val]);
				
			break;
			case PUSH_OBJECT:
				
			break;
			case PUSH_FUNC:
				strcpy(BUFFER, "function");
				if(OPCODE[i+1].code == JUMP) {
					strcat(BUFFER, "()");
					DONE[i]=true;
				}
				func_flags[0]=true;
				func_flags[2]=i;
				
			break;
			case PUSH_ARRAY:
				strcpy(BUFFER, "[]");
				
			break;
			case PUSH_THIS:
				break;

			case PUSH_LOCAL:
				sprintf(BUFFER, "localVar_%d", OPCODE[i].val);
				break;

			case PUSH_GLOBAL:
				sprintf(BUFFER, "%s", glob[OPCODE[i].val]);
				
				
			break;
			case GETATTR:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						sprintf(BUFFER, "%s.%s", CODE[j], attr[OPCODE[i].val]);
						ACTIVE[j] = false;
						break;
					}
				}
				ACTIVE[i] = true;
			}
			
			break;
			case GETATTR_KEEPOBJ:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						sprintf(BUFFER, "%s.%s", CODE[j], attr[OPCODE[i].val]);
						ACTIVE[j]=false;
						break;
					}
				}
			}
			
			break;
			case SETATTR:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s.%s = %s", CODE[text[1]], attr[OPCODE[i].val], CODE[text[0]]);
			}
			break;
			
			case DELATTR:
				break;

			case APPEND_ATTR:
				break;

			case GETITEM:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s[%s]", CODE[text[1]], CODE[text[0]]);
			}
			break;

			case GETITEM_KEEPOBJ:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						num += 1;
						if (num == 2) break;
					}
				}

				sprintf(BUFFER, "%s[%s]", CODE[text[1]], CODE[text[0]]);
				break;
			}
			case SETITEM:
			{
				int num = 0;
				uint32_t text[3];
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[num]=j;
						ACTIVE[j] = false;
						num += 1;
						if(num == 3) break;
					}
				}

				sprintf(BUFFER, "%s[%s] = %s",  CODE[text[2]], CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case DELITEM:
				break;

			case APPEND_ITEM:
			{
				char element[255];
				strcpy(element, CODE[i-1]);
				ACTIVE[i-1] = false;
				
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j] && OPCODE[j].code == 43) {
						char openArray[255];
						memcpy(&openArray, BUFFER, strlen(BUFFER)-1);
						if (openArray[strlen(openArray)-1] == '[') {
							strcat(openArray, ", ");
						}
						strcat(openArray, element);
						strcat(openArray, "]");
						
						strcpy(BUFFER, openArray);
						break;
					}
				}

				ACTIVE[i] = false;
			}
			
			break;
			case JUMP:
			{
				if(for_flags[lvl_for][0] == true) {
					ACTIVE[i] = false;
					DONE[i] = false;
				} else
				if(for_flags[lvl_for][1] == i) {
					sprintf(BUFFER, "%s{", tab);
					strcat(tab, "\t");
					ACTIVE[i] = false;
					DONE[i] = true;
				} else 
				if(for_flags[lvl_for][2] == i) {
					tab[strlen(tab)-1]=0;
					sprintf(BUFFER, "%s}", tab);
					ACTIVE[i] = false;
					DONE[i] = true;
					for_flags[lvl_for][1]=0;
					for_flags[lvl_for][2]=0;
					lvl_for--;
				} else
				if(func_flags[0]==true) {
					sprintf(BUFFER, "%s{", tab);
					strcat(tab, "\t");
					func_flags[0]=false;
					func_flags[1]=OPCODE[i].val;
					ACTIVE[i] = false;
					DONE[i] = true;
				} else
				if(if_flags[lvl_if]!=0) {
					ACTIVE[i] = false;
					DONE[i] = false;
				} else {
					sprintf(BUFFER, "GoTo 0x%X",  OPCODE[i].val);
					ACTIVE[i] = false;
					DONE[i] = true;
				}
			}
			
			break;
			case JUMPT:
			{
				if(OPCODE[i+1].code == 0x39) { // loop for
					lvl_for++;
					for_flags[lvl_for][0]=true;
					for_flags[lvl_for][1]=OPCODE[i].val-1;
					for_flags[lvl_for][2]=OPCODE[i+1].val-1;
					ACTIVE[i]=false;
					DONE[i]=false;
				} else {
					for (j = i - 1; j >= 0; j--) {
						if (ACTIVE[j]) {
							if( CODE[j][0] == '(' && CODE[j][strlen(CODE[j])-1] == ')' ) {
								sprintf(BUFFER, "if(!%s)\n{", CODE[j]);
							} else {
								sprintf(BUFFER, "if(!(%s))\n{", CODE[j]);
							}
							ACTIVE[j] = false;
							break;
						}
					}
					DONE[i]=true;
				}
			}
			
			break;
			case JUMPF:
			{
				for ( j = i - 1; j >= 0; j--) {
					
					if (ACTIVE[j]) {
						if( CODE[j][0] == '(' && CODE[j][strlen(CODE[j])-1] == ')' )
							sprintf(BUFFER, "%sif%s\n%s{", tab, CODE[j], tab); 
						else
							sprintf(BUFFER, "%sif(%s)\n%s{", tab, CODE[j], tab);
						
						lvl_if++;
						strcat(tab, "\t");
						if_flags[lvl_if]=OPCODE[i].val;
						break;
					}
				}
				DONE[i]=true;
				
			}
			
			break;
			case CALL_FUNC:
			{
				uint32_t text[OPCODE[i].val + 1];
				k=OPCODE[i].val;
				
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[k] = j;
						ACTIVE[j] = false;
						k--;
						if (k == -1) break;
					}
				}

				switch (OPCODE[i].val) {
					case 0:
					{
						sprintf(BUFFER, "%s()", CODE[text[0]]);
					}	
					break;
					case 1:
					{
						sprintf(BUFFER, "%s(%s)", CODE[text[0]], CODE[text[1]]);
					}
					break;
					default:
					{
						sprintf(BUFFER, "%s(%s)", CODE[text[0]], CODE[text[1]]);
						for(k=2; k<=OPCODE[i].val; k++) {
							strcat(BUFFER, ", ");
							strcat(BUFFER, CODE[text[k]]);
						}
						strcat(BUFFER, ")");
					}
					break;
				}
				
			}
			break;
			case CALL_METHOD:
			{
				uint32_t text[OPCODE[i].val + 1];
				k=OPCODE[i].val;
				
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[k] = j;
						ACTIVE[j] = false;
						k--;
						if (k == -1) break;
					}
				}

				switch (OPCODE[i].val) {
					case 0:
					{
						sprintf(BUFFER, "%s()", CODE[text[0]]);
					}	
					break;
					case 1:
					{
						sprintf(BUFFER, "%s(%s)", CODE[text[0]], CODE[text[1]]);
					}
					break;
					default:
					{
						sprintf(BUFFER, "%s(%s", CODE[text[0]],  CODE[text[1]]);
						for(k=2; k<=OPCODE[i].val; k++) {
							strcat(BUFFER, ", ");
							strcat(BUFFER, CODE[text[k]]);
						}
						strcat(BUFFER, ")");
					}
					break;
				}
			}
			break;
			case CALL_CONSTRUCTOR:
			{
				uint32_t text[OPCODE[i].val + 1];
				k=OPCODE[i].val;
				
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[k] = j;
						ACTIVE[j] = false;
						DONE[j]=false;
						k--;
						if (k == -1) break;
					}
				}
				
				for(k=0; k<=OPCODE[i].val; k++) {
					if(strstr(CODE[text[k]], "function()") != NULL) {
						
						memset(BUFFER, 0, sizeof(BUFFER));
						
						char *split;
						
						split = strtok (CODE[text[k]],"\n");
						while (split != NULL)
						{
							strcat(BUFFER, "\n\t");
							strcat(BUFFER, split);
							split = strtok (NULL, "\n");
						}
						strcat(BUFFER, "\n");
						
						strcpy(CODE[text[k]], BUFFER);
					}
				}
				
				memset(BUFFER, 0, sizeof(BUFFER));
				
				switch (OPCODE[i].val) {
					case 0:
					{
						sprintf(BUFFER, "%s()", CODE[text[0]]);
					}	
					break;
					case 1:
					{
						sprintf(BUFFER, "%s(%s)", CODE[text[0]], CODE[text[1]]);
					}
					break;
					default:
					{
						sprintf(BUFFER, "%s(%s", CODE[text[0]],  CODE[text[1]]);
						for(k=2; k<=OPCODE[i].val; k++) {
							strcat(BUFFER, ", ");
							strcat(BUFFER, CODE[text[k]]);
						}
						strcat(BUFFER, ")");
					}
					break;
				}
			}
			break;
			case RET:
			{
				if(func_flags[1]==i+1) {
					//function can be an item in an array so I join it in 1 item : CODE[i]
					
					for(j=func_flags[2]; j<=i; j++){
						if(DONE[j]) {
							strcat(BUFFER, CODE[j]);
							strcat(BUFFER, "\n");
						}
						DONE[j]=0;
						ACTIVE[j]=0;
					}
					tab[strlen(tab)-1]=0;
					strcat(BUFFER, tab);
					strcat(BUFFER, "}");
					func_flags[0]=false;
					func_flags[1]=0;
					func_flags[2]=0;
					ACTIVE[i]=true;
					DONE[i]=true;
				} else if(OPCODE[i-1].code==0x23 && OPCODE[i-2].code!=0x3F) {
					strcpy(BUFFER, tab);
					strcat(BUFFER, "return;");
					ACTIVE[i]=true;
					DONE[i]=true;
				} else {
					ACTIVE[i]=false;
					DONE[i]=false;
				}
				
				while( ( if_flags[lvl_if] == i+1) || (if_flags[lvl_if] == i+2 && OPCODE[i+1].code == 0x39) ) 
				{
					if(if_flags[lvl_if] == i+1) {
						tab[strlen(tab)-1]=0;
						if_flags[lvl_if]=0;
						lvl_if--;
						strcat(BUFFER, "\n");
						strcat(BUFFER, tab);
						strcat(BUFFER, "}");
						DONE[i] = true;
						ACTIVE[i] = false;
					} else
					if(if_flags[lvl_if] == i+2 && OPCODE[i+1].code == 0x39) {
						tab[strlen(tab)-1]=0;
						if_flags[lvl_if]=0;
						lvl_if--;
						strcat(BUFFER, "\n");
						strcat(BUFFER, tab);
						strcat(BUFFER, "}");
						strcat(BUFFER, " else {");
						strcat(tab, "\t");
						lvl_if++;
						if_flags[lvl_if]=OPCODE[i+1].val;
						DONE[i] = true;
						ACTIVE[i] = false;
					}
				}	
			}
			break;
			case THROW:
				break;

			case TRYBLK_IN:
			{
				strcpy(BUFFER, "try {");
				DONE[i] = true;
			}
			
			break;
			case TRYBLK_OUT:
				strcpy(BUFFER, "}");
				DONE[i] = true;
				
			break;
			case CATCH_FINALLYBLK_IN:
				strcpy(BUFFER, "catch(exception) {");
				DONE[i] = true;
				
			break;
			case CATCH_FINALLYBLK_OUT:
				strcpy(BUFFER, "}");
				DONE[i] = true;
				
			break;
			case HALT:
				strcpy(BUFFER, "\n\n/* Decompiled by ManaGunZ */");
				DONE[i] = true;
				
			break;
			case DEBUG_FILE:
				break;

			case DEBUG_LINE:
				break;

			case GETITEM_KEEPOBJNAME:
				break;

			case PUSH_VECTOR:
			{
				k = 0;
				uint32_t text[OPCODE[i].val];
				strcpy(BUFFER, "<");
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						text[k]=j;
						k++;
						ACTIVE[j] = false;
						if(k >= OPCODE[i].val) break;
					}
				}
				
				for(k=OPCODE[i].val-1; k>=0; k--) {
					strcat(BUFFER, CODE[text[k]]);
					if(k==0) break;
					strcat(BUFFER, ", ");
				}
				strcat(BUFFER, ">");
			}
			
			break;
			case GET_VECTOR_ELEMENT:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						sprintf(BUFFER, "%s->element_%d", CODE[j], OPCODE[i].arg);
						if(OPCODE[j].code == GETATTR_KEEPOBJ) strcpy(CODE[j], BUFFER);
						else ACTIVE[j] = false;
						break;
					}
				}
			}
			
			break;
			case GET_VECTOR_ELEMENT_KEEPVECTOR:
			{
				for (j = i - 1; j >= 0; j--) {
					if (ACTIVE[j]) {
						sprintf(BUFFER, "%s->element_%d", CODE[j], OPCODE[i].arg);
						break;
					}
				}
			}
			
			break;
			case ASSGN_VECTOR_ELEMENT:
				break;

			case SETATTR_VECTOR_ELEMENT:
			{
				int num = 0;
				uint32_t text[2];
				for (j = i - 1; j >= 0; j--) {
					if(ACTIVE[j]) {
						text[num]=j;
						ACTIVE[num] = false;
						num++;
						if (num == OPCODE[i].var) break;
					}
				}
				
				sprintf(BUFFER, "%s = %s" , CODE[text[1]], CODE[text[0]]);
			}
			
			break;
			case SETITEM_VECTOR_ELEMENT:
			{
				int num = 0;
				uint32_t text[2]={0};
				for (j = i - 1; j >= 0; j--) {
					text[num]=j;
					ACTIVE[num] = false;
					num++;
					if (num == 2) break;
				}

				sprintf(BUFFER, "%s.%s->%d = %s" , CODE[text[1]], attr[OPCODE[i].val], OPCODE[i].var, CODE[text[0]]);
			}
			break;
			
		}
		
		if(BUFFER[0] != 0) {
			CODE[i] = (char *) malloc( strlen(BUFFER)+1 );
			memset(CODE[i], 0, sizeof(CODE[i]));
			
			strcpy(CODE[i], BUFFER);
			
			CODE[i][strlen(CODE[i])] = 0;
		}
		
	}
	
	free(BUFFER);

	FILE *fjs = fopen(js_p, "wb");
	if (fjs != NULL ) {
		for(i=0; i<OPcodeEntries;i++) {
			if(DONE[i]) {
				fputs(CODE[i], fjs);
				fputs("\n", fjs);
			}
			
		}
		fclose(fjs);
	} else print_load("Error : Failed to create JS file");

	for(i=0; i<OPcodeEntries;i++) free(CODE[i]);
	free(DONE);
	free(ACTIVE);
	
}