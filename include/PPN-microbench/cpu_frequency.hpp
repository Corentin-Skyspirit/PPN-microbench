#ifndef CPU_FREQUENCY
#define CPU_FREQUENCY

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/rdtsc.hpp>
#include <vector>
#include <chrono>
#include <thread>

class CPUFrequency : Microbench {
    private:
        int nbThreads;
        int nbMeasures = 0;
        int coresToExecute = 0;
        std::vector<std::vector<u64>> measures;
        std::vector<std::vector<u64>> benchTimes;
        void executeAdds();
        
    public:
        CPUFrequency(std::string name, int nbIterations, int nbMeasures);
        ~CPUFrequency();

        void run() override;
        void run(int maxThreads);
        json getJson() override;
};

#endif