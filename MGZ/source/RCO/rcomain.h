/*
 * rcomain.h - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#ifndef __RCOMAIN_H__
#define __RCOMAIN_H__

#include "general.h"
#include "rcofile.h"
#include <stdio.h>
#include <zlib.h>

#define MAX_FILENAME_LEN 260

typedef struct {
  int packHeader, packImg, packImgCompr, packModel, packText;
  int zlibMethod, zlibLevel;
#define WRITERCO_ZLIB_METHOD_ZDEFAULT Z_DEFAULT_STRATEGY
#define WRITERCO_ZLIB_METHOD_ZFILTERED Z_FILTERED
#define WRITERCO_ZLIB_METHOD_ZHUFFMAN Z_HUFFMAN_ONLY
#define WRITERCO_ZLIB_METHOD_ZRLE Z_RLE
#define WRITERCO_ZLIB_METHOD_ZFIXED Z_FIXED
#define WRITERCO_ZLIB_METHOD_7Z Z_USE_7Z
  int rlzMode;
} writerco_options;

typedef struct __rRCOEntry {
  uint8_t type;			// main table uses 0x01; may be used as a
  // current entry depth value
  uint8_t id;
  // char* label;
  uint32_t labelOffset;

  uint32_t offset;		// absolute offset of this entry in file (only
  // used when reading/writing RCOs - means
  // nothing otherwise; also, writing the RCO may
  // change this value)
  // this value is also used to store the line number of the node when reading
  // an XML

  struct __rRCOFile *rco;
  struct __rRCOEntry *parent;
  struct __rRCOEntry *firstChild;
  struct __rRCOEntry *lastChild;
  struct __rRCOEntry *prev;
  struct __rRCOEntry *next;
  uint32_t numSubentries;

  void *extra;
  uint32_t extraLen;		// in bytes

  // for entries with attached data
  char srcFile[MAX_FILENAME_LEN];
  uint32_t srcAddr;
  uint32_t srcLen;
  uint32_t srcLenUnpacked;
  uint32_t srcCompression;	// use RCO_DATA_COMPRESSION_* constants in
  // rcofile.h
  void *srcBuffer;		// work around for reading XML; should only be
  // used for sound and text entries; need to
  // check if srcFile contains a '*', then use
  // this
} rRCOEntry;

typedef struct {
  uint16_t lang;
  uint16_t format;
  uint32_t numIndexes;
  RCOTextIndex *indexes;
} rRCOTextEntry;

/* packed_struct { char* label; uint32_t length; uint32_t offset; }
 * rRCOTextIndex; */
typedef struct {
  rRCOEntry *textEntry;
  RCOTextIndex *index;
} rRCOTextIdxPtr;

typedef struct __rRCOFile {

  rRCOEntry tblMain;

  char *labels;
  uint32_t labelsLen;
  char *events;
  uint32_t eventsLen;

  /*
   * // pointer segments rRCOTextIdxPtr* ptrText; uint32_t numPtrText; rRCOEntry**
   * ptrImg; uint32_t numPtrImg; rRCOEntry** ptrModel; uint32_t numPtrModel;
   * rRCOEntry** ptrSound; uint32_t numPtrSound; rRCOEntry** ptrObj; uint32_t
   * numPtrObj; rRCOEntry** ptrAnim; uint32_t numPtrAnim; */

  // shortcuts
  rRCOEntry *tblVSMX;
  rRCOEntry *tblText;
  rRCOEntry *tblImage;
  rRCOEntry *tblSound;
  rRCOEntry *tblModel;
  rRCOEntry *tblFont;
  rRCOEntry *tblObj;
  rRCOEntry *tblAnim;

  // additional info about the source (mainly used for displaying info about
  // the RCO)
  uint32_t verId;		// offset 0x04 in file
  uint32_t umdFlag;
  uint32_t headerCompression;
  uint8_t eSwap;
  uint8_t ps3;

} rRCOFile;

typedef struct {
  uint32_t type;
  void *ptr;			// will usu be rRCOEntry*, but may be char* for
  //
  // events; NULL if type is nothing
  uint32_t rawPtr;		// raw value from source - means nothing if
  // type is known
} rRCORef;

typedef struct {
  uint32_t format;
  uint32_t compression;
  uint32_t unkCompr;		// unknown - usually 0, some PS3 rcos have 1
  // here
} rRCOImgModelEntry;

typedef struct {
  uint16_t format;		// 0x01 = VAG
  uint16_t channels;		// 1 or 2 channels
  uint32_t *channelData;	// size/offset pairs
} rRCOSoundEntry;

typedef struct {
  uint32_t format;		// 1
  uint32_t compression;		// 0
  uint32_t unknown;
  uint32_t unknown2;
} rRCOFontEntry;

#define RCO_TEXT_FMT_CHARWIDTH(t) ((t) == RCO_TEXT_FMT_UTF32 ? 4 : (((t) == RCO_TEXT_FMT_UTF8)) ? 1 : 2)

#define RCO_TAGMAP_SIZE 50
#define RCO_OBJMAP_SIZE 100
typedef char ((*RcoTagMap)[RCO_TAGMAP_SIZE][30]);
typedef char ((*RcoObjMap)[RCO_OBJMAP_SIZE][30]);
typedef int ((*RcoObjTypes)[RCO_OBJMAP_SIZE]);

extern int *RCO_OBJ_EXTRA_LEN;
extern uint32_t RCO_OBJ_EXTRA_LEN_NUM;

#define RCO_OBJANIM_IS_REF(v) (\
	(v == RCO_OBJ_EXTRA_TYPE_REF) || \
	(v == RCO_OBJ_EXTRA_TYPE_EVENT) || \
	(v == RCO_OBJ_EXTRA_TYPE_IMG) || \
	(v == RCO_OBJ_EXTRA_TYPE_OBJ) || \
	(v == RCO_OBJ_EXTRA_TYPE_TEXT) || \
	(v == RCO_OBJ_EXTRA_TYPE_MODEL) || \
	(v == RCO_OBJ_EXTRA_TYPE_FONT) \
)
#define RCO_OBJ_IS_REF(a, b) RCO_OBJANIM_IS_REF(RCO_OBJ_EXTRA_TYPES[a][b])
#define RCO_ANIM_IS_REF(a, b) RCO_OBJANIM_IS_REF(RCO_ANIM_EXTRA_TYPES[a][b])

// this doesn't include position info
extern RcoObjMap RCO_OBJ_EXTRA_NAMES;

#define RCO_OBJ_EXTRA_TYPE_UNK   0
#define RCO_OBJ_EXTRA_TYPE_FLOAT 1
#define RCO_OBJ_EXTRA_TYPE_INT   2
#define RCO_OBJ_EXTRA_TYPE_REF   3	// unknown reference
#define RCO_OBJ_EXTRA_TYPE_EVENT 4
#define RCO_OBJ_EXTRA_TYPE_IMG   5
#define RCO_OBJ_EXTRA_TYPE_OBJ   6
#define RCO_OBJ_EXTRA_TYPE_TEXT  7
#define RCO_OBJ_EXTRA_TYPE_MODEL 8
#define RCO_OBJ_EXTRA_TYPE_FONT  9

extern RcoObjTypes RCO_OBJ_EXTRA_TYPES;

extern int *RCO_ANIM_EXTRA_LEN;
extern uint32_t RCO_ANIM_EXTRA_LEN_NUM;

// this doesn't include references
extern RcoObjMap RCO_ANIM_EXTRA_NAMES;

// we'll use the RCO_OBJ_EXTRA_TYPE_* constants here
extern RcoObjTypes RCO_ANIM_EXTRA_TYPES;

rRCOFile *read_rco (char *fn);
uint8_t write_rco (rRCOFile * rco, char *fn, writerco_options opts);
void free_rco (rRCOFile * f);
void rco_map_func (rRCOFile * rco, rRCOEntry * parent, void *arg,
    void (*func) (rRCOFile * rco, rRCOEntry * entry, void *arg));
char *get_label_from_offset (char *labels, uint32_t labelOffset);
void *read_resource (rRCOEntry * entry, uint32_t * outLen);

#define RCO_DATA_COMPRESSION_RCO 0xFF

// rRCOEntry* rco_add_entry(rRCOEntry* parent, rRCOEntry* newEntry, int pos);

void rco_fix_decomp_sizes (rRCOFile * rco, rRCOEntry * entry);

uint32_t count_all_subentries (rRCOEntry * entry);
rRCOEntry **make_sorted_list_of_subentries (rRCOEntry * parent,
    int (*compar) (const rRCOEntry **, const rRCOEntry **));

rRCOEntry *find_entry_from_label (rRCOEntry * parent, const char *s);
int find_text_from_label (char *labels, rRCOTextEntry * textExtra,
    const char *s);

void make_iconv_charset (char out[8], int fmt, uint8_t es);

void es_rcoHeader (PRFHeader * h);
void es_rcoEntry (RCOEntry * e);
void es_rcoVsmxEntry (RCOVSMXEntry * e);
void es_rcoFontEntry (RCOFontEntry * e);
void es_rcoTextEntry (RCOTextEntry * e);
void es_rcoTextIndex (RCOTextIndex * i);
void es_rcoImgModelEntry (RCOImgModelEntry * e);
void es_rcoSoundEntry (RCOSoundEntry * e);
void es_headerComprInfo (HeaderComprInfo * hci);
void es_textComprInfo (TextComprInfo * tci);
void es_extraObjAnim (uint8_t isObj, int type, void *data, uint8_t isPS3);

PACK_STRUCT (RCOObjPos, {
      float posX;
      float posY;
      float objScale;
      float colR;
      float colG;
      float colB;
      float colA;		// RGBA

      // colour
      // weights
      float dimW;
      float dimH;
      float unknown;
      float sclX;
      float sclY;		// scale

      // values
      float elemScale;

      uint32_t iconOffset;	// unknown weird value, appears
      // to affect icon
      // offsetting. Only lowest byte appears to have
      // any effects - upper nibble appears to affect
      // Y offset, and lower nibble affects X offset
      // somehow.
      rRCORef loadAction;	// the event/anim executed on image load (note,
      //
      // load, not display) or describes when image
      // is loaded? (eg onShadowInit)
    });

/*
 * PACK_STRUCT(RCOObjSPage, { uint32_t unknown; // usu 0x111, sometimes 0xFFFF
 * (only seen in UMD video RCOs) rRCORef event1; rRCORef event2; rRCORef
 * event3; rRCORef event4; }); // 0x01 PACK_STRUCT(RCOObjSPlane, { RCOObjPos
 * pos; rRCORef image; uint32_t unknownH; // either 0 or 0xFFFF.  Has weird
 * effect on height.  Upper 2 bytes seem to have no effect. }); // 0x02
 * PACK_STRUCT(RCOObjSButton, { // this page seems to be for buttons/pane
 * items. for "buttons", has events for "Push", "FocusIn", "FocusOut" etc
 * RCOObjPos pos; rRCORef image; rRCORef shadow; // usu this & above images are
 * img/shadow pairs rRCORef image2; rRCORef ref; rRCORef event1; rRCORef
 * event2; rRCORef event3; rRCORef event4; rRCORef event5; rRCORef event6;
 * rRCORef event7; rRCORef event8; uint32_t unknown; // appears to be 0xFFFFFFFF
 * or 0 }); // 0x03 PACK_STRUCT(RCOObjSXmenu, { // only used for XMB menu?
 * RCOObjPos pos; uint32_t unknown; rRCORef event1; rRCORef event2; rRCORef
 * event3; rRCORef event4; rRCORef ref; }); // 0x04 PACK_STRUCT(RCOObjSXmList,
 * { // only used for XMB menu icons? uint32_t unknown; // dunno if hex or float
 * rRCORef image; rRCORef ref; }); // 0x05 PACK_STRUCT(RCOObjSXList, {
 * RCOObjPos pos; uint32_t unknown; rRCORef event1; rRCORef event2; rRCORef
 * event3; rRCORef event4; rRCORef event5; rRCORef event6; rRCORef event7; });
 * // 0x06 PACK_STRUCT(RCOObjSProgress, { RCOObjPos pos; float unknown; uint32_t
 * unknown2; // dunno if hex or float rRCORef ref1; rRCORef ref2; rRCORef ref3;
 * }); // 0x07 PACK_STRUCT(RCOObjSScroll, { // used for ilist? RCOObjPos pos;
 * float unknown; float unknown2; uint32_t unknown3; // dunno if hex or float
 * rRCORef ref1; rRCORef ref2; rRCORef ref3; rRCORef ref4; rRCORef ref5; }); //
 * 0x08 PACK_STRUCT(RCOObjSMList, { // seems to be used for lists/menus
 * RCOObjPos pos; uint32_t unknown; uint32_t unknown2; // dunno if hex or float
 * uint32_t unknown3; float unknown4; float unknown5; rRCORef ref1; rRCORef
 * event1; rRCORef ref2; rRCORef ref3; rRCORef ref4; rRCORef event2; rRCORef
 * ref5; rRCORef ref6; rRCORef ref7; rRCORef event3; rRCORef ref8; }); // 0x09
 * PACK_STRUCT(RCOObjSMItem, { // menu item? rRCORef text; rRCORef textAlt;
 * rRCORef ref; }); // 0x0A PACK_STRUCT(RCOObjSXItem, { rRCORef image; rRCORef
 * text; rRCORef ref; }); // 0x0C PACK_STRUCT(RCOObjSText, { RCOObjPos pos;
 * rRCORef text; // the text displayed rRCORef ref1; uint32_t unknownAlign; //
 * bottom byte: something to do with multiline text align; 1=left align,
 * 2=right, anything else=center uint32_t unknown; float size; float topR; // top
 * RGB values float topG; float topB; float bottomR; // bottom RGB values float
 * bottomG; float bottomB; float spacingHorizontal; uint32_t unknown2; // dunno
 * whether hex or float uint32_t unknown3; // dunno whether hex or float uint32_t
 * unknown4; // dunno whether hex or float float spacingVertical; float shadowX;
 * float shadowY; float shadowPerspective; // ? float shadowR; // ? float
 * shadowG; // ? float shadowB; // ? float shadowA; // ? uint32_t unknown5; //
 * dunno whether hex or float uint32_t unknown6; // dunno whether hex or float
 * uint32_t unknown7; // dunno whether hex or float float unknown8; float unknown9;
 * float unknown10; float unknown11; uint32_t unknown12; // dunno whether hex or
 * float? }); // 0x0D PACK_STRUCT(RCOObjSModel, { RCOObjPos pos; rRCORef model;
 * }); // 0x0E PACK_STRUCT(RCOObjSSpin, { RCOObjPos pos; uint32_t unknown; // dunno
 * whether hex or float uint32_t unknown2; rRCORef ref1; rRCORef ref2; rRCORef
 * event1; rRCORef event2; rRCORef event3; rRCORef ref3; rRCORef ref4; rRCORef
 * ref5; rRCORef ref6; rRCORef ref7; }); // 0x0F PACK_STRUCT(RCOObjSAction, {
 * rRCORef ref; }); // 0x10 PACK_STRUCT(RCOObjSItemSpin, { RCOObjPos pos; uint32_t
 * unknown; uint32_t unknown2; uint32_t unknown3; uint32_t unknown4; uint32_t unknown5;
 * float unknown6; rRCORef ref1; rRCORef ref2; rRCORef event1; rRCORef event2;
 * rRCORef ref3; rRCORef ref4; rRCORef ref5; rRCORef ref6; rRCORef objPrev;
 * rRCORef objNext; }); // 0x11 PACK_STRUCT(RCOObjSGroup, { RCOObjPos pos; }); //
 * 0x12 PACK_STRUCT(RCOObjSLList, { RCOObjPos pos; uint32_t unknown; uint32_t
 * unknown2; // dunno whether hex or float float unknown3; rRCORef ref1; rRCORef
 * ref2; rRCORef ref3; rRCORef ref4; rRCORef ref5; rRCORef ref6; rRCORef event;
 * rRCORef ref7; }); // 0x13 PACK_STRUCT(RCOObjSLItem, { rRCORef text; rRCORef
 * ref1; rRCORef ref2; }); // 0x14 PACK_STRUCT(RCOObjSEdit, { RCOObjPos pos;
 * uint32_t unknown; // dunno whether hex or float uint32_t unknown2; // dunno whether
 * hex or float uint32_t unknown3; // dunno whether hex or float uint32_t unknown4; //
 * dunno whether hex or float rRCORef ref1; rRCORef ref2; rRCORef event1; rRCORef
 * ref3; rRCORef ref4; rRCORef ref5; rRCORef event2; rRCORef event3; rRCORef obj1;
 * rRCORef obj2; rRCORef ref6; }); // 0x15 PACK_STRUCT(RCOObjSClock, { RCOObjPos
 * pos; uint32_t unknown; float unknown2; rRCORef text1; rRCORef text2; rRCORef ref1;
 * rRCORef ref2; rRCORef event1; rRCORef event2; rRCORef ref3; rRCORef ref4; rRCORef
 * event3; rRCORef event4; rRCORef ref5; rRCORef ref6; rRCORef event5; }); // 0x16
 * PACK_STRUCT(RCOObjSIList, { RCOObjPos pos; float unknown; rRCORef ref1; rRCORef
 * ref2; rRCORef event; rRCORef ref3; }); // 0x17 PACK_STRUCT(RCOObjSIItem, {
 * rRCORef textDefault; rRCORef textError; }); // 0x18 PACK_STRUCT(RCOObjSIcon, {
 * RCOObjPos pos; rRCORef img1; rRCORef img2; rRCORef ref1; }); // 0x19
 * PACK_STRUCT(RCOObjSUButton, { RCOObjPos pos; rRCORef img1; rRCORef event1; //
 * onPush rRCORef event2; // onFocusIn rRCORef event3; // [event/anim] onFocusOut
 * rRCORef ref1; // [object/event] rRCORef ref2; // [object/event] rRCORef ref3; //
 * [object/event] prev/up? rRCORef ref4; // [object/event] next/down? uint32_t
 * unknown; // 0xFFFFFFFF or 0 }); // 0x1A
 *
 * PACK_STRUCT(RCOAnimSPos, { rRCORef obj; float time; uint32_t unknown; float x;
 * float y; float unknown2; }); PACK_STRUCT(RCOAnimSColour, { rRCORef obj; float
 * time; uint32_t unknown; // dunno whether float or int (probably int) float r; float
 * g; float b; float a; }); PACK_STRUCT(RCOAnimSRotate, { // TODO: this one needs
 * checking rRCORef obj; float time; uint32_t unknown; // dunno whether float or int
 * (probably int) uint32_t unknown2; // dunno whether float or int (probably int)
 * uint32_t unknown3; // dunno whether float or int (probably int) uint32_t rotation;
 * }); PACK_STRUCT(RCOAnimSScale, { rRCORef obj; float time; uint32_t unknown; float
 * w; float h; float unknown2; }); PACK_STRUCT(RCOAnimSAlpha, { rRCORef obj; float
 * time; uint32_t unknown; float a; }); PACK_STRUCT(RCOAnimSDelay, { float time; });
 * PACK_STRUCT(RCOAnimSEvent, { rRCORef event; }); PACK_STRUCT(RCOAnimSLock, {
 * uint32_t unknown; // always seems to be 0xFFFFFFFF }); PACK_STRUCT(RCOAnimSUnlock,
 * { uint32_t unknown; // always seems to be 0xFFFFFFFF });
 * PACK_STRUCT(RCOAnimSSlideout, { rRCORef obj; uint32_t unknown; uint32_t unknown2;
 * float unknown3; uint32_t unknown4; uint32_t unknown5; float unknown6; }); */

#endif
