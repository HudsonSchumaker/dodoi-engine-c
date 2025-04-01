/**
* @file de_game_object.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_util.h"
#include "../../include/de_math.h"
#include "../../include/de_game_object.h"

void game_object_init(game_object_t* go, const char* vertex_shader, const char* fragment_shader, const char* texture) {
	go->model = mat4_identity();
	go->position = vec3_new(0.0f, 0.0f, 0.0f);
	go->rotation = vec3_new(0.0f, 0.0f, 0.0f);
	go->scale    = vec3_new(1.0f, 1.0f, 1.0f);

	buffer_init(&go->vao, &go->vbo, &go->ebo);

	char* texture_path = buffer_create_texture_path(texture);
	tbo_init(&go->tbo, texture_path);

	if (!tbo_load(&go->tbo)) {
		fprintf(stderr, "failed to load texture.\n");
		exit(EXIT_FAILURE);
	}

	program_init(&go->program);

	char* vertex_shader_path = buffer_create_shader_path(vertex_shader);
	char* fragment_shader_path = buffer_create_shader_path(fragment_shader);

	if (!program_compile(&go->program, vertex_shader_path, fragment_shader_path)) {
		fprintf(stderr, "failed to compile shaders.\n");
		exit(EXIT_FAILURE);
	}

	go->uniform_model = program_get_uniform_location(&go->program, MODEL);
	go->uniform_view = program_get_uniform_location(&go->program,VIEW);
	go->uniform_projection = program_get_uniform_location(&go->program, PROJECTION);
	go->uniform_texture = program_get_uniform_location(&go->program, TEXTURE);

	free(texture_path);
	free(vertex_shader_path);
	free(fragment_shader_path);
}

void game_object_update_model_matrix(game_object_t* go) {
	go->model = mat4_identity();
	game_object_scale(go, &go->scale);
	game_object_rotate(go, &go->rotation);
	game_object_translate(go, &go->position);
}

void game_object_scale(game_object_t* go, const vec3_t* scale) {
	mat4_t scale_matrix = mat4_make_scale(scale->x, scale->y, scale->z);
	go->model = mat4_mul_mat4_sse(&scale_matrix, &go->model);
}

void game_object_rotate(game_object_t* go, const vec3_t* rotation) {
	mat4_t rotation_matrix_x = mat4_make_rotation_x(deg_to_radf(rotation->x));
	mat4_t rotation_matrix_y = mat4_make_rotation_y(deg_to_radf(rotation->y));
	mat4_t rotation_matrix_z = mat4_make_rotation_z(deg_to_radf(rotation->z));

	go->model = mat4_mul_mat4_sse(&rotation_matrix_z, &go->model);
	go->model = mat4_mul_mat4_sse(&rotation_matrix_y, &go->model);
	go->model = mat4_mul_mat4_sse(&rotation_matrix_x, &go->model);
}

void game_object_translate(game_object_t* go, const vec3_t* position) {
	mat4_t translation_matrix = mat4_make_translation(position->x, position->y, position->z);
	go->model = mat4_mul_mat4_sse(&translation_matrix, &go->model);
}
