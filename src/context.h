#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 768

extern SDL_Window *window;
extern TTF_Font *font;
extern FILE *scores;

int Context_init();

void Context_quit();

#endif //CONTEXT_H

