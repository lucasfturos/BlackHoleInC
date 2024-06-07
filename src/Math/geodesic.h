#ifndef GEODESIC_H
#define GEODESIC_H

#include "../Math/tetrad.h"

typedef struct {
    Tensor position;
    Tensor velocity;
} Geodesic;

static Geodesic UNUSED makeLightlikeGeodesic(Tensor pos, Tensor dir,
                                             Tetrad tetrad) {
    assert(dir.data && "Invalid direction tensor.");
    Tensor *normalizeDir = Tensor_normalize(&dir);
    assert(normalizeDir && "Failed to normalize direction tensor.");

    Tensor *t_v = Tensor_mul_scalar(&tetrad.v[0], -1.0);
    Tensor *x_v =
        Tensor_mul_scalar(&tetrad.v[1], Tensor_get(normalizeDir, (int[]){0}));
    Tensor *y_v =
        Tensor_mul_scalar(&tetrad.v[2], Tensor_get(normalizeDir, (int[]){1}));
    Tensor *z_v =
        Tensor_mul_scalar(&tetrad.v[3], Tensor_get(normalizeDir, (int[]){2}));
    Tensor *resultV = Tensor_add(t_v, x_v);
    Tensor_add_inplace(resultV, y_v);
    Tensor_add_inplace(resultV, z_v);

    Tensor_free(normalizeDir);
    Tensor_free(t_v);
    Tensor_free(x_v);
    Tensor_free(y_v);
    Tensor_free(z_v);

    Geodesic result;
    result.position = pos;
    result.velocity = *resultV;

    Tensor_free(resultV);

    return result;
}

#endif //! GEODESIC_H