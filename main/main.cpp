#include <PPN-microbench/driver.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/memory.hpp>
#include <PPN-microbench/ops.hpp>
#include <PPN-microbench/core_to_core_latency.hpp>

int main() {

    Driver driver;

    driver.addBench(new CPUFrequency(10))
        .addBench(new CoreToCoreLatency(10))
        .addBench(new Ops(10))
        // .addBench(new Memory())
        .setOutputFile("../report/out.json")
        .run()
        .save();

    return 0;
}
