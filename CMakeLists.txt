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

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.1
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.5.0
)
FetchContent_MakeAvailable(cli11)

FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)

FetchContent_MakeAvailable(Eigen3)

FetchContent_Declare(
    OpenCL-Headers
    GIT_REPOSITORY  https://github.com/KhronosGroup/OpenCL-Headers.git
    GIT_TAG         main
)
FetchContent_MakeAvailable(OpenCL-Headers)

FetchContent_Declare(
    OpenCL-ICD-Loader
    GIT_REPOSITORY  https://github.com/KhronosGroup/OpenCL-ICD-Loader.git
    GIT_TAG         main
)
FetchContent_MakeAvailable(OpenCL-ICD-Loader)

FetchContent_Declare(
    OpenCL-Headers-Cpp
    GIT_REPOSITORY  https://github.com/KhronosGroup/OpenCL-CLHPP.git
    GIT_TAG         main
)
FetchContent_MakeAvailable(OpenCL-Headers-Cpp)
    
find_package(OpenMP REQUIRED)

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
    target_compile_options(PPN-microbench PRIVATE -Wall -Wextra -g)
endif()

target_compile_features(PPN-microbench PRIVATE cxx_std_20)