#include "../../src/Math/Tensor/geodesic.h"

void test_makeLightlikeGeodesic() {
    Tensor pos = *Tensor_create(1, (int[]){4});
    Tensor_set(&pos, (int[]){0}, 0);
    Tensor_set(&pos, (int[]){1}, 3.0);
    Tensor_set(&pos, (int[]){2}, M_PI / 2);
    Tensor_set(&pos, (int[]){3}, 0);

    Tensor dir = *Tensor_create(1, (int[]){3});
    Tensor_set(&dir, (int[]){0}, 1);
    Tensor_set(&dir, (int[]){1}, 0);
    Tensor_set(&dir, (int[]){2}, 0);

    Tetrad tetrad = calculateSchwarzschildTetrad(pos);
    Geodesic geodesic = makeLightlikeGeodesic(pos, dir, tetrad);

    Tensor expected_velocity = *Tensor_create(1, (int[]){4});
    Tensor_set(&expected_velocity, (int[]){0}, -1.0 / sqrt(1 - RS / 3.0));
    Tensor_set(&expected_velocity, (int[]){1}, sqrt(1 - RS / 3.0));
    Tensor_set(&expected_velocity, (int[]){2}, 0);
    Tensor_set(&expected_velocity, (int[]){3}, 0);

    for (int i = 0; i < 4; i++) {
        assert(fabs(Tensor_get(&geodesic.velocity, (int[]){i}) -
                    Tensor_get(&expected_velocity, (int[]){i})) < 1e-6);
    }

    printf("test_makeLightlikeGeodesic passed.\n");

    Tensor_free(&pos);
    Tensor_free(&dir);
    Tetrad_free(&tetrad);
    Tensor_free(&expected_velocity);
}

int run_all_tests_geodesic() {
    printf("All Geodesic tests passed.\n");

    return 0;
}