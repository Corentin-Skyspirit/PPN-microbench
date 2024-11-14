#include <PPN-microbench/context.hpp>

using std::cout, std::endl;

Context::Context() {
    cpuInfo();
    memoryInfo();
}

Context::~Context() {}

void Context::cpuInfo() {

//////////////////////
// CPU Architecture //
//////////////////////

// ARM
#if defined(__arm__)
    cpuArchi = "ARM";
#endif
#if defined(__aarch64__)
    cpuArchi = "ARM";
#endif

// x86
#if defined(__i386__)
    cpuArchi = "x86";
#endif
#if defined(__x86_64__)
    cpuArchi = "x86";
#endif

    ///////////////
    // Word Size //
    ///////////////

    // I don't know how cursed that is
    wordSize = sizeof(size_t) * 8;

    //////////
    // SIMD // x86 only for now SORRY
    //////////

    // bro..
    if (cpuArchi == "x86") {
        if (__builtin_cpu_supports("sse")) {
            simd.emplace("SSE");
        }
        if (__builtin_cpu_supports("sse2")) {
            simd.emplace("SSE2");
        }
        if (__builtin_cpu_supports("sse3")) {
            simd.emplace("SSE3");
        }
        if (__builtin_cpu_supports("sse4.2")) {
            simd.emplace("SSE4.2");
        }
        if (__builtin_cpu_supports("avx")) {
            simd.emplace("AVX");
        }
        if (__builtin_cpu_supports("avx2")) {
            simd.emplace("AVX2");
        }
        if (__builtin_cpu_supports("avx512f")) {
            simd.emplace("AVX512");
        }
    }

    //////////
    // CPUs //
    //////////
    cpus = sysconf(_SC_NPROCESSORS_ONLN);
}

void Context::memoryInfo() {}

void Context::print() {
    cout << "archi: " << cpuArchi << endl;
    cout << "word size: " << wordSize << " bits" << endl;
    cout << "Core count: " << cpus << endl;
    cout << "SIMD capabilities: " << endl;
    for (std::string s : simd) {
        cout << "\t" << s << endl;
    }
}