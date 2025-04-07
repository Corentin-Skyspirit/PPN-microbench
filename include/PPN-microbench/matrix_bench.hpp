#ifndef PPN_MICROBENCH_MATRIX_HPP
#define PPN_MICROBENCH_MATRIX_HPP

// Include necessary headers

#include <PPN-microbench/microbench.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <Eigen/Dense>


// Matrix class inherits from Microbench
class Matrix_bench : public Microbench {
  private:
    
    std::vector<uint64_t> mem_sizes; // Vector to store memory sizes
    std::vector<double> time_seconds; // Vector to store time in seconds
    std::vector<double> Gflops; // Vector to store floating point operations
    

  public:
    // Constructor
    Matrix_bench();

    // Destructor
    ~Matrix_bench();

    // Function to run the benchmark, overrides the base class method
    void run() override;

    // Function to get the results in JSON format, overrides the base class
    // method
    json getJson() override;
};

#endif