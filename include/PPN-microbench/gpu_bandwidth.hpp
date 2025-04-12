#pragma once
#define __HIP_PLATFORM_AMD__

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <chrono>
#include <thread>

#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

class GPUBandwidth : public Microbench {
    private:
        uint64_t max_buffer_size;
        bool gpuprep();
        void _run();
    public:
        GPUBandwidth();

        void run() override;
        json getJson() override;
};
