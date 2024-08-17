#ifndef MAT4_H
#define MAT4_H

#include "Vec/vec4.h"

typedef struct {
    Vec4 v[4];
} Mat4;

//! Util
static inline Mat4 Mat4_create(Vec4 row0, Vec4 row1, Vec4 row2, Vec4 row3) {
    return (Mat4){.v = {row0, row1, row2, row3}};
}

static inline void Mat4_print(Mat4 m) {
    printf("Matrix:\n");
    printf("| %.1f, %.1f, %.1f, %.1f |\n", m.v[0].x, m.v[0].y, m.v[0].z,
           m.v[0].w);
    printf("| %.1f, %.1f, %.1f, %.1f |\n", m.v[1].x, m.v[1].y, m.v[1].z,
           m.v[1].w);
    printf("| %.1f, %.1f, %.1f, %.1f |\n", m.v[2].x, m.v[2].y, m.v[2].z,
           m.v[2].w);
    printf("| %.1f, %.1f, %.1f, %.1f |\n", m.v[3].x, m.v[3].y, m.v[3].z,
           m.v[3].w);
}

//! Operations
static inline Mat4 Mat4_add(Mat4 m1, Mat4 m2) {
    return Mat4_create(Vec4_add(m1.v[0], m2.v[0]), Vec4_add(m1.v[1], m2.v[1]),
                       Vec4_add(m1.v[2], m2.v[2]), Vec4_add(m1.v[3], m2.v[3]));
}

static inline Mat4 Mat4_sub(Mat4 m1, Mat4 m2) {
    return Mat4_create(Vec4_sub(m1.v[0], m2.v[0]), Vec4_sub(m1.v[1], m2.v[1]),
                       Vec4_sub(m1.v[2], m2.v[2]), Vec4_sub(m1.v[3], m2.v[3]));
}

static inline Mat4 Mat4_transpose(Mat4 m) {
    return Mat4_create(Vec4_create(m.v[0].x, m.v[1].x, m.v[2].x, m.v[3].x),
                       Vec4_create(m.v[0].y, m.v[1].y, m.v[2].y, m.v[3].y),
                       Vec4_create(m.v[0].z, m.v[1].z, m.v[2].z, m.v[3].z),
                       Vec4_create(m.v[0].w, m.v[1].w, m.v[2].w, m.v[3].w));
}

static inline Mat4 Mat4_mul_scalar(Mat4 m, double scalar) {
    return Mat4_create(
        Vec4_mul_scalar(m.v[0], scalar), Vec4_mul_scalar(m.v[1], scalar),
        Vec4_mul_scalar(m.v[2], scalar), Vec4_mul_scalar(m.v[3], scalar));
}

static inline Mat4 Mat4_div_scalar(Mat4 m, double scalar) {
    return Mat4_create(
        Vec4_div_scalar(m.v[0], scalar), Vec4_div_scalar(m.v[1], scalar),
        Vec4_div_scalar(m.v[2], scalar), Vec4_div_scalar(m.v[3], scalar));
}

static inline Mat4 Mat4_mul(Mat4 m1, Mat4 m2) {
    Mat4 m2_t = Mat4_transpose(m2);
    return Mat4_create(
        Vec4_create(Vec4_dot(m1.v[0], m2_t.v[0]), Vec4_dot(m1.v[0], m2_t.v[1]),
                    Vec4_dot(m1.v[0], m2_t.v[2]), Vec4_dot(m1.v[0], m2_t.v[3])),
        Vec4_create(Vec4_dot(m1.v[1], m2_t.v[0]), Vec4_dot(m1.v[1], m2_t.v[1]),
                    Vec4_dot(m1.v[1], m2_t.v[2]), Vec4_dot(m1.v[1], m2_t.v[3])),
        Vec4_create(Vec4_dot(m1.v[2], m2_t.v[0]), Vec4_dot(m1.v[2], m2_t.v[1]),
                    Vec4_dot(m1.v[2], m2_t.v[2]), Vec4_dot(m1.v[2], m2_t.v[3])),
        Vec4_create(Vec4_dot(m1.v[3], m2_t.v[0]), Vec4_dot(m1.v[3], m2_t.v[1]),
                    Vec4_dot(m1.v[3], m2_t.v[2]),
                    Vec4_dot(m1.v[3], m2_t.v[3])));
}

//! Mat4 Operations
static inline Vec4 Mat4_mul_vec4(Mat4 m, Vec4 v) {
    return Vec4_create(Vec4_dot(m.v[0], v), Vec4_dot(m.v[1], v),
                       Vec4_dot(m.v[2], v), Vec4_dot(m.v[3], v));
}

static inline Mat4 Mat4_normalize(Mat4 m) {
    double len = sqrt(Vec4_dotp(m.v[0]) + Vec4_dotp(m.v[1]) +
                      Vec4_dotp(m.v[2]) + Vec4_dotp(m.v[3]));
    return Mat4_div_scalar(m, len);
}

static inline double Mat4_determinant(Mat4 m) {
    Vec4 c0 = Vec4_cross(m.v[1], m.v[2]);
    return Vec4_dot(m.v[0], c0);
}

static inline Mat4 Mat4_adjugate(Mat4 m) {
    Vec4 c0 = Vec4_cross(m.v[1], m.v[2]);
    Vec4 c1 = Vec4_cross(m.v[2], m.v[3]);
    Vec4 c2 = Vec4_cross(m.v[3], m.v[0]);
    Vec4 c3 = Vec4_cross(m.v[0], m.v[1]);

    return Mat4_create(Vec4_create(c0.x, c1.x, c2.x, c3.x),
                       Vec4_create(c0.y, c1.y, c2.y, c3.y),
                       Vec4_create(c0.z, c1.z, c2.z, c3.z),
                       Vec4_create(c0.w, c1.w, c2.w, c3.w));
}

static inline Mat4 Mat4_inverse(Mat4 m) {
    double det = Mat4_determinant(m);
    if (fabs(det) > EPS) {
        return m;
    }
    Mat4 adj = Mat4_adjugate(m);
    Mat4 inv = Mat4_mul_scalar(adj, 1 / det);
    return inv;
}

#endif