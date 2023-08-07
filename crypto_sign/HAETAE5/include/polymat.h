#ifndef HAETAE_POLYMAT_H
#define HAETAE_POLYMAT_H

#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include <stdint.h>

#define polymat_expand HAETAE_NAMESPACE(polymat_expand)
void polymat_expand(polyvecl mat[K], const uint8_t rho[SEEDBYTES]);

#define polymatkl_double HAETAE_NAMESPACE(polymatkl_double)
void polymatkl_double(polyvecl mat[K]);

#define polymatkll_naivemul HAETAE_NAMESPACE(polymatkll_naivemul)
void polymatkll_naivemul(polyveck *t, const polyvecl mat[K], const polyvecl *v);

#endif