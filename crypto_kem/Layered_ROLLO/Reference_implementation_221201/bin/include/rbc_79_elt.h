/**
 * \file rbc_79_vec.h
 * \brief Interface for finite field elements
 */

#ifndef RBC_79_ELT_H
#define RBC_79_ELT_H

#include "rbc_79.h"
#include "random_source.h"

void rbc_79_field_init();
void rbc_79_elt_set_zero(rbc_79_elt o);

void rbc_79_elt_set_one(rbc_79_elt o);

void rbc_79_elt_set(rbc_79_elt o, const rbc_79_elt e);

void rbc_79_elt_set_mask1(rbc_79_elt o, const rbc_79_elt e1, const rbc_79_elt e2, uint32_t mask);

void rbc_79_elt_set_mask2(rbc_79_elt o1, rbc_79_elt o2, const rbc_79_elt e, uint32_t mask);

void rbc_79_elt_set_from_uint64(rbc_79_elt o, const uint64_t* e);

void rbc_79_elt_set_random(random_source* ctx, rbc_79_elt o);
uint8_t rbc_79_elt_is_zero(const rbc_79_elt e);

uint8_t rbc_79_elt_is_equal_to(const rbc_79_elt e1, const rbc_79_elt e2);

uint8_t rbc_79_elt_is_greater_than(const rbc_79_elt e1, const rbc_79_elt e2);

int32_t rbc_79_elt_get_degree(const rbc_79_elt e);

uint8_t rbc_79_elt_get_coefficient_vartime(const rbc_79_elt e, uint32_t index);

void rbc_79_elt_set_coefficient_vartime(rbc_79_elt o, uint32_t index, uint8_t bit);

void rbc_79_elt_add(rbc_79_elt o, const rbc_79_elt e1, const rbc_79_elt e2);

void rbc_79_elt_mul(rbc_79_elt o, const rbc_79_elt e1, const rbc_79_elt e2);

void rbc_79_elt_inv(rbc_79_elt o, const rbc_79_elt e);

void rbc_79_elt_sqr(rbc_79_elt o, const rbc_79_elt e);

void rbc_79_elt_nth_root(rbc_79_elt o, const rbc_79_elt e, uint32_t n);

void rbc_79_elt_reduce(rbc_79_elt o, const rbc_79_elt_ur e);

void rbc_79_elt_print(const rbc_79_elt e);

void rbc_79_elt_ur_set(rbc_79_elt_ur o, const rbc_79_elt_ur e);

void rbc_79_elt_ur_set_zero(rbc_79_elt_ur o);

void rbc_79_elt_ur_set_from_uint64(rbc_79_elt_ur o, const uint64_t* e);

void rbc_79_elt_ur_mul(rbc_79_elt_ur o, const rbc_79_elt e1, const rbc_79_elt e2);

void rbc_79_elt_ur_sqr(rbc_79_elt_ur o, const rbc_79_elt e);

void rbc_79_elt_ur_print(const rbc_79_elt_ur e);

#endif

