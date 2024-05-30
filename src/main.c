#include "Common/blackhole_math.h"
#include "SDL/init.h"
#include "SDL/objects.h"

void render(SDL_Renderer *ren) {
    double particle_radius = 2.0;
    Vec3 cameraPosition = Vec3_create(0.0, 0.2, -3.5);
    // Vec3 cameraPosition = Vec3_create(0.0, 0.4, -3.0);
    double camfov = 2.3;
    Mat3 rotmat = (Mat3){
        .v[0] = Vec3_create(1.0, -0.2, 0.0),
        .v[1] = Vec3_create(0.2, 1.0, 0.1),
        .v[2] = Vec3_create(0.0, -0.1, 1.0),
    };
    // Mat3 rotmat = (Mat3){
    //     .v[0] = Vec3_create(1.0, 0.0, 0.0),
    //     .v[1] = Vec3_create(0.0, 1.0, 0.0),
    //     .v[2] = Vec3_create(0.0, 0.0, 1.0),
    // };
    rotmat = Mat3_normalize(rotmat);
    for (int i = 0; i < 1000 * 4; ++i) {
        Position particle = {fmod(rand(), WIDTH - 1), fmod(rand(), HEIGHT - 1)};
        double inverted_y = HEIGHT - 1 - particle.y;
        Vec2 uv =
            Vec2_create(particle.x / WIDTH - 0.5, particle.y / HEIGHT - 0.5);
        Vec3 rd = Vec3_normalize(
            Vec3_add(Vec3_add(Vec3_mul_scalar(rotmat.v[0], uv.x * camfov),
                              Vec3_mul_scalar(rotmat.v[1], uv.y * camfov)),
                     rotmat.v[2]));
        Vec3 color = radiance(cameraPosition, rd);
        Uint8 r = (Uint8)(fmin(color.x * 0xFF, 0xFF));
        Uint8 g = (Uint8)(fmin(color.y * 0xFF, 0xFF));
        Uint8 b = (Uint8)(fmin(color.z * 0xFF, 0xFF));
        SDL_Color particle_color = {r, g, b, 0xFF};
        drawCircle(ren, particle.x, inverted_y, particle_radius,
                   particle_color);
    }
}

int main(void) {
    init_random();
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

        render(res.ren);

        SDL_RenderPresent(res.ren);
        SDL_Delay(1000 / FPS);
    }

    destroyResources(res);
    SDL_Quit();
    return EXIT_SUCCESS;
}