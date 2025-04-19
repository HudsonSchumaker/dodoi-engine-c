/**
* @file mouse.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_gfx.h"
#include "../../include/de_model.h"
#include "../../include/de_mouse.h"

void handle_mouse_click(int mouse_x, int mouse_y, const mat4_t* view_matrix, const mat4_t* projection_matrix, 
    const vec3_t* camera_position, const game_object_t* objects, int object_count
) {
    printf("Mouse clicked at (%d, %d)\n", mouse_x, mouse_y);

    // Convert mouse_x, mouse_y to normalized device coordinates (NDC)
	fpair_t ndc = mouse_convert_to_ndc(mouse_x, mouse_y);
	
    // Convert NDC to world space
    vec4_t ray_clip = mouse_ray_from_ndc(ndc.first, ndc.second);

	mat4_t inverse_projection_matrix;
    if (mat4_inverse(projection_matrix, &inverse_projection_matrix)) {
        printf("inverse_projection possible\n");
		vec4_t ray_eye = mouse_ray_eye(&inverse_projection_matrix, &ray_clip);

		mat4_t inverse_view_matrix;
        if (mat4_inverse(view_matrix, &inverse_view_matrix)) {
			printf("inverse_view possible\n");
			vec3_t ray_world = mouse_ray_world(&inverse_view_matrix, &ray_eye);

			// Debugging output
			mouse_ray_debug(&ray_clip, &ray_eye, &ray_world);

            ray_t ray = { *camera_position, ray_world };

            // Check intersection with all objects
            for (int i = 0; i < object_count; ++i) {
                if (game_object_ray_intersect(&objects[i], &ray, i)) {
                    printf("Object %d clicked!\n", i);
                }
            }
        }
    }
}

fpair_t mouse_convert_to_ndc(const int mouse_x, const int mouse_y) {
    ipair_t window_size = gfx_get_window_size();
    float window_width  = (float)window_size.first;
    float window_height = (float)window_size.second;

    float ndc_x = (2.0f * mouse_x) / window_width - 1.0f;
    float ndc_y = 1.0f - (2.0f * mouse_y) / window_height;

	return (fpair_t) { ndc_x, ndc_y };
}

vec4_t mouse_ray_from_ndc(float x, float y) {
    vec4_t ray_clip = { x, y, -1.0f, 1.0f };
	return ray_clip;
}

vec4_t mouse_ray_eye(const mat4_t* inverse_projection_matrix, const vec4_t* ray_clip) {
    vec4_t ray_eye = mat4_mul_vec4_sse(inverse_projection_matrix, ray_clip);
	ray_eye.z = -1.0f;
    ray_eye.w = 0.0f;
	return ray_eye;
}

vec3_t mouse_ray_world(const mat4_t* inverse_view_matrix, const vec4_t* ray_eye) {
	vec4_t ray_world = mat4_mul_vec4_sse(inverse_view_matrix, ray_eye);
    vec3_t ray_world_vec3 = vec4_to_vec3(&ray_world);

    printf("Before normalized Ray World: (%f, %f, %f)\n", ray_world.x, ray_world.y, ray_world.z);
    vec3_t ray_world_normalized = vec3_normalized(&ray_world_vec3);
	return ray_world_normalized;
}

void mouse_ray_debug(const vec4_t* ray_clip, const vec4_t* ray_eye, const vec3_t* ray_world) {
	printf("Mouse Ray Debug:\n");
	printf("Ray Clip: (%f, %f, %f, %f)\n", ray_clip->x, ray_clip->y, ray_clip->z, ray_clip->w);
	printf("Ray Eye: (%f, %f, %f, %f)\n", ray_eye->x, ray_eye->y, ray_eye->z, ray_eye->w);
	printf("Ray World: (%f, %f, %f)\n", ray_world->x, ray_world->y, ray_world->z);
}
