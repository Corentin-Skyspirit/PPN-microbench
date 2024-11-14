#ifndef MICROBENCH
#define MICROBENCH

#include <PPN-microbench/constants.hpp>

#include <any>
#include <iostream>
#include <nlohmann/json.hpp>
#include <threads.h>
#include <unistd.h> // sleep
#include <vector>

using json = nlohmann::json;

class Microbench {
  protected:
    std::vector<std::any> results;
    std::string name;
    int nbIterations;

    virtual void executeBench() = 0;

  public:
    Microbench(std::string name, int nbIterations);
    ~Microbench();

    std::string getName();
    int getNbIterations();

    virtual void run() = 0;
    virtual json getJson() = 0;
};

#endif