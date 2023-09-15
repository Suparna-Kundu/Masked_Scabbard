#ifndef PARAMS_H
#define PARAMS_H



/* Change this for different security strengths */
// #define SABER_L 2 /* LightSaber */
#define SABER_L 3 /* Saber */
// #define SABER_L 4 /* FireSaber */

/* Store the secret key as 2-bit value in [-mu/2, mu/2]
    Not compatible with testvectors that check the secret key for its reference value. */
// #define SABER_COMPRESS_SECRETKEY

/* Change these for different masked implementations */
#define SABER_SHARES 4 

/* Don't change anything below this line */
#if SABER_L == 2
    #define SABER_MU 2
    #define SABER_ET 3
    #define SABER_EP 9
    #define SABER_EQ 11
    #define SABER_N 512
    #define SABER_P 512
    #define SABER_Q 2048
#elif SABER_L == 3
    #define SABER_MU 2
    #define SABER_ET 4
    #define SABER_EP 9
    #define SABER_EQ 10
    #define SABER_N 768
    #define SABER_P 512
    #define SABER_Q 1024
#elif SABER_L == 4
    #define SABER_MU 2
    #define SABER_ET 5
    #define SABER_EP 9
    #define SABER_EQ 10
    #define SABER_N 1024
    #define SABER_P 512
    #define SABER_Q 1024
#endif



#define SABER_SEEDBYTES 32
#define SABER_NOISE_SEEDBYTES 32
#define SABER_KEYBYTES 32
#define SABER_HASHBYTES 32

#define SABER_POLYCOINBYTES (SABER_MU * SABER_N / 8)
#define SABER_POLYBYTES (SABER_EQ * SABER_N / 8)
#define SABER_POLYCOMPRESSEDBYTES (SABER_EP * SABER_N / 8)
#define SABER_SCALEBYTES_KEM (SABER_ET * SABER_N / 8)
#define SABER_INDCPA_PUBLICKEYBYTES (SABER_POLYCOMPRESSEDBYTES + SABER_SEEDBYTES)

#ifdef SABER_COMPRESS_SECRETKEY
    #define SABER_POLYSECRETBYTES (2 * SABER_N / 8)  // secret key is stored as 4-bit value in [-mu/2, mu/2]
#else
    #define SABER_POLYSECRETBYTES SABER_POLYBYTES // secret key is stored as q-bit value
#endif

#define SABER_INDCPA_SECRETKEYBYTES (SABER_L * SABER_POLYSECRETBYTES)
#define SABER_PUBLICKEYBYTES (SABER_INDCPA_PUBLICKEYBYTES)
#define SABER_SECRETKEYBYTES (SABER_INDCPA_SECRETKEYBYTES + SABER_INDCPA_PUBLICKEYBYTES + SABER_HASHBYTES + SABER_KEYBYTES)
#define SABER_BYTES_CCA_DEC (SABER_POLYCOMPRESSEDBYTES + SABER_SCALEBYTES_KEM)



#endif
