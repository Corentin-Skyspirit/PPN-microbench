#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <PPN-microbench/constants.hpp>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <set>
#include <string>
#include <thread>
#include <unistd.h>

using json = nlohmann::json;

class Context {
  private:
    std::string cpuArchi;
    size_t wordSize;
    size_t cpus;
    size_t threads;
    bool hyperthreaded;
    std::set<std::string> simd;
    size_t memory;
    // cache size is sum of all
    size_t l1d;
    size_t l1i;
    size_t l2;
    size_t l3;

    Context();

    void cpuInfo();
    void memoryInfo();

  public:
    static Context &getInstance();
    void operator=(Context const &) = delete;
    ~Context();

    void print();
    json getJson();
};

#endif