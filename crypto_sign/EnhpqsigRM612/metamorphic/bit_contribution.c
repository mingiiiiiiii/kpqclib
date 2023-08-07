#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <assert.h>

#include "rng.h"
#include "api.h"
#include "common.h"
#include "matrix.h"
#include "nearest_vector.h"
#include "parm.h"
#include "rm.h"
#include "rng.h"

#include "bit_contribution.h"

#define BIT_CONTRIBUTION_SUCCESS    0
#define BIT_VERIFY_SUCCESS          0
#define BIT_CONTRIBUTION_FAIL       -1

#define BIT_VERIFY_FAIL             -1


int KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t crypto_bytes, char* ALGNAME) 
{
    uint8_t* pk;
    uint8_t* sk;
    uint8_t* m = NULL;
    uint8_t* sig = NULL;
    uint8_t* sig2 = NULL;
    uint8_t* buf = NULL;
    size_t siglen = 0;
    size_t siglen2 = 0;
    bool flag = true;
    int param = 0;

    uint8_t* sm  = (uint8_t*)calloc(crypto_bytes + 2 * mlen, sizeof(uint8_t));
    uint8_t* sm2 = (uint8_t*)calloc(crypto_bytes + 2 * mlen, sizeof(uint8_t));
    size_t smlen  = 0;
    size_t smlen2 = 0;

    
    pk   = (uint8_t*)calloc(pklen,   sizeof(uint8_t));
    sk   = (uint8_t*)calloc(sklen,   sizeof(uint8_t));
    m    = (uint8_t*)calloc(mlen,   sizeof(uint8_t));
    sig  = (uint8_t*)calloc(crypto_bytes, sizeof(uint8_t));
    sig2 = (uint8_t*)calloc(crypto_bytes, sizeof(uint8_t));
    buf  = (uint8_t*)calloc(mlen,   sizeof(uint8_t));
    
    assert(pk   != NULL);
    assert(sk   != NULL);
    assert(m    != NULL);
    assert(sig  != NULL);
    assert(sig2 != NULL);
    assert(buf  != NULL);
    assert(sm   != NULL);
    assert(sm2  != NULL);

    // set message with pseudorandom bytes
    for(int i = 0; i < mlen; i++){
        m[i] = rand() & 0xff;
    }

    crypto_sign_keypair(pk, sk);
    crypto_sign(sm, &smlen, m, mlen, sk);

    for(int i = 0; i < mlen * 8; i++){
        memcpy(buf, m, mlen);
        buf[i/8] ^= 1 << (i % 8);

        smlen2 = smlen;
        crypto_sign(sm2, &smlen, m, mlen, sk);


        if(memcmp(sm+sizeof(unsigned long long)+mlen, sm2+sizeof(unsigned long long)+mlen, smlen - mlen - sizeof(unsigned long long)) == 0 || smlen != smlen2) {
            printf("%s Bit Contribution Test Failed: Failed on messaage\n", ALGNAME);
            // for(int idx = 0; idx < siglen; idx++){
            //     printf("%02x ", sig[idx]);
            // }printf("\n");
            // for(int idx = 0; idx < siglen; idx++){
            //     printf("%02x ", sig2[idx]);
            // }printf("\n");
            // printf("siglen: %d", siglen);
            // printf("siglen2: %d", siglen2);
            flag = false;
            goto EXIT;
        }
    }


EXIT:
    free(m   );
    free(sig );
    free(sig2);
    free(buf );

    if(flag){
        printf("%s Bit Contribution Test Success\n", ALGNAME);
        return BIT_CONTRIBUTION_SUCCESS;
    } else{
        return BIT_CONTRIBUTION_FAIL;
    }    

}
