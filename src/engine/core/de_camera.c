/**
* @file camera.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_gfx.h"
#include "../../include/de_math.h"
#include "../../include/de_camera.h"

mat4_t camera_perspective(const float z_near, const float z_far) {
	return mat4_perspective(deg_to_radf(FOV), gfx_get_aspect_ratio(), z_near, z_far);
}

mat4_t camera_look_at(camera_t* camera) {
	return mat4_look_at(&camera->eye, &camera->target, &camera->up);
}
