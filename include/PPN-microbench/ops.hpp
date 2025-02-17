#ifndef PPN_MICROBENCH_OPS_HPP
#define PPN_MICROBENCH_OPS_HPP

#include <PPN-microbench/intrinsics.h>
#include <PPN-microbench/microbench.hpp>

#include <chrono>
#include <thread>

class Ops : public Microbench {
  private:
    int static const WARMUP_RUNS = 2;
    int static const RUNS = 10;

    size_t n_ops;
    size_t cpus;

    size_t results[6][RUNS];

    // 'reps' represents the number of operations executed in 'f'
    template <class T> void wrap(T (*f)(T, T), T *val, int reps);
    void executeBench() {};

  public:
    Ops(int reps);
    ~Ops();

    void run();
    json getJson();
};

#endif