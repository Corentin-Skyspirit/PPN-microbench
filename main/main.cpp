#include <PPN-microbench/context.hpp>
#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/ops/flops.hpp>
#include <PPN-microbench/ops/iops.hpp>

#include <nlohmann/json.hpp>
#include <vector>

int main() {
    Flops f(10);
    f.context.getInstance().getJson();
}