#include <PPN-microbench/mem_bandwidth.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

MemoryBandwidth::MemoryBandwidth() : Microbench("Memory bandwidth", 5) {}

// https://github.com/besnardjb/memmapper/blob/master/cache.c
void MemoryBandwidth::run() {
    spdlog::set_level(spdlog::level::debug);

    time_point<high_resolution_clock> t1, t2;

    char *source = new char[max_size];
    char *dest = new char[max_size];

    uint64_t reps = 100000;

    spdlog::debug("touching data...");
    for (uint64_t i = 0; i < max_size; i++) {
        source[i] = rand() % 256;
    }
    spdlog::debug("done!");

    int cpt = 0;
    for (uint64_t size = min_size; size <= max_size; size *= 2) {

        if (size >= 1024 * 1024 * 2)
            reps = 100;

        t1 = high_resolution_clock::now();

        for (int j = 0; j < reps; j++) {
            memcpy(dest, source, size);
        }

        t2 = high_resolution_clock::now();

        uint64_t time = (t2 - t1).count();

        // B/ns AKA GB/s
        double bandwidth = (double)(size * reps) / (double)time;

        res[cpt][0] = size;
        res[cpt][1] = reps;
        res[cpt][2] = time;

        spdlog::debug("{:<10}KB {:>7}reps {:.2f} GB/s {:.3f}s", size / 1024, reps, bandwidth, (double)time / 1e9);
        cpt += 1;
    }

    delete[] source;
    delete[] dest;
}

json MemoryBandwidth::getJson() {
    json obj;

    obj["name"] = name;
    obj["results"]["sizes"] = json::array();
    obj["results"]["reps"] = json::array();
    obj["results"]["time"] = json::array();

    for (int i = 0; i < 20; i++) {
        obj["results"]["sizes"].push_back(res[i][0]);
        obj["results"]["reps"].push_back(res[i][1]);
        obj["results"]["time"].push_back(res[i][2]);
    }

    return obj;
}