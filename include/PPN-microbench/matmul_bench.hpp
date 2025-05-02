#ifndef PPN_MICROBENCH_MATRIX_HPP
#define PPN_MICROBENCH_MATRIX_HPP

#include <vector>

#include <nlohmann/json.hpp>

#include <PPN-microbench/microbench.hpp>

// MatMulBench class inherits from Microbench
class MatMulBench : public Microbench {
  private:
    /// Memory sizes.
    std::vector<uint64_t> sizes_;
    /// Mean execution times (in seconds).
    std::vector<double> avg_times_;
    /// Mean compute performance (in Gflop/s).
    /// Vector length depends on the number of benchmarked sizes.
    std::vector<double> avg_perfs_;
    /// Standard deviation on compute performance (in Gflop/s).
    /// Vector length depends on the number of benchmarked sizes.
    std::vector<double> err_perfs_;

  public:
    MatMulBench() : MatMulBench(5) {}
    MatMulBench(int reps);

    // Function to run the benchmark, overrides the base class method
    void run() override;

    // Function to get the results in JSON format, overrides the base class
    // method
    json getJson() override;
};

#endif
