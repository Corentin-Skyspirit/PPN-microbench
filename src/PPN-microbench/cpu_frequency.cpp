#include <PPN-microbench/cpu_frequency.hpp>

CPUFrequency::CPUFrequency(std::string name, int nbIterations) : Microbench(name, nbIterations)  {
    nbThreads = std::thread::hardware_concurrency() - 1;
    measures.reserve(nbThreads * nbIterations);
    benchTimes.reserve(nbThreads * nbIterations);
}

CPUFrequency::~CPUFrequency() {}

void CPUFrequency::executeBench(int id) {
    u64 startMeasure = rdtsc();
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    int cpt;
    for (int i = 0; i < INT32_MAX; i++) {
        cpt++;
    }
    measures[id].push_back(rdtsc() - startMeasure);
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    benchTimes[id].push_back(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
    // std::cout << "Mesure" << std::endl;
}

json CPUFrequency::getJson() {
    json cpuSpeedJson = json::object();
    std::string name;
    for (unsigned int id = 0; id < nbThreads; id++) {
        for (int i = 0; i < getNbIterations(); i++) {
            cpuSpeedJson["CPU" + std::to_string(id)] += {measures[id][i] / benchTimes[id][i], benchTimes[id][i]};
        }
    }
    return cpuSpeedJson;
}

void CPUFrequency::run() {
    std::thread threads[nbThreads];

    for (unsigned int id = 0; id < nbThreads; id++) {
        threads[id] = std::thread([this, id] {
            for (int i = 0; i < getNbIterations(); i++) {
                this->executeBench(id);
            }
        });
    }

    for (auto &th : threads) {
        th.join();
        // std::cout << "Thread fini" << std::endl;
    }
}
