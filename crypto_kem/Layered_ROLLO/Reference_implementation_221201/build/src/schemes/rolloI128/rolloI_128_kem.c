/** 
 * \file kem.c
 * \brief Implementation of api.h
 */

#include "rbc_67_qre.h"
#include "rbc_67_vec.h"
#include "sha2.h"
#include "fips202.h"
#include "rolloI_128_parameters.h"
#include "string.h"
#include "rbc_67_lrpc.h"
#include "rolloI_128_types.h"
#include "rolloI_128_parsing.h"


int rolloI_128_keygen(uint8_t* pk, uint8_t* sk) {
  rolloI_128_secretKey skTmp;
  rolloI_128_publicKey pkTmp;

  rbc_67_qre invX;

  rbc_67_field_init();
  rbc_67_qre_init_modulus(ROLLOI_128_PARAM_N);

  random_source prng;
  random_init(&prng, RANDOM_SOURCE_PRNG);

  uint8_t sk_seed[SEEDEXPANDER_SEED_BYTES];
  random_get_bytes(&prng, sk_seed, SEEDEXPANDER_SEED_BYTES);

  rolloI_128_secret_key_from_string(&skTmp, sk_seed);

  rbc_67_qre_init(&invX);
  rbc_67_qre_inv(invX, skTmp.x);

  rbc_67_qre_init(&(pkTmp.h));
  rbc_67_qre_mul(pkTmp.h, invX, skTmp.y);

  rolloI_128_secret_key_to_string(sk, sk_seed);
  rolloI_128_public_key_to_string(pk, &pkTmp);

  #ifdef VERBOSE
    printf("\n\nsk_seed: "); for(size_t i = 0 ; i < SEEDEXPANDER_SEED_BYTES ; ++i) printf("%02x", sk_seed[i]);
    printf("\n\nx: "); rbc_67_qre_print(skTmp.x);
    printf("\n\ny: "); rbc_67_qre_print(skTmp.y);
    printf("\n\nx^-1: "); rbc_67_qre_print(invX);
    printf("\n\nh: "); rbc_67_qre_print(pkTmp.h);
    printf("\n\nsk: "); for(size_t i = 0 ; i < ROLLOI_128_SECRET_KEY_BYTES ; ++i) printf("%02x", sk[i]);
    printf("\n\npk: "); for(size_t i = 0 ; i < ROLLOI_128_PUBLIC_KEY_BYTES ; ++i) printf("%02x", pk[i]);
  #endif

  rbc_67_qre_clear(invX);

  rbc_67_vspace_clear(skTmp.F);
  rbc_67_qre_clear(skTmp.x);
  rbc_67_qre_clear(skTmp.y);
  rbc_67_qre_clear(pkTmp.h);
  rbc_67_qre_clear_modulus();

  return 0;
}

int rolloI_128_encaps(uint8_t* ct, uint8_t* ss, const uint8_t* pk) {
  rolloI_128_publicKey pkTmp;
  rolloI_128_ciphertext ctTmp;

  rbc_67_vspace E;
  rbc_67_qre E1, E2;

  rbc_67_field_init();
  rbc_67_qre_init_modulus(ROLLOI_128_PARAM_N);

  rolloI_128_public_key_from_string(&pkTmp, pk);

  rbc_67_vspace_init(&E, ROLLOI_128_PARAM_R);

  random_source prng;
  random_init(&prng, RANDOM_SOURCE_PRNG);

  //Support
  rbc_67_vspace_set_random_full_rank(&prng, E, ROLLOI_128_PARAM_R);

  rbc_67_qre_init(&E1);
  rbc_67_qre_init(&E2);
  rbc_67_qre_init(&(ctTmp.syndrom));

  //Random error vectors
  rbc_67_qre_set_random_pair_from_support(&prng, E1, E2, E, ROLLOI_128_PARAM_R, 1);

  rbc_67_qre_mul(ctTmp.syndrom, E2, pkTmp.h);
  rbc_67_qre_add(ctTmp.syndrom, ctTmp.syndrom, E1);

  rolloI_128_rolloI_128_ciphertext_to_string(ct, &ctTmp);

  rbc_67_vec_echelonize(E, ROLLOI_128_PARAM_R);

  uint8_t support[ROLLOI_128_RBC_VEC_R_BYTES];
  rbc_67_vec_to_string(support, E, ROLLOI_128_PARAM_R);
  sha512(ss, support, ROLLOI_128_RBC_VEC_R_BYTES);

  #ifdef VERBOSE
    printf("\n\nE: "); rbc_67_vspace_print(E, ROLLOI_128_PARAM_R);
    printf("\n\nE1: "); rbc_67_qre_print(E1);
    printf("\n\nE2: "); rbc_67_qre_print(E2);
    printf("\n\nsyndrom: "); rbc_67_qre_print(ctTmp.syndrom);
    printf("\n\nROLLOI_128_SHARED secret: "); for(size_t i = 0 ; i < ROLLOI_128_SHARED_SECRET_BYTES ; ++i) printf("%02x", ss[i]);
  #endif

  rbc_67_vspace_clear(E);
  rbc_67_qre_clear(E1);
  rbc_67_qre_clear(E2);
  rbc_67_qre_clear(pkTmp.h);
  rbc_67_qre_clear(ctTmp.syndrom);
  rbc_67_qre_clear_modulus();

  return 0;
}

int rolloI_128_decaps(uint8_t* ss, const uint8_t* ct, const uint8_t* sk) {
  rolloI_128_secretKey skTmp;
  rolloI_128_ciphertext ctTmp;

  rbc_67_qre xc;
  rbc_67_vspace E;
  uint8_t support[ROLLOI_128_RBC_VEC_R_BYTES];

  rbc_67_field_init();
  rbc_67_qre_init_modulus(ROLLOI_128_PARAM_N);

  rolloI_128_secret_key_from_string(&skTmp, sk);
  rolloI_128_rolloI_128_ciphertext_from_string(&ctTmp, ct);

  rbc_67_qre_init(&xc);
  rbc_67_qre_mul(xc, skTmp.x, ctTmp.syndrom);

  uint32_t dimE = 0;

  rbc_67_vspace_init(&E, ROLLOI_128_PARAM_N);

  dimE = rbc_67_lrpc_RSR(E, ROLLOI_128_PARAM_R, skTmp.F, ROLLOI_128_PARAM_D, xc->v, ROLLOI_128_PARAM_N);

  if(dimE != 0) {
    rbc_67_vec_to_string(support, E, ROLLOI_128_PARAM_R);
    sha512(ss, support, ROLLOI_128_RBC_VEC_R_BYTES);
  } else {
    memset(ss, 0, ROLLOI_128_SHARED_SECRET_BYTES);
  }

  #ifdef VERBOSE
    printf("\n\nxc: "); rbc_67_qre_print(xc);
    printf("\n\nRecovered E: "); rbc_67_vspace_print(E, dimE);
    printf("\n\nROLLOI_128_SHARED secret: "); for(size_t i = 0 ; i < ROLLOI_128_SHARED_SECRET_BYTES ; ++i) printf("%02x", ss[i]);
  #endif

  rbc_67_vspace_clear(E);
  rbc_67_qre_clear(xc);
  rbc_67_vspace_clear(skTmp.F);
  rbc_67_qre_clear(skTmp.x);
  rbc_67_qre_clear(skTmp.y);
  rbc_67_qre_clear(ctTmp.syndrom);
  rbc_67_qre_clear_modulus();

  int result;

  result = dimE != ROLLOI_128_PARAM_R;

  return result;
}
