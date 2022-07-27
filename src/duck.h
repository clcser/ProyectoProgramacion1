#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Surface *image[6];
    SDL_Rect position;
    float vel;
    float jumpForce;
} Duck;

Duck Duck_new();
void Duck_move(Duck *duck, int *jump, int count, int *costume);

#endif //DUCK_H
