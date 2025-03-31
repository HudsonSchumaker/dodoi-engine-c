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
#include "de_model.h"

void gfx_init(bool fullscreen, bool vsync);
void gfx_open_gl_info(void);

SDL_Window* gfx_get_window(void);
SDL_GLContext* gfx_get_context(void);
SDL_Surface* gfx_load_texture(const char* path);

float gfx_get_aspect_ratio(void);
ipair_t gfx_get_window_size(void);

void gfx_set_2d_mode(void);
void gfx_set_3d_mode(void);
void gfx_set_clear_color(const float r, const float g, const float b, const float a);
void gfx_clear_screen(void);
void gfx_swap_screen(void);
void gfx_show_mouse_cursor(bool value);
void gfx_set_mouse_position(const int x, const int y);
void gfx_on_window_resized(SDL_Window* window, int new_width, int new_height);
void gfx_close(void);
