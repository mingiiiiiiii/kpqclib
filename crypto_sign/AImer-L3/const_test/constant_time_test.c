/*
NIST-developed software is provided by NIST as a public service. You may use, copy, and distribute copies of the software in any medium, provided that you keep intact this entire notice. You may improve, modify, and create derivative works of the software or any portion of the software, and you may copy and distribute such modifications or works. Modified works should carry a notice stating that you changed the software and should note the date and nature of any such change. Please explicitly acknowledge the National Institute of Standards and Technology as the source of the software.
 
NIST-developed software is expressly provided "AS IS." NIST MAKES NO WARRANTY OF ANY KIND, EXPRESS, IMPLIED, IN FACT, OR ARISING BY OPERATION OF LAW, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND DATA ACCURACY. NIST NEITHER REPRESENTS NOR WARRANTS THAT THE OPERATION OF THE SOFTWARE WILL BE UNINTERRUPTED OR ERROR-FREE, OR THAT ANY DEFECTS WILL BE CORRECTED. NIST DOES NOT WARRANT OR MAKE ANY REPRESENTATIONS REGARDING THE USE OF THE SOFTWARE OR THE RESULTS THEREOF, INCLUDING BUT NOT LIMITED TO THE CORRECTNESS, ACCURACY, RELIABILITY, OR USEFULNESS OF THE SOFTWARE.
 
You are solely responsible for determining the appropriateness of using and distributing the software and you assume all risks associated with its use, including but not limited to the risks and costs of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and the unavailability or interruption of operation. This software is not intended to be used in any situation where a failure could cause risk of injury or damage to property. The software developed by NIST employees is not subject to copyright protection within the United States.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rng.h"
#include "api.h"

#include "poison.h"

#define	MAX_MARKER_LEN		50

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

char    AlgName[] = "My Alg Name";

int
main()
{
    
    unsigned char       seed[48];
    unsigned char       msg[3300];
    unsigned char       entropy_input[48];
    unsigned char       *m, *sm, *m1;
    unsigned long long  mlen, smlen, mlen1;
    int                 count;
    int                 done;
    unsigned char       pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
    int                 ret_val;
    
    for (int i=0; i<48; i++)
        entropy_input[i] = i;

    randombytes_init(entropy_input, NULL, 256);
    
    for (int i=0; i<100; i++) {
        
        randombytes(seed, 48);
        
        mlen = 33*(i+1);
        
        randombytes(msg, mlen);
        
    }

    randombytes_init(seed, NULL, 256);
    
    m = (unsigned char *)calloc(mlen, sizeof(unsigned char));
    m1 = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));
    sm = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));
    
    
    // Generate the public/private keypair
    if ( (ret_val = kat_crypto_sign_keypair(pk, sk)) != 0) {
        printf("crypto_sign_keypair returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }
    printf("crypto_sign_keypair finished\n");
    
    //todo poison sk
    poison(sk, CRYPTO_SECRETKEYBYTES);

    if ( (ret_val = kat_crypto_sign(sm, &smlen, m, mlen, sk)) != 0) {
        printf("crypto_sign returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }
    printf("crypto_sign finished\n");


    // unpoison(sk, CRYPTO_SECRETKEYBYTES);
    
    if ( (ret_val = kat_crypto_sign_open(m1, &mlen1, sm, smlen, pk)) != 0) {
        printf("crypto_sign_open returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }

    if ( mlen != mlen1 ) {
        printf("crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n", mlen1, mlen);
        return KAT_CRYPTO_FAILURE;
    }
    
    if ( memcmp(m, m1, mlen) ) {
        printf("crypto_sign_open returned bad 'm' value\n");
        return KAT_CRYPTO_FAILURE;
    }
    printf("crypto_sign_open finished\n");
    
    free(m);
    free(m1);
    free(sm);

    // return KAT_SUCCESS;
    return 0;
}

