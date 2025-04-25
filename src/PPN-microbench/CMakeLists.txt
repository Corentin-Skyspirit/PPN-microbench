add_library(PPN-microbench STATIC)

target_sources(PPN-microbench PRIVATE 
    microbench.cpp 
    context.cpp 
    driver.cpp 
    cpu_frequency.cpp 
    ops.cpp 
    core_to_core_latency.cpp
    load_test.cpp
    cache_latency.cpp 
    mem_bandwidth.cpp
    stream.cpp
    gpu_h2d_bandwidth.cpp
)

target_sources(
    PPN-microbench
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES 
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/microbench.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/context.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/driver.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/ops.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/cache_latency.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/mem_bandwidth.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/asm_functions.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/core_to_core_latency.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/gpu_h2d_bandwidth.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/stream.hpp
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/load_test.hpp
)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm|aarch64)")
    set(ASM_FILES 
        ${PROJECT_SOURCE_DIR}/src/PPN-microbench/asm/cpu_frequency_arm_64.S
        ${PROJECT_SOURCE_DIR}/src/PPN-microbench/asm/add_arm.S
        ${PROJECT_SOURCE_DIR}/src/PPN-microbench/asm/fma_arm.S
        )

elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|i[3-6]86)")
    set(ASM_FILES 
        ${PROJECT_SOURCE_DIR}/src/PPN-microbench/asm/cpu_frequency_x86_64.S
        ${PROJECT_SOURCE_DIR}/src/PPN-microbench/asm/add_x86.S
        ${PROJECT_SOURCE_DIR}/src/PPN-microbench/asm/fma_x86.S
        )
endif()

target_sources(PPN-microbench PRIVATE ${ASM_FILES})

set_target_properties(PPN-microbench PROPERTIES VERIFY_INTERFACE_HEADER_SETS ON)
target_link_libraries(PPN-microbench PRIVATE nlohmann_json::nlohmann_json spdlog::spdlog CLI11::CLI11 OpenMP::OpenMP_CXX OpenCL::OpenCL OpenCL::HeadersCpp)
