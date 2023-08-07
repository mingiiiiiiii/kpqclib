#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#include "api.h"
#include "rng.h"
#include "params.h"

#include "bit_contribution.h"

#define BIT_CONTRIBUTION_SUCCESS    0
#define BIT_VERIFY_SUCCESS          0
#define BIT_CONTRIBUTION_FAIL       -1

#define BIT_VERIFY_FAIL             -1


int KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t crypto_bytes, char* ALGNAME) 
{
    uint8_t* pk     = NULL;
    uint8_t* sk     = NULL;
    uint8_t* buf    = NULL;
    uint8_t* m      = NULL;
    uint8_t* c      = NULL;
    uint8_t* ss     = NULL;
    uint8_t* ss1    = NULL;
    uint8_t* ss2    = NULL;
    uint8_t* k2     = NULL; // may not used depend on alg.
    uint8_t* dec1   = NULL;
    bool flag = true;

    pk  = (uint8_t*)calloc(pklen,           sizeof(uint8_t));
    sk  = (uint8_t*)calloc(sklen,           sizeof(uint8_t));
    buf = (uint8_t*)calloc(sklen,           sizeof(uint8_t));
    m   = (uint8_t*)calloc(mlen,            sizeof(uint8_t));
    c   = (uint8_t*)calloc(clen,            sizeof(uint8_t));
    ss  = (uint8_t*)calloc(crypto_bytes,    sizeof(uint8_t));
    ss1 = (uint8_t*)calloc(crypto_bytes,    sizeof(uint8_t));
    ss2 = (uint8_t*)calloc(crypto_bytes,    sizeof(uint8_t));
    k2  = (uint8_t*)calloc(keylen,          sizeof(uint8_t));
    
    // Generate keypair
    crypto_kem_keypair(pk, sk); //random seed -> Gen pk and sk

    // Encapsulation
    crypto_kem_enc(c, ss, pk); // BCT, BET -> pk only & memcmp -> ct only //! through pk, gen ss and c, c is ciphertext of ss

    for(int i = 0; i < sklen; i++){
        memcpy(buf, sk, sklen);

        buf[i/8] ^= 1 << (i % 8); //! change sk

        //? relation : if pk changed, then recovered ss is different?
        crypto_kem_dec(ss1, c, sk); //ss1
        crypto_kem_dec(ss2, c, buf); //ss2
        
        if(memcmp(ss1, ss2, crypto_bytes) != 0){
            continue;
        } else {
            printf("%s Bit Contribution Test Fail: Failed on sk\n", ALGNAME);
            flag = false;
            goto EXIT;
        }
    }

    // ss, c contribution
    free(buf);
    buf = (uint8_t*)calloc(clen, sizeof(uint8_t));
    for(int i = 0; i < clen; i++){
        memcpy(buf, c, clen);

        buf[i/8] ^= 1 << (i % 8);

        crypto_kem_dec(ss1,   c, sk);
        crypto_kem_dec(ss2, buf, sk);

        if(memcmp(ss1, ss2, crypto_bytes) != 0){
            continue;
        } else {
            printf("%s Bit Contribution Test Fail: Failed on ct\n", ALGNAME);
            flag = false;
            goto EXIT;
        }
    }

EXIT:
    free(pk ); 
    free(sk ); 
    free(buf); 
    free(m  ); 
    free(c  ); 
    free(ss ); 
    free(ss1); 
    free(ss2); 
    free(k2 ); 

    if(flag){
        printf("%s Bit Exclusion Test Success\n", ALGNAME);
        return BIT_CONTRIBUTION_SUCCESS;
    } else{
        return BIT_CONTRIBUTION_FAIL;
    }    

}
