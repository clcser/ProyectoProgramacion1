#ifndef STARTMENU_H
#define STARTMENU_H

#include "audio.h"

typedef struct {
    SDL_Surface *screen_surface2;
    SDL_Surface *menu_image[4];
    SDL_Rect position;
    int frame; 
} Start_menu;

Start_menu Start_menu_new();

void Start_menu_draw(Start_menu start_menu, int frame);

//void Start_menu_animation(Start_menu *start_menu);

int Start_menu_state(Start_menu *start_menu);

#endif //STARTMENU_H