/*
 * rcomain.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#include <stdlib.h>
#include <string.h>
#include "rcomain.h"

uint8_t suppressDecompWarnings = FALSE;

void
free_rco (rRCOFile * f)
{

  // TODO: this function

  free (f);
}

void
rco_map_func (rRCOFile * rco, rRCOEntry * parent, void *arg,
    void (*func) (rRCOFile * rco, rRCOEntry * entry, void *arg))
{
  rRCOEntry *rcoNode;

  if (!parent)
    parent = &rco->tblMain;
  func (rco, parent, arg);
  for (rcoNode = parent->firstChild; rcoNode; rcoNode = rcoNode->next)
    rco_map_func (rco, rcoNode, arg, func);
}

char *
get_label_from_offset (char *labels, uint32_t labelOffset)
{
  static char labelBuf[255];

  if (labelOffset)
    return labels + labelOffset;
  else {
    sprintf (labelBuf, "No Label");
    return labelBuf;
  }
}

/*
 * rRCOEntry* rco_add_entry(rRCOEntry* parent, rRCOEntry* newEntry, int pos) {
 * rRCOEntry* dest; if(pos != -1 && pos > (int)(parent->numSubentries)) return
 * NULL;
 *
 * if(!parent->numSubentries) { parent->subentries =
 * (rRCOEntry*)malloc(sizeof(rRCOEntry)); dest = parent->subentries; } else {
 * parent->subentries = (rRCOEntry*)realloc(parent->subentries,
 * sizeof(rRCOEntry) * (parent->numSubentries+1)); if(pos == -1) dest =
 * &(parent->subentries[parent->numSubentries]); else { // shift things up by
 * one place dest = &(parent->subentries[pos]); uint32_t numEntriesToMove =
 * parent->numSubentries - pos; //rRCOEntry* tmpBuffer = (rRCOEntry*)malloc()
 * memcpy(&(parent->subentries[pos+1]), &(parent->subentries[pos]),
 * numEntriesToMove * sizeof(rRCOEntry)); } }
 *
 * parent->numSubentries++; memcpy(dest, newEntry, sizeof(rRCOEntry));
 *
 * return dest; } */

// parses an RCO (give it the main entry) to fix any resource which is
// compressed, but uncompressed size is unknown
// *new* actually, now will check decompressed size of all compressed resources
void rco_fix_decomp_sizes (rRCOFile * rco, rRCOEntry * entry)
{
  if (entry->srcFile[0] && entry->srcCompression) {
    if (entry->srcCompression == RCO_DATA_COMPRESSION_ZLIB) {
      // read and stuff
      FILE *fp = fopen (entry->srcFile, "rb");

      if (fp) {
	char *inBuf = (char *) malloc (entry->srcLen);

	fseek (fp, entry->srcAddr, SEEK_SET);
	fileread (fp, inBuf, entry->srcLen);
	fclose (fp);

	uint32_t unpackedLen = zlib_unpacked_size (inBuf, entry->srcLen);

	if (unpackedLen != 0xFFFFFFFF) {
	  if (entry->srcLenUnpacked != 0xFFFFFFFF &&  unpackedLen != entry->srcLenUnpacked) {
			warning("Specified uncompressed size for entry '%s' is incorrect.", rco->labels + entry->labelOffset);
			warning("Specified length = %lX, actual length = %lX",  entry->srcLenUnpacked, unpackedLen);
	  }
	  entry->srcLenUnpacked = unpackedLen;
	}
	free (inBuf);
      }
    }

    if (entry->srcLenUnpacked == 0xFFFFFFFF) {
      warning
	  ("Uncompressed size for entry '%s' not specified and cannot be automatically determined!  Setting size to 0.",
	  rco->labels + entry->labelOffset);
      entry->srcLenUnpacked = 0;
    }
  }

  rRCOEntry *rcoNode;

  for (rcoNode = entry->firstChild; rcoNode; rcoNode = rcoNode->next)
    rco_fix_decomp_sizes (rco, rcoNode);
}

void *
read_resource (rRCOEntry * entry, uint32_t * outLen)
{
  char *bufferMid;

  if ((!entry->srcFile[0] || strchr (entry->srcFile, '*'))
      && entry->srcBuffer) {
    // this entry should be a sound/text entry (we assume this)
    // also entry->srcAddr should be 0, and entry->srcLen ==
    // entry->srcLenUnpacked should be true (and equal the length of the
    // buffer), _and_ entry->srcCompression should be NONE
    bufferMid = (char *) malloc (entry->srcLen);
    char *bufferPos = (char *) entry->srcBuffer + entry->srcAddr;

    memcpy (bufferMid, bufferPos, entry->srcLen);
    *outLen = entry->srcLen;
  } else {
    FILE *src = fopen (entry->srcFile, "rb");

    if (!src) {
      warning ("Unable to open file '%s'.", entry->srcFile);
      return NULL;
    }

    if (entry->srcCompression == RCO_DATA_COMPRESSION_RCO) {
      // special case where stuff is embedded in RCO - this should only be used
      //
      // with VSMX, so we'll take a short cut here, but:
      // TODO: do some extra checks to enforce the above

      // we assume it's in the tables section (otherwise, there's no point in
      // referencing an RCO
      if (entry->srcAddr < sizeof (PRFHeader))
	return NULL;
      PRFHeader header;
      uint8_t eSwap;

      fileread (src, &header, sizeof (header));
      eSwap = (header.signature == ENDIAN_SWAP_32(RCO_SIGNATURE));
      if (eSwap)
	es_rcoHeader (&header);
      if (header.compression >> 4) {
	HeaderComprInfo hci;

	fileread (src, &hci, sizeof (hci));
	if (eSwap)
	  es_headerComprInfo (&hci);

	// check if the entry _does_ exist in the RCO tree structure
	if (!(entry->srcAddr >= sizeof (header)
		&& entry->srcAddr < sizeof (header) + hci.lenUnpacked &&
		entry->srcAddr + entry->srcLen <=
		sizeof (header) + hci.lenUnpacked))
	  return NULL;

	char *bufferIn = (char *) malloc (hci.lenPacked);
	char *bufferInDecomp = (char *) calloc (1, hci.lenUnpacked);

	fileread (src, bufferIn, hci.lenPacked);
	fclose (src);

	if (header.compression >> 4 == RCO_DATA_COMPRESSION_ZLIB) {
	  int uRet = zlib_uncompress (bufferInDecomp, hci.lenUnpacked,
	      bufferIn, hci.lenPacked);

	  if (uRet != Z_OK && uRet != Z_DATA_ERROR) {
	    free (bufferIn);
	    free (bufferInDecomp);
	    return NULL;
	  } else if (uRet == Z_DATA_ERROR && !suppressDecompWarnings) {
	    warning ("Encountered 'data error' when decompressing resource.");
	  }
	  free (bufferIn);

	  bufferMid = (char *) malloc (entry->srcLenUnpacked);
	  memcpy (bufferMid, bufferInDecomp + entry->srcAddr - sizeof (header),
	      entry->srcLen);
	  free (bufferInDecomp);

	  *outLen = entry->srcLen;
	} else {
	  free (bufferIn);
	  free (bufferInDecomp);
	  return NULL;
	}
      } else {
	// er, wtf? uncompressed RCO?
	fseek (src, entry->srcAddr, SEEK_SET);
	bufferMid = (char *) malloc (entry->srcLen);
	fileread (src, bufferMid, entry->srcLen);
	fclose (src);
      }

    } else {
      if (entry->srcAddr)
	fseek (src, entry->srcAddr, SEEK_SET);

      // who cares about mem usage ??
      char *bufferIn = (char *) malloc (entry->srcLen);

      fileread (src, bufferIn, entry->srcLen);
      fclose (src);

      if (entry->srcCompression) {
	bufferMid = (char *) calloc (1, entry->srcLenUnpacked);
	if (entry->srcCompression == RCO_DATA_COMPRESSION_ZLIB) {
	  int uRet = zlib_uncompress (bufferMid, entry->srcLenUnpacked,
	      bufferIn, entry->srcLen);

	  if (uRet != Z_OK && uRet != Z_DATA_ERROR) {
	    free (bufferIn);
	    free (bufferMid);
	    return NULL;
	  } else if (uRet == Z_DATA_ERROR && !suppressDecompWarnings) {
	    warning ("Encountered 'data error' when decompressing resource.");
	  }
	  free (bufferIn);
	  *outLen = entry->srcLenUnpacked;
	} else if (entry->srcCompression == RCO_DATA_COMPRESSION_RLZ) {
	  warning
	      ("RLZ decompression not supported - data will be left uncompressed.");
	  bufferMid = bufferIn;
	  *outLen = entry->srcLen;
	} else {
	  // unknown compression
	  free (bufferIn);
	  free (bufferMid);
	  return NULL;
	}
      } else {
	bufferMid = bufferIn;
	// entry->srcLenUnpacked == entry->srcLen SHOULD BE TRUE HERE (we
	// assume this)
	*outLen = entry->srcLen;
      }
    }
  }
  return bufferMid;
}

uint32_t
count_all_subentries (rRCOEntry * entry)
{
  uint32_t entries = entry->numSubentries;
  rRCOEntry *rcoNode;

  for (rcoNode = entry->firstChild; rcoNode; rcoNode = rcoNode->next)
    entries += count_all_subentries (rcoNode);
  return entries;
}

rRCOEntry **
make_sorted_list_of_subentries (rRCOEntry * parent,
    int (*compar) (const rRCOEntry **, const rRCOEntry **))
{

  rRCOEntry **children =
      (rRCOEntry **) malloc (parent->numSubentries * sizeof (rRCOEntry *));
  children[0] = parent->firstChild;
  uint32_t i;

  for (i = 1; i < parent->numSubentries; i++)
    children[i] = children[i - 1]->next;

  qsort (children, parent->numSubentries, sizeof (rRCOEntry *),
      (int (*)(const void *, const void *)) compar);
  return children;
}

rRCOEntry *
find_entry_from_label (rRCOEntry * parent, const char *s)
{
  if (parent->labelOffset != RCO_NULL_PTR &&
      !strcmp (parent->labelOffset + parent->rco->labels, s))
    return parent;

  rRCOEntry *rcoNode;

  for (rcoNode = parent->firstChild; rcoNode; rcoNode = rcoNode->next) {
    rRCOEntry *res;

    if ((res = find_entry_from_label (rcoNode, s)))
      return res;
  }

  return NULL;
}

// returns -1 if not found
int
find_text_from_label (char *labels, rRCOTextEntry * textExtra, const char *s)
{
  if (!textExtra->numIndexes)
    return -1;

  uint32_t i;

  for (i = 0; i < textExtra->numIndexes; i++) {
    if (!strcmp (labels + textExtra->indexes[i].labelOffset, s))
      return i;
  }
  return -1;
}

void
make_iconv_charset (char out[8], int fmt, uint8_t es)
{
  strcpy (out, "ucs-2le");
  if (es)
    out[5] = 'b';		// big endian
  if (fmt == RCO_TEXT_FMT_UTF32)
    out[4] = '4';
  if (fmt == RCO_TEXT_FMT_UTF8) {
    out[1] = 't';
    out[2] = 'f';
    out[4] = '8';
    out[5] = '\0';
  }
}

// Endian swap functions

void
es_rRCOEntry(rRCOEntry *e)
{
  e->labelOffset = ENDIAN_SWAP (e->labelOffset);
  e->offset = ENDIAN_SWAP (e->offset);
  e->numSubentries = ENDIAN_SWAP (e->numSubentries);
  e->extraLen = ENDIAN_SWAP (e->extraLen);
  e->srcAddr = ENDIAN_SWAP (e->srcAddr);
  e->srcLen = ENDIAN_SWAP (e->srcLen);
  e->srcLenUnpacked = ENDIAN_SWAP (e->srcLenUnpacked);
  e->srcCompression = ENDIAN_SWAP (e->srcCompression);
}

void
es_rcoHeader (PRFHeader * h)
{
  h->signature = ENDIAN_SWAP (h->signature);
  h->version = ENDIAN_SWAP (h->version);
  h->compression = ENDIAN_SWAP (h->compression);
  h->pMainTable = ENDIAN_SWAP (h->pMainTable);
  h->pVSMXTable = ENDIAN_SWAP (h->pVSMXTable);
  h->pTextTable = ENDIAN_SWAP (h->pTextTable);
  h->pSoundTable = ENDIAN_SWAP (h->pSoundTable);
  h->pModelTable = ENDIAN_SWAP (h->pModelTable);
  h->pImgTable = ENDIAN_SWAP (h->pImgTable);
  h->pUnknown = ENDIAN_SWAP (h->pUnknown);
  h->pFontTable = ENDIAN_SWAP (h->pFontTable);
  h->pObjTable = ENDIAN_SWAP (h->pObjTable);
  h->pAnimTable = ENDIAN_SWAP (h->pAnimTable);
  h->pTextData = ENDIAN_SWAP (h->pTextData);
  h->lTextData = ENDIAN_SWAP (h->lTextData);
  h->pLabelData = ENDIAN_SWAP (h->pLabelData);
  h->lLabelData = ENDIAN_SWAP (h->lLabelData);
  h->pEventData = ENDIAN_SWAP (h->pEventData);
  h->lEventData = ENDIAN_SWAP (h->lEventData);
  h->pTextPtrs = ENDIAN_SWAP (h->pTextPtrs);
  h->lTextPtrs = ENDIAN_SWAP (h->lTextPtrs);
  h->pImgPtrs = ENDIAN_SWAP (h->pImgPtrs);
  h->lImgPtrs = ENDIAN_SWAP (h->lImgPtrs);
  h->pModelPtrs = ENDIAN_SWAP (h->pModelPtrs);
  h->lModelPtrs = ENDIAN_SWAP (h->lModelPtrs);
  h->pSoundPtrs = ENDIAN_SWAP (h->pSoundPtrs);
  h->lSoundPtrs = ENDIAN_SWAP (h->lSoundPtrs);
  h->pObjPtrs = ENDIAN_SWAP (h->pObjPtrs);
  h->lObjPtrs = ENDIAN_SWAP (h->lObjPtrs);
  h->pAnimPtrs = ENDIAN_SWAP (h->pAnimPtrs);
  h->lAnimPtrs = ENDIAN_SWAP (h->lAnimPtrs);
  h->pImgData = ENDIAN_SWAP (h->pImgData);
  h->lImgData = ENDIAN_SWAP (h->lImgData);
  h->pSoundData = ENDIAN_SWAP (h->pSoundData);
  h->lSoundData = ENDIAN_SWAP (h->lSoundData);
  h->pModelData = ENDIAN_SWAP (h->pModelData);
  h->lModelData = ENDIAN_SWAP (h->lModelData);

}

void
es_rcoEntry (RCOEntry * e)
{
  e->typeId = ENDIAN_SWAP (e->typeId);
  e->blank = ENDIAN_SWAP (e->blank);
  e->labelOffset = ENDIAN_SWAP (e->labelOffset);
  e->eHeadSize = ENDIAN_SWAP (e->eHeadSize);
  e->entrySize = ENDIAN_SWAP (e->entrySize);
  e->numSubentries = ENDIAN_SWAP (e->numSubentries);
  e->nextEntryOffset = ENDIAN_SWAP (e->nextEntryOffset);
  e->prevEntryOffset = ENDIAN_SWAP (e->prevEntryOffset);
  e->parentTblOffset = ENDIAN_SWAP (e->parentTblOffset);
}

void
es_rcoVsmxEntry (RCOVSMXEntry * e)
{
  e->offset = ENDIAN_SWAP (e->offset);
  e->length = ENDIAN_SWAP (e->length);
}

void
es_rcoFontEntry (RCOFontEntry * e)
{
  e->format = ENDIAN_SWAP (e->format);
  e->unknown = ENDIAN_SWAP (e->unknown);
  e->unknown2 = ENDIAN_SWAP (e->unknown2);
}

void
es_rcoTextEntry (RCOTextEntry * e)
{
  e->lang = ENDIAN_SWAP (e->lang);
  e->format = ENDIAN_SWAP (e->format);
  e->numIndexes = ENDIAN_SWAP (e->numIndexes);
}

void
es_rcoTextIndex (RCOTextIndex * i)
{
  i->labelOffset = ENDIAN_SWAP (i->labelOffset);
  i->length = ENDIAN_SWAP (i->length);
  i->offset = ENDIAN_SWAP (i->offset);
}

void
es_rcoImgModelEntry (RCOImgModelEntry * e)
{
  e->format = ENDIAN_SWAP (e->format);
  e->compression = ENDIAN_SWAP (e->compression);
  e->sizePacked = ENDIAN_SWAP (e->sizePacked);
  e->offset = ENDIAN_SWAP (e->offset);
  e->sizeUnpacked = ENDIAN_SWAP (e->sizeUnpacked);
}

void
es_rcoSoundEntry (RCOSoundEntry * e)
{
  e->format = ENDIAN_SWAP (e->format);
  // e->channels = ENDIAN_SWAP(e->channels);
  e->sizeTotal = ENDIAN_SWAP (e->sizeTotal);
  e->offset = ENDIAN_SWAP (e->offset);
}

void
es_headerComprInfo (HeaderComprInfo * hci)
{
  hci->lenPacked = ENDIAN_SWAP (hci->lenPacked);
  hci->lenUnpacked = ENDIAN_SWAP (hci->lenUnpacked);
  hci->lenLongestText = ENDIAN_SWAP (hci->lenLongestText);
}

void
es_textComprInfo (TextComprInfo * tci)
{
  tci->lang = ENDIAN_SWAP (tci->lang);
  tci->unknown = ENDIAN_SWAP (tci->unknown);
  tci->nextOffset = ENDIAN_SWAP (tci->nextOffset);
  tci->packedLen = ENDIAN_SWAP (tci->packedLen);
  tci->unpackedLen = ENDIAN_SWAP (tci->unpackedLen);
}

void
es_extraObjAnim (uint8_t isObj, int type, void *data, uint8_t isPS3)
{
  if (type == 0)
    return;

  uint32_t len = 0;
  const int *typeArray;

  if (isObj && type <= (int) RCO_OBJ_EXTRA_LEN_NUM) {
    len = RCO_OBJ_EXTRA_LEN[type];
    typeArray = RCO_OBJ_EXTRA_TYPES[type];
  } else if (!isObj && type <= (int) RCO_ANIM_EXTRA_LEN_NUM) {
    len = RCO_ANIM_EXTRA_LEN[type];
    typeArray = RCO_ANIM_EXTRA_TYPES[type];
  }

  if (!len)
    return;

  uint32_t i = 0, i2 = 0;
  uint32_t *uData = (uint32_t *) data;

  for (; i < len; i++, i2++) {
    switch (typeArray[i2]) {
      case RCO_OBJ_EXTRA_TYPE_REF:
      case RCO_OBJ_EXTRA_TYPE_EVENT:
      case RCO_OBJ_EXTRA_TYPE_IMG:
      case RCO_OBJ_EXTRA_TYPE_OBJ:
      case RCO_OBJ_EXTRA_TYPE_TEXT:
      case RCO_OBJ_EXTRA_TYPE_MODEL:
      case RCO_OBJ_EXTRA_TYPE_FONT:
	uData[i] = ENDIAN_SWAP_HALF32 (uData[i]);
	uData[i + 1] = ENDIAN_SWAP (uData[i + 1]);
	i++;
	break;

      case RCO_OBJ_EXTRA_TYPE_INT:
      case RCO_OBJ_EXTRA_TYPE_FLOAT:	// floats are also endian swapped...
	uData[i] = ENDIAN_SWAP (uData[i]);
	break;
	// don't do anything for unknown
    }
  }
}
