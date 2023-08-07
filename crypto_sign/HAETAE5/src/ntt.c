#include "ntt.h"
#include "params.h"
#include "reduce.h"
#include <stdint.h>

// TODO: different zetas / f according to Q

static const int32_t zetas[N] = {
    0,     1106,  1669,  -1638, -696,  2892,  253,   5517,  971,   -1704, 5562,
    4857,  2739,  -4389, 1388,  589,   2289,  5956,  810,   5957,  5052,  196,
    918,   5932,  5029,  3046,  -6048, 1400,  4061,  -3102, 519,   5683,  2304,
    3563,  10,    2501,  5069,  761,   -4085, 4473,  4917,  -2845, -4171, 169,
    657,   872,   1827,  -1447, 1074,  3165,  4165,  3246,  3675,  3587,  624,
    1221,  1812,  946,   1672,  2799,  -2862, -5482, 5172,  5630,  256,   -2335,
    2732,  -2453, 6025,  1450,  2277,  497,   -3550, -3047, 902,   -5443, 73,
    -2634, 203,   5301,  -3977, 4448,  -4999, 4457,  -3688, 1764,  -4027, 4232,
    -3895, 2836,  -5276, 311,   -318,  -3340, 4671,  1991,  -3842, -4800, 90,
    -2069, -3535, -5440, 102,   3390,  -4903, -1027, -672,  1521,  5913,  -4441,
    4154,  -734,  -2623, 3907,  618,   4636,  -3792, -4584, 5616,  -1300, 4019,
    -3775, 2759,  613,   -1180, -182,  -2608, 1514,  -4011, 3318,  5007,  -4914,
    -2088, -3613, 759,   4262,  2913,  -5112, 4397,  2282,  -4072, -878,  4164,
    1767,  -5422, 5579,  2430,  5582,  2867,  588,   2754,  5507,  2798,  -3151,
    -5855, 4200,  -106,  2983,  1557,  4760,  -5377, -1600, 30,    -4786, 2918,
    2283,  34,    1130,  2462,  3754,  -224,  507,   1971,  2616,  5481,  -4341,
    3222,  -2794, 206,   -2551, -1264, -1528, 1872,  3663,  5436,  2838,  5016,
    -3892, 3703,  -4157, 3227,  4601,  768,   5284,  -4093, 4930,  5786,  4350,
    -5458, 1491,  1639,  3148,  2706,  -4040, 219,   4387,  609,   3614,  358,
    1055,  -2708, 1082,  1225,  5292,  208,   407,   604,   -3781, -3539, 933,
    -954,  2269,  1724,  5973,  763,   -2111, 270,   6082,  1684,  -4031, 306,
    -2119, -2420, -3081, -2016, 4563,  5450,  -1034, 173,   -2202, 4420,  -568,
    1854,  1619,  913,   -1463, 4559,  -3900, -232,  964,   -4012, 1839,  -3540,
    -546,  4465,  4542}; // \zeta^1 = 3 , R = 2^32

/*************************************************
 * Name:        ntt
 *
 * Description: Forward NTT, in-place. No modular reduction is performed after
 *              additions or subtractions. Output vector is in bitreversed
 *order.
 *
 * Arguments:   - uint32_t p[N]: input/output coefficient array
 **************************************************/
void ntt(int32_t a[N]) {
    unsigned int len, start, j, k;
    int32_t zeta, t;

    k = 0;
    for (len = 128; len > 0; len >>= 1) {
        for (start = 0; start < N; start = j + len) {
            zeta = zetas[++k];
            for (j = start; j < start + len; ++j) {
                t = montgomery_reduce((int64_t)zeta * a[j + len]);
                a[j + len] = a[j] - t;
                a[j] = a[j] + t;
            }
        }
    }
}

/*************************************************
 * Name:        invntt_tomont
 *
 * Description: Inverse NTT and multiplication by Montgomery factor 2^32.
 *              In-place. No modular reductions after additions or
 *              subtractions; input coefficients need to be smaller than
 *              Q in absolute value. Output coefficient are smaller than Q in
 *              absolute value.
 *
 * Arguments:   - uint32_t p[N]: input/output coefficient array
 **************************************************/
void invntt_tomont(int32_t a[N]) {
    unsigned int start, len, j, k;
    int32_t t, zeta;
    const int32_t f = -1514; // mont^2/256

    k = 256;
    for (len = 1; len < N; len <<= 1) {
        for (start = 0; start < N; start = j + len) {
            zeta = -zetas[--k];
            for (j = start; j < start + len; ++j) {
                t = a[j];
                a[j] = t + a[j + len];
                a[j + len] = t - a[j + len];
                a[j + len] = montgomery_reduce((int64_t)zeta * a[j + len]);
            }
        }
    }

    for (j = 0; j < N; ++j) {
        a[j] = montgomery_reduce((int64_t)f * a[j]);
    }
}
