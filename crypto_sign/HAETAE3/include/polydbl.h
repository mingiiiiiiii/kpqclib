// clang-format off
#ifndef HAETAE_POLYDBL_H
#define HAETAE_POLYDBL_H

#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "reduce.h"
#include <stdint.h>

typedef struct {
    double coeffs[N];
} polydbl;

#define polydbl_norm2 HAETAE_NAMESPACE(polydbl_norm2)
double polydbl_norm2(const polydbl *a);

#define polydbl_round HAETAE_NAMESPACE(polydbl_round)
void polydbl_round(poly *a, const polydbl *b);

#define polydbl_add HAETAE_NAMESPACE(polydbl_add)
void polydbl_add(polydbl *c, const polydbl *a, const poly *b);

#define polydbl_sub HAETAE_NAMESPACE(polydbl_sub)
void polydbl_sub(polydbl *c, const polydbl *a, const poly *b);

typedef struct {
    polydbl vec[K];
} polydblveck;

#define polydblveck_add HAETAE_NAMESPACE(polydblveck_add)
void polydblveck_add(polydblveck *w, const polydblveck *u, const polyveck *v);
#define polydblveck_sub HAETAE_NAMESPACE(polydblveck_sub)
void polydblveck_sub(polydblveck *w, const polydblveck *u, const polyveck *v);
#define polydbldblveck_sub HAETAE_NAMESPACE(polydbldblveck_sub)
void polydbldblveck_sub(polydblveck *w, const polydblveck *u, const polydblveck *v);
#define polydblveck_dobule HAETAE_NAMESPACE(polydblveck_double)
void polydblveck_double(polydblveck *b, const polydblveck *a);

#define polydblveck_round HAETAE_NAMESPACE(polydblveck_round)
void polydblveck_round(polyveck *a, const polydblveck *b);

typedef struct {
    polydbl vec[L];
} polydblvecl;

#define polydblvecl_add HAETAE_NAMESPACE(polydblvecl_add)
void polydblvecl_add(polydblvecl *w, const polydblvecl *u, const polyvecl *v);
#define polydblvecl_sub HAETAE_NAMESPACE(polydblvecl_sub)
void polydblvecl_sub(polydblvecl *w, const polydblvecl *u, const polyvecl *v);
#define polydbldblvecl_sub HAETAE_NAMESPACE(polydbldblvecl_sub)
void polydbldblvecl_sub(polydblvecl *w, const polydblvecl *u, const polydblvecl *v);
#define polydblvecl_dobule HAETAE_NAMESPACE(polydblvecl_double)
void polydblvecl_double(polydblvecl *b, const polydblvecl *a);

#define polydblvecl_round HAETAE_NAMESPACE(polydblvecl_round)
void polydblvecl_round(polyvecl *a, const polydblvecl *b);

#define polydblveclk_uniform_hyperball HAETAE_NAMESPACE(polydblveclk_uniform_hyperball)
void polydblveclk_uniform_hyperball(polydblvecl *a, polydblveck *b, const uint8_t seed[SEEDBYTES], uint16_t nonce);

#define polydblveclk_norm2 HAETAE_NAMESPACE(polydblveclk_norm2)
double polydblveclk_norm2(const polydblvecl *a, const polydblveck *b);

#endif
// clang-format on