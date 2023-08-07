#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "bit_contribution.h"
#include "bit_exclusion.h"
#include "bit_verify.h"

#include "api.h"
#include "blas_comm.h"
#include "blas_matrix.h"
#include "blas_u32.h"
#include "blas.h"
#include "gf16.h"
#include "hash_len_config.h"
#include "mpkc.h"
#include "mqs_blas.h"
#include "mqs_config.h"
#include "mqs_keypair_computation.h"
#include "mqs_keypair.h"
#include "mqs.h"
#include "parallel_matrix_op.h"
#include "rng.h"
#include "utils_hash.h"
#include "utils_malloc.h"
#include "utils_prng.h"
#include "utils.h"

#define SEEDBYTES 32

int main(){
    srand(time(NULL));
    printf("MQS256-72-46 metamorphic test start...\n");

    KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, SEEDBYTES, 
        0, CRYPTO_BYTES+SEEDBYTES, "MQS256-72-46");

    KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, SEEDBYTES, 
        0, CRYPTO_BYTES+SEEDBYTES, "MQS256-72-46");

    KPQCLEAN_METAMORPHIC_bit_verify_test_kem(
        CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES, 0, SEEDBYTES, 
        0, CRYPTO_BYTES+SEEDBYTES, "MQS256-72-46");
   
    return 0;
}
