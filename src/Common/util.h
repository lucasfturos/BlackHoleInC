#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <time.h>

static void init_random() { srand(time(0)); }

static char get_ascii_char(double intensity) {
    const char *chars = " .:-=+*#%@";
    int index = (int)(intensity * 9.0);
    if (index < 0) {
        index = 0;
    }
    if (index > 9) {
        index = 9;
    }
    return chars[index];
}

static double random_double() { return (double)rand() / RAND_MAX; }

static double mix(double a, double b, double t) { return a * (1 - t) + b * t; }

#endif //! UTIL_H