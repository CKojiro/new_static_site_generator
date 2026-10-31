
cmake_minimum_required(VERSION 3.27)
project(new_static_site_generator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_executable(main
    src/main.cpp
    src/filemove.cpp
    src/generator.cpp
    src/converter.cpp
    src/textnode.cpp
    src/htmlnode.cpp
    src/leafnode.cpp
    src/parentnode.cpp
)

target_include_directories(main PRIVATE
    src
)
