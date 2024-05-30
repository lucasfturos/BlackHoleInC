#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UNUSED __attribute__((unused))
#define WIDTH 1080
#define HEIGHT 720
#define FPS 60

static void UNUSED init_random() { srand(time(0)); }

static double UNUSED random_double() { return (double)rand() / RAND_MAX; }

static double UNUSED mix(double a, double b, double t) {
    return a * (1 - t) + b * t;
}

static double UNUSED fract(double a) { return a - floor(a); }

static double UNUSED clamp(double a, double min, double max) {
    const double t = a < min ? min : a;
    return t > max ? max : t;
}

#endif //! UTIL_H