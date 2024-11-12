#ifndef FLOPS_HPP
#define FLOPS_HPP

#include <PPN-microbench/microbench.hpp>

static int c = 0;

class Flops : Microbench {
    private:
        int nb_cpus;
        u64 *results;
        u64**polled_results;

        // running benchmark time (ms)
        int const bench_time = 20000;
        // measurments polling interval (ms)
        int const poll_interval = 100;

        static void *thread_helper(void *context) {((Flops *) context)->compute(c++);}
        void executeBench();
        void compute(int);
    public:
        Flops();
        ~Flops();

        void run();
        json getJson();
};

#endif