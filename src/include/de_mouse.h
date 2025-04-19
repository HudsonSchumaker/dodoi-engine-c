/**
* @file mouse.h
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
#include "de_game_object.h"

void handle_mouse_click(int mouse_x, int mouse_y, const mat4_t* view_matrix, const mat4_t* projection_matrix,
    const vec3_t* camera_position, const game_object_t* objects, int object_count);

fpair_t mouse_convert_to_ndc(const int mouse_x, const int mouse_y);
vec4_t mouse_ray_from_ndc(float x, float y);
vec4_t mouse_ray_eye(const mat4_t* inverse_projection_matrix, const vec4_t* ray_clip);
vec3_t mouse_ray_world(const mat4_t* inverse_view_matrix, const vec4_t* ray_eye);
void mouse_ray_debug(const vec4_t* ray_clip, const vec4_t* ray_eye, const vec3_t* ray_world);
