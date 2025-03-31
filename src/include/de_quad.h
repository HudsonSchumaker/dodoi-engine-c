#pragma once
#include "de_game_object.h"

typedef struct {
	game_object_t go;
} quad_t;

void quad_init(quad_t* quad, const char* vertex_shader, const char* fragment_shader, const char* texture);
void quad_render(quad_t* quad);
void quad_update(quad_t* quad);
void quad_delete(quad_t* quad);
