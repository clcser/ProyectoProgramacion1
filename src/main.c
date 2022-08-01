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

int main(int argc, char *argv[]) {
    Context_init();
    Game game = Game_new(); 
    while(Game_update_state(&game))
        Game_draw(game, 0);
    //Game_main_loop(game);
    Game_delete(game);
    Context_quit();

    return 0;
}

