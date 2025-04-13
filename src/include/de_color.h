/**
* @file color.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

typedef struct {
	float r;
	float g;
	float b;
	float a;
} color_t;

color_t color_new(const float r, const float g, const float b, const float a);
color_t color_new_rgb(const float r, const float g, const float b);
color_t color_new_rgba(const int r, const int g, const int b, const int a);

color_t color_get_red();
color_t color_get_green();
color_t color_get_blue();
color_t color_get_white();
color_t color_get_black();
color_t color_get_gray();
color_t color_get_orange();
color_t color_get_yellow();

float color_int_to_float(const int component);
