#include <PPN-microbench/gpu_bandwidth.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

GPUBandwidth::GPUBandwidth() : Microbench("GPU_Bandwidth", 5) {}

bool GPUBandwidth::gpuprep() {
    int n_devices;
    hipGetDeviceCount(&n_devices);
    if (!n_devices) {
        spdlog::warn("No hip capable device, skipping !");
        return false;
    }

    spdlog::info("Number of HIP devices {}", n_devices);
    int device;
    hipDeviceProp_t props;
    hipGetDeviceProperties(&props, 0);
    spdlog::info("Device 0 name: {}", props.name);
    spdlog::info("Device 0 memory: {}", props.totalGlobalMem);
    max_buffer_size = props.totalGlobalMem;

    return true;
}

void GPUBandwidth::_run() {
    char *buff;
    char *array;
    uint64_t size = 1 << 30;
    time_point<high_resolution_clock> t1, t2;

    array = (char *) calloc(size, sizeof(char));
    
    hipMalloc(&buff, size);
    t1 = high_resolution_clock::now();
    hipMemcpy(buff, array, size, hipMemcpyHostToDevice);
    hipDeviceSynchronize();
    t2 = high_resolution_clock::now();

    spdlog::info("{}", (t2 - t1).count() / 1000000);
}

void GPUBandwidth::run() {
    if (gpuprep()) _run();
}

json GPUBandwidth::getJson() {
    json j;
    return j;
}