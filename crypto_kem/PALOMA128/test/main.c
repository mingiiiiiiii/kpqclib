#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>
#include "rng.h"
#include "api.h"
#include "gf_table_gen.h"

#define	MAX_MARKER_LEN		50
#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

#define MAX_CRYPTO_PUBLICKEYBYTES   1025024
#define MAX_CRYPTO_SECRETKEYBYTES   357064
#define MAX_CRYPTO_CIPHERTEXTBYTES  240
#define MAX_CRYPTO_BYTES            32

#define m_size 10

int indcpa_test();
int kem_test();

int main(void) {
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);
    time_str[strlen(time_str) - 1] = '\0';
    printf("\n*** %s starts at %s\n", CRYPTO_ALGNAME,
           time_str);

    size_t count = 1;
    const size_t iteration = 100;

    uint8_t entropy_input[48] = {0};
    for (size_t i = 0; i < 48; ++i) {
        entropy_input[i] = i;
    }
    randombytes_init(entropy_input, NULL, 256);

    for (size_t i = 0; i < iteration; ++i) {
        if (!(i % (iteration / 10))) {
            printf("...%lu%%", count * 10);
            fflush(stdout);
            ++count;
        }

        // if (indcpa_test()) {
        //     printf("PKE test fails at %lu-th tries\n", i);
        //     break;
        // }
        printf("%d\n",i);
        if (kem_test()) {
            printf("KEM test fails at %lu-th tries\n", i);
            break;
        }
    }

    return 0;
}

// int indcpa_test() {
//     uint8_t pk[PUBLICKEY_BYTES] = {0};
//     uint8_t sk[PKE_SECRETKEY_BYTES] = {0};
//     uint8_t ctxt[CIPHERTEXT_BYTES] = {0};
//     uint8_t mu[DELTA_BYTES] = {0}, mu2[DELTA_BYTES] = {0};
//     uint8_t seed[DELTA_BYTES] = {0};

//     indcpa_keypair(pk, sk);
//     // printf("indcpa_keypair done\n");

//     randombytes(mu, DELTA_BYTES);
//     randombytes(seed, DELTA_BYTES);

//     indcpa_enc(ctxt, pk, mu, seed);
//     // printf("indcpa_enc done\n");

//     indcpa_dec(mu2, sk, ctxt);
//     // printf("indcpa_dec done\n");

//     if (memcmp(mu, mu2, DELTA_BYTES) != 0) {
//         for (int i = 0; i < m_size; ++i)
//             printf("0x%2hx ", mu[i]);
//         printf("\n");

//         for (int i = 0; i < m_size; ++i)
//             printf("0x%2hx ", mu2[i]);
//         printf("\n");
//         return 1;
//     }

//     return 0;
// }

int kem_test() {
    unsigned char pk[MAX_CRYPTO_PUBLICKEYBYTES]={0}; 
    unsigned char sk[MAX_CRYPTO_SECRETKEYBYTES]={0};
    // uint8_t pk[PUBLICKEY_BYTES] = {0};
    // uint8_t sk[KEM_SECRETKEY_BYTES] = {0};

    int n,t,k;
    PARAM PALOMAParam;

    #ifdef PALOMA_MODE
        #if PALOMA_MODE == 1
        t = 64;     
        n = 3904;   
        k = (n-(13*t));

        #elif PALOMA_MODE == 3
        t = 128;     
        n = 5568;   
        k = (n-(13*t));    

        #elif PALOMA_MODE == 5
        t = 128;     
        n = 6592;   
        k = (n-(13*t));  
        #endif
    #endif

    GF_init(&PALOMAParam, n, k, t);
    // randombytes_init(seed, NULL, 256);                              
    
    crypto_PALOMA_keypair(pk, sk, &PALOMAParam);
    
    // crypto_kem_keypair(pk, sk);
    // printf("Keygen_kem done\n");
    unsigned char ct[MAX_CRYPTO_CIPHERTEXTBYTES]={0}; 
    unsigned char ss[MAX_CRYPTO_BYTES]={0}; 
    unsigned char ss2[MAX_CRYPTO_BYTES]={0};
    // uint8_t ctxt[CIPHERTEXT_BYTES] = {0};
    // uint8_t ss[CRYPTO_BYTES] = {0}, ss2[CRYPTO_BYTES] = {0};
    crypto_PALOMA_enc(ct, ss, pk,&PALOMAParam);
    // crypto_kem_encap(ctxt, ss, pk);
    // printf("Encap done\n");

    int res = crypto_PALOMA_dec(ss2, ct, sk,&PALOMAParam);
    // int res = crypto_kem_decap(ss2, sk, pk, ctxt);
    // printf("Decap done\n");

    if (memcmp(ss, ss2, CRYPTO_BYTES) != 0) {
        for (int i = 0; i < m_size; ++i) {
            printf("0x%2hx ", ss[i]);
        }
        printf("\n");

        for (int i = 0; i < m_size; ++i) {
            printf("0x%2hx ", ss2[i]);
        }
        printf("\n");
    }

    return res;
}