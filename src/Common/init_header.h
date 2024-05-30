#ifndef INIT_HEADER_H
#define INIT_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Math/blackhole.h"

#define UNUSED __attribute__((unused))
#define WIDTH 1080
#define HEIGHT 720
#define FPS 60

static void UNUSED init_random() { srand(time(0)); }

#endif //! INIT_HEADER_H