#ifndef PACK_UNPACK_H
#define PACK_UNPACK_H

#include "SABER_params.h"
#include <stddef.h>
#include <stdint.h>


void POLmsg2BS(uint8_t bytes[3*SABER_KEYBYTES], const uint16_t data[SABER_N]);
void POLp2BS(uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const uint16_t data[SABER_N]);
void POLq2BS(uint8_t bytes[SABER_POLYBYTES], const uint16_t data[SABER_N]);
void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N]);
uint32_t POLp2BS_cmp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const uint16_t data[SABER_N]);
uint32_t POLT2BS_cmp(const uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N]);

void BS2POLmsg(const uint8_t bytes[3*SABER_KEYBYTES], uint16_t data[SABER_N]);
void BS2POLp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], uint16_t data[SABER_N]);
void BS2POLq(const uint8_t bytes[SABER_POLYBYTES], uint16_t data[SABER_N]);
void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[SABER_N]);

#ifdef SABER_COMPRESS_SECRETKEY
    void BS2POLmu(const uint8_t bytes[SABER_N / 4], uint16_t data[SABER_N]);
    void POLmu2BS(uint8_t bytes[SABER_N / 4], const uint16_t data[SABER_N]);
#else
    #define POLmu2BS POLq2BS
    #define BS2POLmu BS2POLq
#endif


#endif
