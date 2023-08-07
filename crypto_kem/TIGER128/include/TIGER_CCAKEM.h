#include <stdint.h>
#include "params.h"
#include "TIGER_CPAPKE.h"


void KEM_Keygen(unsigned char *pk, unsigned char *sk);

void KEM_Enc(unsigned char *c, unsigned char *shared_k, const unsigned char *pk);

int KEM_dec(unsigned char *shared_k, const unsigned char *c, const unsigned char *sk, const unsigned char *pk);


