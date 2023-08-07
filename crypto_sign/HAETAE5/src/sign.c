#include "sign.h"
#include "fips202.h"
#include "packing.h"
#include "params.h"
#include "poly.h"
#include "polydbl.h"
#include "polymat.h"
#include "polyvec.h"
#include "randombytes.h"
#include "symmetric.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// This code is Version 0.9.
// The followings will be updated in v1.0:
// (1) Discretized Hyperball sampling
// (2) Check singular value of secret key
// (3) rANS encoding

/*************************************************
 * Name:        crypto_sign_keypair
 *
 * Description: Generates public and private key.
 *
 * Arguments:   - uint8_t *pk: pointer to output public key (allocated
 *                             array of CRYPTO_PUBLICKEYBYTES bytes)
 *              - uint8_t *sk: pointer to output private key (allocated
 *                             array of CRYPTO_SECRETKEYBYTES bytes)
 *
 * Returns 0 (success)
 **************************************************/
static const uint32_t J[32] = {
    0x7425bfb3, 0x187e11e9, 0x19da76f5, 0x2339cf64, 0x2acf3f6b, 0x68b078c1,
    0xa0d5efd5, 0x27ed4167, 0xdc47dd50, 0x8d55174d, 0xc822e7ba, 0x59117689,
    0x0e841e46, 0x3e94d7e0, 0xb3f2959a, 0x57eac7c6, 0x081c5803, 0x837b3a21,
    0xe97aa9f4, 0x65cc5866, 0xf1f826ce, 0x7be73fa8, 0xab0ec195, 0x8fe222ee,
    0x4d996626, 0xad7403c3, 0xbd126386, 0x7d22a054, 0x03bff39d, 0x1477515e,
    0x1fd29d6a, 0xe73f57ba};

int crypto_sign_keypair(uint8_t *pk, uint8_t *sk) {
    uint8_t seedbuf[2 * SEEDBYTES + CRHBYTES] = {0};
    const uint8_t *rhoprime, *sigma, *key;
    polyvecl A[K], s1;
    polyveck b, s2;

    unsigned int i, j;

    // Get entropy \rho
    //randombytes(seedbuf, SEEDBYTES);

    // fix random for metamorphic
    for(int i = 0; i < SEEDBYTES; i++){
        seedbuf[i] = 0xcc;
    }

    // Sample seeds with entropy \rho
    shake256(seedbuf, 2 * SEEDBYTES + CRHBYTES, seedbuf, SEEDBYTES);
    rhoprime = seedbuf;
    sigma = rhoprime + SEEDBYTES;
    key = sigma + CRHBYTES;

    // Expand Matrix A0
    polymat_expand(A, rhoprime);

    // Sample secret vectors s1 and s2
    polyvecl_uniform_eta(&s1, sigma, 0);
    polyveck_uniform_eta(&s2, sigma, L);

    // b = A0 * s1 + s2 mod q
    polymatkll_naivemul(&b, A, &s1);
    polyveck_add(&b, &b, &s2);
    polyveck_reduce(&b);

    // b = 2b
    polyveck_double(&b);

    // b = qj - 2b
    for (i = 0; i < K; ++i) {
        for (j = 0; j < N; ++j) {
            if (J[8 * i + (j >> 5)] & (1u << (j & 0x1f)))
                b.vec[i].coeffs[j] = Q - b.vec[i].coeffs[j];
            else
                b.vec[i].coeffs[j] = -b.vec[i].coeffs[j];
        }
    }
    polyveck_freeze2q(&b);

    // Append 1 into s1
    for (i = 0; i < N; ++i) {
        s1.vec[0].coeffs[i] = !i;
    }

    pack_pk(pk, &b, rhoprime);
    pack_sk(sk, pk, &s1, &s2, key);

    return 0;
}

/*************************************************
 * Name:        crypto_sign_signature
 *
 * Description: Computes signature.
 *
 * Arguments:   - uint8_t *sig:   pointer to output signature (of length
 *                                CRYPTO_BYTES)
 *              - size_t *siglen: pointer to output length of signature
 *              - uint8_t *m:     pointer to message to be signed
 *              - size_t mlen:    length of message
 *              - uint8_t *sk:    pointer to bit-packed secret key
 *
 * Returns 0 (success)
 **************************************************/
int crypto_sign_signature(uint8_t *sig, size_t *siglen, const uint8_t *m,
                          size_t mlen, const uint8_t *sk) {

    uint8_t buf[POLYVECK_BYTES + K * POLYETA_PACKEDBYTES] = {0};
    uint8_t seedbuf[SEEDBYTES + 1] = {0}, key[SEEDBYTES] = {0};
    uint8_t mu[SEEDBYTES] = {0};
    uint8_t cseed[SEEDBYTES] = {0}; // seed of a challenge polynomial c
    uint8_t b = 0;                  // one bit
    uint16_t counter = 0;

    polyvecl A1[K], s1, cs1;
    polyveck s2, cs2, highbits, lsb, qcj;
    polydblvecl y1, z1, z1tmp;
    polydblveck y2, z2, z2tmp;
    polyvecl z1rnd;          // round of z1
    polyveck z2rnd, h, htmp; // round of z2
    poly c;
    keccak_state state;

    unsigned int i, j;

    // Unpack secret key
    unpack_sk(A1, &s1, &s2, key, sk);

    shake256_init(&state);
    shake256_absorb(&state, sk, CRYPTO_PUBLICKEYBYTES);
    shake256_absorb(&state, m, mlen);
    shake256_finalize(&state);
    shake256_squeeze(mu, SEEDBYTES, &state);

    shake256_init(&state);
    shake256_absorb(&state, key, SEEDBYTES);
    shake256_absorb(&state, mu, SEEDBYTES);
    shake256_finalize(&state);
    shake256_squeeze(seedbuf, SEEDBYTES, &state); // seed_ybb

reject:

    /*------------------ 1. Sample y1 and y2 from hyperball ------------------*/
    //randombytes(&b, sizeof(uint8_t));

    // fix random for metamorphic
    b = 0;
    
    polydblveclk_uniform_hyperball(&y1, &y2, seedbuf, counter);

    /*------------------- 2. Compute a chanllenge c --------------------------*/
    // Round y1 and y2
    polydblvecl_round(&z1rnd, &y1);
    polydblveck_round(&z2rnd, &y2);

    // A * round(y) mod 2q = A1 * round(y1) + 2 * round(y2) mod 2q
    polymatkll_naivemul(&highbits, A1, &z1rnd);
    polyveck_double(&z2rnd);
    polyveck_add(&highbits, &highbits, &z2rnd);
    polyveck_reduce2q(&highbits);

    // HighBits of (A * round(y) mod 2q)
    polyveck_highbits(&highbits, &highbits);

    // LSB(round(y_0) * j)
    for (i = 0; i < K; ++i) {
        for (j = 0; j < N; ++j) {
            if (J[8 * i + (j >> 5)] & (1u << (j & 0x1f)))
                lsb.vec[i].coeffs[j] = 1;
            else
                lsb.vec[i].coeffs[j] = 0;
        }
    }
    for (i = 0; i < K; ++i) {
        poly_naivemul(&lsb.vec[i], &z1rnd.vec[0], &lsb.vec[i]);
    }
    polyveck_lsb(&lsb, &lsb);

    // Pack HighBits of A * round(y) mod 2q and LSB of round(y0)
    polyveck_freeze2q(&highbits);
    for (i = 0; i < K; ++i) {
        poly2q_pack(buf + i * POLY2Q_PACKEDBYTES, &highbits.vec[i]);
    }
    for (i = 0; i < K; ++i) {
        polyeta_pack(buf + POLYVECK_BYTES + i * POLYETA_PACKEDBYTES,
                     &lsb.vec[i]);
    }

    // c_seed = H(HighBits(A * y mod 2q), LSB(round(y0) * j), M)
    shake256_init(&state);
    shake256_absorb(&state, buf,
                    K * (POLY2Q_PACKEDBYTES + POLYETA_PACKEDBYTES));
    shake256_absorb(&state, mu, SEEDBYTES);
    shake256_finalize(&state);
    shake256_squeeze(cseed, SEEDBYTES, &state);

    // c = challenge(c_seed)
    poly_challenge(&c, cseed);

    /*------------------- 3. Compute z = y + (-1)^b c * s --------------------*/
    // cs = c * s = c * (s1 || s2)
    for (i = 0; i < L; ++i)
        poly_naivemul(&cs1.vec[i], &c, &s1.vec[i]);
    for (i = 0; i < K; ++i)
        poly_naivemul(&cs2.vec[i], &c, &s2.vec[i]);

    // z = y + (-1)^b cs = z1 + z2
    if (b & 1) {
        polydblvecl_sub(&z1, &y1, &cs1);
        polydblveck_sub(&z2, &y2, &cs2);
    } else {
        polydblvecl_add(&z1, &y1, &cs1);
        polydblveck_add(&z2, &y2, &cs2);
    }

    if (polydblveclk_norm2(&z1, &z2) > B1) {
        ++counter;
        goto reject;
    }

    polydblvecl_double(&z1tmp, &z1);
    polydblveck_double(&z2tmp, &z2);

    polydbldblvecl_sub(&z1tmp, &z1tmp, &y1);
    polydbldblveck_sub(&z2tmp, &z2tmp, &y2);
    if ((b & 0x2) && (polydblveclk_norm2(&z1tmp, &z2tmp) < B0)) {
        ++counter;
        goto reject;
    }

    /*------------------- 4. Make a hint -------------------------------------*/
    // Round z1 and z2
    polydblvecl_round(&z1rnd, &z1);
    polydblveck_round(&z2rnd, &z2);

    // Compute qcj
    for (i = 0; i < K; ++i) {
        for (j = 0; j < N; ++j) {
            if (J[8 * i + (j >> 5)] & (1u << (j & 0x1f)))
                qcj.vec[i].coeffs[j] = Q;
            else
                qcj.vec[i].coeffs[j] = 0;
        }
    }
    for (i = 0; i < K; ++i) {
        poly_naivemul(&qcj.vec[i], &c, &qcj.vec[i]);
    }

    // A1 * round(z1) - qcj mod 2q
    polymatkll_naivemul(&htmp, A1, &z1rnd);
    polyveck_sub(&htmp, &htmp, &qcj);
    polyveck_reduce2q(&htmp);

    // A1 * round(z1) + 2 * round(z2) - qcj mod 2q = A * round(z) - qcj mod 2q
    polyveck_double(&z2rnd);
    polyveck_add(&h, &htmp, &z2rnd);
    polyveck_reduce2q(&h);

    // HighBits of (A * round(z) - qcj mod 2q) and (A1 * round(z1) - qcj mod 2q)
    polyveck_highbits(&htmp, &htmp);
    polyveck_highbits(&h, &h);

    // h = HighBits(A * round(z) - qcj) - HighBits(A1 * round(z1) - qcj)
    polyveck_sub(&h, &h, &htmp);

    /*------------------ Pack signature -------------------*/
    polyveck_freeze2q(&h);
    pack_sig(sig, cseed, &z1rnd, &h);
    *siglen = CRYPTO_BYTES;

    return 0;
}

/*************************************************
 * Name:        crypto_sign
 *
 * Description: Compute signed message.
 *
 * Arguments:   - uint8_t *sm: pointer to output signed message (allocated
 *                             array with CRYPTO_BYTES + mlen bytes),
 *                             can be equal to m
 *              - size_t *smlen: pointer to output length of signed
 *                               message
 *              - const uint8_t *m: pointer to message to be signed
 *              - size_t mlen: length of message
 *              - const uint8_t *sk: pointer to bit-packed secret key
 *
 * Returns 0 (success)
 **************************************************/
int crypto_sign_sign(uint8_t *sm, size_t *smlen, const uint8_t *m, size_t mlen,
                     const uint8_t *sk) {
    size_t i;

    for (i = 0; i < mlen; ++i)
        sm[CRYPTO_BYTES + mlen - 1 - i] = m[mlen - 1 - i];
    crypto_sign_signature(sm, smlen, sm + CRYPTO_BYTES, mlen, sk);
    *smlen += mlen;
    return 0;
}

/*************************************************
 * Name:        crypto_sign_verify
 *
 * Description: Verifies signature.
 *
 * Arguments:   - uint8_t *m: pointer to input signature
 *              - size_t siglen: length of signature
 *              - const uint8_t *m: pointer to message
 *              - size_t mlen: length of message
 *              - const uint8_t *pk: pointer to bit-packed public key
 *
 * Returns 0 if signature could be verified correctly and -1 otherwise
 **************************************************/
int crypto_sign_verify(const uint8_t *sig, size_t siglen, const uint8_t *m,
                       size_t mlen, const uint8_t *pk) {
    unsigned int i, j;
    uint8_t buf[POLYVECK_BYTES + K * POLYETA_PACKEDBYTES] = {0};
    uint8_t c_seed[SEEDBYTES] = {0}, c_seed2[SEEDBYTES] = {0};
    uint8_t rhoprime[SEEDBYTES] = {0};
    polyvecl A1[K], z1;
    polyveck b, qcj, highbits, lowbits, h, hprime, z2;
    poly c;
    keccak_state state;

    // Check signature length
    if (siglen != CRYPTO_BYTES) {
        return -1;
    }

    // Unpack public key
    unpack_pk(&b, rhoprime, pk);

    // Unpack signature and Check conditions
    if (unpack_sig(c_seed, &z1, &h, sig)) {
        return -1;
    }

    /*------------------- 1. Recover A1 --------------------------------------*/
    // A1 = (-2b + qj || 2 * A0)
    polymat_expand(A1, rhoprime);
    polymatkl_double(A1);
    for (i = 0; i < K; ++i) {
        A1[i].vec[0] = b.vec[i];
    }

    /*------------------- 2. Compute \tilde{z}_2 -----------------------------*/
    // h * alpha
    for (i = 0; i < K; ++i)
        for (j = 0; j < N; ++j)
            z2.vec[i].coeffs[j] = h.vec[i].coeffs[j] * ALPHA;

    // c = challenge(c_seed)
    poly_challenge(&c, c_seed);

    // A1 * round(z1) - qcj mod 2q
    polymatkll_naivemul(&highbits, A1, &z1);

    // Compute qcj
    for (i = 0; i < K; ++i) {
        for (j = 0; j < N; ++j) {
            if (J[8 * i + (j >> 5)] & (1u << (j & 0x1f)))
                qcj.vec[i].coeffs[j] = Q;
            else
                qcj.vec[i].coeffs[j] = 0;
        }
    }
    for (i = 0; i < K; ++i) {
        poly_naivemul(&qcj.vec[i], &c, &qcj.vec[i]);
    }
    polyveck_sub(&highbits, &highbits, &qcj);
    polyveck_reduce2q(&highbits);

    // 2 * LowBits(A1 * round(z1) - qcj mod 2q)
    polyveck_lowbits(&lowbits, &highbits);
    polyveck_double(&lowbits);

    // z2 = (h * alpha - 2 * LowBits(d)) / 2
    polyveck_sub(&z2, &z2, &lowbits);
    for (i = 0; i < K; ++i)
        for (j = 0; j < N; ++j)
            z2.vec[i].coeffs[j] >>= 1;
    polyveck_reduce(&z2);

    if (polyveclk_norm2(&z1, &z2) > B2) {
        //printf("fail: norm2 [%f] > %f\n", polyveclk_norm2(&z1, &z2), B2);
        fflush(stdout);
        return -1;
    }

    /*------------------- 3. Compute h' = LSB((z_{1,0} - c) * j) -------------*/
    poly_sub(&c, &z1.vec[0], &c);

    // hprime = (z_{1,0} - c) * j
    for (i = 0; i < K; ++i) {
        for (j = 0; j < N; ++j) {
            if (J[8 * i + (j >> 5)] & (1u << (j & 0x1f)))
                hprime.vec[i].coeffs[j] = 1;
            else
                hprime.vec[i].coeffs[j] = 0;
        }
    }
    for (i = 0; i < K; ++i) {
        poly_naivemul(&hprime.vec[i], &c, &hprime.vec[i]);
    }

    // h' = LSB((z_{1,0} - c) * j)
    polyveck_lsb(&hprime, &hprime);

    /*------------------- 4. Compute c_seed' and Compare ---------------------*/
    polyveck_double(&z2);
    polyveck_add(&highbits, &highbits, &z2);
    polyveck_reduce2q(&highbits);
    polyveck_highbits(&highbits, &highbits);

    // Pack highBits(A * round(z) - qcj mod 2q) and h'
    polyveck_freeze2q(&highbits);
    for (i = 0; i < K; ++i) {
        poly2q_pack(buf + POLY2Q_PACKEDBYTES * i, &highbits.vec[i]);
    }
    for (i = 0; i < K; ++i) {
        polyeta_pack(buf + POLYVECK_BYTES + POLYETA_PACKEDBYTES * i,
                     &hprime.vec[i]);
    }

    shake256_init(&state);
    shake256_absorb(&state, pk, CRYPTO_PUBLICKEYBYTES);
    shake256_absorb(&state, m, mlen);
    shake256_finalize(&state);
    shake256_squeeze(c_seed2, SEEDBYTES, &state);

    // c_seed' = H(HighBits(A * round(z) - qcj mod 2q) and h', M)
    shake256_init(&state);
    shake256_absorb(&state, buf,
                    K * (POLY2Q_PACKEDBYTES + POLYETA_PACKEDBYTES));
    shake256_absorb(&state, c_seed2, SEEDBYTES);
    shake256_finalize(&state);
    shake256_squeeze(c_seed2, SEEDBYTES, &state);

    for (i = 0; i < SEEDBYTES; ++i) {
        if (c_seed[i] != c_seed2[i]) {
            //printf("fail: c_seed != c_seed2 in [%d]\n", i);
            fflush(stdout);
            return -1;
        }
    }

    return 0;
}

/*************************************************
 * Name:        crypto_sign_open
 *
 * Description: Verify signed message.
 *
 * Arguments:   - uint8_t *m: pointer to output message (allocated
 *                            array with smlen bytes), can be equal to sm
 *              - size_t *mlen: pointer to output length of message
 *              - const uint8_t *sm: pointer to signed message
 *              - size_t smlen: length of signed message
 *              - const uint8_t *pk: pointer to bit-packed public key
 *
 * Returns 0 if signed message could be verified correctly and -1 otherwise
 **************************************************/
int crypto_sign_open(uint8_t *m, size_t *mlen, const uint8_t *sm, size_t smlen,
                     const uint8_t *pk) {
    size_t i;

    if (smlen < CRYPTO_BYTES)
        goto badsig;

    *mlen = smlen - CRYPTO_BYTES;
    if (crypto_sign_verify(sm, CRYPTO_BYTES, sm + CRYPTO_BYTES, *mlen, pk))
        goto badsig;
    else {
        /* All good, copy msg, return 0 */
        for (i = 0; i < *mlen; ++i)
            m[i] = sm[CRYPTO_BYTES + i];
        return 0;
    }

badsig:
    /* Signature verification failed */
    *mlen = -1;
    for (i = 0; i < smlen; ++i)
        m[i] = 0;

    return -1;
}
