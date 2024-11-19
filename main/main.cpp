#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/ops/flops.hpp>
#include <PPN-microbench/ops/iops.hpp>

int main() {
    CPUFrequency cpuFrequency("CPU Speed", 101);
    cpuFrequency.run();
    std::cout << cpuFrequency.getJson().dump(4) << std::endl;


    // std::vector<Microbench *> vec;

    // vec.push_back(new Flops(5));
    // vec.push_back(new Iops(5));

    // for (Microbench *b : vec) {
    //     b->run();
    // }

    return 1;
}