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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <glad/glad.h>

// SDL2
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// Window settings
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define WINDOW_H_WIDTH WINDOW_WIDTH / 2
#define WINDOW_H_HEIGHT WINDOW_HEIGHT / 2
#define WINDOW_TITLE "Dodoi-Engine-C-Sdl2-Glad-OpenGL-4.1-HD"

// Math constants
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

// 3D constants
#define FOV 60.0f
#define STRIDE_2f 2 * sizeof(GLfloat)
#define STRIDE_3f 3 * sizeof(GLfloat)
#define STRIDE_4f 4 * sizeof(GLfloat)
#define STRIDE_5f 5 * sizeof(GLfloat)
#define STRIDE_6f 6 * sizeof(GLfloat)
#define STRIDE_3f_2f 5 * sizeof(GLfloat)
#define STRIDE_3f_3f 6 * sizeof(GLfloat)
#define STRIDE_3f_3f_2f 8 * sizeof(GLfloat)
#define STRIDE_3f_3f_3f 9 * sizeof(GLfloat)

// Dodoi-Engine folders
#define MAP_FOLDER "./data/maps/"
#define OBJ_FOLDER "./data/models/"
#define FONT_FOLDER "./data/fonts/"
#define AUDIO_FOLDER "./data/audios/"
#define IMAGE_FOLDER "./data/images/"
#define SHADER_FOLDER "./data/shaders/"
#define SHADER_FOLDER_BINARY "./data/shaders/compiled/"

// Game loop
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
