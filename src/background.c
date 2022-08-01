#include "background.h"

static SDL_Surface *background_surface = NULL;

Background Background_new() {
    Background background;
    /*if (background_surface == NULL) {
        background_surface = IMG_Load("../assets/background2.png");
    }*/
    background.image[0] =  IMG_Load("../assets/background1.png");
    background.image[1] =  IMG_Load("../assets/background2.png");
    background.image[2] =  IMG_Load("../assets/background3.png");
    background.position.x = 0;
    background.position.y = 0;
    background.position.w = 768;
    background.position.h = 768;

    return background;
}

void Background_move(Background *bg) {
    bg->position.x++;

    if (bg->position.x > 2304) {
        bg->position.x = 0;
    }
}

