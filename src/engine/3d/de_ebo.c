/**
* @file de_ebo.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_buffer.h"

ebo_t* ebo_new(void) {
	ebo_t* ebo = (ebo_t*)malloc(sizeof(ebo_t));
	if (ebo == NULL) {
		fprintf(stderr, "failed to allocate memory for ebo.\n");
		exit(EXIT_FAILURE);
	}
	return ebo;
}

void ebo_init(ebo_t* ebo) {
	glGenBuffers(1, &ebo->id);
}

void ebo_set_data(ebo_t* ebo, GLuint* indices, GLsizeiptr size) {
	ebo_bind(ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ebo_bind(ebo_t* ebo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->id);
}

void ebo_unbind(void) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ebo_delete(ebo_t* ebo) {
	glDeleteBuffers(1, &ebo->id);
}

void ebo_destroy(ebo_t* ebo) {
	ebo_delete(ebo);
	free(ebo);
}
