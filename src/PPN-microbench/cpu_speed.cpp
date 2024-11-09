#include <PPN-microbench/cpu_speed.hpp>


CPUSpeed::CPUSpeed(std::string name, int nbIterations) : Microbench(name, nbIterations)  {}

CPUSpeed::~CPUSpeed() {}

void CPUSpeed::executeBench() {}

json CPUSpeed::getJson() {
    return nullptr;   
}

void CPUSpeed::run() {
    Microbench::run();
}
