#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "aimer.h"

#include "bit_exclusion.h"


int KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t crypto_bytes, char* ALGNAME)
{
    aimer_publickey_t  pk;
    aimer_privatekey_t sk;
    uint8_t* m = NULL;
    uint8_t* sig = NULL;
    uint8_t* sig2 = NULL;
    uint8_t* buf = NULL;
    size_t siglen = 0;
    size_t siglen2 = 0;
    bool flag = true;
    int param = 0;
    
#if   (AIMER_MODE == 1)
  param = AIMER_L1_PARAM1;
#elif (AIMER_MODE == 3)
  param = AIMER_L3_PARAM1;
#elif (AIMER_MODE == 5)
  param = AIMER_L5_PARAM1;
#endif

    m    = (uint8_t*)calloc(mlen,   sizeof(uint8_t));
    sig  = (uint8_t*)calloc(crypto_bytes, sizeof(uint8_t));
    sig2 = (uint8_t*)calloc(crypto_bytes, sizeof(uint8_t));
    buf  = (uint8_t*)calloc(mlen+EXCLUSION_BYTELEN,   sizeof(uint8_t));
    
    assert(m    != NULL);
    assert(sig  != NULL);
    assert(sig2 != NULL);
    assert(buf  != NULL);

    // set message with pseudorandom bytes
    for(int i = 0; i < mlen; i++){
        m[i] = rand() & 0xff;
    }

    aimer_keygen(param++, &pk, &sk);
    aimer_sign(&pk, &sk, (const uint8_t*)m, mlen, sig, &siglen);

    for(int i = 0; i < mlen; i++){
        memcpy(buf, m, mlen);
        buf[mlen + i/8] ^= 1 << (i % 8);

        aimer_sign(&pk, &sk, (const uint8_t*)buf, mlen, sig2, &siglen2);
        if(memcmp(sig, sig2, siglen) != 0 || siglen != siglen2) {
            printf("%s Bit Exclusion Test Failed: Failed on messaage\n", ALGNAME);
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
        printf("%s Bit Exclusion Test Success\n", ALGNAME);
        return BIT_EXCLUSION_SUCCESS;
    } else{
        return BIT_EXCLUSION_FAIL;
    }    

}