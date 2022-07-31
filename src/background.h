
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Surface *image[3];
    SDL_Rect position;
} Background;

Background Background_new();

void Background_move();

typedef struct {
    SDL_Surface *lose_menu;
    SDL_Rect position;

}Menu;

Menu Menu_fail();

#endif //BACKGROUND_H
