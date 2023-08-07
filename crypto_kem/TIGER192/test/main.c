#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "TIGER_CPAPKE.h"
#include "TIGER_CCAKEM.h"
#include "fips202.h"
#include "rng.h"
#include "params.h"

#define m_size 10

int indcpa_test();

int main(void) 
{
   
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);
    time_str[strlen(time_str) - 1] = '\0';
    printf("\n*** %s with mode %d starts at %s\n", "TIGER KEM", TIGER_MODE,
           time_str);

    // simple_test();
    // indcpa_test();
    size_t count = 1;
    // const size_t iteration = 10000000;
    const size_t iteration = 100;

    for (size_t i = 0; i < iteration; ++i) {
        if (!(i % (iteration / 10))) {
            printf("...%lu%%", count * 10);
            fflush(stdout);
            ++count;
        }

        if (indcpa_test()) {
            printf("PKE test fails at %lu-th tries\n", i);
            break;
        }

        // if (kem_test()) {
        //     printf("KEM test fails at %lu-th tries\n", i);
        //     break;
        // }
    }

    return 0;
}

// void simple_test() {
//     uint8_t pk[PUBLICKEY_BYTES] = {0}, pk2[PUBLICKEY_BYTES] = {0};
//     uint8_t sk[KEM_SECRETKEY_BYTES] = {0};

//     indcpa_keypair(pk, sk);
//     printf("indcpa_keypair done\n");

//     public_key pk_tmp;
//     load_from_string_pk(&pk_tmp, pk);
//     save_to_string_pk(pk2, &pk_tmp);
//     if (memcmp(pk, pk2, PUBLICKEY_BYTES)) {
//         printf("Diff pk's\n");

//         printf("pk : ");
//         for (int i = 0; i < m_size; ++i)
//             printf("%02x ", pk[i]);
//         printf("\n");

//         printf("pk2: ");
//         for (int i = 0; i < m_size; ++i)
//             printf("%02x ", pk2[i]);
//         printf("\n");
//     }

//     // ind-cpa pke enc
//     uint8_t mx[DELTA_BYTES] = {0};
//     randombytes(mx, DELTA_BYTES);

//     // uint8_t ctxt[CIPHERTEXT_BYTES] = {0};
//     ciphertext ctxt;
//     indcpa_enc(&ctxt, pk, mx);
//     printf("indcpa_enc done\n");

//     // ind-cpa pke dec
//     uint8_t mx2[DELTA_BYTES] = {0};
//     indcpa_dec(mx2, sk, &ctxt);
//     printf("indcpa_dec done\n");

//     if (memcmp(mx, mx2, DELTA_BYTES))
//         printf("Diff mx\n");
// }
    

int indcpa_test() 
{
    unsigned char pk[PUBLICKEYSIZE];
    unsigned char sk[SECRETKEYSIZE];
	unsigned char c[2*LWE_N];
	int i,j, res=0, res_enc = 0, res_dec = 0;
	unsigned char coin[32];
	unsigned char shared_k1[KK_LEN] = {0,};
	unsigned char shared_k2[KK_LEN] = {0,};
	
    // ciphertext ctxt;

    KEM_Keygen(pk, sk);
    // printf("indcpa_keypair done\n");

    KEM_Enc(c, shared_k1, pk);
    // indcpa_enc(&ctxt, pk, delta);
    // printf("indcpa_enc done\n");

    KEM_dec(shared_k2, c, sk, pk);
    // indcpa_dec(delta2, sk, &ctxt);
    // printf("indcpa_dec done\n");

    if (memcmp(shared_k1, shared_k2, KK_LEN)) {
        for (int i = 0; i < m_size; ++i)
            printf("%d ", shared_k1[i]);
        printf("\n");

        for (int i = 0; i < m_size; ++i)
            printf("%d ", shared_k2[i]);
        printf("\n");
        res = 1;
    }

    return res;
}
