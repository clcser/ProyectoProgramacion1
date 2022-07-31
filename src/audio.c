#include "audio.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


Music Music_new(){
	Music music;
	music.audio = Mix_LoadMUS("../audio/inGame.mp3");
//	music.effect = Mix_LoadWAV("../audio/collision.wav");
}



void quit_Audio(Game *game)
{
	Mix_FreeMusic(game->music.audio);	//liberamos la musica
//	Mix_FreeChunk(game->music.effect);
	game->music.audio = NULL;
//	game->music.effect = NULL;
	
	Mix_Quit();	//Cerrar la musica

}

