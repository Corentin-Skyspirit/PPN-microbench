#include <PPN-microbench/ops.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

Ops::Ops(int reps) : Microbench("OPS", reps) {
    cpus = context.getJson()["cpu_info"]["cpus"];
}

Ops::~Ops() {}

template <class T> void Ops::benchhaha(T one) {
    T acc = one;
    for (size_t i = 0; i < N_OPS; i++) {
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
        acc += one;
    }
}

template <class T> void Ops::benchSIMD(T one) {
    // I can't figure out how to make it work :(
}

void Ops::run() {

    std::thread threads[cpus];
    time_point<high_resolution_clock> t1, t2;
    std::vector<size_t> mapping = context.getJson()["cpu_info"]["mapping"];
    cpu_set_t cpusets[cpus];

    for (size_t i = 0; i < cpus; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(mapping[i], &cpusets[i]);
    }

    for (int j = 0; j < RUNS; j++) {

        // i32
        t1 = high_resolution_clock::now();
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->benchhaha((i32)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        t2 = high_resolution_clock::now();

        results[0][j] = (t2 - t1).count();

        // i64
        t1 = high_resolution_clock::now();
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->benchhaha((i64)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        t2 = high_resolution_clock::now();

        results[1][j] = (t2 - t1).count();

        // f32
        t1 = high_resolution_clock::now();
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->benchhaha((float)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        t2 = high_resolution_clock::now();

        results[2][j] = (t2 - t1).count();

        // f64
        t1 = high_resolution_clock::now();
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->benchhaha((double)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        t2 = high_resolution_clock::now();

        results[3][j] = (t2 - t1).count();
    }
}

json Ops::getJson() {
    json obj;

    obj["name"] = name;
    obj["ops_count"] = N_OPS * 16;
    obj["results"] = json::array();

    for (int i = 0; i < 6; i++) {
        obj["results"][i] = json::array();
        for (int j = 0; j < RUNS; j++) {
            obj["results"][i].push_back(results[i][j]);
        }
    }

    return obj;
}