#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <assert.h>

#include "api.h"
#include "blas_comm.h"
#include "blas_matrix.h"
#include "blas_u32.h"
#include "blas.h"
#include "gf16.h"
#include "hash_len_config.h"
#include "mpkc.h"
#include "mqs_blas.h"
#include "mqs_config.h"
#include "mqs_keypair_computation.h"
#include "mqs_keypair.h"
#include "mqs.h"
#include "parallel_matrix_op.h"
#include "rng.h"
#include "utils_hash.h"
#include "utils_malloc.h"
#include "utils_prng.h"
#include "utils.h"
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
    unsigned char seed[48];
    unsigned char       entropy_input[48];
    randombytes_init(entropy_input, NULL, 256);
    randombytes_init(seed, NULL, 256);
    randombytes(seed, 48);

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

    crypto_sign_keypair(pk, sk, seed);
    crypto_sign(sm, &smlen, m, mlen, sk, seed, 0);

    for(int i = 0; i < mlen * 8; i++){
        memcpy(buf, m, mlen);
        buf[i/8] ^= 1 << (i % 8);
        

        crypto_sign(sm2, &smlen2, buf, mlen, sk, seed, 0);

        if(memcmp(sm2, sm, smlen) == 0 || smlen != smlen2) {
    
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
