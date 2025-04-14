#pragma once

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <CL/opencl.hpp>

#include <chrono>
#include <thread>

#define GPUERR(f) if (gpuerr(f)) {return;}

class GPUH2DBandwidth : public Microbench {
    private:
        uint64_t const MAX_SIZE = 1 << 30;

        uint64_t meta[21];
        uint64_t data[5][21];

        // used to provide info in reports if bench execution doesn't go as planned.
        std::string bench_info = "";

        // bool gpuerr(hipError_t err);
        void gpuprep();
        // void _run();
    public:
        GPUH2DBandwidth();
        ~GPUH2DBandwidth() = default;

        void run() override;
        json getJson() override;
};
