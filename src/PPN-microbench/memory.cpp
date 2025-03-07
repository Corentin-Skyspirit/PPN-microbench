#include <PPN-microbench/memory.hpp>

/// Function to generate a random index within a given threshold
#include <vector>
#include <algorithm>
#include <random>

void* pos       = NULL; // Pointer to the last accessed element
void** memblock = NULL;// Pointer to the memory block


/// Function to generate a random index within a given threshold
static inline uint64_t random_index(uint64_t threshold) { 
    uint64_t a = (uint64_t)rand() << 48;
    uint64_t b = (uint64_t)rand() << 32;
    uint64_t c = (uint64_t)rand() << 16;
    uint64_t d = (uint64_t)rand();
    
    return (a ^ b ^ c ^ d) % threshold; }

// Function to measure cache/memory latency using pointer chasing
double measure_latency(uint64_t size, uint64_t nbIterations) {
    //std::vector<void**> memblock(size);
    int cycle_lenght = 1;
    double total_latency = 0.0;


    if (NULL == pos) {
        pos = &memblock[0];
    }

    // Initialize the memory block with pointers to the next element
    for (size_t i = 0; i < size; ++i) {
        memblock[i] = &memblock[i];
    }
    /*for (uint64_t i = 0; i < size; ++i) {
        memblock[i] = (void**)&memblock[(i + 1) % size]; // Boucle circulaire
    }*/
        
      /*  if (i + 1 < size) {
            memblock[i] = (void**)&memblock[i + 1];
        } else {
            memblock[i] = (void**)&memblock[0];
        }
    }*/
//////////a encore changer !!! //////////////
// Shuffle the pointers to create a random access pattern
/*    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(memblock.begin(), memblock.end(), g);
*/
    // Shuffle the pointers using a random index within a cycle
    for (ssize_t i = size - 1; i >= 0; --i) {
        if (i<cycle_lenght) {
            continue;
        }
        uint64_t j = random_index(i/cycle_lenght) * cycle_lenght + (i % cycle_lenght);
        void *tmp = memblock[i];
        memblock[i] = memblock[j];
        memblock[j] = tmp;
    }
   

     // Ensure the shuffled pointers form a single cycle using Fisher-Yates
    //for (int loop = 0; loop < 3; ++loop){
        //if (loop == 0) {
        //    for (uint64_t i = 0; i < size - 1; ++i) {
        //        uint64_t j = random_index(i/cycle_lenght) * cycle_lenght + (i % cycle_lenght);
        //void *tmp = memblock[i];
        //memblock[i] = memblock[j];
        //memblock[j] = (void**)tmp;
        //    }
            
       // //}
       // for (uint64_t i = size - 1; i > 0; --i) {
       //     uint64_t j = random_index(i + 1);
       //     std::swap(memblock[i], memblock[j]);
       //     
       // }
    //}
    /*// Ensure the shuffled pointers form a single cycle
    for (uint64_t i = 0; i < size - 1; ++i) {
        memblock[i] = (void**)&memblock[i + 1];
    }
    memblock[size - 1] = (void**)&memblock[0];*/


    /*// Warmup run
    volatile void *p = memblock[0];
    for (ssize_t i = nbIterations; i; --i) {
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
    }*/
    
    double elapsed = 0.0;
    std::chrono::duration<double, std::nano> elapsed;
    volatile void* p = pos;
    struct timespec t1, t2;

    // Perform the latency measurement 11 times for better accuracy
    for (int run = 0; run < 11; ++run) {
        
        do{
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        //auto start = std::chrono::high_resolution_clock::now();
        // Pointer chasing loop
        for (ssize_t i = nbIterations; i ; --i) {
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
            p = *(void **)p;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        //auto end = std::chrono::high_resolution_clock::now();
        elapsed = (double)(t2.tv_nsec - t1.tv_nsec); //* 1e9 + (t2.tv_nsec - t1.tv_nsec);
        //std::chrono::duration<double, std::nano> elapsed = end - start;
        } while (elapsed <= 0.0);
        // Accumulate the latency
        total_latency = elapsed / (double)nbIterations*16.0;
        pos = (void*)p;
        
    }

    // Calculate the average latency over 11 runs
    return (double)total_latency / 11.0;
}

// Constructor
Memory::Memory() : Microbench("Memory", 1000000) { srand(time(nullptr)); }

// Destructor
Memory::~Memory() {}



// Execute the benchmark
void Memory::run() {
    // Define the sizes to test (in B)
    size_t size = 512;
    size_t step = 16;
    size_t i = 0;
    while (i < mem_sizes.size()) {
        mem_sizes[i++] = size;
        size += step;
        if ((size & (size - 1)) == 0) { // Double step size at powers of two
            step <<= 1;
        }
    }

    mem_times.resize(mem_sizes.size());
    for (size_t i = 0; i < mem_sizes.size(); ++i) {
        uint64_t size_B = mem_sizes[i] ;

        double latency = measure_latency(size_B, getNbIterations());

        if (latency == 0.0) {
            std::cerr << "Warning: Measured latency is 0.0 for size " << size_B << std::endl;
        }
        
        mem_times[i] = latency;
    }
}
// Get the results in JSON format
json Memory::getJson() {
    json result1, result2, result;
    result["name"] = "memory";
    for (size_t i = 0; i < mem_sizes.size(); ++i) {
        result1["Memory_Size"].push_back(mem_sizes[i]*sizeof(void *));
        result2["Latency"].push_back((double)mem_times[i]);
        result["Results"] = {result1, result2};
    }
    return result;
}

