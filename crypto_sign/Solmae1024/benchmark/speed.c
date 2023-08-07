#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "cpucycles.h"

#include "speed_print.h"
#include "api.h"
#include "poly.h"
#include <x86intrin.h>

#define NTESTS 1000

unsigned long long cpucycle(){
    return __rdtsc();
}

uint64_t t[NTESTS];
secret_key sk;   
public_key pk;
signature s;

int main()
{
    printf("Solmae512 benchmark start...\n");

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
        keygen_full(&sk, &pk);
    }
    ed = clock();
    print_results("keygen_kem: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    unsigned char m[32];
    printf("sign start....\n");
    unsigned long long start = cpucycle();
    for (i = 0; i < NTESTS; i++)
    {
        sign(m, &sk, &s);
    }
    unsigned long long end = cpucycle();
    printf("sign: %d\n", (end-start)/NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(end - start - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    srt = clock();
    for (i = 0; i < NTESTS; i++)
    {
        t[i] = cpucycles();
       verify(m, &pk, &s);
    }
    ed = clock();
    print_results("verify: ", t, NTESTS);
    printf("time elapsed: %.8fms\n\n", (double)(ed - srt - overhead * NTESTS) *
                                           1000 / CLOCKS_PER_SEC / NTESTS);

    return 0;
}
