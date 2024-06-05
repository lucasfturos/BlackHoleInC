#ifndef UTIL_H
#define UTIL_H

#include "Vec/vec3.h"

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

#endif //! UTIL_H