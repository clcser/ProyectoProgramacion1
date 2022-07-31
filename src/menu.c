#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "menu.h"

static SDL_Surface *lose_menu= NULL;

Menu Menu_fail(){
	Menu menu;
	lose_menu = IMG_Load("../assets/game_over.png");
	
	menu.lose_menu = lose_menu;
	menu.position.x = 0;
	menu.position.y = 0;
	menu.position.w = 768;
	menu.position.h = 768;
	
	return menu;

}

