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

////////////////////////////////////////
// Mat3 functions
////////////////////////////////////////
mat3_t mat3_identity(void);
vec3_t mat3_mul_vec3(mat3_t* m, vec3_t* v);
mat3_t mat3_mul_mat3(mat3_t* a, mat3_t* b);
void mat3_to_array(const mat3_t* mat, float* array);

////////////////////////////////////////
// Mat4 functions
////////////////////////////////////////
mat4_t mat4_identity(void);
mat4_t mat4_make_scale(float sx, float sy, float sz);
mat4_t mat4_make_translation(float tx, float ty, float tz);

mat4_t mat4_make_rotation_x(float angle);
mat4_t mat4_make_rotation_y(float angle);
mat4_t mat4_make_rotation_z(float angle);

vec4_t mat4_mul_vec4(mat4_t* m, vec4_t* v);
mat4_t mat4_mul_mat4(mat4_t* a, mat4_t* b);

mat4_t mat4_look_at(vec3_t* eye, vec3_t* target, vec3_t* up);
mat4_t mat4_perspective(float fov, float aspect, float near, float far);
mat4_t mat4_orthographic(float left, float right, float bottom, float top, float near, float far);

void mat4_to_array(const mat4_t* mat, float* array);
