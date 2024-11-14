#ifndef CONTEXT_HPP
#define CONTEXT_HPP

/*
 *
 *   Big up to https://github.com/cpredef/predef
 *
 */

#include <PPN-microbench/constants.hpp>

#include <iostream>
#include <set>
#include <string>
#include <unistd.h>

class Context {
  private:
    // Would have loved to use enums here, but unfortunaly we are not in java :(
    std::string cpuArchi;
    size_t wordSize;
    size_t cpus;
    std::set<std::string> simd;
    size_t memory;
    size_t l1;
    size_t l2;
    size_t l3;

    void cpuInfo();
    void memoryInfo();

  public:
    Context();
    ~Context();

    void print();
};

#endif