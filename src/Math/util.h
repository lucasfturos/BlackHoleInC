#ifndef UTIL_H
#define UTIL_H

#include "Mat/mat3.h"
#include "Mat/mat4.h"
#include "common.h"
#include "tensor.h"

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

static Mat3 UNUSED rotationMat3(Vec3 lookFrom, Vec3 lookAt, Vec3 vup) {
    Vec3 w = Vec3_normalize(Vec3_sub(lookFrom, lookAt));
    Vec3 u = Vec3_normalize(Vec3_cross(vup, w));
    Vec3 v = Vec3_cross(w, u);
    return Mat3_create(u, v, w);
}

static UNUSED Tensor *mat3ToTensor(Mat3 mat) {
    Tensor *tensor = Tensor_create(2, (int[]){3, 3});
    for (int i = 0; i < 3; ++i) {
        Tensor_set(tensor, (int[]){i, 0}, mat.v[i].x);
        Tensor_set(tensor, (int[]){i, 1}, mat.v[i].y);
        Tensor_set(tensor, (int[]){i, 2}, mat.v[i].z);
    }
    return tensor;
}

static UNUSED Tensor *mat4ToTensor(Mat4 mat) {
    Tensor *tensor = Tensor_create(2, (int[]){4, 4});
    for (int i = 0; i < 4; ++i) {
        Tensor_set(tensor, (int[]){i, 0}, mat.v[i].x);
        Tensor_set(tensor, (int[]){i, 1}, mat.v[i].y);
        Tensor_set(tensor, (int[]){i, 2}, mat.v[i].z);
        Tensor_set(tensor, (int[]){i, 3}, mat.v[i].w);
    }
    return tensor;
}

static Mat3 UNUSED tensorToMat3(Tensor *t) {
    assert(t->num_dims == 2 && t->dims[0] == 3 && t->dims[1] == 3 &&
           "Tensor dimensions do not match Mat3 dimensions.\n");

    Mat3 mat;
    for (int i = 0; i < 3; ++i) {
        mat.v[i] = Vec3_create(Tensor_get(t, (int[]){i, 0}),
                               Tensor_get(t, (int[]){i, 1}),
                               Tensor_get(t, (int[]){i, 2}));
    }
    return mat;
}

static Mat4 UNUSED tensorToMat4(Tensor *t) {
    assert(t->num_dims == 2 && t->dims[0] == 4 && t->dims[1] == 4 &&
           "Tensor dimensions do not match Mat4 dimensions.\n");

    Mat4 mat;
    for (int i = 0; i < 4; ++i) {
        mat.v[i] = Vec4_create(
            Tensor_get(t, (int[]){i, 0}), Tensor_get(t, (int[]){i, 1}),
            Tensor_get(t, (int[]){i, 2}), Tensor_get(t, (int[]){i, 3}));
    }
    return mat;
}

#endif //! UTIL_H