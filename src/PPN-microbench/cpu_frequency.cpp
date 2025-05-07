#include <PPN-microbench/cpu_frequency.hpp>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

CPUFrequency::CPUFrequency(int nbMeasures) : Microbench("CPU Frequency", 999'999) {
    this->nbMeasures = nbMeasures;
    Context context = Context::getInstance();
    nbCores = context.getCpus();
    measures = std::make_unique<double[]>(nbMeasures * ((nbCores * (nbCores + 1)) / 2));
}

CPUFrequency::~CPUFrequency() {}

void CPUFrequency::executeBench() {
    #if defined(__i386__) || defined(_M_IX86)
    // x86 32
    #elif defined(__x86_64__)
    // x86 64
    cpu_frequency_x86_64(getNbIterations());
    #elif defined(__arm__) || defined(_M_ARM)
    // ARM 32
    #elif defined(__aarch64__) || defined(_M_ARM64)
    // arm 64
    cpu_frequency_arm_64(getNbIterations());
    #else
    #error Unknown architecture: no support for CPU frequency benchmark
    #endif
}

json CPUFrequency::getJson() {
    json cpuSpeedJson = json::object();
    cpuSpeedJson["name"] = getName();
    for (int id = 2; id <= nbTestingCores; id+=2) {
        for (int i = 0; i < nbMeasures * id; i++) {
            cpuSpeedJson["results"][(id/2)-1][i/nbMeasures] += measures[id * nbCores + i];
        }
    }
    return cpuSpeedJson;
}

void CPUFrequency::run() {
    Context context = Context::getInstance();
    std::vector<size_t> threadMapping = context.getThreadMapping();

    cpu_set_t cpusets[nbCores];

    for (int i = 0; i < nbCores; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(threadMapping[i], &cpusets[i]);
    }

    std::thread threads[nbCores];

    nbTestingCores = threadMapping.size();

    for (int coresToExecute = 2; coresToExecute <= nbTestingCores; coresToExecute+=2) { // Main for, equivalent to a graph
        for (int coresExecuted = 1; coresExecuted <= coresToExecute; coresExecuted++) { // For every core count, equivalent to a point in a graph
            for (int sample = -10; sample < nbMeasures; sample++) { // 10 Warmup runs and samples to average tests (in python, later)
                // Execute on 1 Core, then 2 Cores, 3 Cores, etc...
                auto start = steady_clock::now();

                for (int id = 0; id < coresExecuted; id++) {
                    // To call the threads (only 1;  1 and 2;  1, 2 and 3;  etc...)
                    threads[id] = std::thread([this] {
                        executeBench();
                    });
                    pthread_setaffinity_np(threads[id].native_handle(),
                                        sizeof(cpu_set_t), &cpusets[id]);
                }
            
                for (int id = 0; id < coresExecuted; id++) {
                    // Waiting for the threads
                    threads[id].join();
                }

                uint64_t duration = duration_cast<nanoseconds>(steady_clock::now() - start).count();
                if (sample >= 0) {
                    measures[(coresToExecute * (coresToExecute - 1) / 2) * nbMeasures + (coresExecuted - 1) * nbMeasures + sample] = ((16.f * getNbIterations()) / duration);
                }
            }
            spdlog::debug("{}: run {}/{}", name, ((coresToExecute * (coresToExecute - 1)) / 2) + coresExecuted, ((nbCores * (nbCores + 1)) / 2));
        }
    }
}