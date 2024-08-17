#ifndef OBJECTS_H
#define OBJECTS_H

#include "Math/Vec/vec2.h"
#include <SDL2/SDL.h>

static inline void drawCircle(SDL_Renderer *ren, double x, double y, int radius,
                       SDL_Color color) {
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; ++w) {
        for (int h = 0; h < radius * 2; ++h) {
            Vec2 dPos = Vec2_create(radius - w, radius - h);
            (Vec2_dotp(dPos) <= (radius * radius))
                ? SDL_RenderDrawPoint(ren, x + dPos.x, y + dPos.y)
                : 0;
        }
    }
}

#endif //! OBJECTS_H