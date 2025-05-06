#ifndef PPN_MICROBENCH_CONTEXT_HPP
#define PPN_MICROBENCH_CONTEXT_HPP

#define CL_TARGET_OPENCL_VERSION 300
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include <nlohmann/json.hpp>
#include <CL/opencl.hpp>
#include <spdlog/spdlog.h>

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using json = nlohmann::ordered_json;

class Context {
  private:
    std::string cpuArchi;
    size_t wordSize;
    // Amount of sockets on the node
    size_t sockets;
    // Amount of physical cores on the node
    size_t cpus;
    size_t cpusPerSocket;
    // Amount of virtural core on the node
    size_t threads;
    size_t threadsPerCore;
    // Mapping of the virtual cores to the physical ones
    std::vector<size_t> threadMapping;
    //Max cpu frequency
    size_t max_mhz;
    std::set<std::string> simd;
    size_t memory;
    
    // cache size is PER CORE
    size_t l1d;
    size_t l1i;
    size_t l2;
    size_t l3;

    // OpenCL devices
    std::vector<cl::Device> devices;
    // index of main device in device vector
    size_t mainDeviceIndex = 0;
    cl::Device mainDevice;
    cl::Context mainDeviceContext;
    cl::CommandQueue mainDeviceQueue;

    Context();

    int64_t getFirstInt(const std::string);
    void cpuInfo();
    void memoryInfo();
    void gpuInfo();

  public:
    static Context &getInstance();
    void operator=(Context const &) = delete;
    ~Context();

    const std::string &getCpuArchi() const { return cpuArchi; }
    const size_t &getWordSize() const { return wordSize; }
    const size_t &getSockets() const { return sockets; }
    const size_t &getCpus() const { return cpus; }
    const size_t &getThreads() const { return threads; }
    const std::vector<size_t> getThreadMapping() const { return threadMapping; }
    const size_t &getMax_mhz() const {return max_mhz; }
    const std::set<std::string> &getSIMD() const { return simd; }
    
    const size_t &getMemory() const { return memory; }
    const size_t &getl1d() const { return l1d; }
    const size_t &getl1i() const { return l1i; }
    const size_t &getl2() const { return l2; }
    const size_t &getl3() const { return l3; }

    const std::vector<cl::Device> &getDevices() const { return devices; }
    const cl::Device &getMainDevice() const { return mainDevice; }
    const cl::Context &getMainDeviceContext() const { return mainDeviceContext; }
    const cl::CommandQueue &getMainDeviceQueue() const { return mainDeviceQueue; }

    json getJson();
    size_t getCpus();
    std::vector<size_t> getThreadMapping();
    std::set<std::string> getSimd();
};

#endif