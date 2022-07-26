#ifndef GAME_H
#define GAME_H

#include "duck.h"
#include "pipeline.h"
#include "background.h"

extern int running,count,separation_y;

typedef struct {
    Duck duck;
    Background background[2];
    Pipeline pipeline[PIPE_NUMBER];
    SDL_Surface *screen_surface;
} Game;

Game Game_new();

void Game_draw(Game game, int costume);

void Game_main_loop(Game game);

void Game_manage_collissions(Duck *duck, Pipeline *pipeline);

void Game_delete(Game game);

#endif //GAME_H
