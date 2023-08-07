#ifndef _BIT_EXCLUSION_H
#define _BIT_EXCLUSION_H

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define BIT_EXCLUSION_SUCCESS       0
#define BIT_EXCLUSION_FAIL          -1
#define EXCLUSION_BYTELEN           8   // 32 bit


int KPQCLEAN_METAMORPHIC_bit_exclusion_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t crypto_bytes, char* ALGNAME);

#endif