cmake_minimum_required(VERSION 3.20)
project(esercitazione2) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")


add_executable(es1_posizionamento es1_posizionamento.cpp)
add_executable(es2_primi_algoritmi es2_primi_algoritmi.cpp)
add_executable(es2_bubblesort es2_bubblesort.cpp)
