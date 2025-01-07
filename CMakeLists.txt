cmake_minimum_required(VERSION 3.25)
project(PPN-microbench)

include(FetchContent)

FetchContent_Declare(
    json 
    URL 
    https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

# FetchContent_Declare(
#     kokkos
#     URL
#     https://github.com/kokkos/kokkos/releases/download/4.5.00/kokkos-4.5.00.tar.gz
# )

FetchContent_MakeAvailable(json)
# FetchContent_MakeAvailable(kokkos)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -O3 -march=native -fopenmp")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -fopenmp")

find_package(OpenMP)

add_subdirectory(src/PPN-microbench)
add_subdirectory(main)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "")
    target_compile_options(PPN-microbench PRIVATE -Wall -Wextra -march=native)
else()
    target_compile_options(PPN-microbench PRIVATE -march=native)
endif()

target_compile_features(PPN-microbench PRIVATE cxx_std_20)