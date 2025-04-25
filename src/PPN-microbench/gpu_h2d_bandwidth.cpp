#include <PPN-microbench/gpu_h2d_bandwidth.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

GPUH2DBandwidth::GPUH2DBandwidth() : Microbench("GPU_H2D_Bandwidth", 5) {}

void GPUH2DBandwidth::run() {
    // skip if no CL devices
    if (context.getDevices().size() == 0) {
        bench_info = "Could not find any OpenCL device, benchmark is skipped.";
        spdlog::warn(bench_info);
        return;
    }

    char *buffer;
    cl::Buffer buffer_d;
    time_point<high_resolution_clock> t1, t2;

    buffer = new char[MAX_SIZE];
    spdlog::debug("Touching data...");
    for (uint64_t i = 0; i < MAX_SIZE; i++) {
        buffer[i] = rand();
    }
    spdlog::debug("Done!");

    buffer_d = cl::Buffer(mainDeviceContext, CL_MEM_READ_WRITE, MAX_SIZE);

    spdlog::debug("Warming up...");
    for (int i = 0; i < 500; i++) {
        mainDeviceQueue.enqueueWriteBuffer(buffer_d, CL_TRUE, 0, MAX_SIZE, buffer);
    }

    for (int rep = 0; rep < nbIterations; rep++) {
        spdlog::debug("run {}/{}", rep+1, nbIterations);
        int cpt = 0;
        for (size_t size = 1024; size <= MAX_SIZE; size *= 2) {
            t1 = high_resolution_clock::now();
            for (int i = 0; i < 500; i++) {
                mainDeviceQueue.enqueueWriteBuffer(buffer_d, CL_TRUE, 0, size, buffer);
            }
            t2 = high_resolution_clock::now();
            
            uint64_t time = (t2 - t1).count() / 500;
            spdlog::debug("size: {}MiB, {}ms, {}GB/s", (float)size / (1<<20), time / 1e6, (float)size / time);
            meta[cpt] = size;
            data[rep][cpt] = time;
            cpt++;
        }
    }

    delete[] buffer;
}

json GPUH2DBandwidth::getJson() {
    json obj;
    obj["name"] = name;
    obj["info"] = bench_info;

    for (int rep = 0; rep < nbIterations; rep++) {
        for (int cpt = 0; cpt <= 20; cpt++) {
            obj["meta"][cpt] = meta[cpt];
            obj["data"][rep][cpt] = data[rep][cpt];
        }
    }

    return obj;
}