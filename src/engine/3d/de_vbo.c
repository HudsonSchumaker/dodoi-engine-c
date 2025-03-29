/**
* @file de_vbo.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_buffer.h"

vbo_t* vbo_new(void) {
	vbo_t* vbo = (vbo_t*)malloc(sizeof(vbo_t));
	if (vbo == NULL) {
		fprintf(stderr, "failed to allocate memory for vbo.\n");
		exit(EXIT_FAILURE);
	}
	return vbo;
}

void vbo_init(vbo_t* vbo) {
	glGenBuffers(1, &vbo->id);
}

void vbo_set_data(vbo_t* vbo, GLfloat* vertices, GLsizeiptr size) {
	vbo_bind(vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void vbo_bind(vbo_t* vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
}

void vbo_unbind(void) {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_delete(vbo_t* vbo) {
	glDeleteBuffers(1, &vbo->id);
}

void vbo_destroy(vbo_t* vbo) {
	vbo_delete(vbo);
	free(vbo);
}
