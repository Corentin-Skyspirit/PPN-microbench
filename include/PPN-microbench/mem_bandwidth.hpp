#ifndef PPN_MICROBENCH_OPS_HPP
#define PPN_MICROBENCH_OPS_HPP

#include <PPN-microbench/microbench.hpp>

#include <chrono>
#include <span>
#include <string.h>

class MemoryBandwidth : public Microbench {
  private:
    const uint64_t min_size = 1024 * 2;
    const uint64_t max_size = 1024 * 1024 * 1024;

    int warmups = 1;

    uint64_t meta[20][2];
    std::vector<u_int64_t> data;


  public:
    MemoryBandwidth();

    void run();
    json getJson();
};

#endif