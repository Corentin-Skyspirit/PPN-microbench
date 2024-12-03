cmake_minimum_required(VERSION 3.25)
project(PPN-microbench)
set(CMAKE_CXX_STANDARD 20)

# Export compile_commands.json
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all C++ source files
file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/main/*.cpp"
)

add_subdirectory(src/PPN-microbench)
add_subdirectory(main)

# Add target for clang-format
find_program(CLANG_FORMAT_BIN clang-format)
if(CLANG_FORMAT_BIN)
    add_custom_target(
        clang-format
        COMMAND ${CLANG_FORMAT_BIN} -i ${ALL_CXX_SOURCE_FILES}
        COMMENT "Running clang-format on source files"
    )
endif()