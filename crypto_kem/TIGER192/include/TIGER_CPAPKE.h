#include <stdint.h>
#include "params.h"


void Keygen(unsigned char *pk, unsigned char *sk);

void Encryption(unsigned char *c, const unsigned char *pk, unsigned char *Message, unsigned char *coin);

void Decryption(unsigned char *Message, const unsigned char *c, const unsigned char *sk);


