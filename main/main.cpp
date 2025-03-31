#include <PPN-microbench/driver.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/cache_latency.hpp>
#include <PPN-microbench/ops.hpp>

int main() {

    Driver driver;

    driver.addBench(new CPUFrequency(10))
        .addBench(new Ops(10))
        .addBench(new Cache_latency())
        .setOutputFile("../report/out.json")
        .run()
        .save();

    return 0;
}
