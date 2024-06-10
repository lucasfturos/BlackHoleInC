#include "../../src/Math/Tensor/tetrad.h"

void test_calculateSchwarzschildTetrad() {
    double halfPI = M_PI / 2;
    Tensor pos = *Tensor_create(1, (int[]){4});
    Tensor_set(&pos, (int[]){0}, 0);
    Tensor_set(&pos, (int[]){1}, 3.0);
    Tensor_set(&pos, (int[]){2}, halfPI);
    Tensor_set(&pos, (int[]){3}, 0);

    Tetrad result = calculateSchwarzschildTetrad(pos);

    // Verifica os valores do vetor normalizado do tempo
    assert(fabs(Tensor_get(&result.v[0], (int[]){0}) -
                1.0 / sqrt(1 - RS / 3.0)) < 1e-6);
    assert(Tensor_get(&result.v[0], (int[]){1}) == 0);
    assert(Tensor_get(&result.v[0], (int[]){2}) == 0);
    assert(Tensor_get(&result.v[0], (int[]){3}) == 0);

    // Verifica os valores do vetor normalizado radial
    assert(Tensor_get(&result.v[1], (int[]){0}) == 0);
    assert(fabs(Tensor_get(&result.v[1], (int[]){1}) - sqrt(1 - RS / 3.0)) <
           1e-6);
    assert(Tensor_get(&result.v[1], (int[]){2}) == 0);
    assert(Tensor_get(&result.v[1], (int[]){3}) == 0);

    // Verifica os valores do vetor normalizado da coordenada theta
    assert(Tensor_get(&result.v[2], (int[]){0}) == 0);
    assert(Tensor_get(&result.v[2], (int[]){1}) == 0);
    assert(fabs(Tensor_get(&result.v[2], (int[]){2}) - 1 / 3.0) < 1e-6);
    assert(Tensor_get(&result.v[2], (int[]){3}) == 0);

    // Verifica os valores do vetor normalizado da coordenada phi
    assert(Tensor_get(&result.v[3], (int[]){0}) == 0);
    assert(Tensor_get(&result.v[3], (int[]){1}) == 0);
    assert(Tensor_get(&result.v[3], (int[]){2}) == 0);
    assert(fabs(Tensor_get(&result.v[3], (int[]){3}) -
                1 / (3.0 * sin(halfPI))) < 1e-6);

    printf("test_calculateSchwarzschildTetrad passed.\n");
}

int run_all_tests_tetrad() {
    test_calculateSchwarzschildTetrad();
    printf("All Tetrads tests passed.\n");

    return 0;
}
