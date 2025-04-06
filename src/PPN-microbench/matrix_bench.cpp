#include <PPN-microbench/matrix_bench.hpp>

Matrix_bench::Matrix_bench() : Microbench("Matrix Multiplication", 1) {
    // Initialize the memory sizes in bytes for the benchmark
    mem_sizes = {256, 512, 1024, 2048};
}

Matrix_bench::~Matrix_bench() {}

void Matrix_bench::run() {
    for (auto N : mem_sizes) {
        std::vector<double> A(N * N, 1.0);
        std::vector<double> B(N * N, 1.0);
        std::vector<double> C(N * N, 0.0);

        auto start = std::chrono::high_resolution_clock::now();

        // Perform matrix multiplication using cblas_dgemm
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    N, N, N,
                    1.0, A.data(), N, B.data(), N,
                    0.0, C.data(), N);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        double duration = elapsed.count();
        double ops = 2.0 * N * N * N; // Number of double-precision operations
        double Gflop_rate = (ops / duration)/1e9; // Gflop/s

        time_seconds.push_back(duration);
        Gflops.push_back(Gflop_rate);
    }
}

json Matrix_bench::getJson() {
    json j;
    for (size_t i = 0; i < mem_sizes.size(); ++i) {
        j.push_back({
            {"size", mem_sizes[i]},
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
        {"results", j},
        {"summary", summary}
    };
}
