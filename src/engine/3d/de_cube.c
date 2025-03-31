/**
* @file de_cube.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_cube.h"

static float vertices[] = {
    // Positions          // Texture Coords
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, // Front top left
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // Front bottom right
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // Front top right
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // Front bottom left
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, // Back top left
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, // Back bottom right
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // Back top right
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // Back bottom left
};

static unsigned int indices[] = {
    // Front face
    0, 1, 2,
    0, 3, 1,
    // Back face
    4, 5, 6,
    4, 7, 5,
    // Left face
    4, 0, 3,
    4, 3, 7,
    // Right face
    2, 1, 5,
    2, 5, 6,
    // Top face
    4, 6, 2,
    4, 2, 0,
    // Bottom face
    3, 1, 5,
    3, 5, 7,
};

void cube_init(cube_t* cube, const char* vertex_shader, const char* fragment_shader, const char* texture) {
	game_object_init(&cube->go, vertex_shader, fragment_shader, texture);
	
    vao_bind(&cube->go.vao);
	vbo_set_data(&cube->go.vbo, vertices, sizeof(vertices));
	ebo_set_data(&cube->go.ebo, indices, sizeof(indices));
	
    vao_link_vbo_3f2f();
	
    buffer_bind(&cube->go.vao, &cube->go.vbo, &cube->go.ebo);
}

void cube_render(cube_t* cube, mat4_t* view, mat4_t* projection) {
	program_set(&cube->go.program);
	buffer_bind(&cube->go.vao, &cube->go.vbo, &cube->go.ebo);
	tbo_bind(&cube->go.tbo);

	program_set_uniform1i(cube->go.uniform_texture, 0);
	program_set_uniform_mat4f(cube->go.uniform_model, &cube->go.model);
	program_set_uniform_mat4f(cube->go.uniform_view, view);
	program_set_uniform_mat4f(cube->go.uniform_projection, projection);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	buffer_unbind(&cube->go.vao, &cube->go.vbo, &cube->go.ebo);
	program_unset();
}

void cube_update(cube_t* cube) {
	game_object_update_model_matrix(&cube->go);
}

void cube_delete(cube_t* cube) {
	tbo_delete(&cube->go.tbo);
	program_delete(&cube->go.program);
	buffer_delete(&cube->go.vao, &cube->go.vbo, &cube->go.ebo);
}

void cube_set_scale(cube_t* cube, const vec3_t* scale) {
    cube->go.scale = *scale;
}

void cube_set_rotation(cube_t* cube, const vec3_t* rotation) {
	cube->go.rotation = *rotation;
}

void cube_set_position(cube_t* cube, const vec3_t* position) {
	cube->go.position = *position;
}
