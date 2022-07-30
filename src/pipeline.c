#include "pipeline.h"
#include "context.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCALE 2

int separation_y = 150;

static SDL_Surface *pipeline_upper_surface = NULL;
static SDL_Surface *pipeline_lower_surface = NULL;

Pipeline Pipeline_new(int separation_x) {
    Pipeline pipeline;

    pipeline.center = rand() % 400 + 200; // centro de las tuberias (al azar)
    
    if (pipeline_upper_surface == NULL) {
        pipeline_upper_surface = IMG_Load("../assets/pipelineup.png");
    }
    pipeline.upper.image = pipeline_upper_surface;    

    pipeline.upper.position.h = pipeline_upper_surface->h * 4;
    pipeline.upper.position.w = pipeline_upper_surface->w * 4;     
    pipeline.upper.position.y = pipeline.center - separation_y / 2 - 548; // 548 := medida de la tuberia (87*4) + 200 de margen del rand
    pipeline.upper.position.x = WINDOW_WIDTH + 270*separation_x; 

    if (pipeline_lower_surface == NULL) {
        pipeline_lower_surface = IMG_Load("../assets/pipelinelow.png");
    }
    pipeline.lower.image = pipeline_lower_surface;    

    pipeline.lower.position.h = pipeline_lower_surface->h * 4;
    pipeline.lower.position.w = pipeline_lower_surface->w * 4;     
    pipeline.lower.position.y = pipeline.center + separation_y / 2;
    pipeline.lower.position.x = WINDOW_WIDTH + 270*separation_x;

    return pipeline;
}

void Pipeline_move(Pipeline *pipeline) {
    pipeline->upper.position.x -= 3;
    pipeline->lower.position.x -= 3;
    //pipeline->center--;

    if (pipeline->upper.position.x < -100) {
        Pipeline_respawn(pipeline);
    }
}
void Pipeline_respawn(Pipeline *pipeline) {
    pipeline->center = rand() % 400 + 200;
    pipeline->upper.position.x = pipeline->lower.position.x = WINDOW_WIDTH;
    pipeline->upper.position.y = pipeline->center - separation_y / 2 - 548; // medida de la tuberia (87 * 4) + 200 de margen del rand
    pipeline->lower.position.y = pipeline->center + separation_y / 2;
}

