#ifndef __BD_H__
#define __BD_H__

#define PIC_LEN		0x73

u8 get_keys(u8 *d1, u8 *d2, u8 *pic);
u8 get_redump_log(char *log_path, char *pic_path);

void dec_d2(unsigned char* d2);
void dec_d1(unsigned char* d1);
void enc_d2(unsigned char* d2);
void enc_d1(unsigned char* d1);


#endif


