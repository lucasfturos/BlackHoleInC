#include <stdio.h>

// Declaration of test functions
// Vector Library
int run_all_tests_vec2();
int run_all_tests_vec3();
int run_all_tests_vec4();

// Matrix Library
int run_all_tests_mat3();
int run_all_tests_mat4();

// Tensor Library
int run_all_tests_tensor();

int main() {
    printf("Running Vec2 tests...\n");
    run_all_tests_vec2();

    printf("Running Vec3 tests...\n");
    run_all_tests_vec3();

    printf("Running Vec4 tests...\n");
    run_all_tests_vec4();

    printf("Running Mat3 tests...\n");
    run_all_tests_mat3();

    printf("Running Mat4 tests...\n");
    run_all_tests_mat4();

    printf("Running Tensor tests...\n");
    run_all_tests_tensor();

    printf("All tests passed and completed.\n");
    return 0;
}
