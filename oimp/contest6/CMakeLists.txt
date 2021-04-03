cmake_minimum_required(VERSION 3.15)
project(contest6)

# -Werror
set(CMAKE_CXX_FLAGS "-Wall -Wextra --std=c++2a -g ${CMAKE_CXX_FLAGS}")

add_executable(A A.cpp)
add_executable(sem ABCDE.cpp ../contest5/P.cpp)
add_executable(F F.cpp)
add_executable(G G.cpp)
add_executable(L L.cpp)