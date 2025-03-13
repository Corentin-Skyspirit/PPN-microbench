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

    uint64_t res[20][3];

  public:
    MemoryBandwidth();

    void run();
    json getJson();
};

#endif