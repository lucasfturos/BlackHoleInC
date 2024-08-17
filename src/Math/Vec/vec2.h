#ifndef VEC2_H
#define VEC2_H

#include "common.h"

typedef struct {
    double x, y;
} Vec2, Position;

//! Util
static inline Vec2 Vec2_create(double x, double y) {
    return (Vec2){.x = x, .y = y};
}

static inline double Vec2_getValue(Vec2 v, int index) {
    switch (index) {
    case 0:
        return v.x;
    case 1:
        return v.y;
    default:
        fprintf(stderr, "Index out of range in Vec2_getValue.\n");
        exit(EXIT_FAILURE);
    }
}

//! Operations
static inline Vec2 Vec2_add(Vec2 u, Vec2 v) {
    return Vec2_create(u.x + v.x, u.y + v.y);
}

static inline Vec2 Vec2_sub(Vec2 u, Vec2 v) {
    return Vec2_create(u.x - v.x, u.y - v.y);
}

static inline Vec2 Vec2_mul(Vec2 u, Vec2 v) {
    return Vec2_create(u.x * v.x, u.y * v.y);
}

static inline Vec2 Vec2_mul_scalar(Vec2 v, double scalar) {
    return Vec2_create(v.x * scalar, v.y * scalar);
}

static inline Vec2 Vec2_div_scalar(Vec2 v, double scalar) {
    return Vec2_create(v.x / scalar, v.y / scalar);
}

static inline Vec2 Vec2_clamp(Vec2 v, double min, double max) {
    return Vec2_create(clamp(v.x, min, max), clamp(v.y, min, max));
}

static inline Vec2 Vec2_fract(Vec2 v) {
    return Vec2_create(fract(v.x), fract(v.y));
}

static inline Vec2 Vec2_floor(Vec2 v) {
    return Vec2_create(floor(v.x), floor(v.y));
}

static inline Vec2 Vec2_mix(Vec2 u, Vec2 v, double t) {
    return Vec2_create(mix(u.x, v.x, t), mix(u.y, v.y, t));
}

// Vec2 Operations
static inline double Vec2_dot(Vec2 u, Vec2 v) { return u.x * v.x + u.y * v.y; }

static inline double Vec2_dotp(Vec2 v) { return Vec2_dot(v, v); }

static inline double Vec2_length(Vec2 v) { return sqrt(Vec2_dotp(v)); }

static inline Vec2 Vec2_normalize(Vec2 v) {
    double len = Vec2_length(v);
    return Vec2_div_scalar(v, len);
}

// Random
static inline Vec2 Vec2_random() {
    return Vec2_create(random_double(), random_double());
}

static inline Vec2 Vec2_random_range(double min, double max) {
    return Vec2_create(min + (max - min) * random_double(),
                       min + (max - min) * random_double());
}

#endif //! VEC2_H