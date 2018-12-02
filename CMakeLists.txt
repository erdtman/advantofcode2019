cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(Advent-of-code_2018)

set(DAY1 day1/main.cpp)
set(DAY2 day2/main.cpp)

add_executable(day1 ${DAY1})
add_executable(day2 ${DAY2})