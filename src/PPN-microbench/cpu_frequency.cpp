#include <PPN-microbench/cpu_frequency.hpp>

CPUFrequency::CPUFrequency(std::string name, int nbIterations) : Microbench(name, nbIterations)  {
    measures.reserve(nbIterations);
    benchTimes.reserve(nbIterations);
}

CPUFrequency::~CPUFrequency() {}

void CPUFrequency::executeBench() {
    u64 startMeasure = _rdtsc();
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    int cpt;
    for (int i = 0; i < INT32_MAX; i++) {
        cpt++;
    }
    measures.push_back(_rdtsc() - startMeasure);
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    benchTimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
    std::cout << "Mesure" << std::endl;
}

json CPUFrequency::getJson() {
    json cpuSpeedJson = json::object();
    std::string name;
    for (int i = 0; i < getNbIterations(); i++) {
        float frequency = (measures[i] / benchTimes[i]) / 1000.0f;
        cpuSpeedJson["Attempt " + std::to_string(i + 1)] = frequency;
    }
    return cpuSpeedJson;
}

void CPUFrequency::run() {
    for (int i = 0; i < getNbIterations(); i++) {
        executeBench();
    }
}
