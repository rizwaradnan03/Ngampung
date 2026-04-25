cmake_minimum_required(VERSION 3.10)
project(Ngampung)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Ngampung ${SOURCES})

# cari raylib
find_package(raylib REQUIRED)

target_link_libraries(Ngampung raylib)