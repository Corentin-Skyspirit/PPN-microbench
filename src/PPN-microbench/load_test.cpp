#include <PPN-microbench/load_test.hpp>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

LoadTest::LoadTest(int nbMeasures) : Microbench("Load Test", 9'999'999) {
    this->nbMeasures = nbMeasures;
    Context context = Context::getInstance();
    nbCores = context.getCpus();
    measures.reserve(nbCores * nbMeasures);
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

    nbTestingCores = threadMapping.size();

    double nbFMA = (double)(12 * nbIterations);

    for (int maxCores = 1; maxCores < nbTestingCores + 1; maxCores++) {

        for (int k = 0; k < nbMeasures; k ++) {
            auto start = steady_clock::now();

            for (int id = 0; id < maxCores; id++) {

                spdlog::debug("id : {}", id);

                // 1 core, 2 cores and so on
                double x = duration_cast<nanoseconds>(steady_clock::now() - start).count();
                double y = duration_cast<nanoseconds>(steady_clock::now() - start).count();
                double z = duration_cast<nanoseconds>(steady_clock::now() - start).count();

                threads[id] = std::thread([this, x, y, z] {
                    FMA_DOUBLE(x, y, z, this->getNbIterations());
                });
                pthread_setaffinity_np(threads[id].native_handle(),
                                    sizeof(cpu_set_t), &cpusets[id]);
            }

            for (int id = 0; id < maxCores; id++) {

                spdlog::debug("Join thread {}", id);

                threads[id].join();
            }

            uint64_t duration = duration_cast<nanoseconds>(steady_clock::now() - start).count();

            double frequency = (nbFMA / duration) / 2; // divide per 2 because of ~2 fma per cycle
            spdlog::debug("Iteration {} - duration : {} / nbIterations : {} / frequency : {}", maxCores, duration, nbIterations, frequency);
            measures.push_back(frequency);
        }
    }
}

json LoadTest::getJson(){
    json loadTestJson = json::object();
    loadTestJson["name"] = getName();
    for (int i = 0; i < nbCores; i++) {
        for (int k = 0; k < nbMeasures; k++) {
            loadTestJson["results"][i] += measures[i * nbMeasures + k];
        }
    }
    return loadTestJson;
}
