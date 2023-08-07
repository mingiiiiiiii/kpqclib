#include "reduce.h"
#include "params.h"
#include <stdint.h>

/*************************************************
 * Name:        montgomery_reduce
 *
 * Description: For finite field element a with -2^{31}Q <= a <= Q*2^31,
 *              compute r \equiv a*2^{-32} (mod Q) such that -Q < r < Q.
 *
 * Arguments:   - int64_t: finite field element a
 *
 * Returns r.
 **************************************************/
int32_t montgomery_reduce(int64_t a) {
    int32_t t;

    t = (int64_t)(int32_t)a * QINV;
    t = (a - (int64_t)t * Q) >> 32;
    return t;
}

/*************************************************
 * Name:        reduce32
 *
 * Description: For finite field element a with a <= 2^{31} - 2^{22} - 1,
 *              compute r \equiv a (mod Q) such that -6283009 <= r <= 6283007.
 *
 * Arguments:   - int32_t: finite field element a
 *
 * Returns r.
 **************************************************/
int32_t reduce32(int32_t a) {
    /*
    int32_t t;

    t = (a + (1 << 22)) >> 23; // TODO: find barrett reduction parameter
    t = a - t * Q;
    return t;
    */
    int32_t t = a % Q;
    t += (t >> 31) & Q;
    if (t > (Q >> 1)) {
        t -= Q;
    }

    return t;
}

/*************************************************
 * Name:        caddq
 *
 * Description: Add Q if input coefficient is negative.
 *
 * Arguments:   - int32_t: finite field element a
 *
 * Returns r.
 **************************************************/
int32_t caddq(int32_t a) {
    a += (a >> 31) & Q;
    return a;
}

/*************************************************
 * Name:        freeze
 *
 * Description: For finite field element a, compute standard
 *              representative r = a mod^+ Q.
 *
 * Arguments:   - int32_t: finite field element a
 *
 * Returns r.
 **************************************************/
int32_t freeze(int32_t a) {
    a = reduce32(a);
    a = caddq(a);
    return a;
}

/*************************************************
 * Name:        reduce32_2q
 *
 * Description: compute reduction with 2Q
 *
 * Arguments:   - int32_t: finite field element a
 *
 * Returns r.
 **************************************************/
int32_t reduce32_2q(int32_t a) {
    /*
    int32_t t;

    t = (a + (1 << 22)) >> 23; // TODO: find barrett reduction parameter
    t = a - t * Q;
    return t;
    */

    int32_t t = a % DQ;
    t += (t >> 31) & DQ;
    if (t > Q) {
        t -= DQ;
    }

    return t;
}

/*************************************************
 * Name:        cadd2q
 *
 * Description: Add 2Q if input coefficient is negative.
 *
 * Arguments:   - int32_t: finite field element a
 *
 * Returns r.
 **************************************************/
int32_t cadd2q(int32_t a) {
    a += (a >> 31) & DQ;
    return a;
}

/*************************************************
 * Name:        freeze2q
 *
 * Description: For finite field element a, compute standard
 *              representative r = a mod^+ Q.
 *
 * Arguments:   - int32_t: finite field element a
 *
 * Returns r.
 **************************************************/
int32_t freeze2q(int32_t a) {
    a = reduce32_2q(a);
    a = cadd2q(a);
    return a;
}