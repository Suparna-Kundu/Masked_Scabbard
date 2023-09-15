#ifndef PARAMS_H
#define PARAMS_H



/* Change this for different security strengths */
// #define SABER_L 10 /* LightSaber */
#define SABER_L 12 /* Saber */
// #define SABER_L 15 /* FireSaber */

/* Store the secret key as 2-bit value in [-mu/2, mu/2]
    Not compatible with testvectors that check the secret key for its reference value. */
// #define SABER_COMPRESS_SECRETKEY

/* Change these for different masked implementations */
#define SABER_SHARES 4 

/* Don't change anything below this line */
#if SABER_L == 10
    #define SABER_ET 6  //2+4
#elif SABER_L == 12
    #define SABER_ET 7  //3+4
#elif SABER_L == 15
    #define SABER_ET 9  //5+4
#endif

#define SABER_MU 6
#define SABER_EP 13
#define SABER_EQ 15
#define SABER_N 64

#define SABER_Q 32768
#define SABER_P 8192


#define SABER_SEEDBYTES 32
#define SABER_NOISE_SEEDBYTES 32
#define SABER_KEYBYTES 32
#define SABER_HASHBYTES 32

#define SABER_POLYCOINBYTES (SABER_MU * SABER_N / 8)
#define SABER_POLYVECCOINBYTES (SABER_L * SABER_POLYCOINBYTES)

#define SABER_POLYBYTES (SABER_EQ * SABER_N / 8)
#define SABER_POLYVECBYTES (SABER_L * SABER_POLYBYTES)

#define SABER_POLYCOMPRESSEDBYTES (SABER_EP * SABER_N / 8)
#define SABER_POLYVECCOMPRESSEDBYTES (SABER_L * SABER_POLYCOMPRESSEDBYTES)

#define SABER_SCALEBYTES_KEM (SABER_ET * SABER_N / 8)

#define SABER_INDCPA_PUBLICKEYBYTES (SABER_POLYVECCOMPRESSEDBYTES + SABER_SEEDBYTES)

#ifdef SABER_COMPRESS_SECRETKEY
    #define SABER_POLYSECRETBYTES (4 * SABER_N / 8)  // secret key is stored as 4-bit value in [-mu/2, mu/2]
#else
    #define SABER_POLYSECRETBYTES SABER_POLYBYTES // secret key is stored as q-bit value
#endif

#define SABER_INDCPA_SECRETKEYBYTES (SABER_L * SABER_POLYSECRETBYTES)
#define SABER_PUBLICKEYBYTES (SABER_INDCPA_PUBLICKEYBYTES)
#define SABER_SECRETKEYBYTES (SABER_INDCPA_SECRETKEYBYTES + SABER_INDCPA_PUBLICKEYBYTES + SABER_HASHBYTES + SABER_KEYBYTES)

#define SABER_BYTES_CCA_DEC (SABER_POLYVECCOMPRESSEDBYTES + SABER_SCALEBYTES_KEM)



#endif
