cmake_minimum_required(VERSION 3.6)

project(test4-tests)

add_executable(test4-tests main.cpp ../misc.cpp)

target_link_libraries(test4-tests ${GTEST_LIBRARIES})
enable_testing()
add_test(test4-tests "./${PROJECT_NAME}")
target_link_libraries(test4-tests PUBLIC gtest)
