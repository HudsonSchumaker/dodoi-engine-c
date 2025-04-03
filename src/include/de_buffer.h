/**
* @file buffer.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

typedef struct {
    GLuint id;
} vao_t;

typedef struct {
    GLuint id;
} vbo_t;

typedef struct {
	GLuint id;
} ebo_t;

typedef struct {
    GLuint id;
    char* path;
    int width;
    int height;
    int channels;
} tbo_t;

// Buffer
void buffer_init(vao_t* vao, vbo_t* vbo, ebo_t* ebo);
void buffer_bind(vao_t* vao, vbo_t* vbo, ebo_t* ebo);
void buffer_unbind(vao_t* vao, vbo_t* vbo, ebo_t* ebo);
void buffer_delete(vao_t* vao, vbo_t* vbo, ebo_t* ebo);

// Vertex Array Object (VAO)
vao_t* vao_new(void);
void vao_init(vao_t* vao);
void vao_bind(vao_t* vao);
void vao_unbind(void);

void vao_link_vbo_1f(const GLuint layout);
void vao_link_vbo_2f(const GLuint layout);
void vao_link_vbo_3f(const GLuint layout);
void vao_link_vbo_4f(const GLuint layout);
void vao_link_vbo_3f2f();
void vao_link_vbo_3f3f();
void vao_link_vbo_3f2f3f();
void vao_link_vbo_3f3f2f();
void vao_link_vbo_3f3f3f();

void vao_delete(vao_t* vao);
void vao_destroy(vao_t* vao);

// Vertex Buffer Object (VBO)
vbo_t* vbo_new(void);
void vbo_init(vbo_t* vbo);
void vbo_set_data(vbo_t* vbo, GLfloat* vertices, GLsizeiptr size);
void vbo_bind(vbo_t* vbo);
void vbo_unbind(void);
void vbo_delete(vbo_t* vbo);
void vbo_destroy(vbo_t* vbo);

// Element Buffer Object (EBO)
ebo_t* ebo_new(void);
void ebo_init(ebo_t* ebo);
void ebo_set_data(ebo_t* ebo, GLuint* indices, GLsizeiptr size);
void ebo_bind(ebo_t* ebo);
void ebo_unbind(void);
void ebo_delete(ebo_t* ebo);
void ebo_destroy(ebo_t* ebo);

// Texture Buffer Object (TBO)
tbo_t* tbo_new(void);
void tbo_init(tbo_t* tbo, const char* path);
void tbo_bind(tbo_t* tbo);
bool tbo_load(tbo_t* tbo);
void tbo_map_texture(tbo_t* tbo, GLuint texture_unit);
void tbo_unbind(void);
void tbo_delete(tbo_t* tbo);
void tbo_destroy(tbo_t* tbo);
