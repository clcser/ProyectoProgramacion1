#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

const int SCREEN_WIDTH = 720;	
const int SCREEN_HEIGHT = 720;

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    const unsigned char* key;
	key = SDL_GetKeyboardState(NULL);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error al inicializar SDL\n");
        return 1;
    }

    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }

    window = SDL_CreateWindow("Titulo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL) {
        printf("Error al crear la ventana\n");
        return 1;
    }
    SDL_Surface *screen_surface = SDL_GetWindowSurface(window);

    SDL_Surface *duck = IMG_Load("../assets/pato1.png");
    SDL_Surface *fondo = IMG_Load("../assets/grass.png");
    SDL_Surface *pipeline = IMG_Load("../assets/pipeline.png");

    int running = 1, count = 0, pos_y = 50;
    float gravedad = 0.5;
    bool puede_saltar = true;
    SDL_Event event;

    SDL_Rect pato;   
    pato.x = 40;
    pato.y = 100;
    pato.w = 100;
    pato.h = 100;

    SDL_Rect tuberia;
    tuberia.x = 550;
	tuberia.y = 0;
	tuberia.w = 100;
    tuberia.h = 280;

    while (running) {
        // procesar eventos
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            running = 0;
                            break;
                        case SDLK_SPACE:
                            if(event.key.repeat == 0) {
                                if(pato.y-50 < 0){
                                    pato.y = 0;
                                }
                                else{
                                    pato.y -= 70;
                                    gravedad = -0.6;
                                }
                            break;
                            }
                        default:
                            break;
                    }
                    break;
            }
        }

        // limpia la pantalla
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255, 255, 255));
 
        // imprimir fondo
        SDL_BlitSurface(fondo,NULL,screen_surface, NULL); 
        
        count ++;
        if(count%8==0 && pato.y < 620) {  //para que no se mueva constantemente
            tuberia.x--;
            pato.y += gravedad;
            gravedad += 0.1;
        }

        if(tuberia.x < -100)
            tuberia.x = 620;

        SDL_BlitScaled(pipeline, NULL, screen_surface, &tuberia);
        SDL_BlitScaled(duck,NULL,screen_surface,&pato);
        // dibujar
        SDL_UpdateWindowSurface(window);
        }

    SDL_FreeSurface(pipeline);
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(duck);
    SDL_FreeSurface(screen_surface);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
