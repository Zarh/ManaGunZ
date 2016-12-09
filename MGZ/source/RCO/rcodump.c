/*
 * rcodump.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "iconv.h"

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#define makedir(s) mkdir(s, 0777);

#include "general.h"
#include "rcomain.h"
#include "xml.h"
#include "strfuncs.h"

#include "rcodump.h"
#include "vaghandler.h"
#include "vsmx.h"
#include "../gim2png.h"

#define MAX_LABEL_LEN 216

extern void print_load(char *format, ...);

uint8_t dump_resource (char *dest, rRCOEntry * entry, OutputDumpFunc outputfunc)
{

  if (file_exists (dest)) {
    warning ("Warning File '%s' already exists.", dest);
    return FALSE;
  }

  uint32_t len = 0;
  uint8_t *bufferMid = (uint8_t *) read_resource (entry, &len);

  if (!bufferMid) {
	warning ("Warning read_ressource failed");
    return FALSE;
  }
 
  if (!len) {
    warning ("Warning read_ressource failed 2");
    return FALSE;
  }

  if (len != entry->srcLenUnpacked)
    warning ("Warning Extracted resource size for does not match specified length.");

  uint8_t ret = outputfunc (dest, (void *) bufferMid, entry);

  free (bufferMid);
  return ret;
}

uint8_t dump_output_data (char *dest, void *buf, rRCOEntry * entry)
{
  FILE *fp = openwrite (dest);

  if (fp) {
    filewrite (fp, buf, entry->srcLenUnpacked);
    fclose (fp);
    return TRUE;
  }
  warning ("Unable to open to file '%s'.", dest);
  return FALSE;
}

uint8_t dump_output_wav(char *dest, void *buf, rRCOEntry * entry)
{
  int i;
  rRCOSoundEntry *rse = ((rRCOSoundEntry *) entry->extra);
  
  void **vagData = (void **) malloc (ENDIAN_SWAP(rse->channels) * sizeof (void *));
  int *vagLen = (int *) malloc (ENDIAN_SWAP(rse->channels) * sizeof (int));

  uint8_t ret;

  for (i = 0; i < ENDIAN_SWAP(rse->channels); i++) {
    vagLen[i] = rse->channelData[i * 2];
    vagData[i] = (void *) ((char *) buf + rse->channelData[i * 2 + 1]);
  }

  ret = vag2wav (dest, ENDIAN_SWAP(rse->channels), vagLen, vagData);
  free (vagData);
  free (vagLen);
  
  
  return ret;
}

uint8_t dump_output_gimconv (char *dest, void *buf, rRCOEntry * entry)
{
    char gim[260];
	char png[260];
	
    strcpy (gim, dest);
    char *dot = strrchr (gim, '.');

    if (!dot) dot = gim + strlen (gim);
    strcpy (dot, ".gim");
	
	strcpy (png, dest);
    char *dot2 = strrchr (png, '.');

    if (!dot2) dot2 = png + strlen (png);
    strcpy (dot2, ".png");

    if(dump_output_data(gim, buf, entry) == FALSE) return FALSE;
	
	gim2png(gim, png);
	
	return TRUE;
}

uint8_t dump_output_vsmxdec (char *dest, void *buf, rRCOEntry * entry)
{
  VsmxMem *vm = readVSMXMem (buf);
  FILE *fp = openwrite (dest);

  if (fp) {
    if (VsmxDecode (vm, fp)) {
      warning ("Unable to decode VSMX.  Dumping as data instead.");
      freeVsmxMem (vm);
      fclose (fp);
      return dump_output_data (dest, buf, entry);
    }
    freeVsmxMem (vm);
    fclose (fp);
    return TRUE;
  }
  warning ("Unable to open to file '%s'.", dest);
  return FALSE;
}

void dump_resources (char *labels, rRCOEntry * parent, const RcoTableMap extMap, char *pathPrefix)
{
	if (!parent || !parent->numSubentries)	return;

	char fullOutName[MAX_FILENAME_LEN];
	uint32_t extMapLen = 0;
	char dat[5] = "dat";

	strcpy (fullOutName, pathPrefix);
	char *outName = fullOutName + strlen (pathPrefix);

	while (extMap[extMapLen][0])
		extMapLen++;

	uint32_t i;
	rRCOEntry *entry;
	
	for (entry = parent->firstChild; entry; entry = entry->next) {
		char *ext = (char *) dat;
		if (entry->id == RCO_TABLE_IMG || entry->id == RCO_TABLE_MODEL) {
			uint32_t fmt = ((rRCOImgModelEntry *) entry->extra)->format;
			if (fmt <= extMapLen) ext = (char *) extMap[fmt];
		} else if (entry->id == RCO_TABLE_SOUND) {
			rRCOSoundEntry *rse = (rRCOSoundEntry *) entry->extra;
			if (rse->format == RCO_SOUND_VAG) strcpy (ext, "vag");
		}

		char *label = get_label_from_offset (labels, entry->labelOffset);
		uint32_t len = strlen (label);

		if (len > MAX_LABEL_LEN) len = MAX_LABEL_LEN;
		memcpy (outName, label, len);
		outName[len] = '.';

		OutputDumpFunc of = dump_output_data;

		if (entry->id == RCO_TABLE_IMG && ((rRCOImgModelEntry *) entry->extra)->format == RCO_IMG_GIM) 
		of = dump_output_gimconv;

		print_load(" %s", label);

		if(entry->id == RCO_TABLE_SOUND) {
			
			char wavName[255];
			strcpy(wavName , pathPrefix);
			strcat(wavName , label );
			strcat(wavName , ".wav");
			if (dump_resource(wavName, entry, dump_output_wav) == FALSE) warning("Warning : Unable to dump resource '%s.wav'", label);
			
			rRCOSoundEntry *rse = (rRCOSoundEntry *) entry->extra;
			char soundSetSrc[MAX_FILENAME_LEN] = "\0";

			
			for (i = 0; i < ENDIAN_SWAP(rse->channels); i++) {
				outName[len + 1] = '\0';
				if (!soundSetSrc[0]) {
					strcpy(soundSetSrc, fullOutName);
					strcpy(soundSetSrc + strlen (soundSetSrc), "ch*.vag");
				}
				
				sprintf (outName + len + 1, "ch%d.", i);
				
				strcpy (outName + strlen (outName), ext);
				
				uint32_t origAddr = entry->srcAddr, origLen = entry->srcLen, origLenUnpacked = entry->srcLenUnpacked;
				
				entry->srcLen = entry->srcLenUnpacked = ((rRCOSoundEntry *) entry->extra)->channelData[i * 2];
				entry->srcAddr += ((rRCOSoundEntry *) entry->extra)->channelData[i * 2 + 1];
				
				if (dump_resource (fullOutName, entry, of) == FALSE) warning ("Unable to dump resource '%s'.", label);
				
				entry->srcAddr = origAddr;
				entry->srcLen = origLen;
				entry->srcLenUnpacked = origLenUnpacked;
			}
			strcpy (entry->srcFile, soundSetSrc);
		}
		else {
			strcpy (outName + len + 1, ext);
			if (dump_resource (fullOutName, entry, of) == FALSE) warning ("Unable to dump resource '%s'.", label);
			
			strcpy (entry->srcFile, fullOutName);
			entry->srcLenUnpacked = filesize (fullOutName);
		}
		entry->srcAddr = 0;
		entry->srcLen = entry->srcLenUnpacked;
		entry->srcCompression = RCO_DATA_COMPRESSION_NONE;
	}
}

void dump_text_resources(char *labels, rRCOEntry * parent, uint8_t writeHeader, char *pathPrefix, uint8_t bWriteXML)
{
	if (!parent || !parent->numSubentries)
		return;

	FILE *fp;
	char fullOutName[MAX_FILENAME_LEN];

	uint32_t i;
	rRCOEntry *entry;

	for (entry = parent->firstChild; entry; entry = entry->next) {
		// read & decompress text data
		char *textBuffer;
		rRCOTextEntry *textEntry = ((rRCOTextEntry *) entry->extra);

		if (!(fp = fopen (entry->srcFile, "rb"))) return;
		
		if (entry->srcAddr) fseek (fp, entry->srcAddr, SEEK_SET);
		
		char *inBuffer = (char *) malloc (entry->srcLen);

		fileread (fp, inBuffer, entry->srcLen);
		fclose (fp);

		strcpy (fullOutName, pathPrefix);
		char *outName = fullOutName + strlen (pathPrefix);

		rcoxml_int_to_text (textEntry->lang, RCOXML_TABLE_TEXT_LANG, outName);
		// dirty, but since stuff is here conveniently, update srcFile
	
		print_load(" %s", outName);
		if (bWriteXML) {
			sprintf (entry->srcFile, "%s.xml", fullOutName);
			outName += strlen (outName);
			strcpy (outName, ".xml");
		} else {
			makedir (fullOutName);
			sprintf (entry->srcFile, "%s%c*.txt", fullOutName, DIR_SEPARATOR);
			outName += strlen (outName);
			outName[0] = DIR_SEPARATOR;
			outName++;
		}

		if (entry->srcCompression) {
			textBuffer = (char *) malloc (entry->srcLenUnpacked);
			if (entry->srcCompression == RCO_DATA_COMPRESSION_ZLIB) {
				int uRet = zlib_uncompress (textBuffer, entry->srcLenUnpacked, inBuffer,
				entry->srcLen);

				if (uRet != Z_OK && uRet != Z_DATA_ERROR) return;
				
				if (uRet == Z_DATA_ERROR) warning("Encountered 'data error' when decompressing text resource.");
			}
			free (inBuffer);
		} else
			textBuffer = inBuffer;

			iconv_t ic = NULL;

		if(bWriteXML) {
			if(!(fp = fopen (fullOutName, "wb"))) {
				warning ("Unable to write to file '%s'.", fullOutName);
				continue;
			}
				// put UTF-8 header
			fputc (0xEF, fp);
			fputc (0xBB, fp);
			fputc (0xBF, fp);
			fputs ("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n", fp);
			fprintf (fp, "<!-- This XML was generated by %s -->\n", APPNAME_VER);
			fputs ("<TextLang>\n", fp);
			

			char icSrctype[8];
			
			make_iconv_charset (icSrctype, textEntry->format, !parent->rco->eSwap);
			ic = iconv_open ("utf-8", icSrctype);
		}

		for (i = 0; i < textEntry->numIndexes; i++) {
			RCOTextIndex *idx = &(textEntry->indexes[i]);
			uint32_t len = strlen (get_label_from_offset (labels, idx->labelOffset));
			size_t dataLen = 0;
			if (len > MAX_LABEL_LEN) len = MAX_LABEL_LEN;
			
			if (idx->length) {
				uint32_t charWidth = RCO_TEXT_FMT_CHARWIDTH (textEntry->format);
				dataLen = idx->length;
				if (idx->length >= charWidth) 
				{
					int j;
					for (j = 0; j < (int) charWidth; j++) {
						if (textBuffer[idx->offset + idx->length - (j + 1)])
						break;
					}
					if (j == (int) charWidth)
					dataLen -= charWidth;
				}
			}
			
			if (!bWriteXML) {
				memcpy (outName, get_label_from_offset (labels, idx->labelOffset), len);
				strcpy (outName + len, ".txt");

				if (!(fp = fopen (fullOutName, "wb"))) {
					warning ("Unable to write to file '%s'.", fullOutName);
					continue;
				}
				if (writeHeader) {
					if (textEntry->format == RCO_TEXT_FMT_UTF32) {
						uint32_t bom = UTF32_BOM;
						if (!parent->rco->eSwap) bom = ENDIAN_SWAP (bom);
					filewrite (fp, &bom, sizeof (bom));
					} else 
					if (textEntry->format == RCO_TEXT_FMT_UTF8) {
						uint32_t bom = UTF8_BOM;
						filewrite (fp, &bom, 3);
					} else {
						uint16_t bom = UTF16_BOM;
						
						if (!parent->rco->eSwap) bom = ENDIAN_SWAP (bom);
						filewrite (fp, &bom, sizeof (bom));
					}
				}
				
				if (dataLen) filewrite (fp, textBuffer + idx->offset, dataLen);
				fclose (fp);
			}
			else {
				char* bufIn = textBuffer + idx->offset;
				uint8_t useCdata = (memchr(bufIn, '<', dataLen) || memchr(bufIn, '>', dataLen) || memchr(bufIn, '&', dataLen));
				fprintf(fp, "\t<Text name=\"%s\">", get_label_from_offset(labels, idx->labelOffset));
				if(useCdata)
					fputs("<![CDATA[", fp);
				
				char buf[4096];
				char* bufOut = buf;
				size_t outBufLen = 4096;
				
				uint32_t nullsStripped = 0;
				while(dataLen) {
					iconv(ic, (const char**) &bufIn, &dataLen, &bufOut, &outBufLen);
					if(buf == bufOut) {
						warning("iconv failed when converting resource '%s'.", get_label_from_offset(labels, idx->labelOffset));
						break;
					}
					// strip null characters - UTF-8's encoding scheme doesn't contain null bytes in itself, so this simple solution works nicely :)
					char* bufTmp;
					for(bufTmp=buf; bufTmp<bufOut; bufTmp++) {
						if(*bufTmp)
							fputc(*bufTmp, fp);
						else
							nullsStripped++;
					}
					outBufLen = 4096;
					bufOut = buf;
				}
				if (nullsStripped) 
					warning ("%d null(s) were stripped from resource '%s'.", nullsStripped, get_label_from_offset (labels, idx->labelOffset));
				
				if (useCdata) fputs ("]]>", fp); fputs ("</Text>\n", fp);
				
			}
		}
		if (bWriteXML) {
			fputs ("</TextLang>\n", fp);
			fclose (fp);
			iconv_close (ic);
		}
		free (textBuffer);
	}
}

void compile_vagconv_map (rRCOFile * rco, rRCOEntry * entry, void *arg)
{
  rRCOSoundEntry *rse = (rRCOSoundEntry *) entry->extra;

  if (entry->id != RCO_TABLE_SOUND || entry->type != 1 ||
      rse->format != RCO_SOUND_VAG)
    return;

  if (entry->srcFile[0] && entry->srcAddr == 0 &&
      entry->srcCompression == RCO_DATA_COMPRESSION_NONE &&
      !strcasecmp (entry->srcFile + strlen (entry->srcFile) - 4, ".wav")) {
    uint32_t len;
    int i;

    rse->channels = wav2vag (entry->srcFile, &len, &entry->srcBuffer, "");
    if (!rse->channels) {
      error ("WAV->VAG conversion failed for '%s'",
	  get_label_from_offset (rco->labels, entry->labelOffset));
      return;
    }
    entry->srcFile[0] = '\0';
    entry->srcLen = entry->srcLenUnpacked = len * rse->channels;
    entry->srcCompression = RCO_DATA_COMPRESSION_NONE;

    if (!rse->channelData)
      rse->channelData =
	  (uint32_t *) malloc (rse->channels * sizeof (uint32_t) * 2);
    for (i = 0; i < rse->channels; i++) {
      rse->channelData[i * 2] = len;
      rse->channelData[i * 2 + 1] = len * i;
    }
  }
}

void compile_vsmxconv_map (rRCOFile * rco, rRCOEntry * entry, void *arg)
{
  if (entry->id != RCO_TABLE_VSMX || entry->type != 1)
    return;
  if (entry->srcFile[0] && entry->srcAddr == 0 &&
      entry->srcCompression == RCO_DATA_COMPRESSION_NONE &&
      !strcasecmp (entry->srcFile + strlen (entry->srcFile) - 4, ".txt")) {
    FILE *fin = fopen (entry->srcFile, "rb");

    if (fin) {
      VsmxMem *vm = VsmxEncode (fin);

      if (vm) {
	entry->srcBuffer = writeVSMXMem (&entry->srcLen, vm);
	entry->srcLenUnpacked = entry->srcLen;
	entry->srcFile[0] = '\0';
	entry->srcCompression = RCO_DATA_COMPRESSION_NONE;
	freeVsmxMem (vm);
      } else
	error ("Could not encode VSMX!");
      fclose (fin);
    }
  }
}

void compile_wavcheck_map (rRCOFile * rco, rRCOEntry * entry, void *arg)
{
  if (entry->id == RCO_TABLE_SOUND && entry->type == 1 &&
      ((rRCOSoundEntry *) entry->extra)->channels == 0)
    warning ("Unable to determine channel data for sound '%s'.",
	get_label_from_offset (rco->labels, entry->labelOffset));
}
