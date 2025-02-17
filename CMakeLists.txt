cmake_minimum_required(VERSION 3.25)
project(PPN-microbench)

enable_language(CXX ASM)

include(FetchContent)

FetchContent_Declare(
    json 
    URL 
    https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(json)

find_package(OpenMP)

add_subdirectory(src/PPN-microbench)
add_subdirectory(main)

# Setup architecture for assembly

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm|aarch64)")
    message(STATUS "Configuring for ARM")
    target_compile_options(PPN-microbench PRIVATE -mcpu=native)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|i[3-6]86)")
    message(STATUS "Configuring for x86")
    target_compile_options(PPN-microbench PRIVATE -march=native -masm=intel)
else()
    message(WARNING "Unknown architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# Debug or not debug, that is the question

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "")
    target_compile_options(PPN-microbench PRIVATE -Wall -Wextra)
endif()

target_compile_features(PPN-microbench PRIVATE cxx_std_20)