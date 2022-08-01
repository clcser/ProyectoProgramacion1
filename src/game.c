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

int running = 1, count = 0, jump = 0, score = 0;
uint32_t last_tick = 0;

///// itoa //////

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
    game.background[0] = Background_new();
    game.music = Music_new();
    for(int i = 0; i < PIPE_NUMBER; i++) {
        game.pipeline[i] = Pipeline_new(i);    
    }
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
    SDL_BlitScaled(surface, NULL, game.screen_surface, &rect);
    SDL_FreeSurface(surface);
}

void Game_draw(Game game, int costume) {
    //printf("DRAW_S: %d\n", SDL_GetTicks());
    SDL_FillRect(game.screen_surface, NULL, SDL_MapRGB(game.screen_surface->format, 255, 255, 255));
    SDL_BlitSurface(game.background[0].image, &game.background[0].position, game.screen_surface, NULL); 
    for(int i = 0; i < PIPE_NUMBER; i++) {
        SDL_Rect dest = game.pipeline[i].upper.position;
        dest.y -= game.pipeline[i].upper.image->h;
        SDL_BlitScaled(game.pipeline[i].upper.image, NULL, game.screen_surface, &dest);
        SDL_BlitScaled(game.pipeline[i].lower.image, NULL, game.screen_surface, &game.pipeline[i].lower.position);
    }
    SDL_BlitScaled(game.duck.image[costume], NULL, game.screen_surface, &game.duck.position);
    char *str;
    str = malloc(10);
    str = itoa(score, str, 10);
    //printf("%s\n",str);
    struct SDL_Rect r = {100,100,100,100};
    struct SDL_Color c = {0xFF, 0xFF, 0xFF, 0xFF};
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
    int costume = (rand()%5)*2;
    int default_costume = costume;

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
                    
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        running = 0;
                        break;
                    case SDLK_SPACE:
                        costume++;
                        if(costume >= 9) {
                        	costume = 0;
                        }
                        if(event.key.repeat == 0)
                            jump = 1;
                        break;
                    default:
                        break;
                }
        }
    }

    //Context_print_text(":)", (SDL_Rect) {10,10}, 3, (SDL_Color) {255,255,255});

    // actualizar variables

    Duck_move(&game->duck, &jump, count);
    
    for(int i = 0; i < PIPE_NUMBER; i++) {
        Pipeline_move(&game->pipeline[i]);
        if(Game_manage_collissions(&game->duck, &game->pipeline[i])){
            running = 0;
        }
        Game_score_counter(&game->pipeline[i]);
        printf("%d PUNTOS \n", score);
    }

    Background_move(&game->background[0]);

    //printf("%d\n", count);
    last_tick = SDL_GetTicks();
    return running;
}

//void optionsMenu();
//void runGame();

int Game_manage_collissions(Duck *duck, Pipeline *pipeline) {
    if(duck->position.x + duck->position.w < pipeline->upper.position.x + pipeline->upper.position.w 
    && duck->position.x + duck->position.w > pipeline->upper.position.x) { //colisiones en el eje x
        if(duck->position.y < pipeline->center - separation_y/2 - 11
        || duck->position.y + duck->position.h > pipeline->center + separation_y/2) { // colisiones en el eje y
            printf("collision!\n");
            return 1;
        } 
    }
    return 0;
}

void Game_score_counter(Pipeline *pipeline) {
    if(pipeline->lower.position.x + pipeline->lower.position.w == 59) {
        score++;
    }
}

void Game_delete(Game game) {
    quit_Audio(game);
    SDL_FreeSurface(game.pipeline->upper.image);
    SDL_FreeSurface(game.pipeline->lower.image);
    SDL_FreeSurface(game.background->image);
    for(int i = 0; i < 8; ++i) {
        SDL_FreeSurface(game.duck.image[i]);
    }
    SDL_FreeSurface(game.screen_surface);

}
