/*
 * rcofile.h - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#ifndef __RCOFILE_H__
#define __RCOFILE_H__

#include "general.h"

#define RCO_NULL_PTR 0xFFFFFFFF

#define RCO_TABLE_MAIN 1
#define RCO_TABLE_VSMX 2
#define RCO_TABLE_TEXT 3
#define RCO_TABLE_IMG 4
#define RCO_TABLE_MODEL 5
#define RCO_TABLE_SOUND 6
#define RCO_TABLE_FONT 7
#define RCO_TABLE_OBJ 8
#define RCO_TABLE_ANIM 9

#define RCO_SIGNATURE 0x46525000	// .PRF (PSP Resource File?)
PACK_STRUCT (PRFHeader, {
      uint32_t signature;	// RCO_SIGNATURE
      uint32_t version;
      // 0x70 - UMD RCOs (video?), FW1.00
      // 0x71 - UMD RCOs (audio?), FW1.50, FW2.50
      // 0x90 - FW2.60
      // 0x95 - FW2.70, FW2.71
      // 0x96 - FW2.80, FW2.82, FW3.00, FW3.03, FW3.10, FW3.30, FW3.40
      // 0x100 - FW3.50, FW3.52, FW5.00, FW5.55
      uint32_t null;
      uint32_t compression;	// upper nibble = compression,
      // lower nibble:
      // 0=flash0 RCOs, 1=UMD RCOs????
      /*
       * #define RCO_COMPRESSION_NONE 0x00 // entries for 0x01 ?? #define
       * RCO_COMPRESSION_ZLIB 0x10 #define RCO_COMPRESSION_RLZ 0x20 */
      // main table pointers
      uint32_t pMainTable;	// type 1
      uint32_t pVSMXTable;	// type 2
      uint32_t pTextTable;	// type 3
      uint32_t pSoundTable;	// type 5
      uint32_t pModelTable;	// type 6
      uint32_t pImgTable;	// type 4
      uint32_t pUnknown;	// always 0xFFFFFFFF
      uint32_t pFontTable;	// type 7
      uint32_t pObjTable;	// type 8
      uint32_t pAnimTable;	// type 9
      // text stuff
      uint32_t pTextData;	// NOTE: this may == pLabelData if lTextData ==
      //
      // 0
      uint32_t lTextData; uint32_t pLabelData; uint32_t lLabelData;
      uint32_t pEventData;
      uint32_t lEventData;
      // pointer data
      uint32_t pTextPtrs; uint32_t lTextPtrs; uint32_t pImgPtrs;
      uint32_t lImgPtrs;
      uint32_t pModelPtrs; uint32_t lModelPtrs;
      uint32_t pSoundPtrs;
      uint32_t lSoundPtrs; uint32_t pObjPtrs; uint32_t lObjPtrs;
      uint32_t pAnimPtrs;
      uint32_t lAnimPtrs;
      // attached data
      uint32_t pImgData;
      uint32_t lImgData; uint32_t pSoundData; uint32_t lSoundData;
      uint32_t pModelData;
      uint32_t lModelData;
      // always 0xFFFFFFFF
      uint32_t unknown[3];
    });

PACK_STRUCT (RCOEntry, {
      // uint8_t type; // main table uses 0x01; may be used as a current entry
      // depth value
      // uint8_t id;
      uint16_t typeId;
      uint16_t blank;
      uint32_t labelOffset;
      uint32_t eHeadSize;	// =
      // sizeof(RCOEntry)
      // =
      // 0x28
      // [
      // only
      // used
      // for
      // entries with extra info (ie not "main"
      // entries) ]
      uint32_t entrySize;	// main tables (main/img etc) uses 0x28 here,
      // or is this the length of current entry (not
      // including subentries)?
      // 0x10
      uint32_t numSubentries;
      uint32_t nextEntryOffset;
      uint32_t prevEntryOffset;	// this
      // is
      // usually
      // 0x0
      // however
      // (does
      // make
      // writing RCOs easier though :P I guess Sony's
      // tools do something similar...)
      uint32_t parentTblOffset;	// offset of this entry from parent table
      // 0x20
      uint32_t blanks[2];
    });

PACK_STRUCT (RCOVSMXEntry, {
      uint32_t offset;		// always 0x0, so I assume this is an offset
      uint32_t length;		// length of VSMX file
    });

#define RCO_LANG_JAPANESE  0x0
#define RCO_LANG_ENGLISH  0x1
#define RCO_LANG_FRENCH  0x2
#define RCO_LANG_SPANISH  0x3
#define RCO_LANG_GERMAN  0x4
#define RCO_LANG_ITALIAN  0x5
#define RCO_LANG_DUTCH  0x6
#define RCO_LANG_PORTUGESE  0x7
#define RCO_LANG_RUSSIAN  0x8
#define RCO_LANG_KOREAN  0x9
#define RCO_LANG_CHINESE_TRADITIOAL  0xA
#define RCO_LANG_CHINESE_SIMPLIFIED  0xB
// the following are just guestimated from the p3tcompiler readme
#define RCO_LANG_FINNISH  0xC
#define RCO_LANG_SWEDISH  0xD
#define RCO_LANG_DANISH  0xE
#define RCO_LANG_NORWEGIAN  0xF
#define RCO_TEXT_FMT_UTF8 0x0
#define RCO_TEXT_FMT_UTF16 0x1
#define RCO_TEXT_FMT_UTF32 0x2
PACK_STRUCT (RCOTextEntry, {
      uint16_t lang;
      uint16_t format;
      uint32_t numIndexes;
    });

PACK_STRUCT (RCOTextIndex, {
      uint32_t labelOffset;
      uint32_t length;
      uint32_t offset;
    });

#define RCO_DATA_COMPRESSION_NONE 0x0
#define RCO_DATA_COMPRESSION_ZLIB 0x1
#define RCO_DATA_COMPRESSION_RLZ 0x2

#define RCO_IMG_PNG  0x0
#define RCO_IMG_JPEG  0x1
#define RCO_IMG_TIFF  0x2
#define RCO_IMG_GIF  0x3
#define RCO_IMG_BMP  0x4
#define RCO_IMG_GIM  0x5
#define RCO_MODEL_GMO 0x0
PACK_STRUCT (RCOImgModelEntry, {
      uint16_t format;
      uint16_t compression;	// RCO_DATA_COMPRESSION_*
      // constants
      uint32_t sizePacked;
      uint32_t offset;
      uint32_t sizeUnpacked;	// this
      // value
      // doesn't
      // exist
      // if
      // entry
      // isn't
      // compressed
    });

// note, some image/model entries which aren't compressed, don't have the last
// member
PACK_STRUCT (RCOPS3ImgModelEntry, {	// PS3 version of the above
      uint16_t format;
      uint16_t compression;	// RCO_DATA_COMPRESSION_*
      // constants
      uint32_t sizePacked;
      uint32_t offset;
      uint32_t something;	// PS3 RCOs
      // seem to have
      // this extra
      // element -
      // probably something to do with
      // planes/frames?? usually 0x1
      uint32_t sizeUnpacked;	// this value doesn't exist if entry isn't
      // compressed
    });

#define RCO_SOUND_VAG 0x1
PACK_STRUCT (RCOSoundEntry, {
      uint16_t format;		// 0x01 = VAG
      uint16_t channels;	// 1 or 2 channels
      uint32_t sizeTotal;
      uint32_t offset;
      // now pairs of size/offset for each channel
    });

PACK_STRUCT (RCOFontEntry, {
      uint16_t format;		// 1
      uint16_t compression;	// 0
      uint32_t unknown;		// 0
      uint32_t unknown2;
    });

#define RCO_OBJ_TYPE_PAGE		0x1
#define RCO_OBJ_TYPE_PLANE		0x2
#define RCO_OBJ_TYPE_BUTTON		0x3
#define RCO_OBJ_TYPE_XMENU		0x4
#define RCO_OBJ_TYPE_XMLIST		0x5
#define RCO_OBJ_TYPE_XLIST		0x6
#define RCO_OBJ_TYPE_PROGRESS		0x7
#define RCO_OBJ_TYPE_SCROLL		0x8
#define RCO_OBJ_TYPE_MLIST		0x9
#define RCO_OBJ_TYPE_MITEM		0xA
		// #define RCO_OBJ_TYPE_0B = 0xB
#define RCO_OBJ_TYPE_XITEM		0xC
#define RCO_OBJ_TYPE_TEXT		0xD
#define RCO_OBJ_TYPE_MODEL		0xE
#define RCO_OBJ_TYPE_SPIN		0xF
#define RCO_OBJ_TYPE_ACTION		0x10
#define RCO_OBJ_TYPE_ITEMSPIN	0x11
#define RCO_OBJ_TYPE_GROUP		0x12
#define RCO_OBJ_TYPE_LLIST		0x13
#define RCO_OBJ_TYPE_LITEM		0x14
#define RCO_OBJ_TYPE_EDIT		0x15
#define RCO_OBJ_TYPE_CLOCK		0x16
#define RCO_OBJ_TYPE_ILIST		0x17
#define RCO_OBJ_TYPE_IITEM		0x18
#define RCO_OBJ_TYPE_ICON		0x19
#define RCO_OBJ_TYPE_UBUTTON	0x1A

#define RCO_REF_EVENT	0x400	// relative
#define RCO_REF_TEXT	0x401	// # (0-based)
#define RCO_REF_IMG		0x402	// absolute
#define RCO_REF_MODEL	0x403	// absolute
#define RCO_REF_FONT	0x405	// absolute
#define RCO_REF_OBJ2	0x407	// same as 0x409??
#define RCO_REF_ANIM	0x408	// absolute
#define RCO_REF_OBJ		0x409	// absolute
#define RCO_REF_NONE	0xFFFF
PACK_STRUCT (RCOReference, {
      uint32_t type;
      uint32_t ptr;
    });

#define RCO_ANIM_TYPE_POS		0x2
#define RCO_ANIM_TYPE_COLOUR	0x3
#define RCO_ANIM_TYPE_ROTATE	0x4
#define RCO_ANIM_TYPE_SCALE		0x5
#define RCO_ANIM_TYPE_ALPHA		0x6
#define RCO_ANIM_TYPE_DELAY		0x7
#define RCO_ANIM_TYPE_EVENT		0x8
#define RCO_ANIM_TYPE_LOCK		0x9	// ?
#define RCO_ANIM_TYPE_UNLOCK	0xA	// ?
#define RCO_ANIM_TYPE_0B		0xB	// only appears on UMD RCOs?

PACK_STRUCT (HeaderComprInfo, {
      uint32_t lenPacked;
      uint32_t lenUnpacked;
      uint32_t lenLongestText;	// length
      // of
      // the
      // longest
      // language's
      // text
      // data
      // (unpacked)
    });

PACK_STRUCT (TextComprInfo, {
      uint16_t lang;
      uint16_t unknown;		// always 0x1
      uint32_t nextOffset;	// = ALIGN_TO_4(sizeof(TextComprInfo) +
      // packedLen); is 0 for last text entry
      // regardless of what actually comes after
      uint32_t packedLen;
      uint32_t unpackedLen;
    });

#endif
