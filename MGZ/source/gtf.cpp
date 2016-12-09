#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "gtf.h"

#include "apputil.h"
#include "gtfconv.h"

bool sIsVerbose = false;
bool sIsDetail = false;
bool sIsSpecified = false;
bool sPrint = true;

extern "C" void print_load(char *format, ...);

bool BUFFER_NEW(GTF_BUFFER_T &buff, uint32_t size)
{
	if(buff.addr != 0 || buff.size != 0) return false;
	if(size == 0) return false;

	try{
		buff.addr = new uint8_t[size];
		if(buff.addr){
			buff.size = size;
			memset(buff.addr, 0, buff.size);
		}
	}catch(...){
		// nothing todo
	}
	return (buff.size != 0);
}

void BUFFER_DELETE(GTF_BUFFER_T & buff)
{
	if(buff.addr == 0) return;
	
	delete [] buff.addr, buff.addr = 0;
	buff.size = 0;
}

extern "C" bool gtf2dds(const char *gtf_fname, const char *dds_fname, uint8_t index, uint32_t option);
bool gtf2dds(const char *gtf_fname, const char *dds_fname, uint8_t index, uint32_t option)
{
	if(!dds_fname) return false;
	if(!gtf_fname) return false;

	GTF_BUFFER_T gtf = {0, 0};
	
	bool bResult = false;

	if(!fileReadFile(gtf_fname, &gtf.addr, &gtf.size)){
		// error: bad input
		print_load((char *) "Error: Bad input file\n");
		return false;
	}

	int16_t num_gtf = gtfconv_gtf2dds_get_texture_count(&gtf, option);
	if(num_gtf == CELL_GTFCONV_ERROR || num_gtf == 0){
		// error: bad format
		print_load((char *) "Error: Bad format\n");
		BUFFER_DELETE(gtf);
		return false;
	}

	if(sIsSpecified && num_gtf <= index){
		// error: bad id
		print_load((char *) "Error: Bad id\n");
		BUFFER_DELETE(gtf);
		return false;
	}

	if(num_gtf == 1 || sIsSpecified){
		GTF_BUFFER_T dds = {0, 0};
		
		int32_t dds_size = gtfconv_gtf2dds_get_size(&gtf, index, option);
		if(dds_size == CELL_GTFCONV_ERROR){
			// error: bad format
			print_load((char *) "Error: Bad format\n");
			BUFFER_DELETE(gtf);
			return false;
		}

		if(!BUFFER_NEW(dds, dds_size)){
			// error: memory error
			print_load((char *) "Error: Memory access error\n");
			BUFFER_DELETE(gtf);
			return false;
		}
		
		int32_t ret = gtfconv_gtf2dds(&dds, &gtf, index, option);
		bResult = (ret == CELL_GTFCONV_OK);

		if(!bResult){
			// error: conv failed
			print_load((char *) "Error: Conversion failed\n");
		}
		
		if(bResult){
			if(!fileWriteFile(dds_fname, dds.addr, dds.size)){
				// error: out file error
				print_load((char *) "Error: Bad output file\n");
				bResult = false;
			}
		}

		BUFFER_DELETE(dds);

	}else{
		// packed gtf
		option &= ~CELL_GTFCONV_FLAG_VERBOSE;
		
		for(int16_t i = 0; i < num_gtf; ++i){
			GTF_BUFFER_T dds = {0, 0};
			uint8_t index = static_cast<uint8_t>(i);
			int32_t dds_size = gtfconv_gtf2dds_get_size(&gtf, index, option);

			if(dds_size == CELL_GTFCONV_ERROR) continue;

			if(BUFFER_NEW(dds, dds_size) == false) continue;

			int32_t ret = gtfconv_gtf2dds(&dds, &gtf, index, option);

			string_t fname = dds_fname;
			fname = fileRemoveExtention(fname);
			fname = strFormat("%s_%03d.dds", fname.c_str(), i);

			if((ret == CELL_GTFCONV_OK)){
				fileWriteFile(fname.c_str(), dds.addr, dds.size);
			}

			bResult |= (ret == CELL_GTFCONV_OK);
			BUFFER_DELETE(dds);
		}
	}

	BUFFER_DELETE(gtf);

	return bResult;
}