#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define WIDTH 1080
#define HEIGHT 720
#define FPS 60

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Surface *background;
} Resources;

static void destroyResources(Resources res) {
    if (res.win) {
        SDL_DestroyWindow(res.win);
        res.win = NULL;
    }
    if (res.ren) {
        SDL_DestroyRenderer(res.ren);
        res.ren = NULL;
    }
    if (res.background) {
        SDL_FreeSurface(res.background);
    }
}

static inline SDL_Surface *uploadImage(const char *filename) {
    SDL_Surface *loadedSurface = IMG_Load(filename);
    if (loadedSurface == NULL) {
        fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n",
                filename, IMG_GetError());
    }
    return loadedSurface;
}

static int errorMessage(Resources *res, const char *message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    destroyResources(*res);
    SDL_Quit();
    return EXIT_FAILURE;
}

static int initWindow(Resources *res) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    res->win = SDL_CreateWindow("Black Hole in C", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    if (res->win == NULL) {
        return errorMessage(res, "SDL_CreateWindow Error");
    }

    res->ren = SDL_CreateRenderer(
        res->win, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    if (res->ren == NULL) {
        return errorMessage(res, "SDL_CreateRenderer Error");
    }

    const char *filename = "assets/nasa_resize.png";
    res->background = uploadImage(filename);
    if (res->background == NULL) {
        char errorMsg[256];
        snprintf(errorMsg, sizeof(errorMsg), "Failed to load image %s",
                 filename);
        return errorMessage(res, errorMsg);
    }
    return EXIT_SUCCESS;
}

#endif //! INIT_H