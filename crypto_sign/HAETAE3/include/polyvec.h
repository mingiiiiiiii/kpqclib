// clang-format off
#ifndef HAETAE_POLYVEC_H
#define HAETAE_POLYVEC_H

#include "params.h"
#include "poly.h"
#include <stdint.h>

/* Vectors of polynomials of length K */
typedef struct {
    poly vec[K];
} polyveck;

#define polyveck_add HAETAE_NAMESPACE(polyveck_add)
void polyveck_add(polyveck *w, const polyveck *u, const polyveck *v);
#define polyveck_sub HAETAE_NAMESPACE(polyveck_sub)
void polyveck_sub(polyveck *w, const polyveck *u, const polyveck *v);
#define polyveck_double HAETAE_NAMESPACE(polyveck_double)
void polyveck_double(polyveck *b);

#define polyveck_reduce HAETAE_NAMESPACE(polyveck_reduce)
void polyveck_reduce(polyveck *v);
#define polyveck_reduce2q HAETAE_NAMESPACE(polyveck_reduce2q)
void polyveck_reduce2q(polyveck *v);
#define polyveck_freeze2q HAETAE_NAMESPACE(polyveck_freeze2q)
void polyveck_freeze2q(polyveck *v);

#define polyveck_uniform_eta HAETAE_NAMESPACE(polyveck_uniform_eta)
void polyveck_uniform_eta(polyveck *v, const uint8_t seed[CRHBYTES], uint16_t nonce);

#define polyveck_highbits HAETAE_NAMESPACE(polyveck_highbits)
void polyveck_highbits(polyveck *v2, const polyveck *v);
#define polyveck_lowbits HAETAE_NAMESPACE(polyveck_lowbits)
void polyveck_lowbits(polyveck *v2, const polyveck *v);
#define polyveck_lsb HAETAE_NAMESPACE(polyveck_lsb)
void polyveck_lsb(polyveck *v2, const polyveck *v);

#define polyveck_rot HAETAE_NAMESPACE(polyveck_rot)
void polyveck_rot(polyveck *out, const polyveck *in, const int rot_idx);

/* Vectors of polynomials of length L */
typedef struct {
    poly vec[L];
} polyvecl;

#define polyvecl_uniform_eta HAETAE_NAMESPACE(polyvecl_uniform_eta)
void polyvecl_uniform_eta(polyvecl *v, const uint8_t seed[CRHBYTES], uint16_t nonce);

/* Operations of polynomials of length L and L or L and K */
#define polyvecll_naivemul_acc HAETAE_NAMESPACE(polyvecll_naivemul_acc)
void polyvecll_naivemul_acc(poly *w, const polyvecl *u, const polyvecl *v);

#define polyveclk_norm2 HAETAE_NAMESPACE(polyveclk_norm2)
double polyveclk_norm2(const polyvecl *a, const polyveck *b);

#define polyvecl_rot HAETAE_NAMESPACE(polyvecl_rot)
void polyvecl_rot(polyvecl *out, const polyvecl *in, const int rot_idx);

#endif
//clang-format on
