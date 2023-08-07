#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aimer.h"

#define BUF_BYTES (1)
// #define Iterations (1000000)
#define Iterations (200)

uint8_t print_flag = 1;

int sign_verify_test(void);

int main(void) {
    printf("AIMer mode = %d\n", AIMER_MODE);
    size_t count = 1;
    for (int i = 0; i < Iterations; ++i) {
        if (sign_verify_test()) {
            printf("Invalid on %d-th test\n", i);
            break;
        }

        if (!(i % (Iterations / 10))) {
            printf("...%lu%%", count * 10);
            fflush(stdout);
            ++count;
        }
    }
    printf("\n");

    return 0;
}

int sign_verify_test(void) {
    if (print_flag) {
        printf(">> sign and verify test\n");
        print_flag = 0;
    }
  int ret = 0;
  const char *message = "TestMessage";

  aimer_publickey_t  public_key;
  aimer_privatekey_t private_key;
  uint8_t* signature = malloc(AIMER_MAX_SIGNATURE_SIZE);
  size_t  signature_len = 0;
  int param = 0;

#if   (AIMER_MODE == 1)
  param = AIMER_L1_PARAM1;
#elif (AIMER_MODE == 3)
  param = AIMER_L3_PARAM1;
#elif (AIMER_MODE == 5)
  param = AIMER_L5_PARAM1;
#endif


    ret = aimer_keygen(param++, &public_key, &private_key);
    ret = aimer_sign(&public_key, &private_key, (const uint8_t*)message,
                   strlen(message), signature, &signature_len);
    ret = aimer_verify(&public_key, signature, signature_len,
                      (const uint8_t*)message, strlen(message));
    if(ret==0){
        return 0;
    }                
    {
        return 1;
    }

    free(signature);
    return ret;
}
