#ifndef _BIT_CONTRIBUTION_H
#define _BIT_CONTRIBUTION_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>


int KPQCLEAN_METAMORPHIC_bit_contribution_test_kem(
    const size_t pklen, const size_t sklen, const size_t keylen,
    const size_t mlen, const size_t clen, const size_t kem_siglen, char* ALGNAME);
#endif