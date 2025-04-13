/**
* @file set.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2025, Dodoi-Lab
*/
#include "../../include/de_color.h"
#include "../../include/de_model.h"
#include "../../include/de_vector.h"
#include "../../include/de_collection.h"

#define SET_INIT_CAPACITY 64
#define SET_RESIZE_FACTOR 128

void set_init(set_t* set, size_t type_size, int (*equals)(const void*, const void*)) {
    set->size = 0;
    set->capacity = SET_INIT_CAPACITY;
    set->type_size = type_size;
    set->equals = equals;
    set->array = malloc(set->capacity * set->type_size);
}

void set_init_size(set_t* set, size_t type_size, size_t reserve, int (*equals)(const void*, const void*)) {
	set->size = 0;
	set->capacity = reserve;
	set->type_size = type_size;
	set->equals = equals;
	set->array = malloc(set->capacity * set->type_size);
}

bool set_contains(set_t* set, void* value) {
    for (size_t i = 0; i < set->size; i++) {
        void* current = (char*)set->array + i * set->type_size;
        if (set->equals(current, value) == 0) {
            return true;
        }
    }
    return false;
}

void set_add(set_t* set, void* value) {
    if (!set_contains(set, value)) {
        if (set->size == set->capacity) {
            set->capacity += SET_RESIZE_FACTOR;
            void* new_value = realloc(set->array, set->capacity * set->type_size);
            if (new_value) {
				set->array = new_value;
			}
            else {
                fprintf(stderr, "ERROR: set_t, memory reallocation failed\n");
                return;
            }
        }
        memcpy((char*)set->array + set->size * set->type_size, value, set->type_size);
        set->size++;
    }
}

void* set_get(set_t* set, size_t index) {
    if (index < set->size) {
        return (char*)set->array + index * set->type_size;
    }
    return NULL;
}

int set_equals_int(const void* a, const void* b) {
	return (*(int*)a == *(int*)b) ? 0 : 1;
}

int set_equals_float(const void* a, const void* b) {
	return (*(float*)a == *(float*)b) ? 0 : 1;
}

int set_equals_double(const void* a, const void* b) {
	return (*(double*)a == *(double*)b) ? 0 : 1;
}

int set_equals_string(const void* a, const void* b) {
	return (strcmp(*(const char**)a, *(const char**)b) == 0) ? 0 : 1;
}

int set_equals_vec2(const void* a, const void* b) {
	vec2_t* vec_a = (vec2_t*)a;
	vec2_t* vec_b = (vec2_t*)b;
	return (
		vec_a->x == vec_b->x &&
		vec_a->y == vec_b->y
	) ? 0 : 1;
}

int set_equals_vec3(const void* a, const void* b) {
	vec3_t* vec_a = (vec3_t*)a;
	vec3_t* vec_b = (vec3_t*)b;
	return (
		vec_a->x == vec_b->x && 
		vec_a->y == vec_b->y &&
		vec_a->z == vec_b->z
	) ? 0 : 1;
}

int set_equals_vec4(const void* a, const void* b) {
	vec4_t* vec_a = (vec4_t*)a;
	vec4_t* vec_b = (vec4_t*)b;
	return (
		vec_a->x == vec_b->x &&
		vec_a->y == vec_b->y &&
		vec_a->z == vec_b->z &&
		vec_a->w == vec_b->w
	) ? 0 : 1;
}

int set_equals_tex2(const void* a, const void* b) {
	tex2_t* tex_a = (tex2_t*)a;
	tex2_t* tex_b = (tex2_t*)b;
	return (
		tex_a->u == tex_b->u &&
		tex_a->v == tex_b->v
	) ? 0 : 1;
}

int set_equals_color(const void* a, const void* b) {
	color_t* color_a = (color_t*)a;
	color_t* color_b = (color_t*)b;
	return (color_a->r == color_b->r &&
		color_a->g == color_b->g &&
		color_a->b == color_b->b &&
		color_a->a == color_b->a
	) ? 0 : 1;
}

int set_equals_bpair(const void* a, const void* b) {
	bpair_t* pair_a = (bpair_t*)a;
	bpair_t* pair_b = (bpair_t*)b;
	return (pair_a->first == pair_b->first &&
		pair_a->second == pair_b->second
	) ? 0 : 1;
}

int set_equals_ipair(const void* a, const void* b) {
	ipair_t* pair_a = (ipair_t*)a;
	ipair_t* pair_b = (ipair_t*)b;
	return (
		pair_a->first == pair_b->first &&
		pair_a->second == pair_b->second
	) ? 0 : 1;
}

int set_equals_fpair(const void* a, const void* b) {
	fpair_t* pair_a = (fpair_t*)a;
	fpair_t* pair_b = (fpair_t*)b;
	return (
		pair_a->first == pair_b->first &&
		pair_a->second == pair_b->second
	) ? 0 : 1;
}

int set_equals_itriple(const void* a, const void* b) {
	itriple_t* triple_a = (itriple_t*)a;
	itriple_t* triple_b = (itriple_t*)b;
	return (
		triple_a->first == triple_b->first &&
		triple_a->second == triple_b->second &&
		triple_a->third == triple_b->third
	) ? 0 : 1;
}

int set_equals_ftriple(const void* a, const void* b) {
	ftriple_t* triple_a = (ftriple_t*)a;
	ftriple_t* triple_b = (ftriple_t*)b;
	return (
		triple_a->first == triple_b->first &&
		triple_a->second == triple_b->second &&
		triple_a->third == triple_b->third
	) ? 0 : 1;
}

int set_equals_vertex(const void* a, const void* b) {
	vertex_t* vertex_a = (vertex_t*)a;
	vertex_t* vertex_b = (vertex_t*)b;
	return (
		vertex_a->position.x == vertex_b->position.x && 
		vertex_a->position.y == vertex_b->position.y && 
		vertex_a->position.z == vertex_b->position.z &&
		vertex_a->normal.x == vertex_b->normal.x &&
		vertex_a->normal.y == vertex_b->normal.y && 
		vertex_a->normal.z == vertex_b->normal.z &&
		vertex_a->uv.u == vertex_b->uv.u && 
		vertex_a->uv.v == vertex_b->uv.v
	) ? 0 : 1;
}

void set_free(set_t* set) {
    free(set->array);
    set->array = NULL;
    set->size = 0;
    set->capacity = 0;
}
