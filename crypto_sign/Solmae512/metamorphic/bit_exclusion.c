#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>


#include "katrng.h"
#include "bit_exclusion.h"


int KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t crypto_bytes, char* ALGNAME)
{
    uint8_t* pk;
    uint8_t* sk;
    uint8_t* m = NULL;
    uint8_t* sm = NULL;
    uint8_t* sm2 = NULL;
    uint8_t* buf = NULL;
    size_t smlen = 0;
    size_t smlen2 = 0;
    bool flag = true;
    int param = 0;

    pk   = (uint8_t*)calloc(pklen,   sizeof(uint8_t));
    sk   = (uint8_t*)calloc(sklen,   sizeof(uint8_t));
    m    = (uint8_t*)calloc(mlen + EXCLUSION_BYTELEN,   sizeof(uint8_t));
    sm  = (uint8_t*)calloc(crypto_bytes, sizeof(uint8_t));
    sm2 = (uint8_t*)calloc(crypto_bytes, sizeof(uint8_t));
    buf  = (uint8_t*)calloc(mlen + EXCLUSION_BYTELEN,   sizeof(uint8_t));
    
    assert(pk   != NULL);
    assert(sk   != NULL);
    assert(m    != NULL);
    assert(sm  != NULL);
    assert(sm2 != NULL);
    assert(buf  != NULL);

   
    // set message with pseudorandom bytes
    for(int i = 0; i < mlen; i++){
        m[i] = rand() & 0xff;
    }

    crypto_sign_keypair(pk, sk);
    crypto_sign(sm, &smlen, m, mlen, sk);
    // for(int j=0;j<200;j++){
    //             printf("%02X ",sm[j]);
    //         }printf("\n");
    for(int i = 1; i < EXCLUSION_BYTELEN * 8; i++){
        memcpy(buf, m, mlen + EXCLUSION_BYTELEN);
        buf[mlen + i/8] ^= 1 << (i % 8);


        crypto_sign(sm2, &smlen2, m, mlen, sk);
        // for(int j=0;j<200;j++){
        //         printf("%02X ",sm2[j]);
        //     }printf("\n");
        if(memcmp(sm, sm2, smlen) != 0 || smlen != smlen2) {
            printf("%s Bit Exclusion Test Failed: Failed on messaage\n", ALGNAME);
            for(int j=0;j<200;j++){
                printf("%02X ",sm[j]);
            }printf("\n");
            for(int j=0;j<200;j++){
                printf("%02X ",sm2[j]);
            }printf("\n");
            flag = false;
            goto EXIT;
        }
    }

EXIT:
    free(m   );
    free(sm );
    free(sm2);
    free(pk);
    free(sk);
    free(buf );

    if(flag){
        printf("%s Bit Exclusion Test Success\n", ALGNAME);
        return BIT_EXCLUSION_SUCCESS;
    } else{
        return BIT_EXCLUSION_FAIL;
    }    

}