#include <PPN-microbench/cpu_frequency.hpp>

CPUFrequency::CPUFrequency(int nbMeasures) : Microbench("CPU Frequency", 777777){
    this->nbMeasures = nbMeasures;
    Context context = Context::getInstance();
    nbCores = context.getCpus();
    measures = std::make_unique<double[]>(nbCores * getNbIterations());
    benchTimes = std::make_unique<u64[]>(nbCores * getNbIterations());
}

CPUFrequency::~CPUFrequency() {}

void CPUFrequency::executeAdds() {
    int cpt = 0;
    for (int i = 0; i < getNbIterations(); i++) {
        // 32 adds
        cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++;
        cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++;
        cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++;
        cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++;
    }
}

json CPUFrequency::getJson() {
    json cpuSpeedJson = json::object();
    std::string name;
    for (int id = 0; id < coresToExecute; id++) {
        for (int i = 0; i < nbMeasures; i++) {
            cpuSpeedJson["Cores" + std::to_string(id+1)] += {measures[id * nbCores + i], benchTimes[id * nbCores + i]};
        }
    }
    return cpuSpeedJson;
}

void CPUFrequency::run() {
    Context context = Context::getInstance();
    std::vector<size_t> threadMapping = context.getThreadMapping();

    cpu_set_t cpusets[nbCores];

    for (size_t i = 0; i < nbCores; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(threadMapping[i], &cpusets[i]);
    }

    std::thread threads[std::thread::hardware_concurrency()];

    // To stop earlier if it's needed (but protection if maxCores is bigger than the cores count)
    coresToExecute = threadMapping.size();

    for (int coresExecuted = 1; coresExecuted <= coresToExecute; coresExecuted++) {
        for (int repetitions = -16; repetitions < nbMeasures; repetitions++) {
            // Execute on 1 Core, then 2 Cores, 3 Cores, etc...
            auto start = std::chrono::steady_clock::now();

            for (int id = 0; id < coresExecuted; id++) {
                // To call the threads (only 1;  1 and 2;  1, 2 and 3;  etc...)
                threads[threadMapping[id]] = std::thread([this] {
                        this->executeAdds();
                });
                pthread_setaffinity_np(threads[threadMapping[id]].native_handle(),
                                       sizeof(cpu_set_t), &cpusets[id]);
            }
            
            for (int id = 0; id < coresExecuted; id++) {
                // Waiting for the threads
                threads[threadMapping[id]].join();
            }

            u64 duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count();
            if (repetitions >= 0) {
                benchTimes[(coresExecuted - 1) * nbCores + repetitions] = duration;
                measures[(coresExecuted - 1) * nbCores + repetitions] = ((32.f * getNbIterations()) / duration);
            }
        }
    }
}
