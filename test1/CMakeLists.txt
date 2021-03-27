cmake_minimum_required(VERSION 3.5)

project(test1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#include_directories(${PROJECT_SOURCE_DIR})

#add_executable(test1 test1.cpp test1.h)
#target_compile_options(test1 -Wall -Wextra --std=c++14)
#add_executable(${PROJECT_NAME} test1.cpp test1.h)
add_executable(${PROJECT_NAME} test1.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra --std=c++14 -ggdb)
set_target_properties( ${PROJECT_NAME}
    PROPERTIES
	OUTPUT_NAME "${PROJECT_NAME}.exe"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
	#LINKER_LANGUAGE C
)
