#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <assert.h>

#include "bit_verify.h"

#define BIT_VERIFY_SUCCESS          0
#define BIT_VERIFY_FAIL             -1


int KPQCLEAN_METAMORPHIC_bit_verify_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t kem_siglen, char* ALGNAME) 
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
    m    = (uint8_t*)calloc(mlen,   sizeof(uint8_t));
    sm  = (uint8_t*)calloc(kem_siglen, sizeof(uint8_t));
    
    
    assert(pk   != NULL);
    assert(sk   != NULL);
    assert(m    != NULL);
    assert(sm  != NULL);
    
    // set message with pseudorandom bytes
    for(int i = 0; i < mlen; i++){
        m[i] = rand() & 0xff;
    }

    crypto_sign_keypair(pk, sk);
    crypto_sign(sm, &smlen, m, mlen, sk);

    buf  = (uint8_t*)calloc(smlen,   sizeof(uint8_t));
    uint8_t* m2 = (uint8_t*)calloc(mlen, sizeof(uint8_t));
    assert(buf != NULL);
    assert(m2 != NULL);
    for(int i = 0; i < smlen * 8; i++){
        memcpy(buf, sm, smlen);
        buf[i/8] ^= 1 << (i % 8);

        int ret = crypto_sign_open(m2, &mlen, buf, smlen, pk);
        // printf("ret=%d / i = %d\n",ret, i);

        if(ret == 0) {
            printf("%s Bit Verify Test Failed: Failed on messaage\n", ALGNAME);
            for(int j=0;j<100;j++){
            printf("%02X ",sm[j]);
        }printf("\n");
        for(int j=0;j<100;j++){
            printf("%02X ",buf[j]);
        }printf("\n");
            flag = false;
            goto EXIT;
        }
    }


EXIT:
    free(m   );
    free(sm );
    free(pk);
    free(buf );
    free(sk);

    if(flag){
        printf("%s Bit Verify Test Success\n", ALGNAME);
        return BIT_VERIFY_SUCCESS;
    } else{
        return BIT_VERIFY_FAIL;
    }    

}
