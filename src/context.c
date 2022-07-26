// funciones relacionadas al contexto de SDL

#include "context.h"
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

SDL_Window *window = NULL;

// inicializa SDL
int Context_init() {
    srand(time(0)); // cambiar semilla
    const unsigned char* key;
	key = SDL_GetKeyboardState(NULL);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) { // inicia SDL
        printf("Error al inicializar SDL\n");
        return EXIT_FAILURE;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) { // inicia SDL_image
        printf("Error al iniciar SDL_image\n");
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("FlappyDuck", // crea la ventana
                              SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, 
                              WINDOW_WIDTH, 
                              WINDOW_HEIGHT, 
                              0);

    if (window == NULL) { // handle error
        printf("Error al crear la ventana\n");
        SDL_Quit();
        return EXIT_FAILURE;
    }

}

// matar todo y cerrar el programa
void Context_quit() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void print_text(const char *text, SDL_Rect rect, float scale, SDL_Color color) {

}


