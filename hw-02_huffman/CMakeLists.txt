cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME hw-02_huffman)
set(COMMON_SOURCES_SRC huffman.cpp)
set(COMMON_SOURCES_INCLUDE huffman.h)

set(PROJECT_MAIN src/main.cpp)
set(PROJECT_TEST test/test.cpp test/doctest.h)

list(TRANSFORM COMMON_SOURCES_SRC PREPEND src/)
list(TRANSFORM COMMON_SOURCES_INCLUDE PREPEND include/)

set(COMMON_SOURCES ${COMMON_SOURCES_SRC} ${COMMON_SOURCES_INCLUDE})

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES ${PROJECT_MAIN} ${COMMON_SOURCES})
set(TEST_SOURCES ${PROJECT_TEST} ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
target_include_directories(${X_PROJECT_NAME} PRIVATE include)

add_executable(${X_PROJECT_NAME}-test ${TEST_SOURCES})
target_include_directories(${X_PROJECT_NAME}-test PRIVATE include)