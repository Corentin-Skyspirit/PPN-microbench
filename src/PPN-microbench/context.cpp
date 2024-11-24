#include <PPN-microbench/context.hpp>

using std::cout, std::endl;

Context::Context() {
    cpuInfo();
    memoryInfo();
}

Context::~Context() {}

Context &Context::getInstance() {
    static Context instance;
    return instance;
}

// finds and returns the first int in a string, returns 0 if none.
i64 Context::getFirstInt(std::string input) {
    std::regex pattern("(\\d+)");
    std::smatch match;
    std::regex_search(input, match, pattern);

    for (auto m : match) {
        return stoi(m.str());
    }

    return 0;
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

    /////////
    // RAM //
    /////////

    std::ifstream f("/proc/meminfo");
    std::string line;

    while (std::getline(f, line)) {
        // memory in /proc/meminfo is in kB
        if (line.find("MemTotal:") != std::string::npos)
            memory = getFirstInt(line) * 1000;
    }

    std::cout << memory << std::endl;

    ///////////
    // CACHE //
    ///////////
}

json Context::getJson() {
    json obj;

    json cpu_info;
    cpu_info["architechture"] = cpuArchi;
    cpu_info["word_size"] = wordSize;
    cpu_info["cpus"] = cpus;
    cpu_info["simd"] = json(simd);

    json mem_info;
    mem_info["total_mem"] = memory;
    mem_info["l1d"] = l1d;
    mem_info["l1i"] = l1i;
    mem_info["l2"] = l2;
    mem_info["l3"] = l3;

    obj["cpu_info"] = cpu_info;
    obj["mem_info"] = mem_info;

    cout << obj.dump(4) << endl;

    return obj;
}
