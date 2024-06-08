#include "../../src/Math/Vec/vec4.h"

void test_Vec4_create() {
    Vec4 v = Vec4_create(1.0, 2.0, 3.0, 4.0);
    assert(v.x == 1.0);
    assert(v.y == 2.0);
    assert(v.z == 3.0);
    assert(v.w == 4.0);
    printf("test_Vec4_create passed.\n");
}

void test_Vec4_getValue() {
    Vec4 v = Vec4_create(5.0, 6.0, 7.0, 8.0);
    assert(Vec4_getValue(v, 0) == 5.0);
    assert(Vec4_getValue(v, 1) == 6.0);
    assert(Vec4_getValue(v, 2) == 7.0);
    assert(Vec4_getValue(v, 3) == 8.0);
    printf("test_Vec4_getValue passed.\n");
}

void test_Vec4_add() {
    Vec4 v1 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 v2 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 result = Vec4_add(v1, v2);
    assert(result.x == 6.0);
    assert(result.y == 8.0);
    assert(result.z == 10.0);
    assert(result.w == 12.0);
    printf("test_Vec4_add passed.\n");
}

void test_Vec4_sub() {
    Vec4 v1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 v2 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 result = Vec4_sub(v1, v2);
    assert(result.x == 4.0);
    assert(result.y == 4.0);
    assert(result.z == 4.0);
    assert(result.w == 4.0);
    printf("test_Vec4_sub passed.\n");
}

void test_Vec4_mul() {
    Vec4 v1 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 v2 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 result = Vec4_mul(v1, v2);
    assert(result.x == 5.0);
    assert(result.y == 12.0);
    assert(result.z == 21.0);
    assert(result.w == 32.0);
    printf("test_Vec4_mul passed.\n");
}

void test_Vec4_mul_scalar() {
    Vec4 v = Vec4_create(1.0, 2.0, 3.0, 4.0);
    double scalar = 2.0;
    Vec4 result = Vec4_mul_scalar(v, scalar);
    assert(result.x == 2.0);
    assert(result.y == 4.0);
    assert(result.z == 6.0);
    assert(result.w == 8.0);
    printf("test_Vec4_mul_scalar passed.\n");
}

void test_Vec4_div_scalar() {
    Vec4 v = Vec4_create(4.0, 6.0, 8.0, 10.0);
    double scalar = 2.0;
    Vec4 result = Vec4_div_scalar(v, scalar);
    assert(result.x == 2.0);
    assert(result.y == 3.0);
    assert(result.z == 4.0);
    assert(result.w == 5.0);
    printf("test_Vec4_div_scalar passed.\n");
}

void test_Vec4_fract() {
    Vec4 v = Vec4_create(5.5, 6.6, 7.7, 8.8);
    Vec4 result = Vec4_fract(v);
    assert(fabs(result.x - 0.5) < EPS);
    assert(fabs(result.y - 0.6) < EPS);
    assert(fabs(result.z - 0.7) < EPS);
    assert(fabs(result.w - 0.8) < EPS);
    printf("test_Vec4_fract passed.\n");
}

void test_Vec4_clamp() {
    Vec4 v = Vec4_create(5.0, 10.0, 15.0, 20.0);
    double min = 0.0;
    double max = 10.0;
    Vec4 result = Vec4_clamp(v, min, max);
    assert(result.x == 5.0);
    assert(result.y == 10.0);
    assert(result.z == 10.0);
    assert(result.w == 10.0);
    printf("test_Vec4_clamp passed.\n");
}

void test_Vec4_mix() {
    Vec4 v1 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 v2 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    double t = 0.5;
    Vec4 result = Vec4_mix(v1, v2, t);
    assert(result.x == 3.0);
    assert(result.y == 4.0);
    assert(result.z == 5.0);
    assert(result.w == 6.0);
    printf("test_Vec4_mix passed.\n");
}

void test_Vec4_dot() {
    Vec4 v1 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 v2 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    double result = Vec4_dot(v1, v2);
    assert(result == 70.0);
    printf("test_Vec4_dot passed.\n");
}

void test_Vec4_length() {
    Vec4 v = Vec4_create(3.0, 4.0, 5.0, 6.0);
    double result = Vec4_length(v);
    assert(result == sqrt(86.0));
    printf("test_Vec4_length passed.\n");
}

void test_Vec4_normalize() {
    Vec4 v = Vec4_create(3.0, 4.0, 5.0, 6.0);
    Vec4 result = Vec4_normalize(v);

    double inv_length = 1.0 / sqrt(86.0);
    assert(fabs(result.x - 3.0 * inv_length) < EPS);
    assert(fabs(result.y - 4.0 * inv_length) < EPS);
    assert(fabs(result.z - 5.0 * inv_length) < EPS);
    assert(fabs(result.w - 6.0 * inv_length) < EPS);
    printf("test_Vec4_normalize passed.\n");
}

void test_Vec4_cross() {
    Vec4 v1 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 v2 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 result = Vec4_cross(v1, v2);
    assert(result.x == -4.0);
    assert(result.y == 8.0);
    assert(result.z == -4.0);
    assert(result.w == 0.0);
    printf("test_Vec4_cross passed.\n");
}

void test_Vec4_random() {
    Vec4 v = Vec4_random();
    assert(v.x >= 0.0 && v.x <= 1.0);
    assert(v.y >= 0.0 && v.y <= 1.0);
    assert(v.z >= 0.0 && v.z <= 1.0);
    assert(v.w >= 0.0 && v.w <= 1.0);
    printf("test_Vec4_random passed.\n");
}

void test_Vec4_random_range() {
    Vec4 v = Vec4_random_range(5.0, 10.0);
    assert(v.x >= 5.0 && v.x <= 10.0);
    assert(v.y >= 5.0 && v.y <= 10.0);
    assert(v.z >= 5.0 && v.z <= 10.0);
    assert(v.w >= 5.0 && v.w <= 10.0);
    printf("test_Vec4_random_range passed.\n");
}

int run_all_tests_vec4() {
    test_Vec4_create();
    test_Vec4_getValue();
    test_Vec4_add();
    test_Vec4_sub();
    test_Vec4_mul();
    test_Vec4_mul_scalar();
    test_Vec4_div_scalar();
    test_Vec4_fract();
    test_Vec4_clamp();
    test_Vec4_mix();
    test_Vec4_dot();
    test_Vec4_length();
    test_Vec4_normalize();
    test_Vec4_cross();
    test_Vec4_random();
    test_Vec4_random_range();

    printf("All Vec4 tests passed.\n");
    return 0;
}
