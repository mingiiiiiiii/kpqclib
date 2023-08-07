/**
 * \file rbc_79_vec.h
 * \brief Interface for vectors of finite field elements
 */

#ifndef RBC_79_VEC_H
#define RBC_79_VEC_H

#include "rbc_79.h"
#include "rbc_79_elt.h"
#include "random_source.h"

void rbc_79_vec_init(rbc_79_vec* v, uint32_t size);

void rbc_79_vec_clear(rbc_79_vec v);

void rbc_79_vec_set_zero(rbc_79_vec v, uint32_t size);

void rbc_79_vec_set(rbc_79_vec o, const rbc_79_vec v, uint32_t size);

void rbc_79_vec_set_random(random_source* ctx, rbc_79_vec o, uint32_t size);

void rbc_79_vec_set_random_full_rank(random_source*, rbc_79_vec o, uint32_t size);

void rbc_79_vec_set_random_full_rank_with_one(random_source* ctx, rbc_79_vec o, uint32_t size);

void rbc_79_vec_set_random_from_support(random_source* ctx, rbc_79_vec o, uint32_t size, const rbc_79_vec support, uint32_t support_size, uint8_t copy_flag);
void rbc_79_vec_set_random_pair_from_support(random_source* ctx, rbc_79_vec o1, rbc_79_vec o2, uint32_t size, const rbc_79_vec support, uint32_t support_size, uint8_t copy_flag);

uint32_t rbc_79_vec_gauss(rbc_79_vec v, uint32_t size, rbc_79_vec *other_matrices, uint32_t nMatrices);
uint32_t rbc_79_vec_gauss_vartime(rbc_79_vec v, uint32_t size, rbc_79_vec *other_matrices, uint32_t nMatrices);

uint32_t rbc_79_vec_get_rank(const rbc_79_vec v, uint32_t size);
uint32_t rbc_79_vec_get_rank_vartime(const rbc_79_vec v, uint32_t size);

uint32_t rbc_79_vec_echelonize(rbc_79_vec o, uint32_t size);

void rbc_79_vec_add(rbc_79_vec o, const rbc_79_vec v1, const rbc_79_vec v2, uint32_t size);

void rbc_79_vec_scalar_mul(rbc_79_vec o, const rbc_79_vec v, const rbc_79_elt e, uint32_t size);

void rbc_79_vec_to_string(uint8_t* str, const rbc_79_vec v, uint32_t size);

void rbc_79_vec_from_string(rbc_79_vec v, uint32_t size, const uint8_t* str);

void rbc_79_vec_print(const rbc_79_vec v, uint32_t size);

#endif

