/**
* @file util.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

char* concat(const char* s1, const char* s2);

int sign(float value);

float minf(float a, float b);
float maxf(float a, float b);
float wrap(float value, float min_val, float max_val);
float clampf(float value, float min_val, float max_val);
float deg_to_rad(float degrees);
float rad_to_deg(float radians);
float smoothstep(float edge0, float edge1, float x);
float inverse_lerp(float a, float b, float value);
float interpolatef(float start, float end, float t);

double clamp(double value, double min_val, double max_val);
double interpolate(double start, double end, double t);

float distance_between_points(const float x1, const float y1, const float x2, const float y2);
