#include "poly.h"
#include "ntt.h"
#include "params.h"
#include "reduce.h"
#include "rounding.h"
#include "symmetric.h"
#include <stdint.h>

#ifdef DBENCH
#include "test/cpucycles.h"
extern const uint64_t timing_overhead;
extern uint64_t *tred, *tadd, *tmul, *tround, *tsample, *tpack;
#define DBENCH_START() uint64_t time = cpucycles()
#define DBENCH_STOP(t) t += cpucycles() - time - timing_overhead
#else
#define DBENCH_START()
#define DBENCH_STOP(t)
#endif

/*************************************************
 * Name:        poly_add
 *
 * Description: Add polynomials. No modular reduction is performed.
 *
 * Arguments:   - poly *c: pointer to output polynomial
 *              - const poly *a: pointer to first summand
 *              - const poly *b: pointer to second summand
 **************************************************/
void poly_add(poly *c, const poly *a, const poly *b) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        c->coeffs[i] = a->coeffs[i] + b->coeffs[i];

    DBENCH_STOP(*tadd);
}

/*************************************************
 * Name:        poly_sub
 *
 * Description: Subtract polynomials. No modular reduction is
 *              performed.
 *
 * Arguments:   - poly *c: pointer to output polynomial
 *              - const poly *a: pointer to first input polynomial
 *              - const poly *b: pointer to second input polynomial to be
 *                               subtraced from first input polynomial
 **************************************************/
void poly_sub(poly *c, const poly *a, const poly *b) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        c->coeffs[i] = a->coeffs[i] - b->coeffs[i];

    DBENCH_STOP(*tadd);
}

/*************************************************
 * Name:        poly_naivemul
 *
 * Description: Naive Multiplication and modular by 2q
 *
 * Arguments:   - poly *c: pointer to output polynomial
 *              - const poly *a: pointer to input polynomial
 *              - const poly *b: pointer to input polynomial
 *
 **************************************************/
void poly_naivemul(poly *c, const poly *a, const poly *b) {
    unsigned int i, j;
    int32_t r[2 * N] = {0};

    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            r[i + j] = (r[i + j] + (int64_t)a->coeffs[i] * b->coeffs[j]) % DQ;

    for (i = N; i < 2 * N; ++i)
        r[i - N] = (r[i - N] - r[i]) % DQ;

    for (i = 0; i < N; ++i)
        c->coeffs[i] = r[i];
}

/*************************************************
 * Name:        poly_reduce
 *
 * Description: Inplace reduction of all coefficients of polynomial to
 *              representative in [-6283009,6283007].
 *
 * Arguments:   - poly *a: pointer to input/output polynomial
 **************************************************/
void poly_reduce(poly *a) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        a->coeffs[i] = reduce32(a->coeffs[i]);

    DBENCH_STOP(*tred);
}

/*************************************************
 * Name:        poly_reduce2q
 *
 * Description: Inplace reduction of all coefficients of polynomial to 2q
 *
 * Arguments:   - poly *a: pointer to input/output polynomial
 **************************************************/
void poly_reduce2q(poly *a) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        a->coeffs[i] = reduce32_2q(a->coeffs[i]);

    DBENCH_STOP(*tred);
}

/*************************************************
 * Name:        poly_cadd2q
 *
 * Description: For all coefficients of in/out polynomial add 2Q if
 *              coefficient is negative.
 *
 * Arguments:   - poly *a: pointer to input/output polynomial
 **************************************************/
void poly_cadd2q(poly *a) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        a->coeffs[i] = cadd2q(a->coeffs[i]);

    DBENCH_STOP(*tred);
}

/*************************************************
 * Name:        poly_freeze2q
 *
 * Description: For all coefficients of in/out polynomial compute standard
 *              representative r = a mod^+ 2Q
 *
 * Arguments:   - poly *a: pointer to input/output polynomial
 **************************************************/
void poly_freeze2q(poly *a) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        a->coeffs[i] = freeze2q(a->coeffs[i]);

    DBENCH_STOP(*tred);
}

/*************************************************
 * Name:        poly_highbits
 *
 * Description: Compute HighBits of polynomial
 *
 * Arguments:   - poly *a2: pointer to output polynomial
 *              - const poly *a: pointer to input polynomial
 **************************************************/
void poly_highbits(poly *a2, const poly *a) {
    unsigned int i;
    int32_t a1tmp, a0tmp;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        decompose(&a2->coeffs[i], &a1tmp, &a0tmp, a->coeffs[i]);

    DBENCH_STOP(*tround);
}

/*************************************************
 * Name:        poly_lowbits
 *
 * Description: Compute LowBits of polynomial
 *
 * Arguments:   - poly *a1: pointer to output polynomial
 *              - const poly *a: pointer to input polynomial
 **************************************************/
void poly_lowbits(poly *a1, const poly *a) {
    unsigned int i = 0;
    int32_t a2tmp = 0, a0tmp = 0;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        decompose(&a2tmp, &a1->coeffs[i], &a0tmp, a->coeffs[i]);

    DBENCH_STOP(*tround);
}

/*************************************************
 * Name:        poly_lsb
 *
 * Description: Compute least significant bits of polynomial
 *
 * Arguments:   - poly *a0: pointer to output polynomial
 *              - const poly *a: pointer to input polynomial
 **************************************************/
void poly_lsb(poly *a0, const poly *a) {
    unsigned int i;
    int32_t a2tmp = 0, a1tmp = 0;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        decompose(&a2tmp, &a1tmp, &a0->coeffs[i], a->coeffs[i]);

    DBENCH_STOP(*tround);
}

/*************************************************
 * Name:        poly_uniform
 *
 * Description: Sample polynomial with uniformly random coefficients
 *              in [0,Q-1] by performing rejection sampling on the
 *              output stream of SHAKE256(seed|nonce)
 *
 * Arguments:   - poly *a: pointer to output polynomial
 *              - const uint8_t seed[]: byte array with seed of length SEEDBYTES
 *              - uint16_t nonce: 2-byte nonce
 **************************************************/
#define POLY_UNIFORM_NBLOCKS                                                   \
    ((512 + STREAM128_BLOCKBYTES - 1) / STREAM128_BLOCKBYTES)
// N * 2(random bytes for [0, Q - 1])

void poly_uniform(poly *a, const uint8_t seed[SEEDBYTES], uint16_t nonce) {
    unsigned int i, ctr, off;
    unsigned int buflen = POLY_UNIFORM_NBLOCKS * STREAM128_BLOCKBYTES;
    uint8_t buf[POLY_UNIFORM_NBLOCKS * STREAM128_BLOCKBYTES + 1];
    stream128_state state;

    stream128_init(&state, seed, nonce);
    stream128_squeezeblocks(buf, POLY_UNIFORM_NBLOCKS, &state);

    ctr = rej_uniform(a->coeffs, N, buf, buflen);

    while (ctr < N) {
        off = buflen % 2;
        for (i = 0; i < off; ++i)
            buf[i] = buf[buflen - off + i];

        stream128_squeezeblocks(buf + off, 1, &state);
        buflen = STREAM128_BLOCKBYTES + off;
        ctr += rej_uniform(a->coeffs + ctr, N - ctr, buf, buflen);
    }
}

/*************************************************
 * Name:        poly_uniform_eta
 *
 * Description: Sample polynomial with uniformly random coefficients
 *              in [-ETA,ETA] by performing rejection sampling on the
 *              output stream from SHAKE256(seed|nonce)
 *
 * Arguments:   - poly *a: pointer to output polynomial
 *              - const uint8_t seed[]: byte array with seed of length CRHBYTES
 *              - uint16_t nonce: 2-byte nonce
 **************************************************/
#if ETA == 1
#define POLY_UNIFORM_ETA_NBLOCKS                                               \
    ((136 + STREAM256_BLOCKBYTES - 1) / STREAM256_BLOCKBYTES)
#elif ETA == 2
#define POLY_UNIFORM_ETA_NBLOCKS                                               \
    ((136 + STREAM256_BLOCKBYTES - 1) / STREAM256_BLOCKBYTES)
#endif

void poly_uniform_eta(poly *a, const uint8_t seed[CRHBYTES], uint16_t nonce) {
    unsigned int ctr;
    unsigned int buflen = POLY_UNIFORM_ETA_NBLOCKS * STREAM256_BLOCKBYTES;
    uint8_t buf[POLY_UNIFORM_ETA_NBLOCKS * STREAM256_BLOCKBYTES];
    stream256_state state;

    stream256_init(&state, seed, nonce);
    stream256_squeezeblocks(buf, POLY_UNIFORM_ETA_NBLOCKS, &state);

    ctr = rej_eta(a->coeffs, N, buf, buflen);

    while (ctr < N) {
        stream256_squeezeblocks(buf, 1, &state);
        ctr += rej_eta(a->coeffs + ctr, N - ctr, buf, STREAM256_BLOCKBYTES);
    }
}

/*************************************************
 * Name:        poly_challenge
 *
 * Description: Implementation of challenge. Samples polynomial with TAU 1
 *              coefficients using the output stream of SHAKE256(seed).
 *
 * Arguments:   - poly *c: pointer to output polynomial
 *              - const uint8_t seed[]: byte array containing seed of length
 *                SEEDBYTES
 **************************************************/
void poly_challenge(poly *c, const uint8_t seed[SEEDBYTES]) {
    unsigned int i, b, pos = 0;
    uint8_t buf[SHAKE256_RATE];
    keccak_state state;

    shake256_init(&state);
    shake256_absorb(&state, seed, SEEDBYTES);
    shake256_finalize(&state);
    shake256_squeezeblocks(buf, 1, &state);

    for (i = 0; i < N; ++i)
        c->coeffs[i] = 0;
    for (i = N - TAU; i < N; ++i) {
        do {
            if (pos >= SHAKE256_RATE) {
                shake256_squeezeblocks(buf, 1, &state);
                pos = 0;
            }

            b = buf[pos++];
        } while (b > i);

        c->coeffs[i] = c->coeffs[b];
        c->coeffs[b] = 1;
    }
}

/*************************************************
 * Name:        polyq_pack
 *
 * Description: Bit-pack polynomial with coefficients in [0, Q - 1].
 *
 * Arguments:   - uint8_t *r: pointer to output byte array with at least
 *                            POLYQ_PACKEDBYTES bytes
 *              - const poly *a: pointer to input polynomial
 **************************************************/
void polyq_pack(uint8_t *r, const poly *a) {
    unsigned int i;
    DBENCH_START();
    for (i = 0; i < N / 1; ++i) {
        r[2 * i + 0] = a->coeffs[1 * i + 0] >> 0;
        r[2 * i + 1] = a->coeffs[1 * i + 0] >> 8;
    }

    DBENCH_STOP(*tpack);
}

/*************************************************
 * Name:        polyq_unpack
 *
 * Description: Unpack polynomial with coefficients in [0, Q - 1].
 *
 * Arguments:   - poly *r: pointer to output polynomial
 *              - const uint8_t *a: byte array with bit-packed polynomial
 **************************************************/
void polyq_unpack(poly *r, const uint8_t *a) {
    unsigned int i;
    DBENCH_START();
    for (i = 0; i < N / 1; ++i) {
        r->coeffs[1 * i + 0] = a[2 * i + 0] >> 0;
        r->coeffs[1 * i + 0] |= (uint16_t)a[2 * i + 1] << 8;
        r->coeffs[1 * i + 0] &= 0xffff;
    }
    DBENCH_STOP(*tpack);
}

/*************************************************
 * Name:        poly2q_pack
 *
 * Description: Bit-pack polynomial with coefficients in [0, 2Q - 1].
 *
 * Arguments:   - uint8_t *r: pointer to output byte array with at least
 *                            POLY2Q_PACKEDBYTES bytes
 *              - const poly *a: pointer to input polynomial
 **************************************************/
void poly2q_pack(uint8_t *r, const poly *a) {
    unsigned int i;
    DBENCH_START();
    for (i = 0; i < N / 8; ++i) {
        r[17 * i + 0] = a->coeffs[8 * i + 0] >> 0;
        r[17 * i + 1] = a->coeffs[8 * i + 0] >> 8;
        r[17 * i + 2] = a->coeffs[8 * i + 0] >> 16;
        r[17 * i + 2] |= a->coeffs[8 * i + 1] << 1;
        r[17 * i + 3] = a->coeffs[8 * i + 1] >> 7;
        r[17 * i + 4] = a->coeffs[8 * i + 1] >> 15;
        r[17 * i + 4] |= a->coeffs[8 * i + 2] << 2;
        r[17 * i + 5] = a->coeffs[8 * i + 2] >> 6;
        r[17 * i + 6] = a->coeffs[8 * i + 2] >> 14;
        r[17 * i + 6] |= a->coeffs[8 * i + 3] << 3;
        r[17 * i + 7] = a->coeffs[8 * i + 3] >> 5;
        r[17 * i + 8] = a->coeffs[8 * i + 3] >> 13;
        r[17 * i + 8] |= a->coeffs[8 * i + 4] << 4;
        r[17 * i + 9] = a->coeffs[8 * i + 4] >> 4;
        r[17 * i + 10] = a->coeffs[8 * i + 4] >> 12;
        r[17 * i + 10] |= a->coeffs[8 * i + 5] << 5;
        r[17 * i + 11] = a->coeffs[8 * i + 5] >> 3;
        r[17 * i + 12] = a->coeffs[8 * i + 5] >> 11;
        r[17 * i + 12] |= a->coeffs[8 * i + 6] << 6;
        r[17 * i + 13] = a->coeffs[8 * i + 6] >> 2;
        r[17 * i + 14] = a->coeffs[8 * i + 6] >> 10;
        r[17 * i + 14] |= a->coeffs[8 * i + 7] << 7;
        r[17 * i + 15] = a->coeffs[8 * i + 7] >> 1;
        r[17 * i + 16] = a->coeffs[8 * i + 7] >> 9;
    }
    DBENCH_STOP(*tpack);
}

/*************************************************
 * Name:        poly2q_unpack
 *
 * Description: Unpack polynomial with coefficients in [0, 2Q - 1].
 *
 * Arguments:   - poly *r: pointer to output polynomial
 *              - const uint8_t *a: byte array with bit-packed polynomial
 **************************************************/
void poly2q_unpack(poly *r, const uint8_t *a) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N / 8; ++i) {
        r->coeffs[8 * i + 0] = a[17 * i + 0] >> 0;
        r->coeffs[8 * i + 0] |= (uint32_t)a[17 * i + 1] << 8;
        r->coeffs[8 * i + 0] |= (uint32_t)a[17 * i + 2] << 16;
        r->coeffs[8 * i + 0] &= 0x1ffff;

        r->coeffs[8 * i + 1] = a[17 * i + 2] >> 1;
        r->coeffs[8 * i + 1] |= (uint32_t)a[17 * i + 3] << 7;
        r->coeffs[8 * i + 1] |= (uint32_t)a[17 * i + 4] << 15;
        r->coeffs[8 * i + 1] &= 0x1ffff;

        r->coeffs[8 * i + 2] = a[17 * i + 4] >> 2;
        r->coeffs[8 * i + 2] |= (uint32_t)a[17 * i + 5] << 6;
        r->coeffs[8 * i + 2] |= (uint32_t)a[17 * i + 6] << 14;
        r->coeffs[8 * i + 2] &= 0x1ffff;

        r->coeffs[8 * i + 3] = a[17 * i + 6] >> 3;
        r->coeffs[8 * i + 3] |= (uint32_t)a[17 * i + 7] << 5;
        r->coeffs[8 * i + 3] |= (uint32_t)a[17 * i + 8] << 13;
        r->coeffs[8 * i + 3] &= 0x1ffff;

        r->coeffs[8 * i + 4] = a[17 * i + 8] >> 4;
        r->coeffs[8 * i + 4] |= (uint32_t)a[17 * i + 9] << 4;
        r->coeffs[8 * i + 4] |= (uint32_t)a[17 * i + 10] << 12;
        r->coeffs[8 * i + 4] &= 0x1ffff;

        r->coeffs[8 * i + 5] = a[17 * i + 10] >> 5;
        r->coeffs[8 * i + 5] |= (uint32_t)a[17 * i + 11] << 3;
        r->coeffs[8 * i + 5] |= (uint32_t)a[17 * i + 12] << 11;
        r->coeffs[8 * i + 5] &= 0x1ffff;

        r->coeffs[8 * i + 6] = a[17 * i + 12] >> 6;
        r->coeffs[8 * i + 6] |= (uint32_t)a[17 * i + 13] << 2;
        r->coeffs[8 * i + 6] |= (uint32_t)a[17 * i + 14] << 10;
        r->coeffs[8 * i + 6] &= 0x1ffff;

        r->coeffs[8 * i + 7] = a[17 * i + 14] >> 7;
        r->coeffs[8 * i + 7] |= (uint32_t)a[17 * i + 15] << 1;
        r->coeffs[8 * i + 7] |= (uint32_t)a[17 * i + 16] << 9;
        r->coeffs[8 * i + 7] &= 0x1ffff;
    }
    DBENCH_STOP(*tpack);
}

/*************************************************
 * Name:        polyeta_pack
 *
 * Description: Bit-pack polynomial with coefficients in [-ETA,ETA].
 *
 * Arguments:   - uint8_t *r: pointer to output byte array with at least
 *                            POLYETA_PACKEDBYTES bytes
 *              - const poly *a: pointer to input polynomial
 **************************************************/
void polyeta_pack(uint8_t *r, const poly *a) {
    unsigned int i;
    uint8_t t[8];
    DBENCH_START();
#if ETA == 1
    for (i = 0; i < N / 4; ++i) {
        t[0] = ETA - a->coeffs[4 * i + 0];
        t[1] = ETA - a->coeffs[4 * i + 1];
        t[2] = ETA - a->coeffs[4 * i + 2];
        t[3] = ETA - a->coeffs[4 * i + 3];
        r[i] = t[0] >> 0;
        r[i] |= t[1] << 2;
        r[i] |= t[2] << 4;
        r[i] |= t[3] << 6;
    }
#elif ETA == 2
    for (i = 0; i < N / 8; ++i) {
        t[0] = ETA - a->coeffs[8 * i + 0];
        t[1] = ETA - a->coeffs[8 * i + 1];
        t[2] = ETA - a->coeffs[8 * i + 2];
        t[3] = ETA - a->coeffs[8 * i + 3];
        t[4] = ETA - a->coeffs[8 * i + 4];
        t[5] = ETA - a->coeffs[8 * i + 5];
        t[6] = ETA - a->coeffs[8 * i + 6];
        t[7] = ETA - a->coeffs[8 * i + 7];

        r[3 * i + 0] = (t[0] >> 0) | (t[1] << 3) | (t[2] << 6);
        r[3 * i + 1] = (t[2] >> 2) | (t[3] << 1) | (t[4] << 4) | (t[5] << 7);
        r[3 * i + 2] = (t[5] >> 1) | (t[6] << 2) | (t[7] << 5);
    }
#endif

    DBENCH_STOP(*tpack);
}

/*************************************************
 * Name:        polyeta_unpack
 *
 * Description: Unpack polynomial with coefficients in [-ETA,ETA].
 *
 * Arguments:   - poly *r: pointer to output polynomial
 *              - const uint8_t *a: byte array with bit-packed polynomial
 **************************************************/
void polyeta_unpack(poly *r, const uint8_t *a) {
    unsigned int i;
    DBENCH_START();

#if ETA == 1
    for (i = 0; i < N / 4; ++i) {
        r->coeffs[4 * i + 0] = a[i] >> 0;
        r->coeffs[4 * i + 0] &= 0x3;

        r->coeffs[4 * i + 1] = a[i] >> 2;
        r->coeffs[4 * i + 1] &= 0x3;

        r->coeffs[4 * i + 2] = a[i] >> 4;
        r->coeffs[4 * i + 2] &= 0x3;

        r->coeffs[4 * i + 3] = a[i] >> 6;
        r->coeffs[4 * i + 3] &= 0x3;

        r->coeffs[4 * i + 0] = ETA - r->coeffs[4 * i + 0];
        r->coeffs[4 * i + 1] = ETA - r->coeffs[4 * i + 1];
        r->coeffs[4 * i + 2] = ETA - r->coeffs[4 * i + 2];
        r->coeffs[4 * i + 3] = ETA - r->coeffs[4 * i + 3];
    }

#elif ETA == 2
    for (i = 0; i < N / 8; ++i) {
        r->coeffs[8 * i + 0] = (a[3 * i + 0] >> 0) & 7;
        r->coeffs[8 * i + 1] = (a[3 * i + 0] >> 3) & 7;
        r->coeffs[8 * i + 2] = ((a[3 * i + 0] >> 6) | (a[3 * i + 1] << 2)) & 7;
        r->coeffs[8 * i + 3] = (a[3 * i + 1] >> 1) & 7;
        r->coeffs[8 * i + 4] = (a[3 * i + 1] >> 4) & 7;
        r->coeffs[8 * i + 5] = ((a[3 * i + 1] >> 7) | (a[3 * i + 2] << 1)) & 7;
        r->coeffs[8 * i + 6] = (a[3 * i + 2] >> 2) & 7;
        r->coeffs[8 * i + 7] = (a[3 * i + 2] >> 5) & 7;

        r->coeffs[8 * i + 0] = ETA - r->coeffs[8 * i + 0];
        r->coeffs[8 * i + 1] = ETA - r->coeffs[8 * i + 1];
        r->coeffs[8 * i + 2] = ETA - r->coeffs[8 * i + 2];
        r->coeffs[8 * i + 3] = ETA - r->coeffs[8 * i + 3];
        r->coeffs[8 * i + 4] = ETA - r->coeffs[8 * i + 4];
        r->coeffs[8 * i + 5] = ETA - r->coeffs[8 * i + 5];
        r->coeffs[8 * i + 6] = ETA - r->coeffs[8 * i + 6];
        r->coeffs[8 * i + 7] = ETA - r->coeffs[8 * i + 7];
    }
#endif

    DBENCH_STOP(*tpack);
}

/*************************************************
 * Name:        polyB1_pack
 *
 * Description: Bit-pack polynomial with coefficients in [-B1,B1].
 *
 * Arguments:   - uint8_t *r: pointer to output byte array with at least
 *                            POLYB1_PACKEDBYTES bytes
 *              - const poly *a: pointer to input polynomial
 **************************************************/
void polyB1_pack(uint8_t *r, const poly *a) {
    unsigned int i;
    DBENCH_START();
#if HAETAE_MODE == 2
    uint16_t t[8];
    for (i = 0; i < N / 8; ++i) {
        t[0] = 9768 - a->coeffs[8 * i + 0];
        t[1] = 9768 - a->coeffs[8 * i + 1];
        t[2] = 9768 - a->coeffs[8 * i + 2];
        t[3] = 9768 - a->coeffs[8 * i + 3];
        t[4] = 9768 - a->coeffs[8 * i + 4];
        t[5] = 9768 - a->coeffs[8 * i + 5];
        t[6] = 9768 - a->coeffs[8 * i + 6];
        t[7] = 9768 - a->coeffs[8 * i + 7];
        r[15 * i + 0] = t[0] >> 0;
        r[15 * i + 1] = t[0] >> 8;
        r[15 * i + 1] |= t[1] << 7;
        r[15 * i + 2] = t[1] >> 1;
        r[15 * i + 3] = t[1] >> 9;
        r[15 * i + 3] |= t[2] << 6;
        r[15 * i + 4] = t[2] >> 2;
        r[15 * i + 5] = t[2] >> 10;
        r[15 * i + 5] |= t[3] << 5;
        r[15 * i + 6] = t[3] >> 3;
        r[15 * i + 7] = t[3] >> 11;
        r[15 * i + 7] |= t[4] << 4;
        r[15 * i + 8] = t[4] >> 4;
        r[15 * i + 9] = t[4] >> 12;
        r[15 * i + 9] |= t[5] << 3;
        r[15 * i + 10] = t[5] >> 5;
        r[15 * i + 11] = t[5] >> 13;
        r[15 * i + 11] |= t[6] << 2;
        r[15 * i + 12] = t[6] >> 6;
        r[15 * i + 13] = t[6] >> 14;
        r[15 * i + 13] |= t[7] << 1;
        r[15 * i + 14] = t[7] >> 7;
    }

#elif HAETAE_MODE == 3
    uint16_t t[8];
    for (i = 0; i < N / 8; ++i) {
        t[0] = 13989 - a->coeffs[8 * i + 0];
        t[1] = 13989 - a->coeffs[8 * i + 1];
        t[2] = 13989 - a->coeffs[8 * i + 2];
        t[3] = 13989 - a->coeffs[8 * i + 3];
        t[4] = 13989 - a->coeffs[8 * i + 4];
        t[5] = 13989 - a->coeffs[8 * i + 5];
        t[6] = 13989 - a->coeffs[8 * i + 6];
        t[7] = 13989 - a->coeffs[8 * i + 7];
        r[15 * i + 0] = t[0] >> 0;
        r[15 * i + 1] = t[0] >> 8;
        r[15 * i + 1] |= t[1] << 7;
        r[15 * i + 2] = t[1] >> 1;
        r[15 * i + 3] = t[1] >> 9;
        r[15 * i + 3] |= t[2] << 6;
        r[15 * i + 4] = t[2] >> 2;
        r[15 * i + 5] = t[2] >> 10;
        r[15 * i + 5] |= t[3] << 5;
        r[15 * i + 6] = t[3] >> 3;
        r[15 * i + 7] = t[3] >> 11;
        r[15 * i + 7] |= t[4] << 4;
        r[15 * i + 8] = t[4] >> 4;
        r[15 * i + 9] = t[4] >> 12;
        r[15 * i + 9] |= t[5] << 3;
        r[15 * i + 10] = t[5] >> 5;
        r[15 * i + 11] = t[5] >> 13;
        r[15 * i + 11] |= t[6] << 2;
        r[15 * i + 12] = t[6] >> 6;
        r[15 * i + 13] = t[6] >> 14;
        r[15 * i + 13] |= t[7] << 1;
        r[15 * i + 14] = t[7] >> 7;
    }
#elif HAETAE_MODE == 5
    uint16_t t[1];
    for (i = 0; i < N / 1; ++i) {
        t[0] = 20596 - a->coeffs[1 * i + 0];
        r[2 * i + 0] = t[0] >> 0;
        r[2 * i + 1] = t[0] >> 8;
    }
#endif

    DBENCH_STOP(*tpack);
}
/*************************************************
 * Name:        polyB1_unpack
 *
 * Description: Unpack polynomial with coefficients in [-B1,B1].
 *
 * Arguments:   - poly *r: pointer to output polynomial
 *              - const uint8_t *a: byte array with bit-packed polynomial
 **************************************************/
void polyB1_unpack(poly *r, const uint8_t *a) {
    unsigned int i;
    DBENCH_START();
#if HAETAE_MODE == 2
    for (i = 0; i < N / 8; ++i) {
        r->coeffs[8 * i + 0] = a[15 * i + 0] >> 0;
        r->coeffs[8 * i + 0] |= (uint16_t)a[15 * i + 1] << 8;
        r->coeffs[8 * i + 0] &= 0x7fff;

        r->coeffs[8 * i + 1] = a[15 * i + 1] >> 7;
        r->coeffs[8 * i + 1] |= (uint16_t)a[15 * i + 2] << 1;
        r->coeffs[8 * i + 1] |= (uint16_t)a[15 * i + 3] << 9;
        r->coeffs[8 * i + 1] &= 0x7fff;

        r->coeffs[8 * i + 2] = a[15 * i + 3] >> 6;
        r->coeffs[8 * i + 2] |= (uint16_t)a[15 * i + 4] << 2;
        r->coeffs[8 * i + 2] |= (uint16_t)a[15 * i + 5] << 10;
        r->coeffs[8 * i + 2] &= 0x7fff;

        r->coeffs[8 * i + 3] = a[15 * i + 5] >> 5;
        r->coeffs[8 * i + 3] |= (uint16_t)a[15 * i + 6] << 3;
        r->coeffs[8 * i + 3] |= (uint16_t)a[15 * i + 7] << 11;
        r->coeffs[8 * i + 3] &= 0x7fff;

        r->coeffs[8 * i + 4] = a[15 * i + 7] >> 4;
        r->coeffs[8 * i + 4] |= (uint16_t)a[15 * i + 8] << 4;
        r->coeffs[8 * i + 4] |= (uint16_t)a[15 * i + 9] << 12;
        r->coeffs[8 * i + 4] &= 0x7fff;

        r->coeffs[8 * i + 5] = a[15 * i + 9] >> 3;
        r->coeffs[8 * i + 5] |= (uint16_t)a[15 * i + 10] << 5;
        r->coeffs[8 * i + 5] |= (uint16_t)a[15 * i + 11] << 13;
        r->coeffs[8 * i + 5] &= 0x7fff;

        r->coeffs[8 * i + 6] = a[15 * i + 11] >> 2;
        r->coeffs[8 * i + 6] |= (uint16_t)a[15 * i + 12] << 6;
        r->coeffs[8 * i + 6] |= (uint16_t)a[15 * i + 13] << 14;
        r->coeffs[8 * i + 6] &= 0x7fff;

        r->coeffs[8 * i + 7] = a[15 * i + 13] >> 1;
        r->coeffs[8 * i + 7] |= (uint16_t)a[15 * i + 14] << 7;
        r->coeffs[8 * i + 7] &= 0x7fff;

        r->coeffs[8 * i + 0] = 9768 - r->coeffs[8 * i + 0];
        r->coeffs[8 * i + 1] = 9768 - r->coeffs[8 * i + 1];
        r->coeffs[8 * i + 2] = 9768 - r->coeffs[8 * i + 2];
        r->coeffs[8 * i + 3] = 9768 - r->coeffs[8 * i + 3];
        r->coeffs[8 * i + 4] = 9768 - r->coeffs[8 * i + 4];
        r->coeffs[8 * i + 5] = 9768 - r->coeffs[8 * i + 5];
        r->coeffs[8 * i + 6] = 9768 - r->coeffs[8 * i + 6];
        r->coeffs[8 * i + 7] = 9768 - r->coeffs[8 * i + 7];
    }
#elif HAETAE_MODE == 3
    for (i = 0; i < N / 8; ++i) {
        r->coeffs[8 * i + 0] = a[15 * i + 0] >> 0;
        r->coeffs[8 * i + 0] |= (uint16_t)a[15 * i + 1] << 8;
        r->coeffs[8 * i + 0] &= 0x7fff;

        r->coeffs[8 * i + 1] = a[15 * i + 1] >> 7;
        r->coeffs[8 * i + 1] |= (uint16_t)a[15 * i + 2] << 1;
        r->coeffs[8 * i + 1] |= (uint16_t)a[15 * i + 3] << 9;
        r->coeffs[8 * i + 1] &= 0x7fff;

        r->coeffs[8 * i + 2] = a[15 * i + 3] >> 6;
        r->coeffs[8 * i + 2] |= (uint16_t)a[15 * i + 4] << 2;
        r->coeffs[8 * i + 2] |= (uint16_t)a[15 * i + 5] << 10;
        r->coeffs[8 * i + 2] &= 0x7fff;

        r->coeffs[8 * i + 3] = a[15 * i + 5] >> 5;
        r->coeffs[8 * i + 3] |= (uint16_t)a[15 * i + 6] << 3;
        r->coeffs[8 * i + 3] |= (uint16_t)a[15 * i + 7] << 11;
        r->coeffs[8 * i + 3] &= 0x7fff;

        r->coeffs[8 * i + 4] = a[15 * i + 7] >> 4;
        r->coeffs[8 * i + 4] |= (uint16_t)a[15 * i + 8] << 4;
        r->coeffs[8 * i + 4] |= (uint16_t)a[15 * i + 9] << 12;
        r->coeffs[8 * i + 4] &= 0x7fff;

        r->coeffs[8 * i + 5] = a[15 * i + 9] >> 3;
        r->coeffs[8 * i + 5] |= (uint16_t)a[15 * i + 10] << 5;
        r->coeffs[8 * i + 5] |= (uint16_t)a[15 * i + 11] << 13;
        r->coeffs[8 * i + 5] &= 0x7fff;

        r->coeffs[8 * i + 6] = a[15 * i + 11] >> 2;
        r->coeffs[8 * i + 6] |= (uint16_t)a[15 * i + 12] << 6;
        r->coeffs[8 * i + 6] |= (uint16_t)a[15 * i + 13] << 14;
        r->coeffs[8 * i + 6] &= 0x7fff;

        r->coeffs[8 * i + 7] = a[15 * i + 13] >> 1;
        r->coeffs[8 * i + 7] |= (uint16_t)a[15 * i + 14] << 7;
        r->coeffs[8 * i + 7] &= 0x7fff;

        r->coeffs[8 * i + 0] = 13989 - r->coeffs[8 * i + 0];
        r->coeffs[8 * i + 1] = 13989 - r->coeffs[8 * i + 1];
        r->coeffs[8 * i + 2] = 13989 - r->coeffs[8 * i + 2];
        r->coeffs[8 * i + 3] = 13989 - r->coeffs[8 * i + 3];
        r->coeffs[8 * i + 4] = 13989 - r->coeffs[8 * i + 4];
        r->coeffs[8 * i + 5] = 13989 - r->coeffs[8 * i + 5];
        r->coeffs[8 * i + 6] = 13989 - r->coeffs[8 * i + 6];
        r->coeffs[8 * i + 7] = 13989 - r->coeffs[8 * i + 7];
    }
#elif HAETAE_MODE == 5
    for (i = 0; i < N / 1; ++i) {
        r->coeffs[1 * i + 0] = a[2 * i + 0] >> 0;
        r->coeffs[1 * i + 0] |= (uint16_t)a[2 * i + 1] << 8;
        r->coeffs[1 * i + 0] &= 0xffff;

        r->coeffs[1 * i + 0] = 20596 - r->coeffs[1 * i + 0];
    }

#endif

    DBENCH_STOP(*tpack);
}

void poly_rot(poly *out, const poly *in, const int rot_idx) {
    for (int k = 0; k < rot_idx; ++k)
        out->coeffs[k] = in->coeffs[N + k - rot_idx];

    for (int k = rot_idx; k < N; ++k)
        out->coeffs[k] = in->coeffs[k - rot_idx];
}