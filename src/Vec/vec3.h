#ifndef VEC3_H
#define VEC3_H

#include "../Common/util.h"

typedef struct {
    double x, y, z;
} Vec3;

//! Util
static Vec3 Vec3_create(double x, double y, double z) {
    return (Vec3){.x = x, .y = y, .z = z};
}

static void Vec3_print(Vec3 v) __attribute__((unused));
static void Vec3_print(Vec3 v) {
    printf("(%.1f, %.1f, %.1f)\n", v.x, v.y, v.z);
}

//! Operations
static Vec3 Vec3_add(Vec3 u, Vec3 v) __attribute__((unused));
static Vec3 Vec3_add(Vec3 u, Vec3 v) {
    return Vec3_create(u.x + v.x, u.y + v.y, u.z + v.z);
}

static Vec3 Vec3_sub(Vec3 u, Vec3 v) __attribute__((unused));
static Vec3 Vec3_sub(Vec3 u, Vec3 v) {
    return Vec3_create(u.x - v.x, u.y - v.y, u.z - v.z);
}

static Vec3 Vec3_mul(Vec3 u, Vec3 v) __attribute__((unused));
static Vec3 Vec3_mul(Vec3 u, Vec3 v) {
    return Vec3_create(u.x * v.x, u.y * v.y, u.z * v.z);
}

static Vec3 Vec3_div_scalar(Vec3 v, double scalar) __attribute__((unused));
static Vec3 Vec3_div_scalar(Vec3 v, double scalar) {
    if (scalar == 0) {
        return Vec3_create(NAN, NAN, NAN);
    } else {
        return Vec3_create(v.x / scalar, v.y / scalar, v.z / scalar);
    }
}

static Vec3 Vec3_mul_scalar(Vec3 v, double scalar) __attribute__((unused));
static Vec3 Vec3_mul_scalar(Vec3 v, double scalar) {
    return Vec3_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

static Vec3 Vec3_clamp(Vec3 vec, double min, double max)
    __attribute__((unused));
static Vec3 Vec3_clamp(Vec3 vec, double min, double max) {
    return Vec3_create(fmin(fmax(vec.x, min), max), fmin(fmax(vec.y, min), max),
                       fmin(fmax(vec.z, min), max));
}

//! Vec Operations
static Vec3 Vec3_fract(Vec3 v) __attribute__((unused));
static Vec3 Vec3_fract(Vec3 v) {
    Vec3 f = {
        .x = v.x - floor(v.x),
        .y = v.y - floor(v.y),
        .z = v.z - floor(v.z),
    };
    return f;
}

static double Vec3_length(Vec3 v) __attribute__((unused));
static double Vec3_length(Vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

static Vec3 Vec3_normalize(Vec3 v) __attribute__((unused));
static Vec3 Vec3_normalize(Vec3 v) {
    double len = Vec3_length(v);
    return Vec3_div_scalar(v, len);
}

static double Vec3_dot(Vec3 u, Vec3 v) __attribute__((unused));
static double Vec3_dot(Vec3 u, Vec3 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

static double Vec3_dotp(Vec3 v) __attribute__((unused));
static double Vec3_dotp(Vec3 v) { return Vec3_dot(v, v); }

static Vec3 Vec3_cross(Vec3 u, Vec3 v) __attribute__((unused));
static Vec3 Vec3_cross(Vec3 u, Vec3 v) {
    return Vec3_create(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                       u.x * v.y - u.y * v.x);
}

static Vec3 Vec3_reflect(Vec3 v, Vec3 n) __attribute__((unused));
static Vec3 Vec3_reflect(Vec3 v, Vec3 n) {
    return Vec3_sub(v, Vec3_mul_scalar(n, 2.0 * Vec3_dot(v, n)));
}

//! Random
static Vec3 Vec3_random() __attribute__((unused));
static Vec3 Vec3_random() {
    // double theta = random_double() * 2.0 * M_PI;
    // double phi = acos(2.0 * random_double() - 1.0);
    // double x = sin(phi) * cos(theta);
    // double y = sin(phi) * sin(theta);
    // double z = cos(phi);
    // return Vec3_create(x, y, z);
    return Vec3_create(random_double(), random_double(), random_double());
}

static Vec3 Vec3_random_range(double min, double max) __attribute__((unused));
static Vec3 Vec3_random_range(double min, double max) {
    return Vec3_create(min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double());
}

#endif //! VEC3_H