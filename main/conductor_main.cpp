#include <PPN-microbench/conductor.hpp>
#include <PPN-microbench/ops.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/memory.hpp>
#include <PPN-microbench/ops/flops.hpp>
#include <PPN-microbench/ops/iops.hpp>

int main() {

    Conductor conductor;

    conductor.addBench(new Ops(10))
        .addBench(new CPUFrequency(10))
        .addBench(new Memory())
        .setOutputFile("../tmp/out.json")
        .run()
        .save()
        .print();

    return 0;
}
