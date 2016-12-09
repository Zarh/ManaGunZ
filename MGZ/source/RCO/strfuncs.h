/*
 * strfuncs.h - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

// stupid MSVC
#include <string.h>
#ifdef WIN32
#ifndef strcasecmp
#define strcasecmp _stricmp
#endif
#else
#include <strings.h>
#endif
