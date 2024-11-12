#ifndef FLOPS_HPP
#define FLOPS_HPP

#include <PPN-microbench/abstract_ops.hpp>

class Flops : public AbstractOps {
    protected:
        void compute(int);
    public:
        Flops() : AbstractOps("FLOPS", 1) {};
        ~Flops() {};
};

#endif