/*
 * configscan.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "rcomain.h"
#include "xml.h"

#define INI_LINE_BUF_LEN 2048

char *configDir = NULL;

int get_ini_line (FILE * fp, char *buf, char **out1, char **out2);

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

FILE *fopen_local (char *fn, char *mode)
{
  char path[512];
  sprintf(path, "/dev_hdd0/game/MANAGUNZ0/USRDIR/sys/RCO/%s", fn);
  return fopen (path, mode);
}

void configLoadTagmap (void)
{
  FILE *fp = fopen_local ("tagmap.ini", "r");

  if (fp) {
    char buf[INI_LINE_BUF_LEN];
    char *key, *val;
    int type;
    int id = -1, id2 = -1;

    while ((type = get_ini_line (fp, buf, &key, &val))) {
      if (type == 1) {
	id++;
	RCOXML_TABLE_TAGS =
	    (RcoTagMap) realloc (RCOXML_TABLE_TAGS,
	    sizeof (*RCOXML_TABLE_TAGS) * (id + 2));
	RCOXML_TABLE_TAGS[id][0][0] = 0;
	id2 = -1;
	RCOXML_TABLE_NAMES =
	    (RcoTableMap) realloc (RCOXML_TABLE_NAMES,
	    sizeof (*RCOXML_TABLE_NAMES) * (id + 1));
	strcpy (RCOXML_TABLE_NAMES[id], key);
      } else {
	if (id == -1)
	  continue;
	id2++;
	if (id2 >= RCO_TAGMAP_SIZE - 2) {
	  error ("Too many types.");
	  return;
	}
	strcpy (RCOXML_TABLE_TAGS[id][id2], key);
	RCOXML_TABLE_TAGS[id][id2 + 1][0] = 0;
      }
    }
    fclose (fp);
    RCOXML_TABLE_TAGS_NUM = id + 1;
  } else {
    error ("Could not open map file.");
    return;
  }
}

void configLoadMiscmap (void)
{
  FILE *fp = fopen_local ("miscmap.ini", "r");

  if (fp) {
    char buf[INI_LINE_BUF_LEN];
    char *key, *val;
    int type;
    int id = -1;
    RcoTableMap *map = NULL;

    while ((type = get_ini_line (fp, buf, &key, &val))) {
      if (type == 1) {
	if (!strcasecmp (key, "compression")) {
	  map = &RCOXML_TABLE_DATA_COMPRESSION;
	} else if (!strcasecmp (key, "languages")) {
	  map = &RCOXML_TABLE_TEXT_LANG;
	} else if (!strcasecmp (key, "textformats")) {
	  map = &RCOXML_TABLE_TEXT_FMT;
	} else if (!strcasecmp (key, "imageformats")) {
	  map = &RCOXML_TABLE_IMG_FMT;
	} else if (!strcasecmp (key, "soundformats")) {
	  map = &RCOXML_TABLE_SOUND_FMT;
	} else if (!strcasecmp (key, "modelformats")) {
	  map = &RCOXML_TABLE_MODEL_FMT;
	} else {
	  error ("Unknown key %s", key);
	  return;
	}
	*map = (RcoTableMap) malloc (sizeof (**map));
	(*map)[0][0] = 0;
	id = -1;
      } else {
	if (!map)
	  continue;
	id++;
	(*map) = (RcoTableMap) realloc (*map, sizeof (**map) * (id + 2));
	strcpy ((*map)[id], key);
	(*map)[id + 1][0] = 0;
      }
    }
    fclose (fp);
#define CONFIG_LOAD_MISC_CHECK(v, s) if(!v) { error("Couldn't load " s " constants from config file!"); return; }
    CONFIG_LOAD_MISC_CHECK (RCOXML_TABLE_DATA_COMPRESSION, "compression");
    CONFIG_LOAD_MISC_CHECK (RCOXML_TABLE_TEXT_LANG, "language");
    CONFIG_LOAD_MISC_CHECK (RCOXML_TABLE_TEXT_FMT, "textformat");
    CONFIG_LOAD_MISC_CHECK (RCOXML_TABLE_IMG_FMT, "imageformat");
    CONFIG_LOAD_MISC_CHECK (RCOXML_TABLE_SOUND_FMT, "soundformat");
    CONFIG_LOAD_MISC_CHECK (RCOXML_TABLE_MODEL_FMT, "modelformat");
  } else {
    error ("Could not open map file.");
    return;
  }
}

void configLoadObjmap (uint8_t ps3)
{
  char from[30] = "objattribdef-psp.ini";

  if (ps3)
    strcpy (from, "objattribdef-ps3.ini");
  FILE *fp = fopen_local (from, "r");

  if (fp) {
    char buf[INI_LINE_BUF_LEN];
    char *key, *val;
    int type;
    int id = -1, id2 = -1, lenAdd = 0;

    while ((type = get_ini_line (fp, buf, &key, &val))) {
      if (type == 1) {
	id++;
	RCO_OBJ_EXTRA_LEN =
	    (int *) realloc (RCO_OBJ_EXTRA_LEN, sizeof (int) * (id + 1));
	// RCO_OBJ_EXTRA_LEN[id] = id2 + lenAdd;
	RCO_OBJ_EXTRA_LEN[id] = 0;
	RCO_OBJ_EXTRA_NAMES =
	    (RcoObjMap) realloc (RCO_OBJ_EXTRA_NAMES,
	    sizeof (*RCO_OBJ_EXTRA_NAMES) * (id + 1));
	RCO_OBJ_EXTRA_NAMES[id][0][0] = 0;
	RCO_OBJ_EXTRA_TYPES =
	    (RcoObjTypes) realloc (RCO_OBJ_EXTRA_TYPES,
	    sizeof (*RCO_OBJ_EXTRA_TYPES) * (id + 1));
	RCO_OBJ_EXTRA_TYPES[id][0] = 0;
	id2 = -1;
	lenAdd = 0;
      } else {
	id2++;
	RCO_OBJ_EXTRA_LEN[id]++;
	if (id2 >= RCO_OBJMAP_SIZE - 1) {
	  error ("Too many types.");
	  return;
	}
	strcpy (RCO_OBJ_EXTRA_NAMES[id][id2], key);
	if (!strcasecmp (val, "int"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_INT;
	else if (!strcasecmp (val, "float"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_FLOAT;
	else if (!strcasecmp (val, "ref"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_REF;
	else if (!strcasecmp (val, "event"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_EVENT;
	else if (!strcasecmp (val, "image"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_IMG;
	else if (!strcasecmp (val, "object"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_OBJ;
	else if (!strcasecmp (val, "text"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_TEXT;
	else if (!strcasecmp (val, "model"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_MODEL;
	else if (!strcasecmp (val, "font"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_FONT;
	else if (!strcasecmp (val, "unk"))
	  RCO_OBJ_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_UNK;
	else {
	  error ("Unknown type '%s'", val);
	  return;
	}
	if (RCO_OBJ_IS_REF (id, id2))
	  RCO_OBJ_EXTRA_LEN[id]++;
      }
    }
    // RCO_OBJ_EXTRA_LEN[id+1] = id2 + lenAdd;
    fclose (fp);
    RCO_OBJ_EXTRA_LEN_NUM = id + 1;
  } else {
    error ("Could not open map file.");
    return;
  }
}

void configLoadAnimmap (uint8_t ps3)
{
  char from[30] = "animattribdef-psp.ini";

  if (ps3)
    strcpy (from, "animattribdef-ps3.ini");
  FILE *fp = fopen_local (from, "r");

  if (fp) {
    char buf[INI_LINE_BUF_LEN];
    char *key, *val;
    int type;
    int id = -1, id2 = -1, lenAdd = 0;

    while ((type = get_ini_line (fp, buf, &key, &val))) {
      if (type == 1) {
	id++;
	RCO_ANIM_EXTRA_LEN =
	    (int *) realloc (RCO_ANIM_EXTRA_LEN, sizeof (int) * (id + 1));
	RCO_ANIM_EXTRA_LEN[id] = 0;
	RCO_ANIM_EXTRA_NAMES =
	    (RcoObjMap) realloc (RCO_ANIM_EXTRA_NAMES,
	    sizeof (*RCO_ANIM_EXTRA_NAMES) * (id + 1));
	RCO_ANIM_EXTRA_NAMES[id][0][0] = 0;
	RCO_ANIM_EXTRA_TYPES =
	    (RcoObjTypes) realloc (RCO_ANIM_EXTRA_TYPES,
	    sizeof (*RCO_ANIM_EXTRA_TYPES) * (id + 1));
	RCO_ANIM_EXTRA_TYPES[id][0] = 0;
	id2 = -1;
	lenAdd = 0;
      } else {
	id2++;
	RCO_ANIM_EXTRA_LEN[id]++;
	if (id2 >= RCO_OBJMAP_SIZE - 1) {
	  error ("Too many types.");
	  return;
	}
	strcpy (RCO_ANIM_EXTRA_NAMES[id][id2], key);
	if (!strcasecmp (val, "int"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_INT;
	else if (!strcasecmp (val, "float"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_FLOAT;
	else if (!strcasecmp (val, "ref"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_REF;
	else if (!strcasecmp (val, "event"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_EVENT;
	else if (!strcasecmp (val, "image"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_IMG;
	else if (!strcasecmp (val, "object"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_OBJ;
	else if (!strcasecmp (val, "text"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_TEXT;
	else if (!strcasecmp (val, "model"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_MODEL;
	else if (!strcasecmp (val, "font"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_FONT;
	else if (!strcasecmp (val, "unk"))
	  RCO_ANIM_EXTRA_TYPES[id][id2] = RCO_OBJ_EXTRA_TYPE_UNK;
	else {
	  error ("Unknown type '%s'", val);
	  return;
	}
	if (RCO_ANIM_IS_REF (id, id2))
	  RCO_ANIM_EXTRA_LEN[id]++;
      }
    }
    fclose (fp);
    RCO_ANIM_EXTRA_LEN_NUM = id + 1;
  } else {
    error ("Could not open map file.");
    return;
  }
}

int get_ini_line (FILE * fp, char *buf, char **out1, char **out2)
{
  while (fgets (buf, INI_LINE_BUF_LEN, fp)) {
    char *op = buf, *arg = NULL, *tmp;
    unsigned int lineLen;

    // trim line
#define IS_WHITESPACE(x) (x == '\t' || x == ' ' || x == '\n' || x == '\r')
    while (*op && IS_WHITESPACE (*op))
      op++;
    // don't forget to remove comments!
    tmp = op;
    while (*tmp) {
      if (*tmp == ';') {
	*tmp = '\0';
	break;
      }
      tmp++;
    }
    lineLen = strlen (op);
    while (lineLen && IS_WHITESPACE (op[lineLen - 1]))
      lineLen--;
    op[lineLen] = '\0';

    if (lineLen == 0)
      continue;
    if (op[0] == L';')
      continue;			// comment line

    if (op[0] == '[' && op[strlen (op) - 1] == ']') {	// [line]
      op[strlen (op) - 1] = '\0';
      op++;
      *out1 = op;
      *out2 = NULL;
      return 1;
    }
    // find =, if any
    tmp = op;
    while (*(++tmp))
      if (*tmp == '=') {
	arg = tmp + 1;
	*tmp = '\0';
	while (*arg && IS_WHITESPACE (*arg))
	  arg++;

	lineLen = strlen (op);
	while (lineLen && IS_WHITESPACE (op[lineLen - 1]))
	  lineLen--;
	op[lineLen] = '\0';

	break;
      }

    *out1 = op;
    *out2 = arg;

    return 2;
  }
  return 0;
}
