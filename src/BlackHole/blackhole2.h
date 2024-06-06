#ifndef BLACKHOLE2_H
#define BLACKHOLE2_H

#include "../Math/color.h"
#include "../Math/tensor.h"
#include <SDL2/SDL_surface.h>

#define RS 0.5
#define dt 0.3

typedef struct {
    Tensor v[4];
} Tetrad;

typedef struct {
    Tensor position;
    Tensor velocity;
} Geodesic;

enum HitType {
    ESCAPED,
    EVENT_HORIZON,
    UNFINISHED,
};

typedef struct {
    enum HitType type;
} IntegrationResult;

static Tensor UNUSED *schwarzschildMetric(Tensor *pos) {
    assert(pos && "Invalid position tensor.");

    double r = Tensor_get(pos, (int[]){1});
    double theta = Tensor_get(pos, (int[]){2});
    assert(r > RS);

    Tensor *metric = Tensor_create(2, (int[]){4, 4});
    assert(metric && "Failed to allocate memory for metric tensor.");

    Tensor_set(metric, (int[]){0, 0}, -(1 - RS / r));
    Tensor_set(metric, (int[]){1, 1}, 1 / (1 - RS / r));
    Tensor_set(metric, (int[]){2, 2}, r * r);
    Tensor_set(metric, (int[]){3, 3}, r * r * sin(theta) * sin(theta));
    return metric;
}

static Tetrad UNUSED calculateSchwarzschildTetrad(Tensor pos) {
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
    // Vetor normalizado do radial
    Tensor *er = Tensor_create(1, (int[]){4});
    assert(er && "Failed to allocate memory for t vector.");
    Tensor_set(er, (int[]){0}, 0);
    Tensor_set(er, (int[]){1}, sqrt(1 - RS / r));
    Tensor_set(er, (int[]){2}, 0);
    Tensor_set(er, (int[]){3}, 0);
    result.v[1] = *er;
    // Vetor normalizado da coordenada theta
    Tensor *etheta = Tensor_create(1, (int[]){4});
    assert(etheta && "Failed to allocate memory for t vector.");
    Tensor_set(etheta, (int[]){0}, 0);
    Tensor_set(etheta, (int[]){1}, 0);
    Tensor_set(etheta, (int[]){2}, 1 / r);
    Tensor_set(etheta, (int[]){3}, 0);
    result.v[2] = *etheta;
    // Vetor normalizado da coordenada phi
    Tensor *ephi = Tensor_create(1, (int[]){4});
    assert(ephi && "Failed to allocate memory for t vector.");
    Tensor_set(ephi, (int[]){0}, 0);
    Tensor_set(ephi, (int[]){1}, 0);
    Tensor_set(ephi, (int[]){2}, 0);
    Tensor_set(ephi, (int[]){3}, 1 / (r * sin(theta)));
    result.v[3] = *ephi;
    return result;
}

static Tensor UNUSED getRayThroughPixel(int sx, int sy, int width, int height,
                                        float fovDegrees) {
    assert(width > 0 && height > 0 && "Invalid image dimensions.");
    assert(fovDegrees > 0 && fovDegrees < 180 && "Invalid field of view.");

    double fovRad = (fovDegrees / 360.f) * 2 * M_PI;
    double fovStop = (width / 2.0) / tan(fovRad / 2);

    Tensor *pixelDir = Tensor_create(1, (int[]){3});
    assert(pixelDir && "Failed to allocate memory for pixelDir tensor.");
    Tensor_set(pixelDir, (int[]){0}, (sx - width / 2.0) / width);
    Tensor_set(pixelDir, (int[]){1}, (sy - height / 2.0) / width);
    Tensor_set(pixelDir, (int[]){2}, -fovStop / width);

    Tensor result = *Tensor_normalize(pixelDir);
    Tensor_free(pixelDir);
    return result;
}

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

    Geodesic result;
    result.position = pos;
    result.velocity = *resultV;

    Tensor_free(normalizeDir);
    Tensor_free(t_v);
    Tensor_free(x_v);
    Tensor_free(y_v);
    Tensor_free(z_v);

    return result;
}

static Tensor *partialDerivative(Tensor *(*func)(Tensor *), Tensor *pos,
                                 int dir) {
    assert(func && "Invalid function pointer.");
    assert(pos && "Invalid position tensor.");
    assert(dir >= 0 && dir < pos->dims[0] && "Invalid direction.");

    Tensor p_up = *Tensor_copy(pos);
    Tensor p_lo = *Tensor_copy(pos);
    Tensor_set(&p_up, (int[]){dir}, Tensor_get(pos, (int[]){dir}) + EPS);
    Tensor_set(&p_lo, (int[]){dir}, Tensor_get(pos, (int[]){dir}) - EPS);

    Tensor *up = (*func)(&p_up);
    Tensor *lo = (*func)(&p_lo);
    Tensor *diff = Tensor_sub(up, lo);

    double scalar = 1 / (2.0 * EPS);
    Tensor *result = Tensor_create(diff->num_dims, diff->dims);
    for (int i = 0; i < diff->num_dims; ++i) {
        result->data[i] = diff->data[i] * scalar;
    }

    Tensor_free(up);
    Tensor_free(lo);
    Tensor_free(diff);

    return result;
}

static Tensor *calculateChristoff2(Tensor *position,
                                   Tensor *(*get_metric)(Tensor *)) {
    Tensor *metric = get_metric(position);
    Tensor *metric_inverse = Tensor_inverse(metric);

    int dims_diff[] = {4, 4, 4};
    Tensor *metric_diff = Tensor_create(3, dims_diff);
    for (int i = 0; i < 4; ++i) {
        Tensor differentiated = *partialDerivative(get_metric, position, i);
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                Tensor_set(metric_diff, (int[]){i, j, k},
                           Tensor_get(&differentiated, (int[]){j, k}));
            }
        }
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

    Tensor_free(metric);
    Tensor_free(metric_inverse);
    Tensor_free(metric_diff);

    return Gamma;
}

static Tensor *calculateAccelerationOf(Tensor *X, Tensor *v,
                                       Tensor *(*get_metric)(Tensor *)) {
    Tensor *christoff2 = calculateChristoff2(X, get_metric);
    Tensor *acceleration = Tensor_create(1, (int[]){4});
    for (int mu = 0; mu < 4; ++mu) {
        double sum = 0;
        for (int al = 0; al < 4; ++al) {
            for (int be = 0; be < 4; ++be) {
                sum += -Tensor_get(christoff2, (int[]){mu, al, be}) *
                       Tensor_get(v, (int[]){al}) * Tensor_get(v, (int[]){be});
            }
        }
        Tensor_set(acceleration, (int[]){mu}, sum);
    }
    Tensor_free(christoff2);
    return acceleration;
}

static Tensor UNUSED *calculateSchwarzschildAcceleration(Tensor *X, Tensor *v) {
    return calculateAccelerationOf(X, v, schwarzschildMetric);
}

static IntegrationResult UNUSED integrate(Geodesic *g) {
    assert(g && "Invalid geodesic.");

    IntegrationResult result;
    result.type = UNFINISHED;

    double start_time = Tensor_get(&g->position, (int[]){0});
    for (int i = 0; i < 100 * 10; ++i) {
        Tensor acceleration =
            *calculateSchwarzschildAcceleration(&g->position, &g->velocity);

        Tensor_add_inplace(&g->velocity, &acceleration);
        Tensor_add_inplace(&g->position, Tensor_mul_scalar(&g->velocity, dt));

        double radius = Tensor_get(&g->position, (int[]){1});
        if (radius > 10) {
            result.type = ESCAPED;
            return result;
        }
        if (radius <= RS + EPS ||
            Tensor_get(&g->position, (int[]){0}) > start_time + 1000) {
            result.type = EVENT_HORIZON;
            return result;
        }
    }
    return result;
}

static Tensor UNUSED angleToTex(const Tensor *angle) {
    assert(angle != NULL);

    double theta = fmod(angle->data[0], 2 * M_PI);
    double phi = angle->data[1];
    if (theta >= M_PI) {
        phi += M_PI;
        theta -= M_PI;
    }
    phi = fmod(phi, 2 * M_PI);

    double sx = phi / (2 * M_PI);
    double sy = theta / M_PI;
    sx += 0.5;

    Tensor result = *Tensor_create(1, (int[]){2});
    Tensor_set(&result, (int[]){0}, sx);
    Tensor_set(&result, (int[]){1}, sy);
    return result;
}

static Tensor UNUSED renderPixel(int x, int y, int width, int height,
                                 Background *background) {
    Tensor rayDirection = getRayThroughPixel(x, y, width, height, 90);

    Tensor cameraPosition = *Tensor_create(1, (int[]){4});
    Tensor_set(&cameraPosition, (int[]){0}, 0);
    Tensor_set(&cameraPosition, (int[]){1}, 5);
    Tensor_set(&cameraPosition, (int[]){2}, M_PI / 2);
    Tensor_set(&cameraPosition, (int[]){3}, -M_PI / 2);

    Tetrad tetrads = calculateSchwarzschildTetrad(cameraPosition);
    Tensor modifiedRay = *Tensor_create(1, (int[]){3});
    Tensor_set(&modifiedRay, (int[]){0},
               -Tensor_get(&rayDirection, (int[]){2}));
    Tensor_set(&modifiedRay, (int[]){1}, Tensor_get(&rayDirection, (int[]){1}));
    Tensor_set(&modifiedRay, (int[]){2}, Tensor_get(&rayDirection, (int[]){0}));

    Geodesic myGeodesic =
        makeLightlikeGeodesic(cameraPosition, modifiedRay, tetrads);

    IntegrationResult result = integrate(&myGeodesic);
    if (result.type == EVENT_HORIZON || result.type == UNFINISHED) {
        Tensor black = *Tensor_create(1, (int[]){3});
        Tensor_set(&black, (int[]){0}, 0);
        Tensor_set(&black, (int[]){1}, 0);
        Tensor_set(&black, (int[]){2}, 0);
        return black;
    } else {
        double theta = Tensor_get(&myGeodesic.position, (int[]){2});
        double phi = Tensor_get(&myGeodesic.position, (int[]){3});

        Tensor angle = *Tensor_create(1, (int[]){2});
        Tensor_set(&angle, (int[]){0}, theta);
        Tensor_set(&angle, (int[]){1}, phi);

        Tensor texCoord = angleToTex(&angle);
        int tx = (int)(Tensor_get(&texCoord, (int[]){0}) * background->width) %
                 background->width;
        int ty = (int)(Tensor_get(&texCoord, (int[]){1}) * background->height) %
                 background->height;

        Pixel color = background_getPixel(background, tx, ty);
        Tensor resultColor = *Tensor_create(1, (int[]){3});
        Tensor_set(&resultColor, (int[]){0}, color.r / 255.0);
        Tensor_set(&resultColor, (int[]){1}, color.g / 255.0);
        Tensor_set(&resultColor, (int[]){2}, color.b / 255.0);
        return resultColor;
    }
}

static Background extractPixels(SDL_Surface *imgBackground) {
    Background background;
    background.width = imgBackground->w;
    background.height = imgBackground->h;
    background.pixels =
        (Pixel *)malloc(background.width * background.height * sizeof(Pixel));
    return background;
}

static UNUSED Tensor *getPixel(int width, int height,
                               SDL_Surface *imgBackground) {
    Background background = extractPixels(imgBackground);
    Tensor *result = Tensor_create(2, (int[]){height, width, 3});
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tensor renderedPixel =
                renderPixel(x, y, width, height, &background);
            for (int c = 0; c < 3; ++c) {
                Tensor_set(result, (int[]){y, x, c},
                           Tensor_get(&renderedPixel, (int[]){c}));
            }
            Tensor_free(&renderedPixel);
        }
    }
    free(background.pixels);
    return result;
}

#endif //! BLACKHOLE2_H
