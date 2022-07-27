#include "game.h"
#include <SDL2/SDL_image.h>

Duck Duck_new() { // hacer que tenga de parametro una imagen(?
    Duck duck;
    
    duck.image[0] = IMG_Load("../assets/yellow_duck1.png");
    duck.image[1] = IMG_Load("../assets/yellow_duck2.png");
    duck.image[2] = IMG_Load("../assets/blue_duck1.png");
    duck.image[3] = IMG_Load("../assets/blue_duck2.png");
    duck.image[4] = IMG_Load("../assets/purple_duck1.png");
    duck.image[5] = IMG_Load("../assets/purple_duck2.png");
    duck.image[6] = IMG_Load("../assets/gray_duck1.png");
    duck.image[7] = IMG_Load("../assets/gray_duck2.png");
    duck.image[8] = IMG_Load("../assets/red_duck1.png");
    duck.image[9] = IMG_Load("../assets/red_duck2.png");
    
    duck.position.x = 60;
    duck.position.y = 300;
    duck.position.w = 60;
    duck.position.h = 60;

    return duck;
}

void Duck_move(Duck *duck, int *jump, int count) {
    if(*jump) { // salto
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
