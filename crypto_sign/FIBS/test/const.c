
//
//  PQCgenKAT_sign.c
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../api.h"
#include "../fors.h"
#include "../wots.h"
#include "../params.h"
#include "../rng.h"
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
    for (int i=0; i<50; i++) {
        
        randombytes(seed, 48);
        
        mlen = 33*(i+1);
        
        randombytes(msg, mlen);
        
    }
    

        randombytes_init(seed, NULL, 256);

        
        m = (unsigned char *)calloc(mlen, sizeof(unsigned char));
        m1 = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));
        sm = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));

        
        // Generate the public/private keypair
        if ( (ret_val = crypto_sign_keypair(pk, sk)) != 0) {
            printf("crypto_sign_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        printf("crypto_sign_keypair finished\n");

        //todo poison sk
        poison(sk, CRYPTO_SECRETKEYBYTES);
        
        if ( (ret_val = crypto_sign(sm, &smlen, m, mlen, sk)) != 0) {
            printf("crypto_sign returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        printf("crypto_sign finished\n");
        
        if ( (ret_val = crypto_sign_open(m1, &mlen1, sm, smlen, pk)) != 0) {
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

  

    return KAT_SUCCESS;
}

