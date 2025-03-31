/**
* @file matrix.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"
#include "de_vector.h"

typedef struct {
    float m[3][3];
} mat3_t;

typedef struct {
    float m[4][4];
} mat4_t;

// Mat3 functions
mat3_t mat3_identity(void);
vec3_t mat3_mul_vec3(const mat3_t* m, const vec3_t* v);
mat3_t mat3_mul_mat3(const mat3_t* a, const mat3_t* b);
void mat3_to_array(const mat3_t* mat, float* array);

// Mat4 functions
mat4_t mat4_identity(void);
mat4_t mat4_make_scale(const float sx, const float sy, const float sz);

mat4_t mat4_make_rotation_x(const float rx);
mat4_t mat4_make_rotation_y(const float ry);
mat4_t mat4_make_rotation_z(const float rz);

mat4_t mat4_make_translation(const float tx, const float ty, const float tz);

vec4_t mat4_mul_vec4(const mat4_t* m, const vec4_t* v);
vec4_t mat4_mul_vec4_sse(const mat4_t* m, const vec4_t* v);

mat4_t mat4_mul_mat4(const mat4_t* a, const mat4_t* b);
mat4_t mat4_mul_mat4_sse(const mat4_t* a, const mat4_t* b);

mat4_t mat4_look_at(const vec3_t* eye, const vec3_t* target, const vec3_t* up);
mat4_t mat4_perspective(const float fov, const float aspect, const float near, const float far);
mat4_t mat4_orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far);

void mat4_to_array(const mat4_t* mat, float* array);
