#ifndef VEC4_H
#define VEC4_H

#include "common.h"

typedef struct {
    double x, y, z, w;
} Vec4;

// Util
static inline Vec4 Vec4_create(double x, double y, double z, double w) {
    return (Vec4){.x = x, .y = y, .z = z, .w = w};
}

static inline double Vec4_getValue(Vec4 v, int index) {
    switch (index) {
    case 0:
        return v.x;
    case 1:
        return v.y;
    case 2:
        return v.z;
    case 3:
        return v.w;
    default:
        fprintf(stderr, "Index out of range in Vec4_getValue.\n");
        exit(EXIT_FAILURE);
    }
}

static inline void Vec4_print(Vec4 v) {
    printf("(%.1f, %.1f, %.1f, %.1f)\n", v.x, v.y, v.z, v.w);
}

// Operations
static inline Vec4 Vec4_add(Vec4 u, Vec4 v) {
    return Vec4_create(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

static inline Vec4 Vec4_sub(Vec4 u, Vec4 v) {
    return Vec4_create(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

static inline Vec4 Vec4_mul(Vec4 u, Vec4 v) {
    return Vec4_create(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

static inline Vec4 Vec4_mul_scalar(Vec4 v, double scalar) {
    return Vec4_create(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

static inline Vec4 Vec4_div_scalar(Vec4 v, double scalar) {
    return Vec4_create(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

static inline Vec4 Vec4_fract(Vec4 v) {
    return Vec4_create(fract(v.x), fract(v.y), fract(v.z), fract(v.w));
}

static inline Vec4 Vec4_clamp(Vec4 v, double min, double max) {
    return Vec4_create(clamp(v.x, min, max), clamp(v.y, min, max),
                       clamp(v.z, min, max), clamp(v.w, min, max));
}

static inline Vec4 Vec4_mix(Vec4 u, Vec4 v, double t) {
    return Vec4_create(mix(u.x, v.x, t), mix(u.y, v.y, t), mix(u.z, v.z, t),
                       mix(u.w, v.w, t));
}

//! Vec4 Operations
static inline double Vec4_dot(Vec4 u, Vec4 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

static inline double Vec4_dotp(Vec4 v) { return Vec4_dot(v, v); }

static inline double Vec4_length(Vec4 v) { return sqrt(Vec4_dotp(v)); }

static inline Vec4 Vec4_normalize(Vec4 v) {
    double len = Vec4_length(v);
    return Vec4_div_scalar(v, len);
}

static inline Vec4 Vec4_cross(Vec4 u, Vec4 v) {
    return Vec4_create(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                       u.x * v.y - u.y * v.x, 0.0);
}

//! Random
static inline Vec4 Vec4_random() {
    return Vec4_create(random_double(), random_double(), random_double(),
                       random_double());
}

static inline Vec4 Vec4_random_range(double min, double max) {
    return Vec4_create(min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double());
}

#endif // !VEC4_H