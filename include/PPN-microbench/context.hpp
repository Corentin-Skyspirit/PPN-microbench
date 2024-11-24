#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <PPN-microbench/constants.hpp>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <regex>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

using json = nlohmann::json;

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
    static Context &getInstance();
    void operator=(Context const &) = delete;
    ~Context();

    json getJson();
};

#endif