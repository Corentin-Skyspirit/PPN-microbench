#include <PPN-microbench/memory.hpp>

#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

/*void* pos       = NULL; // Pointer to the last accessed element
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
/*    // Shuffle the pointers using a random index within a cycle
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

    /// Ensure the shuffled pointers form a single cycle
    for (u64 i = 0; i < size - 1; ++i) {
        memblock[i] = (void**)&memblock[i + 1];
    }
    memblock[size - 1] = (void**)&memblock[0];
*/

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

 /*   void* p = pos;
    double elapsed = 0.0;
    struct timespec t1, t2;

    // Perform the latency measurement 11 times for better accuracy
    //for (int run = 0; run < 11; ++run) {
        
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
        pos = p;
        
        return total_latency;
    }

    /// Calculate the average latency over 11 runs
    return (double)total_latency / 11.0;*/
//}

void* pos       = NULL; // Pointer to the last accessed element
void** memblock = NULL;// Pointer to the memory block

static inline uint64_t rnd(uint64_t threshold) {
    uint64_t a = (uint64_t)rand() << 48;
    uint64_t b = (uint64_t)rand() << 32;
    uint64_t c = (uint64_t)rand() << 16;
    uint64_t d = (uint64_t)rand();
    return (a ^ b ^ c ^ d) % threshold;
}

/// Using a pointer chasing benchmark to measure the cache latency in ns.
double cache_latency(uint64_t size, uint64_t iterations) {
    int cycle_len    = 1;
    double ns_per_it = 0.0;

    if (NULL == pos) {
        pos = &memblock[0];
    }

    // Initialize
    for (size_t i = 0; i < size; ++i) {
        memblock[i] = &memblock[i];
    }

    // Shuffle pointer addresses
    for (ssize_t i = size - 1; i >= 0; --i) {
        if (i < cycle_len) {
            continue;
        }
        uint64_t j  = rnd(i / cycle_len) * cycle_len + (i % cycle_len);
        void* swp   = memblock[i];
        memblock[i] = memblock[j];
        memblock[j] = swp;
    }

    void* p        = pos;
    double elapsed = 0.0;
    struct timespec t1, t2;
    do {
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        // Random pointer chasing loop, unrolled 16 times
        for (ssize_t i = iterations; i; --i) {
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
            p = *(void**)p;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
        elapsed = (t2.tv_sec - t1.tv_sec) * 1e9 + (t2.tv_nsec - t1.tv_nsec);

    } while (elapsed <= 0.0); // Repeat until we get a valid measurement

    ns_per_it = elapsed / ((double)iterations * 16.0);
    pos       = p;

    return ns_per_it;
}

// Constructor
Memory::Memory() : Microbench("Memory", 1) { srand(time(nullptr)); }

// Destructor
Memory::~Memory() {}


void** allocate_memory(u64 size) {
    void** memblock = static_cast<void**>(aligned_alloc(64, size * sizeof(void*)));
    return memblock;
}
/*// Execute the benchmark
void Memory::run() {

/*
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

        double latency = cache_latency(size_B, getNbIterations());

        if (latency == 0.0) {
            std::cerr << "Warning: Measured latency is 0.0 for size " << size_B << std::endl;
        }
        
        mem_times[i] = latency;
    }

    std::cout << "Memory benchmark start\n";
    u64 addr_space_sz = 67108864;// 64 MiB
    
    std::cerr << "Measuring cache/memory latency up to " 
        << addr_space_sz / sizeof(void*) << " B (" << std::fixed << std::setprecision(3) 
          << ((static_cast<double>(addr_space_sz) / static_cast<double>(sizeof(void*))) / 1024.0 / 1024.0) << " MiB)\n";
    
    u64 rounds = 0;
    u64 min_iterations = 1024;// 1 KiB
    u64 max_iterations = 9437184; // 9 MiB
    u64 iterations = max_iterations;
    
    std::vector<double> nanos(2048);
    std::vector<u64> sizes(2048);
    
    memblock = static_cast<void**>(aligned_alloc(64, addr_space_sz));
    if (memblock == NULL) {
        std::cerr << "Memory allocation failed" << std::endl;
        return;
    }
    // Initial value is the address of the element
    for (size_t i = 0; i < addr_space_sz / sizeof(void*); ++i) {
        memblock[i] = &memblock[i];
    }
    
    std::cout << "Memory size (B), Cache latency (ns)\n";
    for (size_t size = 512, step = 16; size <= addr_space_sz / sizeof(void*); size += step) {
        if (size == 0) continue;
        std::cerr << "Current cache size: " << size << " B (" << std::fixed << std::setprecision(3) << (static_cast<double>(size) / 1024.0) << " KiB)\r";
        double ns_per_it = cache_latency(size, iterations);
    
        if (ns_per_it == 0.0){
            std::cerr << "Warning: cache latency is 0.0 for size " << size << " B\n";
        }

        sizes[rounds] = size;
        nanos[rounds] = ns_per_it;
        rounds++;
    
        // Double step size every powers of two
        if (0 == ((size - 1) & size)) {
            step <<= 1;
        }
        // Adjust the number of iterations based on the measured latency
        iterations = static_cast<u64>(static_cast<double>(max_iterations) / ns_per_it);
        if (iterations < min_iterations) {
            iterations = min_iterations;
        }
        // Output the results every 2048 rounds
        if (rounds == 2048) {
            for (size_t r = 0; r < 2048; ++r) {
                std::cout << sizes[r] << "," << nanos[r] << std::endl;
            }
            rounds = 0;
        }
    }
    
    for (size_t r = 0; r < rounds; ++r) {
        std::cout << sizes[r] << "," << nanos[r] << std::endl;
    }

    mem_sizes = sizes;
    mem_times = nanos;

    std::cout << "Memory benchmark end\n";

    if (memblock != NULL) {
        free(memblock);
    }
   //free(memblock);
}*/

void Memory::run() {
    std::cout << "Memory benchmark start\n";
    u64 addr_space_sz = 67108864; // 64 MiB
    
    std::cerr << "Measuring cache/memory latency up to " 
              << addr_space_sz / sizeof(void*) << " B (" 
              << std::fixed << std::setprecision(3) 
              << ((static_cast<double>(addr_space_sz) / static_cast<double>(sizeof(void*))) / 1024.0 / 1024.0) << " MiB)\n";
    
    u64 rounds = 0;
    u64 min_iterations = 1024;   // 1 KiB
    u64 max_iterations = 9437184; // 9 MiB
    u64 iterations = max_iterations;
    
    std::vector<double> nanos;
    std::vector<u64> sizes;
    
    memblock = static_cast<void**>(aligned_alloc(64, addr_space_sz));
    if (memblock == NULL) {
        std::cerr << "Memory allocation failed" << std::endl;
        return;
    }

    for (size_t i = 0; i < addr_space_sz / sizeof(void*); ++i) {
        memblock[i] = &memblock[i];
    }
    
    std::cout << "Memory size (B), Cache latency (ns)\n";
    for (size_t size = 512, step = 16; size <= addr_space_sz / sizeof(void*); size += step) {
        if (size == 0) continue;
        
        // Barre de progression (affichée sur la même ligne)
        std::cerr << "Current cache size: " << size << " B (" 
                  << std::fixed << std::setprecision(3) 
                  << (static_cast<double>(size) / 1024.0) << " KiB)" << "\r";

        double ns_per_it = cache_latency(size, iterations);

        if (ns_per_it == 0.0) {
            std::cerr << "Warning: cache latency is 0.0 for size " << size << " B\n";
        }

        sizes.push_back(size);
        nanos.push_back(ns_per_it);
        rounds++;

        // Doubler la taille du pas tous les puissances de 2
        if (0 == ((size - 1) & size)) {
            step <<= 1;
        }

        // Ajuster le nombre d'itérations pour les prochaines mesures
        iterations = static_cast<u64>(static_cast<double>(max_iterations) / ns_per_it);
        if (iterations < min_iterations) {
            iterations = min_iterations;
        }

        // Output the results every 2048 rounds
        if (rounds == 2048) {
            for (size_t r = 0; r < 2048; ++r) {
                std::cout << sizes[r] << "," << nanos[r] << std::endl;
            }
            rounds = 0;
        }
    }
    
    for (size_t r = 0; r < rounds; ++r) {
        std::cout << sizes[r] << "," << nanos[r] << std::endl;
    }

    // Copier dans les membres de la classe
    mem_sizes = sizes;
    mem_times = nanos;

    std::cout << "Memory benchmark end\n";

    if (memblock != NULL) {
        free(memblock);
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

