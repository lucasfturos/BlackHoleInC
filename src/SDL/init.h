#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 1080
#define HEIGHT 720
#define FPS 60

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

static SDL_Surface *uploadImage(const char *filename) {
    SDL_Surface *loadedSurface = IMG_Load(filename);
    if (loadedSurface == NULL) {
        fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n",
                filename, IMG_GetError());
    }
    return loadedSurface;
}

#endif //! INIT_H