#include <PPN-microbench/load_test.hpp>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

LoadTest::LoadTest(int nbMeasures) : Microbench("Load Test", 100 * Mi) { // Mi = 1048576
    this->nbMeasures = nbMeasures;
    // Context context = Context::getInstance();
    nbCores = std::thread::hardware_concurrency(); /*context.getCpus();*/
    measures = (double*) calloc(nbMeasures, nbMeasures * sizeof(double));
}

LoadTest::~LoadTest() {
    free(measures);
}

#pragma GCC push_options
#pragma GCC optimize("O0")
void LoadTest::executeBench() {
    int cpt = 0;
    for (int i = 0; i < getNbIterations(); i++) {
        // 16 adds
        cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++;
        cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++; cpt++;
    }
}
#pragma GCC pop_options

void LoadTest::run() {
    // Context context = Context::getInstance();
    // std::vector<size_t> threadMapping = context.getThreadMapping();

    // cpu_set_t cpusets[nbCores];

    // for (int i = 0; i < nbCores; i++) {
    //     CPU_ZERO(&cpusets[i]);
    //     CPU_SET(threadMapping[i], &cpusets[i]);
    // }

    std::thread threads[nbCores];
    int nbThreads = nbCores; /*threadMapping.size();*/

    for (int sample = 0; sample < nbMeasures; sample++) {
        // Execute for every sample
        auto start = steady_clock::now();

        for (int id = 0; id < nbThreads; id++) {
            // To call the threads
            threads[id] = std::thread([this] {
                executeBench();
            });
            // pthread_setaffinity_np(threads[id].native_handle(),
            //                     sizeof(cpu_set_t), &cpusets[id]);
        }
    
        for (int id = 0; id < nbThreads; id++) {
            // Waiting for the threads
            threads[id].join();
        }

        u64 duration = duration_cast<nanoseconds>(steady_clock::now() - start).count();
        if (sample >= 0) {
            measures[sample] = ((16.f * getNbIterations()) / duration);
        }
        std::cout << "\r# " << name << ": run " << sample + 1 << "/" << nbMeasures << std::flush;
    }
    std::cout << std::endl;
}

json LoadTest::getJson() {
    json loadTestJson = json::object();
    loadTestJson["name"] = getName();
    for (int i = 0; i < nbMeasures; i++) {
        loadTestJson["results"][i] = measures[i];
    }
    return loadTestJson;
}