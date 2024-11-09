#include <PPN-microbench/awesome_header.hpp>
#include <PPN-microbench/test_class.hpp>
#include <PPN-microbench/cpu_speed.hpp>

int main() {
    cool_func();

    Test_class test("Test", 7, 3.8);
    test.run();

    CPUSpeed cpuSpeed("CPU Speed", 7);
    cpuSpeed.run();

    return 1;
}