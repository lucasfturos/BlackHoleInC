#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>

static void drawCircle(SDL_Renderer *ren, double x, double y, int radius,
                       SDL_Color color) {
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; ++w) {
        for (int h = 0; h < radius * 2; ++h) {
            double dx = radius - w;
            double dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(ren, x + dx, y + dy);
            }
        }
    }
}

#endif //! OBJECTS_H