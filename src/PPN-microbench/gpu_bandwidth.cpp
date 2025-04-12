#include <PPN-microbench/gpu_bandwidth.hpp>

GPUBandwidth::GPUBandwidth() : Microbench("GPU_Bandwidth", 5) {}

void GPUBandwidth::run() {

    int n_devices;
    hipGetDeviceCount(&n_devices);
    spdlog::info("{}", n_devices);

}

json GPUBandwidth::getJson() {
    json j;
    return j;
}