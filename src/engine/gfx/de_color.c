/**
* @file color.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_color.h"

color_t color_new(const float r, const float g, const float b, const float a) {
    color_t new_color = {
        .r = r,
        .g = g,
        .b = b,
        .a = a
    };

    return new_color;
}

color_t color_new_rgb(const float r, const float g, const float b) {
	return color_new(r, g, b, 1.0f);
}

color_t color_new_rgba(const int r, const int g, const int b, const int a) {
	return color_new(
        color_int_to_float(r),
        color_int_to_float(g),
        color_int_to_float(b),
        color_int_to_float(a)
    );
}

float color_int_to_float(const int component) {
	return (1.0f/255.0f) * component;
}

color_t color_get_red() {
    return color_new(1.0f, 0.0f, 0.0f, 1.0f);
}

color_t color_get_green() {
    return color_new(0.0f, 1.0f, 0.0f, 1.0f);
}

color_t color_get_blue() {
    return color_new(0.0f, 0.0f, 1.0f, 1.0f);
}

color_t color_get_white() {
    return color_new(1.0f, 1.0f, 1.0f, 1.0f);
}

color_t color_get_black() {
    return color_new(0.0f, 0.0f, 0.0f, 1.0f);
}

color_t color_get_gray() {
    return color_new(0.5f, 0.5f, 0.5f, 1.0f);
}

color_t color_get_orange() {
    return color_new(1.0f, 0.8f, 0.0f, 1.0f);
}

color_t color_get_yellow() {
    return color_new(1.0f, 1.0f, 0.0f, 1.0f);
}
