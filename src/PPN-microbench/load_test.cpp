#include <PPN-microbench/load_test.hpp>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

LoadTest::LoadTest() : Microbench("Load Test", 999999) {
    Context context = Context::getInstance();
    // nbCores = context.getCpus();
    nbCores = std::thread::hardware_concurrency();
    measures.reserve(nbMeasures);
}

LoadTest::~LoadTest(){}

void LoadTest::run(){
    // Context context = Context::getInstance();
    // std::vector<size_t> threadMapping = context.getThreadMapping();

    // cpu_set_t cpusets[nbCores];

    // for (int i = 0; i < nbCores; i++) {
    //     CPU_ZERO(&cpusets[i]);
    //     CPU_SET(threadMapping[i], &cpusets[i]);
    // }

    std::thread threads[nbCores];

    for (int maxCores = 1; maxCores < nbCores + 1; maxCores++) {
        auto start = steady_clock::now();

        for (int id = 0; id < maxCores; id++) {

            // 1 core, 2 cores and so on
            double x = duration_cast<nanoseconds>(steady_clock::now() - start).count();
            double y = duration_cast<nanoseconds>(steady_clock::now() - start).count();
            double z = duration_cast<nanoseconds>(steady_clock::now() - start).count();

            threads[id] = std::thread([this, x, y, z] {
                FMA_DOUBLE(x, y, z, this->getNbIterations());
            });
            // pthread_setaffinity_np(threads[id].native_handle(),
            //                     sizeof(cpu_set_t), &cpusets[id]);
        }

        for (int id = 0; id < maxCores; id++) {
            threads[id].join();
        }

        uint64_t duration = duration_cast<nanoseconds>(steady_clock::now() - start).count();
        double fmaPerSecPerCore = ((double)(12 * nbIterations * 1000000000) / duration) / maxCores;
        spdlog::debug("Iteration {} - duration : {} / nbIterations : {} / result : {}", maxCores, duration, nbIterations, fmaPerSecPerCore);
        measures.push_back(fmaPerSecPerCore);
    }
}

json LoadTest::getJson(){
    json loadTestJson = json::object();
    loadTestJson["name"] = getName();
    for (int i = 0; i < nbCores; i++) {
        loadTestJson["results"] += measures[i];
    }
    return loadTestJson;
}
