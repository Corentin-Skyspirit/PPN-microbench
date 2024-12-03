#ifndef PPN_MICROBENCH_OPS_HPP
#define PPN_MICROBENCH_OPS_HPP

#include <PPN-microbench/microbench.hpp>

#include <chrono>
#include <thread>
#include <threads.h> // needed to set thread affinty
#include <time.h>    // clock

class Ops : public Microbench {
  private:
    int static const RUNS = 10;

    size_t const N_OPS = 1024 * 1024 * 8;
    size_t cpus;

    size_t results[6][RUNS];

    template <class T> void benchhaha(T);
    template <class T> void benchSIMD(T);
    void executeBench() {};

  public:
    Ops(int reps);
    ~Ops();

    void run();
    json getJson();
};

#endif