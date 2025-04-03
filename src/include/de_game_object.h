/**
* @file game_object.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"
#include "de_mesh.h"
#include "de_buffer.h"
#include "de_vector.h"
#include "de_matrix.h"
#include "de_program.h"

typedef struct {
	mat4_t model;
    vec3_t scale;
    vec3_t rotation;
    vec3_t position;

    vao_t vao;
    vbo_t vbo;
    ebo_t ebo;
    tbo_t tbo;
    
    program_t program;
	mesh_t mesh;

    GLint uniform_model;
    GLint uniform_view;
    GLint uniform_projection;
    GLint uniform_texture;
} game_object_t;

void game_object_init(game_object_t* go, const char* vertex_shader, const char* fragment_shader, const char* texture);
void game_object_3d_init(game_object_t* go, const char* vertex_shader, const char* fragment_shader, const char* texture, const char* model);

void game_object_update_model_matrix(game_object_t* go);
void game_object_scale(game_object_t* go, const vec3_t* scale);
void game_object_rotate(game_object_t* go, const vec3_t* rotation);
void game_object_translate(game_object_t* go, const vec3_t* position);
