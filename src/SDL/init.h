#ifndef INIT_H
#define INIT_H

#include "../Common/util.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
} Resources;

static void destroyResources(Resources res) {
    SDL_DestroyRenderer(res.ren);
    SDL_DestroyWindow(res.win);
}

static int initWindow(Resources *res) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    res->win = SDL_CreateWindow("Black Hole in C", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                                SDL_WINDOW_VULKAN);

    if (res->win == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        destroyResources(*res);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    res->ren = SDL_CreateRenderer(
        res->win, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    if (res->ren == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        destroyResources(*res);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif //! INIT_H