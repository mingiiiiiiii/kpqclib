#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "api.h"
#include "poly.h"
#include "test_dist.h"

#include "precomp.h"
#include "normaldist.h"
#include "samplerZ.h"
#include "randombytes.h"

#define PRINT_SIZE 8
#define REPEAT 10



void speed()
{
  secret_key sk;
  public_key pk;
  signature s;
  precomp(&sk);
  load_pk(&pk);

  uint8_t m[32] = {0x46, 0xb6, 0xc4, 0x83, 0x3f, 0x61, 0xfa, 0x3e, 0xaa, 0xe9, 0xad, 0x4a, 0x68, 0x8c, 0xd9, 0x6e, 0x22, 0x6d, 0x93, 0x3e, 0xde, 0xc4, 0x64, 0x9a, 0xb2, 0x18, 0x45, 0x2, 0xad, 0xf3, 0xc, 0x61};
  
  sign(m, &sk, &s);
  printf("Sign Generate Completed\n");
  // printf("Sign: ");
}

void speed_keygen()
{
  secret_key sk;
  public_key pk;

  keygen_full(&sk, &pk);

}

int main()
{
  srand(time(0));
  seed_rng();
  printf("Hello world, signature is SOLMAE-%u\n", SOLMAE_D);
  secret_key sk;
  public_key pk;
  signature s;

  // uint8_t m[32] = {0x46, 0xb6, 0xc4, 0x83, 0x3f, 0x61, 0xfa, 0x3e, 0xaa, 0xe9, 0xad, 0x4a, 0x68, 0x8c, 0xd9, 0x6e, 0x22, 0x6d, 0x93, 0x3e, 0xde, 0xc4, 0x64, 0x9a, 0xb2, 0x18, 0x45, 0x2, 0xad, 0xf3, 0xc, 0x61};
  uint8_t m[32];

  for (int n = 0; n < REPEAT; n++)
  {
    printf("[trial %d]\n", n + 1);

    randombytes(m, 32);
    keygen_full(&sk, &pk);

    //print_sk(&sk);

    printf("message: ");
    for (int i = 0; i < 32; i++)
    {
      printf("%02x ", m[i]);
    }

    printf("\nSign.\n");
    sign(m, &sk, &s);

    printf("Verify: %i\n", verify(m, &pk, &s));
  }


  return 0;
}
