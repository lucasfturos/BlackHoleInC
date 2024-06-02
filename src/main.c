#include "Math/Vec/vecn.h"
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
    Vec3 v1 = Vec3_create(1.0, 2.0, 3.0);
    printf("Vec v1: ");
    Vec3_print(v1);
    printf("1 length: %.2f\n", Vec3_length(v1));
    printf("1 dotp: %.1f\n", Vec3_dotp(v1));

    double data_v2[] = {1.0, 2.0, 3.0};
    VecN v2 = VecN_setData(3, data_v2);
    printf("Vec v2: ");
    VecN_print(&v2);
    printf("v2 length: %.2f\n", VecN_length(&v2));
    printf("v2 dotp: %.1f\n", VecN_dotp(&v2));

    VecN v3 = VecN_create(3);
    VecN_setValue(&v3, 0, 1.0);
    VecN_setValue(&v3, 1, 2.0);
    VecN_setValue(&v3, 2, 3.0);
    printf("Vec v3: ");
    VecN_print(&v3);
    printf("v3 length: %.2f\n", VecN_length(&v3));
    printf("v3 dotp: %.1f\n", VecN_dotp(&v3));

    return EXIT_SUCCESS;
}