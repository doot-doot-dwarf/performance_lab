cmake_minimum_required(VERSION 3.5)

project(test3 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra --std=c++14 -ggdb)
#set_target_properties( ${PROJECT_NAME}
#    PROPERTIES
#	OUTPUT_NAME "${PROJECT_NAME}.exe"
#	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
#	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
#	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
#)
