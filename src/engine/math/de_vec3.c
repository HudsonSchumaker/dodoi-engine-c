/**
* @file vec3.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_vector.h"

vec3_t vec3_up(void) {
    return vec3_new(0.0f, 1.0f, 0.0f);
}

vec3_t vec3_zero(void) {
    return vec3_new(0.0f, 0.0f, 0.0f);
}

vec3_t vec3_new(float x, float y, float z) {
    vec3_t new_vec3 = {
        .x = x,
        .y = y,
        .z = z
    };

    return new_vec3;
}

vec3_t vec3_clone(vec3_t* v) {
    return vec3_new(v->x, v->y, v->z);
}

vec3_t vec3_add(vec3_t* a, vec3_t* b) {
    vec3_t result;
    result.x = a->x + b->x;
    result.y = a->y + b->y;
    result.z = a->z + b->z;

    return result;
}

vec3_t vec3_sub(vec3_t* a, vec3_t* b) {
    vec3_t result;
    result.x = a->x - b->x;
    result.y = a->y - b->y;
    result.z = a->z - b->z;

    return result;
}

vec3_t vec3_mul(vec3_t* v, float s) {
    vec3_t result;
    result.x = v->x * s;
    result.y = v->y * s;
    result.z = v->z * s;

    return result;
}

vec3_t vec3_div(vec3_t* v, float s) {
    return vec3_new(v->x / s, v->y / s, v->z / s);
}

vec3_t vec3_rotate_x(vec3_t* v, float angle) {
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);

    vec3_t rotated_vector = {
        .x = v->x,
        .y = v->y * cos_angle - v->z * sin_angle,
        .z = v->y * sin_angle + v->z * cos_angle
    };
    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t* v, float angle) {
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);

    vec3_t rotated_vector = {
        .x = v->x * cos_angle + v->z * sin_angle,
        .y = v->y,
        .z = -v->x * sin_angle + v->z * cos_angle
    };
    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t* v, float angle) {
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);

    vec3_t rotated_vector = {
        .x = v->x * cos_angle - v->y * sin_angle,
        .y = v->x * sin_angle + v->y * cos_angle,
        .z = v->z
    };
    return rotated_vector;
}

vec3_t vec3_normal(vec3_t* v) {
    return vec3_new(-v->y, v->x, 0);
}

vec3_t vec3_unit_vector(vec3_t* v) {
    vec3_t result = vec3_new(0.0f, 0.0f, 0.0f);
    float length = vec3_magnitude(v);
    if (length != 0.0) {
        result.x = v->x / length;
        result.y = v->y / length;
        result.z = v->z / length;
    }
    return result;
}

vec3_t vec3_normalized(vec3_t* v) {
    float length = vec3_magnitude(v);
    vec3_t result = vec3_new(0.0f, 0.0f, 0.0f);
    if (length != 0.0f) {
        result.x /= length;
        result.y /= length;
        result.z /= length;
    }

    return result;
}

vec3_t vec3_cross(vec3_t* a, vec3_t* b) {
    vec3_t result = {
        .x = a->y * b->z - a->z * b->y,
        .y = a->z * b->x - a->x * b->z,
        .z = a->x * b->y - a->y * b->x
    };
    return result;
}

void vec3_normalize(vec3_t* v) {
    float length = vec3_magnitude(v);
    if (length != 0.0f) {
        v->x /= length;
        v->y /= length;
        v->z /= length;
    }
}

void vec3_scale(vec3_t* v, float s) {
    v->x *= s;
    v->y *= s;
    v->z *= s;
}

float vec3_magnitude(vec3_t* v) {
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

float vec3_dot(vec3_t* a, vec3_t* b) {
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

float vec3_magnitude_squared(vec3_t* v) {
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

vec2_t vec3_to_vec2(vec3_t* v) {
    return vec2_new(v->x, v->y);
}

vec4_t vec3_to_vec4(vec3_t* v) {
    return vec4_new(v->x, v->y, v->z, 1.0f);
}
