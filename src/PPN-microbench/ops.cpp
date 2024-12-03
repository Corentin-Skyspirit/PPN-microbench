#include <PPN-microbench/ops.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

Ops::Ops(int reps) : Microbench("OPS", reps) {
    cpus = context.getJson()["cpu_info"]["cpus"];
    size_t rnd = high_resolution_clock::to_time_t(high_resolution_clock::now());
    n_ops = 1024 * 1024 * 8 + (rnd % 123123);
}

Ops::~Ops() {}

template <class T> void Ops::benchhaha(T val) {
    T acc = val;
    for (size_t i = 0; i < n_ops; i++) {
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
        acc += val;
    }
}

template <class T> void Ops::benchSIMD(T one) {
    // I can't figure out how to make it work :(
}

void Ops::run() {

    // std::jthread threads[cpus];
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
        {
            std::jthread threads[cpus];
            for (size_t k = 0; k < cpus; k++) {
                threads[k] = std::jthread([this, t1] {
                    this->benchhaha((i32)t1.time_since_epoch().count());
                });
                pthread_setaffinity_np(threads[k].native_handle(),
                                       sizeof(cpu_set_t), &cpusets[k]);
            }
        }
        t2 = high_resolution_clock::now();
        results[0][j] = (t2 - t1).count();

        // i64
        t1 = high_resolution_clock::now();
        {
            std::jthread threads[cpus];
            for (size_t k = 0; k < cpus; k++) {
                threads[k] = std::jthread([this, t1] {
                    this->benchhaha((i64)t1.time_since_epoch().count());
                });
                pthread_setaffinity_np(threads[k].native_handle(),
                                       sizeof(cpu_set_t), &cpusets[k]);
            }
        }
        t2 = high_resolution_clock::now();
        results[1][j] = (t2 - t1).count();

        // f32
        t1 = high_resolution_clock::now();
        {
            std::jthread threads[cpus];
            for (size_t k = 0; k < cpus; k++) {
                threads[k] = std::jthread([this, t1] {
                    this->benchhaha((float)t1.time_since_epoch().count());
                });
                pthread_setaffinity_np(threads[k].native_handle(),
                                       sizeof(cpu_set_t), &cpusets[k]);
            }
        }
        t2 = high_resolution_clock::now();
        results[2][j] = (t2 - t1).count();

        // f64
        t1 = high_resolution_clock::now();
        {
            std::jthread threads[cpus];
            for (size_t k = 0; k < cpus; k++) {
                threads[k] = std::jthread([this, t1] {
                    this->benchhaha((double)t1.time_since_epoch().count());
                });
                pthread_setaffinity_np(threads[k].native_handle(),
                                       sizeof(cpu_set_t), &cpusets[k]);
            }
        }
        t2 = high_resolution_clock::now();
        results[3][j] = (t2 - t1).count();
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