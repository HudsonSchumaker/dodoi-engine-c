/**
* @file main.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "include/pch.h"
#include "include/de_gfx.h"
#include "include/de_model.h"
#include "include/de_scene.h"
#include "include/de_collection.h"
#include "playground/title_screen.h"
#include "playground/splash_screen.h"
#include "include/de_shader_manager.h"

void shaders(void);
bpair_t args(int argc, char* argv[]);

int main(int argc, char* argv[]) {	
	bpair_t arg = args(argc, argv);
	gfx_init(arg.first, arg.second);

	shaders();
	splash_screen_init();
	title_screen_init();

	scene_t* splash_screen = splash_screen_get_scene();
	scene_t* title_screen = title_screen_get_scene();

	short r = scene_manager_set_scene(splash_screen);
	scene_manager_set_scene(title_screen);

	return 0;
}

bpair_t args(int argc, char* argv[]) {
	bpair_t result = { false, false };
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "--fullscreen") == 0) {
			result.first = true;
		}
		if (strcmp(argv[i], "--vsync") == 0) {
			result.second = true;
		}
	}
	return result;
}

void shaders(void) {
	recipe_t basic = { "basic", "basic.vert", "basic.frag" };
	recipe_t cube = { "cube", "cube.vert", "cube.frag" };
	recipe_t direction_light = { "directional-light", "directional-light.vert", "directional-light.frag" };

	list_t shader_recipes;
	list_init(&shader_recipes, sizeof(recipe_t));
	list_add(&shader_recipes, &basic);
	list_add(&shader_recipes, &cube);
	list_add(&shader_recipes, &direction_light);

	shader_mgr_pre_compile(&shader_recipes);
}
