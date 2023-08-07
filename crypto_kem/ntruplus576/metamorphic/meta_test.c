#include <stdio.h>
#include <stdint.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "params.h"
#include "api.h"


int main(){
    printf("NTRU+576 metamorphic test start...\n");

    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        NTRUPLUS_PUBLICKEYBYTES, NTRUPLUS_SECRETKEYBYTES, 0, 0, NTRUPLUS_CIPHERTEXTBYTES, NTRUPLUS_SSBYTES, "NTRU+576");
    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        NTRUPLUS_PUBLICKEYBYTES, NTRUPLUS_SECRETKEYBYTES, 0, 0, NTRUPLUS_CIPHERTEXTBYTES, NTRUPLUS_SSBYTES, "NTRU+576");

    return 0;
}
