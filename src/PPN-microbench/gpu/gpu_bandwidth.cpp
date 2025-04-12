#include <PPN-microbench/gpu_bandwidth.hpp>

GPUBandwidth::GPUBandwidth() : Microbench("GPU_Bandwidth", 5) {}

void GPUBandwidth::run() {

    int n_devices;
    hipGetDeviceCount(&n_devices);
    spdlog::info("number of HIP devices {}", n_devices);
    int device;
    hipDeviceProp_t props;
    hipGetDeviceProperties(&props, 0);
    spdlog::info("device name: {}", props.name);
}

json GPUBandwidth::getJson() {
    json j;
    return j;
}