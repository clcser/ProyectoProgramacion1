#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    float vel;
    float jumpForce;
} Duck;

Duck Duck_new();
void Duck_move();
void Duck_detect_collission();

#endif //DUCK_H

