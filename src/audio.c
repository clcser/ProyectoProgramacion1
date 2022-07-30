#include "audio.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


Music Music_new(){
	Music music;
	music.audio = Mix_LoadMUS("../audio/inGame.mp3");
}

void quit_Audio(Game *game)
{
	Mix_FreeMusic(game->music.audio);	//liberamos la musica
	game->music.audio = NULL;
	
	Mix_Quit();	//Cerrar la musica

}

