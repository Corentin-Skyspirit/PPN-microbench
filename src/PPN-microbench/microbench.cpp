#include <PPN-microbench/microbench.hpp>

Microbench::Microbench(std::string name, uint64_t nbIterations) {
    this->name = name;
    this->nbIterations = nbIterations;
    
    mainDevice = context.getMainDevice();
    mainDeviceContext = context.getMainDeviceContext();
    mainDeviceQueue = context.getMainDeviceQueue();
}

Microbench::~Microbench() {}

std::string Microbench::getName() { return this->name; }

uint64_t Microbench::getNbIterations() { return this->nbIterations; }