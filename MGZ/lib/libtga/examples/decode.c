/*
 *  tgadecode - Decode TGA image
 *  Copyright (C) 2002  Matthias Brueckner
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Functions demonstrated: TGAOpen(), TGAReadImage(), TGAWriteImage(), 
 *			    TGAClose()
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <tga.h>


void make_header(TGA *src, TGA *dest)
{
	dest->hdr.id_len 	= src->hdr.id_len;
	dest->hdr.map_t		= src->hdr.map_t;
	dest->hdr.img_t 	= src->hdr.img_t;
	dest->hdr.map_first 	= src->hdr.map_first;
	dest->hdr.map_entry 	= src->hdr.map_entry;
	dest->hdr.map_len	= src->hdr.map_len;
	dest->hdr.x 		= src->hdr.x;
	dest->hdr.y 		= src->hdr.y;
	dest->hdr.width 	= src->hdr.width;
	dest->hdr.height 	= src->hdr.height;
	dest->hdr.depth 	= src->hdr.depth;
	dest->hdr.vert 	        = src->hdr.vert;
	dest->hdr.horz          = src->hdr.horz;
	dest->hdr.alpha         = src->hdr.alpha;
}


int main(int argc, char *argv[])
{
       	TGA *in, *out;
	TGAData *data;
	int encode;

	if(argc < 3) {
		printf("Not enough arguments supplied!\n");
		return 0;
	}
	
	data = (TGAData*)malloc(sizeof(TGAData));
	if(!data) {
		TGA_ERROR((TGA*)NULL, TGA_OOM);
		return 0;
	}

        in = TGAOpen(argv[1], "r");
	printf("[open] name=%s, mode=%s\n", argv[1], "r");

	out = TGAOpen(argv[2], "w");
        printf("[open] name=%s, mode=%s\n", argv[2], "w");
	

	data->flags = TGA_IMAGE_ID | TGA_IMAGE_DATA | TGA_RGB;
	TGAReadImage(in, data);
	if (in->last != TGA_OK) {
		TGA_ERROR(in, in->last);
		return 0;
	}

	make_header(in, out);

	TGAWriteImage(out, data);
	if (out->last != TGA_OK) {
		TGA_ERROR(out, out->last);
		return 0;
	}

	printf("[close]\n[close]\n");
        TGAClose(in);
	TGAClose(out);

        printf("[exit] main\n");

	return EXIT_SUCCESS;
}
