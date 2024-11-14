#ifndef CPU_FREQUENCY
#define CPU_FREQUENCY

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/rdtsc.hpp>
#include <vector>
#include <chrono>
#include <thread>

class CPUFrequency : Microbench {
    private:
        unsigned int nbThreads;
        std::vector<std::vector<u64>> measures;
        std::vector<std::vector<u64>> benchTimes;
        void executeBench(int id);
        
    public:
        CPUFrequency(std::string name, int nbIterations);
        ~CPUFrequency();

        void run();
        json getJson() override;
};

#endif