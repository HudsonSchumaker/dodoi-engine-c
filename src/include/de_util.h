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

int sign(float value);

// File path manipulation functions
char* create_model_path(const char* model);
char* create_shader_path(const char* shader);
char* create_texture_path(const char* texture);
char* create_binary_path(const char* binary);

// String manipulation functions
char* concat(const char* s1, const char* s2);
