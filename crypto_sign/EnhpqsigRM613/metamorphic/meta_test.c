#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "bit_verify.h"

#include "rng.h"
#include "api.h"
#include "common.h"
#include "matrix.h"
#include "nearest_vector.h"
#include "parm.h"
#include "rm.h"
#include "rng.h"

#define MLEN 100

int main(){
    srand(time(NULL));
    printf("EnhPQSigRM613 metamorphic test start...\n");

    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, MLEN, 
        0, CRYPTO_BYTES, "EnhPQSigRM613");

    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, MLEN, 
        0, CRYPTO_BYTES, "EnhPQSigRM613");

    KPQCLEAN_METAMORPHIC_bit_verify_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, MLEN, 
        0, CRYPTO_BYTES, "EnhPQSigRM613");
   
    return 0;
}
