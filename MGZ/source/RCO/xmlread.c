/*
 * xmlread.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

// TODO: replace xmlstrcmp with strcasecmp

#define LIBXML_STATIC
#include <libxml/parser.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "iconv.h"

#include "rcomain.h"
#include "xml.h"
#include "strfuncs.h"
#include "configscan.h"

#define _XX(s) ((const xmlChar*)s)
#define INTERPRET_AS_FLOAT(n) (*((float*)(&(n))))

#define strtof(a,b) (float)strtod(a,b)

/*
 * typedef struct { rRCORef* ref; char* label; } xmlrco_read_fix_refs; */
typedef struct {
  // xmlChar *ptrText, *ptrImg, *ptrSound, *ptrModel, *ptrObj, *ptrAnim;
  xmlChar *textData;		// labels data, that is
  // xmlrco_read_fix_refs* refs;
  // uint32_t refsCnt;
} rcoxml_read_fixes;

void parse_entry (xmlNodePtr node, rRCOEntry * entry, rRCOFile * rco,
    rcoxml_read_fixes * fixes);
// uint8_t rcoxml_text_to_int(char* s, const RcoTableMap map, uint32_t* out);
uint32_t rcoxml_add_label (char **labels, uint32_t * labelsLen, char *label,
    uint8_t eventQuirk);
uint32_t rcoxml_add_label_reordering (char *newLabels, uint32_t * labelPos,
    char *label);
void rcoxml_reorder_labels (char *newLabels, uint32_t * labelPos,
    rRCOFile * rco, rRCOEntry * entry);
int label_reorder_qsort (const rRCOEntry ** a, const rRCOEntry ** b);
void parse_obj_extra (xmlNodePtr node, rRCOEntry * entry);
void parse_anim_extra (xmlNodePtr node, rRCOEntry * entry);
xmlChar *rcoxml_get_unknown_attrib (xmlNodePtr node, uint32_t num);
uint32_t rcoxml_parse_value (char *s);
uint8_t rcoxml_parse_ref (char *val, rRCORef * out);
void rcoxml_fix_refs (rRCOEntry * entry, rRCOFile * rco);
uint8_t rcoxml_fix_ref (rRCORef * ref, rRCOFile * rco);
void rcoxml_fix_ptrs (rRCOEntry *** sect, uint32_t * sectCnt, rRCOFile * rco,
    const char *text);
uint32_t split_comma_list (char *s);
char *strtrimr (char *in);
char *expand_fname_to_fmt (char *in, char type);
uint8_t parse_text_xml (char *fn, rRCOFile * rco, rRCOEntry * entry);

rRCOFile *
read_xml (char *fn)
{
  xmlDocPtr doc;
  xmlNodePtr node;
  uint8_t bValidDoc = FALSE;

  rcoxml_read_fixes fixes;	// post fixes need to be done

  // fixes.ptrText = fixes.ptrImg = fixes.ptrSound = fixes.ptrModel =
  // fixes.ptrObj = fixes.ptrAnim = NULL;
  fixes.textData = NULL;
  // fixes.refsCnt = 0;
  // fixes.refs = (xmlrco_read_fix_refs*)malloc(1); // dummy malloc to allow
  // realloc to work later on

  // parse from stdin?
  if (!strcmp (fn, "-")) {
    char *buf = NULL;
    int bufsize = 0;

    while (!feof (stdin)) {
      buf = (char *) realloc (buf, bufsize + 65536);
      uint32_t readAmt = fread (buf + bufsize, 1, 65536, stdin);

      if (!readAmt)
	break;
      bufsize += readAmt;
    }
    fclose (stdin);
    if (!(doc = xmlParseMemory (buf, bufsize))) {
      error ("Can't parse given XML data.");
      return NULL;
    }
    free (buf);
  } else {
    if (!(doc = xmlParseFile (fn))) {
      error ("Can't parse given XML file %s.", fn);
      return NULL;
    }
  }
  if ((node = xmlDocGetRootElement (doc)))
    bValidDoc = (xmlStrcmp (node->name, _XX ("RcoFile")) ? FALSE : TRUE);
  if (bValidDoc)
    bValidDoc = (node->xmlChildrenNode ? TRUE : FALSE);

  xmlNodePtr nodeChild;

  if (bValidDoc) {		// valid document must contain at least one
    // thing under RcoFile (MainTree)
    nodeChild = node->xmlChildrenNode;
    while (nodeChild->next && nodeChild->type != XML_ELEMENT_NODE)
      nodeChild = nodeChild->next;
    bValidDoc = (nodeChild->type == XML_ELEMENT_NODE);
  }

  if (!bValidDoc) {
    error ("Invalid XML file.");
    xmlFreeDoc (doc);
    return NULL;
  }

  rRCOFile *rco = (rRCOFile *) malloc (sizeof (rRCOFile));

  rco->labelsLen = rco->eventsLen = 0;
  // rco->numPtrText = rco->numPtrImg = rco->numPtrModel = rco->numPtrSound =
  // rco->numPtrObj = rco->numPtrAnim = 0;
  rco->tblVSMX = rco->tblText = rco->tblImage = rco->tblSound = rco->tblModel =
      rco->tblFont = rco->tblObj = rco->tblAnim = NULL;

  // version id
  rco->verId = 0x71;		// assumed default
  xmlChar *verId = xmlGetProp (node, _XX ("minFirmwareVer"));

  if (verId) {
    uint32_t verIdInt = 0;
    float verIdFlt = 0;

    if (sscanf ((const char *) verId, "unknownId%i", &verIdInt))
      rco->verId = verIdInt;
    else if (!xmlStrcmp (verId, _XX ("ps3")))	// for compatibility
      rco->verId = 0x107;
    else if (sscanf ((const char *) verId, "%f", &verIdFlt)) {
      if (verIdFlt < 1.0) {
	warning ("[line %d] Invalid value for 'minFirmwareVer'.", node->line);
      } else if (verIdFlt < 1.5) {
	rco->verId = 0x70;
      } else if (verIdFlt < 2.6) {
	rco->verId = 0x71;
      } else if (verIdFlt < 2.7) {
	rco->verId = 0x90;
      } else if (verIdFlt < 2.8) {
	rco->verId = 0x95;
      } else if (verIdFlt < 3.5) {
	rco->verId = 0x96;
      } else if (verIdFlt <= 6.2) {
	rco->verId = 0x100;
      } else {
	warning ("[line %d] Unknown ID for firmware version '%f'.", node->line,
	    verIdFlt);
      }
    } else
      warning ("[line %d] Unknown value for 'minFirmwareVer'.", node->line);
    xmlFree (verId);
  }
  // XML version
  xmlChar *xmlVer = xmlGetProp (node, _XX ("rcomageXmlVer"));

  if (xmlVer) {
    float xmlVerFlt;

    if (sscanf ((const char *) xmlVer, "%f", &xmlVerFlt)) {
      if (xmlVerFlt > APPVER)
	warning
	    ("This XML file was generated by a newer version (v%f) of rcomage\nand may not read properly with this version.",
	    xmlVerFlt);
    } else
      warning
	  ("[line %d] Bad value for 'rcomageXmlVer'.\n  So... do you have a reason for fiddling with this?? >_<",
	  node->line);
    xmlFree (xmlVer);
  }

  rco->umdFlag = 0;		// assumed default
  xmlChar *umdFlag = xmlGetProp (node, _XX ("UMDFlag"));

  if (umdFlag) {
    rco->umdFlag = atoi ((char *) umdFlag);
    if (rco->umdFlag > 0xF || rco->umdFlag < 0) {
      warning ("The UMD Flag must be between 0 and 15, defaulting to 0.");
      rco->umdFlag = 0;
    }
    xmlFree (umdFlag);
  }

  rco->ps3 = FALSE;
  xmlChar *ps3Flag = xmlGetProp (node, _XX ("type"));

  if (ps3Flag) {
    if (!xmlStrcmp (ps3Flag, _XX ("ps3")))
      rco->ps3 = TRUE;
    else if (xmlStrcmp (ps3Flag, _XX ("psp")))
      warning ("Unknown type %s", (char *) ps3Flag);
    xmlFree (ps3Flag);
  }
  configLoadObjmap (rco->ps3);
  configLoadAnimmap (rco->ps3);

  // TODO: check is this is correct
  /* rco->labels = (char*)malloc(1); rco->labels[0] = '\0'; rco->events =
   * (char*)malloc(1); rco->events[0] = '\0'; */
  rco->labels = rco->events = NULL;

  rco->eSwap = rco->ps3;

  /*
   * rco->tblMain.id = rco->tblMain.type = 0; rco->tblMain.labelOffset = 0;
   * rco->tblMain.numSubentries = rco->tblMain.extraLen = 0; */

  parse_entry (nodeChild, &(rco->tblMain), rco, &fixes);
  // TODO: ensure the first table _is_ the main table (and possibly then verify
  //
  // tree structure)

  // - post fixes -
  // fix all obj/anim refs
  rcoxml_fix_refs (&(rco->tblMain), rco);

  xmlFreeDoc (doc);

  rco_fix_decomp_sizes (rco, &rco->tblMain);

  // label reordering - really optional, but does help to make RCOs similar to
  // Sony's
  {
    char *newLabels = (char *) malloc (rco->labelsLen);

    memset (newLabels, 0, rco->labelsLen);
    uint32_t labelPos = 0;

    // don't forget to add the main table label :P
    if (rco->tblMain.labelOffset != RCO_NULL_PTR)
      rco->tblMain.labelOffset =
	  rcoxml_add_label_reordering (newLabels, &labelPos,
	  rco->labels + rco->tblMain.labelOffset);

    // we re-order in order of IDs
    uint32_t i;
    rRCOEntry **sList =
	make_sorted_list_of_subentries (&rco->tblMain, label_reorder_qsort);
    for (i = 0; i < rco->tblMain.numSubentries; i++)
      rcoxml_reorder_labels (newLabels, &labelPos, rco, sList[i]);
    free (sList);

    if (labelPos < rco->labelsLen) {
      // error!
      free (newLabels);
    } else {
      free (rco->labels);
      rco->labels = newLabels;
    }
  }

  return rco;
}

void
parse_entry (xmlNodePtr node, rRCOEntry * entry, rRCOFile * rco,
    rcoxml_read_fixes * fixes)
{
  uint32_t i, j;
  uint8_t knownEntryType = TRUE;

  // crap all over the memory in "entry" so we don't screw stuff over later on
  entry->id = entry->type = 0;
  entry->numSubentries = 0;
  entry->rco = rco;
  entry->parent = entry->firstChild = entry->lastChild = entry->prev =
      entry->next = NULL;
  entry->labelOffset = RCO_NULL_PTR;
  entry->extra = NULL;
  entry->extraLen = 0;
  entry->srcFile[0] = '\0';
  entry->srcAddr = entry->srcLen = entry->srcLenUnpacked =
      entry->srcCompression = 0;
  entry->srcBuffer = NULL;

  for (i = 0; i < RCOXML_TABLE_TAGS_NUM; i++) {
    j = 0;
    while (RCOXML_TABLE_TAGS[i][j][0]) {
      if (!xmlStrcmp (node->name, _XX (RCOXML_TABLE_TAGS[i][j]))) {
	entry->id = i;
	entry->type = j;
	break;
      }
      j++;
    }
    if (entry->id)
      break;
  }

  // check unknown type tags
  if (!entry->id) {
    knownEntryType = FALSE;
    if (!sscanf ((const char *) node->name, "Unknown_%i_%i", (int *) &entry->id,
	    (int *) &entry->type)) {
      char tag[RCOXML_TABLE_2ND_DIM + 11];

      for (i = 0; i < RCOXML_TABLE_TAGS_NUM; i++) {
	sprintf (tag, "%sUnknown_%%i", RCOXML_TABLE_NAMES[i]);
	if (sscanf ((const char *) node->name, tag, &entry->type)) {
	  entry->id = i;
	  break;
	}
      }
      if (!entry->id) {
	// since all the known tags have entry->id >0, we can do this
	error ("[line %d] Unknown entry type '%s'", node->line, node->name);
	return ;
      }
    }
  }

  entry->offset = node->line;	// use the line number later on

  {				// label
    xmlChar *label = xmlGetProp (node, _XX ("name"));

    if (label) {
      entry->labelOffset =
	  rcoxml_add_label (&(rco->labels), &(rco->labelsLen), (char *) label,
	  FALSE);
      xmlFree (label);
    }
  }

  if (knownEntryType) {

    // read src (used by section below this, so there is some importance with
    // this ordering)
    {
      xmlChar *src = xmlGetProp (node, _XX ("src"));

      if (src) {
	strcpy (entry->srcFile, (const char *) src);
	xmlFree (src);

	entry->srcCompression = 0;
	src = xmlGetProp (node, _XX ("srcRange"));
	if (src) {
	  // parse src params
	  char compr[50] = "\0";

	  if (sscanf ((const char *) src, "%i-%i%50s", &(entry->srcAddr),
		  &(entry->srcLen), compr) >= 2) {
	    entry->srcLen -= entry->srcAddr;
	    entry->srcLenUnpacked = entry->srcLen;	// default - assume no
	    // compression
	    if (compr[0]) {
	      // TODO: handle situations where uncompressed size is not
	      // specified
	      if (sscanf (compr, ";zlib[%u]", &(entry->srcLenUnpacked)) == 1) {	// TODO:
		//
		// a
		// temporary
		// fix
		// (prolly
		// need
		// to
		// add
		// more
		// compression
		// algos,
		// since
		// sscanf
		// seems
		// to
		// be
		// rather
		// basic
		// in
		// retrieving
		// %s)
		rcoxml_text_to_int ("zlib", RCOXML_TABLE_DATA_COMPRESSION,
		    &(entry->srcCompression));
	      } else if (!strcmp (compr, ";rco")) {
		entry->srcCompression = RCO_DATA_COMPRESSION_RCO;
	      } else {
		warning ("[line %d] Invalid syntax in srcRange", node->line);
	      }
	    }
	  } else
	    warning ("[line %d] Invalid syntax in srcRange", node->line);

	  xmlFree (src);
	} else {
	  entry->srcAddr = 0;
	  entry->srcLen = entry->srcLenUnpacked = filesize (entry->srcFile);	// won't
	  //
	  // work
	  // if
	  // filename
	  // contains
	  // a
	  // '*'
	}
      }
    }

    // extra
#define RCOXML_READ_ATTRIB_AS_INT(nd, name, tbl, dest, undefmsg) { \
			xmlChar* __attr = xmlGetProp(nd, _XX(name)); \
			if(__attr) { \
				if(!rcoxml_text_to_int((char*)__attr, tbl, dest)) { \
					warning("[line %d] Unrecognised value '%s'", nd->line, __attr); \
				} else { \
					xmlFree(__attr); \
				} \
			} else { \
				warning("[line %d] %s", nd->line, undefmsg); \
			} \
		}

    switch (entry->id) {
      case RCO_TABLE_IMG:
      case RCO_TABLE_MODEL:
	if (entry->type == 1) {
	  entry->extraLen = sizeof (rRCOImgModelEntry);
	  entry->extra = malloc (entry->extraLen);
	  // default value
	  ((rRCOImgModelEntry *) entry->extra)->format =
	      (entry->id == RCO_TABLE_IMG ? RCO_IMG_GIM : RCO_MODEL_GMO);
	  ((rRCOImgModelEntry *) entry->extra)->compression =
	      RCO_DATA_COMPRESSION_NONE;

	  if (entry->id == RCO_TABLE_IMG) {
	    RCOXML_READ_ATTRIB_AS_INT (node, "format", RCOXML_TABLE_IMG_FMT,
		&((rRCOImgModelEntry *)
		    entry->extra)->format,
		"No format attribute defined, defaulting to GIM.");
	  } else {
	    RCOXML_READ_ATTRIB_AS_INT (node, "format", RCOXML_TABLE_MODEL_FMT,
		&((rRCOImgModelEntry *)
		    entry->extra)->format,
		"No format attribute defined, defaulting to GMO.");
	  }
	  RCOXML_READ_ATTRIB_AS_INT (node, "compression",
	      RCOXML_TABLE_DATA_COMPRESSION, &((rRCOImgModelEntry *)
		  entry->extra)->compression,
	      "No compression attribute defined, defaulting to 'uncompressed'.");
	  ((rRCOImgModelEntry *) entry->extra)->unkCompr = 0;
	  xmlChar *unk = xmlGetProp (node, _XX ("unknownByte"));

	  if (unk) {
	    sscanf ((const char *) unk, "%i",
		&((rRCOImgModelEntry *) entry->extra)->unkCompr);
	    xmlFree (unk);
	  }
	}
	break;
      case RCO_TABLE_SOUND:
	if (entry->type == 1) {
	  entry->extraLen = sizeof (rRCOSoundEntry);
	  entry->extra = malloc (entry->extraLen);
	  // default value
	  rRCOSoundEntry *se = (rRCOSoundEntry *) entry->extra;

	  se->format = RCO_SOUND_VAG;
	  se->channels = 1;
	  se->channelData = NULL;

	  RCOXML_READ_ATTRIB_AS_INT (node, "format", RCOXML_TABLE_SOUND_FMT,
	      (uint32_t *) & (se->format),
	      "No format attribute defined, defaulting to VAG.");

	  xmlChar *chStr = xmlGetProp (node, _XX ("channels"));
	  uint16_t ch = 0;

	  if (chStr)
	    ch = (uint16_t) strtol ((const char *) chStr, NULL, 10);
	  if (ch > 0)
	    se->channels = ch;
	  else if (!strcasecmp (entry->srcFile + strlen (entry->srcFile) - 4,
		  ".wav")
	      && se->format == RCO_SOUND_VAG)
	    se->channels = 0;	// we have to fix later
	  else
	    warning
		("[line %d] Number of channels either not specified, or no valid value found.",
		node->line);
	  xmlFree (chStr);

	  if (se->channels) {
	    se->channelData =
		(uint32_t *) malloc (se->channels * sizeof (uint32_t) * 2);
	    memset (se->channelData, 0, se->channels * sizeof (uint32_t) * 2);

	    xmlChar *srcPartsX = xmlGetProp (node, _XX ("srcParts"));

	    if (srcPartsX) {
	      char *srcParts = (char *) srcPartsX;
	      uint32_t numParts = split_comma_list (srcParts);

	      if (numParts == se->channels) {
		for (i = 0; i < se->channels; i++) {
		  while (isspace ((int) srcParts[0]))
		    srcParts++;	// skip whitespace
		  strtrimr (srcParts);
		  if (sscanf (srcParts, "%i@%i",
			  (int *) &(se->channelData[i * 2]),
			  (int *) &(se->channelData[i * 2 + 1])) != 2)
		    warning ("[line %d] Invalid syntax for part '%s'",
			node->line, srcParts);
		  srcParts += strlen (srcParts) + 1;
		}
	      } else
		warning
		    ("[line %d] Number of defined parts does not match number of defined sound channels!",
		    node->line);

	      xmlFree (srcPartsX);
	    } else if (strchr (entry->srcFile, '*')) {
	      // check files
	      char *srcFileFmt = expand_fname_to_fmt (entry->srcFile, 'd');

	      // TODO: loop thru each file, record size and add to buffer
	      if (strlen (srcFileFmt) < MAX_FILENAME_LEN) {
		char srcFile[MAX_FILENAME_LEN];
		uint32_t curPos = 0;
		void *srcBufferTmp = malloc (1);

		for (i = 0; i < se->channels; i++) {
		  sprintf (srcFile, srcFileFmt, i);
		  if (file_exists (srcFile)) {
		    se->channelData[i * 2] = filesize (srcFile);
		    if (se->channelData[i * 2]) {
		      // read into srcBuffer
		      FILE *fp = fopen (srcFile, "rb");

		      if (fp) {
			srcBufferTmp =
			    realloc (srcBufferTmp,
			    curPos + ALIGN_TO_4 (se->channelData[i * 2]));
			uint8_t *bufferPos =
			    (uint8_t *) (srcBufferTmp) + curPos;

			fileread (fp, bufferPos, se->channelData[i * 2]);
			fclose (fp);
		      } else
			warning ("[line %d] Can't find or open file '%s'",
			    node->line, srcFile);
		    }
		  } else {
		    se->channelData[i * 2] = 0;
		    warning ("[line %d] Can't find or open file '%s'",
			node->line, srcFile);
		  }
		  se->channelData[i * 2 + 1] = curPos;
		  curPos += ALIGN_TO_4 (se->channelData[i * 2]);
		}
		entry->srcBuffer = srcBufferTmp;
		entry->srcLen = entry->srcLenUnpacked = curPos;
	      }			// else, they're trying to hack us... :/
	      free (srcFileFmt);
	    } else if (se->channels == 1 && entry->srcLen) {
	      // err, if there's just one channel, we can just use the
	      // srcRange, lol
	      se->channelData[0] = entry->srcLen;
	      se->channelData[1] = 0;
	    } else {
	      warning ("[line %d] Cannot determine sizes of sound channels!",
		  node->line);
	    }
	  }

	}
	break;

      case RCO_TABLE_TEXT:
	if (entry->type == 1) {
	  uint8_t xmlInput = FALSE;

	  entry->extraLen = sizeof (rRCOTextEntry);
	  entry->extra = malloc (entry->extraLen);
	  // default value
	  rRCOTextEntry *te = (rRCOTextEntry *) entry->extra;

	  te->lang = 0;
	  te->format = RCO_TEXT_FMT_UTF16;
	  te->numIndexes = 0;

	  RCOXML_READ_ATTRIB_AS_INT (node, "language", RCOXML_TABLE_TEXT_LANG,
	      (uint32_t *) & te->lang,
	      "No language attribute defined - RCO may no longer be valid.");
	  RCOXML_READ_ATTRIB_AS_INT (node, "format", RCOXML_TABLE_TEXT_FMT,
	      (uint32_t *) & te->format,
	      "No destination format defined - assuming UTF16.");

	  if (te->format != RCO_TEXT_FMT_UTF16 && !rco->ps3) {
	    warning ("[line %d] Non UTF-16 text not supported on the PSP.",
		node->line);
	  }
	  // text indexes
	  xmlChar *textEntriesX = xmlGetProp (node, _XX ("entries"));

	  if (textEntriesX) {
	    char *textEntries = (char *) textEntriesX;

	    te->numIndexes = split_comma_list (textEntries);
	    te->indexes =
		(RCOTextIndex *) malloc (te->numIndexes *
		sizeof (RCOTextIndex));
	    memset (te->indexes, 0, te->numIndexes * sizeof (RCOTextIndex));

	    for (i = 0; i < te->numIndexes; i++) {
	      while (isspace ((int)textEntries[0]))
		textEntries++;	// skip whitespace
	      strtrimr (textEntries);
	      te->indexes[i].labelOffset =
		  rcoxml_add_label (&rco->labels, &rco->labelsLen, textEntries,
		  FALSE);
	      textEntries += strlen (textEntries) + 1;
	    }

	    xmlFree (textEntriesX);
	  } else {		// assume XML input
	    if (!(xmlInput = parse_text_xml (entry->srcFile, rco, entry)))
	      warning
		  ("[line %d] Text entries not specified!  Assuming no entries.",
		  node->line);
	  }

	  if (!xmlInput && te->numIndexes) {
	    xmlChar *srcPartsX = xmlGetProp (node, _XX ("srcParts"));

	    if (srcPartsX) {
	      char *srcParts = (char *) srcPartsX;
	      uint32_t numParts = split_comma_list (srcParts);

	      if (numParts == te->numIndexes) {
		for (i = 0; i < te->numIndexes; i++) {
		  while (isspace ((int)srcParts[0]))
		    srcParts++;	// skip whitespace
		  strtrimr (srcParts);
		  if (sscanf (srcParts, "%i@%i",
			  (int *) &(te->indexes[i].length),
			  (int *) &(te->indexes[i].offset)) != 2)
		    warning ("[line %d] Invalid syntax for part '%s'",
			node->line, srcParts);
		  srcParts += strlen (srcParts) + 1;
		}
	      } else
		warning
		    ("[line %d] Number of defined parts does not match number of defined text entries!",
		    node->line);

	      xmlFree (srcPartsX);
	    } else if (strchr (entry->srcFile, '*')) {
	      // check files
	      char *srcFileFmt = expand_fname_to_fmt (entry->srcFile, 's');

	      // loop thru each file, record size and add to buffer
	      if (strlen (srcFileFmt) < MAX_FILENAME_LEN) {
		char srcFile[MAX_FILENAME_LEN];
		uint32_t curPos = 0;
		void *srcBufferTmp = malloc (1);

		for (i = 0; i < te->numIndexes; i++) {
		  sprintf (srcFile, srcFileFmt,
		      rco->labels + te->indexes[i].labelOffset);
		  if (file_exists (srcFile)) {
		    te->indexes[i].length = filesize (srcFile);
		    if (te->indexes[i].length) {
		      // read into srcBuffer
		      FILE *fp = fopen (srcFile, "rb");

		      if (fp) {
			// do we have a BOM?
			unsigned char bom[4] = { 0x80, 0x80, 0x80, 0x80 };	// dummy
			//
			// values
			// that
			// aren't
			// used
			char srcFmt[10] = "", destFmt[8];
			uint32_t bom32le = UTF32_BOM;
			uint32_t bom32be = ENDIAN_SWAP (UTF32_BOM);
			uint16_t bom16le = UTF16_BOM;
			uint16_t bom16be = ENDIAN_SWAP (UTF16_BOM);
			uint32_t bom8 = UTF8_BOM;
			uint32_t bomLen =
			    (te->format ==
			    RCO_TEXT_FMT_UTF32 ? 4 : (te->format ==
				RCO_TEXT_FMT_UTF8 ? 3 : 2));
			make_iconv_charset (destFmt, te->format, rco->eSwap);

			fileread (fp, bom, 4);
			if (!memcmp (bom, &bom32le, sizeof (bom32le))) {
			  strcpy (srcFmt, "utf-32le");
			  bomLen = 4;
			} else if (!memcmp (bom, &bom32be, sizeof (bom32be))) {
			  strcpy (srcFmt, "utf-32be");
			  bomLen = 4;
			} else if (!memcmp (bom, &bom16le, sizeof (bom16le))) {
			  strcpy (srcFmt, "utf-16le");
			  bomLen = 2;
			} else if (!memcmp (bom, &bom16be, sizeof (bom16be))) {
			  strcpy (srcFmt, "utf-16be");
			  bomLen = 2;
			} else if (!memcmp (bom, &bom8, 3)) {
			  strcpy (srcFmt, "utf-8");
			  bomLen = 3;
			} else {	// don't convert
			  strcpy (srcFmt, destFmt);
			  bomLen = 0;
			}

			if (bomLen != 4) {
			  fseek (fp, bomLen, SEEK_SET);
			}
			te->indexes[i].length -= bomLen;

			// re-use BOMlen to specify character width
			bomLen = RCO_TEXT_FMT_CHARWIDTH (te->format);
			srcBufferTmp =
			    realloc (srcBufferTmp,
			    curPos + ALIGN_TO_4 (te->indexes[i].length +
				bomLen));
			uint8_t *bufferPos = (uint8_t *) srcBufferTmp + curPos;

			if (strcmp (srcFmt, destFmt)) {
			  uint32_t fPos = ftell (fp);
			  uint32_t fSize;

			  fseek (fp, 0, SEEK_END);
			  fSize = ftell (fp) - fPos;
			  fseek (fp, fPos, SEEK_SET);

			  uint8_t *fBuf = (uint8_t *) malloc (fSize);

			  fileread (fp, fBuf, fSize);
			  iconv_t ic = iconv_open (destFmt, srcFmt);

			  // get rid of BOM made by iconv
			  iconv (ic, (const char **) (&fBuf), (size_t *) (&fSize),
			      (char **) &bom, (size_t *) (&bomLen));
			  iconv (ic, (const char **) (&fBuf), (size_t *) (&fSize),
			      (char **) &bufferPos,
			      (size_t *) (&te->indexes[i].length));
			  iconv_close (ic);
			} else
			  fileread (fp, bufferPos, te->indexes[i].length);
			// add terminating null & any necessary padding
			memset (bufferPos + (te->indexes[i].length), 0,
			    ALIGN_TO_4 (te->indexes[i].length + bomLen) -
			    (te->indexes[i].length));

			/* uint16_t unisig; if(te->indexes[i].length >= 2)
			 * fileread(fp, &unisig, sizeof(unisig));
			 * if(te->indexes[i].length == 1 || unisig !=
			 * UNICODE_SIGNATURE) { te->indexes[i].length += 2; //
			 * add space for trailing null fseek(fp, 0, SEEK_SET);
			 * } if(te->indexes[i].length <= 2) { // this is
			 * probably blank te->indexes[i].length = 0; } else {
			 * srcBufferTmp = realloc(srcBufferTmp, curPos +
			 * ALIGN_TO_4(te->indexes[i].length)); uint8_t*
			 * bufferPos = (uint8_t*)srcBufferTmp + curPos;
			 * fileread(fp, bufferPos, te->indexes[i].length-2); //
			 * add terminating null & any necessary padding
			 * memset(bufferPos + (te->indexes[i].length-2), 0,
			 * ALIGN_TO_4(te->indexes[i].length) -
			 * (te->indexes[i].length-2)); } */
			fclose (fp);
		      } else
			warning ("[line %d] Can't find or open file '%s'",
			    node->line, srcFile);
		    }
		  } else {
		    te->indexes[i].length = 0;
		    warning ("[line %d] Can't find or open file '%s'",
			node->line, srcFile);
		  }
		  te->indexes[i].offset = curPos;
		  curPos += ALIGN_TO_4 (te->indexes[i].length);
		}
		entry->srcBuffer = srcBufferTmp;
		entry->srcLen = entry->srcLenUnpacked = curPos;
	      }			// else, they're trying to hack us... :/
	      free (srcFileFmt);
	    } else if (te->numIndexes == 1 && entry->srcLen) {
	      // err, if there's just one text, we can just use the srcRange,
	      // lol
	      te->indexes[0].length = entry->srcLen;
	      te->indexes[0].offset = 0;
	    } else {
	      warning ("[line %d] Cannot determine sizes of text data!",
		  node->line);
	    }
	  }

	}
	break;

      case RCO_TABLE_FONT:
	if (entry->type == 1) {
	  entry->extraLen = sizeof (rRCOFontEntry);
	  entry->extra = malloc (entry->extraLen);
	  rRCOFontEntry *rfe = (rRCOFontEntry *) entry->extra;

	  // default value
	  rfe->format = 1;
	  rfe->compression = 0;
	  rfe->unknown = 0;
	  rfe->unknown2 = 0;

	  xmlChar *val;

	  val = xmlGetProp (node, _XX ("unknownShort1"));
	  sscanf ((const char *) val, "%i", &rfe->format);
	  xmlFree (val);
	  val = xmlGetProp (node, _XX ("unknownShort2"));
	  sscanf ((const char *) val, "%i", &rfe->compression);
	  xmlFree (val);
	  val = xmlGetProp (node, _XX ("unknownInt3"));
	  sscanf ((const char *) val, "%i", &rfe->unknown);
	  xmlFree (val);
	  val = xmlGetProp (node, _XX ("unknownInt4"));
	  sscanf ((const char *) val, "%i", &rfe->unknown2);
	  xmlFree (val);
	}
	break;
      case RCO_TABLE_OBJ:
	parse_obj_extra (node, entry);
	break;
      case RCO_TABLE_ANIM:
	parse_anim_extra (node, entry);
	break;
    }

    // pointer sect
    if (entry->type == 0 || (entry->type == 1 && entry->id == RCO_TABLE_VSMX)) {

      // shortcut table assignment
      rRCOEntry **shortcutTbl = NULL;

      switch (entry->id) {
	case RCO_TABLE_VSMX:
	  shortcutTbl = &(rco->tblVSMX);
	  break;
	case RCO_TABLE_TEXT:
	  shortcutTbl = &(rco->tblText);
	  break;
	case RCO_TABLE_IMG:
	  shortcutTbl = &(rco->tblImage);
	  break;
	case RCO_TABLE_SOUND:
	  shortcutTbl = &(rco->tblSound);
	  break;
	case RCO_TABLE_MODEL:
	  shortcutTbl = &(rco->tblModel);
	  break;
	case RCO_TABLE_FONT:
	  shortcutTbl = &(rco->tblFont);
	  break;
	case RCO_TABLE_OBJ:
	  shortcutTbl = &(rco->tblObj);
	  break;
	case RCO_TABLE_ANIM:
	  shortcutTbl = &(rco->tblAnim);
	  break;
      }
      if (shortcutTbl) {
	if (*shortcutTbl) {
	  warning
	      ("[line %d] 'Container' tree redefinition (only one should exist in an RCO file).",
	      node->line);
	} else {
	  *shortcutTbl = entry;
	}
      }
    }
  }
  // subentries
  if (node->xmlChildrenNode) {
    xmlNodePtr np = node->xmlChildrenNode;
    rRCOEntry *rcoNode = NULL;

    while (np->next) {
      if (np->type == XML_ELEMENT_NODE) {
	rRCOEntry *curNode = (rRCOEntry *) malloc (sizeof (rRCOEntry));

	parse_entry (np, curNode, rco, fixes);

	curNode->parent = entry;
	if (rcoNode) {
	  curNode->prev = rcoNode;
	  curNode->prev->next = curNode;
	} else
	  entry->firstChild = curNode;

	rcoNode = curNode;
	entry->numSubentries++;
      }
      np = np->next;
    }
    entry->lastChild = rcoNode;

  }

}

uint8_t
rcoxml_text_to_int (char *s, const RcoTableMap map, uint32_t * out)
{
  if (!s[0])
    return FALSE;

  int i = 0;

  while (map[i][0]) {
    if (!strcasecmp (map[i], s)) {
      *out = (uint32_t) i;
      return TRUE;
    }
    i++;
  }

  // see if this is "unknown"
  return (sscanf (s, "unknown%i", out) == 1);
}

// currently very basic - resize when adding a label
// uint32_t rcoxml_add_label(rRCOFile* rco, char* label) {
uint32_t
rcoxml_add_label (char **labels, uint32_t * labelsLen, char *label,
    uint8_t eventQuirk)
{
  // first, see if we already have this label
  uint32_t p = 0;

  while (p < *labelsLen && (*labels)[p]) {
    if (!strcmp (*labels + p, label))
      return p;			// found
    p += strlen (*labels + p) + 1;
    p = ALIGN_TO_4 (p);		// urgh, this is kinda a little dirty, but it
    // works; if we hit a blank 4 bytes, the above
    // line will cause it to go forward by 1, this
    // will align it forward to 4, so, if we've hit
    // some nulls, we're effectively jumping 4
    // bytes at a time
  }

  // don't have it? add it
  uint32_t curLen = *labelsLen;
  uint32_t labelLen = strlen (label) + 1;

  if (eventQuirk) {
    // TODO:
  }
  uint32_t newLen = curLen + labelLen;

  newLen = ALIGN_TO_4 (newLen);

  *labels = (char *) realloc (*labels, newLen);
  strcpy (*labels + curLen, label);
  if (labelLen % 4) {
    memset (*labels + curLen + labelLen, 0, 4 - (labelLen % 4));
  }
  *labelsLen = newLen;

  /*
   * uint32_t curLen = rco->labelsLen; uint32_t newLen = rco->labelsLen + strlen(label)
   * + 1;
   *
   * rco->labels = (char*)realloc(rco->labels, newLen); strcpy(curLen, label);
   * rco->labelsLen = newLen; */
  return curLen;
}

uint32_t
rcoxml_add_label_reordering (char *newLabels, uint32_t * labelPos, char *label)
{
  // first, see if we already have this label
  uint32_t p = 0;

  while (p < *labelPos && newLabels[p]) {
    if (!strcmp (newLabels + p, label))
      return p;			// found
    p += strlen (newLabels + p) + 1;
    p = ALIGN_TO_4 (p);		// dirty, but it works (see note from
    // rcoxml_add_label)
  }

  // don't have it? add it
  strcpy (newLabels + *labelPos, label);
  uint32_t curPos = *labelPos;

  *labelPos += strlen (label) + 1;
  *labelPos = ALIGN_TO_4 (*labelPos);

  return curPos;
}

int
label_reorder_qsort (const rRCOEntry ** a, const rRCOEntry ** b)
{
  return (*a)->id - (*b)->id;
}

void
rcoxml_reorder_labels (char *newLabels, uint32_t * labelPos, rRCOFile * rco,
    rRCOEntry * entry)
{
  uint32_t i;

  if (entry->labelOffset != RCO_NULL_PTR)
    entry->labelOffset =
	rcoxml_add_label_reordering (newLabels, labelPos,
	rco->labels + entry->labelOffset);

  if (entry->id == RCO_TABLE_TEXT && entry->type == 1) {
    rRCOTextEntry *extra = (rRCOTextEntry *) entry->extra;

    for (i = 0; i < extra->numIndexes; i++)
      if (extra->indexes[i].labelOffset != RCO_NULL_PTR)
	extra->indexes[i].labelOffset =
	    rcoxml_add_label_reordering (newLabels, labelPos,
	    rco->labels + extra->indexes[i].labelOffset);
  }

  rRCOEntry *rcoNode;

  for (rcoNode = entry->firstChild; rcoNode; rcoNode = rcoNode->next)
    rcoxml_reorder_labels (newLabels, labelPos, rco, rcoNode);
}

void
parse_obj_extra (xmlNodePtr node, rRCOEntry * entry)
{

  if (entry->type <= RCO_OBJ_EXTRA_LEN_NUM &&
      RCO_OBJ_EXTRA_LEN[entry->type] != -1) {
    uint32_t i = 0, i2 = 0;

    // work out the length of this thing, lol
    entry->extraLen = RCO_OBJ_EXTRA_LEN[entry->type] * sizeof (uint32_t);
    for (i = 0, i2 = 0; i < (uint32_t) RCO_OBJ_EXTRA_LEN[entry->type];
	i++, i2++) {
      if (RCO_OBJ_IS_REF (entry->type, i2)) {
	entry->extraLen -= 2 * sizeof (uint32_t);
	entry->extraLen += sizeof (rRCORef);
	i++;
      }
    }

    entry->extra = malloc (entry->extraLen);
    uint8_t *extra = (uint8_t *) entry->extra;

    memset (extra, 0, entry->extraLen);

    for (i = 0, i2 = 0; (int) i < RCO_OBJ_EXTRA_LEN[entry->type]; i++, i2++) {
      uint8_t isRef = RCO_OBJ_IS_REF (entry->type, i2);

      xmlChar *val = NULL;

      if (RCO_OBJ_EXTRA_NAMES[entry->type][i2][0]) {
	val = xmlGetProp (node, _XX (RCO_OBJ_EXTRA_NAMES[entry->type][i2]));
      }

      if (!val) {
	val = rcoxml_get_unknown_attrib (node, i);
      }

      if (!val) {
	if (RCO_OBJ_EXTRA_NAMES[entry->type][i2][0]) {
	  warning
	      ("[line %d] Missing attribute '%s', defaulting to 0 / nothing.",
	      node->line, RCO_OBJ_EXTRA_NAMES[entry->type][i2]);
	} else {
	  char ts[10] = "\0";

	  switch (RCO_OBJ_EXTRA_TYPES[entry->type][i2]) {
	    case RCO_OBJ_EXTRA_TYPE_FLOAT:
	      strcpy (ts, "Float");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_INT:
	      strcpy (ts, "Int");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_EVENT:
	      strcpy (ts, "Event");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_IMG:
	      strcpy (ts, "Image");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_FONT:
	      strcpy (ts, "Font");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_MODEL:
	      strcpy (ts, "Model");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_OBJ:
	      strcpy (ts, "Object");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_UNK:
	    case RCO_OBJ_EXTRA_TYPE_REF:
	      if (isRef)
		strcpy (ts, "Ref");
	      break;
	  }
	  warning
	      ("[line %d] Missing attribute 'unknown%s%d', defaulting to 0 / nothing.",
	      node->line, ts, i);
	}

	// default values
	if (isRef)
	  ((rRCORef *) extra)->type = RCO_REF_NONE;
	else
	  *(uint32_t *) extra = 0;
      } else {
	if (isRef) {
	  // refs may need fixing later on
	  if (!rcoxml_parse_ref ((char *) val, (rRCORef *) extra))
	    warning
		("[line %d] Unable to parse reference '%s' - defaulting to 'nothing'.",
		node->line, (char *) val);
	  /*
	   * // we really need to fix refs after all entries are loaded - I'm
	   * going to be lazy here since we can't actually do anything terribly
	   * useful right now ((rRCORef*)extra)->type = RCO_REF_NONE;
	   * add_ref_to_fix(fixes, , (rRCORef*)extra); */
	} else {
	  *(uint32_t *) extra = rcoxml_parse_value ((char *) val);
	}
	xmlFree (val);
      }

      if (isRef) {
	extra += sizeof (rRCORef);
	i++;
      } else
	extra += sizeof (uint32_t);
    }
  } else {
    // TODO: handle unknown types
  }
}

void
parse_anim_extra (xmlNodePtr node, rRCOEntry * entry)
{

  if (entry->type <= RCO_ANIM_EXTRA_LEN_NUM &&
      RCO_ANIM_EXTRA_LEN[entry->type] != -1) {
    uint32_t i = 0, i2 = 0;

    // work out the length of this thing, lol
    entry->extraLen = RCO_ANIM_EXTRA_LEN[entry->type] * sizeof (uint32_t);
    for (i = 0, i2 = 0; i < (uint32_t) RCO_ANIM_EXTRA_LEN[entry->type];
	i++, i2++) {
      if (RCO_ANIM_IS_REF (entry->type, i2)) {
	entry->extraLen -= 2 * sizeof (uint32_t);
	entry->extraLen += sizeof (rRCORef);
	i++;
      }
    }

    entry->extra = malloc (entry->extraLen);
    uint8_t *extra = (uint8_t *) entry->extra;

    memset (extra, 0, entry->extraLen);

    for (i = 0, i2 = 0; (int) i < RCO_ANIM_EXTRA_LEN[entry->type]; i++, i2++) {
      uint8_t isRef = RCO_ANIM_IS_REF (entry->type, i2);

      xmlChar *val = NULL;

      if (RCO_ANIM_EXTRA_NAMES[entry->type][i2][0]) {
	val = xmlGetProp (node, _XX (RCO_ANIM_EXTRA_NAMES[entry->type][i2]));
      }

      if (!val) {
	val = rcoxml_get_unknown_attrib (node, i);
      }

      if (!val) {
	if (RCO_ANIM_EXTRA_NAMES[entry->type][i2][0]) {
	  warning
	      ("[line %d] Missing attribute '%s', defaulting to 0 / nothing.",
	      node->line, RCO_ANIM_EXTRA_NAMES[entry->type][i2]);
	} else {
	  char ts[10] = "\0";

	  switch (RCO_ANIM_EXTRA_TYPES[entry->type][i2]) {
	    case RCO_OBJ_EXTRA_TYPE_FLOAT:
	      strcpy (ts, "Float");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_INT:
	      strcpy (ts, "Int");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_EVENT:
	      strcpy (ts, "Event");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_IMG:
	      strcpy (ts, "Image");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_FONT:
	      strcpy (ts, "Font");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_MODEL:
	      strcpy (ts, "Model");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_OBJ:
	      strcpy (ts, "Object");
	      break;
	    case RCO_OBJ_EXTRA_TYPE_UNK:
	    case RCO_OBJ_EXTRA_TYPE_REF:
	      if (isRef)
		strcpy (ts, "Ref");
	      break;
	  }
	  warning
	      ("[line %d] Missing attribute 'unknown%s%d', defaulting to 0 / nothing.",
	      node->line, ts, i);
	}

	// default values
	if (isRef)
	  ((rRCORef *) extra)->type = RCO_REF_NONE;
	else
	  *(uint32_t *) extra = 0;
      } else {
	if (isRef) {
	  // refs may need fixing later on
	  if (!rcoxml_parse_ref ((char *) val, (rRCORef *) extra))
	    warning
		("[line %d] Unable to parse reference '%s' - defaulting to 'nothing'.",
		node->line, (char *) val);
	  /*
	   * // we really need to fix refs after all entries are loaded - I'm
	   * going to be lazy here since we can't actually do anything terribly
	   * useful right now ((rRCORef*)extra)->type = RCO_REF_NONE;
	   * add_ref_to_fix(fixes, , (rRCORef*)extra); */
	} else {
	  *(uint32_t *) extra = rcoxml_parse_value ((char *) val);
	}
	xmlFree (val);
      }

      if (isRef) {
	extra += sizeof (rRCORef);
	i++;
      } else
	extra += sizeof (uint32_t);
    }
  } else {
    // TODO: handle unknown types
  }
}

/*
 * void parse_anim_extra(xmlNodePtr node, rRCOEntry* entry) {
 *
 * if(entry->type <= RCO_ANIM_EXTRA_LEN_NUM && RCO_ANIM_EXTRA_LEN[entry->type]
 * != -1) { uint32_t i = 0;
 *
 * entry->extraLen = 0; for(i=0, i2=0; i<(uint32_t)RCO_ANIM_EXTRA_LEN[entry->type];
 * i++, i2++) { if(RCO_ANIM_IS_REF(entry->type, i2)) { entry->extraLen +=
 * sizeof(rRCORef); i++; } else entry->extraLen += sizeof(uint32_t); }
 *
 * //if(RCO_ANIM_EXTRA_REFS[entry->type]) { // entry->extraLen =
 * (RCO_ANIM_EXTRA_LEN[entry->type]-2) * sizeof(uint32_t) + sizeof(rRCORef); //}
 * else { // entry->extraLen = RCO_ANIM_EXTRA_LEN[entry->type] *
 * sizeof(uint32_t); //}
 *
 * entry->extra = malloc(entry->extraLen); uint8_t* extra = (uint8_t*)entry->extra;
 * memset(extra, 0, entry->extraLen);
 *
 * uint32_t entryLen = (uint32_t)RCO_ANIM_EXTRA_LEN[entry->type];
 *
 * if(RCO_ANIM_EXTRA_REFS[entry->type]) { xmlChar* val = NULL; if(entry->type ==
 * RCO_ANIM_TYPE_EVENT) val = xmlGetProp(node, _XX("event")); else val =
 * xmlGetProp(node, _XX("object"));
 *
 * if(val) { if(!rcoxml_parse_ref((char*)val, (rRCORef*)extra)) warning("[line
 * %d] Unable to parse object reference '%s' - defaulting to 'nothing'.",
 * node->line, (char*)val); } else { warning("[line %d] No object/event defined
 * for anim entry.  Defaulting to nothing.", node->line); // blank ref rRCORef*
 * dr = ((rRCORef*)extra); dr->type = RCO_REF_NONE; dr->ptr = NULL; dr->rawPtr =
 * RCO_NULL_PTR; } extra += sizeof(rRCORef); entryLen -=2; }
 *
 * for(i=0; i<entryLen; i++) { xmlChar* val = NULL;
 * if(RCO_ANIM_EXTRA_NAMES[entry->type][i][0]) { val = xmlGetProp(node,
 * _XX(RCO_ANIM_EXTRA_NAMES[entry->type][i])); } if(!val) { val =
 * rcoxml_get_unknown_attrib(node, i); }
 *
 * if(!val) { if(RCO_ANIM_EXTRA_NAMES[entry->type][i][0]) { warning("[line %d]
 * Missing attribute '%s', defaulting to 0 / nothing.", node->line,
 * RCO_ANIM_EXTRA_NAMES[entry->type][i]); } else { warning("[line %d] Missing
 * attribute (index %d), defaulting to 0 / nothing.", node->line, i); // TODO:
 * better message } *(uint32_t*)extra = 0; } else { *(uint32_t*)extra =
 * rcoxml_parse_value((char*)val); xmlFree(val); }
 *
 * extra += sizeof(uint32_t); } } else { // TODO: handle unknown types } } */

// TODO: this somewhat mixes normal vals with refs (not optimal) - may wish to
// do something about this
xmlChar *
rcoxml_get_unknown_attrib (xmlNodePtr node, uint32_t num)
{
  xmlChar *ret = NULL;
  char n[30];

#define RCOXML_GET_UNKNOWN_ATTRIB_DO(t) { \
		sprintf(n, "unknown" t "%d", num); \
		ret = xmlGetProp(node, _XX(n)); \
		if(ret) return ret; \
	}
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("");
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("Int");
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("Float");
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("Event");
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("Image");
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("Model");
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("Font");
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("Object");
  RCOXML_GET_UNKNOWN_ATTRIB_DO ("Ref");

  return NULL;
}

// parse object/anim attrib values
uint32_t
rcoxml_parse_value (char *s)
{
  uint32_t retI = 0;
  float retF = 0;

  if (sscanf (s, "0x%x", (uint32_t *) & retI))
    return retI;

  retF = strtof (s, NULL);
  memcpy (&retI, &retF, sizeof (uint32_t));

  return retI;
}

uint8_t
rcoxml_parse_ref (char *val, rRCORef * out)
{
  // defaults
  out->type = RCO_REF_NONE;
  out->rawPtr = RCO_NULL_PTR;
  out->ptr = NULL;

  if (!strcasecmp (val, "nothing")) {
    return TRUE;
  }
  // search for ":"
  char *colon = strchr (val, ':');

  if (!colon)
    return FALSE;
  colon[0] = '\0';

  if (!strcasecmp (val, "event"))
    out->type = RCO_REF_EVENT;
  else if (!strcasecmp (val, "text"))
    out->type = RCO_REF_TEXT;
  else if (!strcasecmp (val, "image"))
    out->type = RCO_REF_IMG;
  else if (!strcasecmp (val, "model"))
    out->type = RCO_REF_MODEL;
  else if (!strcasecmp (val, "font"))
    out->type = RCO_REF_FONT;
  else if (!strcasecmp (val, "object2"))
    out->type = RCO_REF_OBJ2;
  else if (!strcasecmp (val, "anim"))
    out->type = RCO_REF_ANIM;
  else if (!strcasecmp (val, "object"))
    out->type = RCO_REF_OBJ;

  colon[0] = ':';		// restore for good measure
  colon++;			// colon is now "name"

  if (out->type == RCO_REF_NONE) {	// not assigned by above ifs
    if (sscanf (val, "unknown%i", (int *) &(out->type))) {	// this is
      // actually
      // case
      // sensitive...
      // :|
      out->rawPtr = strtol (colon, NULL, 10);
      return TRUE;
    } else {
      return FALSE;
    }
  }

  out->ptr = malloc (strlen (colon) + 1);
  strcpy ((char *) out->ptr, colon);

  return TRUE;
}

/*
 * // a very simple resize method :/ void add_ref_to_fix(rcoxml_read_fixes*
 * fixes, char* label, rRCORef* ref) { fixes->refs =
 * (xmlrco_read_fix_refs*)realloc(fixes->refs, sizeof(xmlrco_read_fix_refs) *
 * (fixes->refCnt+1)); xmlrco_read_fix_refs* fr =
 * &(fixes->refs[fixes->refsCnt]);
 *
 * fr->ref = ref; fr->label = (char*)malloc(strlen(label)+1); strcpy(fr->label,
 * label);
 *
 * fixes->refsCnt++; } */

void
rcoxml_fix_refs (rRCOEntry * entry, rRCOFile * rco)
{
  uint32_t i = 0, i2 = 0;

  if ((entry->id == RCO_TABLE_OBJ && entry->type > 0 &&
	  entry->type <= RCO_OBJ_EXTRA_LEN_NUM &&
	  RCO_OBJ_EXTRA_LEN[entry->type] != -1)
      || (entry->id == RCO_TABLE_ANIM && entry->type > 1 &&
	  entry->type <= RCO_ANIM_EXTRA_LEN_NUM &&
	  RCO_ANIM_EXTRA_LEN[entry->type] != -1)) {
    uint8_t *extra = (uint8_t *) entry->extra;

    uint32_t len;

    if (entry->id == RCO_TABLE_OBJ)
      len = RCO_OBJ_EXTRA_LEN[entry->type];
    else
      len = RCO_ANIM_EXTRA_LEN[entry->type];
    for (i = 0, i2 = 0; i < len; i++, i2++) {
      if ((entry->id == RCO_TABLE_OBJ && RCO_OBJ_IS_REF (entry->type, i2))
	  || (entry->id != RCO_TABLE_OBJ && RCO_ANIM_IS_REF (entry->type, i2))) {
	rcoxml_fix_ref ((rRCORef *) extra, rco);
	extra += sizeof (rRCORef);
	i++;
      } else
	extra += sizeof (uint32_t);
    }
    /*
     * if(entry->id == RCO_TABLE_OBJ) { for(i=0, i2=0;
     * (int)i<RCO_OBJ_EXTRA_LEN[entry->type]; i++, i2++) {
     * if(RCO_OBJ_IS_REF(entry->type, i2)) { rcoxml_fix_ref((rRCORef*)extra,
     * rco); extra += sizeof(rRCORef); i++; } else extra += sizeof(uint32_t); }
     *
     * } else { // anim entries if(RCO_ANIM_EXTRA_REFS[entry->type]) {
     * rcoxml_fix_ref((rRCORef*)extra, rco); } } */
  }

  if (entry->numSubentries) {
    rRCOEntry *rcoNode;

    for (rcoNode = entry->firstChild; rcoNode; rcoNode = rcoNode->next)
      rcoxml_fix_refs (rcoNode, rco);
  }
}

// fixes the pointer of a reference if it needs one
// (current pointer needs to be pointing at label name)
uint8_t
rcoxml_fix_ref (rRCORef * ref, rRCOFile * rco)
{
  if (ref->type == RCO_REF_IMG || ref->type == RCO_REF_MODEL ||
      ref->type == RCO_REF_FONT || ref->type == RCO_REF_OBJ2 ||
      ref->type == RCO_REF_ANIM || ref->type == RCO_REF_OBJ) {
    if (!ref->ptr)
      return FALSE;		// no label... (this should never happen...)

    rRCOEntry *e =
	find_entry_from_label (&(rco->tblMain), (const char *) ref->ptr);
    if (!e) {
      warning ("[entry-reference] Cannot find entry with label '%s'!",
	  (const char *) ref->ptr);
    } else if ((ref->type == RCO_REF_IMG && e->id != RCO_TABLE_IMG)
	|| (ref->type == RCO_REF_MODEL && e->id != RCO_TABLE_MODEL)
	|| (ref->type == RCO_REF_FONT && e->id != RCO_TABLE_FONT)
	|| (ref->type == RCO_REF_OBJ && e->id != RCO_TABLE_OBJ)
	|| (ref->type == RCO_REF_ANIM && e->id != RCO_TABLE_ANIM)) {
      warning
	  ("[entry-reference] Mismatching reference type and entry type for reference with label '%s' - have you used the right name?",
	  (const char *) ref->ptr);
    }

    free (ref->ptr);		// unallocate malloc'd label
    ref->ptr = e;
    ref->rawPtr = 0;		// makes no sense, so blank it out

    return (e != NULL);
  } else if (ref->type == RCO_REF_EVENT) {
    if (!ref->ptr)
      return FALSE;		// no event... (this should never happen...)

    ref->rawPtr =
	rcoxml_add_label (&(rco->events), &rco->eventsLen, (char *) ref->ptr,
	TRUE);
    free (ref->ptr);		// unallocate malloc'd label
    return TRUE;
  } else if (ref->type == RCO_REF_TEXT) {
    ref->rawPtr = RCO_NULL_PTR;
    // assume first text entry is correct
    if (rco->tblText && rco->tblText->numSubentries) {
      int idx = find_text_from_label (rco->labels,
	  (rRCOTextEntry *) (rco->tblText->firstChild->extra),
	  (const char *) ref->ptr);

      if (idx == -1) {
	warning
	    ("[entry-reference] Cannot find text entry with label '%s'! (note, only first text language is checked as the RCO format assumes that all languages have the same entry labels)",
	    (const char *) ref->ptr);
      } else {
	ref->rawPtr = idx;
      }
    } else
      warning
	  ("[entry-reference] Unable to reference text entry '%s' as text tree cannot be found, or contains no text languages!",
	  (const char *) ref->ptr);

    free (ref->ptr);
    ref->ptr = NULL;
    return (ref->rawPtr != RCO_NULL_PTR);
  } else			// no fixing required
    return TRUE;
}

void
rcoxml_fix_ptrs (rRCOEntry *** sect, uint32_t * sectCnt, rRCOFile * rco,
    const char *text)
{
  uint32_t textLen = strlen (text);

  *sectCnt = 0;
  if (!textLen) {
    // no text, we'll blank the section
    *sect = NULL;
    return;
  }

  *sectCnt = 1;
  char *tmpText = (char *) malloc (textLen + 1);
  char *tmpTextPtr = tmpText;

  strcpy (tmpText, text);

  uint32_t i;

  /*
   * for(i=0; i<textLen; i++) if(tmpText[i] == ',') { (*sectCnt)++; tmpText[i]
   * = '\0'; } */
  *sectCnt = split_comma_list (tmpText);

  *sect = (rRCOEntry **) malloc (*sectCnt * sizeof (rRCOEntry *));
  rRCOEntry **entryPtr = *sect;

  for (i = 0; i < *sectCnt; i++) {
    while (isspace ((int)tmpTextPtr[0]))
      tmpTextPtr++;		// skip whitespace
    strtrimr (tmpTextPtr);
    uint32_t labelLen = strlen (tmpTextPtr);

    if (labelLen) {
      *entryPtr = find_entry_from_label (&(rco->tblMain), tmpTextPtr);
      if (!(*entryPtr))
	warning ("[entry-ptr] Cannot find entry with label '%s'!", tmpTextPtr);
    } else			// blank pointer
      *entryPtr = NULL;

    tmpTextPtr += labelLen + 1;
    entryPtr++;
  }

  free (tmpText);
}

// takes a comma separated string, replaces commas with nullchars and returns
// number of items in the list
uint32_t
split_comma_list (char *s)
{
  uint32_t cnt = 1;
  uint32_t i;
  uint32_t sLen = strlen (s);

  if (!s[0])
    return 0;			// empty string

  for (i = 0; i < sLen; i++)
    if (s[i] == ',') {
      cnt++;
      s[i] = '\0';
    }				// else if(s[i] == '\t' || s[i] == '\r' || s[i]
  //
  // == '\n' || s[i] == ' ') // whitespace
  // s[i] = '\0';

  return cnt;
}

// trim whitespace off end of string
char *
strtrimr (char *in)
{
  uint32_t len = strlen (in);

  while (len--)
    if (!isspace ((int)in[len]))
      break;
  in[len + 1] = '\0';
  return in;
}

// replaces '*' with '%1$s' or whatever
// UH-OH, issue, C99 doesn't support the above syntax...
// using standard '%s' notation instead...
char *
expand_fname_to_fmt (char *in, char type)
{
  uint32_t newSz = strlen (in) + 1;
  char *p = in;

  while ((p = strchr (p, '*'))) {
    // newSz += 3;
    newSz += 1;
    p++;
  }

  char *newStr = (char *) malloc (newSz);
  char *newStrPtr = newStr;
  char *prevP = in;

  p = in;
  while ((p = strchr (p, '*'))) {
    if (p != in) {
      memcpy (newStrPtr, prevP, p - prevP);
      newStrPtr += p - prevP;
    }
    /*
     * newStrPtr[0] = '%'; newStrPtr[1] = '1'; newStrPtr[2] = '$'; newStrPtr[3]
     * = type; newStrPtr += 4; */
    newStrPtr[0] = '%';
    newStrPtr[1] = type;
    newStrPtr += 2;
    p++;
    prevP = p;
  }

  uint32_t ppLen = strlen (prevP);

  if (ppLen) {
    memcpy (newStrPtr, prevP, ppLen);
  }
  newStr[newSz - 1] = '\0';

  return newStr;
}

uint8_t
parse_text_xml (char *fn, rRCOFile * rco, rRCOEntry * entry)
{
  xmlDocPtr doc;
  xmlNodePtr node;
  int i;
  uint8_t bValidDoc = FALSE;
  rRCOTextEntry *te = (rRCOTextEntry *) entry->extra;

  if (!(doc = xmlParseFile (fn))) {
    warning ("Can't parse XML file %s.", fn);
    return FALSE;
  }
  if ((node = xmlDocGetRootElement (doc)))
    bValidDoc = (xmlStrcmp (node->name, _XX ("TextLang")) ? FALSE : TRUE);
  if (!bValidDoc) {
    warning ("Invalid XML document %s.", fn);
    return FALSE;
  }

  te->numIndexes = 0;
  if (!node->xmlChildrenNode) {
    xmlFreeDoc (doc);
    return TRUE;
  }
  // count num of child nodes (don't use xmlChildElementCount because this may
  // include text nodes)
  xmlNodePtr np = node->xmlChildrenNode;

  while (np->next) {
    if (np->type == XML_ELEMENT_NODE && !xmlStrcmp (np->name, _XX ("Text")))
      te->numIndexes++;
    np = np->next;
  }

  if (te->numIndexes) {
    void *textBuffer = NULL;
    uint32_t curPos = 0;
    uint32_t fmt = te->format;
    char icDestFmt[8];
    uint32_t charWidth = 2;

    make_iconv_charset (icDestFmt, fmt, rco->eSwap);
    if (fmt == RCO_TEXT_FMT_UTF32) {
      charWidth = 4;
    }
    if (fmt == RCO_TEXT_FMT_UTF8) {
      charWidth = 1;
    }
    iconv_t ic = iconv_open (icDestFmt, "utf-8");;
    te->indexes =
	(RCOTextIndex *) calloc (1, te->numIndexes * sizeof (RCOTextIndex));

    np = node->xmlChildrenNode;
    i = 0;
    while (np->next) {
      if (np->type == XML_ELEMENT_NODE && !xmlStrcmp (np->name, _XX ("Text"))) {
	xmlChar *n = xmlGetProp (np, _XX ("name"));

	if (n) {
	  te->indexes[i].labelOffset =
	      rcoxml_add_label (&rco->labels, &rco->labelsLen, (char *) n,
	      FALSE);
	  xmlFree (n);

	  te->indexes[i].length = 0;
	  te->indexes[i].offset = RCO_NULL_PTR;

	  if (np->xmlChildrenNode && (np->xmlChildrenNode->type == XML_TEXT_NODE
		  || np->xmlChildrenNode->type == XML_CDATA_SECTION_NODE)) {
	    n = np->xmlChildrenNode->content;
	    if (fmt == RCO_TEXT_FMT_UTF8) {
	      te->indexes[i].length = xmlStrlen (n) + 1 /* null */ ;
	      if ((*(uint32_t *) n & 0xFFFFFF) == UTF8_BOM)
		te->indexes[i].length -= 3;
	    } else {
	      // xmlUTF8Strlen used because libxml2 will guarantee src is UTF8
	      te->indexes[i].length =
		  (xmlUTF8Strlen (n) + 1 /* null */ ) * charWidth;
	      if ((*(uint32_t *) n & 0xFFFFFF) == UTF8_BOM) {	// fix for
		// older
		// versions of
		// rcomage - if
		// BOM exists,
		// reduce
		// length by 1
		// char
		te->indexes[i].length -= charWidth;
	      }
	    }
	    if (te->indexes[i].length > 2) {
	      size_t contentLen = xmlStrlen (n);
	      size_t outBufLen = te->indexes[i].length;

	      textBuffer =
		  realloc (textBuffer,
		  ALIGN_TO_4 (te->indexes[i].length + curPos));
	      char *tbPtr = (char *) textBuffer;

	      tbPtr += curPos;
	      // first get rid of BOM if we have one (earlier versions of
	      // rcomage)
	      /* if((fmt == RCO_TEXT_FMT_UTF32 && *(uint32_t*)n == UTF32_BOM)
	       * ||(fmt == RCO_TEXT_FMT_UTF16 && *(uint16_t*)n == UTF16_BOM)
	       * ||(fmt == RCO_TEXT_FMT_UTF8 && (*(uint32_t*)n & 0x00FFFFFF) ==
	       * UTF8_BOM)) { */
	      if ((*(uint32_t *) n & 0xFFFFFF) == UTF8_BOM) {
		char bom[4];
		char *bomPtr = bom;
		size_t bomLen =
		    (fmt == RCO_TEXT_FMT_UTF32 ? 4 : (fmt ==
			RCO_TEXT_FMT_UTF8 ? 3 : 2));
		iconv (ic, (const char **) (&n), &contentLen,
		    (char **) &bomPtr, &bomLen);
	      }
	      iconv (ic, (const char **) (&n), &contentLen, &tbPtr,
		  &outBufLen);
	      if (outBufLen && outBufLen == charWidth) {	// *should*
		// always be
		// true
		memset (tbPtr, 0,
		    ALIGN_TO_4 (te->indexes[i].length) -
		    (te->indexes[i].length - outBufLen));
	      } else
		warning
		    ("[%s:%d] iconv error when trying to convert text for '%s'! (%d byte(s) not converted)",
		    fn, np->line, rco->labels + te->indexes[i].labelOffset,
		    (int) (outBufLen - charWidth));

	      te->indexes[i].offset = curPos;
	      curPos += ALIGN_TO_4 (te->indexes[i].length);
	    } else
	      te->indexes[i].length = 0;	// blank string
	  }

	  i++;
	} else
	  warning ("[%s:%d] No name specified for Text!", fn, np->line);
      }
      np = np->next;
    }
    entry->srcBuffer = textBuffer;
    entry->srcFile[0] = '\0';
    entry->srcLen = entry->srcLenUnpacked = curPos;
    iconv_close (ic);
  }

  xmlFreeDoc (doc);
  return TRUE;
}
