/*
 * rlzpack.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>

#define RLZI_WINDOW_SIZE	0x7FED	// *4 = 130,996 bytes (128KB - 76
					// bytes)
#define RLZI_DICTIONARY_SIZE	0x3FFFF	// *4 = 1,048,572 bytes (1MB - 4 bytes)

#define ABS_INPUT_POS ((unsigned long int) (rlzi->input + rlzi->inputpos))

/** Function Prototypes **/
int rlzcompress (void *output, int inlen, void *input, unsigned char mode);

// void sub_405810(int arg_CB8, int64_t arg_CB0);
void flush_output (void);
void write_output (void);
void write_bit (unsigned char *unk0ptr, unsigned char arg_flag);
void write_special (unsigned char *unk0ptr, int num, int arg_edx);
int write_match_len (unsigned char len, unsigned int arg_4);
int find_match (int *arg_0, unsigned char realMode);

#define logD(x) (log((long double)(x)) / (long double)0.30102999566398119521373889472449)

typedef struct {		// unk_421D80
  unsigned char literals[8 * 0xFF];	// grouped in 8 groups of 0xFF; group
  // selected by has of input position,
  // last byte and mode, the 0xFF part is
  // based on the input byte with various
  // shifts
  unsigned char distDescLong[0xF0];	// 30x8 (match >= 4)
  unsigned char distDescShort[0x40];	// 8x8 (match < 4)
  unsigned char distances[12 * 0x20];	// grouped in 0x20 based on bit
  // position
  unsigned char lenDesc[0x40];	// 8 x 8; group selected by bit position,
  // position is var_C from main function
  unsigned char matchlens[0xFF];

  void *input;			// 0xCA8
  void *output;			// 0xCAC
  // long dword_CB0; // 0xCB0 (0x422A30) - only wrtten to in sub_405810
  // long dword_CB4; // 0xCB4
  int64_t rangeOffset;		// 0xCB0 (0x422A30) - only written to in
  // sub_405810(), affected by write_bit and
  // write_match_len
  // - appears to be a data queue - top 24 bits not used, next 8 bits->data to
  // be written, next 8 bits->data mask; affected by CB8 in some way (CB8 is
  // added to this)
  long rangeSize;		// 0xCB8
  char nextOutputByte;		// 0xCBC - some byte offset; 3rd byte in CB0,
  // only ever used in sub_405810; guaranteed
  // never to == 0xFF
  char bytesToWrite;		// 0xCBD (0x422A3D) - only used in sub_405810
  char writeLock;		// 0xCBE - only ever used as a switch
  char lastSearchBack;		// 0xCBF - some byte flag used in find_match()
  unsigned long outputpos;	// 0xCC0 (0x422A40)
  // long unused_CC4; // 0xCC4 - align 8? - always 0 in program
  unsigned long inputpos;	// 0xCC8 (0x422A48)
  unsigned long inputlen;	// 0xCCC (0x422A4C)

  // window stores positions of stuff; the index itself is based on hashed data
  long window[RLZI_WINDOW_SIZE];	// 0xCD0-0x20C84
  // dictionary stores same stuff as window, but indexed on positions
  long dictionary[RLZI_DICTIONARY_SIZE];	// 1MB - dictionary??
  // long unused_120C80;

  float sgl_120C84;
  float sgl_120C88;		// starts as 0.0625 and increments by that
  // amount every time the dictionary coder fails
  // to pack stuff
} RLZ_Info;			// about 1.128MB
RLZ_Info rlzip;
RLZ_Info *rlzi = &rlzip;

/** Functions **/
// sub_406070
int
rlzcompress (void *output, int inlen, void *input, unsigned char mode)
{
  if (!inlen)
    return -1;			// sanity check

	/** ABOUT THE MODE ARGUMENT
	 *  The mode argument contains two values broken up like (___|45|678)
	 *  Bits 678 are the compression mode
	 *  Bits 45 determine the default values to store in literals/distances etc array
	 *  The first 3 bits aren't used
	 */
  int var_C = 0;		// var_C appears to do some tracking in regards

  //
  // to how well the dictionary coder is packing
  // things?
  char realMode;
  int dictSearchBack = 0;	// just assign something in case... :S

  // variables introduced by me
  unsigned int i;
  unsigned int matchLen = 0;

  // unsigned int iInputPosTemp;

  realMode = mode & 7;		// grab the compression mode

  // originally init_rlzi()
  rlzi->input = input;
  rlzi->inputlen = inlen;
  rlzi->output = output;
  rlzi->rangeOffset = 0;
  rlzi->rangeSize = -1;
  rlzi->nextOutputByte = 0;
  rlzi->bytesToWrite = 0;
  // no writeLock=0 - writeLock is _always_ assigned before calling the write
  // function anyway
  rlzi->lastSearchBack = 0;
  rlzi->outputpos = 0;
  rlzi->inputpos = 0;		// added by me

  rlzi->sgl_120C84 = 0;
  rlzi->sgl_120C88 = 0.0625;
  memset (rlzi->window, 0xFF, sizeof (rlzi->window));

  // grab the 2nd number from the mode
  // eax = (4 - ((mode >> 3) & 0x03)) << 5; // 12345678 -> 45
  /* ^ 4 possible combinations for the above if bits45 == 00 (should be) then
   * eax => 0x80 (10000000) if bits45 == 01 then eax => 0x60 (01100000) if
   * bits45 == 10 then eax => 0x40 (01000000) if bits45 == 11 then eax => 0x20
   * (00100000) */
  {
    unsigned char byteSet = ((4 - ((mode >> 3) & 0x03)) << 5);

    memset (rlzi->literals, byteSet, sizeof (rlzi->literals));
    memset (rlzi->distDescLong, byteSet, sizeof (rlzi->distDescLong));
    memset (rlzi->distDescShort, byteSet, sizeof (rlzi->distDescShort));
    memset (rlzi->distances, byteSet, sizeof (rlzi->distances));
    memset (rlzi->lenDesc, byteSet, sizeof (rlzi->lenDesc));
    memset (rlzi->matchlens, byteSet, sizeof (rlzi->matchlens));
  }

  unsigned char lastInputByte = 0;

  // main loop - this will loop until all the data is processed
  while (rlzi->inputpos < rlzi->inputlen)	// loc_4060D0
  {
    matchLen = find_match (&dictSearchBack, realMode);
    if (matchLen < 2)
      matchLen = 1;
    int sub_405B90_ret = write_match_len (matchLen - 1, var_C);

    if (matchLen == 1)		// no match found
    {
      // write literal
      // the following code was previously sub_405A10( (((((unsigned
      // int)rlzi->inputpos & 7) << 8) | lastInputByte) >> realMode) & 7 )
      int arg_ecx = (((((unsigned int) rlzi->inputpos & 7) << 8) | lastInputByte) >> realMode) & 7;	// top

      //
      // bit
      // in
      // (rlzi->inputpos
      // &
      // 7)
      // will
      // actually
      // be
      // discarded
      // -
      // that
      // is,
      // (rlzi->inputpos
      // &
      // 3)
      // should
      // give
      // the
      // same
      // result
      int oldRangeSize = rlzi->rangeSize;
      unsigned int oldOutputpos = rlzi->outputpos;
      unsigned int inputVal = *(unsigned char *) ABS_INPUT_POS + 0x100;

      for (; !(inputVal & 0x10000); inputVal <<= 1)	// loop 8 times
	write_bit ((unsigned char *) ((unsigned long int) rlzi->literals + arg_ecx * 0xFF + (inputVal >> 8) - 1), (inputVal >> 7) & 1);	// last
      //
      // arg
      // (now
      // deleted)
      // is
      // actually
      // ebx,
      // but
      // ebx
      // is
      // 3
      // at
      // this
      // time

      // these values are only ever used if realMode==7, and only in
      // find_match() function
#define scast_405A10(v) ((long double)((unsigned int)(v)))
      // (int) cast added to make it consistent with good rlz packer, but
      // unsure if this is correct...
      rlzi->sgl_120C84 +=
	  (float) (logD (scast_405A10 (oldRangeSize) /
	      scast_405A10 (rlzi->rangeSize)) + (int) ((rlzi->outputpos -
		  oldOutputpos - 1) * 8));
      rlzi->sgl_120C88 += 0.0625f;	// flt_41A3AC

      if (var_C > 0)
	var_C--;
    } else {
      // write distance instead of literal
      // originally sub_405C10(dictSearchBack, sub_405B90(matchLen -1, var_C),
      // matchLen)
      int searchBackPlus1 = dictSearchBack + 1;
      unsigned char *treeStore;

      // int o_ebx=ebx, o_ebp=ebp, o_esi=esi, o_edi=edi;
      int sbSignifBit = 0;
      int var_edi;

      i = 0;
      if ((searchBackPlus1 & 0xFFFFFFFE) > 0)	// if searchBackPlus1 has bits
	// other than the first set...
	// (that is, searchBackPlus1 !=
	// 0 && searchBackPlus1 != 1)
      {				// this condition _should_ always be true, as
	// min dictSearchBack is 1, and with +1, min
	// value for searchBackPlus1 is 2
	// find the position of the most significant "1"
	for (i = 2; (searchBackPlus1 >> i) > 0; i++) ;
	sbSignifBit = --i;	// put the bit position in ebp
      }

      if (matchLen < 4) {
	var_edi = 4;
	treeStore = rlzi->distDescShort;
      } else {
	var_edi = 16;
	treeStore = rlzi->distDescLong;
	sbSignifBit += 0xC;
      }

      int var_ebx = 1;
      int var_esi;

      do {			// write packed thing - perhaps a length of
	// next number descriptor?
	var_esi = ((sbSignifBit & var_edi) > 0 ? 1 : 0);	// check if
	// certain bit
	// in ebp is
	// set
	write_bit ((unsigned char *) ((unsigned long int)
		&treeStore[var_ebx * 8] + sub_405B90_ret), var_esi);
	var_edi >>= 1;
	var_ebx = var_esi + var_ebx * 2;
      }
      while (var_edi > 0);	// loop 3 or 5 times

      if (i > 0)		// should always be true
      {
	// write distance
	i--;
	write_special (rlzi->distances + i * 0x20, searchBackPlus1, i);
      }

      var_C = 7 - ((rlzi->inputpos + matchLen) & 1);
    }

    unsigned int bytesLeftMinus3 = rlzi->inputlen - rlzi->inputpos - 3;

    if (matchLen < bytesLeftMinus3)
      bytesLeftMinus3 = matchLen;
    for (i = 0; i < bytesLeftMinus3; i++)	// goes thru all the bytes just
      //
      // written and pushes some
      // things into the dictionary
    {
      unsigned int brHash = *(unsigned int *) (ABS_INPUT_POS + i) << 8;

      brHash %= RLZI_WINDOW_SIZE;

      rlzi->dictionary[(rlzi->inputpos + i) & RLZI_DICTIONARY_SIZE] =
	  rlzi->window[brHash];
      rlzi->window[brHash] = rlzi->inputpos + i;
    }

    rlzi->inputpos += matchLen;
    lastInputByte = *(unsigned char *) (ABS_INPUT_POS - 1);
    if (rlzi->outputpos == rlzi->inputlen)	// is the compressed output
      // larger than the original
      // stream?
      return -1;
  }

  write_match_len (0xFF, var_C);	// end marker or is this used for
  // flushing data?

  {				// originally sub_4058E0()
    i = (rlzi->writeLock ? 5 : 4);
    // rlzi->writeLock = 0;
    while (i--)
      flush_output ();
  }

  // stick the mode into the first byte of the output
  // (otherwise, first byte is guaranteed to be 0)
  *(unsigned char *) output = mode;

  return rlzi->outputpos;	// length of compressed data
}

// calls write_bit, write_special
// function handles some packing routines
int
write_match_len (unsigned char len, unsigned int arg_4)	// arg_4 -> something
							// that keeps track of
							// no. past blocks
							// packed with
							// find_match() (always
							//
							// var_C from
							// rlzcompress())
{
  // len is the length -1 (amount of data removed by dictionary coder), except
  // when 0xFF (when called after loop has finished)
  int i;
  char flagTemp;

  // determine how packed the data is - ie, 1 bytes removed? 2 bytes?, 4?, 8?
  // ...
  // or perhaps, this is actually outputting the length code!
  for (i = 0; i < 8; i++) {
    flagTemp = (len >= (1u << i) ? 1 : 0);
    write_bit ((unsigned char *) ((unsigned long int) &rlzi->lenDesc[i * 8] + arg_4),
	flagTemp);
    if (flagTemp == 0)
      break;
  }
  i--;
  if (i > 0)			// --> identical to if(len != 0); this will
    // only be true if len >= 1 (or len<0) - eg if
    // data was packed
  {
    i--;
    unsigned char *ptr = rlzi->matchlens + ((arg_4 & 7) + i * 8) * 4;

    write_special (ptr + ((rlzi->inputpos << i) & 3), len, i);
    i++;
  }
  return i;			// returns packing threshold?
}

// calls sub_405810
void
write_bit (unsigned char *unk0ptr, unsigned char arg_flag)
{
  unsigned int range = (unsigned int) rlzi->rangeSize;

  unsigned int pMid = (range >> 8) * (*unk0ptr);

  if (!arg_flag) {
    rlzi->rangeOffset += pMid;
    range -= pMid;
  } else {
    range = pMid;
    *unk0ptr += 0xFF;		// increase probability
  }
  *unk0ptr -= ((unsigned int) (*unk0ptr) >> 3);
  rlzi->rangeSize = (long) range;
  write_output ();
}

// calls write_bit (used to)sub_4059B0
// arg_4, always either rlzi->distances or rlzi->matchlens
// inputpos: either rlzi->inputpos or 0
// arg_edx is likely to be a 8bit value; something to do with bit position in
// distance
// distance: but can be "len" when called from write_match_len
void
write_special (unsigned char *unk0ptr, int num, int arg_edx)
// void write_special(int arg_4, int distance, int inputpos, int arg_ecx, int
// arg_edx)
{
  if (arg_edx > 255)
    printf ("ASSUMPTION FAILURE\n");
  // int var_ebx = ((inputpos << (arg_edx & 0xFF)) & 3) + arg_4 + ((arg_ecx &
  // 7)+arg_edx*8)*4;
  if (arg_edx >= 3) {
    write_bit (unk0ptr, (num >> arg_edx) & 1);
    arg_edx--;
    if (arg_edx >= 3) {
      write_bit (unk0ptr, (num >> arg_edx) & 1);
      arg_edx--;
    }
    unk0ptr++;
    if (arg_edx >= 3) {
      // previously sub_4059B0()
      unsigned int rangeTmp = (unsigned int) rlzi->rangeSize;

      arg_edx -= 2;
      while (arg_edx--) {
	rangeTmp >>= 1;
	if (((num >> (3 + arg_edx)) & 1) == 0) {
	  rlzi->rangeOffset += rangeTmp;
	}
      }
      arg_edx += 3;		// 2 (reverse previous subtraction), and +1 for
      //
      // the above loop
      rlzi->rangeSize = (long) rangeTmp;
      write_output ();
    }
  }
  do {
    write_bit (unk0ptr, (num >> arg_edx) & 1);
    unk0ptr++;
    arg_edx--;
  }
  while (arg_edx >= 0);
}

void
flush_output (void)
{
  // if byte CB3 is NOT 0xFF, OR dword CB4 is true
  // -- which means it can only be false if rlzi->rangeOffset ==
  // 0x00000000FF??????
  if ((rlzi->rangeOffset >> 0x18) != 0xFF) {
    unsigned char byteOut = rlzi->nextOutputByte;	// starts off as 0,

    // then becomes 3rd
    // byte of
    // rlzi->rangeOffset

    rlzi->nextOutputByte = (rlzi->rangeOffset >> 0x18) & 0xFF;
    do {
      if (rlzi->outputpos == rlzi->inputlen)
	return;
      *(unsigned char *) ((unsigned long int) rlzi->output + rlzi->outputpos) =
	  ((rlzi->rangeOffset >> 32) & 0xFF) + byteOut;
      rlzi->bytesToWrite--;
      rlzi->outputpos++;
      byteOut = 0xFF;
    }
    while (rlzi->bytesToWrite >= 0);
  }
  // loc_4058A4:
  rlzi->bytesToWrite++;
  // rlzi->rangeOffset = (arg_CB0 << 8) & 0xFFFFFFFF; // make sure high 32 bits
  //
  // are 0
  // rlzi->rangeSize = arg_CB8 << 8;
  rlzi->rangeOffset <<= 8;
  rlzi->rangeOffset &= 0xFFFFFFFF;	// make sure high 32 bits are 0
  rlzi->rangeSize <<= 8;
}

void
write_output (void)
{
  rlzi->writeLock = ((rlzi->rangeSize >> 0x18) & 0xFF ? 1 : 0);
  if (!rlzi->writeLock) {
    flush_output ();
  }
}

// sub_405CE0: arg_0 = buf
// this function determines how much data we can pack into a single byte
// return of 1 = can't compress; don't think this can return 0xFF or higher
// NEW: this function searches for distance-length, but doesn't actually encode
//
// anything
int
find_match (int *searchBackUsed, unsigned char realMode)
{
  int tempCompare = 0;
  int maxBlockSize = 0xFF, matchLen = 1, backRef;

  unsigned int bytesLeft = rlzi->inputlen - rlzi->inputpos;
  unsigned long int searchBack;	// not too sure about this variable's name

  char realMode7Threshold;
  int i;

  if (bytesLeft < 2)
    return 1;
  if (bytesLeft < 0xFF)		// if we have less bytes left than the maximum
    // block size
    maxBlockSize = bytesLeft;

  // realMode7Threshold = ((unsigned int)(rlzi->sgl_120C84 / rlzi->sgl_120C88 +
  //
  // 128.5) > 0x64); //dbl_41A3B8
  // realMode7Threshold = ((int)((unsigned int)(rlzi->sgl_120C84 /
  // rlzi->sgl_120C88 + 128.5)) > 0x64);
#define ROUND(n) ((int)((n) + 0.5))
  realMode7Threshold = (ROUND (rlzi->sgl_120C84 / rlzi->sgl_120C88) > -28);
  // the second line above generates output consistent with the good rlzpacker,
  //
  // but is this typecasting all correct?

  // check if we have a continuous copy of something
  searchBack = ABS_INPUT_POS - rlzi->lastSearchBack;	// byte_CBF only used
  // by find_match(); is
  // initially 0
  if ((unsigned int) rlzi->lastSearchBack < rlzi->inputpos 
	  && *(unsigned char *) (searchBack - 1) == *(unsigned char *) (ABS_INPUT_POS)
      && *(unsigned char *) (searchBack) == *(unsigned char *) (ABS_INPUT_POS + 1)) 
	  {
    // if we've found repeated bytes...
    *searchBackUsed = rlzi->lastSearchBack;
    matchLen = 2;
  }
  // no continuous copy from previously found stream - check if any
  // similarities in the past few (up to 3) bytes
  else if ((realMode == 7 && realMode7Threshold) || realMode != 7) {
    // i = (realMode == 7 ? 1 : 0);
    // while((unsigned int)i < rlzi->inputpos && i <= 3)
    for (i = (realMode == 7 ? 1 : 0); i <= 3; i++) {
      if ((unsigned int) i >= rlzi->inputpos)
	break;

      searchBack = ABS_INPUT_POS - i;
      if (*(unsigned char *) (searchBack - 1) ==
	  *(unsigned char *) (ABS_INPUT_POS)
	  && *(unsigned char *) (searchBack) ==
	  *(unsigned char *) (ABS_INPUT_POS + 1)) {
	*searchBackUsed = i;
	matchLen = 2;
	break;
      }
      // i++;
    }
  }
  // loc_405DB7:
  // if we have 2 bytes left in the buffer (remember, if there's 1 byte left,
  // this function would've
  // already returned), we'll either by able to pack 1 or 2 bytes into a single
  //
  // byte
  // We can pack 2 bytes into a byte if repeat bytes (above) have been found.
  if (maxBlockSize < 3) {
    return matchLen;
  }
  // loc_405DC9:
  // edx = ABS_INPUT_POS; - never actually read...
  unsigned int brHash = *(unsigned int *) ABS_INPUT_POS << 8;	// previously

  // eax

  backRef = rlzi->window[(unsigned int) brHash % RLZI_WINDOW_SIZE];
  while (backRef != -1) {	// found a back reference
    if (backRef < (int) (rlzi->inputpos - RLZI_DICTIONARY_SIZE - 1))	// is
      // the
      // backreference
      // out
      // of
      // bounds?
      break;

    unsigned int matchAmt = matchLen + 1;

    // verify that the current matchLen is valid?
    for (i = matchLen; i >= 0; i--) {
      if (*(unsigned char *) ((unsigned long int) rlzi->input + backRef + i) !=
	  *(unsigned char *) (ABS_INPUT_POS + i))
	goto loc_405F97;	// jumps to end of while-loop (not valid -
      // search for more references which could be
      // valid)
    }

    // see how much more we can match
    for (; matchAmt < maxBlockSize; matchAmt++) {
      // loc_405E70:
      if (*(unsigned char *)
	  (((unsigned long int) rlzi->input + matchAmt) + backRef) !=
	  *(unsigned char *) (((unsigned long int) rlzi->input + matchAmt) +
	      rlzi->inputpos))
	break;
    }
    i = rlzi->inputpos - backRef - 1;	// distance? penalising short matches
    // which have a large distance??
    if (matchAmt >= 3 && (matchAmt != 3 || (i <= 0x7F && (i <= 0x30 ||
		    realMode != 5)))) {
      tempCompare = 0;
      switch (matchAmt) {
	case (3):
	  tempCompare = 0x7E;
	  break;
	case (4):
	  tempCompare = 0x4400;
	  break;
	case (5):
	  tempCompare = 0x6A00;
	  break;
	case (6):
	  tempCompare = 0x28400;
	  break;
      }
      if (!tempCompare || (i <= tempCompare)) {
	matchLen = matchAmt;	// this is a good match
	*searchBackUsed = i;
	if (*searchBackUsed) {
	  // check if all matched is actually the same character
	  for (i = 0; i < matchAmt; i++) {
	    if (*(unsigned char *)
		((unsigned long int) rlzi->input + backRef) !=
		*(unsigned char *) (ABS_INPUT_POS + i))
	      break;
	  }
	  if (matchAmt == i) {	// all matched is all the same character!
	    do {		// see how far ahead we can go
	      if (*(unsigned char *)
		  ((unsigned long int) rlzi->input + backRef) !=
		  *(unsigned char *) (ABS_INPUT_POS + i))
		break;
	      i++;
	    }
	    while (i < maxBlockSize);
	    // loc_405F3D:
	    if (i == maxBlockSize) {
	      if (matchAmt <= 3)
		return 3;

	      // loc_405F60:
	      for (i = 3; i < matchAmt; i++)	// loop max of 6 times due to
		// code below
	      {
		if (i != 3 || (*searchBackUsed <= 0x7F &&
			(*searchBackUsed <= 0x30 || realMode != 5))) {
		  switch (i) {
		    case (3):
		      tempCompare = 0x7E;
		      break;
		    case (4):
		      tempCompare = 0x4400;
		      break;
		    case (5):
		      tempCompare = 0x6A00;
		      break;
		    case (6):
		      tempCompare = 0x28400;
		      break;
		    default:
		      return i;
		  }
		  if (*searchBackUsed <= tempCompare)
		    break;
		}
	      }
	      return i;
	    }
	  }
	}
	// loc_405F8F:
	if (matchAmt == maxBlockSize) {
	  // loc_406009:
	  if (maxBlockSize != 0xFF)
	    return maxBlockSize;
	  // since maxBlockSize <= 0xFF, this implies maxBlockSize==0xFF
	  if (bytesLeft <= 0xFF)	// if bytesLeft < 0xFF, then
	    // maxBlockSize < 0xFF will be true
	    // (enforced above), thus this line is
	    // essentially "if(bytesLeft == 0xFF)"
	  {
	    return 0xFD;	// or 0x100 - 3
	  }
	  // loc_406030:
	  // note, at this point, matchAmt = maxBlockSize = 0xFF, bytesLeft >
	  // 0xFF
	  if (bytesLeft == 0x100)
	    return 0xFD;
	  for (i = matchAmt; i < 0x101; i++)
	    if (*(unsigned char *)
		(ABS_INPUT_POS + i + backRef - rlzi->inputpos) !=
		*(unsigned char *) (ABS_INPUT_POS + i))
	      return 0xFD;
	  return 0xFF;
	}
      }
    }
  loc_405F97:
    backRef = rlzi->dictionary[backRef & RLZI_DICTIONARY_SIZE];
  }

  // loc_405FB4:
  if (matchLen == 2)
    rlzi->lastSearchBack = *searchBackUsed & 0xFF;
  return matchLen;
}
