#include <PPN-microbench/context.hpp>
#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/ops/flops.hpp>
#include <PPN-microbench/ops/iops.hpp>

#include <nlohmann/json.hpp>
#include <vector>

int main() {
    
    CPUFrequency cpuFrequency(50);
    cpuFrequency.run();
    std::cout << cpuFrequency.getJson().dump(4) << std::endl;

    // Flops f(10);
    // f.context.getInstance().getJson();
}