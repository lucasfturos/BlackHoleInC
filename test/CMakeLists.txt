# -------------------------------------------------------------------

set(TEST_SOURCES
    test_tensor.c
)

add_executable(Tests
    ${TEST_SOURCES}
)

target_include_directories(Tests 
    PRIVATE ../src/
)

target_link_libraries(Tests 
    PRIVATE m
)

enable_testing()
add_test(NAME Testes COMMAND Tests)

# -------------------------------------------------------------------