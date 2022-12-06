cmake_minimum_required(VERSION 3.23)
project(Project_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_cpp main.cpp)

target_link_libraries(Project_cpp sfml-graphics sfml-window sfml-system)