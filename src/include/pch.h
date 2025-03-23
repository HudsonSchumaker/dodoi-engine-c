/**
* @file pch.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <glad/glad.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VEC2 2
#define VEC3 3
#define VEC4 4
#define MAT3 9
#define MAT4 16

#define PI 3.14159265358979323846f
#define TWO_PI (2.0f * PI)
#define HALF_PI (PI / 2.0f)
#define DIV_PI_180 (PI / 180.0f)
#define DIV_180_PI (180.0f / PI)
