/**
* @file light.h
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
	vec3_t ambient;
	vec3_t diffuse;
	vec3_t specular;
	vec3_t direction;
} directional_light_t;

directional_light_t directional_light_init(void);
directional_light_t* directional_light_new(vec3_t ambient, vec3_t diffuse, vec3_t specular, vec3_t direction);

typedef struct {
	vec3_t position;
	vec3_t ambient;
	vec3_t diffuse;
	vec3_t specular;
	
	float constant;  // Kc
	float linear;    // Kl
	float quadratic; // Kq

} point_light_t;

point_light_t point_light_init(void);

typedef struct {
	vec3_t ambient;
	vec3_t diffuse;
	vec3_t specular;

	vec3_t position;
	vec3_t direction;

	float cosInnerCone; // cos(theta)
	float cosOuterCone; // cos(theta + angle)

	float constant;  // Kc
	float linear;    // Kl
	float quadratic; // Kq
} spot_light_t;

spot_light_t spot_light_init(void);
