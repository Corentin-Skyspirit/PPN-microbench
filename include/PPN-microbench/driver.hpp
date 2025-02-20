#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <filesystem>

using json = nlohmann::ordered_json;

class Driver {
  private:
    Context context = Context::getInstance();
    std::vector<Microbench *> benches;
    std::filesystem::path path = std::filesystem::canonical(".");
    json results;
    void start();
    void buildJson();

  public:
    Driver();
    Driver(int, char **);
    ~Driver();
    Driver &addBench(Microbench *);
    Driver &setOutputFile(std::string);
    Driver &run();
    Driver &print();
    Driver &save();
};