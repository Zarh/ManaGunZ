/*
 * vsmx.h - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#ifndef __VSMX_H__
#define __VSMX_H__

#include "general.h"

typedef wchar_t wchar;

#define VSMX_SIGNATURE 0x584D5356	// "VSMX"
#define VSMX_VERSION 0x00010000		// found in PSP RCOs
#define JSX_VERSION 0x00020000		// found on .jsx files for PS3 .raf themes
PACK_STRUCT (VSMXHeader, {
      uint32_t sig; uint32_t ver; uint32_t codeOffset; uint32_t codeLength;
      uint32_t textOffset; uint32_t textLength; uint32_t textEntries;
      uint32_t propOffset;
      uint32_t propLength; uint32_t propEntries; uint32_t namesOffset;
      uint32_t namesLength;
      uint32_t namesEntries;
    });

PACK_STRUCT (VSMXGroup, {
      uint32_t id;
      union {
	uint32_t u32;
	float f;
      } val;
    });

typedef struct {
  VSMXGroup *code;
  wchar *text, *prop;
  char *names;
  wchar **pText, **pProp;
  char **pNames;

  uint32_t codeGroups, numText, numProp, numNames, lenText, lenProp, lenNames;
} VsmxMem;

VsmxMem *readVSMX (FILE * fp);
VsmxMem *readVSMXMem (const void *in);
void writeVSMX (FILE * fp, VsmxMem * in);
void *writeVSMXMem (unsigned int *len, VsmxMem * in);
int VsmxDecode (VsmxMem * in, FILE * out);
VsmxMem *VsmxEncode (FILE * in);
int VsmxDecompile (VsmxMem * in, FILE * out);
void freeVsmxMem (VsmxMem * vm);

#endif
