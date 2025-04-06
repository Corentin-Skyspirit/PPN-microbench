#include <PPN-microbench/stream.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;

Stream::Stream() : Microbench("STREAM", 5) {
    cpus = context.getCpus();
    std::vector<size_t> mapping = context.getThreadMapping();
    cpusets.reserve(cpus);
    for (size_t i = 0; i < cpus; i++) {
        CPU_ZERO(&cpusets[i]);
        CPU_SET(mapping[i], &cpusets[i]);
    }

    alpha = (double) high_resolution_clock::now().time_since_epoch().count();
}

void Stream::init(uint64_t start, uint64_t end) {
    for (uint64_t i = start; i < end; i++) {
        a[i] = 1;
        b[i] = 1;
        c[i] = 0;
    }
}

void Stream::copy(uint64_t start, uint64_t end) {
    for (uint64_t i = start; i < end; i++) {
        c[i] = a[i];
    }
}

void Stream::mul(uint64_t start, uint64_t end) {
    for (uint64_t i = start; i < end; i++) {
        c[i] = alpha * a[i];
    }
}

void Stream::add(uint64_t start, uint64_t end) {
    for (uint64_t i = start; i < end; i++) {
        c[i] = a[i] + b[i];
    }
}

void Stream::triad(uint64_t start, uint64_t end) {
    for (uint64_t i = start; i < end; i++) {
        c[i] = alpha * a[i] + b[i];
    }
}

template <typename F>
uint64_t Stream::wrap(F &&f) {
    uint64_t slice = a.size() / cpus;
    time_point<high_resolution_clock> t1, t2;

    t1 = high_resolution_clock::now();
    {
        std::jthread threads[cpus];
        for (int cpu = 0; cpu < cpus; cpu++) {
            uint64_t start = cpu * slice;
            uint64_t end = cpu * slice + slice;
            threads[cpu] = std::jthread([&]{ 
                for (int i = 0; i < 1000; i++) 
                    f(start, end); 
            });
            pthread_setaffinity_np(threads[cpu].native_handle(), sizeof(cpu_set_t), &cpusets[cpu]);
        }
    }
    t2 = high_resolution_clock::now();

    return (t2 - t1).count();
}

void Stream::run() {

    a.reserve(MAX_SIZE);
    b.reserve(MAX_SIZE);
    c.reserve(MAX_SIZE);
    wrap( [&](uint64_t s, uint64_t e){this->init(s, e);});
    // warmups
    wrap( [&](uint64_t s, uint64_t e){this->triad(s, e);});
    wrap( [&](uint64_t s, uint64_t e){this->triad(s, e);});

    for (int rep = 0; rep < nbIterations; rep++) {
        spdlog::debug("run {}/{}", rep+1, nbIterations);
        uint64_t size = MAX_SIZE;
        
        int i = 0;
        while (size > MIN_SIZE) {
            spdlog::debug("current buffer: {} doubles ({}KiB)", size, size * sizeof(double) / ( 1 << 10));
            results[0][rep][i] = wrap( [&](uint64_t s, uint64_t e){this->copy(s, e);});
            results[1][rep][i] = wrap( [&](uint64_t s, uint64_t e){this->mul(s, e);});
            results[2][rep][i] = wrap( [&](uint64_t s, uint64_t e){this->add(s, e);});
            results[3][rep][i] = wrap( [&](uint64_t s, uint64_t e){this->triad(s, e);});
            i++;
            size /= 2;
            a.resize(size);
            b.resize(size);
            c.resize(size);
        }
    }

    a.clear();
    b.clear();
    c.clear();
}

json Stream::getJson() {
    json obj;
    obj["name"] = name;
    obj["max_size"] = MAX_SIZE * sizeof(double);
    obj["min_size"] = MIN_SIZE * sizeof(double);

    for (int rep = 0; rep < nbIterations; rep++) {
        for (int i = 0; i < 17; i++) {
            obj["copy"][rep][i] = results[0][rep][i];
            obj["mul"][rep][i] = results[1][rep][i];
            obj["add"][rep][i] = results[2][rep][i];
            obj["triad"][rep][i] = results[3][rep][i];
        }
    }

    return obj;
}