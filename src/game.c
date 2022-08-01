#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "duck.h"
#include "audio.h"
#include "pipeline.h"
#include "background.h"
#include "context.h"

#define MS_PER_TICK 10

unsigned int lastTime = 0;
unsigned int currentTime;

int running = 1, count = 0, jump = 0, collision = 0; //, score = 0;

uint32_t last_tick = 0;

/////// itoa: funcion para pasar de int a char //////

/**
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.

	 */
char* itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

//////// itoa /////////


Game Game_new() {
    Game game;
    game.screen_surface = SDL_GetWindowSurface(window);
    game.duck = Duck_new();
    game.costume = (rand()%4)*2;
    game.background = Background_new();
    game.scenery = (rand()%3);
    game.music = Music_new();
    for(int i = 0; i < PIPE_NUMBER; i++) {
        game.pipeline[i] = Pipeline_new(i);    
    }
    game.score = 0;
    last_tick = SDL_GetTicks();
    return game;
}

void Game_print_text(Game game, const char *text, struct SDL_Rect rect, float scale, struct SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL) {
        printf("no se pudo generar el texto\n");
        exit(1);
    }
    rect.w = surface->w * scale;
    rect.h = surface->h * scale;
    SDL_BlitSurface(surface, NULL, game.screen_surface, &rect);
    SDL_FreeSurface(surface);
}

void Game_draw(Game game, int costume, int scenery) {
   
    SDL_FillRect(game.screen_surface, NULL, SDL_MapRGB(game.screen_surface->format, 255, 255, 255));
    SDL_BlitSurface(game.background.image[scenery], &game.background.position, game.screen_surface, NULL);   
    for(int i = 0; i < PIPE_NUMBER; i++) {
        SDL_Rect dest = game.pipeline[i].upper.position;
        dest.y -= game.pipeline[i].upper.image->h;
        SDL_BlitScaled(game.pipeline[i].upper.image, NULL, game.screen_surface, &dest);
        SDL_BlitScaled(game.pipeline[i].lower.image, NULL, game.screen_surface, &game.pipeline[i].lower.position);
    }
    SDL_BlitScaled(game.duck.image[costume], NULL, game.screen_surface, &game.duck.position);
    
    char *str;
    str = malloc(10);
    str = itoa(game.score, str, 10);
    //printf("%s\n",str);
    struct SDL_Rect r = {384,50,15,20};
    struct SDL_Rect r1 = {380,50,20,20};
    struct SDL_Color c = {0xFF, 0xFF, 0xFF, 0xFF};
    SDL_FillRect(game.screen_surface, &r1, SDL_MapRGB(game.screen_surface->format, 0, 0, 0));
    Game_print_text(game, str, r, 10.0, c);
    free(str);

    SDL_UpdateWindowSurface(window);
}

int Game_update_state(Game *game) {
    if(last_tick + MS_PER_TICK >= SDL_GetTicks()) {
        //printf("Skipped tick %d\n", SDL_GetTicks());
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
                	 	if(!Mix_PlayingMusic()) {
                    	 	Mix_PlayMusic(game->music.audio, -1);
                    		
                     	} else if(Mix_PausedMusic()) {
                	 		Mix_ResumeMusic();
                	 	
                	 	} else {
                	 		Mix_PausedMusic();	
                	 	}
                        break;

                    case SDLK_s:
                        Mix_HaltMusic();
                        break;

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
        if(Game_manage_collisions(&game->duck, &game->pipeline[i])) {
            running = 0;
            break;
        }
        Game_score_counter(game, &game->pipeline[i]);
        //printf("%d PUNTOS \n", score);
   }

    Background_move(&game->background);

    last_tick = SDL_GetTicks();
    return running;
}

//void optionsMenu();
//void runGame();

int Game_manage_collisions(Duck *duck, Pipeline *pipeline) {
    if(duck->position.x + duck->position.w < pipeline->upper.position.x + pipeline->upper.position.w 
    && duck->position.x + duck->position.w > pipeline->upper.position.x) { //colisiones en el eje x
        if(duck->position.y < pipeline->center - separation_y/2 - 11
        || duck->position.y + duck->position.h > pipeline->center + separation_y/2) { // colisiones en el eje y
            //printf("collision!\n");
            return 1;
        } 
    }
    return 0;
}

void Game_score_counter(Game *game, Pipeline *pipeline) {
    if(pipeline->lower.position.x + pipeline->lower.position.w == 59) {
        game->score++;
        printf("%d \n", game->score);
    }
}

void Game_delete(Game game) {
    quit_Audio(game.music);
    SDL_FreeSurface(game.pipeline->upper.image);
    SDL_FreeSurface(game.pipeline->lower.image);
    for(int i=0; i<3; ++i) {
       SDL_FreeSurface(game.background.image[i]); 
    }
    for(int i=0; i<8; ++i) {
        SDL_FreeSurface(game.duck.image[i]);
    }
    SDL_FreeSurface(game.screen_surface);
}
