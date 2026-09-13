#pragma once
#include "pch.h"

float minf(float a, float b);
float maxf(float a, float b);
float randf(float min, float max);
float wrapf(float value, float min_val, float max_val);
float clampf(float value, float min_val, float max_val);
float deg_to_radf(float degrees);
float rad_to_degf(float radians);
float normalize_anglef(float angle);
float smoothstepf(float edge0, float edge1, float x);
float inverse_lerpf(float a, float b, float value);
float interpolatef(float start, float end, float t);
float distance_between_points(const float x1, const float y1, const float x2, const float y2);

static inline float rsqrtf(float number) {
    union {
        float f;
        int i;
    } conv;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    conv.f = number;

    conv.i = 0x5f3759df - (conv.i >> 1);
    y = conv.f;

    y = y * (threehalfs - (x2 * y * y));
    return y;
}

static inline float fsqrtf(float number) {
    return number * rsqrtf(number);
}
