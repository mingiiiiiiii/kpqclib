#include <stdio.h>
#include <time.h>

#include "cpucycles.h"
#include "api.h"
#include "rng.h"
#include "params.h"
#include "speed_print.h"

#define NTESTS 1000

uint64_t t[NTESTS];


int main() {

    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
	unsigned char sk[CRYPTO_SECRETKEYBYTES];
	unsigned char ct[CRYPTO_CIPHERTEXTBYTES];
	unsigned char ss[CRYPTO_BYTES];
	unsigned char dss[CRYPTO_BYTES];

    int i = 0;
    clock_t srt, ed;
    clock_t overhead;

    overhead = clock();
    cpucycles();
    overhead = clock() - overhead;

    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_kem_keypair(pk, sk);

    }
    ed = clock();
    print_results("keygen_kem: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

   
    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_kem_enc(ct, ss, pk);
    }
    ed = clock();
    print_results("encap: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);


    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_kem_dec(dss, ct, sk);
    }
    ed = clock();
    print_results("decap: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    return 0;
}
