cmake_minimum_required(VERSION 3.22)
project(JS_CMP_alpha)

set(CMAKE_CXX_STANDARD 23)

include_directories(includes/class)
include_directories(includes/types)

file(GLOB_RECURSE SOURCES_LIB
        "includes/**/*.hpp"
        "lib/class/Rope/*.hpp"
        "lib/types/*.cpp"
        "lib/types/**/*.cpp"
)

file(GLOB_RECURSE SOURCES_GLOB
        "src/*.cpp"
        "src/**/*.cpp"
        "src/*.hpp"
        "src/**/*.hpp"
)

add_library(JS_CMP ${SOURCES_LIB})

add_executable(JS_CMP_alpha main.cpp ${SOURCES_GLOB})
