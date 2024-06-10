# -------------------------------------------------------------------

set(TEST_SOURCES
    # Black Hole
    BlackHole/blackhole2.c
    # Mat
    Mat/mat3.c
    Mat/mat4.c
    # Tensor
    Tensor/geodesic.c
    Tensor/tensor.c
    Tensor/tetrad.c
    # Vec
    Vec/vec2.c
    Vec/vec3.c
    Vec/vec4.c
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

set(CTEST_PROGRESS_OUTPUT ON)
set(CTEST_OUTPUT_ON_FAILURE ON)

add_test(NAME Tests COMMAND Tests)

# -------------------------------------------------------------------