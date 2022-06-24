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

    SDL_Surface *logo = IMG_Load("../assets/pato1.png");
    SDL_Surface *fondo = IMG_Load("../assets/grass.png");

    int running = 1, count = 0, pos_y = 50;
    float gravedad = 0.5;
    bool puede_saltar = true;
    SDL_Event event;

    SDL_Rect destino;
    
    destino.x = 40;
    destino.y = 100;
    destino.w = 70;
    destino.h = 70;

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
                                destino.y -= 50;
                                gravedad = -0.6;
                            }
                            break;
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
        if(count%8==0 && destino.y < 650) {  //para que no se mueva constantemente
            destino.y += gravedad;
            gravedad += 0.1;
        }

        SDL_BlitScaled(logo,NULL,screen_surface,&destino);
        // dibujar
        SDL_UpdateWindowSurface(window);
        }

    SDL_FreeSurface(fondo);
    SDL_FreeSurface(logo);
    SDL_FreeSurface(screen_surface);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
