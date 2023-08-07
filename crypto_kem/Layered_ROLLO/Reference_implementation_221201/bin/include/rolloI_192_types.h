/** 
 * \file rolloI_192_types.h
 * \brief File defining publicKey, secretKey and cipherText types for ROLLO-I
 */

#ifndef ROLLOI_192_TYPES_H
#define ROLLOI_192_TYPES_H

#include "rbc_79_qre.h"
#include "rbc_79_vspace.h"

typedef struct rolloI_192_secretKey {
	rbc_79_vspace F;
	rbc_79_qre x;
	rbc_79_qre y;
} rolloI_192_secretKey;

typedef struct rolloI_192_publicKey {
	rbc_79_qre h;
} rolloI_192_publicKey;

typedef struct rolloI_192_ciphertext{
	rbc_79_qre syndrom;
} rolloI_192_ciphertext;

#endif
