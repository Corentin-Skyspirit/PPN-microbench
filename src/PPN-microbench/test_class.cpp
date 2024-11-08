#include <PPN-microbench/test_class.hpp>
#include <iostream>

Test_class::Test_class(std::string name, int nbIterations, float number) : Microbench(name, nbIterations) {
    this->number = number;
}

Test_class::~Test_class() {
}

void Test_class::executeBench() {
    std::cout << getName() << " " << this->getNbIterations() << " " << this->number << " " << std::endl;
}

json Test_class::getJson() {
    return nullptr;   
}

void Test_class::run() {
    Microbench::run();
}
