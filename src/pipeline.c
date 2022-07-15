#include "pipeline.h"

bool colision(SDL_Rect *pato, struct tubo *tubo) {
    if(pato->y < tubo->center-120 || (pato->y + pato->h) > tubo->center+120)
        return 1;
    return 0;
}

struct pipeline newPipeline(SDL_Rect *rect, int d) {
    rect->h = rand() % 680 + 20;
    rect->y = 0;
    rect->x = 100 + 50*d;
    rect->w = 100;

}
