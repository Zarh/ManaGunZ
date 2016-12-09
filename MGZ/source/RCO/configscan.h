/*
 * configscan.h - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#ifndef __CONFIGSCAN_H__
#define __CONFIGSCAN_H__
#include "general.h"

extern char *configDir;

void configLoadTagmap (void);
void configLoadMiscmap (void);
void configLoadObjmap (uint8_t ps3);
void configLoadAnimmap (uint8_t ps3);

#endif
