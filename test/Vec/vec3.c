#include "../../src/Math/Vec/vec3.h"

void test_Vec3_create() {
    Vec3 v = Vec3_create(1.0, 2.0, 3.0);
    assert(v.x == 1.0);
    assert(v.y == 2.0);
    assert(v.z == 3.0);
    printf("test_Vec3_create passed.\n");
}

void test_Vec3_getValue() {
    Vec3 v = Vec3_create(4.0, 5.0, 6.0);
    assert(Vec3_getValue(v, 0) == 4.0);
    assert(Vec3_getValue(v, 1) == 5.0);
    assert(Vec3_getValue(v, 2) == 6.0);
    printf("test_Vec3_getValue passed.\n");
}

void test_Vec3_add() {
    Vec3 v1 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 v2 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 result = Vec3_add(v1, v2);
    assert(result.x == 5.0);
    assert(result.y == 7.0);
    assert(result.z == 9.0);
    printf("test_Vec3_add passed.\n");
}

void test_Vec3_sub() {
    Vec3 v1 = Vec3_create(5.0, 6.0, 7.0);
    Vec3 v2 = Vec3_create(3.0, 2.0, 1.0);
    Vec3 result = Vec3_sub(v1, v2);
    assert(result.x == 2.0);
    assert(result.y == 4.0);
    assert(result.z == 6.0);
    printf("test_Vec3_sub passed.\n");
}

void test_Vec3_mul() {
    Vec3 v1 = Vec3_create(2.0, 3.0, 4.0);
    Vec3 v2 = Vec3_create(5.0, 6.0, 7.0);
    Vec3 result = Vec3_mul(v1, v2);
    assert(result.x == 10.0);
    assert(result.y == 18.0);
    assert(result.z == 28.0);
    printf("test_Vec3_mul passed.\n");
}

void test_Vec3_div_scalar() {
    Vec3 v = Vec3_create(8.0, 10.0, 12.0);
    double scalar = 2.0;
    Vec3 result = Vec3_div_scalar(v, scalar);
    assert(result.x == 4.0);
    assert(result.y == 5.0);
    assert(result.z == 6.0);
    printf("test_Vec3_div_scalar passed.\n");
}

void test_Vec3_mul_scalar() {
    Vec3 v = Vec3_create(2.0, 3.0, 4.0);
    double scalar = 3.0;
    Vec3 result = Vec3_mul_scalar(v, scalar);
    assert(result.x == 6.0);
    assert(result.y == 9.0);
    assert(result.z == 12.0);
    printf("test_Vec3_mul_scalar passed.\n");
}

void test_Vec3_clamp() {
    Vec3 v = Vec3_create(5.0, 10.0, 15.0);
    double min = 0.0;
    double max = 6.0;
    Vec3 result = Vec3_clamp(v, min, max);
    assert(result.x == 5.0);
    assert(result.y == 6.0);
    assert(result.z == 6.0);
    printf("test_Vec3_clamp passed.\n");
}

void test_Vec3_mix() {
    Vec3 v1 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 v2 = Vec3_create(4.0, 5.0, 6.0);
    double t = 0.5;
    Vec3 result = Vec3_mix(v1, v2, t);
    assert(result.x == 2.5);
    assert(result.y == 3.5);
    assert(result.z == 4.5);
    printf("test_Vec3_mix passed.\n");
}

void test_Vec3_fract() {
    Vec3 v = Vec3_create(5.5, 10.9, 15.3);
    Vec3 result = Vec3_fract(v);
    assert(fabs(result.x - 0.5) < EPS);
    assert(fabs(result.y - 0.9) < EPS);
    assert(fabs(result.z - 0.3) < EPS);
    printf("test_Vec3_fract passed.\n");
}

void test_Vec3_dot() {
    Vec3 v1 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 v2 = Vec3_create(4.0, 5.0, 6.0);
    double result = Vec3_dot(v1, v2);
    assert(result == 32.0);
    printf("test_Vec3_dot passed.\n");
}

void test_Vec3_length() {
    Vec3 v = Vec3_create(3.0, 4.0, 5.0);
    double result = Vec3_length(v);
    assert(result == sqrt(50.0));
    printf("test_Vec3_length passed.\n");
}

void test_Vec3_normalize() {
    Vec3 v = Vec3_create(3.0, 4.0, 5.0);
    Vec3 result = Vec3_normalize(v);
    double len = Vec3_length(v);
    assert(fabs(result.x - 3.0 / len) < EPS);
    assert(fabs(result.y - 4.0 / len) < EPS);
    assert(fabs(result.z - 5.0 / len) < EPS);
    printf("test_Vec3_normalize passed.\n");
}

void test_Vec3_cross() {
    Vec3 v1 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 v2 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 result = Vec3_cross(v1, v2);
    assert(result.x == -3.0);
    assert(result.y == 6.0);
    assert(result.z == -3.0);
    printf("test_Vec3_cross passed.\n");
}

void test_Vec3_reflect() {
    Vec3 v = Vec3_create(1.0, -1.0, 0.0);
    Vec3 n = Vec3_create(0.0, 1.0, 0.0);
    Vec3 result = Vec3_reflect(v, n);
    assert(result.x == 1.0);
    assert(result.y == 1.0);
    assert(result.z == 0.0);
    printf("test_Vec3_reflect passed.\n");
}

void test_Vec3_rotate2() {
    Vec3 v = Vec3_create(1.0, 0.0, 0.0);
    double rot = M_PI / 2.0;
    Vec3 result = rotate2(v, rot);
    assert(fabs(result.x - 0.0) < EPS);
    assert(fabs(result.y - 0.0) < EPS);
    assert(fabs(result.z - 1.0) < EPS);
    printf("test_Vec3_rotate2 passed.\n");
}

void test_Vec3_random() {
    Vec3 v = Vec3_random();
    assert(v.x >= 0.0 && v.x <= 1.0);
    assert(v.y >= 0.0 && v.y <= 1.0);
    assert(v.z >= 0.0 && v.z <= 1.0);
    printf("test_Vec3_random passed.\n");
}

void test_Vec3_random_range() {
    Vec3 v = Vec3_random_range(5.0, 10.0);
    assert(v.x >= 5.0 && v.x <= 10.0);
    assert(v.y >= 5.0 && v.y <= 10.0);
    assert(v.z >= 5.0 && v.z <= 10.0);
    printf("test_Vec3_random_range passed.\n");
}

int run_all_tests_vec3() {
    test_Vec3_create();
    test_Vec3_getValue();
    test_Vec3_add();
    test_Vec3_sub();
    test_Vec3_mul();
    test_Vec3_div_scalar();
    test_Vec3_mul_scalar();
    test_Vec3_clamp();
    test_Vec3_mix();
    test_Vec3_fract();
    test_Vec3_dot();
    test_Vec3_length();
    test_Vec3_normalize();
    test_Vec3_cross();
    test_Vec3_reflect();
    test_Vec3_rotate2();
    test_Vec3_random();
    test_Vec3_random_range();

    printf("All Vec3 tests passed.\n");
    return 0;
}