/**
* @file de_cube.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_cube.h"

void cube_init(cube_t* cube, const char* vertex_shader, const char* fragment_shader, const char* texture, const char* model) {
	game_object_3d_init(&cube->go, vertex_shader, fragment_shader, texture, model);

    vao_bind(&cube->go.vao);
	
	float* vertex_buffer = mesh_vertex_to_gl_buffer(&cube->go.mesh);
	for (int i = 0; i < cube->go.mesh.vertex_count; i++) {
		printf("Vertex %d: Position(%f, %f, %f), Normal(%f, %f, %f), UV(%f, %f)\n",
			i,
			vertex_buffer[i * 8 + 0], vertex_buffer[i * 8 + 1], vertex_buffer[i * 8 + 2],
			vertex_buffer[i * 8 + 3], vertex_buffer[i * 8 + 4], vertex_buffer[i * 8 + 5],
			vertex_buffer[i * 8 + 6], vertex_buffer[i * 8 + 7]);
	}
	
	unsigned int* index_buffer = mesh_index_to_gl_buffer(&cube->go.mesh);
	for (int i = 0; i < cube->go.mesh.face_count; i++) {
		printf("Face %d: Indices(%u, %u, %u)\n",
			i,
			index_buffer[i * 3 + 0], index_buffer[i * 3 + 1], index_buffer[i * 3 + 2]);
	}


	vbo_set_data(&cube->go.vbo, mesh_vertex_to_gl_buffer(&cube->go.mesh), cube->go.mesh.vertex_count * 8 * sizeof(float));
	ebo_set_data(&cube->go.ebo, mesh_index_to_gl_buffer(&cube->go.mesh), cube->go.mesh.face_count * 3 * sizeof(unsigned int));
	
    vao_link_vbo_3f3f2f();
	
    buffer_unbind(&cube->go.vao, &cube->go.vbo, &cube->go.ebo);
}

void cube_render(cube_t* cube, mat4_t* view, mat4_t* projection) {
	program_set(&cube->go.program);
	buffer_bind(&cube->go.vao, &cube->go.vbo, &cube->go.ebo);
	tbo_bind(&cube->go.tbo);

	program_set_uniform1i(cube->go.uniform_texture, 0);
	program_set_uniform_mat4f(cube->go.uniform_model, &cube->go.model);
	program_set_uniform_mat4f(cube->go.uniform_view, view);
	program_set_uniform_mat4f(cube->go.uniform_projection, projection);

	//glDrawElements(GL_TRIANGLES, cube->go.mesh.face_count * 3, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, cube->go.mesh.vertex_count);

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
