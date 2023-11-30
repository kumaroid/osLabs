set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/parent.cpp main.cpp)
add_executable(child src/child.cpp)

target_include_directories(main PRIVATE include)
target_include_directories(child PRIVATE include)
