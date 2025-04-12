#ifndef PPN_MICROBENCH_LOAD_TEST
#define PPN_MICROBENCH_LOAD_TEST

#include <PPN-microbench/microbench.hpp>

#include <chrono>
#include <thread>
#include <cmath>

class LoadTest : public Microbench {
    private:
        int nbMeasures;
        int nbCores;
        std::vector<double> measures;
        
    public:
        LoadTest();
        ~LoadTest();

        void run() override;
        json getJson() override;
};

#endif