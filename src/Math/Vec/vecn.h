#ifndef VECN_H
#define VECN_H

#include "../common.h"

typedef struct {
    int size;
    double *data;
} VecN;

//! Util
static VecN VecN_create(int size) {
    VecN v = {.size = size, .data = (double *)malloc(size * sizeof(double))};
    assert(v.data != NULL && "Error allocating memory for vector.");
    return v;
}

static void UNUSED VecN_free(VecN *v) {
    if (v->data) {
        free(v->data);
        v->data = NULL;
    }
    v->size = 0;
}

static void UNUSED VecN_print(VecN *v) {
    putchar('(');
    for (int i = 0; i < v->size; ++i) {
        printf("%.1f, ", v->data[i]);
    }
    printf("\b\b)\n");
}

static VecN UNUSED VecN_setData(int size, double *data) {
    VecN v = VecN_create(size);
    for (int i = 0; i < size; ++i) {
        v.data[i] = data[i];
    }
    return v;
}

static void UNUSED VecN_setValue(VecN *v, int index, double value) {
    assert(index >= 0 && index < v->size && "Index out of bounds.");
    v->data[index] = value;
}

static double UNUSED VecN_getValue(VecN *v, int index) {
    assert(index >= 0 && index < v->size && "Index out of bounds.");
    return v->data[index];
}

// Operations
static VecN UNUSED VecN_add(VecN *u, VecN *v) {
    assert(u->size == v->size && "Vectors must be of the same size.");
    VecN result = VecN_create(u->size);
    for (int i = 0; i < u->size; ++i) {
        result.data[i] = u->data[i] + v->data[i];
    }
    return result;
}

static VecN UNUSED VecN_sub(VecN *u, VecN *v) {
    assert(u->size == v->size && "Vectors must be of the same size.");
    VecN result = VecN_create(u->size);
    for (int i = 0; i < u->size; ++i) {
        result.data[i] = u->data[i] - v->data[i];
    }
    return result;
}

static VecN UNUSED VecN_mul(VecN *u, VecN *v) {
    assert(u->size == v->size && "Vectors must be of the same size.");
    VecN result = VecN_create(u->size);
    for (int i = 0; i < u->size; ++i) {
        result.data[i] = u->data[i] * v->data[i];
    }
    return result;
}

static VecN UNUSED VecN_mul_scalar(VecN *v, double scalar) {
    VecN result = VecN_create(v->size);
    for (int i = 0; i < v->size; ++i) {
        result.data[i] = v->data[i] * scalar;
    }
    return result;
}

static VecN UNUSED VecN_div_scalar(VecN *v, double scalar) {
    assert(scalar != 0.0 && "Scalar division by zero.");
    VecN result = VecN_create(v->size);
    for (int i = 0; i < v->size; ++i) {
        result.data[i] = v->data[i] / scalar;
    }
    return result;
}

static VecN UNUSED VecN_clamp(VecN *v, double min, double max) {
    VecN result = VecN_create(v->size);
    for (int i = 0; i < v->size; ++i) {
        result.data[i] = clamp(v->data[i], min, max);
    }
    return result;
}

static VecN UNUSED VecN_mix(VecN *u, VecN *v, double t) {
    assert(u->size == v->size && "Vectors must be of the same size.");
    VecN result = VecN_create(u->size);
    for (int i = 0; i < u->size; ++i) {
        result.data[i] = mix(u->data[i], v->data[i], t);
    }
    return result;
}

static VecN UNUSED VecN_fract(VecN *v) {
    VecN result = VecN_create(v->size);
    for (int i = 0; i < v->size; ++i) {
        result.data[i] = fract(v->data[i]);
    }
    return result;
}

static VecN UNUSED VecN_floor(VecN *v) {
    VecN result = VecN_create(v->size);
    for (int i = 0; i < v->size; ++i) {
        result.data[i] = floor(v->data[i]);
    }
    return result;
}

// VecN Operations
static double UNUSED VecN_dot(VecN *u, VecN *v) {
    assert(u->size == v->size && "Vectors must be of the same size.");
    double dot = 0.0;
    for (int i = 0; i < u->size; ++i) {
        dot += u->data[i] * v->data[i];
    }
    return dot;
}

static double UNUSED VecN_dotp(VecN *v) { return VecN_dot(v, v); }

static double UNUSED VecN_length(VecN *v) { return sqrt(VecN_dotp(v)); }

static VecN UNUSED VecN_normalize(VecN *v) {
    double len = VecN_length(v);
    assert(len != 0.0 && "Cannot normalize a zero-length vector.");
    return VecN_div_scalar(v, len);
}

static VecN UNUSED VecN_reflect(VecN *v, VecN *n) {
    assert(v->size == n->size && "Vectors must be of the same size.");
    VecN mulScalar = VecN_mul_scalar(n, 2.0 * VecN_dot(v, n));
    return VecN_sub(v, &mulScalar);
}

//! Random
static VecN UNUSED VecN_random(int size) {
    VecN result = VecN_create(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = random_double();
    }
    return result;
}

static VecN UNUSED VecN_random_range(int size, double min, double max) {
    VecN result = VecN_create(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = min + (max - min) * random_double();
    }
    return result;
}

#endif //! VECN_H