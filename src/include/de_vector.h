/**
* @file vector.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

typedef struct {
    union {
        struct {
            float x;
            float y;
        };
        float as_array[2];
    };
} vec2_t;

typedef struct {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float as_array[3];
    };
} vec3_t;

typedef struct {
	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float as_array[4];
	};
} vec4_t;

////////////////////////////////////////
// Vec2 functions
////////////////////////////////////////
vec2_t vec2_zero(void);
vec2_t vec2_new(float x, float y);
vec2_t vec2_clone(vec2_t* v);

vec2_t vec2_add(vec2_t* a, vec2_t* b);
vec2_t vec2_sub(vec2_t* a, vec2_t* b);
vec2_t vec2_mul(vec2_t* v, float s);
vec2_t vec2_div(vec2_t* v, float s);

vec2_t vec2_rotate(vec2_t* v, float angle);
vec2_t vec2_normal(vec2_t* v);
vec2_t vec2_unit_vector(vec2_t* v);

void vec2_normalize(vec2_t* v);
void vec2_scale(vec2_t* v, float s);

float vec2_dot(vec2_t* a, vec2_t* b);
float vec2_cross(vec2_t* a, vec2_t* b);
float vec2_magnitude(vec2_t* v);
float vec2_magnitude_squared(vec2_t* v);

////////////////////////////////////////
// Vec3 functions
////////////////////////////////////////
vec3_t vec3_up(void);
vec3_t vec3_zero(void);
vec3_t vec3_new(float x, float y, float z);
vec3_t vec3_clone(vec3_t* v);

void vec3_normalize(vec3_t* v);
void vec3_scale(vec3_t* v, float s);

vec3_t vec3_add(vec3_t* a, vec3_t* b);
vec3_t vec3_sub(vec3_t* a, vec3_t* b);
vec3_t vec3_mul(vec3_t* v, float s);
vec3_t vec3_div(vec3_t* v, float s);

vec3_t vec3_rotate_x(vec3_t* v, float angle);
vec3_t vec3_rotate_y(vec3_t* v, float angle);
vec3_t vec3_rotate_z(vec3_t* v, float angle);

vec3_t vec3_cross(vec3_t* a, vec3_t* b);
vec3_t vec3_normal(vec3_t* v);
vec3_t vec3_unit_vector(vec3_t* v);
vec3_t vec3_normalized(vec3_t* v);

float vec3_dot(vec3_t* a, vec3_t* b);
float vec3_magnitude(vec3_t* v);
float vec3_magnitude_squared(vec3_t* v);

////////////////////////////////////////
// Vec4 functions
////////////////////////////////////////
vec4_t vec4_zero(void);
vec4_t vec4_new(float x, float y, float z, float w);
vec4_t vec4_clone(vec4_t* v);

////////////////////////////////////////
// Convertion functions
////////////////////////////////////////
vec3_t vec2_to_vec3(vec2_t* v);
vec4_t vec2_to_vec4(vec2_t* v);

vec2_t vec3_to_vec2(vec3_t* v);
vec4_t vec3_to_vec4(vec3_t* v);

vec2_t vec4_to_vec2(vec4_t* v);
vec3_t vec4_to_vec3(vec4_t* v);
