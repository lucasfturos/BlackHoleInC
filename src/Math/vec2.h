#ifndef VEC2_H
#define VEC2_H

#include <math.h>

typedef struct {
    double x, y;
} Vec2, Position;

static Vec2 Vec2_create(double x, double y) { return (Vec2){.x = x, .y = y}; }

static Vec2 Vec2_add(Vec2 u, Vec2 v) __attribute__((unused));
static Vec2 Vec2_add(Vec2 u, Vec2 v) {
    return Vec2_create(u.x + v.x, u.y + v.y);
}

static Vec2 Vec2_sub(Vec2 u, Vec2 v) __attribute__((unused));
static Vec2 Vec2_sub(Vec2 u, Vec2 v) {
    return Vec2_create(u.x - v.x, u.y - v.y);
}

static Vec2 Vec2_mul(Vec2 u, Vec2 v) __attribute__((unused));
static Vec2 Vec2_mul(Vec2 u, Vec2 v) {
    return Vec2_create(u.x * v.x, u.y * v.y);
}

static Vec2 Vec2_mul_scalar(Vec2 v, double scalar) __attribute__((unused));
static Vec2 Vec2_mul_scalar(Vec2 v, double scalar) {
    return Vec2_create(v.x * scalar, v.y * scalar);
}

static Vec2 Vec2_div_scalar(Vec2 v, double scalar) __attribute__((unused));
static Vec2 Vec2_div_scalar(Vec2 v, double scalar) {
    return Vec2_create(v.x / scalar, v.y / scalar);
}

static double Vec2_dot(Vec2 u, Vec2 v) __attribute__((unused));
static double Vec2_dot(Vec2 u, Vec2 v) { return u.x * v.x + u.y * v.y; }

static double Vec2_dotp(Vec2 v) __attribute__((unused));
static double Vec2_dotp(Vec2 v) { return Vec2_dot(v, v); }

static double Vec2_length(Vec2 v) __attribute__((unused));
static double Vec2_length(Vec2 v) { return sqrt(v.x * v.x + v.y * v.y); }

static Vec2 Vec2_normalize(Vec2 v) __attribute__((unused));
static Vec2 Vec2_normalize(Vec2 v) {
    double len = Vec2_length(v);
    return Vec2_div_scalar(v, len);
}

static Vec2 Vec2_fract(Vec2 v) __attribute__((unused));
static Vec2 Vec2_fract(Vec2 v) {
    return Vec2_create(v.x - floor(v.x), v.y - floor(v.y));
}

static Vec2 Vec2_mix(Vec2 u, Vec2 v, double t) __attribute__((unused));
static Vec2 Vec2_mix(Vec2 u, Vec2 v, double t) {
    return Vec2_create(u.x * (1.0 - t) + v.x * t, u.y * (1.0 - t) + v.y * t);
}

#endif //! VEC2_H