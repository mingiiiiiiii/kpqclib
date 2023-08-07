#include <stdio.h>
#include <stdint.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "params.h"


int main(){
    printf("TIGER192 metamorphic test start...\n");

    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        PUBLICKEYSIZE, SECRETKEYSIZE, 0, 0, CIPHERTEXTSIZE, KK_LEN, "TIGER192");
    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        PUBLICKEYSIZE, SECRETKEYSIZE, 0, 0, CIPHERTEXTSIZE, KK_LEN);

    return 0;
}
