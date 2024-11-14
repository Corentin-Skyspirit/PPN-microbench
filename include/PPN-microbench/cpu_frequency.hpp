#ifndef CPU_FREQUENCY
#define CPU_FREQUENCY

#include <PPN-microbench/microbench.hpp>
#include <vector>
#include <chrono>
#include <x86intrin.h>

class CPUFrequency : Microbench {
    private:
        std::vector<u64> measures;
        std::vector<u64> benchTimes;
        void executeBench();
        
    public:
        CPUFrequency(std::string name, int nbIterations);
        ~CPUFrequency();

        void run();
        json getJson() override;
};

#endif