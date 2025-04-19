/**
* @file cube.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "de_light.h"
#include "de_material.h"
#include "de_game_object.h"

typedef struct {
	material_t material;
	directional_light_t light;
	game_object_t go;

	GLint uniform_material_ambient;
	GLint uniform_material_specular;
	GLint uniform_material_shininess;
	GLint uniform_material_diffuse_map;

	GLint uniform_light_direction;
	GLint uniform_light_ambient;
	GLint uniform_light_diffuse;
	GLint uniform_light_specular;
} cube_t;

void cube_init(cube_t* cube, const char* vertex_shader, const char* fragment_shader, const char* texture, const char* model);
void cube_render(cube_t* cube, mat4_t* view, mat4_t* projection);
void cube_update(cube_t* cube);
void cube_delete(cube_t* cube);

void cube_set_scale(cube_t* cube, const vec3_t* scale);
void cube_set_position(cube_t* cube, const vec3_t* position);
void cube_set_rotation(cube_t* cube, const vec3_t* rotation);
