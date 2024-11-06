#ifndef TEST_CLASS
#define TEST_CLASS

#include <PPN-microbench/microbench.hpp>

class Test_class : Microbench {
    private:
        float number;
        void executeBench() override;
        
    public:
        Test_class(std::string name, int nbIterations, float number);
        ~Test_class();

        void run();
        json getJson() override;
};

#endif