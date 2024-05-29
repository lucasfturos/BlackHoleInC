# -------------------------------------------------------------------

cmake_minimum_required(VERSION 3.4...3.20 FATAL_ERROR)

set(PROJECT_NAME
    Demo
    LANGUAGES C
    VERSION 1.0.0
)

project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(src)

# -------------------------------------------------------------------