#ifndef ABSTRACT_OPS_HPP
#define ABSTRACT_OPS_HPP

#include <PPN-microbench/microbench.hpp>

#include <string>

static int c;

class AbstractOps : Microbench {
    protected:
        int nb_cpus;
        u64 *results;
        u64**polled_results;

        // running benchmark time (ms)
        int const bench_time = 20000;
        // measurments polling interval (ms)
        int const poll_interval = 100;

        static void *thread_helper(void *context) {((AbstractOps *) context)->compute(c++); return nullptr;}
        void executeBench();
        virtual void compute(int) = 0;
    public:
        AbstractOps(std::string, int);
        ~AbstractOps();

        void run();
        json getJson();
};

#endif