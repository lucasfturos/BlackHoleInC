# -------------------------------------------------------------------

cmake_minimum_required(VERSION 3.4...3.20 FATAL_ERROR)

project(Tests LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(TEST_SOURCES
    # Mat
    Mat/mat3.c
    Mat/mat4.c
    # Vec
    Vec/vec2.c
    Vec/vec3.c
    Vec/vec4.c
    # Tensors
    tensor.c
    # main
    main.c
)

add_executable(Tests
    ${TEST_SOURCES}
)

target_include_directories(Tests 
    PRIVATE ../src/Math
)

target_link_libraries(Tests 
    PRIVATE m
)

enable_testing()
add_test(NAME Tests COMMAND Tests)

# -------------------------------------------------------------------