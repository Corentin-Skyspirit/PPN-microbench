#ifndef PPN_MICROBENCH_CACHE_HPP
#define PPN_MICROBENCH_CACHE_HPP

// Include necessary headers

#include <PPN-microbench/microbench.hpp>

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <random>

// Cache_latency class inherits from Microbench
class CacheLatency : public Microbench {
  private:
    // Vectors to store memory sizes and times
    std::vector<uint64_t> mem_sizes; 
    std::vector<double> mem_times;

    double measure_ns(uint64_t size, uint64_t iterations);

  public:
    // Constructor
    CacheLatency();

    // Destructor
    ~CacheLatency();

    // Function to run the benchmark, overrides the base class method
    void run() override;

    // Function to get the results in JSON format, overrides the base class
    // method
    json getJson() override;
};

#endif