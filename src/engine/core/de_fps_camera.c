/**
* @file fps_camera.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_util.h"
#include "../../include/de_camera.h"

fps_camera_t* fps_camera_new(void) {
	fps_camera_t* camera = (fps_camera_t*)malloc(sizeof(fps_camera_t));
	if (camera == NULL) {
		fprintf(stderr, "failed to allocate memory for fps camera.\n");
		exit(EXIT_FAILURE);
	}
	camera->coords.eye    = vec3_zero();
	camera->coords.target = vec3_zero();
	camera->coords.up     = vec3_up();
	camera->coords.yaw   = 0.0f;
	camera->coords.pitch = 0.0f;

	camera->look  = vec3_new(0.0f, 0.0f, -1.0f);
	camera->right = vec3_new(1.0f, 0.0f, 0.0f);
	return camera;
}

void fps_camera_update(fps_camera_t* camera) {
    vec3_t look;
    look.x = cosf(camera->coords.pitch) * sinf(camera->coords.yaw);
    look.y = sinf(camera->coords.pitch);
    look.z = cosf(camera->coords.pitch) * cosf(camera->coords.yaw);

    vec3_normalize(&look);
    vec3_t up = vec3_new(0.0f, 1.0f, 0.0f);

    vec3_t crossRight = vec3_cross(&look, &up);
    vec3_normalize(&crossRight);
    camera->right = crossRight;

    vec3_t crossUp = vec3_cross(&camera->right, &look);
    vec3_normalize(&crossUp);
    camera->coords.up = crossUp;

    camera->look = look;
    camera->coords.target = vec3_add(&camera->coords.eye, &look);
}

void fps_camera_move(fps_camera_t* camera, vec3_t direction) {
	camera->coords.eye = vec3_add(&camera->coords.eye, &direction);
	fps_camera_update(camera);
}

void fps_camera_set_position(fps_camera_t* camera, vec3_t position) {
	camera->coords.eye = position;
}

void fps_camera_set_rotation(fps_camera_t* camera, float yaw, float pitch) {
	camera->coords.yaw   = deg_to_rad(yaw);
	camera->coords.pitch = clampf(deg_to_rad(pitch), -HALF_PI + 0.1f, HALF_PI - 0.1f);

	if (camera->coords.yaw >  TWO_PI) {
		camera->coords.yaw -= TWO_PI;
	}
	else if (camera->coords.yaw < 0.0f) {
		camera->coords.yaw += TWO_PI;
	}

	fps_camera_update(camera);
}

vec3_t* fps_camera_get_look(fps_camera_t* camera) {
	return &camera->look;
}

vec3_t* fps_camera_get_right(fps_camera_t* camera) {
	return &camera->right;
}
