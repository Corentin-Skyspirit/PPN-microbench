set(CMAKE_C_COMPILER /usr/bin/hipcc)
set(CMAKE_CXX_COMPILER /usr/bin/hipcc)

add_library(PPN-microbench-gpu STATIC)

target_sources(PPN-microbench-gpu PRIVATE gpu_bandwidth.cpp)

target_sources(
    PPN-microbench-gpu
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES 
            ${PROJECT_SOURCE_DIR}/include/PPN-microbench/gpu_bandwidth.hpp
)

set_target_properties(PPN-microbench-gpu PROPERTIES VERIFY_INTERFACE_HEADER_SETS ON)
target_link_libraries(PPN-microbench-gpu PRIVATE nlohmann_json::nlohmann_json spdlog::spdlog CLI11::CLI11 Kokkos::kokkos)
