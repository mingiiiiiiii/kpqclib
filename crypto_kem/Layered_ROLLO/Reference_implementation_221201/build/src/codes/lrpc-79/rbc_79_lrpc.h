/**
 * \file lrpc.h
 * \brief Fonctions to decode the error support using LRPC codes
 *
 */

#ifndef RBC_79_LRPC_H
#define RBC_79_LRPC_H

#include "rbc_79_vspace.h"
#include "rbc_79_qre.h"

unsigned int rbc_79_lrpc_RSR(rbc_79_vspace E, const uint32_t E_expected_dim, const rbc_79_vspace F, const uint32_t F_dim, const rbc_79_vec ec, const uint32_t ec_size);
unsigned int rbc_79_lrpc_RSR_vartime(rbc_79_vspace E, const uint32_t E_expected_dim, const rbc_79_vspace F, const uint32_t F_dim, const rbc_79_vec ec, const uint32_t ec_size);

#endif

