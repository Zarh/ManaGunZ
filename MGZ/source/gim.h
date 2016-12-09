/*
 *  gim.h
 *  
 *
 *  Created by Johannes Wilke on 2008/08/16.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GIM__H__
#define GIM__H__

#include <stdlib.h>

enum {
  GIM_OK = 0,
  GIM_CANNOT_OPEN_READ_FILE,
  GIM_CANNOT_CREATE_WRITE_FILE,
  GIM_OUT_OF_MEMORY,
  GIM_CANNOT_READ_FILE,
  GIM_CANNOT_INITIALIZE,
  GIM_COMPRESSION_FAILURE,
  GIM_CANNOT_WRITE_FILE  
};

typedef enum {
  GIM_COMPRESS,
  GIM_UNCOMPRESS
} gimCompressionDirection;

#endif
