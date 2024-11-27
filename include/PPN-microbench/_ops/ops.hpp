#ifndef _OPS_HPP
#define _OPS_HPP

#include <PPN-microbench/microbench.hpp>

#include <chrono>
#include <thread>
// needed to set thread affinty
#include <threads.h>

class Ops : public Microbench {
  private:
    size_t const N_OPS = 1024 * 1024;
    size_t cpus;

    // size_t **i32Res;
    // size_t **i64Res;
    // size_t **i64SIMDRes;
    // size_t **f32Res;
    // size_t **f64Res;
    // size_t **f64SIMDRes;

    size_t **results;

    template <class T> void bench(T, size_t *);
    void executeBench() {};

  public:
    Ops(int reps);
    ~Ops();

    void run();
    json getJson();
};

#endif