#ifndef RENDER_H
#define RENDER_H

#include "../BlackHole/blackhole1.h"
#include "init.h"
#include "objects.h"

const double particleRadius = 2.5;

static void UNUSED render1(SDL_Renderer *ren) {
    Vec3 camera = Vec3_create(0.0, 0.2, -3.5);
    // Vec3 camera = Vec3_create(0.0, 0.4, -3.0);
    double vfov = 2.3;
    Mat3 world = Mat3_normalize(Mat3_create(Vec3_create(1.0, -0.2, 0.0),
                                            Vec3_create(0.2, 1.0, 0.0),
                                            Vec3_create(0.0, -0.1, 1.0)));
    // Mat3 world = Mat3_normalize(Mat3_create(Vec3_create(1.0, 0.0, 0.0),
    //                                         Vec3_create(0.0, 1.0, 0.0),
    //                                         Vec3_create(0.0, 0.0, 1.0)));
    for (int i = 0; i < 1000; ++i) {
        Position particle = {
            .x = gaussianNoise(WIDTH / 2.0, WIDTH / 8.0),
            .y = gaussianNoise(HEIGHT / 2.0, HEIGHT / 8.0),
        };
        particle.x = fmin(fmax(particle.x, 0), WIDTH - 1);
        particle.y = fmin(fmax(particle.y, 0), HEIGHT - 1);

        Vec2 uv =
            Vec2_create(particle.x / WIDTH - 0.5, particle.y / HEIGHT - 0.5);
        Vec3 rd = Vec3_normalize(
            Vec3_add(Vec3_add(Vec3_mul_scalar(world.v[0], uv.x * vfov),
                              Vec3_mul_scalar(world.v[1], uv.y * vfov)),
                     world.v[2]));

        Vec3 color = radiance(camera, rd);
        Uint8 r = (Uint8)(fmin(color.x * 0xFF, 0xFF));
        Uint8 g = (Uint8)(fmin(color.y * 0xFF, 0xFF));
        Uint8 b = (Uint8)(fmin(color.z * 0xFF, 0xFF));
        SDL_Color particleColor = {r, g, b, 0xFF};

        double invertedY = HEIGHT - 1 - particle.y;
        drawCircle(ren, particle.x, invertedY, particleRadius, particleColor);
    }
}

static void UNUSED render2(/* SDL_Renderer * ren */) {}

#endif
