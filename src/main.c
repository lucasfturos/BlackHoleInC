#include "SDL/render.h"
#include <time.h>

int main() {
    srand(time(0));
    Resources res;
    initWindow(&res);

    const char *filename = "assets/nasa_resize.png";
    SDL_Surface *imageBackgroud = uploadImage(filename);
    if (imageBackgroud == NULL) {
        fprintf(stderr, "Failed to load image %s\n", filename);
        destroyResources(res);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    int quit = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            event.type == SDL_QUIT ? (quit = 1) : 0;
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                quit = 1;
                break;
            default:
                break;
            }
        }
        SDL_SetRenderDrawColor(res.ren, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(res.ren);

        render3(res.ren, imageBackgroud);

        SDL_RenderPresent(res.ren);
        SDL_Delay(1000 / FPS);
    }
    destroyResources(res);
    SDL_FreeSurface(imageBackgroud);
    SDL_Quit();
    return EXIT_SUCCESS;
}