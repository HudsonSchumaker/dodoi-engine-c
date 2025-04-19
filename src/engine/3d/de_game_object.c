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

bool game_object_ray_intersect(const game_object_t* go, const ray_t* ray, int i) {
    // Define the object's bounding box in world space
    vec3_t min = {
        go->position.x - go->scale.x * 0.5f,
        go->position.y - go->scale.y * 0.5f,
        go->position.z - go->scale.z * 0.5f
    };

    vec3_t max = {
        go->position.x + go->scale.x * 0.5f,
        go->position.y + go->scale.y * 0.5f,
        go->position.z + go->scale.z * 0.5f
    };

    printf("  Bounding Box Min: (%f, %f, %f)\n", min.x, min.y, min.z);
    printf("  Bounding Box Max: (%f, %f, %f)\n", max.x, max.y, max.z);

    // Avoid division by zero (or very close to it)
    float inv_dir_x = (ray->direction.x != 0.0f) ? 1.0f / ray->direction.x : FLT_MAX;
    float inv_dir_y = (ray->direction.y != 0.0f) ? 1.0f / ray->direction.y : FLT_MAX;
    float inv_dir_z = (ray->direction.z != 0.0f) ? 1.0f / ray->direction.z : FLT_MAX;

    float t1 = (min.x - ray->origin.x) * inv_dir_x;
    float t2 = (max.x - ray->origin.x) * inv_dir_x;
    float tmin = fminf(t1, t2);
    float tmax = fmaxf(t1, t2);

    float ty1 = (min.y - ray->origin.y) * inv_dir_y;
    float ty2 = (max.y - ray->origin.y) * inv_dir_y;
    float tymin = fminf(ty1, ty2);
    float tymax = fmaxf(ty1, ty2);

    if ((tmin > tymax) || (tymin > tmax)) return false;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    float tz1 = (min.z - ray->origin.z) * inv_dir_z;
    float tz2 = (max.z - ray->origin.z) * inv_dir_z;
    float tzmin = fminf(tz1, tz2);
    float tzmax = fmaxf(tz1, tz2);

    if ((tmin > tzmax) || (tzmin > tmax)) return false;
    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;

    // Intersection is valid if tmin is positive (in front of the camera)
    if (tmin < 0.0f) return false;

    // Debug output
    printf("Object %d intersected!\n", i);
    printf("  Bounding Box Min: (%f, %f, %f)\n", min.x, min.y, min.z);
    printf("  Bounding Box Max: (%f, %f, %f)\n", max.x, max.y, max.z);
    printf("  Ray Origin: (%f, %f, %f)\n", ray->origin.x, ray->origin.y, ray->origin.z);
    printf("  Ray Direction: (%f, %f, %f)\n", ray->direction.x, ray->direction.y, ray->direction.z);
    printf("  tmin: %f, tmax: %f\n", tmin, tmax);

    return true;
}
