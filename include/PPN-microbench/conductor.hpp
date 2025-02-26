#include <PPN-microbench/microbench.hpp>
#include <PPN-microbench/context.hpp>

#include <filesystem>

using json = nlohmann::ordered_json;

class Conductor {
  private:
    Context context = Context::getInstance();
    std::vector<Microbench *> benches;
    std::filesystem::path path = std::filesystem::canonical(".");
    json results;
    void start();
    void buildJson();

  public:
    Conductor();
    Conductor(int, char **);
    ~Conductor();
    Conductor &addBench(Microbench *);
    Conductor &setOutputFile(std::string);
    Conductor &run();
    Conductor &print();
    Conductor &save();
};