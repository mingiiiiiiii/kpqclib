#ifndef HAETAE_SAMPLER_H
#define HAETAE_SAMPLER_H

#include "params.h"
#include "reduce.h"
#include <math.h>
#include <stdint.h>

#define rej_uniform HAETAE_NAMESPACE(rej_uniform)
unsigned int rej_uniform(int32_t *a, unsigned int len, const uint8_t *buf,
                         unsigned int buflen);
#define rej_eta HAETAE_NAMESPACE(rej_eta)
unsigned int rej_eta(int32_t *a, unsigned int len, const uint8_t *buf,
                     unsigned int buflen);

#define sampler_gaussian HAETAE_NAMESPACE(sampler_gaussian)
unsigned int sampler_gaussian(double *a, unsigned int len, const uint8_t *buf,
                              unsigned int buflen);

#endif