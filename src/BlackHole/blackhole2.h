#ifndef BLACKHOLE2_H
#define BLACKHOLE2_H

#include "../Math/tensor.h"

#define RS 1.0

typedef struct {
    Tensor v[4];
} Tetrad;

typedef struct {
    Tensor position;
    Tensor velocity;
} Geodesic;

static Tensor UNUSED schwarzschildMetric(Tensor *pos) {
    double r = Tensor_get(pos, (int[]){0});
    double theta = Tensor_get(pos, (int[]){1});
    assert(r > RS);

    Tensor metric = *Tensor_create(2, (int[]){4, 4});
    Tensor_set(&metric, (int[]){0, 0}, -(1 - RS / r));
    Tensor_set(&metric, (int[]){1, 1}, 1 / (1 - RS / r));
    Tensor_set(&metric, (int[]){2, 2}, r * r);
    Tensor_set(&metric, (int[]){3, 3}, r * r * sin(theta) * sin(theta));
    return metric;
}

static Tetrad UNUSED calculateSchwarzschildTetrad(Tensor pos) {
    double r = Tensor_get(&pos, (int[]){0});
    double theta = Tensor_get(&pos, (int[]){1});
    assert(r > RS);

    Tetrad result;
    // Vetor normalizado do tempo
    Tensor *et = Tensor_create(1, (int[]){4});
    Tensor_set(et, (int[]){0}, 1.0 / sqrt(1 - RS / r));
    Tensor_set(et, (int[]){1}, 0);
    Tensor_set(et, (int[]){2}, 0);
    Tensor_set(et, (int[]){3}, 0);
    result.v[0] = *et;
    // Vetor normalizado do radial
    Tensor *er = Tensor_create(1, (int[]){4});
    Tensor_set(er, (int[]){0}, 0);
    Tensor_set(er, (int[]){1}, sqrt(1 - RS / r));
    Tensor_set(er, (int[]){2}, 0);
    Tensor_set(er, (int[]){3}, 0);
    result.v[1] = *er;
    // Vetor normalizado da coordenada theta
    Tensor *etheta = Tensor_create(1, (int[]){4});
    Tensor_set(etheta, (int[]){0}, 0);
    Tensor_set(etheta, (int[]){1}, 0);
    Tensor_set(etheta, (int[]){2}, 1 / r);
    Tensor_set(etheta, (int[]){3}, 0);
    result.v[2] = *etheta;
    // Vetor normalizado da coordenada phi
    Tensor *ephi = Tensor_create(1, (int[]){4});
    Tensor_set(ephi, (int[]){0}, 0);
    Tensor_set(ephi, (int[]){1}, 0);
    Tensor_set(ephi, (int[]){2}, 0);
    Tensor_set(ephi, (int[]){3}, 1 / (r * sin(theta)));
    result.v[3] = *ephi;
    return result;
}

static Tensor UNUSED getRayThroughPixel(int sx, int sy, int width, int height,
                                        float fovDegrees) {
    double fovRad = (fovDegrees / 360.f) * 2 * M_PI;
    double fovStop = (width / 2.0) / tan(fovRad / 2);

    Tensor *pixelDir = Tensor_create(1, (int[]){3});
    Tensor_set(pixelDir, (int[]){0}, (sx - width / 2.0) / width);
    Tensor_set(pixelDir, (int[]){1}, (sy - height / 2.0) / width);
    Tensor_set(pixelDir, (int[]){2}, -fovStop / width);

    Tensor result = *Tensor_normalize(pixelDir);
    Tensor_free(pixelDir);
    return result;
}

static Geodesic UNUSED makeLightlikeGeodesic(Tensor pos, Tensor dir,
                                             Tetrad tetrad) {
    Tensor *normalizeDir = Tensor_normalize(&dir);

    Tensor *t_v = Tensor_mul_scalar(&tetrad.v[0], -1.0);
    Tensor *x_v =
        Tensor_mul_scalar(&tetrad.v[1], Tensor_get(normalizeDir, (int[]){0}));
    Tensor *y_v =
        Tensor_mul_scalar(&tetrad.v[2], Tensor_get(normalizeDir, (int[]){1}));
    Tensor *z_v =
        Tensor_mul_scalar(&tetrad.v[3], Tensor_get(normalizeDir, (int[]){2}));

    Tensor *resultV = Tensor_add(t_v, x_v);
    Tensor_add(resultV, y_v);
    Tensor_add(resultV, z_v);

    Geodesic result;
    result.position = pos;
    result.velocity = *resultV;
    return result;
}

static Tensor UNUSED partialDerivative(Tensor (*func)(Tensor *), Tensor *pos,
                                       int dir) {
    Tensor p_up = *Tensor_copy(pos);
    Tensor p_lo = *Tensor_copy(pos);
    Tensor_set(&p_up, (int[]){dir}, Tensor_get(pos, (int[]){dir}) + EPS);
    Tensor_set(&p_lo, (int[]){dir}, Tensor_get(pos, (int[]){dir}) - EPS);

    Tensor up = (*func)(&p_up);
    Tensor lo = (*func)(&p_lo);
    Tensor diff = *Tensor_sub(&up, &lo);
    return *Tensor_mul_scalar(&diff, 1 / (2.0 * EPS));
}

static UNUSED Tensor *calculateChristoff2(Tensor *position,
                                          Tensor (*get_metric)(Tensor *)) {
    Tensor metric = get_metric(position);
    Tensor *metric_inverse = Tensor_inverse(&metric);

    int dims_diff[] = {4, 4, 4};
    Tensor *metric_diff = Tensor_create(3, dims_diff);
    for (int i = 0; i < 4; ++i) {
        Tensor differentiated = partialDerivative(get_metric, position, i);
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                Tensor_set(metric_diff, (int[]){i, j, k},
                           Tensor_get(&differentiated, (int[]){j, k}));
            }
        }
        Tensor_free(&differentiated);
    }
    int dims_gamma[] = {4, 4, 4};
    Tensor *Gamma = Tensor_create(3, dims_gamma);
    for (int mu = 0; mu < 4; mu++) {
        for (int alpha = 0; alpha < 4; ++alpha) {
            for (int beta = 0; beta < 4; ++beta) {
                double sum = 0;
                for (int sigma = 0; sigma < 4; sigma++) {
                    double term1 =
                        Tensor_get(metric_diff, (int[]){beta, sigma, alpha});
                    double term2 =
                        Tensor_get(metric_diff, (int[]){alpha, sigma, beta});
                    double term3 =
                        Tensor_get(metric_diff, (int[]){sigma, alpha, beta});
                    double inverse =
                        Tensor_get(metric_inverse, (int[]){mu, sigma});
                    sum += 0.5 * inverse * (term1 + term2 - term3);
                }
                Tensor_set(Gamma, (int[]){mu, alpha, beta}, sum);
            }
        }
    }
    return Gamma;
}

static void UNUSED test() {
    Tensor position = *Tensor_create(1, (int[]){2});
    Tensor_set(&position, (int[]){0}, 2.0);
    Tensor_set(&position, (int[]){1}, M_PI / 4);

    Tensor metric = schwarzschildMetric(&position);
    printf("Métrica de Schwarzschild:\n");
    Tensor_print(&metric);

    Tensor *inv_metric = Tensor_inverse(&metric);
    if (inv_metric) {
        printf("Inversa da métrica de Schwarzschild:\n");
        Tensor_print(inv_metric);
        Tensor_free(inv_metric);
    }
}

#endif // BLACKHOLE2_H
