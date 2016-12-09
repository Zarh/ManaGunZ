/*
 * vaghandler.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

/**
 ** A big thanks goes to highboy for his VAG <-> WAV sample code, which this file is based upon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vaghandler.h"
#include "general.h"

const double f[5][2] = { {0.0, 0.0},
{60.0 / 64.0, 0.0},
{115.0 / 64.0, -52.0 / 64.0},
{98.0 / 64.0, -55.0 / 64.0},
{122.0 / 64.0, -60.0 / 64.0}
};

#define ROUND(x) ((int)(x<0 ? x-0.5 : x+0.5))

#define VAG_SIGNATURE 0x70474156
#define VAG_VERSION 0x4000000	// 0x2000000
PACK_STRUCT (VagHeader, {
      uint32_t signature;	// "VAGp"
      uint32_t version;		// 0x20
      uint32_t reserved;	// 0
      uint32_t dataSize;	// size of file - 0x30
      uint32_t frequency;
      uint8_t reserved2[12];	// 0
      char name[16];
      char unknown[16];
    });

PACK_STRUCT (VagChunk, {
      char predict_shift;	// upper 4 bits = predict, lower 4 bits = shift
      char flags;		// 0 or 7 (end)
      char s[14];
    });

#define WAV_SIGNATURE 0x46464952
#define WAV_FORMAT 0x45564157
#define WAV_S1_SIG 0x20746D66
#define WAV_S1_SIZE_PCM 16
#define WAV_PCM_FORMAT 1
#define WAV_S2_SIG 0x61746164
PACK_STRUCT (WavHeader, {
      uint32_t signature;	// "RIFF"
      uint32_t size;		// filesize - 8
      uint32_t format;		// "WAVE"
      uint32_t s1sig;		// "fmt "
      uint32_t s1size;		// 16 for PCM
      uint16_t audioFmt;	// PCM = 1
      uint16_t channels;
      uint32_t frequency;
      uint32_t byterate;	// = frequency
      // * channels *
      // bitDepth/8
      uint16_t sampleSize;	// = channels * bitDepth / 8
      uint16_t bitDepth;	// we'll always use 16
      uint32_t s2sig;		// "data"
      uint32_t s2size;		// = numSamples * channels * bitDepth/8 OR
      // size-36
    });

void es_WavHeader(WavHeader *w) 
{
      w->signature=ENDIAN_SWAP(w->signature);
      w->size=ENDIAN_SWAP(w->size);
      w->format=ENDIAN_SWAP(w->format);
      w->s1sig=ENDIAN_SWAP(w->s1sig);
      w->s1size=ENDIAN_SWAP(w->s1size);
      w->audioFmt=ENDIAN_SWAP(w->audioFmt);
      w->channels=ENDIAN_SWAP(w->channels);
      w->frequency=ENDIAN_SWAP(w->frequency);
      w->byterate=ENDIAN_SWAP(w->byterate);
      w->sampleSize=ENDIAN_SWAP(w->sampleSize);
      w->bitDepth=ENDIAN_SWAP(w->bitDepth);
	  w->s2sig=ENDIAN_SWAP(w->s2sig);
      w->s2size=ENDIAN_SWAP(w->s2size);
}

uint8_t vag2wav(const char *fWav, int numChannels, int *vagLen, void **vagData)
{

  FILE *fp = openwrite (fWav);

  if (!fp)
    return FALSE;

  char **vag = (char **) malloc (numChannels * sizeof (char *));

  memcpy (vag, vagData, numChannels * sizeof (char *));

  /* put WAV header */
  WavHeader wh;

  wh.signature = WAV_SIGNATURE;
  wh.format = WAV_FORMAT;
  wh.s1sig = WAV_S1_SIG;
  wh.s1size = WAV_S1_SIZE_PCM;
  wh.audioFmt = WAV_PCM_FORMAT;
  wh.channels = numChannels;
  wh.bitDepth = 16;
  wh.sampleSize = wh.channels * wh.bitDepth / 8;
  wh.s2sig = WAV_S2_SIG;

  int i, j;

  // read VAG header
  for (i = 0; i < numChannels; i++) {
    VagHeader *vh = (VagHeader *) (vag[i]);

    vag[i] += sizeof (VagHeader);

    wh.frequency = vh->frequency;
    // TODO: version check
    if (vh->signature != ENDIAN_SWAP(VAG_SIGNATURE) || vh->frequency != wh.frequency) {
      free (vag);
      fclose (fp);
      return FALSE;
    }
  }
  //wh.frequency = ENDIAN_SWAP(wh.frequency);
  wh.byterate = wh.sampleSize * wh.frequency;

  // take a guess at the length (we'll fix these later if wrong) - make
  // assumption that all channels are of same size
  wh.s2size = (((*vagLen - sizeof (VagHeader)) / sizeof (VagChunk)) - 1) * 28 /* samples */  * 2	/* 16bit
													 */  * numChannels;
  wh.size = wh.s2size + 28;
  
  es_WavHeader(&wh);
  filewrite(fp, &wh, sizeof (wh));

  int wavSamplesSize = numChannels * 28 * sizeof (int16_t);
  int16_t *wavSamples = (int16_t *) malloc (wavSamplesSize);
  double *factors = (double *) calloc (numChannels * 2, sizeof (double));

  while (TRUE) {
    uint8_t notEnded = FALSE;

    memset (wavSamples, 0, numChannels * 28);
    for (i = 0; i < numChannels; i++) {
      VagChunk *vc = (VagChunk *) (vag[i]);

      vag[i] += sizeof (VagChunk);
      if (vc->flags != 7) {
	int shift = vc->predict_shift & 0xF;
	int predict = (vc->predict_shift & 0xF0) >> 4;
	int samples[28];

	// expand 4bit -> 8bit
	for (j = 0; j < 14; j++) {
	  samples[j * 2] = vc->s[j] & 0xF;
	  samples[j * 2 + 1] = (vc->s[j] & 0xF0) >> 4;
	}
	for (j = 0; j < 28; j++) {
	  int s = samples[j] << 12;	// shift 4 bits to top range of int16_t

	  if (s & 0x8000)
	    s |= 0xFFFF0000;
	  double sample =
	      (double) (s >> shift) + factors[i * 2] * f[predict][0] +
	      factors[i * 2 + 1] * f[predict][1];
	  factors[i * 2 + 1] = factors[i * 2];
	  factors[i * 2] = sample;
	  wavSamples[j * numChannels + i] = (int16_t)  ENDIAN_SWAP_16(ROUND (sample));
	}
	notEnded = TRUE;
      }
    }

    if (!notEnded) break;
	
    filewrite (fp, wavSamples, wavSamplesSize);
  }

  free (vag);
  free (wavSamples);
  free (factors);

  if (wh.size != (uint32_t) (ftell (fp) - 8)) {	// fixup WAV sizes if wrong
    if (strcmp (fWav, "-")) {	// can only fix if not writing to stdout
      es_WavHeader(&wh);
	  wh.size = ftell (fp) - 8;
      wh.s2size = wh.size - 36;
      rewind (fp);
	  es_WavHeader(&wh);
      filewrite (fp, &wh, sizeof (wh));
    } else
      warning ("Written WAV lengths were incorrect - can't go back and fix.");
  }

  fclose (fp);
  
  
  return TRUE;
}

int
wav2vag (const char *fWav, uint32_t * len, void **vagData, const char *vagName)
{
  FILE *fp = openread (fWav);

  if (!fp)
    return 0;

  WavHeader wh;

  fileread (fp, &wh, sizeof (wh));

#define WAV2VAG_ERROR_EXIT(s) { \
		error(s, fWav); \
		fclose(fp); \
		return 0; \
	}

  if (wh.signature != WAV_SIGNATURE || wh.format != WAV_FORMAT)
    WAV2VAG_ERROR_EXIT ("File '%s' not a valid WAV file, conversion aborted.")
	if (wh.s1size != WAV_S1_SIZE_PCM) {
      warning
	  ("File '%s' appears to have a non-standard header length for PCM.  Attempting to auto-skip...",
	  fWav);
      fseek (fp,
	  sizeof (wh) + (wh.s1size - WAV_S1_SIZE_PCM) - sizeof (uint32_t) * 2,
	  SEEK_SET);
      fileread (fp, &wh.s2sig, sizeof (uint32_t));
    }
  if (wh.s1sig != WAV_S1_SIG || wh.s2sig != WAV_S2_SIG)
    WAV2VAG_ERROR_EXIT
	("File '%s' structure not supported by rcomage's VAG handler; conversion aborted.")
	if (wh.audioFmt != WAV_PCM_FORMAT || wh.bitDepth != 16)
      WAV2VAG_ERROR_EXIT
	  ("rcomage's VAG handler only supports 16-bit PCM data, file '%s' not converted.")
	  if (wh.channels > 9)
	WAV2VAG_ERROR_EXIT ("Channels number too high for '%s'.")
	    // if(wh.s2size != wh.size-36 || wh.size+8 != filesize(fWav) ||
	    // wh.sampleSize != wh.channels*wh.bitDepth/8)
	    // WAV2VAG_ERROR_EXIT("Bad size values in WAV header for '%s'.")
	int i, j, k;

  // size compression is 28 16-bit samples -> 16 bytes
  uint32_t numSamples = wh.s2size / wh.sampleSize;

  *len =
      (numSamples / 28 + (numSamples % 28 ? 2 : 1)) * sizeof (VagChunk) +
      sizeof (VagHeader);
  *vagData = calloc (1, *len * wh.channels);

  for (i = 0; i < wh.channels; i++) {
    VagHeader *vh = (VagHeader *) ((char *) (*vagData) + *len * i);

    vh->signature = VAG_SIGNATURE;
    vh->version = VAG_VERSION;
    vh->reserved = 0;
    vh->dataSize = ENDIAN_SWAP (*len - 0x30);
    vh->frequency = ENDIAN_SWAP (wh.frequency);
    strncpy (vh->name, vagName, 16);
  }

  uint32_t pos;
  int wavBufSize = 28 * (wh.bitDepth / 8) * wh.channels;
  int16_t *wavBuf = (int16_t *) malloc (wavBufSize);
  double *factors = (double *) calloc (wh.channels * 2, sizeof (double));
  double *factors2 = (double *) calloc (wh.channels * 2, sizeof (double));

  for (pos = 0; pos < numSamples; pos += 28) {
    if (!fileread (fp, wavBuf, wavBufSize)) {
      free (wavBuf);
      free (factors);
      free (factors2);
    WAV2VAG_ERROR_EXIT ("Premature end in WAV file '%s'; conversion failed.")}
    if (pos + 28 > numSamples)
      memset (wavBuf + ((numSamples -
		  pos) * (wh.bitDepth / 8) * wh.channels / sizeof (int16_t)), 0,
	  (28 - numSamples + pos) * (wh.bitDepth / 8) * wh.channels);

    uint32_t ch;

    for (ch = 0; ch < wh.channels; ch++) {
      VagChunk *vc =
	  (VagChunk *) ((char *) (*vagData) + *len * ch + sizeof (VagHeader) +
	  sizeof (VagChunk) * (pos / 28));

      // find_predict
      double min = 1e10;
      double predictBuf[5][28];
      int predict = 0, shift = 0;	// prevent gcc warnings
      double s1[5], s2[5];

      for (j = 0; j < 5; j++) {
	double max = 0;

	s1[j] = factors[ch * 2];
	s2[j] = factors[ch * 2 + 1];
	for (k = 0; k < 28; k++) {
	  double sample = (double) wavBuf[k * wh.channels + ch];

	  if (sample > 30719.0)
	    sample = 30719.0;
	  if (sample < -30720.0)
	    sample = -30720.0;
	  predictBuf[j][k] = sample - s1[j] * f[j][0] - s2[j] * f[j][1];
	  if (fabs (predictBuf[j][k]) > max)
	    max = fabs (predictBuf[j][k]);
	  s2[j] = s1[j];
	  s1[j] = sample;
	}
	if (max < min) {
	  min = max;
	  predict = j;
	}
	// ????
	// if(min <= 7) {
	// predict = 0;
	// break;
	// }
      }
      factors[ch * 2] = s1[predict];
      factors[ch * 2 + 1] = s2[predict];

      // find_shift
      uint32_t shiftMask;

      for (shift = 0, shiftMask = 0x4000; shift < 12; shift++, shiftMask >>= 1) {
	if (shiftMask & ((int) min + (shiftMask >> 3)))
	  break;
      }
      // so shift==12 if none found...

      vc->predict_shift = ((predict << 4) & 0xF0) | (shift & 0xF);
      vc->flags = (numSamples - pos >= 28 ? 0 : 1);

      // pack
      // I don't understand it, but it seems that the second transformation is
      // required to prevent a clipping sound effect although it should produce
      //
      // worse reconverts...
      int8_t outBuf[28];

      for (k = 0; k < 28; k++) {
	double s_double_trans =
	    predictBuf[predict][k] - factors2[ch * 2] * f[predict][0] -
	    factors2[ch * 2 + 1] * f[predict][1];
	// +0x800 for signed conversion??
	int sample =
	    (((int) ROUND (s_double_trans) << shift) + 0x800) & 0xFFFFF000;
	if (sample > 32767)
	  sample = 32767;
	if (sample < -32768)
	  sample = -32768;

	outBuf[k] = (int8_t) (sample >> 12);
	factors2[ch * 2 + 1] = factors2[ch * 2];
	factors2[ch * 2] = (double) (sample >> shift) - s_double_trans;
      }
      for (k = 0; k < 14; k++)
	vc->s[k] = ((outBuf[k * 2 + 1] << 4) & 0xF0) | (outBuf[k * 2] & 0xF);

      // checker code
      /* { int samples[28]; // expand 4bit -> 8bit for(j=0; j<14; j++) {
       * samples[j*2] = vc->s[j] & 0xF; samples[j*2+1] = (vc->s[j] & 0xF0) >>
       * 4; } for(j=0; j<28; j++) { int s = samples[j] << 12; // shift 4 bits
       * to top range of int16_t if(s & 0x8000) s |= 0xFFFF0000; double sample
       * = (double)(s >> shift) + factors2[ch*2] * f[predict][0] +
       * factors2[ch*2+1] * f[predict][1]; factors2[ch*2+1] = factors2[ch*2];
       * factors2[ch*2] = sample; if(wavBuf[j*wh.channels + ch] !=
       * (int16_t)ROUND(sample)) { printf("a"); } } } */
    }
  }

  free (wavBuf);
  free (factors);
  free (factors2);

  // put terminating chunk
  for (i = 0; i < wh.channels; i++) {
    VagChunk *vc =
	(VagChunk *) ((char *) (*vagData) + *len * (i + 1) - sizeof (VagChunk));
    vc->predict_shift = 0;
    vc->flags = 7;
    memset (&vc->s, 0x77, 14);
  }

  fclose (fp);
  return wh.channels;
}

/*
 * int wav2vag(const char* fWav, uint32_t* len, void** vagData, const char*
 * vagName) { FILE* fp = fopen(fWav, "rb"); if(!fp) return 0;
 *
 * WavHeader wh; fileread(fp, &wh, sizeof(wh));
 *
 * #define WAV2VAG_ERROR_EXIT(s) { \ error(s, fWav); \ fclose(fp); \ return 0;
 * \ }
 *
 * if(wh.signature != WAV_SIGNATURE || wh.format != WAV_FORMAT)
 * WAV2VAG_ERROR_EXIT("File '%s' not a valid WAV file, conversion aborted.")
 * if(wh.s1sig != WAV_S1_SIG || wh.s1size != WAV_S1_SIZE_PCM || wh.s2sig !=
 * WAV_S2_SIG) WAV2VAG_ERROR_EXIT("File '%s' structure not supported by
 * rcomage's VAG handler; conversion aborted.") if(wh.audioFmt !=
 * WAV_PCM_FORMAT || wh.bitDepth != 16) WAV2VAG_ERROR_EXIT("rcomage's VAG
 * handler only supports 16-bit PCM data, file '%s' not converted.")
 *
 * if(wh.channels > 9) WAV2VAG_ERROR_EXIT("Channels number too high for '%s'.")
 *
 * //if(wh.s2size != wh.size-36 || wh.size+8 != filesize(fWav) || wh.sampleSize
 * != wh.channels*wh.bitDepth/8) // WAV2VAG_ERROR_EXIT("Bad size values in WAV
 * header for '%s'.")
 *
 *
 * int i, j, k; // size compression is 28 16-bit samples -> 16 bytes uint32_t
 * numSamples = wh.s2size / wh.sampleSize; *len = (numSamples/28 + (numSamples
 * % 28 ? 2:1)) * sizeof(VagChunk) + sizeof(VagHeader); *vagData = calloc(1,
 * *len * wh.channels);
 *
 * for(i=0; i<wh.channels; i++) { VagHeader* vh =
 * (VagHeader*)((char*)(*vagData) + *len * i); vh->signature = VAG_SIGNATURE;
 * vh->version = VAG_VERSION; vh->reserved = 0; vh->dataSize = ENDIAN_SWAP(*len
 * - 0x30); vh->frequency = ENDIAN_SWAP(wh.frequency); strncpy(vh->name,
 * vagName, 16); }
 *
 * uint32_t pos; int wavBufSize = 28 * (wh.bitDepth/8) * wh.channels; int16_t* wavBuf
 * = (int16_t*)malloc(wavBufSize); double* factors =
 * (double*)calloc(wh.channels*2, sizeof(double)); double* factors2 =
 * (double*)calloc(wh.channels*2, sizeof(double)); for(pos=0; pos<numSamples;
 * pos += 28) { if(!fileread(fp, wavBuf, wavBufSize)) { free(wavBuf);
 * free(factors); free(factors2); WAV2VAG_ERROR_EXIT("Premature end in WAV file
 * '%s'; conversion failed.") }
 *
 * uint32_t ch; for(ch=0; ch<wh.channels; ch++) { VagChunk* vc =
 * (VagChunk*)((char*)(*vagData) + *len * ch + sizeof(VagHeader) +
 * sizeof(VagChunk)*(pos/28));
 *
 * // find_predict double min = 1e10; double predictBuf[5][28]; int predict,
 * shift; double s1, s2; for(j=0; j<5; j++) { double max = 0; s1 =
 * factors[ch*2]; s2 = factors[ch*2+1]; for(k=0; k<28; k++) { double sample =
 * (double)wavBuf[k*wh.channels + ch]; if(sample > 30719.0) sample = 30719.0;
 * if(sample < -30720.0) sample = -30720.0; predictBuf[j][k] = sample - s1 *
 * f[j][0] - s2 * f[j][1]; if(fabs(predictBuf[j][k]) > max) max =
 * fabs(predictBuf[j][k]); s2 = s1; s1 = sample; } if(max < min) { min = max;
 * predict = j; // ???? store s1 & s2 into temp place? } // ???? if(min <= 7) {
 * predict = 0; break; } } // ???? factors[ch*2] = s1; factors[ch*2+1] = s2;
 *
 * // find_shift uint32_t shiftMask; for(shift=0, shiftMask=0x4000; shift<12;
 * shift++, shiftMask>>=1) { if(shiftMask & ((int)min + (shiftMask >> 3)))
 * break; } // so shift==12 if none found...
 *
 * vc->predict_shift = ((predict << 4) & 0xF0) | (shift & 0xF); vc->flags =
 * (numSamples - pos >= 28 ? 0:1);
 *
 * // pack uint8_t outBuf[28]; for(k=0; k<28; k++) { double sample =
 * predictBuf[predict][k] - factors2[ch*2] * f[predict][0] - factors2[ch*2+1] *
 * f[predict][1]; int sample2 = ((int)(sample * (1 << shift)) + 0x800) &
 * 0xfffff000; if(sample2 > 32767) sample2 = 32767; if(sample2 < -32768) sample2
 * = -32768; outBuf[k] = (uint8_t)(sample2 >> 8); sample2 >>= shift;
 * factors2[ch*2+1] = factors2[ch*2]; factors2[ch*2] = (double)sample2 - sample;
 * } for(k=0; k<14; k++) vc->s[k] = (outBuf[k*2+1] & 0xF0) | ((outBuf[k*2] >> 4)
 * & 0xF); } }
 *
 * free(wavBuf); free(factors); free(factors2);
 *
 * // put terminating chunk for(i=0; i<wh.channels; i++) { VagChunk* vc =
 * (VagChunk*)((char*)(*vagData) + *len * (i+1) - sizeof(VagChunk));
 * vc->predict_shift = 0; vc->flags = 7; memset(&vc->s, 0x77, 14); }
 *
 * fclose(fp); return wh.channels; } */
