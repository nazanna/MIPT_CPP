cmake_minimum_required(VERSION 3.23)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project main.cpp)

target_link_libraries(Project sfml-graphics sfml-window sfml-system)