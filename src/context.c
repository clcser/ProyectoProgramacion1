// funciones relacionadas al contexto de SDL

#include "context.h"
#include "audio.h"
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

SDL_Window *window = NULL;
TTF_Font *font;
FILE *scores;

// inicializa SDL
int Context_init() {
    srand(time(0)); // cambiar semilla
    const unsigned char* key;
	key = SDL_GetKeyboardState(NULL);
	
     if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1 )
     {
        printf( "Error al inicializar SDL_mixer\n");
        return EXIT_FAILURE;
     }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) { // inicia SDL
        printf("Error al inicializar SDL\n");
        return EXIT_FAILURE;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) { // inicia SDL_image
        printf("Error al iniciar SDL_image\n");
        return EXIT_FAILURE;
    }
    
    if (TTF_Init() != 0) {
        printf("Error al iniciar SDL_ttf\n");
        return EXIT_FAILURE;
    }

    font = TTF_OpenFont("../assets/font.ttf", 16); // carga la font
    if (font == NULL)
        printf("Error al abrir font\n");

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

    scores = fopen("scores.txt", "r+");
    if (!scores) {
        printf("Error abriendo archivo\n");
        return EXIT_FAILURE;
    }

}

// cerrar todo
void Context_quit() {
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

