#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/ops/flops.hpp>
#include <PPN-microbench/ops/iops.hpp>

#include <PPN-microbench/context.hpp>

#include <vector>

int main() {

    std::vector<Microbench *> vec;

    vec.push_back(new Flops(5));
    vec.push_back(new Iops(5));

    for (Microbench *b : vec) {
        // b->run();
        b->context.print();
    }

    return 1;
}