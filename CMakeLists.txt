cmake_minimum_required(VERSION 3.10)
project(task8_2)

set(CMAKE_CXX_STANDARD 14)

# google test framework
add_subdirectory(googletest)

# end google test framework
add_subdirectory(Matrix)
add_executable(main main.cpp)

target_link_libraries(main matrix_lib)

## Build test
enable_testing()
add_subdirectory(test)