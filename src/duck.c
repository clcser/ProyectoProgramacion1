#include "duck.h"
#include <SDL2/SDL_image.h>

Duck Duck_new() { //hacer que tenga de parametro una imagen
    Duck duck;
    
    duck.image[0] = IMG_Load("../assets/duck1.png");
    duck.image[1] = IMG_Load("../assets/duck2.png");
    
    duck.position.x = 40;
    duck.position.y = 100;
    duck.position.w = 60;
    duck.position.h = 60;

    return duck;
}
