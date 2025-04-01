#pragma once
#include "pch.h"

float minf(float a, float b);
float maxf(float a, float b);
float wrap(float value, float min_val, float max_val);
float clampf(float value, float min_val, float max_val);
float deg_to_radf(float degrees);
float rad_to_degf(float radians);
float smoothstepf(float edge0, float edge1, float x);
float inverse_lerpf(float a, float b, float value);
float interpolatef(float start, float end, float t);
float distance_between_points(const float x1, const float y1, const float x2, const float y2);
