/**
* @file gfx.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

void gfx_init(bool fullscreen, bool vsync);
void gfx_open_gl_info(void);

SDL_Window* gfx_get_window(void);
SDL_GLContext* gfx_get_context(void);

void gfx_on_window_resized(SDL_Window* window, int new_width, int new_height);
void gfx_close(void);
