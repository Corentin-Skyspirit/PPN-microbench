#ifndef PPN_MICROBENCH_CORE_TO_CORE_FREQUENCY
#define PPN_MICROBENCH_CORE_TO_CORE_FREQUENCY

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <chrono>
#include <thread>

class CoreToCoreFrequency : public Microbench {
    private:
    public:
        CoreToCoreFrequency(int nbMeasures);
        ~CoreToCoreFrequency();

        void run() override;
        json getJson() override;
};

#endif