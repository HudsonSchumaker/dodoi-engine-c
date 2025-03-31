#pragma once
#include "de_game_object.h"

typedef struct {
	game_object_t go;
} cube_t;

void cube_init(cube_t* cube, const char* vertex_shader, const char* fragment_shader, const char* texture);
void cube_render(cube_t* cube, mat4_t* view, mat4_t* projection);
void cube_update(cube_t* cube);
void cube_delete(cube_t* cube);

void cube_set_scale(cube_t* cube, const vec3_t* scale);
void cube_set_position(cube_t* cube, const vec3_t* position);
void cube_set_rotation(cube_t* cube, const vec3_t* rotation);
