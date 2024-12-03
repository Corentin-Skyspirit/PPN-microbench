#include <PPN-microbench/ops.hpp>

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
    struct timespec t1, t2;
    std::vector<size_t> mapping = context.getJson()["cpu_info"]["mapping"];
    cpu_set_t cpusets[cpus];

    for (size_t i = 0; i < cpus; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(mapping[i], &cpusets[i]);
    }

    for (int j = 0; j < RUNS; j++) {

        // i32
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->benchhaha((i32)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        clock_gettime(CLOCK_MONOTONIC, &t2);

        results[0][j] =
            t2.tv_sec * 1e9 + t2.tv_nsec - (t1.tv_sec * 1e9 + t1.tv_nsec);

        // i64
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->benchhaha((i64)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        clock_gettime(CLOCK_MONOTONIC, &t2);

        results[1][j] =
            t2.tv_sec * 1e9 + t2.tv_nsec - (t1.tv_sec * 1e9 + t1.tv_nsec);

        // f32
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->benchhaha((float)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        clock_gettime(CLOCK_MONOTONIC, &t2);

        results[2][j] =
            t2.tv_sec * 1e9 + t2.tv_nsec - (t1.tv_sec * 1e9 + t1.tv_nsec);

        // f64
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->benchhaha((double)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        clock_gettime(CLOCK_MONOTONIC, &t2);

        results[3][j] =
            t2.tv_sec * 1e9 + t2.tv_nsec - (t1.tv_sec * 1e9 + t1.tv_nsec);
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