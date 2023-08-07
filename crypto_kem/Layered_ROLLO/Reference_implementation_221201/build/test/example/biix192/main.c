
#include <stdio.h>
#include "rbc.h"

#define VERBOSE

static long long cpucycles() {
  unsigned long long result;
  __asm__ volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax" : "=a" (result) ::  "%rdx");
  return result;
}

int main() {

  unsigned char pk[BIIX_192_PUBLIC_KEY_BYTES] = {0};
  unsigned char sk[BIIX_192_SECRET_KEY_BYTES] = {0};
  unsigned char ct[BIIX_192_CIPHERTEXT_BYTES] = {0};
  unsigned char ss1[BIIX_192_SHARED_SECRET_BYTES] = {0};
  unsigned char ss2[BIIX_192_SHARED_SECRET_BYTES] = {0};
  unsigned char ss3[BIIX_192_SHARED_SECRET_BYTES] = {0};

  long long t1 = cpucycles();
  biix_192_keygen(pk, sk);
  long long t2 = cpucycles();


  long long t3 = cpucycles();
  biix_192_encaps(ct, ss1, pk);
  long long t4 = cpucycles();
 
  long long t5 = cpucycles();
  biix_192_decaps(ss2, ct, sk);
  long long t6 = cpucycles();
  

  printf("\nKeygen: %lld CPU cycles", t2 - t1);
  
  printf("\nEncaps: %lld CPU cycles", t4 - t3);
  
  printf("\nDecaps: %lld CPU cycles", t6 - t5);

  printf("\n\nsecret1: ");
  for(int i = 0 ; i < BIIX_192_SHARED_SECRET_BYTES ; ++i) printf("%02x", ss1[i]);

  printf("\nsecret2: ");
  for(int i = 0 ; i < BIIX_192_SHARED_SECRET_BYTES ; ++i) printf("%02x", ss2[i]);
  printf("\n\n");
  
  
  // metamorphic 
  memset(pk, 0, BIIX_192_PUBLIC_KEY_BYTES);
  memset(sk, 0, BIIX_192_SECRET_KEY_BYTES);
  memset(ct, 0, BIIX_192_CIPHERTEXT_BYTES);
  memset(ss1, 0, BIIX_192_SHARED_SECRET_BYTES);
  memset(ss2, 0, BIIX_192_SHARED_SECRET_BYTES);


  biix_192_keygen(pk, sk);
  biix_192_encaps(ct, ss1, pk);

  uint8_t* buf = (uint8_t*)calloc(BIIX_192_SECRET_KEY_BYTES, sizeof(uint8_t));
  int res_bct = 1;
  for(int i = 0; i < BIIX_192_SECRET_KEY_BYTES; i++){
    memcpy(buf, sk, BIIX_192_SECRET_KEY_BYTES);

    buf[i/8] ^= 1 << (i % 8); //! change sk

    //? relation : if pk changed, then recovered ss is different?
    biix_192_decaps(ss2, ct, sk); //ss1
    biix_192_decaps(ss3, ct, buf); //ss2
    
    if(memcmp(ss3, ss2, BIIX_192_SHARED_SECRET_BYTES) != 0){
      continue;
    } else {
      printf("biix_192_128 Bit Contribution Test Fail: Failed on sk\n");
      res_bct = 0;
      break;
    }
  }

  free(buf);
  buf = (uint8_t*)calloc(BIIX_192_CIPHERTEXT_BYTES, sizeof(uint8_t));
  for(int i = 0; i < BIIX_192_CIPHERTEXT_BYTES; i++){
    memcpy(buf, ct, BIIX_192_CIPHERTEXT_BYTES);

    buf[i/8] ^= 1 << (i % 8);

    biix_192_decaps(ss2,  ct, sk);
    biix_192_decaps(ss3, buf, sk);

    if(memcmp(ss3, ss2, BIIX_192_SHARED_SECRET_BYTES) != 0){
        continue;
    } else {
      printf("biix_192_128 Bit Contribution Test Fail: Failed on ct\n");
      res_bct = 0;
      break;
    }
  }
  if(res_bct){
    printf("biix_192_128 Bit Contribution Test Success\n");
  }

  free(buf);
  buf = (uint8_t*)calloc(BIIX_192_SECRET_KEY_BYTES, sizeof(uint8_t));
  int res_bet = 1;
  for(int i = 0; i < BIIX_192_SECRET_KEY_BYTES; i++){
    memcpy(buf, sk, BIIX_192_SECRET_KEY_BYTES);

    buf[i/8] ^= 1 << (i % 8);

    biix_192_decaps(ss2, ct, sk);
    biix_192_decaps(ss3, ct, buf);

    if(memcmp(ss3, ss2, BIIX_192_SHARED_SECRET_BYTES) == 0){
        continue;
    } else {
      printf("biix_192_128 Bit Exclusion Test Fail: Failed on sk\n");
      res_bet = 0;
      break;
    }
  }  

  free(buf);
  buf = (uint8_t*)calloc(BIIX_192_CIPHERTEXT_BYTES, sizeof(uint8_t));
  for(int i = 0; i < BIIX_192_CIPHERTEXT_BYTES; i++){
    memcpy(buf, ct, BIIX_192_CIPHERTEXT_BYTES);

    buf[i/8] ^= 1 << (i % 8);

    biix_192_decaps(ss2, ct,  sk);
    biix_192_decaps(ss3, buf, sk);

    if(memcmp(ss3, ss2, BIIX_192_SHARED_SECRET_BYTES) == 0){
        continue;
    } else {
      printf("biix_192_128 Bit Exclusion Test Fail: Failed on ct\n");
      res_bet = 0;
      break;
    }
  }  
  free(buf);
  if(res_bet){
    printf("biix_192_128 Bit Exclusion Test Success\n");
  }
}

