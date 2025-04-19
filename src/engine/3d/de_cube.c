/**
* @file de_cube.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_cube.h"

void cube_load_uniform_locations(cube_t* cube) {
	// Materials
	cube->uniform_material_ambient = program_get_uniform_location(&cube->go.program, MATERIAL_AMBIENT);
	cube->uniform_material_specular = program_get_uniform_location(&cube->go.program, MATERIAL_SPECULAR);
	cube->uniform_material_shininess = program_get_uniform_location(&cube->go.program, MATERIAL_SHININESS);
	cube->uniform_material_diffuse_map = program_get_uniform_location(&cube->go.program, MATERIAL_DIFFUSE_MAP);

	// Lights
	cube->uniform_light_ambient = program_get_uniform_location(&cube->go.program, LIGHT_AMBIENT);
	cube->uniform_light_diffuse = program_get_uniform_location(&cube->go.program, LIGHT_DIFFUSE);
	cube->uniform_light_specular = program_get_uniform_location(&cube->go.program, LIGHT_SPECULAR);
	cube->uniform_light_direction = program_get_uniform_location(&cube->go.program, LIGHT_DIRECTION);
}

void cube_init(cube_t* cube, const char* vertex_shader, const char* fragment_shader, const char* texture, const char* model) {
	game_object_3d_init(&cube->go, vertex_shader, fragment_shader, texture, model);

    vao_bind(&cube->go.vao);
	vbo_set_data(&cube->go.vbo, mesh_vertex_to_gl_buffer(&cube->go.mesh), cube->go.mesh.vertex_count * 8 * sizeof(float));
	ebo_set_data(&cube->go.ebo, mesh_index_to_gl_buffer(&cube->go.mesh), cube->go.mesh.face_count * 3 * sizeof(unsigned int));
	
    vao_link_vbo_3f3f2f();
    buffer_unbind();

	cube->material = material_brass();
	cube->light = directional_light_init();

	cube_load_uniform_locations(cube);
}

void cube_render(cube_t* cube, mat4_t* view, mat4_t* projection) {
	program_set(&cube->go.program);
	buffer_bind(&cube->go.vao, &cube->go.vbo, &cube->go.ebo);
	tbo_bind(&cube->go.tbo);

	// Set material properties
	program_set_uniform1f(cube->uniform_material_shininess, cube->material.shininess);
	program_set_uniform_vec3f(cube->uniform_material_ambient, cube->material.ambient);
	program_set_uniform_vec3f(cube->uniform_material_specular, cube->material.specular);

	// Set light properties
	program_set_uniform_vec3f(cube->uniform_light_ambient, cube->light.ambient);
	program_set_uniform_vec3f(cube->uniform_light_diffuse, cube->light.diffuse);
	program_set_uniform_vec3f(cube->uniform_light_specular, cube->light.specular);
	program_set_uniform_vec3f(cube->uniform_light_direction, cube->light.direction);

	// Set texture and MVP matrices
	program_set_uniform1i(cube->go.uniform_texture, 0);
	program_set_uniform_mat4f(cube->go.uniform_model, &cube->go.model); // model matrix
	program_set_uniform_mat4f(cube->go.uniform_view, view);             // view matrix
	program_set_uniform_mat4f(cube->go.uniform_projection, projection); // projection matrix

	glDrawArrays(GL_TRIANGLES, 0, cube->go.mesh.vertex_count);

	buffer_unbind();
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
