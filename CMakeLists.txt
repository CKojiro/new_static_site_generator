
cmake_minimum_required(VERSION 3.27)
project(new_static_site_generator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tests
    tests/test.cpp
    src/textnode.cpp
)

target_include_directories(tests PRIVATE
    tests
    src
)
