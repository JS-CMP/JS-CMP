cmake_minimum_required(VERSION 3.22)
project(js_cmp VERSION 0.0.1 LANGUAGES CXX)

# Build options
option(BUILD_STATIC "Build static library and statically linked executable" OFF)
option(BUILD_SHARED "Build shared library and dynamically linked executable" ON)
option(BUILD_TESTS "Build test executables" OFF)
option(FORCE_STATIC_DEPS "Force static linking of dependencies where possible" OFF)

add_compile_definitions(
        JS_CMP_VERSION="${PROJECT_VERSION}"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    if(FORCE_STATIC_DEPS)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
    endif()
endif()

# Platform-specific settings
if(APPLE)
    set(ICU_ROOT /opt/homebrew/opt/icu4c CACHE PATH "Path to ICU root")
    # For ARM64 macOS builds
    if(CMAKE_OSX_ARCHITECTURES STREQUAL "arm64")
        set(CMAKE_OSX_ARCHITECTURES arm64 CACHE STRING "Build for ARM64")
    endif()
elseif(UNIX AND NOT APPLE)
    # Linux specific settings
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
        set(ARM64_BUILD TRUE)
    endif()
endif()

include_directories(${PROJECT_SOURCE_DIR}/includes)
include_directories(${PROJECT_SOURCE_DIR}/submodules/Lexer/include)
include_directories(${PROJECT_SOURCE_DIR}/submodules/SyntaxSmith/includes)

# Submodules
add_subdirectory(submodules/Lexer)
add_subdirectory(submodules/SyntaxSmith)

# Find Packages
find_package(Boost REQUIRED COMPONENTS program_options regex)
find_package(ICU REQUIRED COMPONENTS uc i18n)

# JS_CMP core library
file(GLOB_RECURSE SOURCES_LIB "lib/*.cpp")

if(BUILD_STATIC)
    add_library(jscmp STATIC ${SOURCES_LIB})
    set(JSCMP_LIB_TYPE "STATIC")
elseif(BUILD_SHARED)
    add_library(jscmp SHARED ${SOURCES_LIB})
    set(JSCMP_LIB_TYPE "SHARED")
else()
    # Default to static for release, shared for debug
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_library(jscmp STATIC ${SOURCES_LIB})
        set(JSCMP_LIB_TYPE "STATIC")
    else()
        add_library(jscmp SHARED ${SOURCES_LIB})
        set(JSCMP_LIB_TYPE "SHARED")
    endif()
endif()

# Library properties
set_target_properties(jscmp PROPERTIES
    OUTPUT_NAME "jscmp"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Link dependencies based on static/dynamic preference
if(FORCE_STATIC_DEPS OR BUILD_STATIC)
    # Try to link statically where possible
    if(Boost_USE_STATIC_LIBS)
        target_link_libraries(jscmp PUBLIC Boost::regex)
    else()
        # Fallback to dynamic if static not available
        target_link_libraries(jscmp PUBLIC Boost::regex)
    endif()
    
    # ICU static linking
    target_link_libraries(jscmp PUBLIC ICU::uc ICU::i18n)
else()
    # Dynamic linking
    target_link_libraries(jscmp PUBLIC Boost::regex)
    target_link_libraries(jscmp PUBLIC ICU::uc ICU::i18n)
endif()

# Include directories
target_include_directories(jscmp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${ICU_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
)

# JS_CMP executable
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# Executable linking
target_include_directories(${PROJECT_NAME} PRIVATE ${ICU_INCLUDE_DIRS})

if(BUILD_STATIC OR FORCE_STATIC_DEPS)
    # Static executable
    target_link_libraries(${PROJECT_NAME} PRIVATE jscmp)
    target_link_libraries(${PROJECT_NAME} PRIVATE JS_CMP_LEXER)
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
    
    # Try to link ICU statically
    if(ICU_STATIC)
        target_link_libraries(${PROJECT_NAME} PRIVATE ICU::uc ICU::i18n)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE ICU::uc ICU::i18n)
    endif()
else()
    # Dynamic executable
    target_link_libraries(${PROJECT_NAME} PRIVATE jscmp)
    target_link_libraries(${PROJECT_NAME} PRIVATE JS_CMP_LEXER)
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
    target_link_libraries(${PROJECT_NAME} PRIVATE ICU::uc ICU::i18n)
    
    # Set rpath for dynamic executable to find shared libraries
    if(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            INSTALL_RPATH "@loader_path"
            BUILD_RPATH "${CMAKE_BINARY_DIR}"
        )
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES
            INSTALL_RPATH "$ORIGIN"
            BUILD_RPATH "${CMAKE_BINARY_DIR}"
        )
    endif()
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/submodules/Lexer/include)

# Install rules
install(TARGETS jscmp ${PROJECT_NAME}
        EXPORT js_cmpTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Include directories for installation
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/includes/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp")

# Package configuration
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Generate package version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/js_cmpConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Generate package configuration file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/js_cmpConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/js_cmpConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/js_cmp
)

# Install package files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/js_cmpConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/js_cmpConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/js_cmp
)

# Export targets
install(EXPORT js_cmpTargets
    FILE js_cmpTargets.cmake
    NAMESPACE js_cmp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/js_cmp
)

# CMake presets (if supported)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.23)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/presets.cmake OPTIONAL)
endif()