#include <PPN-microbench/core_to_core_latency.hpp>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

CoreToCoreLatency::CoreToCoreLatency(int nbMeasures) : Microbench("Core To Core Latency", 100) {
    nbMeasures = nbMeasures;
    nbCores = context.getCpus();
    results.reserve(nbCores * nbCores);
}

CoreToCoreLatency::~CoreToCoreLatency() {}

void CoreToCoreLatency::run() {
    Context context = Context::getInstance();
    std::vector<size_t> threadMapping = context.getThreadMapping();

    cpu_set_t cpusets[nbCores];

    for (int i = 0; i < nbCores; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(threadMapping[i], &cpusets[i]);
    }

    std::thread threads[nbCores];

    for (int id_1 = 0; id_1 < nbCores; id_1++) {
        for (int id_2 = 0; id_2 < nbCores; id_2++) {
            if (id_1 == id_2) {
                results.push_back(0);
            } else {
                for (int sample; sample < nbMeasures; sample++) {
                    auto start = steady_clock::now();

                    alignas(64) std::atomic<int> core1 = {-1};
                    alignas(64) std::atomic<int> core2 = {-1};

                    for (int n = 0; n < getNbIterations(); ++n) {
                        while (core1.load(std::memory_order_acquire) != n) {;}
                        core2.store(n, std::memory_order_release);
                    }
                    
                    uint64_t duration = duration_cast<nanoseconds>(steady_clock::now() - start).count();
                    sumDuration += duration;
                }
                results.push_back(sumDuration / nbMeasures);
            }
            spdlog::debug("\r# {}: run {} / {}", name, id_1 * nbCores + (id_2 + 1), nbCores * nbCores);
        }
    }
}

json CoreToCoreLatency::getJson() { 
    json coreToCoreJson = json::object();
    coreToCoreJson["name"] = getName();
    for (int line = 0; line < nbCores; line++) {
        for (int col = 0; col < nbCores; col++) {
            coreToCoreJson["results"][line] += results[line * nbCores + col];
        }
    }
    return coreToCoreJson;
}
