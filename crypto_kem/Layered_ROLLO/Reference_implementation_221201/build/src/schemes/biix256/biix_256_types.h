/** 
 * \file biix_256_types.h
 * \brief File defining publicKey, secretKey and cipherText types for ROLLO-I
 */

#ifndef BIIX_256_TYPES_H
#define BIIX_256_TYPES_H

#include "rbc_97_qre.h"
#include "rbc_97_vspace.h"

// Additional part for permutation matrix
// Later, substituted for the better performance

//#include <vector> // Not supported as in C

typedef struct biix_256_secretKey {
	rbc_97_vspace F;
	rbc_97_qre x;
	rbc_97_qre y;
	// Additional part
	// std::vector<int> P
	
} biix_256_secretKey;

// C: Acutally, Not a PK, rather, indeterminated set of sub-PKs for string-like values 

typedef struct biix_256_publicKey {
	rbc_97_qre h;
} biix_256_publicKey;

typedef struct biix_256_ciphertext{
	rbc_97_qre syndrom;
} biix_256_ciphertext;

//

typedef struct biix_256_errgen{
	rbc_97_qre Err;
	rbc_97_vspace E;
} biix_256_errgen;


#endif
