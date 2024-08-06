#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "../Math/color.h"
#include "../Math/noise.h"

#define dt 0.3
#define MAX_DIST 5.0
#define MAX_BOUNCES 4U
#define MAX_STEPS 65536U
#define BLACKHOLE_RADIUS 0.5

static Vec3 gravitationalForce(Vec3 pos) {
    Vec3 r = Vec3_div_scalar(pos, BLACKHOLE_RADIUS);
    double R = Vec3_length(r);
    double factor = -6.0 / (R * R * R * R * R);
    return Vec3_mul_scalar(r, factor);
}

static double getDensity(Vec3 pos, Vec3 *volumeColor, Vec3 *emission) {
    *volumeColor = Vec3_create(0.20, 0.15, 0.10);
    *emission = Vec3_create(0.0, 0.0, 0.0);
    Vec3 xz = Vec3_create(pos.x, 0.0, pos.z);

    if (Vec3_dotp(xz) > 8.0 || fabs(pos.y) > 0.3 * 0.3) {
        return 0.0;
    }

    Vec3 gasColor = colorBlackBodyXYZ(2300.0);
    gasColor = XYZtoRGB(gasColor);
    gasColor =
        Vec3_clamp(Vec3_div_scalar(gasColor, fmax(fmax(gasColor.x, gasColor.y),
                                                  gasColor.z)),
                   0.0, 1.0);

    Vec3 rotate = rotate2(xz, pos.y + Vec3_length(xz) * 2.0);
    double volumeNoise = fbm(Vec3_mul_scalar(rotate, 20.0));
    double multEmiLength =
        Vec3_length(Vec3_mul(Vec3_create(0.2, 8.0, 0.2), pos));
    double emissionScale = 128.0 * fmax(volumeNoise - multEmiLength, 0.0) /
                           ((Vec3_dotp(Vec3_mul_scalar(pos, 0.5)) *
                             Vec3_dotp(Vec3_mul_scalar(pos, 0.5))) +
                            0.05);
    *emission = Vec3_mul_scalar(gasColor, emissionScale);

    double densiMultLength =
        Vec3_length(Vec3_mul(Vec3_create(0.12, 7.5, 0.12), pos));
    return fmax(volumeNoise - densiMultLength, 0.0) * 128.0;
}

static Vec3 skyColor(Vec3 dir) {
    if (Vec3_dotp(dir) < BLACKHOLE_RADIUS * BLACKHOLE_RADIUS) {
        return dir;
    }
    return Vec3_create(0.0, 0.0, 0.0);
}

static Vec3 radiance(Vec3 ro, Vec3 rd) {
    Vec3 rayPos = Vec3_add(ro, Vec3_mul_scalar(rd, random_double() * dt));
    Vec3 velocity = rd;
    Vec3 attenuation = Vec3_create(1.0, 1.0, 1.0);
    Vec3 radiance = Vec3_create(0.0, 0.0, 0.0);
    Vec3 volumeColor = Vec3_create(1.0, 1.0, 1.0);
    Vec3 volumeEmission = Vec3_create(0.0, 0.0, 0.0);
    uint32_t bounces = 0U;

    for (uint32_t i = 0U; i < MAX_STEPS; ++i) {
        if (bounces > MAX_BOUNCES) {
            break;
        }
        if (Vec3_dotp(rayPos) > MAX_DIST * MAX_DIST) {
            radiance = Vec3_add(
                radiance,
                Vec3_mul(attenuation, skyColor(Vec3_normalize(velocity))));
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