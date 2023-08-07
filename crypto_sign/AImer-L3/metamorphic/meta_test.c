#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "aimer.h"


int main(){
    srand(time(NULL));
    printf("AIMer L3 metamorphic test start...\n");
    
    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        AIMER_PUBLICKEY_SIZE, AIMER_PRIVATEKEY_SIZE, 0, 32, 
        0, AIMER_MAX_SIGNATURE_SIZE, "AIMer L3");

    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        AIMER_PUBLICKEY_SIZE, AIMER_PRIVATEKEY_SIZE, 0, 32, 
        0, AIMER_MAX_SIGNATURE_SIZE, "AIMer L3");
   
    return 0;
}
