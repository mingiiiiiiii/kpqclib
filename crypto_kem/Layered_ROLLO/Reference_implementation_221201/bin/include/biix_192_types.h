/** 
 * \file biix_192_types.h
 * \brief File defining publicKey, secretKey and cipherText types for ROLLO-I
 */

#ifndef BIIX_192_TYPES_H
#define BIIX_192_TYPES_H

#include "rbc_79_qre.h"
#include "rbc_79_vspace.h"

// Additional part for permutation matrix
// Later, substituted for the better performance

//#include <vector> // Not supported as in C

typedef struct biix_192_secretKey {
	rbc_79_vspace F;
	rbc_79_qre x;
	rbc_79_qre y;
	// Additional part
	// std::vector<int> P
	
} biix_192_secretKey;

// C: Acutally, Not a PK, rather, indeterminated set of sub-PKs for string-like values 

typedef struct biix_192_publicKey {
	rbc_79_qre h;
} biix_192_publicKey;

typedef struct biix_192_ciphertext{
	rbc_79_qre syndrom;
} biix_192_ciphertext;

//

typedef struct biix_192_errgen{
	rbc_79_qre Err;
	rbc_79_vspace E;
} biix_192_errgen;


#endif
