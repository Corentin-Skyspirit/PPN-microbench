#include <PPN-microbench/load_test.hpp>

constexpr double y = 45.0;
double x = 320.0;

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

LoadTest::LoadTest(int nbMeasures) : Microbench("Load Test", 99999) {
    this->nbMeasures = nbMeasures;
    Context context = Context::getInstance();
    nbCores = context.getCpus();
    measures.reserve(nbMeasures);
}

LoadTest::~LoadTest(){}

void LoadTest::executeBench(){
    std::set<std::string> simd = context.getSimd();
    if (simd.find("AVX2") != simd.end()) {

    }
    if (simd.find("AVX2") != simd.end()) {

    }
    if (simd.find("AVX2") != simd.end()) {

    }
    if (simd.find("AVX2") != simd.end()) {

    }
    else {}
}

void LoadTest::run(){
    Context context = Context::getInstance();
    std::vector<size_t> threadMapping = context.getThreadMapping();

    cpu_set_t cpusets[nbCores];

    for (int i = 0; i < nbCores; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(threadMapping[i], &cpusets[i]);
    }

    std::thread threads[nbCores];

    for (int maxCores = 0; maxCores < nbMeasures; maxCores++) {
        auto start = steady_clock::now();

        for (int id = 0; id < maxCores; id++) {
            threads[id] = std::thread([this] {
                for (double z = 0; z < nbIterations; z++) {
                    
                }
            });
            pthread_setaffinity_np(threads[id].native_handle(),
                                sizeof(cpu_set_t), &cpusets[id]);
        }

        for (int id = 0; id < nbCores; id++) {
            threads[id].join();
        }

        uint64_t duration = duration_cast<nanoseconds>(steady_clock::now() - start).count();
        double fmaPerSec = duration;
        measures.push_back(fmaPerSec);
    }
}

json LoadTest::getJson(){
    json loadTestJson = json::object();
    loadTestJson["name"] = getName();
    for (int i = 0; i < nbMeasures; i++) {
        loadTestJson["results"] += measures[i];
    }
    return loadTestJson;
}
