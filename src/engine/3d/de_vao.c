/**
* @file de_vao.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_buffer.h"

vao_t* vao_new(void) {
	vao_t* vao = (vao_t*)malloc(sizeof(vao_t));
	if (vao == NULL) {
		fprintf(stderr, "failed to allocate memory for vao.\n");
		exit(EXIT_FAILURE);
	}
	vao_init(vao);
	return vao;
}

void vao_init(vao_t* vao) {
	glGenVertexArrays(1, &vao->id);
}

void vao_bind(vao_t* vao) {
	glBindVertexArray(vao->id);
}

void vao_link_vbo_2f(const GLuint layout) {
	glVertexAttribPointer(layout, 2, GL_FLOAT, GL_FALSE, STRIDE_2f, (void*)0);
	glEnableVertexAttribArray(layout);
}

void vao_link_vbo_3f(const GLuint layout) {
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, STRIDE_3f, (void*)0);
	glEnableVertexAttribArray(layout);
}

void vao_link_vbo_4f(const GLuint layout) {
	glVertexAttribPointer(layout, 4, GL_FLOAT, GL_FALSE, STRIDE_4f, (void*)0);
	glEnableVertexAttribArray(layout);
}

void vao_link_vbo_3f2f() {
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_2f, (void*)0);
	glEnableVertexAttribArray(0);
	
	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE_3f_2f, (void*)(STRIDE_3f));
	glEnableVertexAttribArray(1);
}

void vao_link_vbo_3f3f() {
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f, (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f, (void*)(STRIDE_3f));
	glEnableVertexAttribArray(1);
}

void vao_link_vbo_3f2f3f() {
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_2f, (void*)0);
	glEnableVertexAttribArray(0);
	
	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_2f, (void*)(STRIDE_3f));
	glEnableVertexAttribArray(1);
	
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_2f, (void*)(STRIDE_5f));
	glEnableVertexAttribArray(2);
}
void vao_link_vbo_3f3f2f() {
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_2f, (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_2f, (void*)(STRIDE_3f));
	glEnableVertexAttribArray(1);

	// Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_2f, (void*)(STRIDE_6f));
	glEnableVertexAttribArray(2);
}
void vao_link_vbo_3f3f3f() {
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_3f, (void*)0);
	glEnableVertexAttribArray(0);
	
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_3f, (void*)(STRIDE_3f));
	glEnableVertexAttribArray(1);
	
	// Texture attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, STRIDE_3f_3f_3f, (void*)(STRIDE_6f));
	glEnableVertexAttribArray(2);
}

void vao_unbind(void) {
	glBindVertexArray(0);
}

void vao_delete(vao_t* vao) {
	glDeleteVertexArrays(1, &vao->id);	
}

void vao_destroy(vao_t* vao) {
	vao_delete(vao);
	free(vao);
}
