#include <PPN-microbench/ops.hpp>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

Ops::Ops(int reps) : Microbench("OPS", reps) {
    cpus = context.getJson()["cpu_info"]["cpus"];
    results = new size_t *[6];
    for (int i = 0; i < 6; i++) {
        results[i] = new size_t[reps];
    }
}

Ops::~Ops() {
    for (int i = 0; i < 6; i++) {
        delete[] results[i];
    }
    delete[] results;
}

template <class T> void Ops::bench(T one) {
    T acc[16];
    for (size_t i = 0; i < N_OPS; i++) {
        acc[0] += one * one;
        acc[1] += one * one;
        acc[2] += one * one;
        acc[3] += one * one;
        acc[4] += one * one;
        acc[5] += one * one;
        acc[6] += one * one;
        acc[7] += one * one;
        acc[8] += one * one;
        acc[9] += one * one;
        acc[10] += one * one;
        acc[11] += one * one;
        acc[12] += one * one;
        acc[13] += one * one;
        acc[14] += one * one;
        acc[15] += one * one;
    }
}

template <class T> void Ops::benchSIMD(T one) {
    // I can't figure out how to make it work :(
}

void Ops::run() {

    steady_clock::time_point t1, t2;
    std::thread threads[cpus];
    std::vector<size_t> mapping = context.getJson()["cpu_info"]["mapping"];
    cpu_set_t cpusets[cpus];

    for (size_t i = 0; i < cpus; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(mapping[i], &cpusets[i]);
    }

    for (int j = 0; j < nbIterations; j++) {

        // i32
        t1 = steady_clock::now();
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->bench((i32)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        t2 = steady_clock::now();

        results[0][j] = duration_cast<nanoseconds>(t2 - t1).count();

        // i64
        t1 = steady_clock::now();
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->bench((i64)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        t2 = steady_clock::now();

        results[1][j] = duration_cast<nanoseconds>(t2 - t1).count();

        // f32
        t1 = steady_clock::now();
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->bench((float)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        t2 = steady_clock::now();

        results[2][j] = duration_cast<nanoseconds>(t2 - t1).count();

        // f64
        t1 = steady_clock::now();
        for (size_t k = 0; k < cpus; k++) {
            threads[k] = std::thread([this] { this->bench((double)1); });
            pthread_setaffinity_np(threads[k].native_handle(),
                                   sizeof(cpu_set_t), &cpusets[k]);
        }
        for (size_t k = 0; k < cpus; k++) {
            threads[k].join();
        }
        t2 = steady_clock::now();

        results[3][j] = duration_cast<nanoseconds>(t2 - t1).count();

        /*

            // i64 SIMD
            t1 = steady_clock::now();
            for (size_t k = 0; k < cpus; k++) {
                threads[k] = std::thread([this] { this->benchSIMD((i64)1); });
                pthread_setaffinity_np(threads[k].native_handle(),
                                    sizeof(cpu_set_t), &cpusets[k]);
            }
            for (size_t k = 0; k < cpus; k++) {
                threads[k].join();
            }
            t2 = steady_clock::now();

            results[4][j] = duration_cast<nanoseconds>(t2 - t1).count();

            // f64 SIMD
            t1 = steady_clock::now();
            for (size_t k = 0; k < cpus; k++) {
                threads[k] = std::thread([this] { this->benchSIMD((double)1);
           }); pthread_setaffinity_np(threads[k].native_handle(),
                                    sizeof(cpu_set_t), &cpusets[k]);
            }
            for (size_t k = 0; k < cpus; k++) {
                threads[k].join();
            }
            t2 = steady_clock::now();

            results[5][j] = duration_cast<nanoseconds>(t2 - t1).count();

        */
    }
}

json Ops::getJson() {
    json obj;

    obj["name"] = name;
    obj["ops_count"] = N_OPS * 16 * 2;
    obj["results"] = json::array();

    for (int i = 0; i < 6; i++) {
        obj["results"][i] = json::array();
        for (int j = 0; j < nbIterations; j++) {
            obj["results"][i].push_back(results[i][j]);
        }
    }

    return obj;
}