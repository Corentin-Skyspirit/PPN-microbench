#ifndef PPN_MICROBENCH_STREAM_HPP
#define PPN_MICROBENCH_STREAM_HPP

#include <PPN-microbench/microbench.hpp>

#include <chrono>
#include <thread>
#include <vector>

static double alpha;
static std::vector<double> a;
static std::vector<double> b;
static std::vector<double> c;

void init(uint64_t start, uint64_t end);
void copy(uint64_t start, uint64_t end);
void mul(uint64_t start, uint64_t end);
void add(uint64_t start, uint64_t end);
void triad(uint64_t start, uint64_t end);

class Stream : public Microbench {
  private:
    const uint64_t MAX_SIZE = (1 << 27) / sizeof(double);
    const uint64_t MIN_SIZE = 1024 / sizeof(double);

    size_t cpus;
    std::vector<cpu_set_t> cpusets;

    uint64_t results[4][10][17];

    template <typename F>
    uint64_t wrap(F&&);

  public:
    Stream();

    void run();
    json getJson();
};

#endif