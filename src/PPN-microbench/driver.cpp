#include <PPN-microbench/driver.hpp>

Driver::Driver() {}

Driver::Driver(int argc, char **argv) {
    CLI::App app("PPN-microbench");
    argv = app.ensure_utf8(argv);

    std::string fname = ".";
    app.add_option("-o,--output", fname, "JSON output file path");
    app.parse(argc, argv);
    spdlog::info(fname);
}

void Driver::start() {
    spdlog::info("Executing {} microbenches", benches.size());
    for (Microbench *bench : benches) {
        spdlog::info("Running bench: {}", bench->getName());
        bench->run();
    }
}

void Driver::buildJson() {
    results["meta"] = context.getJson();
    json dataArray = json::array();

    for (Microbench *bench : benches) {
        dataArray.push_back(bench->getJson());
    }

    results["data"] = dataArray;
}

Driver &Driver::addBench(Microbench *bench) {
    benches.push_back(bench);
    return *this;
}

Driver &Driver::setOutputFile(std::string fname) {
    path = std::filesystem::weakly_canonical(fname);
    spdlog::info("Output path is {}", path.string());
    return *this;
}

Driver &Driver::run() {
    start();
    buildJson();
    return *this;
}

Driver &Driver::print() {
    std::cout << results.dump(4) << std::endl;
    return *this;
}

Driver &Driver::save() {
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
