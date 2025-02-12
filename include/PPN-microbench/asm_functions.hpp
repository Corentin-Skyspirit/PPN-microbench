#ifndef PPN_MICROBENCH_ASM
#define PPN_MICROBENCH_ASM

#include <cstdint>

extern "C" void cpu_frequency_x86_64(uint64_t iterations);
extern "C" void cpu_frequency_arm_64(uint64_t iterations);

#endif