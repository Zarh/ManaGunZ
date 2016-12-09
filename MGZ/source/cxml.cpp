/*   SCE CONFIDENTIAL                                       */
/*   PlayStation(R)3 Programmer Tool Runtime Library 400.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <string.h>

#include "cxml/cxmlutil.h"
#include "cxml/cxmlaccess.h"
#include "zlib.h"
#include "gtf.h"

#define _EXIST		1
#define _NOT_EXIST	0

// -------------------------------------------

extern "C" void cxml_extract(char *file_path);
extern "C" u8 path_info(char *path);
extern "C" void print_load(char *format, ...);
extern "C" void ConvertImage(char *file_in, char *file_out);
extern "C" char *LoadFile(char *path, int *file_size);
extern "C" char GIM2PNG(char *in, char *out);
extern "C" void Delete(char* path);
extern "C" int VAG2WAV(char *vag_path, char *wav_path);
extern "C" void JSX2JS(char *in, char *out);

// -------------------------------------------


char table[10][32];
int lv_table=-1;

using namespace cxml;

int zlib_decompressed_size(void *src, int srcLen)
{
  z_stream s;

  memset (&s, 0, sizeof (s));

#define ZLIB_TESTUNPACK_BUFSIZE 65536
  char buffer[ZLIB_TESTUNPACK_BUFSIZE];

  s.next_in = (Bytef *) src;
  s.avail_in = srcLen;
  s.next_out = (Bytef *) buffer;
  s.avail_out = ZLIB_TESTUNPACK_BUFSIZE;

  if (inflateInit (&s) != Z_OK)
    return 0;

  uint32_t size = 0;
  int ret;

  while ((ret = inflate (&s, Z_NO_FLUSH)) == Z_OK) {
    size += ZLIB_TESTUNPACK_BUFSIZE - s.avail_out;
    if (!s.avail_in)
      break;
    s.next_out = (Bytef *) buffer;
    s.avail_out = ZLIB_TESTUNPACK_BUFSIZE;
  }

  if (ret == Z_STREAM_END) {
    size += ZLIB_TESTUNPACK_BUFSIZE - s.avail_out;
  }

  inflateEnd (&s);
  if (s.avail_in || (ret != Z_STREAM_END && ret != Z_OK))
    return 0;

  return size;
}

int mkdir_rec(const char *path)
{
  int len = strlen (path);
  char *temp = (char *) malloc (len + 1);
  int i;
  int ret = 0;
  struct stat stat_buf;

  memcpy (temp, path, len);

  if (temp[0] == '/')
    i = 1;
  else
    i = 0;
  while (i < len) {
    for (; i < len && temp[i] != '/'; i++);
    temp[i] = 0;
    if (stat (temp, &stat_buf) != 0) {
      ret = mkdir(temp, 0777);;
      if (ret != 0) {
		goto end;
	  }
    }
    if (i < len)
      temp[i] = '/';
    i++;
  }
 end:
  free (temp);
  return ret;
}

static void print_indent( int indent, FILE *out )
{
	int i;
	for( i=0 ; i<indent ; i++ ) fputs("\t", out);
}

static int dump_element( const Element & element, int indent , FILE *out, char *dir_path)
{
	int ret;

	char temp[128];
	char src[10][128];
	char input[10][128];
	char dst_name[10][128];
	int n_file=-1;
	int have_child=0;
	int close=1;
	int have_ID=0;
	char NameID[128];
	
	Element child=element.GetFirstChild();
	if( child.NumAttribute() > 0) have_child=1;
	
	if(lv_table<indent && have_child) {
		lv_table++;
		strcpy(table[lv_table], element.GetName());
	}
	
	print_indent(indent, out);
	
	sprintf(temp, "<%s", element.GetName() ); fputs(temp, out);
	int i;
	for( i=0 ; i<element.NumAttribute() ; i++ )
	{
		Attribute attr;

		ret = element.GetAttribute( i, &attr );

		if(ret<0)
		{
			return ret;
		}

		switch(attr.GetType())
		{
		case AttributeType_None:
			{
				sprintf(temp, " %s=\"None\"", attr.GetName()); fputs(temp, out);
			}
			break;

		case AttributeType_Int:
			{
				int _i;
				ret = attr.GetInt(&_i);
				
				if(ret<0)
				{
					return ret;
				}
				sprintf(temp, " %s=\"%d\"", attr.GetName(), _i ); fputs(temp, out);
				
			}
			break;

		case AttributeType_Float:
			{
				float f;
				ret = attr.GetFloat(&f);

				if(ret<0)
				{
					return ret;
				}

				sprintf(temp, " %s=\"%f\"", attr.GetName(), f ); fputs(temp, out);
			}
			break;

		case AttributeType_String:
			{
				const char * str;
				unsigned int len;

				ret = attr.GetString( &str, &len );

				if(ret<0)
				{
					return ret;
				}

				sprintf(temp, " %s=\"%s\"", attr.GetName(), str ); fputs(temp, out);
			}
			break;

		case AttributeType_IntArray:
			{
				const int * array;
				unsigned int num;

				ret = attr.GetIntArray( &array, &num );

				if(ret<0)
				{
					return ret;
				}
				sprintf(temp, " %s=\"", attr.GetName());	fputs(temp, out);

				for( unsigned int k=0 ; k<num ; k++ )
				{
					sprintf(temp, "%d", array[k] ); fputs(temp, out);
					if(k+1<num) fputs(",", out);
				}
				fputs("\"", out);
			}
			break;

		case AttributeType_FloatArray:
			{
				const float * array;
				unsigned int num;

				ret = attr.GetFloatArray( &array, &num );

				if(ret<0)
				{
					return ret;
				}
				sprintf(temp, " %s=\"", attr.GetName());	fputs(temp, out);

				for( unsigned int k=0 ; k<num ; k++ )
				{
					sprintf(temp, "%f", array[k] ); fputs(temp, out);
					if(k+1<num) fputs(",", out);
				}
				fputs("\"", out);
			}
			break;

		case AttributeType_File:
			{
				File file;

				ret = attr.GetFile( &file );

				if(ret<0)
				{
					return ret;
				}
				
				unsigned int file_size=0;
				
				file_size = file.GetSize();
				void * file_image = malloc( file_size );
				ret = file.Load( file_image, file_size );

				if(ret<0)
				{
					free(file_image);
					return ret;
				}
				
				FILE *fp;
				
				int k=0;
				
				n_file++;
				
				sprintf(src[n_file], "%s/temp_%d", dir_path, k);
				while(path_info(src[n_file]) != _NOT_EXIST) {
					k++;
					sprintf(src[n_file], "%s/temp_%d", dir_path, k);
				}
				
				fp = fopen(src[n_file], "wb");
				if(fp!=NULL) {
					fwrite(file_image, file_size, 1, fp);
					fclose(fp);
				} else print_load((char *) "Error : failed to open %s", src[n_file]);

				free(file_image);
				
				strcpy(input[n_file], attr.GetName());
				
				sprintf(dst_name[n_file], "%s_%s", element.GetName(), attr.GetName());
			}
			break;

		case AttributeType_ID:
			{
				const char * id;

				ret = attr.GetID( &id );

				if(ret<0)
				{
					return ret;
				}
				
				sprintf(temp, " %s=\"%s\"", attr.GetName(), id); fputs(temp, out);
				
				have_ID = 1; strcpy(NameID, id);
				
				strcpy(dst_name[n_file], id);
				
			}
			break;

		case AttributeType_IDRef:
			{
				const char * id;
				Element entity;

				ret = attr.GetIDRef( &id, &entity );

				if(ret<0)
				{
					return ret;
				}
				
				strcpy(dst_name[n_file], id);
				
				sprintf(temp, " %s=\"%s\">\n", attr.GetName(), id); fputs(temp, out);
				
				if(strcmp(table[lv_table], element.GetName()) == 0) {
					lv_table++;
					strcpy(table[lv_table], entity.GetName());
				} else {
					lv_table++;
					strcpy(table[lv_table], element.GetName());
				}
				
				dump_element( entity, indent+1 , out, dir_path);
				
				if(i!=element.NumAttribute()-1) {
					print_indent(indent+1, out);
					sprintf(temp, "<%s", entity.GetName()); fputs(temp, out);
				} else close=0;
			}
			break;

		default:
			sprintf(temp, " %s=\"invalid type\"", attr.GetName()); fputs(temp, out );
			return -1;
		}
	}
	
	for(i=0; i <= n_file; i++) {
		
		// 1 ID and several file ex: sound
		if( have_ID==1 && n_file>0 )  sprintf(dst_name[i], "%s_%s", NameID, input[i]);
			
		fputs(" ", out);
		fputs(input[i], out); 
		fputs("=\"", out);
		fputs(dst_name[i], out);
		
		char dst[128];
		
		sprintf(dst, "%s/%s", dir_path, dst_name[i]);
		if(path_info(dst) != _NOT_EXIST) {
			// todo compare hashe to be sure that file are the same
			fputs("\"", out);
			Delete(src[i]);
			continue;
		}
		if(strstr(dst, "/")) {
			char dir[128];
			strcpy(dir, dst);
			dir[strrchr(dir, '/') - dir] = 0;
			mkdir_rec(dir);
		}
		rename(src[i], dst);
		
		print_load((char *) "FILE : %s", dst_name[i]);
		
		while(1) 
		{
			FILE *in;
			FILE *f;
			u32 magic;
			
			in = fopen(dst, "rb");
			if(in == NULL) {
				print_load((char *) "Warning : can't open %s ", dst);
				break;
			}
			fread(&magic, sizeof(u32), 1, in);
			fclose(in);
			
			if( (magic>>16) == 0x78DA ) { // libz : compressed file
			
				strcpy(temp, dst);
				strcat(temp, ".lz");
				rename(dst, temp);
				
				int size_in;				
				char *data_in = LoadFile(temp, &size_in);
				if(data_in==NULL) break;
				
				int size_out = zlib_decompressed_size(data_in, size_in);
				
				char *data_out = (char *) malloc(size_out);
				if(data_out==NULL) {free(data_in); break;}
				
				zlib_decompress(data_in, data_out, size_in, &size_out);
				
				free(data_in);
				
				f = fopen(dst, "wb");
				if(f == NULL) {free(data_out); break;}
				fwrite(data_out, size_out, 1, f);
				fclose(f);
				
				free(data_out);
				
				continue;
				
			} else
			if( magic == 0x5F524146) { // _RAF : compressed RAF

				fputs("._RAF", out);
				
				strcpy(temp, dst);
				strcat(temp, "._RAF");
				rename(dst, temp);
				strcat(dst, ".RAF");
				
				int size_in;
				char *data_in = LoadFile(temp, &size_in);
				if(data_in==NULL) {
					print_load((char *) "Error : failed to load %s", temp); 
					break;
				}
				
				int size_out = 0;
				memcpy(&size_out, &data_in[4], 4);
				//size_out = zlib_decompressed_size(data_in+8, size_in);
				if(size_out==0) {
					print_load((char *) "Error : failed to get decompressed size %s", temp); 
					free(data_in);
					break;
				}
				
				char *data_out = (char *) malloc(size_out);
				if(data_out==NULL) {
					print_load((char *) "Error : failed to malloc data_out"); 
					free(data_in); 
					break;
				}
				
				size_out=0;
				zlib_decompress(data_in+8, data_out, size_in, &size_out);
				free(data_in);
				
				if(size_out==0) { 
					print_load((char *) "Error : failed to decompress %s", temp); 
					free(data_in);
					break;
				}

				f = fopen(dst, "wb");
				if(f == NULL) {
					print_load((char *) "Error : cannot open %s", dst); 
					free(data_out);
					break;
				}
				fwrite(data_out, size_out, 1, f);
				fclose(f);
				
				free(data_out);

				continue;
				
			} else
			if( magic == 0x2E47494D ) { // GIM : picture
				if(strcmp(&dst[strlen(dst)-4], ".gim") != 0){
					fputs(".gim", out);
					strcpy(temp, dst);
					strcat(temp, ".gim");
					rename(dst, temp);
					strcat(dst, ".png");
				} else {
					strcpy(temp, dst);
					dst[strlen(dst)-3]='p';
					dst[strlen(dst)-2]='n';
					dst[strlen(dst)-1]='g';
				}
			
				GIM2PNG(temp, dst);
				
				break;
			} else
			if(strcmp(&dst[strlen(dst)-4], ".gtf") == 0) { // GTF : picture
				strcpy(temp, dst);
				dst[strlen(dst)-3]='d';
				dst[strlen(dst)-2]='d';
				dst[strlen(dst)-1]='s';
				
				if( gtf2dds(temp, dst, 0, 0) == false ) break;
				
				strcpy(temp, dst);
				dst[strlen(dst)-3]='p';
				dst[strlen(dst)-2]='n';
				dst[strlen(dst)-1]='g';
				
				ConvertImage(temp, dst);
				
				break;
			
			} else
			if( magic == 0x56414770) { // VAG : sound
				if(strcmp(&dst[strlen(dst)-4], ".vag") != 0) {
					fputs(".vag", out);					
					strcpy(temp, dst);
					strcat(temp, ".vag");
					rename(dst, temp);
					strcat(dst, ".wav");
				} else {
					strcpy(temp, dst);
					dst[strlen(dst)-3]='w';
					dst[strlen(dst)-2]='a';
					dst[strlen(dst)-1]='v';
				}
				
				VAG2WAV(temp, dst); 
				
				break;
			} else
			if( magic == 0x56534D58) { // VSMX : script
				if(strcmp(&dst[strlen(dst)-4], ".jsx") != 0) {
					fputs(".jsx", out);
					strcpy(temp, dst);
					strcat(temp, ".jsx");
					rename(dst, temp);
					strcat(dst, ".js");
				} else {
					strcpy(temp, dst);
					dst[strlen(dst)-1]=0;
				}
				
				JSX2JS(temp, dst);
				
				break;
			} else 
			if( magic == 0x5241464F) { // RAF : cxml
				cxml_extract(dst);
				break;
			}
			
			break;
		}
		
		fputs("\"", out);
	}
	
	if(!have_child && close) fputs("/", out);
	
	if(close) fputs(">\n", out);
	
	for( Element child=element.GetFirstChild() ; child ; child=child.GetNextSibling() )
	{
		ret = dump_element( child, indent + 1, out, dir_path);
		if( ret<0 )
		{
			return ret;
		}
	}
	
	if(lv_table==indent) {
		print_indent(indent, out);
		sprintf(temp, "</%s>\n", table[lv_table]);
		fputs(temp, out);
		memset(table[lv_table], 0, sizeof(table[lv_table]));
		lv_table--;
	}
	
	return 0;
}

int dump_document(Document & doc , FILE *out,  char *dir_path)
{
	Element root = doc.GetDocumentElement();
	lv_table=-1;
	return dump_element( root, 0 , out, dir_path);
}

void cxml_extract(char *file_path)
{
	int ret;
	Document doc;
	
	FILE *out;
	char dir_path[128];
	char out_path[128];
	
	if(strstr("dev_flash", file_path) != NULL) {
		strcpy(dir_path, "/dev_hdd0/tmp");
		mkdir(dir_path, 0777);
		strcat(dir_path, "/CXML");
		mkdir(dir_path, 0777);
		strcat(dir_path, &strrchr(file_path, '/')[1]);
	} 
	else strcpy(dir_path, file_path);
	
	if(strrchr(strrchr(dir_path, '/'), '.') != NULL) {
		while(dir_path[strlen(dir_path)-1] != '.') dir_path[strlen(dir_path)-1] = 0;
		dir_path[strlen(dir_path)-1] = 0;
	}
	
	strcpy(out_path, dir_path);
	strcat(out_path, "/data.xml");
	
	mkdir(dir_path, 0777);
	
	out = fopen(out_path, "wb");
	if(out == NULL) {
		print_load((char *)"Error : failed to create xml");
		goto error;
	}
	// ----------------------------------------------

	ret = doc.CreateFromFile( file_path );
	if( ret<0 )
	{
		print_load((char *) "Error : Open failed. - %x\n", ret );
		goto error;
	}

	// ----------------------------------------------

	ret = dump_document(doc, out, dir_path);
	if( ret<0 )
	{
		print_load((char *) "Error : dump failed - %x\n", ret );
		goto error;
	}

	// ----------------------------------------------
	
error:
	if(out != NULL) fclose(out);
}
