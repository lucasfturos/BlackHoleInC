#ifndef UTIL_H
#define UTIL_H

#include "mat3.h"

static Vec3 UNUSED toCartesian(double rho, double phi, double theta) {
    double sinTheta = sin(theta);
    return Vec3_mul_scalar(
        Vec3_create(sinTheta * cos(phi), sinTheta * sin(phi), cos(theta)), rho);
}

static void UNUSED toSpherical(Vec3 xyz, double *rho, double *phi,
                               double *theta) {
    *rho = Vec3_length(xyz);
    *phi = atan2(xyz.y, xyz.x);
    *theta = acos(xyz.z / *rho);
}

static Mat3 rotationMatrix(Vec3 lookFrom, Vec3 lookAt, Vec3 vup) {
    Vec3 w = Vec3_normalize(Vec3_sub(lookFrom, lookAt));
    Vec3 u = Vec3_normalize(Vec3_cross(vup, w));
    Vec3 v = Vec3_cross(w, u);
    return Mat3_create(w, u, v);
}

#endif //! UTIL_H