#ifndef VEC4_H
#define VEC4_H

#include "util.h"

typedef struct {
    double x, y, z, w;
} Vec4;

// Util
static Vec4 Vec4_create(double x, double y, double z, double w) {
    return (Vec4){.x = x, .y = y, .z = z, .w = w};
}

static void UNUSED Vec4_print(Vec4 v) {
    printf("(%.1f, %.1f, %.1f, %.1f)\n", v.x, v.y, v.z, v.w);
}

// Operations
static Vec4 UNUSED Vec4_add(Vec4 u, Vec4 v) {
    return Vec4_create(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

static Vec4 UNUSED Vec4_sub(Vec4 u, Vec4 v) {
    return Vec4_create(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

static Vec4 UNUSED Vec4_mul(Vec4 u, Vec4 v) {
    return Vec4_create(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

static Vec4 UNUSED Vec4_mul_scalar(Vec4 v, double scalar) {
    return Vec4_create(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

static Vec4 UNUSED Vec4_div_scalar(Vec4 v, double scalar) {
    return Vec4_create(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

static Vec4 UNUSED Vec4_fract(Vec4 v) {
    return Vec4_create(fract(v.x), fract(v.y), fract(v.z), fract(v.z));
}

static double UNUSED Vec4_length(Vec4 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

static Vec4 UNUSED Vec4_normalize(Vec4 v) {
    double len = Vec4_length(v);
    return Vec4_div_scalar(v, len);
}

static double UNUSED Vec4_dot(Vec4 u, Vec4 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

static double UNUSED Vec4_dotp(Vec4 v) { return Vec4_dot(v, v); }

static Vec4 UNUSED Vec4_clamp(Vec4 v, double min, double max) {
    return Vec4_create(clamp(v.x, min, max), clamp(v.y, min, max),
                       clamp(v.z, min, max), clamp(v.w, min, max));
}

static Vec4 UNUSED Vec4_mix(Vec4 u, Vec4 v, double t) {
    return Vec4_create(mix(u.x, v.x, t), mix(u.y, v.y, t), mix(u.z, v.z, t),
                       mix(u.w, v.w, t));
}

//! Random
static Vec4 UNUSED Vec4_random() {
    return Vec4_create(random_double(), random_double(), random_double(),
                       random_double());
}

static Vec4 UNUSED Vec4_random_range(double min, double max) {
    return Vec4_create(min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double());
}

#endif // !VEC4_H