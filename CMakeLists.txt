cmake_minimum_required(VERSION 4.0)
project(k_lang C)

set(CMAKE_C_STANDARD 23)
file(GLOB SOURCES "src/*.c" "include/*.h")

add_executable(k_lang ${SOURCES})
target_include_directories(k_lang PRIVATE include)