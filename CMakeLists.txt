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

set(RESOURCES_DIRECTORY 
    "${CMAKE_SOURCE_DIR}/assets"
)

file(COPY ${RESOURCES_DIRECTORY} 
    DESTINATION ${CMAKE_BINARY_DIR}
)

add_compile_options(
    -Wall -Wextra -Wpedantic -Werror -pedantic -g
)

include(CTest)
add_subdirectory(test)

add_subdirectory(src)

# -------------------------------------------------------------------