#ifndef TETRAD_H
#define TETRAD_H

#include "tensor.h"

typedef struct {
    Tensor v[4];
} Tetrad;

static Tetrad Tetrad_create() {
    Tetrad result;
    for (int i = 0; i < 4; i++) {
        result.v[i] = *Tensor_create(1, (int[]){4});
    }
    return result;
}

static inline void Tetrad_free(Tetrad *tetrad) {
    for (int i = 0; i < 4; i++) {
        Tensor_free(&tetrad->v[i]);
    }
}

static Tetrad calculateSchwarzschildTetrad(Tensor pos) {
    double r = pos.data[1];
    double theta = pos.data[2];
    assert(r > RS);

    Tetrad result = Tetrad_create();
    // Vetor normalizado do tempo
    Tensor_set(&result.v[0], (int[]){0}, 1.0 / sqrt(1.0 - RS / r));
    Tensor_set(&result.v[0], (int[]){1}, 0);
    Tensor_set(&result.v[0], (int[]){2}, 0);
    Tensor_set(&result.v[0], (int[]){3}, 0);

    // Vetor normalizado do radial
    Tensor_set(&result.v[1], (int[]){0}, 0);
    Tensor_set(&result.v[1], (int[]){1}, sqrt(1.0 - RS / r));
    Tensor_set(&result.v[1], (int[]){2}, 0);
    Tensor_set(&result.v[1], (int[]){3}, 0);

    // Vetor normalizado da coordenada theta
    Tensor_set(&result.v[2], (int[]){0}, 0);
    Tensor_set(&result.v[2], (int[]){1}, 0);
    Tensor_set(&result.v[2], (int[]){2}, 1.0 / r);
    Tensor_set(&result.v[2], (int[]){3}, 0);

    // Vetor normalizado da coordenada phi
    Tensor_set(&result.v[3], (int[]){0}, 0);
    Tensor_set(&result.v[3], (int[]){1}, 0);
    Tensor_set(&result.v[3], (int[]){2}, 0);
    Tensor_set(&result.v[3], (int[]){3}, 1.0 / (r * sin(theta)));

    return result;
}

#endif //! TETRAD_H