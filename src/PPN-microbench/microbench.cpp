#include <PPN-microbench/microbench.hpp>

Microbench::Microbench(std::string name, uint64_t nbIterations) {
    this->name = name;
    this->nbIterations = nbIterations;
}

Microbench::~Microbench() {}

std::string Microbench::getName() { return this->name; }

u64 Microbench::getNbIterations() { return this->nbIterations; }