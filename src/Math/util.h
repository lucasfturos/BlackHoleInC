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

static inline Tensor *partialDerivative(Tensor *(*get_metric)(Tensor *),
                                        Tensor *position, int dimension) {
    assert(dimension >= 0 && dimension < position->dims[0] &&
           "Invalid dimension for partial derivative.");

    double h = 1e-5;

    Tensor *pos_plus_h = Tensor_copy(position);
    Tensor *pos_minus_h = Tensor_copy(position);

    pos_plus_h->data[dimension] += h;
    pos_minus_h->data[dimension] -= h;

    Tensor *metric_plus_h = get_metric(pos_plus_h);
    Tensor *metric_minus_h = get_metric(pos_minus_h);

    Tensor *diff = Tensor_sub(metric_plus_h, metric_minus_h);
    Tensor *derivative = Tensor_div_scalar(diff, 2.0 * h);

    Tensor_free(pos_plus_h);
    Tensor_free(pos_minus_h);
    Tensor_free(metric_plus_h);
    Tensor_free(metric_minus_h);
    Tensor_free(diff);

    return derivative;
}

static inline Tensor *angleToTex(Tensor *angle) {
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

    Tensor *result = Tensor_create(1, (int[]){2});
    Tensor_set(result, (int[]){0}, sx);
    Tensor_set(result, (int[]){1}, sy);
    return result;
}

#endif //! UTIL_H