#include <PPN-microbench/mem_bandwidth.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

MemoryBandwidth::MemoryBandwidth() : Microbench("Memory bandwidth", 5) {
    int cpus = context.getCpus();

    data_singlecore.reserve(nbIterations * 20);
    data_multicore.reserve(nbIterations * 20 * cpus);

    std::vector<size_t> mapping = context.getThreadMapping();
    cpusets = new cpu_set_t[cpus];
    for (size_t i = 0; i < cpus; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(mapping[i], &cpusets[i]);
    }
}

void MemoryBandwidth::run() {
    int cpus = context.getCpus();
    source = new char[max_size * cpus];
    dest = new char[max_size * cpus];
    
    spdlog::debug("touching data...");
    for (uint64_t i = 0; i < max_size; i++) {
        source[i] = rand() % 256;
    }
    spdlog::debug("done!");

    bench(1, data_singlecore);
    bench(context.getCpus(), data_multicore);

    delete[] source;
    delete[] dest;
}

void MemoryBandwidth::bench(int cpus, std::vector<uint64_t> &vec) {
    uint64_t start_reps = 100000;
    uint64_t end_reps = 100;

    for (int i = 0; i < nbIterations + warmups; i++) {
        spdlog::debug("run {}.", i);
        int cpt = 0;
        uint64_t res_buffer[cpus];

        for (uint64_t size = min_size; size <= max_size; size *= 2) {
            uint64_t reps = (1l << 33) / size + 50;
            {
                std::jthread threads[cpus];
                for (int j = 0; j < cpus; j++) {
                    threads[j] = std::jthread([&](int j) { 
                        auto t1 = high_resolution_clock::now();
                        for (uint64_t k = 0; k < reps; k++) {
                            memcpy(dest+size*j, source+size*j, size); 
                        }
                        auto t2 = high_resolution_clock::now();
                        res_buffer[j] = (t2 - t1).count();
                    }, j);
                    pthread_setaffinity_np(threads[j].native_handle(), sizeof(cpu_set_t), &cpusets[j]);
                }
            }
            // B/ns AKA GB/s

            meta[0][cpt] = size;
            meta[1][cpt] = reps;

            if (i >= warmups) {
                for (int j = 0; j < cpus; j++) {
                    vec[((i-warmups) * 20 + cpt) * cpus + j] = res_buffer[j];
                }
            }

            double bandwidth = (double)(size * reps) / (double)res_buffer[0];
            spdlog::debug("{:<10}KB {:>7}reps {:.2f} GB/s {:.3f}s", size / 1024, reps, bandwidth, (double)res_buffer[0] / 1e9);
            cpt += 1;
        }
    }
}

json MemoryBandwidth::getJson() {
    int cpus = context.getCpus();
    json obj;

    obj["name"] = name;
    obj["results"]["runs"] = nbIterations;

    for (int i = 0; i < 20; i++) {
        obj["results"]["sizes"].push_back(meta[0][i]);
        obj["results"]["reps"].push_back(meta[1][i]);
    }
    for (int j = 0; j < nbIterations; j++) {
        for (int i = 0; i < 20; i++) {
            obj["results"]["times"]["single"][j].push_back(data_singlecore[j * 20 + i]);
            for (int c = 0; c < cpus; c++) {
                obj["results"]["times"]["multi"][j][c].push_back(data_multicore[(j * 20 + i) * cpus + c]);
            }
        }
    }
    return obj;
}