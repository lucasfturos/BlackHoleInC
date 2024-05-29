#include "Common/Math/math_utils.h"
#include "Common/util.h"
#include "Vec/vec2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 120
#define HEIGHT 40

#define FRAME 50000UL

void render_frame(int frame) {
    Vec3 cameraPosition = Vec3_create(0.0, 0.1, -3.5);
    double camfov = 1.2;

    Vec3 rotmat[3] = {
        Vec3_create(1.0, -0.2, 0.0),
        Vec3_create(0.2, 1.0, 0.1),
        Vec3_create(0.0, -0.1, 1.0),
    };

    normalize_matrix(rotmat);

    double resolution[2] = {WIDTH, HEIGHT};

    printf("\033c");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Vec2 fragCoord = Vec2_create(x, y);
            Vec2 uv = Vec2_create(2.0 * (fragCoord.x / resolution[0] - 0.5),
                                  2.0 * (fragCoord.y / resolution[1] - 0.5));
            Vec3 rd = Vec3_normalize(
                Vec3_add(Vec3_add(Vec3_mul_scalar(rotmat[0], uv.x * camfov),
                                  Vec3_mul_scalar(rotmat[1], uv.y * camfov)),
                         rotmat[2]));

            Vec3 color = radiance(cameraPosition, rd);

            double intensity = Vec3_length(color);
            char c = get_ascii_char(intensity);

            putchar(c);
        }
        putchar('\n');
    }
}

int main(void) {
    init_random();

    for (int frame = 0; frame < 100; frame++) {
        render_frame(frame);
        usleep(FRAME);
    }
    return 0;
}
