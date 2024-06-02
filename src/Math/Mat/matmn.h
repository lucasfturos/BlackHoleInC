#ifndef MATMN_H
#define MATMN_H

#include "../common.h"

typedef struct {
    int rows, cols;
    double *data;
} MatMN;

//! Util
static MatMN MatMN_create(int rows, int cols) {
    return (MatMN){
        .rows = rows,
        .cols = cols,
        .data = (double *)malloc(rows * cols * sizeof(double)),
    };
}

static void UNUSED MatMN_free(MatMN *m) {
    free(m->data);
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}

static void UNUSED MatMN_print(MatMN m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            printf("%f ", m.data[i * m.cols + j]);
        }
        printf("\n");
    }
}

static MatMN UNUSED MatMN_setData(int rows, int cols, double *data) {
    MatMN m = MatMN_create(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        m.data[i] = data[i];
    }
    return m;
}

static void UNUSED MatMN_setValue(MatMN *m, int row, int col, double value) {
    if (row >= 0 && row < m->rows && col >= 0 && col < m->cols) {
        m->data[row * m->cols + col] = value;
    }
}

static double UNUSED MatMN_getValue(const MatMN *m, int row, int col) {
    if (row >= 0 && row < m->rows && col >= 0 && col < m->cols) {
        return m->data[row * m->cols + col];
    }
    return 0.0;
}

//! Operations
static MatMN UNUSED MatMN_add(const MatMN *m1, const MatMN *m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        return MatMN_create(0, 0);
    }
    MatMN result = MatMN_create(m1->rows, m1->cols);
    for (int i = 0; i < m1->rows * m1->cols; ++i) {
        result.data[i] = m1->data[i] + m2->data[i];
    }
    return result;
}

static MatMN UNUSED MatMN_sub(const MatMN *m1, const MatMN *m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        return MatMN_create(0, 0);
    }
    MatMN result = MatMN_create(m1->rows, m1->cols);
    for (int i = 0; i < m1->rows * m1->cols; ++i) {
        result.data[i] = m1->data[i] - m2->data[i];
    }
    return result;
}

static MatMN UNUSED MatMN_mul_scalar(const MatMN *m, double scalar) {
    MatMN result = MatMN_create(m->rows, m->cols);
    for (int i = 0; i < m->rows * m->cols; ++i) {
        result.data[i] = m->data[i] * scalar;
    }
    return result;
}

static MatMN UNUSED MatMN_div_scalar(const MatMN *m, double scalar) {
    MatMN result = MatMN_create(m->rows, m->cols);
    for (int i = 0; i < m->rows * m->cols; ++i) {
        result.data[i] = m->data[i] / scalar;
    }
    return result;
}

static MatMN UNUSED MatMN_transpose(const MatMN *m) {
    MatMN result = MatMN_create(m->cols, m->rows);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            result.data[j * m->rows + i] = m->data[i * m->cols + j];
        }
    }
    return result;
}

#endif //! MATMN_H