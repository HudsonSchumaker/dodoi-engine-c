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

// Vec2 functions
vec2_t vec2_zero(void);
vec2_t vec2_new(const float x, const float y);
vec2_t vec2_clone(const vec2_t* v);

vec2_t vec2_add(const vec2_t* a, const vec2_t* b);
vec2_t vec2_sub(const vec2_t* a, const vec2_t* b);
vec2_t vec2_mul(const vec2_t* v, const float s);
vec2_t vec2_div(const vec2_t* v, const float s);

vec2_t vec2_rotate(const vec2_t* v, const float angle);
vec2_t vec2_normal(const vec2_t* v);
vec2_t vec2_unit_vector(const vec2_t* v);

void vec2_normalize(vec2_t* v);
void vec2_scale(vec2_t* v, float s);

float vec2_dot(const vec2_t* a, const vec2_t* b);
float vec2_cross(const vec2_t* a, const vec2_t* b);
float vec2_magnitude(const vec2_t* v);
float vec2_magnitude_squared(const vec2_t* v);

// Vec3 functions
vec3_t vec3_up(void);
vec3_t vec3_zero(void);
vec3_t vec3_new(const float x, const float y, const float z);
vec3_t vec3_clone(const vec3_t* v);

void vec3_normalize(vec3_t* v);
void vec3_scale(vec3_t* v, float s);

vec3_t vec3_add(const vec3_t* a, const vec3_t* b);
vec3_t vec3_sub(const vec3_t* a, const vec3_t* b);
vec3_t vec3_mul(const vec3_t* v, const float s);
vec3_t vec3_div(const vec3_t* v, const float s);

vec3_t vec3_rotate_x(const vec3_t* v, const float rx);
vec3_t vec3_rotate_y(const vec3_t* v, const float ry);
vec3_t vec3_rotate_z(const vec3_t* v, const float rz);

vec3_t vec3_cross(const vec3_t* a, const vec3_t* b);
vec3_t vec3_normal(const vec3_t* v);
vec3_t vec3_unit_vector(const vec3_t* v);
vec3_t vec3_normalized(const vec3_t* v);

float vec3_dot(const vec3_t* a, const vec3_t* b);
float vec3_magnitude(const vec3_t* v);
float vec3_magnitude_squared(const vec3_t* v);

// Vec4 functions
vec4_t vec4_zero(void);
vec4_t vec4_new(const float x, const float y, const float z, const float w);
vec4_t vec4_clone(const vec4_t* v);

// Convertion functions
vec3_t vec2_to_vec3(const vec2_t* v);
vec4_t vec2_to_vec4(const vec2_t* v);
vec2_t vec3_to_vec2(const vec3_t* v);
vec4_t vec3_to_vec4(const vec3_t* v);
vec2_t vec4_to_vec2(const vec4_t* v);
vec3_t vec4_to_vec3(const vec4_t* v);
