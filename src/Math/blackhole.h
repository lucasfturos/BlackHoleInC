#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "mat3.h"
#include "vec2.h"
#include "vec4.h"

#define dt 0.3
#define MAX_DIST 5.0
#define MAX_BOUNCES 8U
#define MAX_STEPS 65536U
// #define MAX_STEPS 256U
#define BLACKHOLE_RADIUS 0.5

static Vec4 Vec4_hash44(Vec3 v, double t) {
    Vec4 p4 = Vec4_create(v.x, v.y, v.z, t);
    Vec4 factors = Vec4_create(0.1031, 0.1030, 0.0973, 0.1099);
    p4 = Vec4_fract((Vec4){p4.x * factors.x, p4.y * factors.y, p4.z * factors.z,
                           p4.w * factors.w});

    Vec4 sum = Vec4_add(p4, (Vec4){p4.w, p4.z, p4.x, p4.y});
    double dot_product = Vec4_dot(p4, sum) + 33.33;
    Vec4 p4_plus_dot = Vec4_add(
        p4, (Vec4){dot_product, dot_product, dot_product, dot_product});
    Vec4 p4_swizzled2 =
        Vec4_create(p4_plus_dot.x, p4_plus_dot.x, p4_plus_dot.y, p4_plus_dot.z);
    Vec4 p4_swizzled =
        Vec4_create(p4_plus_dot.z, p4_plus_dot.y, p4_plus_dot.w, p4_plus_dot.x);

    return Vec4_fract(
        (Vec4){p4_swizzled2.x + p4_swizzled.y, p4_swizzled2.y + p4_swizzled.z,
               p4_swizzled2.z + p4_swizzled.x, p4_swizzled2.w + p4_swizzled.w});
}

static double noise(Vec3 pos, uint32_t octave) {
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

static double fbm(Vec3 pos) {
    double value = 0.0;
    double scale = 1.0;
    double atten = 0.5;
    for (uint32_t i = 0U; i < 8U; ++i) {
        Vec3 scaled_pos = Vec3_mul_scalar(pos, scale);
        value += noise(scaled_pos, 10U * i) * atten;
        scale *= 2.2;
        atten *= 0.5;
    }
    return value;
}

static Vec3 XYZtoRGB(Vec3 XYZ) {
    const Mat3 XYZ2sRGB = Mat3_create(Vec3_create(3.240, -1.537, -0.499),
                                      Vec3_create(-0.969, 1.876, 0.042),
                                      Vec3_create(0.056, -0.204, 1.057));
    return Mat3_mul_vec3(XYZ2sRGB, XYZ);
}

static Vec3 blackbodyXYZ(double t) {
    double u = (0.860117757 + 1.54118254E-4 * t + 1.28641212E-7 * t * t) /
               (1.0 + 8.42420235E-4 * t + 7.08145163E-7 * t * t);
    double v = (0.317398726 + 4.22806245E-5 * t + 4.20481691E-8 * t * t) /
               (1.0 - 2.89741816E-5 * t + 1.61456053E-7 * t * t);

    Vec2 xy = Vec2_create(3.0 * u, 2.0 * v);
    xy = Vec2_div_scalar(xy, 2.0 * u - 8.0 * v + 4.0);
    return Vec3_create(xy.x / xy.y, 1.0, (1.0 - xy.x - xy.y) / xy.y);
}

static Vec3 rotate2(Vec3 vec, double rot) {
    double s = sin(rot), c = cos(rot);
    return Vec3_create(vec.x * c - vec.z * s, vec.y, vec.x * s + vec.z * c);
}

static Vec3 gravitationalForce(Vec3 pos) {
    Vec3 r = Vec3_div_scalar(pos, BLACKHOLE_RADIUS);
    double R = Vec3_length(r);
    double factor = -4.0 * 1.5 / pow(R, 5.0);
    return Vec3_mul_scalar(r, factor);
}

static double getDensity(Vec3 pos, Vec3 *volumeColor, Vec3 *emission) {
    *volumeColor = Vec3_create(0.20, 0.15, 0.10);
    *emission = Vec3_create(0.0, 0.0, 0.0);

    if (Vec3_dotp((Vec3){pos.x, 0.0, pos.z}) > 8.0 || fabs(pos.y) > 0.3) {
        return 0.0;
    }

    Vec3 gasColor = blackbodyXYZ(3300.0);
    gasColor = XYZtoRGB(gasColor);
    gasColor =
        Vec3_clamp(Vec3_div_scalar(gasColor, fmax(fmax(gasColor.x, gasColor.y),
                                                  gasColor.z)),
                   0.0, 1.0);

    Vec3 rotate = rotate2((Vec3){pos.x, 0.0, pos.z},
                          pos.y + Vec3_length((Vec3){pos.x, 0.0, pos.z}) * 2.0);
    double volumeNoise = fbm(Vec3_mul_scalar(rotate, 20.0));
    double multEmiLength =
        Vec3_length((Vec3){0.2 * pos.x, 8.0 * pos.y, 0.2 * pos.z});
    double emissionScale = 128.0 * fmax(volumeNoise - multEmiLength, 0.0) /
                           (Vec3_dotp(pos) * Vec3_dotp(pos) + 0.05);
    *emission = Vec3_mul_scalar(gasColor, emissionScale);

    double densiMultLength =
        Vec3_length((Vec3){0.12 * pos.x, 7.5 * pos.y, 0.12 * pos.z});
    return fmax(volumeNoise - densiMultLength, 0.0) * 128.0;
}

static Vec3 radiance(Vec3 ro, Vec3 rd) {
    Vec3 rayPos = Vec3_add(ro, Vec3_mul_scalar(rd, random_double() * dt));
    Vec3 velocity = rd;
    Vec3 attenuation = Vec3_create(1.0, 1.0, 1.0);
    Vec3 radiance = Vec3_create(0.0, 0.0, 0.0);
    Vec3 volumeColor = Vec3_create(1.0, 1.0, 1.0);
    Vec3 volumeEmission = Vec3_create(0.0, 0.0, 0.0);
    uint32_t bounces = 0U;

    for (uint32_t i = 0U; i < MAX_STEPS; i++) {
        if (bounces > MAX_BOUNCES) {
            break;
        }
        if (Vec3_dotp(rayPos) > MAX_DIST * MAX_DIST) {
            radiance = Vec3_add(
                radiance,
                Vec3_mul_scalar(attenuation,
                                Vec3_length(Vec3_create(0.0, 0.0, 0.0))));
            return radiance;
        }
        double density = getDensity(rayPos, &volumeColor, &volumeEmission);
        double absorbance = exp(-1.0 * density * dt);
        radiance = Vec3_add(
            radiance,
            Vec3_mul_scalar(Vec3_mul(volumeEmission, attenuation), dt));
        if (absorbance < random_double()) {
            velocity = Vec3_reflect(velocity, Vec3_random());
            attenuation =
                Vec3_clamp(Vec3_mul(volumeColor, attenuation), 0.0, 1.0);
            bounces++;
        }
        Vec3 g = gravitationalForce(rayPos);
        velocity = Vec3_add(velocity, Vec3_mul_scalar(g, dt));
        rayPos = Vec3_add(rayPos, Vec3_mul_scalar(velocity, dt));
        if (Vec3_dotp(rayPos) < BLACKHOLE_RADIUS * BLACKHOLE_RADIUS) {
            return radiance;
        }
    }
    return Vec3_create(-1.0, -1.0, -1.0);
}

#endif //! BLACKHOLE_H