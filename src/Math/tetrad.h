#ifndef TETRAD_H
#define TETRAD_H

#include "tensor.h"

typedef struct {
    Tensor v[4];
} Tetrad;

static Tetrad calculateSchwarzschildTetrad(Tensor pos) {
    double r = Tensor_get(&pos, (int[]){1});
    double theta = Tensor_get(&pos, (int[]){2});
    assert(r > RS);

    Tetrad result;
    // Vetor normalizado do tempo
    Tensor *et = Tensor_create(1, (int[]){4});
    assert(et && "Failed to allocate memory for t vector.");
    Tensor_set(et, (int[]){0}, 1.0 / sqrt(1 - RS / r));
    Tensor_set(et, (int[]){1}, 0);
    Tensor_set(et, (int[]){2}, 0);
    Tensor_set(et, (int[]){3}, 0);
    result.v[0] = *et;
    Tensor_free(et);
    // Vetor normalizado do radial
    Tensor *er = Tensor_create(1, (int[]){4});
    assert(er && "Failed to allocate memory for t vector.");
    Tensor_set(er, (int[]){0}, 0);
    Tensor_set(er, (int[]){1}, sqrt(1 - RS / r));
    Tensor_set(er, (int[]){2}, 0);
    Tensor_set(er, (int[]){3}, 0);
    result.v[1] = *er;
    Tensor_free(er);
    // Vetor normalizado da coordenada theta
    Tensor *etheta = Tensor_create(1, (int[]){4});
    assert(etheta && "Failed to allocate memory for t vector.");
    Tensor_set(etheta, (int[]){0}, 0);
    Tensor_set(etheta, (int[]){1}, 0);
    Tensor_set(etheta, (int[]){2}, 1 / r);
    Tensor_set(etheta, (int[]){3}, 0);
    result.v[2] = *etheta;
    Tensor_free(etheta);
    // Vetor normalizado da coordenada phi
    Tensor *ephi = Tensor_create(1, (int[]){4});
    assert(ephi && "Failed to allocate memory for t vector.");
    Tensor_set(ephi, (int[]){0}, 0);
    Tensor_set(ephi, (int[]){1}, 0);
    Tensor_set(ephi, (int[]){2}, 0);
    Tensor_set(ephi, (int[]){3}, 1 / (r * sin(theta)));
    result.v[3] = *ephi;
    Tensor_free(ephi);
    return result;
}

#endif //! TETRAD_H