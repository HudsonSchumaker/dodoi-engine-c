/**
* @file vec2.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_vector.h"

vec2_t vec2_zero(void) {
    return vec2_new(0.0f, 0.0f);
}

vec2_t vec2_new(const float x, const float y) {
    vec2_t new_vec2 = {
        .x = x,
        .y = y
    };

    return new_vec2;
}

vec2_t vec2_clone(const vec2_t* v) {
    return vec2_new(v->x, v->y);
}

vec2_t vec2_add(const vec2_t* a, const vec2_t* b) {
    return vec2_new(a->x + b->x, a->y + b->y);
}

vec2_t vec2_sub(const vec2_t* a, const vec2_t* b) {
    return vec2_new(a->x - b->x, a->y - b->y);
}

vec2_t vec2_mul(const vec2_t* v, const float s) {
    return vec2_new(v->x * s, v->y * s);
}

vec2_t vec2_div(const vec2_t* v, const float s) {
    return vec2_new(v->x / s, v->y / s);
}

#pragma intrinsic(cosf, sinf)
vec2_t vec2_rotate(const vec2_t* v, const float angle) {
    return vec2_new(v->x * cosf(angle) - v->y * sinf(angle), v->x * sinf(angle) + v->y * cosf(angle));
}

vec2_t vec2_normal(const vec2_t* v) {
    return vec2_new(-v->y, v->x);
}

vec2_t vec2_unit_vector(const vec2_t* v) {
    vec2_t result = vec2_new(0.0f, 0.0f);
    float length = vec2_magnitude(v);
    if (length != 0.0f) {
        result.x = v->x / length;
        result.y = v->y / length;
    }
    return result;
}

void vec2_normalize(vec2_t* v) {
    float length = vec2_magnitude(v);
    if (length != 0.0f) {
        v->x /= length;
        v->y /= length;
    }
}

void vec2_scale(vec2_t* v, float s) {
    v->x *= s;
    v->y *= s;
}

float vec2_dot(const vec2_t* a, const vec2_t* b) {
    return (a->x * b->x) + (a->y * b->y);
}

float vec2_cross(const vec2_t* a, const vec2_t* b) {
    return (a->x * b->y) - (a->y * b->x);
}

#pragma intrinsic(sqrtf)
float vec2_magnitude(const vec2_t* v) {
    return sqrtf(v->x * v->x + v->y * v->y);
}

float vec2_magnitude_squared(const vec2_t* v) {
    return v->x * v->x + v->y * v->y;
}

vec3_t vec2_to_vec3(const vec2_t* v) {
    return vec3_new(v->x, v->y, 0.0f);
}

vec4_t vec2_to_vec4(const vec2_t* v) {
    return vec4_new(v->x, v->y, 0.0f, 1.0f);
}
