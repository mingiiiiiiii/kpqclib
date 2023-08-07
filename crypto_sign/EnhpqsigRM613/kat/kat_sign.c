#include "api.h"
#include <stdint.h>

int kat_crypto_sign_keypair(uint8_t *pk, uint8_t *sk) {
    return crypto_sign_keypair(pk, sk);
}

int
kat_crypto_sign(unsigned char *sm, unsigned long long *smlen,
            const unsigned char *m, unsigned long long mlen,
            const unsigned char *sk){
                return crypto_sign(sm, smlen, m, mlen, sk);
            }


int
kat_crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                 const unsigned char *sm, unsigned long long smlen,
                 const unsigned char *pk){
    return crypto_sign_open(m, mlen, sm, smlen, pk);
}