#include "game.h"
#include <SDL2/SDL_image.h>

Duck Duck_new() { // hacer que tenga de parametro una imagen(?
    Duck duck;
    
    duck.image[0] = IMG_Load("../assets/duck1.png");
    duck.image[1] = IMG_Load("../assets/duck2.png");
    
    duck.position.x = 60;
    duck.position.y = 300;
    duck.position.w = 60;
    duck.position.h = 60;

    return duck;
}

void Duck_move(Duck *duck, int *jump, int count, int *costume) {
    if(*jump) { // salto
        *costume = 1;
        printf("jump!\n");
        for(float i = 0; i < 1; i += 0.01) {
            duck->vel = -3*i;
        }
        *jump = 0;
    }

    if(duck->position.y > 660) {// si se pasa por abajo
        duck->position.y = 660;
        duck->vel = 0;
    }
    else { // para que caiga
        duck->position.y += duck->vel;
        duck->vel += 0.08;
    }

    if(duck->position.y < 0) { // si se pasa por arriba
        duck->position.y = 0;
        duck->vel = 0.08;
    }
}
