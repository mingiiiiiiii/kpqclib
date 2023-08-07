#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "aes256ctr.h"
#include "fips202.h"
#include "pack.h"
#include "params.h"
#include "poly.h"
#include "reduce.h"
#include "sample.h"
#include "sign.h"
#include "symmetric.h"

#include "bit_exclusion.h"


int KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t crypto_bytes, char* ALGNAME)
{
    uint8_t* pk;
    uint8_t* sk;
    uint8_t* m = NULL;
    uint8_t* buf = NULL;
    size_t siglen = 0;
    size_t siglen2 = 0;
    bool flag = true;
    int param = 0;

    uint8_t* sm  = (uint8_t*)calloc(crypto_bytes + mlen * 2, sizeof(uint8_t));
    uint8_t* sm2 = (uint8_t*)calloc(crypto_bytes + mlen * 2, sizeof(uint8_t));
    unsigned long long smlen  = 0;
    unsigned long long smlen2 = 0;

    
    pk   = (uint8_t*)calloc(pklen,   sizeof(uint8_t));
    sk   = (uint8_t*)calloc(sklen,   sizeof(uint8_t));
    m    = (uint8_t*)calloc(mlen,   sizeof(uint8_t));
    buf  = (uint8_t*)calloc(mlen + EXCLUSION_BYTELEN,   sizeof(uint8_t));
    
    assert(pk   != NULL);
    assert(sk   != NULL);
    assert(m    != NULL);
    assert(buf  != NULL);
    assert(sm   != NULL);
    assert(sm2  != NULL);

    // set message with pseudorandom bytes
    for(int i = 0; i < mlen + EXCLUSION_BYTELEN; i++){
        m[i] = rand() & 0xff;
    }

    crypto_sign_keypair(pk, sk);
    crypto_sign(sm, &smlen, m, mlen, sk);

    for(int i = 1; i < EXCLUSION_BYTELEN * 8; i++){
        memcpy(buf, m, mlen + EXCLUSION_BYTELEN);
        buf[mlen + i/8] ^= 1 << (i % 8);

        crypto_sign(sm2, &smlen2, buf, mlen, sk);
        
        if(memcmp(sm, sm2, smlen) != 0 || smlen != smlen2) {
            printf("%s Bit Exclusion Test Failed: Failed on messaage\n", ALGNAME);
            flag = false;
            goto EXIT;
        }
    }

EXIT:
    // free(m   );
    // free(buf );

    if(flag){
        printf("%s Bit Exclusion Test Success\n", ALGNAME);
        return BIT_EXCLUSION_SUCCESS;
    } else{
        return BIT_EXCLUSION_FAIL;
    }    

}