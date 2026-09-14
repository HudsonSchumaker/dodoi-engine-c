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
#include "../../include/simd_math.h"
#include "../../include/de_game_object.h"

void game_object_init(game_object_t* go, const char* vertex_shader, const char* fragment_shader, const char* texture) {
	go->model = mat4_identity();
	go->position = vec3_new(0.0f, 0.0f, 0.0f);
	go->rotation = vec3_new(0.0f, 0.0f, 0.0f);
	go->scale    = vec3_new(1.0f, 1.0f, 1.0f);

	buffer_init(&go->vao, &go->vbo, &go->ebo);

	char* texture_path = create_texture_path(texture);
	tbo_init(&go->tbo, texture_path);

	if (!tbo_load(&go->tbo)) {
		fprintf(stderr, "failed to load texture.\n");
		exit(EXIT_FAILURE);
	}

	program_init(&go->program);

	char* vertex_shader_path   = create_shader_path(vertex_shader);
	char* fragment_shader_path = create_shader_path(fragment_shader);

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

void game_object_3d_init(game_object_t* go, const char* vertex_shader, const char* fragment_shader, const char* texture, const char* model) {
	game_object_init(go, vertex_shader, fragment_shader, texture);
	mesh_load_obj(&go->mesh, model);
	go->bounding_radius = mesh_compute_bounding_radius(&go->mesh);
}

void game_object_update_model_matrix(game_object_t* go) {
	go->model = mat4_identity();
	game_object_scale(go, &go->scale);
	game_object_rotate(go, &go->rotation);
	game_object_translate(go, &go->position);
}

void game_object_scale(game_object_t* go, const vec3_t* scale) {
	mat4_t scale_matrix = mat4_make_scale(scale->x, scale->y, scale->z);
	go->model = mat4_mul_mat4(&scale_matrix, &go->model);
}

void game_object_rotate(game_object_t* go, const vec3_t* rotation) {
	mat4_t rotation_matrix_x = mat4_make_rotation_x(deg_to_radf(rotation->x));
	mat4_t rotation_matrix_y = mat4_make_rotation_y(deg_to_radf(rotation->y));
	mat4_t rotation_matrix_z = mat4_make_rotation_z(deg_to_radf(rotation->z));

	go->model = mat4_mul_mat4(&rotation_matrix_z, &go->model);
	go->model = mat4_mul_mat4(&rotation_matrix_y, &go->model);
	go->model = mat4_mul_mat4(&rotation_matrix_x, &go->model);
}

void game_object_translate(game_object_t* go, const vec3_t* position) {
	mat4_t translation_matrix = mat4_make_translation(position->x, position->y, position->z);
	go->model = mat4_mul_mat4(&translation_matrix, &go->model);
}

#pragma intrinsic(sqrtf)
bool ray_intersects_sphere(const ray_t* ray, const vec3_t* sphere_center, float sphere_radius, float* out_t) {
	vec3_t oc = {
		ray->origin.x - sphere_center->x,
		ray->origin.y - sphere_center->y,
		ray->origin.z - sphere_center->z
	};

	float a = vec3_dot(&ray->direction, &ray->direction);
	float b = 2.0f * vec3_dot(&oc, &ray->direction);
	float c = vec3_dot(&oc, &oc) - sphere_radius * sphere_radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return false;
	}

	float sqrt_disc = sqrtf(discriminant);
	float t1 = (-b - sqrt_disc) / (2.0f * a);
	float t2 = (-b + sqrt_disc) / (2.0f * a);

	// Take the nearest intersection that is in front of the ray origin.
	float t = (t1 >= 0.0f) ? t1 : t2;
	if (t < 0.0f) {
		return false; // both intersections are behind the ray origin
	}

	if (out_t) *out_t = t;
	return true;
}

bool game_object_ray_intersect(const game_object_t* go, const ray_t* ray, float* out_t) {
	float max_scale = fmaxf(go->scale.x, fmaxf(go->scale.y, go->scale.z));
	float world_radius = go->bounding_radius * max_scale;
	return ray_intersects_sphere(ray, &go->position, world_radius, out_t);
}
