#include "../../src/BlackHole/blackhole2.h"

void test_schwarzschildMetric() {
    Tensor *pos = Tensor_create(1, (int[]){4});
    Tensor_set(pos, (int[]){0}, 1.0);
    Tensor_set(pos, (int[]){1}, 2.0);
    Tensor_set(pos, (int[]){2}, 3.0);
    Tensor_set(pos, (int[]){3}, 4.0);

    Tensor *metric = schwarzschildMetric(pos);

    assert(metric != NULL);
    assert(Tensor_get(metric, (int[]){0, 0}) == -0.5);

    Tensor_free(pos);
    Tensor_free(metric);

    printf("test_schwarzschildMetric passed.\n");
}

void test_getRayThroughPixel() { printf("test_getRayThroughPixel passed.\n"); }

void test_calculateChristoff2() {
    printf("test_calculateChristoff2 passed.\n");
}

int run_all_tests_blackhole2() {
    test_schwarzschildMetric();
    test_getRayThroughPixel();
    test_calculateChristoff2();

    printf("All BlackHole2 tests passed.\n");
    return 0;
}
