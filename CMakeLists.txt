cmake_minimum_required(VERSION 3.20)
project(js_cmp VERSION 0.0.1 LANGUAGES CXX)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Add the JS_CMP_LEXER submodule
add_subdirectory(submodules/Lexer)

# Add the source files for the main program
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "main.cpp"
)


# Add the source files for the JS_CMP library
file(GLOB_RECURSE SOURCES_LIB
        "includes/**/*.hpp"
        "lib/types/*.cpp"
        "lib/types/**/*.cpp"
)

# Add the library for the JS_CMP program
add_library(jscmp ${SOURCES_LIB})

# Add the executable for the JS_CMP program
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the JS_CMP executable with the JS_CMP_LEXER library
target_link_libraries(${PROJECT_NAME} PRIVATE JS_CMP_LEXER)

# Include directories for the JS_CMP_LEXER headers
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/submodules/Lexer/include
)

# Optionally, specify an install rule for the JS_CMP executable
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
