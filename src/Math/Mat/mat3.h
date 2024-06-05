#ifndef MAT3_H
#define MAT3_H

#include "../Vec/vec3.h"
#include "../common.h"

typedef struct {
    Vec3 v[3];
} Mat3;

//! Util
static Mat3 Mat3_create(Vec3 row0, Vec3 row1, Vec3 row2) {
    return (Mat3){.v = {row0, row1, row2}};
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
    return Vec3_create(Vec3_dot(m.v[0], v), Vec3_dot(m.v[1], v),
                       Vec3_dot(m.v[2], v));
}

static Mat3 UNUSED Mat3_normalize(Mat3 m) {
    double len =
        sqrt(Vec3_dotp(m.v[0]) + Vec3_dotp(m.v[1]) + Vec3_dotp(m.v[2]));
    return Mat3_div_scalar(m, len);
}

static Mat3 UNUSED Mat3_rotational(Vec3 lookFrom, Vec3 lookAt, Vec3 vup) {
    Vec3 w = Vec3_normalize(Vec3_sub(lookFrom, lookAt));
    Vec3 u = Vec3_normalize(Vec3_cross(vup, w));
    Vec3 v = Vec3_cross(w, u);
    return Mat3_create(u, v, w);
}

#endif //! MAT3_H