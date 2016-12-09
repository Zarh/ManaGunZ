/*
 * globaldefs.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

/***  For rcomain.h  ***/
#include "rcomain.h"

// 0x1F object type only found in PS3 RCOs and may not be valid for PSP!!!
int *RCO_OBJ_EXTRA_LEN = NULL;
uint32_t RCO_OBJ_EXTRA_LEN_NUM;

// this doesn't include position info
RcoObjMap RCO_OBJ_EXTRA_NAMES = NULL;

RcoObjTypes RCO_OBJ_EXTRA_TYPES = NULL;

int *RCO_ANIM_EXTRA_LEN = NULL;
uint32_t RCO_ANIM_EXTRA_LEN_NUM;

const uint8_t RCO_ANIM_EXTRA_REFS[] =
    { FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE,
  TRUE
};

// this doesn't include references
RcoObjMap RCO_ANIM_EXTRA_NAMES = NULL;

// we'll use the RCO_OBJ_EXTRA_TYPE_* constants here
RcoObjTypes RCO_ANIM_EXTRA_TYPES = NULL;

/***  For xml.h  ***/
#include "xml.h"

RcoTableMap RCOXML_TABLE_DATA_COMPRESSION = NULL;

RcoTableMap RCOXML_TABLE_TEXT_LANG = NULL;
RcoTableMap RCOXML_TABLE_TEXT_FMT = NULL;
RcoTableMap RCOXML_TABLE_IMG_FMT = NULL;
RcoTableMap RCOXML_TABLE_MODEL_FMT = NULL;
RcoTableMap RCOXML_TABLE_SOUND_FMT = NULL;

// const RcoTableMap RCOXML_TABLE_REFTYPE = {"event", "text"}; // TODO:

RcoTagMap RCOXML_TABLE_TAGS = NULL;

uint32_t RCOXML_TABLE_TAGS_NUM;

RcoTableMap RCOXML_TABLE_NAMES = NULL;
