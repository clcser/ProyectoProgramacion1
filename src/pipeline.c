#include "pipeline.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCALE 2

static SDL_Surface *pipeline_upper_surface = NULL;
static SDL_Surface *pipeline_lower_surface = NULL;

Pipeline Pipeline_new() {
    Pipeline pipeline;

    pipeline.center = rand() % 620 + 40; // centro de las tuberias (al azar)
    
    if (pipeline_upper_surface == NULL) {
        pipeline_upper_surface = IMG_Load("../assets/pipelineup.png");
    }
    pipeline.upper.image = pipeline_upper_surface;    

    pipeline.upper.position.h = pipeline_upper_surface->h * 4;
    pipeline.upper.position.w = pipeline_upper_surface->w * 4;     
    pipeline.upper.position.y = 20-pipeline.center;
    pipeline.upper.position.x = 720;
   

    if (pipeline_lower_surface == NULL) {
        pipeline_lower_surface = IMG_Load("../assets/pipelinelow.png");
    }
    pipeline.lower.image = pipeline_lower_surface;    

    pipeline.lower.position.h = pipeline_lower_surface->h * 4;
    pipeline.lower.position.w = pipeline_lower_surface->w * 4;     
    pipeline.lower.position.y = 700-pipeline.center;
    pipeline.lower.position.x = 720;

    return pipeline;
}
/*
void Pipeline_move() {
    for(int i = 0; i < PIPE_NUMBER; i++) {
        pipeline[i].upper.position.x--;
        pipeline[i].upper.position.x--;
    }
}*/
void Pipeline_respawn(Pipeline *pipeline) {
    pipeline[i].center = rand() % 600 + 40;            
    pipeline[i].upper.position.x = pipeline[i].lower.position.x = 720;
}
/*
bool colision(SDL_Rect *pato, struct tubo *tubo) {
    if(pato->y < tubo->center-120 || (pato->y + pato->h) > tubo->center+120)
        return 1;
    return 0;
}

funcion(SDL_Rect *rect, int d)
    rect->h = rand() % 680 + 20;
    rect->y = 0;
    rect->x = 100 + 50*d;
    rect->w = 100;
*/
