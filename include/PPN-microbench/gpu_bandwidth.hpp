#ifndef PPN_MICROBENCH_GPU_BANDWIDTH
#define PPN_MICROBENCH_GPU_BANDWIDTH

#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <chrono>
#include <thread>

#include <Kokkos_Core.hpp>
#include <HIP/Kokkos_HIP.hpp>
#include <hip/hip_common.h>

class GPUBandwidth : public Microbench {
    private:
    public:
        GPUBandwidth();

        void run() override;
        json getJson() override;
};

#endif