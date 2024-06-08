#include "../src/Math/tensor.h"

void test_tensor_create() {
    int dims[2] = {3, 3};
    Tensor *t = Tensor_create(2, dims);
    assert(t != NULL);
    assert(t->num_dims == 2);
    assert(t->dims[0] == 3);
    assert(t->dims[1] == 3);
    Tensor_free(t);
    printf("test_tensor_create passed.\n");
}

void test_tensor_set_get() {
    int dims[2] = {2, 2};
    Tensor *t = Tensor_create(2, dims);
    int indices[2] = {1, 1};
    Tensor_set(t, indices, 3.5);
    double value = Tensor_get(t, indices);
    assert(value == 3.5);
    Tensor_free(t);
    printf("test_tensor_set_get passed.\n");
}

void test_tensor_add() {
    int dims[2] = {2, 2};
    Tensor *t1 = Tensor_create(2, dims);
    Tensor *t2 = Tensor_create(2, dims);

    Tensor_set(t1, (int[]){0, 0}, 1.0);
    Tensor_set(t1, (int[]){0, 1}, 2.0);
    Tensor_set(t1, (int[]){1, 0}, 3.0);
    Tensor_set(t1, (int[]){1, 1}, 4.0);

    Tensor_set(t2, (int[]){0, 0}, 5.0);
    Tensor_set(t2, (int[]){0, 1}, 6.0);
    Tensor_set(t2, (int[]){1, 0}, 7.0);
    Tensor_set(t2, (int[]){1, 1}, 8.0);

    Tensor *result = Tensor_add(t1, t2);

    assert(Tensor_get(result, (int[]){0, 0}) == 6.0);
    assert(Tensor_get(result, (int[]){0, 1}) == 8.0);
    assert(Tensor_get(result, (int[]){1, 0}) == 10.0);
    assert(Tensor_get(result, (int[]){1, 1}) == 12.0);

    Tensor_free(t1);
    Tensor_free(t2);
    Tensor_free(result);

    printf("test_tensor_add passed.\n");
}

void test_tensor_sub() {
    int dims[2] = {2, 2};
    Tensor *t1 = Tensor_create(2, dims);
    Tensor *t2 = Tensor_create(2, dims);

    Tensor_set(t1, (int[]){0, 0}, 5.0);
    Tensor_set(t1, (int[]){0, 1}, 7.0);
    Tensor_set(t1, (int[]){1, 0}, 9.0);
    Tensor_set(t1, (int[]){1, 1}, 11.0);

    Tensor_set(t2, (int[]){0, 0}, 1.0);
    Tensor_set(t2, (int[]){0, 1}, 2.0);
    Tensor_set(t2, (int[]){1, 0}, 3.0);
    Tensor_set(t2, (int[]){1, 1}, 4.0);

    Tensor *result = Tensor_sub(t1, t2);

    assert(Tensor_get(result, (int[]){0, 0}) == 4.0);
    assert(Tensor_get(result, (int[]){0, 1}) == 5.0);
    assert(Tensor_get(result, (int[]){1, 0}) == 6.0);
    assert(Tensor_get(result, (int[]){1, 1}) == 7.0);

    Tensor_free(t1);
    Tensor_free(t2);
    Tensor_free(result);

    printf("test_tensor_sub passed.\n");
}

void test_tensor_mul_scalar() {
    int dims[2] = {2, 2};
    Tensor *t = Tensor_create(2, dims);

    Tensor_set(t, (int[]){0, 0}, 1.0);
    Tensor_set(t, (int[]){0, 1}, 2.0);
    Tensor_set(t, (int[]){1, 0}, 3.0);
    Tensor_set(t, (int[]){1, 1}, 4.0);

    Tensor *result = Tensor_mul_scalar(t, 2.0);

    assert(Tensor_get(result, (int[]){0, 0}) == 2.0);
    assert(Tensor_get(result, (int[]){0, 1}) == 4.0);
    assert(Tensor_get(result, (int[]){1, 0}) == 6.0);
    assert(Tensor_get(result, (int[]){1, 1}) == 8.0);

    Tensor_free(t);
    Tensor_free(result);

    printf("test_tensor_mul_scalar passed.\n");
}

void test_tensor_div_scalar() {
    int dims[1] = {3};
    Tensor *t = Tensor_create(1, dims);

    Tensor_set(t, (int[]){0}, 2.0);
    Tensor_set(t, (int[]){1}, 4.0);
    Tensor_set(t, (int[]){2}, 6.0);

    double scalar = 2.0;
    Tensor *result = Tensor_div_scalar(t, scalar);

    assert(Tensor_get(result, (int[]){0}) == 1.0);
    assert(Tensor_get(result, (int[]){1}) == 2.0);
    assert(Tensor_get(result, (int[]){2}) == 3.0);

    Tensor_free(t);
    Tensor_free(result);

    printf("test_tensor_div_scalar passed.\n");
}

void test_tensor_sumElements() {
    int dims[2] = {2, 2};
    Tensor *t = Tensor_create(2, dims);

    Tensor_set(t, (int[]){0, 0}, 1.0);
    Tensor_set(t, (int[]){0, 1}, 2.0);
    Tensor_set(t, (int[]){1, 0}, 3.0);
    Tensor_set(t, (int[]){1, 1}, 4.0);

    double sum = Tensor_sumElements(t);
    assert(sum == 10.0);

    Tensor_free(t);

    printf("test_tensor_sumElements passed.\n");
}

void test_tensor_dot() {
    int dims[1] = {3};
    Tensor *t1 = Tensor_create(1, dims);
    Tensor *t2 = Tensor_create(1, dims);

    Tensor_set(t1, (int[]){0}, 1.0);
    Tensor_set(t1, (int[]){1}, 2.0);
    Tensor_set(t1, (int[]){2}, 3.0);

    Tensor_set(t2, (int[]){0}, 4.0);
    Tensor_set(t2, (int[]){1}, 5.0);
    Tensor_set(t2, (int[]){2}, 6.0);

    double result = Tensor_dot(t1, t2);
    assert(result == 32.0);

    Tensor_free(t1);
    Tensor_free(t2);

    printf("test_tensor_dot passed.\n");
}

void test_tensor_cross() {
    int dims[1] = {3};
    Tensor *t1 = Tensor_create(1, dims);
    Tensor *t2 = Tensor_create(1, dims);

    Tensor_set(t1, (int[]){0}, 1.0);
    Tensor_set(t1, (int[]){1}, 2.0);
    Tensor_set(t1, (int[]){2}, 3.0);

    Tensor_set(t2, (int[]){0}, 4.0);
    Tensor_set(t2, (int[]){1}, 5.0);
    Tensor_set(t2, (int[]){2}, 6.0);

    Tensor *result = Tensor_cross(t1, t2);

    assert(Tensor_get(result, (int[]){0}) == -3.0);
    assert(Tensor_get(result, (int[]){1}) == 6.0);
    assert(Tensor_get(result, (int[]){2}) == -3.0);

    Tensor_free(t1);
    Tensor_free(t2);
    Tensor_free(result);

    printf("test_tensor_cross passed.\n");
}

void test_tensor_inverse() {
    int dims[2] = {4, 4};
    Tensor *t = Tensor_create(2, dims);

    double values[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    for (int i = 0; i < 16; ++i) {
        t->data[i] = values[i];
    }

    Tensor *inv_t = Tensor_inverse(t);
    for (int i = 0; i < 16; ++i) {
        assert(t->data[i] == inv_t->data[i]);
    }

    Tensor_free(t);
    Tensor_free(inv_t);

    printf("test_tensor_inverse passed.\n");
}

void test_tensor_reshape() {
    int dims[2] = {2, 3};
    Tensor *t = Tensor_create(2, dims);

    int new_dims[2] = {3, 2};
    Tensor *reshaped = Tensor_reshape(t, 2, new_dims);

    assert(reshaped->num_dims == 2);
    assert(reshaped->dims[0] == 3);
    assert(reshaped->dims[1] == 2);

    Tensor_free(t);
    Tensor_free(reshaped);

    printf("test_tensor_reshape passed.\n");
}

void test_tensor_length() {
    int dims[1] = {3};
    Tensor *t = Tensor_create(1, dims);

    Tensor_set(t, (int[]){0}, 1.0);
    Tensor_set(t, (int[]){1}, 2.0);
    Tensor_set(t, (int[]){2}, 2.0);

    double length = Tensor_length(t);
    assert(length == sqrt(9.0));

    Tensor_free(t);

    printf("test_tensor_length passed.\n");
}

void test_tensor_trace() {
    int dims[2] = {3, 3};
    Tensor *t = Tensor_create(2, dims);

    double values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; ++i) {
        t->data[i] = values[i];
    }

    double trace = Tensor_trace(t);
    assert(trace == 15.0);

    Tensor_free(t);

    printf("test_tensor_trace passed.\n");
}

void test_tensor_det2x2() {
    int dims[2] = {2, 2};
    Tensor *t = Tensor_create(2, dims);

    Tensor_set(t, (int[]){0, 0}, 1.0);
    Tensor_set(t, (int[]){0, 1}, 2.0);
    Tensor_set(t, (int[]){1, 0}, 3.0);
    Tensor_set(t, (int[]){1, 1}, 4.0);

    double det = Tensor_det2x2(t);
    assert(det == -2.0);

    Tensor_free(t);

    printf("test_tensor_det2x2 passed.\n");
}

void test_tensor_det3x3() {
    int dims[2] = {3, 3};
    Tensor *t = Tensor_create(2, dims);

    Tensor_set(t, (int[]){0, 0}, 6.0);
    Tensor_set(t, (int[]){0, 1}, 1.0);
    Tensor_set(t, (int[]){0, 2}, 1.0);
    Tensor_set(t, (int[]){1, 0}, 4.0);
    Tensor_set(t, (int[]){1, 1}, -2.0);
    Tensor_set(t, (int[]){1, 2}, 5.0);
    Tensor_set(t, (int[]){2, 0}, 2.0);
    Tensor_set(t, (int[]){2, 1}, 8.0);
    Tensor_set(t, (int[]){2, 2}, 7.0);

    double det = Tensor_det3x3(t);
    assert(det == -306.0);

    Tensor_free(t);

    printf("test_tensor_det3x3 passed.\n");
}

void test_tensor_det() {
    int dims[2] = {3, 3};
    Tensor *t = Tensor_create(2, dims);

    Tensor_set(t, (int[]){0, 0}, 1.0);
    Tensor_set(t, (int[]){0, 1}, 2.0);
    Tensor_set(t, (int[]){0, 2}, 3.0);
    Tensor_set(t, (int[]){1, 0}, 4.0);
    Tensor_set(t, (int[]){1, 1}, 5.0);
    Tensor_set(t, (int[]){1, 2}, 6.0);
    Tensor_set(t, (int[]){2, 0}, 7.0);
    Tensor_set(t, (int[]){2, 1}, 8.0);
    Tensor_set(t, (int[]){2, 2}, 9.0);

    double det = Tensor_det(t);
    assert(det ==
           0.0); // Determinante de uma matriz 3x3 com linhas colineares é zero

    Tensor_free(t);

    printf("test_tensor_det passed.\n");
}

void test_tensor_normalize() {
    int dims[1] = {3};
    Tensor *t = Tensor_create(1, dims);

    Tensor_set(t, (int[]){0}, 1.0);
    Tensor_set(t, (int[]){1}, 2.0);
    Tensor_set(t, (int[]){2}, 2.0);

    Tensor *normalized = Tensor_normalize(t);

    assert(Tensor_get(normalized, (int[]){0}) == 1.0 / 3.0);
    assert(Tensor_get(normalized, (int[]){1}) == 2.0 / 3.0);
    assert(Tensor_get(normalized, (int[]){2}) == 2.0 / 3.0);

    Tensor_free(t);
    Tensor_free(normalized);

    printf("test_tensor_normalize passed.\n");
}

void test_tensor_mul() {
    int dims1[2] = {3, 3};
    Tensor *t1 = Tensor_create(2, dims1);
    Tensor_set(t1, (int[]){0, 0}, 1.0);
    Tensor_set(t1, (int[]){0, 1}, 2.0);
    Tensor_set(t1, (int[]){0, 2}, 3.0);
    Tensor_set(t1, (int[]){1, 0}, 4.0);
    Tensor_set(t1, (int[]){1, 1}, 5.0);
    Tensor_set(t1, (int[]){1, 2}, 6.0);
    Tensor_set(t1, (int[]){2, 0}, 7.0);
    Tensor_set(t1, (int[]){2, 1}, 8.0);
    Tensor_set(t1, (int[]){2, 2}, 9.0);

    int dims2[2] = {3, 3};
    Tensor *t2 = Tensor_create(2, dims2);
    Tensor_set(t2, (int[]){0, 0}, 9.0);
    Tensor_set(t2, (int[]){0, 1}, 8.0);
    Tensor_set(t2, (int[]){0, 2}, 7.0);
    Tensor_set(t2, (int[]){1, 0}, 6.0);
    Tensor_set(t2, (int[]){1, 1}, 5.0);
    Tensor_set(t2, (int[]){1, 2}, 4.0);
    Tensor_set(t2, (int[]){2, 0}, 3.0);
    Tensor_set(t2, (int[]){2, 1}, 2.0);
    Tensor_set(t2, (int[]){2, 2}, 1.0);

    Tensor *result = Tensor_mul(t1, t2);

    assert(Tensor_get(result, (int[]){0, 0}) == 30.0);
    assert(Tensor_get(result, (int[]){0, 1}) == 24.0);
    assert(Tensor_get(result, (int[]){0, 2}) == 18.0);
    assert(Tensor_get(result, (int[]){1, 0}) == 84.0);
    assert(Tensor_get(result, (int[]){1, 1}) == 69.0);
    assert(Tensor_get(result, (int[]){1, 2}) == 54.0);
    assert(Tensor_get(result, (int[]){2, 0}) == 138.0);
    assert(Tensor_get(result, (int[]){2, 1}) == 114.0);
    assert(Tensor_get(result, (int[]){2, 2}) == 90.0);

    Tensor_free(t1);
    Tensor_free(t2);
    Tensor_free(result);

    printf("test_tensor_mul passed.\n");
}

int run_all_tests_tensor() {
    test_tensor_create();
    test_tensor_set_get();
    test_tensor_add();
    test_tensor_sub();
    test_tensor_mul();
    test_tensor_mul_scalar();
    test_tensor_div_scalar();
    test_tensor_sumElements();
    test_tensor_dot();
    test_tensor_cross();
    test_tensor_inverse();
    test_tensor_reshape();
    test_tensor_length();
    test_tensor_trace();
    test_tensor_det2x2();
    test_tensor_det3x3();
    test_tensor_det();
    test_tensor_normalize();

    return 0;
}
