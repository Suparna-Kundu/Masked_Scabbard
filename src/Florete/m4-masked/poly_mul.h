#ifndef POLYMUL_H
#define POLYMUL_H

#include "SABER_params.h"

extern void polymul_asm(uint16_t *r, const uint16_t *a, const uint16_t *b);
void poly_mul(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N]);

#endif
