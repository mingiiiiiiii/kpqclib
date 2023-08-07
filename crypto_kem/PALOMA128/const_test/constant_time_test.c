/*
NIST-developed software is provided by NIST as a public service. You may use, copy, and distribute copies of the software in any medium, provided that you keep intact this entire notice. You may improve, modify, and create derivative works of the software or any portion of the software, and you may copy and distribute such modifications or works. Modified works should carry a notice stating that you changed the software and should note the date and nature of any such change. Please explicitly acknowledge the National Institute of Standards and Technology as the source of the software.
 
NIST-developed software is expressly provided "AS IS." NIST MAKES NO WARRANTY OF ANY KIND, EXPRESS, IMPLIED, IN FACT, OR ARISING BY OPERATION OF LAW, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND DATA ACCURACY. NIST NEITHER REPRESENTS NOR WARRANTS THAT THE OPERATION OF THE SOFTWARE WILL BE UNINTERRUPTED OR ERROR-FREE, OR THAT ANY DEFECTS WILL BE CORRECTED. NIST DOES NOT WARRANT OR MAKE ANY REPRESENTATIONS REGARDING THE USE OF THE SOFTWARE OR THE RESULTS THEREOF, INCLUDING BUT NOT LIMITED TO THE CORRECTNESS, ACCURACY, RELIABILITY, OR USEFULNESS OF THE SOFTWARE.
 
You are solely responsible for determining the appropriateness of using and distributing the software and you assume all risks associated with its use, including but not limited to the risks and costs of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and the unavailability or interruption of operation. This software is not intended to be used in any situation where a failure could cause risk of injury or damage to property. The software developed by NIST employees is not subject to copyright protection within the United States.
*/

// gcc -Wl,-stack_size -Wl,0x20000000 -O2 gf_table_gen.c gf.c gfpoly.c goppa_instance.c keygen.c mat_mul.c common.c lsh.c lsh512.c encap.c decap.c paloma.c rng.c kat.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rng.h"
#include "api.h"
#include "gf_table_gen.h"

#include "poison.h"

#define	MAX_MARKER_LEN		50
#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

#define MAX_CRYPTO_PUBLICKEYBYTES   1025024
#define MAX_CRYPTO_SECRETKEYBYTES   357064
#define MAX_CRYPTO_CIPHERTEXTBYTES  240
#define MAX_CRYPTO_BYTES            32

/* flag */
// PALOMA1 > 1
// PALOMA2 > 2
// PALOMA3 > 3
// #define flag           2      

int
main()
{
    unsigned char       seed[48];
    unsigned char       entropy_input[48];
    unsigned char       ct[MAX_CRYPTO_CIPHERTEXTBYTES]={0,}, ss[MAX_CRYPTO_BYTES]={0,}, ss1[MAX_CRYPTO_BYTES]={0,};
    int                 count;
    int                 done;
    unsigned char       pk[MAX_CRYPTO_PUBLICKEYBYTES]={0,}, sk[MAX_CRYPTO_SECRETKEYBYTES]={0,};
    int                 ret_val;
    int                 freturn;
    // int                 CRYPTO_CIPHERTEXTBYTES, CRYPTO_BYTES, CRYPTO_PUBLICKEYBYTES, CRYPTO_SECRETKEYBYTES;

    int n,t,k;
    PARAM PALOMAParam;
    int flag;

    #ifdef PALOMA_MODE
        #if PALOMA_MODE == 1
        t = 64;     
        n = 3904;   
        k = (n-(13*t));
        flag = 1;

        #elif PALOMA_MODE == 3
        t = 128;     
        n = 5568;   
        k = (n-(13*t));    
        flag = 2;

        #elif PALOMA_MODE == 5
        t = 128;     
        n = 6592;   
        k = (n-(13*t));  
        flag = 3;
        #endif
    #endif

    GF_init(&PALOMAParam, n, k, t);  
    
    for (int i=0; i<48; i++){
        entropy_input[i] = i;
    }

    randombytes_init(entropy_input, NULL, 256);       

    for (int i=0; i<100; i++) {
        randombytes(seed, 48);                              
    }
    
    randombytes_init(seed, NULL, 256);                              

    // Generate the public/private keypair
    crypto_PALOMA_keypair(pk, sk, &PALOMAParam);
    printf("crypto_kem_keypair finished\n");
    
    ret_val = crypto_PALOMA_enc(ct, ss, pk,&PALOMAParam);
    printf("crypto_kem_enc finished\n");

    //todo poison sk
    poison(sk, MAX_CRYPTO_SECRETKEYBYTES);
    
    crypto_PALOMA_dec(ss1, ct, sk,&PALOMAParam);             //수정해야함.
    printf("crypto_kem_dec finished\n");

    // return KAT_SUCCESS;
    return 0;
}



