#include <stdio.h>
#include <stdint.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "rng.h"
#include "api.h"
#include "gf_table_gen.h"

#define MAX_CRYPTO_PUBLICKEYBYTES   1025024
#define MAX_CRYPTO_SECRETKEYBYTES   357064
#define MAX_CRYPTO_CIPHERTEXTBYTES  240
#define MAX_CRYPTO_BYTES            32


int main(){
    printf("PALOMA128 metamorphic test start...\n");

    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        MAX_CRYPTO_PUBLICKEYBYTES, MAX_CRYPTO_SECRETKEYBYTES, 0, 0, MAX_CRYPTO_CIPHERTEXTBYTES, MAX_CRYPTO_BYTES, "PALOMA128");
    
    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        MAX_CRYPTO_PUBLICKEYBYTES, MAX_CRYPTO_SECRETKEYBYTES, 0, 0, MAX_CRYPTO_CIPHERTEXTBYTES, MAX_CRYPTO_BYTES, "PALOMA128");

    return 0;
}
