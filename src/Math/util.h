#ifndef UTIL_H
#define UTIL_H

#include "Tensor/tensor.h"
#include "Vec/vec3.h"

static inline Vec3 toCartesian(double rho, double phi, double theta) {
    double sinTheta = sin(theta);
    return Vec3_mul_scalar(
        Vec3_create(sinTheta * cos(phi), sinTheta * sin(phi), cos(theta)), rho);
}

static inline void toSpherical(Vec3 xyz, double *rho, double *phi,
                               double *theta) {
    *rho = Vec3_length(xyz);
    *phi = atan2(xyz.y, xyz.x);
    *theta = acos(xyz.z / *rho);
}

static inline Tensor *partialDerivative(Tensor *(*func)(Tensor *), Tensor *pos,
                                        int dir) {
    assert(func && "Invalid function pointer.");
    assert(pos && "Invalid position tensor.");
    assert(dir >= 0 && dir < pos->dims[0] && "Invalid direction.");

    Tensor p_up = *Tensor_copy(pos);
    Tensor p_lo = *Tensor_copy(pos);
    Tensor_set(&p_up, (int[]){dir}, pos->data[dir] + EPS);
    Tensor_set(&p_lo, (int[]){dir}, pos->data[dir] - EPS);

    Tensor up = *(*func)(&p_up);
    Tensor lo = *(*func)(&p_lo);
    Tensor diff = *Tensor_sub(&up, &lo);

    double scalar = 1 / (2.0 * EPS);
    Tensor *result = Tensor_create(diff.num_dims, diff.dims);
    for (int i = 0; i < diff.num_dims; ++i) {
        result->data[i] = diff.data[i] * scalar;
    }

    Tensor_free(&up);
    Tensor_free(&lo);
    Tensor_free(&diff);

    return result;
}

static inline Tensor angleToTex(Tensor *angle) {
    assert(angle != NULL);

    double theta = fmod(angle->data[0], 2 * M_PI);
    double phi = angle->data[1];
    if (theta >= M_PI) {
        phi += M_PI;
        theta -= M_PI;
    }
    phi = fmod(phi, 2 * M_PI);

    double sx = phi / (2 * M_PI);
    double sy = theta / M_PI;
    sx += 0.5;

    Tensor result = *Tensor_create(1, (int[]){2});
    Tensor_set(&result, (int[]){0}, sx);
    Tensor_set(&result, (int[]){1}, sy);
    return result;
}

#endif //! UTIL_H