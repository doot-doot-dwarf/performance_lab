cmake_minimum_required(VERSION 3.5)

project(test4 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(BUILD_GMOCK OFF)
option(INSTALL_GTEST OFF)
option(BUILD_SHARED_LIBS OFF)

configure_file(CMakeLists.txt.in googletest/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/googletest
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest
                 EXCLUDE_FROM_ALL)

# Now simply link against gtest or gtest_main as needed. Eg
#add_executable(example example.cpp)
#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)

include_directories(./ deps/googletest/googletest/include)
add_subdirectory(tests)
#add_subdirectory(deps/googletest)


add_executable(${PROJECT_NAME} main.cpp misc.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra --std=c++14 -ggdb)
set_target_properties( ${PROJECT_NAME}
    PROPERTIES
	OUTPUT_NAME "${PROJECT_NAME}.exe"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
enable_testing()
# Download and unpack googletest at configure time

# Prevent overriding the parent project's compiler/linker
# settings on Windows

