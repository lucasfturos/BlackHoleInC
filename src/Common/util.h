#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

static void init_random() __attribute__((unused));
static void init_random() { srand(time(0)); }

static double random_double() __attribute__((unused));
static double random_double() { return (double)rand() / RAND_MAX; }

static double mix(double a, double b, double t) __attribute__((unused));
static double mix(double a, double b, double t) { return a * (1 - t) + b * t; }

#endif //! UTIL_H