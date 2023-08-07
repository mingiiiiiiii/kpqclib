/** 
 * \file parsing.c
 * \brief Implementation of parsing.h
 */

#include "rolloI_192_parsing.h"
#include "string.h"
#include "rolloI_192_parameters.h"
#include "random_source.h"

void rolloI_192_secret_key_to_string(uint8_t* skString, const uint8_t* seed) {
	memcpy(skString, seed, SEEDEXPANDER_SEED_BYTES);
}

void rolloI_192_secret_key_from_string(rolloI_192_secretKey* sk, const uint8_t* skString) {
  uint8_t sk_seed[SEEDEXPANDER_SEED_BYTES] = {0};
  random_source sk_seedexpander;
  
  memcpy(sk_seed, skString, SEEDEXPANDER_SEED_BYTES);
  random_init(&sk_seedexpander, RANDOM_SOURCE_SEEDEXP);
  random_seed(&sk_seedexpander, sk_seed, sk_seed + 32, SEEDEXPANDER_MAX_LENGTH);

  rbc_79_vspace_init(&(sk->F), ROLLOI_192_PARAM_D);
  rbc_79_qre_init(&(sk->x));
  rbc_79_qre_init(&(sk->y));

  rbc_79_vspace_set_random_full_rank(&sk_seedexpander, sk->F, ROLLOI_192_PARAM_D);
  rbc_79_qre_set_random_pair_from_support(&sk_seedexpander, sk->x, sk->y, sk->F, ROLLOI_192_PARAM_D, 1);

  random_clear(&sk_seedexpander);
}


void rolloI_192_public_key_to_string(uint8_t* pkString, rolloI_192_publicKey* pk) {
	rbc_79_qre_to_string(pkString, pk->h);
}

void rolloI_192_public_key_from_string(rolloI_192_publicKey* pk, const uint8_t* pkString) {
	rbc_79_qre_init(&(pk->h));
	rbc_79_qre_from_string(pk->h, pkString);
}


void rolloI_192_rolloI_192_ciphertext_to_string(uint8_t* ctString, rolloI_192_ciphertext* ct) {
	rbc_79_qre_to_string(ctString, ct->syndrom);
}

void rolloI_192_rolloI_192_ciphertext_from_string(rolloI_192_ciphertext* ct, const uint8_t* ctString) {
	rbc_79_qre_init(&(ct->syndrom));
	rbc_79_qre_from_string(ct->syndrom, ctString);
}
