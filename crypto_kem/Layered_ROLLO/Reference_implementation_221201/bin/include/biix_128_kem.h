/**
 * \file api.h
 * \brief NIST KEM API used by the BIIX_128_KEM IND-CPA scheme
 */


#ifndef BIIX_128_KEM_H
#define BIIX_128_KEM_H

int biix_128_keygen(uint8_t* pk, uint8_t* sk);
int biix_128_encaps(uint8_t* ct, uint8_t* ss, const uint8_t* pk);
int biix_128_decaps(uint8_t* ss, const uint8_t* ct, const uint8_t* sk);

#endif

