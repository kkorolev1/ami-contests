cmake_minimum_required(VERSION 3.15)
project(contest4)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror --std=c++17 -g ${CMAKE_CXX_FLAGS}")

add_executable(A A.cpp)
add_executable(G G.cpp)
add_executable(H H.cpp)
add_executable(B B.cpp)