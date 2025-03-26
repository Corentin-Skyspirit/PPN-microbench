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

    char *source;
    char *dest;

    cpu_set_t *cpusets;

    int warmups = 0;

    uint64_t meta[2][20];
    std::vector<uint64_t> data_singlecore;
    std::vector<uint64_t> data_multicore;

    void bench(int cpus, std::vector<uint64_t> &vec);

  public:
    MemoryBandwidth();

    void run();
    json getJson();
};

#endif