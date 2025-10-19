cmake_minimum_required(VERSION 3.10)
project(GenericCFR)

add_subdirectory(GameTree)
add_subdirectory(extern/pybind11)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

target_include_directories(GenericCFR PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/GameTree ${CMAKE_CURRENT_SOURCE_DIR}/extern/pybind11/include
)