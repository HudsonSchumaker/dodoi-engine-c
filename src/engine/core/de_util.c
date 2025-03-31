/**
* @file util.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_util.h"

int sign(register float value) {
	return (value > 0) - (value < 0);
}

float minf(register float a, register float b) {
    return (a < b) ? a : b;
}

float maxf(register float a, register float b) {
    return (a > b) ? a : b;
}

float clampf(register float value, register float min_val, register float max_val) {
    return maxf(min_val, minf(value, max_val));
}

float interpolatef(register float start, register float end, register float t) {
    return start + t * (end - start);
}

float deg_to_rad(register float degrees) {
    return degrees * DIV_PI_180;
}

float rad_to_deg(register float radians) {
    return radians * DIV_180_PI;
}

float smoothstep(register float edge0, register float edge1, register float x) {
    x = clampf((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return x * x * (3 - 2 * x);
}

float inverse_lerp(register float a, register float b, register float value) {
    return (value - a) / (b - a);
}

float wrap(register float value, register float min_val, register float max_val) {
    register float range = max_val - min_val;
    return min_val + fmodf(fmodf(value - min_val, range) + range, range);
}

double clamp(register double value, register double min_val, register double max_val) {
    return max(min_val, min(value, max_val));
}

double interpolate(register double start, register double end, register double t) {
    return start + t * (end - start);
}

#pragma intrinsic(sqrtf)
float distance_between_points(const float x1, const float y1, const float x2, const float y2) {
    // using the euclidean distance formula
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


char* concat(const char* s1, const char* s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char* result = malloc(len1 + len2 + 1); // +1 for the null-terminator
	
    if (!result) {
		fprintf(stderr, "failed to allocate memory for concat.\n");
		exit(EXIT_FAILURE);
	}

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return result;
}
