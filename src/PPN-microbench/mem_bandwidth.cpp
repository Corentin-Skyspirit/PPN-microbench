#include <PPN-microbench/mem_bandwidth.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

MemoryBandwidth::MemoryBandwidth() : Microbench("Memory bandwidth", 5) {
    data.reserve(nbIterations * 20);
}

// https://github.com/besnardjb/memmapper/blob/master/cache.c
void MemoryBandwidth::run() {
    spdlog::set_level(spdlog::level::debug);

    time_point<high_resolution_clock> t1, t2;

    char *source = new char[max_size];
    char *dest = new char[max_size];

    uint64_t start_reps = 100000;
    uint64_t end_reps = 100;

    spdlog::debug("touching data...");
    for (uint64_t i = 0; i < max_size; i++) {
        source[i] = rand() % 256;
    }
    spdlog::debug("done!");

    for (int i = 0; i < nbIterations + warmups; i++) {
        spdlog::debug("run {}.", i);
        int cpt = 0;
        for (uint64_t size = min_size; size <= max_size; size *= 2) {
            
            int reps = (1l << 33) / size + 50;
            
            t1 = high_resolution_clock::now();
            
            for (int j = 0; j < reps; j++) {
                memcpy(dest, source, size);
            }
            
            t2 = high_resolution_clock::now();
            
            uint64_t time = (t2 - t1).count();
            
            // B/ns AKA GB/s
            double bandwidth = (double)(size * reps) / (double)time;
            
            meta[cpt][0] = size;
            meta[cpt][1] = reps;

            data[i * 20 + cpt] = time;

            spdlog::debug("{:<10}KB {:>7}reps {:.2f} GB/s {:.3f}s", size / 1024, reps, bandwidth, (double)time / 1e9);
            cpt += 1;
        }
    }

    delete[] source;
    delete[] dest;
}

json MemoryBandwidth::getJson() {
    json obj;

    obj["name"] = name;
    obj["results"]["runs"] = nbIterations;

    for (int i = 0; i < 20; i++) {
        obj["results"]["sizes"].push_back(meta[i][0]);
        obj["results"]["reps"].push_back(meta[i][1]);
    }
    for (int j = 0; j < nbIterations; j++) {
        for (int i = 0; i < 20; i++) {
            obj["results"]["times"][j].push_back(data[j * 20 + i]);
        }
    }

    return obj;
}