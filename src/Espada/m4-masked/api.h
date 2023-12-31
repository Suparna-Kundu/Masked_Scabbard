#ifndef API_H
#define API_H

#include "SABER_params.h"
#include <stdint.h>

#if SABER_L == 10
    #define CRYPTO_ALGNAME "LightSaber"
#elif SABER_L == 12
    #define CRYPTO_ALGNAME "Saber"
#elif SABER_L == 15
    #define CRYPTO_ALGNAME "FireSaber"
#else
    #error "Unsupported SABER parameter."
#endif

#define CRYPTO_SECRETKEYBYTES SABER_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES SABER_PUBLICKEYBYTES
#define CRYPTO_BYTES SABER_KEYBYTES
#define CRYPTO_CIPHERTEXTBYTES SABER_BYTES_CCA_DEC

int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
int crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

////////////////////////////////////////////////////////////////////////////////////////////////
///                                   Masking functions                                      ///
////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
    uint16_t s[SABER_SHARES][SABER_L][SABER_N]; // shared
    uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES];
    uint8_t hpk[SABER_SHARES][32]; // shared
    uint8_t z[SABER_KEYBYTES];
} sk_masked_s;

/*
-------------------------------------------
       Higher order masking functions
-------------------------------------------
*/

int crypto_kem_keypair_sk_masked_HO(sk_masked_s *sksv1, const uint8_t *sk);
int crypto_kem_dec_masked_HO(uint8_t *k, const uint8_t *c, sk_masked_s *sk_masked);


#endif
