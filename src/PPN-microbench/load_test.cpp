#include <PPN-microbench/load_test.hpp>

LoadTest::LoadTest(int nbMeasures) : Microbench("Load Test", 9999) {
    this->nbMeasures = nbMeasures;
    Context context = Context::getInstance();
    nbCores = context.getCpus();
}

LoadTest::~LoadTest(){}

void LoadTest::run(){
    Context context = Context::getInstance();
    std::vector<size_t> threadMapping = context.getThreadMapping();

    cpu_set_t cpusets[nbCores];

    for (int i = 0; i < nbCores; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(threadMapping[i], &cpusets[i]);
    }

    std::thread threads[nbCores];

    for (int i = 0; i < nbCores; i++) {
        
    }
}

json LoadTest::getJson(){}
