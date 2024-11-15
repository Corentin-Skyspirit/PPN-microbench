#include <PPN-microbench/context.hpp>

using std::cout, std::endl;

Context::Context() {
    cpuInfo();
    memoryInfo();
}

Context::~Context() { cout << "haha" << endl; }

Context &Context::getInstance() {
    static Context instance;
    return instance;
}

void Context::cpuInfo() {

//////////////////////
// CPU Architecture //
//////////////////////

// ARM
#if defined(__arm__) || defined(__aarch64__)
    cpuArchi = "ARM";
#endif

// x86
#if defined(__i386__) || defined(__x86_64__)
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
#if defined(__i386__) || defined(__x86_64__)
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
#endif

    //////////
    // CPUs //
    //////////

    // idk how to get thread to core mapping reliably so we're not getting it
    // for now
    cpus = std::thread::hardware_concurrency();
}

void Context::memoryInfo() {

    ///////////
    // CACHE //
    ///////////

    // :(
    // system("lscpu -B | grep L1d | awk '{print $3}'");
}

void Context::print() {
    cout << "archi: " << cpuArchi << endl;
    cout << "word size: " << wordSize << " bits" << endl;
    cout << "Core count: " << cpus << endl;
    cout << "SIMD capabilities: " << endl;
    for (std::string s : simd) {
        cout << "\t" << s << endl;
    }
}

json Context::getJson() { json obj; }