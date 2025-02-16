#ifndef PPN_MICROBENCH_INTRINSICS_H
#define PPN_MICROBENCH_INTRINSICS_H

#include <immintrin.h>

#define __STR(HAHA) #HAHA
#define _STR(HAHA) __STR(HAHA)

#if defined(__i386__) || defined(__x86_64__)
#    if defined(__SSE2__)
#        define SIMD_INT_MAX_FN _mm_add_epi64
#        define SIMD_INT_MAX_TYPE __m128i
#        define SIMD_FLOAT_MAX_FN _mm_add_pd
#        define SIMD_FLOAT_MAX_TYPE __m128d
#    endif
#    if defined(__AVX__)
#        undef SIMD_FLOAT_MAX_FN
#        undef SIMD_FLOAT_MAX_TYPE
#        define SIMD_FLOAT_MAX_FN _mm256_add_pd
#        define SIMD_FLOAT_MAX_TYPE __m256d
#    endif
#    if defined(__AVX2__)
#        undef SIMD_INT_MAX_FN
#        undef SIMD_INT_MAX_TYPE
#        define SIMD_INT_MAX_FN _mm256_add_epi64
#        define SIMD_INT_MAX_TYPE __m256i
#    endif
#    if defined(__AVX512F__)
#        undef SIMD_INT_MAX_FN
#        undef SIMD_INT_MAX_TYPE
#        undef SIMD_FLOAT_MAX_FN
#        undef SIMD_FLOAT_MAX_TYPE
#        define SIMD_INT_MAX_FN _mm512_add_epi64
#        define SIMD_INT_MAX_TYPE __m512i
#        define SIMD_FLOAT_MAX_FN _mm512_add_pd
#        define SIMD_FLOAT_MAX_TYPE __m512d
#    endif
#endif

#endif