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
    const int repeats = 5; // Number of repeats for each benchmark
    for (auto N : N_sizes) {
        double total_duration = 0.0;
        double total_gflops = 0.0;
    
        for (int i = 0; i < repeats; ++i) {
            
            Eigen::MatrixXd A = Eigen::MatrixXd::Random(N, N);
            Eigen::MatrixXd B = Eigen::MatrixXd::Random(N, N);
            Eigen::MatrixXd C = Eigen::MatrixXd::Random(N, N);

            auto start = std::chrono::high_resolution_clock::now();

            // Perform Dense matrix multiplication using Eigen same as DGEMM
            C = A * B;

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            double duration = elapsed.count();
            double ops = 2.0 * N * N * N; // Number of double-precision operations
            double Gflop_rate = (ops / duration) / 1e9; // Gflop/s

            total_duration += duration;
            total_gflops += Gflop_rate;
            gflops_per_run.push_back(Gflop_rate); // Store Gflops for this run
        }

        // Calculate the average results over the repetitions
        double duration = total_duration / repeats;
        double Gflop_rate = total_gflops / repeats;
        
        // Calculate the standard deviation of Gflops
        double sum_squared_diff = 0.0;
        for (double gflops : gflops_per_run) {
            sum_squared_diff += (gflops - Gflop_rate) * (gflops - Gflop_rate);
        }
        double stddev_gflops = std::sqrt(sum_squared_diff / repeats);

        // Store the results
        time_seconds.push_back(duration);
        Gflops.push_back(Gflop_rate);
        error_Gflops.push_back(stddev_gflops); // Store the error (standard deviation)
    }
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
