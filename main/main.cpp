#include <PPN-microbench/awesome_header.hpp>
#include <PPN-microbench/test_class.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/flops.hpp>
#include <PPN-microbench/iops.hpp>

int main() {
    CPUFrequency cpuFrequency("CPU Speed", 3);
    cpuFrequency.run();
    std::cout << cpuFrequency.getJson().dump() << std::endl;


    std::vector<Microbench *> vec;

    vec.push_back(new Flops(5));
    vec.push_back(new Iops(5));

    for (Microbench *b : vec) {
        b->run();
    }

    return 1;
}