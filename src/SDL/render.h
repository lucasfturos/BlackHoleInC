#ifndef RENDER_H
#define RENDER_H

#include "BlackHole/blackhole.h"
#include "init.h"
#include "objects.h"

const double particleRadius = 2.0;

static inline void render1(SDL_Renderer *ren) {
    Vec3 camera = Vec3_create(0.0, 0.2, -3.5);
    // Vec3 camera = Vec3_create(0.0, 0.4, -3.0);
    double vfov = 2.6;
    Mat3 world = Mat3_normalize(Mat3_create(Vec3_create(1.0, -0.2, 0.0),
                                            Vec3_create(0.2, 1.0, 0.0),
                                            Vec3_create(0.0, -0.1, 1.0)));
    // Mat3 world = Mat3_normalize(Mat3_create(Vec3_create(1.0, 0.0, 0.0),
    //                                         Vec3_create(0.0, 1.0, 0.0),
    //                                         Vec3_create(0.0, 0.0, 1.0)));
    for (int i = 0; i < 1000 * 4; ++i) {
        Position particle = {
            .x = gaussianNoise(WIDTH / 2.0, WIDTH / 5.0),
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
        SDL_Color particleColor = {r, g, b, SDL_ALPHA_OPAQUE};

        double invertedY = HEIGHT - 1 - particle.y;
        drawCircle(ren, particle.x, invertedY, particleRadius, particleColor);
    }
}

static inline void render2(SDL_Renderer *ren, SDL_Surface *imgBackground) {
    int imgWidth = imgBackground->w;
    int imgHeight = imgBackground->h;
    Uint32 *pixels = (Uint32 *)imgBackground->pixels;
    SDL_PixelFormat *format = imgBackground->format;

    Vec3 camera = Vec3_create(0.0, 0.15, -3.5);
    double vfov = 3.6;
    Mat3 world = Mat3_normalize(Mat3_create(Vec3_create(1.0, -0.2, 0.0),
                                            Vec3_create(0.2, 1.0, 0.0),
                                            Vec3_create(0.0, -0.1, 1.0)));

    const double samplePercentage = 0.7;
    const int numSamples = (int)(WIDTH * 0.5 * HEIGHT * 0.5 * samplePercentage);
    for (int i = 0; i < numSamples; ++i) {
        int x = random_range(0, WIDTH - 1);
        int y = random_range(0, HEIGHT - 1);

        int imgX = (int)(x / (double)WIDTH * imgWidth);
        int imgY = (int)(y / (double)HEIGHT * imgHeight);

        Uint32 pixel = pixels[imgY * imgWidth + imgX];
        Uint8 r, g, b;
        SDL_GetRGB(pixel, format, &r, &g, &b);

        Vec2 uv =
            Vec2_create((double)x / WIDTH - 0.5, (double)y / HEIGHT - 0.5);
        Vec3 rd = Vec3_normalize(
            Vec3_add(Vec3_add(Vec3_mul_scalar(world.v[0], uv.x * vfov),
                              Vec3_mul_scalar(world.v[1], uv.y * vfov)),
                     world.v[2]));

        Vec3 colorRadiance = radiance(camera, rd);
        Uint8 newR = (Uint8)(fmin(colorRadiance.x * 0xFF, 0xFF));
        Uint8 newG = (Uint8)(fmin(colorRadiance.y * 0xFF, 0xFF));
        Uint8 newB = (Uint8)(fmin(colorRadiance.z * 0xFF, 0xFF));

        Uint8 mixedR = (Uint8)((0.5 * r) + (0.5 * newR));
        Uint8 mixedG = (Uint8)((0.5 * g) + (0.5 * newG));
        Uint8 mixedB = (Uint8)((0.5 * b) + (0.5 * newB));

        double invertedY = HEIGHT - 1 - y;
        SDL_SetRenderDrawColor(ren, mixedR, mixedG, mixedB, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(ren, x, invertedY);
    }
}

#endif //! RENDER_H