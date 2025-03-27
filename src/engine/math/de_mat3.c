/**
* @file mat3.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_matrix.h"

mat3_t mat3_identity(void) {
	mat3_t m = {{
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	}};
	return m;
}

vec3_t mat3_mul_vec3(const mat3_t* m, const vec3_t* v) {
	vec3_t result = vec3_zero();
	result.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z;
	result.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z;
	result.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z;
	return result;
}

mat3_t mat3_mul_mat3(const mat3_t* a, const mat3_t* b) {
	mat3_t m;
	for (byte i = 0; i < 3; i++) {
		for (byte j = 0; j < 3; j++) {
			m.m[i][j] = a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j];
		}
	}
	return m;
}

void mat3_to_array(const mat3_t* mat, float* array) {
	for (byte i = 0; i < 3; i++) {
		for (byte j = 0; j < 3; j++) {
			array[j * 3 + i] = mat->m[i][j]; // column-major order
		}
	}
}
