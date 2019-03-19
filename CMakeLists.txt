cmake_minimum_required(VERSION 3.12)
project(Stress++)
set(CMAKE_CXX_STANDARD 17)

add_executable(Stress++ main.cpp)
target_link_libraries(Stress++ pthread)
