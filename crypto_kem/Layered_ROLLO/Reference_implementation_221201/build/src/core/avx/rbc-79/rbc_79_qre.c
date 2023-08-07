/**
 * \file rbc_79_qre.c
 * \brief Implementation of rbc_79_qre.h
 */

#include "rbc_79_elt.h"
#include "rbc_79_qre.h"
#include "rbc_79_poly.h"

static uint32_t RBC_79_QRE_DEG;
static int rbc_79_init_qre_modulus = 0;
static rbc_79_poly_sparse rbc_79_qre_modulus;
static rbc_79_poly rbc_79_qre_modulus_inv;




/**
 * \fn void rbc_79_qre_init_modulus(uint32_t degree) {
 * \brief This function init the quotient ring modulus corresponding to PARAM_N.
 *
 * \param[in] degree Degree of the modulus
 */
void rbc_79_qre_init_modulus(uint32_t degree) {
  if(rbc_79_init_qre_modulus == 0) {
    RBC_79_QRE_DEG = degree - 1;
    rbc_79_qre_modulus = rbc_79_qre_get_modulus(degree);
    rbc_79_poly_init(&rbc_79_qre_modulus_inv, RBC_79_QRE_DEG + 1);
    rbc_79_poly_set_zero(rbc_79_qre_modulus_inv, RBC_79_QRE_DEG + 1);
    for(uint32_t i = 0 ; i < rbc_79_qre_modulus->coeffs_nb ; i++) {
      rbc_79_elt_set_one(rbc_79_qre_modulus_inv->v[rbc_79_qre_modulus->coeffs[i]]);
    }
  }
  if(rbc_79_init_qre_modulus != 0)
  {
   printf("Err: qre_modulus is not working\n");
  }  

  rbc_79_init_qre_modulus++;
}




/**
 * \fn void rbc_79_qre_clear_modulus() {
 * \brief This function clears the quotient ring modulus in use.
 */
void rbc_79_qre_clear_modulus() {
  rbc_79_init_qre_modulus--;

  if(rbc_79_init_qre_modulus == 0) {
    rbc_79_poly_sparse_clear(rbc_79_qre_modulus);
    rbc_79_poly_clear(rbc_79_qre_modulus_inv);
  }
}

/**
 * \fn rbc_79_poly_sparse rbc_79_qre_get_modulus(uint32_t degree) {
 * \brief This function return the sparse polynomial used as the quotient ring modulus for PARAM_N.
 *
 * \param[in] degree Degree of the modulus
 */
rbc_79_poly_sparse rbc_79_qre_get_modulus(uint32_t degree) {
  rbc_79_poly_sparse modulus = NULL;
  uint32_t* values;
  if(degree == 83) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 2;
    values[2] = 4;
    values[3] = 7;
    values[4] = 83;
    rbc_79_poly_sparse_init(&modulus, 5, values);
    free(values);
  }
  else if(degree == 97) {
    values = (uint32_t*) malloc(3 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 6;
    values[2] = 97;
    rbc_79_poly_sparse_init(&modulus, 3, values);
    free(values);
  }
  else if(degree == 113) {
    values = (uint32_t*) malloc(3 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 9;
    values[2] = 113;
    rbc_79_poly_sparse_init(&modulus, 3, values);
    free(values);
  }
  else if(degree == 37) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 2;
    values[2] = 14;
    values[3] = 22;
    values[4] = 37;
    rbc_79_poly_sparse_init(&modulus, 5, values);
    free(values);
  }
  else if(degree == 43) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 5;
    values[2] = 22;
    values[3] = 27;
    values[4] = 43;
    rbc_79_poly_sparse_init(&modulus, 5, values);
    free(values);
  }
  else if(degree == 53) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 20;
    values[2] = 41;
    values[3] = 50;
    values[4] = 53;
    rbc_79_poly_sparse_init(&modulus, 5, values);
    free(values);
  }
  else if(degree == 74) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 4;
    values[2] = 28;
    values[3] = 44;
    values[4] = 74;
    rbc_79_poly_sparse_init(&modulus, 5, values);
    free(values);
  }
  else if(degree == 86) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 10;
    values[2] = 44;
    values[3] = 54;
    values[4] = 86;
    rbc_79_poly_sparse_init(&modulus, 5, values);
    free(values);
  }
  else if(degree == 106) {
    values = (uint32_t*) malloc(5 * sizeof(uint32_t));
    values[0] = 0;
    values[1] = 40;
    values[2] = 82;
    values[3] = 100;
    values[4] = 106;
    rbc_79_poly_sparse_init(&modulus, 5, values);
    free(values);
  }

 return modulus;
}




/**
 * \fn void rbc_79_qre_init(rbc_79_qre* p)
 * \brief This function allocates the memory for a rbc_79_qre element.
 *
 * \param[out] p Pointer to the allocated rbc_79_qre
 */
void rbc_79_qre_init(rbc_79_qre* p) {
  rbc_79_poly_init(p, RBC_79_QRE_DEG);
}




/**
 * \fn void rbc_79_qre_clear(rbc_79_qre p)
 * \brief This function clears the memory allocated for a rbc_79_qre element.
 *
 * \param[in] p rbc_79_qre
 */
void rbc_79_qre_clear(rbc_79_qre p) {
  rbc_79_poly_clear(p);
}




/**
 * \fn void rbc_79_qre_set_zero(rbc_79_qre o)
 * \brief This functions sets a rbc_79_qre to zero.
 *
 * \param[in] o rbc_79_qre
 */
void rbc_79_qre_set_zero(rbc_79_qre o) {
  rbc_79_poly_set_zero(o, RBC_79_QRE_DEG);
}




/**
 * \fn void rbc_79_qre_set_random(random_source* ctx, rbc_79_qre o)
 * \brief This function sets a rbc_79_qre with random values using NIST seed expander.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_79_qre
 */
void rbc_79_qre_set_random(random_source* ctx, rbc_79_qre o) {
  rbc_79_poly_set_random(ctx, o, RBC_79_QRE_DEG);
}




/**
 * \fn void rbc_79_qre_set_random_full_rank(random_source* ctx, rbc_79_qre o)
 * \brief This function sets a rbc_79_qre with random values using the NIST seed expander. The returned rbc_79_qre has full rank.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_79_qre
 */
void rbc_79_qre_set_random_full_rank(random_source* ctx, rbc_79_qre o) {
  rbc_79_poly_set_random_full_rank(ctx, o, RBC_79_QRE_DEG);
}




/**
 * \fn void rbc_79_qre_set_random_full_rank_with_one(random_source* ctx, rbc_79_qre o)
 * \brief This function sets a rbc_79_qre with random values using the NIST seed expander. The returned rbc_79_qre has full rank and contains one.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_79_qre
 */
void rbc_79_qre_set_random_full_rank_with_one(random_source* ctx, rbc_79_qre o) {
  rbc_79_poly_set_random_full_rank_with_one(ctx, o, RBC_79_QRE_DEG);
}




/**
 * \fn void rbc_79_qre_set_random_from_support(random_source* ctx, rbc_79_qre o, const rbc_79_vspace support, uint32_t support_size)
 * \brief This function sets a rbc_79_qre with random values using the NIST seed expander. The support of the rbc_79_qre returned by this function is the one given in input.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_79_qre
 * \param[in] support Support of <b>o</b>
 * \param[in] support_size Size of the support
 * \param[in] copy_flag If not 0, the support is copied into random coordinates of the resulting vector
 */
void rbc_79_qre_set_random_from_support(random_source* ctx, rbc_79_qre o, const rbc_79_vspace support, uint32_t support_size, uint8_t copy_flag) {
  rbc_79_poly_set_random_from_support(ctx, o, RBC_79_QRE_DEG, support, support_size, copy_flag);
}




/**
 * \fn void rbc_79_qre_set_random_pair_from_support(random_source* ctx, rbc_79_qre o1, rbc_79_qre o2, const rbc_79_vspace support, uint32_t support_size)
 * \brief This function sets a pair of rbc_79_qre with random values using the NIST seed expander. The support of (o1 || o2) is the one given in input.
 *
 * \param[out] ctx random_source
 * \param[out] o1 rbc_79_qre
 * \param[out] o2 rbc_79_qre
 * \param[in] support Support
 * \param[in] support_size Size of the support
 * \param[in] copy_flag If not 0, the support is copied into random coordinates of the resulting vector
 */
void rbc_79_qre_set_random_pair_from_support(random_source* ctx, rbc_79_qre o1, rbc_79_qre o2, const rbc_79_vspace support, uint32_t support_size, uint8_t copy_flag) {
  rbc_79_poly_set_random_pair_from_support(ctx, o1, o2, RBC_79_QRE_DEG, support, support_size, copy_flag);
}




/**
 * \fn uint8_t rbc_79_qre_is_equal_to(const rbc_79_qre p1, const rbc_79_qre p2)
 * \brief This function test if two rbc_79_qre are equal.
 *
 * \param[in] p1 rbc_79_qre
 * \param[in] p2 rbc_79_qre
 * \return 1 if the rbc_79_qre are equal, 0 otherwise
 */
uint8_t rbc_79_qre_is_equal_to(const rbc_79_qre p1, const rbc_79_qre p2) {
  return rbc_79_poly_is_equal_to(p1, p2);
}




/**
 * \fn void rbc_79_qre_add(rbc_79_qre o, const rbc_79_qre p1, const rbc_79_qre p2)
 * \brief This function adds two rbc_79_qre.
 *
 * \param[out] o Sum of <b>p1</b> and <b>p2</b>
 * \param[in] p1 rbc_79_qre
 * \param[in] p2 rbc_79_qre
 */
void rbc_79_qre_add(rbc_79_qre o, const rbc_79_qre p1, const rbc_79_qre p2) {
  rbc_79_poly_add(o, p1, p2);
}




/**
 * \fn void rbc_79_qre_mul(rbc_79_qre o, const rbc_79_qre p1, const rbc_79_qre p2)
 * \brief This function multiplies two rbc_79_qre.
 *
 * \param[out] o Product of <b>p1</b> and <b>p2</b>
 * \param[in] p1 rbc_79_qre
 * \param[in] p2 rbc_79_qre
 */
void rbc_79_qre_mul(rbc_79_qre o, const rbc_79_qre p1, const rbc_79_qre p2) {
  if(rbc_79_init_qre_modulus == 0) {
    printf("Call to rbc_79_qre_mul with uninitialized modulus\n");
    exit(1);
  }

  rbc_79_poly_mulmod_sparse(o, p1, p2, rbc_79_qre_modulus);
}




/**
 * \fn void rbc_79_qre_inv(rbc_79_qre o, const rbc_79_qre p)
 * \brief This function performs the extended euclidean algorithm to compute the inverse of p.
 *
 * \param[out] o Inverse of <b>e</b> modulo <b>modulus</b>
 * \param[in] p rbc_79_qre
 * \param[in] modulus Polynomial
 */
void rbc_79_qre_inv(rbc_79_qre o, const rbc_79_qre p) {
  if(rbc_79_init_qre_modulus == 0) {
    printf("Call to rbc_79_qre_inv with uninitialized modulus\n");
    exit(1);
  }

  rbc_79_poly_inv(o, p, rbc_79_qre_modulus_inv);
}




/**
 * \fn void rbc_79_qre_to_string(uint8_t* str, const rbc_79_qre p)
 * \brief This function parses a rbc_79_qre into a string.
 *
 * \param[out] str String
 * \param[in] e rbc_79_qre
 */
void rbc_79_qre_to_string(uint8_t* str, const rbc_79_qre p) {
  rbc_79_poly_to_string(str, p);
}




/**
 * \fn void rbc_79_qre_from_string(rbc_79_qre o, const uint8_t* str)
 * \brief This function parses a string into a rbc_79_qre.
 *
 * \param[out] o rbc_79_qre
 * \param[in] str String to parse
 */
void rbc_79_qre_from_string(rbc_79_qre o, const uint8_t* str) {
  rbc_79_poly_from_string(o, str);
}




/**
 * \fn void rbc_79_qre_print(const rbc_79_qre p)
 * \brief This function displays a rbc_79_qre.
 *
 * \param[in] p rbc_79_qre
 */
void rbc_79_qre_print(const rbc_79_qre p) {
  rbc_79_poly_print(p);
}

