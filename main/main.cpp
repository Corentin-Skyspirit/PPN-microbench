#include <PPN-microbench/awesome_header.hpp>
#include <PPN-microbench/test_class.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/flops.hpp>
// #include <PPN-microbench/iops.hpp>

int main() {
    // Iops test;
    // Flops test;
    // test.run();

    CPUFrequency cpuFrequency("CPU Speed", 3);
    cpuFrequency.run();
    std::cout << cpuFrequency.getJson().dump() << std::endl;

    return 1;
}