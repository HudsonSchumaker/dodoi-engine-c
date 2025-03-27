/**
* @file vec4.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_vector.h"

vec4_t vec4_zero(void) {
    return vec4_new(0.0f, 0.0f, 0.0f, 0.0f);
}

vec4_t vec4_new(const float x, const float y, const float z, const float w) {
    vec4_t new_vec4 = {
        .x = x,
        .y = y,
        .z = z,
        .w = w
    };

    return new_vec4;
}

vec4_t vec4_clone(const vec4_t* v) {
    return vec4_new(v->x, v->y, v->z, v->w);
}

vec2_t vec4_to_vec2(const vec4_t* v) {
    return vec2_new(v->x, v->y);
}

vec3_t vec4_to_vec3(const vec4_t* v) {
    return vec3_new(v->x, v->y, v->z);
}
