#ifndef __EC_H
#define __EC_H

#include <string.h>
#include <stdio.h>

int ecdsa_set_curve(unsigned char *p, unsigned char *a, unsigned char *b, unsigned char *N, unsigned char *Gx, unsigned char *Gy);
void ecdsa_set_pub(unsigned char *Q);
void ecdsa_set_priv(unsigned char *k);
int ecdsa_verify(unsigned char *hash, unsigned char *R, unsigned char *S);
void ecdsa_sign(unsigned char *hash, unsigned char *R, unsigned char *S);

#endif