#include <PPN-microbench/core_to_core_frequency.hpp>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

CoreToCoreFrequency::CoreToCoreFrequency(int nbMeasures) : Microbench("CPU Frequency", 10) {}

CoreToCoreFrequency::~CoreToCoreFrequency() {}

void CoreToCoreFrequency::run() {}

json CoreToCoreFrequency::getJson() { return json(); }
