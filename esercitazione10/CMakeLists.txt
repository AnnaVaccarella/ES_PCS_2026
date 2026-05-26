cmake_minimum_required(VERSION 3.10)
project(esercitazione10)

set(CMAKE_CXX_STANDARD 17)


find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(main_program main.cpp)


add_executable(test_program test_gradiente_coniugato.cpp)