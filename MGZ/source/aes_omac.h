#ifndef _AES_OMAC_H_
#define _AES_OMAC_H_

#include "types.h"

#define AES_OMAC1_DIGEST_SIZE 0x10

void aes_omac1(unsigned char *digest, unsigned char *input, unsigned int length, unsigned char *key, unsigned int keybits);

#endif
