#ifndef IOPS_HPP
#define IOPS_HPP

#include <PPN-microbench/ops/abstract_ops.hpp>

class Iops : public AbstractOps {
    protected:
        void compute(int);
    public:
        Iops() : AbstractOps("IOPS", 1) {};
        ~Iops() {};
};

#endif