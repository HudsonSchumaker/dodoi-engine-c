/**
* @file util.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_util.h"

int sign(float value) {
	return (value > 0) - (value < 0);
}

float minf(float a, float b) {
    return (a < b) ? a : b;
}

float maxf(float a, float b) {
    return (a > b) ? a : b;
}

float clampf(float value, float min_val, float max_val) {
    return maxf(min_val, minf(value, max_val));
}

float interpolatef(float start, float end, float t) {
    return start + t * (end - start);
}

float deg_to_rad(float degrees) {
    return degrees * DIV_PI_180;
}

float rad_to_deg(float radians) {
    return radians * DIV_180_PI;
}

float smoothstep(float edge0, float edge1, float x) {
    x = clampf((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return x * x * (3 - 2 * x);
}

float inverse_lerp(float a, float b, float value) {
    return (value - a) / (b - a);
}

float wrap(float value, float min_val, float max_val) {
    float range = max_val - min_val;
    return min_val + fmodf(fmodf(value - min_val, range) + range, range);
}

double clamp(double value, double min_val, double max_val) {
    return max(min_val, min(value, max_val));
}

double interpolate(double start, double end, double t) {
    return start + t * (end - start);
}
