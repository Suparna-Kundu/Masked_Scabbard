#include "SABER_indcpa.h"
#include "randombytes.h"
#include "pack_unpack.h"
#include "fips202.h"
#include "poly.h"
#include "verify.h"
#include <string.h>
#include <stdlib.h>

// #ifdef PROFILE_HASHING
// #include "hal.h"
// #include "sendfn.h"
// unsigned long long comparator_cycles;
// #define printcycles(S, U) send_unsignedll((S), (U))
// #endif

void indcpa_kem_keypair(uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t sk[SABER_INDCPA_SECRETKEYBYTES])
{
    uint8_t *seed_A = pk + SABER_POLYCOMPRESSEDBYTES; // pk[1] <- seed_A
    uint8_t *seed_s = sk; // temporary storage

    randombytes(seed_A, SABER_SEEDBYTES);
    randombytes(seed_s, SABER_NOISE_SEEDBYTES);
    shake128(seed_A, SABER_SEEDBYTES, seed_A, SABER_SEEDBYTES); // for not revealing system RNG state

    MatrixVectorMulKeyPair(pk, sk); // pk[0] <- Pack(Round((A^T)*s)), sk <- s
}


void indcpa_kem_enc(const uint8_t m[SABER_KEYBYTES], const uint8_t seed_sp[SABER_NOISE_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t ciphertext[SABER_BYTES_CCA_DEC])
{
    const uint8_t *seed_A = pk + SABER_POLYCOMPRESSEDBYTES;
    uint8_t *ct0 = ciphertext;
    uint8_t *ct1 = ciphertext + SABER_POLYCOMPRESSEDBYTES;
    uint16_t sp[SABER_N];

    GenSecret(sp, (uint8_t *)seed_sp, 0);
    MatrixVectorMulEnc(ct0, seed_A, sp, 0); // ct[0] <- Pack(Round(A*s'))
    InnerProdEnc(ct1, pk, sp, m, 0); // ct[1] <- Pack(Round(b*s' + m'))
}

uint8_t indcpa_kem_enc_cmp(const uint8_t m[SABER_KEYBYTES], const uint8_t seed_sp[SABER_NOISE_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC])
{
    uint32_t fail = 0;
    const uint8_t *seed_A = pk + SABER_POLYCOMPRESSEDBYTES;
    const uint8_t *ct0 = ciphertext;
    const uint8_t *ct1 = ciphertext + SABER_POLYCOMPRESSEDBYTES;
    uint16_t sp[SABER_N];

    // #ifdef PROFILE_HASHING
    // unsigned long long t0, t1;
    // t0 = hal_get_time();
    // #endif

    GenSecret(sp, (uint8_t *)seed_sp, 0);

    // #ifdef PROFILE_HASHING
    // t1 = hal_get_time();
    // comparator_cycles = t1 - t0;
    // printcycles("GenSecret_masked_HO cycles:", comparator_cycles);
    // #endif


    fail |= MatrixVectorMulEnc((uint8_t *)ct0, seed_A, sp, 1); // verify(ct[0], Pack(Round(A*s')))
    fail |= InnerProdEnc((uint8_t *)ct1, pk, sp, m, 1); // verify(ct[1], Pack(Round(b*s' + m')))
    fail = (~fail + 1);
    fail >>= 31;

    return (uint8_t)fail;
}

void indcpa_kem_dec(const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC], uint8_t m[SABER_KEYBYTES])
{
    InnerProdDec(m, ciphertext, sk); // m <- Pack(Round(b'*s - cm))
}

void original_msg(unsigned char *buf1_byte,unsigned char *buf_byte)
{
	uint32_t i;
	uint16_t buf1[SABER_N];
	
	//-------unpack buf1_byte---------
  	
  	BS2POLmsg(buf1_byte, buf1);

	for(i=0;i<SABER_N/3;i++)
	{
		if(((buf1[i]==0)&&(buf1[(SABER_N/3)+i]==0)&&(buf1[2*(SABER_N/3)+i]==0))||((buf1[i]==0)&&(buf1[(SABER_N/3)+i]==0)&&(buf1[2*(SABER_N/3)+i]==1))||((buf1[i]==0)&&(buf1[(SABER_N/3)+i]==1)&&(buf1[2*(SABER_N/3)+i]==0))||((buf1[i]==1)&&(buf1[(SABER_N/3)+i]==0)&&(buf1[2*(SABER_N/3)+i]==0)))
			buf1[i] = 0;
		if(((buf1[i]==1)&&(buf1[(SABER_N/3)+i]==1)&&(buf1[2*(SABER_N/3)+i]==1))||((buf1[i]==1)&&(buf1[(SABER_N/3)+i]==1)&&(buf1[2*(SABER_N/3)+i]==0))||((buf1[i]==1)&&(buf1[(SABER_N/3)+i]==0)&&(buf1[2*(SABER_N/3)+i]==1))||((buf1[i]==0)&&(buf1[(SABER_N/3)+i]==1)&&(buf1[2*(SABER_N/3)+i]==1)))
			buf1[i] = 1;
	}
	for(i=0;i<SABER_N/24;i++)
	{
		buf_byte[i] = ( buf1[ 8*i + 0 ] & 0x01)|(( buf1[ 8*i + 1 ] & 0x01)<<1)|(( buf1[ 8*i + 2 ] & 0x01)<<2)|(( buf1[ 8*i + 3 ] & 0x01)<<3)|(( buf1[ 8*i + 4 ] & 0x01)<<4)|(( buf1[ 8*i + 5] & 0x01)<<5)|(( buf1[ 8*i + 6 ] & 0x01)<<6)|(( buf1[ 8*i + 7 ] & 0x01)<<7);
	}	
}

/*
-------------------------------------------
       Higher order masking functions
-------------------------------------------
*/

uint8_t indcpa_kem_enc_cmp_masked_HO(const uint8_t m[SABER_SHARES][3*SABER_KEYBYTES], const uint8_t seed_sp[SABER_SHARES][SABER_NOISE_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC])
{
    const uint8_t *seed_A = pk + SABER_POLYCOMPRESSEDBYTES;
    uint16_t sp[SABER_SHARES][SABER_N];
    uint16_t ct0[SABER_SHARES][SABER_N],ct1[SABER_SHARES][SABER_N];

    // #ifdef PROFILE_HASHING
    // unsigned long long t0, t1;
    // t0 = hal_get_time();
    // #endif

    GenSecret_masked_HO(sp, seed_sp);

    // #ifdef PROFILE_HASHING
    // t1 = hal_get_time();
    // comparator_cycles = t1 - t0;
    // printcycles("GenSecret_masked_HO cycles:", comparator_cycles);
    // #endif


    MatrixVectorMulEnc_masked_HO(ct0, seed_A, sp); // verify(ct[0], Pack(Round(A*s')))
    InnerProdEnc_masked_HO(ct1, pk, sp, m); // verify(ct[1], Pack(Round(b*s' + m')))
    

    uint16_t pksv[SABER_N];
	uint16_t op[SABER_N];
    uint8_t b[SABER_SHARES],out=0;
    int i;

    BS2POLp(ciphertext, pksv);
    BS2POLT(&ciphertext[SABER_POLYCOMPRESSEDBYTES], op);

    // #ifdef PROFILE_HASHING
    // unsigned long long t2, t3;
    // t2 = hal_get_time();
    // #endif

    masked_comparison_simple(b,ct0,ct1,pksv,op);
    for(i=0;i<SABER_SHARES;i++){
        out = out ^ b[i];
    }

    // #ifdef PROFILE_HASHING
    // t3 = hal_get_time();
    // comparator_cycles = t3 - t2;
    // printcycles("masked_comparison_new cycles cycles:", comparator_cycles);
    // #endif


    return out;
}

void indcpa_kem_dec_masked_HO(uint16_t s[SABER_SHARES][SABER_N], const uint8_t ciphertext[SABER_BYTES_CCA_DEC], uint8_t m[SABER_SHARES][SABER_KEYBYTES])
{
    InnerProdDec_masked_HO(m, ciphertext, s); // m <- Pack(Round(b'*s - cm))
}

