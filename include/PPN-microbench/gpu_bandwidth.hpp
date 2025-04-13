#pragma once

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <hip/hip_runtime.h>

#include <chrono>
#include <thread>

#define GPUERR(f) if (gpuerr(f)) {return;}

class GPUBandwidth : public Microbench {
    private:
        uint64_t const MAX_SIZE = 1 << 30;

        uint64_t meta[21];
        uint64_t data[5][21];

        // used to provide info in reports if bench execution doesn't go as planned.
        std::string bench_info = "";

        bool gpuerr(hipError_t err);
        bool gpuprep();
        void _run();
    public:
        GPUBandwidth();
        ~GPUBandwidth() = default;

        void run() override;
        json getJson() override;
};
