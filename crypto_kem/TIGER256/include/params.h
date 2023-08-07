#ifndef TIGER_PARAMETERS_H
#define TIGER_PARAMETERS_H

#if TIGER_MODE == 1
#define PARAMNAME "TIGER128"
#define LWE_N 512		// LWE dim and LWR dim
#define LOG_N 9
#define LOG_Q 8
#define Modulus_Q 256
#define LOG_P 7
#define LOG_K_1 6
#define LOG_K_2 6
#define HR 160			// Hamming weight of coefficient vector r
#define HS 160			// Hamming weight of coefficient vector s
#define HE 32
#define SEED_LEN 32
#define KK_LEN 16
#define size_of_delta 16

#define PUBLICKEYSIZE 32+LWE_N 
#define SECRETKEYSIZE LWE_N+MESSAGE_LEN 
#define CIPHERTEXTSIZE LWE_N*2 

#define MESSAGE_LEN 16
#define _8_LOG_T 7
#define sft (sizeof(size_t) * 4 - 1)


#elif TIGER_MODE == 3
#define PARAMNAME "TIGER192"
#define LWE_N 1024		// LWE dim and LWR dim
#define LOG_N 10
#define LOG_Q 8
#define Modulus_Q 256
#define LOG_P 6
#define LOG_K_1 6
#define LOG_K_2 2
#define HR 84			// Hamming weight of coefficient vector r
#define HS 84			// Hamming weight of coefficient vector s
#define HE 84
#define SEED_LEN 32
#define KK_LEN 32
#define size_of_delta 32

#define PUBLICKEYSIZE 32+LWE_N 
#define SECRETKEYSIZE LWE_N+MESSAGE_LEN 
#define CIPHERTEXTSIZE LWE_N*2 

#define MESSAGE_LEN 32
#define _8_LOG_T 7
#define sft (sizeof(size_t) * 4 - 1)



#elif TIGER_MODE == 5

#define PARAMNAME "TIGER256"
#define LWE_N 1024		// LWE dim and LWR dim
#define LOG_N 10
#define LOG_Q 8
#define Modulus_Q 256
#define LOG_P 7
#define LOG_K_1 7
#define LOG_K_2 3
#define HR 164			// Hamming weight of coefficient vector r
#define HS 198			// Hamming weight of coefficient vector s
#define HE 610
#define SEED_LEN 32
#define KK_LEN 32
#define size_of_delta 32

#define PUBLICKEYSIZE 32+LWE_N 
#define SECRETKEYSIZE LWE_N+MESSAGE_LEN 
#define CIPHERTEXTSIZE LWE_N*2 

#define MESSAGE_LEN 32
#define _8_LOG_T 7
#define sft (sizeof(size_t) * 4 - 1)




#endif
#endif // SMAUG_PARAMETERS_H
