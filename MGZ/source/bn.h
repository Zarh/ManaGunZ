#ifndef __BN_H
#define __BN_H

void bn_print(char *name, unsigned char *a, unsigned int n);
void bn_copy(unsigned char *d, unsigned char *a, unsigned int n);
int bn_compare(unsigned char *a, unsigned char *b, unsigned int n);
void bn_reduce(unsigned char *d, unsigned char *N, unsigned int n);
void bn_add(unsigned char *d, unsigned char *a, unsigned char *b, unsigned char *N, unsigned int n);
void bn_sub(unsigned char *d, unsigned char *a, unsigned char *b, unsigned char *N, unsigned int n);
void bn_to_mon(unsigned char *d, unsigned char *N, unsigned int n);
void bn_from_mon(unsigned char *d, unsigned char *N, unsigned int n);
void bn_mon_mul(unsigned char *d, unsigned char *a, unsigned char *b, unsigned char *N, unsigned int n);
void bn_mon_inv(unsigned char *d, unsigned char *a, unsigned char *N, unsigned int n);

#endif