#include "audio.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


Music Music_new(){
	Music music;
	music.audio = Mix_LoadMUS("../audio/inGame.mp3");
	music.start = Mix_LoadMUS("../audio/mainMenu.mp3");
	return music;
}

void quit_Audio(Music music){
	Mix_FreeMusic(music.audio);	//liberamos la musica
	Mix_FreeMusic(music.start);
	music.audio = NULL;
	music.start = NULL;
	Mix_Quit();	//Cerrar la musica
}
