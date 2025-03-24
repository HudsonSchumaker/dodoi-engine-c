/**
* @file program.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"
#include "de_matrix.h"
#include "de_shader.h"

typedef struct {
    GLuint id;
} program_t;

program_t* program_new(void);
void program_init(program_t* program);
bool program_compile(program_t* program, const GLchar* vertex_path, const GLchar* fragment_path);
bool program_link(program_t* program, shader_t* vertex_shader, shader_t* fragment_shader);
bool saveBinary(const char* binary_path);
bool loadBinary(const char* binray_Path);

void program_bind(program_t* program);
void program_unbind(void);
void program_delete(program_t* program);
void program_destroy(program_t* program);

GLint program_get_uniform_location(program_t* program, const GLchar* name);
void program_set_uniform1i(GLint location, GLint value);
void program_set_uniform1f(GLint location, GLfloat value);
void program_set_uniform2f(GLint location, GLfloat x, GLfloat y);
void program_set_uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z);
void program_set_uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void program_set_uniform_mat4f(GLint location, const mat4_t* matrix);
