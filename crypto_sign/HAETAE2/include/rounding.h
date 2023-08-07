#ifndef HAETAE_ROUNDING_H
#define HAETAE_ROUNDING_H

#include "params.h"
#include <stdint.h>

#define decompose HAETAE_NAMESPACE(decompose)
void decompose(int32_t *r2, int32_t *r1, int32_t *r0, const int32_t r);

#endif
