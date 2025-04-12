set(CMAKE_C_COMPILER /usr/bin/hipcc)
set(CMAKE_CXX_COMPILER /usr/bin/hipcc)

add_executable(main)
target_sources(main PRIVATE main.cpp)
target_link_libraries(main PPN-microbench PPN-microbench-gpu nlohmann_json::nlohmann_json spdlog::spdlog CLI11::CLI11 Kokkos::kokkos)
