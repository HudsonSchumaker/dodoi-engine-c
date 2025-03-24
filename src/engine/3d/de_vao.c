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

void vao_link_vbo_2f(vao_t* vao, vbo_t* vbo, const GLuint layout) {
	vao_bind(vao);
	vbo_bind(vbo);
	glVertexAttribPointer(layout, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(layout);
	vbo_unbind();
	vao_unbind();
}

void vao_link_vbo_3f(vao_t* vao, vbo_t* vbo, const GLuint layout) {
	vao_bind(vao);
	vbo_bind(vbo);
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(layout);
	vbo_unbind();
	vao_unbind();
}

void vao_link_vbo_4f(vao_t* vao, vbo_t* vbo, const GLuint layout) {
	vao_bind(vao);
	vbo_bind(vbo);
	glVertexAttribPointer(layout, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(layout);
	vbo_unbind();
	vao_unbind();
}

void vao_link_vbo_3f2f(vao_t* vao, vbo_t* vbo) {
	vao_bind(vao);
	vbo_bind(vbo);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3_2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	
	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE_3_2 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	vbo_unbind();
	vao_unbind();
}

void vao_link_vbo_3f3f(vao_t* vao, vbo_t* vbo) {
	vao_bind(vao);
	vbo_bind(vbo);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	vbo_unbind();
	vao_unbind();
}

void vao_link_vbo_3f2f3f(vao_t* vao, vbo_t* vbo) {
	vao_bind(vao);
	vbo_bind(vbo);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3_2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	
	// Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE_3_3_2 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3_2 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	vbo_unbind();
	vao_unbind();
}
void vao_link_vbo_3f3f2f(vao_t* vao, vbo_t* vbo) {
	vao_bind(vao);
	vbo_bind(vbo);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3_2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3_2 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE_3_3_2 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	vbo_unbind();
	vao_unbind();
}
void vao_link_vbo_3f3f3f(vao_t* vao, vbo_t* vbo) {
	vao_bind(vao);
	vbo_bind(vbo);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3_3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3_3 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	// Texture attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, STRIDE_3_3_3 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	vbo_unbind();
	vao_unbind();
}

void vao_link_ebo(vao_t* vao, ebo_t* ebo) {
	// TODO
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
