#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 1080
#define HEIGHT 720
#define FPS 60

static void init_random() __attribute__((unused));
static void init_random() { srand(time(0)); }

static double random_double() __attribute__((unused));
static double random_double() { return (double)rand() / RAND_MAX; }

static double mix(double a, double b, double t) __attribute__((unused));
static double mix(double a, double b, double t) { return a * (1 - t) + b * t; }

static double clamp(double d, double min, double max) __attribute__((unused));
static double clamp(double d, double min, double max) {
    const double t = d < min ? min : d;
    return t > max ? max : t;
}

#endif //! UTIL_H