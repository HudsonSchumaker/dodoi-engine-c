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

bpair_t args(int argc, char* argv[]) {
	bpair_t result = { false, true };
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

int main(int argc, char* argv[]) {	
	vec3_t v0 = { 1.0f, 2.0f, 3.0f };
	vec3_t v1 = { 1.0f, 2.0f, 3.0f };
	vec3_t v2 = { 1.0f, 2.0f, 3.0f };
	vec3_t v3 = { 1.0f, 2.0f, 3.001f };


	set_t vset;
	set_init(&vset, sizeof(vec3_t), set_equals_vec3);
	set_add(&vset, &v0);
	set_add(&vset, &v1);
	set_add(&vset, &v2);
	set_add(&vset, &v2);
	set_add(&vset, &v3);

	for(int i = 0; i < vset.size; i++) {
		vec3_t* vec = (vec3_t*)set_get(&vset, i);
		printf("vec3_t[%d]: %f %f %f\n", i, vec->x, vec->y, vec->z);
	}













	bpair_t arg = args(argc, argv);
	gfx_init(arg.first, arg.second);
	
	splash_screen_init();
	title_screen_init();

	scene_t* splash_screen = splash_screen_get_scene();
	scene_t* title_screen = title_screen_get_scene();

	short r = scene_manager_set_scene(splash_screen);
	scene_manager_set_scene(title_screen);

	return 0;
}
