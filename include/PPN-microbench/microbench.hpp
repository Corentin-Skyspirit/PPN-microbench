#ifndef MICROBENCH
#define MICROBENCH

#include <PPN-microbench/constants.hpp>

#include <iostream>
#include <vector>
#include <any>
#include <nlohmann/json.hpp>
#include <threads.h>
#include <unistd.h> // sleep

using json = nlohmann::json;

class Microbench {
    private:
        std::vector<std::any> results;
        std::string name;
        //std::string category;
        int nbIterations;

        virtual void executeBench() = 0;

    public:
        Microbench(std::string name, int nbIterations);
        ~Microbench();

        std::string getName();
        int getNbIterations();
        
        void run();
        virtual json getJson() = 0;
};


#endif