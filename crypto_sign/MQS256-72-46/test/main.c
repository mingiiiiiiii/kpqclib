#include "api.h"
#include "blas_comm.h"
#include "blas_matrix.h"
#include "blas_u32.h"
#include "blas.h"
#include "gf16.h"
#include "hash_len_config.h"
#include "mpkc.h"
#include "mqs_blas.h"
#include "mqs_config.h"
#include "mqs_keypair_computation.h"
#include "mqs_keypair.h"
#include "mqs.h"
#include "parallel_matrix_op.h"
#include "rng.h"
#include "utils_hash.h"
#include "utils_malloc.h"
#include "utils_prng.h"
#include "utils.h"


#include <stdio.h>
#include <string.h>

#define BUF_BYTES (1)
#define SEEDBYTES 32
// #define Iterations (1000000)
#define Iterations (200)

uint8_t print_flag = 1;

int sign_verify_test(void);

int main(void) {
    printf("MQS256 mode = %d\n", MQS256_MODE);
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
    unsigned char       seed[48];
    uint8_t pk[CRYPTO_PUBLICKEYBYTES] = {0};
    uint8_t sk[CRYPTO_SECRETKEYBYTES] = {0};
    uint8_t sm[CRYPTO_BYTES+SEEDBYTES] = {0};
    uint8_t m1[CRYPTO_BYTES+SEEDBYTES] = {0};
    unsigned long long mlen1, smlen;
    randombytes_init(seed, NULL, 256);
    randombytes(seed, 48);
    crypto_sign_keypair(pk, sk, seed);

    size_t siglen = 0;
    uint8_t sig[CRYPTO_BYTES] = {0};
    uint8_t msg[SEEDBYTES] = {0};
    randombytes(msg, SEEDBYTES);
    crypto_sign(sm, &smlen, msg, SEEDBYTES, sk, seed, 0);

    if (crypto_sign_open(m1, &mlen1, sm, smlen, pk)) {
        return 1;
    }

    return 0;
}
