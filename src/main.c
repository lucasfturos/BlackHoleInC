#include "Common/blackhole_util.h"
#include "Mat/mat3.h"
#include "Vec/vec2.h"

#include <unistd.h>

void render_frame(int frame) {
    Vec3 cameraPosition = Vec3_create(0.0, 0.1, -3.5);
    double camfov = 1.2;

    Mat3 rotmat = {
        Vec3_create(1.0, -0.2, 0.0),
        Vec3_create(0.2, 1.0, 0.1),
        Vec3_create(0.0, -0.1, 1.0),
    };
    rotmat = Mat3_normalize(rotmat);

    Vec2 resolution = {WIDTH, HEIGHT};
    printf("\033c");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Vec2 fragCoord = Vec2_create(x, y);
            Vec2 uv = Vec2_create(2.0 * (fragCoord.x / resolution.x - 0.5),
                                  2.0 * (fragCoord.y / resolution.y - 0.5));
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

void run() {
    init_random();
    for (int frame = 0; frame < 100; ++frame) {
        render_frame(frame);
        usleep(50000);
    }
}

int main(void) {
    run();
    return 0;
}
