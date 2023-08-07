
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

#define MAX_MARKER_LEN 50

#define KAT_SUCCESS 0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR -3
#define KAT_CRYPTO_FAILURE -4

#define VERBOSE 0
#define REPEAT_NUM 100 // number of KAT tests
#define VAR_KEYGEN 0   // way of using keypairs for each signing (0: fixed, 1: random)

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

// ft() to find marker in a file
int FindMarker(FILE *infile, const char *marker);
// ft() to read hexacode
int ReadHex(FILE *infile, unsigned char *A, int Length, char *str);
// ft() to print binary string
void fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L);

char AlgName[] = "Solmae-1024";

#define STR(x) STR_(x)
#define STR_(x) #x

/*
 * This main() is for KAT execution.
 * Another main() in main.c is for Solmae-1024 internal execution.
 */
int main()
{
#ifdef ALGNAME
    char *fn_req, *fn_rsp;
#else
    // file name
    char fn_req[32], fn_rsp[32];
#endif
    // request and response files
    FILE *fp_req, *fp_rsp;
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

// Create the REQUEST file
#ifdef ALGNAME
    fn_req = "PQCsignKAT_" STR(ALGNAME) ".req";
#else
    sprintf(fn_req, "PQCsignKAT_%d.req", CRYPTO_SECRETKEYBYTES);
#endif
    if ((fp_req = fopen(fn_req, "w")) == NULL)
    {
        printf("Couldn't open <%s> for write\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
#ifdef ALGNAME
    fn_rsp = "PQCsignKAT_" STR(ALGNAME) ".rsp";
#else
    sprintf(fn_rsp, "PQCsignKAT_%d.rsp", CRYPTO_SECRETKEYBYTES);
#endif
    if ((fp_rsp = fopen(fn_rsp, "w")) == NULL)
    {
        printf("Couldn't open <%s> for write\n", fn_rsp);
        return KAT_FILE_OPEN_ERROR;
    }

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
        PRINT(fp_req, "count = %d\n", i);
        random_bytes(seed, 48);
        PRINTBSTR(fp_req, "seed = ", seed, 48);
        mlen = 33 * (i + 1);
        // mlen = 32;
        PRINT(fp_req, "mlen = %llu\n", mlen);
        random_bytes(msg, mlen);
        PRINTBSTR(fp_req, "msg = ", msg, mlen);
        // pk: public key, sk: secret key
        PRINT(fp_req, "pk =\n");
        PRINT(fp_req, "sk =\n");
        // sm: signed message
        PRINT(fp_req, "smlen =\n");
        PRINT(fp_req, "sm =\n\n");
    }
    fclose(fp_req);

    // printf("/n Intialization of Request file completed !! \n");

    // Create the RESPONSE file based on what's in the REQUEST file
    if ((fp_req = fopen(fn_req, "r")) == NULL)
    {
        printf("Couldn't open <%s> for read\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }

    PRINT(fp_rsp, "# %s\n\n", CRYPTO_ALGNAME);
    done = 0;
    do
    {
        if (FindMarker(fp_req, "count = "))
        {
            if (fscanf(fp_req, "%d", &count) != 1)
            {
                abort();
            }
        }
        else
        {
            done = 1;
            break;
        }
        PRINT(fp_rsp, "count = %d\n", count);
        printf("\n count= %d\n", count);

        if (!ReadHex(fp_req, seed, 48, "seed = "))
        {
            printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        // request file seed into 48 bytes hex code
        PRINTBSTR(fp_rsp, "seed = ", seed, 48);

        randombytes_init(entropy_input, NULL, 256);

        if (FindMarker(fp_req, "mlen = "))
        {
            if (fscanf(fp_req, "%llu", &mlen) != 1)
            {
                abort();
            }
        }
        else
        {
            printf("ERROR: unable to read 'mlen' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        // initial message length
        PRINT(fp_rsp, "mlen = %llu\n", mlen);

        m = (unsigned char *)calloc(mlen, sizeof(unsigned char));
        m1 = (unsigned char *)calloc(mlen, sizeof(unsigned char));
        sm = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));

        if (!ReadHex(fp_req, m, (int)mlen, "msg = "))
        {
            printf("ERROR: unable to read 'msg' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        PRINTBSTR(fp_rsp, "msg = ", m, mlen);

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
#endif
        // output generated pk and sk
        PRINTBSTR(fp_rsp, "pk = ", pk, CRYPTO_PUBLICKEYBYTES);
        PRINTBSTR(fp_rsp, "sk = ", sk, CRYPTO_SECRETKEYBYTES);

        // printf("\n Printing coded pk & sk print response file completed !! \n");
        // printf("msg to be signed =");
        // for (int i = 0; i < MSG_BYTES; i++)
        //    printf("%d", msg[i]);
        // printf("\n printing msg completed !!\n");

        if ((ret_val = crypto_sign(sm, &smlen, m, mlen, sk)) != 0)
        {
            printf("crypto_sign returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        // printf("\n Crypto_signing completed !! \n");
        // print signature and its length to .rsp file
        PRINT(fp_rsp, "smlen = %llu\n", smlen);
        PRINTBSTR(fp_rsp, "sm = ", sm, smlen);
        PRINT(fp_rsp, "\n");

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

        free(m);
        free(m1);
        free(sm);

    } while (!done);

    fclose(fp_req);
    fclose(fp_rsp);

    return KAT_SUCCESS;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int FindMarker(FILE *infile, const char *marker)
{
    char line[MAX_MARKER_LEN];
    int i, len;
    int curr_line;

    // limit maximum marker length to MAX_MARKER_LEN
    len = (int)strlen(marker);
    if (len > MAX_MARKER_LEN - 1)
        len = MAX_MARKER_LEN - 1;

    for (i = 0; i < len; i++)
    {
        curr_line = fgetc(infile);
        line[i] = curr_line;
        if (curr_line == EOF)
            return 0;
    }
    line[len] = '\0';

    // finding the marker by shifting left
    while (1)
    {
        if (!strncmp(line, marker, len))
            return 1;

        for (i = 0; i < len - 1; i++)
            line[i] = line[i + 1];
        curr_line = fgetc(infile);
        line[len - 1] = curr_line;
        if (curr_line == EOF)
            return 0;
        line[len] = '\0';
    }

    // shouldn't get here
    return 0;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int ReadHex(FILE *infile, unsigned char *A, int Length, char *str)
{
    int i, ch, started;
    unsigned char ich;

    if (Length == 0)
    {
        A[0] = 0x00;
        return 1;
    }
    memset(A, 0x00, Length);
    started = 0;
    // read hex code right after detecting marker
    if (FindMarker(infile, str))
        while ((ch = fgetc(infile)) != EOF)
        {
            if (!isxdigit(ch))
            {
                if (!started)
                {
                    if (ch == '\n')
                        break;
                    else
                        continue;
                }
                else
                    break;
            }
            started = 1;
            if ((ch >= '0') && (ch <= '9'))
                ich = ch - '0';
            else if ((ch >= 'A') && (ch <= 'F'))
                ich = ch - 'A' + 10;
            else if ((ch >= 'a') && (ch <= 'f'))
                ich = ch - 'a' + 10;
            else // shouldn't ever get here
                ich = 0;
            // concatenate 4 bytes per character read
            for (i = 0; i < Length - 1; i++)
                A[i] = (A[i] << 4) | (A[i + 1] >> 4);
            A[Length - 1] = (A[Length - 1] << 4) | ich;
        }
    else
        return 0;

    return 1;
}
// output A value through hex code
void fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L)
{
    unsigned long long i;

    fprintf(fp, "%s", S);

    for (i = 0; i < L; i++)
        fprintf(fp, "%02X", A[i]);

    if (L == 0)
        fprintf(fp, "00");

    fprintf(fp, "\n");
}
