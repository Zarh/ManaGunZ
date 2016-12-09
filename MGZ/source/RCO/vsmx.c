#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include "general.h"
#include "vsmx.h"

#include <ppu-types.h>

#ifndef wcscasecmp
#include <wctype.h>
int wcscasecmp(const wchar_t *s1, const wchar_t *s2) {
	while(*s1 && *s2) {
		int diff = towlower(*s1) - towlower(*s2);
		if(diff)
			return diff;
		s1++;
		s2++;
	}
	return towlower(*s1) - towlower(*s2);
}
#endif
// following doesn't seem to work - probably the define is required in the project
/* #ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // get rid of MSVC's annoying security stuff
#define _CRT_NON_CONFORMING_SWPRINTFS // urgh... seems that mingw uses bad swprintf >_>
#endif */


// since swprintf seems to accept different arguments...
#if defined(MINGW) || defined(__MINGW32__)
#define SWPRINTF(s, l, f, ...) swprintf(s, f, __VA_ARGS__)
#else
#define SWPRINTF(s, l, f, ...) swprintf(s, l, f, __VA_ARGS__)
#endif


enum {
	VID_NOP = 0x0, // dummy
	VID_OPERATOR_ASSIGN = 0x1,
	VID_OPERATOR_ADD = 0x2,
	VID_OPERATOR_SUBTRACT = 0x3,
	VID_OPERATOR_MULTIPLY = 0x4,
	VID_OPERATOR_DIVIDE = 0x5,
	VID_OPERATOR_MOD = 0x6,
	VID_OPERATOR_POSITIVE = 0x7,
	VID_OPERATOR_NEGATE = 0x8,
	VID_OPERATOR_NOT = 0x9,
	VID_P_INCREMENT = 0xa,
	VID_P_DECREMENT = 0xb,
	VID_INCREMENT = 0xc,
	VID_DECREMENT = 0xd,
	VID_OPERATOR_EQUAL = 0xe,
	VID_OPERATOR_NOT_EQUAL = 0xf,
	VID_OPERATOR_IDENTITY = 0x10, // === operator; used in case labels
	VID_OPERATOR_NON_IDENTITY = 0x11,
	VID_OPERATOR_LT = 0x12,
	VID_OPERATOR_LTE = 0x13,
	VID_OPERATOR_GTE = 0x14,
	VID_OPERATOR_GT = 0x15,
	VID_OPERATOR_INSTANCEOF = 0x16,
	VID_OPERATOR_IN = 0x17,
	VID_OPERATOR_TYPEOF = 0x18,
	VID_OPERATOR_B_AND = 0x19,
	VID_OPERATOR_B_XOR = 0x1a,
	VID_OPERATOR_B_OR = 0x1b,
	VID_OPERATOR_B_NOT = 0x1c,
	VID_OPERATOR_LSHIFT = 0x1d,
	VID_OPERATOR_RSHIFT = 0x1e,
	VID_OPERATOR_URSHIFT = 0x1f,
	VID_STACK_PUSH = 0x20,
	// VID_SWAP = 0x21,
	VID_END_STMT = 0x22,
	VID_CONST_NULL = 0x23, // undefined
	VID_CONST_EMPTYARRAY = 0x24, // null
	VID_CONST_BOOL = 0x25,
	VID_CONST_INT = 0x26,
	VID_CONST_FLOAT = 0x27,
	VID_CONST_STRING = 0x28,
	VID_CONST_OBJECT = 0x29,
	VID_FUNCTION = 0x2a,
	VID_ARRAY = 0x2b, // start an array constant
	VID_THIS = 0x2c,
	VID_UNNAMED_VAR = 0x2d,
	VID_VARIABLE = 0x2e,
	VID_PROPERTY = 0x2f,
	VID_METHOD = 0x30,
	VID_UNK_31 = 0x31, // appears to be an object set; pops last two items off the stack; Sony's ASM = "SETATTR"
	VID_UNSET = 0x32, // guess; looks like above, but only with one item
	VID_OBJ_ADD_ATTR = 0x33,
	VID_ARRAY_INDEX = 0x34,
	// GETITEM_KEEPOBJ = 0x35,
	VID_ARRAY_INDEX_ASSIGN = 0x36,
	// DELITEM = 0x37,
	VID_ARRAY_ELEM = 0x38, // push something into array constant
	VID_SECT_START = 0x39, // jump statement; can indicate end of function, end of else/for, or return to beginning of loop
	VID_JUMP_TRUE = 0x3a, // jump if previous value is true
	VID_JUMP_FALSE = 0x3b,
	VID_CALL_FUNC = 0x3c,
	VID_CALL_METHOD = 0x3d,
	VID_CALL_NEW = 0x3e,
	VID_RETURN = 0x3f,
	VID_THROW = 0x40,
	VID_TRY_START = 0x41,
	VID_TRY_END = 0x42,
	VID_TRY_CATCH_START = 0x43,
	VID_TRY_CATCH_END = 0x44,
	VID_END = 0x45,
	VID_DEBUG_FILE = 0x46,
	VID_DEBUG_LINE = 0x47,
	// GETITEM_KEEPOBJNAME = 0x48,
	VID_CONST_VECTOR = 0x49
	// GET_VECTOR_ELEMENT
	// GET_VECTOR_ELEMENT_KEEPVECTOR
	// ASSGN_VECTOR_ELEMENT
	// SETATTR_VECTOR_ELEMENT
	// SETITEM_VECTOR_ELEMENT
};

const wchar VsmxDecOps[][50] = {
	L"NOP",
	L"ASSIGN",
	L"ADD",
	L"SUBTRACT",
	L"MULTIPLY",
	L"DIVIDE",
	L"MODULUS",
	L"POSITIVE",
	L"NEGATE",
	L"NOT",
	L"PRE_INCREMENT",
	L"PRE_DECREMENT",
	L"INCREMENT",
	L"DECREMENT",
	L"TEST_EQUAL",
	L"TEST_NOT_EQUAL",
	L"TEST_IDENTITY",
	L"TEST_NON_IDENTITY",
	L"TEST_LESS_THAN",
	L"TEST_LESS_EQUAL_THAN",
	L"TEST_MORE_EQUAL_THAN",
	L"TEST_MORE_THAN",
	L"INSTANCEOF",
	L"IN",
	L"TYPEOF",
	L"BINARY_AND",
	L"BINARY_XOR",
	L"BINARY_OR",
	L"BINARY_NOT",
	L"LSHIFT",
	L"RSHIFT",
	L"UNSIGNED_RSHIFT",
	L"STACK_PUSH",
	L"UNKNOWN_21",
	L"END_STATEMENT",
	L"CONST_NULL",
	L"CONST_EMPTY_ARRAY",
	L"CONST_BOOL",
	L"CONST_INT",
	L"CONST_FLOAT",
	L"CONST_STRING",
	L"CONST_OBJECT",
	L"FUNCTION",
	L"CONST_ARRAY",
	L"THIS_OBJECT",
	L"UNNAMED_VARIABLE",
	L"NAME",
	L"PROPERTY",
	L"METHOD",
	L"SET",
	L"UNSET",
	L"OBJECT_ADD_ATTRIBUTE",
	L"ARRAY_INDEX",
	L"UNKNOWN_35",
	L"ARRAY_INDEX_ASSIGN",
	L"UNKNOWN_37",
	L"ARRAY_PUSH",
	L"JUMP",
	L"JUMP_IF_TRUE",
	L"JUMP_IF_FALSE",
	L"CALL_FUNCTION",
	L"CALL_METHOD",
	L"CALL_NEW",
	L"RETURN",
	L"UNKNOWN_40",
	L"UNKNOWN_41",
	L"UNKNOWN_42",
	L"UNKNOWN_43",
	L"UNKNOWN_44",
	L"END_SCRIPT",
	L"DEBUG_FILE",
	L"DEBUG_LINE",
	L"UNKNOWN_48",
	L"MAKE_VECTOR"
};
const unsigned int VSMX_NUM_DEC_OPS = 0x49+1;

static inline wchar_t* strwcpy(wchar_t* dest, const char* src, unsigned int maxLen) {
	while(--maxLen && (*dest = (wchar_t)(*src))) {
		dest++;
		src++;
	}
	*dest = 0; // ensure last char is null
	return dest;
}

// similar to wcscat, except it puts the s2 before s1, rather than after
static inline wchar_t * wcsprecat (wchar_t * dest, const wchar_t *src, unsigned int maxLen) {
  	unsigned int len = wcslen(src);
	unsigned int destLen;
	if(len >= maxLen) {
		wmemcpy(dest, src, maxLen);
		dest[maxLen-1] = L'\0';
		return dest;
	}
	// unfortunately, wcscpy can't have overlapping ranges
	destLen = wcslen(dest);
	if(len + destLen >= maxLen)
		destLen = maxLen - len;
	*(dest + len + destLen) = L'\0';
	while(destLen--) {
		*(dest + len + destLen) = *(dest + destLen);
	}
	// wcscpy(dest + len, dest);
	wmemcpy(dest, src, len);
	return dest;
}

VsmxMem* readVSMX(FILE* fp) {
	
	VSMXHeader header;
	uint filePos;
	VsmxMem* out;
	int i;
	
	u32 *mem = (u32 *) malloc(sizeof(header));
	fileread(fp, mem, sizeof(header));
	for(i=0; i<sizeof(header)/sizeof(u32); i++) {
       mem[i] = ENDIAN_SWAP_32(mem[i]);
    }
	memcpy(&header, mem, sizeof(header));
	free(mem);
	
	if(header.sig != VSMX_SIGNATURE || (header.ver != VSMX_VERSION && header.ver != JSX_VERSION)) {
		error("Not a valid VSMX file.");
		return NULL;
	}
	
	if(header.codeOffset != sizeof(header)) {
		warning("Skipping range 0x%x-0x%x", sizeof(header), header.codeOffset);
		return NULL;
		fseek(fp, header.codeOffset, SEEK_SET);
	}
	
	if(header.codeLength % sizeof(VSMXGroup)) {
		error("Code size not aligned to 8 bytes.");
		return NULL;
	}
	out = (VsmxMem*)malloc(sizeof(VsmxMem));
	
	// TODO: check lengths are in sane ranges
	out->code = (VSMXGroup*)malloc(header.codeLength);
	fileread(fp, out->code, header.codeLength);
	out->codeGroups = header.codeLength / sizeof(VSMXGroup);
	
	filePos = header.codeOffset + header.codeLength;
	
	#define READ_TEXT_SECTION(to, tl, te, typ, var, pVar, nam) \
		if(tl || te) { \
			if(to != filePos) { \
				warning("Skipping range 0x%x-0x%x", filePos, to); \
				fseek(fp, to, SEEK_SET); \
			} \
			if(!tl) { \
				error("Number of " nam " entries > 1 but length of data is 0!"); \
				free(out); \
				return NULL; \
			} \
			if(!te) { \
				error("Number of " nam " entries = 0 but length of data is > 0!"); \
				free(out); \
				return NULL; \
			} \
			if(tl % sizeof(typ)) { \
				error("Size of " nam " not aligned to %d byte(s).", sizeof(typ)); \
				free(out); \
				return NULL; \
			} \
			 \
			var = (typ *)malloc(tl); \
			fileread(fp, var, tl); \
			pVar = (typ **)malloc(te * 128); \
			int i;\
			int k=0;\
			int j=0;\
			char temp[128]; \
			for(i=0; i<te; i++) { \
				memset(temp, 0, 128); \
				while(k < tl) { \
					if(sizeof(typ) == 1) { \
						if(var[k] != 0) temp[j]= var[k]; else break; \
					} \
					else if(sizeof(typ)== 2) { \
						if(var[k] != 0) temp[j] = (char) ENDIAN_SWAP_16(var[k]); else break;\
					} \
					else if(sizeof(typ)== 4) { \
						u32 val = ENDIAN_SWAP_HALF32(var[k]); \
						u16 val1 = (u16)(val >> 16); \
						u16 val2 = (u16)(val & 0xffff); \
						if(val1!=0) temp[j] = (char) val1; else break; \
						j++; \
						if(val2!=0) temp[j] = (char) val2; else break; \
					} else break; \
					k++; j++; \
				} \
				warning("%s", temp); \
				memcpy(pVar[i], temp, sizeof(temp)); \
				warning("%s", pVar[i]); \
			}\
			filePos += tl; \
			error("i %X k %X tl : %X", i, k, tl);\
		}
	
	READ_TEXT_SECTION(header.textOffset, header.textLength, header.textEntries, wchar, out->text, out->pText, "text");
	READ_TEXT_SECTION(header.propOffset, header.propLength, header.propEntries, wchar, out->prop, out->pProp, "properties");
	READ_TEXT_SECTION(header.namesOffset, header.namesLength, header.namesEntries, char, out->names, out->pNames, "names");
	
	out->numText = header.textEntries;
	out->lenText = header.textLength;
	out->numProp = header.propEntries;
	out->lenProp = header.propLength;
	out->numNames = header.namesEntries;
	out->lenNames = header.namesLength;
	
	fclose(fp);
	
	return out;
}

// urgh, this is a bit of a duplicate of the above
// TODO: don't make this so crap
VsmxMem* readVSMXMem(const void *in) {
	
	VSMXHeader* header = (VSMXHeader*)in;
	uint filePos;
	VsmxMem* out;
	
	if(header->sig != VSMX_SIGNATURE || header->ver != VSMX_VERSION) {
		error("Not a valid VSMX file.");
		return NULL;
	}
	
	if(header->codeOffset != sizeof(VSMXHeader)) {
		warning("Skipping range 0x%x-0x%x", sizeof(VSMXHeader), header->codeOffset);
		//fseek(fp, header->codeOffset, SEEK_SET);
	}
	
	if(header->codeLength % sizeof(VSMXGroup)) {
		error("Code size not aligned to 8 bytes.");
		return NULL;
	}
	out = (VsmxMem*)malloc(sizeof(VsmxMem));
	
	// TODO: check lengths are in sane ranges
	out->code = (VSMXGroup*)malloc(header->codeLength);
	memcpy(out->code, (uint8_t*)in + header->codeOffset, header->codeLength);
	out->codeGroups = header->codeLength / sizeof(VSMXGroup);
	
	filePos = header->codeOffset + header->codeLength;
	
	#define READ_TEXT_SECTION_MEM(to, tl, te, typ, var, pVar, nam) \
		if(tl || te) { \
			if(to != filePos) { \
				warning("Skipping range 0x%x-0x%x", filePos, to); \
				filePos = to; \
			} \
			if(!tl) { \
				error("Number of " nam " entries > 1 but length of data is 0!"); \
				free(out); \
				return NULL; \
			} \
			if(!te) { \
				error("Number of " nam " entries = 0 but length of data is > 0!"); \
				free(out); \
				return NULL; \
			} \
			if(tl % sizeof(typ)) { \
				error("Size of " nam " not aligned to %d byte(s).", sizeof(typ)); \
				free(out); \
				return NULL; \
			} \
			 \
			var = (typ *)malloc(tl +sizeof(typ)); \
			memcpy(var, (uint8_t*)in + filePos, tl); \
			var[tl / sizeof(typ)] = 0; \
			 \
			pVar = (typ **)malloc(te * sizeof(typ *)); \
			pVar[0] = var; \
			 \
			uint pti = 1, ci; \
			for(ci = 1; ci < tl / sizeof(typ); ci++) { \
				if(var[ci-1] == 0) { \
					if(pti == te) { \
						error("Number of " nam " entries found exceeds number specified in header!"); \
						free(out); \
						return NULL; \
					} \
					pVar[pti++] = var + ci; \
				} \
			} \
			if(pti != te) { \
				error("Number of " nam " entries found is less than number specified in header!"); \
				free(out); \
				return NULL; \
			} \
			 \
			filePos += tl; \
		}
	
	READ_TEXT_SECTION_MEM(header->textOffset, header->textLength, header->textEntries, wchar, out->text, out->pText, "text");
	READ_TEXT_SECTION_MEM(header->propOffset, header->propLength, header->propEntries, wchar, out->prop, out->pProp, "properties");
	READ_TEXT_SECTION_MEM(header->namesOffset, header->namesLength, header->namesEntries, char, out->names, out->pNames, "names");
	
	out->numText = header->textEntries;
	out->lenText = header->textLength;
	out->numProp = header->propEntries;
	out->lenProp = header->propLength;
	out->numNames = header->namesEntries;
	out->lenNames = header->namesLength;
	
	return out;
}

void writeVSMX(FILE* fp, VsmxMem* in) {
	VSMXHeader header;
	unsigned int pos = 0x34;
	header.sig = VSMX_SIGNATURE;
	header.ver = VSMX_VERSION;
	header.codeOffset = pos;
	header.codeLength = in->codeGroups * sizeof(VSMXGroup);
	pos += header.codeLength;
	header.textOffset = pos;
	header.textLength = in->lenText;
	header.textEntries = in->numText;
	pos += header.textLength;
	header.propOffset = pos;
	header.propLength = in->lenProp;
	header.propEntries = in->numProp;
	pos += header.propLength;
	header.namesOffset = pos;
	header.namesLength = in->lenNames;
	header.namesEntries = in->numNames;
	
	fwrite(&header, sizeof(header), 1, fp);
	
	if(in->code)
		fwrite(in->code, header.codeLength, 1, fp);
	if(in->text)
		fwrite(in->text, header.textLength, 1, fp);
	if(in->prop)
		fwrite(in->prop, header.propLength, 1, fp);
	if(in->names)
		fwrite(in->names, header.namesLength, 1, fp);
}
// like the read thing above, this sucks
void* writeVSMXMem(unsigned int* len, VsmxMem* in) {
	*len = sizeof(VSMXHeader) + in->codeGroups * sizeof(VSMXGroup) + in->lenText + in->lenProp + in->lenNames;
	void* ret = malloc(*len);
	
	VSMXHeader* header = (VSMXHeader*)ret;
	unsigned int pos = sizeof(VSMXHeader);
	header->sig = VSMX_SIGNATURE;
	header->ver = VSMX_VERSION;
	header->codeOffset = pos;
	header->codeLength = in->codeGroups * sizeof(VSMXGroup);
	pos += header->codeLength;
	header->textOffset = pos;
	header->textLength = in->lenText;
	header->textEntries = in->numText;
	pos += header->textLength;
	header->propOffset = pos;
	header->propLength = in->lenProp;
	header->propEntries = in->numProp;
	pos += header->propLength;
	header->namesOffset = pos;
	header->namesLength = in->lenNames;
	header->namesEntries = in->numNames;
	
	pos = sizeof(VSMXHeader);
	if(in->code) {
		memcpy((uint8_t*)ret + pos, in->code, header->codeLength);
		pos += header->codeLength;
	}
	if(in->text) {
		memcpy((uint8_t*)ret + pos, in->text, header->textLength);
		pos += header->textLength;
	}
	if(in->prop) {
		memcpy((uint8_t*)ret + pos, in->prop, header->propLength);
		pos += header->propLength;
	}
	if(in->names) {
		memcpy((uint8_t*)ret + pos, in->names, header->namesLength);
		pos += header->namesLength;
	}
	return ret;
}

// macro used in both decode and decompile functions
#define CHECK_INDEX(num,nam) \
	if(in->code[i].val.u32 >= num) { \
		error("Invalid " nam " index 0x%x at group %d!", in->code[i].val.u32, i); \
		return 1; \
	}

int VsmxDecode(VsmxMem* in, FILE* out) {
	uint i;
	
	fputws(L"; Decoded VSMX file written by " APPNAME_VER "\n\n", out);
	
	for(i=0; i < in->codeGroups; i++) {
		if((in->code[i].id & 0xFF) <= VSMX_NUM_DEC_OPS) {
			fputws(VsmxDecOps[in->code[i].id & 0xFF], out);
			//fputwc(L' ', out);
		} else
			fwprintf(out, L"UNKNOWN_%x", in->code[i].id);
		
		switch(in->code[i].id & 0xFF) {
			
			case VID_CONST_BOOL:
				if(in->code[i].val.u32 == 1)
					fputws(L" true", out);
				else if(in->code[i].val.u32 == 0)
					fputws(L" false", out);
				else {
					warning("Unexpected boolean value 0x%x at line %d!", in->code[i].val.u32, i+1);
					fwprintf(out, L" 0x%x", in->code[i].val.u32);
				}
			break;
			case VID_CONST_INT:
			case VID_DEBUG_LINE:
				fwprintf(out, L" %u", in->code[i].val.u32);
			break;
			case VID_CONST_FLOAT:
				fwprintf(out, L" %#g", in->code[i].val.f);
			break;
			case VID_CONST_STRING:
			case VID_DEBUG_FILE:
				CHECK_INDEX(in->numText, "text");
				fwprintf(out, L" \"%ls\"", in->pText[in->code[i].val.u32]);
			break;
			case VID_VARIABLE: {
				// for some reason, the %s modifier in fwprintf doesn't work properly... :/ so we need to convert to a wide char string
				wchar *tmp;
				uint tmpLen = strlen(in->pNames[in->code[i].val.u32]);
				CHECK_INDEX(in->numNames, "name");
				tmp = (wchar*)malloc((tmpLen+1) * sizeof(wchar));
				strwcpy(tmp, in->pNames[in->code[i].val.u32], tmpLen+1);
				fwprintf(out, L" %ls", tmp);
				free(tmp);
			} break;
			case VID_PROPERTY:
			case VID_METHOD:
			case VID_UNK_31:
			case VID_UNSET:
			case VID_OBJ_ADD_ATTR:
				CHECK_INDEX(in->numProp, "property");
				fwprintf(out, L" %ls", in->pProp[in->code[i].val.u32]);
			break;
			case VID_FUNCTION:
				if(in->code[i].id >> 16 & 0xFF)
					warning("Unexpected localvars value for function at line %d, expected 0, got %d", i+1, in->code[i].id >> 16 & 0xFF);
				fwprintf(out, L" args=%u, localvars=%u, start_line=%u", (in->code[i].id >> 8) & 0xFF, (in->code[i].id >> 24) & 0xFF, in->code[i].val.u32+1);
			break;
			case VID_UNNAMED_VAR:
				fwprintf(out, L" %u", in->code[i].val.u32);
			break;
			
			// jumps
			case VID_SECT_START:
			case VID_JUMP_TRUE:
			case VID_JUMP_FALSE:
				fwprintf(out, L" line=%u", in->code[i].val.u32+1);
			break;
			
			// function calls
			case VID_CALL_FUNC:
			case VID_CALL_METHOD:
			case VID_CALL_NEW:
				fwprintf(out, L" args=%u", in->code[i].val.u32);
			break;
			
			case VID_CONST_VECTOR:
				fwprintf(out, L" items=%u", in->code[i].val.u32);
				break;
			
			// ops w/o arg - check for zero
			case VID_OPERATOR_ASSIGN:
			case VID_OPERATOR_ADD:
			case VID_OPERATOR_SUBTRACT:
			case VID_OPERATOR_MULTIPLY:
			case VID_OPERATOR_DIVIDE:
			case VID_OPERATOR_MOD:
			case VID_OPERATOR_POSITIVE:
			case VID_OPERATOR_NEGATE:
			case VID_OPERATOR_NOT:
			case VID_P_INCREMENT:
			case VID_P_DECREMENT:
			case VID_INCREMENT:
			case VID_DECREMENT:
			case VID_OPERATOR_TYPEOF:
			case VID_OPERATOR_EQUAL:
			case VID_OPERATOR_NOT_EQUAL:
			case VID_OPERATOR_IDENTITY:
			case VID_OPERATOR_NON_IDENTITY:
			case VID_OPERATOR_LT:
			case VID_OPERATOR_LTE:
			case VID_OPERATOR_GT:
			case VID_OPERATOR_GTE:
			case VID_OPERATOR_INSTANCEOF:
			case VID_OPERATOR_IN:
			case VID_OPERATOR_B_AND:
			case VID_OPERATOR_B_XOR:
			case VID_OPERATOR_B_OR:
			case VID_OPERATOR_B_NOT:
			case VID_OPERATOR_LSHIFT:
			case VID_OPERATOR_RSHIFT:
			case VID_OPERATOR_URSHIFT:
			case VID_STACK_PUSH:
			case VID_END_STMT:
			case VID_CONST_NULL:
			case VID_CONST_EMPTYARRAY:
			case VID_CONST_OBJECT:
			case VID_ARRAY:
			case VID_THIS:
			case VID_ARRAY_INDEX:
			case VID_ARRAY_INDEX_ASSIGN:
			case VID_ARRAY_ELEM:
			case VID_RETURN:
			case VID_END:
				if(in->code[i].val.u32)
					warning("Unexpected non-zero value at line %d!", i+1);
				
			break;
			
			default:
				warning("Unknown ID 0x%x at line %d", in->code[i].id, i+1);
				fwprintf(out, L" 0x%x", in->code[i].val.u32);
		}
		fputwc(L'\n', out);
	}
	return 0;
}

// !! doesn't properly fix up pText !!
unsigned int VsmxAddText(void** text, unsigned int** offs, unsigned int* textLen, unsigned int* numText, wchar* newText, int charWidth) {
	// first, see if we already have this text
	unsigned int p = 0;
	unsigned int len = wcslen(newText);
	
	char* newTextByte = NULL;
	//wprintf(L"adding text %ls\n", newText);
	//fflush(stdout);
	if(charWidth == 1) { // convert wchar to char
		char *ptr = (char*)malloc(len +1);
		newTextByte = ptr;
		if(!ptr) {
			error("malloc failed");
			exit(1);
		}
		while((*ptr = (char)(*newText))) {
			ptr++;
			newText++;
		}
	}
	
	for(p=0; p < *numText; p++) {
		uint8_t cond;
		if(charWidth == 1) {
			cond = strcmp(*(char**)text + (*offs)[p], newTextByte);
		}
		else
			cond = wcscmp(*(wchar**)text + (*offs)[p] / charWidth, newText);
		if(!cond) {
			if(newTextByte) free(newTextByte);
			return p; // found
		}
	}
	
	// don't have it? add it
	(*numText)++;
	*text = realloc(*text, *textLen + (len+1)*charWidth);
	*offs = (unsigned int*)realloc(*offs, sizeof(unsigned int) * (*numText));
	if(charWidth == 1) {
		strcpy(*(char**)text + *textLen, newTextByte);
	} else {
		wcscpy(*(wchar**)text + *textLen / charWidth, newText);
	}
	(*offs)[*numText -1] = *textLen;
	*textLen += (len+1)*charWidth;
	
	if(newTextByte) free(newTextByte);
	return *numText-1;
}


VsmxMem* VsmxEncode(FILE* in) {
	wchar buf[2048];
	unsigned int lineCount = 1;
	VsmxMem* ret = (VsmxMem*)malloc(sizeof(VsmxMem));
	unsigned int *oText = NULL, *oProp = NULL, *oNames = NULL;
	
	ret->codeGroups = ret->numText = ret->numProp = ret->numNames = ret->lenText = ret->lenProp = ret->lenNames = 0;
	ret->code = NULL;
	ret->text = NULL;
	ret->prop = NULL;
	ret->names = NULL;
	ret->pText = NULL;
	ret->pProp = NULL;
	ret->pNames = NULL;
	
	while(fgetws(buf, 2048, in)) {
		wchar *op = buf, *arg = NULL, *tmp;
		int opNum = -1;
		unsigned int opNum2, argNum = 0;
		unsigned int lineLen;
		// trim line
		#define IS_WHITESPACE(x) (x == L'\t' || x == L' ' || x == L'\n' || x == L'\r')
		while(*op && IS_WHITESPACE(*op))
			op++;
		/* code is BAD - can remove stuff if in a string!
		// don't forget to remove comments!
		tmp = op;
		while(*tmp) {
			if(*tmp == L';') {
				*tmp = L'\0';
				break;
			}
			tmp++;
		}
		*/
		lineLen = wcslen(op);
		while(lineLen && IS_WHITESPACE(op[lineLen-1]))
			lineLen--;
		op[lineLen] = L'\0';
		
		if(lineLen == 0) continue;
		if(op[0] == L';') continue; // comment line
		
		// find space, if any
		tmp = op;
		while(*(++tmp))
			if(*tmp == L' ') {
				arg = tmp+1;
				*tmp = L'\0';
				while(*arg && *arg == L' ')
					arg++;
				break;
			}
		
		// determine op
		if(swscanf(op, L"UNKNOWN_%x", &opNum) != 1) {
			unsigned int i;
			for(i=0; i<VSMX_NUM_DEC_OPS; i++)
				if(!wcscasecmp(op, VsmxDecOps[i])) {
					opNum = i;
					break;
				}
		}
		if(opNum == -1) {
			error("Invalid operation specified at line %d.", lineCount);
			return NULL;
		}
		
		opNum2 = opNum;
		// parse args
		// TODO: check if arg is true for places that require it
		switch(opNum) {
			case VID_CONST_BOOL:
				if(!wcscasecmp(arg, L"true"))
					argNum = 1;
				else if(!wcscasecmp(arg, L"false"))
					argNum = 0;
				else
					swscanf(arg, L"%i", &argNum);
			break;
			case VID_CONST_INT:
			case VID_UNNAMED_VAR:
			case VID_DEBUG_LINE:
				swscanf(arg, L"%u", &argNum);
			break;
			case VID_CONST_FLOAT:
				swscanf(arg, L"%f", &argNum);
			break;
			
			
			case VID_CONST_STRING:
			case VID_DEBUG_FILE: {
				if(arg[0] != '"' || arg[wcslen(arg)-1] != '"') {
					warning("[line %d] Bad string style.", lineCount);
				} else {
					arg++;
					arg[wcslen(arg)-1] = '\0';
					argNum = VsmxAddText((void**)&ret->text, &oText, &ret->lenText, &ret->numText, arg, sizeof(*(ret->text)));
				}
			} break;
			case VID_VARIABLE:
				argNum = VsmxAddText((void**)&ret->names, &oNames, &ret->lenNames, &ret->numNames, arg, sizeof(*(ret->names)));
			break;
			case VID_PROPERTY:
			case VID_METHOD:
			case VID_UNK_31:
			case VID_UNSET:
			case VID_OBJ_ADD_ATTR:
				argNum = VsmxAddText((void**)&ret->prop, &oProp, &ret->lenProp, &ret->numProp, arg, sizeof(*(ret->prop)));
			break;
			
			case VID_FUNCTION: {
				int iArgs, iFlag;
				// TODO: better parser here
				swscanf(arg, L"args=%u, localvars=%u, start_line=%u", &iArgs, &iFlag, &argNum);
				argNum--;
				opNum2 = ((iFlag & 0xFF) << 24) | ((iArgs & 0xFF) << 8) | opNum2;
			} break;
			case VID_SECT_START:
			case VID_JUMP_TRUE:
			case VID_JUMP_FALSE:
				swscanf(arg, L"line=%u", &argNum);
				argNum--;
			break;
			case VID_CALL_FUNC:
			case VID_CALL_METHOD:
			case VID_CALL_NEW:
				swscanf(arg, L"args=%u", &argNum);
			break;
			
			case VID_CONST_VECTOR:
				swscanf(arg, L"items=%u", &argNum);
			break;
			
			// ops w/o arg - check for zero
			case VID_OPERATOR_ASSIGN:
			case VID_OPERATOR_ADD:
			case VID_OPERATOR_SUBTRACT:
			case VID_OPERATOR_MULTIPLY:
			case VID_OPERATOR_DIVIDE:
			case VID_OPERATOR_MOD:
			case VID_OPERATOR_POSITIVE:
			case VID_OPERATOR_NEGATE:
			case VID_OPERATOR_NOT:
			case VID_P_INCREMENT:
			case VID_P_DECREMENT:
			case VID_INCREMENT:
			case VID_DECREMENT:
			case VID_OPERATOR_TYPEOF:
			case VID_OPERATOR_EQUAL:
			case VID_OPERATOR_NOT_EQUAL:
			case VID_OPERATOR_IDENTITY:
			case VID_OPERATOR_NON_IDENTITY:
			case VID_OPERATOR_LT:
			case VID_OPERATOR_LTE:
			case VID_OPERATOR_GT:
			case VID_OPERATOR_GTE:
			case VID_OPERATOR_INSTANCEOF:
			case VID_OPERATOR_IN:
			case VID_OPERATOR_B_AND:
			case VID_OPERATOR_B_XOR:
			case VID_OPERATOR_B_OR:
			case VID_OPERATOR_B_NOT:
			case VID_OPERATOR_LSHIFT:
			case VID_OPERATOR_RSHIFT:
			case VID_OPERATOR_URSHIFT:
			case VID_STACK_PUSH:
			case VID_END_STMT:
			case VID_CONST_NULL:
			case VID_CONST_EMPTYARRAY:
			case VID_CONST_OBJECT:
			case VID_ARRAY:
			case VID_THIS:
			case VID_ARRAY_INDEX:
			case VID_ARRAY_INDEX_ASSIGN:
			case VID_ARRAY_ELEM:
			case VID_RETURN:
			case VID_END:
				if(arg) warning("[line %d] Operator does not have value.", lineCount);
			break;
			
			default:
				swscanf(arg, L"%i", &argNum);
		}
		
		ret->codeGroups++;
		ret->code = (VSMXGroup*)realloc(ret->code, ret->codeGroups * sizeof(VSMXGroup));
		ret->code[ret->codeGroups-1].id = opNum2;
		ret->code[ret->codeGroups-1].val.u32 = argNum;
		
		lineCount++;
	}
	
	if(oText) {
		unsigned int i;
		ret->pText = (wchar**)malloc(ret->numText * sizeof(wchar*));
		for(i=0; i<ret->numText; i++)
			ret->pText[i] = ret->text + oText[i];
		free(oText);
	}
	if(oProp) {
		unsigned int i;
		ret->pProp = (wchar**)malloc(ret->numProp * sizeof(wchar*));
		for(i=0; i<ret->numProp; i++)
			ret->pProp[i] = ret->prop + oProp[i];
		free(oProp);
	}
	if(oNames) {
		unsigned int i;
		ret->pNames = (char**)malloc(ret->numNames * sizeof(char*));
		for(i=0; i<ret->numNames; i++)
			ret->pNames[i] = ret->names + oNames[i];
		free(oNames);
	}
	
	return ret;
}

#define MAX_TEXT_LEN 4096
typedef struct __VsmxDecompileStack VsmxDecompileStack;

struct __VsmxDecompileStack {
	wchar str[MAX_TEXT_LEN]; // a bit of RAM wastage perhaps
	VSMXGroup item;
	int arrayFlag;
	int objectFlag;
	
	VsmxDecompileStack* prev;
	uint depth;
};

static inline void VsmxDecompileStackPush(VsmxDecompileStack** stack, VsmxDecompileStack* item) {
	VsmxDecompileStack* newItem = (VsmxDecompileStack*)malloc(sizeof(VsmxDecompileStack));
	*newItem = *item;
	newItem->prev = *stack;
	if(*stack) newItem->depth = (*stack)->depth + 1;
	else newItem->depth = 0;
	*stack = newItem;
}
static inline VsmxDecompileStack* VsmxDecompileStackPop(VsmxDecompileStack** stack) {
	if(!(*stack)) {
		error("Stack underflow occurred!");
		return NULL;
	}
	VsmxDecompileStack* theItem = *stack;
	*stack = (*stack)->prev;
	return theItem;
}
static inline void VsmxDecompileStackDestroy(VsmxDecompileStack** stack) {
	if(!*stack) return;
	while(*stack) {
		VsmxDecompileStack* tmp = (*stack)->prev;
		free(*stack);
		*stack = tmp;
	}
}

typedef struct __VsmxDecompMarkStack VsmxDecompMarkStack;

struct __VsmxDecompMarkStack {
	uint loc;
	uint src;

	VsmxDecompMarkStack* prev;
	uint depth;
};

static inline void VsmxDecompMarkStackPush(VsmxDecompMarkStack** stack, VsmxDecompMarkStack* item) {
	VsmxDecompMarkStack* newItem = (VsmxDecompMarkStack*)malloc(sizeof(VsmxDecompMarkStack));
	*newItem = *item;
	newItem->prev = *stack;
	if(*stack) {
		newItem->depth = (*stack)->depth + 1;
		if(newItem->loc > (*stack)->loc) {
			warning("Bad nesting hierachy detected!");
			// well, what to do?  Just switch them around I guess...
			uint tmp = newItem->loc;
			newItem->loc = (*stack)->loc;
			(*stack)->loc = tmp;
		}
	}
	else newItem->depth = 0;
	*stack = newItem;
}
static inline VsmxDecompMarkStack* VsmxDecompMarkStackPop(VsmxDecompMarkStack** stack) {
	if(!(*stack)) {
		error("Marker stack underflow occurred!");
		return NULL;
	}
	VsmxDecompMarkStack* theItem = *stack;
	*stack = (*stack)->prev;
	return theItem;
}
static inline void VsmxDecompMarkStackDestroy(VsmxDecompMarkStack** stack) {
	if(!*stack) return;
	while(*stack) {
		VsmxDecompMarkStack* tmp = (*stack)->prev;
		free(*stack);
		*stack = tmp;
	}
}

static inline void writeTabs(FILE* out, uint num) {
	while(num--)
		fputwc('\t', out);
}

int VsmxDecompile(VsmxMem* in, FILE* out) {
	uint i, indent=0, stmtStart=0;
	int indentAdd=0;
	VsmxDecompileStack* stack = NULL;
	VsmxDecompileStack item;
	VsmxDecompMarkStack* mStack = NULL;
	VsmxDecompMarkStack mItem;
	uint endStmtConcat = 1;
	
	//uint forStmtEnd = 0;
	
	
	fputws(L"// Decompiled VSMX -> Javascript output by " APPNAME_VER "\n//Note, this is highly experimental and the output probably sucks.\n\n", out);
	
	for(i=0; i < in->codeGroups; i++) {
		item.str[0] = 0;
		item.arrayFlag = 0;
		item.objectFlag = 0;
		
		item.item.id = 0;
		item.item.val.u32 = 0;
		
		// TODO: check that in->code[i].val is 0 for various things
		
		
		if(in->code[i].id >> 8 && (in->code[i].id & 0xFF) != VID_FUNCTION) {
			warning("Unexpected flags 0x%x for id 0x%x at %d", in->code[i].id >> 8, in->code[i].id & 0xFF, i);
		}
		
		
		// check for markers
		while(mStack && mStack->loc == i) {
			if(stack) {
				// inline marker
				
				// TODO: should we really concatenate here?
				while(endStmtConcat--) {
					VsmxDecompileStack *prev;
					prev = VsmxDecompileStackPop(&stack);
					wcscat(prev->str, item.str);
					wcscpy(item.str, prev->str);
					free(prev);
				}
				endStmtConcat = 1;
				
				if(in->code[mStack->src].id == VID_JUMP_FALSE) {
					// check for special and operation
					if(in->code[i].id == VID_JUMP_FALSE) {
						// this upcomming if acts as an AND - we'll display this as a nested if though
						mStack->loc = in->code[i].val.u32;
						// duplicate this marker as a copy will get popped later
						VsmxDecompMarkStackPush(&mStack, mStack);
						wcscat(item.str, L" /* AND condition shown as nested if */ ");
					} else { // inline if which doesn't have an else
						wcscat(item.str, L" : false )");
					}
				}
				else
					wcscat(item.str, L" )");
				VsmxDecompileStackPush(&stack, &item);
				item.str[0] = 0;
			} else {
				if(indent > 0) indent--; // this should always be true
				else warning("Internal state nesting error!");
				
				// TODO: remove debugging line
				fwprintf(out, L"/*%d*/\t", stmtStart);
				
				writeTabs(out, indent);
				fwprintf(out, L"}\n");
			}
			
			VsmxDecompMarkStackPop(&mStack);
		}
		
		
		// stuff we'll use later
		wchar op[50] = {0};
		uint8_t notSectStart = FALSE;
		/* #ifdef MINGW
		#define SWPRINTF_ITEM(s, ...) swprintf(item.str, L##s, __VA_ARGS__)
		#else
		#define SWPRINTF_ITEM(s, ...) swprintf(item.str, MAX_TEXT_LEN, L##s, __VA_ARGS__)
		#endif */
		#define SWPRINTF_ITEM(s, ...) SWPRINTF(item.str, MAX_TEXT_LEN, L##s, __VA_ARGS__)
		//#define SWPRINTF_ITEM(s, ...) swprintf(item.str, MAX_TEXT_LEN, L s, __VA_ARGS__)
		
		switch(in->code[i].id & 0xFF) {
			
			// binary operators
			case VID_OPERATOR_ASSIGN:		if(!op[0]) wcscpy(op, L"=");
			case VID_OPERATOR_ADD:			if(!op[0]) wcscpy(op, L"+");
			case VID_OPERATOR_SUBTRACT:		if(!op[0]) wcscpy(op, L"-");
			case VID_OPERATOR_MULTIPLY:		if(!op[0]) wcscpy(op, L"*");
			case VID_OPERATOR_DIVIDE:		if(!op[0]) wcscpy(op, L"/");
			case VID_OPERATOR_MOD:			if(!op[0]) wcscpy(op, L"%");
			case VID_OPERATOR_EQUAL:		if(!op[0]) wcscpy(op, L"==");
			case VID_OPERATOR_NOT_EQUAL:	if(!op[0]) wcscpy(op, L"!=");
			case VID_OPERATOR_IDENTITY:		if(!op[0]) wcscpy(op, L"===");
			case VID_OPERATOR_NON_IDENTITY:	if(!op[0]) wcscpy(op, L"!==");
			case VID_OPERATOR_LT:			if(!op[0]) wcscpy(op, L"<");
			case VID_OPERATOR_LTE:			if(!op[0]) wcscpy(op, L"<=");
			case VID_OPERATOR_GT:			if(!op[0]) wcscpy(op, L">");
			case VID_OPERATOR_GTE:			if(!op[0]) wcscpy(op, L">=");
			case VID_OPERATOR_INSTANCEOF:	if(!op[0]) wcscpy(op, L"instanceof");
			case VID_OPERATOR_IN:			if(!op[0]) wcscpy(op, L"in");
			case VID_OPERATOR_B_AND:		if(!op[0]) wcscpy(op, L"&");
			case VID_OPERATOR_B_XOR:		if(!op[0]) wcscpy(op, L"^");
			case VID_OPERATOR_B_OR:			if(!op[0]) wcscpy(op, L"|");
			case VID_OPERATOR_LSHIFT:		if(!op[0]) wcscpy(op, L"<<");
			case VID_OPERATOR_RSHIFT:		if(!op[0]) wcscpy(op, L">>");
			case VID_OPERATOR_URSHIFT:		if(!op[0]) wcscpy(op, L">>>");
			{ // TODO: need to consider when to use brackets
				VsmxDecompileStack *left, *right;
				right = VsmxDecompileStackPop(&stack);
				left = VsmxDecompileStackPop(&stack);
				SWPRINTF_ITEM("%ls %ls %ls", left->str, op, right->str);
				//swprintf(item.str, MAX_TEXT_LEN, L"%s %s %s", left->str, op, right->str);
				VsmxDecompileStackPush(&stack, &item);
				free(left); free(right);
			} break;
			
			
			case VID_OPERATOR_POSITIVE:		if(!op[0]) wcscpy(op, L"+");
			case VID_OPERATOR_NEGATE:		if(!op[0]) wcscpy(op, L"-");
			case VID_OPERATOR_NOT:			if(!op[0]) wcscpy(op, L"!");
			case VID_OPERATOR_B_NOT:			if(!op[0]) wcscpy(op, L"~");
			case VID_OPERATOR_TYPEOF:			if(!op[0]) wcscpy(op, L"typeof ");
			{
				VsmxDecompileStack *prev;
				prev = VsmxDecompileStackPop(&stack);
				//swprintf(item.str, MAX_TEXT_LEN, L"-(%s)", prev->str);
				SWPRINTF_ITEM("%ls(%ls)", op, prev->str);
				VsmxDecompileStackPush(&stack, &item);
				free(prev);
			} break;
			
			case VID_P_INCREMENT:
			case VID_INCREMENT:		if(!op[0]) wcscpy(op, L"++");
			case VID_P_DECREMENT:
			case VID_DECREMENT:		if(!op[0]) wcscpy(op, L"--");
			{
				VsmxDecompileStack *prev;
				prev = VsmxDecompileStackPop(&stack);
				//swprintf(item.str, MAX_TEXT_LEN, L"-(%s)", prev->str);
				if((in->code[i].id & 0xFF) == VID_P_INCREMENT || (in->code[i].id & 0xFF) == VID_P_DECREMENT)
					SWPRINTF_ITEM ("%ls(%ls)", op, prev->str);
				else
					SWPRINTF_ITEM ("(%ls)%ls", prev->str, op);
				VsmxDecompileStackPush(&stack, &item);
				free(prev);
			} break;
			
			
			// constants & variables
			case VID_CONST_NULL:
				wcscpy(item.str, L"null");
				VsmxDecompileStackPush(&stack, &item);
			break;
			case VID_CONST_EMPTYARRAY:
				wcscpy(item.str, L"[]");
				VsmxDecompileStackPush(&stack, &item);
			break;
			
			//case VID_CONST_TIME: break; // TODO:
			case VID_CONST_BOOL:
				if(in->code[i].val.u32 == 0)
					wcscpy(item.str, L"false");
				else {
					wcscpy(item.str, L"true");
					if(in->code[i].val.u32 != 1)
						warning("Boolean value at group #%d is not 0 or 1.", i);
				}
				VsmxDecompileStackPush(&stack, &item);
			break;
			
			case VID_CONST_INT:
				//swprintf(item.str, MAX_TEXT_LEN, L"%u", in->code[i].val.u32);
				SWPRINTF_ITEM("%u", in->code[i].val.u32);
				VsmxDecompileStackPush(&stack, &item);
			break;
			case VID_CONST_FLOAT:
				//swprintf(item.str, MAX_TEXT_LEN, L"%f", *(float*)(&in->code[i].val.u32));
				SWPRINTF_ITEM("%#g", in->code[i].val.f);
				VsmxDecompileStackPush(&stack, &item);
			break;
			case VID_CONST_STRING: { // TODO: unicode issues... :(
				CHECK_INDEX(in->numText, "text");
				//swprintf(item.str, MAX_TEXT_LEN, L"\"%s\"", in->pText[in->code[i].val.u32]);
				SWPRINTF_ITEM("\"%ls\"", in->pText[in->code[i].val.u32]);
				VsmxDecompileStackPush(&stack, &item);
			} break;
			case VID_THIS: {
				wcscpy(item.str, L"this");
				VsmxDecompileStackPush(&stack, &item);
			} break;
			case VID_UNNAMED_VAR:
				//swprintf(item.str, MAX_TEXT_LEN, L"__GLOBALS__[%u]", in->code[i].val.u32);
				SWPRINTF_ITEM("__var%u", in->code[i].val.u32);
				VsmxDecompileStackPush(&stack, &item);
			break;
			case VID_VARIABLE:
				CHECK_INDEX(in->numNames, "name");
				strwcpy(item.str, in->pNames[in->code[i].val.u32], MAX_TEXT_LEN);
				VsmxDecompileStackPush(&stack, &item);
			break;
			
			case VID_UNK_31:
				CHECK_INDEX(in->numProp, "prop");
				if(stack && stack->depth >= 1) { // TODO: this is really not correct
					VsmxDecompileStack *obj, *val;
					val = VsmxDecompileStackPop(&stack);
					obj = VsmxDecompileStackPop(&stack);
					SWPRINTF_ITEM("%ls.%ls = %ls", obj->str, in->pProp[in->code[i].val.u32], val->str);
					free(obj);
					free(val);
				} else
					wcscpy(item.str, in->pProp[in->code[i].val.u32]);
				VsmxDecompileStackPush(&stack, &item);
			break;
			
			case VID_PROPERTY:
			case VID_METHOD:
			case VID_UNSET:
			{
				VsmxDecompileStack *prev;
				prev = VsmxDecompileStackPop(&stack);
				CHECK_INDEX(in->numProp, "property/method");
				//swprintf(item.str, MAX_TEXT_LEN, L"%s.%s", prev->str, in->pProp[in->code[i].val.u32]);
				if(in->code[i].id == VID_UNSET)
					SWPRINTF_ITEM("delete %ls.%ls", prev->str, in->pProp[in->code[i].val.u32]);
				else
					SWPRINTF_ITEM("%ls.%ls", prev->str, in->pProp[in->code[i].val.u32]);
				VsmxDecompileStackPush(&stack, &item);
				free(prev);
			} break;
			
			
			case VID_CONST_VECTOR:
			{
				VsmxDecompileStack *prev;
				uint j;
				
				for(j=0; j<in->code[i].val.u32; j++) {
					prev = VsmxDecompileStackPop(&stack);
					if(j) {
						wchar_t tmp[MAX_TEXT_LEN];
						swprintf(tmp, MAX_TEXT_LEN, L" %ls,", prev->str);
						wcsprecat(item.str, tmp, MAX_TEXT_LEN);
						// SWPRINTF_ITEM (" %ls,%ls", prev->str, item.str);
					} else
						SWPRINTF_ITEM(" %ls ", prev->str);
					free(prev);
				}
				wcscat(item.str, L">");
				wcsprecat(item.str, L"<", MAX_TEXT_LEN);
				// SWPRINTF_ITEM("<%ls>", item.str);
				VsmxDecompileStackPush(&stack, &item);
			} break;
			
			case VID_CONST_OBJECT:
				wcscpy(item.str, L"{}");
				item.objectFlag = 1;
				VsmxDecompileStackPush(&stack, &item);
			break;
			case VID_OBJ_ADD_ATTR:
			{
				VsmxDecompileStack *obj, *prev;
				
				CHECK_INDEX(in->numProp, "prop");
				
				prev = VsmxDecompileStackPop (&stack);
				obj = VsmxDecompileStackPop (&stack);
				if (obj->objectFlag == 0) {
					warning ("Object elem being pushed, but object not found at %d!", i);
				} else if (obj->objectFlag == 1) {	// first element
					SWPRINTF_ITEM ("{ %ls: %ls }", in->pProp[in->code[i].val.u32], prev->str);
					item.objectFlag = 2;
					VsmxDecompileStackPush (&stack, &item);
				} else {
					uint32_t aLen = wcslen (obj->str);
					
					if (aLen < 3) {
						error ("Internal object handling error at %d!", i);
						return 1;
					}
					obj->str[aLen - 2] = L'\0';
					SWPRINTF_ITEM ("%ls, %ls: %ls }", obj->str, in->pProp[in->code[i].val.u32], prev->str);
					item.objectFlag = 2;
					VsmxDecompileStackPush (&stack, &item);
				}
				free (prev);
				free (obj);
			} break;
			
			case VID_ARRAY:
				wcscpy(item.str, L"[]");
				item.arrayFlag = 1;
				VsmxDecompileStackPush(&stack, &item);
			break;
			case VID_ARRAY_ELEM: {
				VsmxDecompileStack *array, *prev;
				prev = VsmxDecompileStackPop(&stack);
				array = VsmxDecompileStackPop(&stack);
				if(array->arrayFlag == 0) {
					warning("Array elem being pushed, but array not found at %d!", i);
				} else if(array->arrayFlag == 1) { // first element
					SWPRINTF_ITEM("[ %ls ]", prev->str);
					item.arrayFlag = 2;
					VsmxDecompileStackPush(&stack, &item);
				} else {
					uint aLen = wcslen(array->str);
					if(aLen < 3) {
						error("Internal array handling error at %d!", i);
						return 1;
					}
					array->str[aLen - 2] = L'\0';
					SWPRINTF_ITEM("%ls, %ls ]", array->str, prev->str);
					item.arrayFlag = 2;
					VsmxDecompileStackPush(&stack, &item);
				}
				free(prev);
				free(array);
			} break;
			
			case VID_STACK_PUSH: {
				// we only consider two possible uses for this
				// 1. push for conditional - we'll ignore these
				// 2. push for -= and += operators
				
				// !!! look ahead used!
				if(i+1 < in->codeGroups && (in->code[i+1].id == VID_JUMP_FALSE || in->code[i+1].id == VID_JUMP_TRUE)) {
					// 1st condition (hoping there isn't a more complex situation) - ignore
				} else {
					// 2nd, duplicate top of stack
					VsmxDecompileStackPush(&stack, stack);
				}
			} break;
			
			
			case VID_FUNCTION: {
				// TODO: need to check marker stack for look aheads
				// !!! note look ahead used!
				uint8_t funcEndStmtStyle = (i+3 < in->codeGroups && in->code[i+2].id == VID_END_STMT && in->code[i+3].id == VID_SECT_START && in->code[i].val.u32 == i+4);
				
				wchar args[4096] = L""; // large enough for anything
				uint numArgs = (in->code[i].id >> 8) & 0xFF, argI;
				
				if(in->code[i].id >> 16 & 0xFF) {
					warning("Unexpected flag value for function at %d, expected 0, got %d", i, in->code[i].id >> 16 & 0xFF);
				}
				SWPRINTF(args, 4096, L"/*localvars=%d*/", in->code[i].id >> 24);
				if(numArgs) wcscat(args, L" ");
				
				for(argI = 0; argI < numArgs; argI++) {
					if(argI) wcscat(args, L", ");
					SWPRINTF(args + wcslen(args), 4096-wcslen(args), L"__var%d", argI+1);
				}
				
				if(i+2 < in->codeGroups && in->code[i+1].id == VID_OPERATOR_ASSIGN && (
					funcEndStmtStyle || 
					(in->code[i+2].id == VID_SECT_START && in->code[i].val.u32 == i+3)
				)) {
					// abc = function() style?
					
					if(in->code[i+1].val.u32 || (funcEndStmtStyle && in->code[i+2].val.u32)) {
						warning("Unexpected values in function definition style at %d", i);
					}
					
					if(!stack) {
						warning("Function encountered at %d, but no name found on stack!", i);
						SWPRINTF_ITEM("function __unnamed_%d__(%ls)", i, args);
						VsmxDecompileStackPush(&stack, &item);
					} else if(stack->depth == 0) {
						VsmxDecompileStack *prev;
						prev = VsmxDecompileStackPop(&stack);
						//SWPRINTF_ITEM("function %ls(%ls)", prev->str, args);
						SWPRINTF_ITEM("%ls = function(%ls)", prev->str, args);
						VsmxDecompileStackPush(&stack, &item);
						free(prev);
					} else if(stack->depth == 1) { // weird...
						VsmxDecompileStack *prev, *var;
						prev = VsmxDecompileStackPop(&stack);
						var = VsmxDecompileStackPop(&stack);
						SWPRINTF_ITEM("%ls = function %ls(%ls)", var->str, prev->str, args);
						VsmxDecompileStackPush(&stack, &item);
						free(prev); free(var);
					} else { // weird...
						warning("Function encountered at %d, but more than one item found on stack!", i);
						VsmxDecompileStack *prev;
						prev = VsmxDecompileStackPop(&stack);
						SWPRINTF_ITEM("%ls = function(%ls)", prev->str, args);
						VsmxDecompileStackPush(&stack, &item);
						free(prev);
					}
					if(funcEndStmtStyle)
						i += 2;
					else
						i++;
				} else if(i+1 < in->codeGroups && in->code[i+1].id == VID_SECT_START && in->code[i].val.u32 == i+2) {
					// function abc() style?
					VsmxDecompileStack *prev;
					prev = VsmxDecompileStackPop(&stack);
					SWPRINTF_ITEM("function %ls(%ls)", prev->str, args);
					VsmxDecompileStackPush(&stack, &item);
					free(prev);
					
				}
				else {
					warning("Unexpected function definition syntax at %d!", i);
					SWPRINTF_ITEM("function __%u__(%ls)", in->code[i].val.u32, args);
					VsmxDecompileStackPush(&stack, &item);
				}
			} break;
			
			case VID_ARRAY_INDEX: {
				VsmxDecompileStack *idx, *parent;
				// TODO: check that the number supplied in in->code[i].val.u32 isn't used (always is 0)!
				idx = VsmxDecompileStackPop(&stack);
				parent = VsmxDecompileStackPop(&stack);
				SWPRINTF_ITEM("%ls[%ls]", parent->str, idx->str);
				VsmxDecompileStackPush(&stack, &item);
				free(idx);
				free(parent);
			} break;
			case VID_ARRAY_INDEX_ASSIGN: {
				VsmxDecompileStack *val, *idx, *parent;
				val = VsmxDecompileStackPop(&stack);
				idx = VsmxDecompileStackPop(&stack);
				parent = VsmxDecompileStackPop(&stack);
				SWPRINTF_ITEM("%ls[%ls] = %ls", parent->str, idx->str, val->str);
				VsmxDecompileStackPush(&stack, &item);
				free(val);
				free(idx);
				free(parent);
			} break;
			
			case VID_CALL_FUNC:
			case VID_CALL_METHOD:
			case VID_CALL_NEW:
			{
				if(stack->depth < in->code[i].val.u32) {
					error("Not enough arguments to perform requested function call at group %d.", i);
					return 1;
				}
				VsmxDecompileStack *prev;
				if(in->code[i].val.u32 > 0) {
					uint arg;
					strwcpy(item.str, " )", MAX_TEXT_LEN);
					for(arg = 0; arg < in->code[i].val.u32; arg++) {
						prev = VsmxDecompileStackPop(&stack);
						//swprintf(item.str, MAX_TEXT_LEN, L"%s%s", prev->str, item.str);
						//SWPRINTF_ITEM("%ls%ls", prev->str, item.str);
						if(arg+1 < in->code[i].val.u32) {
							//swprintf(item.str, MAX_TEXT_LEN, L", %s", item.str);
							//SWPRINTF_ITEM(", %ls", item.str);
							memmove(prev->str + 2, prev->str, (wcslen(prev->str)+1)*sizeof(wchar));
							//wcscat(prev->str, L", ");
							prev->str[0] = ',';
							prev->str[1] = ' ';
							wcscat(prev->str, item.str);
						} else
							wcscat(prev->str, item.str);
						wcscpy(item.str, prev->str);
						free(prev);
					}
					// function name
					prev = VsmxDecompileStackPop(&stack);
					//swprintf(item.str, MAX_TEXT_LEN, L"%s( %s", prev->str, item.str);
					//SWPRINTF_ITEM("%ls( %ls", prev->str, item.str);
					wcscat(prev->str, L"( ");
					wcscat(prev->str, item.str);
					wcscpy(item.str, prev->str);
				}
				else {
					prev = VsmxDecompileStackPop(&stack);
					//swprintf(item.str, MAX_TEXT_LEN, L"%s( )", prev->str);
					SWPRINTF_ITEM("%ls()", prev->str);
				}
				if((in->code[i].id & 0xFF) == VID_CALL_NEW) {
					wcsprecat(item.str, L"new ", MAX_TEXT_LEN);
				}
				free(prev);
				VsmxDecompileStackPush(&stack, &item);
			} break;
			
			
			// this is either an OR or a for loop
			case VID_JUMP_TRUE: {
				VsmxDecompileStack *prev;
				prev = VsmxDecompileStackPop(&stack);
				
				// check for FOR loop
				// !!! look ahead used !!!
				if(
					// check that next group is a sect start
					   i+1 < in->codeGroups && in->code[i+1].id == VID_SECT_START
					// check that end of for stmt is a jump back
					&& in->code[i].val.u32 < in->codeGroups && in->code[in->code[i].val.u32-1].id == VID_SECT_START && in->code[in->code[i].val.u32-1].val.u32 == stmtStart
					// end of for loop should be after end of for stmt
					&& in->code[i+1].val.u32 > in->code[i].val.u32
					// check that end of for loop jumps back to incrementor
					&& in->code[i+1].val.u32 < in->codeGroups && in->code[in->code[i+1].val.u32-1].id == VID_SECT_START && in->code[in->code[i+1].val.u32-1].val.u32 == i+2
				) {
					// assume for loop
					SWPRINTF_ITEM("for(; %ls /* jump to %d */; ", prev->str, in->code[i].val.u32);
					VsmxDecompileStackPush(&stack, &item);
					
					//forStmtEnd = in->code[i].val.u32;
					// push for end marker of loop
					mItem.src = i+1;
					mItem.loc = in->code[i+1].val.u32;
					VsmxDecompMarkStackPush(&mStack, &mItem);
					// push for end bracket on for()
					mItem.src = i;
					mItem.loc = in->code[i].val.u32;
					VsmxDecompMarkStackPush(&mStack, &mItem);
					i++;
				} else {
					// assume OR
					SWPRINTF_ITEM("( %ls ) || /* ends at %d */ ( ", prev->str, in->code[i].val.u32);
					VsmxDecompileStackPush(&stack, &item);
					
					mItem.src = i;
					mItem.loc = in->code[i].val.u32;
					VsmxDecompMarkStackPush(&mStack, &mItem);
				}
				free(prev);
				endStmtConcat++;
			} break;
			
			// section markers
			case VID_SECT_START: if(!op[0]) {
				// this is either a function start or "else" section, or end of loop
				if(mStack && (in->code[mStack->src].id == VID_JUMP_FALSE || (in->code[mStack->src].id == VID_SECT_START && in->code[i].val.u32 < i))) {
					// check whether else or end of while
					if(in->code[i].val.u32 < i) {
						// assume end of loop
						SWPRINTF(op, 50, L"} %%ls/* jump back to %d */\n", in->code[i].val.u32);
						// push dummy element
						VsmxDecompileStackPush(&stack, &item);
						if(indent > 0) indent--; // this should always be true
						// prevent a section start as this really is an end of section
						notSectStart = TRUE;
						// remove top of marker stack
						if(mStack->loc == i+1)
							VsmxDecompMarkStackPop(&mStack);
						else
							warning("Unexpected loop structure at %d!", i);
					} else {
						// else segment
						// pop top of stack off here, as it's a little weird
						if(mStack->loc == i+1) {
							if(indent > 0) indent--; // this should always be true
							else warning("Internal state nesting error!");
							
							if(stack)
								warning("Unexpected elements found in stack at %d!", i);
							
							VsmxDecompMarkStackPop(&mStack);
						} else {
							warning("Unexpected else stack structure at %d!", i);
						}
						if(stack) {
							// inline else
							wcscat(stack->str, L" : ");
							mItem.src = i;
							mItem.loc = in->code[i].val.u32;
							VsmxDecompMarkStackPush(&mStack, &mItem);
							break;
						} else {
							SWPRINTF(op, 50, L"} else %%ls{ /* ends at %d */\n", in->code[i].val.u32);
							// push dummy element
							VsmxDecompileStackPush(&stack, &item);
						}
					}
				} else if(mStack && in->code[mStack->src].id == VID_JUMP_TRUE && in->code[mStack->src].val.u32 == i+1) {
					// for loop end of stmt probably
					if(stack) warning("Unexpected stack at end of for at %d", i);
					// TODO: need to fix this so it doesn't go on a new line
					SWPRINTF(op, 50, L"%%ls /* return to %d */) {\n", in->code[i].val.u32);
					// push dummy element
					VsmxDecompileStackPush(&stack, &item);
					indentAdd++;
					// prevent a section start (this is a special case)
					notSectStart = TRUE;
					// remove top of marker stack
					VsmxDecompMarkStackPop(&mStack);
					
				} else {
					// function start
					SWPRINTF(op, 50, L"%%ls { /* ends at %d */\n", in->code[i].val.u32); // wcscpy(op, L"%s {\n");
				}
			}
			case VID_JUMP_FALSE: if(!op[0]) {
				// !!! look ahead!
				if(in->code[i].val.u32-1 >= in->codeGroups) {
					error("Invalid jump reference supplied at %d", i);
					return 1;
				}
				// check whether this is an "if" or "while"
				if(in->code[in->code[i].val.u32-1].id == VID_SECT_START && in->code[in->code[i].val.u32-1].val.u32 == stmtStart) {
					// while loop
					SWPRINTF(op, 50, L"while( %%s ) { /* ends at %d */\n", in->code[i].val.u32); // wcscpy(op, L"while( %s ) {\n");
				} else {
					// if statement
					if(stack->depth > endStmtConcat-1) {
						// inline if - special case
						wchar tmp[MAX_TEXT_LEN] = {0};
						
						while(endStmtConcat--) {
							VsmxDecompileStack *prev;
							prev = VsmxDecompileStackPop(&stack);
							wcscat(prev->str, tmp);
							wcscpy(tmp, prev->str);
							free(prev);
						}
						endStmtConcat = 2;
						SWPRINTF_ITEM("( %ls ? /* ends at %d */ ", tmp, in->code[i].val.u32);
						VsmxDecompileStackPush(&stack, &item);
						mItem.src = i;
						mItem.loc = in->code[i].val.u32;
						VsmxDecompMarkStackPush(&mStack, &mItem);
						break;
					} else {
						SWPRINTF(op, 50, L"if( %%s ) { /* ends at %d */\n", in->code[i].val.u32); // wcscpy(op, L"if( %s ) {\n");
					}
				}
			}
			if(!notSectStart) {
				mItem.src = i;
				mItem.loc = in->code[i].val.u32;
				VsmxDecompMarkStackPush(&mStack, &mItem);
				indentAdd++;
			} // fall through to end of statement
			
			case VID_RETURN:		if(!op[0]) wcscpy(op, L"return %s;\n");
			case VID_END_STMT:		if(!op[0]) wcscpy(op, L"%s;\n");
			{
				// end of statement following conditional - skip
				if(in->code[i].id == VID_END_STMT && i && (in->code[i-1].id == VID_JUMP_TRUE || in->code[i-1].id == VID_JUMP_FALSE))
					break;
				
				if(stack) {
					if(stack->depth > endStmtConcat-1) {
						warning("End of statement but more stack elements than expected at groups %d-%d!", stmtStart, i);
					}
					
					
					// TODO: remove debugging line
					fwprintf(out, L"/*%d*/\t", stmtStart);
					
					
					writeTabs(out, indent);
					
					while(endStmtConcat--) {
						VsmxDecompileStack *prev;
						prev = VsmxDecompileStackPop(&stack);
						wcscat(prev->str, item.str);
						wcscpy(item.str, prev->str);
						free(prev);
					}
					fwprintf(out, op, item.str);
					endStmtConcat = 1;
					fflush(out); // TODO: remove later
					
					VsmxDecompileStackDestroy(&stack);
					stmtStart = i+1;
					indent += indentAdd;
					indentAdd = 0;
				} else
					warning("No stack at end of statement at %d!", i);
			} break;
			
			
			
			case VID_END:
				if(i+1 < in->codeGroups) {
					warning("End marker found at %d, but is not end of code!", i);
				}
			break;
			
			case VID_DEBUG_FILE:
			case VID_DEBUG_LINE:
				// TODO: stick in debugging comments
			// ignore NOP
			case VID_NOP:
			break;
			
			default:
				warning("Unknown id 0x%x at %d", in->code[i].id, i);
				SWPRINTF_ITEM("<< UNKNOWN 0x%x 0x%x >>", in->code[i].id, in->code[i].val.u32);
				VsmxDecompileStackPush(&stack, &item);
		}
		
		/*if(is_value) {
			item.item = in->code[i];
			VsmxDecompileStackPush(&stack, &item);
		}*/
	}
	return 0;
}

void freeVsmxMem(VsmxMem* vm) {
	free(vm->code);
	free(vm->text);
	free(vm->prop);
	free(vm->names);
	free(vm->pText);
	free(vm->pProp);
	free(vm->pNames);
	free(vm);
}
