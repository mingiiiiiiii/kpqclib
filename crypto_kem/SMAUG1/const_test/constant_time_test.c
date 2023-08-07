#include "api.h"
#include "rng.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "poison.h"

#define MAX_MARKER_LEN 50
#define KAT_SUCCESS 0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR -3
#define KAT_CRYPTO_FAILURE -4

int main(int argc, const char **argv) {
    
    unsigned char seed[48];
    unsigned char entropy_input[48];
    unsigned char ct[CRYPTO_CIPHERTEXTBYTES], ss[CRYPTO_BYTES],
        ss1[CRYPTO_BYTES];
    int count;
    int done;
    unsigned char pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_KEM_SECRETKEYBYTES];
    int ret_val;

    for (int i = 0; i < 48; i++){
        entropy_input[i] = i;
    }
    
    randombytes_init(entropy_input, NULL, 256);
    
    for (int i = 0; i < 100; i++) {
        randombytes(seed, 48);
    }

    randombytes_init(seed, NULL, 256);
    
    kat_crypto_kem_keypair(pk, sk);
    printf("crypto_kem_keypair finished\n");

    kat_crypto_kem_enc(ct, ss, pk);
    printf("crypto_kem_enc finished\n");

    //todo poison sk
    poison(sk, CRYPTO_KEM_SECRETKEYBYTES);

    kat_crypto_kem_dec(ss1, ct, pk, sk);
    printf("crypto_kem_dec finished\n");

    // if (memcmp(ss, ss1, CRYPTO_BYTES)) {
    //     printf("crypto_kem_dec returned bad 'ss' value\n");
    //     return KAT_CRYPTO_FAILURE;
    // }

    // return KAT_SUCCESS;
    return 0;
}
