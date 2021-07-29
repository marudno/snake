cmake_minimum_required(VERSION 3.5)

project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    *.h
    *.cpp
    )

add_executable(snake ${SOURCES})

include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.18362.0/um")
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.18362.0/shared")
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.18362.0/winrt")
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.18362.0/cppwinrt")

target_link_libraries(snake d2d1.lib)
