
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
#include "katrng.h"
#include "api.h"

#include "poison.h"

#define MAX_MARKER_LEN 50

#define KAT_SUCCESS 0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR -3
#define KAT_CRYPTO_FAILURE -4

#define VERBOSE 0
#define REPEAT_NUM 100 // number of KAT tests
#define VAR_KEYGEN 1   // way of using keypairs for each signing (0: fixed, 1: random)

// if VERBOSE is true, .rsp file content is printed to the console
#if VERBOSE == 1
#define PRINT(fp, str, ...)          \
    fprintf(fp, str, ##__VA_ARGS__); \
    fprintf(stdout, str, ##__VA_ARGS__);
#define PRINTBSTR(fp, s, a, l) \
    fprintBstr(fp, s, a, l);   \
    fprintBstr(stdout, s, a, l)
#else
#define PRINT(fp, str, ...) \
    fprintf(fp, str, ##__VA_ARGS__);
#define PRINTBSTR(fp, s, a, l) \
    fprintBstr(fp, s, a, l);
#endif

char AlgName[] = "Solmae-512";

#define STR(x) STR_(x)
#define STR_(x) #x

/*
 * This main() is for KAT execution.
 * Another main() in main.c is for Solmae-512 internal execution.
 */
int main()
{
#ifdef ALGNAME
    // char *fn_req, *fn_rsp;
#else
    // file name
    // char fn_req[32], fn_rsp[32];
#endif
    // request and response files
    // FILE *fp_req, *fp_rsp;
    unsigned char *m, *sm, *m1;
    unsigned long long mlen, smlen, mlen1;
    int count;
    int done;
    int ret_val;

    /*
     * Temporary buffers made static to save space on constrained
     * systems (e.g. ARM Cortex M4).
     */
    static unsigned char seed[48];
    static unsigned char entropy_input[48];

    // == Fixed Input Msg ===
    // static unsigned char msg[/*3300*/ 32] = {0x46, 0xb6, 0xc4, 0x83, 0x3f, 0x61, 0xfa, 0x3e, 0xaa, 0xe9, 0xad, 0x4a, 0x68, 0x8c, 0xd9, 0x6e, 0x22, 0x6d, 0x93, 0x3e, 0xde, 0xc4, 0x64, 0x9a, 0xb2, 0x18, 0x45, 0x2, 0xad, 0xf3, 0xc, 0x61};

    static unsigned char msg[33 * REPEAT_NUM];
    // static unsigned char msg[/*3300*/ 32] = {0x0,};
    // static unsigned char msg[/*3300*/ 32] = {0xf,};
    // static unsigned char msg[/*3300*/ 32] = {0x1,};

    static unsigned char pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];

    // Represent keygen mode

    printf("Way of using keypairs: %s\n", VAR_KEYGEN ? "variable" : "fixed");


    // Initialization for random input values using entropy_input (by kj
    // check i++ or ++i later
    for (int i = 0; i < 48; i++)
        entropy_input[i] = i;
    randombytes_init(entropy_input, NULL, 256);

// printf("/n Intialization of Random Inputs Completed !! \n");

// Fixed keygen
#if VAR_KEYGEN == 0
    if ((ret_val = crypto_sign_keypair(pk, sk)) != 0)
    {
        printf("crypto_sign_keypair returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }
#endif

    // print message, pk, sk, and signature to .req file
    for (int i = 0; i < REPEAT_NUM; i++)
    {
        random_bytes(seed, 48);
        
        mlen = 33 * (i + 1);
        // mlen = 32;
        
        random_bytes(msg, mlen);
    }

    // printf("/n Intialization of Request file completed !! \n");

    
        

        randombytes_init(entropy_input, NULL, 256);


        m = (unsigned char *)calloc(mlen, sizeof(unsigned char));
        m1 = (unsigned char *)calloc(mlen, sizeof(unsigned char));
        sm = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));

        // backup copy m to m1
        mlen1 = mlen;
        memcpy(m1, m, mlen);

// Generate the public/private keypair
// Variable keygen
#if VAR_KEYGEN == 1
        if ((ret_val = crypto_sign_keypair(pk, sk)) != 0)
        {
            printf("crypto_sign_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        printf("crypto_sign_keypair finished\n");
#endif

    // printf("\n Printing coded pk & sk print response file completed !! \n");
    // printf("msg to be signed =");
    // for (int i = 0; i < MSG_BYTES; i++)
    //    printf("%d", msg[i]);
    // printf("\n printing msg completed !!\n");

    //todo poison sk
    poison(sk, CRYPTO_SECRETKEYBYTES);

    if ((ret_val = crypto_sign(sm, &smlen, m, mlen, sk)) != 0)
    {
        printf("crypto_sign returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }
    printf("crypto_sign finished\n");

    // printf("\n Printing smlen and sm completed !! \n");

    if ((ret_val = crypto_sign_open(m, &mlen, sm, smlen, pk)) != 0)
    {
        printf("crypto_sign_open returned <%d>\n", ret_val);
        return KAT_CRYPTO_FAILURE;
    }

    // printf("\n Printing crypto_sign_open completed !! \n");

    if (mlen != mlen1)
    {
        printf("crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n", mlen1, mlen);
        return KAT_CRYPTO_FAILURE;
    }

    if (memcmp(m, m1, mlen))
    {
        printf("crypto_sign_open returned bad 'm' value\n");
        return KAT_CRYPTO_FAILURE;
    }
    printf("crypto_sign_open finished\n");

    free(m);
    free(m1);
    free(sm);

    return KAT_SUCCESS;
}

