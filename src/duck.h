#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL.h>
#define GRAVITY = 1

typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    float vel;
    float jumpForce;
} duck;

duck newDuck();
void duckMove();
void duckDetectCollission();

#endif //DUCK_H
