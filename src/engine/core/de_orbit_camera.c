/**
* @file orbit_camera.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_math.h"
#include "../../include/de_camera.h"

orbit_camera_t* orbit_camera_new(void) {
	orbit_camera_t* camera = (orbit_camera_t*)malloc(sizeof(orbit_camera_t));
	if (camera == NULL) {
		fprintf(stderr, "failed to allocate memory for orbit camera.\n");
		exit(EXIT_FAILURE);
	}
	camera->coords.eye    = vec3_zero();
	camera->coords.target = vec3_zero();
	camera->coords.up     = vec3_up();

	camera->coords.yaw   = 0.0f;
	camera->coords.pitch = 0.0f;
	camera->radius = 10.0f;
	return camera;
}

#pragma intrinsic(cosf, sinf)
void orbit_camera_update(orbit_camera_t* camera) {
	camera->coords.eye.x = camera->coords.target.x + camera->radius * cosf(camera->coords.pitch) * sinf(camera->coords.yaw);
	camera->coords.eye.y = camera->coords.target.y + camera->radius * sinf(camera->coords.pitch);
	camera->coords.eye.z = camera->coords.target.z + camera->radius * cosf(camera->coords.pitch) * cosf(camera->coords.yaw);
}

void orbit_camera_set_radius(orbit_camera_t* camera, float radius) {
	camera->radius = clampf(radius, 1.0f, 100.0f);
}

void orbit_camera_set_target(orbit_camera_t* camera, vec3_t target) {
	camera->coords.target = target;
}

void orbit_camera_set_position(orbit_camera_t* camera, vec3_t position) {
	camera->coords.eye = position;
}

void orbit_camera_set_rotation(orbit_camera_t* camera, float yaw, float pitch) {
	camera->coords.yaw   = deg_to_radf(yaw);
	camera->coords.pitch = clampf(deg_to_radf(pitch), -HALF_PI + 0.1f, HALF_PI - 0.1f);

	orbit_camera_update(camera);
}
