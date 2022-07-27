#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <time.h>
#define SCALE 2
#define SEPARATION 50




extern int running,count;

typedef struct {
    Duck duck;
    Background background[2];
    Pipeline pipeline[PIPE_NUMBER];
    SDL_Surface *screen_surface;
} Game;

Game Game_new();

void Game_draw(Game game);

void Game_main_loop(Game game);

void Game_manage_collissions(Game game);

void Game_delete(Game game);

int running = 1, count = 0;

Game Game_new() {
    Game game;
    game.screen_surface = SDL_GetWindowSurface(window);
    game.duck = Duck_new();
    game.background[0] = Background_new();
    game.background[1] = Background_new();
    for(int i = 0; i < PIPE_NUMBER; i++) {
        game.pipeline[i] = Pipeline_new();
    }
    return game;
}

void Game_draw(Game game) {
    SDL_FillRect(game.screen_surface, NULL, SDL_MapRGB(game.screen_surface->format, 255, 255, 255));
    SDL_BlitSurface(game.background[0].image, NULL, game.screen_surface, NULL);
    SDL_BlitSurface(game.background[1].image, NULL, game.screen_surface, NULL);
    for(int i = 0; i < PIPE_NUMBER; i++) {
        SDL_Rect dest = game.pipeline[i].upper.position;
        dest.y -= game.pipeline[i].upper.image->h;
        SDL_BlitScaled(game.pipeline[i].upper.image, NULL, game.screen_surface, &dest);
        SDL_BlitScaled(game.pipeline[i].lower.image, NULL, game.screen_surface, &game.pipeline[i].lower.position);
    }
    SDL_BlitScaled(game.duck.image, NULL, game.screen_surface, &game.duck.position);
    SDL_UpdateWindowSurface(window);
}

void Game_main_loop(Game game) {
    SDL_Event event;

    while (running) {
        // obtener input
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
                                if(game.duck.position.y-50 < 0){
                                    game.duck.position.y = 0;
                                }
                                else{
                                    game.duck.position.y -= 70;
                                    game.duck.vel = -0.6;
                                }
                            }
                            break;
                        default:
                            break;
                    }
            }
        }

        // actualizar variables
        count ++;
        if(game.duck.position.y < 620 && count%5==0) {  //para que no se mueva constantemente
            game.duck.position.y += game.duck.vel;
            game.duck.vel += 0.1;
        }

        if(count % 4 == 0){
            //game.pipeline->upper.position.x--;
            //game.pipeline->lower.position.x--;
        }

        if(game.duck.position.y < 0)
            game.duck.position.y = 0;

        for(int i = 0; i < PIPE_NUMBER; i++) {
            //if(game.pipeline[i].upper.position.x < -100 || game.pipeline[i].lower.position.x < -100)
            //    Pipeline_respawn(game.pipeline[i]);
            Pipeline_move(&game.pipeline[i]);
        }

        // dibujar
        Game_draw(game);
    }
}

//void optionsMenu();
//void runGame();

void Game_manage_collissions(Game game) {

}

void Game_delete(Game game) {
    SDL_FreeSurface(game.pipeline->upper.image);
    SDL_FreeSurface(game.pipeline->lower.image);
    SDL_FreeSurface(game.background->image);
    SDL_FreeSurface(game.duck.image);
    SDL_FreeSurface(game.screen_surface);

}

typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    float vel;
    float jumpForce;
} Duck;

Duck Duck_new();
void Duck_move();
void Duck_detect_collission();

Duck Duck_new() { //hacer que tenga de parametro una imagen
    Duck duck;

    duck.image = IMG_Load("../assets/duck.png");

    duck.position.x = 40;
    duck.position.y = 100;
    duck.position.w = 60;
    duck.position.h = 60;

    return duck;
}

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

void Pipeline_move(Pipeline *pipeline) {
    pipeline->upper.position.x--;
    pipeline->lower.position.x--;
    //pipeline->center--;

    if (pipeline->upper.position.x < -100) {
        Pipeline_respawn(pipeline);
    }
}
void Pipeline_respawn(Pipeline *pipeline) {
    pipeline->center = rand() % 600 + 40;
    pipeline->upper.position.x = pipeline->lower.position.x = 720;
    pipeline->upper.position.y = pipeline->center + SEPARATION / 2;
    pipeline->lower.position.y = pipeline->center - SEPARATION / 2;
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



int main(int argc, char *argv[]) {
    Context_init();

    Game game = Game_new();
    Game_main_loop(game);

    Game_delete(game);
    Context_quit();

    return 0;
}



/*
void generar_tuberia(SDL_Rect* rect, int i){
    rect->h= rand()%720;
    rect->y = 0;
    rect->x= 100 + 50*i;
    rect->w= 100;
}

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

int main(int argc, char *argv[]) {
    srand(time(0));
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

    SDL_Surface *duck = IMG_Load("../folder/pato1.png");
    SDL_Surface *fondo = IMG_Load("../folder/grass.png");
    SDL_Surface *pipeline = IMG_Load("../folder/pipeline.png");

    int running = 1, count = 0, pos_y = 50;
    float gravedad = 0.5;
    bool puede_saltar = true;
    SDL_Event event;

    SDL_Rect pato;
    pato.x = 40;
    pato.y = 100;
    pato.w = 80;
    pato.h = 80;

    SDL_Rect tuberia;
    tuberia.x = 550;
	tuberia.y = 0;
	tuberia.w = 100;
    tuberia.h = 280;
    generar_tuberia(&tuberia, 4);

    while (running)
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

                            }
                            break;
                        default:
                            break;
                    }
                    //break;
            }
        }

        // limpia la pantalla
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255, 255, 255));

        // imprimir fondo
        SDL_BlitSurface(fondo,NULL,screen_surface, NULL);

        count ++;
        if(pato.y < 620 && count%5==0) {  //para que no se mueva constantemente

            pato.y += gravedad;
            gravedad += 0.1;
        }
        if(count%5==0)tuberia.x--;

        if(pato.y<0){
            pato.y=0;

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
*/
