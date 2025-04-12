#pragma once

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <chrono>
#include <thread>

#define __HIP_PLATFORM_AMD__

#include <Kokkos_Core.hpp>
// #include <HIP/Kokkos_HIP.hpp>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

class GPUBandwidth : public Microbench {
    private:
    public:
        GPUBandwidth();

        void run() override;
        json getJson() override;
};
