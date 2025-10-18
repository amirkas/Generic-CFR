cmake_minimum_required(VERSION 3.10)
project(GenericCFR)

add_subdirectory(GameTree)

target_include_directories(GenericCFR PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/GameTree
)