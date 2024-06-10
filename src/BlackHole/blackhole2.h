#ifndef BLACKHOLE2_H
#define BLACKHOLE2_H

#include "../Math/Tensor/geodesic.h"
#include "../Math/color.h"
#include "../Math/util.h"

#define dt 0.3

enum HitType {
    ESCAPED,
    EVENT_HORIZON,
    UNFINISHED,
};

typedef struct {
    enum HitType type;
} IntegrationResult;

static Tensor *schwarzschildMetric(Tensor *pos) {
    assert(pos && "Invalid position tensor.");

    double r = pos->data[1];
    double theta = pos->data[2];
    assert(r > RS);

    Tensor *metric = Tensor_create(2, (int[]){4, 4});
    assert(metric && "Failed to allocate memory for metric tensor.");

    Tensor_set(metric, (int[]){0, 0}, -(1 - RS / r));
    Tensor_set(metric, (int[]){1, 1}, 1 / (1 - RS / r));
    Tensor_set(metric, (int[]){2, 2}, r * r);
    Tensor_set(metric, (int[]){3, 3}, r * r * sin(theta) * sin(theta));
    return metric;
}

static Tensor getRayThroughPixel(int sx, int sy, int width, int height,
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

static Tensor *calculateChristoff2(Tensor *position,
                                   Tensor *(*get_metric)(Tensor *)) {
    Tensor *metric = get_metric(position);
    Tensor *metric_inverse = Tensor_inverse(metric);

    Tensor *metric_diff = Tensor_create(3, (int[]){4, 4, 4});
    for (int i = 0; i < 4; ++i) {
        Tensor differentiated = *partialDerivative(get_metric, position, i);
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                Tensor_set(metric_diff, (int[]){i, j, k},
                           Tensor_get(&differentiated, (int[]){j, k}));
            }
        }
        Tensor_free(&differentiated);
    }

    Tensor *Gamma = Tensor_create(3, (int[]){4, 4, 4});
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
    assert(christoff2 && "Failed to calculate Christoff2 tensor.");
    Tensor *acceleration = Tensor_create(1, (int[]){4});
    for (int mu = 0; mu < 4; ++mu) {
        double sum = 0;
        for (int al = 0; al < 4; ++al) {
            for (int be = 0; be < 4; ++be) {
                sum += -Tensor_get(christoff2, (int[]){mu, al, be}) *
                       v->data[al] * v->data[be];
            }
        }
        Tensor_set(acceleration, (int[]){mu}, sum);
    }
    Tensor_free(christoff2);
    return acceleration;
}

static Tensor *calculateSchwarzschildAcceleration(Tensor *X, Tensor *v) {
    return calculateAccelerationOf(X, v, schwarzschildMetric);
}

static IntegrationResult integrate(Geodesic *g) {
    assert(g && "Invalid geodesic.");

    IntegrationResult result;
    result.type = UNFINISHED;

    double start_time = g->position.data[0];
    for (int i = 0; i < 100 * 1; ++i) {
        Tensor acceleration =
            *calculateSchwarzschildAcceleration(&g->position, &g->velocity);
        Tensor_add_inplace(&g->velocity, &acceleration);
        Tensor_add_inplace(&g->position, Tensor_mul_scalar(&g->velocity, dt));

        double radius = g->position.data[1];
        if (radius > 10) {
            result.type = ESCAPED;
            return result;
        }
        if (radius <= RS + EPS || g->position.data[0] > start_time + 1000) {
            result.type = EVENT_HORIZON;
            return result;
        }
        Tensor_free(&acceleration);
    }
    return result;
}

static Tensor *renderPixel(int x, int y, int width, int height,
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
    Tensor_set(&modifiedRay, (int[]){1}, rayDirection.data[1]);
    Tensor_set(&modifiedRay, (int[]){2}, rayDirection.data[0]);

    Geodesic geodesic =
        makeLightlikeGeodesic(cameraPosition, modifiedRay, tetrads);

    IntegrationResult result = integrate(&geodesic);
    if (result.type != EVENT_HORIZON || result.type != UNFINISHED) {
        double theta = geodesic.position.data[2];
        double phi = geodesic.position.data[3];

        Tensor angle = *Tensor_create(1, (int[]){2});
        Tensor_set(&angle, (int[]){0}, theta);
        Tensor_set(&angle, (int[]){1}, phi);

        Tensor texCoord = angleToTex(&angle);
        int tx =
            (int)(texCoord.data[0] * background->width) % background->width;
        int ty =
            (int)(texCoord.data[1] * background->height) % background->height;

        Pixel color = background->pixels[ty * background->width + tx];
        Tensor *resultColor = Tensor_create(1, (int[]){3});
        Tensor_set(resultColor, (int[]){0}, color.r / 255.0);
        Tensor_set(resultColor, (int[]){1}, color.g / 255.0);
        Tensor_set(resultColor, (int[]){2}, color.b / 255.0);
        Tensor_free(&angle);
        Tensor_free(&texCoord);
        Tensor_free(&cameraPosition);
        Tensor_free(&modifiedRay);
        Tensor_free(&rayDirection);
        Tetrad_free(&tetrads);
        return resultColor;
    }

    Tensor *black = Tensor_create(1, (int[]){3});
    Tensor_set(black, (int[]){0}, 0);
    Tensor_set(black, (int[]){1}, 0);
    Tensor_set(black, (int[]){2}, 0);
    return black;
}

static double *getPixel(int width, int height, SDL_Surface *imgBackground) {
    Background background = getBackgroudData(imgBackground);
    double *result = (double *)malloc(height * width * sizeof(double));
    assert(result != NULL && "Failed to allocate memory for result array.");

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tensor *renderedPixel =
                renderPixel(x, y, width, height, &background);
            for (int c = 0; c < 3; ++c) {
                result[y * width + x] = renderedPixel->data[c];
            }
            Tensor_free(renderedPixel);
        }
    }

    // for (int i = 0; i < height * width; ++i) {
    //     printf("(%d, %d, %d) ", (int)(result[i * 3] * 255),
    //            (int)(result[i * 3 + 1] * 255), (int)(result[i * 3 + 2] *
    //            255));
    //     if ((i + 1) % width == 0) {
    //         printf("\n");
    //     }
    // }

    free(background.pixels);
    return result;
}

#endif //! BLACKHOLE2_H
