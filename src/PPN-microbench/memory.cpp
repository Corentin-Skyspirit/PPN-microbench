#include <PPN-microbench/memory.hpp>


void* pos       = NULL; // Pointer to the last accessed element
void** memblock = NULL; // Pointer to the memory block

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
Memory::Memory() : Microbench("Cache Latency", 1) { srand(time(nullptr)); }

// Destructor
Memory::~Memory() {}


void** allocate_memory(uint64_t size) {
    void** memblock = static_cast<void**>(aligned_alloc(64, size * sizeof(void*)));
    return memblock;
}

void Memory::run() {

    uint64_t addr_space_sz = 67108864; // 64 MiB
    
    spdlog::debug("Measuring cache/memory latency up to {} B ({:.3f} MiB)", 
                  addr_space_sz / sizeof(void*), 
                  (static_cast<double>(addr_space_sz) / static_cast<double>(sizeof(void*))) / 1024.0 / 1024.0);
    
    uint64_t rounds = 0;
    uint64_t min_iterations = 1024;   // 1 KiB
    uint64_t max_iterations = 9437184; // 9 MiB
    uint64_t iterations = max_iterations;
    
    std::vector<double> nanos;
    std::vector<uint64_t> sizes;
    
    memblock = static_cast<void**>(aligned_alloc(64, addr_space_sz));
    if (memblock == NULL) {
        spdlog::error ("Memory allocation failed\n");
        return;
    }

    for (size_t i = 0; i < addr_space_sz / sizeof(void*); ++i) {
        memblock[i] = &memblock[i];
    }
    

    for (size_t size = 512, step = 16; size <= addr_space_sz / sizeof(void*); size += step) {
        if (size == 0) continue;
        
        // Output the current cache size    
        spdlog::debug("Current cache size: {} B ({:.3f} KiB)\r", size, static_cast<double>(size) / 1024.0);

        double ns_per_it = cache_latency(size, iterations);

        if (ns_per_it == 0.0) {
            spdlog::warn("Warning: cache latency is 0.0 for size {} B", size);
        }

        sizes.push_back(size);
        nanos.push_back(ns_per_it);
        rounds++;

        // Double the step size at powers of two
        if (0 == ((size - 1) & size)) {
            step <<= 1;
        }

        //  Adjust the number of iterations based on latency
        iterations = static_cast<uint64_t>(static_cast<double>(max_iterations) / ns_per_it);
        if (iterations < min_iterations) {
            iterations = min_iterations;
        }

        // Output the results every 2048 rounds
        if (rounds == 2048) {
            for (size_t r = 0; r < 2048; ++r) {
                spdlog::debug("{} , {}", sizes[r], nanos[r]);
            }
            rounds = 0;
        }
    }
    


    // Store the results
    mem_sizes = sizes;
    mem_times = nanos;



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
/////// remplacer tous les cout par spdlog::info --> fait
//////// remplacer tous les cout par spdlog::debug --> fait
//////// remplacer tous les cout par spdlog::warn --> fait
//////// remplacer tous les cerr par spdlog::error
//////// remplacer les noms Memory par Cache_latency --> fait
//////// changer destrucs dans le json??? --> demander à Miguet
//////// changer truc dans json pour que ça marche pour ARM et x86 , car pas les même caches dans ARM 
//////// changer le python pour trouver les bons caches expérimentaux 