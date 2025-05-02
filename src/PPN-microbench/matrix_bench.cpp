#include <PPN-microbench/matrix_bench.hpp>

Matrix_bench::Matrix_bench() : Microbench("Matrix Multiplication", 1) {
    // Determine the number of iterations based on the number of physical cores
        int num_cores;
        num_cores = context.getCpus(); 
        int max_iterations = num_cores;

    // Initialize the N size for N*N matrix for the benchmark
    for (int i = 1; i <= max_iterations; ++i) {
        N_sizes.push_back(512 * i);
    }
}


Matrix_bench::~Matrix_bench() {}

void Matrix_bench::run() {
}

json Matrix_bench::getJson() {
    json j;
    for (size_t i = 0; i < N_sizes.size(); ++i) {
        j.push_back({
            {"size", N_sizes[i]},
            {"time_seconds", time_seconds[i]},
            {"Gflops", Gflops[i]},
            {"error_Gflops", error_Gflops[i]} // Include the error in the JSON
        });
    }
    // Calculate the maximum Gflops to get the highest performance peak
    double max_gflops = *std::max_element(Gflops.begin(), Gflops.end());
    
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
