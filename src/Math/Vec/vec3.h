#ifndef VEC3_H
#define VEC3_H

#include "common.h"

typedef struct {
    double x, y, z;
} Vec3;

//! Util
static inline Vec3 Vec3_create(double x, double y, double z) {
    return (Vec3){.x = x, .y = y, .z = z};
}

static inline double Vec3_getValue(Vec3 v, int index) {
    switch (index) {
    case 0:
        return v.x;
    case 1:
        return v.y;
    case 2:
        return v.z;
    default:
        fprintf(stderr, "Index out of range in Vec3_getValue.\n");
        exit(EXIT_FAILURE);
    }
}

static inline void Vec3_print(Vec3 v) {
    printf("(%.1f, %.1f, %.1f)\n", v.x, v.y, v.z);
}

//! Operations
static inline Vec3 Vec3_add(Vec3 u, Vec3 v) {
    return Vec3_create(u.x + v.x, u.y + v.y, u.z + v.z);
}

static inline Vec3 Vec3_sub(Vec3 u, Vec3 v) {
    return Vec3_create(u.x - v.x, u.y - v.y, u.z - v.z);
}

static inline Vec3 Vec3_mul(Vec3 u, Vec3 v) {
    return Vec3_create(u.x * v.x, u.y * v.y, u.z * v.z);
}

static inline Vec3 Vec3_div_scalar(Vec3 v, double scalar) {
    if (scalar == 0) {
        return Vec3_create(NAN, NAN, NAN);
    } else {
        return Vec3_create(v.x / scalar, v.y / scalar, v.z / scalar);
    }
}

static inline Vec3 Vec3_mul_scalar(Vec3 v, double scalar) {
    return Vec3_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

static inline Vec3 Vec3_clamp(Vec3 v, double min, double max) {
    return Vec3_create(clamp(v.x, min, max), clamp(v.y, min, max),
                       clamp(v.z, min, max));
}

static inline Vec3 Vec3_mix(Vec3 u, Vec3 v, double t) {
    return Vec3_create(mix(u.x, v.x, t), mix(u.y, v.y, t), mix(u.z, v.z, t));
}

static inline Vec3 Vec3_fract(Vec3 v) {
    return Vec3_create(fract(v.x), fract(v.y), fract(v.z));
}

//! Vec Operations
static inline double Vec3_dot(Vec3 u, Vec3 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

static inline double Vec3_dotp(Vec3 v) { return Vec3_dot(v, v); }

static inline double Vec3_length(Vec3 v) { return sqrt(Vec3_dotp(v)); }

static inline Vec3 Vec3_normalize(Vec3 v) {
    double len = Vec3_length(v);
    return Vec3_div_scalar(v, len);
}

static inline Vec3 Vec3_cross(Vec3 u, Vec3 v) {
    return Vec3_create(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                       u.x * v.y - u.y * v.x);
}

static inline Vec3 Vec3_reflect(Vec3 v, Vec3 n) {
    return Vec3_sub(v, Vec3_mul_scalar(n, 2.0 * Vec3_dot(v, n)));
}

static inline Vec3 rotate2(Vec3 v, double rot) {
    double s = sin(rot), c = cos(rot);
    return Vec3_create(v.x * c - v.z * s, v.y, v.x * s + v.z * c);
}

//! Random
static inline Vec3 Vec3_random() {
    return Vec3_create(random_double(), random_double(), random_double());
}

static inline Vec3 Vec3_random_range(double min, double max) {
    return Vec3_create(min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double());
}

#endif //! VEC3_H