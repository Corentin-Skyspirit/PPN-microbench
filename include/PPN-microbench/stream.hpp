#ifndef PPN_MICROBENCH_STREAM_HPP
#define PPN_MICROBENCH_STREAM_HPP

#include <PPN-microbench/microbench.hpp>

#include <chrono>
#include <thread>
#include <vector>

class Stream : public Microbench {
  private:
    const uint64_t MAX_SIZE = (1 << 27) / sizeof(double);
    const uint64_t MIN_SIZE = 1024 / sizeof(double);

    size_t cpus;
    std::vector<cpu_set_t> cpusets;

    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    double alpha;

    void init(uint64_t start, uint64_t end);
    void copy(uint64_t start, uint64_t end);
    void mul(uint64_t start, uint64_t end);
    void add(uint64_t start, uint64_t end);
    void triad(uint64_t start, uint64_t end);

    uint64_t results[4][10][17];

    template <typename F>
    uint64_t wrap(F&&);

  public:
    Stream();

    void run();
    json getJson();
};

#endif