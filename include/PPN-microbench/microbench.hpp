#ifndef MICROBENCH
#define MICROBENCH

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Microbench {

  private:
  public:
    Microbench();
    ~Microbench();

    virtual bool executeBench() = 0;
    virtual json getJson() = 0;
};

#endif