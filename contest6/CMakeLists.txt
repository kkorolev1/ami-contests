cmake_minimum_required(VERSION 3.15)
project(contest6)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror --std=c++2a -g ${CMAKE_CXX_FLAGS}")

add_executable(A A.cpp)