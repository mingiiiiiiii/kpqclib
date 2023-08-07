#include "polymat.h"
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include <stdint.h>

/*************************************************
 * Name:        polymat_expand
 *
 * Description: Implementation of ExpandA. Generates matrix A with uniformly
 *              random coefficients a_{i,j} by performing rejection
 *              sampling on the output stream of SHAKE128(rho|j|i)
 *              or AES256CTR(rho,j|i).
 *
 * Arguments:   - polyvecl mat[K]: output matrix k \times (m - 1)
 *              - const uint8_t rho[]: byte array containing seed rho
 **************************************************/
void polymat_expand(polyvecl mat[K], const uint8_t rho[SEEDBYTES]) {
    unsigned int i, j;

    for (i = 0; i < K; ++i)
        for (j = 1; j < L; ++j)
            poly_uniform(&mat[i].vec[j], rho, (i << 8) + j);

    for (i = 0; i < K; ++i)
        for (j = 1; j < N; ++j)
            mat[i].vec[0].coeffs[j] = 0;
}

// doubles k * (l - 1) matrix mat
void polymatkl_double(polyvecl mat[K]) {
    unsigned int i, j, k;
    for (i = 0; i < K; ++i)
        for (j = 1; j < L; ++j)
            for (k = 0; k < N; ++k)
                mat[i].vec[j].coeffs[k] *= 2;
}

void polymatkll_naivemul(polyveck *t, const polyvecl mat[K],
                         const polyvecl *v) {
    unsigned int i;

    for (i = 0; i < K; ++i) {
        polyvecll_naivemul_acc(&t->vec[i], &mat[i], v);
    }
}