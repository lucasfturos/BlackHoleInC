#include "SDL/render.h"
#include <time.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Informe qual opção de plot quer. Ex: ./src/Demo 1\n");
        exit(1);
    }
    
    int opc = atoi(argv[1]);

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

        switch (opc) {
        case 1:
            render1(res.ren);
            break;
        case 2:
            render2(res.ren, res.background);
            break;
        default:
            break;
        }

        SDL_RenderPresent(res.ren);
        SDL_Delay(1000 / FPS);
    }
    destroyResources(res);
    SDL_Quit();
    return EXIT_SUCCESS;
}