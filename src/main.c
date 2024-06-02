#include "Math/Vec/vec3.h"
#include "Math/common.h"
#include "SDL/render.h"
#include <time.h>

void UNUSED run() {
    srand(time(0));
    Resources res;
    initWindow(&res);
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

        render1(res.ren);

        SDL_RenderPresent(res.ren);
        SDL_Delay(1000 / FPS);
    }
    destroyResources(res);
    SDL_Quit();
}

int main(void) {
    Vec3 v = Vec3_create(1.0, 2.0, 3.0);
    printf("Vec3: ");
    Vec3_print(v);
    printf("Vec3 length: %.2f\n", Vec3_length(v));
    printf("Vec3 dotp: %.2f\n", Vec3_dotp(v));

    return EXIT_SUCCESS;
}