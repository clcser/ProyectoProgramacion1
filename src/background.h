#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Surface *image[2];
    SDL_Rect position;
    float vel;
} Background;

Background Background_new();

void Background_move();

#endif //BACKGROUND_H
