#include <string.h>
#include <png.h>
#include <ppu-types.h>
#include "makepng.h"

u8 make_png(char *outfile, imgData data)
{	
	FILE *fp = fopen(outfile, "wb");
    if(!fp) return FAILED; 
    
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr){
		fclose(fp);
		return FAILED;
	}
	
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
       png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
       fclose(fp);
       return FAILED;
    }
	
	if (setjmp(png_jmpbuf(png_ptr))) {
       png_destroy_write_struct(&png_ptr, &info_ptr);
       fclose(fp);
       return FAILED;
    }

	png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, data.width, data.height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    
	png_write_info(png_ptr, info_ptr);	

	png_bytep *row_pointers = (png_bytep *) malloc( sizeof(png_bytep) * data.height);
    int i,j;
    for(i = 0; i < data.height; i++) {
        row_pointers[i] = (png_byte*) malloc(sizeof(png_byte) * data.width * 4);
        for(j = 0; j < data.width; j++) {
			u8 ARGB[4] = {0};
			memcpy(&ARGB, data.bmp_out + i*data.width*4 + j*4, 4);
		
            row_pointers[i][0+4*j] = ARGB[1];
            row_pointers[i][1+4*j] = ARGB[2];   
            row_pointers[i][2+4*j] = ARGB[3];   
            row_pointers[i][3+4*j] = ARGB[0];
        }
    }
	
	png_write_image(png_ptr, row_pointers);
	
	png_write_end(png_ptr, NULL);
	
	for (i = 0; i < data.height; i++) {
        free(row_pointers[i]);
    }
    free(row_pointers);
	
	png_destroy_write_struct(&png_ptr, &info_ptr);
		
	fclose(fp);
	
	return SUCCESS;
}