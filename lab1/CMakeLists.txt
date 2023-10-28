cmake_minimum_required(VERSION 3.27.5)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable("son.out" son.cpp)
add_executable(${PROJECT_NAME} main.cpp)


