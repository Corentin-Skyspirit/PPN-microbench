#ifndef PPN_MICROBENCH_INTRINSICS_H
#define PPN_MICROBENCH_INTRINSICS_H

#include <PPN-microbench/constants.hpp>

#define __STR(S) #S
#define _STR(S) __STR(S)

#if defined(__i386__) || defined(__x86_64__)

#    include <immintrin.h>

extern "C" i32 ADD_X86_i32(i32, i32);
extern "C" i64 ADD_X86_i64(i64, i64);
extern "C" float ADD_X86_f32(float, float);
extern "C" double ADD_X86_f64(double, double);

#    define ADD_i32 ADD_X86_i32
#    define ADD_i64 ADD_X86_i64
#    define ADD_f32 ADD_X86_f32
#    define ADD_f64 ADD_X86_f64

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

#if defined(__arm__) || defined(__aarch64__)

#    include <arm_neon.h>

extern "C" i32 ADD_ARM_i32(i32, i32);
extern "C" i64 ADD_ARM_i64(i64, i64);
extern "C" float ADD_ARM_f32(float, float);
extern "C" double ADD_ARM_f64(double, double);

#    define ADD_i32 ADD_ARM_i32
#    define ADD_i64 ADD_ARM_i64
#    define ADD_f32 ADD_ARM_f32
#    define ADD_f64 ADD_ARM_f64

#if defined(__ARM_NEON)

    #define SIMD_INT_MAX_FN vaddq_s64
    #define SIMD_INT_MAX_TYPE int64x2_t
    #define SIMD_FLOAT_MAX_FN vaddq_f64
    #define SIMD_FLOAT_MAX_TYPE float64x2_t

#else

#    define SIMD_INT_MAX_FN ADD_i64
#    define SIMD_INT_MAX_TYPE i64
#    define SIMD_FLOAT_MAX_FN ADD_f64
#    define SIMD_FLOAT_MAX_TYPE double

#endif 

#endif

#endif