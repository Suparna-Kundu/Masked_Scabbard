#include "poly.h"
#include "poly_mul.h"
#include "cbd.h"
#include "cbd-masked.h"
#include "fips202.h"
#include "fips202-masked.h"
#include "pack_unpack.h"
#include "masksONOFF.h"
#include "A2B.h"

// #ifdef PROFILE_HASHING
// #include "hal.h"
// #include "sendfn.h"
// unsigned long long measure_cycles;
// #define printcycles(S, U) send_unsignedll((S), (U))
// #endif

#define h1 (1 << (SABER_EQ - SABER_EP - 1))
#define h2 ((1 << (SABER_EP - 2)) - (1 << (SABER_EP - SABER_ET - 1)) + (1 << (SABER_EQ - SABER_EP - 1)))
#define MAX(a,b) (((a)>(b))?(a):(b))

static inline shake128incctx shake128_absorb_seed(const uint8_t seed[SABER_SEEDBYTES])
{
    shake128incctx ctx;
    shake128_inc_init(&ctx);
    shake128_inc_absorb(&ctx, seed, SABER_SEEDBYTES);
    shake128_inc_finalize(&ctx);
    return ctx;
}

// noinline such that toom-cook can reclaim the memory of shake_out
static void __attribute__((noinline)) shake128_squeeze_poly(uint16_t poly[SABER_N], shake128incctx *ctx)
{
    uint8_t shake_out[SABER_POLYBYTES];

    shake128_inc_squeeze(shake_out, SABER_POLYBYTES, ctx);
    BS2POLq(shake_out, poly);
}

// noinline such that toom-cook can reclaim the memory of shake_out
static void __attribute__((noinline)) shake128_squeeze_secret(uint16_t s[SABER_N], shake128incctx *ctx)
{
    uint8_t shake_out[SABER_POLYCOINBYTES];

    shake128_inc_squeeze(shake_out, SABER_POLYCOINBYTES, ctx);
    cbd(s, shake_out);
}

void GenSecret(uint16_t s[SABER_L][SABER_N], uint8_t seed_s[SABER_NOISE_SEEDBYTES], int keypair)
{
    size_t i;
    uint8_t shake_out[SABER_L * SABER_POLYCOINBYTES];
    uint8_t *sk = seed_s; // temporary storage

    // #ifdef PROFILE_HASHING
    // unsigned long long t0, t1;
    // t0 = hal_get_time();
    // #endif

    shake128(shake_out, SABER_L * SABER_POLYCOINBYTES, seed_s, SABER_NOISE_SEEDBYTES);

    // #ifdef PROFILE_HASHING
    // t1 = hal_get_time();
    // measure_cycles = t1 - t0;
    // printcycles("shake128_masked_HO cycles:", measure_cycles);
    // #endif

    // #ifdef PROFILE_HASHING
    // unsigned long long t2, t3;
    // t2 = hal_get_time();
    // #endif

    for (i = 0; i < SABER_L; i++) {
        cbd(s[i], &shake_out[i * SABER_POLYCOINBYTES]);
    }

    // #ifdef PROFILE_HASHING
    // t3 = hal_get_time();
    // measure_cycles = t3 - t2;
    // printcycles("cbd_masked_HO cycles:", measure_cycles);
    // #endif

    if (keypair) { // during keypair generation, sk <- s
        POLVECmu2BS(sk, s);
    }
}

/* pk[0] <- Pack(Round((A^T)*s)) */
void MatrixVectorMulKeyPair(uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t sk[SABER_INDCPA_SECRETKEYBYTES])
{
    size_t i, j;
    uint16_t A[SABER_N];
    uint16_t s[SABER_N];
    uint16_t b[SABER_L][SABER_N];

    uint8_t *seed_A = pk + SABER_POLYVECCOMPRESSEDBYTES;
    uint8_t *seed_s = sk;
    shake128incctx shake_A_ctx = shake128_absorb_seed(seed_A);
    shake128incctx shake_s_ctx = shake128_absorb_seed(seed_s);

    for (i = 0; i < SABER_L; i++) {

        shake128_squeeze_secret(s, &shake_s_ctx);
        POLmu2BS(&sk[i * SABER_POLYSECRETBYTES], s); // sk <- s

        for (j = 0; j < SABER_L; j++) {

            shake128_squeeze_poly(A, &shake_A_ctx);

            if (i == 0) {
                poly_mul(s, A, b[j]);
            } else {
                poly_mul_acc(s, A, b[j]);
            }
        }
    }

    shake128_inc_ctx_release(&shake_A_ctx);
    shake128_inc_ctx_release(&shake_s_ctx);

    for (i = 0; i < SABER_L; i++) {

        // Round
        for (j = 0; j < SABER_N; j++) {
            b[i][j] = ((b[i][j] + h1) >> (SABER_EQ - SABER_EP));
        }

        // Pack
        POLp2BS(&pk[i * SABER_POLYCOMPRESSEDBYTES], b[i]);
    }
}



/**
 *  if (compare)
 *      verify(ct[0], Pack(Round(A*s')))
 *  else
 *      ct[0] <- Pack(Round(A*s'))
 */
uint32_t MatrixVectorMulEnc(uint8_t ct0[SABER_POLYVECCOMPRESSEDBYTES], const uint8_t seed_A[SABER_SEEDBYTES], uint16_t sp[SABER_L][SABER_N], int compare)
{
    size_t i, j;
    uint32_t fail = 0;
    uint16_t A[SABER_N];
    uint16_t bp[SABER_N];

    shake128incctx shake_A_ctx = shake128_absorb_seed(seed_A);

    for (i = 0; i < SABER_L; i++) {

        for (j = 0; j < SABER_L; j++) {

            shake128_squeeze_poly(A, &shake_A_ctx);

            if (j == 0) {
                poly_mul(sp[j], A, bp);
            } else {
                poly_mul_acc(sp[j], A, bp);
            }
        }

        for (j = 0; j < SABER_N; j++) {
            bp[j] = ((bp[j] + h1) >> (SABER_EQ - SABER_EP));
        }

        if (compare) {
            fail |= POLp2BS_cmp(&ct0[i * SABER_POLYCOMPRESSEDBYTES], bp);
        } else {
            POLp2BS(&ct0[i * SABER_POLYCOMPRESSEDBYTES], bp);
        }
    }

    shake128_inc_ctx_release(&shake_A_ctx);
    return fail;
}

/**
 *  if (compare)
 *      verify(ct[1], Pack(Round(b*s' + m')))
 *  else
 *      ct[1] <- Pack(Round(b*s' + m'))
 */
uint32_t InnerProdEnc(uint8_t ct1[SABER_SCALEBYTES_KEM], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint16_t sp[SABER_L][SABER_N], const uint8_t m[SABER_KEYBYTES], int compare)
{
    size_t j;
    uint32_t fail = 0;
    uint16_t b[SABER_N];
    uint16_t vp[SABER_N];
    uint16_t (*mp) = b;

    for (j = 0; j < SABER_L; j++) {

        BS2POLp(&pk[j * SABER_POLYCOMPRESSEDBYTES], b);

        if (j == 0) {
            poly_mul(sp[j], b, vp);
        } else {
            poly_mul_acc(sp[j], b, vp);
        }
    }

    BS2POLmsg(m, mp);

    for (j = 0; j < SABER_N; j++) {
        vp[j] = (vp[j] - (mp[j] << (SABER_EP - 1)) + h1) >> (SABER_EP - SABER_ET);
    }

    if (compare) {
        fail |= POLT2BS_cmp(ct1, vp);
    } else {
        POLT2BS(ct1, vp);
    }

    return fail;
}

/* m <- Pack(Round(b'*s - cm)) */
void InnerProdDec(uint8_t m[SABER_KEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC], const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES])
{
    size_t i;
    uint16_t v[SABER_N];
    uint16_t s[SABER_N];
    uint16_t bp[SABER_N];
    uint16_t (*cm) = bp;

    for (i = 0; i < SABER_L; i++) {

        BS2POLmu(&sk[i * SABER_POLYSECRETBYTES], s);

        BS2POLp(&ciphertext[i * SABER_POLYCOMPRESSEDBYTES], bp);

        if (i == 0) {
            poly_mul(s, bp, v);
        } else {
            poly_mul_acc(s, bp, v);
        }
    }

    BS2POLT(ciphertext + SABER_POLYVECCOMPRESSEDBYTES, cm);

    for (i = 0; i < SABER_N; i++) {
        v[i] = (v[i] + h2 - (cm[i] << (SABER_EP - SABER_ET)));
    }

    // #ifdef PROFILE_HASHING
    // unsigned long long t0, t1;
    // t0 = hal_get_time();
    // #endif

    for (i = 0; i < SABER_N; i++) {
        v[i] = v[i] >> (SABER_EP - 1);
    }

    // #ifdef PROFILE_HASHING
    // t1 = hal_get_time();
    // measure_cycles = t1 - t0;
    // printcycles("A2B 256 coefficients shift cycles:", measure_cycles);
    // #endif


    POLmsg2BS(m, v);
}


/*
-------------------------------------------
       Higher order masking functions
-------------------------------------------
*/


void GenSecret_masked_HO(uint16_t r[SABER_SHARES][SABER_L][SABER_N],const unsigned char seed[SABER_SHARES][SABER_NOISE_SEEDBYTES])
{
	uint8_t buf[SABER_SHARES][SABER_POLYVECCOINBYTES];


    // #ifdef PROFILE_HASHING
    // unsigned long long t0, t1;
    // t0 = hal_get_time();
    // #endif

	shake128_masked_HO(SABER_POLYVECCOINBYTES, buf, SABER_NOISE_SEEDBYTES, seed);	
   
    // #ifdef PROFILE_HASHING
    // t1 = hal_get_time();
    // measure_cycles = t1 - t0;
    // printcycles("shake128_masked_HO cycles:", measure_cycles);
    // #endif

    // #ifdef PROFILE_HASHING
    // unsigned long long t2, t3;
    // t2 = hal_get_time();
    // #endif

    cbd_masked_HO(r,buf);

    // #ifdef PROFILE_HASHING
    // t3 = hal_get_time();
    // measure_cycles = t3 - t2;
    // printcycles("cbd_masked_HO cycles:", measure_cycles);
    // #endif
}

void MatrixVectorMulEnc_masked_HO( uint16_t ct[SABER_SHARES][SABER_L][SABER_N], const uint8_t seed_A[SABER_SEEDBYTES], uint16_t sp[SABER_SHARES][SABER_L][SABER_N])
{
    size_t i, j, k;
    uint16_t A[SABER_N];
    uint16_t bp[SABER_SHARES][SABER_N];
    

    shake128incctx shake_A_ctx = shake128_absorb_seed(seed_A);

    for (i = 0; i < SABER_L; i++) {

        for (j = 0; j < SABER_L; j++) {

            shake128_squeeze_poly(A, &shake_A_ctx);

            for (k = 0; k < SABER_SHARES; k++) {
                if (j == 0) {
                    poly_mul(sp[k][j], A, bp[k]);
                } else {
                    poly_mul_acc(sp[k][j], A, bp[k]);
                }
            }
        }
        for (j = 0; j < SABER_N; j++) {
            bp[0][j] += h1;
        }
        for (k = 0; k < SABER_SHARES; k++){
            for (j = 0; j < SABER_N; j++) {
                ct[k][i][j] = bp[k][j];
            }
        }
        
    }
    
}

void InnerProdEnc_masked_HO(uint16_t ct1[SABER_SHARES][SABER_N], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint16_t sp[SABER_SHARES][SABER_L][SABER_N], const uint8_t m[SABER_SHARES][SABER_KEYBYTES])
{
    size_t j, k;
    uint16_t mp[SABER_SHARES][SABER_N];
    uint16_t vp[SABER_SHARES][SABER_N];
    uint16_t (*b) = mp[0];

    for (j = 0; j < SABER_L; j++) {

        BS2POLp(&pk[j * SABER_POLYCOMPRESSEDBYTES], b);

        for (k = 0; k < SABER_SHARES; k++) {
            if (j == 0) {
                poly_mul(sp[k][j], b, vp[k]);
            } else {
                poly_mul_acc(sp[k][j], b, vp[k]);
            }
        }
    }

    for (k = 0; k < SABER_SHARES; k++) {
        BS2POLmsg(m[k], mp[k]);
        for (j = 0; j < SABER_N; j++) {
            vp[k][j] = vp[k][j] - (mp[k][j] << (SABER_EP - 1));
            if (k == 0) {
                vp[k][j] += h1;
            }
        }
    }

    for (k = 0; k < SABER_SHARES; k++) {
        for (j = 0; j < SABER_N; j++) {
            ct1[k][j]= vp[k][j];
        }    
    }    
}

void InnerProdDec_masked_HO(uint8_t m[SABER_SHARES][SABER_KEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC], uint16_t s[SABER_SHARES][SABER_L][SABER_N])
{
    size_t i, j;
    uint16_t v[SABER_SHARES][SABER_N], vtemp[SABER_N][SABER_SHARES];
    uint16_t bp[SABER_N];
    uint16_t (*cm) = bp;

    for (i = 0; i < SABER_L; i++) {

        BS2POLp(&ciphertext[i * SABER_POLYCOMPRESSEDBYTES], bp);

        for (j = 0; j < SABER_SHARES; j++) {
            if (i == 0) {
                poly_mul(s[j][i], bp, v[j]);
            } else {
                poly_mul_acc(s[j][i], bp, v[j]);
            }
        }
    }

    BS2POLT(ciphertext + SABER_POLYVECCOMPRESSEDBYTES, cm);

    for (i = 0; i < SABER_N; i++) {
        v[0][i] += h2 - (cm[i] << (SABER_EP - SABER_ET));
    }

    // A2B conversion 

    for (j=0; j<SABER_SHARES; j++) 
	{	
		for(i=0;i<SABER_N;i++)
		{
			vtemp[i][j]= v[j][i]&(SABER_P-1);
		}
	}

    // #ifdef PROFILE_HASHING
    // unsigned long long t0, t1;
    // t0 = hal_get_time();
    // #endif

    A2B_bitsliced_msg(v, vtemp);

    // #ifdef PROFILE_HASHING
    // t1 = hal_get_time();
    // measure_cycles = t1 - t0;
    // printcycles("A2B 256 coefficients shift cycles:", measure_cycles);
    // #endif

    for (i = 0; i < SABER_SHARES; i++) {
        POLmsg2BS(m[i], v[i]);
    }
}