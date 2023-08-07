#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "bit_verify.h"

#include "api.h"
#include "config.h"
#include "fips202.h"
#include "fpr.h"
#include "inner.h"
#include "normaldist.h"
#include "param.h"
#include "poly.h"
#include "precomp.h"
#include "precomp_data1024.h"
#include "randombytes.h"
#include "samplerZ.h"
#include "test_dist.h"

#define SEEDBYTES 48
int main(){
    srand(time(NULL));
    printf("SOLMAE512 metamorphic test start...\n");

    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, SEEDBYTES, 
        0, CRYPTO_BYTES+SEEDBYTES, "SOLMAE512");

    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, SEEDBYTES, 
        0, CRYPTO_BYTES+SEEDBYTES, "SOLMAE512");

    KPQCLEAN_METAMORPHIC_bit_verify_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, SEEDBYTES, 
        0, CRYPTO_BYTES+SEEDBYTES, "SOLMAE512");
   
    return 0;
}
