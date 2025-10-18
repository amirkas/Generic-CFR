cmake_minimum_required(VERSION 3.10) 
project(GenericCfrLib VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)

set(LIB_SOURCES
        src/node.cpp
        src/infoset.tpp
        src/nodes/player_node.tpp
        src/nodes/chance_node.tpp
        src/probability_set.tpp
        headers/navigator.h
)

# Create the static library target
add_library(GenericCfrLib STATIC ${LIB_SOURCES})

# Specify include directories for the library (if any)
target_include_directories(GenericCfrLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers ${CMAKE_CURRENT_SOURCE_DIR}/headers/nodes
)