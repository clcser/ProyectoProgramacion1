#include "background.h"

static SDL_Surface *background_surface = NULL;

Background Background_new() {
    Background background;
    if (background_surface == NULL) {
        background_surface = IMG_Load("../assets/grass.png");
    }
    background.image = background_surface;
    background.position.x = 0;
    background.position.y = 0;
    background.position.w = 720;
    background.position.h = 720;

    return background;
}

void Background_move(Background *bg) {
    bg->position.x++;

    if (bg->position.x > 2160) {
        bg->position.x = 0;
    }
}

