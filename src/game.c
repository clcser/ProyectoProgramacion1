#include <SDL2/SDL.h>
#include <stdint.h>
#include "game.h"
#include "duck.h"
#include "audio.h"
#include "pipeline.h"
#include "background.h"
#include "context.h"

#define MS_PER_TICK 10

unsigned int lastTime = 0;
unsigned int currentTime;

int running = 1, count = 0, jump = 0;

uint32_t last_tick = 0;

Game Game_new() {
    Game game;
    game.screen_surface = SDL_GetWindowSurface(window);
    game.duck = Duck_new();
    game.costume = (rand()%4)*2;
    game.background[0] = Background_new();
    game.music = Music_new();
    game.menu[0]= Menu_fail(); 
    for(int i = 0; i < PIPE_NUMBER; i++) {
        game.pipeline[i] = Pipeline_new(i);  
    }
    last_tick = SDL_GetTicks();
    return game;
}
    bool collision;
int Game_manage_collissions(Duck *duck, Pipeline *pipeline) {
    if(duck->position.x + duck->position.w < pipeline->upper.position.x + pipeline->upper.position.w
    && duck->position.x + duck->position.w > pipeline->upper.position.x) {
        if(duck->position.y < pipeline->center - separation_y/2 
        || duck->position.y + duck->position.h > pipeline->center + separation_y/2) {
             collision=true;
   	     return 1;
        }
    }
}

void Game_draw(Game game, int costume) {
    printf("DRAW_S: %d\n", SDL_GetTicks());
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
        if(collision==true){
    SDL_BlitSurface(game.menu[0].lose_menu, &game.menu[0].position, game.screen_surface, NULL);
    running=0;}
    
    SDL_UpdateWindowSurface(window);
}


int Game_update_state(Game *game) {
    if(last_tick + MS_PER_TICK >= SDL_GetTicks()) {
        return 2;
    }
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                running = 0;
                break;           
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_m:
                	 	if(!Mix_PlayingMusic()){
                    	 	Mix_PlayMusic(game->music.audio, -1);
                    		
                     	}else if(Mix_PausedMusic()){
                	 		Mix_ResumeMusic();
                	 	
                	 	}else{
                	 		Mix_PausedMusic();	
                    	 	
                	 	}
                        break;

                    case SDLK_s:
                        Mix_HaltMusic();
                        break;
                    
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        running = 0;
                        break;
                    case SDLK_SPACE:
                        if(event.key.repeat == 0)
                            jump = 1;
                        break;
                    default:
                        break;
                }
        }
    }

    // actualizar variables

    currentTime = SDL_GetTicks();
    if(currentTime > lastTime + 100){
        if(game->costume % 2 == 0){
            game->costume++;
        }
        else{
            game->costume--;
        }
        lastTime = currentTime;
    }


    Duck_move(&game->duck, &jump, count);
    
    for(int i = 0; i < PIPE_NUMBER; i++) {
        Pipeline_move(&game->pipeline[i]);
        Game_manage_collissions(&game->duck, &game->pipeline[i]);
    }

    Background_move(&game->background[0]);

    //printf("%d\n", count);
    last_tick = SDL_GetTicks();
    return running;
}

//void optionsMenu();
//void runGame();



void Game_delete(Game game) {
    quit_Audio(game.music);
    SDL_FreeSurface(game.menu->lose_menu);
    SDL_FreeSurface(game.pipeline->upper.image);
    SDL_FreeSurface(game.pipeline->lower.image);
    SDL_FreeSurface(game.background->image);
    for(int i=0; i<8; ++i){
        SDL_FreeSurface(game.duck.image[i]);
    }
    SDL_FreeSurface(game.screen_surface);

}
