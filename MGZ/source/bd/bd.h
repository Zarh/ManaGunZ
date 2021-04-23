#ifndef __BD_H__
#define __BD_H__

//it's supposed to be 112=0x70, but 3key team used a len of 115=0x73 for ird.
//https://www.t10.org/ftp/t10/document.04/04-328r0.pdf#page=43
#define PIC_LEN		0x73

u8 get_keys(u8 *d1, u8 *d2, u8 *pic);
u8 dump_disc_key();

void dec_d2(unsigned char* d2);
void dec_d1(unsigned char* d1);
void enc_d2(unsigned char* d2);
void enc_d1(unsigned char* d1);


#endif /* _SYS_STORAGE_H__ */


