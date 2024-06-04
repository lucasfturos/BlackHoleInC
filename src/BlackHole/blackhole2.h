#ifndef BLACKHOLE2_H
#define BLACKHOLE2_H

#include "../Math/tensor.h"

typedef struct {
    Tensor v[4];
} Tetrad;

typedef struct {
    Tensor position;
    Tensor velocity;
} Geodesic;

static UNUSED Tensor *schwarzschildMetric(Tensor *position) {
    double rs = 1.0;
    double r = Tensor_get(position, (int[]){0, 0});
    double theta = Tensor_get(position, (int[]){0, 1});

    Tensor *m = Tensor_create(2, (int[]){4, 4});
    Tensor_set(m, (int[]){0, 0}, -(1 - rs / r));
    Tensor_set(m, (int[]){1, 1}, 1 / (1 - rs / r));
    Tensor_set(m, (int[]){2, 2}, r * r);
    Tensor_set(m, (int[]){3, 3}, r * r * sin(theta) * sin(theta));
    return m;
}

static Tetrad UNUSED calculateSchwarzschildTetrad(Tensor position) {
    double rs = 1.0;
    double r = Tensor_get(&position, (int[]){0, 0});
    double theta = Tensor_get(&position, (int[]){0, 1});

    Tetrad result;

    Tensor *et = Tensor_create(1, (int[]){4});
    Tensor_set(et, (int[]){0}, 1.0 / sqrt(1 - rs / r));
    Tensor_set(et, (int[]){1}, 0);
    Tensor_set(et, (int[]){2}, 0);
    Tensor_set(et, (int[]){3}, 0);
    result.v[0] = *et;

    Tensor *er = Tensor_create(1, (int[]){4});
    Tensor_set(er, (int[]){0}, 0);
    Tensor_set(er, (int[]){1}, sqrt(1 - rs / r));
    Tensor_set(er, (int[]){2}, 0);
    Tensor_set(er, (int[]){3}, 0);
    result.v[1] = *er;

    Tensor *etheta = Tensor_create(1, (int[]){4});
    Tensor_set(etheta, (int[]){0}, 0);
    Tensor_set(etheta, (int[]){1}, 0);
    Tensor_set(etheta, (int[]){2}, 1 / r);
    Tensor_set(etheta, (int[]){3}, 0);
    result.v[2] = *etheta;

    Tensor *ephi = Tensor_create(1, (int[]){4});
    Tensor_set(ephi, (int[]){0}, 0);
    Tensor_set(ephi, (int[]){1}, 0);
    Tensor_set(ephi, (int[]){2}, 0);
    Tensor_set(ephi, (int[]){3}, 1 / (r * sin(theta)));
    result.v[3] = *ephi;

    return result;
}

static Tensor UNUSED getRayThroughPixel(int sx, int sy, int width, int height,
                                        float fov_degrees) {
    double fov_rad = (fov_degrees / 360.f) * 2 * M_PI;
    double f_stop = (width / 2.0) / tanf(fov_rad / 2);
    Tensor *pixel_direction = Tensor_create(1, (int[]){3});
    Tensor_set(pixel_direction, (int[]){0}, (sx - width / 2.0));
    Tensor_set(pixel_direction, (int[]){1}, (sy - height / 2.0));
    Tensor_set(pixel_direction, (int[]){2}, f_stop);
    return *Tensor_normalize(pixel_direction);
}

static Geodesic UNUSED makeLightlikeGeodesic(Tensor position, Tensor direction,
                                             Tetrad tetrads) {
    Geodesic g;
    g.position = position;
    g.velocity = *Tensor_create(1, (int[]){4});

    Tensor temp1 = *Tensor_mul_scalar(&(tetrads.v[0]), -1.0);
    Tensor temp2 = *Tensor_mul_scalar(&(tetrads.v[1]), direction.data[0]);
    Tensor temp3 = *Tensor_mul_scalar(&(tetrads.v[2]), direction.data[1]);
    Tensor temp4 = *Tensor_mul_scalar(&(tetrads.v[3]), direction.data[2]);

    Tensor sum1 = *Tensor_add(&temp1, &temp2);
    Tensor sum2 = *Tensor_add(&temp3, &temp4);
    Tensor sum = *Tensor_add(&sum1, &sum2);
    g.velocity = sum;

    Tensor_free(&temp1);
    Tensor_free(&temp2);
    Tensor_free(&temp3);
    Tensor_free(&temp4);

    return g;
}

#endif //! BLACKHOLE2_H