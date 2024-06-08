#include "../../src/Math/Mat/mat4.h"

void test_Mat4_create() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    assert(m.v[0].x == 1.0 && m.v[0].y == 2.0 && m.v[0].z == 3.0 &&
           m.v[0].w == 4.0);
    assert(m.v[1].x == 5.0 && m.v[1].y == 6.0 && m.v[1].z == 7.0 &&
           m.v[1].w == 8.0);
    assert(m.v[2].x == 9.0 && m.v[2].y == 10.0 && m.v[2].z == 11.0 &&
           m.v[2].w == 12.0);
    assert(m.v[3].x == 13.0 && m.v[3].y == 14.0 && m.v[3].z == 15.0 &&
           m.v[3].w == 16.0);
    printf("test_Mat4_create passed.\n");
}

void test_Mat4_add() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m1 = Mat4_create(row0, row1, row2, row3);
    Mat4 m2 = Mat4_create(row0, row1, row2, row3);
    Mat4 result = Mat4_add(m1, m2);
    assert(result.v[0].x == 2.0 && result.v[0].y == 4.0 &&
           result.v[0].z == 6.0 && result.v[0].w == 8.0);
    assert(result.v[1].x == 10.0 && result.v[1].y == 12.0 &&
           result.v[1].z == 14.0 && result.v[1].w == 16.0);
    assert(result.v[2].x == 18.0 && result.v[2].y == 20.0 &&
           result.v[2].z == 22.0 && result.v[2].w == 24.0);
    assert(result.v[3].x == 26.0 && result.v[3].y == 28.0 &&
           result.v[3].z == 30.0 && result.v[3].w == 32.0);
    printf("test_Mat4_add passed.\n");
}

void test_Mat4_sub() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m1 = Mat4_create(row0, row1, row2, row3);
    Mat4 m2 = Mat4_create(row0, row1, row2, row3);
    Mat4 result = Mat4_sub(m1, m2);
    assert(result.v[0].x == 0.0 && result.v[0].y == 0.0 &&
           result.v[0].z == 0.0 && result.v[0].w == 0.0);
    assert(result.v[1].x == 0.0 && result.v[1].y == 0.0 &&
           result.v[1].z == 0.0 && result.v[1].w == 0.0);
    assert(result.v[2].x == 0.0 && result.v[2].y == 0.0 &&
           result.v[2].z == 0.0 && result.v[2].w == 0.0);
    assert(result.v[3].x == 0.0 && result.v[3].y == 0.0 &&
           result.v[3].z == 0.0 && result.v[3].w == 0.0);
    printf("test_Mat4_sub passed.\n");
}

void test_Mat4_transpose() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    Mat4 result = Mat4_transpose(m);
    assert(result.v[0].x == 1.0 && result.v[1].x == 2.0 &&
           result.v[2].x == 3.0 && result.v[3].x == 4.0);
    assert(result.v[0].y == 5.0 && result.v[1].y == 6.0 &&
           result.v[2].y == 7.0 && result.v[3].y == 8.0);
    assert(result.v[0].z == 9.0 && result.v[1].z == 10.0 &&
           result.v[2].z == 11.0 && result.v[3].z == 12.0);
    assert(result.v[0].w == 13.0 && result.v[1].w == 14.0 &&
           result.v[2].w == 15.0 && result.v[3].w == 16.0);
    printf("test_Mat4_transpose passed.\n");
}

void test_Mat4_mul_scalar() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    double scalar = 2.0;
    Mat4 result = Mat4_mul_scalar(m, scalar);
    assert(result.v[0].x == 2.0 && result.v[0].y == 4.0 &&
           result.v[0].z == 6.0 && result.v[0].w == 8.0);
    assert(result.v[1].x == 10.0 && result.v[1].y == 12.0 &&
           result.v[1].z == 14.0 && result.v[1].w == 16.0);
    assert(result.v[2].x == 18.0 && result.v[2].y == 20.0 &&
           result.v[2].z == 22.0 && result.v[2].w == 24.0);
    assert(result.v[3].x == 26.0 && result.v[3].y == 28.0 &&
           result.v[3].z == 30.0 && result.v[3].w == 32.0);
    printf("test_Mat4_mul_scalar passed.\n");
}

void test_Mat4_div_scalar() {
    Vec4 row0 = Vec4_create(2.0, 4.0, 6.0, 8.0);
    Vec4 row1 = Vec4_create(10.0, 12.0, 14.0, 16.0);
    Vec4 row2 = Vec4_create(18.0, 20.0, 22.0, 24.0);
    Vec4 row3 = Vec4_create(26.0, 28.0, 30.0, 32.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    double scalar = 2.0;
    Mat4 result = Mat4_div_scalar(m, scalar);
    assert(result.v[0].x == 1.0 && result.v[0].y == 2.0 &&
           result.v[0].z == 3.0 && result.v[0].w == 4.0);
    assert(result.v[1].x == 5.0 && result.v[1].y == 6.0 &&
           result.v[1].z == 7.0 && result.v[1].w == 8.0);
    assert(result.v[2].x == 9.0 && result.v[2].y == 10.0 &&
           result.v[2].z == 11.0 && result.v[2].w == 12.0);
    assert(result.v[3].x == 13.0 && result.v[3].y == 14.0 &&
           result.v[3].z == 15.0 && result.v[3].w == 16.0);
    printf("test_Mat4_div_scalar passed.\n");
}

void test_Mat4_mul() {
    Vec4 row0_m1 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1_m1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2_m1 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3_m1 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m1 = Mat4_create(row0_m1, row1_m1, row2_m1, row3_m1);

    Vec4 row0_m2 = Vec4_create(17.0, 18.0, 19.0, 20.0);
    Vec4 row1_m2 = Vec4_create(21.0, 22.0, 23.0, 24.0);
    Vec4 row2_m2 = Vec4_create(25.0, 26.0, 27.0, 28.0);
    Vec4 row3_m2 = Vec4_create(29.0, 30.0, 31.0, 32.0);
    Mat4 m2 = Mat4_create(row0_m2, row1_m2, row2_m2, row3_m2);

    Mat4 result = Mat4_mul(m1, m2);
    assert(result.v[0].x == 250.0 && result.v[0].y == 260.0 &&
           result.v[0].z == 270.0 && result.v[0].w == 280.0);
    assert(result.v[1].x == 618.0 && result.v[1].y == 644.0 &&
           result.v[1].z == 670.0 && result.v[1].w == 696.0);
    assert(result.v[2].x == 986.0 && result.v[2].y == 1028.0 &&
           result.v[2].z == 1070.0 && result.v[2].w == 1112.0);
    assert(result.v[3].x == 1354.0 && result.v[3].y == 1412.0 &&
           result.v[3].z == 1470.0 && result.v[3].w == 1528.0);
    printf("test_Mat4_mul passed.\n");
}

void test_Mat4_determinant() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    double det = Mat4_determinant(m);
    assert(det == 0.0);
    printf("test_Mat4_determinant passed.\n");
}

void test_Mat4_inverse() {
    Vec4 row0 = Vec4_create(1.0, 0.0, 0.0, 0.0);
    Vec4 row1 = Vec4_create(0.0, 1.0, 0.0, 0.0);
    Vec4 row2 = Vec4_create(0.0, 0.0, 1.0, 0.0);
    Vec4 row3 = Vec4_create(0.0, 0.0, 0.0, 1.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    Mat4 result = Mat4_inverse(m);
    assert(result.v[0].x == 1.0 && result.v[0].y == 0.0 &&
           result.v[0].z == 0.0 && result.v[0].w == 0.0);
    assert(result.v[1].x == 0.0 && result.v[1].y == 1.0 &&
           result.v[1].z == 0.0 && result.v[1].w == 0.0);
    assert(result.v[2].x == 0.0 && result.v[2].y == 0.0 &&
           result.v[2].z == 1.0 && result.v[2].w == 0.0);
    assert(result.v[3].x == 0.0 && result.v[3].y == 0.0 &&
           result.v[3].z == 0.0 && result.v[3].w == 1.0);
    printf("test_Mat4_inverse passed.\n");
}

void test_Mat4_mul_vec4() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    Vec4 v = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 result = Mat4_mul_vec4(m, v);
    assert(result.x == 30.0 && result.y == 70.0 && result.z == 110.0 &&
           result.w == 150.0);
    printf("test_Mat4_mul_vec4 passed.\n");
}

void test_Mat4_normalize() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 3.0, 4.0);
    Vec4 row1 = Vec4_create(5.0, 6.0, 7.0, 8.0);
    Vec4 row2 = Vec4_create(9.0, 10.0, 11.0, 12.0);
    Vec4 row3 = Vec4_create(13.0, 14.0, 15.0, 16.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    Mat4 normalized = Mat4_normalize(m);
    assert(fabs(normalized.v[0].x - 0.025854) < EPS);
    assert(fabs(normalized.v[1].y - 0.155126) < EPS);
    assert(fabs(normalized.v[2].z - 0.284398) < EPS);
    assert(fabs(normalized.v[3].w - 0.413670) < EPS);
    printf("test_Mat4_normalize passed.\n");
}

void test_Mat4_adjugate() {
    Vec4 row0 = Vec4_create(1.0, 2.0, 0.0, 1.0);
    Vec4 row1 = Vec4_create(-1.0, -3.0, 0.0, 1.0);
    Vec4 row2 = Vec4_create(3.0, 6.0, 1.0, 3.0);
    Vec4 row3 = Vec4_create(2.0, 4.0, 0.0, 3.0);
    Mat4 m = Mat4_create(row0, row1, row2, row3);
    Mat4 adjugate = Mat4_adjugate(m);
    assert(adjugate.v[0].x == -3.0);
    assert(adjugate.v[1].y == 2.0);
    assert(adjugate.v[2].z == 0.0);
    assert(adjugate.v[3].w == 0.0);
    printf("test_Mat4_adjugate passed.\n");
}

int run_all_tests_mat4() {
    test_Mat4_create();
    test_Mat4_add();
    test_Mat4_sub();
    test_Mat4_transpose();
    test_Mat4_mul_scalar();
    test_Mat4_div_scalar();
    test_Mat4_mul();
    test_Mat4_determinant();
    test_Mat4_inverse();
    test_Mat4_mul_vec4();
    test_Mat4_normalize();
    test_Mat4_adjugate();

    printf("All Mat4 tests passed.\n");

    return 0;
}
