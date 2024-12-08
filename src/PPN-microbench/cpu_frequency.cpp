#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/context.hpp>

CPUFrequency::CPUFrequency(int nbMeasures) : Microbench("CPU Frequency", 999999){
    this->nbMeasures = nbMeasures;
    nbThreads = std::thread::hardware_concurrency();
    measures.reserve(nbThreads * getNbIterations());
    benchTimes.reserve(nbThreads * getNbIterations());
}

CPUFrequency::~CPUFrequency() {}

void CPUFrequency::executeAdds() {
    int cpt = 0;
    for (int i = 0; i < getNbIterations(); i++) {
        // 16 adds
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
        cpt++;
    }
}

json CPUFrequency::getJson() {
    json cpuSpeedJson = json::object();
    std::string name;
    for (int id = 0; id < coresToExecute; id++) {
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

    for (int coresExecuted = 1; coresExecuted <= coresToExecute; coresExecuted++) {
        for (int repetitions = 0; repetitions < nbMeasures; repetitions++) {
            // Execute on 1 thread, then 2 threads, 3 threads, etc...
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

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

            u64 duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count();

            benchTimes[coresExecuted-1].push_back(duration);
            measures[coresExecuted-1].push_back((16.f * getNbIterations()) / duration);
        }
    }
}
