#include "api.h"
#include "randombytes.h"
#include "hal.h"
#include "fips202.h"

#include <string.h>

#define NTESTS 10

// https://stackoverflow.com/a/1489985/1711232
#define PASTER(x, y) x##y
#define EVALUATOR(x, y) PASTER(x, y)
#define NAMESPACE(fun) EVALUATOR(MUPQ_NAMESPACE, fun)

// use different names so we can have empty namespaces
#define MUPQ_CRYPTO_BYTES           NAMESPACE(CRYPTO_BYTES)
#define MUPQ_CRYPTO_PUBLICKEYBYTES  NAMESPACE(CRYPTO_PUBLICKEYBYTES)
#define MUPQ_CRYPTO_SECRETKEYBYTES  NAMESPACE(CRYPTO_SECRETKEYBYTES)
#define MUPQ_CRYPTO_CIPHERTEXTBYTES NAMESPACE(CRYPTO_CIPHERTEXTBYTES)
#define MUPQ_CRYPTO_ALGNAME NAMESPACE(CRYPTO_ALGNAME)

#define MUPQ_crypto_kem_keypair NAMESPACE(crypto_kem_keypair)
#define MUPQ_crypto_kem_enc NAMESPACE(crypto_kem_enc)
#define MUPQ_crypto_kem_dec NAMESPACE(crypto_kem_dec)
#define MUPQ_crypto_kem_crypto_kem_keypair_sk_masked_HO NAMESPACE(crypto_kem_keypair_sk_masked_HO)
#define MUPQ_crypto_kem_dec_masked_HO NAMESPACE(crypto_kem_dec_masked_HO)

const uint8_t canary[8] = {
  0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
};

/* allocate a bit more for all keys and messages and
 * make sure it is not touched by the implementations.
 */
static void write_canary(uint8_t *d) {
  for (size_t i = 0; i < 8; i++) {
    d[i] = canary[i];
  }
}

static int check_canary(const uint8_t *d) {
  for (size_t i = 0; i < 8; i++) {
    if (d[i] != canary[i]) {
      return -1;
    }
  }
  return 0;
}

static int test_keys(void)
{
  unsigned char key_a[MUPQ_CRYPTO_BYTES+16], key_b[MUPQ_CRYPTO_BYTES+16], key_c[MUPQ_CRYPTO_BYTES+16];
  unsigned char pk[MUPQ_CRYPTO_PUBLICKEYBYTES+16];
  unsigned char sendb[MUPQ_CRYPTO_CIPHERTEXTBYTES+16];
  unsigned char sk_a[MUPQ_CRYPTO_SECRETKEYBYTES+16];

  struct //__attribute__((__packed__)) //TODO: check alignment
  {
    unsigned char canary_front[8];
    sk_masked_s sk_masked;
    unsigned char canary_back[8];
  } sk_masked_with_canaries;

  write_canary(key_a); write_canary(key_a+sizeof(key_a)-8);
  write_canary(key_b); write_canary(key_b+sizeof(key_b)-8);
  write_canary(key_c); write_canary(key_c+sizeof(key_c)-8);
  write_canary(pk); write_canary(pk+sizeof(pk)-8);
  write_canary(sendb); write_canary(sendb+sizeof(sendb)-8);
  write_canary(sk_a); write_canary(sk_a+sizeof(sk_a)-8);
  write_canary(sk_masked_with_canaries.canary_front); write_canary(sk_masked_with_canaries.canary_back);


  int i;

  for(i=0; i<NTESTS; i++)
  {
    //Alice generates a public key
    MUPQ_crypto_kem_keypair(pk+8, sk_a+8);
    hal_send_str("DONE key pair generation!");

    //Bob derives a secret key and creates a response
    MUPQ_crypto_kem_enc(sendb+8, key_b+8, pk+8);
    hal_send_str("DONE encapsulation!");

    //Alice uses Bobs response to get her secret key
    MUPQ_crypto_kem_dec(key_a+8, sendb+8, sk_a+8);
    hal_send_str("DONE decapsulation!");

    //Alice uses Bobs response to get her secret key (masked)
    MUPQ_crypto_kem_crypto_kem_keypair_sk_masked_HO(&(sk_masked_with_canaries.sk_masked), sk_a+8);
    MUPQ_crypto_kem_dec_masked_HO(key_c+8, sendb+8, &(sk_masked_with_canaries.sk_masked));
    hal_send_str("DONE masked decapsulation!");

    if(memcmp(key_a+8, key_b+8, MUPQ_CRYPTO_BYTES) | memcmp(key_a+8, key_c+8, MUPQ_CRYPTO_BYTES))
    {
      hal_send_str("ERROR KEYS\n");
      // hal_send_str("OK KEYS\n");
    }
    else if(check_canary(key_a) || check_canary(key_a+sizeof(key_a)-8) ||
            check_canary(key_b) || check_canary(key_b+sizeof(key_b)-8) ||
            check_canary(pk) || check_canary(pk+sizeof(pk)-8) ||
            check_canary(sendb) || check_canary(sendb+sizeof(sendb)-8) ||
            check_canary(sk_a) || check_canary(sk_a+sizeof(sk_a)-8)||
            check_canary(key_c) || check_canary(key_b+sizeof(key_c)-8) ||
            check_canary(sk_masked_with_canaries.canary_front) || check_canary(sk_masked_with_canaries.canary_back))
    {
      hal_send_str("ERROR canary overwritten\n");
      // hal_send_str("OK KEYS\n");
    }
    else
    {
      hal_send_str("OK KEYS\n");
    }
  }

  return 0;
}


static int test_invalid_sk_a(void)
{
  unsigned char sk_a[MUPQ_CRYPTO_SECRETKEYBYTES];
  unsigned char key_a[MUPQ_CRYPTO_BYTES], key_b[MUPQ_CRYPTO_BYTES], key_c[MUPQ_CRYPTO_BYTES], key_d[MUPQ_CRYPTO_BYTES];
  unsigned char pk[MUPQ_CRYPTO_PUBLICKEYBYTES];
  unsigned char sendb[MUPQ_CRYPTO_CIPHERTEXTBYTES];
  uint8_t kr[64]; // Will contain key, coins
  sk_masked_s sk_masked;
  int i;

  for(i=0; i<NTESTS; i++)
  {
    //Alice generates a public key
    MUPQ_crypto_kem_keypair(pk, sk_a);

    //Bob derives a secret key and creates a response
    MUPQ_crypto_kem_enc(sendb, key_b, pk);

    //Replace secret key with random values
    randombytes(sk_a, MUPQ_CRYPTO_SECRETKEYBYTES);

    //Alice uses Bobs response to get her secre key
    MUPQ_crypto_kem_dec(key_a, sendb, sk_a);

    //Alice uses Bobs response to get her secret key (masked)
    MUPQ_crypto_kem_crypto_kem_keypair_sk_masked_HO(&sk_masked, sk_a);
    MUPQ_crypto_kem_dec_masked_HO(key_c, sendb, &sk_masked);

    // The following part is specific to SABER's CCA transform
    sha3_256(kr + 32, sendb, MUPQ_CRYPTO_CIPHERTEXTBYTES); // overwrite coins in kr with h(c)
    memcpy(kr, sk_a + MUPQ_CRYPTO_SECRETKEYBYTES - MUPQ_CRYPTO_BYTES, MUPQ_CRYPTO_BYTES);
    sha3_256(key_d, kr, 64); // hash concatenation of pre-k and h(c) to k

    if((!memcmp(key_a, key_b, MUPQ_CRYPTO_BYTES)) | memcmp(key_a, key_d, MUPQ_CRYPTO_BYTES) | !memcmp(key_c, key_b, MUPQ_CRYPTO_BYTES) | memcmp(key_c, key_d, MUPQ_CRYPTO_BYTES))
    {
      hal_send_str("ERROR invalid sk_a\n");
      // hal_send_str("OK invalid sk_a\n");
    }
    else
    {
      hal_send_str("OK invalid sk_a\n");
    }
  }

  return 0;
}


static int test_invalid_ciphertext(void)
{
  unsigned char sk_a[MUPQ_CRYPTO_SECRETKEYBYTES];
  unsigned char key_a[MUPQ_CRYPTO_BYTES], key_b[MUPQ_CRYPTO_BYTES], key_c[MUPQ_CRYPTO_BYTES], key_d[MUPQ_CRYPTO_BYTES];
  unsigned char pk[MUPQ_CRYPTO_PUBLICKEYBYTES];
  unsigned char sendb[MUPQ_CRYPTO_CIPHERTEXTBYTES];
  uint8_t kr[64]; // Will contain key, coins
  sk_masked_s sk_masked;
  int i;
  size_t pos;

  for(i=0; i<NTESTS; i++)
  {
    randombytes((unsigned char *)&pos, sizeof(size_t));

    //Alice generates a public key
    MUPQ_crypto_kem_keypair(pk, sk_a);

    //Bob derives a secret key and creates a response
    MUPQ_crypto_kem_enc(sendb, key_b, pk);

    // Change ciphertext to random value
    randombytes(sendb, sizeof(sendb));

    //Alice uses Bobs response to get her secret key
    MUPQ_crypto_kem_dec(key_a, sendb, sk_a);

    //Alice uses Bobs response to get her secret key (masked)
    MUPQ_crypto_kem_crypto_kem_keypair_sk_masked_HO(&sk_masked, sk_a);
    MUPQ_crypto_kem_dec_masked_HO(key_c, sendb, &sk_masked);

    // The following part is specific to SABER's CCA transform
    sha3_256(kr + 32, sendb, MUPQ_CRYPTO_CIPHERTEXTBYTES); // overwrite coins in kr with h(c)
    memcpy(kr, sk_a + MUPQ_CRYPTO_SECRETKEYBYTES - MUPQ_CRYPTO_BYTES, MUPQ_CRYPTO_BYTES);
    sha3_256(key_d, kr, 64); // hash concatenation of pre-k and h(c) to k

    if((!memcmp(key_a, key_b, MUPQ_CRYPTO_BYTES)) | memcmp(key_a, key_d, MUPQ_CRYPTO_BYTES) | !memcmp(key_c, key_b, MUPQ_CRYPTO_BYTES) | memcmp(key_c, key_d, MUPQ_CRYPTO_BYTES))
    {
      hal_send_str("ERROR invalid ciphertext\n");
      // hal_send_str("OK invalid ciphertext\n");
    }
    else
    {
      hal_send_str("OK invalid ciphertext\n");
    }
  }

  return 0;
}

int main(void)
{
  hal_setup(CLOCK_FAST);

  // marker for automated testing
  hal_send_str("==========================");
  test_keys();
  test_invalid_sk_a();
  test_invalid_ciphertext();
  hal_send_str("#");

  return 0;
}
