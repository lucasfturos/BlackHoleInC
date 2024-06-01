#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UNUSED __attribute__((unused))

static double UNUSED random_double() { return (double)rand() / (1 * RAND_MAX); }

static double UNUSED mix(double a, double b, double t) {
    return a * (1 - t) + b * t;
}

static double UNUSED fract(double a) { return a - floor(a); }

static double UNUSED clamp(double a, double min, double max) {
    const double t = a < min ? min : a;
    return t > max ? max : t;
}

#endif //! COMMON_H