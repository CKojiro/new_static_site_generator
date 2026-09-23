cmake_minimum_required(VERSION 3.27)
project(new_static_site_generator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

include(FetchContent)
FetchContent_Declare(
    md4qt
    GIT_REPOSITORY https://github.com/KDE/md4qt.git
    GIT_TAG        kde_dirs
)
FetchContent_MakeAvailable(md4qt)

add_executables(main main.cpp)

target_link_libraries(main PRIVATE Qt6::Core md4qt)
