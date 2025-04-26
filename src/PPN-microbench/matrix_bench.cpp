#include <PPN-microbench/matrix_bench.hpp>

Matrix_bench::Matrix_bench() : Microbench("Matrix Multiplication", 1) {
    // Determine the number of iterations based on the number of physical cores
        int num_cores;
        num_cores = context.getCpus(); 
        std::cout << "Number of physical cores " << num_cores << std::endl;
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
        double Gflop_rate = (ops / duration)/1e9; // Gflop/s

        total_duration += duration;
        total_gflops += Gflop_rate;
        }

        // Calculate the average results over the repetitions
        double duration = total_duration / repeats;
        double Gflop_rate = total_gflops / repeats;
        
        // Store the results
        time_seconds.push_back(duration);
        Gflops.push_back(Gflop_rate);
    }
}

json Matrix_bench::getJson() {
    json j;
    for (size_t i = 0; i < N_sizes.size(); ++i) {
        j.push_back({
            {"size", N_sizes[i]},
            {"time_seconds", time_seconds[i]},
            {"Gflops", Gflops[i]}
        });
    }
    // Calculate the maximum Gflops to get the highest performance peak
    // Calculate the average Gflops and time to get the typical performance
    double max_gflops = *std::max_element(Gflops.begin(), Gflops.end());
    double avg_gflops = std::accumulate(Gflops.begin(), Gflops.end(), 0.0) / Gflops.size();
    double avg_time = std::accumulate(time_seconds.begin(), time_seconds.end(), 0.0) / time_seconds.size();
    
    // Create a JSON object to store the summary
    json summary = {
        {"gflops_max", max_gflops},
        {"gflops_avg", avg_gflops},
        {"time_avg", avg_time}
    };

    return {
        {"name", name},
        {"results", j},
        {"summary", summary}
    };
}
