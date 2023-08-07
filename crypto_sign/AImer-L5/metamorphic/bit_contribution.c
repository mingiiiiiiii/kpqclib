#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <assert.h>

#include "aimer.h"

#include "bit_contribution.h"

#define BIT_CONTRIBUTION_SUCCESS    0
#define BIT_VERIFY_SUCCESS          0
#define BIT_CONTRIBUTION_FAIL       -1

#define BIT_VERIFY_FAIL             -1


int KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t kem_siglen, char* ALGNAME) 
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
    sig  = (uint8_t*)calloc(kem_siglen, sizeof(uint8_t));
    sig2 = (uint8_t*)calloc(kem_siglen, sizeof(uint8_t));
    buf  = (uint8_t*)calloc(mlen,   sizeof(uint8_t));
    
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
        buf[i/8] ^= 1 << (i % 8);

        aimer_sign(&pk, &sk, (const uint8_t*)buf, mlen, sig2, &siglen2);
        
        if(memcmp(sig, sig2, siglen) == 0 || siglen != siglen2) {
            printf("%s Bit Contribution Test Failed: Failed on messaage\n", ALGNAME);
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
