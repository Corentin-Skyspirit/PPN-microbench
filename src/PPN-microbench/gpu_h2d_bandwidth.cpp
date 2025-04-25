#include <PPN-microbench/gpu_h2d_bandwidth.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

GPUH2DBandwidth::GPUH2DBandwidth() : Microbench("GPU_H2D_Bandwidth", 5) {}

void GPUH2DBandwidth::gpuprep() {
    std::vector<cl::Device> tmp_devices;
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    for (int i = 0; i < platforms.size(); i++) {
        platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &tmp_devices);
        for (auto d : tmp_devices) {
            spdlog::debug("found CL device: {}", d.getInfo<CL_DEVICE_NAME>());
            devices.push_back(d);
        }
    }

    if (devices.size() == 0) {
        spdlog::warn("No OpenCL device, skipping !");
        bench_info = "Could not find any OpenCL device, benchmark is skipped.";
        return;
    }

    device = devices[0];
    context = cl::Context({device});
    queue = cl::CommandQueue(context, device);

    spdlog::info("Number of OpenCL devices: {}", devices.size());
    // AMD cards are weird names =(
    std::string device_name = device.getInfo<CL_DEVICE_BOARD_NAME_AMD>() == "" ? device.getInfo<CL_DEVICE_NAME>() :  device.getInfo<CL_DEVICE_BOARD_NAME_AMD>();
    spdlog::info("Device 0 name: {}", device_name);
    spdlog::info("Device 0 memory: {} Bytes", device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>());

    device_info["name"] = device_name;
    device_info["total_mem"] = device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
}

void GPUH2DBandwidth::_run() {
    char *buffer;
    cl::Buffer buffer_d;
    time_point<high_resolution_clock> t1, t2;

    buffer = new char[MAX_SIZE];
    spdlog::debug("Touching data...");
    for (uint64_t i = 0; i < MAX_SIZE; i++) {
        buffer[i] = rand();
    }
    spdlog::debug("Done!");

    buffer_d = cl::Buffer(context, CL_MEM_READ_WRITE, MAX_SIZE);

    spdlog::debug("Warming up...");
    for (int i = 0; i < 500; i++) {
        queue.enqueueWriteBuffer(buffer_d, CL_TRUE, 0, MAX_SIZE, buffer);
    }

    for (int rep = 0; rep < nbIterations; rep++) {
        spdlog::debug("run {}/{}", rep+1, nbIterations);
        int cpt = 0;
        for (size_t size = 1024; size <= MAX_SIZE; size *= 2) {
            t1 = high_resolution_clock::now();
            for (int i = 0; i < 500; i++) {
                queue.enqueueWriteBuffer(buffer_d, CL_TRUE, 0, size, buffer);
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

void GPUH2DBandwidth::run() {
    gpuprep();
    if (devices.size() > 0) _run();
}

json GPUH2DBandwidth::getJson() {
    json obj;
    obj["name"] = name;
    obj["info"] = bench_info;
    obj["device_info"] = device_info;

    for (int rep = 0; rep < nbIterations; rep++) {
        for (int cpt = 0; cpt <= 20; cpt++) {
            obj["meta"][cpt] = meta[cpt];
            obj["data"][rep][cpt] = data[rep][cpt];
        }
    }

    return obj;
}