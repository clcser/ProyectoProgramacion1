#include <SDL2/SDL.h>
#include <stdint.h>
#include "game.h"
#include "duck.h"
#include "pipeline.h"
#include "background.h"
#include "context.h"

#define MS_PER_TICK 10

int running = 1, count = 0, jump = 0;

uint32_t last_tick = 0;

Game Game_new() {
    Game game;
    game.screen_surface = SDL_GetWindowSurface(window);
    game.duck = Duck_new();
    game.background[0] = Background_new();
    for(int i = 0; i < PIPE_NUMBER; i++) {
        game.pipeline[i] = Pipeline_new(i);    
    }
    last_tick = SDL_GetTicks();
    return game;
}

void Game_draw(Game game, int costume) {
    SDL_FillRect(game.screen_surface, NULL, SDL_MapRGB(game.screen_surface->format, 255, 255, 255));
    SDL_BlitSurface(game.background[0].image, &game.background[0].position, game.screen_surface, NULL);
    // SDL_BlitSurface(game.background[1].image, NULL, game.screen_surface, &game.background[1].position);    
    for(int i = 0; i < PIPE_NUMBER; i++) {
        SDL_Rect dest = game.pipeline[i].upper.position;
        dest.y -= game.pipeline[i].upper.image->h;
        SDL_BlitScaled(game.pipeline[i].upper.image, NULL, game.screen_surface, &dest);
        SDL_BlitScaled(game.pipeline[i].lower.image, NULL, game.screen_surface, &game.pipeline[i].lower.position);
    }
    SDL_BlitScaled(game.duck.image[costume], NULL, game.screen_surface, &game.duck.position);
    SDL_UpdateWindowSurface(window);
}

int Game_update_state(Game *game) {
    if(last_tick + MS_PER_TICK >= SDL_GetTicks()) {
        printf("Skipped tick %d\n", SDL_GetTicks());
        return 2;
    }
    SDL_Event event;
    int costume = (rand()%5)*2;
    int default_costume = costume;
    //uint32_t ticks_start = SDL_GetTicks();
    // obtener input
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYUP:
                costume = default_costume;
                break;             
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        running = 0;
                        break;
                    case SDLK_SPACE:
                        costume++;
                        if(event.key.repeat == 0)
                            jump = 1;
                        break;
                    default:
                        break;
                }
        }
    }

    // actualizar variables
    //count++;

    if(count % 4 == 0 || 1) {
        Duck_move(&game->duck, &jump, count);
    }
    for(int i = 0; i < PIPE_NUMBER; i++) {
        if(count % 2 == 0 || 1) {
            Pipeline_move(&game->pipeline[i]);
            Game_manage_collissions(&game->duck, &game->pipeline[i]);
        }
    }

    if(count % 10 == 0 || 1){
        Background_move(&game->background[0]);
    }
    //printf("%d\n", count);
    last_tick = SDL_GetTicks();
    return running;
}

//void optionsMenu();
//void runGame();

void Game_manage_collissions(Duck *duck, Pipeline *pipeline) {
    bool collission;
    if(duck->position.x + duck->position.w < pipeline->upper.position.x + pipeline->upper.position.w
    && duck->position.x + duck->position.w > pipeline->upper.position.x) {
        if(duck->position.y < pipeline->center - separation_y/2 
        || duck->position.y + duck->position.h > pipeline->center + separation_y/2) {
            collission = true;
            printf("collision!\n");
        }
    }
}

void Game_delete(Game game) {
    SDL_FreeSurface(game.pipeline->upper.image);
    SDL_FreeSurface(game.pipeline->lower.image);
    SDL_FreeSurface(game.background->image);
    for(int i=0; i<8; ++i){
        SDL_FreeSurface(game.duck.image[i]);
    }
    SDL_FreeSurface(game.screen_surface);

}
