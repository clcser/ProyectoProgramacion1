#ifndef GAME_H
#define GAME_H

#include "duck.h"
#include "pipeline.h"
#include "background.h"
#include "audio.h"

extern int running,count,separation_y;

typedef struct {
    Duck duck;
    int costume;
    int timer;
    Background background[2];
    Pipeline pipeline[PIPE_NUMBER];
    SDL_Surface *screen_surface;
    Music music;
} Game;

Game Game_new();

void Game_draw(Game game, int costume);

int Game_update_state   (Game *game);

void Game_manage_collissions(Duck *duck, Pipeline *pipeline);

void Game_delete(Game game);

#endif //GAME_H
