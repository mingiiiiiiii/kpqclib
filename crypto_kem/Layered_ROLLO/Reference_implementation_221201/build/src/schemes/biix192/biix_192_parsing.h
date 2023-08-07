/** 
 * \file parsing.h
 * \brief Functions to parse secret key, public key and ciphertext of the ROLLO scheme
 */

#ifndef PARSING_H
#define PARSING_H

#include "biix_192_types.h"

void biix_192_secret_key_to_string(uint8_t* skString, const uint8_t* seed);
void biix_192_secret_key_from_string(biix_192_secretKey* sk, const uint8_t* skString);


void biix_192_public_key_to_string(uint8_t* pkString, biix_192_publicKey* pk);
void biix_192_public_key_from_string(biix_192_publicKey* pk, const uint8_t* pkString);


void biix_192_biix_192_ciphertext_to_string(uint8_t* ctString, biix_192_ciphertext* ct);
void biix_192_biix_192_ciphertext_from_string(biix_192_ciphertext* ct, const uint8_t* ctString);

#endif
