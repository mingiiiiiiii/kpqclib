/**
 * \file rbc_79_qre.h
 * \brief Interface for quotient ring elements 
 * */

#ifndef RBC_79_QRE_H
#define RBC_79_QRE_H

#include "rbc_79.h"
#include "random_source.h"

void rbc_79_qre_init_modulus(uint32_t degree);

void rbc_79_qre_clear_modulus();

rbc_79_poly_sparse rbc_79_qre_get_modulus(uint32_t degree);

void rbc_79_qre_init(rbc_79_qre* p);

void rbc_79_qre_clear(rbc_79_qre p);

void rbc_79_qre_set_zero(rbc_79_qre o);

void rbc_79_qre_set_random(random_source* ctx, rbc_79_qre o);

void rbc_79_qre_set_random_full_rank(random_source* ctx, rbc_79_qre o);

void rbc_79_qre_set_random_full_rank_with_one(random_source* ctx, rbc_79_qre o);

void rbc_79_qre_set_random_from_support(random_source* ctx, rbc_79_qre o, const rbc_79_vspace support, uint32_t support_size, uint8_t copy_flag);

void rbc_79_qre_set_random_pair_from_support(random_source* ctx, rbc_79_qre o1, rbc_79_qre o2, const rbc_79_vspace support, uint32_t support_size, uint8_t copy_flag);

uint8_t rbc_79_qre_is_equal_to(const rbc_79_qre p1, const rbc_79_qre p2);

void rbc_79_qre_add(rbc_79_qre o, const rbc_79_qre p1, const rbc_79_qre p2);

void rbc_79_qre_mul(rbc_79_qre o, const rbc_79_qre p1, const rbc_79_qre p2);

void rbc_79_qre_inv(rbc_79_qre o, const rbc_79_qre p);

void rbc_79_qre_to_string(uint8_t* str, const rbc_79_qre p);

void rbc_79_qre_from_string(rbc_79_qre o, const uint8_t* str);

void rbc_79_qre_print(const rbc_79_qre p);

#endif

