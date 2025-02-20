#include <PPN-microbench/driver.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/memory.hpp>
#include <PPN-microbench/ops.hpp>

int main() {

    Driver driver;

    driver.addBench(new CPUFrequency(10))
        .addBench(new Ops(10))
        .addBench(new Memory())
        .setOutputFile("../tmp/out.json")
        .run()
        .save()
        .print();

    return 0;
}
