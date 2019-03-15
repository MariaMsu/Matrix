## Locate GTest
#find_package(GTest REQUIRED)

# google test framework
include(GoogleTest)

add_executable(run_matrix_test matrix_test.cpp)

target_link_libraries(run_matrix_test matrix_lib)
target_link_libraries(run_matrix_test gtest gtest_main pthread)

gtest_add_tests(TARGET run_matrix_test)
