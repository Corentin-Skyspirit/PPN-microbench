#include <PPN-microbench/driver.hpp>

Driver::Driver() {}

void haha(const std::string &value) {
    spdlog::info(value);
}

Driver::Driver(int argc, char **argv) {
    CLI::App app("PPN-microbench");
    argv = app.ensure_utf8(argv);

    // logging level
    app.add_option_function<std::string>("-l,--log", [&](const std::string level){spdlog::set_level(spdlog::level::from_str(level));}, "Logging level");
    // output path
    app.add_option_function<std::string>("-o,--output", [this](const std::string &fname){this->setOutputFile(fname);}, "JSON output file path");
    // benchmark selection
    app.add_flag_callback("--ops", [this](){this->addBench(new Ops(10));}, "Run operations/second benchmark");
    app.add_flag_callback("--memory_latency", [this](){this->addBench(new Memory);}, "Run cpu ram/cache latency benchmark");
    app.add_flag_callback("--cpu_frequency", [this](){this->addBench(new CPUFrequency(10));}, "Run frequency benchmark");

    app.parse(argc, argv);
    run();
    save();
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

    std::filesystem::path dirPath = path.parent_path();
    std::filesystem::path fileName = path.filename();

    if (!std::filesystem::exists(dirPath)) {
        spdlog::warn("Directory {} does not exist!", dirPath.string());
    } else if (std::filesystem::is_directory(path)) {
        spdlog::warn("{} is a directory, setting output to {}/out.json.", path.string(), path.string());
        path.append("out.json");
    } else {
        spdlog::info("Output path is {}", path.string());
    }

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
        spdlog::warn("Failed to save results to {}", path.string());
    }
    o.close();
    return *this;
}
