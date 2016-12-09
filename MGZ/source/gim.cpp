/*
 *  gim.c
 *  
 *
 *  Created by Johannes Wilke on 2008/08/16.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "gim.h"

#include <stdio.h>
#include "zlib.h"

//#define OUTPUT_DEBUG_TEXT 1
#define OUTPUT_ERROR_TEXT 1

extern "C" int compressGIMBuffer(void* gim_buffer, size_t gim_buffer_size, void* compressed_buffer, size_t compressed_buffer_size);
extern "C" int uncompressGIMBuffer(void* compressed_buffer, size_t compressed_buffer_size, void** gim_buffer);
extern "C" int gimCompression(char* read_filename, char* write_filename, gimCompressionDirection direction);
extern "C" void print_load(char *format, ...);

int compressGIMBuffer(void* gim_buffer, size_t gim_buffer_size, void* compressed_buffer, size_t compressed_buffer_size)
{
  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  
  int deflate_init_result = deflateInit (&strm, 9);
  if (deflate_init_result != Z_OK)
  {
    return -GIM_CANNOT_INITIALIZE;
  }

  strm.next_in = (Bytef*)gim_buffer;
  strm.avail_in = gim_buffer_size;
  strm.next_out = (Bytef*)compressed_buffer;
  strm.avail_out = compressed_buffer_size;
  
  int deflate_result = deflate(&strm, Z_FINISH);
  if (deflate_result != Z_STREAM_END)
  {
    deflateEnd(&strm);
    return -GIM_COMPRESSION_FAILURE;
  }
  
  deflateEnd(&strm);
  
  return strm.total_out;
}

int uncompressGIMBuffer(void* compressed_buffer, size_t compressed_buffer_size, void** gim_buffer)
{  
  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  
  size_t gim_buffer_size = compressed_buffer_size * 2;
  
  while(1)
  {
    strm.next_in = (Bytef*)compressed_buffer;
    strm.avail_in = compressed_buffer_size;  

    int inflate_init_result = inflateInit (&strm);
    if (inflate_init_result != Z_OK)
    {
      *gim_buffer = 0;
      return -GIM_CANNOT_INITIALIZE;
    }
  
    *gim_buffer = (void*)new Bytef[gim_buffer_size];
    
    strm.next_in = (Bytef*)compressed_buffer;
    strm.avail_in = compressed_buffer_size;
    strm.total_in = 0;
    strm.next_out = (Bytef*)*gim_buffer;
    strm.avail_out = gim_buffer_size;
    strm.total_out = 0;
    
    int inflate_result = inflate(&strm, Z_FINISH);
    if (inflate_result != Z_STREAM_END)
    {
      if (inflate_result != Z_BUF_ERROR)
      {
#ifdef OUTPUT_ERROR_TEXT
        print_load((char *)"*** Uncompress failure: =%d\n", inflate_result);
#endif
        
        delete[](Bytef*)(*gim_buffer);
        *gim_buffer = 0;
        inflateEnd(&strm);
        return -GIM_COMPRESSION_FAILURE;
      }
    }
    else
      break;
    
    delete[](Bytef*)*gim_buffer;
    gim_buffer_size *= 2;

    inflateEnd(&strm);
  }  
  
  inflateEnd(&strm);
  
  return strm.total_out;
}

int gimCompression(char* read_filename, char* write_filename, gimCompressionDirection direction)
{
  FILE* read_file_handle = fopen(read_filename, "rb");
  if (read_file_handle == 0)
  {
    return -GIM_CANNOT_OPEN_READ_FILE;
  }
  
  fseek(read_file_handle, 0, SEEK_END);
  size_t no_bytes_to_read = ftell(read_file_handle);
  fseek(read_file_handle, 0, SEEK_SET);
  
  if (no_bytes_to_read == 0)
  {
    fclose(read_file_handle);
    return -GIM_CANNOT_OPEN_READ_FILE;
  }
  
  Bytef* read_buffer = new Bytef[no_bytes_to_read];
  if (read_buffer == 0)
  {
    fclose(read_file_handle);
    return -GIM_OUT_OF_MEMORY;
  }
  
  size_t no_bytes_read = fread(read_buffer, 1, no_bytes_to_read, read_file_handle);
  fclose(read_file_handle);
  if (no_bytes_read != no_bytes_to_read)
  {
    delete[]read_buffer;
    return -GIM_CANNOT_READ_FILE;
  }
  
  Bytef* compression_buffer = 0;
  size_t compression_buffer_size;
  
  if (direction == GIM_COMPRESS)
  {
    compression_buffer_size = no_bytes_read;
  }
  else
    compression_buffer_size = no_bytes_read*5;
  
  if (direction == GIM_COMPRESS)
  {
    compression_buffer = new Bytef[compression_buffer_size];
  
    if (compression_buffer == 0)
    {
      delete[]read_buffer;
      return -GIM_OUT_OF_MEMORY;
    }
  }
  
  int compression_result;
  if (direction == GIM_COMPRESS)
  {
    compression_result = compressGIMBuffer(read_buffer, no_bytes_to_read, compression_buffer, compression_buffer_size);
  }
  else
    compression_result = uncompressGIMBuffer(read_buffer, no_bytes_to_read, (void**)&compression_buffer);
    
  if (compression_result < GIM_OK)
  {
    if (compression_buffer != 0)
      delete[]compression_buffer;
    delete[]read_buffer;
    return compression_result;
  }
  
  unsigned int no_bytes_to_write = compression_result;
  
  FILE* write_file_handle = fopen(write_filename, "wb");
  if (write_file_handle == 0)
  {
    delete[]compression_buffer;
    delete[]read_buffer;
    return -GIM_CANNOT_CREATE_WRITE_FILE;
  }
  
  size_t no_bytes_written = fwrite(compression_buffer, 1, no_bytes_to_write, write_file_handle);
  if (no_bytes_written != no_bytes_to_write)
  {
    fclose(write_file_handle);
    delete[]compression_buffer;
    delete[]read_buffer;
    return -GIM_CANNOT_WRITE_FILE;
  }
  
  fclose(write_file_handle);
  delete[]compression_buffer;
  delete[]read_buffer;

  return GIM_OK;
}
