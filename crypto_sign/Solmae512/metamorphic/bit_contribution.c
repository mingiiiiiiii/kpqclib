#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <assert.h>
#include "katrng.h"
#include "bit_contribution.h"

#define BIT_CONTRIBUTION_SUCCESS    0
#define BIT_VERIFY_SUCCESS          0
#define BIT_CONTRIBUTION_FAIL       -1

#define BIT_VERIFY_FAIL             -1


int KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
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
    sm2 = (uint8_t*)calloc(kem_siglen, sizeof(uint8_t));
    buf  = (uint8_t*)calloc(mlen,   sizeof(uint8_t));
    
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

    static unsigned char seed[48];
    static unsigned char entropy_input[48];
    randombytes_init(entropy_input, NULL, 256);
    randombytes_init(seed, NULL, 256);
    randombytes(seed, 48);

    crypto_sign_keypair(pk, sk);
    crypto_sign(sm, &smlen, m, mlen, sk);

    for(int i = 0; i < mlen * 8; i++){
        memcpy(buf, m, mlen);
        buf[i/8] ^= 1 << (i % 8);

        crypto_sign(sm2, &smlen2, buf, mlen, sk);

            // for(int idx = 0; idx < 200; idx++){
            //     printf("%02x ", sm[idx]);
            // }printf("\n");
            // for(int idx = 0; idx < 200; idx++){
            //     printf("%02x ", sm2[idx]);
            // }printf("\n");
            // getchar();
        if(memcmp(sm, sm2, smlen) == 0 || smlen != smlen2) {
            printf("%s Bit Contribution Test Failed: Failed on messaage\n", ALGNAME);
            // printf("siglen: %d", siglen);
            // printf("siglen2: %d", siglen2);
            flag = false;
            goto EXIT;
        }
    }


EXIT:
    free(m   );
    free(sm );
    free(sm2);
    free(buf );
    free(pk );
    free(sk );

    if(flag){
        printf("%s Bit Contribution Test Success\n", ALGNAME);
        return BIT_CONTRIBUTION_SUCCESS;
    } else{
        return BIT_CONTRIBUTION_FAIL;
    }    

}
