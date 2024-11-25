cmake_minimum_required(VERSION 3.22)
project(js_cmp VERSION 0.0.1 LANGUAGES CXX)

add_compile_definitions(
        JS_CMP_VERSION="${PROJECT_VERSION}"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
include_directories(${PROJECT_SOURCE_DIR}/includes)
add_subdirectory(submodules/Lexer)

find_package(Boost REQUIRED COMPONENTS program_options)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Boost not found!")
endif ()

file(GLOB_RECURSE SOURCES_LIB
        "includes/**/*.hpp"
        "lib/class/**/*.hpp"
        "lib/class/**/*.cpp"
        "lib/types/*.cpp"
        "lib/types/**/*.cpp"
)

file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "src/**/*.cpp"
        "src/*.hpp"
        "src/**/*.hpp"
)
add_library(jscmp ${SOURCES_LIB})

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE JS_CMP_LEXER)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/submodules/Lexer/include
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)