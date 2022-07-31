#include "audio.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


Music Music_new(){
	Music music;
	music.audio = Mix_LoadMUS("../audio/inGame.mp3");
	
	return music;
}

Sound Sound_effect(){
	Sound sound;
	sound.effect = Mix_LoadWAV("../audio/collision.wav");
	
	return sound;
}

void quit_Sound(Sound sound){
	Mix_FreeChunk(sound.effect);
	sound.effect = NULL;
	
	Mix_Quit;
}

void quit_Audio(Music music){
	Mix_FreeMusic(music.audio);	//liberamos la musica
	
	music.audio = NULL;
	
	
	Mix_Quit();	//Cerrar la musica
}
