/** 
 * \file parsing.h
 * \brief Functions to parse secret key, public key and ciphertext of the ROLLO scheme
 */

#ifndef PARSING_H
#define PARSING_H

#include "biix_128_types.h"

void biix_128_secret_key_to_string(uint8_t* skString, const uint8_t* seed);
void biix_128_secret_key_from_string(biix_128_secretKey* sk, const uint8_t* skString);


void biix_128_public_key_to_string(uint8_t* pkString, biix_128_publicKey* pk);
void biix_128_public_key_from_string(biix_128_publicKey* pk, const uint8_t* pkString);


void biix_128_biix_128_ciphertext_to_string(uint8_t* ctString, biix_128_ciphertext* ct);
void biix_128_biix_128_ciphertext_from_string(biix_128_ciphertext* ct, const uint8_t* ctString);

#endif
