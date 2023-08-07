#include "rounding.h"
#include "params.h"
#include <stdint.h>

/*************************************************
 * Name:        decompose
 *
 * Description: For finite field element r, compute high, low, and least
 *              significant bits r2, r1, r0 such that r = r2 * ALPHA + r1 * 2 +
 *              r_0 with -ALPHA/4 < r1 <= ALPHA/4.
 *
 * Arguments:   - int32_t r: input element
 *              - int32_t *r2: pointer to output element r2
 *              - int32_t *r1: pointer to output element r1
 *              - int32_t *r0: pointer to output element r0
 *
 * Returns a1.
 **************************************************/
void decompose(int32_t *r2, int32_t *r1, int32_t *r0, const int32_t r) {
    int32_t newr = (r % DQ + DQ) % DQ;
    int32_t rprime = newr % ALPHA;
    if (rprime >= HALF_ALPHA)
        rprime -= ALPHA;

    *r0 = newr & 0x1;
    *r1 = (rprime - *r0) / 2;
    *r2 = (newr + HALF_ALPHA) / ALPHA;
}