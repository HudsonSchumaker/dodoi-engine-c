/**
* @file material.h
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
	float shininess;
} material_t;

material_t material_init(void);
material_t* material_new(vec3_t ambient, vec3_t diffuse, vec3_t specular, float shininess);

material_t material_emerald(void);
material_t material_jade(void);
material_t material_obsidian(void);
material_t material_pearl(void);
material_t material_ruby(void);
material_t material_turquoise(void);
material_t material_brass(void);
material_t material_bronze(void);
material_t material_chrome(void);
material_t material_copper(void);
material_t material_gold(void);
material_t material_silver(void);
material_t material_black_plastic(void);
material_t material_cyan_plastic(void);
material_t material_green_plastic(void);
material_t material_red_plastic(void);
material_t material_white_plastic(void);
material_t material_yellow_plastic(void);
material_t material_black_rubber(void);
material_t material_cyan_rubber(void);
material_t material_green_rubber(void);
material_t material_red_rubber(void);
material_t material_white_rubber(void);
material_t material_yellow_rubber(void);
material_t material_polished_bronze(void);
material_t material_polished_copper(void);
material_t material_polished_gold(void);
material_t material_polished_silver(void);
material_t material_pewter(void);
material_t material_rubber(void);
material_t material_plastic(void);
material_t material_polished_emerald(void);
material_t material_polished_jade(void);
material_t material_polished_obsidian(void);
material_t material_polished_pearl(void);
material_t material_polished_ruby(void);
material_t material_polished_turquoise(void);
