/**
 * \file rbc_97_vec.c
 * \brief Implementation of rbc_97_vec.h
 */

#include "rbc_97_vec.h"




/**
 * \fn void rbc_97_vec_init(rbc_97_vec* v, uint32_t size)
 * \brief This function initiates a rbc_97_vec element.
 *
 * \param[out] v Pointer to a rbc_97_vec element
 * \param[in] size Size of the vector
 */
void rbc_97_vec_init(rbc_97_vec* v, uint32_t size) {
  *v = calloc(size, sizeof(rbc_97_elt));
  if(v == NULL) exit(EXIT_FAILURE);
}




/**
 * \fn void rbc_97_vec_clear(rbc_97_vec v)
 * \brief This function clears a rbc_97_vec element.
 *
 * \param[out] v rbc_97_vec
 */
void rbc_97_vec_clear(rbc_97_vec v) {
  free(v);
}




/**
 * \fn void rbc_97_vec_set_zero(rbc_97_vec v, uint32_t size)
 * \brief This function sets a vector of finite elements to zero.
 *
 * \param[out] v rbc_97_vec
 * \param[in] size Size of the vector
 */
void rbc_97_vec_set_zero(rbc_97_vec v, uint32_t size) {
  for(size_t i = 0 ; i < size ; ++i) {
    rbc_97_elt_set_zero(v[i]);
  }
}




/**
 * \fn void rbc_97_vec_set(rbc_97_vec o, const rbc_97_vec v, uint32_t size)
 * \brief This function copies a vector of finite field elements to another one.
 *
 * \param[out] o rbc_97_vec
 * \param[in] v rbc_97_vec
 * \param[in] size Size of the vectors
 */
void rbc_97_vec_set(rbc_97_vec o, const rbc_97_vec v, uint32_t size) {
  for(size_t i = 0 ; i < size ; ++i) {
    rbc_97_elt_set(o[i], v[i]);
  }
}




/**
 * \fn void rbc_97_vec_set_random(random_source*, rbc_97_vec v, uint32_t size)
 * \brief This function sets a vector of finite field elements with random values using NIST seed expander.
 *
 * \param[out] ctx random source
 * \param[out] v rbc_97_vec
 * \param[in] size Size of the vector
 */
void rbc_97_vec_set_random(random_source* ctx, rbc_97_vec v, uint32_t size) {
  uint32_t bytes = (RBC_97_FIELD_M % 8 == 0) ? RBC_97_FIELD_M / 8 : RBC_97_FIELD_M / 8 + 1;
  uint8_t random[size * bytes];
  uint8_t mask = (1 << RBC_97_FIELD_M % 8) - 1;

  rbc_97_vec_set_zero(v, size);
  random_get_bytes(ctx, random, size * bytes);

  for(size_t i = 0 ; i < size ; ++i) {
    random[(i + 1) * bytes - 1] &= mask;
    memcpy(v[i], random + i * bytes, bytes);
  }
}




/**
 * \fn void rbc_97_vec_set_random_full_rank(random_source* ctx, rbc_97_vec o, uint32_t size)
 * \brief This function sets a vector with random values using the NIST seed expander. The returned vector has full rank. This functions leaks the number of iterations needed to compute the vector but this gives no informations about the returned vector.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_97_vec
 * \param[in] size Size of the vector
 */
void rbc_97_vec_set_random_full_rank(random_source* ctx, rbc_97_vec o, uint32_t size) {
  int32_t rank_max = RBC_97_FIELD_M < size ? RBC_97_FIELD_M : size;
  int32_t rank = -1;

  while(rank != rank_max) {
    rbc_97_vec_set_random(ctx, o, size);
    rank = rbc_97_vec_get_rank(o, size);
  }
}




/**
 * \fn void rbc_97_vec_set_random_full_rank_with_one(random_source* ctx, rbc_97_vec o, uint32_t size) {
 * \brief This function sets a vector with random values using the NIST seed expander. The vector returned by this function has full rank and contains one as the last coordinate.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_97_vec
 * \param[in] size Size of the vector
 */
void rbc_97_vec_set_random_full_rank_with_one(random_source* ctx, rbc_97_vec o, uint32_t size) {
  int32_t rank_max = RBC_97_FIELD_M < size ? RBC_97_FIELD_M : size;
  int32_t rank = -1;

  while(rank != rank_max) {
    rbc_97_vec_set_random(ctx, o, size - 1);
    rbc_97_elt_set_one(o[size - 1]);
    rank = rbc_97_vec_get_rank(o, size);
  }
}




/**
 * \fn void rbc_97_vec_set_random_from_support(random_source* o, rbc_97_vec o, uint32_t size, const rbc_97_vec support, uint32_t support_size)
 * \brief This function sets a vector with random values using the NIST seed expander. The support of the vector returned by this function is included in the one given in input.
 *
 * \param[out] ctx random source
 * \param[out] o rbc_97_vec
 * \param[in] size Size of <b>o</b>
 * \param[in] support Support of <b>v</b>
 * \param[in] rank Size of the support
 * \param[in] copy_flag If not 0, the support is copied into random coordinates of the resulting vector
 */
void rbc_97_vec_set_random_from_support(random_source* ctx, rbc_97_vec o, uint32_t size, const rbc_97_vec support, uint32_t support_size, uint8_t copy_flag) {
  rbc_97_vec_set_zero(o, size);

  uint32_t i=0;
  uint32_t j=0;

  if(copy_flag) {
    uint32_t random1_size = 2 * support_size;
    uint32_t random2_size = (support_size * (size - support_size)) / 8 + 1;
    uint8_t random1[random1_size];
    uint8_t random2[random2_size];

    // Copy the support vector in support_size random positions of o
    random_get_bytes(ctx, random1, random1_size);

    uint32_t position;
    while(i != support_size) {
      position = random1[j];

      // Check that the position is not already taken
      if(position < size * (256 / size) && rbc_97_elt_is_zero(o[position % size])) {
        rbc_97_elt_set(o[position % size], support[i]);
        i++;
      }

      // Get more randomness if necessary
      j++;
      if(j % random1_size == 0 && i != support_size) {
        random_get_bytes(ctx, random1, random1_size);
        j = 0;
      }
    }

    // Set all the remaining coordinates with random linear combinations of the support coordinates
    random_get_bytes(ctx, random2, random2_size);

    uint32_t k = 0;
    uint32_t l = 0;
    for(i = 0 ; i < size ; ++i) {
      if(rbc_97_elt_is_zero(o[i])) {

        for(j = 0 ; j < support_size ; ++j) {
          if(random2[k] & 0x1) {
            rbc_97_elt_add(o[i], support[j], o[i]);
          }

          random2[k] = random2[k] >> 1;
          l++;
          if(l == 8) {
            l = 0;
            k++;
          }

        }
      }
    }
  }
  else {
    // Set all the coordinates with random linear combinations of the support coordinates
    uint32_t random_size = support_size * size / 8 + 1;
    unsigned char random[random_size];
    random_get_bytes(ctx, random, random_size);

    uint32_t k = 0;
    uint32_t l = 0;

    for(i=0 ; i<size ; i++) {
      for(j=0 ; j<support_size ; j++) {
        if(random[k] & 0x01) {
          rbc_97_elt_add(o[i], o[i], support[j]);
        }

        random[k] = random[k] >> 1;
        l++;
        if(l == 8) {
          l=0;
          k++;
        }
      }
    }
  }
}




/**
 * \fn void rbc_97_vec_set_random_pair_from_support(random_source* o, rbc_97_vec o1, rbc_97_vec o2, uint32_t size, const rbc_97_vec support, uint32_t support_size)
 * \brief This function sets a pair of vector with random values using the NIST seed expander. The support of the vector (o1 || o2) is the one given in input.
 *
 * This function copies the support vector in rank random positions of <b>o1</b> or <b>o2</b>. Next, all the remaining coordinates of <b>o1</b> and <b>o2</b> are set using random linear combinations of the support coordinates. 
 *
 * This function should not be called with size < support_size.
 * 
 * \param[out] ctx random source
 * \param[out] o1 rbc_97_vec
 * \param[out] o2 rbc_97_vec
 * \param[in] size Size of <b>o1</b> and <b>o2</b>
 * \param[in] support Support
 * \param[in] support_size Size of the support
 * \param[in] copy_flag If not 0, the support is copied into random coordinates of the resulting vector
 */
void rbc_97_vec_set_random_pair_from_support(random_source* ctx, rbc_97_vec o1, rbc_97_vec o2, uint32_t size, const rbc_97_vec support, uint32_t support_size, uint8_t copy_flag) {
  if (copy_flag) {
    uint32_t random1_size = 4 * support_size;
    uint32_t random2_size = (support_size * (2 * size - support_size)) / 8 + 2;
    uint8_t random1[random1_size];
    uint8_t random2[random2_size];

    // Copy the support vector in support_size random positions of o
    random_get_bytes(ctx, random1, random1_size);

    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t position;

    while(i != support_size) {
      position = random1[j];

      // Check that the position is not already taken
      if(position < size * (256 / size)) {
        if(random1[j + 1] & 0x1) {
          if(rbc_97_elt_is_zero(o1[position % size])) {
            rbc_97_elt_set(o1[position % size], support[i]);
            i++;
          }
        } 
        else {
          if(rbc_97_elt_is_zero(o2[position % size])) {
            rbc_97_elt_set(o2[position % size], support[i]);
            i++;
          }
        }
      }

      // Get more randomness if necessary
      j = j + 2;
      if(j % random1_size == 0 && i != support_size) {
        random_get_bytes(ctx, random1, random1_size);
        j = 0;
      }
    }

    // Set all the remaining coordinates with random linear combinations of the support coordinates
    random_get_bytes(ctx, random2, random2_size);

    uint32_t k = 0;
    uint32_t l = 0;

    for(i = 0 ; i < size ; ++i) {
      if(rbc_97_elt_is_zero(o1[i])) {
        for(j = 0 ; j < support_size ; ++j) {
          if(random2[k] & 0x1) {
            rbc_97_elt_add(o1[i], support[j], o1[i]);
          }

          random2[k] = random2[k] >> 1;
          l++;
          if(l == 8) {
            l = 0;
            k++;
          }
        }
      }
    }

    k++;

    for(i = 0 ; i < size ; ++i) {
      if(rbc_97_elt_is_zero(o2[i])) {
        for(j = 0 ; j < support_size ; ++j) {
          if(random2[k] & 0x1) {
            rbc_97_elt_add(o2[i], support[j], o2[i]);
          }

          random2[k] = random2[k] >> 1;
          l++;
          if(l == 8) {
            l = 0;
            k++;
          }
        }
      }
    }
  }
  else {
    //Set all the coordinates to random linear combinations of the support
    uint32_t random_size = 2 * support_size * size / 8 + 1;
    uint8_t random[random_size];
    random_get_bytes(ctx, random, random_size);

    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t k = 0;
    uint32_t l = 0;

    for(i = 0 ; i < size ; ++i) {
      for(j = 0 ; j < support_size ; ++j) {
        if(random[k] & 0x1) {
          rbc_97_elt_add(o1[i], support[j], o1[i]);
        }

        random[k] = random[k] >> 1;
        l++;
        if(l == 8) {
          l = 0;
          k++;
        }
      }
    }

    for(i = 0 ; i < size ; ++i) {
      for(j = 0 ; j < support_size ; ++j) {
        if(random[k] & 0x1) {
          rbc_97_elt_add(o2[i], support[j], o2[i]);
        }

        random[k] = random[k] >> 1;
        l++;
        if(l == 8) {
          l = 0;
          k++;
        }
      }
    }
  }
}




/**
 * \fn uint32_t rbc_97_vec_gauss(rbc_97_vec v, uint32_t size, rbc_97_vec *other_matrices, uint32_t nMatrices)
 * \brief This function transform a vector of finite field elements to its row echelon form and returns its rank.
 *
 * Replicates linear operations on the nMatrices matrices indexed by other_matrices.
 *
 * \param[in] v rbc_97_vec
 * \param[in] size Size of the vector
 * \param[in] other_matrices Pointer to other matrices to replicate the operations on
 * \param[in] nMatrices Number of other matrices
 *
 * \return Rank of the vector <b>v</b>
 */
uint32_t rbc_97_vec_gauss(rbc_97_vec v, uint32_t size, rbc_97_vec *other_matrices, uint32_t nMatrices) {
  if(size == 0) return 0;

  uint32_t dimension = 0;
  rbc_97_elt sum, tmp;
  rbc_97_elt zero;
  rbc_97_elt_set_zero(zero);
  rbc_97_elt dummy;

  //For each column
  for(size_t i = 0 ; i < RBC_97_FIELD_M ; i++) {
    int64_t mask;
    size_t column = RBC_97_FIELD_M - i - 1;
    uint32_t row = min(dimension, size-1);

    //For each line below
    for(size_t j=0 ; j < size ; j++) {
        rbc_97_elt_add(sum, v[row], v[j]);
        mask = rbc_97_elt_get_coefficient_vartime(sum, column);
        rbc_97_elt_set_mask1(tmp, v[j], zero, mask);
        if(j > row) {
          rbc_97_elt_add(v[row], v[row], tmp);
          for(size_t k=0 ; k<nMatrices ; k++) {
            rbc_97_elt_set_mask1(tmp, other_matrices[k][j], zero, mask);
            rbc_97_elt_add(other_matrices[k][row], other_matrices[k][row], tmp);
          }
        }
        else {
          rbc_97_elt_add(dummy, v[row], tmp);
          for(size_t k=0 ; k<nMatrices ; k++) {
            rbc_97_elt_add(dummy, other_matrices[k][row], tmp);
          }
        }
    }

    //For each other line
    for(size_t j=0 ; j < size ; j++) {
      if(j == row) continue;
      mask = rbc_97_elt_get_coefficient_vartime(v[j], column);
      rbc_97_elt_set_mask1(tmp, v[row], zero, mask);
      if(dimension < size) {
        rbc_97_elt_add(v[j], v[j], tmp);
        for(size_t k=0 ; k<nMatrices ; k++) {
          rbc_97_elt_set_mask1(tmp, other_matrices[k][row], zero, mask);
          rbc_97_elt_add(other_matrices[k][j], other_matrices[k][j], tmp);
        }
      }
      else {
        rbc_97_elt_add(dummy, v[j], tmp);
        for(size_t k=0 ; k<nMatrices ; k++) {
          rbc_97_elt_add(dummy, other_matrices[k][j], tmp);
        }
      }
    }

    dimension += rbc_97_elt_get_coefficient_vartime(v[row], column);
  }

  return min(dimension, size);
}



/**
 * \fn uint32_t rbc_97_vec_gauss_vartime(rbc_97_vec v, uint32_t size, rbc_97_vec *other_matrices, uint32_t nMatrices)
 * \brief This function transform a vector of finite field elements to its row echelon form and returns its rank.
 *
 * Replicates linear operations on the nMatrices matrices indexed by other_matrices.
 *
 * \param[in] v rbc_97_vec
 * \param[in] size Size of the vector
 * \param[in] other_matrices Pointer to other matrices to replicate the operations on
 * \param[in] nMatrices Number of other matrices
 *
 * \return Rank of the vector <b>v</b>
 */
uint32_t rbc_97_vec_gauss_vartime(rbc_97_vec v, uint32_t size, rbc_97_vec *other_matrices, uint32_t nMatrices) {
  if(size == 0) return 0;

  int32_t degree;
  int32_t target_deg, current_deg;
  size_t pivot;

  target_deg = RBC_97_FIELD_M;

  for(size_t i = 0 ; i < size ; i++) {
    // Take the pivot as the greatest coordinate of v
    pivot = i;
    current_deg = rbc_97_elt_get_degree(v[pivot]);

    for(size_t j = pivot + 1 ; j < size ; j++) {
      if(current_deg == target_deg) {
        break;
      }

      int j_deg = rbc_97_elt_get_degree(v[j]);
      if(j_deg > current_deg) {
        pivot = j;
        current_deg = j_deg;
      }
    }

    // Stop computation if the pivot is equal to zero
    if(current_deg == -1) {
      return pivot;
    }

    target_deg = current_deg - 1;

    // Swap current coordinate with pivot
    rbc_97_elt tmp;
    rbc_97_elt_set(tmp, v[i]);
    rbc_97_elt_set(v[i], v[pivot]);
    rbc_97_elt_set(v[pivot], tmp);

    for(size_t k=0 ; k<nMatrices ; k++) {
      rbc_97_elt_set(tmp, other_matrices[k][i]);
      rbc_97_elt_set(other_matrices[k][i], other_matrices[k][pivot]);
      rbc_97_elt_set(other_matrices[k][pivot], tmp);
    }
    degree = rbc_97_elt_get_degree(v[i]);

    // Add matrix columns whenever necessary
    for(size_t j = i + 1; j < size; j++) {
      if(!(rbc_97_elt_is_zero(v[j]) || rbc_97_elt_get_degree(v[j]) < degree)) {
        rbc_97_elt_add(v[j], v[j], v[i]);
        for(size_t k=0 ; k<nMatrices ; k++) {
          rbc_97_elt_add(other_matrices[k][j], other_matrices[k][j], other_matrices[k][i]);
        }
      }
    }
  }

  return size;
}




/**
 * \fn uint32_t rbc_97_vec_get_rank(const rbc_97_vec v, uint32_t size)
 * \brief This function computes the rank of a vector of finite field elements.
 *
 * \param[in] v rbc_97_vec
 * \param[in] size Size of the vector
 *
 * \return Rank of the vector <b>v</b>
 */
uint32_t rbc_97_vec_get_rank(const rbc_97_vec v, uint32_t size) {
  rbc_97_vec copy;
  uint32_t dimension;

  rbc_97_vec_init(&copy, size);
  rbc_97_vec_set(copy, v, size);
  dimension = rbc_97_vec_gauss(copy, size, NULL, 0);
  rbc_97_vec_clear(copy);

  return dimension;
}



/**
 * \fn uint32_t rbc_97_vec_get_rank_vartime(const rbc_97_vec v, uint32_t size)
 * \brief This function computes the rank of a vector of finite field elements.
 *
 * \param[in] v rbc_97_vec
 * \param[in] size Size of the vector
 *
 * \return Rank of the vector <b>v</b>
 */
uint32_t rbc_97_vec_get_rank_vartime(const rbc_97_vec v, uint32_t size) {
  rbc_97_vec copy;
  uint32_t dimension;

  rbc_97_vec_init(&copy, size);
  rbc_97_vec_set(copy, v, size);
  dimension = rbc_97_vec_gauss_vartime(copy, size, NULL, 0);
  rbc_97_vec_clear(copy);

  return dimension;
}




/**
 * \fn uint32_t rbc_97_vec_echelonize(rbc_97_vec v, uint32_t size)
 * \brief This function computes the row reduced echelon form of a vector of finite field elements and returns its rank.
 *
 * \param[in] v rbc_97_vec
 * \param[in] size Size of the vector
 *
 * \return Rank of the vector <b>v</b>
 */
uint32_t rbc_97_vec_echelonize(rbc_97_vec v, uint32_t size) {
  uint32_t degree;
  uint32_t dimension = rbc_97_vec_gauss(v, size, NULL, 0);

  for(int32_t i = dimension - 1 ; i >= 1 ; i--) {
    degree = rbc_97_elt_get_degree(v[i]);

    for(int32_t j = i - 1 ; j >= 0 ; j--) {
      if(rbc_97_elt_get_coefficient_vartime(v[j], degree) == 1) {
        rbc_97_elt_add(v[j], v[j], v[i]);
      }
    }
  }

  return dimension;
}




/**
 * \fn void rbc_97_vec_add(rbc_97_vec o, const rbc_97_vec v1, const rbc_97_vec v2, uint32_t size)
 * \brief This function adds two vectors of finite field elements.
 *
 * \param[out] o Sum of <b>v1</b> and <b>v2</b>
 * \param[in] v1 rbc_97_vec
 * \param[in] v2 rbc_97_vec
 * \param[in] size Size of the vectors
 */
void rbc_97_vec_add(rbc_97_vec o, const rbc_97_vec v1, const rbc_97_vec v2, uint32_t size) {
  for(size_t i = 0 ; i < size ; ++i) {
    rbc_97_elt_add(o[i], v1[i], v2[i]);
  }
}




/**
 * \fn void rbc_97_vec_scalar_mul(rbc_97_vec o, const rbc_97_vec v, const rbc_97_elt e, uint32_t size)
 * \brief This functions multiplies a vector of finite field elements by a scalar.
 *
 * \param[out] o rbc_97_vec equal to \f$ e \times v \f$
 * \param[in] v rbc_97_vec
 * \param[in] e Finite field element
 * \param[in] size Size of the vector
 */
void rbc_97_vec_scalar_mul(rbc_97_vec o, const rbc_97_vec v, const rbc_97_elt e, uint32_t size) {
  for(size_t i = 0 ; i < size ; ++i) {
    rbc_97_elt_mul(o[i], v[i], e);
  }
}




/**
 * \fn void rbc_97_vec_to_string(uint8_t* str, const rbc_97_vec v, uint32_t size)
 * \brief This function parses a vector of finite field elements into a string.
 *
 * \param[out] str Output string
 * \param[in] v rbc_97_vec
 * \param[in] size Size of the vector
 */
void rbc_97_vec_to_string(uint8_t* str, const rbc_97_vec v, uint32_t size) {
  uint32_t bytes1 = RBC_97_FIELD_M / 8;
  uint32_t bytes2 = RBC_97_FIELD_M % 8;
  uint32_t index = bytes1 * size;
  uint32_t str_size = ((size * RBC_97_FIELD_M) % 8 == 0) ? (size * RBC_97_FIELD_M) / 8 : (size * RBC_97_FIELD_M) / 8 + 1;

  memset(str, 0, str_size);

  for(size_t i = 0 ; i < size ; i++) {
    memcpy(str + i * bytes1, v[i], bytes1);
  }

  uint8_t k = 0;
  for(size_t i = 0 ; i < size ; i++) {
    for(size_t j = 1 ; j <= bytes2 ; j++) {
      uint8_t bit = rbc_97_elt_get_coefficient_vartime(v[i], RBC_97_FIELD_M - j);
      *(str + index) |= (bit << k % 8);
      k++;
      if(k % 8 == 0) index++;
    }
  }
}




/**
 * \fn void rbc_97_vec_from_string(rbc_97_vec v, uint32_t size, const uint8_t* str)
 * \brief This function parses a string into a vector of finite field elements.
 *
 * \param[out] v rbc_97_vec
 * \param[in] size Size of the vector
 * \param[in] str String to parse
 */
void rbc_97_vec_from_string(rbc_97_vec v, uint32_t size, const uint8_t* str) {
  uint32_t bytes1 = RBC_97_FIELD_M / 8;
  uint32_t bytes2 = RBC_97_FIELD_M % 8;
  uint32_t index = bytes1 * size;

  rbc_97_vec_set_zero(v, size);

  for(size_t i = 0 ; i < size ; i++) {
    memcpy(v[i], str + i * bytes1, bytes1);
  }

  uint8_t k = 0;
  for(size_t i = 0 ; i < size ; i++) {
    for(size_t j = 1 ; j <= bytes2 ; j++) {
      uint8_t bit = (str[index] >> k % 8) & 0x01;
      rbc_97_elt_set_coefficient_vartime(v[i], RBC_97_FIELD_M - j, bit);
      k++;
      if(k % 8 == 0) index++;
    }
  }
}




/**
 * \fn void rbc_97_vec_print(rbc_97_vec v, uint32_t size)
 * \brief Display an rbc_97_vec element.
 *
 * \param[out] v rbc_97_vec
 * \param[in] size Size of the vector
 */
void rbc_97_vec_print(rbc_97_vec v, uint32_t size) {
  printf("[\n");
  for(size_t i = 0 ; i < size ; ++i) {
    rbc_97_elt_print(v[i]);
    printf("\n");
  }
  printf("]\n");
}

