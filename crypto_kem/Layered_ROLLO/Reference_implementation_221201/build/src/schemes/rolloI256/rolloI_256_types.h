/** 
 * \file rolloI_256_types.h
 * \brief File defining publicKey, secretKey and cipherText types for ROLLO-I
 */

#ifndef ROLLOI_256_TYPES_H
#define ROLLOI_256_TYPES_H

#include "rbc_97_qre.h"
#include "rbc_97_vspace.h"

typedef struct rolloI_256_secretKey {
	rbc_97_vspace F;
	rbc_97_qre x;
	rbc_97_qre y;
} rolloI_256_secretKey;

typedef struct rolloI_256_publicKey {
	rbc_97_qre h;
} rolloI_256_publicKey;

typedef struct rolloI_256_ciphertext{
	rbc_97_qre syndrom;
} rolloI_256_ciphertext;

#endif
