#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <time.h>
#include "game.h"
#include "context.h"
#include "startmenu.h"


int main(int argc, char *argv[]) {
    srand(time(0));
    Context_init();

    Music music = Music_new();

    Start_menu start_menu = Start_menu_new();
    Mix_PlayMusic(music.start, -1);
    while(Start_menu_state(&start_menu)){   // PENDIENTE HACER QUE CON Q SE SALGA DE TODO EL JUEGO Y NO SÓLO DEL MENÚ
        Start_menu_draw(start_menu, start_menu.frame);
    }
    Mix_HaltMusic();
     
    Game game = Game_new();
    Mix_PlayMusic(music.audio, -1);
    while(Game_update_state(&game)) 
        Game_draw(game, game.costume, game.scenery);
    Game_delete(game);
    Context_quit();
    return 0;
}