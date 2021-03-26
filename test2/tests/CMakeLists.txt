cmake_minimum_required(VERSION 3.6)

project(test2-unit_tests)

add_executable(test2-unit_tests main.cpp ../test2.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra --std=c++14 -ggdb)

target_link_libraries(test2-unit_tests ${GTEST_LIBRARIES})
enable_testing()
add_test(test2-unit_tests "./${PROJECT_NAME}")
target_link_libraries(test2-unit_tests PUBLIC gtest)
