cmake_minimum_required(VERSION 3.15)
project(cw2)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror --std=c++17 -g ${CMAKE_CXX_FLAGS}")

add_executable(A A.cpp)
add_executable(B B.cpp)
add_executable(C C.cpp)
add_executable(D D.cpp)
add_executable(E E.cpp)