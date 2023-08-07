// clang-format off
#ifndef HAETAE_PARAMS_H
#define HAETAE_PARAMS_H

#include "config.h"

#define SEEDBYTES 32
#define CRHBYTES 64
#define N 256
#define ROOT_OF_UNITY 3

#define Q 64513
#define DQ (Q << 1)// 2Q

#if HAETAE_MODE == 2
#define K 2
#define L 4
#define ETA 1
#define TAU 39
#define B0 9779.3229
#define B1 9774.9271
#define B2 11197.4229
#define ALPHA 256
#define HALF_ALPHA (ALPHA >> 1) // ALPHA / 2
#define GAMMA 47

#define POLYB1_PACKEDBYTES 480     // 15bits * N / 8bits

#elif HAETAE_MODE == 3
#define K 3
#define L 6
#define ETA 1
#define TAU 49
#define B0 15709.1546
#define B1 15704.4361
#define B2 17973.1740
#define ALPHA 324
#define HALF_ALPHA (ALPHA >> 1) // ALPHA / 2
#define GAMMA 55

#define POLYB1_PACKEDBYTES 480     // 15bits * N / 8bits

#elif HAETAE_MODE == 5
#define K 4
#define L 7
#define ETA 1
#define TAU 60
#define B0 20614.9815
#define B1 20609.9152
#define B2 23740.4482
#define ALPHA 384
#define HALF_ALPHA (ALPHA >> 1) // ALPHA / 2
#define GAMMA 59

#define POLYB1_PACKEDBYTES 512     // 16bits * N / 8bits

#endif

#define POLYQ_PACKEDBYTES 512  // 16bits * N / 8bits
#define POLY2Q_PACKEDBYTES 544 // 17bits * N / 8bits


#if ETA == 1
#define POLYETA_PACKEDBYTES 64
#elif ETA == 2
#define POLYETA_PACKEDBYTES 96
#endif

#define POLYC_PACKEDBYTES 32       // 1bit * N / 8bits
#define POLYVECK_BYTES (K * N * sizeof(int32_t))
#define POLYVECL_BYTES (L * N * sizeof(int32_t))

#define CRYPTO_PUBLICKEYBYTES (SEEDBYTES + K * POLY2Q_PACKEDBYTES)                                      // seed + b         1056/1568/2080 bytes
#define CRYPTO_SECRETKEYBYTES (CRYPTO_PUBLICKEYBYTES + (K + L) * POLYETA_PACKEDBYTES + SEEDBYTES)       // pk + s + K       1472/2112/2816 bytes
#define CRYPTO_BYTES (SEEDBYTES + L * POLYB1_PACKEDBYTES + K * POLY2Q_PACKEDBYTES)                      // c_seed + z1 + h  3040/4064/5792 bytes

#endif
// clang-format on