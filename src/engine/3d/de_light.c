/**
* @file de_light.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_light.h"

directional_light_t directional_light_init(void) {
	directional_light_t light;
	light.ambient = vec3_new(0.9f, 0.9f, 0.9f);
	light.diffuse = vec3_new(0.5f, 0.5f, 0.5f);
	light.specular = vec3_new(0.5f, 0.5f, 0.5f);
	light.direction = vec3_new(0.0f, -0.9f, -0.17f); // Sun direction
	return light;
}

directional_light_t* directional_light_new(vec3_t ambient, vec3_t diffuse, vec3_t specular, vec3_t direction) {
	directional_light_t* light = (directional_light_t*)malloc(sizeof(directional_light_t));
	if (light == NULL) {
		fprintf(stderr, "failed to allocate memory for directional light.\n");
		exit(EXIT_FAILURE);
	}
	light->ambient = ambient;
	light->diffuse = diffuse;
	light->specular = specular;
	light->direction = direction;
	return light;
}

point_light_t point_light_init(void) {
	point_light_t light;
	light.position = vec3_new(0.0f, 0.0f, 0.0f);
	light.ambient = vec3_new(0.9f, 0.9f, 0.9f);
	light.diffuse = vec3_new(0.5f, 0.5f, 0.5f);
	light.specular = vec3_new(1.0f, 1.0f, 1.0f);
	light.constant = 1.0f;
	light.linear = 0.09f;
	light.quadratic = 0.032f;
	return light;
}

spot_light_t spot_light_init(void) {
	spot_light_t light;
	light.position = vec3_new(0.0f, 0.0f, 0.0f);
	light.direction = vec3_new(0.0f, 0.0f, -1.0f);
	light.ambient = vec3_new(0.9f, 0.9f, 0.9f);
	light.diffuse = vec3_new(1.0f, 1.0f, 1.0f);
	light.specular = vec3_new(1.0f, 1.0f, 1.0f);
	light.cosInnerCone = 0.0f;
	light.cosOuterCone = 0.0f;
	light.constant = 1.0f;
	light.linear = 0.09f;
	light.quadratic = 0.032f;
	return light;
}
