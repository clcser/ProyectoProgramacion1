#include "audio.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


Music Music_new(){
	Music music;
	music.audio = Mix_LoadMUS("../audio/inGame.mp3");
	return music;
}

void quit_Audio(Music music){
	Mix_FreeMusic(music.audio);	//liberamos la musica
	music.audio = NULL;
	Mix_Quit();	//Cerrar la musica
}
