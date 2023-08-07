#include <stdio.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rng.h"
#include "sign.h"
#include "cpucycles.h"
#include "speed_print.h"

#define NTESTS 1000
#define SEEDBYTES 32
uint64_t t[NTESTS];

int main() {

    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sk[CRYPTO_SECRETKEYBYTES];
    unsigned char sm[CRYPTO_BYTES + 200];
    uint8_t msg[SEEDBYTES];
    uint8_t msg1[SEEDBYTES];
    unsigned long long  mlen, smlen, mlen1;

    int i = 0;
    clock_t srt, ed;
    clock_t overhead;
    mlen=SEEDBYTES;
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
        crypto_sign(sm, &smlen, msg, mlen, sk);
    }
    ed = clock();
    print_results("crypto_sign_signature: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_sign_open(msg1, &mlen1, sm, smlen, pk);
    }
    ed = clock();
    print_results("crypto_sign_verify: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);
    return 0;
}
