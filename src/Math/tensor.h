#ifndef TENSOR_H
#define TENSOR_H

#include "Mat/mat3.h"
#include "Mat/mat4.h"
#include "common.h"
#include <string.h>

#define MAX_DIM 4

typedef struct {
    int dims[MAX_DIM];
    int num_dims;
    double *data;
} Tensor;

//! Util
static UNUSED Tensor *Tensor_create(int num_dims, int *dims) {
    assert(num_dims > 0 && num_dims <= MAX_DIM &&
           "Invalid number of dimensions.");
    for (int i = 0; i < num_dims; ++i) {
        assert(dims[i] > 0 && "Invalid dimension size.");
    }
    Tensor *t = (Tensor *)malloc(sizeof(Tensor));
    t->num_dims = num_dims;
    memcpy(t->dims, dims, num_dims * sizeof(int));
    int total_size = 1;
    for (int i = 0; i < num_dims; ++i) {
        total_size *= dims[i];
    }
    t->data = (double *)malloc(total_size * sizeof(double));
    assert(t->data && "Failed to allocate memory for tensor data.");
    return t;
}

static void UNUSED Tensor_free(Tensor *t) {
    assert(t && "Invalid tensor.");
    if (t->data) {
        free(t->data);
        t->data = NULL;
    }
    t->num_dims = 0;
    for (int i = 0; i < MAX_DIM; ++i) {
        t->dims[i] = 0;
    }
    free(t);
}

static int Tensor_index(Tensor *t, int *indices) {
    for (int i = 0; i < t->num_dims; ++i) {
        assert(indices[i] >= 0 && indices[i] < t->dims[i] &&
               "Index out of bounds.");
    }
    int idx = 0;
    int stride = 1;
    for (int i = t->num_dims - 1; i >= 0; i--) {
        idx += indices[i] * stride;
        stride *= t->dims[i];
    }
    return idx;
}

static double UNUSED Tensor_get(Tensor *t, int *indices) {
    int idx = Tensor_index(t, indices);
    return t->data[idx];
}

static void UNUSED Tensor_set(Tensor *t, int *indices, double value) {
    int idx = Tensor_index(t, indices);
    t->data[idx] = value;
}

static UNUSED Tensor *Tensor_copy(Tensor *t) {
    assert(t && "Invalid tensor.");
    Tensor *copy = Tensor_create(t->num_dims, t->dims);
    int total_size = 1;
    for (int i = 0; i < t->num_dims; ++i) {
        total_size *= t->dims[i];
    }
    memcpy(copy->data, t->data, total_size * sizeof(double));
    return copy;
}

static UNUSED Tensor *Tensor_reshape(Tensor *t, int num_dims, int *dims) {
    assert(t && "Invalid tensor.");
    int total_size = 1;
    for (int i = 0; i < num_dims; ++i) {
        total_size *= dims[i];
    }
    int original_size = 1;
    for (int i = 0; i < t->num_dims; ++i) {
        original_size *= t->dims[i];
    }
    assert(total_size == original_size &&
           "Total number of elements must not change.");

    Tensor *result = Tensor_create(num_dims, dims);
    memcpy(result->data, t->data, total_size * sizeof(double));
    return result;
}

static void UNUSED Tensor_print(Tensor *t) {
    if (t->num_dims == 1) {
        printf("[ ");
        for (int i = 0; i < t->dims[0]; ++i) {
            printf("%.1f ", t->data[i]);
        }
        printf("]\n");
    } else {
        for (int i = 0; i < t->dims[0]; ++i) {
            printf("| ");
            for (int j = 0; j < t->dims[1]; ++j) {
                int idx = i * t->dims[1] + j;
                printf("%.1f\t", t->data[idx]);
            }
            printf("\b\b\b|\n");
        }
    }
}

//! Convert
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

//! Operation
static UNUSED Tensor *Tensor_add(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    int total_size = 1;
    for (int i = 0; i < t1->num_dims; ++i) {
        total_size *= t1->dims[i];
    }
    Tensor *result = Tensor_create(t1->num_dims, t1->dims);
    for (int i = 0; i < total_size; ++i) {
        result->data[i] = t1->data[i] + t2->data[i];
    }
    return result;
}

static void UNUSED Tensor_add_inplace(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    assert(t1->num_dims == t2->num_dims &&
           "Tensors must have the same number of dimensions.");
    for (int i = 0; i < t1->num_dims; ++i) {
        assert(t1->dims[i] == t2->dims[i] &&
               "Tensors must have the same dimensions.");
    }
    int total_size = 1;
    for (int i = 0; i < t1->num_dims; ++i) {
        total_size *= t1->dims[i];
    }
    for (int i = 0; i < total_size; ++i) {
        t1->data[i] += t2->data[i];
    }
}

static UNUSED Tensor *Tensor_sub(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    int total_size = 1;
    for (int i = 0; i < t1->num_dims; ++i) {
        total_size *= t1->dims[i];
    }
    Tensor *result = Tensor_create(t1->num_dims, t1->dims);
    for (int i = 0; i < total_size; ++i) {
        result->data[i] = t1->data[i] - t2->data[i];
    }
    return result;
}

static UNUSED Tensor *Tensor_mul(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    assert(t1->num_dims == 1 && t2->num_dims == 1 &&
           "The tensors must have the same dimensions for the operation of "
           "product.");
    int rows = t1->dims[0];
    int cols = t2->dims[0];
    int dims[] = {rows, cols};
    Tensor *result = Tensor_create(2, dims);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result->data[i * cols + j] = t1->data[i] * t2->data[j];
        }
    }
    return result;
}

static UNUSED Tensor *Tensor_div(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    for (int i = 0; i < t1->num_dims; ++i) {
        assert(t1->dims[i] == t2->dims[i] &&
               "The tensors must have the same dimensions for the operation of "
               "division.");
    }
    if (t1->num_dims != 1 || t2->num_dims != 1) {
        fprintf(stderr, "Division is only supported for 1D tensors.\n");
        exit(EXIT_FAILURE);
    }

    int size = t1->dims[0];
    Tensor *result = Tensor_create(t1->num_dims, t1->dims);
    for (int i = 0; i < size; ++i) {
        result->data[i] = t1->data[i] / t2->data[i];
    }
    return result;
}

static UNUSED Tensor *Tensor_mul_scalar(Tensor *t, double scalar) {
    assert(t && "Invalid tensor.");
    assert(t->num_dims == 1 &&
           "The tensors must have the same dimensions for the operation of "
           "product.");
    int total_elements = 1;
    for (int i = 0; i < t->num_dims; ++i) {
        total_elements *= t->dims[i];
    }

    Tensor *result = Tensor_create(t->num_dims, t->dims);
    for (int i = 0; i < total_elements; ++i) {
        result->data[i] = t->data[i] * scalar;
    }
    return result;
}

static UNUSED Tensor *Tensor_div_scalar(Tensor *t, double scalar) {
    assert(t && "Invalid tensor.");
    assert(scalar == 0 && "Division by zero.\n");
    int total_elements = 1;
    for (int i = 0; i < t->num_dims; ++i) {
        total_elements *= t->dims[i];
    }

    Tensor *result = Tensor_create(t->num_dims, t->dims);
    for (int i = 0; i < total_elements; ++i) {
        result->data[i] = t->data[i] / scalar;
    }
    return result;
}

static double UNUSED Tensor_sumElements(Tensor *t) {
    assert(t && "Invalid tensor.");
    double sum = 0;
    int total_size = 1;
    for (int i = 0; i < t->num_dims; ++i) {
        total_size *= t->dims[i];
    }
    for (int i = 0; i < total_size; ++i) {
        sum += t->data[i];
    }
    return sum;
}

//! Tensor Operation
static UNUSED Tensor *Tensor_inverse(Tensor *t) {
    assert(t->num_dims == 2);
    assert(t->dims[0] == 4 && t->dims[1] == 4);

    Mat4 mat = tensorToMat4(t);
    Mat4 inv_mat = Mat4_inverse(mat);
    return mat4ToTensor(inv_mat);
}

static double UNUSED Tensor_dot(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    assert(t1->num_dims == 1 && t2->num_dims == 1 &&
           "Dot product is only supported for 1D tensors.");
    assert(t1->dims[0] == t2->dims[0] &&
           "Tensors must have the same dimension.");

    double result = 0;
    for (int i = 0; i < t1->dims[0]; ++i) {
        result += t1->data[i] * t2->data[i];
    }
    return result;
}

static UNUSED Tensor *UNUSED Tensor_cross(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    assert(t1->num_dims == 1 && t2->num_dims == 1 &&
           "Cross product is only supported for 1D tensors.");
    assert(t1->dims[0] == 3 && t2->dims[0] == 3 &&
           "Tensors must have dimension 3.");

    int dims[] = {3};
    Tensor *result = Tensor_create(1, dims);
    result->data[0] = t1->data[1] * t2->data[2] - t1->data[2] * t2->data[1];
    result->data[1] = t1->data[2] * t2->data[0] - t1->data[0] * t2->data[2];
    result->data[2] = t1->data[0] * t2->data[1] - t1->data[1] * t2->data[0];
    return result;
}

static double Tensor_det2x2(Tensor *t) {
    return t->data[0] * t->data[3] - t->data[1] * t->data[2];
}

static double Tensor_det3x3(Tensor *t) {
    return t->data[0] * (t->data[4] * t->data[8] - t->data[5] * t->data[7]) -
           t->data[1] * (t->data[3] * t->data[8] - t->data[5] * t->data[6]) +
           t->data[2] * (t->data[3] * t->data[7] - t->data[4] * t->data[6]);
}

static double UNUSED Tensor_det(Tensor *t) {
    assert(t && "Invalid tensor.");
    assert(t->num_dims == 2 && t->dims[0] == t->dims[1] &&
           "Determinant is only supported for square matrices.");

    switch (t->dims[0]) {
    case 2:
        return Tensor_det2x2(t);
        break;
    case 3:
        return Tensor_det3x3(t);
        break;
    default:
        fprintf(stderr,
                "Determinant is only supported for 2x2 and 3x3 matrices.\n");
        exit(EXIT_FAILURE);
        break;
    }
}

static UNUSED Tensor *Tensor_inverse2x2(Tensor *t) {
    assert(t && "Invalid tensor.");
    assert(t->num_dims == 2 && t->dims[0] == 2 && t->dims[1] == 2 &&
           "Inverse is only supported for 2x2 matrices.");

    double det = Tensor_det2x2(t);
    assert(det != 0 && "Matrix is singular and cannot be inverted.");

    int dims[] = {2, 2};
    Tensor *result = Tensor_create(2, dims);
    result->data[0] = t->data[3] / det;
    result->data[1] = -t->data[1] / det;
    result->data[2] = -t->data[2] / det;
    result->data[3] = t->data[0] / det;
    return result;
}

static UNUSED Tensor *Tensor_matrixMul(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    assert(t1->num_dims == 2 && t2->num_dims == 2 &&
           "Matrix multiplication is only supported for 2D tensors.");
    assert(t1->dims[1] == t2->dims[0] &&
           "The number of columns of the first matrix must equal the number of "
           "rows of the second matrix.");

    int rows = t1->dims[0];
    int cols = t2->dims[1];
    int common_dim = t1->dims[1];
    int dims[] = {rows, cols};
    Tensor *result = Tensor_create(2, dims);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result->data[i * cols + j] = 0;
            for (int k = 0; k < common_dim; ++k) {
                result->data[i * cols + j] +=
                    t1->data[i * common_dim + k] * t2->data[k * cols + j];
            }
        }
    }
    return result;
}

static double UNUSED Tensor_length(Tensor *t) {
    assert(t && "Invalid tensor.");
    assert(t->num_dims == 1 && "Length is only supported for 1D tensors.");

    double sum = 0;
    for (int i = 0; i < t->dims[0]; ++i) {
        sum += t->data[i] * t->data[i];
    }
    return sqrt(sum);
}

static UNUSED Tensor *Tensor_normalize(Tensor *t) {
    assert(t && "Invalid tensor.");
    assert(t->num_dims == 1 &&
           "Normalization is only supported for 1D tensors.");

    int size = t->dims[0];
    double length = Tensor_length(t);
    Tensor *result = Tensor_create(1, &(t->dims[0]));
    for (int i = 0; i < size; ++i) {
        result->data[i] = t->data[i] / length;
    }
    return result;
}

static double UNUSED Tensor_trace(Tensor *t) {
    assert(t && "Invalid tensor.");
    assert(t->num_dims == 2 && t->dims[0] == t->dims[1] &&
           "Trace is only supported for square matrices.");

    double trace = 0;
    for (int i = 0; i < t->dims[0]; ++i) {
        trace += t->data[i * t->dims[0] + i];
    }
    return trace;
}

static UNUSED Tensor *Tensor_wedge(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    assert(t1->num_dims == 1 && t2->num_dims == 1 &&
           "Wedge product is only supported for 1D tensors.");

    int n = t1->dims[0];
    assert(n == t2->dims[0] && "Tensors must have the same dimension.");

    int dims[] = {n, n};
    Tensor *result = Tensor_create(2, dims);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result->data[i * n + j] =
                t1->data[i] * t2->data[j] - t1->data[j] * t2->data[i];
        }
    }
    return result;
}

static UNUSED Tensor *Tensor_extDerivate(Tensor *t) {
    assert(t && "Invalid tensor.");
    assert(t->num_dims == 1 &&
           "Exterior derivative is only supported for 1D tensors.");

    int n = t->dims[0];
    int dims[] = {n, n};
    Tensor *result = Tensor_create(2, dims);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            result->data[i * n + j] = t->data[j] - t->data[i];
        }
    }
    return result;
}

static UNUSED Tensor *Tensor_hadamardProduct(Tensor *t1, Tensor *t2) {
    assert(t1 && t2 && "Invalid tensor.");
    assert(t1->num_dims == t2->num_dims &&
           "Tensors must have the same number of dimensions.");
    for (int i = 0; i < t1->num_dims; ++i) {
        assert(t1->dims[i] == t2->dims[i] &&
               "Tensors must have the same dimensions.");
    }
    int total_size = 1;
    for (int i = 0; i < t1->num_dims; ++i) {
        total_size *= t1->dims[i];
    }
    Tensor *result = Tensor_create(t1->num_dims, t1->dims);
    for (int i = 0; i < total_size; ++i) {
        result->data[i] = t1->data[i] * t2->data[i];
    }
    return result;
}

#endif //! TENSOR_H