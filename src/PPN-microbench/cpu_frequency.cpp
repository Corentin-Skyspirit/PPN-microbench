#include <PPN-microbench/cpu_frequency.hpp>

CPUFrequency::CPUFrequency(std::string name, int nbIterations, int nbMeasures) : Microbench(name, nbIterations)  {
    this->nbMeasures = nbMeasures;
    nbThreads = std::thread::hardware_concurrency() - 1;
    measures.reserve(nbThreads * nbIterations);
    benchTimes.reserve(nbThreads * nbIterations);
}

CPUFrequency::~CPUFrequency() {}

void CPUFrequency::executeAdds() {
    int cpt;
    for (int i = 0; i < getNbIterations(); i++) {
        // 16 adds
        cpt = 0;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
        cpt++;
    }
}

json CPUFrequency::getJson() {
    json cpuSpeedJson = json::object();
    std::string name;
    for (int id = 0; id <= coresToExecute; id++) {
        for (int i = 0; i < nbMeasures; i++) {
            cpuSpeedJson["Cores" + std::to_string(id+1)] += {measures[id][i], benchTimes[id][i]};
        }
    }
    return cpuSpeedJson;
}

void CPUFrequency::run() {
    run(nbThreads);
}

void CPUFrequency::run(int maxCores) {
    std::thread threads[nbThreads];

    // To stop earlier if it's needed (but protection if maxCores is bigger than the cores count)
    coresToExecute = std::min(nbThreads, maxCores);

    for (int coresExecuted = 0; coresExecuted <= coresToExecute; coresExecuted++) {
        std::cerr << coresExecuted << std::endl;
        for (int repetitions = 0; repetitions < nbMeasures; repetitions++) {
            // Execute on 1 core, then 2 core, 3 cores, etc...
            // u64 startMeasure = rdtsc();
            std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

            for (int id = 0; id < coresExecuted; id++) {
                // To call the threads (only 1;  1 and 2;  1, 2 and 3;  etc...)
                threads[id] = std::thread([this] {
                        this->executeAdds();
                });
            }
            
            for (int id = 0; id < coresExecuted; id++) {
            // Waiting for the threads
            threads[id].join();
            }
            std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
            // measures[coresExecuted].push_back(rdtsc() - startMeasure);
            u64 timeMeasured = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
            benchTimes[coresExecuted].push_back(timeMeasured);
            measures[coresExecuted].push_back((16.f * getNbIterations()) / timeMeasured);
        }
    }
}
