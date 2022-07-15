#ifndef PIPELINE_H
#define PIPELINE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

struct tubo {
    int center;
    int pos;
};

bool colision(SDL_Rect *pato, struct tubo * tubo);
void newPipieline(SDL_Rect *rect, int d);

#endif //PIPELINE_H
