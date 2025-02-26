#include <PPN-microbench/conductor.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/memory.hpp>
#include <PPN-microbench/ops.hpp>
#include <PPN-microbench/core_to_core_latency.hpp>

int main() {

    Conductor conductor;

    conductor.addBench(new CPUFrequency(10))
        .addBench(new CoreToCoreLatency(10))
        .addBench(new Ops(10))
        // .addBench(new Memory())
        .setOutputFile("../tmp/out.json")
        .run()
        .save();

    return 0;
}
