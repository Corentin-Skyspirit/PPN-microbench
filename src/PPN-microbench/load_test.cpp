#include <PPN-microbench/load_test.hpp>
#include <PPN-microbench/rdtsc.hpp>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

LoadTest::LoadTest() : Microbench("Load Test", 999999) {
    nbCores = std::thread::hardware_concurrency();
    measures.reserve(nbMeasures);
}

LoadTest::~LoadTest(){}

void LoadTest::run(){

    std::thread threads[nbCores];

    double nbFMA = (double)(12 * nbIterations);

    for (int maxCores = 1; maxCores < nbCores + 1; maxCores++) {
        auto start = steady_clock::now();
        unsigned long long start_cycle = rdtsc();

        for (int id = 0; id < maxCores; id++) {

            int half = (maxCores + (maxCores % 2)) / 2;
            id = 2 * (id % half) + (id / half); // To "shuffle" the threads id to have better performance when hyperthreading on core (0, 1, 2, 3 become 0, 2 ,1 ,3)

            spdlog::debug("id : {}, half : {}", id, half);

            // 1 core, 2 cores and so on
            double x = duration_cast<nanoseconds>(steady_clock::now() - start).count();
            double y = duration_cast<nanoseconds>(steady_clock::now() - start).count();
            double z = duration_cast<nanoseconds>(steady_clock::now() - start).count();

            threads[id] = std::thread([this, x, y, z] {
                FMA_DOUBLE(x, y, z, this->getNbIterations());
            });
        }
        uint64_t cycles = rdtsc() - start_cycle;

        for (int id = 0; id < maxCores; id++) {

            int half = (maxCores + (maxCores % 2)) / 2;
            id = 2 * (id % half) + (id / half); // To "shuffle" the threads id to have better performance when hyperthreading on core (0, 1, 2, 3 become 0, 2 ,1 ,3)

            threads[id].join();
        }

        uint64_t duration = duration_cast<nanoseconds>(steady_clock::now() - start).count();

        double debit = nbFMA / cycles;
        spdlog::debug("Iteration {} - duration : {} / nbIterations : {} / result : {}", maxCores, duration, nbIterations, debit);
        measures.push_back(debit);
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
