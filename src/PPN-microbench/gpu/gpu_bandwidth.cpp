#include <PPN-microbench/gpu_bandwidth.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

GPUBandwidth::GPUBandwidth() : Microbench("GPU_Bandwidth", 5) {}

bool GPUBandwidth::gpuerr(hipError_t err) {
    if (err != hipSuccess) {
        spdlog::error("hip error: {}", hipGetErrorString(err));
        spdlog::error("cancelling bench...");
        bench_info = "Bench returned the following HIP error: " + std::string(hipGetErrorString(err));
        return true;
    }
    return false;
}

bool GPUBandwidth::gpuprep() {
    int n_devices;
    hipError_t err;
    err = hipGetDeviceCount(&n_devices);
    if (!n_devices) {
        spdlog::warn("No hip capable device, skipping !");
        bench_info = "Could not find any hip capable device, benchmark is skipped.";
        return false;
    }

    spdlog::info("Number of HIP devices {}", n_devices);
    int device;
    hipDeviceProp_t props;
    err = hipGetDeviceProperties(&props, 0);
    spdlog::info("Device 0 name: {}", props.name);
    spdlog::info("Device 0 memory: {} Bytes", props.totalGlobalMem);

    return true;
}

void GPUBandwidth::_run() {
    char *buff;
    char *array;
    time_point<high_resolution_clock> t1, t2;

    array = new char[MAX_SIZE];
    spdlog::debug("Touching data...");
    for (uint64_t i = 0; i < MAX_SIZE; i++) {
        array[i] = rand();
    }
    spdlog::debug("Done!");

    GPUERR(hipMalloc(&buff, MAX_SIZE))

    spdlog::debug("Warming up...");
    for (int i = 0; i < 500; i++) {
        GPUERR(hipMemcpy(buff, array, MAX_SIZE, hipMemcpyHostToDevice))
        GPUERR(hipDeviceSynchronize())
    }

    for (int rep = 0; rep < nbIterations; rep++) {
        spdlog::debug("run {}/{}", rep+1, nbIterations);
        int cpt = 0;
        for (size_t size = 1024; size <= MAX_SIZE; size *= 2) {
            t1 = high_resolution_clock::now();
            for (int i = 0; i < 1000; i++) {
                GPUERR(hipMemcpy(buff, array, size, hipMemcpyHostToDevice))
                GPUERR(hipDeviceSynchronize())
            }
            t2 = high_resolution_clock::now();
            
            uint64_t time = (t2 - t1).count() / 1000;
            spdlog::debug("size: {}MiB, {}ms, {}GB/s", (float)size / (1<<20), time / 1e6, (float)size / time);
            meta[cpt] = size;
            data[rep][cpt] = time;
            cpt++;
        }
    }

    delete[] array;
}

void GPUBandwidth::run() {
    if (gpuprep()) _run();
}

json GPUBandwidth::getJson() {
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