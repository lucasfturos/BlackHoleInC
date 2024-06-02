#ifndef NOISE_H
#define NOISE_H

#include "Vec/vec2.h"
#include "Vec/vec3.h"
#include "Vec/vec4.h"

//! Gaussian noise generation using Box-Muller transform with precomputed values
static double UNUSED gaussianNoise(double mu, double sigma) {
    static const double two_pi = 2.0 * M_PI;
    static Vec2 z;
    static int gen;
    gen = !gen;
    if (!gen) {
        return z.y * sigma + mu;
    }
    Vec2 u = Vec2_create(random_double(), random_double());
    z.x = sqrt(-2.0 * log(u.x)) * cos(two_pi * u.y);
    z.y = sqrt(-2.0 * log(u.x)) * sin(two_pi * u.y);
    return z.x * sigma + mu;
}

//! Vec4 hash function
static Vec4 Vec4_hash44(Vec3 v, double t) {
    Vec4 p4 = Vec4_create(v.x, v.y, v.z, t);
    Vec4 factors = Vec4_create(0.1031, 0.1030, 0.0973, 0.1099);
    p4 = Vec4_fract(Vec4_mul(p4, factors));

    Vec4 sum = Vec4_add(p4, Vec4_create(p4.w, p4.z, p4.x, p4.y));
    double dotProduct = Vec4_dot(p4, sum) + 33.33;
    Vec4 p4PlusDot = Vec4_add(
        p4, Vec4_create(dotProduct, dotProduct, dotProduct, dotProduct));
    Vec4 p4Swizzled2 =
        Vec4_create(p4PlusDot.x, p4PlusDot.x, p4PlusDot.y, p4PlusDot.z);
    Vec4 p4Swizzled =
        Vec4_create(p4PlusDot.z, p4PlusDot.y, p4PlusDot.w, p4PlusDot.x);

    return Vec4_fract(Vec4_create(
        p4Swizzled2.x + p4Swizzled.y, p4Swizzled2.y + p4Swizzled.z,
        p4Swizzled2.z + p4Swizzled.x, p4Swizzled2.w + p4Swizzled.w));
}

//! Perlin noise function
static double perlinNoise(Vec3 pos, uint32_t octave) {
    double t = (double)octave;
    Vec3 f = Vec3_fract(pos);
    pos.x = floor(pos.x);
    pos.y = floor(pos.y);
    pos.z = floor(pos.z);

    double t0 = Vec4_hash44(Vec3_add(Vec3_create(0.0, 0.0, 0.0), pos), t).x;
    double t1 = Vec4_hash44(Vec3_add(Vec3_create(1.0, 0.0, 0.0), pos), t).x;
    double t2 = Vec4_hash44(Vec3_add(Vec3_create(0.0, 1.0, 0.0), pos), t).x;
    double t3 = Vec4_hash44(Vec3_add(Vec3_create(1.0, 1.0, 0.0), pos), t).x;
    double t4 = Vec4_hash44(Vec3_add(Vec3_create(0.0, 0.0, 1.0), pos), t).x;
    double t5 = Vec4_hash44(Vec3_add(Vec3_create(1.0, 0.0, 1.0), pos), t).x;
    double t6 = Vec4_hash44(Vec3_add(Vec3_create(0.0, 1.0, 1.0), pos), t).x;
    double t7 = Vec4_hash44(Vec3_add(Vec3_create(1.0, 1.0, 1.0), pos), t).x;

    Vec4 mix_x = Vec4_create(mix(t0, t1, f.x), mix(t2, t3, f.x),
                             mix(t4, t5, f.x), mix(t6, t7, f.x));
    Vec2 mix_y = Vec2_mix(Vec2_create(mix_x.x, mix_x.y),
                          Vec2_create(mix_x.z, mix_x.w), f.y);
    return mix(mix_y.x, mix_y.y, f.z);
}

//! Fractional Brownian Motion (fBm) function
static double fbm(Vec3 pos) {
    double value = 0.0;
    double scale = 1.0;
    double atten = 0.5;
    for (uint32_t i = 0U; i < 8U; ++i) {
        Vec3 scaledPos = Vec3_mul_scalar(pos, scale);
        value += perlinNoise(scaledPos, 10U * i) * atten;
        scale *= 2.2;
        atten *= 0.5;
    }
    return value;
}

#endif