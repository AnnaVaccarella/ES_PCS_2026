cmake_minimum_required(VERSION 3.10)
project(Esercitazione8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_arco test_undirected_edge.cpp)
add_executable(test_grafo test_undirected_graph.cpp)

