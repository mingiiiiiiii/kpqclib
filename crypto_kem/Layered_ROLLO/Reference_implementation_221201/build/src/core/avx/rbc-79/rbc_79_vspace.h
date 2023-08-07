/**
 * \file rbc_79_vspace.h
 * \brief Interface for subspaces of Fq^m
 */

#ifndef RBC_79_VSPACE_H
#define RBC_79_VSPACE_H

#include "rbc_79.h"
#include "random_source.h"

void rbc_79_vspace_init(rbc_79_vspace* vs, uint32_t size);

void rbc_79_vspace_clear(rbc_79_vspace vs);

void rbc_79_vspace_set(rbc_79_vspace o, const rbc_79_vspace vs, uint32_t size);

void rbc_79_vspace_set_zero(rbc_79_vspace o, uint32_t size);

void rbc_79_vspace_set_random_full_rank(random_source* ctx, rbc_79_vspace o, uint32_t size);

void rbc_79_vspace_set_random_full_rank_with_one(random_source* ctx, rbc_79_vspace o, uint32_t size);

void rbc_79_vspace_direct_sum(rbc_79_vspace o, const rbc_79_vspace vs1, const rbc_79_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

uint32_t rbc_79_vspace_intersection(rbc_79_vspace o, const rbc_79_vspace vs1, const rbc_79_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);
uint32_t rbc_79_vspace_intersection_vartime(rbc_79_vspace o, const rbc_79_vspace vs1, const rbc_79_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_79_vspace_product(rbc_79_vspace o, const rbc_79_vspace vs1, const rbc_79_vspace vs2, uint32_t vs1_size, uint32_t vs2_size);

void rbc_79_vspace_print(const rbc_79_vspace vs, uint32_t size);

#endif

