#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include "audio.h"
#include "context.h"
#include "finalscore.h"
#include "game.h"

int run_score = 1;

Final_score Final_score_new(){
	Final_score final_score;
	final_score.screen_surface3 = SDL_GetWindowSurface(window);
	final_score.score_table = IMG_Load("../assets/final_score.png");

	final_score.position.x = 0;
	final_score.position.y = 0;
	final_score.position.w = 768;
	final_score.position.h = 768;

	return final_score;
}

void Final_score_draw(Final_score final_score, Game game, SDL_Surface *background, SDL_Rect position){
	SDL_FillRect(final_score.screen_surface3, NULL, SDL_MapRGB(final_score.screen_surface3->format, 255, 255, 255));
    SDL_BlitSurface(background, &position, final_score.screen_surface3, NULL);
    SDL_BlitSurface(final_score.score_table, &final_score.position, final_score.screen_surface3, NULL);

    char *actual_score, *best_score;
    
    actual_score = malloc(10);
    best_score = malloc(10);
    
    actual_score = itoa(score, actual_score, 10);
    best_score = itoa(game.best_score, best_score, 10);
    //printf("%s\n",actual_score)
    struct SDL_Rect r1 = {410,335,15,20};
    struct SDL_Rect r2 = {410,400,20,20};
    struct SDL_Color c = {245, 200, 255, 0xFF};
    Game_print_text(game, actual_score, r1, 10.0, c);
    Game_print_text(game, best_score , r2, 10.0, c);
    free(actual_score);
    free(best_score);

    SDL_UpdateWindowSurface(window);
}

int Final_score_state(Final_score *final_score){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                run_score = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_q:
                        run_score = 0;
                        break;               
                }
        }
    }

    return run_score;
}

void Final_score_delete(Final_score final_score){
    SDL_FreeSurface(final_score.score_table);
}
