#include <PPN-microbench/context.hpp>
#include <PPN-microbench/cpu_frequency.hpp>
#include <PPN-microbench/cache_latency.hpp>
#include <PPN-microbench/core_to_core_latency.hpp>
#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/ops.hpp>
#include <PPN-microbench/matmul_bench.hpp>
#include <PPN-microbench/gpu_h2d_bandwidth.hpp>
#include <PPN-microbench/mem_bandwidth.hpp>
#include <PPN-microbench/stream.hpp>
#include <PPN-microbench/load_test.hpp>

#include <CLI/CLI.hpp>

#include <filesystem>

using json = nlohmann::ordered_json;

class Driver {
  private:
    Context context = Context::getInstance();
    std::vector<Microbench *> benches;
    std::filesystem::path path = std::filesystem::weakly_canonical("./out.json");
    json results;
    void start();
    void buildJson();

  public:
    Driver();
    Driver(int argc, char **argv);

    Driver(Driver const &d) = delete;
    Driver(Driver &&) = delete;
    Driver &operator=(const Driver &) = delete;
    Driver operator=(Driver &&) = delete;

    ~Driver() {
      for (Microbench *bench : benches) {
          delete bench;
      }
      benches.clear();

    };
    Driver &addBench(Microbench *);
    Driver &setOutputFile(std::string);
    Driver &run();
    Driver &print();
    Driver &save();
};
