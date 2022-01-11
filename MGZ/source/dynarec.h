#ifndef _DYNAREC_H
#define _DYNAREC_H

#include "extern.h"

// address of the payload
// IngPereira  =  0x8000000000700000ULL
// DeanK 	   =  BASE_ADDR  + 0x100ULL
#define DYNAREC_PAYLOAD_ADDR	0x8000000000700000ULL

u8 HaveDynarec();
void InstallDynarec();
void RemoveDynarec();
	
#endif