#ifndef RENDER_H
#define RENDER_H

#include "../Math/blackhole.h"
#include "init.h"
#include "objects.h"

static void render1(SDL_Renderer *ren) {
    double particle_radius = 2.0;
    Vec3 camera = Vec3_create(0.0, 0.2, -3.5);
    // Vec3 camera = Vec3_create(0.0, 0.4, -3.0);
    double camfov = 2.3;
    Mat3 world =
        Mat3_create(Vec3_create(1.0, -0.2, 0.0), Vec3_create(0.2, 1.0, 0.1),
                    Vec3_create(0.0, -0.1, 1.0));
    // Mat3 world =
    //     Mat3_create(Vec3_create(1.0, 0.0, 0.0), Vec3_create(0.0, 1.0, 0.0),
    // Vec3_create(0.0, 0.0, 1.0));
    world = Mat3_normalize(world);
    for (int i = 0; i < 1000 * 4; ++i) {
        Position particle = {fmod(rand(), WIDTH - 1), fmod(rand(), HEIGHT - 1)};
        double inverted_y = HEIGHT - 1 - particle.y;
        Vec2 uv =
            Vec2_create(particle.x / WIDTH - 0.5, particle.y / HEIGHT - 0.5);
        Vec3 rd = Vec3_normalize(
            Vec3_add(Vec3_add(Vec3_mul_scalar(world.v[0], uv.x * camfov),
                              Vec3_mul_scalar(world.v[1], uv.y * camfov)),
                     world.v[2]));
        Vec3 color = radiance(camera, rd);
        Uint8 r = (Uint8)(fmin(color.x * 0xFF, 0xFF));
        Uint8 g = (Uint8)(fmin(color.y * 0xFF, 0xFF));
        Uint8 b = (Uint8)(fmin(color.z * 0xFF, 0xFF));
        SDL_Color particle_color = {r, g, b, 0xFF};
        drawCircle(ren, particle.x, inverted_y, particle_radius,
                   particle_color);
    }
}

#endif