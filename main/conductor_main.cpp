#include <PPN-microbench/_ops/ops.hpp>
#include <PPN-microbench/conductor.hpp>
#include <PPN-microbench/ops/flops.hpp>

#include <iostream>

int main() {

    Conductor conductor;

    conductor.addBench(new Ops(50))
        .setOutputFile("../tmp/out.json")
        .run()
        .save()
        .print();

    return 0;
}
