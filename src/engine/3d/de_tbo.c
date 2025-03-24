/**
* @file de_tbo.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_buffer.h"
void tbo_flip_surface(SDL_Surface* surface);

tbo_t* tbo_new(void) {
	tbo_t* tbo = (tbo_t*)malloc(sizeof(tbo_t));
	if (tbo == NULL) {
		fprintf(stderr, "failed to allocate memory for tbo.\n");
		exit(EXIT_FAILURE);
	}
	return tbo;
}

void tbo_init(tbo_t* tbo, const char* path) {
	tbo->path = (char*)path;
	tbo->width = 0;
	tbo->height = 0;
	tbo->channels = 0;
	glGenTextures(1, &tbo->id);
}

void tbo_bind(tbo_t* tbo) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tbo->id);
}

bool tbo_load(tbo_t* tbo) {
    SDL_Surface* surface = IMG_Load(tbo->path);
    if (surface == NULL) {
        fprintf(stderr, "failed to load texture: %s.\n", tbo->path);
        return false;
    }

    tbo_flip_surface(surface);
    GLenum format = GL_RGB;
    if (surface->format->BytesPerPixel == 4) {
        format = GL_RGBA;
    }

    tbo->width = surface->w;
    tbo->height = surface->h;
    tbo->channels = surface->format->BytesPerPixel;

    glBindTexture(GL_TEXTURE_2D, tbo->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexImage2D(GL_TEXTURE_2D, 0, format, tbo->width, tbo->height, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(surface);
    return true;
}

void tbo_map_texture(tbo_t* tbo, GLuint texture_unit) {
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, tbo->id);
}

void tbo_unbind(void) {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void tbo_delete(tbo_t* tbo) {
	glDeleteTextures(1, &tbo->id);
}

void tbo_destroy(tbo_t* tbo) {
	tbo_delete(tbo);
	free(tbo);
}

void tbo_flip_surface(SDL_Surface* surface) {
    if (SDL_LockSurface(surface) < 0) {
        fprintf(stderr, "failed to lock surface.\n");
        return; // Failed to lock surface
    }

    int pitch = surface->pitch;        // row size
    char* temp = (char*)malloc(pitch); // intermediate buffer
    if (temp == NULL) {
        SDL_UnlockSurface(surface);
        fprintf(stderr, "failed to allocate memory for flip surface.\n");
        return; // Memory allocation failed
    }

    char* pixels = (char*)surface->pixels;

    for (int i = 0; i < surface->h / 2; ++i) {
        // get pointers to the two rows to swap
        char* row1 = pixels + i * pitch;
        char* row2 = pixels + (surface->h - i - 1) * pitch;

        // swap rows
        memcpy(temp, row1, pitch);
        memcpy(row1, row2, pitch);
        memcpy(row2, temp, pitch);
    }

    free(temp);
    SDL_UnlockSurface(surface);
}
