cmake_minimum_required(VERSION 3.27)
project(new_static_site_generator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(static_site_lib STATIC
    textnode.hpp
)

target_include_directories(static_site_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(new_static_site_generator main.cpp)

target_include_directories(new_static_site_generator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/md4qt)

find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(new_static_site_generator PRIVATE Qt6::Core)
target_compile_definitions(new_static_site_generator PRIVATE MD4QT_QT_SUPPORT)
