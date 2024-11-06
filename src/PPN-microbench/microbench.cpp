#include <PPN-microbench/microbench.hpp>

Microbench::Microbench(std::string name, int nbIterations) {
    this->name = name;
    this->nbIterations = nbIterations;
}

Microbench::~Microbench() {
}

void Microbench::run() {
    for (int i = 0; i < this->nbIterations; i++) {
        executeBench();
    }
}

std::string Microbench::getName(){
    return this->name;
}

int Microbench::getNbIterations(){
    return this->nbIterations;
}