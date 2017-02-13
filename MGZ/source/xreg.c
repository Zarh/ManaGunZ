#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define SUCCESS 	1
#define FAILED	 	0

int xreg2txt(char *xreg_path, char *txt_path)
{

	FILE *txt;
	FILE *xreg;
	
	xreg = fopen(xreg_path, "rb");
	if(xreg==NULL) return FAILED;
	
	txt = fopen(txt_path, "wb");
	if(txt==NULL) { fclose(xreg); return FAILED; }

	uint8_t magic[0x10] = {0xBC, 0xAD, 0xAD, 0xBC, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x02, 0xBC, 0xAD, 0xAD, 0xBC};
	
	uint8_t data[0x10];
	fread(&data, 0x10, 1, xreg);
	
	if( memcmp(data, magic, 0x10) != 0 ) {
		fclose(txt);
		fclose(xreg);
		printf("Error : Bad magic");
		return FAILED;
	}
	uint32_t index_off;
	uint32_t current_entry_offset;
	
	uint16_t str_len;
	uint8_t index_type;
	
	while( 1 )
	{
		uint16_t unk0;
		index_off = ftell(xreg);
		current_entry_offset = ftell(xreg);
		
		fread(&unk0, 2, 1, xreg);
		fread(&str_len, 2, 1, xreg);
		fread(&index_type, 1, 1, xreg);
		
		//unk0 = ENDIAN_SWAP(unk0);
		//str_len = ENDIAN_SWAP(str_len);
		
		if( unk0 == 0xAABB && str_len == 0xCCDD && index_type==0xEE ) break;
		
		if(index_type == 0) fputs("[ ACTIVE     ] ", txt); else
		if(index_type == 1) fputs("[ INACTIVE   ] ", txt); else
		if(index_type == 2) fputs("[ HIDDEN     ] ", txt); else
		if(index_type == 3) fputs("[ DIRECTORY  ] ", txt); else
						    fputs("[ UNKNOWN    ] ", txt);
		
		char *str_index = malloc(str_len+2);
		fread(str_index, str_len+1, 1, xreg);
		fputs(str_index, txt);
		
		free(str_index);
		
		index_off = ftell(xreg);

		fseek(xreg, 0x10000, SEEK_SET);
		while( 1 )
		{
			uint16_t unk1;
			uint16_t entry_offset;
			uint16_t unk2;
			uint16_t data_lenth;
			uint8_t data_type;
			//uint8_t separator;
			
			fread(&unk1, 2, 1, xreg);
			fread(&entry_offset, 2, 1, xreg);
			fread(&unk2, 2, 1, xreg);
			fread(&data_lenth, 2, 1, xreg);
			fread(&data_type, 1, 1, xreg);
			
			//unk1 = ENDIAN_SWAP(unk1);
			//entry_offset = ENDIAN_SWAP(entry_offset);
			//unk2 = ENDIAN_SWAP(unk2);
			//data_lenth = ENDIAN_SWAP(data_lenth);
			
			if(unk1 == 0xAABB && entry_offset == 0xCCDD && unk2 == 0xEE00) break;
			
			entry_offset += 0x10;
			
			uint8_t *data=NULL;
			
			data = (uint8_t *) malloc(data_lenth+2);
			fread(data, data_lenth+1, 1, xreg);
						
			//fread(&separator, 1, 1, xreg);
			
			if(entry_offset == current_entry_offset) {
				uint8_t i;
				for(i=str_len; i < 50; i++) fputs(" ", txt);
				
				if(data_type == 0) {
					fputs("[ BOOL ]", txt);
					if(data_lenth==0) break;
					if(data == 0) fputs("False", txt);
					else fputs("True", txt);
				} else
				if(data_type == 1) {
					fputs("[ INT  ]", txt);
					if(data_lenth==0) break;
					char temp[128];
					sprintf(temp, "0x%X", (unsigned int) (uintptr_t) data);
					fputs(temp, txt);
				} else
				if(data_type == 2) {
					fputs("[ STR  ]", txt);
					if(data_lenth==0) break;
					fputs((char *) data, txt);
				}
				free(data);
				break;
			}
			free(data);
		}
		fputs("\n", txt);
		
		fseek(xreg, index_off, SEEK_SET);
	}
	
	fclose(txt);
	fclose(xreg); 
	
	return SUCCESS;
}
