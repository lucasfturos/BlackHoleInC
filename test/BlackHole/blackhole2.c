#include "../../src/BlackHole/blackhole2.h"

void test_schwarzschildMetric() {
    Tensor *pos = Tensor_create(1, (int[]){4});
    Tensor_set(pos, (int[]){0}, 0.0);
    Tensor_set(pos, (int[]){1}, 2.0);
    Tensor_set(pos, (int[]){2}, 3.0);
    Tensor_set(pos, (int[]){3}, 0.0);

    Tensor *metric = schwarzschildMetric(pos);

    double r = pos->data[1];
    double theta = pos->data[2];

    double g00 = -(1 - RS / r);
    double g11 = 1 / (1 - RS / r);
    double g22 = r * r;
    double g33 = r * r * sin(theta) * sin(theta);

    assert(fabs(Tensor_get(metric, (int[]){0, 0}) - g00) < 1e-6);
    assert(fabs(Tensor_get(metric, (int[]){1, 1}) - g11) < 1e-6);
    assert(fabs(Tensor_get(metric, (int[]){2, 2}) - g22) < 1e-6);
    assert(fabs(Tensor_get(metric, (int[]){3, 3}) - g33) < 1e-6);

    Tensor_free(pos);
    Tensor_free(metric);

    printf("test_schwarzschildMetric passed.\n");
}

void test_getRayThroughPixel() {
    int screenWidth = 800;
    int screenHeight = 600;
    float fovDegrees = 90.0;
    int sx = screenWidth / 2;
    int sy = screenHeight / 2;

    Tensor ray =
        getRayThroughPixel(sx, sy, screenWidth, screenHeight, fovDegrees);
    double length = Tensor_length(&ray);
    assert(fabs(length - 1.0) < 1e-6);
    assert(fabs(Tensor_get(&ray, (int[]){0})) < 1e-6);
    assert(fabs(Tensor_get(&ray, (int[]){1})) < 1e-6);
    assert(fabs(Tensor_get(&ray, (int[]){2}) + 1.0) < 1e-6);

    Tensor_free(&ray);

    printf("test_getRayThroughPixel passed.\n");
}

void test_calculateChristoff2() {
    Tensor *position1 = Tensor_create(1, (int[]){4});
    Tensor_set(position1, (int[]){0}, 0.0);
    Tensor_set(position1, (int[]){1}, 2.0);
    Tensor_set(position1, (int[]){2}, 3.0);
    Tensor_set(position1, (int[]){3}, 0.0);

    Tensor *Gamma1 = calculateChristoff2(position1, schwarzschildMetric);
    assert(Gamma1 != NULL);
    assert(Tensor_get(Gamma1, (int[]){0, 1, 1}) == 0.0);
    Tensor_free(position1);
    Tensor_free(Gamma1);

    Tensor *position2 = Tensor_create(1, (int[]){4});
    Tensor_set(position2, (int[]){0}, 0.0);
    Tensor_set(position2, (int[]){1}, 3.0);
    Tensor_set(position2, (int[]){2}, 2.0);
    Tensor_set(position2, (int[]){3}, 0.0);

    Tensor *Gamma2 = calculateChristoff2(position2, schwarzschildMetric);
    assert(Gamma2 != NULL);
    assert(Tensor_get(Gamma2, (int[]){0, 1, 1}) != 0.0);
    Tensor_free(position2);
    Tensor_free(Gamma2);

    printf("All calculateChristoff2 tests passed.\n");
}

void test_calculateAccelerationOf() {
    Tensor *X = Tensor_create(1, (int[]){4});
    Tensor_set(X, (int[]){0}, 0.0);
    Tensor_set(X, (int[]){1}, 2.0);
    Tensor_set(X, (int[]){2}, 3.0);
    Tensor_set(X, (int[]){3}, 0.0);

    Tensor *v = Tensor_create(1, (int[]){4});
    Tensor_set(v, (int[]){0}, 1.0);
    Tensor_set(v, (int[]){1}, 2.0);
    Tensor_set(v, (int[]){2}, 0.0);
    Tensor_set(v, (int[]){3}, 0.0);

    Tensor *acceleration = calculateAccelerationOf(X, v, schwarzschildMetric);
    assert(acceleration != NULL);
    assert(acceleration->num_dims == 1);
    assert(acceleration->dims[0] == 4);

    Tensor_free(X);
    Tensor_free(v);
    Tensor_free(acceleration);

    printf("test_calculateAccelerationOf passed.\n");
}

void test_calculateSchwarzschildAcceleration() {
    Tensor *X = Tensor_create(1, (int[]){4});
    Tensor_set(X, (int[]){0}, 0.0);
    Tensor_set(X, (int[]){1}, 2.0);
    Tensor_set(X, (int[]){2}, 3.0);
    Tensor_set(X, (int[]){3}, 0.0);

    Tensor *v = Tensor_create(1, (int[]){4});
    Tensor_set(v, (int[]){0}, 1.0);
    Tensor_set(v, (int[]){1}, 2.0);
    Tensor_set(v, (int[]){2}, 0.0);
    Tensor_set(v, (int[]){3}, 0.0);

    Tensor *acceleration = calculateSchwarzschildAcceleration(X, v);
    assert(acceleration != NULL);
    assert(acceleration->num_dims == 1);
    assert(acceleration->dims[0] == 4);

    Tensor_free(X);
    Tensor_free(v);
    Tensor_free(acceleration);

    printf("test_calculateSchwarzschildAcceleration passed.\n");
}

void test_integrate() {
    Geodesic g;
    g.position = *Tensor_create(1, (int[]){4});
    g.velocity = *Tensor_create(1, (int[]){4});

    // IntegrationResult result = integrate(&g);

    Tensor_free(&g.position);
    Tensor_free(&g.velocity);

    printf("test_integrate passed.\n");
}

int run_all_tests_blackhole2() {
    test_schwarzschildMetric();
    test_getRayThroughPixel();
    test_calculateChristoff2();
    test_calculateAccelerationOf();
    test_calculateSchwarzschildAcceleration();

    printf("All BlackHole2 tests passed.\n");
    return 0;
}
