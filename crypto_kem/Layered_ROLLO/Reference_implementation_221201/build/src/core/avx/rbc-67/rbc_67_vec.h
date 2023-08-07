/**
 * \file rbc_67_vec.h
 * \brief Interface for vectors of finite field elements
 */

#ifndef RBC_67_VEC_H
#define RBC_67_VEC_H

#include "rbc_67.h"
#include "rbc_67_elt.h"
#include "random_source.h"

void rbc_67_vec_init(rbc_67_vec* v, uint32_t size);

void rbc_67_vec_clear(rbc_67_vec v);

void rbc_67_vec_set_zero(rbc_67_vec v, uint32_t size);

void rbc_67_vec_set(rbc_67_vec o, const rbc_67_vec v, uint32_t size);

void rbc_67_vec_set_random(random_source* ctx, rbc_67_vec o, uint32_t size);

void rbc_67_vec_set_random_full_rank(random_source*, rbc_67_vec o, uint32_t size);

void rbc_67_vec_set_random_full_rank_with_one(random_source* ctx, rbc_67_vec o, uint32_t size);

void rbc_67_vec_set_random_from_support(random_source* ctx, rbc_67_vec o, uint32_t size, const rbc_67_vec support, uint32_t support_size, uint8_t copy_flag);
void rbc_67_vec_set_random_pair_from_support(random_source* ctx, rbc_67_vec o1, rbc_67_vec o2, uint32_t size, const rbc_67_vec support, uint32_t support_size, uint8_t copy_flag);

uint32_t rbc_67_vec_gauss(rbc_67_vec v, uint32_t size, rbc_67_vec *other_matrices, uint32_t nMatrices);
uint32_t rbc_67_vec_gauss_vartime(rbc_67_vec v, uint32_t size, rbc_67_vec *other_matrices, uint32_t nMatrices);

uint32_t rbc_67_vec_get_rank(const rbc_67_vec v, uint32_t size);
uint32_t rbc_67_vec_get_rank_vartime(const rbc_67_vec v, uint32_t size);

uint32_t rbc_67_vec_echelonize(rbc_67_vec o, uint32_t size);

void rbc_67_vec_add(rbc_67_vec o, const rbc_67_vec v1, const rbc_67_vec v2, uint32_t size);

void rbc_67_vec_scalar_mul(rbc_67_vec o, const rbc_67_vec v, const rbc_67_elt e, uint32_t size);

void rbc_67_vec_to_string(uint8_t* str, const rbc_67_vec v, uint32_t size);

void rbc_67_vec_from_string(rbc_67_vec v, uint32_t size, const uint8_t* str);

void rbc_67_vec_print(const rbc_67_vec v, uint32_t size);

#endif

