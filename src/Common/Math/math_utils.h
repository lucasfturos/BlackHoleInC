#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "../../Vec/vec4.h"

#include <stdint.h>

#define dt 0.05
#define MAX_DIST 4.0
#define MAX_BOUNCES 8U
#define MAX_STEPS 65536U
#define BLACKHOLE_RADIUS 0.5

double fbm(Vec3 pos);
double noise(Vec3 pos, uint32_t octave);
double getDensity(Vec3 position, Vec3 *volumeColor, Vec3 *emission);
void normalize_matrix(Vec3 mat[3]);

Vec3 skyColor(Vec3 dir);
Vec3 XYZtoRGB(Vec3 XYZ);
Vec3 blackbodyXYZ(double t);
Vec3 radiance(Vec3 ro, Vec3 rd);
Vec3 gravitationalForce(Vec3 pos);
Vec3 rotate2(Vec3 vec, double rot);
Vec4 Vec4_hash44(Vec3 v, double t);

#endif //! MATH_UTILS_H