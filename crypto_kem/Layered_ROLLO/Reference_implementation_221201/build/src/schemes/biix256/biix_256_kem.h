/**
 * \file api.h
 * \brief NIST KEM API used by the BIIX_256_KEM IND-CPA scheme
 */


#ifndef BIIX_256_KEM_H
#define BIIX_256_KEM_H

int biix_256_keygen(uint8_t* pk, uint8_t* sk);
int biix_256_encaps(uint8_t* ct, uint8_t* ss, const uint8_t* pk);
int biix_256_decaps(uint8_t* ss, const uint8_t* ct, const uint8_t* sk);

#endif

