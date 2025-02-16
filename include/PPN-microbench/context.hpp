#ifndef PPN_MICROBENCH_CONTEXT_HPP
#define PPN_MICROBENCH_CONTEXT_HPP

#include <PPN-microbench/constants.hpp>

#include <fstream>
#include <immintrin.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <regex>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

using json = nlohmann::ordered_json;

extern "C" i32 ADD_X86_i32(i32, i32);
extern "C" i64 ADD_X86_i64(i64, i64);
extern "C" float ADD_X86_f32(float, float);
extern "C" double ADD_X86_f64(double, double);

class Context {
  private:
    std::string cpuArchi;
    size_t wordSize;
    // Amound of sockets on the node
    size_t sockets;
    // Amound of physical cores on the node
    size_t cpus;
    // Amound of virtural core on the node
    size_t threads;
    // Mapping of the virtual cores to the physical ones
    std::vector<size_t> threadMapping;
    std::set<std::string> simd;
    size_t memory;
    // cache size is PER CORE
    size_t l1d;
    size_t l1i;
    size_t l2;
    size_t l3;

    Context();

    i64 getFirstInt(const std::string);
    void cpuInfo();
    void memoryInfo();

  public:
    // PORTABLE FUNCTIONS
    i32 (*_add_i32)(i32, i32);
    i64 (*_add_i64)(i64, i64);
    float (*_add_f32)(float, float);
    double (*_add_f64)(double, double);
    // maximum-length simd operation for 64 integers and floating point numbers
    // template <class T> T (*_add_iSIMD)(T, T);
    // template <class T> T (*_add_fSIMD)(T, T);
    // void *_add_iSIMD;

    static Context &getInstance();
    void operator=(Context const &) = delete;
    ~Context();

    const std::string &getCpuArchi() const { return cpuArchi; }
    const size_t &getWordSize() const { return wordSize; }
    const size_t &getSockets() const { return sockets; }
    const size_t &getCpus() const { return cpus; }
    const size_t &getThreads() const { return threads; }
    const std::vector<size_t> getThreadMapping() const { return threadMapping; }
    const std::set<std::string> &getSIMD() const { return simd; }
    const size_t &getMemory() const { return memory; }
    const size_t &getl1d() const { return l1d; }
    const size_t &getl1i() const { return l1i; }
    const size_t &getl2() const { return l2; }
    const size_t &getl3() const { return l3; }

    // const void *add_i32() const { return _add_i32; }
    // const void *add_i64() const { return _add_i64; }
    // const void *add_f32() const { return _add_f32; }
    // const void *add_f64() const { return _add_f64; }

    json getJson();
    size_t getCpus();
    std::vector<size_t> getThreadMapping();
    std::set<std::string> getSimd();
};

#endif