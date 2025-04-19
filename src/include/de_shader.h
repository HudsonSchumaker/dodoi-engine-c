/**
* @file shader.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"
#include "de_collection.h"

typedef struct {
    GLuint id;
} shader_t;

shader_t* shader_new(void);
void shader_init_frag_shader(shader_t* shader);
void shader_init_vert_shader(shader_t* shader);
bool shader_compile(shader_t* shader, const GLchar* path);
void shader_delete(shader_t* shader);
void shader_destroy(shader_t* shader);
char* shader_load_file(const char* path);
