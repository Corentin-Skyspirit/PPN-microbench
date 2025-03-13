#ifndef PPN_MICROBENCH_CORE_TO_CORE_LATENCY
#define PPN_MICROBENCH_CORE_TO_CORE_LATENCY

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <chrono>
#include <thread>

class CoreToCoreLatency : public Microbench {
    private:
        int nbCores;
        int nbMeasures;
        int sumDuration = 0;
        std::vector<int> results;
    public:
        CoreToCoreLatency(int nbMeasures);
        ~CoreToCoreLatency();

        void run() override;
        json getJson() override;
};

#endif