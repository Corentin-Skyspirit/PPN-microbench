#ifndef CPU_SPEED
#define CPU_SPEED

#include <PPN-microbench/microbench.hpp>
#include <vector>

class CPUSpeed : Microbench {
    private:
        std::vector<int> measures;
        void executeBench() override;
        
    public:
        CPUSpeed(std::string name, int nbIterations);
        ~CPUSpeed();

        void run();
        json getJson() override;
};

#endif