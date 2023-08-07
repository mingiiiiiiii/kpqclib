#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "sign.h"
#include "poly.h"
#include "params.h"
#include "cpucycles.h"
#include "speed_print.h"
#include "stdio.h"


#define NTESTS 1000
#define SEEDBYTES 32

uint64_t t[NTESTS];

int main() {
    
    size_t smlen;
    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sk[CRYPTO_SECRETKEYBYTES];
    uint8_t sm[CRYPTO_BYTES + CRHBYTES];
    unsigned long long  mlen, mlen1;
    int i = 0;
    clock_t srt, ed;
    clock_t overhead;

    randombytes(sm, CRYPTO_BYTES);
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
        crypto_sign(sm, &smlen, sm, CRHBYTES, sk);
    }
    ed = clock();
    print_results("crypto_sign_signature: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_sign_verify(sm, CRYPTO_BYTES, sm, CRHBYTES, pk);
    }
    ed = clock();
    print_results("crypto_sign_verify: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);
    return 0;
}
