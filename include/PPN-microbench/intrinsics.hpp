#ifndef PPN_MICROBENCH_INTRINSICS_HPP
#define PPN_MICROBENCH_INTRINSICS_HPP

#include <PPN-microbench/constants.hpp>

#define __STR(S) #S
#define _STR(S) __STR(S)

#if defined(__i386__) || defined(__x86_64__)

    extern "C" void ADD_X86_i32(i64);
    extern "C" void ADD_X86_i64(i64);
    extern "C" void ADD_X86_f32(i64);
    extern "C" void ADD_X86_f64(i64);

    extern "C" void ADD_X86_i64_SSE(i64);
    extern "C" void ADD_X86_f64_SSE(i64);

    extern "C" void ADD_X86_i64_AVX(i64);
    extern "C" void ADD_X86_f64_AVX(i64);

    extern "C" void ADD_X86_i64_AVX512(i64);
    extern "C" void ADD_X86_f64_AVX512(i64);

#    define ADD_i32 ADD_X86_i32
#    define ADD_i64 ADD_X86_i64
#    define ADD_f32 ADD_X86_f32
#    define ADD_f64 ADD_X86_f64

#    if defined(__SSE2__)
#        define SIMD_INT_MAX_FN ADD_X86_i64_SSE
#        define SIMD_FLOAT_MAX_FN ADD_X86_f64_SSE
#    endif
#    if defined(__AVX__)
#        undef SIMD_FLOAT_MAX_FN
#        define SIMD_FLOAT_MAX_FN ADD_X86_f64_AVX
#    endif
#    if defined(__AVX2__)
#        undef SIMD_INT_MAX_FN
#        define SIMD_INT_MAX_FN ADD_X86_i64_AVX
#    endif
#    if defined(__AVX512F__)
#        undef SIMD_INT_MAX_FN
#        undef SIMD_FLOAT_MAX_FN
#        define SIMD_INT_MAX_FN ADD_X86_i64_AVX512
#        define SIMD_FLOAT_MAX_FN ADD_X86_f64_AVX512
#    endif
#endif

#if defined(__arm__) || defined(__aarch64__)

    extern "C" void ADD_ARM_i32(i64);
    extern "C" void ADD_ARM_i64(i64);
    extern "C" void ADD_ARM_f32(i64);
    extern "C" void ADD_ARM_f64(i64);

    extern "C" void ADD_ARM_i64_NEON(i64);
    extern "C" void ADD_ARM_f64_NEON(i64);

#    define ADD_i32 ADD_ARM_i32
#    define ADD_i64 ADD_ARM_i64
#    define ADD_f32 ADD_ARM_f32
#    define ADD_f64 ADD_ARM_f64

    #if defined(__ARM_NEON)
        #define SIMD_INT_MAX_FN ADD_ARM_i64_NEON
        #define SIMD_FLOAT_MAX_FN ADD_ARM_f64_NEON
    #else
    #    define SIMD_INT_MAX_FN ADD_ARM_i64
    #    define SIMD_FLOAT_MAX_FN ADD_ARM_f64
    #endif
#endif

#endif