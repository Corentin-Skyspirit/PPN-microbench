#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/ops/flops.hpp>
#include <PPN-microbench/ops/iops.hpp>

#include <vector>

int main() {

    std::vector<Microbench *> vec;

    vec.push_back(new Flops(50));
    vec.push_back(new Iops(50));

    for (Microbench *b : vec) {
        b->run();
    }

    return 1;
}