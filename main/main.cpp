#include <PPN-microbench/context.hpp>
#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/ops/flops.hpp>
#include <PPN-microbench/ops/iops.hpp>

#include <nlohmann/json.hpp>
#include <vector>

int main() {

    std::vector<Microbench *> vec;

    json obj;

    vec.push_back(new Flops(10));
    // vec.push_back(new Iops(5));

    // obj["meta"] = vec[0]->context.getJson();
    // obj["data"] = json::array();

    for (Microbench *b : vec) {
        b->run();
        // obj["data"].push_back(b->getJson());
    }

    // std::cout << obj.dump(4) << std::endl;

    return 1;
}