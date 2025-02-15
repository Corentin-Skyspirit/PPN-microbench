#ifndef PPN_MICROBENCH_OPS_HPP
#define PPN_MICROBENCH_OPS_HPP

#include <PPN-microbench/microbench.hpp>

#include <immintrin.h>

#include <chrono>
#include <thread>

extern "C" i32 ADD_X86_i32(i32, i32);
extern "C" i64 ADD_X86_i64(i64, i64);
extern "C" float ADD_X86_f32(float, float);
extern "C" double ADD_X86_f64(double, double);

class Ops : public Microbench {
  private:
    int static const WARMUP_RUNS = 2;
    int static const RUNS = 10;

    size_t n_ops;
    size_t cpus;

    size_t results[6][RUNS];

    template <class T> void benchhaha(T *);
    template <class T> void wrap(T (*f)(T, T), T *val);
    void executeBench() {};

  public:
    Ops(int reps);
    ~Ops();

    void run();
    json getJson();
};

#endif