#ifndef FINALSCORE_H
#define FINALSCORE_H

typedef struct{
	SDL_Surface *screen_surface3;
    SDL_Surface *score_table;
    SDL_Rect position;
} Final_score;

Final_score Final_score_new();

void Final_score_draw(Final_score final_score, SDL_Surface *background, SDL_Rect position);

int Final_score_state(Final_score *final_score);

void Final_score_delete(Final_score final_score);

#endif //FINALSCORE_H