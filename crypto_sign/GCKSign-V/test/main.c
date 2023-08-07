#include "aes256ctr.h"
#include "fips202.h"
#include "pack.h"
#include "params.h"
#include "poly.h"
#include "reduce.h"
#include "sample.h"
#include "sign.h"
#include "symmetric.h"


#include <stdio.h>
#include <string.h>

#define BUF_BYTES (1)
// #define Iterations (1000000)
#define Iterations (200)
#define SEEDBYTES 32

uint8_t print_flag = 1;

int sign_verify_test(void);

int main(void) {
    printf("GCKSign mode = %d\n", GCKSign_MODE);
    size_t count = 1;
    for (int i = 0; i < Iterations; ++i) {
        if (sign_verify_test()) {
            printf("Invalid on %d-th test\n", i);
            break;
        }

        if (!(i % (Iterations / 10))) {
            printf("...%lu%%", count * 10);
            fflush(stdout);
            ++count;
        }
    }
    printf("\n");

    return 0;
}

int sign_verify_test(void) {
    if (print_flag) {
        printf(">> sign and verify test\n");
        print_flag = 0;
    }

    unsigned char       pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sk[CRYPTO_SECRETKEYBYTES];

    crypto_sign_keypair(pk, sk);

    unsigned char sm[CRYPTO_BYTES + 200];
    unsigned long long  mlen = 0;
    unsigned long long  mlen1 = 0;
	unsigned long long smlen;
    unsigned char  msg[100];
    unsigned char  msg1[100];
    mlen=SEEDBYTES;
    randombytes(msg, SEEDBYTES);
    crypto_sign(sm, &smlen, msg, mlen, sk);

    if (crypto_sign_open(msg1, &mlen1, sm, smlen, pk)) {
        return 1;
    }
    if ( mlen != mlen1 ) {
        return 1;
        }

    return 0;
}
