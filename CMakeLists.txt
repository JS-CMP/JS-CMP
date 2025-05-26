cmake_minimum_required(VERSION 3.22)
project(js_cmp VERSION 0.0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(JS_CMP_VERSION="${PROJECT_VERSION}")

add_subdirectory(submodules/Lexer)

if(APPLE)
    set(ICU_ROOT /opt/homebrew/opt/icu4c CACHE PATH "Path to ICU root")
endif()

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(ICU REQUIRED COMPONENTS uc i18n)

include_directories(${PROJECT_SOURCE_DIR}/includes)

file(GLOB_RECURSE SOURCES_LIB "lib/*.cpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(jscmp STATIC ${SOURCES_LIB})
target_link_libraries(jscmp PUBLIC ICU::uc ICU::i18n)
target_include_directories(jscmp PRIVATE ${ICU_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${ICU_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE JS_CMP_LEXER)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/submodules/Lexer/include)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)