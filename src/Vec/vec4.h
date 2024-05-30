#ifndef VEC4_H
#define VEC4_H

#include "../Common/util.h"

typedef struct {
    double x, y, z, w;
} Vec4;

// Util
static Vec4 Vec4_create(double x, double y, double z, double w) {
    return (Vec4){.x = x, .y = y, .z = z, .w = w};
}

static void Vec4_print(Vec4 v) __attribute__((unused));
static void Vec4_print(Vec4 v) {
    printf("(%.1f, %.1f, %.1f, %.1f)\n", v.x, v.y, v.z, v.w);
}

// Operations
static Vec4 Vec4_add(Vec4 u, Vec4 v) __attribute__((unused));
static Vec4 Vec4_add(Vec4 u, Vec4 v) {
    return Vec4_create(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

static Vec4 Vec4_sub(Vec4 u, Vec4 v) __attribute__((unused));
static Vec4 Vec4_sub(Vec4 u, Vec4 v) {
    return Vec4_create(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

static Vec4 Vec4_mul(Vec4 u, Vec4 v) __attribute__((unused));
static Vec4 Vec4_mul(Vec4 u, Vec4 v) {
    return Vec4_create(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

static Vec4 Vec4_mul_scalar(Vec4 v, double scalar) __attribute__((unused));
static Vec4 Vec4_mul_scalar(Vec4 v, double scalar) {
    return Vec4_create(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

static Vec4 Vec4_div_scalar(Vec4 v, double scalar) __attribute__((unused));
static Vec4 Vec4_div_scalar(Vec4 v, double scalar) {
    return Vec4_create(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

static Vec4 Vec4_fract(Vec4 v) __attribute__((unused));
static Vec4 Vec4_fract(Vec4 v) {
    return Vec4_create(v.x - floor(v.x), v.y - floor(v.y), v.z - floor(v.z),
                       v.w - floor(v.w));
}

static double Vec4_length(Vec4 v) __attribute__((unused));
static double Vec4_length(Vec4 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

static Vec4 Vec4_normalize(Vec4 v) __attribute__((unused));
static Vec4 Vec4_normalize(Vec4 v) {
    double len = Vec4_length(v);
    return Vec4_div_scalar(v, len);
}

static double Vec4_dot(Vec4 u, Vec4 v) __attribute__((unused));
static double Vec4_dot(Vec4 u, Vec4 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

static double Vec4_dotp(Vec4 v) __attribute__((unused));
static double Vec4_dotp(Vec4 v) { return Vec4_dot(v, v); }

//! Random
static Vec4 Vec4_random() __attribute__((unused));
static Vec4 Vec4_random() {
    return Vec4_create(random_double(), random_double(), random_double(),
                       random_double());
}

static Vec4 Vec4_random_range(double min, double max) __attribute__((unused));
static Vec4 Vec4_random_range(double min, double max) {
    return Vec4_create(min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double(),
                       min + (max - min) * random_double());
}

#endif // !VEC4_H