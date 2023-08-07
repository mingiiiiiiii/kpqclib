#include "api.h"
#include "TIGER_CCAKEM.h"
#include "poison.h"

int kat_crypto_kem_keypair(unsigned char *pk, unsigned char *sk) {
    KEM_Keygen(pk, sk);
    return 0;
}

int kat_crypto_kem_enc( unsigned char *ct, unsigned char *ss, const unsigned char *pk){
    KEM_Enc(ct, ss, pk);
    return 0;
}

int kat_crypto_kem_dec( unsigned char *ss, const unsigned char *ct, const unsigned char *sk, unsigned char* pk){
    // poison(sk, LWE_N);
    return KEM_dec(ss, ct, sk, pk);
}