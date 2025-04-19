/**
* @file model.h
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
    int first;
    int second;
} ipair_t;

typedef struct {
    float first;
    float second;
} fpair_t;

typedef struct {
	bool first;
	bool second;
} bpair_t;

typedef struct {
	char* first;
	char* second;
} cpair_t;

typedef struct {
    int first;
    int second;
    int third;
} itriple_t;

typedef struct {
    float first;
    float second;
    float third;
} ftriple_t;

typedef struct {
    char* first;
    char* second;
	char* third;
} ctriple_t;

typedef struct {
    union {
        struct {
            float u;
            float v;
        };
        float as_array[2];
    };
} tex2_t;

typedef struct {
    vec3_t position;
    vec3_t normal;
    tex2_t uv;
} vertex_t;

typedef struct {
	int vertex[3];
	int uv[3];
	int normal[3];
} face_t;

typedef struct {
    vec3_t origin;
    vec3_t direction;
} ray_t;

typedef struct {
    char* name;
    char* vert;
    char* frag;
} recipe_t;
