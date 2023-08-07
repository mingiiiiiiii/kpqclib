#include "packing.h"
#include "params.h"
#include "poly.h"
#include "polymat.h"
#include "polyvec.h"
#include <string.h>

/*************************************************
 * Name:        pack_pk
 *
 * Description: Bit-pack public key pk = (seed, b).
 *
 * Arguments:   - uint8_t pk[]: output byte array
 *              - const polyveck *b: polynomial vector of length K containg b
 *              - const uint8_t seed[]: seed for A'
 **************************************************/
void pack_pk(uint8_t pk[CRYPTO_PUBLICKEYBYTES], const polyveck *b,
             const uint8_t seed[SEEDBYTES]) {
    unsigned int i;

    memcpy(pk, seed, SEEDBYTES);

    pk += SEEDBYTES;
    for (i = 0; i < K; ++i) {
        poly2q_pack(pk + i * POLY2Q_PACKEDBYTES, &b->vec[i]);
    }
}

/*************************************************
 * Name:        unpack_pk
 *
 * Description: Unpack public key pk = (seed, b).
 *
 * Arguments:   - uint8_t seed[]: seed for A'
 *              - polyveck *b: polynomial vector of length K containg b
 *              - const uint8_t pk[]: output byte array
 **************************************************/
void unpack_pk(polyveck *b, uint8_t seed[SEEDBYTES],
               const uint8_t pk[CRYPTO_PUBLICKEYBYTES]) {
    unsigned int i;

    memcpy(seed, pk, SEEDBYTES);

    pk += SEEDBYTES;
    for (i = 0; i < K; ++i) {
        poly2q_unpack(&b->vec[i], pk + i * POLY2Q_PACKEDBYTES);
    }
}

/*************************************************
 * Name:        pack_sk
 *
 * Description: Bit-pack secret key sk = (pk, s).
 *
 * Arguments:   - uint8_t sk[]: output byte array
 *              - const uint8_t pk[PUBLICKEYBYTES]: packed pk
 *              - const polyvecl *s0: polyvecl pointer containing s0
 *              - const polyveck *s1: polyveck pointer containing s1
 **************************************************/
void pack_sk(uint8_t sk[CRYPTO_SECRETKEYBYTES],
             const uint8_t pk[CRYPTO_PUBLICKEYBYTES], const polyvecl *s0,
             const polyveck *s1, const uint8_t key[SEEDBYTES]) {
    unsigned int i;
    memcpy(sk, pk, CRYPTO_PUBLICKEYBYTES);

    sk += CRYPTO_PUBLICKEYBYTES;
    for (i = 0; i < L; ++i)
        polyeta_pack(sk + i * POLYETA_PACKEDBYTES, &s0->vec[i]);

    sk += L * POLYETA_PACKEDBYTES;
    for (i = 0; i < K; ++i)
        polyeta_pack(sk + i * POLYETA_PACKEDBYTES, &s1->vec[i]);
    sk += K * POLYETA_PACKEDBYTES;
    memcpy(sk, key, SEEDBYTES);
}

/*************************************************
 * Name:        unpack_sk
 *
 * Description: Unpack secret key sk = (A, s).
 *
 * Arguments:   - polyvecl A[K]: output polyvecl array for A
 *              - polyvecl s0: output polyvecl pointer for s0
 *              - polyveck s1: output polyveck pointer for s1
 *              - const uint8_t sk[]: byte array containing bit-packed sk
 **************************************************/
void unpack_sk(polyvecl A[K], polyvecl *s0, polyveck *s1, uint8_t *key,
               const uint8_t sk[CRYPTO_SECRETKEYBYTES]) {
    unsigned int i;
    uint8_t rhoprime[SEEDBYTES];
    polyveck b;

    unpack_pk(&b, rhoprime, sk);

    sk += CRYPTO_PUBLICKEYBYTES;
    for (i = 0; i < L; ++i)
        polyeta_unpack(&s0->vec[i], sk + i * POLYETA_PACKEDBYTES);

    sk += L * POLYETA_PACKEDBYTES;
    for (i = 0; i < K; ++i)
        polyeta_unpack(&s1->vec[i], sk + i * POLYETA_PACKEDBYTES);

    sk += K * POLYETA_PACKEDBYTES;
    memcpy(key, sk, SEEDBYTES);

    // A' = PRG(rhoprime)
    polymat_expand(A, rhoprime);

    // A = 2A'
    polymatkl_double(A);

    // append b into A
    for (i = 0; i < K; ++i) {
        A[i].vec[0] = b.vec[i];
    }
}

/*************************************************
 * Name:        pack_sig
 *
 * Description: Bit-pack signature sig = (c, z0, h).
 *
 * Arguments:   - uint8_t sig[]: output byte array
 *              - const uint8_t c[]: pointer to seed of challenge
 *              - const polyvecl *z0: pointer to vector z0 of length L
 *              - const polyveck *h: pointer to vector h of length K
 **************************************************/
void pack_sig(uint8_t sig[CRYPTO_BYTES], const uint8_t c_seed[SEEDBYTES],
              const polyvecl *z0, const polyveck *h) {
    unsigned int i;

    for (i = 0; i < SEEDBYTES; ++i)
        sig[i] = c_seed[i];
    sig += SEEDBYTES;

    for (i = 0; i < L; ++i)
        polyB1_pack(sig + POLYB1_PACKEDBYTES * i, &z0->vec[i]);
    sig += POLYB1_PACKEDBYTES * L;

    for (i = 0; i < K; ++i)
        poly2q_pack(sig + POLY2Q_PACKEDBYTES * i, &h->vec[i]);
}

/*************************************************
 * Name:        unpack_sig
 *
 * Description: Unpack signature sig = (c, z0, h).
 *
 * Arguments:   - uint8_t c_seed[]: pointer to output seed of challenge
 *              - polyvecl *z0: pointer to output vector z0
 *              - polyveck *h: pointer to output vector h
 *              - const uint8_t sig[]: byte array containing
 *                bit-packed signature
 *
 * Returns 1 in case of malformed signature; otherwise 0.
 **************************************************/
int unpack_sig(uint8_t c_seed[SEEDBYTES], polyvecl *z0, polyveck *h,
               const uint8_t sig[CRYPTO_BYTES]) {
    unsigned int i;

    for (i = 0; i < SEEDBYTES; ++i)
        c_seed[i] = sig[i];
    sig += SEEDBYTES;

    for (i = 0; i < L; ++i)
        polyB1_unpack(&z0->vec[i], sig + POLYB1_PACKEDBYTES * i);
    sig += POLYB1_PACKEDBYTES * L;

    for (i = 0; i < K; ++i)
        poly2q_unpack(&h->vec[i], sig + POLY2Q_PACKEDBYTES * i);
    return 0;
}