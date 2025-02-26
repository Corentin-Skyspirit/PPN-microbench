#include <PPN-microbench/conductor.hpp>

Conductor::Conductor() {}

Conductor::Conductor(int argc, char **argv) {
    // TODO
}

Conductor::~Conductor() {
    for (Microbench *bench : benches) {
        delete bench;
    }
    benches.clear();
}

void Conductor::start() {
    spdlog::info("Executing {} microbenches", benches.size());
    for (Microbench *bench : benches) {
        bench->run();
    }
}

void Conductor::buildJson() {
    results["meta"] = context.getJson();
    json dataArray = json::array();

    for (Microbench *bench : benches) {
        dataArray.push_back(bench->getJson());
    }

    results["data"] = dataArray;
}

Conductor &Conductor::addBench(Microbench *bench) {
    benches.push_back(bench);
    return *this;
}

Conductor &Conductor::setOutputFile(std::string fname) {
    path = std::filesystem::canonical(fname);
    spdlog::info("Output path is {}", path.string());
    return *this;
}

Conductor &Conductor::run() {
    start();
    buildJson();
    return *this;
}

Conductor &Conductor::print() {
    std::cout << results.dump(4) << std::endl;
    return *this;
}

Conductor &Conductor::save() {
    std::ofstream o(path);
    o << std::setw(4) << results << std::endl;
    if (o.is_open()) {
        spdlog::info("Saved results to {}", path.string());
    } else {
        spdlog::warn("Failed to save results to {}, file is closed", path.string());
    }
    o.close();
    return *this;
}
