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
	float r;
	float g;
	float b;
	float a;
} color_t;

typedef struct {
    union {
        struct {
            float x;
            float y;
        };
        float as_array[2];
    };
} text2_t;

typedef struct {
    vec3_t position;
    vec3_t normal;
    text2_t uv;
} vertex_t;
