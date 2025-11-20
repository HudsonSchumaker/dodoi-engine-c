/**
* @file de_quad.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_quad.h"

static float vertices[] = {
	// positions        // texture coords
	 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  // top right
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f,  0.0f, 1.0f   // top left 
};

static unsigned int indices[] = {
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

void quad_init(quad_t* quad, const char* vertex_shader, const char* fragment_shader, const char* texture) {
	game_object_init(&quad->go, vertex_shader, fragment_shader, texture);

	vao_bind(&quad->go.vao);
	vbo_set_data(&quad->go.vbo, vertices, sizeof(vertices));
	ebo_set_data(&quad->go.ebo, indices, sizeof(indices));
	vao_link_vbo_3f2f();

	buffer_unbind();
}

void quad_render(quad_t* quad) {
	program_set(&quad->go.program);
	buffer_bind(&quad->go.vao, &quad->go.vbo, &quad->go.ebo);
	tbo_bind(&quad->go.tbo);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	buffer_unbind();
	program_unset();
}

void quad_update(quad_t* quad) {
	game_object_update_model_matrix(&quad->go);
}

void quad_delete(quad_t* quad) {
	tbo_delete(&quad->go.tbo);
	program_delete(&quad->go.program);
	buffer_delete(&quad->go.vao, &quad->go.vbo, &quad->go.ebo);
}
