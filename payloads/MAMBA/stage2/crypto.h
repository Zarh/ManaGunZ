#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <lv1/inttypes.h>

/*
typedef struct
{
    int mode;                   //!<  encrypt/decrypt  
    unsigned long sk[32];       //!<  DES subkeys      
}
des_context;
*/
void xtea_ctr(u8 *key, u64 nounce, u8 *buf, int size);
/*
void des_init(void);
void des_destroy(void);

void des_setkey_enc(des_context *ctx, const u8 key[8]);
void des_crypt_ecb(des_context *ctx, const u8 input[8], u8 output[8]);
*/
#endif /* __CRYPTO_H__ */
