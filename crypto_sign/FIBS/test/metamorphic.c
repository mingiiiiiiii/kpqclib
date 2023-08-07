#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <memory.h>

#include "../api.h"
#include "../fors.h"
#include "../wots.h"
#include "../params.h"
#include "../rng.h"

#define SPX_MLEN 32
#define NTESTS 1
#define EXCLUSION_BYTELEN 4

#define BIT_CONTRIBUTION_SUCCESS    0
#define BIT_VERIFY_SUCCESS          0
#define BIT_CONTRIBUTION_FAIL       -1
#define BIT_VERIFY_FAIL             -1


int main()
{
    /* Make stdout buffer more responsive. */
    setbuf(stdout, NULL);

    unsigned char pk[SPX_PK_BYTES];
    unsigned char sk[SPX_SK_BYTES];
    unsigned char *m = malloc(SPX_MLEN);
    unsigned char *sm  = malloc(SPX_BYTES + SPX_MLEN);
    unsigned char *sm2 = malloc(SPX_BYTES + SPX_MLEN);
    unsigned char *mout  = malloc(SPX_BYTES + SPX_MLEN);
    unsigned char *mout2 = malloc(SPX_BYTES + SPX_MLEN);

    unsigned char fors_pk[SPX_FORS_PK_BYTES];
    unsigned char fors_m[SPX_FORS_MSG_BYTES];
    unsigned char fors_sig[SPX_FORS_BYTES];
    unsigned char addr[SPX_ADDR_BYTES];

    unsigned char wots_sig[SPX_WOTS_BYTES];
    unsigned char wots_m[SPX_N];
    unsigned char wots_pk[SPX_WOTS_PK_BYTES];

    unsigned long long smlen;
    unsigned long long smlen2;
    unsigned long long mlen;
    unsigned long long mlen2;
    unsigned long long t[NTESTS+1];
    double result;
    int i;

    randombytes(m, SPX_MLEN);
    randombytes(addr, SPX_ADDR_BYTES);

    printf("FIBS Metamorphic Testing start...\n");
    printf("Parameters: n = %d, h = %d, d = %d, b = %d, k = %d, w = %d\n",
           SPX_N, SPX_FULL_HEIGHT, SPX_D, SPX_FORS_HEIGHT, SPX_FORS_TREES,
           SPX_WOTS_W);


    crypto_sign_keypair(pk, sk);
    crypto_sign(sm, &smlen, m, SPX_MLEN, sk);

    uint8_t* buf = (uint8_t*)calloc(SPX_MLEN, sizeof(uint8_t));
    assert(buf != NULL);

    // bit contribution test
    // int res_bct = 1;
    // for(int i = 0; i < 2; i++){
    //     memcpy(buf, m, SPX_MLEN);
    //     buf[i/8] ^= 1 << (i % 8);

    //     crypto_sign(sm2, &smlen2, buf, SPX_MLEN, sk);

    //     if(memcmp(sm, sm2, SPX_BYTES) == 0){
    //         printf("FIBS Bit Contribution Test Failed: Failed on message\n");
    //         res_bct = 0;
    //         break;
    //     }
    // }
    // if(res_bct)
    //     printf("FIBS Bit Contribution Test Success\n");
    // free(buf);

    // bit exclusion test
    buf = (uint8_t*)calloc(SPX_MLEN + EXCLUSION_BYTELEN, sizeof(uint8_t));
    assert(buf != NULL);
    int res_bet = 1;
    for(int i = 0; i < 2; i++){
        memcpy(buf, m, SPX_MLEN);
        buf[SPX_MLEN + i/8] ^= 1 << (i % 8);

        crypto_sign(sm2, &smlen2, buf, SPX_MLEN, sk);

        if(memcmp(sm, sm2, SPX_BYTES) != 0){
            printf("FIBS Bit Exclusion Test Failed: Failed on message\n");
            res_bet = 0;
            break;
        }
    }
    if(res_bet)
        printf("FIBS Bit Exclusion Test Success\n");
    free(buf);

    // bit verif test
    buf = (uint8_t*)calloc(SPX_BYTES + SPX_MLEN, sizeof(uint8_t));
    assert(buf != NULL);
    int res_bvt = 1;
    for(int i = 0; i < 2; i++){
        memcpy(buf, sm, SPX_BYTES + SPX_MLEN);
        buf[i/8] ^= 1 << (i % 8);

        mlen2 = SPX_MLEN;
        crypto_sign_open(mout,  &mlen,  sm, smlen, pk);
        crypto_sign_open(mout2, &mlen2, sm, smlen, pk);

        if(memcmp(mout2, mout, SPX_MLEN) == 0){
            printf("FIBS Bit Verify Test Failed: Failed on message\n");
            res_bvt = 0;
            break;
        }
    }
    if(res_bvt)
        printf("FIBS Bit Verify Test Success\n");


    free(m);
    free(sm);
    free(mout);
    free(buf);

    return 0;
}