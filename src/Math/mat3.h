#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"

typedef struct {
    Vec3 v[3];
} Mat3;

//! Util
static Mat3 Mat3_create(Vec3 col0, Vec3 col1, Vec3 col2) {
    return (Mat3){.v = {col0, col1, col2}};
}

static void UNUSED Mat3_print(Mat3 m) {
    printf("Matrix:\n");
    printf("| %.1f, %.1f, %.1f |\n", m.v[0].x, m.v[0].y, m.v[0].z);
    printf("| %.1f, %.1f, %.1f |\n", m.v[1].x, m.v[1].y, m.v[1].z);
    printf("| %.1f, %.1f, %.1f |\n", m.v[2].x, m.v[2].y, m.v[2].z);
}

//! Operations
static Mat3 UNUSED Mat3_add(Mat3 m1, Mat3 m2) {
    return Mat3_create(Vec3_add(m1.v[0], m2.v[0]), Vec3_add(m1.v[1], m2.v[1]),
                       Vec3_add(m1.v[2], m2.v[2]));
}

static Mat3 UNUSED Mat3_sub(Mat3 m1, Mat3 m2) {
    return Mat3_create(Vec3_sub(m1.v[0], m2.v[0]), Vec3_sub(m1.v[1], m2.v[1]),
                       Vec3_sub(m1.v[2], m2.v[2]));
}

static Mat3 UNUSED Mat3_transpose(Mat3 m) {
    return Mat3_create(Vec3_create(m.v[0].x, m.v[1].x, m.v[2].x),
                       Vec3_create(m.v[0].y, m.v[1].y, m.v[2].y),
                       Vec3_create(m.v[0].z, m.v[1].z, m.v[2].z));
}

static Mat3 UNUSED Mat3_mul_scalar(Mat3 m, double scalar) {
    return Mat3_create(Vec3_mul_scalar(m.v[0], scalar),
                       Vec3_mul_scalar(m.v[1], scalar),
                       Vec3_mul_scalar(m.v[2], scalar));
}

static Mat3 UNUSED Mat3_div_scalar(Mat3 m, double scalar) {
    return Mat3_create(Vec3_div_scalar(m.v[0], scalar),
                       Vec3_div_scalar(m.v[1], scalar),
                       Vec3_div_scalar(m.v[2], scalar));
}

static Mat3 UNUSED Mat3_mul(Mat3 m1, Mat3 m2) {
    Mat3 m2_t = Mat3_transpose(m2);
    return Mat3_create(
        Vec3_create(Vec3_dot(m1.v[0], m2_t.v[0]), Vec3_dot(m1.v[0], m2_t.v[1]),
                    Vec3_dot(m1.v[0], m2_t.v[2])),
        Vec3_create(Vec3_dot(m1.v[1], m2_t.v[0]), Vec3_dot(m1.v[1], m2_t.v[1]),
                    Vec3_dot(m1.v[1], m2_t.v[2])),
        Vec3_create(Vec3_dot(m1.v[2], m2_t.v[0]), Vec3_dot(m1.v[2], m2_t.v[1]),
                    Vec3_dot(m1.v[2], m2_t.v[2])));
}

//! Mat3 Operations
static Vec3 UNUSED Mat3_mul_vec3(Mat3 m, Vec3 v) {
    return Vec3_create(m.v[0].x * v.x + m.v[1].x * v.y + m.v[2].x * v.z,
                       m.v[0].y * v.x + m.v[1].y * v.y + m.v[2].y * v.z,
                       m.v[0].z * v.x + m.v[1].z * v.y + m.v[2].z * v.z);
}

static Mat3 UNUSED Mat3_normalize(Mat3 m) {
    return Mat3_create(Vec3_normalize(m.v[0]), Vec3_normalize(m.v[1]),
                       Vec3_normalize(m.v[2]));
}

#endif //! MAT3_H