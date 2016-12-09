#ifndef _ECDSA_H_
#define _ECDSA_H_

int ecdsa_set_curve(unsigned int type);
void ecdsa_set_pub(unsigned char *Q);
void ecdsa_set_priv(unsigned char *k);
int ecdsa_verify(unsigned char *hash, unsigned char *R, unsigned char *S);
void ecdsa_sign(unsigned char *hash, unsigned char *R, unsigned char *S);

#endif
