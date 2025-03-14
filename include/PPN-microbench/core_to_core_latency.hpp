#ifndef PPN_MICROBENCH_CORE_TO_CORE_LATENCY
#define PPN_MICROBENCH_CORE_TO_CORE_LATENCY

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <sched.h>
#include <stdlib.h>

#include <chrono>
#include <thread>
#include <atomic>

class CoreToCoreLatency : public Microbench {
    private:
        int nbCores;
        int nbMeasures;
        uint64_t sumDuration;
        uint64_t minDuration;
        std::vector<int> results;

        void pinThread(int core);
    public:
        CoreToCoreLatency(int nbMeasures);
        ~CoreToCoreLatency();

        void run() override;
        json getJson() override;
};

#endif