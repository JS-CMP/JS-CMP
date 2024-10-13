cmake_minimum_required(VERSION 3.22)
project(JS_CMP VERSION 0.0.1 LANGUAGES CXX)

add_compile_definitions(
        JS_CMP_VERSION="${PROJECT_VERSION}"
)

set(CMAKE_CXX_STANDARD 23)

# Find Boost and specify that we need the program_options component
find_package(Boost REQUIRED COMPONENTS program_options)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

include_directories(includes/class)
include_directories(includes/types)

file(GLOB_RECURSE SOURCES_LIB
        "includes/**/*.hpp"
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

# Link Boost program_options library to both the library and executable
target_link_libraries(JS_CMP PRIVATE Boost::program_options)
add_executable(JS_CMP_alpha main.cpp ${SOURCES_GLOB})
target_link_libraries(JS_CMP_alpha PRIVATE JS_CMP Boost::program_options)
