#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "randombytes.h"
#include "sign.h"

#define MLEN 59
#define Iterations (200)

uint8_t print_flag = 1;

int sign_verify_test(void);

int main(void) {
    printf("NCCSign mode = %d\n", NIMS_MODE);
    size_t count = 1;
    for (int i = 0; i < Iterations; ++i) {
        if (sign_verify_test()) {
            printf("Invalid on %d-th test\n", i);
            break;
        }

        if (!(i % (Iterations / 10))) {
            printf("...%lu%%", count * 10);
            fflush(stdout);
            ++count;
        }
    }
    printf("\n");

    return 0;
}

int sign_verify_test(void) {
    if (print_flag) {
        printf(">> sign and verify test\n");
        print_flag = 0;
    }
  int ret = 0;
  size_t mlen, smlen;
	uint8_t m[MLEN] = { 0 };
	uint8_t sm[MLEN + CRYPTO_BYTES];
	uint8_t m2[MLEN + CRYPTO_BYTES];
	uint8_t pk[CRYPTO_PUBLICKEYBYTES];
	uint8_t sk[CRYPTO_SECRETKEYBYTES];

    randombytes(m, MLEN);

		crypto_sign_keypair(pk, sk);
		crypto_sign(sm, &smlen, m, MLEN, sk);
		ret = crypto_sign_open(m2, &mlen, sm, smlen, pk);

		if (ret) {
			fprintf(stderr, "Verification failed\n");
			return 1;
		}

		if (mlen != MLEN) {
			fprintf(stderr, "Message lengths don't match\n");
			return 1;
		}

        return 0;

}
