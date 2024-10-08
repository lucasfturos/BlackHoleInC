#ifndef RUN_H
#define RUN_H

#include "BlackHole/blackhole.h"
#include <time.h>
#include <unistd.h>

#define WIDTH 140
#define HEIGHT 40

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

static void render_frame() {
    Vec2 screenSize = {.x = WIDTH, .y = HEIGHT};
    Vec3 cameraPosition = Vec3_create(0.0, 0.1, -3.5);
    double camfov = 1.2;
    Mat3 rotmat =
        Mat3_create(Vec3_create(1.0, -0.2, 0.0), Vec3_create(0.2, 1.0, 0.1),
                    Vec3_create(0.0, -0.1, 1.0));
    rotmat = Mat3_normalize(rotmat);

    printf("\033c");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Vec2 coord = Vec2_create(x, y);
            Vec2 uv = Vec2_create(2.0 * (coord.x / screenSize.x - 0.5),
                                  2.0 * (coord.y / screenSize.y - 0.5));
            Vec3 rd = Vec3_normalize(
                Vec3_add(Vec3_add(Vec3_mul_scalar(rotmat.v[0], uv.x * camfov),
                                  Vec3_mul_scalar(rotmat.v[1], uv.y * camfov)),
                         rotmat.v[2]));
            Vec3 color = radiance(cameraPosition, rd);
            double intensity = Vec3_length(color);
            char c = get_ascii_char(intensity);
            putchar(c);
        }
        putchar('\n');
    }
}

static void run_terminal() {
    srand(time(0));

    for (int frame = 0; frame < 100; frame++) {
        render_frame();
        usleep(50000);
    }
}

#endif //! RUN_H