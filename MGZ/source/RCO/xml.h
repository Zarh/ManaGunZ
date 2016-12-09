/*
 * xml.h - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#ifndef __RCOXML_H__
#define __RCOXML_H__

#include "general.h"
#include "rcomain.h"

uint8_t write_xml (rRCOFile * rco, FILE * fp, char *textDir, uint8_t textXmlOut,
    int sndDumped, uint8_t vsmxConv);
rRCOFile *read_xml (char *fn);

#define RCOXML_TABLE_2ND_DIM 20
typedef char ((*RcoTableMap)[RCOXML_TABLE_2ND_DIM]);	// doesn't make

							// sense...  I want a
							// pointer to an array,
							//
							// not an array of
							// pointers...
extern RcoTableMap RCOXML_TABLE_DATA_COMPRESSION;

extern RcoTableMap RCOXML_TABLE_TEXT_LANG;
extern RcoTableMap RCOXML_TABLE_TEXT_FMT;
extern RcoTableMap RCOXML_TABLE_IMG_FMT;
extern RcoTableMap RCOXML_TABLE_MODEL_FMT;
extern RcoTableMap RCOXML_TABLE_SOUND_FMT;
extern RcoTableMap RCOXML_TABLE_REFTYPE;

extern RcoTagMap RCOXML_TABLE_TAGS;

extern uint32_t RCOXML_TABLE_TAGS_NUM;

extern RcoTableMap RCOXML_TABLE_NAMES;

void rcoxml_int_to_text (uint32_t in, const RcoTableMap map, char *out);
uint8_t rcoxml_text_to_int (char *s, const RcoTableMap map, uint32_t * out);

#endif
