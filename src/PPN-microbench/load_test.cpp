#include <PPN-microbench/load_test.hpp>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

LoadTest::LoadTest() : Microbench("Load Test", 10) {}

LoadTest::~LoadTest() {}

void LoadTest::run() {
    
}

json LoadTest::getJson() {

}