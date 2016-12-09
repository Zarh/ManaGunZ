/*
 * vaghandler.h - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#ifndef __VAGHANDLER__
#define __VAGHANDLER__
#include "general.h"
uint8_t vag2wav (const char *fWav, int numChannels, int *vagLen,
    void **vagData);
int wav2vag (const char *fWav, uint32_t * len, void **vagData,
    const char *vagName);
#endif
