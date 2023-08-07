#include <stdio.h>
#include <stdint.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "parameters.h"


int main(){
    printf("SMAUG1 metamorphic test start...\n");

    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        PUBLICKEY_BYTES, KEM_SECRETKEY_BYTES, 0, 0, CIPHERTEXT_BYTES, CRYPTO_BYTES, "SMAUG1");
    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        PUBLICKEY_BYTES, KEM_SECRETKEY_BYTES, 0, 0, CIPHERTEXT_BYTES, CRYPTO_BYTES, "SMAUG1");

    return 0;
}
