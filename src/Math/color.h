#ifndef COLOR_H
#define COLOR_H

#include "Mat/mat3.h"
#include "Vec/vec2.h"
#include "Vec/vec3.h"
#include "common.h"
#include <SDL2/SDL_surface.h>

typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    int width, height;
    Pixel *pixels;
} Background;

static inline Background getBackgroudData(SDL_Surface *imgBackground) {
    return (Background){
        .width = imgBackground->w,
        .height = imgBackground->h,
        .pixels = (Pixel *)malloc(imgBackground->w * imgBackground->h *
                                  sizeof(Pixel *)),
    };
}

//! Function to convert from CIE XYZ color space to RGB color space
static inline Vec3 XYZtoRGB(Vec3 XYZ) {
    const Mat3 XYZ2sRGB = Mat3_create(Vec3_create(3.240, -1.537, -0.499),
                                      Vec3_create(-0.969, 1.876, 0.042),
                                      Vec3_create(0.056, -0.204, 1.057));
    return Mat3_mul_vec3(XYZ2sRGB, XYZ);
}

//! Function to calculate the XYZ color corresponding to a blackbody at
//! temperature t
static inline Vec3 colorBlackBodyXYZ(double t) {
    double u = (0.860117757 + 1.54118254E-4 * t + 1.28641212E-7 * t * t) /
               (1.0 + 8.42420235E-4 * t + 7.08145163E-7 * t * t);
    double v = (0.317398726 + 4.22806245E-5 * t + 4.20481691E-8 * t * t) /
               (1.0 - 2.89741816E-5 * t + 1.61456053E-7 * t * t);

    Vec2 xy = Vec2_create(3.0 * u, 2.0 * v);
    xy = Vec2_div_scalar(xy, 2.0 * u - 8.0 * v + 4.0);
    return Vec3_create(xy.x / xy.y, 1.0, (1.0 - xy.x - xy.y) / xy.y);
}

#endif //! COLOR_H