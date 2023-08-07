/** 
 * \file biix_128_types.h
 * \brief File defining publicKey, secretKey and cipherText types for ROLLO-I
 */

#ifndef BIIX_128_TYPES_H
#define BIIX_128_TYPES_H

#include "rbc_67_qre.h"
#include "rbc_67_vspace.h"

// Additional part for permutation matrix
// Later, substituted for the better performance

//#include <vector> // Not supported as in C

typedef struct biix_128_secretKey {
	rbc_67_vspace F;
	rbc_67_qre x;
	rbc_67_qre y;
	// Additional part
	// std::vector<int> P
	
} biix_128_secretKey;

// C: Acutally, Not a PK, rather, indeterminated set of sub-PKs for string-like values 

typedef struct biix_128_publicKey {
	rbc_67_qre h;
} biix_128_publicKey;

typedef struct biix_128_ciphertext{
	rbc_67_qre syndrom;
} biix_128_ciphertext;

//

typedef struct biix_128_errgen{
	rbc_67_qre Err;
	rbc_67_vspace E;
} biix_128_errgen;


#endif
