#include <stdio.h>
#include <time.h>

#include "cpucycles.h"
#include "params.h"
#include "speed_print.h"

// #define NTESTS 1000
#define NTESTS 100

uint64_t t[NTESTS];


int main() {

    unsigned int    pk1[IPCC_PUBLICKEYBYTES_ROW][IPCC_PUBLICKEYBYTES_COL];
    unsigned int    pk2[IPCC_PUBLICKEYBYTES_ROW][IPCC_PUBLICKEYBYTES_COL];
    unsigned int    ct[IPCC_CIPHERTEXTBYTES_ROW][IPCC_CIPHERTEXTBYTES_COL];
    unsigned int    sk[IPCC_SECRETKEYBYTES];
    unsigned int    clen[1];
    unsigned int    m[1];

    int i = 0;
    clock_t srt, ed;
    clock_t overhead;

    overhead = clock();
    cpucycles();
    overhead = clock() - overhead;

    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_encrypt_keypair(pk1, pk2, sk);
    }
    ed = clock();
    print_results("keygen_kem: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_encrypt(ct, clen, m, sizeof(m), pk1, pk2);
    }
    ed = clock();
    print_results("encap: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    // uint8_t ss2[CRYPTO_BYTES] = {0};
    srt = clock();
    for (i = 0; i < NTESTS; i++) {
        t[i] = cpucycles();
        crypto_encrypt_open(m, sizeof(m), ct, clen, sk);
    }
    ed = clock();
    print_results("decap: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    return 0;
}
