#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "bit_verify.h"

#include "aes256ctr.h"
#include "fips202.h"
#include "pack.h"
#include "params.h"
#include "poly.h"
#include "reduce.h"
#include "sample.h"
#include "sign.h"
#include "symmetric.h"

#define MLEN 100

int main(){
    srand(time(NULL));
    printf("GCKSign-II metamorphic test start...\n");

    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, MLEN, 
        0, CRYPTO_BYTES, "GCKSign-II");

    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, MLEN, 
        0, CRYPTO_BYTES, "GCKSign-II");

    KPQCLEAN_METAMORPHIC_bit_verify_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, MLEN, 
        0, CRYPTO_BYTES, "GCKSign-II");
   
    return 0;
}
