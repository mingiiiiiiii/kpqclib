#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "rng.h"
#include "api.h"
#include "gf_table_gen.h"

#include "bit_exclusion.h"


int KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t crypto_bytes, char* ALGNAME)
{
    uint8_t* pk     = NULL;
    uint8_t* sk     = NULL;
    uint8_t* buf    = NULL;
    uint8_t* m      = NULL;
    uint8_t* c      = NULL;
    uint8_t* c2     = NULL;
    uint8_t* ss     = NULL;
    uint8_t* ss1    = NULL;
    uint8_t* ss2    = NULL;
    uint8_t* k2     = NULL; // may not used depend on alg.
    uint8_t* dec1   = NULL;
    bool flag = true;

    PARAM PALOMAparam;
    int n, t, k;

    t = 128;     
    n = 6592;   
    k = (n-(13*t));  

    pk  = (uint8_t*)calloc(pklen,           sizeof(uint8_t));
    sk  = (uint8_t*)calloc(sklen + EXCLUSION_BYTELEN,           sizeof(uint8_t));
    buf = (uint8_t*)calloc(sklen + EXCLUSION_BYTELEN,           sizeof(uint8_t));
    m   = (uint8_t*)calloc(mlen,            sizeof(uint8_t));
    c   = (uint8_t*)calloc(clen,            sizeof(uint8_t));
    ss  = (uint8_t*)calloc(crypto_bytes,    sizeof(uint8_t));
    ss1 = (uint8_t*)calloc(crypto_bytes,    sizeof(uint8_t));
    ss2 = (uint8_t*)calloc(crypto_bytes,    sizeof(uint8_t));
    k2  = (uint8_t*)calloc(keylen,          sizeof(uint8_t));
    
    // Generate keypair
    GF_init(&PALOMAparam, n, k, t);
    crypto_PALOMA_keypair(pk, sk, &PALOMAparam); //random seed -> Gen pk and sk

    // Encapsulation
    crypto_PALOMA_enc(c, ss, pk, &PALOMAparam); // BCT, BET -> pk only & memcmp -> ct only //! through pk, gen ss and c, c is ciphertext of ss

    for(int j = 0; j < EXCLUSION_BYTELEN * 8; j++){
        memcpy(buf, sk, sklen);
        buf[sklen + j/8] ^= 1 << (j%8);

        crypto_PALOMA_dec(ss1, c, sk,  &PALOMAparam); //ss1
        crypto_PALOMA_dec(ss2, c, buf, &PALOMAparam); //ss2

        if(memcmp(ss1, ss2, crypto_bytes) == 0){
            continue;
        } else {
            printf("%s Bit Exclusion Test Fail: Failed on sk\n", ALGNAME);
            for(int i = 0; i < crypto_bytes; i++){
                printf("%02x ", ss1[i]);
            }printf("\n");
            for(int i = 0; i < crypto_bytes; i++){
                printf("%02x ", ss2[i]);
            }printf("\n");
            flag = false;
            goto EXIT;
        }
    }

    free(buf);
    buf = (uint8_t*)calloc(clen + EXCLUSION_BYTELEN, sizeof(uint8_t));
    for(int i = 0; i < EXCLUSION_BYTELEN * 8; i++){
        memcpy(buf, c, clen);
        buf[clen + i/8] ^= 1 << (i%8);

        crypto_PALOMA_dec(ss1, c, sk,  &PALOMAparam); //ss1
        crypto_PALOMA_dec(ss2, c, buf, &PALOMAparam); //ss2

        if(memcmp(ss1, ss2, crypto_bytes) == 0){
            continue;
        } else {
            printf("%s Bit Exclusion Test Fail: Failed on ct\n", ALGNAME);
            for(int j = 0; j < crypto_bytes; j++){
                printf("%02x ", ss1[j]);
            }printf("\n");
            for(int j = 0; j < crypto_bytes; j++){
                printf("%02x ", ss2[j]);
            }printf("\n");
            flag = false;
            goto EXIT;
        }
    }

EXIT:
    // free(pk ); 
    // free(sk ); 
    // free(buf); 
    // free(m  ); 
    // free(c  ); 
    // free(ss ); 
    // free(ss1); 
    // free(ss2); 
    // free(k2 ); 

    if(flag){
        printf("%s Bit Exclusion Test Success\n", ALGNAME);
        return BIT_EXCLUSION_SUCCESS;
    } else{
        return BIT_EXCLUSION_FAIL;
    }
}