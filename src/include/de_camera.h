/**
* @file camera.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"
#include "de_vector.h"
#include "de_matrix.h"

typedef struct {
    vec3_t eye;
    vec3_t target;
    vec3_t up;

    float yaw;
    float pitch;
} camera_t;

typedef struct {
    camera_t coords;
    float radius;
} orbit_camera_t;

typedef struct {
    camera_t coords;
    vec3_t look;
    vec3_t right;
} fps_camera_t;

orbit_camera_t* orbit_camera_new(void);
void orbit_camera_update(orbit_camera_t* camera);
void orbit_camera_set_radius(orbit_camera_t* camera, float radius);
void orbit_camera_set_target(orbit_camera_t* camera, vec3_t target);     // lookAt
void orbit_camera_set_position(orbit_camera_t* camera, vec3_t position); // eye
void orbit_camera_set_rotation(orbit_camera_t* camera, float yaw, float pitch);

fps_camera_t* fps_camera_new(vec3_t position, vec3_t target);
void fps_camera_init(fps_camera_t* camera, vec3_t position, vec3_t target);
void fps_camera_update(fps_camera_t* camera);
void fps_camera_move(fps_camera_t* camera, vec3_t direction);
void fps_camera_set_position(fps_camera_t* camera, vec3_t direction);
void fps_camera_set_rotation(fps_camera_t* camera, float yaw, float pitch);
vec3_t* fps_camera_get_look(fps_camera_t* camera);
vec3_t* fps_camera_get_right(fps_camera_t* camera);
