#include <SDL2/SDL.h>
#include "game.h"
#include "duck.h"
#include "pipeline.h"
#include "background.h"
#include "context.h"

int running = 1, count = 0, jump = 0;

Game Game_new() {
    Game game;
    game.screen_surface = SDL_GetWindowSurface(window);
    game.duck = Duck_new();
    game.background[0] = Background_new();
    game.background[1] = Background_new();
    for(int i = 0; i < PIPE_NUMBER; i++) {
        game.pipeline[i] = Pipeline_new(i);    
    }
    return game;
}

void Game_draw(Game game, int costume) {
    SDL_FillRect(game.screen_surface, NULL, SDL_MapRGB(game.screen_surface->format, 255, 255, 255));
    SDL_BlitSurface(game.background[0].image, NULL, game.screen_surface, NULL);
    SDL_BlitSurface(game.background[1].image, NULL, game.screen_surface, NULL);    
    for(int i = 0; i < PIPE_NUMBER; i++) {
        SDL_Rect dest = game.pipeline[i].upper.position;
        dest.y -= game.pipeline[i].upper.image->h;
        SDL_BlitScaled(game.pipeline[i].upper.image, NULL, game.screen_surface, &dest);
        SDL_BlitScaled(game.pipeline[i].lower.image, NULL, game.screen_surface, &game.pipeline[i].lower.position);
    }    
    SDL_BlitScaled(game.duck.image[costume], NULL, game.screen_surface, &game.duck.position);
    SDL_UpdateWindowSurface(window);
}

void Game_main_loop(Game game) {
    SDL_Event event;
    int costume = 0;

    while (running) {
        
        // obtener input
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYUP:
                    costume = 0;
                    break;             
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            running = 0;
                            break;
                        case SDLK_SPACE:
                            costume = 1;
                            if(event.key.repeat == 0) {                           
                                if(game.duck.position.y-50 < 0){
                                    game.duck.position.y = 0;
                                }
                                else{
                                    game.duck.position.y -= 60;
                                    game.duck.vel = -0.6;
                                }
                            }    
                            if(event.key.repeat == 0) {
                                jump = 1;
                            }
                            break;
                        default:
                            break;
                    } 
                // default:
                   // break;  
            }
        }

        // actualizar variables
        count ++;

        if(count % 4 == 0) {
            Duck_move(&game.duck, &jump, count);
        }
        for(int i = 0; i < PIPE_NUMBER; i++) {
            if(count % 2 == 0) {
                Pipeline_move(&game.pipeline[i]);
                Game_manage_collissions(&game.duck, &game.pipeline[i]);
            }
        }
        
        // dibujar
        Game_draw(game, costume);
    }
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
    SDL_FreeSurface(game.duck.image[0]);
    SDL_FreeSurface(game.duck.image[1]);
    SDL_FreeSurface(game.screen_surface);

}