cmake_minimum_required(VERSION 3.20)
project(JS_CMP VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define output directory for the binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Add the JS_CMP_LEXER submodule
add_subdirectory(submodules/Lexer)

# Add the source files for the main program
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "main.cpp"
)

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
