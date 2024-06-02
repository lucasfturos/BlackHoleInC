#ifndef TENSOR_H
#define TENSOR_H

#include "common.h"
#include <string.h>

#define MAX_DIM 4

typedef struct {
    int dims[MAX_DIM];
    int num_dims;
    double *data;
} Tensor;

//! Util
static Tensor *UNUSED Tensor_create(int num_dims, int *dims) {
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

//! Operation
static void UNUSED Tensor_add(Tensor *t1, Tensor *t2, Tensor *out) {
    assert(t1 && t2 && out && "Invalid tensor.");
    int total_size = 1;
    for (int i = 0; i < t1->num_dims; ++i) {
        total_size *= t1->dims[i];
    }
    for (int i = 0; i < total_size; ++i) {
        out->data[i] = t1->data[i] + t2->data[i];
    }
}

static void UNUSED Tensor_sub(Tensor *t1, Tensor *t2, Tensor *out) {
    assert(t1 && t2 && out && "Invalid tensor.");
    int total_size = 1;
    for (int i = 0; i < t1->num_dims; ++i) {
        total_size *= t1->dims[i];
    }
    for (int i = 0; i < total_size; ++i) {
        out->data[i] = t1->data[i] - t2->data[i];
    }
}

static void UNUSED Tensor_product(Tensor *t1, Tensor *t2, Tensor *out) {
    assert(t1 && t2 && out && "Invalid tensor.");
    for (int i = 0; i < t1->num_dims; ++i) {
        assert(t1->dims[i] == t2->dims[i] &&
               "The tensors must have the same dimensions for the operation of "
               "product.");
    }
    if (t1->num_dims != 1 || t2->num_dims != 1) {
        fprintf(stderr, "Product is only supported for vectors (tensors "
                        "one-dimensional).\n");
        exit(EXIT_FAILURE);
    }
    int rows = t1->dims[0];
    int cols = t2->dims[0];
    int total_size = rows * cols;
    out->num_dims = 2;
    out->dims[0] = rows;
    out->dims[1] = cols;
    out->data = (double *)malloc(total_size * sizeof(double));
    assert(out->data &&
           "Failed to allocate memory for the output tensor data.");

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            out->data[i * cols + j] = t1->data[i] * t2->data[j];
        }
    }
}

static void UNUSED Tensor_div(Tensor *t1, Tensor *t2, Tensor *out) {
    assert(t1 && t2 && out && "Invalid tensor.");
    for (int i = 0; i < t1->num_dims; ++i) {
        assert(t1->dims[i] == t2->dims[i] &&
               "The tensors must have the same dimensions for the operation of "
               "division.");
    }
    if (t1->num_dims != 1 || t2->num_dims != 1) {
        fprintf(stderr, "Division is only supported for vectors (tensors)"
                        "one-dimensional).\n");
        exit(EXIT_FAILURE);
    }

    int size = t1->dims[0];
    out->num_dims = 1;
    out->dims[0] = size;
    out->data = (double *)malloc(size * sizeof(double));
    assert(out->data &&
           "Failed to allocate memory for the output tensor data.");

    for (int i = 0; i < size; ++i) {
        out->data[i] = t1->data[i] / t2->data[i];
    }
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

#endif //! TENSOR_H