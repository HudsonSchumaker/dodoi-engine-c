/**
* @file sfx.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_sfx.h"

static Mix_Music* music = NULL;
static Mix_Chunk* sound = NULL;

void sfx_init(void) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "failed to init SDL2_mixer: %s.\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}
}

void sfx_load_music(const char* path) {
	music = Mix_LoadMUS(path);
	if (music == NULL) {
		fprintf(stderr, "failed to load music: %s.\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}
}

void sfx_load_sound(const char* path) {
	sound = Mix_LoadWAV(path);
	if (sound == NULL) {
		fprintf(stderr, "failed to load sound: %s.\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}
}

void sfx_play_music(void) {
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(music, -1);
	}
}

void sfx_play_sound(void) {
	Mix_PlayChannel(-1, sound, 0);
}

void sfx_stop_music(void) {
	Mix_HaltMusic();
}

void sfx_stop_sound(void) {
	Mix_HaltChannel(-1);
}

void sfx_close(void) {
	Mix_FreeMusic(music);
	Mix_FreeChunk(sound);
	Mix_CloseAudio();
	Mix_Quit();
}
