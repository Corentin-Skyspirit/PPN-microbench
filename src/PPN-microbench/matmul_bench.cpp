#include <PPN-microbench/matmul_bench.hpp>

#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

#include <Eigen/Dense>
#include <spdlog/spdlog.h>

MatMulBench::MatMulBench(int reps) : Microbench("Matrix Multiplication", reps) {
    // Determine the number of iterations based on the number of physical cores
    const int num_cores = context.getCpus();

    // Initialize the N size for N*N matrix for the benchmark, starting at size 512x512
    for (int i = 1; i <= num_cores; ++i) {
        sizes_.push_back(512 * i);
    }

    const auto n_sizes = sizes_.size();
    avg_times_.reserve(n_sizes);
    avg_perfs_.reserve(n_sizes);
    err_perfs_.reserve(n_sizes);
}

void MatMulBench::run() {
    // Number of benchmark warmups
    constexpr int N_WARMUPS = 1;
    // Number of benchmark repetitions
    const int N_REPETITIONS = nbIterations;

    std::vector<double> run_perf(N_REPETITIONS);
    for (uint64_t N : sizes_) {
        const double N_fp = static_cast<double>(N);
        // Number of double-precision floating-point operations
        const double N_GFLOP = (2.0 * N_fp * N_fp * N_fp) / 1.0e9;

        // Initialize matrices
        const Eigen::MatrixXd A = Eigen::MatrixXd::Random(N, N);
        const Eigen::MatrixXd B = Eigen::MatrixXd::Random(N, N);
        Eigen::MatrixXd C = Eigen::MatrixXd::Random(N, N);

        // Warmup runs
        for (int w = 0; w < N_WARMUPS; ++w) {
            C = A * B;
        }

        double total_elapsed_s = 0.0;
        double total_gflop_per_s = 0.0;
        // Benchmarked runs
        for (int r = 0; r < N_REPETITIONS; ++r) {
            const auto t0 = std::chrono::high_resolution_clock::now();
            C = A * B;
            const auto t1 = std::chrono::high_resolution_clock::now();

            const double elapsed_s = std::chrono::duration<double>(t1 - t0).count();
            const double gflop_per_s = (N_GFLOP / elapsed_s);
            total_elapsed_s += elapsed_s;
            total_gflop_per_s += gflop_per_s;
            run_perf[r] = gflop_per_s;
        }
        // Calculate the average results over the repetitions
        double avg_elapsed_s = total_elapsed_s / static_cast<double>(N_REPETITIONS);
        double avg_gflop_per_s = total_gflop_per_s / static_cast<double>(N_REPETITIONS);
        // Calculate the standard deviation on compute performance
        double stddev_gflop_per_s = std::sqrt(std::accumulate(
            run_perf.begin(),
            run_perf.end(),
            0.0,
            [=](double acc, double gflop_per_s) {
                return acc + (gflop_per_s - avg_gflop_per_s) * (gflop_per_s - avg_gflop_per_s);
            }
        ) / static_cast<double>(N_REPETITIONS));

        // Store the results
        avg_times_.push_back(avg_elapsed_s);
        avg_perfs_.push_back(avg_gflop_per_s);
        err_perfs_.push_back(stddev_gflop_per_s);
    }
}

json MatMulBench::getJson() {
    json j;
    for (size_t i = 0; i < sizes_.size(); ++i) {
        j.push_back({
            {"size", sizes_[i]},
            {"time_seconds", avg_times_[i]},
            {"Gflops", avg_perfs_[i]},
            {"error_Gflops", err_perfs_[i]} // Include the error in the JSON
        });
    }
    // Calculate the maximum Gflops to get the highest performance peak
    double max_gflops = *std::max_element(avg_perfs_.begin(), avg_perfs_.end());
    
    // Create a JSON object to store the summary
    json summary = {
        {"gflops_max", max_gflops}
    };

    return {
        {"name", name},
        {"results", j},
        {"summary", summary}
    };
}
