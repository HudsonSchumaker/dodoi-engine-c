/**
* @file de_buffer.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_buffer.h"
#include "../../include/de_util.h"

void buffer_init(vao_t* vao, vbo_t* vbo, ebo_t* ebo) {
	vao_init(vao);
	vbo_init(vbo);
	ebo_init(ebo);
}

void buffer_bind(vao_t* vao, vbo_t* vbo, ebo_t* ebo) {
	vao_bind(vao);
	vbo_bind(vbo);
	ebo_bind(ebo);
}

void buffer_unbind(vao_t* vao, vbo_t* vbo, ebo_t* ebo) {
	ebo_unbind();
	vbo_unbind();
	vao_unbind();
}

void buffer_delete(vao_t* vao, vbo_t* vbo, ebo_t* ebo) {
	vao_delete(vao);
	vbo_delete(vbo);
	ebo_delete(ebo);
}

char* buffer_create_shader_path(const char* shader) {
	return concat(SHADER_FOLDER, shader);
}

char* buffer_create_texture_path(const char* texture) {
	return concat(IMAGE_FOLDER, texture);
}
