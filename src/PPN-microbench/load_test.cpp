#include <PPN-microbench/load_test.hpp>

LoadTest::LoadTest(int nbMeasures) : Microbench("Load Test", 10) {
    this->nbMeasures = nbMeasures;
}

LoadTest::~LoadTest(){}

void LoadTest::run(){}

json LoadTest::getJson(){}
