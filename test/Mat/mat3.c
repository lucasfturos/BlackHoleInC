#include "../../src/Math/Mat/mat3.h"

void test_Mat3_create() {
    Vec3 row0 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 row1 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 row2 = Vec3_create(7.0, 8.0, 9.0);
    Mat3 m = Mat3_create(row0, row1, row2);
    assert(m.v[0].x == 1.0 && m.v[0].y == 2.0 && m.v[0].z == 3.0);
    assert(m.v[1].x == 4.0 && m.v[1].y == 5.0 && m.v[1].z == 6.0);
    assert(m.v[2].x == 7.0 && m.v[2].y == 8.0 && m.v[2].z == 9.0);
    printf("test_Mat3_create passed.\n");
}

void test_Mat3_add() {
    Vec3 row0 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 row1 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 row2 = Vec3_create(7.0, 8.0, 9.0);
    Mat3 m1 = Mat3_create(row0, row1, row2);
    Mat3 m2 = Mat3_create(row0, row1, row2);
    Mat3 result = Mat3_add(m1, m2);
    assert(result.v[0].x == 2.0 && result.v[0].y == 4.0 &&
           result.v[0].z == 6.0);
    assert(result.v[1].x == 8.0 && result.v[1].y == 10.0 &&
           result.v[1].z == 12.0);
    assert(result.v[2].x == 14.0 && result.v[2].y == 16.0 &&
           result.v[2].z == 18.0);
    printf("test_Mat3_add passed.\n");
}

void test_Mat3_sub() {
    Vec3 row0 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 row1 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 row2 = Vec3_create(7.0, 8.0, 9.0);
    Mat3 m1 = Mat3_create(row0, row1, row2);
    Mat3 m2 = Mat3_create(row0, row1, row2);
    Mat3 result = Mat3_sub(m1, m2);
    assert(result.v[0].x == 0.0 && result.v[0].y == 0.0 &&
           result.v[0].z == 0.0);
    assert(result.v[1].x == 0.0 && result.v[1].y == 0.0 &&
           result.v[1].z == 0.0);
    assert(result.v[2].x == 0.0 && result.v[2].y == 0.0 &&
           result.v[2].z == 0.0);
    printf("test_Mat3_sub passed.\n");
}

void test_Mat3_transpose() {
    Vec3 row0 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 row1 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 row2 = Vec3_create(7.0, 8.0, 9.0);
    Mat3 m = Mat3_create(row0, row1, row2);
    Mat3 result = Mat3_transpose(m);
    assert(result.v[0].x == 1.0 && result.v[1].x == 2.0 &&
           result.v[2].x == 3.0);
    assert(result.v[0].y == 4.0 && result.v[1].y == 5.0 &&
           result.v[2].y == 6.0);
    assert(result.v[0].z == 7.0 && result.v[1].z == 8.0 &&
           result.v[2].z == 9.0);
    printf("test_Mat3_transpose passed.\n");
}

void test_Mat3_mul_scalar() {
    Vec3 row0 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 row1 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 row2 = Vec3_create(7.0, 8.0, 9.0);
    Mat3 m = Mat3_create(row0, row1, row2);
    double scalar = 2.0;
    Mat3 result = Mat3_mul_scalar(m, scalar);
    assert(result.v[0].x == 2.0 && result.v[0].y == 4.0 &&
           result.v[0].z == 6.0);
    assert(result.v[1].x == 8.0 && result.v[1].y == 10.0 &&
           result.v[1].z == 12.0);
    assert(result.v[2].x == 14.0 && result.v[2].y == 16.0 &&
           result.v[2].z == 18.0);
    printf("test_Mat3_mul_scalar passed.\n");
}

void test_Mat3_div_scalar() {
    Vec3 row0 = Vec3_create(2.0, 4.0, 6.0);
    Vec3 row1 = Vec3_create(8.0, 10.0, 12.0);
    Vec3 row2 = Vec3_create(14.0, 16.0, 18.0);
    Mat3 m = Mat3_create(row0, row1, row2);
    double scalar = 2.0;
    Mat3 result = Mat3_div_scalar(m, scalar);
    assert(result.v[0].x == 1.0 && result.v[0].y == 2.0 &&
           result.v[0].z == 3.0);
    assert(result.v[1].x == 4.0 && result.v[1].y == 5.0 &&
           result.v[1].z == 6.0);
    assert(result.v[2].x == 7.0 && result.v[2].y == 8.0 &&
           result.v[2].z == 9.0);
    printf("test_Mat3_div_scalar passed.\n");
}

void test_Mat3_mul() {
    Vec3 row0 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 row1 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 row2 = Vec3_create(7.0, 8.0, 9.0);
    Mat3 m1 = Mat3_create(row0, row1, row2);
    Mat3 m2 = Mat3_create(row0, row1, row2);
    Mat3 result = Mat3_mul(m1, m2);
    assert(result.v[0].x == 30.0 && result.v[0].y == 36.0 &&
           result.v[0].z == 42.0);
    assert(result.v[1].x == 66.0 && result.v[1].y == 81.0 &&
           result.v[1].z == 96.0);
    assert(result.v[2].x == 102.0 && result.v[2].y == 126.0 &&
           result.v[2].z == 150.0);
    printf("test_Mat3_mul passed.\n");
}

void test_Mat3_mul_vec3() {
    Vec3 row0 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 row1 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 row2 = Vec3_create(7.0, 8.0, 9.0);
    Mat3 m = Mat3_create(row0, row1, row2);
    Vec3 v = Vec3_create(1.0, 2.0, 3.0);
    Vec3 result = Mat3_mul_vec3(m, v);
    assert(result.x == 14.0 && result.y == 32.0 && result.z == 50.0);
    printf("test_Mat3_mul_vec3 passed.\n");
}

void test_Mat3_normalize() {
    Vec3 row0 = Vec3_create(1.0, 2.0, 3.0);
    Vec3 row1 = Vec3_create(4.0, 5.0, 6.0);
    Vec3 row2 = Vec3_create(7.0, 8.0, 9.0);
    Mat3 m = Mat3_create(row0, row1, row2);
    Mat3 result = Mat3_normalize(m);
    assert(fabs(result.v[0].x - 0.059235) < EPS &&
           fabs(result.v[0].y - 0.118470) < EPS &&
           fabs(result.v[0].z - 0.177705) < EPS);
    assert(fabs(result.v[1].x - 0.236940) < EPS &&
           fabs(result.v[1].y - 0.296174) < EPS &&
           fabs(result.v[1].z - 0.355409) < EPS);
    assert(fabs(result.v[2].x - 0.414644) < EPS &&
           fabs(result.v[2].y - 0.473879) < EPS &&
           fabs(result.v[2].z - 0.533114) < EPS);
    printf("test_Mat3_normalize passed.\n");
}

int run_all_tests_mat3() {
    test_Mat3_create();
    test_Mat3_add();
    test_Mat3_sub();
    test_Mat3_transpose();
    test_Mat3_mul_scalar();
    test_Mat3_div_scalar();
    test_Mat3_mul();
    test_Mat3_mul_vec3();
    test_Mat3_normalize();

    printf("All Mat3 tests passed.\n");
    return 0;
}
