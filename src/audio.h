#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


/*enum audio {
    JUMP,
    WIN,
    LOSE
};

void play_audio(enum audio type);
	
*/

typedef struct {
	Mix_Music *audio;
    Mix_Music *start;
}Music;

Music Music_new();

void quit_Audio();

#endif
