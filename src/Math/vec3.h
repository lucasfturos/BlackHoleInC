#ifndef VEC3_H
#define VEC3_H

#include "util.h"

typedef struct {
    double x, y, z;
} Vec3;

//! Util
static Vec3 Vec3_create(double x, double y, double z) {
    return (Vec3){.x = x, .y = y, .z = z};
}

static void UNUSED Vec3_print(Vec3 v) {
    printf("(%.1f, %.1f, %.1f)\n", v.x, v.y, v.z);
}

//! Operations
static Vec3 UNUSED Vec3_add(Vec3 u, Vec3 v) {
    return Vec3_create(u.x + v.x, u.y + v.y, u.z + v.z);
}

static Vec3 UNUSED Vec3_sub(Vec3 u, Vec3 v) {
    return Vec3_create(u.x - v.x, u.y - v.y, u.z - v.z);
}

static Vec3 UNUSED Vec3_mul(Vec3 u, Vec3 v) {
    return Vec3_create(u.x * v.x, u.y * v.y, u.z * v.z);
}

static Vec3 UNUSED Vec3_div_scalar(Vec3 v, double scalar) {
    if (scalar == 0) {
        return Vec3_create(NAN, NAN, NAN);
    } else {
        return Vec3_create(v.x / scalar, v.y / scalar, v.z / scalar);
    }
}

static Vec3 UNUSED Vec3_mul_scalar(Vec3 v, double scalar) {
    return Vec3_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

static Vec3 UNUSED Vec3_clamp(Vec3 v, double min, double max) {
    return Vec3_create(clamp(v.x, min, max), clamp(v.y, min, max),
                       clamp(v.z, min, max));
}

static Vec3 UNUSED Vec3_mix(Vec3 u, Vec3 v, double t) {
    return Vec3_create(mix(u.x, v.x, t), mix(u.y, v.y, t), mix(u.z, v.z, t));
}

//! Vec Operations
static Vec3 UNUSED Vec3_fract(Vec3 v) {
    return Vec3_create(fract(v.x), fract(v.y), fract(v.z));
}

static double UNUSED Vec3_length(Vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

static Vec3 UNUSED Vec3_normalize(Vec3 v) {
    double len = Vec3_length(v);
    return Vec3_div_scalar(v, len);
}

static double UNUSED Vec3_dot(Vec3 u, Vec3 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

static double UNUSED Vec3_dotp(Vec3 v) { return Vec3_dot(v, v); }

static Vec3 UNUSED Vec3_cross(Vec3 u, Vec3 v) {
    return Vec3_create(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                       u.x * v.y - u.y * v.x);
}

static Vec3 UNUSED Vec3_reflect(Vec3 v, Vec3 n) {
    return Vec3_sub(v, Vec3_mul_scalar(n, 2.0 * Vec3_dot(v, n)));
}

static Vec3 rotate2(Vec3 vec, double rot) {
    double s = sin(rot), c = cos(rot);
    return Vec3_create(vec.x * c - vec.z * s, vec.y, vec.x * s + vec.z * c);
}

//! Random
static Vec3 UNUSED Vec3_random() {
    return Vec3_create(random_double(), random_double(), random_double());
}

static Vec3 UNUSED Vec3_random_range(double min, double max) {
    return Vec3_create(min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double());
}

#endif //! VEC3_H