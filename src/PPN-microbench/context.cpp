#include <PPN-microbench/context.hpp>

Context::Context() {
    cpuInfo();
    memoryInfo();
    gpuInfo();
}

Context::~Context() {}

Context &Context::getInstance() {
    static Context instance;
    return instance;
}

// finds and returns the first int in a string, returns 0 if none.
int64_t Context::getFirstInt(std::string input) {
    std::regex pattern("(\\d+)");
    std::smatch match;
    std::regex_search(input, match, pattern);

    for (auto m : match) {
        return stoi(m.str());
    }

    return 0;
}

void Context::cpuInfo() {

    //////////////////////
    // CPU Architecture //
    //////////////////////
    //       SIMD       //
    //////////////////////

    // x86
    #if defined(__i386__) || defined(__x86_64__)
        cpuArchi = "x86";

        if (__builtin_cpu_supports("sse")) {
            simd.emplace("SSE");
        }
        if (__builtin_cpu_supports("sse2")) {
            simd.emplace("SSE2");
        }
        if (__builtin_cpu_supports("sse3")) {
            simd.emplace("SSE3");
        }
        if (__builtin_cpu_supports("sse4.2")) {
            simd.emplace("SSE4.2");
        }
        if (__builtin_cpu_supports("avx")) {
            simd.emplace("AVX");
        }
        if (__builtin_cpu_supports("avx2")) {
            simd.emplace("AVX2");
        }
        if (__builtin_cpu_supports("avx512f")) {
            simd.emplace("AVX512");
        }
    #endif

    // ARM
    #if defined(__arm__) || defined(__aarch64__)
        cpuArchi = "ARM";

        #if defined(__ARM_NEON)
            simd.emplace("NEON");
        #endif
    #endif

    
    double max_mhz = 0.0;
    system("lscpu > /tmp/lscpu_out.txt");
    std::ifstream f_re("/tmp/lscpu_out.txt");


    if (!f_re.is_open()) {
        spdlog::warn("Error opening /tmp/lscpu_out.txt");
        return ;
    }

    std::string re_line;
    bool found = false;

    while (std::getline(f_re, re_line)) {
        if (re_line.find("Vitesse maximale du processeur en MHz") != std::string::npos) {
            // Found the correct line
            std::size_t pos = re_line.find(":");
            if (pos != std::string::npos) {
                std::string value_str = re_line.substr(pos + 1);
                
                // Clean the string (remove spaces)
                value_str.erase(0, value_str.find_first_not_of(" \t"));
                value_str.erase(value_str.find_last_not_of(" \t")+1);

                // Replace comma with a dot for correct conversion
                for (auto& c : value_str) {
                    if (c == ',') c = '.';
                }

                // Convert to double
                std::istringstream iss(value_str);
                iss >> max_mhz;
            }
            found = true;
            break; // No need to continue after finding the correct line
        } else if (re_line.find("CPU max MHz") != std::string::npos) {
            // Found an alternative line
            std::size_t pos = re_line.find(":");
            if (pos != std::string::npos) {
                std::string value_str = re_line.substr(pos + 1);
                
                // Clean the string (remove spaces)
                value_str.erase(0, value_str.find_first_not_of(" \t"));
                value_str.erase(value_str.find_last_not_of(" \t")+1);

                // Convert to double
                std::istringstream iss(value_str);
                iss >> max_mhz;
            }
            found = true;
            break; // No need to continue after finding the correct line
        }
    }

    if (!found) {
        spdlog::warn("No CPU frequency information found in lscpu output.");
    }

    f_re.close();

    this->max_mhz = max_mhz;

    ///////////////
    // Word Size //
    ///////////////

    // I don't know how cursed that is
    wordSize = sizeof(size_t) * 8;

    //////////
    // CPUs //
    //////////

    std::ifstream f("/proc/cpuinfo");
    std::string line;

    size_t currProc = 0;
    std::set<size_t> mappedCores;

    while (std::getline(f, line)) {
        if (line.find("processor") != std::string::npos) {
            currProc = getFirstInt(line);
            threads += 1;
        }

        if (line.find("core id") != std::string::npos) {
            size_t proc = getFirstInt(line);

            // only add the current core to the mapping if it hasn't appeared
            // before.
            if (mappedCores.find(proc) == mappedCores.end()) {
                threadMapping.push_back(currProc);
                mappedCores.emplace(proc);
            }
        }

        if (line.find("physical id") != std::string::npos) {
            size_t sockCout = getFirstInt(line) + 1;
            if (sockets != sockCout) {
                // new socket, we need to clear the mapping set
                mappedCores.clear();
                sockets = sockCout;
            }
        }
    }

    // ARM /proc/cpuinfo has way less information about cpu cores
    // we have to manuall set the mapping
    if (cpuArchi == "ARM") {
        cpus = threads;
        for (size_t i = 0; i < cpus; i++) {
            threadMapping.push_back(i);
        }
    }

    cpus = threadMapping.size();
    f.close();
}

void Context::memoryInfo() {

    /////////
    // RAM //
    /////////

    std::ifstream f("/proc/meminfo");
    std::string line;

    while (std::getline(f, line)) {
        // memory in /proc/meminfo is in kB
        if (line.find("MemTotal:") != std::string::npos)
            memory = getFirstInt(line) * 1000;
    }

    f.close();

    ///////////
    // CACHE //
    ///////////

    l1d = sysconf(_SC_LEVEL1_DCACHE_SIZE);
    l1i = sysconf(_SC_LEVEL1_ICACHE_SIZE);
    l2 = sysconf(_SC_LEVEL2_CACHE_SIZE);
    l3 = sysconf(_SC_LEVEL3_CACHE_SIZE);
}

void Context::gpuInfo() {
    std::vector<cl::Device> tmp_devices;
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // gather a list of all devices. The "main" device will be 
    // the one with the highest compute unit count.
    for (int i = 0; i < platforms.size(); i++) {
        platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &tmp_devices);
        for (auto d : tmp_devices) {
            std::string device_name = d.getInfo<CL_DEVICE_BOARD_NAME_AMD>() == "" ? d.getInfo<CL_DEVICE_NAME>() : d.getInfo<CL_DEVICE_BOARD_NAME_AMD>();
            spdlog::debug("found CL device: {}", device_name);
            devices.push_back(d);

            // chose main device
            if (devices.size() == 1) mainDevice = devices[0];
            if (d.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() > mainDevice.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()) {
                mainDevice = d;
                mainDeviceIndex = devices.size() - 1;
            }
        }
    }

    if (devices.size() == 0) {
        spdlog::warn("No OpenCL device found");
        return;
    }

    // setup a main device and ways to access it
    mainDeviceContext = cl::Context({mainDevice});
    mainDeviceQueue = cl::CommandQueue(mainDeviceContext, mainDevice);

    spdlog::info("Number of OpenCL devices: {}", devices.size());
    // AMD cards are weird names =(
    std::string device_name = mainDevice.getInfo<CL_DEVICE_BOARD_NAME_AMD>() == "" ? mainDevice.getInfo<CL_DEVICE_NAME>() :  mainDevice.getInfo<CL_DEVICE_BOARD_NAME_AMD>();
    spdlog::info("Main device name: {}", device_name);
    spdlog::info("Main device memory: {} Bytes", mainDevice.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>());
    spdlog::info("Main device compute units: {}", mainDevice.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>());
}

json Context::getJson() {
    json obj;

    json cpu_info;
    cpu_info["architechture"] = cpuArchi;
    cpu_info["word_size"] = wordSize;
    cpu_info["sockets"] = sockets;
    cpu_info["cpus"] = cpus;
    cpu_info["threads"] = threads;
    cpu_info["mapping"] = threadMapping;
    cpu_info["max_mhz"] = max_mhz; 
    cpu_info["simd"] = json(simd);


    json mem_info;
    mem_info["total_mem"] = memory;
    mem_info["l1d"] = l1d;
    mem_info["l1i"] = l1i;
    mem_info["l2"] = l2;
    mem_info["l3"] = l3;

    json gpu_info;
    gpu_info["main_device_index"] = mainDeviceIndex;
    gpu_info["devices"] = json::array();
    size_t i;
    for (auto d : devices) {
        json o;
        o["name"] = d.getInfo<CL_DEVICE_BOARD_NAME_AMD>() == "" ? d.getInfo<CL_DEVICE_NAME>() :  d.getInfo<CL_DEVICE_BOARD_NAME_AMD>();
        o["total_memory"] = d.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
        o["max_freq"] = d.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>();
        o["compute_units"] = d.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
        gpu_info["devices"][i] = o;
        i++;
    }

    obj["cpu_info"] = cpu_info;
    obj["mem_info"] = mem_info;
    obj["gpu_info"] = gpu_info;

    return obj;
}

size_t Context::getCpus() { return this->cpus; }

std::vector<size_t> Context::getThreadMapping() { return this->threadMapping; }