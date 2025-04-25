#include <PPN-microbench/stream.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

void init() {
    #pragma omp parallel for
    for (uint64_t i = 0; i < a.size(); i++) {
        a[i] = 1;
        b[i] = 1;
        c[i] = 0;
    }
}

void copy() {
    #pragma omp parallel for
    for (uint64_t i = 0; i < a.size(); i++) {
        c[i] = a[i];
    }
}

void mul() {
    #pragma omp parallel for
    for (uint64_t i = 0; i < a.size(); i++) {
        c[i] = alpha * a[i];
    }
}

void add() {
    #pragma omp parallel for
    for (uint64_t i = 0; i < a.size(); i++) {
        c[i] = a[i] + b[i];
    }
}

void triad() {
    #pragma omp parallel for
    for (uint64_t i = 0; i < a.size(); i++) {
        c[i] = alpha * a[i] + b[i];
    }
}

Stream::Stream() : Microbench("STREAM", 5) {
    alpha = (double) high_resolution_clock::now().time_since_epoch().count();
}

template <typename F>
uint64_t Stream::wrap(F &&f) {
    time_point<high_resolution_clock> t1, t2;

    t1 = high_resolution_clock::now();
    for (int i = 0; i < 200; i++) {
        f(); 
    }
    t2 = high_resolution_clock::now();

    return (t2 - t1).count();
}

void Stream::run() {
    a.resize(MAX_SIZE);
    b.resize(MAX_SIZE);
    c.resize(MAX_SIZE);
    init();
    // warmups
    wrap(triad);
    wrap(triad);

    for (uint64_t rep = 0; rep < nbIterations; rep++) {
        spdlog::debug("run {}/{}", rep+1, nbIterations);
        uint64_t size = MAX_SIZE;
        
        int i = 0;
        while (size > MIN_SIZE) {
            a.resize(size);
            b.resize(size);
            c.resize(size);
            spdlog::debug("current buffer: {} doubles ({}KiB)", size, size * sizeof(double) / ( 1 << 10));
            results[0][rep][i] = wrap(copy);
            results[1][rep][i] = wrap(mul);
            results[2][rep][i] = wrap(add);
            results[3][rep][i] = wrap(triad);
            i++;
            size /= 2;
        }
    }

    std::vector<double>().swap(a);
    std::vector<double>().swap(b);
    std::vector<double>().swap(c);
}

json Stream::getJson() {
    json obj;
    obj["name"] = name;
    obj["max_size"] = MAX_SIZE * sizeof(double);
    obj["min_size"] = MIN_SIZE * sizeof(double);

    for (uint64_t rep = 0; rep < nbIterations; rep++) {
        for (int i = 0; i < 17; i++) {
            obj["copy"][rep][i] = results[0][rep][i] / 200;
            obj["mul"][rep][i] = results[1][rep][i] / 200;
            obj["add"][rep][i] = results[2][rep][i] / 200;
            obj["triad"][rep][i] = results[3][rep][i] / 200;
        }
    }

    return obj;
}