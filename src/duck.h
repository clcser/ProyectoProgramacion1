#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Surface *image[2];
    SDL_Rect position;
    float vel;
    float jumpForce;
} Duck;

Duck Duck_new();
void Duck_move();

#endif //DUCK_H
