/**
* @file pch.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include <time.h>
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
#define WINDOW_H_WIDTH 540
#define WINDOW_H_HEIGHT 360
#define WINDOW_TITLE "Dodoi-Engine-C-Sdl2-Glad-OpenGL-4.1-HD"

// Math constants
#define VEC2 2
#define VEC3 3
#define VEC4 4
#define MAT3 9
#define MAT4 16
#define PI 3.14159265358979323846f
#define TWO_PI 6.28318530717958647692f
#define HALF_PI 1.57079632679489661923f
#define DIV_PI_180 0.01745329251994329577f
#define DIV_180_PI 57.2957795130823208768f

// 3D constants
#define FOV 60.0f
#define STRIDE_1f 1 * sizeof(GLfloat)
#define STRIDE_2f 2 * sizeof(GLfloat)
#define STRIDE_3f 3 * sizeof(GLfloat)
#define STRIDE_4f 4 * sizeof(GLfloat)
#define STRIDE_5f 5 * sizeof(GLfloat)
#define STRIDE_6f 6 * sizeof(GLfloat)
#define STRIDE_3f_2f 5 * sizeof(GLfloat)
#define STRIDE_3f_3f 6 * sizeof(GLfloat)
#define STRIDE_3f_3f_2f 8 * sizeof(GLfloat)
#define STRIDE_3f_3f_3f 9 * sizeof(GLfloat)

// MVP
#define EYE "eye"
#define VIEW "view"
#define MODEL "model"
#define PROJECTION "projection"
#define POSITION "aPosition"
#define NORMAL "aNormal"
#define TEX_COORD "aTexCoord"

// Texture
#define TEXTURE "texture0"
#define TEXTURE1 "texture1"

// Light
#define LIGHT_COLOR "light.color"
#define LIGHT_POSITION "light.position"
#define LIGHT_DIRECTION "light.direction"
#define LIGHT_AMBIENT "light.ambient"
#define LIGHT_DIFFUSE "light.diffuse"
#define LIGHT_SPECULAR "light.specular"

// Attenuation
#define LIGHT_LINEAR "light.linear"
#define LIGHT_CONSTANT "light.constant"
#define LIGHT_QUADRATIC "light.quadratic"

// Material
#define MATERIAL_AMBIENT "material.ambient"
#define MATERIAL_DIFFUSE "material.diffuse"
#define MATERIAL_DIFFUSE_MAP "material.diffuseMap"
#define MATERIAL_SPECULAR "material.specular"
#define MATERIAL_SHININESS "material.shininess"

// Dodoi-Engine folders
#define MAP_FOLDER "./data/maps/"
#define OBJ_FOLDER "./data/models/"
#define FONT_FOLDER "./data/fonts/"
#define AUDIO_FOLDER "./data/audios/"
#define IMAGE_FOLDER "./data/images/"
#define SHADER_FOLDER "./data/shaders/"
#define BINARY_FOLDER "./data/binary/"

// Game loop
#define FPS 144
#define FRAME_TARGET_TIME (1000 / FPS)
