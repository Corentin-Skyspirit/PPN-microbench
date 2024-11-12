find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(PPN-microbench STATIC)

target_sources(PPN-microbench PRIVATE awesome_func.cpp microbench.cpp test_class.cpp flops.cpp)

target_sources(
    PPN-microbench
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES ${PROJECT_SOURCE_DIR}/include/PPN-microbench/awesome_header.hpp
        FILES ${PROJECT_SOURCE_DIR}/include/PPN-microbench/microbench.hpp
        FILES ${PROJECT_SOURCE_DIR}/include/PPN-microbench/test_class.hpp
)

set_target_properties(PPN-microbench PROPERTIES VERIFY_INTERFACE_HEADER_SETS ON)

target_link_libraries(PPN-microbench PRIVATE nlohmann_json::nlohmann_json)