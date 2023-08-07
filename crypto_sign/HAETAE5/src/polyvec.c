#include "polyvec.h"
#include "params.h"
#include "poly.h"
#include <stdint.h>

/**************************************************************/
/************ Vectors of polynomials of length K **************/
/**************************************************************/

/*************************************************
 * Name:        polyveck_add
 *
 * Description: Add vectors of polynomials of length K.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyveck *w: pointer to output vector
 *              - const polyveck *u: pointer to first summand
 *              - const polyveck *v: pointer to second summand
 **************************************************/
void polyveck_add(polyveck *w, const polyveck *u, const polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        poly_add(&w->vec[i], &u->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polyveck_sub
 *
 * Description: Subtract vectors of polynomials of length K.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyveck *w: pointer to output vector
 *              - const polyveck *u: pointer to first input vector
 *              - const polyveck *v: pointer to second input vector to be
 *                                   subtracted from first input vector
 **************************************************/
void polyveck_sub(polyveck *w, const polyveck *u, const polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        poly_sub(&w->vec[i], &u->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polyveck_double
 *
 * Description: Double vector of polynomials of length K.
 *              No modular reduction is performed.
 *
 * Arguments:   - polyveck *w: pointer to output vector
 **************************************************/
void polyveck_double(polyveck *b) {
    unsigned int i, j;

    for (i = 0; i < K; ++i)
        for (j = 0; j < N; ++j)
            b->vec[i].coeffs[j] *= 2;
}

/*************************************************
 * Name:        polyveck_reduce
 *
 * Description: Reduce coefficients of polynomials in vector of length K
 *              to representatives in [-6283009,6283007].
 *
 * Arguments:   - polyveck *v: pointer to input/output vector
 **************************************************/
void polyveck_reduce(polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        poly_reduce(&v->vec[i]);
}

/*************************************************
 * Name:        polyveck_reduce2q
 *
 * Description: Reduce coefficients to 2q
 *
 * Arguments:   - polyveck *v: pointer to input/output vector
 **************************************************/
void polyveck_reduce2q(polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        poly_reduce2q(&v->vec[i]);
}

/*************************************************
 * Name:        polyveck_freeze2q
 *
 * Description: For all coefficients of polynomials in vector of length K
 *              compute standard representative r = a mod^+ 2Q.
 *
 * Arguments:   - polyveck *v: pointer to input/output vector
 **************************************************/
void polyveck_freeze2q(polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        poly_freeze2q(&v->vec[i]);
}

/*************************************************
 * Name:        polyveck_uniform_eta
 *
 * Description: Sample a vector of polynomials with uniformly random
 *              coefficients in [-ETA,ETA] by rejection sampling on the
 *              output stream from SHAKE256(seed|nonce)
 *
 * Arguments:   - polyveck *v: pointer to output a vector of polynomials of
 *                             length K
 *              - const uint8_t seed[]: byte array with seed of length CRHBYTES
 *              - uint16_t nonce: 2-byte nonce
 **************************************************/
void polyveck_uniform_eta(polyveck *v, const uint8_t seed[CRHBYTES],
                          uint16_t nonce) {
    unsigned int i;
    for (i = 0; i < K; ++i)
        poly_uniform_eta(&v->vec[i], seed, nonce++);
}

/*************************************************
 * Name:        polyveck_highbits
 *
 * Description: Compute HighBits of a vector of polynomials
 *
 * Arguments:   - polyveck *v2: pointer to output vector of polynomials of
 *                              length K
 *              - const polyveck *v: pointer to input vector of polynomials of
 *                                   length K
 **************************************************/
void polyveck_highbits(polyveck *v2, const polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        poly_highbits(&v2->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polyveck_lowbits
 *
 * Description: Compute LowBits of a vector of polynomials
 *
 * Arguments:   - polyveck *v1: pointer to output vector of polynomials of
 *                              length K
 *              - const polyveck *v: pointer to input vector of polynomials of
 *                                   length K
 **************************************************/
void polyveck_lowbits(polyveck *v1, const polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        poly_lowbits(&v1->vec[i], &v->vec[i]);
}

/*************************************************
 * Name:        polyveck_lsb
 *
 * Description: Compute least significant bit of a vector of polynomials
 *
 * Arguments:   - polyveck *v0: pointer to output vector of polynomials of
 *                              length K
 *              - const polyveck *v: pointer to input vector of polynomials of
 *                                   length K
 **************************************************/
void polyveck_lsb(polyveck *v0, const polyveck *v) {
    unsigned int i;

    for (i = 0; i < K; ++i)
        poly_lsb(&v0->vec[i], &v->vec[i]);
}

void polyveck_rot(polyveck *out, const polyveck *in, const int rot_idx) {
    for (int i = 0; i < K; ++i)
        poly_rot(&(out->vec[i]), &(in->vec[i]), rot_idx);
}

/************ Vectors of polynomials of length L **************/

/*************************************************
 * Name:        polyvecl_uniform_eta
 *
 * Description: Sample a vector of polynomials with uniformly random
 *              coefficients in [-ETA,ETA] by rejection sampling on the
 *              output stream from SHAKE256(seed|nonce)
 *
 * Arguments:   - polyveck *v: pointer to output a vector of polynomials of
 *                             length L
 *              - const uint8_t seed[]: byte array with seed of length CRHBYTES
 *              - uint16_t nonce: 2-byte nonce
 **************************************************/
void polyvecl_uniform_eta(polyvecl *v, const uint8_t seed[CRHBYTES],
                          uint16_t nonce) {
    unsigned int i;
    for (i = 1; i < L; ++i)
        poly_uniform_eta(&v->vec[i], seed, nonce++);

    for (i = 0; i < N; ++i)
        v->vec[0].coeffs[i] = 0;
}

/***** Operations of polynomials of length L and L or L and K *****/

/*************************************************
 * Name:        polyvecll_naivemul_acc
 *
 * Description: Naively multiply vectors of polynomials of length L - 1,
 *              and add (accumulate) polynomials in it.
 *
 * Arguments:   - poly *w: output polynomial
 *              - const polyvecl *u: pointer to first input vector
 *              - const polyvecl *v: pointer to second input vector
 **************************************************/
void polyvecll_naivemul_acc(poly *w, const polyvecl *u, const polyvecl *v) {
    unsigned int i;
    poly t;

    poly_naivemul(w, &u->vec[0], &v->vec[0]);
    for (i = 1; i < L; ++i) {
        poly_naivemul(&t, &u->vec[i], &v->vec[i]);
        poly_add(w, w, &t);
    }
}

/*************************************************
 * Name:        polyveclk_norm2
 *
 * Description: Calculates L2 norm of a polynomial vector with length m
 *
 * Arguments:   - polyveclk *a: polynomial vector with length m to calculate
 *norm
 **************************************************/
double polyveclk_norm2(const polyvecl *a, const polyveck *b) {
    unsigned int i, j;
    double ret = 0.0;

    for (i = 0; i < L; ++i) {
        for (j = 0; j < N; ++j) {
            ret += (double)a->vec[i].coeffs[j] * a->vec[i].coeffs[j];
        }
    }

    for (i = 0; i < K; ++i) {
        for (j = 0; j < N; ++j) {
            ret += (double)b->vec[i].coeffs[j] * b->vec[i].coeffs[j];
        }
    }
    return sqrt(ret);
}

void polyvecl_rot(polyvecl *out, const polyvecl *in, const int rot_idx) {
    for (int i = 0; i < L; ++i)
        poly_rot(&out->vec[i], &in->vec[i], rot_idx);
}