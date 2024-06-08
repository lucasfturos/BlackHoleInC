#include "../../src/Math/Vec/vec2.h"

void test_Vec2_create() {
    Vec2 v = Vec2_create(1.0, 2.0);
    assert(v.x == 1.0);
    assert(v.y == 2.0);
    printf("test_Vec2_create passed.\n");
}

void test_Vec2_getValue() {
    Vec2 v = Vec2_create(3.0, 4.0);
    assert(Vec2_getValue(v, 0) == 3.0);
    assert(Vec2_getValue(v, 1) == 4.0);
    printf("test_Vec2_getValue passed.\n");
}

void test_Vec2_add() {
    Vec2 v1 = Vec2_create(1.0, 2.0);
    Vec2 v2 = Vec2_create(3.0, 4.0);
    Vec2 result = Vec2_add(v1, v2);
    assert(result.x == 4.0);
    assert(result.y == 6.0);
    printf("test_Vec2_add passed.\n");
}

void test_Vec2_sub() {
    Vec2 v1 = Vec2_create(5.0, 6.0);
    Vec2 v2 = Vec2_create(3.0, 4.0);
    Vec2 result = Vec2_sub(v1, v2);
    assert(result.x == 2.0);
    assert(result.y == 2.0);
    printf("test_Vec2_sub passed.\n");
}

void test_Vec2_mul() {
    Vec2 v1 = Vec2_create(2.0, 3.0);
    Vec2 v2 = Vec2_create(4.0, 5.0);
    Vec2 result = Vec2_mul(v1, v2);
    assert(result.x == 8.0);
    assert(result.y == 15.0);
    printf("test_Vec2_mul passed.\n");
}

void test_Vec2_mul_scalar() {
    Vec2 v = Vec2_create(2.0, 3.0);
    double scalar = 2.0;
    Vec2 result = Vec2_mul_scalar(v, scalar);
    assert(result.x == 4.0);
    assert(result.y == 6.0);
    printf("test_Vec2_mul_scalar passed.\n");
}

void test_Vec2_div_scalar() {
    Vec2 v = Vec2_create(4.0, 6.0);
    double scalar = 2.0;
    Vec2 result = Vec2_div_scalar(v, scalar);
    assert(result.x == 2.0);
    assert(result.y == 3.0);
    printf("test_Vec2_div_scalar passed.\n");
}

void test_Vec2_clamp() {
    Vec2 v = Vec2_create(5.0, 10.0);
    double min = 0.0;
    double max = 6.0;
    Vec2 result = Vec2_clamp(v, min, max);
    assert(result.x == 5.0);
    assert(result.y == 6.0);
    printf("test_Vec2_clamp passed.\n");
}

void test_Vec2_fract() {
    Vec2 v = Vec2_create(5.5, 10.9);
    Vec2 result = Vec2_fract(v);
    assert(fabs(result.x - 0.5) < EPS);
    assert(fabs(result.y - 0.9) < EPS);
    printf("test_Vec2_fract passed.\n");
}

void test_Vec2_floor() {
    Vec2 v = Vec2_create(5.5, 10.9);
    Vec2 result = Vec2_floor(v);
    assert(result.x == 5.0);
    assert(result.y == 10.0);
    printf("test_Vec2_floor passed.\n");
}

void test_Vec2_mix() {
    Vec2 v1 = Vec2_create(1.0, 2.0);
    Vec2 v2 = Vec2_create(3.0, 4.0);
    double t = 0.5;
    Vec2 result = Vec2_mix(v1, v2, t);
    assert(result.x == 2.0);
    assert(result.y == 3.0);
    printf("test_Vec2_mix passed.\n");
}

void test_Vec2_dot() {
    Vec2 v1 = Vec2_create(1.0, 2.0);
    Vec2 v2 = Vec2_create(3.0, 4.0);
    double result = Vec2_dot(v1, v2);
    assert(result == 11.0);
    printf("test_Vec2_dot passed.\n");
}

void test_Vec2_length() {
    Vec2 v = Vec2_create(3.0, 4.0);
    double result = Vec2_length(v);
    assert(result == 5.0);
    printf("test_Vec2_length passed.\n");
}

void test_Vec2_normalize() {
    Vec2 v = Vec2_create(3.0, 4.0);
    Vec2 result = Vec2_normalize(v);
    assert(fabs(result.x - 0.6) < EPS);
    assert(fabs(result.y - 0.8) < EPS);
    printf("test_Vec2_normalize passed.\n");
}

void test_Vec2_random() {
    Vec2 v = Vec2_random();
    assert(v.x >= 0.0 && v.x <= 1.0);
    assert(v.y >= 0.0 && v.y <= 1.0);
    printf("test_Vec2_random passed.\n");
}

void test_Vec2_random_range() {
    Vec2 v = Vec2_random_range(5.0, 10.0);
    assert(v.x >= 5.0 && v.x <= 10.0);
    assert(v.y >= 5.0 && v.y <= 10.0);
    printf("test_Vec2_random_range passed.\n");
}

int run_all_tests_vec2() {
    test_Vec2_create();
    test_Vec2_getValue();
    test_Vec2_add();
    test_Vec2_sub();
    test_Vec2_mul();
    test_Vec2_mul_scalar();
    test_Vec2_div_scalar();
    test_Vec2_clamp();
    test_Vec2_fract();
    test_Vec2_floor();
    test_Vec2_mix();
    test_Vec2_dot();
    test_Vec2_length();
    test_Vec2_normalize();
    test_Vec2_random();
    test_Vec2_random_range();

    printf("All Vec2 tests passed.\n");
    return 0;
}
