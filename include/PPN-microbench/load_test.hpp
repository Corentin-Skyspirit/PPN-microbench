#ifndef PPN_MICROBENCH_LOAD_TEST
#define PPN_MICROBENCH_LOAD_TEST
#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <chrono>
#include <thread>
#include <sched.h>

class LoadTest : public Microbench {
    private:
        int nbCores;
        int nbMeasures;
        double* measures;
        void executeBench();
        
    public:
        LoadTest(int nbMeasures);
        ~LoadTest();

        void run() override;
        json getJson() override;
};

#endif