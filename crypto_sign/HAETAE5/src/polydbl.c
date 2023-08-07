#include "polydbl.h"
#include "math.h"
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
 * Name:        polydbl_norm2
 *
 * Description: Calculates L2 norm of a double polynomial
 *
 * Arguments:   - polydbl *a: polynomial to calculate norm
 **************************************************/
double polydbl_norm2(const polydbl *a) {
    double ret = 0.0;
    unsigned i;
    DBENCH_START();
    for (i = 0; i < N; ++i) {
        ret += a->coeffs[i] * a->coeffs[i];
    }
    DBENCH_STOP(*tsample);
    return sqrt(ret);
}

/*************************************************
 * Name:        polydbl_round
 *
 * Description: rounds a double polynomial to integer polynomial
 *
 * Arguments:   - poly *a: output integer polynomial
 *              - poly *b: input double polynomial
 **************************************************/
void polydbl_round(poly *a, const polydbl *b) {
    unsigned i;
    DBENCH_START();
    for (i = 0; i < N; ++i) {
        a->coeffs[i] = round(b->coeffs[i]);
    }
    DBENCH_STOP(*tround);
}

/*************************************************
 * Name:        polydbl_add
 *
 * Description: Add double polynomial and integer polynomial.
 *              No modular reduction is performed.
 *
 * Arguments:   - polydbl *c: pointer to output double polynomial
 *              - const polydbl *a: pointer to first summand
 *              - const poly *b: pointer to second summand
 **************************************************/
void polydbl_add(polydbl *c, const polydbl *a, const poly *b) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        c->coeffs[i] = a->coeffs[i] + b->coeffs[i];

    DBENCH_STOP(*tadd);
}

/*************************************************
 * Name:        polydbl_sub
 *
 * Description: Subtract double polynomial and integer polynomial.
 *              No modular reduction is performed.
 *
 * Arguments:   - polydbl *c: pointer to output double polynomial
 *              - const polydbl *a: pointer to first summand
 *              - const poly *b: pointer to second summand
 **************************************************/
void polydbl_sub(polydbl *c, const polydbl *a, const poly *b) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        c->coeffs[i] = a->coeffs[i] - b->coeffs[i];

    DBENCH_STOP(*tadd);
}

/*************************************************
 * Name:        polydbldbl_sub
 *
 * Description: Subtract double polynomial and integer polynomial.
 *              No modular reduction is performed.
 *
 * Arguments:   - polydbl *c: pointer to output double polynomial
 *              - const polydbl *a: pointer to first summand
 *              - const polydbl *b: pointer to second summand
 **************************************************/
void polydbldbl_sub(polydbl *c, const polydbl *a, const polydbl *b) {
    unsigned int i;
    DBENCH_START();

    for (i = 0; i < N; ++i)
        c->coeffs[i] = a->coeffs[i] - b->coeffs[i];

    DBENCH_STOP(*tadd);
}

/*************************************************
 * Name:        polydblveclk_uniform_hyperball
 *
 * Description: samples a double polynomial from uniform hyperball with
 *              radius B
 *              by using gaussian sampling on N(k + l) + 2 dimension
 *
 * Arguments:   - polydblvecl *a: output double polynomial vector with length
 *                                L
 *              - polydblveck *b: output double polynomial vector with length
 *                                K
 *              - const uint8_t seed[]: byte array with seed of length
 *                                      SEEDBYTES
 *              - uint16_t nonce: 2-byte nonce
 **************************************************/
#define POLYDBL_UNIFORM_HYPERBALL_NBLOCKS                                      \
    ((7690 + STREAM128_BLOCKBYTES - 1) / STREAM128_BLOCKBYTES)
void polydblveclk_uniform_hyperball(polydblvecl *a, polydblveck *b,
                                    const uint8_t seed[SEEDBYTES],
                                    uint16_t nonce) {
    unsigned int i, j, ctr;
    unsigned int buflen =
        POLYDBL_UNIFORM_HYPERBALL_NBLOCKS * STREAM128_BLOCKBYTES;
    uint8_t buf[POLYDBL_UNIFORM_HYPERBALL_NBLOCKS * STREAM128_BLOCKBYTES];
    stream128_state state;
    double y[N * (K + L) + 2];
    double l2norm = 0.0;

    stream128_init(&state, seed, nonce);
    stream128_squeezeblocks(buf, POLYDBL_UNIFORM_HYPERBALL_NBLOCKS, &state);

    ctr = sampler_gaussian(y, N * (K + L) + 2, buf, buflen);

    while (ctr < N * (K + L) + 2) { // TODO: use off as in dilithium
        stream128_squeezeblocks(buf, 1, &state);
        buflen = STREAM256_BLOCKBYTES;
        ctr += sampler_gaussian(y + ctr, N * (K + L) + 2 - ctr, buf, buflen);
    }
    for (i = 0; i < N * (K + L) + 2; ++i)
        l2norm += y[i] * y[i];

    l2norm = sqrt(l2norm);
    for (i = 0; i < L; ++i) {
        for (j = 0; j < N; ++j) {
            a->vec[i].coeffs[j] = y[i * N + j] / l2norm * B0;
        }
    }

    for (i = 0; i < K; ++i) {
        for (j = 0; j < N; ++j) {
            b->vec[i].coeffs[j] = y[N * L + i * N + j] / l2norm * B0;
        }
    }
}

/**************************************************************/
/********* Double Vectors of polynomials of length K **********/
/**************************************************************/

/*************************************************
 * Name:        polydblveck_add
 *
 * Description: Add vector to a vector of double polynomials of length K.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyveck *w: pointer to output vector
 *              - const polyveck *u: pointer to first summand
 *              - const polyveck *v: pointer to second summand
 **************************************************/
void polydblveck_add(polydblveck *w, const polydblveck *u, const polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        polydbl_add(&w->vec[i], &u->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polydblveck_sub
 *
 * Description: subtract vector to a vector of double polynomials of length k.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyveck *w: pointer to output vector
 *              - const polydblveck *u: pointer to first summand
 *              - const polyveck *v: pointer to second summand
 **************************************************/
void polydblveck_sub(polydblveck *w, const polydblveck *u, const polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        polydbl_sub(&w->vec[i], &u->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polydbldblveck_sub
 *
 * Description: subtract vector to a vector of double polynomials of length k.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyveck *w: pointer to output vector
 *              - const polydblveck *u: pointer to first summand
 *              - const polydblveck *v: pointer to second summand
 **************************************************/
void polydbldblveck_sub(polydblveck *w, const polydblveck *u,
                        const polydblveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        polydbldbl_sub(&w->vec[i], &u->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polydblveck_double
 *
 * Description: Double vector of polynomials of length K.
 *
 * Arguments:   - polyveck *b: pointer to output vector
 *              - polyveck *a: pointer to input vector
 **************************************************/
void polydblveck_double(polydblveck *b, const polydblveck *a) {
    unsigned int i, j;

    for (i = 0; i < K; ++i)
        for (j = 0; j < N; ++j)
            b->vec[i].coeffs[j] = 2 * a->vec[i].coeffs[j];
}

/*************************************************
 * Name:        polydblveck_round
 *
 * Description: rounds a double polynomial vector of length K
 *
 * Arguments:   - polyveck *a: output integer polynomial vector
 *              - polydblveck *b: input double polynomial vector
 **************************************************/
void polydblveck_round(polyveck *a, const polydblveck *b) {
    unsigned i;
    DBENCH_START();
    for (i = 0; i < K; ++i) {
        polydbl_round(&a->vec[i], &b->vec[i]);
    }
    DBENCH_STOP(*tround);
}

/**************************************************************/
/********* Double Vectors of polynomials of length L **********/
/**************************************************************/

/*************************************************
 * Name:        polydblvecl_add
 *
 * Description: Add vector to a vector of double polynomials of length L.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyvecl *w: pointer to output vector
 *              - const polydblvecl *u: pointer to first summand
 *              - const polyvecl *v: pointer to second summand
 **************************************************/
void polydblvecl_add(polydblvecl *w, const polydblvecl *u, const polyvecl *v) {
    unsigned int i;

    for (i = 0; i < L; ++i)
        polydbl_add(&w->vec[i], &u->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polydblvecl_sub
 *
 * Description: subtract vector to a vector of double polynomials of length L.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyvecl *w: pointer to output vector
 *              - const polyvecl *u: pointer to first summand
 *              - const polyvecl *v: pointer to second summand
 **************************************************/
void polydblvecl_sub(polydblvecl *w, const polydblvecl *u, const polyvecl *v) {
    unsigned int i;

    for (i = 0; i < L; ++i)
        polydbl_sub(&w->vec[i], &u->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polydbldblvecl_sub
 *
 * Description: subtract vector to a vector of double polynomials of length L.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyvecl *w: pointer to output vector
 *              - const polydblvecl *u: pointer to first summand
 *              - const polydblvecl *v: pointer to second summand
 **************************************************/
void polydbldblvecl_sub(polydblvecl *w, const polydblvecl *u,
                        const polydblvecl *v) {
    unsigned int i;

    for (i = 0; i < L; ++i)
        polydbldbl_sub(&w->vec[i], &u->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polydblvecl_double
 *
 * Description: Double vector of polynomials of length L.
 *
 * Arguments:   - polyveck *b: pointer to output vector
 *              - polyveck *a: pointer to input vector
 **************************************************/
void polydblvecl_double(polydblvecl *b, const polydblvecl *a) {
    unsigned int i, j;

    for (i = 0; i < L; ++i)
        for (j = 0; j < N; ++j)
            b->vec[i].coeffs[j] = 2 * a->vec[i].coeffs[j];
}

/*************************************************
 * Name:        polydblvecl_round
 *
 * Description: rounds a double polynomial vector of length L
 *
 * Arguments:   - polyvecl *a: output integer polynomial vector
 *              - polydblvecl *b: input double polynomial vector
 **************************************************/
void polydblvecl_round(polyvecl *a, const polydblvecl *b) {
    unsigned i;
    DBENCH_START();
    for (i = 0; i < L; ++i) {
        polydbl_round(&a->vec[i], &b->vec[i]);
    }
    DBENCH_STOP(*tround);
}

/*************************************************
 * Name:        polydblvecl_norm2
 *
 * Description: Calculates L2 norm of a double polynomial vector with length L
 *
 * Arguments:   - polydblvecl *a: polynomial vector with length M to calculate
 *                norm
 **************************************************/
double polydblveclk_norm2(const polydblvecl *a, const polydblveck *b) {
    unsigned int i, j;
    double ret = 0.0;
    DBENCH_START();
    for (i = 0; i < L; ++i) {
        for (j = 0; j < N; ++j) {
            ret += a->vec[i].coeffs[j] * a->vec[i].coeffs[j];
        }
    }

    for (i = 0; i < K; ++i) {
        for (j = 0; j < N; ++j) {
            ret += b->vec[i].coeffs[j] * b->vec[i].coeffs[j];
        }
    }
    DBENCH_STOP(*tsample);
    return sqrt(ret);
}
