#include <stdio.h>
#include <time.h>

#include "../include/randombytes.h"
#include "cpucycles.h"
#include "params.h"
#include "sign.h"
#include "speed_print.h"

#define NTESTS 1000

uint64_t t[NTESTS];

int main() {

    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sk[CRYPTO_SECRETKEYBYTES];
    uint8_t sig[CRYPTO_BYTES];
    uint8_t msg[SEEDBYTES];
    size_t siglen;
    int i = 0;
    clock_t srt, ed;
    clock_t overhead;

    randombytes(msg, SEEDBYTES);
    overhead = clock();
    cpucycles();
    overhead = clock() - overhead;

    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_sign_keypair(pk, sk);
    }
    ed = clock();
    print_results("crypto_sign_keypair: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_sign_signature(sig, &siglen, msg, SEEDBYTES, sk);
    }
    ed = clock();
    print_results("crypto_sign_signature: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_sign_verify(sig, siglen, msg, SEEDBYTES, pk);
    }
    ed = clock();
    print_results("crypto_sign_verify: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);
    return 0;
}
