/*
 * rcoreader.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rcofile.h"
#include "rcomain.h"
#include "configscan.h"

#define MAX_LABEL_DATA 16777216	// 16MB of data; also used for event/text data
#define MAX_TREE_DATA 33554432	// 32MB of data
#define MAX_SUBENTRIES 65536	// used for max num text indexes too

// items used only when reading the file
typedef struct {
  char *fName;
  uint32_t fSize;
  uint32_t fSizeExpanded;	// file size with decompressed header

  void *tables;			// decompressed tables
  uint32_t tablesSize;
  uint32_t memPos;
  uint32_t memOffset;

  FILE *fp;			// for uncompressed tables

  uint32_t *ptrsObj;
  uint32_t numObjPtrs;
  uint32_t *ptrsAnim;
  uint32_t numAnimPtrs;

  uint8_t ps3;			// TRUE if PS3 RCO

} rRCOFile_readhelper;

void read_entry (rRCOFile_readhelper * rcoH, rRCOFile * rco, rRCOEntry * data,
    uint8_t readSubEntries);
rRCOEntry *find_entry_from_offset (rRCOEntry * parent, uint32_t offset);
uint8_t check_file_region (uint32_t fSize, uint32_t offset, uint32_t size);
uint32_t rco_fread (rRCOFile_readhelper * rcoH, void *buf, uint32_t len);
uint32_t rcoread_ftell (rRCOFile_readhelper * rcoH);
int rcoread_fseek (rRCOFile_readhelper * rcoH, uint32_t pos);

void fix_refs (rRCOFile * rco, rRCOEntry * entry, const int *lenArray,
    const uint32_t lenNum, uint8_t isObj);

rRCOFile *
read_rco (char *fn)
{
  rRCOFile_readhelper rcoH;
  rRCOFile *rco = (rRCOFile *) malloc (sizeof (rRCOFile));

  rcoH.fName = fn;
  rcoH.fp = fopen (fn, "rb");

  if (!rcoH.fp) {
    error ("Unable to open file %s", fn);
    return NULL;
  }

  fseek (rcoH.fp, 0, SEEK_END);
  rcoH.fSizeExpanded = rcoH.fSize = ftell (rcoH.fp);
  rewind (rcoH.fp);

  PRFHeader header;

  if (!check_file_region (rcoH.fSize, 0, sizeof (header))) {
    error ("File too small to be a valid RCO file.");
    return NULL;
  }
  fileread (rcoH.fp, &header, sizeof (header));

  // check for endian swapped signature
  if (header.signature == ENDIAN_SWAP_32(RCO_SIGNATURE)) {
    rco->eSwap = TRUE;
    es_rcoHeader (&header);
  } else
    rco->eSwap = FALSE;

  if (header.signature != RCO_SIGNATURE) {
    error ("[header] Invalid signature - not a valid RCO file.");
    return NULL;
  }
  if (header.null != 0) {
    warning ("[header] Unexpected value @ 0x8: 0x%d (expected: 0x0).",
	header.null);
  }

  if (header.pUnknown != RCO_NULL_PTR) {
    warning ("[header] Unknown RCO section @ 0x28 (points to 0x%x)",
	header.pUnknown);
  }
  // if(header.pFontTable != RCO_NULL_PTR) {
  // warning("[header] Unknown RCO section @ 0x2C (points to 0x%x)",
  // header.pFontTable);
  // }
  if (header.unknown[0] != 0xFFFFFFFF || header.unknown[1] != 0xFFFFFFFF ||
      header.unknown[2] != 0xFFFFFFFF) {
    warning ("[header] Unexpected value(s) in range 0x98-0xA4");
  }

  rco->umdFlag = header.compression & 0xF;	// actually, I'm usure about
  // this, but meh
  rco->headerCompression = header.compression >> 4;
  rco->verId = header.version;

  {
    info ("RCO header info:");
    if (rco->eSwap) {
      info ("    Endian = big (PS3)");
    } else {
      info ("    Endian = little (PSP)");
    }
    info ("    VersionID = 0x%x", rco->verId);
    info ("    Compression = 0x%x", rco->headerCompression);
    info ("    UMDFlag = %d", rco->umdFlag);
    info ("    MainTree Offset = 0x%x", header.pMainTable);
    if (header.pVSMXTable != RCO_NULL_PTR)
      info ("    VSMXTree Offset = 0x%x", header.pVSMXTable);
    if (header.pTextTable != RCO_NULL_PTR)
      info ("    TextTree Offset = 0x%x", header.pTextTable);
    if (header.pSoundTable != RCO_NULL_PTR)
      info ("    SoundTree Offset = 0x%x", header.pSoundTable);
    if (header.pModelTable != RCO_NULL_PTR)
      info ("    ModelTree Offset = 0x%x", header.pModelTable);
    if (header.pFontTable != RCO_NULL_PTR)
      info ("    FontTree Offset = 0x%x", header.pFontTable);
    if (header.pImgTable != RCO_NULL_PTR)
      info ("    ImageTree Offset = 0x%x", header.pImgTable);
    if (header.pObjTable != RCO_NULL_PTR)
      info ("    ObjectTree Offset = 0x%x", header.pObjTable);
    if (header.pAnimTable != RCO_NULL_PTR)
      info ("    AnimTree Offset = 0x%x", header.pAnimTable);

    if (header.lTextData)
      info ("    TextData Offset = 0x%x [length = 0x%x]", header.pTextData,
	  header.lTextData);
    if (header.lLabelData)
      info ("    NameData Offset = 0x%x [length = 0x%x]", header.pLabelData,
	  header.lLabelData);
    if (header.lEventData)
      info ("    EventData Offset = 0x%x [length = 0x%x]", header.pEventData,
	  header.lEventData);

    if (header.lImgData)
      info ("    ImageData Offset = 0x%x [length = 0x%x]", header.pImgData,
	  header.lImgData);
    if (header.lSoundData)
      info ("    SoundData Offset = 0x%x [length = 0x%x]", header.pSoundData,
	  header.lSoundData);
    if (header.lModelData)
      info ("    ModelData Offset = 0x%x [length = 0x%x]", header.pModelData,
	  header.lModelData);
  }
  
  // check compression headers
  switch (rco->headerCompression) {
    case RCO_DATA_COMPRESSION_NONE:
      break;
    case RCO_DATA_COMPRESSION_ZLIB:
      if (header.version < 0x90)
	warning ("[header] Unexpected version 0x%x for compression type",
	    header.version);
      break;
    case RCO_DATA_COMPRESSION_RLZ:
      if (header.version < 0x95)
	warning ("[header] Unexpected version 0x%x for compression type",
	    header.version);
      break;

    default:
      error
	  ("[header] Unknown compression type 0x%x - process cannot continue.",
	  rco->headerCompression);
      return NULL;
      /* warning("[header] Unknown compression type 0x%x - assuming
       * uncompressed data.", rco->headerCompression); // set it to no
       * compression rco->headerCompression = RCO_DATA_COMPRESSION_NONE; */
  }

  rco->ps3 = TRUE;	// && header.version >= 0x97
  configLoadObjmap (rco->ps3);
  configLoadAnimmap (rco->ps3);
  // rcoH.ps3 = (rco->eSwap && header.version >= 0x107);

  // TODO: check file regions for decompression

  rcoH.tablesSize = 0;
  rcoH.tables = 0;
  rcoH.memPos = 0;
  if (rco->headerCompression) {
    rcoH.memOffset = ftell (rcoH.fp);	// should = 0xA4
    HeaderComprInfo ci;

    if (!fileread (rcoH.fp, &ci, sizeof (ci))) {
      error ("[header] Unable to read in compression info!");
      return NULL;
    }
    if (rco->eSwap)
      es_headerComprInfo (&ci);
    info ("    Header compression: compressed = 0x%x bytes, uncompressed = 0x%x bytes", ci.lenPacked, ci.lenUnpacked);

    rcoH.tablesSize = ci.lenUnpacked;
    if (ci.lenUnpacked > MAX_TREE_DATA || ci.lenPacked > MAX_TREE_DATA) {
      error
	  ("[header] Size of tree data exceeds sane limit.  This is probably a bad RCO.");
      return NULL;
    }

    rcoH.tables = malloc (ci.lenUnpacked);

    switch (rco->headerCompression) {
      case RCO_DATA_COMPRESSION_ZLIB:
	{
	  // uses a bit of memory... - could use zlib's inflate routines, but
	  // eh, I doubt it really matters that much...
	  void *readBuf = malloc (ci.lenPacked);

	  fileread (rcoH.fp, readBuf, ci.lenPacked);
	  int uRet = zlib_uncompress (rcoH.tables, ci.lenUnpacked, readBuf,
	      ci.lenPacked);

	  if (uRet != Z_OK && uRet != Z_DATA_ERROR) {
	    error ("[entries] Unable to decompress tree entries!");
	    return FALSE;
	  } else if (uRet == Z_DATA_ERROR) {
	    warning
		("Encountered 'data error' when decompressing tree entries.");
	  }
	  free (readBuf);

	  rcoH.fSizeExpanded += ci.lenUnpacked - ALIGN_TO_4 (ci.lenPacked);
	}

	break;

      case RCO_DATA_COMPRESSION_RLZ:
	error
	    ("[header] This RCO uses RLZ compression which currently cannot be decompressed with rcomage.  (use Z33's Resurssiklunssi to decompress the RCO)");
	return NULL;

      default:			// this won't actually ever be executed due to
	// the new compression checking code above...
	// :/
	error
	    ("[header] Unknown compression method specified (0x%x) - can't continue.",
	    rco->headerCompression);
	return NULL;
    }

    // decompress text data
    if (header.pTextData != RCO_NULL_PTR && header.lTextData) {
      fseek (rcoH.fp, header.pTextData, SEEK_SET);	// TODO: check offset
      // first!
      TextComprInfo tci;

      info ("TextData Compression info:");

      rcoH.tablesSize = ALIGN_TO_4 (rcoH.tablesSize);
      do {
	if (!fileread (rcoH.fp, &tci, sizeof (tci))) {
	  error ("Failed to read in text compression info.");
	  return NULL;
	}
	if (rco->eSwap)
	  es_textComprInfo (&tci);

	if (tci.unknown != 0x1)
	  warning ("[text-data] Unexpected value (0x%x) @ 0x2 - expected 0x1",
	      tci.unknown);
	info ("    LangID = 0x%x, compressed = 0x%x bytes, uncompressed = 0x%x bytes", tci.lang, tci.packedLen, tci.unpackedLen);

	if (tci.unpackedLen > MAX_LABEL_DATA || tci.packedLen > MAX_LABEL_DATA) {
	  error ("[text-data] Size of text data exceeds sane limits.");
	  return NULL;
	}
	uint32_t oldSize = rcoH.tablesSize;

	rcoH.tablesSize += ALIGN_TO_4 (tci.unpackedLen);
	rcoH.tables = realloc (rcoH.tables, rcoH.tablesSize);

	void *readBuf = malloc (tci.packedLen);

	fileread (rcoH.fp, readBuf, tci.packedLen);
	int uRet = zlib_uncompress ((char *) rcoH.tables + oldSize,
	    tci.unpackedLen, readBuf,
	    tci.packedLen);

	if (uRet != Z_OK && uRet != Z_DATA_ERROR) {
	  error ("[text-data] Unable to decompress text data!");
	  return FALSE;
	} else if (uRet == Z_DATA_ERROR) {
	  warning ("Encountered 'data error' when decompressing text data.");
	}
	free (readBuf);

	rcoH.fSizeExpanded += ALIGN_TO_4 (tci.unpackedLen) - ALIGN_TO_4 (tci.packedLen);	// TODO:
	//
	// need
	// to
	// check
	// if
	// this
	// is
	// correct

	if (!tci.nextOffset)
	  break;
	int seekAmt = tci.nextOffset - sizeof (tci) - tci.packedLen;

	if (seekAmt)
	  fseek (rcoH.fp, seekAmt, SEEK_CUR);
      }
      while (tci.nextOffset);
    }
  }

  if (!check_file_region (rcoH.fSizeExpanded, header.pLabelData,
	  header.lLabelData)) {
    error ("[header] Invalid label pointer/length specified.");
    return NULL;
  }
  if (header.lLabelData > MAX_LABEL_DATA) {
    header.lLabelData = MAX_LABEL_DATA;
    warning
	("[labels] Total data length exceeds safety limit of 16MB - data has been truncated!");
  }
  rco->labelsLen = header.lLabelData;
  if (header.lLabelData) {
    rco->labels = (char *) malloc (header.lLabelData);
    rcoread_fseek (&rcoH, header.pLabelData);
    rco_fread (&rcoH, rco->labels, header.lLabelData);
  }

  if (!check_file_region (rcoH.fSizeExpanded, header.pEventData,
	  header.lEventData)) {
    error ("[header] Invalid event pointer/length specified.");
    return NULL;
  }
  if (header.lEventData > MAX_LABEL_DATA) {
    warning
	("[events] Total data length (%d) exceeds safety limit of 16MB - data has been truncated!",
	header.lEventData);
    header.lEventData = MAX_LABEL_DATA;
  }
  rco->eventsLen = header.lEventData;
  if (header.lEventData) {
    rco->events = (char *) malloc (header.lEventData);
    rcoread_fseek (&rcoH, header.pEventData);
    rco_fread (&rcoH, rco->events, header.lEventData);
  }
  // read pointer tables
  // TODO: think about what to do with these
  {
    // rcoH.ptrsText = rcoH.ptrsImg = rcoH.ptrsModel = rcoH.ptrsSound = 0;
    rcoH.ptrsObj = rcoH.ptrsAnim = 0;

    // macro to help save us some code
#define READ_RCO_READ_PTR_SEGMENT(hp, hl, dp, dl, s) \
			dp = 0; \
			dl = 0; \
			if(hp != RCO_NULL_PTR) { \
				if(!check_file_region(rcoH.fSizeExpanded, hp, hl)) { \
					error("[header] Invalid %s pointer/length specified.", s); \
					return NULL; \
				} \
				if((hl) > MAX_LABEL_DATA) { \
					warning("[%s] Total data length (%d) exceeds safety limit of 16MB - data has been truncated!", s, hl); \
					hl = MAX_LABEL_DATA; \
				} \
				dl = (hl) / sizeof(uint32_t); \
				hl = (dl) * sizeof(uint32_t); \
				if(dl) { \
					dp = (uint32_t*)malloc(hl); \
					rcoread_fseek(&rcoH, hp); \
					rco_fread(&rcoH, dp, hl); \
				} \
			}
    /*
     * READ_RCO_READ_PTR_SEGMENT(header.pTextPtrs, header.lTextPtrs,
     * rcoH.ptrsText, rcoH.numTextPtrs, "text");
     * READ_RCO_READ_PTR_SEGMENT(header.pImgPtrs, header.lImgPtrs,
     * rcoH.ptrsImg, rcoH.numImgPtrs, "image");
     * READ_RCO_READ_PTR_SEGMENT(header.pModelPtrs, header.lModelPtrs,
     * rcoH.ptrsModel, rcoH.numModelPtrs, "model");
     * READ_RCO_READ_PTR_SEGMENT(header.pSoundPtrs, header.lSoundPtrs,
     * rcoH.ptrsSound, rcoH.numSoundPtrs, "sound"); */
    READ_RCO_READ_PTR_SEGMENT (header.pObjPtrs, header.lObjPtrs, rcoH.ptrsObj,
	rcoH.numObjPtrs, "object");
    READ_RCO_READ_PTR_SEGMENT (header.pAnimPtrs, header.lAnimPtrs,
	rcoH.ptrsAnim, rcoH.numAnimPtrs, "anim");

    // TODO: possibly sort these for the following section (not that necessary
    // - only useful if we find an unknown object/anim type)
    // TODO: endian swap these entries if we intend to read them...
  }

  // read main/vsmx/text/sound/model/img/obj/anim tables
  rcoread_fseek (&rcoH, header.pMainTable);
  read_entry (&rcoH, rco, &(rco->tblMain), TRUE);

  // TODO: check for unreferenced labels / events?

  // assign shortcut tables
  {
    rco->tblVSMX = rco->tblText = rco->tblImage = rco->tblSound =
	rco->tblModel = rco->tblFont = rco->tblObj = rco->tblAnim = 0;
    rRCOEntry *rcoNode;

    for (rcoNode = rco->tblMain.firstChild; rcoNode; rcoNode = rcoNode->next) {
      switch (rcoNode->id) {
#define READ_RCO_ASN_SHORTCUT_TBL(hp, sc, s) \
					if(hp == RCO_NULL_PTR) warning("[header] %c%s main tree not referenced but found in entries.", toupper((int)s[0]), s+1); \
					if(sc) { warning("[header] Multiple %s main trees found!", s); } \
					else { sc = rcoNode; } \
					break;

	case RCO_TABLE_VSMX:
	  READ_RCO_ASN_SHORTCUT_TBL (header.pVSMXTable, rco->tblVSMX, "VSMX");
	  break;
	case RCO_TABLE_TEXT:
	  READ_RCO_ASN_SHORTCUT_TBL (header.pTextTable, rco->tblText, "text");
	  break;
	case RCO_TABLE_IMG:
	  READ_RCO_ASN_SHORTCUT_TBL (header.pImgTable, rco->tblImage, "image");
	  break;
	case RCO_TABLE_SOUND:
	  READ_RCO_ASN_SHORTCUT_TBL (header.pSoundTable, rco->tblSound,
	      "sound");
	  break;
	case RCO_TABLE_MODEL:
	  READ_RCO_ASN_SHORTCUT_TBL (header.pModelTable, rco->tblModel,
	      "model");
	  break;
	case RCO_TABLE_FONT:
	  READ_RCO_ASN_SHORTCUT_TBL (header.pFontTable, rco->tblFont, "font");
	  break;
	case RCO_TABLE_OBJ:
	  READ_RCO_ASN_SHORTCUT_TBL (header.pObjTable, rco->tblObj, "object");
	  break;
	case RCO_TABLE_ANIM:
	  READ_RCO_ASN_SHORTCUT_TBL (header.pAnimTable, rco->tblAnim,
	      "animation");
	  break;
      }
    }

    if (header.pVSMXTable != RCO_NULL_PTR && !rco->tblVSMX)
      warning
	  ("[header] VSMX tree referenced in header, but couldn't be found when parsing entries!  Section has been discarded.");
    if (header.pTextTable != RCO_NULL_PTR && !rco->tblText)
      warning
	  ("[header] Text tree referenced in header, but couldn't be found when parsing entries!  Section has been discarded.");
    if (header.pImgTable != RCO_NULL_PTR && !rco->tblImage)
      warning
	  ("[header] Image tree referenced in header, but couldn't be found when parsing entries!  Section has been discarded.");
    if (header.pSoundTable != RCO_NULL_PTR && !rco->tblSound)
      warning
	  ("[header] Sound tree referenced in header, but couldn't be found when parsing entries!  Section has been discarded.");
    if (header.pModelTable != RCO_NULL_PTR && !rco->tblModel)
      warning
	  ("[header] Model tree referenced in header, but couldn't be found when parsing entries!  Section has been discarded.");
    if (header.pFontTable != RCO_NULL_PTR && !rco->tblFont)
      warning
	  ("[header] Font tree referenced in header, but couldn't be found when parsing entries!  Section has been discarded.");
    if (header.pObjTable != RCO_NULL_PTR && !rco->tblObj)
      warning
	  ("[header] Object tree referenced in header, but couldn't be found when parsing entries!  Section has been discarded.");
    if (header.pAnimTable != RCO_NULL_PTR && !rco->tblAnim)
      warning
	  ("[header] Animation tree referenced in header, but couldn't be found when parsing entries!  Section has been discarded.");
  }

  // add offset/len/compression info for text entries
  if (rco->tblText && header.lTextData) {
    // TODO: assign things for compressed text data
    rRCOEntry *rcoNode = rco->tblText->firstChild;

    if (rco->headerCompression != RCO_DATA_COMPRESSION_NONE) {
      // if header is compressed, we've got to reparse the RCO file to get the
      // positions :/
      FILE *fp2 = fopen (fn, "rb");
      HeaderComprInfo hci;
      TextComprInfo tci;

      fseek (fp2, sizeof (header), SEEK_SET);
      fileread (fp2, &hci, sizeof (hci));
      if (rco->eSwap)
	es_headerComprInfo (&hci);
      fseek (fp2, ALIGN_TO_4 (hci.lenPacked), SEEK_CUR);

      // before parsing the file, we'll be on the safe side and blank out all
      // text entries' src
      for (; rcoNode; rcoNode = rcoNode->next) {
	rcoNode->srcAddr = rcoNode->srcLenUnpacked = rcoNode->srcLen = 0;
	rcoNode->srcCompression = RCO_DATA_COMPRESSION_NONE;
      }

      tci.nextOffset = 1;	// dummy
      while (tci.nextOffset) {
	fileread (fp2, &tci, sizeof (tci));
	if (rco->eSwap)
	  es_textComprInfo (&tci);
	// search for correct entry to assign to
	for (rcoNode = rco->tblText->firstChild; rcoNode;
	    rcoNode = rcoNode->next) {
	  if (((rRCOTextEntry *) rcoNode->extra)->lang == tci.lang) {
	    rcoNode->srcAddr = ftell (fp2);
	    rcoNode->srcLenUnpacked = tci.unpackedLen;
	    rcoNode->srcLen = tci.packedLen;
	    rcoNode->srcCompression = rco->headerCompression;
	    break;
	  }
	}

	if (!tci.nextOffset)
	  break;
	fseek (fp2, tci.nextOffset - sizeof (tci), SEEK_CUR);
      }

      fclose (fp2);
    } else {
      for (; rcoNode; rcoNode = rcoNode->next) {
	rcoNode->srcAddr = header.pTextData;
	rcoNode->srcLenUnpacked = rcoNode->srcLen = header.lTextData;
	rcoNode->srcCompression = RCO_DATA_COMPRESSION_NONE;
      }
    }
  }
  // fix offsets for img/model/sound srcAddr
  // TODO: really should put in the right values when traversing the tree
  // instead of a post-fix
  {
    rRCOEntry *rcoNode;

    if (rco->tblImage) {
      for (rcoNode = rco->tblImage->firstChild; rcoNode;
	  rcoNode = rcoNode->next)
	rcoNode->srcAddr += header.pImgData;
    }
    if (rco->tblModel) {
      for (rcoNode = rco->tblModel->firstChild; rcoNode;
	  rcoNode = rcoNode->next)
	rcoNode->srcAddr += header.pModelData;
    }
    if (rco->tblSound) {
      for (rcoNode = rco->tblSound->firstChild; rcoNode;
	  rcoNode = rcoNode->next)
	rcoNode->srcAddr += header.pSoundData;
    }
  }

  // TODO: check for dupe labels

  // fix object/anim references
  if (rco->tblObj)
    fix_refs (rco, rco->tblObj, RCO_OBJ_EXTRA_LEN, RCO_OBJ_EXTRA_LEN_NUM, TRUE);
  if (rco->tblAnim)
    fix_refs (rco, rco->tblAnim, RCO_ANIM_EXTRA_LEN, RCO_ANIM_EXTRA_LEN_NUM,
	FALSE);

  rco_fix_decomp_sizes (rco, &rco->tblMain);

  // check resources
  {
    // TODO: should use rcoH.fSizeExpanded here otherwise we stuff up the
    // region tracking code
    if (rco->tblText && rco->tblText->numSubentries) {
      if (!check_file_region (rcoH.fSize, header.pTextData, header.lTextData))
	warning ("[header] Text resource pointer/length is invalid.");
    }
    if (rco->tblImage && rco->tblImage->numSubentries) {
      if (!check_file_region (rcoH.fSize, header.pImgData, header.lImgData))
	warning ("[header] Image resource pointer/length is invalid.");
    }
    if (rco->tblSound && rco->tblSound->numSubentries) {
      if (!check_file_region (rcoH.fSize, header.pSoundData, header.lSoundData))
	warning ("[header] Sound resource pointer/length is invalid.");
    }
    if (rco->tblModel && rco->tblModel->numSubentries) {
      if (!check_file_region (rcoH.fSize, header.pModelData, header.lModelData))
	warning ("[header] Model resource pointer/length is invalid.");
    }

    /*
     * rco->pDataText = header.pTextData; rco->lDataText = header.lTextData;
     * if(!rco->lDataText) rco->pDataText = 0; rco->pDataImg = header.pImgData;
     * rco->lDataImg = header.lImgData; if(!rco->lDataImg) rco->pDataImg = 0;
     * rco->pDataSound = header.pSoundData; rco->lDataSound = header.lSoundData;
     * if(!rco->lDataSound) rco->pDataSound = 0; rco->pDataModel =
     * header.pModelData; rco->lDataModel = header.lModelData;
     * if(!rco->lDataModel) rco->pDataModel = 0;
     *
     * rco->attachSource = (char*)malloc(strlen(fn) +1);
     * strcpy(rco->attachSource, fn); */
  }

  fclose (rcoH.fp);
  if (rcoH.tables)
    free (rcoH.tables);

  /* if(rcoH.ptrsText) free(rcoH.ptrsText); if(rcoH.ptrsImg)
   * free(rcoH.ptrsImg); if(rcoH.ptrsModel) free(rcoH.ptrsModel);
   * if(rcoH.ptrsSound) free(rcoH.ptrsSound); */
  if (rcoH.ptrsObj)
    free (rcoH.ptrsObj);
  if (rcoH.ptrsAnim)
    free (rcoH.ptrsAnim);

  return rco;
}

void
read_entry (rRCOFile_readhelper * rcoH, rRCOFile * rco, rRCOEntry * data,
    uint8_t readSubEntries)
{

  data->offset = rcoread_ftell (rcoH);
  if (!check_file_region (rcoH->fSizeExpanded, data->offset, sizeof (RCOEntry))) {
    error ("[entry] Unable to read entry - file exhausted.");
    return;
  }

  RCOEntry re;

  rco_fread (rcoH, &re, sizeof (re));
  if (rco->eSwap)
    es_rcoEntry (&re);

  data->type = re.typeId & 0xFF;
  data->id = (re.typeId & 0xFF00) >> 8;
  
  if (re.blank != 0) {
    warning ("[entry (0x%x)] Unexpected entry value @ 0x2", data->offset);
  }
  data->labelOffset = RCO_NULL_PTR;
  if (re.labelOffset != RCO_NULL_PTR) {
    if (re.labelOffset >= rco->labelsLen) {
      warning ("[entry (0x%x)] Invalid label offset supplied - label removed",
	  data->offset);
    } else {
      // WARNING! this assignment is unchecked (ie possible to cause this to
      // point to anything)
      data->labelOffset = re.labelOffset;
    }
  }
  if (re.eHeadSize && re.eHeadSize != sizeof (re)) {
    warning ("[entry (0x%x)] Non-standard entry header size found!",
	data->offset);
  }

  data->numSubentries = re.numSubentries;
  data->rco = rco;
  data->parent = data->firstChild = data->lastChild = data->prev = data->next =
      NULL;
  if (re.blanks[0] != 0 || re.blanks[1] != 0) {
    warning ("[entry (0x%x)] Unexpected entry value in range 0x20-0x28",
	data->offset);
  }

  data->srcFile[0] = '\0';

  data->extra = 0;
  data->srcBuffer = NULL;
  // data->extraSize = 0;
  uint32_t extraSize = 0;

  {
    // cbf checking for file exhaustion here - just let read calls fail
    // a shortcut to help us
#define READ_ENTRY_MALLOC_AND_READ(s) { \
			extraSize = s; \
			data->extra = malloc(s); \
			if(!rco_fread(rcoH, data->extra, s)) { \
				error("[entry (0x%x)] Unable to read entry extra data - file exhausted.", data->offset); \
				return; \
			} \
		}
		
    switch (data->id) {
      case RCO_TABLE_MAIN:
	if (data->type != 1)
	  warning ("[entry (0x%x)] Unexpected 'main' type (0x%x)!",
	      data->offset, data->type);
	break;			// nothing needs to be done

      case RCO_TABLE_VSMX:
	if (data->type == 1) {
	  RCOVSMXEntry rve;

	  if (!rco_fread (rcoH, &rve, sizeof (rve))) {
	    error
		("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		data->offset);
	    return;
	  }
	  if (rco->eSwap)
	    es_rcoVsmxEntry (&rve);
	  data->srcAddr = rcoread_ftell (rcoH) + rve.offset;
	  data->srcLen = data->srcLenUnpacked = rve.length;
	  strcpy (data->srcFile, rcoH->fName);
	  // need to consider possibility that VSMX table is compressed inside
	  // compressed RCO header
	  data->srcCompression =
	      (rcoH->
	      tables ? RCO_DATA_COMPRESSION_RCO : RCO_DATA_COMPRESSION_NONE);

	  extraSize = sizeof (RCOVSMXEntry) + rve.length;
	  // 4 byte alignment
	  extraSize = ALIGN_TO_4 (extraSize);
	  rcoread_fseek (rcoH,
	      rcoread_ftell (rcoH) + extraSize - sizeof (RCOVSMXEntry));
	} else
	  warning ("[entry (0x%x)] Unknown VSMX type (0x%x)!", data->offset,
	      data->type);

	break;

      case RCO_TABLE_TEXT:
	if (data->type == 1) {
	  RCOTextEntry rte;
	  rRCOTextEntry *dest;

	  data->extraLen = sizeof (rRCOTextEntry);
	  data->extra = malloc (data->extraLen);
	  dest = (rRCOTextEntry *) data->extra;
	  if (!rco_fread (rcoH, &rte, sizeof (rte))) {
	    error
		("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		data->offset);
	    return;
	  }
	  if (rco->eSwap)
	    es_rcoTextEntry (&rte);

	  dest->lang = rte.lang;
	  dest->format = rte.format;
	  if (rte.format != RCO_TEXT_FMT_UTF8 &&
	      rte.format != RCO_TEXT_FMT_UTF16 &&
	      rte.format != RCO_TEXT_FMT_UTF32) {
	    warning ("[entry (0x%x)] Unknown format for text entry (0x%x)",
		data->offset, rte.format);
	  }
	  dest->numIndexes = rte.numIndexes;

	  // alloc & read indexes
	  if (dest->numIndexes > MAX_SUBENTRIES) {
	    warning
		("[entry (0x%x)] Number of text indexes (0x%x) exceeds safety limit.",
		data->offset, ((rRCOTextEntry *) data->extra)->numIndexes);
	    dest->numIndexes = MAX_SUBENTRIES;
	  }
	  uint32_t readAmt = dest->numIndexes * sizeof (RCOTextIndex);

	  extraSize = sizeof (RCOTextEntry) + readAmt;
	  dest->indexes = (RCOTextIndex *) malloc (readAmt);
	  if (!rco_fread (rcoH, dest->indexes, readAmt)) {
	    error
		("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		data->offset);
	    return;
	  }
	  if (rco->eSwap) {	// endian swap all indexes
	    uint32_t i;

	    for (i = 0; i < dest->numIndexes; i++)
	      es_rcoTextIndex (dest->indexes + i);
	  }

	  strcpy (data->srcFile, rcoH->fName);
	  // special case for text - source address/length must be updated
	  // later

	} else if (data->type != 0)
	  warning ("[entry (0x%x)] Unknown text type (0x%x)!", data->offset,
	      data->type);
	break;

      case RCO_TABLE_IMG:
      case RCO_TABLE_MODEL:
	if (data->type == 1) {
	  RCOImgModelEntry rie;
	  uint32_t rimeSize =
	      (rco->
	      ps3 ? sizeof (RCOPS3ImgModelEntry) : sizeof (RCOImgModelEntry));
	  uint16_t compression;

	  extraSize = rimeSize;

	  // check for those certain entries which aren't compressed and don't
	  // have a packed size value
	  // urgh, this is a bit of an ugly hack - these short entries are
	  // something I didn't know about before :/

	  if (rco_fread (rcoH, &rie, sizeof (uint32_t))) {
	    compression = rie.compression;
	    if (rco->eSwap)
	      compression = ENDIAN_SWAP (compression);
	    compression &= 0xFF;
	    if (compression == RCO_DATA_COMPRESSION_NONE) {
	      // assume that this doesn't include the packed length value
	      // ...but we'll still at least _try_ to see if this isn't a short
	      //
	      // entry (not guaranteed to succeed, especially for the last
	      // image entry)
	      if (!re.nextEntryOffset ||
		  re.nextEntryOffset < sizeof (RCOEntry) + rimeSize)
		extraSize -= sizeof (uint32_t);
	    }
	  } else {
	    error
		("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		data->offset);
	    return;
	  }

	  if (rco->ps3) {
	    if (!rco_fread (rcoH, (uint8_t *) (&rie) + sizeof (uint32_t),
		    sizeof (uint32_t) * 3)) {
	      error
		  ("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		  data->offset);
	      return;
	    }
	    if (rie.sizeUnpacked != 1)
	      warning
		  ("[entry (0x%x)] Unexpected value 0x%x for PS3 image - expected 0x1.",
		  data->offset, ENDIAN_SWAP (rie.sizeUnpacked));
	    rie.sizeUnpacked = rie.sizePacked;
	    if (compression) {
	      rco_fread (rcoH, &rie.sizeUnpacked, sizeof (uint32_t));
	    }
	  } else if (!rco_fread (rcoH, (uint8_t *) (&rie) + sizeof (uint32_t),
		  extraSize - sizeof (uint32_t))) {
	    error
		("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		data->offset);
	    return;
	  }

	  /*
	   * // dirty hack for reading PS3 stuff if(rco->ps3 && extraSize ==
	   * rimeSize) extraSize -= sizeof(uint32_t);
	   *
	   * if(!rco_fread(rcoH, (uint8_t*)(&rie) +sizeof(uint32_t), extraSize -
	   * sizeof(uint32_t))) { error("[entry (0x%x)] Unable to read entry
	   * extra data - file exhausted.", data->offset); return; }
	   * if(rco->ps3 && rie.sizeUnpacked != ENDIAN_SWAP_32(1))
	   * warning("[entry (0x%x)] Unexpected value 0x%x for PS3 image -
	   * expected 0x1.", data->offset, ENDIAN_SWAP(rie.sizeUnpacked));
	   * if(rco->ps3 && compression && extraSize + sizeof(uint32_t) ==
	   * rimeSize) { extraSize += sizeof(uint32_t); rco_fread(rcoH,
	   * &rie.sizeUnpacked, sizeof(uint32_t)); // TODO: (fix this?) ignore
	   * the weird unknown entry for now } */
	  if (rco->eSwap)
	    es_rcoImgModelEntry (&rie);

	  if (rimeSize != extraSize) {
	    // no packed size value
	    rie.sizeUnpacked = rie.sizePacked;
	  }
	  strcpy (data->srcFile, rcoH->fName);
	  data->srcAddr = rie.offset;
	  data->srcLen = rie.sizePacked;
	  data->srcLenUnpacked = rie.sizeUnpacked;
	  data->srcCompression = rie.compression & 0xFF;

	  data->extraLen = sizeof (rRCOImgModelEntry);
	  data->extra = malloc (data->extraLen);
	  ((rRCOImgModelEntry *) data->extra)->format = rie.format;
	  ((rRCOImgModelEntry *) data->extra)->compression =
	      rie.compression & 0xFF;
	  ((rRCOImgModelEntry *) data->extra)->unkCompr = rie.compression >> 8;
	} else if (data->type != 0)
	  warning ("[entry (0x%x)] Unknown image/model type (0x%x)!",
	      data->offset, data->type);
	break;

      case RCO_TABLE_SOUND:
	if (data->type == 1) {
	  RCOSoundEntry rse;

	  extraSize = sizeof (RCOSoundEntry);
	  if (!rco_fread (rcoH, &rse, extraSize)) {
	    error
		("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		data->offset);
	    return;
	  }
	  if (rco->eSwap)
	    es_rcoSoundEntry (&rse);
	  strcpy (data->srcFile, rcoH->fName);
	  data->srcAddr = rse.offset;
	  data->srcLenUnpacked = data->srcLen = rse.sizeTotal;
	  data->srcCompression = RCO_DATA_COMPRESSION_NONE;

	  // data->extraSize = sizeof(rRCOSoundEntry);
	  data->extra = malloc (sizeof (rRCOSoundEntry));
	  ((rRCOSoundEntry *) data->extra)->format = rse.format;
	  ((rRCOSoundEntry *) data->extra)->channels = rse.channels;
	  // alloc & read channels (max = 65535, so don't bother checking)
	  uint32_t readAmt = rse.channels * 2 * sizeof (uint32_t);

	  extraSize = sizeof (RCOSoundEntry) + readAmt;
	  ((rRCOSoundEntry *) data->extra)->channelData =
	      (uint32_t *) malloc (readAmt);
	  if (!rco_fread (rcoH, ((rRCOSoundEntry *) data->extra)->channelData,
		  readAmt)) {
	    error
		("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		data->offset);
	    return;
	  }
	  uint32_t i;

	  if (rco->eSwap) {
	    uint32_t *cd = ((rRCOSoundEntry *) data->extra)->channelData;

	    for (i = 0; i < (uint32_t) rse.channels * 2; i++)
	      cd[i] = ENDIAN_SWAP (cd[i]);
	  }
	  // make offsets relative
	  for (i = 0; i < rse.channels; i++)
	    ((rRCOSoundEntry *) data->extra)->channelData[i * 2 + 1] -=
		rse.offset;

	  if (rse.channels < 2) {
	    // check if we need to skip some stuff
	    // AMENDMENT: actually, it seems that there _must_ be two channels
	    // defined (no clear indication of size otherwise)
	    for (i = rse.channels; i < 2; i++) {
	      struct {
		uint32_t size;
		uint32_t offset;
	      } p;

	      // not sure if there's padding, so just read things one by one
	      rco_fread (rcoH, &(p.size), sizeof (uint32_t));
	      rco_fread (rcoH, &(p.offset), sizeof (uint32_t));
	      if (p.size || p.offset != RCO_NULL_PTR)
		warning
		    ("[entry (0x%x)] Unexpected values found in sound entry data where null channels were expected.",
		    data->offset);

	      extraSize += sizeof (uint32_t) * 2;
	    }
	  }
	} else if (data->type != 0)
	  warning ("[entry (0x%x)] Unknown sound type (0x%x)!", data->offset,
	      data->type);
	break;

      case RCO_TABLE_FONT:
	if (data->type == 1) {
	  RCOFontEntry rfe;

	  if (!rco_fread (rcoH, &rfe, sizeof (rfe))) {
	    error
		("[entry (0x%x)] Unable to read entry extra data - file exhausted.",
		data->offset);
	    return;
	  }
	  if (rco->eSwap)
	    es_rcoFontEntry (&rfe);
	  extraSize = sizeof (rfe);

	  data->extraLen = sizeof (rRCOFontEntry);
	  data->extra = malloc (data->extraLen);
	  rRCOFontEntry *drfe = (rRCOFontEntry *) (data->extra);

	  drfe->format = rfe.format;
	  drfe->compression = rfe.compression;
	  drfe->unknown = rfe.unknown;
	  drfe->unknown2 = rfe.unknown2;

	} else if (data->type != 0)
	  warning ("[entry (0x%x)] Unknown Font type (0x%x)!", data->offset,
	      data->type);

	break;

      case RCO_TABLE_OBJ:
	if (data->type > 0) {
	  uint32_t entrySize = 0;

	  // determine size of entry from object type
	  if (data->type <= (int) RCO_OBJ_EXTRA_LEN_NUM &&
	      RCO_OBJ_EXTRA_LEN[data->type] != -1) {
	    entrySize = RCO_OBJ_EXTRA_LEN[data->type] * 4;
	  } else
	    warning ("[entry (0x%x)] Unknown object type (0x%x)!", data->offset,
		data->type);

	  if (re.entrySize) {
	    if (entrySize) {
	      if (entrySize != re.entrySize - sizeof (re))
		warning
		    ("[entry (0x%x)] Entry length does not match standard length for this type of object!",
		    data->offset);
	    }
	    entrySize = re.entrySize - sizeof (re);
	  } else {
	    // TODO: check pointer table for entrySize
	  }

	  if (entrySize) {
	    READ_ENTRY_MALLOC_AND_READ (entrySize);
	    if (rco->eSwap)
	      es_extraObjAnim (TRUE, data->type, data->extra, rco->ps3);
	  } else {
	    error ("[entry (0x%x)] Unable to determine object entry length!",
		data->offset);
	    return;
	  }
	}
	data->extraLen = extraSize;
	break;

      case RCO_TABLE_ANIM:
	if (data->type > 1) {
	  uint32_t entrySize = 0;

	  // determine size of entry from anim type
	  if (data->type <= RCO_ANIM_EXTRA_LEN_NUM &&
	      RCO_ANIM_EXTRA_LEN[data->type] != -1)
	    entrySize = RCO_ANIM_EXTRA_LEN[data->type] * 4;
	  else
	    warning ("[entry (0x%x)] Unknown animation type (0x%x)!",
		data->offset, data->type);

	  if (re.nextEntryOffset) {
	    if (entrySize) {
	      if (entrySize != re.nextEntryOffset - sizeof (re))
		warning("[entry (0x%x)] Entry length (%d) does not match standard length (%d) for this type of animation action!",
		    data->offset, (int) (re.nextEntryOffset - sizeof (re)), (int) entrySize);
	    }
	    entrySize = re.nextEntryOffset - sizeof (re);
	  } else {
	    // TODO: check pointer table for entrySize
	  }

	  if (entrySize) {
	    READ_ENTRY_MALLOC_AND_READ (entrySize);
	    if (rco->eSwap)
	      es_extraObjAnim (FALSE, data->type, data->extra, rco->ps3);
	  } else {
	    error ("[entry (0x%x)] Unable to determine anim entry length!",
		data->offset);
	    return;
	  }
	}
	data->extraLen = extraSize;
	break;

      default:
	warning ("[entry (0x%x)] Unknown entry type (0x%x)", data->offset, data->id);
    }

  }

  // process subentries
  if (readSubEntries && data->numSubentries) {
    uint32_t i;

    if (data->numSubentries > MAX_SUBENTRIES) {
      warning
	  ("[entry (0x%x)] Number of subentries (%d) exceeds safety limit of 65536!",
	  data->offset, data->numSubentries);
      data->numSubentries = MAX_SUBENTRIES;
    }

    uint32_t curFPos = data->offset + sizeof (re) + extraSize;
    rRCOEntry *rcoNode = (rRCOEntry *) malloc (sizeof (rRCOEntry));

    data->firstChild = rcoNode;
    for (i = 0; i < data->numSubentries; i++) {
      read_entry (rcoH, rco, rcoNode, readSubEntries);
      rcoNode->parent = data;
      if (i + 1 < data->numSubentries) {
	rcoNode->next = (rRCOEntry *) malloc (sizeof (rRCOEntry));
	rcoNode->next->prev = rcoNode;
	rcoNode = rcoNode->next;
      } else			// is last node
	data->lastChild = rcoNode;
    }
    extraSize += rcoread_ftell (rcoH) - curFPos;
  }
  // check if lengths match - note, last entry in list won't have a next entry
  // offset so will cause a misalignment for the parent
  if (re.nextEntryOffset && re.nextEntryOffset != sizeof (re) + extraSize) {
    warning
	("[entry (0x%x)] Entry boundaries not aligned (going forward %d bytes)",
	data->offset, (int) (re.nextEntryOffset - (sizeof (re) + extraSize)));
    rcoread_fseek (rcoH, data->offset + re.nextEntryOffset);

    // our ugly hack to get around borked update_plugin.rco when decompressed
    // with Resurssiklunssi
    // the issue is that the image isn't compressed by default, so uses a short
    //
    // image entry (ie, doesn't include decompressed size), however
    // Resurssiklunssi will compress it but won't add in this decompressed size
    //
    // since there is no room for it
    // rcomage expects a decompressed size so will assume it exists (no way to
    // tell if it's not there) but this will cause an alignment error for the
    // parent.  The only way to detect this is, thus, trap this alignment error
    //
    // and check the child entry
    // still, we are left without a decompressed size, thus we have to figure
    // out something for this

    // we'll do this by seeing if the misalignment is -4 and the previous entry
    //
    // is a compressed image/model; if there are child entries, we'll check
    // this instead of the previous entry
    // obviously this isn't guaranteed to work in 100% of cases, but will get
    // around the update_plugin.rco bug
    if (re.nextEntryOffset == sizeof (re) + extraSize - 4) {
      if (data->lastChild) {
	if (data->lastChild->srcFile[0]
	    && data->lastChild->srcCompression && data->lastChild->type == 1 &&
	    (data->lastChild->id == RCO_TABLE_IMG ||
		data->lastChild->id == RCO_TABLE_MODEL)) {
	  // looks like we need a fix
	  data->lastChild->srcLenUnpacked = 0xFFFFFFFF;
	}
      }

    } else {
      // TODO: figure out something for looking at previous entry
    }
  }
}

// linear/recursive search - not the fastest, but eh, performance isn't that
// much of an issue
rRCOEntry *
find_entry_from_offset (rRCOEntry * parent, uint32_t offset)
{
  if (parent->offset == offset)
    return parent;

  rRCOEntry *rcoNode;

  for (rcoNode = parent->firstChild; rcoNode; rcoNode = rcoNode->next) {
    rRCOEntry *f = find_entry_from_offset (rcoNode, offset);

    if (f)
      return f;
  }

  return NULL;			// not found
}

void
fix_refs (rRCOFile * rco, rRCOEntry * entry, const int *lenArray,
    const uint32_t lenNum, uint8_t isObj)
{
  uint32_t i, i2;

  // only fix refs if type is known, and not the main object(0x800)/anim(0x900)
  //
  // table
  if (entry->type != 0 && entry->type <= (int) lenNum &&
      lenArray[entry->type] != -1) {

    uint32_t destSize = lenArray[entry->type] * sizeof (uint32_t);

    if (isObj) {
      for (i = 0, i2 = 0; i < (uint32_t) RCO_OBJ_EXTRA_LEN[entry->type];
	  i++, i2++)
	if (RCO_OBJ_IS_REF (entry->type, i2)) {
	  destSize -= sizeof (uint32_t) * 2;	// size of ref source
	  destSize += sizeof (rRCORef);
	  i++;
	}
    } else {
      /* if(RCO_ANIM_EXTRA_REFS[entry->type]) { destSize -= sizeof(uint32_t)*2;
       * // size of ref source destSize += sizeof(rRCORef); } */
      for (i = 0, i2 = 0; i < (uint32_t) RCO_ANIM_EXTRA_LEN[entry->type];
	  i++, i2++)
	if (RCO_ANIM_IS_REF (entry->type, i2)) {
	  destSize -= sizeof (uint32_t) * 2;	// size of ref source
	  destSize += sizeof (rRCORef);
	  i++;
	}
    }

    void *dest = malloc (destSize);
    uint8_t *destPtr = (uint8_t *) dest;

    for (i = 0, i2 = 0; i < (uint32_t) lenArray[entry->type]; i++, i2++) {
      uint8_t cond;

      if (isObj)
	cond = (RCO_OBJ_IS_REF (entry->type, i2));
      else			// anim
	cond = (RCO_ANIM_IS_REF (entry->type, i2));
      // cond = (RCO_ANIM_EXTRA_REFS[entry->type] && i == 0);
      if (cond) {
	RCOReference *ref = (RCOReference *) ((uint8_t *) entry->extra + i * 4);
	rRCORef *newRef = (rRCORef *) destPtr;

	newRef->type = ref->type;
	newRef->ptr = NULL;
	newRef->rawPtr = ref->ptr;
	// check for types
	ref->type = ENDIAN_SWAP_32(ref->type);
	ref->type = ENDIAN_SWAP_16(ref->type);
	
	switch (ref->type) {
	  case RCO_REF_EVENT:
	    if (ref->ptr < rco->eventsLen)
	      newRef->ptr = rco->events + ref->ptr;
	    else
	      warning ("[entry (0x%x)] Invalid event pointer.", entry->offset);
	    break;
	  case RCO_REF_TEXT:
	    // just rely on the raw pointer
	    // TODO: because of the above, we should probably check that all
	    // the labels for all text data are the same (though this app will
	    // work fine without it, except for XML writing/reading)
	    break;
	  case RCO_REF_IMG:
	  case RCO_REF_MODEL:
	  case RCO_REF_FONT:
	  case RCO_REF_OBJ2:
	  case RCO_REF_ANIM:
	  case RCO_REF_OBJ:
	    // TODO: consider only searching specific sections instead of the
	    // entire table
	    newRef->ptr = find_entry_from_offset (&(rco->tblMain), ref->ptr);
	    if (!newRef->ptr)
	      warning
		  ("[entry (0x%x)] Unable to find referenced entry from supplied pointer.",
		  entry->offset);
	    break;
	  case RCO_REF_NONE:
	    if (ref->ptr != RCO_NULL_PTR)
	      warning
		  ("[entry (0x%x)] Unexpected pointer value for null pointer (expected 0xFFFFFFFF but got 0x%x).",
		  entry->offset, ref->ptr);
	    break;
	  default:
	    warning ("[entry (0x%x)] Unknown reference type 0x%x.",
		entry->offset, ref->type);
	}
	i++;
	destPtr += sizeof (rRCORef);
      } else {
	*(uint32_t *) destPtr =
	    *(uint32_t *) ((uint8_t *) entry->extra + i * 4);
	destPtr += sizeof (uint32_t);
      }
    }

    free (entry->extra);
    entry->extra = dest;
  }
  // recurse down to other objects
  rRCOEntry *rcoNode;

  for (rcoNode = entry->firstChild; rcoNode; rcoNode = rcoNode->next)
    fix_refs (rco, rcoNode, lenArray, lenNum, isObj);
}

uint8_t
check_file_region (uint32_t fSize, uint32_t offset, uint32_t size)
{
  if (offset + size > fSize)
    return FALSE;
  // TODO: add declared section to list

  return TRUE;
}

// wrapper file functions, but can read from memory
uint32_t
rco_fread (rRCOFile_readhelper * rcoH, void *buf, uint32_t len)
{
  if (rcoH->tablesSize) {
    if (rcoH->memPos + len > rcoH->tablesSize)
      len = rcoH->tablesSize - rcoH->memPos;
    memcpy (buf, ((uint8_t *) rcoH->tables) + rcoH->memPos, len);

    rcoH->memPos += len;
    return len;
  } else {
    // regular file read
    return fileread (rcoH->fp, buf, len);
  }
}

uint32_t
rcoread_ftell (rRCOFile_readhelper * rcoH)
{
  if (rcoH->tablesSize) {
    return rcoH->memOffset + rcoH->memPos;
  } else {
    return ftell (rcoH->fp);
  }
}

int
rcoread_fseek (rRCOFile_readhelper * rcoH, uint32_t pos)
{
  if (rcoH->tablesSize) {
    if (pos < rcoH->memOffset || pos - rcoH->memOffset > rcoH->tablesSize)
      return -1;
    rcoH->memPos = pos - rcoH->memOffset;
    return 0;
  } else {
    return fseek (rcoH->fp, pos, SEEK_SET);
  }
}
