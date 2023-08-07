#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "cpucycles.h"
#include "params.h"
#include "TIGER_CCAKEM.h"
#include "speed_print.h"


#define NTESTS 1000

uint64_t t[NTESTS];
   
    uint8_t pk[32 + LWE_N] = {0};
    uint8_t sk[LWE_N + MESSAGE_LEN] = {0};

int main()
{

    int i = 0;
    clock_t srt, ed;
    clock_t overhead;


    overhead = clock();
    cpucycles();
    overhead = clock() - overhead;

    srt = clock();
    for (i = 0; i < NTESTS; i++)
    {
        t[i] = cpucycles();
        KEM_Keygen(pk, sk);
    }
    ed = clock();
    print_results("keygen_kem: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    unsigned char c[2 * LWE_N];
    uint8_t ss1[KK_LEN] = {0};

    srt = clock();
    for (i = 0; i < NTESTS; i++)
    {
        t[i] = cpucycles();
        KEM_Enc(c, ss1, pk);
    }
    ed = clock();
    print_results("encap: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    uint8_t ss2[KK_LEN] = {0};
    srt = clock();
    for (i = 0; i < NTESTS; i++)
    {
        t[i] = cpucycles();
       KEM_dec(ss2, c, sk, pk);
    }
    ed = clock();
    print_results("decap: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    return 0;
}
