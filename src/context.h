#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 768

extern SDL_Window *window;

int Context_init();

void Context_quit();

//void print_text(const char *text, SDL_Rect rect, float scale, SDL_Color color);

#endif //CONTEXT_H
