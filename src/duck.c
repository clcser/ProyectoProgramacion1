#include "duck.h"
#include <SDL2/SDL_image.h>

Duck Duck_new() { //hacer que tenga de parametro una imagen
    Duck duck;
    
    duck.image = IMG_Load("../assets/duck.png");
    
    duck.position.x = 40;
    duck.position.y = 100;
    duck.position.w = 80;
    duck.position.h = 80;

    return duck;
}
