#include "background.h"

static SDL_Surface *background_surface = NULL;

Background Background_new() {
    Background background;
    if (background_surface == NULL) {
        background_surface = IMG_Load("../assets/fondo.png");
    }
    background.image = background_surface;

    return background;
}
