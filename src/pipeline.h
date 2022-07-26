#ifndef PIPELINE_H
#define PIPELINE_H

#define PIPE_SPEED 1
#define PIPE_NUMBER 3
#include <stdbool.h>
#include <SDL2/SDL.h>

struct pipe {
    SDL_Rect position;
    SDL_Surface *image;
};

typedef struct {
    int center;
    struct pipe upper;
    struct pipe lower;
} Pipeline;


Pipeline Pipeline_new(int separacion);

void Pipeline_move(Pipeline *pipeline);

void Pipeline_respawn(Pipeline *pipeline);

#endif //PIPELINE_H
