#include <PPN-microbench/ops.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

Ops::Ops(int reps) : Microbench("OPS", reps) {
    cpus = context.getCpus();
    size_t rnd = high_resolution_clock::to_time_t(high_resolution_clock::now());
    n_ops = 1024 * 1024 * 8 + (rnd % 123123);

    std::vector<size_t> mapping = context.getThreadMapping();
    cpusets = new cpu_set_t[cpus];
    for (size_t i = 0; i < cpus; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(mapping[i], &cpusets[i]);
    }
}

Ops::~Ops() {
    delete[] cpusets;
}

size_t Ops::wrap(void (*f)(int64_t)) {
    time_point<high_resolution_clock> t1, t2;

    t1 = high_resolution_clock::now();
    {
        std::jthread threads[cpus];
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::jthread([this, f] { f(n_ops); });
            pthread_setaffinity_np(threads[k].native_handle(), sizeof(cpu_set_t), &cpusets[k]);
        }
    }
    t2 = high_resolution_clock::now();

    return (t2 - t1).count();
}

void Ops::run() {

    // Warmup runs
    for (int i = 0; i < WARMUP_RUNS; i++) {
        wrap(SIMD_FLOAT_MAX_FN);
    }

    // Actual runs
    for (int i = 0; i < RUNS; i++) {

        // i32
        results[0][i] = wrap(ADD_i32);

        // i64
        results[1][i] = wrap(ADD_i64);

        // f32
        results[2][i] = wrap(ADD_f32);

        // f64
        results[3][i] = wrap(ADD_f64);

        // i64 SIMD
        results[4][i] = wrap(SIMD_INT_MAX_FN);

        // f64 SIMD
        results[5][i] = wrap(SIMD_FLOAT_MAX_FN);
    }
}

json Ops::getJson() {
    json obj;

    obj["name"] = name;
    obj["ops_count"] = n_ops * 16;
    obj["results"] = json::array();

    for (int i = 0; i < 6; i++) {
        obj["results"][i] = json::array();
        for (int j = 0; j < RUNS; j++) {
            obj["results"][i].push_back(results[i][j]);
        }
    }

    return obj;
}