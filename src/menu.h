#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    SDL_Surface *lose_menu;
    SDL_Rect position;

}Menu;

Menu Menu_fail();

#endif //MENU_H
