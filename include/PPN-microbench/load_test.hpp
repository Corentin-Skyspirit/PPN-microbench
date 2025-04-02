#ifndef PPN_MICROBENCH_LOAD_TEST
#define PPN_MICROBENCH_LOAD_TEST

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <chrono>
#include <thread>

class LoadTest : public Microbench {
    private:
        int nbMeasures;
        
    public:
        LoadTest(int nbMeasures);
        ~LoadTest();

        void run() override;
        json getJson() override;
};

#endif