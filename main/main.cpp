#include <PPN-microbench/awesome_header.hpp>
#include <PPN-microbench/test_class.hpp>
#include <PPN-microbench/cpu_speed.hpp>
#include <PPN-microbench/flops.hpp>
#include <PPN-microbench/iops.hpp>

int main() {
    // Iops test;
    Flops test;
    test.run();

    CPUSpeed cpuSpeed("CPU Speed", 7);
    cpuSpeed.run();

    return 1;
}